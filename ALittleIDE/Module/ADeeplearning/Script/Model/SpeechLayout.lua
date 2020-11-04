-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ADeeplearning == nil then _G.ADeeplearning = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ADeeplearning.CommonTrainLayout, " extends class:ADeeplearning.CommonTrainLayout is nil")
ADeeplearning.SpeechTrainLayout = Lua.Class(ADeeplearning.CommonTrainLayout, "ADeeplearning.SpeechTrainLayout")

function ADeeplearning.SpeechTrainLayout.__getter:model()
	if self._model == nil then
		self._model = deeplearning.DeeplearningSpeechModel(ADeeplearning.g_ModuleBasePath .. "Data/thchs30_word.dat")
		self._model_path = ADeeplearning.g_ModuleBasePath .. "Other/speech.model"
		self._model:SetSpeechDataPath(ADeeplearning.g_ModuleBasePath .. "Data/thchs30_speech.dat")
	end
	return self._model
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ADeeplearning.SpeechLayout = Lua.Class(ALittle.DisplayLayout, "ADeeplearning.SpeechLayout")

function ADeeplearning.SpeechLayout:TCtor()
	self._train:AddEventListener(___all_struct[958494922], self, self.HandleTrainChanged)
	self._model_path = ADeeplearning.g_ModuleBasePath .. "Other/speech.model"
	self._model = deeplearning.DeeplearningSpeechModel(ADeeplearning.g_ModuleBasePath .. "Data/thchs30_word.dat")
end

function ADeeplearning.SpeechLayout:HandleTrainChanged(event)
end

function ADeeplearning.SpeechLayout:HandleCalcClick(event)
end

end