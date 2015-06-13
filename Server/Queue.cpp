#include "Queue.h"


Queue::Queue()
{
	uv_mutex_init(&m_lock);
}

Queue::~Queue()
{
	uv_mutex_destroy(&m_lock);
}

void Queue::enqueue(char *object, size_t len)
{

}

/*ReadResponse*/ void Queue::read(uint32_t timeout)
{

}

void Queue::dequeue(const std::string &QueueEntityId)
{

}
