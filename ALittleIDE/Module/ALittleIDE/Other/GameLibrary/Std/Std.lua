-- ALittle Generate Lua And Do Not Edit This Line!
do
local ___pairs = pairs
local ___ipairs = ipairs


function _G.RequireStd(base_path)
	local ___COROUTINE = coroutine.running()
	Require(base_path, "Std/Reflect/ReflectCmd")
	Require(base_path, "Std/Reflect/ReflectCsv")
	Require(base_path, "Std/Reflect/ReflectMessage")
	Require(base_path, "Std/Loop/LoopObject")
	Require(base_path, "Std/Loop/ILoopSystem")
	Require(base_path, "Std/Loop/LoopFrame")
	Require(base_path, "Std/Loop/LoopFunction")
	Require(base_path, "Std/Loop/LoopGroup")
	Require(base_path, "Std/Loop/LoopList")
	Require(base_path, "Std/Loop/LoopTimer")
	Require(base_path, "Std/Utility/Bit")
	Require(base_path, "Std/Utility/WeakRef")
	Require(base_path, "Std/Utility/IHeapTimer")
	Require(base_path, "Std/Utility/ISchedule")
	Require(base_path, "Std/Utility/CsvConfig")
	Require(base_path, "Std/Utility/EventDispatcher")
	Require(base_path, "Std/Utility/SafeIDCreator")
	Require(base_path, "Std/Utility/String")
	Require(base_path, "Std/Utility/File")
	Require(base_path, "Std/Utility/JsonConfig")
	Require(base_path, "Std/Net/HttpFileReceiverTemplate")
	Require(base_path, "Std/Net/HttpFileSenderTemplate")
	Require(base_path, "Std/Net/HttpReceiverTemplate")
	Require(base_path, "Std/Net/HttpSenderTemplate")
	Require(base_path, "Std/Net/MsgCommonTemplate")
	Require(base_path, "Std/Net/MsgReceiverTemplate")
	Require(base_path, "Std/Net/MsgSenderTemplate")
	Require(base_path, "Std/Net/MsgSessionTemplate")
	Require(base_path, "Adapter/Lua/LuaHeapTimer")
	Require(base_path, "Adapter/Lua/LuaCsvFile")
	do
		Require(base_path, "Adapter/Lua/LuaHttpFileInterface")
		Require(base_path, "Adapter/Lua/LuaHttpInterface")
		Require(base_path, "Adapter/Lua/LuaMsgInterface")
		Require(base_path, "Adapter/Lua/LuaMessageFactory")
		Require(base_path, "Adapter/Lua/LuaSchedule")
	end
	do
		Require(base_path, "Adapter/Lua/ISocket")
		Require(base_path, "Adapter/Lua/LuaSocketSchedule")
	end
	Require(base_path, "Std/Singleton/LoopSystem")
	Require(base_path, "Std/Singleton/Schedule")
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(2073949729, "ALittle.CmdCallbackInfo", {
name = "ALittle.CmdCallbackInfo", ns_name = "ALittle", rl_name = "CmdCallbackInfo", hash_code = 2073949729,
name_list = {"callback","var_list","name_list","desc"},
type_list = {"Functor<(...)>","List<string>","List<string>","string"},
option_map = {}
})

local __all_callback = {}
function ALittle.RegCmdCallback(method, callback, var_list, name_list, desc)
	if __all_callback[method] ~= nil then
		ALittle.Error("RegCmdCallback消息回调函数注册失败，名字为" .. method .. "已存在")
		return
	end
	local info = {}
	info.callback = callback
	info.var_list = var_list
	info.name_list = name_list
	if desc == nil then
		info.desc = ""
	else
		info.desc = desc
	end
	__all_callback[method] = info
end

function ALittle.ExecuteCommand(cmd)
	if cmd == "" then
		ALittle.Warn("命令行是空")
		return
	end
	local method = ""
	local param = ""
	local index = ALittle.String_Find(cmd, " ")
	if index == nil then
		method = cmd
		param = ""
	else
		method = ALittle.String_Sub(cmd, 1, index - 1)
		param = ALittle.String_Sub(cmd, index + 1)
	end
	if ALittle.String_Upper(method) == "HELP" then
		local method_list = {}
		for method_name, info in ___pairs(__all_callback) do
			ALittle.List_Push(method_list, method_name)
		end
		ALittle.List_Sort(method_list)
		local out_list = {}
		ALittle.List_Push(out_list, "")
		ALittle.List_Push(out_list, "help 打印当前模块支持的指令列表")
		for _, method_name in ___ipairs(method_list) do
			local info = __all_callback[method_name]
			local detail = method_name .. " "
			local param_list = {}
			for i, v in ___ipairs(info.var_list) do
				ALittle.List_Push(param_list, info.name_list[i] .. ":" .. v)
			end
			detail = method_name .. " " .. ALittle.String_Join(param_list, ", ") .. " " .. info.desc
			ALittle.List_Push(out_list, detail)
		end
		ALittle.Log(ALittle.String_Join(out_list, "\n"))
		return
	end
	local info = __all_callback[method]
	if info == nil then
		ALittle.Warn("未知指令:" .. cmd)
		return
	end
	local param_list = {}
	index = 1
	local in_quote = false
	local len = ALittle.String_Len(param)
	local i = 1
	while i <= len do
		local byte = ALittle.String_Byte(param, i)
		if byte == 32 then
			if in_quote then
				i = i + 1
			else
				if index == i then
					i = i + 1
					index = i
				else
					ALittle.List_Push(param_list, ALittle.String_Sub(param, index, i - 1))
					i = i + 1
					index = i
				end
			end
		elseif byte == 34 then
			if in_quote then
				in_quote = false
				if index == i then
					ALittle.List_Push(param_list, "")
					i = i + 1
					index = i
				else
					ALittle.List_Push(param_list, ALittle.String_Sub(param, index, i - 1))
					i = i + 1
					index = i
				end
			else
				in_quote = true
				if index ~= i then
					ALittle.List_Push(param_list, ALittle.String_Sub(param, index, i - 1))
					i = i + 1
					index = i
				end
			end
		else
			i = i + 1
		end
	end
	if index ~= i then
		ALittle.List_Push(param_list, ALittle.String_Sub(param, index, i - 1))
		i = i + 1
		index = i
	end
	len = ALittle.List_MaxN(param_list)
	local need_len = ALittle.List_MaxN(info.var_list)
	if len ~= need_len then
		ALittle.Warn("输入的参数数量" .. len .. "和指令要求" .. need_len .. "的不一致")
		return
	end
	local value_list = {}
	for ii, _ in ___ipairs(param_list) do
		local var_type = info.var_list[ii]
		if var_type == "int" or var_type == "long" or var_type == "double" then
			value_list[ii] = ALittle.Math_ToDouble(param_list[ii])
			if value_list[ii] == nil then
				ALittle.Warn("输入的第" .. ii .. "个参数" .. param_list[ii] .. "转为" .. var_type .. "失败")
				return
			end
		elseif var_type == "string" then
			value_list[ii] = param_list[ii]
		elseif var_type == "bool" then
			if param_list[ii] == "true" then
				value_list[ii] = true
			elseif param_list[ii] == "false" then
				value_list[ii] = false
			else
				ALittle.Warn("输入的第" .. ii .. "个参数" .. param_list[ii] .. "转为" .. var_type .. "失败")
				return
			end
		else
			ALittle.Warn("输入的第" .. ii .. "个参数" .. param_list[ii] .. "转为" .. var_type .. "失败，支持基本变量类型")
			return
		end
	end
	info.callback(unpack(value_list, 1, len))
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1155101349, "ALittle.CsvInvokeInfo", {
name = "ALittle.CsvInvokeInfo", ns_name = "ALittle", rl_name = "CsvInvokeInfo", hash_code = -1155101349,
name_list = {"func","var_name","split","sub_info","handle"},
type_list = {"Functor<(string,ALittle.CsvInvokeInfo):any>","string","string","ALittle.CsvInvokeInfo","List<ALittle.CsvInvokeInfo>"},
option_map = {}
})

local floor = ALittle.Math_Floor
local tonumber = ALittle.Math_ToDouble
local maxn = ALittle.List_MaxN
local upper = ALittle.String_Upper
local Csv_ReadBool
Csv_ReadBool = function(content, value)
	return upper(content) == "TRUE"
end

local Csv_ReadInt
Csv_ReadInt = function(content, value)
	if content == "" then
		return 0
	end
	return floor(tonumber(content))
end

local Csv_ReadLong
Csv_ReadLong = function(content, value)
	if content == "" then
		return 0
	end
	return floor(tonumber(content))
end

local Csv_ReadString
Csv_ReadString = function(content, value)
	return content
end

local Csv_ReadDouble
Csv_ReadDouble = function(content, value)
	if content == "" then
		return 0
	end
	return tonumber(content)
end

local Csv_ReadArray
Csv_ReadArray = function(content, value)
	local list = ALittle.String_Split(content, value.split)
	local result = {}
	for index, sub in ___ipairs(list) do
		local v = value.sub_info.func(sub, value.sub_info)
		if v == nil then
			return nil
		end
		result[index] = v
	end
	return result
end

function ALittle.Csv_ReadMessage(content, value)
	local list = ALittle.String_Split(content, value.split)
	local t = {}
	for index, handle in ___ipairs(value.handle) do
		t[handle.var_name] = handle.func(list[index], handle)
	end
	return t
end

local __csv_read_data_map = {}
__csv_read_data_map["bool"] = Csv_ReadBool
__csv_read_data_map["int"] = Csv_ReadInt
__csv_read_data_map["long"] = Csv_ReadLong
__csv_read_data_map["string"] = Csv_ReadString
__csv_read_data_map["double"] = Csv_ReadDouble
local __split_list = {"*", "#", ";"}
local __split_list_last = __split_list[maxn(__split_list)]
local __split_list_max = maxn(__split_list)
local find = ALittle.String_Find
local sub = ALittle.String_Sub
function ALittle.CalcCsvSubInfoSplit(sub_type, split_index)
	if find(sub_type, "List<") == 1 then
		return ALittle.CalcCsvSubInfoSplit(sub(sub_type, 6, -2), split_index + 1)
	end
	if find(sub_type, "Map<") == 1 then
		Lua.Throw("不支持Map解析")
	end
	local func = __csv_read_data_map[sub_type]
	if func ~= nil then
		return split_index
	end
	return ALittle.CalcCsvInfoSplitImpl(sub_type, split_index + 1)
end

function ALittle.CalcCsvInfoSplitImpl(var_type, split_index)
	local rflt = ALittle.FindStructByName(var_type)
	Lua.Assert(rflt ~= nil, "FindReflectByName调用失败! 未知类型:" .. var_type)
	local max_count = split_index
	for index, var_name in ___ipairs(rflt.name_list) do
		local count = ALittle.CalcCsvSubInfoSplit(rflt.type_list[index], split_index)
		if max_count < count then
			max_count = count
		end
	end
	return max_count
end

