#pragma once

#include <string>
#include <list>
#include <map>
#include <queue>
#include <ctime>
#include <sstream>

#include "uv.h"
#include "../Common/QueueService.pb.h"
#include "Queue.h"

/*
	Queue Service - is a thread safe container for queues
*/
class QueueService
{
	uv_rwlock_t m_lock;		/* all regular queue operations are done with read lock held */
	std::map<std::string, std::string> m_nameToId;
	std::map<std::string, Queue *> m_idToQ;
	uint32_t m_id;
	uv_thread_t m_thread;
	bool m_exitThread;

	virtual void ThreadMain();
	static void SThreadMain(void* arg);

public:
	QueueService();
	virtual ~QueueService();
	virtual std::string CreateQueue(std::string name);
	virtual std::string GetQueue(std::string name);
	virtual void DeleteQueue(std::string queueid);
	virtual void enqueue(std::string queueid, const char *object, size_t len);
	virtual ReadResponse read(std::string queueid, uint32_t timeout);
	virtual bool dequeue(std::string queueid, const std::string &QueueEntityId);
};

