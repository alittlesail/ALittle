-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.LoopObject, " extends class:ALittle.LoopObject is nil")
ALittle.LoopGroup = Lua.Class(ALittle.LoopObject, "ALittle.LoopGroup")

function ALittle.LoopGroup:Ctor()
	___rawset(self, "_total_count", 0)
	___rawset(self, "_complete_count", 0)
	___rawset(self, "_loop_updaters", {})
	___rawset(self, "_complete_updaters", {})
	___rawset(self, "_complete_callback", nil)
end

function ALittle.LoopGroup.__getter:complete_callback()
	return self._complete_callback
end

function ALittle.LoopGroup.__setter:complete_callback(value)
	self._complete_callback = value
end

function ALittle.LoopGroup.__getter:total_count()
	return self._total_count
end

function ALittle.LoopGroup:AddUpdater(value)
	if value == nil then
		return
	end
	if self._complete_updaters[value] or self._loop_updaters[value] then
		return
	end
	self._loop_updaters[value] = true
	self._total_count = self._total_count + 1
end

function ALittle.LoopGroup:RemoveUpdater(value)
	if self._loop_updaters[value] then
		self._loop_updaters[value] = nil
		self._total_count = self._total_count - 1
		return
	end
	if self._complete_updaters[value] then
		self._complete_updaters[value] = nil
		self._total_count = self._total_count - 1
		self._complete_count = self._complete_count - 1
	end
end

function ALittle.LoopGroup:Reset()
	self._complete_count = 0
	for updater, v in ___pairs(self._loop_updaters) do
		updater:Reset()
	end
	for updater, v in ___pairs(self._complete_updaters) do
		self._loop_updaters[updater] = true
		updater:Reset()
	end
end

function ALittle.LoopGroup:SetTime(time)
	if self._total_count == 0 then
		return time, true
	end
	local total_updater = {}
	for updater, v in ___pairs(self._loop_updaters) do
		total_updater[updater] = true
	end
	for updater, v in ___pairs(self._complete_updaters) do
		total_updater[updater] = true
	end
	self._loop_updaters = {}
	self._complete_updaters = {}
	self._complete_count = 0
	local min_time = nil
	for updater, v in ___pairs(total_updater) do
		local remain_time, completed = updater:SetTime(time)
		if completed then
			self._complete_updaters[updater] = true
			self._complete_count = self._complete_count + 1
		else
			self._loop_updaters[updater] = true
		end
		if min_time == nil or min_time > remain_time then
			min_time = remain_time
		end
	end
	return min_time, self._complete_count == self._total_count
end

function ALittle.LoopGroup:IsCompleted()
	return self._complete_count >= self._total_count
end

function ALittle.LoopGroup:Completed()
	if self._complete_callback ~= nil then
		self._complete_callback()
	end
end

function ALittle.LoopGroup:SetCompleted()
	self._complete_count = self._total_count
	for updater, v in ___pairs(self._loop_updaters) do
		updater:SetCompleted()
		self._complete_updaters[updater] = true
	end
	self._loop_updaters = {}
end

function ALittle.LoopGroup:Update(frame_time)
	if self._complete_count >= self._total_count then
		return
	end
	local remove_map = {}
	for updater, v in ___pairs(self._loop_updaters) do
		if updater:IsCompleted() then
			remove_map[updater] = true
		else
			updater:Update(frame_time)
		end
	end
	for updater, v in ___pairs(remove_map) do
		self._loop_updaters[updater] = nil
		self._complete_updaters[updater] = true
		self._complete_count = self._complete_count + 1
		updater:Completed()
	end
end

end