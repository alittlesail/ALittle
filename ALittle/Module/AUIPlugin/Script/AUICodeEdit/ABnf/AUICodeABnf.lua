-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1083672388, "AUIPlugin.ABnfProjectInfo", {
name = "AUIPlugin.ABnfProjectInfo", ns_name = "AUIPlugin", rl_name = "ABnfProjectInfo", hash_code = 1083672388,
name_list = {"project"},
type_list = {"AUIPlugin.AUICodeProject"},
option_map = {}
})

local g_ABnfColor = nil
ABnfColorType = {
	ABnfKeyWord = 1,
	ABnfId = 2,
	ABnfComment = 3,
	ABnfKey = 4,
	ABnfString = 5,
	ABnfRegex = 6,
}

g_ABnfProjectInfo = ALittle.CreateValueWeakMap()
assert(AUIPlugin.AUICodeLanguage, " extends class:AUIPlugin.AUICodeLanguage is nil")
AUICodeABnf = Lua.Class(AUIPlugin.AUICodeLanguage, "AUIPlugin.AUICodeABnf")

function AUICodeABnf:Ctor(project, full_path)
	if self._project == nil and g_ABnfProjectInfo.project == nil then
		local buffer = ALittle.File_ReadTextFromFile(g_ModuleBasePath .. "/Other/ABnf/ABnf.abnf")
		if buffer == nil then
			buffer = ""
		end
		local native_project = abnf.create_abnf_project("", buffer)
		g_ABnfProjectInfo.project = AUICodeProject(native_project)
		g_ABnfProjectInfo.project:Start()
	end
	if self._project == nil then
		___rawset(self, "_project", g_ABnfProjectInfo.project)
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
			color.red = 53 / 255
			color.green = 155 / 255
			color.blue = 185 / 255
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
	___rawset(self, "_abnf_file", abnf.create_abnf_file(self._project.project, full_path, ""))
end

function AUICodeABnf:OnOpen()
	self._project:UpdateFile(self._full_path)
end

function AUICodeABnf:OnShow()
end

function AUICodeABnf:OnHide()
end

function AUICodeABnf:OnClose()
	self._project:RemoveFile(self._full_path)
end

function AUICodeABnf:QueryColorValue(tag)
	return g_ABnfColor[tag]
end

function AUICodeABnf:GenerateABnf()
end
AUICodeABnf.GenerateABnf = Lua.CoWrap(AUICodeABnf.GenerateABnf)

function AUICodeABnf:Generate(target_path, language_name)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	abnf.abnffile_generate(self._abnf_file, query_id, self._version, target_path, language_name)
	return coroutine.yield()
end

