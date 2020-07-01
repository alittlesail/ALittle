-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local g_ABnf = nil
local g_ABnfFactory = nil
local g_ABnfColor = nil
ALittleScriptColorType = {
	ABnfKeyWord = 1,
	ABnfId = 2,
	ABnfComment = 3,
	ABnfKey = 4,
	ABnfString = 5,
	ABnfRegex = 6,
}

assert(AUIPlugin.AUICodeLanguage, " extends class:AUIPlugin.AUICodeLanguage is nil")
AUICodeALittleScript = Lua.Class(AUIPlugin.AUICodeLanguage, "AUIPlugin.AUICodeALittleScript")

function AUICodeALittleScript:Ctor(full_path)
	if g_ABnfFactory == nil then
		g_ABnfFactory = alittlescript.create_alittlescript_factory()
	end
	if g_ABnf == nil then
		g_ABnf = alanguage.create_abnf()
		local abnf_path = g_ModuleBasePath .. "/Other/ABnf/ALittleScript.abnf"
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
			g_ABnfColor[ALittleScriptColorType.ABnfKeyWord] = color
		end
		do
			color = {}
			color.red = 204 / 255
			color.green = 120 / 255
			color.blue = 50 / 255
			g_ABnfColor[ALittleScriptColorType.ABnfId] = color
		end
		do
			color = {}
			color.red = 128 / 255
			color.green = 128 / 255
			color.blue = 128 / 255
			g_ABnfColor[ALittleScriptColorType.ABnfComment] = color
		end
		do
			color = {}
			color.red = 53 / 255
			color.green = 155 / 255
			color.blue = 185 / 255
			g_ABnfColor[ALittleScriptColorType.ABnfKey] = color
		end
		do
			color = {}
			color.red = 85 / 255
			color.green = 134 / 255
			color.blue = 74 / 255
			g_ABnfColor[ALittleScriptColorType.ABnfString] = color
		end
		do
			color = {}
			color.red = 152 / 255
			color.green = 118 / 255
			color.blue = 170 / 255
			g_ABnfColor[ALittleScriptColorType.ABnfRegex] = color
		end
	end
	___rawset(self, "_abnf_file", alittlescript.create_alittlescript_file(full_path, g_ABnf, ""))
end

function AUICodeALittleScript:QueryColorValue(tag)
	return g_ABnfColor[tag]
end

