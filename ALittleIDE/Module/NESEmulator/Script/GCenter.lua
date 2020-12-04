-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.g_GConfig = nil
NESEmulator.GCenter = Lua.Class(nil, "NESEmulator.GCenter")

function NESEmulator.GCenter:Ctor()
end

function NESEmulator.GCenter:Setup()
	NESEmulator.g_GConfig = ALittle.CreateConfigSystem(NESEmulator.g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1)
	self._main_layer = ALittle.DisplayLayout(NESEmulator.g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	NESEmulator.g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(NESEmulator.g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	NESEmulator.g_LayerGroup:AddChild(self._dialog_layer, nil)
end

function NESEmulator.GCenter:Shutdown()
end

_G.g_GCenter = NESEmulator.GCenter()
end