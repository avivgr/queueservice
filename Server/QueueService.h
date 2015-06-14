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
#include "Queue.h"

class QueueService
{
public:
	QueueService();
	virtual ~QueueService();
	virtual std::string CreateQueue(std::string & name);
	virtual std::string GetQueue(std::string & name);
	virtual void DeleteQueue(std::string & name);
	virtual void enqueue(std::string &queueid, char *object, size_t len);
	virtual ReadResponse read(std::string &queueid, uint32_t timeout);
	virtual DequeueResponse dequeue(std::string &queueid, const std::string &QueueEntityId);
};

