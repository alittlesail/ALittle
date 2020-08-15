-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Lua == nil then _G.Lua = {} end
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-2114130826, "Lua.CoFunctorMetatable", {
name = "Lua.CoFunctorMetatable", ns_name = "Lua", rl_name = "CoFunctorMetatable", hash_code = -2114130826,
name_list = {"__call","__tostring"},
type_list = {"any","Functor<(Lua.CoFunctorObject):string>"},
option_map = {}
})
ALittle.RegStruct(1817653851, "Lua.CoFunctorObject", {
name = "Lua.CoFunctorObject", ns_name = "Lua", rl_name = "CoFunctorObject", hash_code = 1817653851,
name_list = {"_func"},
type_list = {"Functor<(any):any>"},
option_map = {}
})
ALittle.RegStruct(-1456681653, "Lua.FunctorObject", {
name = "Lua.FunctorObject", ns_name = "Lua", rl_name = "FunctorObject", hash_code = -1456681653,
name_list = {"_arg","_arg_count","_func"},
type_list = {"List<any>","int","Functor<(any):any>"},
option_map = {}
})
ALittle.RegStruct(1453939213, "Lua.FunctorMetatable", {
name = "Lua.FunctorMetatable", ns_name = "Lua", rl_name = "FunctorMetatable", hash_code = 1453939213,
name_list = {"__call","__tostring"},
type_list = {"any","Functor<(Lua.FunctorObject):string>"},
option_map = {}
})

local select = select
local unpack = unpack
local tostring = tostring
local setmetatable = setmetatable
local getmetatable = getmetatable
local coroutine = coroutine
local type = type
local __functor_mt = {}
local __functor_mt__call
__functor_mt__call = function(caller, ...)
	local new_arg_list = {}
	local arg_list = caller._arg
	local arg_count = caller._arg_count
	local i = 1
	while true do
		if not(i <= arg_count) then break end
		new_arg_list[i] = arg_list[i]
		i = i+(1)
	end
	local add_count = select("#", ...)
	local i = 1
	while true do
		if not(i <= add_count) then break end
		new_arg_list[arg_count + i] = select(i, ...)
		i = i+(1)
	end
	return caller._func(unpack(new_arg_list, 1, arg_count + add_count))
end

__functor_mt.__call = __functor_mt__call
local __functor_mt__tostring
__functor_mt__tostring = function(caller)
	return "[ALittle Functor:" .. tostring(caller) .. "]"
end

__functor_mt.__tostring = __functor_mt__tostring
function Lua.Bind(func, ...)
	Lua.Assert(func, "func == null")
	if select("#", ...) == 0 then
		return func
	end
	local object = {}
	object._func = func
	object._arg = {...}
	object._arg_count = select("#", ...)
	setmetatable(object, __functor_mt)
	return object
end

local __co_functor_mt = {}
local __co_functor_mt__call
__co_functor_mt__call = function(caller, ...)
	return coroutine.wrap(caller._func)(...)
end

__co_functor_mt.__call = __co_functor_mt__call
local __co_functor_mt__tostring
__co_functor_mt__tostring = function(caller)
	return "[ALittle CoWrap:" .. tostring(caller) .. "]"
end

__co_functor_mt.__tostring = __co_functor_mt__tostring
function Lua.CoWrap(func)
	local object = {}
	object._func = func
	setmetatable(object, __co_functor_mt)
	return object
end

function Lua.IsCoWrap(value)
	return type(value) == "table" and getmetatable(value) == __co_functor_mt
end

end