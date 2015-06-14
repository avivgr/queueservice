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
		char  *m_data;
		size_t m_size;
	public:
		Element(char *data, size_t len);
		~Element();

		char *data() { return m_data; }
		size_t size() { return m_size; }
	};

	class ExpirationEntry
	{
		time_t m_expire;
		std::string m_elementid;
	public:
		ExpirationEntry(time_t expire, std::string &elementid)
			: m_expire(expire), m_elementid(elementid) { }

		time_t expire() const { return m_expire; }
		std::string elementid() const { return m_elementid; }

		bool operator<(const ExpirationEntry &other) const {
			return this->expire() > other.expire();
		}
	};

	std::string m_queueid;
	uv_mutex_t m_lock;
	size_t m_max_mem;
	size_t m_current_mem;
	std::list<Element*> m_queue;

	uv_mutex_t m_readlock;
	std::priority_queue<ExpirationEntry> m_expire;
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

