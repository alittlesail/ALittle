-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ADeeplearning == nil then _G.ADeeplearning = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ADeeplearning.MnistTestLayout = Lua.Class(ALittle.DisplayLayout, "ADeeplearning.MnistTestLayout")

function ADeeplearning.MnistTestLayout:TCtor()
	self._model = deeplearning.DeeplearningMnistModel()
	self._model:Init(ADeeplearning.g_ModuleBasePath .. "Other/mnist.model", nil, nil)
	self._board:SetDrawSize(ALittle.Math_Floor(self._board.width), ALittle.Math_Floor(self._board.height))
	self._result_text.text = "识别结果"
end

function ADeeplearning.MnistTestLayout:HandleChanged(event)
	local address = carp.GetCarpSurfaceAddress(self._board.surface)
	local result = self._model:Output(address)
	self._result_text.text = "识别结果:" .. result
end

function ADeeplearning.MnistTestLayout:HandleClearClick(event)
	self._result_text.text = "识别结果"
	self._board:ClearContent()
end

end