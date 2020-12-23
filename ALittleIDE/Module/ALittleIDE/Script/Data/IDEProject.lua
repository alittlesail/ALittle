-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(2057209532, "AUIPlugin.AUICodeProjectGotoEvent", {
name = "AUIPlugin.AUICodeProjectGotoEvent", ns_name = "AUIPlugin", rl_name = "AUICodeProjectGotoEvent", hash_code = 2057209532,
name_list = {"target","file_path","line_start","char_start","line_end","char_end"},
type_list = {"ALittle.EventDispatcher","string","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(1962591044, "ALittleIDE.IDEProjectDeleteControlEvent", {
name = "ALittleIDE.IDEProjectDeleteControlEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectDeleteControlEvent", hash_code = 1962591044,
name_list = {"target","module","name"},
type_list = {"ALittle.EventDispatcher","string","string"},
option_map = {}
})
ALittle.RegStruct(1910687721, "ALittleIDE.IDEProjectEvent", {
name = "ALittleIDE.IDEProjectEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectEvent", hash_code = 1910687721,
name_list = {"target","module","name"},
type_list = {"ALittle.EventDispatcher","string","string"},
option_map = {}
})
ALittle.RegStruct(1787992834, "ALittleIDE.IDEProjectSettingChanged", {
name = "ALittleIDE.IDEProjectSettingChanged", ns_name = "ALittleIDE", rl_name = "IDEProjectSettingChanged", hash_code = 1787992834,
name_list = {"target","default_show_width","default_show_height","default_font_path","default_font_size"},
type_list = {"ALittle.EventDispatcher","double","double","string","int"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(-975432877, "ALittleIDE.IDEProjectOpenEvent", {
name = "ALittleIDE.IDEProjectOpenEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectOpenEvent", hash_code = -975432877,
name_list = {"target","module","name"},
type_list = {"ALittle.EventDispatcher","string","string"},
option_map = {}
})
ALittle.RegStruct(934918978, "ALittleIDE.IDEProjectInfo", {
name = "ALittleIDE.IDEProjectInfo", ns_name = "ALittleIDE", rl_name = "IDEProjectInfo", hash_code = 934918978,
name_list = {"name","config","ui","code"},
type_list = {"string","ALittle.IJsonConfig","Map<string,ALittleIDE.IDEUIManager>","AUIPlugin.AUICodeProject"},
option_map = {}
})
ALittle.RegStruct(-685984390, "ALittleIDE.IDEProjectAddEvent", {
name = "ALittleIDE.IDEProjectAddEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectAddEvent", hash_code = -685984390,
name_list = {"target","module","name"},
type_list = {"ALittle.EventDispatcher","string","string"},
option_map = {}
})
ALittle.RegStruct(374071006, "ALittleIDE.IDEProjectChangeControlEvent", {
name = "ALittleIDE.IDEProjectChangeControlEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectChangeControlEvent", hash_code = 374071006,
name_list = {"target","module","name"},
type_list = {"ALittle.EventDispatcher","string","string"},
option_map = {}
})
ALittle.RegStruct(-332308624, "ALittleIDE.IDEProjectCloseEvent", {
name = "ALittleIDE.IDEProjectCloseEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectCloseEvent", hash_code = -332308624,
name_list = {"target","module","name"},
type_list = {"ALittle.EventDispatcher","string","string"},
option_map = {}
})
ALittle.RegStruct(-277092447, "ALittleIDE.IDEProjectRemoveEvent", {
name = "ALittleIDE.IDEProjectRemoveEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectRemoveEvent", hash_code = -277092447,
name_list = {"target","module","name"},
type_list = {"ALittle.EventDispatcher","string","string"},
option_map = {}
})
ALittle.RegStruct(-93681239, "ALittleIDE.IDEProjectCreateControlEvent", {
name = "ALittleIDE.IDEProjectCreateControlEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectCreateControlEvent", hash_code = -93681239,
name_list = {"target","module","name"},
type_list = {"ALittle.EventDispatcher","string","string"},
option_map = {}
})

assert(ALittle.EventDispatcher, " extends class:ALittle.EventDispatcher is nil")
ALittleIDE.IDEProject = Lua.Class(ALittle.EventDispatcher, "ALittleIDE.IDEProject")

function ALittleIDE.IDEProject:Ctor()
	___rawset(self, "_in_debug", false)
end

function ALittleIDE.IDEProject:AddProjectConfig(name)
	local project_map = ALittleIDE.g_IDEConfig:GetConfig("project_map", {})
	if project_map[name] == nil then
		project_map[name] = name
		ALittleIDE.g_IDEConfig:SetConfig("project_map", project_map)
	end
end

function ALittleIDE.IDEProject:RemoveProjectConfig(name)
	local project_map = ALittleIDE.g_IDEConfig:GetConfig("project_map", {})
	if project_map[name] == nil then
		return
	end
	project_map[name] = nil
	ALittleIDE.g_IDEConfig:SetConfig("project_map", project_map)
end

function ALittleIDE.IDEProject:GetBreakPoint(file_path)
	if self._project == nil then
		return nil
	end
	local map = self._project.config:GetConfig("break_points", nil)
	if map == nil then
		return nil
	end
	return map[file_path]
end

function ALittleIDE.IDEProject:AddBreakPoint(file_path, line)
	if self._project == nil then
		return
	end
	local map = self._project.config:GetConfig("break_points", nil)
	if map == nil then
		map = {}
	end
	local lines = map[file_path]
	if lines == nil then
		lines = {}
		map[file_path] = lines
	end
	if ALittle.List_IndexOf(lines, line) == nil then
		ALittle.List_Push(lines, line)
	end
	self._project.config:SetConfig("break_points", map)
	if self._debug_client ~= nil then
		self._debug_client:AddBreakPoint(file_path, line)
	end
end

function ALittleIDE.IDEProject:RemoveBreakPoint(file_path, line)
	if self._project == nil then
		return
	end
	local map = self._project.config:GetConfig("break_points", nil)
	if map == nil then
		return
	end
	local lines = map[file_path]
	if lines == nil then
		return
	end
	local index = ALittle.List_IndexOf(lines, line)
	if index ~= nil then
		ALittle.List_Remove(lines, index)
	end
	if ALittle.IsEmpty(lines) then
		map[file_path] = nil
	end
	self._project.config:SetConfig("break_points", map)
	if self._debug_client ~= nil then
		self._debug_client:RemoveBreakPoint(file_path, line)
	end
end

function ALittleIDE.IDEProject:NewProject(name, window_width, window_height, font_path, font_size)
	ALittle.File_MakeDeepDir(ALittle.File_BaseFilePath() .. "Module/" .. name)
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Texture")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Font")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Sound")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Other")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/JSScript")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Script")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/UI")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Tile")
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

