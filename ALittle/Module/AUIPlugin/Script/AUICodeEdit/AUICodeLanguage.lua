-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1378427401, "AUIPlugin.AUICodeQueryColor", {
name = "AUIPlugin.AUICodeQueryColor", ns_name = "AUIPlugin", rl_name = "AUICodeQueryColor", hash_code = 1378427401,
name_list = {"start","count","red","green","blue","alpha"},
type_list = {"int","int","double","double","double","double"},
option_map = {}
})

AUICodeLanguage = Lua.Class(nil, "AUIPlugin.AUICodeLanguage")

function AUICodeLanguage:SetText(content)
end

function AUICodeLanguage:InsertText(content, it_line, it_char)
end

function AUICodeLanguage:DeleteText(it_line_start, it_char_start, it_line_end, it_char_end)
end

function AUICodeLanguage:QueryColor(line)
	return {}
end

