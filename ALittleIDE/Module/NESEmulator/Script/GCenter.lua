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
	local screen = ALittle.DynamicImage(NESEmulator.g_Control)
	screen.width = NESEmulator.SCREEN_WIDTH
	screen.height = NESEmulator.SCREEN_HEIGHT
	screen:SetSurfaceSize(NESEmulator.SCREEN_WIDTH, NESEmulator.SCREEN_HEIGHT, 0)
	self._main_layer:AddChild(screen)
	g_GNes:Setup(screen)
	g_GNes:LoadROM("MetalMax.nes")
end

function NESEmulator.GCenter:Shutdown()
	g_GNes:Shutdown()
end

_G.g_GCenter = NESEmulator.GCenter()
end