// Server.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#include "../Common/QueueService.pb.h"
#include "Queue.h"

#define DEFAULT_PORT 7000
#define DEFAULT_BACKLOG 128

uv_loop_t *loop;
struct sockaddr_in addr;

struct client_info
{

};

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
	buf->base = (char*)malloc(suggested_size);
	buf->len = suggested_size;
}

void echo_write(uv_write_t *req, int status) {
	if (status) {
		fprintf(stderr, "Write error %s\n", uv_strerror(status));
	}
	free(req);
}

void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
	if (nread < 0) {
		if (nread != UV_EOF)
			fprintf(stderr, "Read error %s\n", uv_err_name(nread));
		uv_close((uv_handle_t*)client, NULL);
	}
	else if (nread > 0) {
		uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
		uv_buf_t wrbuf = uv_buf_init(buf->base, nread);
		uv_write(req, client, &wrbuf, 1, echo_write);
	}

	if (buf->base)
		free(buf->base);
}

void on_new_connection(uv_stream_t *server, int status) {
	if (status < 0) {
		fprintf(stderr, "New connection error %s\n", uv_strerror(status));
		// error!
		return;
	}

	uv_tcp_t *client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
	uv_tcp_init(loop, client);
	if (uv_accept(server, (uv_stream_t*)client) == 0) {
		client->data = malloc(sizeof(struct client_info));
		uv_read_start((uv_stream_t*)client, alloc_buffer, echo_read);
	}
	else {
		uv_close((uv_handle_t*)client, NULL);
	}
}

#if 0
int main() {
	loop = uv_default_loop();

	uv_tcp_t server;
	uv_tcp_init(loop, &server);

	uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);

	uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
	int r = uv_listen((uv_stream_t*)&server, DEFAULT_BACKLOG, on_new_connection);
	if (r) {
		fprintf(stderr, "Listen error %s\n", uv_strerror(r));
		return 1;
	}
	return uv_run(loop, UV_RUN_DEFAULT);
}
#else 
int main(int argc, char* argv[])
{
	std::string name("myqueue");
	std::string id("100");
	Queue *q = new Queue(id, name);

	q->enqueue("aviv1", 5);
	q->enqueue("aviv2", 5);
	q->enqueue("aviv3", 5);
	q->enqueue("aviv4", 5);
	q->enqueue("aviv5", 5);
	q->enqueue("aviv6", 5);

	auto r1 = q->read(10);
	auto r2 = q->read(9);
	auto r3 = q->read(1);
	auto r4 = q->read(3);

	Sleep(3000);
	q->timer_expire_cb();

	q->dequeue(r1.queueentitiyid());
	q->dequeue("garbage");

	return 0;
}
#endif
