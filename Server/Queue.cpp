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
		m_read.erase(it);
	}
	uv_mutex_unlock(&m_readlock);

	return DequeueResponse();
}
