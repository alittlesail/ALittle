-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
ALittleIDE.FramePlayS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.FramePlayS")

function ALittleIDE.FramePlayS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_frameplay")
end

function ALittleIDE.FramePlayS:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("interval")
	self:LoadValueData("play_loop_count")
	self:LoadValueData("base_y")
	self:LoadBoolData("auto_play", true, ALittleIDE.g_IDEEnum.yn_type)
end

function ALittleIDE.FramePlayS:HandleIntervalFOCUSOUT(event)
	self:ValueNumZInputChange("interval", false)
end

function ALittleIDE.FramePlayS:HandleFramePlay(event)
	self._object:Play()
end

function ALittleIDE.FramePlayS:HandleFrameStop(event)
	self._object:Stop()
	self._object:ShowAllChild()
end

function ALittleIDE.FramePlayS:HandleBaseYFOCUSOUT(event)
	self:ValueNumZInputChange("base_y", false)
end

function ALittleIDE.FramePlayS:HandleAutoPlaySELECT_CHANGE(event)
	self:BoolSelectChange("auto_play", false, ALittleIDE.g_IDEEnum.yn_type)
end

function ALittleIDE.FramePlayS:HandlePlayLoopCountFOCUSOUT(event)
	self:ValueNumZInputChange("play_loop_count", false)
end

end