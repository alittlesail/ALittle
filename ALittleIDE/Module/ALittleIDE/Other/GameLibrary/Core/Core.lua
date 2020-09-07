-- ALittle Generate Lua And Do Not Edit This Line!
do
local ___pairs = pairs
local ___ipairs = ipairs


function _G.Require(base_path, url)
	local ___COROUTINE = coroutine.running()
	if _G["core_require"] ~= nil then
		_G["core_require"](base_path .. url)
	else
		require(base_path .. url)
	end
	return nil
end

function _G.RequireFromPaths(base_path, rel_path, file_list)
	local ___COROUTINE = coroutine.running()
	for index, path in ___ipairs(file_list) do
		path = string.sub(path, 1, -9)
		Require(base_path, rel_path .. path)
	end
end

function _G.RequireCore(base_path)
	local ___COROUTINE = coroutine.running()
	Require(base_path, "Core/Reflect/ReflectRegister")
	Require(base_path, "Core/Reflect/ReflectDefine")
	Require(base_path, "Core/Lua/LuaBind")
	Require(base_path, "Core/Lua/LuaClass")
	Require(base_path, "Core/Lua/LuaException")
	if _G["bit"] == nil then
		_G["bit"] = _G["bit32"]
	end
	Require(base_path, "Core/Utility/Log")
	Require(base_path, "Core/Utility/List")
	Require(base_path, "Core/Utility/Map")
	Require(base_path, "Core/Utility/Math")
	Require(base_path, "Core/Utility/String")
	Require(base_path, "Core/Utility/Time")
	Require(base_path, "Core/Utility/Coroutine")
	Require(base_path, "Core/Net/HttpFileReceiver")
	Require(base_path, "Core/Net/HttpFileSender")
	Require(base_path, "Core/Net/HttpReceiver")
	Require(base_path, "Core/Net/HttpSender")
	Require(base_path, "Core/Net/MsgCommon")
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


local __all_name_struct = {}
local __all_id_struct = {}
function ALittle.RegStruct(hash, name, info)
	if __all_name_struct[name] ~= nil then
		return
	end
	local old_info = __all_id_struct[hash]
	if old_info ~= nil then
		Lua.Throw("RegReflect 名字为" .. name .. "和名字为" .. old_info.name .. "哈希值冲突, 请为" .. name .. "修改名字来避开冲突！")
	end
	__all_name_struct[name] = info
	__all_id_struct[hash] = info
end

function ALittle.FindStructByName(name)
	return __all_name_struct[name]
end

function ALittle.FindStructById(id)
	return __all_id_struct[id]
end

function ALittle.GetAllStruct()
	return __all_id_struct
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1847150134, "ALittle.StructInfo", {
name = "ALittle.StructInfo", ns_name = "ALittle", rl_name = "StructInfo", hash_code = 1847150134,
name_list = {"name","ns_name","rl_name","hash_code","name_list","type_list","option_map"},
type_list = {"string","string","string","int","List<string>","List<string>","Map<string,string>"},
option_map = {}
})
ALittle.RegStruct(318154964, "ALittle.ClassInfo", {
name = "ALittle.ClassInfo", ns_name = "ALittle", rl_name = "ClassInfo", hash_code = 318154964,
name_list = {"__name","__super","__element","__child","__getter","__setter"},
type_list = {"string","ALittle.ClassInfo","List<ALittle.ClassInfo>","Map<string,ALittle.ClassInfo>","Map<string,Functor<(any):any>>","Map<string,Functor<(any,any)>>"},
option_map = {}
})

function ALittle.NewObject(clazz, ...)
	return clazz(...)
end

function ALittle.Cast(T, O, object)
	if object == nil then
		return nil
	end
	local o_info = (object).__class
	local t_info = T
	if o_info ~= t_info then
		return nil
	end
	return object
end

end
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
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Lua == nil then _G.Lua = {} end
local ___pairs = pairs
local ___ipairs = ipairs


local error = error
function Lua.TCall(...)
	local out_list = {pcall(...)}
	if out_list[1] ~= true then
		if out_list[2] == nil then
			return "nil"
		end
		return out_list[2]
	end
	local l = table.maxn(out_list)
	out_list[1] = nil
	return unpack(out_list, 1, l)
