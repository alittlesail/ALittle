-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ADeeplearning == nil then _G.ADeeplearning = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ADeeplearning.MnistTestLayout = Lua.Class(ALittle.DisplayLayout, "ADeeplearning.MnistTestLayout")

function ADeeplearning.MnistTestLayout:Ctor()
	___rawset(self, "_loaded", false)
end

function ADeeplearning.MnistTestLayout:TCtor()
	self._model_path = ADeeplearning.g_ModuleBasePath .. "Other/mnist-cnn.model"
	self._model = deeplearning.DeeplearningMnistCNNModel()
	local load_path
	if ALittle.File_GetFileAttr(self._model_path) ~= nil then
		load_path = self._model_path
	end
	self._board:SetPan(5, 0xFFFFFFFF)
	self._board:SetDrawSize(ALittle.Math_Floor(self._board.width), ALittle.Math_Floor(self._board.height), 0xFF000000)
	self._result_text.text = "识别结果"
end

function ADeeplearning.MnistTestLayout:Reset()
	self._model:Load(self._model_path)
end

function ADeeplearning.MnistTestLayout:HandleChanged(event)
	if deeplearning.GetNumberOfGraph() > 0 then
		g_AUITool:ShowNotice("提示", "当前有图正在计算，请稍后再试")
		return
	end
	if not self._loaded then
		self._model:Load(self._model_path)
		self._loaded = true
	end
	local address = carp.GetCarpSurfaceAddress(self._board.surface)
	local result = self._model:Output(address)
	self._result_text.text = "识别结果:" .. result
end

function ADeeplearning.MnistTestLayout:HandleClearClick(event)
	self._result_text.text = "识别结果"
	self._board:ClearContent(0xFF000000)
end

end