
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "deeplearninglib.h"
}
#include <LuaBridge/LuaBridge.h>

#include "deeplearning_xor.hpp"
#include "deeplearning_mnist_cnn.hpp"
#include "deeplearning_speech.hpp"

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
		.addFunction("Load", &DeeplearningModel::Load)
		.addFunction("StartTraining", &DeeplearningModel::StartTraining)
		.addFunction("StopTraining", &DeeplearningModel::StopTraining)
		.addFunction("HandleEvent", &DeeplearningModel::HandleEvent)
		.addFunction("HasResult", &DeeplearningModel::HasResult)
		.addFunction("GetLoss", &DeeplearningModel::GetLoss)
		.addFunction("GetRight", &DeeplearningModel::GetRight)
		.addFunction("GetTotalTrainCount", &DeeplearningModel::GetTotalTrainCount)
		.addFunction("GetCurTrainCount", &DeeplearningModel::GetCurTrainCount)
		.addFunction("GetTrainRound", &DeeplearningModel::GetTrainRound)
		.addFunction("GetCurRightCount", &DeeplearningModel::GetCurRightCount)
		.endClass()
		.deriveClass<DeeplearningXorModel, DeeplearningModel>("DeeplearningXorModel")
		.addConstructor<void(*)()>()
		.addFunction("Output", &DeeplearningXorModel::Output)
		.endClass()
		.deriveClass<DeeplearningMnistCNNModel, DeeplearningModel>("DeeplearningMnistCNNModel")
		.addConstructor<void(*)()>()
		.addFunction("SetTrainDataPath", &DeeplearningMnistCNNModel::SetTrainDataPath)
		.addFunction("Output", &DeeplearningMnistCNNModel::Output)
		.endClass()
		.deriveClass<DeeplearningSpeechModel, DeeplearningModel>("DeeplearningSpeechModel")
		.addConstructor<void(*)(const char*)>()
		.addFunction("Wav2MFCC", &DeeplearningSpeechModel::Wav2MFCC)
		.addFunction("SetTrainDataPath", &DeeplearningSpeechModel::SetTrainDataPath)
		.addFunction("Output", &DeeplearningSpeechModel::Output)
		.endClass()
		.endNamespace();
    lua_getglobal(l_state, "deeplearning");
    return 1;
}

#define CARP_TASK_CONSUMER_IMPL
#include "carp_task_consumer.hpp"