end

function Lua.Throw(msg)
	error(msg)
end

function Lua.Assert(value, msg)
	if value ~= nil and value ~= false then
		return
	end
	if msg == nil then
		msg = "Assert failed"
	end
	error(msg)
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-930447138, "ALittle.Thread", {
name = "ALittle.Thread", ns_name = "ALittle", rl_name = "Thread", hash_code = -930447138,
name_list = {},
type_list = {},
option_map = {}
})

ALittle.Coroutine = Lua.Class(nil, "ALittle.Coroutine")

function ALittle.Coroutine.Resume(thread, ...)
	return coroutine.resume(thread, ...)
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


local insert = table.insert
local remove = table.remove
local maxn = table.maxn
local sort = table.sort
function ALittle.List_MaxN(list)
	return maxn(list)
end

function ALittle.List_Push(list, object)
	insert(list, object)
end

function ALittle.List_Shuffle(list)
	local len = ALittle.List_MaxN(list)
	local i = 1
	while true do
		if not(i <= len) then break end
		local index = ALittle.Math_RandomInt(i, len)
		local temp = list[index]
		list[index] = list[i]
		list[i] = temp
		i = i+(1)
	end
end

function ALittle.List_PushList(list, other_list)
	for index, other in ___ipairs(other_list) do
		ALittle.List_Push(list, other)
	end
end

function ALittle.List_Find(list, object)
	for index, o in ___ipairs(list) do
		if o == object then
			return index
		end
	end
	return nil
end

function ALittle.List_Copy(list)
	local new_list = {}
	for index, o in ___ipairs(list) do
		new_list[index] = o
	end
	return new_list
end

function ALittle.List_Insert(list, index, object)
	insert(list, index, object)
end

function ALittle.List_IndexOf(list, object)
	for index, o in ___ipairs(list) do
		if o == object then
			return index
		end
	end
	return nil
end

function ALittle.List_Remove(list, index)
	remove(list, index)
end

function ALittle.List_Splice(list, index, count)
	do
		local endi = index + count
		while list[endi] ~= nil do
			list[index] = list[endi]
			index = index + 1
			endi = endi + 1
		end
		while count > 0 do
			list[endi - 1] = nil
			endi = endi - 1
			count = count - 1
		end
	end
end

function ALittle.List_Sort(list, cmp)
	sort(list, cmp)
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.LogLevel = {
	INFO = 0,
	WARN = 1,
	ERROR = 2,
}

local __LOG_FUNC = nil
function ALittle.SetLogFunc(func)
	__LOG_FUNC = func
end

function ALittle.Log(...)
	if __LOG_FUNC ~= nil then
		local scount = select("#", ...)
		local slist = {}
		local i = 1
		while true do
			if not(i <= scount) then break end
			slist[i] = ALittle.String_ToString(select(i, ...))
			i = i+(1)
		end
		local s = ALittle.String_Join(slist, "\t")
		__LOG_FUNC(s, 0)
		return
	end
	print(...)
end

function ALittle.Warn(...)
	if __LOG_FUNC ~= nil then
		local scount = select("#", ...)
		local slist = {}
		local i = 1
		while true do
			if not(i <= scount) then break end
			slist[i] = ALittle.String_ToString(select(i, ...))
			i = i+(1)
		end
		local s = ALittle.String_Join(slist, "\t")
		__LOG_FUNC(s, 1)
		return
	end
	print(...)
end

function ALittle.Error(...)
	if __LOG_FUNC ~= nil then
		local scount = select("#", ...)
		local slist = {}
		local i = 1
		while true do
			if not(i <= scount) then break end
			slist[i] = ALittle.String_ToString(select(i, ...))
			i = i+(1)
		end
		local s = ALittle.String_Join(slist, "\t")
		__LOG_FUNC(s, 2)
		return
	end
	print(...)
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function ALittle.IsEmpty(object)
	return next(object) == nil
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


