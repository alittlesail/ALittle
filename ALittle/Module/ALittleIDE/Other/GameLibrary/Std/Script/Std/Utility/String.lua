-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


function String_JsonEncode(object)
	return json.encode(object)
end

function String_JsonDecode(text)
	return json.decode(text)
end

function String_MD5(text)
	return md5.stringmd5(text)
end

function String_Base64Encode(text)
	return base64.encode(text)
end

function String_Base64Decode(text)
	return base64.decode(text)
end

function String_GetWordCount(text)
	return utf8.wordcount(text)
end

function String_GetByteCount(text, word_count)
	return utf8.bytecount(text, word_count)
end

StringGenerateID = Lua.Class(nil, "ALittle.StringGenerateID")

function StringGenerateID:Ctor()
	___rawset(self, "_string_last_index", 0)
	___rawset(self, "_string_last_time", 0)
end

function StringGenerateID:GenID(pre)
	local cur_time = Time_GetCurTime()
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
	result = result .. self._string_last_time .. "-" .. self._string_last_index .. "-" .. Math_RandomInt(0, 10000) .. "-" .. Math_RandomInt(0, 10000)
	return result
end

local A_StringGenerateID = StringGenerateID()
function String_GenerateID(pre)
	return A_StringGenerateID:GenID(pre)
end

function String_HttpAnalysisValueMap(param, content)
	local value_map = {}
	local param_split_list = String_Split(param, "&")
	for index, param_content in ___ipairs(param_split_list) do
		local value_split_list = String_Split(param_content, "=")
		if List_MaxN(value_split_list) == 2 then
			if String_Sub(value_split_list[2], 1, 1) == "\"" and String_Sub(value_split_list[2], -1, -1) == "\"" then
				value_map[value_split_list[1]] = String_Sub(value_split_list[2], 2, -2)
			else
				local number = Math_ToDouble(value_split_list[2])
				if number == nil then
					value_map[value_split_list[1]] = value_split_list[2]
				else
					value_map[value_split_list[1]] = number
				end
			end
		end
	end
	if String_Len(content) > 0 then
		local error, value = Lua.TCall(String_JsonDecode, content)
		if error == nil then
			for k, v in ___pairs(value) do
				value_map[k] = v
			end
		end
	end
	return value_map
end

function String_IsPhoneNumber(number)
	local l = String_Len(number)
	local i = 1
	while true do
		if not(i <= l) then break end
		local value = String_Byte(number, i)
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

