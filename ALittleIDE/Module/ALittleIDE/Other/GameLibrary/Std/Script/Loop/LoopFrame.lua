-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.LoopObject, " extends class:ALittle.LoopObject is nil")
ALittle.LoopFrame = Lua.Class(ALittle.LoopObject, "ALittle.LoopFrame")

function ALittle.LoopFrame:Ctor(func)
	___rawset(self, "_func", func)
	___rawset(self, "_force_completed", false)
	if self._func == nil then
		___rawset(self, "_force_completed", true)
		ALittle.Log("LoopFrame create failed:function is nil or not a function")
		return
	end
end

function ALittle.LoopFrame:Reset()
end

function ALittle.LoopFrame:Completed()
end

function ALittle.LoopFrame:IsCompleted()
	return self._force_completed
end

function ALittle.LoopFrame:SetCompleted()
	self._force_completed = true
end

function ALittle.LoopFrame:SetTime(time)
	return time, true
end

function ALittle.LoopFrame:Update(frame_time)
	self._func(frame_time)
end

end