function ALittle.CalcCsvInfoSplit(rflt)
	local max_count = 0
	for index, var_name in ___ipairs(rflt.name_list) do
		local count = ALittle.CalcCsvSubInfoSplit(rflt.type_list[index], 0)
		if max_count < count then
			max_count = count
		end
	end
	return max_count
end

function ALittle.CreateCsvSubInfo(sub_type, split_index)
	local func = __csv_read_data_map[sub_type]
	if func ~= nil then
		local sub_info = {}
		sub_info.func = func
		return sub_info
	end
	if find(sub_type, "List<") == 1 then
		return ALittle.CreateCsvArrayInfo(sub_type, split_index)
	end
	if find(sub_type, "Map<") == 1 then
		Lua.Throw("不支持Map解析")
	end
	return ALittle.CreateCsvInfoImpl(sub_type, split_index)
end

function ALittle.CreateCsvArrayInfo(var_type, split_index)
	Lua.Assert(split_index > 0, "分隔符数量不足")
	local invoke_info = {}
	invoke_info.func = Csv_ReadArray
	invoke_info.split = __split_list[split_index]
	invoke_info.sub_info = ALittle.CreateCsvSubInfo(sub(var_type, 6, -2), split_index - 1)
	return invoke_info
end

function ALittle.CreateCsvInfoImpl(var_type, split_index)
	Lua.Assert(split_index > 0, "分隔符数量不足")
	local rflt = ALittle.FindStructByName(var_type)
	Lua.Assert(rflt, "FindReflectByName调用失败! 未知类型:" .. var_type)
	local invoke_info = {}
	invoke_info.split = __split_list[split_index]
	invoke_info.func = ALittle.Csv_ReadMessage
	local handle = {}
	invoke_info.handle = handle
	local handle_count = 0
	for index, var_name in ___ipairs(rflt.name_list) do
		local var_info = ALittle.CreateCsvSubInfo(rflt.type_list[index], split_index - 1)
		var_info.var_name = var_name
		handle_count = handle_count + 1
		handle[handle_count] = var_info
	end
	return invoke_info
end

function ALittle.CreateCsvInfo(rflt)
	local split_index = ALittle.CalcCsvInfoSplit(rflt)
	local invoke_info = {}
	invoke_info.split = __split_list[split_index]
	invoke_info.func = ALittle.Csv_ReadMessage
	local handle = {}
	invoke_info.handle = handle
	local handle_count = 0
	for index, var_name in ___ipairs(rflt.name_list) do
		local var_info = ALittle.CreateCsvSubInfo(rflt.type_list[index], split_index)
		var_info.var_name = var_name
		handle_count = handle_count + 1
		handle[handle_count] = var_info
	end
	return invoke_info
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
ALittle.RegStruct(1821069430, "ALittle.ProtocolAnyStruct", {
name = "ALittle.ProtocolAnyStruct", ns_name = "ALittle", rl_name = "ProtocolAnyStruct", hash_code = 1821069430,
name_list = {"hash_code","value"},
type_list = {"int","any"},
option_map = {}
})
ALittle.RegStruct(-1602043290, "ALittle.ProtocolInvokeInfo", {
name = "ALittle.ProtocolInvokeInfo", ns_name = "ALittle", rl_name = "ProtocolInvokeInfo", hash_code = -1602043290,
name_list = {"wfunc","rfunc","rflt","var_name","key_info","value_info","sub_info","handle"},
type_list = {"Functor<(ALittle.IMessageWriteFactory,ALittle.ProtocolInvokeInfo,any,any):int>","Functor<(ALittle.IMessageReadFactory,ALittle.ProtocolInvokeInfo,any,int):any,int>","ALittle.StructInfo","string","ALittle.ProtocolInvokeInfo","ALittle.ProtocolInvokeInfo","ALittle.ProtocolInvokeInfo","List<ALittle.ProtocolInvokeInfo>"},
option_map = {}
})

local __all_name_invoke = {}
local __all_id_invoke = {}
local PS_WriteBool
PS_WriteBool = function(factory, var_info, parent, var_value)
	if var_value == nil then
		return factory:WriteBool(false)
	end
	return factory:WriteBool(var_value)
end

local PS_WriteInt
PS_WriteInt = function(factory, var_info, parent, var_value)
	if var_value == nil then
		return factory:WriteInt(0)
	end
	return factory:WriteInt(var_value)
end

local PS_WriteString
PS_WriteString = function(factory, var_info, parent, var_value)
	if var_value == nil then
		return factory:WriteString("")
	end
	return factory:WriteString(var_value)
end

local PS_WriteDouble
PS_WriteDouble = function(factory, var_info, parent, var_value)
	if var_value == nil then
		return factory:WriteDouble(0)
	end
	return factory:WriteDouble(var_value)
end

local PS_WriteLong
PS_WriteLong = function(factory, var_info, parent, var_value)
	if var_value == nil then
		return factory:WriteLong(0)
	end
	return factory:WriteLong(var_value)
end

local PS_WriteArray
PS_WriteArray = function(factory, var_info, parent, var_value)
	if var_value == nil then
		return factory:WriteInt(0)
	end
	local offset = factory:GetOffset()
	local l = factory:WriteInt(0)
	local sub_info = var_info.sub_info
	local sub_func = sub_info.wfunc
	local count = 0
	for index, value in ___ipairs(var_value) do
		l = l + sub_func(factory, sub_info, var_value, value)
		count = count + 1
	end
	factory:SetInt(offset, count)
	return l
end

local PS_WriteMap
PS_WriteMap = function(factory, var_info, parent, var_value)
	if var_value == nil then
		return factory:WriteInt(0)
	end
	local offset = factory:GetOffset()
	local l = factory:WriteInt(0)
	local key_info = var_info.key_info
	local key_func = key_info.wfunc
	local value_info = var_info.value_info
	local value_func = value_info.wfunc
	local count = 0
	for key, value in ___pairs(var_value) do
		l = l + key_func(factory, key_info, var_value, key)
		l = l + value_func(factory, value_info, var_value, value)
		count = count + 1
	end
	factory:SetInt(offset, count)
	return l
end

function ALittle.PS_WriteMessage(factory, var_info, parent, var_value)
	if var_value == nil then
		local offset = factory:GetOffset()
		local pre_size = factory:WriteInt(0)
		local size = 0
		for index, info in ___ipairs(var_info.handle) do
			size = size + info.wfunc(factory, info, var_value, nil)
		end
		factory:SetInt(offset, size)
		return pre_size + size
	end
	local offset = factory:GetOffset()
	local pre_size = factory:WriteInt(0)
	local size = 0
	for index, info in ___ipairs(var_info.handle) do
		size = size + info.wfunc(factory, info, var_value, var_value[info.var_name])
	end
	factory:SetInt(offset, size)
	return pre_size + size
end

function ALittle.PS_WriteAny(factory, var_info, parent, var_value)
	local invoke_info = ALittle.CreateProtocolInvokeInfo(parent.hash_code)
	return ALittle.PS_WriteMessage(factory, invoke_info, parent, var_value)
end

function ALittle.PS_WriteMessageForSend(factory, var_info, parent, var_value)
	if var_value == nil then
		local offset = factory:GetOffset()
		local size = 0
		for index, info in ___ipairs(var_info.handle) do
			size = size + info.wfunc(factory, info, var_value, nil)
		end
		return size
	end
	local offset = factory:GetOffset()
	local size = 0
	for index, info in ___ipairs(var_info.handle) do
		size = size + info.wfunc(factory, info, var_value, var_value[info.var_name])
	end
	return size
end

local PS_ReadBool
PS_ReadBool = function(factory, var_info, parent, l)
	if l == 0 then
		return false, 0
	end
	if l < 1 then
		return false, -1
	end
	return factory:ReadBool(), 1
end

local PS_ReadInt
PS_ReadInt = function(factory, var_info, parent, l)
	if l == 0 then
		return 0, 0
	end
	if l < 4 then
		return 0, -1
	end
	return factory:ReadInt(), 4
end

local PS_ReadString
PS_ReadString = function(factory, var_info, parent, l)
	if l == 0 then
		return "", 0
	end
	return factory:ReadString(), factory:GetReadSize()
end

local PS_ReadDouble
PS_ReadDouble = function(factory, var_info, parent, l)
	if l == 0 then
		return 0, 0
	end
	if l < 8 then
		return 0, -1
	end
	return factory:ReadDouble(), 8
end

local PS_ReadLong
PS_ReadLong = function(factory, var_info, parent, l)
	if l == 0 then
		return 0, 0
	end
	if l < 8 then
		return 0, -1
	end
	return factory:ReadLong(), 8
end

local PS_ReadArray
PS_ReadArray = function(factory, var_info, parent, l)
	if l == 0 then
		return {}, 0
	end
	local save_len = l
	if l < 4 then
		return nil, -1
	end
	local count = factory:ReadInt()
	l = l - 4
	if count < 0 then
		return nil, -1
	end
	local sub_info = var_info.sub_info
	local sub_func = sub_info.rfunc
	local sub_len = 0
	local value_list = {}
	local index = 1
	while true do
		if not(index <= count) then break end
		value_list[index], sub_len = sub_func(factory, sub_info, value_list, l)
		if sub_len < 0 then
			return nil, sub_len
		end
		l = l - (sub_len)
		index = index+(1)
	end
	return value_list, save_len - l
end

local PS_ReadMap
PS_ReadMap = function(factory, var_info, parent, l)
	if l == 0 then
		return {}, 0
	end
	local save_len = l
	if l < 4 then
		return nil, -1
	end
	local count = factory:ReadInt()
	l = l - 4
	if count < 0 then
		return nil, -1
	end
	local key_info = var_info.key_info
	local key_func = key_info.rfunc
	local value_info = var_info.value_info
	local value_func = value_info.rfunc
	do
		local value_map = {}
		local index = 1
		while true do
			if not(index <= count) then break end
			local key, key_len = key_func(factory, key_info, value_map, l)
			if key_len < 0 then
				return nil, key_len
			end
			l = l - key_len
			local value, value_len = value_func(factory, value_info, value_map, l)
			if value_len < 0 then
				return nil, value_len
			end
			l = l - value_len
			value_map[key] = value
			index = index+(1)
		end
		return value_map, save_len - l
	end
end

function ALittle.PS_ReadMessage(factory, var_info, parent, l)
	if l == 0 then
		local value_map = {}
		local sub_len = 0
		for index, info in ___ipairs(var_info.handle) do
			value_map[info.var_name], sub_len = info.rfunc(factory, info, value_map, 0)
		end
		return value_map, 0
	end
	if l < 4 then
		return nil, -1
	end
	local object_len = factory:ReadInt()
	l = l - 4
	local save_len = 4
	if object_len > l then
		return nil, -1
	end
	save_len = save_len + object_len
	local sub_len = 0
	local value_map = {}
	for index, info in ___ipairs(var_info.handle) do
		value_map[info.var_name], sub_len = info.rfunc(factory, info, value_map, object_len)
		if sub_len < 0 then
			return nil, sub_len
		end
		object_len = object_len - sub_len
	end
	return value_map, save_len
end

function ALittle.PS_ReadAny(factory, var_info, parent, l)
	local invoke_info = ALittle.CreateProtocolInvokeInfo(parent.hash_code)
	return ALittle.PS_ReadMessage(factory, invoke_info, parent, l)
