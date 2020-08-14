#ifndef CARP_SCHEDULE_INCLUDED
#define CARP_SCHEDULE_INCLUDED

#define SOKOL_IMPL
#define SOKOL_D3D11
#include "sokol_app.h"

#include "carp_dump.h"
#include "carp_log.h"

typedef struct  {
    bool has_updater;
} _schedule_t;
static _schedule_t _schedule;

void _schedule_setup(void)
{
	SOKOL_LOG("==>ScheduleSystem Setup Begin<==");
	carp_dump_setup("ALittleClient");
}

void _schedule_run(void)
{
	
}

void _schedule_event(const sapp_event* e)
{
}

void _schedule_shutdown(void)
{
	carp_dump_shutdown();
    carp_log_shutdown();
}

sapp_desc sokol_main(int argc, char* argv[]) {
    sapp_desc desc = { 0 };
    desc.init_cb = _schedule_setup;
    desc.frame_cb = _schedule_run;
    desc.cleanup_cb = _schedule_shutdown;
    desc.event_cb = _schedule_event;
    return desc;
}

#endif