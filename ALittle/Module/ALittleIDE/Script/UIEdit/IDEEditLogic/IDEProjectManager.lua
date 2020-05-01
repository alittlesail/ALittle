-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})

IDEProjectManager = Lua.Class(nil, "ALittleIDE.IDEProjectManager")

function IDEProjectManager:OpenLastProject()
	if g_IDEProject.project ~= nil then
		return
	end
	local project_name = g_IDEConfig:GetConfig("last_project", "")
	if project_name == "" then
		return
	end
	self:OpenProjectImpl(project_name)
end

function IDEProjectManager:HandleProjectSearchClick(event)
	self._project_scroll_screen:RemoveAllChild()
	local key = self._project_search_key.text
	local project_map = g_IDEConfig:GetConfig("project_map", {})
	for k, v in ___pairs(project_map) do
		if key == "" or ALittle.String_Find(v, key) ~= nil then
			local item = g_Control:CreateControl("ide_common_item_button")
			item.text = v
			item.drag_trans_target = self._project_scroll_screen
			item:AddEventListener(___all_struct[-641444818], self, self.HandleProjectItemRightClick)
			self._project_scroll_screen:AddChild(item)
		end
	end
end

function IDEProjectManager:ShowNewProject()
	if self._project_new_dialog == nil then
		self._project_new_dialog = g_Control:CreateControl("ide_new_project_dialog", self)
		A_LayerManager:AddToModal(self._project_new_dialog)
	end
	self._project_new_name.text = ""
	self._project_new_dialog.visible = true
	A_UISystem.focus = self._project_new_name.show_input
end

function IDEProjectManager:HandleNewProjectCancel(event)
	self._project_new_dialog.visible = false
end

function IDEProjectManager:HandleNewProjectConfirm(event)
	local name = self._project_new_name.text
	if name == "" then
		g_IDETool:ShowNotice("错误", "请输入项目名")
		return
	end
	if IDEUtility_CheckName(name) == false then
		g_IDETool:ShowNotice("错误", "项目名不合法:" .. name)
		return
	end
	if ALittle.File_GetFileAttr(ALittle.File_BaseFilePath() .. name) ~= nil then
		g_IDETool:ShowNotice("错误", "项目已存在:" .. name)
		return
	end
	local size_list = ALittle.String_Split(self._view_size_dropdown.text, "x")
	local window_width = ALittle.Math_ToInt(size_list[1])
	if window_width == nil then
		window_width = 800
	end
	local window_height = ALittle.Math_ToInt(size_list[2])
	if window_height == nil then
		window_height = 600
	end
	local font_path = self._default_font_path.text
	local font_size = ALittle.Math_ToInt(self._default_font_size.text)
	if font_size == nil then
		font_size = 25
	end
	g_IDEProject:NewProject(name, ALittle.Math_Floor(window_width), ALittle.Math_Floor(window_height), font_path, ALittle.Math_Floor(font_size))
	g_IDECenter:UpdateProjectList()
	if g_IDEProject.project == nil then
		g_IDECenter:OpenProject(name)
	end
	self._project_new_dialog.visible = false
end

function IDEProjectManager:OpenProjectImpl(name)
	if name == "" then
		g_IDETool:ShowNotice("错误", "请输入项目名")
		return
	end
	if ALittle.File_GetFileAttr(ALittle.File_BaseFilePath() .. "Module/" .. name) == nil then
		g_IDETool:ShowNotice("错误", "项目不存在:" .. name)
		return
	end
	g_IDECenter:CloseProject()
	g_IDECenter:OpenProject(name)
end

function IDEProjectManager:ShowOpenProject()
	if self._project_open_dialog == nil then
		self._project_open_dialog = g_Control:CreateControl("ide_open_project_dialog", self)
		A_LayerManager:AddToModal(self._project_open_dialog)
	end
	self._project_open_name.text = ""
	self._project_open_dialog.visible = true
	A_UISystem.focus = self._project_open_name.show_input
end

function IDEProjectManager:HandleOpenProjectCancel(event)
	self._project_open_dialog.visible = false
end

function IDEProjectManager:HandleOpenProjectConfirm(event)
	self._project_open_dialog.visible = false
	local name = self._project_open_name.text
	if g_IDETabManager:IsSaveAll() then
		self:OpenProjectImpl(name)
		return
	end
	local cancel_callback = Lua.Bind(self.OpenProjectImpl, self, name)
	local confirm_callback = Lua.Bind(g_IDETabManager.SaveAllTab, g_IDETabManager)
	g_IDETool:SaveNotice("提示", "是否保存当前项目?", cancel_callback, confirm_callback)
end

function IDEProjectManager:ShowSettingProject(event)
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("错误", "当前没有打开的项目")
		return
	end
	if self._project_setting_dialog == nil then
		self._project_setting_dialog = g_Control:CreateControl("ide_setting_project_dialog", self)
		A_LayerManager:AddToModal(self._project_setting_dialog)
	end
	self._project_setting_dialog.visible = true
	self._default_show_width.text = g_IDEProject.project.config:GetConfig("default_show_width", 800)
	self._default_show_height.text = g_IDEProject.project.config:GetConfig("default_show_height", 600)
	self._default_font_path.text = g_IDEProject.project.config:GetConfig("default_font_path", "")
	self._default_font_size.text = g_IDEProject.project.config:GetConfig("default_font_size", 15)
end

function IDEProjectManager:HandleSettingProjectCancel(event)
	self._project_setting_dialog.visible = false
end

