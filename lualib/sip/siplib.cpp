
extern "C" {
#include "siplib.h"
}

#include <asio.hpp>

#include "carp_log.hpp"
#include "SipSchedule.h"

int luaopen_sip(lua_State* l_state)
{
	SipSchedule::Bind(l_state);
	lua_getglobal(l_state, "sip");
	return 1;
}

#define CARP_LOG_IMPL
#include "carp_log.hpp"