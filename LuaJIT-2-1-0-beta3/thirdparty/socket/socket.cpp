
#include "SocketSchedule.h"
#include "SocketClient.h"
extern "C" {
    #include "socket.h"
}

struct _socket* socket_create()
{
    struct _socket* c = (struct _socket*)malloc(sizeof(struct _socket));
    socket_init(c);
    return c;
}

void socket_init(struct _socket* c)
{
    c->schedule = new ALittle::SocketSchedule();
    c->wait_count = 0;
    
    c->events = 0;
    c->events_pool = 0;
    c->events_pool_count = 0;
}

void socket_clear(struct _socket* c)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    schedule->Exit();
    delete schedule;
    while (c->events)
    {
        socket_event* event = c->events;
        c->events = c->events->next;
        socket_freeevent(event);
    }
    while (c->events_pool)
    {
        socket_event* event = c->events_pool;
        c->events_pool = c->events_pool->next;
        socket_freeevent(event);
    }
    c->events_pool_count = 0;
}

void socket_destroy(struct _socket* c)
{
    socket_clear(c);
    free(c);
}

void socket_exit(struct _socket* c)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    schedule->Exit();
}

socket_event* socket_runone(struct _socket* c)
{
    if (c->events)
    {
        socket_event* event = c->events;
        c->events = c->events->next;
        return event;
    }

    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    while ((c->wait_count > 0 || schedule->GetConnectCount() > 0) && c->events == 0 && !schedule->IsExit())
        schedule->RunOne();

    if (c->events)
    {
        socket_event* event = c->events;
        c->events = c->events->next;
        return event;
    }

    return 0;
}

socket_event* socket_pollone(struct _socket* c)
{
    if (c->events)
    {
        socket_event* event = c->events;
        c->events = c->events->next;
        return event;
    }

    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    if ((c->wait_count > 0 || schedule->GetConnectCount() > 0) && c->events == 0 && !schedule->IsExit())
        schedule->PollOne();

    if (c->events)
    {
        socket_event* event = c->events;
        c->events = c->events->next;
        return event;
    }

    return 0;
}

void socket_clearevent(socket_event* event)
{
    if (event->binary_value)
    {
        free(event->binary_value);
        event->binary_value = 0;
    }

    if (event->string_value)
    {
        free(event->string_value);
        event->string_value = 0;
    }
}

void socket_freeevent(socket_event* event)
{
    socket_clearevent(event);
    free(event);
}

socket_event* socket_createevent(struct _socket* c)
{
    if (c->events_pool_count == 0)
        return (socket_event*)calloc(1, sizeof(socket_event));

    socket_event* event = c->events_pool;
    c->events_pool = c->events_pool->next;
    -- c->events_pool_count;
    memset(event, 0, sizeof(socket_event));
    return event;
}

void socket_releaseevent(struct _socket* c, socket_event* event)
{
    if (c->events_pool_count > 100)
    {
        socket_freeevent(event);
        return;
    }

    socket_clearevent(event);
    ++c->events_pool_count;
    if (c->events_pool)
        c->events_pool->next = event;
    else
        c->events_pool = event;
    event->next = 0;
}

void socket_addevent(struct _socket* c, socket_event* event, int dec_wait)
{
    event->next = 0;
    if (c->events == 0)
        c->events = event;
    else
        c->events->next = event;
    c->wait_count -= dec_wait;
}

void socket_connect(struct _socket* c, int id, const char* ip, int port)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    schedule->Connect(c, id, ip, port);
}

void socket_close(struct _socket* c, int id)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    schedule->Close(c, id);
}

void socket_timer(struct _socket* c, int delay_ms)
{
    ++c->wait_count;
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    schedule->Timer(c, delay_ms);
}

void socket_readuint8(struct _socket* c, int id)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    client->ReadNumber(sizeof(unsigned char), socket_event_types::MSG_READ_UINT8);
}
void socket_readint8(struct _socket* c, int id)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->ReadNumber(sizeof(char), socket_event_types::MSG_READ_INT8);
}
void socket_readuint16(struct _socket* c, int id)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->ReadNumber(sizeof(unsigned short), socket_event_types::MSG_READ_UINT16);
}
void socket_readint16(struct _socket* c, int id)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->ReadNumber(sizeof(short), socket_event_types::MSG_READ_INT16);
}
void socket_readuint32(struct _socket* c, int id)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->ReadNumber(sizeof(unsigned int), socket_event_types::MSG_READ_UINT32);
}
void socket_readint32(struct _socket* c, int id)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->ReadNumber(sizeof(int), socket_event_types::MSG_READ_INT32);
}
void socket_readuint64(struct _socket* c, int id)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->ReadNumber(sizeof(unsigned long long), socket_event_types::MSG_READ_UINT64);
}
void socket_readint64(struct _socket* c, int id)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->ReadNumber(sizeof(long long), socket_event_types::MSG_READ_INT64);
}
void socket_readfloat(struct _socket* c, int id)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->ReadNumber(sizeof(float), socket_event_types::MSG_READ_FLOAT);
}
void socket_readdouble(struct _socket* c, int id)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->ReadNumber(sizeof(double), socket_event_types::MSG_READ_DOUBLE);
}
void socket_readbinary(struct _socket* c, int id, int len)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->ReadBinary(len, socket_event_types::MSG_READ_BINARY);
}
void socket_readstring(struct _socket* c, int id, int len)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->ReadString(len, socket_event_types::MSG_READ_STRING);
}

void socket_writeuint8(struct _socket* c, int id, unsigned char value)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->WriteNumber(value);
}
void socket_writeint8(struct _socket* c, int id, char value)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->WriteNumber(value);
}
void socket_writeuint16(struct _socket* c, int id, unsigned short value)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->WriteNumber(value);
}
void socket_writeint16(struct _socket* c, int id, short value)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->WriteNumber(value);
}
void socket_writeuint32(struct _socket* c, int id, unsigned int value)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->WriteNumber(value);
}
void socket_writeint32(struct _socket* c, int id, int value)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->WriteNumber(value);
}
void socket_writeuint64(struct _socket* c, int id, unsigned long long value)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->WriteNumber(value);
}
void socket_writeint64(struct _socket* c, int id, long long value)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->WriteNumber(value);
}
void socket_writefloat(struct _socket* c, int id, float value)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->WriteNumber(value);
}
void socket_writedouble(struct _socket* c, int id, double value)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (client) client->WriteNumber(value);
}
void socket_writebinary(struct _socket* c, int id, void* buffer, int size)
{
    ALittle::SocketSchedule* schedule = (ALittle::SocketSchedule*)(c->schedule);
    auto client = schedule->GetClient(id);
    if (!client) return;

    client->WriteBinary(buffer, size);
}
