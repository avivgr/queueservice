#ifndef __QUEUE_PROTOCOL__
#define __QUEUE_PROTOCOL__

#ifdef _MSC_VER
#pragma pack(push,1)
#define PACKED
#else
#define PACKED __attribute__ ((__packed__))
#endif

#define REQ_TYPE_ENQUEUE 1
#define REQ_TYPE_READ 2
#define REQ_TYPE_DEQUEUE 2
#define REQ_TYPE_CREATEQ 3
#define REQ_TYPE_GETQ 4
#define REQ_TYPE_DESTROYQ 5
struct request_hdr
{
	uint8_t req_type;
} PACKED;

struct enqueue_request
{
	struct request_hdr hdr;
} PACKED;































#ifdef _MSC_VER
#pragma pack(push,1)
#endif

#endif /* __QUEUE_PROTOCOL__ */