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