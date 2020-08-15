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