
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "deeplearninglib.h"
}
#include <LuaBridge/LuaBridge.h>

#include "deeplearning_darknet.hpp"

int luaopen_deeplearning(lua_State* l_state)
{
	luabridge::getGlobalNamespace(l_state)
		.beginNamespace("deeplearning")
		.beginClass<DeeplearningYolov3>("DeeplearningYolov3")
		.addConstructor<void(*)()>()
		.addFunction("Load", &DeeplearningYolov3::Load)
		.addFunction("Predict", &DeeplearningYolov3::Predict)
		.endClass()

		.endNamespace();

    lua_getglobal(l_state, "deeplearning");
    return 1;
}