local tonumber = tonumber
local floor = math.floor
local ceil = math.ceil
local random = math.random
local randomseed = math.randomseed
local abs = math.abs
local cos = math.cos
local sin = math.sin
local tan = math.tan
local sqrt = math.sqrt
function ALittle.Math_Min(x, y)
	if x < y then
		return x
	end
	return y
end

function ALittle.Math_Max(x, y)
	if x < y then
		return y
	end
	return x
end

function ALittle.Math_Sin(v)
	return sin(v)
end

function ALittle.Math_Tan(v)
	return tan(v)
end

function ALittle.Math_Cos(v)
	return cos(v)
end

function ALittle.Math_Abs(v)
	return abs(v)
end

function ALittle.Math_Floor(v)
	return floor(v)
end

function ALittle.Math_Ceil(v)
	return ceil(v)
end

function ALittle.Math_Sqrt(v)
	return sqrt(v)
end

function ALittle.Math_ToInt(s)
	local n = tonumber(s)
	if n == nil then
		return nil
	end
	return floor(n)
end

function ALittle.Math_ToIntOrZero(s)
	local value = ALittle.Math_ToInt(s)
	if value == nil then
		return 0
	end
	return value
end

function ALittle.Math_ToDouble(s)
	return tonumber(s)
end

function ALittle.Math_ToDoubleOrZero(s)
	local value = ALittle.Math_ToDouble(s)
	if value == nil then
		return 0
	end
	return value
end

function ALittle.Math_RandomSeed(seed)
	randomseed(seed)
end

function ALittle.Math_RandomInt(min, max)
	return random(min, max)
end

function ALittle.Math_RandomDouble(min, max)
	return random() * (max - min) + min
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


local byte = string.byte
local sub = string.sub
local len = string.len
local find = string.find
local upper = string.upper
local lower = string.lower
local match = string.match
local concat = table.concat
local tostring = tostring
local tonumber = tonumber
local floor = math.floor
function ALittle.String_Upper(s)
	return upper(s)
end

function ALittle.String_Lower(s)
	return lower(s)
end

function ALittle.String_ToString(s)
	return tostring(s)
end

function ALittle.String_Byte(s, index)
	return byte(s, index)
end

function ALittle.String_Type(v)
	return type(v)
end

function ALittle.String_Len(s)
	return len(s)
end

function ALittle.String_Find(s, t, init)
	local result = find(s, t, init, true)
	return result
end

function ALittle.String_Sub(s, starti, endi)
	return sub(s, starti, endi)
end

function ALittle.String_Trim(text)
	return string.gsub(text, "^%s*(.-)%s*$", "%1")
end

function ALittle.String_Split(target, sep)
	if target == nil or target == "" then
		return {}
	end
	if sep == nil or sep == "" then
		sep = ","
	end
	local fields = {}
	local fields_count = 0
	local start_pos = 1
	while true do
		local start_index = ALittle.String_Find(target, sep, start_pos)
		if start_index == nil then
			fields_count = fields_count + 1
			fields[fields_count] = ALittle.String_Sub(target, start_pos)
			break
		end
		fields_count = fields_count + 1
		fields[fields_count] = ALittle.String_Sub(target, start_pos, start_index - 1)
		start_pos = start_index + ALittle.String_Len(sep)
	end
	return fields
end

function ALittle.String_SplitSepList(target, sep_list)
	if target == nil or target == "" then
		return {}
	end
	if sep_list == nil then
		sep_list = {}
	end
	local fields = {}
	local fields_count = 0
	local start_pos = 1
	while true do
		local start_index
		local end_index
		for _, sep in ___ipairs(sep_list) do
			local start_index_tmp = ALittle.String_Find(target, sep, start_pos)
			if start_index_tmp ~= nil then
				if start_index == nil or start_index_tmp < start_index then
					start_index = start_index_tmp
					end_index = start_index + ALittle.String_Len(sep) - 1
				end
			end
		end
		if start_index == nil then
			local value = ALittle.String_Sub(target, start_pos)
			if ALittle.String_Len(value) > 0 then
				fields_count = fields_count + 1
				fields[fields_count] = ALittle.String_Sub(target, start_pos)
			end
			break
		end
		local value = ALittle.String_Sub(target, start_pos, start_index - 1)
		if ALittle.String_Len(value) > 0 then
			fields_count = fields_count + 1
			fields[fields_count] = ALittle.String_Sub(target, start_pos, start_index - 1)
		end
		start_pos = end_index + 1
	end
	return fields
