
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "deeplearninglib.h"
}
#include <LuaBridge/LuaBridge.h>

#include "deeplearning_xor.hpp"
#include "deeplearning_mnist.hpp"
#include "deeplearning_speech.hpp"

int luaopen_deeplearning(lua_State* l_state) {
	luabridge::getGlobalNamespace(l_state)
		.beginNamespace("deeplearning")
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
		.deriveClass<DeeplearningMnistModel, DeeplearningModel>("DeeplearningMnistModel")
		.addConstructor<void(*)()>()
		.addFunction("SetMnistRoot", &DeeplearningMnistModel::SetMnistRoot)
		.addFunction("Output", &DeeplearningMnistModel::Output)
		.endClass()
		.deriveClass<DeeplearningSpeechModel, DeeplearningModel>("DeeplearningSpeechModel")
		.addConstructor<void(*)(const char*)>()
		.addFunction("Wav2MFCC", &DeeplearningSpeechModel::Wav2MFCC)
		.addFunction("SetSpeechDataPath", &DeeplearningSpeechModel::SetSpeechDataPath)
		.addFunction("Output", &DeeplearningSpeechModel::Output)
		.endClass()
		.endNamespace();
    lua_getglobal(l_state, "deeplearning");
    return 1;
}

#define CARP_TASK_CONSUMER_IMPL
#include "carp_task_consumer.hpp"
#define CARP_MESSAGE_IMPL
#include "carp_message.hpp"