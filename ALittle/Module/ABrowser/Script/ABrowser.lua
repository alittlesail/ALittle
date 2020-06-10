-- ALittle Generate Lua And Do Not Edit This Line!
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1652314301, "ALittle.ModuleShortInfo", {
name = "ALittle.ModuleShortInfo", ns_name = "ALittle", rl_name = "ModuleShortInfo", hash_code = -1652314301,
name_list = {"title","icon","width_type","width_value","height_type","height_value"},
type_list = {"string","string","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1337207166, "ABrowser.ABrowserTabChildUserData", {
name = "ABrowser.ABrowserTabChildUserData", ns_name = "ABrowser", rl_name = "ABrowserTabChildUserData", hash_code = -1337207166,
name_list = {"module_name","module_info"},
type_list = {"string","ALittle.ModuleShortInfo"},
option_map = {}
})
ALittle.RegStruct(444989011, "ALittle.UISelectChangedEvent", {
name = "ALittle.UISelectChangedEvent", ns_name = "ALittle", rl_name = "UISelectChangedEvent", hash_code = 444989011,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

ABrowserMain = Lua.Class(nil, "ABrowser.ABrowserMain")

function ABrowserMain:Ctor()
	___rawset(self, "_module_name_map_tab", {})
	___rawset(self, "_ui_pre", "")
	if ALittle.System_IsPhone() then
		___rawset(self, "_ui_pre", "m_")
	end
end

function ABrowserMain.__getter:ui_pre()
	return self._ui_pre
end

function ABrowserMain.__getter:browser_tab()
	return self._browser_tab
end

function ABrowserMain:Setup(debug)
	local ___COROUTINE = coroutine.running()
	self._debug = debug
	Require(g_ScriptBasePath, "ATool")
	Require(g_ScriptBasePath, "AHomePage")
	Require(g_ScriptBasePath, "AModuleDownload")
	Require(g_ScriptBasePath, "AVersionManager")
	Require(g_ScriptBasePath, "AIMEManager")
	g_ConfigSystem = ALittle.CreateConfigSystem(g_ModuleBasePath .. "/Other/ABrowserSysem.cfg")
	g_ConfigSystemUser = ALittle.CreateConfigSystem(g_ModuleBasePath .. "/ABrowserUser.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(5)
	self._main_layer = ALittle.DisplayLayout(g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	g_LayerGroup:AddChild(self._main_layer)
	self._dialog_layer = ALittle.DisplayLayout(g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	g_LayerGroup:AddChild(self._dialog_layer)
	g_Control:CreateControl(self._ui_pre .. "abrowser_main_scene", self, self._main_layer)
	self._browser_tab.close_post_callback = Lua.Bind(self.HandleTabRemoved, self)
	self._browser_tab:AddEventListener(___all_struct[444989011], self, self.HandleTabChanged)
	g_AIMEManager:Setup()
	g_AHomePage:Setup()
	g_AVersionManager:Setup(debug)
end

function ABrowserMain:HandleAddressLoad(event)
	local object = event.target
	local url_list = ALittle.String_Split(object.text, "/")
	if ALittle.List_MaxN(url_list) < 1 then
		g_ATool:ShowNotice("提示", "地址格式不正确，正确格式为->IP或者域名:端口/账号名/模块名")
		return
	end
	if ALittle.List_MaxN(url_list) == 1 then
		self:LoadModule(url_list[1])
		return
	end
	local account_name = "alittle"
	local module_name = ""
	local ip = "139.159.176.119"
	local port = 1011
	if ALittle.List_MaxN(url_list) == 2 then
		account_name = url_list[1]
		module_name = url_list[2]
	else
		account_name = url_list[2]
		module_name = url_list[3]
		local address_list = ALittle.String_Split(url_list[1], ":")
		if address_list[1] ~= nil and address_list[1] ~= "" then
			ip = address_list[1]
		end
		if address_list[2] ~= nil then
			port = ALittle.Math_ToIntOrZero(address_list[2])
		end
	end
	if ip == nil or port == nil or account_name == nil or module_name == nil then
		g_ATool:ShowNotice("提示", "地址格式不正确，正确格式为->IP或者域名:端口/账号名/模块名")
		return
	end
	self:LoadModule(module_name, ip, port, account_name)
end
ABrowserMain.HandleAddressLoad = Lua.CoWrap(ABrowserMain.HandleAddressLoad)

function ABrowserMain:HandleShowHomeScene(event)
	g_AHomePage:ShowHomeScene()
end

function ABrowserMain:HandleShowMainMenu(event)
	if self._main_menu == nil then
		self._main_menu = g_Control:CreateControl(self._ui_pre .. "abrowser_main_menu", self)
	end
	A_LayerManager:ShowFromRight(self._main_menu)
	local x, y = self._main_menu_button:LocalToGlobal()
	y = y + self._main_menu_button.height
	x = A_UISystem.view_width - self._main_menu.width
	self._main_menu.x = x
	self._main_menu.y = y
end

function ABrowserMain:HandleMainMenuUpdateVersion(event)
	A_LayerManager:HideFromRight(self._main_menu)
	g_AVersionManager:ShowDialog()
end

function ABrowserMain:HandleMainMenuHelp(event)
	A_LayerManager:HideFromRight(self._main_menu)
end

function ABrowserMain:LoadModule(module_name, ip, port, account_name)
	local ___COROUTINE = coroutine.running()
	local tab_child = self._module_name_map_tab[module_name]
	if tab_child ~= nil then
		self._browser_tab.tab = tab_child
		return
	end
	if ip ~= nil and self._debug ~= "debug" then
		g_AModuleDownload:Download(module_name, ip, port, account_name)
	else
		local result = A_ModuleSystem:LoadModule("Module/" .. module_name .. "/", module_name)
		if result == false then
			g_ATool:ShowNotice("错误", "模块加载失败")
		end
	end
end

function ABrowserMain:AddModule(module_name, layer_group, module_info)
	local child = layer_group
	layer_group.width_type = 4
	layer_group.width_value = 0
	layer_group.height_type = 4
	layer_group.height_value = 0
	if module_info ~= nil then
		if module_info.width_type == 1 and module_info.height_type == 1 then
			local screen = g_Control:CreateControl("abrowser_hv_scroll_screen")
			local container = ALittle.DisplayView(g_Control)
			container.width = module_info.width_value
			container.height = module_info.height_value
			screen.container = container
			screen:AddChild(layer_group)
			child = screen
		elseif module_info.width_type == 1 and module_info.height_type ~= 1 then
			local screen = g_Control:CreateControl("abrowser_h_scroll_screen")
			local container = ALittle.DisplayView(g_Control)
			container.width = module_info.width_value
			container.height_type = 4
			container.height_value = 0
			screen.container = container
			screen:AddChild(layer_group)
			child = screen
		elseif module_info.width_type ~= 1 and module_info.height_type == 1 then
			local screen = g_Control:CreateControl("abrowser_v_scroll_screen")
			local container = ALittle.DisplayView(g_Control)
			container.height = module_info.height_value
			container.width_type = 4
			container.width_value = 0
			screen.container = container
			screen:AddChild(layer_group)
			child = screen
		end
	end
	local user_data = {}
	user_data.module_name = module_name
	user_data.module_info = module_info
	child._user_data = user_data
	self._browser_tab:AddChild(child)
	self._browser_tab.tab = child
	self._module_name_map_tab[module_name] = child
	g_AHomePage:SaveModuleScreen(child)
	local title = module_name
	if module_info ~= nil and module_info.title ~= nil then
		title = module_info.title
	end
	self._browser_tab:SetChildText(child, title)
	return true
end

function ABrowserMain:HandleTabChanged(event)
	local object = event.target
	local tab = object.tab
	if tab == nil then
		return
	end
	if tab._user_data == nil then
		return
	end
	local user_data = tab._user_data
end

function ABrowserMain:HandleTabRemoved(child)
	local user_data = child._user_data
	A_ModuleSystem:RemoveModule(user_data.module_name)
	self._module_name_map_tab[user_data.module_name] = nil
end

function ABrowserMain:HandleAddressRightMenu(event)
	local object = event.target
	g_ATool:ShowCopyCutPasteMenu(object.text, object)
end

function ABrowserMain:Shutdown()
	g_AIMEManager:Shutdown()
end

g_ABrowser = ABrowserMain()
