#pragma once

#include <string>
#include <list>
#include <atomic>
#include "uv.h"

class Queue
{
	class Element
	{
	public:
		char  *data;
		size_t size;
	};

	uv_mutex_t m_lock;
	size_t m_max_mem;
	size_t m_current_mem;
	std::list<Element*> m_queue;

public:
	Queue();
	virtual ~Queue();

	// Enqueue the object into the queue
	virtual void enqueue(char *object, size_t len);

	// Read an object from the queue.
	// This object will not be returned as a response to
	// another read until the given timeout has expired.
	// Once dequeue is called then the object will not be
	// returned by a subsequent read.
	virtual /*ReadResponse*/ void read(uint32_t timeout);

	// Dequeue the object with the given QueueEntityId.
	// A dequeue permanently removes the object from the queue.
	virtual void dequeue(const std::string &QueueEntityId);
};

