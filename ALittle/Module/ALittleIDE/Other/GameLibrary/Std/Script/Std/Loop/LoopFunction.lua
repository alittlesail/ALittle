
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.LoopObject, " extends class:ALittle.LoopObject is nil")
LoopFunction = Lua.Class(ALittle.LoopObject, "ALittle.LoopFunction")

function LoopFunction:Ctor(func, count, interval_time, delay_time)
	___rawset(self, "_func", func)
	___rawset(self, "_total_count", count)
	___rawset(self, "_force_completed", false)
	if delay_time == nil or delay_time < 0 then
		delay_time = 0
	end
	if interval_time < 0 then
		interval_time = 0
	end
	___rawset(self, "_total_interval_time", interval_time)
	___rawset(self, "_total_delay_time", delay_time)
	___rawset(self, "_accumulate_count", 0)
	___rawset(self, "_accumulate_time", 0)
	___rawset(self, "_accumulate_delay_time", 0)
	if self._func == nil then
		___rawset(self, "_accumulate_count", 0)
		___rawset(self, "_total_count", 0)
		Log("LoopFunction create failed:function is nil or not a function")
		return
	end
	___rawset(self, "_complete_callback", nil)
end

function LoopFunction.__getter:complete_callback()
	return self._complete_callback
end

function LoopFunction.__setter:complete_callback(value)
	self._complete_callback = value
end

function LoopFunction:Reset()
	self._accumulate_count = 0
	self._accumulate_time = 0
	self._accumulate_delay_time = 0
end

function LoopFunction:Completed()
	if self._complete_callback ~= nil then
		self._complete_callback()
	end
end

function LoopFunction:IsCompleted()
	if self._force_completed then
		return true
	end
	if self._total_count < 0 then
		return false
	end
	return self._total_count <= self._accumulate_count
end

function LoopFunction:SetCompleted()
	if self._total_count < 0 then
		self._force_completed = true
		return
	end
	self._accumulate_count = self._total_count
end

function LoopFunction:SetTime(time)
	self._accumulate_count = 0
	self._accumulate_delay_time = 0
	self._accumulate_time = 0
	if time <= 0 then
		return 0, false
	end
	if self._total_count < 0 then
		return 0, false
	end
	if time <= self._total_delay_time then
		self._accumulate_delay_time = time
		return 0, false
	end
	self._accumulate_delay_time = self._total_delay_time
	time = time - (self._total_delay_time)
	local total_time = self._total_interval_time * self._total_count
	if time < total_time then
		local float_count = total_time / self._total_interval_time
		local count = Math_Floor(float_count)
		self._accumulate_count = count
		self._accumulate_time = Math_Floor((float_count - count) * self._total_interval_time)
		return 0, false
	end
	self._accumulate_count = self._total_count
	return time - total_time, true
end

function LoopFunction:Update(frame_time)
	if self._accumulate_delay_time < self._total_delay_time then
		self._accumulate_delay_time = self._accumulate_delay_time + (frame_time)
		if self._accumulate_delay_time < self._total_delay_time then
			return
		end
		frame_time = self._accumulate_delay_time - self._total_delay_time
		self._accumulate_delay_time = self._total_delay_time
	end
	self._accumulate_time = self._accumulate_time + (frame_time)
	if self._accumulate_time > self._total_interval_time then
		self._accumulate_time = 0
		self._accumulate_count = self._accumulate_count + 1
		self._func()
	end
end