end

function ALittle.PS_ReadMessageForReceive(factory, var_info, parent, l)
	if l == 0 then
		local value_map = {}
		local sub_len = 0
		for index, info in ___ipairs(var_info.handle) do
			value_map[info.var_name], sub_len = info.rfunc(factory, info, value_map, 0)
		end
		return value_map, 0
	end
	local sub_len = 0
	local value_map = {}
	for index, info in ___ipairs(var_info.handle) do
		value_map[info.var_name], sub_len = info.rfunc(factory, info, value_map, l)
		if sub_len < 0 then
			return nil, sub_len
		end
		l = l - sub_len
	end
	return value_map, l
end

local __ps_write_data_map = {}
__ps_write_data_map["bool"] = PS_WriteBool
__ps_write_data_map["int"] = PS_WriteInt
__ps_write_data_map["long"] = PS_WriteLong
__ps_write_data_map["string"] = PS_WriteString
__ps_write_data_map["double"] = PS_WriteDouble
__ps_write_data_map["any"] = ALittle.PS_WriteAny
local __ps_read_data_map = {}
__ps_read_data_map["bool"] = PS_ReadBool
__ps_read_data_map["int"] = PS_ReadInt
__ps_read_data_map["long"] = PS_ReadLong
__ps_read_data_map["string"] = PS_ReadString
__ps_read_data_map["double"] = PS_ReadDouble
__ps_read_data_map["any"] = ALittle.PS_ReadAny
local find = ALittle.String_Find
local sub = ALittle.String_Sub
local len = ALittle.String_Len
local byte = ALittle.String_Byte
function ALittle.CreateSubInfo(sub_type)
	local wfunc = __ps_write_data_map[sub_type]
	if wfunc ~= nil then
		local sub_info = {}
		sub_info.wfunc = wfunc
		sub_info.rfunc = __ps_read_data_map[sub_type]
		return sub_info
	end
	if find(sub_type, "List<") == 1 then
		return ALittle.CreateArrayInfo(sub_type)
	end
	if find(sub_type, "Map<") == 1 then
		return ALittle.CreateMapInfo(sub_type)
	end
	return ALittle.CreateMessageInfo(sub_type)
end

function ALittle.CreateArrayInfo(var_type)
	local invoke_info = {}
	invoke_info.wfunc = PS_WriteArray
	invoke_info.rfunc = PS_ReadArray
	invoke_info.sub_info = ALittle.CreateSubInfo(sub(var_type, 6, -2))
	return invoke_info
end

function ALittle.CreateMapInfo(var_type)
	local invoke_info = {}
	local sub_type = sub(var_type, 5, -2)
	local comma_index = 0
	local sub_type_len = len(sub_type)
	local ltgt = 0
	local i = 1
	while true do
		if not(i <= sub_type_len) then break end
		local code = byte(sub_type, i)
		if code == 60 then
			ltgt = ltgt + 1
		elseif code == 62 then
			ltgt = ltgt - 1
		elseif code == 44 then
			if ltgt == 0 then
				comma_index = i
				break
			end
		end
		i = i+(1)
	end
	Lua.Assert(comma_index ~= 0, "can'f find comma in var_type:" .. var_type)
	invoke_info.wfunc = PS_WriteMap
	invoke_info.rfunc = PS_ReadMap
	invoke_info.key_info = ALittle.CreateSubInfo(sub(sub_type, 1, comma_index - 1))
	invoke_info.value_info = ALittle.CreateSubInfo(sub(sub_type, comma_index + 1))
	return invoke_info
end

function ALittle.CreateMessageInfo(var_type)
	local invoke = __all_name_invoke[var_type]
	if invoke ~= nil then
		return invoke
	end
	local rflt = ALittle.FindStructByName(var_type)
	Lua.Assert(rflt ~= nil, "FindReflect调用失败! 未知类型:" .. var_type)
	invoke = ALittle.CreateMessageInfoImpl(rflt)
	__all_id_invoke[rflt.hash_code] = invoke
	__all_name_invoke[rflt.name] = invoke
	return invoke
end

function ALittle.CreateMessageInfoImpl(rflt)
	local invoke_info = {}
	invoke_info.wfunc = ALittle.PS_WriteMessage
	invoke_info.rfunc = ALittle.PS_ReadMessage
	invoke_info.rflt = rflt
	local handle = {}
	invoke_info.handle = handle
	local handle_count = 0
	for index, var_name in ___ipairs(rflt.name_list) do
		local var_info = ALittle.CreateSubInfo(rflt.type_list[index])
		var_info.var_name = var_name
		handle_count = handle_count + 1
		handle[handle_count] = var_info
	end
	return invoke_info
end

function ALittle.CreateProtocolInvokeInfo(msg_id)
	local invoke = __all_id_invoke[msg_id]
	if invoke ~= nil then
		return invoke
	end
	local rflt = ALittle.FindStructById(msg_id)
	Lua.Assert(rflt ~= nil, "FindReflect调用失败! 未知ID:" .. msg_id)
	invoke = ALittle.CreateMessageInfoImpl(rflt)
	__all_id_invoke[rflt.hash_code] = invoke
	__all_name_invoke[rflt.name] = invoke
	return invoke
end

local CollectStructInfo
CollectStructInfo = function(invoke, map)
	if invoke == nil then
		return
	end
	if invoke.rflt ~= nil then
		if map[invoke.rflt.hash_code] ~= nil then
			return
		end
		map[invoke.rflt.hash_code] = invoke.rflt
	end
	if invoke.key_info ~= nil then
		CollectStructInfo(invoke.key_info, map)
	end
	if invoke.value_info ~= nil then
		CollectStructInfo(invoke.value_info, map)
	end
	if invoke.sub_info ~= nil then
		CollectStructInfo(invoke.sub_info, map)
	end
	if invoke.handle ~= nil then
		for index, info in ___ipairs(invoke.handle) do
			CollectStructInfo(info, map)
		end
	end
end

function ALittle.CollectStructReflect(info, map)
	if info == nil then
		return "参数info是null"
	end
	local error, invoke = Lua.TCall(ALittle.CreateMessageInfoImpl, info)
	if error ~= nil then
		return error
	end
	CollectStructInfo(invoke, map)
	return nil
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.LoopObject = Lua.Class(nil, "ALittle.LoopObject")

function ALittle.LoopObject:IsCompleted()
	return true
end

function ALittle.LoopObject:Completed()
end

function ALittle.LoopObject:Update(frame_time)
end

function ALittle.LoopObject:Reset()
end

function ALittle.LoopObject:SetTime(time)
	return time, true
end

function ALittle.LoopObject:SetCompleted()
end

function ALittle.LoopObject:Dispose(deep)
	self:Stop()
end

function ALittle.LoopObject:Start()
	A_LuaLoopSystem:AddUpdater(self)
end

function ALittle.LoopObject:Stop()
	A_LuaLoopSystem:RemoveUpdater(self)
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.ILoopSystem = Lua.Class(nil, "ALittle.ILoopSystem")

function ALittle.ILoopSystem:Update(frame_time)
end

function ALittle.ILoopSystem:AddTimer(delay_ms, callback, loop, interval_ms)
	return 0
end

function ALittle.ILoopSystem:RemoveTimer(id)
	return false
end

function ALittle.ILoopSystem:AddUpdater(object)
end

function ALittle.ILoopSystem:RemoveUpdater(object)
end

function ALittle.ILoopSystem:HasUpdater(object)
	return false
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.LoopObject, " extends class:ALittle.LoopObject is nil")
ALittle.LoopFrame = Lua.Class(ALittle.LoopObject, "ALittle.LoopFrame")

function ALittle.LoopFrame:Ctor(func)
	___rawset(self, "_func", func)
	___rawset(self, "_force_completed", false)
	if self._func == nil then
		___rawset(self, "_force_completed", true)
		ALittle.Log("LoopFrame create failed:function is nil or not a function")
		return
	end
end

function ALittle.LoopFrame:Reset()
end

function ALittle.LoopFrame:Completed()
end

function ALittle.LoopFrame:IsCompleted()
	return self._force_completed
end

function ALittle.LoopFrame:SetCompleted()
	self._force_completed = true
end

function ALittle.LoopFrame:SetTime(time)
	return time, true
end

function ALittle.LoopFrame:Update(frame_time)
	self._func(frame_time)
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.LoopObject, " extends class:ALittle.LoopObject is nil")
ALittle.LoopFunction = Lua.Class(ALittle.LoopObject, "ALittle.LoopFunction")

function ALittle.LoopFunction:Ctor(func, count, interval_time, delay_time)
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
		ALittle.Log("LoopFunction create failed:function is nil or not a function")
		return
	end
	___rawset(self, "_complete_callback", nil)
end

function ALittle.LoopFunction.__getter:complete_callback()
	return self._complete_callback
end

function ALittle.LoopFunction.__setter:complete_callback(value)
	self._complete_callback = value
end

function ALittle.LoopFunction:Reset()
	self._accumulate_count = 0
	self._accumulate_time = 0
	self._accumulate_delay_time = 0
end

function ALittle.LoopFunction:Completed()
	if self._complete_callback ~= nil then
		self._complete_callback()
	end
end

function ALittle.LoopFunction:IsCompleted()
	if self._force_completed then
		return true
	end
	if self._total_count < 0 then
		return false
	end
	return self._total_count <= self._accumulate_count
end

function ALittle.LoopFunction:SetCompleted()
	if self._total_count < 0 then
		self._force_completed = true
		return
	end
	self._accumulate_count = self._total_count
end

function ALittle.LoopFunction:SetTime(time)
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
		local count = ALittle.Math_Floor(float_count)
		self._accumulate_count = count
		self._accumulate_time = ALittle.Math_Floor((float_count - count) * self._total_interval_time)
		return 0, false
	end
	self._accumulate_count = self._total_count
	return time - total_time, true
end

function ALittle.LoopFunction:Update(frame_time)
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

end
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
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.LoopObject, " extends class:ALittle.LoopObject is nil")
ALittle.LoopList = Lua.Class(ALittle.LoopObject, "ALittle.LoopList")

function ALittle.LoopList:Ctor()
	___rawset(self, "_count", 0)
	___rawset(self, "_cur_index", 1)
	___rawset(self, "_update_list", {})
	___rawset(self, "_complete_callback", nil)
end

function ALittle.LoopList.__getter:complete_callback()
	return self._complete_callback
end

function ALittle.LoopList.__setter:complete_callback(value)
	self._complete_callback = value
end

function ALittle.LoopList.__getter:total_count()
	return self._count
end

function ALittle.LoopList:AddUpdater(value)
	if value == nil then
		return
	end
	self._count = self._count + 1
	self._update_list[self._count] = value
end

function ALittle.LoopList:RemoveUpdater(value)
	if value == nil or self._count == 0 then
		return
	end
	for index, updater in ___ipairs(self._update_list) do
		if value == updater then
			if self._cur_index > index then
				self._cur_index = self._cur_index - 1
			end
			ALittle.List_Remove(self._update_list, index)
			self._count = self._count - 1
			break
		end
	end
