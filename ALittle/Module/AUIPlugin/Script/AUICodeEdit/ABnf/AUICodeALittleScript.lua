-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

local g_ALittleScriptColor = nil
local g_ALittleScriptIcon = nil
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

ALittleScriptIconType = {
	CLASS = 1,
	STRUCT = 2,
	PROPERTY = 3,
	NAMESPACE = 4,
	TEMPLATE = 5,
	ENUM = 6,
	LANGUAGE = 7,
	GLOBAL_METHOD = 8,
	MEMBER_METHOD = 9,
	FIELD_METHOD = 10,
	STATIC_METHOD = 11,
	INSTANCE = 12,
	PARAM = 13,
	VARIABLE = 14,
}

assert(AUIPlugin.AUICodeLanguage, " extends class:AUIPlugin.AUICodeLanguage is nil")
AUICodeALittleScript = Lua.Class(AUIPlugin.AUICodeLanguage, "AUIPlugin.AUICodeALittleScript")

function AUICodeALittleScript:Ctor(project, full_path, module_path)
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
	if g_ALittleScriptIcon == nil then
		g_ALittleScriptIcon = {}
		g_ALittleScriptIcon[ALittleScriptIconType.CLASS] = "ABnf/ALittleScript/ALittleScriptClassIcon.png"
		g_ALittleScriptIcon[ALittleScriptIconType.STRUCT] = "ABnf/ALittleScript/ALittleScriptStructIcon.png"
		g_ALittleScriptIcon[ALittleScriptIconType.PROPERTY] = "ABnf/ALittleScript/ALittleScriptPropertyIcon.png"
		g_ALittleScriptIcon[ALittleScriptIconType.NAMESPACE] = "ABnf/ALittleScript/ALittleScriptNamespaceIcon.png"
		g_ALittleScriptIcon[ALittleScriptIconType.TEMPLATE] = "ABnf/ALittleScript/ALittleScriptTemplateIcon.png"
		g_ALittleScriptIcon[ALittleScriptIconType.ENUM] = "ABnf/ALittleScript/ALittleScriptEnumIcon.png"
		g_ALittleScriptIcon[ALittleScriptIconType.LANGUAGE] = "ABnf/ALittleScript/ALittleScriptNamespaceIcon.png"
		g_ALittleScriptIcon[ALittleScriptIconType.GLOBAL_METHOD] = "ABnf/ALittleScript/ALittleScriptStaticIcon.png"
		g_ALittleScriptIcon[ALittleScriptIconType.MEMBER_METHOD] = "ABnf/ALittleScript/ALittleScriptMethodIcon.png"
		g_ALittleScriptIcon[ALittleScriptIconType.FIELD_METHOD] = "ABnf/ALittleScript/ALittleScriptFieldIcon.png"
		g_ALittleScriptIcon[ALittleScriptIconType.STATIC_METHOD] = "ABnf/ALittleScript/ALittleScriptStaticIcon.png"
		g_ALittleScriptIcon[ALittleScriptIconType.INSTANCE] = "ABnf/ALittleScript/ALittleScriptInstanceIcon.png"
		g_ALittleScriptIcon[ALittleScriptIconType.PARAM] = "ABnf/ALittleScript/ALittleScriptParamIcon.png"
		g_ALittleScriptIcon[ALittleScriptIconType.VARIABLE] = "ABnf/ALittleScript/ALittleScriptVariableIcon.png"
	end
	___rawset(self, "_abnf_file", alittlescript.create_alittlescript_file(project.project, module_path, full_path, ""))
end

function AUICodeALittleScript:OnRightMenu(menu)
	menu:AddItem("生成", Lua.Bind(self.GenerateLanguage, self, true))
end

function AUICodeALittleScript:OnSave()
	self:GenerateLanguage(false)
end

function AUICodeALittleScript:GenerateLanguage(notice)
	local error = self:Generate(self._full_path)
	if error ~= nil then
		if notice then
			g_AUITool:ShowNotice("错误", error.error .. " 文件路径" .. error.full_path)
		end
		return
	end
	if notice then
		g_AUITool:ShowNotice("提示", "生成成功")
	end
end
AUICodeALittleScript.GenerateLanguage = Lua.CoWrap(AUICodeALittleScript.GenerateLanguage)

function AUICodeALittleScript:QueryColorValue(tag)
	return g_ALittleScriptColor[tag]
