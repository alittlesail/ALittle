-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Lua == nil then _G.Lua = {} end
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1652320227, "Lua.ObjectInfo", {
name = "Lua.ObjectInfo", ns_name = "Lua", rl_name = "ObjectInfo", hash_code = 1652320227,
name_list = {"__class"},
type_list = {"ALittle.ClassInfo"},
option_map = {}
})
ALittle.RegStruct(1620637943, "Lua.ObjectMetatable", {
name = "Lua.ObjectMetatable", ns_name = "Lua", rl_name = "ObjectMetatable", hash_code = 1620637943,
name_list = {"__index","__newindex","__tostring"},
type_list = {"Functor<(Lua.ObjectInfo,string):any>","Functor<(Lua.ObjectInfo,string,any)>","Functor<(Lua.ObjectInfo):string>"},
option_map = {}
})
ALittle.RegStruct(-1535459145, "Lua.ClassMetatable", {
name = "Lua.ClassMetatable", ns_name = "Lua", rl_name = "ClassMetatable", hash_code = -1535459145,
name_list = {"__index","__call","__tostring"},
type_list = {"Functor<(ALittle.ClassInfo,string):any>","any","Functor<(ALittle.ClassInfo):string>"},
option_map = {}
})

local rawget = rawget
local rawset = rawset
local tostring = tostring
local setmetatable = setmetatable
local type = type
local select = select
local __object_index_function
__object_index_function = function(object, key)
	local clazz = rawget(object, "__class")
	local getter = clazz.__getter[key]
	if getter ~= nil then
		return getter(object)
	end
	local value = clazz[key]
	if value ~= nil then
		rawset(object, key, value)
		return value
	end
	return nil
end

local __object_newindex_function
__object_newindex_function = function(object, key, value)
	local clazz = rawget(object, "__class")
	local setter = clazz.__setter[key]
	if setter ~= nil then
		setter(object, value)
		return
	end
	rawset(object, key, value)
end

local __object_tostring_function
__object_tostring_function = function(object)
	local clazz = rawget(object, "__class")
	return "[ALittle Object instance of " .. tostring(clazz.__name) .. "]"
end

local __object_mt = {}
__object_mt.__index = __object_index_function
__object_mt.__newindex = __object_newindex_function
__object_mt.__tostring = __object_tostring_function
local __class_create_function
__class_create_function = function(clazz, object, ...)
	local super = rawget(clazz, "__super")
	if super ~= nil then
		__class_create_function(super, object, ...)
	end
	local fctor = rawget(clazz, "Ctor")
	if fctor ~= nil then
		fctor(object, ...)
	end
end

local __class_index_function
__class_index_function = function(clazz, key)
	local super = rawget(clazz, "__super")
	if super == nil then
		return nil
	end
	local value = super[key]
	rawset(clazz, key, value)
	return value
end

local __class_call_function
__class_call_function = function(clazz, ...)
	local object = {}
	object.__class = clazz
	setmetatable(object, __object_mt)
	__class_create_function(clazz, object, ...)
	return object
end

local __class_tostring_function
__class_tostring_function = function(clazz)
	return "[ALittle Class:" .. tostring(clazz.__name) .. "]"
end

local __class_mt = {}
__class_mt.__index = __class_index_function
__class_mt.__call = __class_call_function
__class_mt.__tostring = __class_tostring_function
function Lua.Class(super, name)
	local clazz = {}
	clazz.__super = super
	clazz.__name = name
	local setter = {}
	local getter = {}
	if super ~= nil then
		for k, v in ___pairs(super.__setter) do
			setter[k] = v
		end
		for k, v in ___pairs(super.__getter) do
			getter[k] = v
		end
	end
	clazz.__setter = setter
	clazz.__getter = getter
	setmetatable(clazz, __class_mt)
	return clazz
end

function Lua.Template(clazz, name, ...)
	local child = clazz.__child
	if child == nil then
		child = {}
		clazz.__child = child
	end
	local template = child[name]
	if template ~= nil then
		return template
	end
	template = {}
	child[name] = template
	for key, value in ___pairs(clazz) do
		if type(value) == "function" or Lua.IsCoWrap(value) then
			template[key] = value
		end
	end
	template.__super = clazz.__super
	template.__name = name
	template.__setter = clazz.__setter
	template.__getter = clazz.__getter
	template.__element = {...}
	setmetatable(template, __class_mt)
	return template
end

end