end

function ALittle.LoopList:Reset()
	self._cur_index = 1
	for index, updater in ___ipairs(self._update_list) do
		updater:Reset()
	end
end

function ALittle.LoopList:SetTime(time)
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

function ALittle.LoopList:IsCompleted()
	return self._cur_index > self._count
end

function ALittle.LoopList:Completed()
	if self._complete_callback ~= nil then
		self._complete_callback()
	end
end

function ALittle.LoopList:SetCompleted()
	local index = self._cur_index
	while true do
		if not(index <= self._count) then break end
		self._update_list[index]:SetCompleted()
		index = index+(1)
	end
	self._cur_index = self._count + 1
end

function ALittle.LoopList:Update(frame_time)
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

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.LoopObject, " extends class:ALittle.LoopObject is nil")
ALittle.LoopTimer = Lua.Class(ALittle.LoopObject, "ALittle.LoopTimer")

function ALittle.LoopTimer:Ctor(func, delay_time)
	___rawset(self, "_func", func)
	if delay_time == nil or delay_time < 0 then
		delay_time = 0
	end
	___rawset(self, "_total_delay_time", delay_time)
	___rawset(self, "_accumulate_count", 0)
	___rawset(self, "_accumulate_delay_time", 0)
	if self._func == nil then
		___rawset(self, "_accumulate_count", 1)
		___rawset(self, "_accumulate_delay_time", self._total_delay_time)
		ALittle.Log("LoopTimer create failed:function is nil or not a function")
		return
	end
	___rawset(self, "_complete_callback", nil)
end

function ALittle.LoopTimer.__getter:complete_callback()
	return self._complete_callback
end

function ALittle.LoopTimer.__setter:complete_callback(value)
	self._complete_callback = value
end

function ALittle.LoopTimer:Reset()
	self._accumulate_count = 0
	self._accumulate_delay_time = 0
end

function ALittle.LoopTimer:Completed()
	if self._complete_callback ~= nil then
		self._complete_callback()
	end
end

function ALittle.LoopTimer:IsCompleted()
	return self._accumulate_count >= 1
end

function ALittle.LoopTimer:SetCompleted()
	if self._accumulate_count >= 1 then
		return
	end
	self._accumulate_count = 1
	self._accumulate_delay_time = self._total_delay_time
	self._func()
end

function ALittle.LoopTimer:SetTime(time)
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
	self._func()
	return time - self._total_delay_time, true
end

function ALittle.LoopTimer:Update(frame_time)
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
	self._func()
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function ALittle.BitAnd(x, y)
	return bit.band(x, y)
end

function ALittle.BitOr(x, y)
	return bit.bor(x, y)
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(115253948, "ALittle.KeyValueInfo", {
name = "ALittle.KeyValueInfo", ns_name = "ALittle", rl_name = "KeyValueInfo", hash_code = 115253948,
name_list = {"key","value"},
type_list = {"string","string"},
option_map = {}
})

ALittle.ICsvFile = Lua.Class(nil, "ALittle.ICsvFile")

function ALittle.ICsvFile:Close()
end

function ALittle.ICsvFile:ReadCell(row, col)
	return ""
end

function ALittle.ICsvFile:GetRowCount()
	return 0
end

function ALittle.ICsvFile:GetColCount()
	return 0
end

ALittle.ICsvFileLoader = Lua.Class(nil, "ALittle.ICsvFileLoader")

function ALittle.ICsvFileLoader:Start()
end

function ALittle.ICsvFileLoader:SetPath(file_path, only_from_asset)
end

function ALittle.ICsvFileLoader:GetPath()
	return nil
end

function ALittle.ICsvFileLoader:GetID()
	return nil
end

ALittle.CsvConfig = Lua.Class(nil, "ALittle.CsvConfig")

function ALittle.CsvConfig:Load(file_path)
	local lua_file = Lua.LuaCsvFile()
	Lua.Assert(lua_file:Load(file_path), file_path .. " load failed!")
	self:Init(lua_file)
	ALittle.Log(file_path .. " load succeed!")
end

function ALittle.CsvConfig:Init(file)
end

assert(ALittle.CsvConfig, " extends class:ALittle.CsvConfig is nil")
ALittle.KeyValueConfig = Lua.Class(ALittle.CsvConfig, "ALittle.KeyValueConfig")

function ALittle.KeyValueConfig:Ctor()
	___rawset(self, "_data", {})
	___rawset(self, "_csv_info", ALittle.CreateCsvInfo(self.__class.__element[1]))
end

function ALittle.KeyValueConfig:Init(file)
	if file == nil then
		return
	end
	local reflt = self.__class.__element[1]
	local handle_map = {}
	for index, handle in ___ipairs(self._csv_info.handle) do
		handle_map[handle.var_name] = handle
	end
	local row_count = file:GetRowCount()
	local row = 1
	while true do
		if not(row <= row_count) then break end
		local key = file:ReadCell(row, 1)
		local value = file:ReadCell(row, 2)
		if key ~= nil and value ~= nil then
			local handle = handle_map[key]
			if handle ~= nil then
				local hvalue = handle.func(value, handle)
				if hvalue ~= nil then
					self._data[key] = hvalue
				else
					ALittle.Error("key:" .. key .. " load failed!")
				end
			end
		end
		row = row+(1)
	end
	file:Close()
end

function ALittle.KeyValueConfig:GetFieldNameList()
	local rflt = ___all_struct[115253948]
	return rflt.name_list
end

function ALittle.KeyValueConfig:GetData()
	return self._data
end

assert(ALittle.CsvConfig, " extends class:ALittle.CsvConfig is nil")
ALittle.CsvTableConfig = Lua.Class(ALittle.CsvConfig, "ALittle.CsvTableConfig")

function ALittle.CsvTableConfig:Ctor()
	local error = nil
	error, self._csv_info = Lua.TCall(ALittle.CreateCsvInfo, self.__class.__element[1])
	if error ~= nil then
		ALittle.Error(error)
	end
	___rawset(self, "_col_map", {})
end

function ALittle.CsvTableConfig:Init(file)
	if self._csv_file ~= nil then
		self._csv_file:Close()
	end
	self._csv_file = file
	if self._csv_file == nil then
		return
	end
	local rflt = self.__class.__element[1]
	local name_map = {}
	for index, name in ___ipairs(rflt.name_list) do
		name_map[name] = index
	end
	local i = 1
	while true do
		if not(i <= self._csv_file:GetColCount()) then break end
		local name = self._csv_file:ReadCell(1, i)
		local index = name_map[name]
		if index ~= nil then
			self._col_map[index] = i
		end
		i = i+(1)
	end
	self:onInit()
end

function ALittle.CsvTableConfig:onInit()
end

function ALittle.CsvTableConfig:LoadCell(row)
	local value = {}
	for index, handle in ___ipairs(self._csv_info.handle) do
		local real = self._col_map[index]
		if real == nil then
			value[handle.var_name] = handle.func("", handle)
		else
			local read = self._csv_file:ReadCell(row, real)
			if read == nil then
				value[handle.var_name] = handle.func("", handle)
			else
				value[handle.var_name] = handle.func(read, handle)
			end
		end
	end
	return value
end

assert(ALittle.CsvTableConfig, " extends class:ALittle.CsvTableConfig is nil")
ALittle.SingleKeyTableConfig = Lua.Class(ALittle.CsvTableConfig, "ALittle.SingleKeyTableConfig")

function ALittle.SingleKeyTableConfig:Ctor()
	___rawset(self, "_key_map", {})
	___rawset(self, "_cache_map", {})
end

function ALittle.SingleKeyTableConfig:onInit()
	local rflt = self.__class.__element[1]
	local key_type = rflt.type_list[1]
	local key_index = self._col_map[1]
	local is_int = key_type == "int" or key_type == "long"
	local is_double = key_type == "double"
	local row_count = self._csv_file:GetRowCount()
	local row = 2
	while true do
		if not(row <= row_count) then break end
		local value = self._csv_file:ReadCell(row, key_index)
		if value ~= nil then
			if is_int then
				self._key_map[ALittle.Math_ToInt(value)] = row
			elseif is_double then
				self._key_map[ALittle.Math_ToDouble(value)] = row
			else
				self._key_map[value] = row
			end
		end
		row = row+(1)
	end
end

function ALittle.SingleKeyTableConfig:GetData(key)
	if self._csv_file == nil then
		return nil
	end
	local value = self._cache_map[key]
	if value ~= nil then
		return value
	end
	local row = self._key_map[key]
	if row == nil then
		return nil
	end
	value = self:LoadCell(row)
	if value == nil then
		return nil
	end
	self._cache_map[key] = value
	return value
end

assert(ALittle.CsvTableConfig, " extends class:ALittle.CsvTableConfig is nil")
ALittle.DoubleKeyTableConfig = Lua.Class(ALittle.CsvTableConfig, "ALittle.DoubleKeyTableConfig")

function ALittle.DoubleKeyTableConfig:Ctor()
	___rawset(self, "_key_map", {})
	___rawset(self, "_cache_map", {})
end

function ALittle.DoubleKeyTableConfig:onInit()
	local rflt = self.__class.__element[1]
	local first_key_type = rflt.type_list[1]
	local first_key_index = self._col_map[1]
	local first_is_int = first_key_type == "int" or first_key_type == "long"
	local first_is_double = first_key_type == "double"
	local second_key_type = rflt.type_list[2]
	local second_key_index = self._col_map[2]
	local second_is_int = second_key_type == "int" or second_key_type == "long"
	local second_is_double = second_key_type == "double"
	local row_count = self._csv_file:GetRowCount()
	local row = 2
	while true do
		if not(row <= row_count) then break end
		local tmp
		local value = self._csv_file:ReadCell(row, first_key_index)
		if value ~= nil then
			if first_is_int then
				tmp = self._key_map[ALittle.Math_ToInt(value)]
				if tmp == nil then
					tmp = {}
					self._key_map[ALittle.Math_ToInt(value)] = tmp
				end
			elseif first_is_double then
				tmp = self._key_map[ALittle.Math_ToDouble(value)]
				if tmp == nil then
					tmp = {}
					self._key_map[ALittle.Math_ToDouble(value)] = tmp
				end
			else
				tmp = self._key_map[value]
				if tmp == nil then
					tmp = {}
					self._key_map[value] = tmp
				end
			end
		end
		if tmp == nil then
			goto continue_1
		end
		value = self._csv_file:ReadCell(row, second_key_index)
		if value ~= nil then
			if second_is_int then
				tmp[ALittle.Math_ToInt(value)] = row
			elseif second_is_double then
				tmp[ALittle.Math_ToDouble(value)] = row
			else
				tmp[value] = row
			end
		end
		::continue_1::
		row = row+(1)
	end
end