end

function AUICodeALittleScript:QueryAutoFormat(input)
	return input == ";" or input == "}"
end

function AUICodeALittleScript:NeedAutoFormat()
	return true
end

function AUICodeALittleScript:SetTargetLanguage(target_languaeg)
	alittlescript.alittlescriptproject_settargetlanguage(self._project.project, target_languaeg)
end

function AUICodeALittleScript:Generate(full_path)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	alittlescript.alittlescriptproject_generate(self._project.project, query_id, full_path)
	return coroutine.yield()
end

function AUICodeALittleScript:QueryCompleteIcon(tag)
	return g_ALittleScriptIcon[tag]
end

assert(AUIPlugin.AUICodeProject, " extends class:AUIPlugin.AUICodeProject is nil")
AUICodeALittleScriptProject = Lua.Class(AUIPlugin.AUICodeProject, "AUIPlugin.AUICodeALittleScriptProject")

function AUICodeALittleScriptProject.__getter:upper_ext()
	return "ALITTLE"
end

function AUICodeALittleScriptProject:OnTreeMenu(full_path, menu)
	menu:AddItem("生成目标代码", Lua.Bind(self.GenerateDir, self, full_path))
end

function AUICodeALittleScriptProject:OnTreeItemMenu(full_path, menu)
	menu:AddItem("生成目标代码", Lua.Bind(self.GenerateFile, self, full_path))
	menu:AddItem("打开Lua代码", Lua.Bind(self.OpenTargetLuaFile, self, full_path))
	menu:AddItem("打开JavaScript代码", Lua.Bind(self.OpenTargetJavaScriptFile, self, full_path))
end

function AUICodeALittleScriptProject:GenerateDir(full_path)
	local file_map = ALittle.File_GetFileAttrByDir(full_path)
	for file_path, attr in ___pairs(file_map) do
		local error = self:Generate(file_path)
		if error ~= nil then
			if AUIToolOption.YES == g_AUITool:DeleteNotice("错误", error.error .. "\n 文件路径" .. file_path .. "\n是否打开该文件?") then
				local goto_event = {}
				goto_event.file_path = error.full_path
				if goto_event.file_path == nil then
					goto_event.file_path = file_path
				end
				goto_event.line_start = error.line_start
				goto_event.char_start = error.char_start
				goto_event.line_end = error.line_end
				goto_event.char_end = error.char_end
				self:DispatchEvent(___all_struct[2057209532], goto_event)
			end
			return
		end
	end
	g_AUITool:ShowNotice("提示", "生成成功")
end
AUICodeALittleScriptProject.GenerateDir = Lua.CoWrap(AUICodeALittleScriptProject.GenerateDir)

function AUICodeALittleScriptProject:GenerateFile(full_path)
	local error = self:Generate(full_path)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error.error .. " 文件路径" .. error.full_path)
		return
	end
	g_AUITool:ShowNotice("提示", "生成成功")
end
AUICodeALittleScriptProject.GenerateFile = Lua.CoWrap(AUICodeALittleScriptProject.GenerateFile)

function AUICodeALittleScriptProject:OpenTargetLuaFile(full_path)
	full_path = ALittle.File_ChangeFileExtByPath(full_path, "lua")
	local index = ALittle.String_Find(full_path, "/src/")
	if index == nil then
		return
	end
	local new_path = ALittle.String_Sub(full_path, 1, index) .. "Script/" .. ALittle.String_Sub(full_path, index + 5)
	local event = {}
	event.file_path = new_path
	self:DispatchEvent(___all_struct[2057209532], event)
end

function AUICodeALittleScriptProject:OpenTargetJavaScriptFile(full_path)
	full_path = ALittle.File_ChangeFileExtByPath(full_path, "js")
	local index = ALittle.String_Find(full_path, "/src/")
	if index == nil then
		return
	end
	local new_path = ALittle.String_Sub(full_path, 1, index) .. "JSScript/" .. ALittle.String_Sub(full_path, index + 5)
	local event = {}
	event.file_path = new_path
	self:DispatchEvent(___all_struct[2057209532], event)
end

function AUICodeALittleScriptProject:Generate(full_path)
	local ___COROUTINE = coroutine.running()
	local query_id = self:Add(___COROUTINE)
	alittlescript.alittlescriptproject_generate(self._project, query_id, full_path)
	return coroutine.yield()
end