end

function ALittle.String_Join(list, sep)
	if sep == nil then
		sep = ","
	end
	return concat(list, sep)
end

function ALittle.String_Replace(s, os, ns)
	return ALittle.String_Join(ALittle.String_Split(s, os), ns)
end

function ALittle.String_CopyTable(info)
	do
		local new_info = {}
		for key, value in ___pairs(info) do
			if type(value) ~= "table" then
				new_info[key] = value
			else
				new_info[key] = ALittle.String_CopyTable(value)
			end
		end
		return new_info
	end
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function ALittle.Time_GetCurTime()
	return os.time()
end

function ALittle.Time_GetCurDate(time)
	return os.date("%Y-%m-%d-%H-%M-%S", time)
end

function ALittle.Time_GetCurYMD(time)
	return os.date("%Y-%m-%d", time)
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpFileReceiver = Lua.Class(nil, "ALittle.IHttpFileReceiver")

function ALittle.IHttpFileReceiver:StartReceiveFile(file_path, start_size)
	local ___COROUTINE = coroutine.running()
	return "not impl"
end

local __all_callback = {}
function ALittle.RegHttpFileCallback(method, callback)
	if __all_callback[method] ~= nil then
		ALittle.Error("RegHttpFileCallback消息回调函数注册失败，名字为" .. method .. "已存在")
		return
	end
	__all_callback[method] = callback
end

function ALittle.FindHttpFileReceiverCallback(method)
	return __all_callback[method]
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpFileSender = Lua.Class(nil, "ALittle.IHttpFileSender")

function ALittle.IHttpFileSender:HandleSucceed()
end

function ALittle.IHttpFileSender:HandleProcess(cur_size, total_size)
end

function ALittle.IHttpFileSender:HandleFailed(reason)
end

function ALittle.IHttpFileSender:Stop()
end

function ALittle.IHttpFileSender:GetFilePath()
	return nil
end

function ALittle.IHttpFileSender:GetTotalSize()
	return 0
end

function ALittle.IHttpFileSender:GetCurSize()
	return 0
end

function ALittle.IHttpFileSender:SendDownloadRPC(thread, method, content, array_buffer)
	Lua.Throw("not impl")
end

function ALittle.IHttpFileSender:SendUploadRPC(thread, method, content, array_buffer)
	Lua.Throw("not impl")
end

function ALittle.IHttpFileSender.InvokeDownload(method, client, content, array_buffer)
	local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程"
	end
	client:SendDownloadRPC(___COROUTINE, method, content, array_buffer)
	return coroutine.yield()
end

function ALittle.IHttpFileSender.InvokeUpload(method, client, content, array_buffer)
	local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程"
	end
	client:SendUploadRPC(___COROUTINE, method, content, array_buffer)
	return coroutine.yield()
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpReceiver = Lua.Class(nil, "ALittle.IHttpReceiver")

local __all_callback = {}
function ALittle.RegHttpCallback(method, callback)
	if __all_callback[method] ~= nil then
		ALittle.Error("RegHttpCallback消息回调函数注册失败，名字为" .. method .. "已存在")
		return
	end
	__all_callback[method] = callback
end

function ALittle.FindHttpCallback(method)
	return __all_callback[method]
end

local __all_download_callback = {}
function ALittle.RegHttpDownloadCallback(method, callback)
	if __all_download_callback[method] ~= nil then
		ALittle.Error("RegHttpDownloadCallback消息回调函数注册失败，名字为" .. method .. "已存在")
		return
	end
	__all_download_callback[method] = callback
end

function ALittle.FindHttpDownloadCallback(method)
	return __all_download_callback[method]
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpSender = Lua.Class(nil, "ALittle.IHttpSender")

function ALittle.IHttpSender:HandleSucceed()
end

function ALittle.IHttpSender:HandleFailed(reason)
end

function ALittle.IHttpSender:Stop()
end

