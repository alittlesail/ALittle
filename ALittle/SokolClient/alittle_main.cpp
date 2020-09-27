
#include <asio.hpp>

#define CARP_CONSOLE_IMPL
#include "Carp/carp_console.hpp"
#define CARP_DUMP_IMPL
#include "Carp/carp_dump.hpp"
#define CARP_LOG_IMPL
#include "Carp/carp_log.hpp"
#define CARP_TASK_CONSUMER_IMPL
#include "Carp/carp_task_consumer.hpp"
#define CARP_SCHEDULE_IMPL
#include "Carp/carp_schedule.hpp"

#define ALITTLE_SCHEDULE_IMPL
#include "alittle_schedule.hpp"
#define ALITTLE_SCRIPT_IMPL
#include "alittle_script.hpp"
#define ALITTLE_AUDIO_IMPL
#include "alittle_audio.hpp"
#define ALITTLE_NET_IMPL
#include "alittle_net.hpp"
#define ALITTLE_CSV_IMPL
#include "alittle_csv.hpp"
#define ALITTLE_SURFACE_IMPL
#include "alittle_surface.hpp"
#define ALITTLE_FONT_IMPL
#include "alittle_font.hpp"

#define SOKOL_IMPL
#define SOKOL_D3D11

#ifdef _DEBUG
#define SOKOL_WIN32_FORCE_MAIN
#endif

#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_glue.h"

#define CARP_RWOPS_HPP_IMPL
#include "Carp/carp_rwops.hpp"

#define CARP_MIXER_IMPL
#include "Carp/carp_mixer.hpp"

void alittle_init()
{
    sg_desc desc = { 0 };
    desc.context = sapp_sgcontext();
    sg_setup(&desc);

    s_alittle_schedule.Setup();
}

void alittle_frame()
{
    s_alittle_schedule.Update();
}

void alittle_cleanup()
{
    s_alittle_schedule.Shutdown();
}

void alittle_event(const sapp_event* event)
{
	
}

sapp_desc sokol_main(int argc, char* argv[])
{
	// 保存参数，用于启动使用
    s_alittle_schedule.SetArgs(argc, argv);
	
    sapp_desc desc = {0};
    desc.init_cb = alittle_init;
    desc.frame_cb = alittle_frame;
    desc.cleanup_cb = alittle_cleanup;
    desc.event_cb = alittle_event;
    return desc;
}