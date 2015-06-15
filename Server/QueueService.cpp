#include "QueueService.h"
#include "Util.h"

QueueService::QueueService()
{
	m_id = 1;
	uv_rwlock_init(&m_lock);
	m_exitThread = false;
	uv_thread_create(&m_thread, SThreadMain, this);
}

QueueService::~QueueService()
{
	m_exitThread = true;
	uv_thread_join(&m_thread);
	uv_rwlock_destroy(&m_lock);
}

/* this is an internal thread, which job is simply
	to call queue->timer_expire_cb() for each queue every second.
*/
void QueueService::ThreadMain()
{
	std::map<std::string, Queue *>::iterator it;

	while (!m_exitThread)
	{
		uv_rwlock_rdlock(&m_lock);
		for (it = m_idToQ.begin(); it != m_idToQ.end(); ++it)
		{
			Queue *q = it->second;
			q->timer_expire_cb();
		}
		uv_rwlock_rdunlock(&m_lock);
#ifdef WIN32
		Sleep(1000);
#else
		sleep(1);
#endif
	}
}

void QueueService::SThreadMain(void* arg)
{
	QueueService *_this = (QueueService *)arg;
	_this->ThreadMain();
}

std::string QueueService::CreateQueue(std::string name)
{
	std::string queueid;
	std::map<std::string, std::string>::iterator it;

	uv_rwlock_wrlock(&m_lock);
	/* If it is already there, return existing id */
	it = m_nameToId.find(name);
	if (it != m_nameToId.end()) {
		queueid = it->second;
	} else {
		/* Create a new queue */
		std::stringstream queueidss;
		queueidss << m_id++;
		queueid = queueidss.str();
		Queue *q = new Queue(queueid, name);
		m_idToQ[queueid] = q;
		m_nameToId[name] = queueid;
	}
	uv_rwlock_wrunlock(&m_lock);

	return queueid;
}

std::string QueueService::GetQueue(std::string name)
{
	std::string queueid = "-1";
	std::map<std::string, std::string>::iterator it;

	uv_rwlock_rdlock(&m_lock);
	it = m_nameToId.find(name);
	if (it != m_nameToId.end()) {
		queueid = it->second;
	}
	uv_rwlock_rdunlock(&m_lock);

	return queueid;
}

void QueueService::DeleteQueue(std::string queueid)
{
	std::map<std::string, std::string>::iterator it;
	std::map<std::string, Queue *>::iterator it2;

	/* remove id and name from both maps */
	uv_rwlock_wrlock(&m_lock);
	it2 = m_idToQ.find(queueid);
	if (it2 != m_idToQ.end()) {
		Queue *q = it2->second;
		m_idToQ.erase(it2);
		it = m_nameToId.find(q->name());
		if (it != m_nameToId.end())
			m_nameToId.erase(it);
		delete q;
	}
	uv_rwlock_wrunlock(&m_lock);
}

void QueueService::enqueue(std::string queueid, const char *object, size_t len)
{
	std::map<std::string, Queue *>::iterator it;

	uv_rwlock_rdlock(&m_lock);
	it = m_idToQ.find(queueid);
	if (it != m_idToQ.end()) {
		Queue *q = it->second;
		q->enqueue(object, len);
	}
	uv_rwlock_rdunlock(&m_lock);
}

ReadResponse QueueService::read(std::string queueid, uint32_t timeout)
{
	std::map<std::string, Queue *>::iterator it;
	ReadResponse resp;

	uv_rwlock_rdlock(&m_lock);
	it = m_idToQ.find(queueid);
	if (it != m_idToQ.end()) {
		Queue *q = it->second;
		resp = q->read(timeout);
	}
	uv_rwlock_rdunlock(&m_lock);

	return resp;
}

bool QueueService::dequeue(std::string queueid, const std::string &QueueEntityId)
{
	std::map<std::string, Queue *>::iterator it;
	bool ret = false;

	uv_rwlock_rdlock(&m_lock);
	it = m_idToQ.find(queueid);
	if (it != m_idToQ.end()) {
		Queue *q = it->second;
		ret = q->dequeue(QueueEntityId);
	}
	uv_rwlock_rdunlock(&m_lock);

	return ret;
}