function ALittle.DoubleKeyTableConfig:GetData(first_key, second_key)
	if self._csv_file == nil then
		return nil
	end
	local value_map = self._cache_map[first_key]
	if value_map ~= nil then
		local value = value_map[second_key]
		if value ~= nil then
			return value
		end
	end
	local key_tmp = self._key_map[first_key]
	if key_tmp == nil then
		return nil
	end
	local row = key_tmp[second_key]
	if row == nil then
		return nil
	end
	local value = self:LoadCell(row)
	if value == nil then
		return nil
	end
	local tmp = self._cache_map[first_key]
	if tmp == nil then
		tmp = {}
		self._cache_map[first_key] = tmp
	end
	tmp[second_key] = value
	return value
end

end
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
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


local open = io.open
local rename = os.rename
local remove = os.remove
local attributes = lfs.attributes
local dir = lfs.dir
local currentdir = lfs.currentdir
local chdir = lfs.chdir
local rmdir = lfs.rmdir
local mkdir = lfs.mkdir
ALittle.IFileLoader = Lua.Class(nil, "ALittle.IFileLoader")

function ALittle.IFileLoader:Load(file_path)
	return nil
end

assert(ALittle.IFileLoader, " extends class:ALittle.IFileLoader is nil")
ALittle.LuaFileLoader = Lua.Class(ALittle.IFileLoader, "ALittle.LuaFileLoader")

function ALittle.LuaFileLoader:Load(file_path)
	local file = open(file_path, "r")
	if file == nil then
		return nil
	end
	local content = file:read("*a")
	file:close()
	return content
end

ALittle.IFileSaver = Lua.Class(nil, "ALittle.IFileSaver")

function ALittle.IFileSaver:Save(file_path, content)
	return false
end

assert(ALittle.IFileSaver, " extends class:ALittle.IFileSaver is nil")
ALittle.LuaFileSaver = Lua.Class(ALittle.IFileSaver, "ALittle.LuaFileSaver")

function ALittle.LuaFileSaver:Save(file_path, content)
	local file = open(file_path, "w")
	if file == nil then
		return false
	end
	file:write(content)
	file:close()
	return true
end

function ALittle.File_GetCurrentPath()
	return currentdir()
end

function ALittle.File_SetCurrentPath(path)
	return chdir(path)
end

function ALittle.File_RenameFile(path, new_path)
	return rename(path, new_path)
end

function ALittle.File_DeleteFile(path)
	return remove(path)
end

function ALittle.File_GetFileAttr(path)
	return attributes(path)
end

function ALittle.File_GetFileAttrByDir(path, file_map)
	do
		if file_map == nil then
			file_map = {}
		end
		for file in dir(path) do
			if file ~= "." and file ~= ".." then
				local file_path = path .. "/" .. file
				local attr = attributes(file_path)
				if attr.mode == "directory" then
					ALittle.File_GetFileAttrByDir(file_path, file_map)
				else
					file_map[file_path] = attr
				end
			end
		end
		return file_map
	end
end

function ALittle.File_GetFileListByDir(path, file_list)
	do
		if file_list == nil then
			file_list = {}
		end
		for file in dir(path) do
			if file ~= "." and file ~= ".." then
				local file_path = path .. "/" .. file
				local attr = attributes(file_path)
				if attr.mode == "directory" then
					ALittle.File_GetFileListByDir(file_path, file_list)
				else
					ALittle.List_Push(file_list, file_path)
				end
			end
		end
		return file_list
	end
end

function ALittle.File_GetFileNameListByDir(path, file_map)
	do
		if file_map == nil then
			file_map = {}
		end
		for file in dir(path) do
			if file ~= "." and file ~= ".." then
				local file_path = path .. "/" .. file
				file_map[file] = attributes(file_path)
			end
		end
		return file_map
	end
end

function ALittle.File_DeleteDir(path)
	return rmdir(path)
end

function ALittle.File_DeleteDeepDir(path, log_path)
	do
		if path == nil or path == "" then
			return
		end
		if ALittle.File_GetFileAttr(path) == nil then
			return
		end
		for file in dir(path) do
			if file ~= "." and file ~= ".." then
				local file_path = path .. "/" .. file
				local attr = attributes(file_path)
				if attr.mode == "directory" then
					ALittle.File_DeleteDeepDir(file_path, log_path)
				else
					ALittle.File_DeleteFile(file_path)
					if log_path then
						ALittle.Log("delete file:", file_path)
					end
				end
			end
		end
		ALittle.File_DeleteDir(path)
	end
end

function ALittle.File_MakeDir(path)
	return mkdir(path)
end

function ALittle.File_MakeDeepDir(path)
	local path_list = ALittle.String_SplitSepList(path, {"/", "\\"})
	local cur_path = ""
	for index, sub_path in ___ipairs(path_list) do
		cur_path = cur_path .. sub_path
		ALittle.File_MakeDir(cur_path)
		cur_path = cur_path .. "/"
	end
end

function ALittle.File_PathEndWithSplit(file_path)
	local len = ALittle.String_Len(file_path)
	if len == 0 then
		return file_path
	end
	local byte = ALittle.String_Byte(file_path, len)
	if byte == 47 or byte == 92 then
		return file_path
	end
	if ALittle.String_Find(file_path, "\\") ~= nil then
		return file_path .. "\\"
	end
	return file_path .. "/"
end

function ALittle.File_GetFileNameByPath(file_path)
	local list = ALittle.String_SplitSepList(file_path, {"/", "\\"})
	local l = ALittle.List_MaxN(list)
	if l <= 0 then
		return file_path
	end
	return list[l]
end

function ALittle.File_GetFilePathByPath(file_path)
	local new_file_path = ALittle.File_GetFileNameByPath(file_path)
	return ALittle.String_Sub(file_path, 1, -ALittle.String_Len(new_file_path) - 2)
end

function ALittle.File_GetFileExtByPath(file_path)
	local list = ALittle.String_Split(file_path, ".")
	local l = ALittle.List_MaxN(list)
	if l <= 0 then
		return file_path
	end
	return list[l]
end

function ALittle.File_ChangeFileExtByPath(file_path, ext)
	local list = ALittle.String_Split(file_path, ".")
	local l = ALittle.List_MaxN(list)
	if l <= 0 then
		return file_path .. "." .. ext
	end
	list[l] = ext
	return ALittle.String_Join(list, ".")
end

function ALittle.File_GetFileExtByPathAndUpper(file_path)
	return ALittle.String_Upper(ALittle.File_GetFileExtByPath(file_path))
end

function ALittle.File_GetJustFileNameByPath(file_path)
	local new_file_path = ALittle.File_GetFileNameByPath(file_path)
	local list = ALittle.String_Split(new_file_path, ".")
	local l = ALittle.List_MaxN(list)
	if l <= 1 then
		return new_file_path
	end
	return list[l - 1]
end

function ALittle.File_ReadJsonFromStdFile(file_path)
	do
		local file = io.open(file_path, "rb")
		if file == nil then
			return nil, file_path .. " load failed"
		end
		local content = file:read("*a")
		file:close()
		local error, new_content = Lua.TCall(json.decode, content)
		if error == nil then
			return new_content, content
		end
		return nil, new_content
	end
end

function ALittle.File_WriteJsonFromStdFile(content, file_path)
	do
		local file = io.open(file_path, "wb")
		if file == nil then
			return false
		end
		file:write(json.encode(content))
		file:close()
		return true
	end
end

function ALittle.File_ReadTextFromStdFile(file_path)
	do
		local file = io.open(file_path, "rb")
		if file == nil then
			return nil
		end
		local content = file:read("*a")
		file:close()
		return content
	end
end

function ALittle.File_WriteTextFromStdFile(content, file_path)
	do
		local file = io.open(file_path, "wb")
		if file == nil then
			return false
		end
		file:write(content)
		file:close()
		return true
	end
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHeapTimer = Lua.Class(nil, "ALittle.IHeapTimer")

function ALittle.IHeapTimer:Add(delay_ms, loop, interval_ms)
	return 0
end

function ALittle.IHeapTimer:Remove(id)
	return false
end

function ALittle.IHeapTimer:Update(ms)
end

function ALittle.IHeapTimer:Poll()
	return 0
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.ISchedule = Lua.Class(nil, "ALittle.ISchedule")

function ALittle.ISchedule:Run()
end

function ALittle.ISchedule:RunInFrame()
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IJsonConfig = Lua.Class(nil, "ALittle.IJsonConfig")

function ALittle.IJsonConfig:GetConfig(key, defaultv)
	return defaultv
end

function ALittle.IJsonConfig:GetBool(key, defaultv)
	return defaultv
end

function ALittle.IJsonConfig:GetInt(key, defaultv)
	return defaultv
end

function ALittle.IJsonConfig:GetDouble(key, defaultv)
	return defaultv
end

function ALittle.IJsonConfig:GetString(key, defaultv)
	return defaultv
end

function ALittle.IJsonConfig:SetConfig(key, value, not_save)
end

function ALittle.IJsonConfig:CoverConfig(msg, save)
end

function ALittle.IJsonConfig:SaveConfig()
end

assert(ALittle.IJsonConfig, " extends class:ALittle.IJsonConfig is nil")
ALittle.JsonConfig = Lua.Class(ALittle.IJsonConfig, "ALittle.JsonConfig")

function ALittle.JsonConfig:Ctor(file_path, print_error)
	___rawset(self, "_file_path", file_path)
	___rawset(self, "_config_map", {})
	local file = self.__class.__element[1]()
	local content = file:Load(self._file_path)
	if content == nil then
		if print_error then
			ALittle.Error("config load failed." .. file_path)
		end
		return
	end
	local error, json_content = Lua.TCall(ALittle.String_JsonDecode, content)
	if error ~= nil then
		ALittle.Log("Json Decode failed." .. file_path .. ", " .. error)
		return
	end
	___rawset(self, "_config_map", json_content)
end

function ALittle.JsonConfig:GetConfig(key, defaultv)
	local value = self._config_map[key]
	if value == nil then
		return defaultv
	end
	return value
end

function ALittle.JsonConfig:GetBool(key, defaultv)
	local value = self:GetConfig(key, defaultv)
	return value ~= nil and value ~= false
end

function ALittle.JsonConfig:GetInt(key, defaultv)
	local value = self:GetConfig(key, defaultv)
	if value == nil then
		value = 0
	end
	return value
end

function ALittle.JsonConfig:GetDouble(key, defaultv)
	local value = self:GetConfig(key, defaultv)
	if value == nil then
		value = 0
	end
	return value
end

function ALittle.JsonConfig:GetString(key, defaultv)
	local value = self:GetConfig(key, defaultv)
	if value == nil then
		value = ""
	end
	return value
end

function ALittle.JsonConfig:SetConfig(key, value, not_save)
	self._config_map[key] = value
	if not not_save then
		self:SaveConfig()
	end
end

function ALittle.JsonConfig:CoverConfig(msg, save)
	for k, v in ___pairs(msg) do
		self._config_map[k] = v
	end
	if not save then
		self:SaveConfig()
	end
end

function ALittle.JsonConfig:SaveConfig()
	local file = self.__class.__element[2]()
	if not file:Save(self._file_path, ALittle.String_JsonEncode(self._config_map)) then
		ALittle.Log("Save Congig Failed.", self._file_path)
	end
end

