-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local g_ABnf = nil
local g_ABnfFactory = nil
local g_ABnfColor = nil
ABnfColorType = {
	ABnfKeyWord = 1,
	ABnfId = 2,
	ABnfComment = 3,
	ABnfKey = 4,
	ABnfString = 5,
	ABnfRegex = 6,
}

assert(AUIPlugin.AUICodeLanguage, " extends class:AUIPlugin.AUICodeLanguage is nil")
AUICodeABnf = Lua.Class(AUIPlugin.AUICodeLanguage, "AUIPlugin.AUICodeABnf")

function AUICodeABnf:Ctor(full_path)
	if g_ABnfFactory == nil then
		g_ABnfFactory = abnf.create_abnf_factory()
	end
	if g_ABnf == nil then
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
	if g_ABnfColor == nil then
		g_ABnfColor = {}
		local color
		do
			color = {}
			color.red = 255 / 255
			color.green = 198 / 255
			color.blue = 109 / 255
			g_ABnfColor[ABnfColorType.ABnfKeyWord] = color
		end
		do
			color = {}
			color.red = 204 / 255
			color.green = 120 / 255
			color.blue = 50 / 255
			g_ABnfColor[ABnfColorType.ABnfId] = color
		end
		do
			color = {}
			color.red = 128 / 255
			color.green = 128 / 255
			color.blue = 128 / 255
			g_ABnfColor[ABnfColorType.ABnfComment] = color
		end
		do
			color = {}
			color.red = 204 / 255
			color.green = 120 / 255
			color.blue = 50 / 255
			g_ABnfColor[ABnfColorType.ABnfKey] = color
		end
		do
			color = {}
			color.red = 85 / 255
			color.green = 134 / 255
			color.blue = 74 / 255
			g_ABnfColor[ABnfColorType.ABnfString] = color
		end
		do
			color = {}
			color.red = 152 / 255
			color.green = 118 / 255
			color.blue = 170 / 255
			g_ABnfColor[ABnfColorType.ABnfRegex] = color
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

function AUICodeABnf:QueryColorValue(tag)
	return g_ABnfColor[tag]
end

