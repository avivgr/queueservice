// Server.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#ifndef WIN32
#include <unistd.h>  /* getopt */
#else
extern char	*optarg;
int getopt(int nargc, char * const nargv[], char *ostr);
#endif

#include "../Common/QueueService.pb.h"
#include "Queue.h"
#include "QueueService.h"
#include "Util.h"

#define DEFAULT_BIND_HOST     "0.0.0.0"
#define DEFAULT_BIND_PORT     7001
#define DEFAULT_IDLE_TIMEOUT  (1000)
#ifndef INET6_ADDRSTRLEN
# define INET6_ADDRSTRLEN 63
#endif

typedef struct {
	const char *bind_host;
	unsigned short bind_port;
	unsigned int idle_timeout;
} server_config;

typedef struct {
	unsigned int idle_timeout;
	uv_tcp_t tcp_handle;
	uv_loop_t *loop;
} server_ctx;

/* A connection is modeled as an abstraction on top of two simple state
* machines, one for reading and one for writing.  Either state machine
* is, when active, in one of three states: busy, done or stop; the fourth
* and final state, dead, is an end state and only relevant when shutting
* down the connection.  A short overview:
*
*                          busy                  done           stop
*  ----------|---------------------------|--------------------|------|
*  readable  | waiting for incoming data | have incoming data | idle |
*  writable  | busy writing out data     | completed write    | idle |
*
* We could remove the done state from the writable state machine. For our
* purposes, it's functionally equivalent to the stop state.
*
* An interesting deviation from libuv's I/O model is that reads are discrete
* rather than continuous events.  In layman's terms, when a read operation
* completes, the connection stops reading until further notice.
*
* The rationale for this approach is that we have to wait until the request
* completes (and response is sent) before we can reuse the read buffer.
*/
enum conn_state {
	c_busy,  /* Busy; waiting for incoming data or for a write to complete. */
	c_done,  /* Done; read incoming data or write finished. */
	c_stop,  /* Stopped. */
	c_dead
};

struct client_ctx;
typedef struct {
	struct client_ctx *client;  /* Backlink to owning client context. */
	conn_state rdstate;
	conn_state wrstate;
	ssize_t result;
	union {
		uv_handle_t handle;
		uv_stream_t stream;
		uv_tcp_t tcp;
	} handle;
	uv_timer_t timer_handle;
	uv_write_t write_req;
	uv_req_t req;
	char buf[2048];
} conn;

/* Protocol parsing:

	read_size - read 2 bytes specifying the request expected data size in bytes.
	            we need to delianate data so we can feed it into protobuf.
	read_request - read request data, we read n bytes based on read_size.
	process_request - let a worker thread process the request, and produce a response
	write_response - write the response back to the client
*/
enum protocol_state
{
	read_size = 1,
	read_request = 2,
	process_request = 3,
	write_response = 4
};

typedef struct client_ctx
{
	protocol_state state;
	server_ctx *sx;  /* Backlink to owning server context. */
	conn incoming;  /* Connection with the client. */
} client_ctx;

typedef struct
{
	uv_getaddrinfo_t getaddrinfo_req;
	server_config config;
	server_ctx *servers;
	uv_loop_t *loop;
} server_state;


static void do_next(client_ctx *cx) {
	int new_state;
#if 0
	ASSERT(cx->state != s_dead);
	switch (cx->state) {
	case s_handshake:
		new_state = do_handshake(cx);
		break;
	case s_handshake_auth:
		new_state = do_handshake_auth(cx);
		break;
	case s_req_start:
		new_state = do_req_start(cx);
		break;
	case s_req_parse:
		new_state = do_req_parse(cx);
		break;
	case s_req_lookup:
		new_state = do_req_lookup(cx);
		break;
	case s_req_connect:
		new_state = do_req_connect(cx);
		break;
	case s_proxy_start:
		new_state = do_proxy_start(cx);
		break;
	case s_proxy:
		new_state = do_proxy(cx);
		break;
	case s_kill:
		new_state = do_kill(cx);
		break;
	case s_almost_dead_0:
	case s_almost_dead_1:
	case s_almost_dead_2:
	case s_almost_dead_3:
	case s_almost_dead_4:
		new_state = do_almost_dead(cx);
		break;
	default:
		UNREACHABLE();
	}
	cx->state = new_state;

	if (cx->state == s_dead) {
		if (DEBUG_CHECKS) {
			memset(cx, -1, sizeof(*cx));
		}
		free(cx);
	}
#endif
}

