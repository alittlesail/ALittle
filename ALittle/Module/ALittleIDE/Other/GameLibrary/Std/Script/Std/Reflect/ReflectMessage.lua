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