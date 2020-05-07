
#ifndef _ALITTLE_socket_H_
#define _ALITTLE_socket_H_

#include "../klib/kstring.h"
#include "../klib/kvec.h"
#include "lua.h"

typedef enum
{
	TIMER = 21,     // 定时器

	MSG_CONNECT_SUCCEED = 31,
	MSG_CONNECT_FAILED = 32,
	MSG_DISCONNECTED = 33,
	MSG_READ_UINT8 = 34,
	MSG_READ_INT8 = 35,
	MSG_READ_UINT16 = 36,
	MSG_READ_INT16 = 37,
	MSG_READ_UINT32 = 38,
	MSG_READ_INT32 = 39,
	MSG_READ_UINT64 = 40,
	MSG_READ_INT64 = 41,
	MSG_READ_FLOAT = 42,
	MSG_READ_DOUBLE = 43,
	MSG_READ_PROTOBUF = 44,
} socket_event_types;

typedef struct _socket_event
{
	socket_event_types type;
	int id;
	int time;
	long long int_value;
	double double_value;
	char* protobuf_name;
	void* protobuf_value;
	struct _socket_event* next;
} socket_event;

struct _socket
{
	void* schedule;
	int wait_count;

	socket_event* events;
	socket_event* events_pool;
	int events_pool_count;
};

// 生命周期相关
struct _socket* socket_create();
void socket_init(struct _socket* c);
void socket_clear(struct _socket* c);
void socket_destroy(struct _socket* c);
void socket_exit(struct _socket* c);
socket_event* socket_runone(struct _socket* c);

// 事件相关
void socket_addevent(struct _socket* c, socket_event* event, int dec_wait);

void socket_freeevent(socket_event* event);
void socket_clearevent(socket_event* event);
socket_event* socket_createevent(struct _socket* c);
void socket_releaseevent(struct _socket* c, socket_event* event);

// 定时器相关
void socket_timer(struct _socket* c, int delay_ms);

// 长连接相关
void socket_connect(struct _socket* c, int id, const char* ip, int port);
void socket_close(struct _socket* c, int id);

void socket_readuint8(struct _socket* c, int id);
void socket_readint8(struct _socket* c, int id);
void socket_readuint16(struct _socket* c, int id);
void socket_readint16(struct _socket* c, int id);
void socket_readuint32(struct _socket* c, int id);
void socket_readint32(struct _socket* c, int id);
void socket_readuint64(struct _socket* c, int id);
void socket_readint64(struct _socket* c, int id);
void socket_readfloat(struct _socket* c, int id);
void socket_readdouble(struct _socket* c, int id);
void socket_readprotobuf(struct _socket* c, int id, const char* name, int len);

void socket_writeuint8(struct _socket* c, int id, unsigned char value);
void socket_writeint8(struct _socket* c, int id, char value);
void socket_writeuint16(struct _socket* c, int id, unsigned short value);
void socket_writeint16(struct _socket* c, int id, short value);
void socket_writeuint32(struct _socket* c, int id, unsigned int value);
void socket_writeint32(struct _socket* c, int id, int value);
void socket_writeuint64(struct _socket* c, int id, unsigned long long value);
void socket_writeint64(struct _socket* c, int id, long long value);
void socket_writefloat(struct _socket* c, int id, float value);
void socket_writedouble(struct _socket* c, int id, double value);
void socket_writeprotobuf(struct _socket* c, int id, const char* name, lua_State* L, int index);

int socket_calcprotobufsize(struct _socket* c, const char* name, lua_State* L, int index);


#endif // _ALITTLE_socket_H_
