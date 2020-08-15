-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.ILoopSystem, " extends class:ALittle.ILoopSystem is nil")
ALittle.LoopSystem = Lua.Class(ALittle.ILoopSystem, "ALittle.LoopSystem")

function ALittle.LoopSystem:Ctor(weak)
	if weak then
		___rawset(self, "_loop_updaters", ALittle.CreateKeyWeakMap())
	else
		___rawset(self, "_loop_updaters", {})
	end
	___rawset(self, "_in_update", false)
	___rawset(self, "_loop_cache", {})
	___rawset(self, "_cache_empty", true)
	___rawset(self, "_timer", self.__class.__element[1]())
	___rawset(self, "_handler_map", {})
end

function ALittle.LoopSystem:AddUpdater(updater)
	if updater == nil then
		return
	end
	if self._in_update then
		self._cache_empty = false
		self._loop_cache[updater] = true
	else
		self._loop_updaters[updater] = true
	end
end

function ALittle.LoopSystem:RemoveUpdater(updater)
	if updater == nil then
		return
	end
	if self._in_update then
		self._cache_empty = false
		self._loop_cache[updater] = false
	else
		self._loop_updaters[updater] = nil
	end
end

function ALittle.LoopSystem:HasUpdater(updater)
	return self._loop_updaters[updater] ~= nil or self._loop_cache[updater] == true
end

function ALittle.LoopSystem:AddTimer(delay_ms, callback, loop, interval_ms)
	if callback == nil then
		return 0
	end
	if loop == nil then
		loop = 1
	end
	if interval_ms == nil then
		interval_ms = 1
	end
	local id = self._timer:Add(delay_ms, loop, interval_ms)
	self._handler_map[id] = callback
	return id
end

function ALittle.LoopSystem:RemoveTimer(id)
	if id == nil then
		return false
	end
	self._handler_map[id] = nil
	return self._timer:Remove(id)
end

function ALittle.LoopSystem:Update(frame_time)
	self._in_update = true
	local remove_map = nil
	for updater, v in ___pairs(self._loop_updaters) do
		if updater:IsCompleted() then
			if remove_map == nil then
				remove_map = {}
			end
			remove_map[updater] = true
		else
			updater:Update(frame_time)
		end
	end
	if remove_map ~= nil then
		for updater, v in ___pairs(remove_map) do
			self._loop_updaters[updater] = nil
			updater:Completed()
		end
	end
	if not self._cache_empty then
		for updater, v in ___pairs(self._loop_cache) do
			if v then
				self._loop_updaters[updater] = true
			else
				self._loop_updaters[updater] = nil
			end
		end
		self._loop_cache = {}
		self._cache_empty = true
	end
	self._in_update = false
	self._timer:Update(frame_time)
	while true do
		local id = self._timer:Poll()
		if id == 0 then
			break
		end
		if id < 0 then
			local handle = self._handler_map[-id]
			if handle ~= nil then
				handle()
				self._handler_map[-id] = nil
			end
		else
			local handle = self._handler_map[id]
			if handle ~= nil then
				handle()
			end
		end
	end
end

_G.A_LuaLoopSystem = Lua.Template(ALittle.LoopSystem, "ALittle.LoopSystem<Lua.LuaHeapTimer>", Lua.LuaHeapTimer)()
_G.A_LuaWeakLoopSystem = Lua.Template(ALittle.LoopSystem, "ALittle.LoopSystem<Lua.LuaHeapTimer>", Lua.LuaHeapTimer)(true)
local GetLoopSystem
GetLoopSystem = function()
	return A_LuaLoopSystem
end

local GetWeakLoopSystem
GetWeakLoopSystem = function()
	return A_LuaWeakLoopSystem
end

_G.A_LoopSystem = GetLoopSystem()
_G.A_WeakLoopSystem = GetWeakLoopSystem()
end