function IDEProjectManager:HandleSettingProjectConfirm(event)
	local default_show_width = ALittle.Math_ToInt(self._default_show_width.text)
	if default_show_width == nil or default_show_width <= 0 then
		g_IDETool:ShowNotice("错误", "默认宽度不合法")
		return
	end
	local default_show_height = ALittle.Math_ToInt(self._default_show_height.text)
	if default_show_height == nil or default_show_height <= 0 then
		g_IDETool:ShowNotice("错误", "默认高度不合法")
		return
	end
	local default_font_path = self._default_font_path.text
	local default_font_size = ALittle.Math_ToInt(self._default_font_size.text)
	if default_font_size == nil or default_font_size <= 0 then
		g_IDETool:ShowNotice("错误", "默认字体大小不合法")
		return
	end
	g_IDEProject.project.config:SetConfig("default_show_width", default_show_width)
	g_IDEProject.project.config:SetConfig("default_show_height", default_show_height)
	g_IDEProject.project.config:SetConfig("default_font_path", default_font_path)
	g_IDEProject.project.config:SetConfig("default_font_size", default_font_size)
	g_IDETabManager:SetTabChildWH(default_show_width, default_show_height)
	self._project_setting_dialog.visible = false
end

function IDEProjectManager:HandleProjectItemRightClick(event)
	if self._project_search_menu == nil then
		self._project_search_menu = g_Control:CreateControl("ide_search_project_menu", self)
	end
	self._project_search_menu.x = A_UISystem.mouse_x
	self._project_search_menu.y = A_UISystem.mouse_y
	if self._project_search_menu.y + self._project_search_menu.height > A_UISystem.view_height then
		self._project_search_menu.y = A_UISystem.view_height - self._project_search_menu.height
	end
	self._project_search_menu._user_data = event.target
	A_LayerManager:ShowFromRight(self._project_search_menu)
end

function IDEProjectManager:HandleRightProjectOpen(event)
	A_LayerManager:HideFromRight(self._project_search_menu)
	local target = self._project_search_menu._user_data
	self._project_search_menu._user_data = nil
	local project_name = target.text
	if g_IDETabManager:IsSaveAll() then
		self:OpenProjectImpl(project_name)
		return
	end
	local cancel_callback = Lua.Bind(self.OpenProjectImpl, self, project_name)
	local confirm_callback = Lua.Bind(g_IDETabManager.SaveAllTab, g_IDETabManager)
	g_IDETool:SaveNotice("提示", "是否保存当前项目?", cancel_callback, confirm_callback)
end

function IDEProjectManager:HandleRightProjectRemove(event)
	A_LayerManager:HideFromRight(self._project_search_menu)
	local target = self._project_search_menu._user_data
	self._project_search_menu._user_data = nil
	local project_name = target.text
	if g_IDEProject.project ~= nil and g_IDEProject.project.name == project_name then
		g_IDETool:ShowNotice("提示", "当前项目正在编辑，请先关闭")
		return
	end
	g_IDEProject:RemoveProject(project_name)
	self._project_scroll_screen:RemoveChild(target)
	g_IDECenter:UpdateProjectList()
end

function IDEProjectManager:HandleRightProjectClose(event)
	A_LayerManager:HideFromRight(self._project_search_menu)
	local target = self._project_search_menu._user_data
	self._project_search_menu._user_data = nil
	local project_name = target.text
	if g_IDEProject.project == nil or g_IDEProject.project.name ~= project_name then
		return
	end
	if g_IDETabManager:IsSaveAll() then
		g_IDECenter:CloseProject()
		return
	end
	local cancel_callback = Lua.Bind(g_IDECenter.CloseProject, g_IDECenter)
	local confirm_callback = Lua.Bind(g_IDETabManager.SaveAllTab, g_IDETabManager)
	g_IDETool:SaveNotice("提示", "是否保存当前项目?", cancel_callback, confirm_callback)
end

function IDEProjectManager:RefreshProject()
	if g_IDETabManager:IsSaveAll() then
		g_IDECenter:RefreshProject()
		return
	end
	local cancel_callback = Lua.Bind(g_IDECenter.RefreshProject, g_IDECenter)
	local confirm_callback = Lua.Bind(g_IDETabManager.SaveAllTab, g_IDETabManager)
	g_IDETool:SaveNotice("提示", "是否保存当前项目?", cancel_callback, confirm_callback)
end

function IDEProjectManager:HandleRightProjectRefresh(event)
	A_LayerManager:HideFromRight(self._project_search_menu)
	local target = self._project_search_menu._user_data
	self._project_search_menu._user_data = nil
	local project_name = target.text
	if g_IDEProject.project == nil or g_IDEProject.project.name ~= project_name then
		return
	end
	self:RefreshProject()
end

function IDEProjectManager:ShowExportProject()
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("错误", "当前没有打开的项目")
		return
	end
	if self._export_dialog == nil then
		self._export_dialog = g_Control:CreateControl("ide_export_dialog", self)
		g_IDECenter.dialog_layer:AddChild(self._export_dialog)
		self._main_export_tab:DisableAllCloseButton()
		self._main_export_tab.tab_index = 1
		self._export_windows_official.config_key = "export_windows_official"
		self._export_android_official.config_key = "export_android_official"
		self._export_ios_official.config_key = "export_ios_official"
	end
	self._export_dialog.visible = true
	self._export_windows_official:LoadConfigImpl()
	self._export_android_official:LoadConfigImpl()
	self._export_ios_official:LoadConfigImpl()
end

function IDEProjectManager:RunProject()
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("提示", "当前没有打开的项目")
		return
	end
	os.execute("start ALittleClient.exe " .. g_IDEProject.project.name)
end

g_IDEProjectManager = IDEProjectManager()
