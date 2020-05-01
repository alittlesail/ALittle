-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.LoopObject, " extends class:ALittle.LoopObject is nil")
LoopTimer = Lua.Class(ALittle.LoopObject, "ALittle.LoopTimer")

function LoopTimer:Ctor(func, delay_time)
	___rawset(self, "_func", func)
	if delay_time == nil or delay_time < 0 then
		delay_time = 0
	end
	___rawset(self, "_total_delay_time", delay_time)
	___rawset(self, "_accumulate_count", 0)
	___rawset(self, "_accumulate_delay_time", 0)
	if self._func == nil then
		___rawset(self, "_accumulate_count", 1)
		___rawset(self, "_accumulate_delay_time", self._total_delay_time)
		Log("LoopTimer create failed:function is nil or not a function")
		return
	end
	___rawset(self, "_complete_callback", nil)
end

function LoopTimer.__getter:complete_callback()
	return self._complete_callback
end

function LoopTimer.__setter:complete_callback(value)
	self._complete_callback = value
end

function LoopTimer:Reset()
	self._accumulate_count = 0
	self._accumulate_delay_time = 0
end

function LoopTimer:Completed()
	if self._complete_callback ~= nil then
		self._complete_callback()
	end
end

function LoopTimer:IsCompleted()
	return self._accumulate_count >= 1
end

function LoopTimer:SetCompleted()
	if self._accumulate_count >= 1 then
		return
	end
	self._accumulate_count = 1
	self._accumulate_delay_time = self._total_delay_time
	self._func()
end

function LoopTimer:SetTime(time)
	self._accumulate_count = 0
	self._accumulate_delay_time = 0
	if time <= 0 then
		return 0, false
	end
	if time <= self._total_delay_time then
		self._accumulate_delay_time = time
		return 0, false
	end
	self._accumulate_delay_time = self._total_delay_time
	self._accumulate_count = 1
	self._func()
	return time - self._total_delay_time, true
end

function LoopTimer:Update(frame_time)
	if self._accumulate_delay_time < self._total_delay_time then
		self._accumulate_delay_time = self._accumulate_delay_time + (frame_time)
		if self._accumulate_delay_time < self._total_delay_time then
			return
		end
		self._accumulate_delay_time = self._total_delay_time
	end
	if self._accumulate_count >= 1 then
		return
	end
	self._accumulate_count = 1
	self._func()
end

