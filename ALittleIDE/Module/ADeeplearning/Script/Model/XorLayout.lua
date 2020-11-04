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
ADeeplearning.XorTrainLayout = Lua.Class(ADeeplearning.CommonTrainLayout, "ADeeplearning.XorTrainLayout")

function ADeeplearning.XorTrainLayout.__getter:model()
	if self._model == nil then
		self._model = deeplearning.DeeplearningXorModel()
		self._model_path = ADeeplearning.g_ModuleBasePath .. "Other/xor.model"
	end
	return self._model
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ADeeplearning.XorLayout = Lua.Class(ALittle.DisplayLayout, "ADeeplearning.XorLayout")

function ADeeplearning.XorLayout:TCtor()
	self._train:AddEventListener(___all_struct[958494922], self, self.HandleTrainChanged)
	self._model_path = ADeeplearning.g_ModuleBasePath .. "Other/xor.model"
	self._model = deeplearning.DeeplearningXorModel()
end

function ADeeplearning.XorLayout:HandleTrainChanged(event)
	self:Calc()
end

function ADeeplearning.XorLayout:HandleCalcClick(event)
	self:Calc()
end

function ADeeplearning.XorLayout:Calc()
	self._model:Load(self._model_path)
	self._result_1.text = ALittle.Math_Floor(self._model:Output(0.0, 0.0) * 100000) / 100000
	self._result_2.text = ALittle.Math_Floor(self._model:Output(0.0, 1.0) * 100000) / 100000
	self._result_3.text = ALittle.Math_Floor(self._model:Output(1.0, 0.0) * 100000) / 100000
	self._result_4.text = ALittle.Math_Floor(self._model:Output(1.0, 1.0) * 100000) / 100000
end

end