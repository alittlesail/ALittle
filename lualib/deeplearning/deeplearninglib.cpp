
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "deeplearninglib.h"
}
#include <LuaBridge/LuaBridge.h>

#include "deeplearning_xor.hpp"

void DyNetInitialize()
{
	dynet::DynetParams param;
	param.mem_descriptor = "1";
	dynet::initialize(param);
}

void DyNetCleanup()
{
	dynet::cleanup();
}

int luaopen_deeplearning(lua_State* l_state) {
	luabridge::getGlobalNamespace(l_state)
		.beginNamespace("deeplearning")
		.addFunction("Initialize", DyNetInitialize)
		.addFunction("Cleanup", DyNetCleanup)
		.beginClass<DeeplearningXorModel>("DeeplearningXorModel")
		.addConstructor<void(*)()>()
		.addFunction("Init", &DeeplearningXorModel::Init)
		.addFunction("Training", &DeeplearningXorModel::Training)
		.addFunction("Output", &DeeplearningXorModel::Output)
		.addFunction("Save", &DeeplearningXorModel::Save)
		.endClass()
		.endNamespace();
    lua_getglobal(l_state, "deeplearning");
    return 1;
}