function ALittle.CreateJsonConfig(file_path, print_error)
	return Lua.Template(ALittle.JsonConfig, "ALittle.JsonConfig<ALittle.LuaFileLoader, ALittle.LuaFileSaver>", ALittle.LuaFileLoader, ALittle.LuaFileSaver)(file_path, print_error)
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.SafeIDCreator = Lua.Class(nil, "ALittle.SafeIDCreator")

function ALittle.SafeIDCreator:Ctor()
	___rawset(self, "_max_id", 0)
	___rawset(self, "_map", {})
end

function ALittle.SafeIDCreator:CreateID()
	local id = nil
	for k, v in ___pairs(self._map) do
		id = k
		break
	end
	if id ~= nil then
		self._map[id] = nil
		return id
	end
	self._max_id = self._max_id + 1
	return self._max_id
end

function ALittle.SafeIDCreator:ReleaseID(id)
	self._map[id] = true
end

function ALittle.SafeIDCreator:PrintStatus()
	local count = 0
	for k, v in ___pairs(self._map) do
		count = count + 1
	end
	ALittle.Log("SafeIDCreator:PrintStatus count:" .. count .. " max_id:" .. self._max_id)
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


function ALittle.String_JsonEncode(object)
	return json.encode(object)
end

function ALittle.String_JsonDecode(text)
	return json.decode(text)
end

function ALittle.String_MD5(text)
	return md5.stringmd5(text)
end

function ALittle.String_Base64Encode(text)
	return base64.encode(text)
end

function ALittle.String_Base64Decode(text)
	return base64.decode(text)
end

function ALittle.String_GetWordCount(text)
	return utf8.wordcount(text)
end

function ALittle.String_GetByteCount(text, word_count)
	return utf8.bytecount(text, 0, word_count)
end

ALittle.StringGenerateID = Lua.Class(nil, "ALittle.StringGenerateID")

function ALittle.StringGenerateID:Ctor()
	___rawset(self, "_string_last_index", 0)
	___rawset(self, "_string_last_time", 0)
end

function ALittle.StringGenerateID:GenID(pre)
	local cur_time = ALittle.Time_GetCurTime()
	if cur_time ~= self._string_last_time then
		self._string_last_time = cur_time
		self._string_last_index = 0
	else
		self._string_last_index = self._string_last_index + 1
	end
	local result = ""
	if pre ~= nil then
		result = pre .. "-"
	end
	result = result .. self._string_last_time .. "-" .. self._string_last_index .. "-" .. ALittle.Math_RandomInt(0, 10000) .. "-" .. ALittle.Math_RandomInt(0, 10000)
	return result
end

local A_StringGenerateID = ALittle.StringGenerateID()
function ALittle.String_GenerateID(pre)
	return A_StringGenerateID:GenID(pre)
end

function ALittle.String_HttpAnalysisValueMap(param, content)
	local value_map = {}
	local param_split_list = ALittle.String_Split(param, "&")
	for index, param_content in ___ipairs(param_split_list) do
		local value_split_list = ALittle.String_Split(param_content, "=")
		if ALittle.List_MaxN(value_split_list) == 2 then
			if ALittle.String_Sub(value_split_list[2], 1, 1) == "\"" and ALittle.String_Sub(value_split_list[2], -1, -1) == "\"" then
				value_map[value_split_list[1]] = ALittle.String_Sub(value_split_list[2], 2, -2)
			else
				local number = ALittle.Math_ToDouble(value_split_list[2])
				if number == nil then
					value_map[value_split_list[1]] = value_split_list[2]
				else
					value_map[value_split_list[1]] = number
				end
			end
		end
	end
	if ALittle.String_Len(content) > 0 then
		local error, value = Lua.TCall(ALittle.String_JsonDecode, content)
		if error == nil then
			for k, v in ___pairs(value) do
				value_map[k] = v
			end
		end
	end
	return value_map
end

function ALittle.String_IsPhoneNumber(number)
	local l = ALittle.String_Len(number)
	local i = 1
	while true do
		if not(i <= l) then break end
		local value = ALittle.String_Byte(number, i)
		if value < 48 then
			return false
		end
		if value > 57 then
			return false
		end
		i = i+(1)
	end
	return true
end

function ALittle.String_IsWordChar(char)
	local len = ALittle.String_Len(char)
	if len ~= 1 then
		return false
	end
	local value = ALittle.String_Byte(char, 1)
	if value >= 48 and value <= 57 then
		return true
	end
	if value == 95 then
		return true
	end
	if value >= 97 and value <= 122 then
		return true
	end
	if value >= 64 and value <= 90 then
		return true
	end
	return false
end

function ALittle.String_SplitUTF8(content)
	local len = ALittle.String_Len(content)
	local index = 1
	local char_list = {}
	local char_count = 0
	while index <= len do
		do
			local byte_count = utf8.bytecount(content, index - 1, 1)
			char_count = char_count + (1)
			char_list[char_count] = string.sub(content, index, index + byte_count - 1)
			index = index + (byte_count)
		end
	end
	return char_list
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function ALittle.CreateKeyWeakMap()
	local mt = {}
	mt["__mode"] = "k"
	local table = {}
	setmetatable(table, mt)
	return table
end

function ALittle.CreateValueWeakMap()
	local mt = {}
	mt["__mode"] = "v"
	local table = {}
	setmetatable(table, mt)
	return table
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpFileReceiverNative = Lua.Class(nil, "ALittle.IHttpFileReceiverNative")

function ALittle.IHttpFileReceiverNative:Close(http_id)
end

function ALittle.IHttpFileReceiverNative:SendString(http_id, content)
end

function ALittle.IHttpFileReceiverNative:StartReceiveFile(http_id, file_path, start_size)
end

assert(ALittle.IHttpFileReceiver, " extends class:ALittle.IHttpFileReceiver is nil")
ALittle.HttpFileReceiverTemplate = Lua.Class(ALittle.IHttpFileReceiver, "ALittle.HttpFileReceiverTemplate")

function ALittle.HttpFileReceiverTemplate:Ctor(http_id, thread)
	___rawset(self, "_http_id", http_id)
	___rawset(self, "_thread", thread)
	___rawset(self, "_received", false)
	___rawset(self, "_interface", self.__class.__element[1]())
end

function ALittle.HttpFileReceiverTemplate:StartReceiveFile(file_path, start_size)
	local ___COROUTINE = coroutine.running()
	if self._received then
		return "StartReceiveFile已经被调用过"
	end
	self._received = true
	self._interface:StartReceiveFile(self._http_id, file_path, start_size)
	return coroutine.yield()
end

function ALittle.HttpFileReceiverTemplate:HandleReceiveResult(reason)
	local result, error = ALittle.Coroutine.Resume(self._thread, reason)
	if not result then
		ALittle.Error(error)
	end
end

function ALittle.HttpFileReceiverTemplate.__getter:received()
	return self._received
end

function ALittle.HttpFileReceiverTemplate:SendString(content)
	self._interface:SendString(self._http_id, content)
end

function ALittle.HttpFileReceiverTemplate:Clsoe()
	self._interface:Close(self._http_id)
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpFileSenderNative = Lua.Class(nil, "ALittle.IHttpFileSenderNative")

function ALittle.IHttpFileSenderNative:GetID()
	return 0
end

function ALittle.IHttpFileSenderNative:SetURL(url, file_path, download, start_size, array_buffer)
end

function ALittle.IHttpFileSenderNative:Start()
end

function ALittle.IHttpFileSenderNative:Stop()
end

function ALittle.IHttpFileSenderNative:GetPath()
	return ""
end

local __HttpFileSenderMap = {}
assert(ALittle.IHttpFileSender, " extends class:ALittle.IHttpFileSender is nil")
ALittle.HttpFileSenderTemplate = Lua.Class(ALittle.IHttpFileSender, "ALittle.HttpFileSenderTemplate")

function ALittle.HttpFileSenderTemplate:Ctor(ip, port, file_path, start_size, callback)
	___rawset(self, "_interface", self.__class.__element[1]())
	___rawset(self, "_ip", ip)
	___rawset(self, "_port", port)
	if self._port == nil then
		___rawset(self, "_port", 80)
	end
	___rawset(self, "_file_path", file_path)
	___rawset(self, "_start_size", start_size)
	___rawset(self, "_callback", callback)
	___rawset(self, "_cur_size", 0)
	___rawset(self, "_total_size", 0)
end

function ALittle.HttpFileSenderTemplate:SendDownloadRPC(thread, method, content, array_buffer)
	self._thread = thread
	__HttpFileSenderMap[self._interface:GetID()] = self
	if self._start_size == nil then
		self._start_size = 0
	end
	local url = self._ip .. ":" .. self._port .. "/" .. method
	if ALittle.String_Find(self._ip, "http://") ~= 1 and ALittle.String_Find(self._ip, "https://") ~= 1 then
		if self._port == 443 then
			url = "https://" .. url
		else
			url = "http://" .. url
		end
	end
	self._interface:SetURL(self:HttpUrlAppendParamMap(url, content), self._file_path, true, self._start_size, array_buffer)
	self._interface:Start()
end

function ALittle.HttpFileSenderTemplate:SendUploadRPC(thread, method, content, array_buffer)
	self._thread = thread
	__HttpFileSenderMap[self._interface:GetID()] = self
	if self._start_size == nil then
		self._start_size = 0
	end
	local url = "http://" .. self._ip .. ":" .. self._port .. "/" .. method
	self._interface:SetURL(self:HttpUrlAppendParamMap(url, content), self._file_path, false, self._start_size, array_buffer)
	self._interface:Start()
end

function ALittle.HttpFileSenderTemplate:Stop()
	self._interface:Stop()
end

function ALittle.HttpFileSenderTemplate:GetFilePath()
	return self._file_path
end

function ALittle.HttpFileSenderTemplate:GetTotalSize()
	return self._total_size
end

function ALittle.HttpFileSenderTemplate:GetCurSize()
	return self._cur_size
end

function ALittle.HttpFileSenderTemplate:HandleSucceed()
	__HttpFileSenderMap[self._interface:GetID()] = nil
	local result, reason = ALittle.Coroutine.Resume(self._thread, nil)
	if result ~= true then
		ALittle.Error(reason)
	end
end

function ALittle.HttpFileSenderTemplate:HandleFailed(reason)
	__HttpFileSenderMap[self._interface:GetID()] = nil
	local result, error = ALittle.Coroutine.Resume(self._thread, reason)
	if result ~= true then
		ALittle.Error(error)
	end
end

function ALittle.HttpFileSenderTemplate:HandleProcess(cur_size, total_size)
	self._cur_size = cur_size
	self._total_size = total_size
	if self._callback ~= nil then
		self._callback(self)
	end
end

function ALittle.HttpFileSenderTemplate:HttpUrlAppendParamMap(url, param)
	if param == nil then
		return url
	end
	local list = {}
	local count = 0
	for key, value in ___pairs(param) do
		count = count + 1
		list[count] = key .. "=" .. ALittle.String_ToString(value)
	end
	if ALittle.String_Find(url, "?") == nil then
		url = url .. "?"
	else
		url = url .. "&"
	end
	return url .. ALittle.String_Join(list, "&")
end

