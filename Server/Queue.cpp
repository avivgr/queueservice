#include "Queue.h"
#include "Util.h"

Queue::Queue(std::string &queueid, std::string &name)
	: m_queueid(queueid), m_name(name)
{
	uv_mutex_init(&m_lock);
	uv_mutex_init(&m_readlock);
}

Queue::~Queue()
{
	/* Empty the queue, and the read hashmap.
	   Since the timer cb grabs locks in certain
	   order, make sure to follow the same order to avoid deadlocks
	*/
	uv_mutex_lock(&m_readlock);
	uv_mutex_lock(&m_lock);
	while (!m_queue.empty()) {
		m_queue.pop_front();
	}
	m_read.clear();
	uv_mutex_unlock(&m_lock);
	uv_mutex_unlock(&m_readlock);

	uv_mutex_destroy(&m_lock);
	uv_mutex_destroy(&m_readlock);
}

Queue::Element::Element(const char *object, size_t len)
{
	/* allocate new data array and copy object */
	m_data = new char[len];
	m_size = len;
	memcpy(m_data, object, len);
}

Queue::Element::~Element()
{
	/* free data */
	delete[] m_data;
}

void Queue::enqueue(const char *object, size_t len)
{
	Element *e = new Element(object, len);

	uv_mutex_lock(&m_lock);
	m_queue.push_back(e);
	uv_mutex_unlock(&m_lock);
}

const ReadResponse Queue::read(uint32_t timeout)
{
	ReadResponse response;
	Element *e = NULL;

	/* first - dequeue an element from the list */
	uv_mutex_lock(&m_lock);
	if (!m_queue.empty()) {
		e = m_queue.front();
		m_queue.pop_front();
	}	
	uv_mutex_unlock(&m_lock);

	/* No entry - exit */
	if (e == NULL) {
		response.set_data(NULL, 0);
		response.set_queueentitiyid("-1");
		response.set_queueid(m_queueid);
		return response;
	}

	/* prepare new queue element id, and expire entry */
	time_t expire = time(0) + timeout;
	std::stringstream elementqueueid;
	elementqueueid << expire << "-" << e;
	pr_info("read - %s\n", elementqueueid.str().c_str());

	ExpirationEntry re(expire, elementqueueid.str());

	/* Save in map and expiry queue */
	uv_mutex_lock(&m_readlock);
	m_read[re.elementid()] = e;
	m_expire.push(re);	
	uv_mutex_unlock(&m_readlock);

	response.set_data(e->data(), e->size());
	response.set_queueentitiyid(re.elementid());
	response.set_queueid(m_queueid);

	return response;
}

bool Queue::dequeue(const std::string &QueueEntityId)
{
	std::map<std::string, Element *>::iterator it;
	Element *e = NULL;
	bool ret = false;

	/* Find the QueueEntityId in the read map */
	uv_mutex_lock(&m_readlock);
	it = m_read.find(QueueEntityId);
	if (it != m_read.end()) {
		e = it->second;
		m_read.erase(it);
	}
	uv_mutex_unlock(&m_readlock);

	if (e != NULL) {
		ret = true;
		delete e;
	}

	return ret;
}

/*
	timer callback - this routine is called every second.
	here we check for expired entries using the priority
	queue - and return them to the main fifo.
*/
void Queue::timer_expire_cb()
{
	time_t now = time(0);
	std::map<std::string, Element *>::iterator it;
	Element *e = NULL;

	uv_mutex_lock(&m_readlock);
	while (!m_expire.empty()) {
		ExpirationEntry re = m_expire.top();
		/* Expire now ?*/
		if (now < re.expire())
			break;		
		m_expire.pop();
		it = m_read.find(re.elementid());
		if (it != m_read.end()) {
			e = it->second;
			m_read.erase(it);
			/* Reinsert to queue - will be read again later */
			uv_mutex_lock(&m_lock);
			m_queue.push_front(e);	/* yes in the front ! */
			uv_mutex_unlock(&m_lock);
		}
	}
	uv_mutex_unlock(&m_readlock);
}
