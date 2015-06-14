#include "QueueService.h"


QueueService::QueueService()
{
}

QueueService::~QueueService()
{
}

std::string QueueService::CreateQueue(std::string &name)
{
	return std::string();
}

std::string QueueService::GetQueue(std::string &name)
{
	return std::string();
}

void QueueService::DeleteQueue(std::string & name)
{
}

void QueueService::enqueue(std::string &queueid, char *object, size_t len)
{

}

ReadResponse QueueService::read(std::string &queueid, uint32_t timeout)
{
	return ReadResponse();
}

DequeueResponse QueueService::dequeue(std::string &queueid, const std::string &QueueEntityId)
{
	return DequeueResponse();
}
