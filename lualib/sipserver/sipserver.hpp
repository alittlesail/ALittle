#ifndef SIPSERVER_INCLUDED
#define SIPSERVER_INCLUDED

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/time.h>
#endif

#include "osip2/osip.h"

class SipServer
{
public:
    SipServer()
    {
        osip_init(&m_osip);
    }

    ~SipServer()
    {
        osip_release(m_osip);
    }

private:
    osip_t* m_osip = nullptr;
};

#endif
