
extern "C" {
#include "rtplib.h"
}

#include <asio.hpp>

#include "carp_log.hpp"
#include "RtpSchedule.h"

int luaopen_rtp(lua_State* l_state)
{
	RtpSchedule::Bind(l_state);
	lua_getglobal(l_state, "rtp");
	return 1;
}


#define CARP_LOG_IMPL
#include "carp_log.hpp"