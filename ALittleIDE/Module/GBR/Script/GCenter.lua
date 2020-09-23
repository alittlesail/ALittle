-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.GBR == nil then _G.GBR = {} end
local ___pairs = pairs
local ___ipairs = ipairs


GBR.g_GConfig = nil
GBR.GCenter = Lua.Class(nil, "GBR.GCenter")

function GBR.GCenter:Ctor()
end

function GBR.GCenter:Setup()
	GBR.g_GConfig = ALittle.CreateConfigSystem(GBR.g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1)
	self._main_layer = ALittle.DisplayLayout(GBR.g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	GBR.g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(GBR.g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	GBR.g_LayerGroup:AddChild(self._dialog_layer, nil)
end

function GBR.GCenter:Shutdown()
end

_G.g_GCenter = GBR.GCenter()
end