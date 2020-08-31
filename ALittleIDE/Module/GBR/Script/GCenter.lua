-- ALittle Generate Lua And Do Not Edit This Line!
module("GBR", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


g_GConfig = nil
GCenter = Lua.Class(nil, "GBR.GCenter")

function GCenter:Ctor()
end

function GCenter:Setup()
	g_GConfig = ALittle.CreateConfigSystem(g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1, 2)
	self._main_layer = ALittle.DisplayLayout(g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	g_LayerGroup:AddChild(self._dialog_layer, nil)
end

function GCenter:Shutdown()
end

_G.g_GCenter = GCenter()
