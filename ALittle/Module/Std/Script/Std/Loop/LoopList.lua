-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.LoopObject, " extends class:ALittle.LoopObject is nil")
LoopList = Lua.Class(ALittle.LoopObject, "ALittle.LoopList")

function LoopList:Ctor()
	___rawset(self, "_count", 0)
	___rawset(self, "_cur_index", 1)
	___rawset(self, "_update_list", {})
	___rawset(self, "_complete_callback", nil)
end

function LoopList.__getter:complete_callback()
	return self._complete_callback
end

function LoopList.__setter:complete_callback(value)
	self._complete_callback = value
end

function LoopList.__getter:total_count()
	return self._count
end

function LoopList:AddUpdater(value)
	if value == nil then
		return
	end
	self._count = self._count + 1
	self._update_list[self._count] = value
end

function LoopList:RemoveUpdater(value)
	if value == nil or self._count == 0 then
		return
	end
	for index, updater in ___ipairs(self._update_list) do
		if value == updater then
			if self._cur_index > index then
				self._cur_index = self._cur_index - 1
			end
			List_Remove(self._update_list, index)
			self._count = self._count - 1
			break
		end
	end
end

function LoopList:Reset()
	self._cur_index = 1
	for index, updater in ___ipairs(self._update_list) do
		updater:Reset()
	end
end

function LoopList:SetTime(time)
	for index, updater in ___ipairs(self._update_list) do
		updater:SetTime(0)
	end
	self._cur_index = 1
	if time <= 0 then
		return 0, false
	end
	for index, updater in ___ipairs(self._update_list) do
		local completed
		time, completed = updater:SetTime(time)
		if not completed then
			self._cur_index = index
			return 0, false
		end
	end
	self._cur_index = self._count + 1
	return time, true
end

function LoopList:IsCompleted()
	return self._cur_index > self._count
end

function LoopList:Completed()
	if self._complete_callback ~= nil then
		self._complete_callback()
	end
end

function LoopList:SetCompleted()
	local index = self._cur_index
	while true do
		if not(index <= self._count) then break end
		self._update_list[index]:SetCompleted()
		index = index+(1)
	end
	self._cur_index = self._count + 1
end

function LoopList:Update(frame_time)
	if self._cur_index > self._count then
		return
	end
	local updater = self._update_list[self._cur_index]
	updater:Update(frame_time)
	if updater:IsCompleted() then
		self._cur_index = self._cur_index + 1
		updater:Completed()
	end
end

