
#ifdef _WIN32
#include <stdlib.h>
#include <crtdbg.h>
#endif // _WIN32

#include <SDL_main.h>

#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"

int main(int argc, char* argv[])
{
#ifdef _WIN32
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#endif // _WIN32	
	return g_ScheduleSystem.Run(argc, argv);
}