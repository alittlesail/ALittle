
extern "C" {
    #include "net.h"
}
#include "../ServerSystem/ServerSchedule.h"

net* net_create()
{
    net* c = (net*)malloc(sizeof(net));
    net_init(c);
    return c;
}

void net_init(net* c)
{
    c->schedule = new ALittle::ServerSchedule();
    c->events = 0;
    c->wait_count = 0;
}

void net_clear(net* c)
{
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->Exit();
    delete schedule;
    while (c->events)
    {
        net_event* event = c->events;
        c->events = c->events->next;
        net_freeevent(event);
    }
}

void net_destroy(net* c)
{
    net_clear(c);
    free(c);
}

void net_exit(net* c)
{
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->Exit();
}

net_event* net_runone(net* c)
{
    if (c->events)
    {
        net_event* event = c->events;
        c->events = c->events->next;
        return event;
    }

    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    while (c->wait_count > 0 && c->events == 0)
        schedule->RunOne();

    if (c->events)
    {
        net_event* event = c->events;
        c->events = c->events->next;
        return event;
    }

    return 0;
}

void net_freeevent(net_event* event)
{
    if (event->content)
    {
        free(event->content->s);
        free(event->content);
    }
    free(event);
}

void net_addevent(net* c, net_event* event, int dec_wait)
{
    if (c->events == 0)
        c->events = event;
    else
        c->events->next = event;
    c->wait_count -= dec_wait;
}

void net_httpget(net* c, int id, const char* url)
{
    ++ c->wait_count;
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->HttpGet(c, id, url);
}

void net_httpdownload(net* c, int id, const char* url, const char* file_path)
{
    ++c->wait_count;
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->HttpDownload(c, id, url, file_path);
}

void net_httppost(net* c, int id, const char* url, const char* type, const char* content)
{
    ++c->wait_count;
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->HttpPost(c, id, url, type, content);
}

void net_httpupload(net* c, int id, const char* url, const char* file_path)
{
    ++c->wait_count;
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->HttpUpload(c, id, url, file_path);
}
