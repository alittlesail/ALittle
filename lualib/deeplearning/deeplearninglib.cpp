
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "deeplearninglib.h"
}
#include <LuaBridge/LuaBridge.h>

#include "deeplearning_xor.hpp"
#include "deeplearning_mnist_mlp.hpp"
#include "deeplearning_mnist_cnn.hpp"

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
		.beginClass<DeeplearningModel>("DeeplearningModel")
		.addFunction("Save", &DeeplearningModel::Save)
		.addFunction("GetTotalTrainCount", &DeeplearningModel::GetTotalTrainCount)
		.addFunction("GetCurTrainCount", &DeeplearningModel::GetCurTrainCount)
		.addFunction("GetTrainRound", &DeeplearningModel::GetTrainRound)
		.endClass()
		.deriveClass<DeeplearningXorModel, DeeplearningModel>("DeeplearningXorModel")
		.addConstructor<void(*)()>()
		.addFunction("Init", &DeeplearningXorModel::Init)
		.addFunction("Training", &DeeplearningXorModel::Training)
		.addFunction("Output", &DeeplearningXorModel::Output)
		.endClass()
		.deriveClass<DeeplearningMnistMLPModel, DeeplearningModel>("DeeplearningMnistMLPModel")
		.addConstructor<void(*)()>()
		.addFunction("Init", &DeeplearningMnistMLPModel::Init)
		.addFunction("Training", &DeeplearningMnistMLPModel::Training)
		.addFunction("Output", &DeeplearningMnistMLPModel::Output)
		.endClass()
		.deriveClass<DeeplearningMnistCNNModel, DeeplearningModel>("DeeplearningMnistCNNModel")
		.addConstructor<void(*)()>()
		.addFunction("Init", &DeeplearningMnistCNNModel::Init)
		.addFunction("Training", &DeeplearningMnistCNNModel::Training)
		.addFunction("Output", &DeeplearningMnistCNNModel::Output)
		.endClass()
		.endNamespace();
    lua_getglobal(l_state, "deeplearning");
    return 1;
}