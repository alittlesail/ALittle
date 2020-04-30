-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1255897792, "ALittleIDE.IDEMainMenuImageInfo", {
name = "ALittleIDE.IDEMainMenuImageInfo", ns_name = "ALittleIDE", rl_name = "IDEMainMenuImageInfo", hash_code = 1255897792,
name_list = {"file_name","x","y","width","height"},
type_list = {"string","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1020446174, "ALittleIDE.IDEMainMenuFramePlayInfo", {
name = "ALittleIDE.IDEMainMenuFramePlayInfo", ns_name = "ALittleIDE", rl_name = "IDEMainMenuFramePlayInfo", hash_code = 1020446174,
name_list = {"width","height","root_path","image_list","image_count"},
type_list = {"double","double","string","List<ALittleIDE.IDEMainMenuImageInfo>","int"},
option_map = {}
})

IDEMainMenu = Lua.Class(nil, "ALittleIDE.IDEMainMenu")

function IDEMainMenu:ShowFileMenu(event)
	if self._menu_file_menu == nil then
		self._menu_file_menu = g_Control:CreateControl("ide_file_menu", self)
	end
	local x, y = event.target:LocalToGlobal()
	self._menu_file_menu.x = x
	self._menu_file_menu.y = y + event.target.height
	A_LayerManager:ShowFromRight(self._menu_file_menu)
end

function IDEMainMenu:HandleNewProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:ShowNewProject()
end

function IDEMainMenu:HandleOpenProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:ShowOpenProject()
end

function IDEMainMenu:HandleSettingProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:ShowSettingProject(nil)
end

function IDEMainMenu:HandleSaveProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDETabManager:SaveAllTab()
end

function IDEMainMenu:HandleRefreshProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:RefreshProject()
end

function IDEMainMenu:HandleExportProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:ShowExportProject()
end

function IDEMainMenu:HandleRun(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:RunProject()
end

function IDEMainMenu:ShowEditMenu(event)
	if self._menu_edit_menu == nil then
		self._menu_edit_menu = g_Control:CreateControl("ide_edit_menu", self)
	end
	local x, y = event.target:LocalToGlobal()
	self._menu_edit_menu.x = x
	self._menu_edit_menu.y = y + event.target.height
	A_LayerManager:ShowFromRight(self._menu_edit_menu)
end

function IDEMainMenu:HandleNewControl(event)
	A_LayerManager:HideFromRight(self._menu_edit_menu)
	g_IDEControlManager:ShowNewControl()
end

function IDEMainMenu:HandleUndoRevoke(event)
	A_LayerManager:HideFromRight(self._menu_edit_menu)
	g_IDEUICenter:HandleUndoRevoke(nil)
end

function IDEMainMenu:HandleDoRevoke(event)
	A_LayerManager:HideFromRight(self._menu_edit_menu)
	g_IDEUICenter:HandleDoRevoke(nil)
end

function IDEMainMenu:ShowToolMenu(event)
	if self._menu_tool_menu == nil then
		self._menu_tool_menu = g_Control:CreateControl("ide_tool_menu", self)
	end
	local x, y = event.target:LocalToGlobal()
	self._menu_tool_menu.x = x
	self._menu_tool_menu.y = y + event.target.height
	A_LayerManager:ShowFromRight(self._menu_tool_menu)
end

function IDEMainMenu:HandleGenUIAllInOneClick(event)
	A_LayerManager:HideFromRight(self._menu_tool_menu)
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("提示", "没有加载项目")
		return
	end
	local all_in_one = {}
	local map = ALittle.File_GetFileAttrByDir("Module/" .. g_IDEProject.project.name .. "/UI")
	for path, _ in ___pairs(map) do
		local json = ALittle.File_ReadJsonFromStdFile(path)
		for name, o in ___pairs(json) do
			all_in_one[name] = o
		end
	end
	local result = ALittle.File_WriteJsonFromStdFile(all_in_one, "Module/" .. g_IDEProject.project.name .. "/ui_all_in_one.json")
	if result then
		g_IDETool:ShowNotice("提示", "生成成功")
	else
		g_IDETool:ShowNotice("提示", "生成失败")
	end
end

function IDEMainMenu:HandleFramePlayFromPList(event)
	A_LayerManager:HideFromRight(self._menu_tool_menu)
	if self._frameplay_plist_dialog == nil then
		self._frameplay_plist_dialog = g_Control:CreateControl("ide_frameplay_plist_dialog", self, g_IDECenter.dialog_layer)
	end
	self._frameplay_plist_dialog.visible = true
end

function IDEMainMenu.ImageListInFramePlayCmp(a, b)
	return a.file_name < a.file_name
end

function IDEMainMenu:HandleViewLog(event)
	A_LayerManager:HideFromRight(self._menu_tool_menu)
	if self._view_log_dialog == nil then
		self._view_log_dialog = g_Control:CreateControl("ide_view_log_dialog", self, g_IDECenter.dialog_layer)
		self:HandleViewLogRefresh(nil)
	end
	self._view_log_dialog.visible = true
end

function IDEMainMenu:HandleViewLogRefresh(event)
	local file_name = ALittle.Time_GetCurYMD(ALittle.Time_GetCurTime()) .. ".log"
	local file_path = ALittle.File_BaseFilePath() .. "Log/" .. file_name
	local content = ALittle.File_ReadTextFromFile(file_path, false)
	if content == nil then
		return
	end
	local content_list = ALittle.String_Split(content, "\n")
	local content_len = ALittle.List_MaxN(content_list)
	local copy_len = content_len - 100
	if copy_len < 1 then
		copy_len = 1
	end
	local log_list = {}
	local log_list_count = 0
	local i = content_len
	while true do
		if not(i >= copy_len) then break end
		log_list_count = log_list_count + 1
		log_list[log_list_count] = content_list[i]
		i = i+(-1)
	end
	self._view_log_content.text = ALittle.String_Join(log_list, "\n")
end

function IDEMainMenu:HandleViewLogClose(event)
	self._view_log_dialog.visible = false
end

g_IDEMainMenu = IDEMainMenu()