function ALittle.__ALITTLEAPI_HttpFileSucceed(id)
	local client = __HttpFileSenderMap[id]
	if client == nil then
		return
	end
	client:HandleSucceed()
end

function ALittle.__ALITTLEAPI_HttpFileFailed(id, reason)
	local client = __HttpFileSenderMap[id]
	if client == nil then
		return
	end
	client:HandleFailed(reason)
end

function ALittle.__ALITTLEAPI_HttpFileProcess(id, cur_size, total_size)
	local client = __HttpFileSenderMap[id]
	if client == nil then
		return
	end
	client:HandleProcess(cur_size, total_size)
end

function ALittle.DownloadFile(ip, port, method, file_path, array_buffer)
	local ___COROUTINE = coroutine.running()
	local sender
	sender = Lua.Template(ALittle.HttpFileSenderTemplate, "ALittle.HttpFileSenderTemplate<Lua.LuaHttpFileInterface>", Lua.LuaHttpFileInterface)(ip, port, file_path, 0)
	return ALittle.IHttpFileSender.InvokeDownload(method, sender, nil, array_buffer)
end

function ALittle.UploadFile(ip, port, method, file_path, array_buffer)
	local ___COROUTINE = coroutine.running()
	local sender
	sender = Lua.Template(ALittle.HttpFileSenderTemplate, "ALittle.HttpFileSenderTemplate<Lua.LuaHttpFileInterface>", Lua.LuaHttpFileInterface)(ip, port, file_path, 0)
	local error = ALittle.IHttpFileSender.InvokeUpload(method, sender, nil, array_buffer)
	return error
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpReceiverNative = Lua.Class(nil, "ALittle.IHttpReceiverNative")

function ALittle.IHttpReceiverNative:Close(http_id)
end

function ALittle.IHttpReceiverNative:SendString(http_id, content)
end

function ALittle.IHttpReceiverNative:SendFile(http_id, file_path, start_size)
end

assert(ALittle.IHttpReceiver, " extends class:ALittle.IHttpReceiver is nil")
ALittle.HttpReceiverTemplate = Lua.Class(ALittle.IHttpReceiver, "ALittle.HttpReceiverTemplate")

function ALittle.HttpReceiverTemplate:Ctor(http_id)
	___rawset(self, "_http_id", http_id)
	___rawset(self, "_interface", self.__class.__element[1]())
end

function ALittle.HttpReceiverTemplate:Close()
	self._interface:Close(self._http_id)
end

function ALittle.HttpReceiverTemplate:SendString(content)
	self._interface:SendString(self._http_id, content)
end

function ALittle.HttpReceiverTemplate:SendFile(file_path, start_size)
	self._interface:SendFile(self._http_id, file_path, start_size)
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpSenderNative = Lua.Class(nil, "ALittle.IHttpSenderNative")

function ALittle.IHttpSenderNative:GetID()
	return 0
end

function ALittle.IHttpSenderNative:SetURL(url, content)
end

function ALittle.IHttpSenderNative:Start()
end

function ALittle.IHttpSenderNative:Stop()
end

function ALittle.IHttpSenderNative:GetResponse()
	return nil
end

local __HttpSenderMap = {}
assert(ALittle.IHttpSender, " extends class:ALittle.IHttpSender is nil")
ALittle.HttpSenderTemplate = Lua.Class(ALittle.IHttpSender, "ALittle.HttpSenderTemplate")

function ALittle.HttpSenderTemplate:Ctor(ip, port)
	___rawset(self, "_interface", self.__class.__element[1]())
	___rawset(self, "_ip", ip)
	___rawset(self, "_port", port)
	if self._port == nil then
		___rawset(self, "_port", 80)
	end
end

function ALittle.HttpSenderTemplate:SendRPC(thread, method, content)
	self._thread = thread
	__HttpSenderMap[self._interface:GetID()] = self
	local url = self._ip .. ":" .. self._port .. "/" .. method
	if ALittle.String_Find(self._ip, "http://") ~= 1 and ALittle.String_Find(self._ip, "https://") ~= 1 then
		if self._port == 443 then
			url = "https://" .. url
		else
			url = "http://" .. url
		end
	end
	if content == nil then
		self._interface:SetURL(url, nil)
	else
		self._interface:SetURL(url, ALittle.String_JsonEncode(content))
	end
	self._interface:Start()
end

function ALittle.HttpSenderTemplate:Stop()
	self._interface:Stop()
end

function ALittle.HttpSenderTemplate:HandleSucceed()
	__HttpSenderMap[self._interface:GetID()] = nil
	local error, param = Lua.TCall(ALittle.String_JsonDecode, self._interface:GetResponse())
	if error ~= nil then
		local result, reason = ALittle.Coroutine.Resume(self._thread, error, nil)
		if result ~= true then
			ALittle.Error(reason)
		end
		return
	end
	if param["error"] ~= nil then
		local result, reason = ALittle.Coroutine.Resume(self._thread, param["error"], nil)
		if result ~= true then
			ALittle.Error(reason)
		end
		return
	end
	local result, reason = ALittle.Coroutine.Resume(self._thread, nil, param)
	if result ~= true then
		ALittle.Error(reason)
	end
end

function ALittle.HttpSenderTemplate:HandleFailed(reason)
	__HttpSenderMap[self._interface:GetID()] = nil
	local result, error = ALittle.Coroutine.Resume(self._thread, reason, nil)
	if result ~= true then
		ALittle.Error(error)
	end
end

function ALittle.__ALITTLEAPI_HttpClientSucceed(id)
	local client = __HttpSenderMap[id]
	if client == nil then
		return
	end
	client:HandleSucceed()
end

function ALittle.__ALITTLEAPI_HttpClientFailed(id, reason)
	local client = __HttpSenderMap[id]
	if client == nil then
		return
	end
	client:HandleFailed(reason)
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-930447138, "ALittle.Thread", {
name = "ALittle.Thread", ns_name = "ALittle", rl_name = "Thread", hash_code = -930447138,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(361433949, "ALittle.MsgRPCInfo", {
name = "ALittle.MsgRPCInfo", ns_name = "ALittle", rl_name = "MsgRPCInfo", hash_code = 361433949,
name_list = {"rpc_id","thread"},
type_list = {"int","ALittle.Thread"},
option_map = {}
})

ALittle.IMsgCommonNative = Lua.Class(nil, "ALittle.IMsgCommonNative")

function ALittle.IMsgCommonNative:SetID(id)
end

function ALittle.IMsgCommonNative:GetID()
	return 0
end

function ALittle.IMsgCommonNative:Connect(ip, port)
end

function ALittle.IMsgCommonNative:IsConnected()
	return false
end

function ALittle.IMsgCommonNative:SendFactory(factory)
end

function ALittle.IMsgCommonNative:Close()
end

assert(ALittle.IMsgCommon, " extends class:ALittle.IMsgCommon is nil")
ALittle.IMsgCommonTemplate = Lua.Class(ALittle.IMsgCommon, "ALittle.IMsgCommonTemplate")

function ALittle.IMsgCommonTemplate:Ctor()
	___rawset(self, "_last_recv_time", 0)
	___rawset(self, "_id_creator", ALittle.SafeIDCreator())
	___rawset(self, "_id_map_rpc", {})
end

function ALittle.IMsgCommonTemplate:GetID()
	return self._interface:GetID()
end

function ALittle.IMsgCommonTemplate:Connect(ip, port)
	local ___COROUTINE = coroutine.running()
	return "not impl"
end

function ALittle.IMsgCommonTemplate:IsConnected()
	return self._interface:IsConnected()
end

function ALittle.IMsgCommonTemplate:MessageRead(factory, msg_id)
	local invoke = ALittle.CreateProtocolInvokeInfo(msg_id)
	local object, size = ALittle.PS_ReadMessageForReceive(factory, invoke, nil, factory:GetDataSize())
	return object
end

function ALittle.IMsgCommonTemplate:MessageWrite(msg_id, msg_body)
	local invoke = ALittle.CreateProtocolInvokeInfo(msg_id)
	self._write_factory:ResetOffset()
	ALittle.PS_WriteMessageForSend(self._write_factory, invoke, nil, msg_body)
	self._write_factory:SetID(msg_id)
end

function ALittle.IMsgCommonTemplate:HandleMessage(id, rpc_id, factory)
	if id == 0 then
		self._last_recv_time = ALittle.Time_GetCurTime()
		return
	end
	if rpc_id == 0 then
		local callback = ALittle.FindMsgCallback(id)
		if callback == nil then
			local name = "unknow"
			local rflt = ALittle.FindStructById(id)
			if rflt ~= nil then
				name = rflt.name
			end
			ALittle.Log("MsgSystem.HandleMessage can't find callback by id:" .. id .. ", name:" .. name)
			return
		end
		local msg = self:MessageRead(factory, id)
		if msg == nil then
			local name = "unknow"
			local rflt = ALittle.FindStructById(id)
			if rflt ~= nil then
				name = rflt.name
			end
			ALittle.Log("MsgSystem.HandleMessage MessageRead failed by id:" .. id .. ", name:" .. name)
			return
		end
		callback(self, msg)
		return
	end
	if rpc_id > 0 then
		self:HandleRPCRequest(id, rpc_id, factory)
		return
	end
	rpc_id = -rpc_id
	self._id_creator:ReleaseID(rpc_id)
	local info = self._id_map_rpc[rpc_id]
	if info == nil then
		ALittle.Log("MsgSystem.HandleMessage can't find rpc info by id:" .. id)
		return
	end
	self._id_map_rpc[rpc_id] = nil
	if id == 1 then
		local result, reason = ALittle.Coroutine.Resume(info.thread, factory:ReadString(), nil)
		if result ~= true then
			ALittle.Error(reason)
		end
		return
	end
	local msg = self:MessageRead(factory, id)
	if msg == nil then
		local result, reason = ALittle.Coroutine.Resume(info.thread, "MsgSystem.HandleMessage MessageRead failed by id:" .. id, nil)
		if result ~= true then
			ALittle.Error(reason)
		end
		ALittle.Log("MsgSystem.HandleMessage MessageRead failed by id:" .. id)
		return
	end
	local result, reason = ALittle.Coroutine.Resume(info.thread, nil, msg)
	if result ~= true then
		ALittle.Error(reason)
	end
end

function ALittle.IMsgCommonTemplate:SendMsg(T, msg)
	local info = T
	self:Send(info.hash_code, msg, 0)
end

function ALittle.IMsgCommonTemplate:Send(msg_id, msg_body, rpc_id)
	if not self:IsConnected() then
		return
	end
	self._write_factory:SetRpcID(rpc_id)
	self:MessageWrite(msg_id, msg_body)
	self._interface:SendFactory(self._write_factory)
end

function ALittle.IMsgCommonTemplate:SendRpcError(rpc_id, reason)
	if not self:IsConnected() then
		return
	end
	self._write_factory:ResetOffset()
	self._write_factory:SetID(1)
	self._write_factory:SetRpcID(-rpc_id)
	self._write_factory:WriteString(reason)
	self._interface:SendFactory(self._write_factory)
end

function ALittle.IMsgCommonTemplate:SendRPC(thread, msg_id, msg_body)
	local rpc_id = self._id_creator:CreateID()
	self._write_factory:SetRpcID(rpc_id)
	self:MessageWrite(msg_id, msg_body)
	self._interface:SendFactory(self._write_factory)
	local info = {}
	info.thread = thread
	info.rpc_id = rpc_id
	self._id_map_rpc[rpc_id] = info
end

function ALittle.IMsgCommonTemplate:HandleRPCRequest(id, rpc_id, factory)
	local callback, return_id = ALittle.FindMsgRpcCallback(id)
	if callback == nil then
		self:SendRpcError(rpc_id, "没有注册消息RPC回调函数")
		ALittle.Log("MsgSystem.HandleMessage can't find callback by id:" .. id)
		return
	end
	local msg = self:MessageRead(factory, id)
	if msg == nil then
		self:SendRpcError(rpc_id, "MsgSystem.HandleMessage MessageRead failed by id:" .. id)
		ALittle.Log("MsgSystem.HandleMessage MessageRead failed by id:" .. id)
		return
	end
	local error, return_body = Lua.TCall(callback, self, msg)
	if error ~= nil then
		self:SendRpcError(rpc_id, error)
		ALittle.Log("MsgSystem.HandleMessage callback invoke failed! by id:" .. id .. ", reason:" .. error)
		return
	end
	if return_body == nil then
		self:SendRpcError(rpc_id, "MsgSystem.HandleMessage callback have not return! by id:" .. id)
		ALittle.Log("MsgSystem.HandleMessage callback have not return! by id:" .. id)
		return
	end
	self:Send(return_id, return_body, -rpc_id)
end
ALittle.IMsgCommonTemplate.HandleRPCRequest = Lua.CoWrap(ALittle.IMsgCommonTemplate.HandleRPCRequest)

function ALittle.IMsgCommonTemplate:ClearRPC(reason)
	local tmp = {}
	for rpc_id, info in ___pairs(self._id_map_rpc) do
		self._id_creator:ReleaseID(rpc_id)
		tmp[rpc_id] = info
	end
	self._id_map_rpc = {}
	for rpc_id, info in ___pairs(tmp) do
		local result, error = ALittle.Coroutine.Resume(info.thread, reason, nil)
		if result ~= true then
			ALittle.Error(error)
		end
	end
end

function ALittle.IMsgCommonTemplate:Close(reason)
	if reason == nil then
		reason = "主动关闭连接"
	end
	self:ClearRPC(reason)
	self._interface:Close()
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.IMsgCommonTemplate, " extends class:ALittle.IMsgCommonTemplate is nil")
ALittle.MsgReceiverTemplate = Lua.Class(ALittle.IMsgCommonTemplate, "ALittle.MsgReceiverTemplate")