function ALittleIDE.IDEProject:RefreshProject()
	if self._project == nil then
		return
	end
	local name = self._project.name
	self:CloseProject()
	self:OpenProject(name)
end

function ALittleIDE.IDEProject:OpenProject(name)
	if name == "" or name == nil then
		return "请输入项目名"
	end
	if ALittle.File_GetFileAttr(ALittle.File_BaseFilePath() .. "Module/" .. name) == nil then
		return "项目不存在:" .. name
	end
	self:CloseProject()
	self:AddProjectConfig(name)
	self._project = {}
	self._project.name = name
	self._project.config = ALittle.CreateConfigSystem("Module/" .. name .. "/ALittleIDE.cfg")
	self._project.ui = {}
	self._project.code = AUIPlugin.AUICodeProject.CreateALittleScriptProject()
	if self._project.code ~= nil then
		self._project.code:AddEventListener(___all_struct[2057209532], self, self.HandleCodeProjectGoToEvent)
	end
	if self._project.code ~= nil then
		alittlescript.alittlescriptproject_settargetlanguage(self._project.code.project, self._project.config:GetConfig("target_language", "Lua"))
	end
	ALittleIDE.g_IDEConfig:SetConfig("last_project", name)
	local e = {}
	e.name = name
	self:DispatchEvent(___all_struct[-975432877], e)
	return nil
end

function ALittleIDE.IDEProject:HandleCodeProjectGoToEvent(event)
	ALittleIDE.g_IDECenter.center.code_list:OpenByFullPath(event.file_path, event.line_start, event.char_start, event.line_end, event.char_end)
end

