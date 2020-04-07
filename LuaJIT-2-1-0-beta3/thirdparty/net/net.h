
#ifndef _ALITTLE_NET_H_
#define _ALITTLE_NET_H_

#include "../klib/kstring.h"

typedef enum
{
	HTTP_SUCCEED = 1,
	HTTP_FAILED = 2,

	HTTP_FILE_SUCCEED = 11,
	HTTP_FILE_FAILED = 12,
	HTTP_FILE_PROGRESS = 13,
} net_event_types;

typedef struct _net_event
{
	net_event_types type;
	int id;
	int cur_size;
	int total_size;
	kstring_t* content;
	struct _net_event* next;
} net_event;

typedef struct _net
{
	void* schedule;
	net_event* events;
	int wait_count;
} net;

net* net_create();
void net_init(net* c);
void net_clear(net* c);
void net_destroy(net* c);
void net_exit(net* c);
net_event* net_runone(net* c);
void net_addevent(net* c, net_event* event, int dec_wait);
void net_freeevent(net_event* event);
void net_httpget(net* c, int id, const char* url);
void net_httpdownload(net* c, int id, const char* url, const char* file_path);
void net_httppost(net* c, int id, const char* url, const char* type, const char* content);
void net_httpupload(net* c, int id, const char* url, const char* file_path);

#endif // _ALITTLE_NET_H_
