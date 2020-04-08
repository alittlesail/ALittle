
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
    c->pool = 0;
    c->pool_count = 0;
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
    while (c->pool)
    {
        net_event* event = c->pool;
        c->pool = c->pool->next;
        net_freeevent(event);
    }
    c->pool_count = 0;
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

void net_clearevent(net_event* event)
{
    if (event->content)
    {
        free(event->content->s);
        free(event->content);
    }
    if (event->error)
    {
        free(event->error->s);
        free(event->error);
    }
}

void net_freeevent(net_event* event)
{
    net_clearevent(event);
    free(event);
}

net_event* net_createevent(net* c)
{
    if (c->pool_count == 0)
        return (net_event*)calloc(1, sizeof(net_event));

    net_event* event = c->pool;
    c->pool = c->pool->next;
    -- c->pool_count;
    memset(event, 0, sizeof(net_event));
    return event;
}

void net_releaseevent(net* c, net_event* event)
{
    if (c->pool_count > 100)
    {
        net_freeevent(event);
        return;
    }

    net_clearevent(event);
    ++c->pool_count;
    c->pool->next = event;
    event->next = 0;
}

void net_addevent(net* c, net_event* event, int dec_wait)
{
    event->next = 0;
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

void net_httpstopget(net* c, int id)
{
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->HttpStopGet(c, id);
}

void net_httpstoppost(net* c, int id)
{
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->HttpStopPost(c, id);
}

void net_httpstopdownload(net* c, int id)
{
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->HttpStopDownload(c, id);
}

void net_httpstopupload(net* c, int id)
{
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->HttpStopUpload(c, id);
}

void net_timer(net* c, int delay_ms)
{
    ++c->wait_count;
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->Timer(c, delay_ms);
}
