#include "Queue.h"


Queue::Queue()
{
	uv_mutex_init(&m_lock);
	uv_mutex_init(&m_readlock);
}

Queue::~Queue()
{
	uv_mutex_destroy(&m_lock);
	uv_mutex_destroy(&m_readlock);
}

void Queue::enqueue(char *object, size_t len)
{
	Element *e = new Element();
	e->data = new char[len];
	e->size = len;
	memcpy(e->data, object, len);

	uv_mutex_lock(&m_lock);
	m_queue.push_back(e);
	uv_mutex_unlock(&m_lock);
}

const ReadResponse Queue::read(uint32_t timeout)
{
	Element *e = NULL;

	uv_mutex_lock(&m_lock);
	if (!m_queue.empty()) {
		e = m_queue.front();
		m_queue.pop_front();
	}	
	uv_mutex_unlock(&m_lock);

	time_t expire = time(0) + timeout;
	std::stringstream elementqueueid;
	elementqueueid << expire << "-" << e;
	printf("%s\n", elementqueueid.str().c_str());

	ReadElement re;
	re.elementid = elementqueueid.str();
	re.expire = expire;

	uv_mutex_lock(&m_readlock);
	m_read[re.elementid] = e;
	m_expire.push(re);	
	uv_mutex_unlock(&m_readlock);

	ReadResponse response;
	response.set_data(e->data, e->size);
	response.set_queueentitiyid(re.elementid);
	response.set_queueid(m_queueid);
	
	return response;
}

DequeueResponse Queue::dequeue(const std::string &QueueEntityId)
{
	std::map<std::string, Element *>::iterator it;
	Element *e = NULL;

	uv_mutex_lock(&m_readlock);
	it = m_read.find(QueueEntityId);
	if (it != m_read.end()) {
		e = it->second;
		m_read.erase(it);
	}
	uv_mutex_unlock(&m_readlock);

	if (e != NULL) {
		delete[] e->data;
		delete e;
	}

	return DequeueResponse();
}

void Queue::timer_expire_cb()
{
	time_t now = time(0);
	std::map<std::string, Element *>::iterator it;
	Element *e = NULL;

	uv_mutex_lock(&m_readlock);
	while (!m_expire.empty()) {
		ReadElement re = m_expire.top();
		if (now < re.expire)
			break;		
		m_expire.pop();
		it = m_read.find(re.elementid);
		if (it != m_read.end()) {
			e = it->second;
			m_read.erase(it);
			/* Reinsert to queue */
			uv_mutex_lock(&m_lock);
			m_queue.push_front(e);
			uv_mutex_unlock(&m_lock);
		}
	}
	uv_mutex_unlock(&m_readlock);

}