function ALittleIDE.IDEProject:OpenLastProject()
	local default_name = "BattleCity"
	default_name = nil
	local name = ALittleIDE.g_IDEConfig:GetString("last_project", default_name)
	if name == nil then
		return
	end
	self:OpenProject(name)
end

function ALittleIDE.IDEProject:CloseProject()
	if self._project == nil then
		return "当前没有项目"
	end
	local e = {}
	e.name = self._project.name
	self:DispatchEvent(___all_struct[-332308624], e)
	if self._project.code ~= nil then
		self._project.code:RemoveEventListener(___all_struct[2057209532], self, self.HandleCodeProjectGoToEvent)
		self._project.code:Stop()
	end
	self._project = nil
	if self._debug_loop ~= nil then
		self._debug_loop:Stop()
		self._debug_loop = nil
	end
	if self._debug_client ~= nil then
		self._debug_client:Close()
		self._debug_client = nil
	end
	self._in_debug = false
	return nil
end

function ALittleIDE.IDEProject:RemoveProject(name)
	if self._project ~= nil and self._project.name == name then
		return "请先关闭项目，再移除"
	end
	self:RemoveProjectConfig(name)
	local project_name = ALittleIDE.g_IDEConfig:GetConfig("last_project", "")
	if project_name == name then
		ALittleIDE.g_IDEConfig:SetConfig("last_project", "")
	end
	local event = {}
	event.name = name
	self:DispatchEvent(___all_struct[-277092447], event)
	return nil
end

function ALittleIDE.IDEProject:RunProject(debug)
	if self._project == nil then
		g_AUITool:ShowNotice("提示", "当前没有打开的项目")
		return
	end
	local debug_info = ""
	if debug then
		debug_info = "debug"
	end
	os.execute("start ALittleClient.exe " .. self._project.name .. " " .. debug_info)
end

function ALittleIDE.IDEProject:IsDebug()
	return self._in_debug
end

function ALittleIDE.IDEProject:StartDebugProject()
	if self._project == nil then
		g_AUITool:ShowNotice("提示", "当前没有打开的项目")
		return
	end
	if self._in_debug then
		g_AUITool:ShowNotice("提示", "已启动调试")
		return
	end
	if self._debug_client == nil then
		self._debug_client = carp.CarpLuaDebugClient()
	end
	self._debug_client:Start("127.0.0.1", 1001)
	self._in_debug = true
	if self._debug_loop == nil then
		self._debug_loop = ALittle.LoopFrame(Lua.Bind(self.HandleDebugFrame, self))
	end
	self._debug_loop:Start()
	local break_map = self._project.config:GetConfig("break_points", nil)
	for file_path, lines in ___pairs(break_map) do
		for index, line in ___ipairs(lines) do
			self._debug_client:AddBreakPoint(file_path, line)
		end
	end
end

function ALittleIDE.IDEProject:ContinueDebug()
	if self._debug_client == nil then
		return
	end
	self._debug_client:DoContinue()
end

function ALittleIDE.IDEProject:NextLineDebug()
	if self._debug_client == nil then
		return
	end
	self._debug_client:DoNextLine()
end

function ALittleIDE.IDEProject:HandleDebugFrame(frame_time)
	local event = self._debug_client:HandleEvent()
	if event == nil then
		return
	end
	if event.type == 1 then
		ALittleIDE.g_IDECenter.center.code_list:OpenByFullPath(event.file_path, event.file_line, 1, event.file_line, 1)
	elseif event.type == 2 then
	end
end

function ALittleIDE.IDEProject:StopDebugProject()
	if self._project == nil then
		g_AUITool:ShowNotice("提示", "当前没有打开的项目")
		return
	end
	if self._debug_loop ~= nil then
		self._debug_loop:Stop()
		self._debug_loop = nil
	end
	if self._debug_client ~= nil then
		self._debug_client:Close()
		self._debug_client = nil
	end
	self._in_debug = false
end

function ALittleIDE.IDEProject.__getter:project()
	return self._project
end

function ALittleIDE.IDEProject:GetUIManager(module_name)
	if self._project == nil then
		return nil
	end
	if module_name == nil then
		module_name = self._project.name
	end
	return self._project.ui[module_name]
end

ALittleIDE.g_IDEProject = ALittleIDE.IDEProject()
end