static int do_handshake(client_ctx *cx) {

}

static void conn_close_done(uv_handle_t *handle)
{
	conn *c;

	c = (conn *)handle->data;
	do_next(c->client);
}

static void conn_close(conn *c) {
	ASSERT(c->rdstate != c_dead);
	ASSERT(c->wrstate != c_dead);
	c->rdstate = c_dead;
	c->wrstate = c_dead;
	c->timer_handle.data = c;
	c->handle.handle.data = c;
	uv_close(&c->handle.handle, conn_close_done);
	uv_close((uv_handle_t *)&c->timer_handle, conn_close_done);
}

static int do_kill(client_ctx *cx)
{

	conn_close(&cx->incoming);
	return 0;
}

static void conn_timer_expire(uv_timer_t *handle)
{
	conn *c;

	c = CONTAINER_OF(handle, conn, timer_handle);
	c->result = UV_ETIMEDOUT;
	do_next(c->client);
}

static void conn_timer_reset(conn *c)
{
	CHECK(0 == uv_timer_start(&c->timer_handle,
		conn_timer_expire,
		c->client->sx->idle_timeout,
		0));
}

static void conn_alloc(uv_handle_t *handle, size_t size, uv_buf_t *buf) {
	conn *c;

	c = CONTAINER_OF(handle, conn, handle);
	ASSERT(c->rdstate == c_busy);
	buf->base = c->buf;
	buf->len = sizeof(c->buf);
}

static void conn_read_done(uv_stream_t *handle,
	ssize_t nread,
	const uv_buf_t *buf) {
	conn *c;

	c = CONTAINER_OF(handle, conn, handle);
	ASSERT(c->buf == buf->base);
	ASSERT(c->rdstate == c_busy);
	c->rdstate = c_done;
	c->result = nread;

	uv_read_stop(&c->handle.stream);
	do_next(c->client);
}

static void conn_read(conn *c)
{
	ASSERT(c->rdstate == c_stop);
	CHECK(0 == uv_read_start(&c->handle.stream, conn_alloc, conn_read_done));
	c->rdstate = c_busy;
	conn_timer_reset(c);
}

static void conn_write_done(uv_write_t *req, int status)
{
	conn *c;

	if (status == UV_ECANCELED) {
		return;  /* Handle has been closed. */
	}

	c = CONTAINER_OF(req, conn, write_req);
	ASSERT(c->wrstate == c_busy);
	c->wrstate = c_done;
	c->result = status;
	do_next(c->client);
}

static void conn_write(conn *c, const void *data, unsigned int len) {
	uv_buf_t buf;

	ASSERT(c->wrstate == c_stop || c->wrstate == c_done);
	c->wrstate = c_busy;

	/* It's okay to cast away constness here, uv_write() won't modify the
	* memory.
	*/
	buf.base = (char *)data;
	buf.len = len;

	CHECK(0 == uv_write(&c->write_req,
		&c->handle.stream,
		&buf,
		1,
		conn_write_done));
	conn_timer_reset(c);
}

void client_finish_init(server_ctx *sx, client_ctx *cx)
{
	conn *incoming;

	cx->sx = sx;
	cx->state = read_size;

	incoming = &cx->incoming;
	incoming->client = cx;
	incoming->result = 0;
	incoming->rdstate = c_stop;
	incoming->wrstate = c_stop;
	CHECK(0 == uv_timer_init(sx->loop, &incoming->timer_handle));

	/* Wait for the initial packet. */
	conn_read(incoming);
}

