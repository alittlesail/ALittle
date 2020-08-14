#ifndef CARP_SCRIPT_INCLUDED
#define CARP_SCRIPT_INCLUDED

#include "lua.h"
#include "lauxlib.h"
#include "klib/kstring.h"

typedef struct  {
	lua_State* L;					// lua state
	kstring_t module_title;
	kstring_t string;
} _script_t;
static _script_t _script = {0};

void carp_script_setup(const char* module_title)
{
	kputs(module_title, &_script.module_title);

	// create state
	_script.L = luaL_newstate();
	if (!_script.L)
	{
		ALITTLE_SCRIPT_ERROR("lua_open failed!");
		return;
	}
}

void carp_script_shutdown()
{
	if (_script.L)
	{
		lua_close(_script.L);
		_script.L = 0;
	}
	free(ks_release(&_script.module_title));
	free(ks_release(&_script.string));
}

#endif