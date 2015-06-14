#pragma once

#include <string>
#include <list>
#include <atomic>
#include <map>
#include <queue>
#include <ctime>
#include <sstream>

#include "uv.h"
#include "../Common/QueueService.pb.h"

class Queue
{
	class Element
	{
	public:
		char  *data;
		size_t size;
	};

	class ReadElement
	{
	public:
		time_t expire;
		std::string elementid;

		bool operator<(const ReadElement &other) const {
			return this->expire > other.expire;
		}
	};

	std::string m_queueid;
	uv_mutex_t m_lock;
	size_t m_max_mem;
	size_t m_current_mem;
	std::list<Element*> m_queue;

	uv_mutex_t m_readlock;
	std::priority_queue<ReadElement> m_expire;
	std::map<std::string, Element *> m_read;

public:
	Queue();
	virtual ~Queue();

	void timer_expire_cb();

	// Enqueue the object into the queue
	virtual void enqueue(char *object, size_t len);

	// Read an object from the queue.
	// This object will not be returned as a response to
	// another read until the given timeout has expired.
	// Once dequeue is called then the object will not be
	// returned by a subsequent read.
	virtual const ReadResponse read(uint32_t timeout);

	// Dequeue the object with the given QueueEntityId.
	// A dequeue permanently removes the object from the queue.
	virtual DequeueResponse dequeue(const std::string &QueueEntityId);
};

