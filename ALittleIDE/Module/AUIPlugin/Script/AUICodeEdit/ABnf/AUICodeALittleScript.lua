-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
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
AUIPlugin.ALittleScriptColorType = {
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

AUIPlugin.ALittleScriptIconType = {
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

local g_ALittleScriptIcon = {}
g_ALittleScriptIcon[1] = "ABnf/ALittleScript/ALittleScriptClassIcon.png"
g_ALittleScriptIcon[2] = "ABnf/ALittleScript/ALittleScriptStructIcon.png"
g_ALittleScriptIcon[3] = "ABnf/ALittleScript/ALittleScriptPropertyIcon.png"
g_ALittleScriptIcon[4] = "ABnf/ALittleScript/ALittleScriptNamespaceIcon.png"
g_ALittleScriptIcon[5] = "ABnf/ALittleScript/ALittleScriptTemplateIcon.png"
g_ALittleScriptIcon[6] = "ABnf/ALittleScript/ALittleScriptEnumIcon.png"
g_ALittleScriptIcon[7] = "ABnf/ALittleScript/ALittleScriptNamespaceIcon.png"
g_ALittleScriptIcon[8] = "ABnf/ALittleScript/ALittleScriptStaticIcon.png"
g_ALittleScriptIcon[9] = "ABnf/ALittleScript/ALittleScriptMethodIcon.png"
g_ALittleScriptIcon[10] = "ABnf/ALittleScript/ALittleScriptFieldIcon.png"
g_ALittleScriptIcon[11] = "ABnf/ALittleScript/ALittleScriptStaticIcon.png"
g_ALittleScriptIcon[12] = "ABnf/ALittleScript/ALittleScriptInstanceIcon.png"
g_ALittleScriptIcon[13] = "ABnf/ALittleScript/ALittleScriptParamIcon.png"
g_ALittleScriptIcon[14] = "ABnf/ALittleScript/ALittleScriptVariableIcon.png"
assert(AUIPlugin.AUICodeLanguage, " extends class:AUIPlugin.AUICodeLanguage is nil")
AUIPlugin.AUICodeALittleScript = Lua.Class(AUIPlugin.AUICodeLanguage, "AUIPlugin.AUICodeALittleScript")

function AUIPlugin.AUICodeALittleScript:Ctor(project, full_path, module_path)
	if g_ALittleScriptColor == nil then
		g_ALittleScriptColor = {}
		local color
		do
			color = {}
			color.red = 87 / 255
			color.green = 166 / 255
			color.blue = 74 / 255
			g_ALittleScriptColor[1] = color
		end
		do
			color = {}
			color.red = 78 / 255
			color.green = 201 / 255
			color.blue = 176 / 255
			g_ALittleScriptColor[2] = color
		end
		do
			color = {}
			color.red = 218 / 255
			color.green = 218 / 255
			color.blue = 218 / 255
			g_ALittleScriptColor[3] = color
		end
		do
			color = {}
			color.red = 146 / 255
			color.green = 210 / 255
			color.blue = 244 / 255
			g_ALittleScriptColor[4] = color
		end
		do
			color = {}
			color.red = 216 / 255
			color.green = 160 / 255
			color.blue = 223 / 255
			g_ALittleScriptColor[5] = color
		end
		do
			color = {}
			color.red = 86 / 255
			color.green = 156 / 255
			color.blue = 214 / 255
			g_ALittleScriptColor[6] = color
		end
		do
			color = {}
			color.red = 210 / 255
			color.green = 210 / 255
			color.blue = 160 / 255
			g_ALittleScriptColor[7] = color
		end
		do
			color = {}
			color.red = 169 / 255
			color.green = 183 / 255
			color.blue = 198 / 255
			g_ALittleScriptColor[8] = color
		end
		do
			color = {}
			color.red = 214 / 255
			color.green = 157 / 255
			color.blue = 133 / 255
			g_ALittleScriptColor[9] = color
		end
	end
	___rawset(self, "_abnf_file", alittlescript.create_alittlescript_file(project.project, module_path, full_path, ""))
end

function AUIPlugin.AUICodeALittleScript:OnRightMenu(menu)
	menu:AddItem("生成", Lua.Bind(self.GenerateLanguage, self, true))
end

function AUIPlugin.AUICodeALittleScript:OnSave()
	self:GenerateLanguage(false)
end

function AUIPlugin.AUICodeALittleScript:GenerateLanguage(notice)
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
AUIPlugin.AUICodeALittleScript.GenerateLanguage = Lua.CoWrap(AUIPlugin.AUICodeALittleScript.GenerateLanguage)

function AUIPlugin.AUICodeALittleScript:QueryColorValue(tag)
	return g_ALittleScriptColor[tag]
end

function AUIPlugin.AUICodeALittleScript:QueryAutoFormat(input)
	return input == ";" or input == "}"
end

function AUIPlugin.AUICodeALittleScript:NeedAutoFormat()
	return true
end

function AUIPlugin.AUICodeALittleScript:SetTargetLanguage(target_languaeg)
	alittlescript.alittlescriptproject_settargetlanguage(self._project.project, target_languaeg)
end

function AUIPlugin.AUICodeALittleScript:Generate(full_path)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	alittlescript.alittlescriptproject_generate(self._project.project, query_id, full_path)
	return coroutine.yield()
end

function AUIPlugin.AUICodeALittleScript:QueryCompleteIcon(tag)
	return g_ALittleScriptIcon[tag]
end

assert(AUIPlugin.AUICodeProject, " extends class:AUIPlugin.AUICodeProject is nil")
AUIPlugin.AUICodeALittleScriptProject = Lua.Class(AUIPlugin.AUICodeProject, "AUIPlugin.AUICodeALittleScriptProject")

function AUIPlugin.AUICodeALittleScriptProject.__getter:upper_ext()
	return "ALITTLE"
end

function AUIPlugin.AUICodeALittleScriptProject:OnTreeMenu(full_path, menu)
	menu:AddItem("生成目标代码", Lua.Bind(self.GenerateDir, self, full_path))
end

function AUIPlugin.AUICodeALittleScriptProject:OnTreeItemMenu(full_path, menu)
	menu:AddItem("生成目标代码", Lua.Bind(self.GenerateFile, self, full_path))
	menu:AddItem("打开Lua代码", Lua.Bind(self.OpenTargetLuaFile, self, full_path))
	menu:AddItem("打开JavaScript代码", Lua.Bind(self.OpenTargetJavaScriptFile, self, full_path))
	menu:AddItem("打开Lua字节码", Lua.Bind(self.OpenTargetLuaByteCode, self, full_path))
end

function AUIPlugin.AUICodeALittleScriptProject:GenerateDir(full_path)
	local index = ALittle.String_Find(full_path, "/src")
	if index == nil then
		g_AUITool:ShowNotice("提示", "当前不是/src的子目录")
		return
	end
	local pre = ""
	if alittlescript.alittlescriptproject_gettargetlanguage(self._project) == "JavaScript" then
		pre = "JS"
	end
	local new_path = ALittle.String_Sub(full_path, 1, index) .. pre .. "Script" .. ALittle.String_Sub(full_path, index + 4)
	ALittle.File_DeleteDeepDir(new_path)
	ALittle.File_MakeDeepDir(new_path)
	local file_map = ALittle.File_GetFileAttrByDir(full_path)
	for file_path, attr in ___pairs(file_map) do
		local error = self:Generate(file_path)
		if error ~= nil then
			if "YES" == g_AUITool:DeleteNotice("错误", error.error .. "\n 文件路径" .. file_path .. "\n是否打开该文件?") then
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
AUIPlugin.AUICodeALittleScriptProject.GenerateDir = Lua.CoWrap(AUIPlugin.AUICodeALittleScriptProject.GenerateDir)

function AUIPlugin.AUICodeALittleScriptProject:GenerateFile(full_path)
	local error = self:Generate(full_path)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error.error .. " 文件路径" .. error.full_path)
		return
	end
	g_AUITool:ShowNotice("提示", "生成成功")
end
AUIPlugin.AUICodeALittleScriptProject.GenerateFile = Lua.CoWrap(AUIPlugin.AUICodeALittleScriptProject.GenerateFile)

function AUIPlugin.AUICodeALittleScriptProject:OpenTargetLuaFile(full_path)
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

function AUIPlugin.AUICodeALittleScriptProject:OpenTargetLuaByteCode(full_path)
	full_path = ALittle.File_ChangeFileExtByPath(full_path, "lua")
	local index = ALittle.String_Find(full_path, "/src/")
	if index == nil then
		return
	end
	local new_path = ALittle.String_Sub(full_path, 1, index) .. "Script/" .. ALittle.String_Sub(full_path, index + 5)
	local out_path = ALittle.String_Sub(full_path, 1, index) .. "ByteCode/" .. ALittle.String_Sub(full_path, index + 5)
	local out_dir = ALittle.File_GetFilePathByPath(out_path)
	ALittle.File_MakeDeepDir(out_dir)
	out_path = ALittle.File_ChangeFileExtByPath(out_path, "txt")
	local decompile = carp.CarpLuaDecompile()
	decompile:Decompile(new_path, out_path)
	local event = {}
	event.file_path = out_path
	self:DispatchEvent(___all_struct[2057209532], event)
end

function AUIPlugin.AUICodeALittleScriptProject:OpenTargetJavaScriptFile(full_path)
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

function AUIPlugin.AUICodeALittleScriptProject:Generate(full_path)
	local ___COROUTINE = coroutine.running()
	local query_id = self:Add(___COROUTINE)
	alittlescript.alittlescriptproject_generate(self._project, query_id, full_path)
	return coroutine.yield()
end

function AUIPlugin.AUICodeALittleScriptProject:QueryCompleteIcon(tag)
	return g_ALittleScriptIcon[tag]
end

end