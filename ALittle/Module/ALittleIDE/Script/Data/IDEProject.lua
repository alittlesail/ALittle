-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(1910687721, "ALittleIDE.IDEProjectEvent", {
name = "ALittleIDE.IDEProjectEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectEvent", hash_code = 1910687721,
name_list = {"target","name"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
ALittle.RegStruct(-975432877, "ALittleIDE.IDEProjectOpenEvent", {
name = "ALittleIDE.IDEProjectOpenEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectOpenEvent", hash_code = -975432877,
name_list = {"target","name"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
ALittle.RegStruct(-685984390, "ALittleIDE.IDEProjectAddEvent", {
name = "ALittleIDE.IDEProjectAddEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectAddEvent", hash_code = -685984390,
name_list = {"target","name"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
ALittle.RegStruct(-332308624, "ALittleIDE.IDEProjectCloseEvent", {
name = "ALittleIDE.IDEProjectCloseEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectCloseEvent", hash_code = -332308624,
name_list = {"target","name"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
ALittle.RegStruct(-277092447, "ALittleIDE.IDEProjectRemoveEvent", {
name = "ALittleIDE.IDEProjectRemoveEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectRemoveEvent", hash_code = -277092447,
name_list = {"target","name"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
ALittle.RegStruct(-93681239, "ALittleIDE.IDEProjectCreateControlEvent", {
name = "ALittleIDE.IDEProjectCreateControlEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectCreateControlEvent", hash_code = -93681239,
name_list = {"target","name"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
ALittle.RegStruct(374071006, "ALittleIDE.IDEProjectChangeControlEvent", {
name = "ALittleIDE.IDEProjectChangeControlEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectChangeControlEvent", hash_code = 374071006,
name_list = {"target","name"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
ALittle.RegStruct(934918978, "ALittleIDE.IDEProjectInfo", {
name = "ALittleIDE.IDEProjectInfo", ns_name = "ALittleIDE", rl_name = "IDEProjectInfo", hash_code = 934918978,
name_list = {"name","base_path","texture_path","save","control","config","ui"},
type_list = {"string","string","string","bool","ALittle.ControlSystem","ALittle.IJsonConfig","ALittleIDE.IDEUIManager"},
option_map = {}
})
ALittle.RegStruct(1962591044, "ALittleIDE.IDEProjectDeleteControlEvent", {
name = "ALittleIDE.IDEProjectDeleteControlEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectDeleteControlEvent", hash_code = 1962591044,
name_list = {"target","name"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})

assert(ALittle.EventDispatcher, " extends class:ALittle.EventDispatcher is nil")
IDEProject = Lua.Class(ALittle.EventDispatcher, "ALittleIDE.IDEProject")

function IDEProject:AddProjectConfig(name)
	local project_map = g_IDEConfig:GetConfig("project_map", {})
	if project_map[name] == nil then
		project_map[name] = name
		g_IDEConfig:SetConfig("project_map", project_map)
	end
end

function IDEProject:RemoveProjectConfig(name)
	local project_map = g_IDEConfig:GetConfig("project_map", {})
	if project_map[name] == nil then
		return
	end
	project_map[name] = nil
	g_IDEConfig:SetConfig("project_map", project_map)
end

function IDEProject:NewProject(name, window_width, window_height, font_path, font_size)
	ALittle.File_MakeDeepDir(ALittle.File_BaseFilePath() .. "Module/" .. name)
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Texture")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Texture/" .. name)
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Font")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Sound")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Other")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/JSScript")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Script")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/UI")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Icon")
	local base_path = ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameTemplate"
	local target_path = ALittle.File_BaseFilePath() .. "Module/" .. name .. "/"
	local file_map = ALittle.File_GetFileAttrByDir(base_path)
	for file_path, attr in ___pairs(file_map) do
		local rel_path = ALittle.String_Sub(file_path, ALittle.String_Len(base_path) + 1)
		local full_path = target_path .. rel_path
		full_path = ALittle.String_Replace(full_path, "abcd@module_name@abcd", name)
		full_path = ALittle.String_Replace(full_path, "abcd@upper_module_name@abcd", ALittle.String_Upper(name))
		full_path = ALittle.String_Replace(full_path, "abcd@lower_module_name@abcd", ALittle.String_Lower(name))
		ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(full_path))
		local ext = ALittle.String_Upper(ALittle.File_GetFileExtByPath(file_path))
		if ext == "JSON" or ext == "LUA" or ext == "CFG" or ext == "TXT" or ext == "ALITTLE" or ext == "XML" or ext == "NAME" or ext == "SLN" or ext == "VCXPROJ" or ext == "FILTERS" or ext == "USER" then
			local content = ALittle.File_ReadTextFromFile(file_path)
			if content ~= nil then
				content = ALittle.String_Replace(content, "abcd@module_name@abcd", name)
				content = ALittle.String_Replace(content, "abcd@upper_module_name@abcd", ALittle.String_Upper(name))
				content = ALittle.String_Replace(content, "abcd@lower_module_name@abcd", ALittle.String_Lower(name))
				content = ALittle.String_Replace(content, "abcd@view_width@abcd", "" .. window_width)
				content = ALittle.String_Replace(content, "abcd@view_height@abcd", "" .. window_height)
				content = ALittle.String_Replace(content, "abcd@font_path@abcd", font_path)
				ALittle.File_WriteTextToFile(content, full_path)
			end
		else
			ALittle.File_CopyFile(file_path, full_path)
		end
	end
	ALittle.File_CopyFile("Export/Icon/install.ico", ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Icon/install.ico")
	ALittle.File_CopyFile("Export/Icon/install.png", ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Icon/install.png")
	local config = ALittle.CreateConfigSystem("Module/" .. name .. "/ALittleIDE.cfg")
	config:SetConfig("default_show_width", window_width, true)
	config:SetConfig("default_show_height", window_height, true)
	config:SetConfig("default_font_path", font_path, true)
	config:SetConfig("default_font_size", font_size, true)
	config:SaveConfig()
	self:AddProjectConfig(name)
	local event = {}
	event.name = name
	self:DispatchEvent(___all_struct[-685984390], event)
	return true
end

function IDEProject:OpenProject(name)
	self:AddProjectConfig(name)
	self._project = {}
	self._project.name = name
	self._project.base_path = ALittle.File_BaseFilePath() .. "Module/" .. name .. "/"
	self._project.texture_path = self._project.base_path .. "Texture"
	self._project.save = true
	self._project.control = ALittle.ControlSystem(name)
	self._project.control.log_error = false
	self._project.control.cache_texture = false
	self._project.config = ALittle.CreateConfigSystem("Module/" .. name .. "/ALittleIDE.cfg")
	self._project.ui = IDEUIManager(name, self._project.control)
	g_IDEConfig:SetConfig("last_project", name)
	local e = {}
	e.name = name
	self:DispatchEvent(___all_struct[-975432877], e)
	return true
end

function IDEProject:CloseProject()
	if self._project == nil then
		return "当前没有项目"
	end
	local e = {}
	e.name = self._project.name
	self:DispatchEvent(___all_struct[-332308624], e)
	self._project = nil
	return nil
end

function IDEProject:RemoveProject(name)
	if self._project ~= nil and self._project.name == name then
		return "请先关闭项目，再移除"
	end
	self:RemoveProjectConfig(name)
	local project_name = g_IDEConfig:GetConfig("last_project", "")
	if project_name == name then
		g_IDEConfig:SetConfig("last_project", "")
	end
	local event = {}
	event.name = name
	self:DispatchEvent(___all_struct[-277092447], event)
	return nil
end

function IDEProject.__getter:project()
	return self._project
end

g_IDEProject = IDEProject()
