
#include <asio.hpp>

#ifdef _WIN32
#include <stdlib.h>
#include <crtdbg.h>
#endif // _WIN32

#include <SDL_main.h>

#include "alittle_schedule.hpp"

int main(int argc, char* argv[])
{
#ifdef _WIN32
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#endif // _WIN32	
	return s_alittle_schedule.Run(argc, argv);
}

#define ALITTLE_AUDIO_IMPL
#include "alittle_audio.hpp"
#define ALITTLE_CSV_IMPL
#include "alittle_csv.hpp"
#define ALITTLE_DISPLAY_IMPL
#include "alittle_display.hpp"
#define ALITTLE_FONT_IMPL
#include "alittle_font.hpp"
#define ALITTLE_INPUT_IMPL
#include "alittle_input.hpp"
#define ALITTLE_NET_IMPL
#include "alittle_net.hpp"
#define ALITTLE_QUAD_IMPL
#include "alittle_quad.hpp"
#define ALITTLE_RENDER_IMPL
#include "alittle_render.hpp"
#define ALITTLE_SCHEDULE_IMPL
#include "alittle_schedule.hpp"
#define ALITTLE_SCRIPT_IMPL
#include "alittle_script.hpp"
#define ALITTLE_SYSTEM_IMPL
#include "alittle_system.hpp"
#define ALITTLE_TEXT_IMPL
#include "alittle_text.hpp"
#define ALITTLE_DISPLAYVIEW_IMPL
#include "alittle_displayview.hpp"
#define ALITTLE_TEXTURE_IMPL
#include "alittle_texture.hpp"
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
#define CARP_SURFACE_IMPL
#include "Carp/carp_surface_bind.hpp"
#define CARP_MIXER_IMPL
#include "Carp/carp_sdl_mixer.hpp"