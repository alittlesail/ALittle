-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ADeeplearning == nil then _G.ADeeplearning = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(ADeeplearning.CommonTrainLayout, " extends class:ADeeplearning.CommonTrainLayout is nil")
ADeeplearning.MnistTrainLayout = Lua.Class(ADeeplearning.CommonTrainLayout, "ADeeplearning.MnistTrainLayout")

function ADeeplearning.MnistTrainLayout:TCtor()
	self._model = deeplearning.DeeplearningMnistCNNModel()
	self._model_path = ADeeplearning.g_ModuleBasePath .. "Other/mnist-cnn.model"
	self._model:SetTrainDataPath(ADeeplearning.g_ModuleBasePath .. "Data/train-images.idx3-ubyte", ADeeplearning.g_ModuleBasePath .. "Data/train-labels.idx1-ubyte")
end

function ADeeplearning.MnistTrainLayout.__getter:model()
	return self._model
end

end