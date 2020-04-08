
#ifndef _ALITTLE_NET_H_
#define _ALITTLE_NET_H_

#include "../klib/kstring.h"
#include "../klib/kvec.h"

typedef enum
{
	HTTP_SUCCEED = 1,
	HTTP_FAILED = 2,

	HTTP_FILE_SUCCEED = 11,
	HTTP_FILE_FAILED = 12,
	HTTP_FILE_PROGRESS = 13,

	TIMER = 21,     // 定时器

	MSG_CONNECT_SUCCEED = 31,
	MSG_CONNECT_FAILED = 32,
	MSG_DISCONNECTED = 33,
	MSG_MESSAGE = 34,
} net_event_types;

typedef struct _read_factory
{
	char* memory;	// memory
	int read_size;		// read offset
	int total_size;		// total size
	int last_read_size;   // last read size
	int id;		// ID
	int rpc_id;
	char empty[1];

	struct _read_factory* next;
} read_factory;

typedef struct _write_factory
{
	kvec_t(char) memory;

	int id;	// 消息ID
	int rpc_id;	// RPCID
	unsigned int size; // 协议总大小
} write_factory;

typedef struct _net_event
{
	net_event_types type;
	int id;
	int cur_size;
	int total_size;
	kstring_t* content;
	kstring_t* error;
	read_factory* rfactory;
	int time;

	struct _net_event* next;
} net_event;

typedef struct _net
{
	void* schedule;
	int wait_count;

	net_event* events;
	net_event* events_pool;
	int events_pool_count;

	read_factory* rfactorys;
	read_factory* rfactorys_pool;
	int rfactorys_pool_count;
} net;

// 生命周期相关
net* net_create();
void net_init(net* c);
void net_clear(net* c);
void net_destroy(net* c);
void net_exit(net* c);
net_event* net_runone(net* c);

// 事件相关
void net_addevent(net* c, net_event* event, int dec_wait);

void net_freeevent(net_event* event);
void net_clearevent(net_event* event);
net_event* net_createevent(net* c);
void net_releaseevent(net* c, net_event* event);

void net_freerfactory(read_factory* rfactory);
void net_clearrfactory(read_factory* rfactory);
read_factory* net_createrfactory(net* c, char* memory, int memory_size);
void net_releaserfactory(net* c, read_factory* rfactory);

// http相关
void net_httpget(net* c, int id, const char* url);
void net_httpdownload(net* c, int id, const char* url, const char* file_path);
void net_httppost(net* c, int id, const char* url, const char* type, const char* content);
void net_httpupload(net* c, int id, const char* url, const char* file_path);
void net_httpstopget(net* c, int id);
void net_httpstopdownload(net* c, int id);
void net_httpstoppost(net* c, int id);
void net_httpstopupload(net* c, int id);

// 定时器相关
void net_timer(net* c, int delay_ms);

// 序列化反序列化相关
write_factory* net_createwfactory();
void net_wfactoryinit(write_factory* c);
void net_wfactoryclear(write_factory* c);
void net_wfactorydestroy(write_factory* c);

void net_wfactorysetid(write_factory* c, int id);
void net_wfactorysetrpcid(write_factory* c, int rpc_id);
void net_wfactoryresetoffset(write_factory* c);
int net_wfactorygetoffset(write_factory* c);
void net_wfactorysetint(write_factory* c, int offset, int value);
int net_wfactorywritebool(write_factory* c, char value);
int net_wfactorywriteint(write_factory* c, int value);
int net_wfactorywritelong(write_factory* c, long long value);
int net_wfactorywritestring(write_factory* c, const char* value, int len);
int net_wfactorywritedouble(write_factory* c, double value);

int net_rfactorygettotalsize(read_factory* c);
int net_rfactoryreadbool(read_factory* c);
int net_rfactoryreadint(read_factory* c);
long long net_rfactoryreadlong(read_factory* c);
const char* net_rfactoryreadstring(read_factory* c);
double net_rfactoryreaddouble(read_factory* c);
int net_rfactorygetreadsize(read_factory* c);

// 长连接相关
void net_connect(net* c, int id, const char* ip, int port);
int net_isconnected(net* c, int id);
int net_isconnecting(net* c, int id);
void net_close(net* c, int id);
void net_send(net* c, int id, write_factory* factory);

#endif // _ALITTLE_NET_H_
