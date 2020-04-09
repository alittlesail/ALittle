
module("ALittle", package.seeall)

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

function String_Trim(text)
	return string.gsub(text, "^%s*(.-)%s*$", "%1")
end

