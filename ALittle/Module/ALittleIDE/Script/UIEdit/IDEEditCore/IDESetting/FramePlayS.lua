-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
FramePlayS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.FramePlayS")

function FramePlayS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_frameplay")
end

function FramePlayS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("interval")
	self:LoadValueData("play_loop_count")
	self:LoadValueData("base_y")
	self:LoadBoolData("auto_play", true, g_IDEEnum.yn_type)
end

function FramePlayS:HandleIntervalFOCUSOUT(event)
	self:ValueNumZInputChange("interval", false)
end

function FramePlayS:HandleFramePlay(event)
	self._object:Play()
end

function FramePlayS:HandleFrameStop(event)
	self._object:Stop()
	self._object:ShowAllChild()
end

function FramePlayS:HandleBaseYFOCUSOUT(event)
	self:ValueNumZInputChange("base_y", false)
end

function FramePlayS:HandleAutoPlaySELECT_CHANGE(event)
	self:BoolSelectChange("auto_play", false, g_IDEEnum.yn_type)
end

function FramePlayS:HandlePlayLoopCountFOCUSOUT(event)
	self:ValueNumZInputChange("play_loop_count", false)
end

