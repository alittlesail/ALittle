-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local g_ABnf = nil
local g_ABnfFactory = nil
assert(AUIPlugin.AUICodeLanguage, " extends class:AUIPlugin.AUICodeLanguage is nil")
AUICodeABnf = Lua.Class(AUIPlugin.AUICodeLanguage, "AUIPlugin.AUICodeABnf")

function AUICodeABnf:Ctor(full_path)
	if g_ABnf == nil then
		g_ABnfFactory = abnf.create_abnf_factory()
		g_ABnf = alanguage.create_abnf()
		local abnf_path = g_ModuleBasePath .. "/Other/ABnf/ABnf.abnf"
		local buffer = ALittle.File_ReadTextFromFile(abnf_path)
		if buffer ~= nil then
			local error = alanguage.abnf_load(g_ABnf, buffer, g_ABnfFactory)
			if error ~= nil then
				ALittle.Log("abnf load failed! " .. error)
			end
		else
			ALittle.Log("abnf file read failed! " .. abnf_path)
		end
	end
	___rawset(self, "_abnf_file", abnf.create_abnf_file(full_path, g_ABnf, ""))
end

function AUICodeABnf:SetText(content)
	self._version = self._version + (1)
	alanguage.abnffile_settext(self._abnf_file, content)
end

function AUICodeABnf:InsertText(content, it_line, it_char)
	self._version = self._version + (1)
	alanguage.abnffile_inserttext(self._abnf_file, content, it_line, it_char)
end

function AUICodeABnf:DeleteText(it_line_start, it_char_start, it_line_end, it_char_end)
	self._version = self._version + (1)
	alanguage.abnffile_deletetext(self._abnf_file, it_line_start, it_char_start, it_line_end, it_char_end)
end

function AUICodeABnf:QueryColor(line)
	return alanguage.abnffile_querycolor(self._abnf_file, self._version, line)
end