function ALittle.MsgReceiverTemplate:Ctor(client_id, remote_ip, remote_port)
	___rawset(self, "_interface", self.__class.__element[1]())
	self._interface:SetID(client_id)
	___rawset(self, "_write_factory", self.__class.__element[2]())
	___rawset(self, "_is_connected", true)
	___rawset(self, "_client_id", client_id)
	___rawset(self, "_remote_ip", remote_ip)
	___rawset(self, "_remote_port", remote_port)
	___rawset(self, "_client_account_id", 0)
	___rawset(self, "_client_logining", false)
	___rawset(self, "_web_account_id", "")
	___rawset(self, "_web_is_logining", false)
end

function ALittle.MsgReceiverTemplate.__getter:remote_ip()
	return self._remote_ip
end

function ALittle.MsgReceiverTemplate.__getter:remote_port()
	return self._remote_port
end

function ALittle.MsgReceiverTemplate:IsConnected()
	return self._is_connected
end

function ALittle.MsgReceiverTemplate:HandleConnected()
	self._is_connected = true
end

function ALittle.MsgReceiverTemplate:HandleDisconnected()
	self._is_connected = false
	self:ClearRPC("连接断开了")
end

function ALittle.MsgReceiverTemplate:Close(reason)
	if not self._is_connected then
		return
	end
	self._is_connected = false
	if reason == nil then
		reason = "主动关闭连接"
	end
	self:ClearRPC(reason)
	self._interface:Close()
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __MsgSenderMap = {}
assert(ALittle.IMsgCommonTemplate, " extends class:ALittle.IMsgCommonTemplate is nil")
ALittle.MsgSenderTemplate = Lua.Class(ALittle.IMsgCommonTemplate, "ALittle.MsgSenderTemplate")

function ALittle.MsgSenderTemplate:Ctor(heartbeat, check_heartbeat, loop_system, callback)
	___rawset(self, "_interface", self.__class.__element[1]())
	___rawset(self, "_write_factory", self.__class.__element[2]())
	___rawset(self, "_loop_system", loop_system)
	___rawset(self, "_heartbeat", heartbeat)
	___rawset(self, "_heartbeat_loop", nil)
	___rawset(self, "_check_heartbeat", nil)
	if self._heartbeat ~= nil then
		___rawset(self, "_check_heartbeat", check_heartbeat)
	end
	___rawset(self, "_last_recv_time", 0)
	___rawset(self, "_callback", callback)
end

function ALittle.MsgSenderTemplate:Connect(ip, port)
	local ___COROUTINE = coroutine.running()
	if ip == nil then
		ip = ""
	end
	if port == nil then
		port = 0
	end
	if ___COROUTINE == nil then
		return "当前不是协程"
	end
	self._co = ___COROUTINE
	__MsgSenderMap[self._interface:GetID()] = self
	self._ip = ip
	self._port = port
	self._interface:Connect(ip, port)
	return coroutine.yield()
end

function ALittle.MsgSenderTemplate:HandleConnectSucceed()
	self._last_recv_time = 0
	self:SendHeartbeat()
	self:StartHeartbeat()
	local result, reason = ALittle.Coroutine.Resume(self._co, nil)
	if result ~= true then
		ALittle.Error(reason)
	end
end

function ALittle.MsgSenderTemplate:HandleDisconnect()
	self:StopHeartbeat()
	__MsgSenderMap[self._interface:GetID()] = nil
	self:ClearRPC("连接断开了")
	if self._callback ~= nil then
		self._callback()
	end
end

function ALittle.MsgSenderTemplate:HandleConnectFailed(error)
	__MsgSenderMap[self._interface:GetID()] = nil
	if error == nil then
		error = self._ip .. ":" .. self._port .. "连接失败"
	end
	local result, reason = ALittle.Coroutine.Resume(self._co, error)
	if result ~= true then
		ALittle.Error(reason)
	end
end

function ALittle.MsgSenderTemplate:Close(reason)
	self:StopHeartbeat()
	self._interface:Close()
	if reason == nil then
		reason = "主动关闭连接"
	end
	self:ClearRPC(reason)
	__MsgSenderMap[self._interface:GetID()] = nil
end

function ALittle.MsgSenderTemplate:SendHeartbeat(max_ms)
	if self._interface:IsConnected() == false then
		return
	end
	self._write_factory:ResetOffset()
	self._write_factory:SetID(0)
	self._write_factory:SetRpcID(0)
	self._interface:SendFactory(self._write_factory)
	if self._check_heartbeat then
		local send_time = ALittle.Time_GetCurTime()
		local default_delta = self._heartbeat / 2
		local delta_time = max_ms
		if delta_time == nil then
			delta_time = default_delta
		end
		if delta_time > default_delta then
			delta_time = default_delta
		end
		self._loop_system:AddTimer(ALittle.Math_Floor(delta_time) * 1000, Lua.Bind(self.CheckHeartbeat, self, send_time, ALittle.Math_Floor(delta_time)))
	end
end

function ALittle.MsgSenderTemplate:CheckHeartbeat(send_time, delta_time)
	local invoke_time = ALittle.Time_GetCurTime()
	local interval_time = invoke_time - send_time
	if interval_time > delta_time + 2 then
		return
	end
	if self._last_recv_time > 0 and send_time - self._last_recv_time > delta_time then
		if self._interface:IsConnected() == false then
			return
		end
		self:Close("心跳检测失败，主动断开连接")
		if self._callback ~= nil then
			self._callback()
		end
	end
end

function ALittle.MsgSenderTemplate:StartHeartbeat()
	if self._heartbeat == nil then
		return
	end
	if self._heartbeat <= 0 then
		return
	end
	if self._heartbeat_loop ~= nil then
		return
	end
	self._heartbeat_loop = self._loop_system:AddTimer(1, Lua.Bind(self.SendHeartbeat, self, nil), -1, self._heartbeat * 1000)
end

function ALittle.MsgSenderTemplate:StopHeartbeat()
	if self._heartbeat_loop == nil then
		return
	end
	self._last_recv_time = 0
	self._loop_system:RemoveTimer(self._heartbeat_loop)
	self._heartbeat_loop = nil
end

function ALittle.__ALITTLEAPI_ConnectSucceed(id)
	local client = __MsgSenderMap[id]
	if client == nil then
		return
	end
	client:HandleConnectSucceed()
end

function ALittle.__ALITTLEAPI_Disconnect(id)
	local client = __MsgSenderMap[id]
	if client == nil then
		return
	end
	client:HandleDisconnect()
end

function ALittle.__ALITTLEAPI_ConnectFailed(id)
	local client = __MsgSenderMap[id]
	if client == nil then
		return
	end
	client:HandleConnectFailed(nil)
end

function ALittle.__ALITTLEAPI_Message(id, msg_id, rpc_id, factory)
	local client = __MsgSenderMap[id]
	if client == nil then
		return
	end
	client:HandleMessage(msg_id, rpc_id, factory)
end

end
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.IMsgCommonTemplate, " extends class:ALittle.IMsgCommonTemplate is nil")
ALittle.MsgSessionTemplate = Lua.Class(ALittle.IMsgCommonTemplate, "ALittle.MsgSessionTemplate")

function ALittle.MsgSessionTemplate:Ctor(connect_key, route_type, route_num)
	___rawset(self, "_interface", self.__class.__element[1]())
	self._interface:SetID(connect_key)
	___rawset(self, "_write_factory", self.__class.__element[2]())
	___rawset(self, "_is_connected", true)
	___rawset(self, "_connect_key", connect_key)
	___rawset(self, "_route_type", route_type)
	___rawset(self, "_route_num", route_num)
end

function ALittle.MsgSessionTemplate.__getter:route_type()
	return self._route_type
end

function ALittle.MsgSessionTemplate.__getter:route_num()
	return self._route_num
end

function ALittle.MsgSessionTemplate:IsConnected()
	return self._is_connected
end

function ALittle.MsgSessionTemplate:HandleConnected()
	self._is_connected = true
end

function ALittle.MsgSessionTemplate:HandleDisconnected()
	self._is_connected = false
	self:ClearRPC("连接断开了")
end

function ALittle.MsgSessionTemplate:Close(reason)
	if not self._is_connected then
		return
	end
	self._is_connected = false
	if reason == nil then
		reason = "主动关闭连接"
	end
	self:ClearRPC(reason)
	self._interface:Close()
end

end
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
-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


local GetSchedule
GetSchedule = function()
	return A_LuaSchedule
end

_G.A_Schedule = GetSchedule()
end