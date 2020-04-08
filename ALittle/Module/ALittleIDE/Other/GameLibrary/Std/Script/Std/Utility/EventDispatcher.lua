
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

EventListener = Lua.Class(nil, "ALittle.EventListener")

function EventListener:Ctor()
end

function EventListener:RemoveFromDispatcher()
	if self._ref_map == nil then
		return
	end
	for d, t in ___pairs(self._ref_map) do
		for hash_code, vb in ___pairs(t) do
			local callback_table = d._listeners[hash_code]
			if callback_table ~= nil then
				callback_table[self] = nil
			end
		end
	end
	self._ref_map = nil
end

EventDispatcher = Lua.Class(nil, "ALittle.EventDispatcher")

function EventDispatcher:Ctor()
	___rawset(self, "_listeners", {})
	___rawset(self, "_abs_disabled", false)
end

function EventDispatcher:AddEventListener(T, object, callback)
	if object == nil then
		return false
	end
	if callback == nil then
		return false
	end
	local rflt = T
	local callback_table = self._listeners[rflt.hash_code]
	if callback_table == nil then
		callback_table = {}
		self._listeners[rflt.hash_code] = callback_table
	end
	local callback_value = callback_table[object]
	if callback_value == nil then
		callback_value = {}
		callback_table[object] = callback_value
	end
	callback_value[callback] = true
	local ref_map = object._ref_map
	if ref_map == nil then
		ref_map = {}
		object._ref_map = ref_map
	end
	local ref_value = ref_map[self]
	if ref_value == nil then
		ref_value = {}
		ref_map[self] = ref_value
	end
	ref_value[rflt.hash_code] = true
	return true
end

function EventDispatcher:RemoveEventListener(T, object, callback)
	local rflt = T
	local callback_table = self._listeners[rflt.hash_code]
	if callback_table == nil then
		return
	end
	if callback == nil then
		object._ref_map[self] = nil
		callback_table[object] = nil
	else
		local callback_value = callback_table[object]
		if callback_value == nil then
			return
		end
		callback_value[callback] = nil
		object._ref_map[self][rflt.hash_code] = nil
	end
end

function EventDispatcher:ClearEventListener()
	for hash_code, callback_table in ___pairs(self._listeners) do
		for listener, callback_value in ___pairs(callback_table) do
			listener._ref_map[self] = nil
		end
	end
	self._listeners = {}
end

function EventDispatcher:DispatchEvent(T, event)
	local rflt = T
	if event.target == nil then
		event.target = self
	end
	local callback_table = self._listeners[rflt.hash_code]
	if callback_table == nil then
		return
	end
	for object, callback_value in ___pairs(callback_table) do
		for func, _ in ___pairs(callback_value) do
			func(object, event)
		end
	end
end

