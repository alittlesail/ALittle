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

g_IDEWebLoginManager = nil
IDECenter = Lua.Class(nil, "ALittleIDE.IDECenter")

function IDECenter:Ctor()
end

function IDECenter:Setup()
	local ___COROUTINE = coroutine.running()
	RequireFromPaths(g_ScriptBasePath, "Data/", {"IDEEnum.alittle", "IDEExport.alittle", "IDEProject.alittle", "IDEUIManager.alittle"})
	Require(g_ScriptBasePath, "UIEdit/IDEUICenter")
	g_Control:CreateControl("ide_main_scene", self, g_MainLayer)
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
	g_IDEWebLoginManager = AUIPlugin.AUIWebLoginManager()
	g_IDEWebLoginManager:AddEventListener(___all_struct[-262794256], self, self.HandleAccountInReconnect)
	g_IDEWebLoginManager:AddEventListener(___all_struct[-1848509213], self, self.HandleAccountInLogout)
	g_IDEWebLoginManager:AddEventListener(___all_struct[-420010531], self, self.HandleAccountInLogin)
	g_IDEWebLoginManager:Setup(logingate_ip, logingate_port, g_IDEConfig)
end

function IDECenter:Shutdown()
	g_IDEUICenter:Shutdown()
	self._version_manager:Shutdown()
	g_IDEWebLoginManager:Shutdown()
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
	g_IDEControlManager:ClearControlItem()
	g_IDETabManager:CloseAllTab()
	g_IDEProject:CloseProject()
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
			local control_info = g_IDEProject.project.ui.control_map[name_list[i]]
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

function IDECenter:HandleAccountInLogin(event)
	self._account_login.visible = false
	self._account_dropdown.visible = true
	local data_list = {}
	data_list[1] = "修改密码"
	data_list[2] = "登出"
	self._account_dropdown.data_list = data_list
	self._account_dropdown.text = g_IDEWebLoginManager.account_name
	self._account_icon.x_value = self._account_dropdown.x_value + self._account_dropdown.width + 5
end

function IDECenter:HandleAccountInLogout(event)
	self._account_login.text = "请登录"
	self._account_login.underline = true
	self._account_login.visible = true
	self._account_login.disabled = false
	self._account_dropdown.visible = false
	self._account_icon.x_value = self._account_login.x_value + self._account_login.width + 5
end

function IDECenter:HandleAccountInReconnect(event)
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
