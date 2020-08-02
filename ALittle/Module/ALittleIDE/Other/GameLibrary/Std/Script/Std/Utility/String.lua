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