static void on_connection(uv_stream_t *server, int status)
{
	server_ctx *sx;
	client_ctx *cx;

	CHECK(status == 0);
	sx = CONTAINER_OF(server, server_ctx, tcp_handle);
	cx = (client_ctx *)xmalloc(sizeof(*cx));
	CHECK(0 == uv_tcp_init(sx->loop, &cx->incoming.handle.tcp));
	CHECK(0 == uv_accept(server, &cx->incoming.handle.stream));
	client_finish_init(sx, cx);
}

/* Bind a server to each address that getaddrinfo() reported. */
static void do_bind(uv_getaddrinfo_t *req, int status, struct addrinfo *addrs)
{
	char addrbuf[INET6_ADDRSTRLEN + 1];
	unsigned int ipv4_naddrs;
	unsigned int ipv6_naddrs;
	server_state *state;
	server_config *cf;
	struct addrinfo *ai;
	const void *addrv;
	const char *what;
	uv_loop_t *loop;
	server_ctx *sx;
	unsigned int n;
	int err;
	union {
		struct sockaddr addr;
		struct sockaddr_in addr4;
		struct sockaddr_in6 addr6;
	} s;

	state = CONTAINER_OF(req, server_state, getaddrinfo_req);
	loop = state->loop;
	cf = &state->config;

	if (status < 0) {
		pr_err("getaddrinfo(\"%s\"): %s", cf->bind_host, uv_strerror(status));
		uv_freeaddrinfo(addrs);
		return;
	}

	ipv4_naddrs = 0;
	ipv6_naddrs = 0;
	for (ai = addrs; ai != NULL; ai = ai->ai_next) {
		if (ai->ai_family == AF_INET) {
			ipv4_naddrs += 1;
		}
		else if (ai->ai_family == AF_INET6) {
			ipv6_naddrs += 1;
		}
	}

	if (ipv4_naddrs == 0 && ipv6_naddrs == 0) {
		pr_err("%s has no IPv4/6 addresses", cf->bind_host);
		uv_freeaddrinfo(addrs);
		return;
	}

	state->servers =
		(server_ctx *)xmalloc((ipv4_naddrs + ipv6_naddrs) * sizeof(state->servers[0]));

	n = 0;
	for (ai = addrs; ai != NULL; ai = ai->ai_next) {
		if (ai->ai_family != AF_INET && ai->ai_family != AF_INET6) {
			continue;
		}

		if (ai->ai_family == AF_INET) {
			s.addr4 = *(const struct sockaddr_in *) ai->ai_addr;
			s.addr4.sin_port = htons(cf->bind_port);
			addrv = &s.addr4.sin_addr;
		}
		else if (ai->ai_family == AF_INET6) {
			s.addr6 = *(const struct sockaddr_in6 *) ai->ai_addr;
			s.addr6.sin6_port = htons(cf->bind_port);
			addrv = &s.addr6.sin6_addr;
		}
		else {
			UNREACHABLE();
		}

		if (uv_inet_ntop(s.addr.sa_family, addrv, addrbuf, sizeof(addrbuf))) {
			UNREACHABLE();
		}

		sx = state->servers + n;
		sx->loop = loop;
		sx->idle_timeout = state->config.idle_timeout;
		CHECK(0 == uv_tcp_init(loop, &sx->tcp_handle));

		what = "uv_tcp_bind";
		err = uv_tcp_bind(&sx->tcp_handle, &s.addr, 0);
		if (err == 0) {
			what = "uv_listen";
			err = uv_listen((uv_stream_t *)&sx->tcp_handle, 128, on_connection);
		}

		if (err != 0) {
			pr_err("%s(\"%s:%hu\"): %s",
				what,
				addrbuf,
				cf->bind_port,
				uv_strerror(err));
			while (n > 0) {
				n -= 1;
				uv_close((uv_handle_t *)(state->servers + n), NULL);
			}
			break;
		}

		pr_info("listening on %s:%hu", addrbuf, cf->bind_port);
		n += 1;
	}

	uv_freeaddrinfo(addrs);
}

