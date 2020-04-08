
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
    c->wait_count = 0;
    
    c->events = 0;
    c->events_pool = 0;
    c->events_pool_count = 0;

    c->rfactorys = 0;
    c->rfactorys_pool = 0;
    c->rfactorys_pool_count = 0;
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
    while (c->events_pool)
    {
        net_event* event = c->events_pool;
        c->events_pool = c->events_pool->next;
        net_freeevent(event);
    }
    c->events_pool_count = 0;

    while (c->rfactorys_pool)
    {
        read_factory* rfactory = c->rfactorys_pool;
        c->rfactorys_pool = c->rfactorys_pool->next;
        net_freerfactory(rfactory);
    }
    c->rfactorys_pool_count = 0;
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
    while ((c->wait_count > 0 || schedule->GetConnectCount() > 0)
        && c->events == 0 && !schedule->IsExit())
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
    event->rfactory = 0;
}

void net_freeevent(net_event* event)
{
    net_clearevent(event);
    free(event);
}

net_event* net_createevent(net* c)
{
    if (c->events_pool_count == 0)
        return (net_event*)calloc(1, sizeof(net_event));

    net_event* event = c->events_pool;
    c->events_pool = c->events_pool->next;
    -- c->events_pool_count;
    memset(event, 0, sizeof(net_event));
    return event;
}

void net_releaseevent(net* c, net_event* event)
{
    if (c->events_pool_count > 100)
    {
        net_freeevent(event);
        return;
    }

    net_clearevent(event);
    ++c->events_pool_count;
    if (c->events_pool)
        c->events_pool->next = event;
    else
        c->events_pool = event;
    event->next = 0;
}

void net_freerfactory(read_factory* rfactory)
{
    net_clearrfactory(rfactory);
    free(rfactory);
}

void net_clearrfactory(read_factory* rfactory)
{
    rfactory->id = 0;
    rfactory->last_read_size = 0;
    if (rfactory->memory) free(rfactory->memory);
    rfactory->memory = 0;
    rfactory->read_size = 0;
    rfactory->rpc_id = 0;
    rfactory->total_size = 0;
}

read_factory* net_createrfactory(net* c, char* memory, int memory_size)
{
    read_factory* rfactory = 0;
    if (c->rfactorys_pool_count == 0)
    {
        rfactory = (read_factory*)calloc(1, sizeof(read_factory));
    }
    else
    {
        rfactory = c->rfactorys_pool;
        c->rfactorys_pool = c->rfactorys_pool->next;
        --c->rfactorys_pool_count;
        memset(rfactory, 0, sizeof(read_factory));
    }

    rfactory->memory = memory;
    rfactory->total_size = memory_size;
    rfactory->total_size = net_rfactoryreadint(rfactory);
    rfactory->id = net_rfactoryreadint(rfactory);
    rfactory->rpc_id = net_rfactoryreadint(rfactory);

    return rfactory;
}

