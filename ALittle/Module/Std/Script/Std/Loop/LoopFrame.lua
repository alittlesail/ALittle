-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.LoopObject, " extends class:ALittle.LoopObject is nil")
LoopFrame = Lua.Class(ALittle.LoopObject, "ALittle.LoopFrame")

function LoopFrame:Ctor(func)
	___rawset(self, "_func", func)
	___rawset(self, "_force_completed", false)
	if self._func == nil then
		___rawset(self, "_force_completed", true)
		Log("LoopFrame create failed:function is nil or not a function")
		return
	end
end

function LoopFrame:Reset()
end

function LoopFrame:Completed()
end

function LoopFrame:IsCompleted()
	return self._force_completed
end

function LoopFrame:SetCompleted()
	self._force_completed = true
end

function LoopFrame:SetTime(time)
	return time, true
end

function LoopFrame:Update(frame_time)
	self._func(frame_time)
end

