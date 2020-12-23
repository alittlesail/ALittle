-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.LoopObject, " extends class:ALittle.LoopObject is nil")
ALittle.LoopAttribute = Lua.Class(ALittle.LoopObject, "ALittle.LoopAttribute")

function ALittle.LoopAttribute:Ctor(target, property, target_value, delay_time)
	___rawset(self, "_target", target)
	___rawset(self, "_property", property)
	___rawset(self, "_target_value", target_value)
	if delay_time == nil or delay_time < 0 then
		delay_time = 0
	end
	___rawset(self, "_total_delay_time", delay_time)
	___rawset(self, "_accumulate_count", 0)
	___rawset(self, "_accumulate_delay_time", 0)
	___rawset(self, "_complete_callback", nil)
end

function ALittle.LoopAttribute.__getter:complete_callback()
	return self._complete_callback
end

function ALittle.LoopAttribute.__setter:complete_callback(value)
	self._complete_callback = value
end

function ALittle.LoopAttribute:Reset()
	self._accumulate_count = 0
	self._accumulate_delay_time = 0
end

function ALittle.LoopAttribute:Completed()
	if self._complete_callback ~= nil then
		self._complete_callback()
	end
end

function ALittle.LoopAttribute:IsCompleted()
	return self._accumulate_count >= 1
end

function ALittle.LoopAttribute:SetCompleted()
	if self._accumulate_count >= 1 then
		return
	end
	self._accumulate_count = 1
	self._accumulate_delay_time = self._total_delay_time
	self._target[self._property] = self._target_value
end

function ALittle.LoopAttribute:SetTime(time)
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
	self._target[self._property] = self._target_value
	return time - self._total_delay_time, true
end

function ALittle.LoopAttribute:Update(frame_time)
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
	self._target[self._property] = self._target_value
end

end