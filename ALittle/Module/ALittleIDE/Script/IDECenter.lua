-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-262794256, "AUIPlugin.AUIWebAccountReconnectEvent", {
name = "AUIPlugin.AUIWebAccountReconnectEvent", ns_name = "AUIPlugin", rl_name = "AUIWebAccountReconnectEvent", hash_code = -262794256,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(-1848509213, "AUIPlugin.AUIWebAccountLogoutEvent", {
name = "AUIPlugin.AUIWebAccountLogoutEvent", ns_name = "AUIPlugin", rl_name = "AUIWebAccountLogoutEvent", hash_code = -1848509213,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(-420010531, "AUIPlugin.AUIWebAccountLoginEvent", {
name = "AUIPlugin.AUIWebAccountLoginEvent", ns_name = "AUIPlugin", rl_name = "AUIWebAccountLoginEvent", hash_code = -420010531,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

IDECenter = Lua.Class(nil, "ALittleIDE.IDECenter")

function IDECenter:Ctor()
end

function IDECenter.__getter:main_layer()
	return self._main_layer
end

function IDECenter.__getter:dialog_layer()
	return self._dialog_layer
end

function IDECenter:Setup()
	local ___COROUTINE = coroutine.running()
	Require(g_ScriptBasePath, "IDEProject")
	Require(g_ScriptBasePath, "UIEdit/IDEUICenter")
	g_IDEConfig = ALittle.CreateConfigSystem("ALittleIDE.cfg")
	g_IDEServerConfig = ALittle.CreateConfigSystem(g_ModuleBasePath .. "/Other/Server.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(5)
	local background_quad = ALittle.Quad(g_Control)
	background_quad.height_type = 4
	background_quad.width_type = 4
	background_quad.alpha = 0.8
	g_LayerGroup:AddChild(background_quad)
	self._phone_status_quad = background_quad
	self._main_layer = ALittle.DisplayLayout(g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	g_LayerGroup:AddChild(self._main_layer)
	self._dialog_layer = ALittle.DisplayLayout(g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	g_LayerGroup:AddChild(self._dialog_layer)
	self:ShowPhoneStatusLine(106, 106, 106)
	g_Control:CreateControl("ide_main_scene", self, self._main_layer)
	self:UpdateProjectList()
	g_IDEUICenter:Setup(self._edit_container)
	g_IDEUICenter:Show()
	A_UISystem.keydown_callback = Lua.Bind(self.HandleShortcutKey, self)
	g_IDEProjectManager:OpenLastProject()
	local version_ip = g_IDEServerConfig:GetConfig("version_ip", "139.159.176.119")
	local version_port = g_IDEServerConfig:GetConfig("version_port", 1011)
	self._version_manager = AUIPlugin.AUIVersionManager(version_ip, version_port, "alittle", "ALittleIDE")
	if not g_Control.crypt_mode then
		self._version_manager:CheckVersionUpdate()
	end
	local logingate_ip = g_IDEServerConfig:GetConfig("logingate_ip", "139.159.176.119")
	local logingate_port = g_IDEServerConfig:GetConfig("logingate_port", 1000)
	g_IDEWebLoginManager:AddEventListener(___all_struct[-262794256], self, self.AccountInReconnect)
	g_IDEWebLoginManager:AddEventListener(___all_struct[-1848509213], self, self.AccountInLogout)
	g_IDEWebLoginManager:AddEventListener(___all_struct[-420010531], self, self.AccountInLogin)
	g_IDEWebLoginManager:Setup(logingate_ip, logingate_port, g_IDEConfig)
end

function IDECenter:Shutdown()
	g_IDEUICenter:Shutdown()
	self._version_manager:Shutdown()
end

function IDECenter:ShowPhoneStatusLine(r, g, b)
	local background_quad = self._phone_status_quad
	background_quad.red = r / 255
	background_quad.green = g / 255
	background_quad.blue = b / 255
	background_quad.visible = true
	local status_h = ALittle.System_GetStatusBarHeight()
	self._main_layer.height_value = status_h
	self._main_layer.y = status_h
	self._dialog_layer.height_value = status_h
	self._dialog_layer.y = status_h
end

function IDECenter:HidePhoneStatusLine()
	local background_quad = self._phone_status_quad
	background_quad.visible = false
	self._main_layer.height_value = 0
	self._main_layer.y = 0
	self._dialog_layer.height_value = 0
	self._dialog_layer.y = 0
end

function IDECenter:HandlePeojectSelectChange(event)
	local name = ""
	if g_IDEProject.project ~= nil then
		name = g_IDEProject.project.name
	end
	local new_name = event.target.text
	if new_name == name then
		return
	end
	if g_IDETabManager:IsSaveAll() then
		g_IDEProjectManager:OpenProjectImpl(new_name)
		return
	end
	event.target.text = name
	local result = g_AUITool:SaveNotice("提示", "是否保存当前项目?")
	if result == "YES" then
		g_IDETabManager:SaveAllTab()
	end
	g_IDEProjectManager:OpenProjectImpl(new_name)
end
IDECenter.HandlePeojectSelectChange = Lua.CoWrap(IDECenter.HandlePeojectSelectChange)

function IDECenter:UpdateProjectList()
	if self._current_project_name == nil then
		return
	end
	local data_list = {}
	local data_list_count = 0
	local project_map = g_IDEConfig:GetConfig("project_map", {})
	for k, v in ___pairs(project_map) do
		data_list_count = data_list_count + 1
		data_list[data_list_count] = v
	end
	ALittle.List_Sort(data_list)
	local text = self._current_project_name.text
	self._current_project_name.data_list = data_list
	self._current_project_name.text = text
end

function IDECenter:OpenProject(name)
	if name == "" then
		self._current_project_name.text = "当前没有打开的项目"
	else
		self._current_project_name.text = name
	end
	g_IDEProject:OpenProject(name)
	self:UpdateProjectList()
end

function IDECenter:CloseProject()
	self._current_project_name.text = "当前没有打开的项目"
	g_IDEImageManager:ClearImageItem()
	g_IDEControlManager:ClearControlItem()
	g_IDETabManager:CloseAllTab()
	g_IDEProject:CloseProject()
	g_IDEAttrImageDialog:Close()
end

function IDECenter:RefreshProject()
	if g_IDEProject.project == nil then
		return
	end
	local project_name = g_IDEProject.project.name
	local name_list = g_IDETabManager:GetTabNameList()
	local tab_index = g_IDETabManager:GetCurTabIndex()
	self:CloseProject()
	self:OpenProject(project_name)
	local count = ALittle.List_MaxN(name_list)
	if count > 0 then
		local i = count
		while true do
			if not(i >= 1) then break end
			local control_info = g_IDEProject.project.control_map[name_list[i]]
			if control_info ~= nil then
				g_IDETabManager:StartEditControlBySelect(control_info.name, control_info.info)
			end
			i = i+(-1)
		end
		g_IDETabManager:SetCurTabIndex(tab_index)
	end
end

function IDECenter:HandleFileMenuClick(event)
	g_IDEMainMenu:ShowFileMenu(event.target)
end

function IDECenter:HandleEditMenuClick(event)
	g_IDEMainMenu:ShowEditMenu(event.target)
end

function IDECenter:HandleToolMenuClick(event)
	g_IDEMainMenu:ShowToolMenu(event.target)
end

function IDECenter:HandleVersionMenuClick(event)
	self._version_manager:ShowDialog()
end

function IDECenter:HandleRunMenuClick(event)
	g_IDEProjectManager:RunProject()
end

function IDECenter:HandleShortcutKey(mod, sym, scancode)
	if A_UISystem.sym_map[1073741886] then
		g_IDEProjectManager:RunProject()
		return
	end
	g_IDEUICenter:HandleShortcutKey()
end

function IDECenter:HandleAccountLoginLB(event)
	g_IDEWebLoginManager:ShowLoginDialog()
end

function IDECenter:AccountInLogin(event)
	self._account_login.visible = false
	self._account_dropdown.visible = true
	local data_list = {}
	data_list[1] = "修改密码"
	data_list[2] = "登出"
	self._account_dropdown.data_list = data_list
	self._account_dropdown.text = g_IDEWebLoginManager.account_name
	self._account_icon.x_value = self._account_dropdown.x_value + self._account_dropdown.width + 5
end

function IDECenter:AccountInLogout(event)
	self._account_login.text = "请登录"
	self._account_login.underline = true
	self._account_login.visible = true
	self._account_login.disabled = false
	self._account_dropdown.visible = false
	self._account_icon.x_value = self._account_login.x_value + self._account_login.width + 5
end

function IDECenter:AccountInReconnect(event)
	self._account_login.text = "正在重连"
	self._account_login.underline = false
	self._account_login.visible = true
	self._account_login.disabled = true
	self._account_dropdown.visible = false
	self._account_icon.x_value = self._account_login.x_value + self._account_login.width + 5
end

function IDECenter:HandleAccountDropdownChange(event)
	if event.target.text == "登出" then
		g_IDEWebLoginManager:Logout()
	elseif event.target.text == "修改密码" then
		g_IDEWebLoginManager:ShowPasswordDialog()
	end
	self._account_dropdown.text = g_IDEWebLoginManager.account_name
end

g_IDECenter = IDECenter()
