
#define SOKOL_IMPL
#define SOKOL_D3D11

#ifdef _DEBUG
#define SOKOL_WIN32_FORCE_MAIN
#endif

#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_glue.h"

#include "alittle_schedule.hpp"

static ALittleSchedule schedule;

void alittle_init()
{
    sg_desc desc = { 0 };
    desc.context = sapp_sgcontext();
    sg_setup(&desc);

    schedule.Setup();
}

void alittle_frame()
{
    schedule.Update();
}

void alittle_cleanup()
{
    schedule.Shutdown();
}

void alittle_event(const sapp_event* event)
{
	
}

sapp_desc sokol_main(int argc, char* argv[])
{
    sapp_desc desc = {0};
    desc.init_cb = alittle_init;
    desc.frame_cb = alittle_frame;
    desc.cleanup_cb = alittle_cleanup;
    desc.event_cb = alittle_event;

    return desc;
}