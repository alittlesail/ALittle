-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(152169657, "AUIPlugin.ABnfColor", {
name = "AUIPlugin.ABnfColor", ns_name = "AUIPlugin", rl_name = "ABnfColor", hash_code = 152169657,
name_list = {"red","green","blue","alpha"},
type_list = {"double","double","double","double"},
option_map = {}
})

AUICodeLanguage = Lua.Class(nil, "AUIPlugin.AUICodeLanguage")

function AUICodeLanguage:Ctor()
	___rawset(self, "_version", 1)
end

function AUICodeLanguage.__getter:version()
	return self._version
end

function AUICodeLanguage:SetText(content)
end

function AUICodeLanguage:InsertText(content, it_line, it_char)
end

function AUICodeLanguage:DeleteText(it_line_start, it_char_start, it_line_end, it_char_end)
end

function AUICodeLanguage:QueryColor(line)
	return {}
end

function AUICodeLanguage:QueryColorValue(tag)
	return nil
end

