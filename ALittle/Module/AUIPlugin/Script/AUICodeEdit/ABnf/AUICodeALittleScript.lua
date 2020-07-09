-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local g_ALittleScriptColor = nil
ALittleScriptColorType = {
	COMMENT = 1,
	DEFINE_NAME = 2,
	VAR_NAME = 3,
	CUSTOM_NAME = 4,
	CTRL_KEYWORD = 5,
	KEYWORD = 6,
	METHOD_NAME = 7,
	DEFAULT = 8,
	TEXT = 9,
}

assert(AUIPlugin.AUICodeLanguage, " extends class:AUIPlugin.AUICodeLanguage is nil")
AUICodeALittleScript = Lua.Class(AUIPlugin.AUICodeLanguage, "AUIPlugin.AUICodeALittleScript")

function AUICodeALittleScript:Ctor(project, full_path)
	if g_ALittleScriptColor == nil then
		g_ALittleScriptColor = {}
		local color
		do
			color = {}
			color.red = 87 / 255
			color.green = 166 / 255
			color.blue = 74 / 255
			g_ALittleScriptColor[ALittleScriptColorType.COMMENT] = color
		end
		do
			color = {}
			color.red = 78 / 255
			color.green = 201 / 255
			color.blue = 176 / 255
			g_ALittleScriptColor[ALittleScriptColorType.DEFINE_NAME] = color
		end
		do
			color = {}
			color.red = 218 / 255
			color.green = 218 / 255
			color.blue = 218 / 255
			g_ALittleScriptColor[ALittleScriptColorType.VAR_NAME] = color
		end
		do
			color = {}
			color.red = 156 / 255
			color.green = 220 / 255
			color.blue = 254 / 255
			g_ALittleScriptColor[ALittleScriptColorType.CUSTOM_NAME] = color
		end
		do
			color = {}
			color.red = 216 / 255
			color.green = 160 / 255
			color.blue = 223 / 255
			g_ALittleScriptColor[ALittleScriptColorType.CTRL_KEYWORD] = color
		end
		do
			color = {}
			color.red = 86 / 255
			color.green = 156 / 255
			color.blue = 214 / 255
			g_ALittleScriptColor[ALittleScriptColorType.KEYWORD] = color
		end
		do
			color = {}
			color.red = 220 / 255
			color.green = 220 / 255
			color.blue = 170 / 255
			g_ALittleScriptColor[ALittleScriptColorType.METHOD_NAME] = color
		end
		do
			color = {}
			color.red = 169 / 255
			color.green = 183 / 255
			color.blue = 198 / 255
			g_ALittleScriptColor[ALittleScriptColorType.DEFAULT] = color
		end
		do
			color = {}
			color.red = 214 / 255
			color.green = 157 / 255
			color.blue = 133 / 255
			g_ALittleScriptColor[ALittleScriptColorType.TEXT] = color
		end
	end
	___rawset(self, "_abnf_file", alittlescript.create_alittlescript_file(project.project, full_path, ""))
end

function AUICodeALittleScript:QueryColorValue(tag)
	return g_ALittleScriptColor[tag]
end

function AUICodeALittleScript:SetTargetLanguage(target_languaeg)
	alittlescript.alittlescriptproject_settargetlanguage(self._project.project, target_languaeg)
end