void net_releaserfactory(net* c, read_factory* rfactory)
{
    if (c->rfactorys_pool_count > 100)
    {
        net_freerfactory(rfactory);
        return;
    }

    net_clearrfactory(rfactory);
    ++c->rfactorys_pool_count;
    if (c->rfactorys_pool)
        c->rfactorys_pool->next = rfactory;
    else
        c->rfactorys_pool = rfactory;
    rfactory->next = 0;
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

void net_connect(net* c, int id, const char* ip, int port)
{
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->Connect(c, id, ip, port);
}

int net_isconnecting(net* c, int id)
{
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    return schedule->IsConnecting(c, id) ? 1 : 0;
}

int net_isconnected(net* c, int id)
{
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    return schedule->IsConnected(c, id) ? 1 : 0;
}

void net_close(net* c, int id)
{
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->Close(c, id);
}

void net_send(net* c, int id, write_factory* factory)
{
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->Send(c, id, factory);
}

void net_timer(net* c, int delay_ms)
{
    ++c->wait_count;
    ALittle::ServerSchedule* schedule = (ALittle::ServerSchedule*)(c->schedule);
    schedule->Timer(c, delay_ms);
}

write_factory* net_createwfactory()
{
    write_factory* factory = (write_factory*)malloc(sizeof(write_factory));
    net_wfactoryinit(factory);
	return factory;
}

void net_wfactoryinit(write_factory* c)
{
     kv_init(c->memory);
     c->id = 0;
     c->rpc_id = 0;
     c->size = 0;
}

void net_wfactoryclear(write_factory* c)
{
    kv_destroy(c->memory);
    c->id = 0;
    c->rpc_id = 0;
    c->size = 0;
}

void net_wfactorydestroy(write_factory* c)
{
    net_wfactoryclear(c);
    free(c);
}

void net_wfactorysetid(write_factory* c, int id)
{
    c->id = id;
}

void net_wfactorysetrpcid(write_factory* c, int rpc_id)
{
    c->rpc_id = rpc_id;
}

void net_wfactoryresetoffset(write_factory* c)
{
    c->size = 0;
}

int net_wfactorygetoffset(write_factory* c)
{
    return c->size;
}

void net_wfactorysetint(write_factory* c, int offset, int value)
{
    memcpy(&(kv_A(c->memory, offset)), &value, sizeof(int));
}

int net_wfactorywritebool(write_factory* c, char value)
{
    if (kv_size(c->memory) < c->size + sizeof(value))
        kv_resize(char, c->memory, c->size + sizeof(value));
    memcpy(&(kv_A(c->memory, c->size)), &value, sizeof(value));
    c->size += sizeof(value);
    return sizeof(value);
}

int net_wfactorywriteint(write_factory* c, int value)
{
    if (kv_size(c->memory) < c->size + sizeof(value))
        kv_resize(char, c->memory, c->size + sizeof(value));
    memcpy(&(kv_A(c->memory, c->size)), &value, sizeof(value));
    c->size += sizeof(value);
    return sizeof(value);
}

int net_wfactorywritelong(write_factory* c, long long value)
{
    if (kv_size(c->memory) < c->size + sizeof(value))
        kv_resize(char, c->memory, c->size + sizeof(value));
    memcpy(&(kv_A(c->memory, c->size)), &value, sizeof(value));
    c->size += sizeof(value);
    return sizeof(value);
}

int net_wfactorywritestring(write_factory* c, const char* value, int len)
{
    int total_size = len + sizeof(int) + 1;
    if (kv_size(c->memory) < c->size + total_size)
        kv_resize(char, c->memory, c->size + total_size);

    char* memory = &kv_A(c->memory, c->size);

    int str_len = len + 1; // include '\0'
    memcpy(memory, &str_len, sizeof(str_len));
    char* data_string = memory + sizeof(int);
    for (int i = 0; i < len; ++i)
        data_string[i] = value[i];
    data_string[len] = 0;

    c->size += total_size;

    return total_size;
}

int net_wfactorywritedouble(write_factory* c, double value)
{
    if (kv_size(c->memory) < c->size + sizeof(value))
        kv_resize(char, c->memory, c->size + sizeof(value));
    memcpy(&(kv_A(c->memory, c->size)), &value, sizeof(value));
    c->size += sizeof(value);
    return sizeof(value);
}

int net_rfactorygettotalsize(read_factory* c)
{
    return c->total_size;
}

int net_rfactoryreadbool(read_factory* c)
{
    if (c->read_size >= c->total_size || c->read_size < 0)
        return 0;
    bool value = 0;
    memcpy(&value, c->memory + c->read_size, sizeof(value));
    c->read_size += static_cast<int>(sizeof(value));
    c->last_read_size = static_cast<int>(sizeof(value));
    return value;
}

int net_rfactoryreadint(read_factory* c)
{
    if (c->read_size >= c->total_size || c->read_size < 0)
        return 0;
    int value = 0;
    memcpy(&value, c->memory + c->read_size, sizeof(value));
    c->read_size += static_cast<int>(sizeof(value));
    c->last_read_size = static_cast<int>(sizeof(value));
    return value;
}

long long net_rfactoryreadlong(read_factory* c)
{
    if (c->read_size >= c->total_size || c->read_size < 0)
        return 0;
    long long value = 0;
    memcpy(&value, c->memory + c->read_size, sizeof(value));
    c->read_size += static_cast<int>(sizeof(value));
    c->last_read_size = static_cast<int>(sizeof(value));
    return value;
}

double net_rfactoryreaddouble(read_factory* c)
{
    if (c->read_size >= c->total_size || c->read_size < 0)
        return 0;
    double value = 0;
    memcpy(&value, c->memory + c->read_size, sizeof(value));
    c->read_size += static_cast<int>(sizeof(value));
    c->last_read_size = static_cast<int>(sizeof(value));
    return value;
}

int net_rfactorygetreadsize(read_factory* c)
{
    return c->last_read_size;
}

const char* net_rfactoryreadstring(read_factory* c)
{
    if (c->read_size >= c->total_size || c->read_size < 0)
    {
        c->last_read_size = -1;
        return c->empty;
    }
    int len = 0; // include '\0'
    memcpy(&len, c->memory + c->read_size, sizeof(len));
    if (len <= 0)
    {
        c->last_read_size = -1;
        return c->empty;
    }
    const char* value = c->memory + c->read_size + sizeof(int);
    c->read_size += len + static_cast<int>(sizeof(int));
    c->last_read_size = len + static_cast<int>(sizeof(int));
    return value;
}
