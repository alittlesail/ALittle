-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

ALittle.EventDispatcher = Lua.Class(nil, "ALittle.EventDispatcher")

function ALittle.EventDispatcher:Ctor()
	___rawset(self, "_listeners", {})
	___rawset(self, "_abs_disabled", false)
end

function ALittle.EventDispatcher:AddEventListener(T, object, callback)
	if object == nil then
		return false
	end
	if callback == nil then
		return false
	end
	local rflt = T
	local callback_table = self._listeners[rflt.hash_code]
	if callback_table == nil then
		callback_table = ALittle.CreateKeyWeakMap()
		self._listeners[rflt.hash_code] = callback_table
	end
	local callback_value = callback_table[object]
	if callback_value == nil then
		callback_value = {}
		callback_table[object] = callback_value
	end
	callback_value[callback] = true
	return true
end

function ALittle.EventDispatcher:RemoveEventListener(T, object, callback)
	local rflt = T
	local callback_table = self._listeners[rflt.hash_code]
	if callback_table == nil then
		return
	end
	if callback == nil then
		callback_table[object] = nil
	else
		local callback_value = callback_table[object]
		if callback_value == nil then
			return
		end
		callback_value[callback] = nil
	end
end

function ALittle.EventDispatcher:ClearEventListener()
	self._listeners = {}
end

function ALittle.EventDispatcher:DispatchEvent(T, event)
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

end