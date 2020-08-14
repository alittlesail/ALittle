#ifndef CARP_SCHEDULE_INCLUDED
#define CARP_SCHEDULE_INCLUDED

#define SOKOL_IMPL
#define SOKOL_D3D11
#define SOKOL_WIN32_FORCE_MAIN
#include "sokol/sokol_app.h"

#include "carp_dump.h"
#include "carp_log.h"
#include "carp_script.h"

typedef struct  {
    bool has_updater;
} _schedule_t;
static _schedule_t _schedule = {0};

void _schedule_setup(void)
{
    carp_log_setup();
	SOKOL_LOG("==>ScheduleSystem Setup Begin<==");
	carp_dump_setup("ALittleClient");
    carp_script_setup();
	
}

void _schedule_run(void)
{
	
}

void _schedule_event(const sapp_event* e)
{
}

void _schedule_shutdown(void)
{
    carp_script_shutdown();
    carp_log_shutdown();
	carp_dump_shutdown();
}

sapp_desc sokol_main(int argc, char* argv[])
{
    sapp_desc desc = { 0 };
    desc.init_cb = _schedule_setup;
    desc.frame_cb = _schedule_run;
    desc.cleanup_cb = _schedule_shutdown;
    desc.event_cb = _schedule_event;
    return desc;
}

#endif