function ALittle.IHttpSender:SendRPC(thread, method, content)
	Lua.Throw("not impl")
end

function ALittle.IHttpSender.Invoke(method, client, content)
	local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程", nil
	end
	client:SendRPC(___COROUTINE, method, content)
	return coroutine.yield()
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IMessageWriteFactory = Lua.Class(nil, "ALittle.IMessageWriteFactory")

function ALittle.IMessageWriteFactory:SetID(id)
end

function ALittle.IMessageWriteFactory:SetRpcID(id)
end

function ALittle.IMessageWriteFactory:ResetOffset()
end

function ALittle.IMessageWriteFactory:GetOffset()
	return 0
end

function ALittle.IMessageWriteFactory:SetInt(offset, value)
end

function ALittle.IMessageWriteFactory:WriteBool(value)
	return 0
end

function ALittle.IMessageWriteFactory:WriteInt(value)
	return 0
end

function ALittle.IMessageWriteFactory:WriteLong(value)
	return 0
end

function ALittle.IMessageWriteFactory:WriteString(value)
	return 0
end

function ALittle.IMessageWriteFactory:WriteDouble(value)
	return 0
end

ALittle.IMessageReadFactory = Lua.Class(nil, "ALittle.IMessageReadFactory")

function ALittle.IMessageReadFactory:GetDataSize()
	return 0
end

function ALittle.IMessageReadFactory:ReadBool()
	return false
end

function ALittle.IMessageReadFactory:ReadInt()
	return 0
end

function ALittle.IMessageReadFactory:ReadLong()
	return 0
end

function ALittle.IMessageReadFactory:ReadString()
	return ""
end

function ALittle.IMessageReadFactory:ReadDouble()
	return 0
end

function ALittle.IMessageReadFactory:GetReadSize()
	return 0
end

ALittle.IMsgCommon = Lua.Class(nil, "ALittle.IMsgCommon")

function ALittle.IMsgCommon:IsConnected()
	return false
end

function ALittle.IMsgCommon:Close(reason)
end

function ALittle.IMsgCommon:HandleConnectSucceed()
end

function ALittle.IMsgCommon:HandleDisconnect()
end

function ALittle.IMsgCommon:HandleConnectFailed(reason)
end

function ALittle.IMsgCommon:HandleMessage(id, rpc_id, factory)
end

function ALittle.IMsgCommon:SendMsg(T, msg)
	local rflt = T
	self:Send(rflt.hash_code, msg, 0)
end

function ALittle.IMsgCommon:Send(msg_id, msg_body, rpc_id)
	Lua.Throw("not impl")
end

function ALittle.IMsgCommon:SendRPC(thread, msg_id, msg_body)
end

function ALittle.IMsgCommon.Invoke(msg_id, client, msg_body)
	client:Send(msg_id, msg_body, 0)
end

function ALittle.IMsgCommon.InvokeRPC(msg_id, client, msg_body)
	local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程", nil
	end
	if not client:IsConnected() then
		return "连接还没成功", nil
	end
	client:SendRPC(___COROUTINE, msg_id, msg_body)
	return coroutine.yield()
end

local __all_callback = {}
function ALittle.RegMsgCallback(msg_id, callback)
	if __all_callback[msg_id] ~= nil then
		ALittle.Error("RegMsgCallback消息回调函数注册失败，名字为" .. msg_id .. "已存在")
		return
	end
	__all_callback[msg_id] = callback
end

function ALittle.FindMsgCallback(msg_id)
	return __all_callback[msg_id]
end

local __all_rpc_callback = {}
local __all_rpc_return_id = {}
function ALittle.RegMsgRpcCallback(msg_id, callback, return_id)
	if __all_rpc_callback[msg_id] ~= nil then
		ALittle.Error("RegMsgRpcCallback消息回调函数注册失败，名字为" .. msg_id .. "已存在")
		return
	end
	__all_rpc_callback[msg_id] = callback
	__all_rpc_return_id[msg_id] = return_id
end

function ALittle.FindMsgRpcCallback(msg_id)
	return __all_rpc_callback[msg_id], __all_rpc_return_id[msg_id]
end

end