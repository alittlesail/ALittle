
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

int DyNetGetNumberOfGraph()
{
	return dynet::get_number_of_active_graphs();
}

int luaopen_deeplearning(lua_State* l_state) {
	luabridge::getGlobalNamespace(l_state)
		.beginNamespace("deeplearning")
		.addFunction("Initialize", DyNetInitialize)
		.addFunction("Cleanup", DyNetCleanup)
		.addFunction("GetNumberOfGraph", DyNetGetNumberOfGraph)
		.beginClass<DeeplearningModel>("DeeplearningModel")
		.addFunction("Save", &DeeplearningModel::Save)
		.addFunction("StartTraining", &DeeplearningModel::StartTraining)
		.addFunction("StopTraining", &DeeplearningModel::StopTraining)
		.addFunction("HandleEvent", &DeeplearningModel::HandleEvent)
		.addFunction("HasLoss", &DeeplearningModel::HasLoss)
		.addFunction("GetLoss", &DeeplearningModel::GetLoss)
		.addFunction("GetTotalTrainCount", &DeeplearningModel::GetTotalTrainCount)
		.addFunction("GetCurTrainCount", &DeeplearningModel::GetCurTrainCount)
		.addFunction("GetTrainRound", &DeeplearningModel::GetTrainRound)
		.addFunction("GetCurRightCount", &DeeplearningModel::GetCurRightCount)
		.endClass()
		.deriveClass<DeeplearningXorModel, DeeplearningModel>("DeeplearningXorModel")
		.addConstructor<void(*)()>()
		.addFunction("Init", &DeeplearningXorModel::Init)
		.addFunction("Output", &DeeplearningXorModel::Output)
		.endClass()
		.deriveClass<DeeplearningMnistMLPModel, DeeplearningModel>("DeeplearningMnistMLPModel")
		.addConstructor<void(*)()>()
		.addFunction("Init", &DeeplearningMnistMLPModel::Init)
		.addFunction("Output", &DeeplearningMnistMLPModel::Output)
		.endClass()
		.deriveClass<DeeplearningMnistCNNModel, DeeplearningModel>("DeeplearningMnistCNNModel")
		.addConstructor<void(*)()>()
		.addFunction("Init", &DeeplearningMnistCNNModel::Init)
		.addFunction("Output", &DeeplearningMnistCNNModel::Output)
		.endClass()
		.endNamespace();
    lua_getglobal(l_state, "deeplearning");
    return 1;
}

#define CARP_TASK_CONSUMER_IMPL
#include "carp_task_consumer.hpp"