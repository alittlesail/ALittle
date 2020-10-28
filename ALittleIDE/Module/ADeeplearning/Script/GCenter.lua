-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ADeeplearning == nil then _G.ADeeplearning = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ADeeplearning.g_GConfig = nil
ADeeplearning.GCenter = Lua.Class(nil, "ADeeplearning.GCenter")

function ADeeplearning.GCenter:Setup()
	ADeeplearning.g_GConfig = ALittle.CreateConfigSystem(ADeeplearning.g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1)
	self._main_layer = ALittle.DisplayLayout(ADeeplearning.g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	ADeeplearning.g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(ADeeplearning.g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	ADeeplearning.g_LayerGroup:AddChild(self._dialog_layer, nil)
	local main_scene = ADeeplearning.g_Control:CreateControl("main_scene")
	self._main_layer:AddChild(main_scene)
end

function ADeeplearning.GCenter:Shutdown()
end

ADeeplearning.g_GCenter = ADeeplearning.GCenter()
end