int server_run(const server_config *cf, uv_loop_t *loop)
{
	struct addrinfo hints;
	server_state state;
	int err;

	memset(&state, 0, sizeof(state));
	state.servers = NULL;
	state.config = *cf;
	state.loop = loop;

	/* Resolve the address of the interface that we should bind to.
	* The getaddrinfo callback starts the server and everything else.
	*/
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	err = uv_getaddrinfo(loop,
		&state.getaddrinfo_req,
		do_bind,
		cf->bind_host,
		NULL,
		&hints);
	if (err != 0) {
		pr_err("getaddrinfo: %s", uv_strerror(err));
		return err;
	}

	/* Start the event loop.  Control continues in do_bind(). */
	if (uv_run(loop, UV_RUN_DEFAULT)) {
		abort();
	}

	uv_loop_delete(loop);
	free(state.servers);
	return 0;
}

static void usage(char *progname) {
	printf("Usage:\n"
		"\n"
		"  %s [-b <address> [-h] [-p <port>]\n"
		"\n"
		"Options:\n"
		"\n"
		"  -b <hostname|address>  Bind to this address or hostname.\n"
		"                         Default: \"127.0.0.1\"\n"
		"  -h                     Show this help message.\n"
		"  -p <port>              Bind to this port number.  Default: 1080\n"
		"",
		progname);
	exit(1);
}

static void parse_opts(server_config *cf, int argc, char **argv)
{
	int opt;

	while (-1 != (opt = getopt(argc, argv, "H:hp:"))) {
		switch (opt) {
		case 'H':
			cf->bind_host = optarg;
			break;

		case 'p':
			if (1 != sscanf(optarg, "%hu", &cf->bind_port)) {
				pr_err("bad port number: %s", optarg);
				usage(argv[0]);
			}
			break;

		default:
			usage(argv[0]);
		}
	}
}

int main(int argc, char **argv)
{
	server_config config;
	int err;

	memset(&config, 0, sizeof(config));
	config.bind_host = DEFAULT_BIND_HOST;
	config.bind_port = DEFAULT_BIND_PORT;
	config.idle_timeout = DEFAULT_IDLE_TIMEOUT;
	parse_opts(&config, argc, argv);

	err = server_run(&config, uv_default_loop());
	if (err) {
		exit(1);
	}

	return 0;
}

#if 1

#else
int main(int argc, char* argv[])
{
	std::string name("myqueue");
	std::string id;
	QueueService *s = new QueueService();
	id = s->CreateQueue(name);

	s->enqueue(id, "aviv1", 5);
	s->enqueue(id, "aviv2", 5);
	s->enqueue(id, "aviv3", 5);
	s->enqueue(id, "aviv4", 5);
	s->enqueue(id, "aviv5", 5);
	s->enqueue(id, "aviv6", 5);

	auto r1 = s->read(id, 10);
	auto r2 = s->read(id, 9);
	auto r3 = s->read(id, 1);
	auto r4 = s->read(id, 3);

	//Sleep(3000);
	//q->timer_expire_cb();

	s->dequeue(id, r1.queueentitiyid());
	s->dequeue(id, "garbage");

	Request r11;
	r11.set_type(Request::ENQUEUE);
	EnqueueRequest er;
	er.set_data("12345");
	er.set_queueid(id);
	r11.set_allocated_enqueue(&er);
	char d[100] = { 0 };
	r11.SerializeToArray(d, 100);

	Request r;
	r.ParsePartialFromArray(d, 5);

	return 0;
}
#endif
