-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1848509213, "AUIPlugin.AUIWebAccountLogoutEvent", {
name = "AUIPlugin.AUIWebAccountLogoutEvent", ns_name = "AUIPlugin", rl_name = "AUIWebAccountLogoutEvent", hash_code = -1848509213,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(1809602374, "ALittle.S2CWebSession", {
name = "ALittle.S2CWebSession", ns_name = "ALittle", rl_name = "S2CWebSession", hash_code = 1809602374,
name_list = {"session_id"},
type_list = {"string"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(1652964636, "ALittle.AWebChangePassword", {
name = "ALittle.AWebChangePassword", ns_name = "ALittle", rl_name = "AWebChangePassword", hash_code = 1652964636,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1598450085, "ALittle.QWebLogout", {
name = "ALittle.QWebLogout", ns_name = "ALittle", rl_name = "QWebLogout", hash_code = 1598450085,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1391512615, "ALittle.S2CWebForceLogout", {
name = "ALittle.S2CWebForceLogout", ns_name = "ALittle", rl_name = "S2CWebForceLogout", hash_code = 1391512615,
name_list = {"reason"},
type_list = {"string"},
option_map = {}
})
ALittle.RegStruct(-1373673802, "ALittle.QWebChangePassword", {
name = "ALittle.QWebChangePassword", ns_name = "ALittle", rl_name = "QWebChangePassword", hash_code = -1373673802,
name_list = {"old_password","new_password"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(898014419, "ALittle.QWebLogin", {
name = "ALittle.QWebLogin", ns_name = "ALittle", rl_name = "QWebLogin", hash_code = 898014419,
name_list = {"device_id","client_platform","third_platform","account_name","account_pwd"},
type_list = {"string","string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(-420010531, "AUIPlugin.AUIWebAccountLoginEvent", {
name = "AUIPlugin.AUIWebAccountLoginEvent", ns_name = "AUIPlugin", rl_name = "AUIWebAccountLoginEvent", hash_code = -420010531,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(-417093574, "ALittle.S2CWebAccountInfo", {
name = "ALittle.S2CWebAccountInfo", ns_name = "ALittle", rl_name = "S2CWebAccountInfo", hash_code = -417093574,
name_list = {"account_id","account_name","role_id","role_name","permission_map"},
type_list = {"string","string","string","string","Map<string,bool>"},
option_map = {}
})
ALittle.RegStruct(-344058063, "ALittle.AWebLogout", {
name = "ALittle.AWebLogout", ns_name = "ALittle", rl_name = "AWebLogout", hash_code = -344058063,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-303211063, "ALittle.AWebLogin", {
name = "ALittle.AWebLogin", ns_name = "ALittle", rl_name = "AWebLogin", hash_code = -303211063,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-300988017, "ALittle.S2CWebServerInfo", {
name = "ALittle.S2CWebServerInfo", ns_name = "ALittle", rl_name = "S2CWebServerInfo", hash_code = -300988017,
name_list = {"http_ip","http_port"},
type_list = {"string","int"},
option_map = {}
})
ALittle.RegStruct(-262794256, "AUIPlugin.AUIWebAccountReconnectEvent", {
name = "AUIPlugin.AUIWebAccountReconnectEvent", ns_name = "AUIPlugin", rl_name = "AUIWebAccountReconnectEvent", hash_code = -262794256,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

assert(ALittle.EventDispatcher, " extends class:ALittle.EventDispatcher is nil")
AUIPlugin.AUIWebLoginManager = Lua.Class(ALittle.EventDispatcher, "AUIPlugin.AUIWebLoginManager")

function AUIPlugin.AUIWebLoginManager.__getter:msg_client()
	return self._msg_client
end

function AUIPlugin.AUIWebLoginManager:Setup(ip, port, is_logingate, config)
	self._logingate_ip = ip
	self._logingate_port = port
	self._is_logingate = is_logingate
	self._config = config
	self._session_id = ""
	self._account_info = {}
	self._server_info = {}
	self._server_info.http_ip = ""
	self._server_info.http_port = 0
	self._account_name = ""
	self._account_pwd = ""
	self._first_login = true
	self._is_login = false
	self._save_password = config:GetConfig("save_password", false)
	self._auto_login = config:GetConfig("auto_login", false)
	if self._save_password then
		self._account_name = config:GetConfig("account_name", "")
		self._account_pwd = ALittle.String_DecryptPassword(self._account_name, config:GetConfig("account_pwd", ""))
	end
	self:Connect()
end

function AUIPlugin.AUIWebLoginManager:Shutdown()
	if self._msg_client ~= nil then
		self._msg_client:Close()
		self._msg_client = nil
	end
	if self._login_dialog ~= nil then
		A_LayerManager:RemoveFromModal(self._login_dialog)
		self._login_dialog = nil
	end
	if self._password_dialog ~= nil then
		A_LayerManager:RemoveFromModal(self._password_dialog)
		self._password_dialog = nil
	end
end

function AUIPlugin.AUIWebLoginManager:Connect()
	local client_ip = self._logingate_ip
	local client_port = self._logingate_port
	if self._is_logingate then
		local param = {}
		param.route_type = 3
		local client = ALittle.CreateHttpSender(self._logingate_ip, self._logingate_port)
		local error, result = ALittle.IHttpSender.Invoke("GatewayServer.QRouteInfo", client, param)
		if error ~= nil then
			ALittle.Log(error)
			self._msg_client = nil
			self:OnConnectFailed()
			A_LoopSystem:AddTimer(5000, Lua.Bind(self.Connect, self))
			return
		end
		if result.client_ip == nil or result.client_ip == "" or result.client_port == nil then
			self._msg_client = nil
			self:OnConnectFailed()
			A_LoopSystem:AddTimer(5000, Lua.Bind(self.Connect, self))
			return
		end
		client_ip = result.client_ip
		client_port = result.client_port
	end
	self._msg_client = ALittle.CreateMsgSender(60, true, Lua.Bind(self.OnDisconnected, self))
	self._msg_client._user_data = self
	local error = self._msg_client:Connect(client_ip, client_port)
	if error ~= nil then
		self._msg_client = nil
		self:OnConnectFailed()
		A_LoopSystem:AddTimer(5000, Lua.Bind(self.Connect, self))
		return
	end
	self:OnConnectSucceed()
end
AUIPlugin.AUIWebLoginManager.Connect = Lua.CoWrap(AUIPlugin.AUIWebLoginManager.Connect)

function AUIPlugin.AUIWebLoginManager:OnConnectFailed()
	self:DispatchEvent(___all_struct[-262794256], {})
	self:HidePasswordDialog()
end

function AUIPlugin.AUIWebLoginManager:OnConnectSucceed()
	if (self._first_login and self._auto_login) or (self._login_button ~= nil and self._login_button.disabled) or self._is_login then
		self:LoginImpl()
	else
		self:DispatchEvent(___all_struct[-1848509213], {})
	end
end

function AUIPlugin.AUIWebLoginManager:OnDisconnected()
	self:DispatchEvent(___all_struct[-262794256], {})
	self:HidePasswordDialog()
	A_LoopSystem:AddTimer(5000, Lua.Bind(self.Connect, self))
end

function AUIPlugin.AUIWebLoginManager:ShowLoginDialog()
	if self._login_dialog == nil then
		self._login_dialog = AUIPlugin.g_Control:CreateControl("account_login_dialog", self)
		A_LayerManager:AddToModal(self._login_dialog)
		self._login_account.text = self._account_name
		self._login_password.text = ""
		self._save_password_check.selected = self._save_password
		self._auto_login_check.selected = self._auto_login
	end
	self._login_dialog.visible = true
	self._login_account:DelayFocus()
end

function AUIPlugin.AUIWebLoginManager:HideLoginDialog()
	if self._login_dialog == nil then
		return
	end
	self._login_dialog.visible = false
end

function AUIPlugin.AUIWebLoginManager:ShowPasswordDialog()
	if self._password_dialog == nil then
		self._password_dialog = AUIPlugin.g_Control:CreateControl("account_password_dialog", self)
		A_LayerManager:AddToModal(self._password_dialog)
	end
	self._password_dialog.visible = true
	self._pas_old_password.focus = true
	self._pas_old_password.text = ""
	self._pas_new_password.text = ""
	self._pas_repeat_password.text = ""
end

function AUIPlugin.AUIWebLoginManager:HidePasswordDialog()
	if self._password_dialog == nil then
		return
	end
	self._password_dialog.visible = false
end

function AUIPlugin.AUIWebLoginManager:HandleLoginClick(event)
	if self._login_button.disabled then
		return
	end
	self._login_button.disabled = true
	if self._msg_client:IsConnected() == false then
		return
	end
	self._account_name = self._login_account.text
	if self._login_password.text ~= "" then
		self._account_pwd = ALittle.String_Md5(self._login_password.text)
	end
	self._save_password = self._save_password_check.selected
	self._auto_login = self._auto_login_check.selected
	self:LoginImpl()
end

function AUIPlugin.AUIWebLoginManager:HandleLoginAccountTabKey(event)
	self._login_password.focus = true
end

function AUIPlugin.AUIWebLoginManager:HandleLoginPasswordTabKey(event)
	self._login_account.focus = true
end

function AUIPlugin.AUIWebLoginManager:HandleOldPasswordTabKey(event)
	self._pas_new_password.focus = true
end

function AUIPlugin.AUIWebLoginManager:HandleNewPasswordTabKey(event)
	self._pas_repeat_password.focus = true
end

function AUIPlugin.AUIWebLoginManager:Logout()
	if self._msg_client == nil then
		return
	end
	local param = {}
	local error, result = ALittle.IMsgCommon.InvokeRPC(1598450085, self._msg_client, param)
	if error ~= nil then
		ALittle.Error(error)
		return
	end
	self._is_login = false
	if self._login_button ~= nil then
		self._login_password.text = ""
		self._account_name = ""
		self._account_pwd = ""
	end
	if self._change_pas_confirm ~= nil then
		self._change_pas_confirm.disabled = false
	end
	self:DispatchEvent(___all_struct[-1848509213], {})
end
AUIPlugin.AUIWebLoginManager.Logout = Lua.CoWrap(AUIPlugin.AUIWebLoginManager.Logout)

function AUIPlugin.AUIWebLoginManager:HandleMsgNForceLogout()
	self._is_login = false
	g_AUITool:ShowNotice("提示", "您的账号在另一个地方登录")
	if self._login_button ~= nil then
		self._login_password.text = ""
		self._account_name = ""
		self._account_pwd = ""
	end
	if self._change_pas_confirm ~= nil then
		self._change_pas_confirm.disabled = false
	end
	self:DispatchEvent(___all_struct[-1848509213], {})
end

function AUIPlugin.AUIWebLoginManager:HandleMsgNWebSession(msg)
	self._session_id = msg.session_id
end

function AUIPlugin.AUIWebLoginManager:HandleMsgNWebAccountInfo(msg)
	self._account_info = msg
end

function AUIPlugin.AUIWebLoginManager:HandleMsgNWebServerInfo(msg)
	self._server_info = msg
end

function AUIPlugin.AUIWebLoginManager:LoginImpl()
	if self._msg_client == nil then
		return
	end
	self._first_login = false
	local param = {}
	param.device_id = ""
	param.third_platform = "account"
	param.client_platform = ALittle.System_GetPlatform()
	param.account_name = self._account_name
	param.account_pwd = self._account_pwd
	local error, result = ALittle.IMsgCommon.InvokeRPC(898014419, self._msg_client, param)
	if self._login_button ~= nil then
		self._login_button.disabled = false
	end
	self._is_login = (error == nil)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
		return
	end
	if self._save_password then
		self._config:SetConfig("account_name", self._account_name)
		self._config:SetConfig("account_pwd", ALittle.String_CryptPassword(self._account_name, self._account_pwd))
	end
	self._config:SetConfig("save_password", self._save_password)
	self._config:SetConfig("auto_login", self._auto_login)
	self:HideLoginDialog()
	self:DispatchEvent(___all_struct[-420010531], {})
end
AUIPlugin.AUIWebLoginManager.LoginImpl = Lua.CoWrap(AUIPlugin.AUIWebLoginManager.LoginImpl)

function AUIPlugin.AUIWebLoginManager:HandlePasswordAlterClick(event)
	local old_password = self._pas_old_password.text
	local new_password = self._pas_new_password.text
	local repeat_password = self._pas_repeat_password.text
	if new_password ~= repeat_password then
		g_AUITool:ShowNotice("提示", "新密码和重复密码不一致")
		return
	end
	self._change_pas_confirm.disabled = true
	local param = {}
	param.old_password = ALittle.String_Md5(old_password)
	param.new_password = ALittle.String_Md5(new_password)
	local error, result = ALittle.IMsgCommon.InvokeRPC(-1373673802, self._msg_client, param)
	self._change_pas_confirm.disabled = false
	if self._change_pas_confirm ~= nil then
		self._change_pas_confirm.disabled = false
	end
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
		return
	end
	g_AUITool:ShowNotice("提示", "密码修改成功")
	self:HidePasswordDialog()
end
AUIPlugin.AUIWebLoginManager.HandlePasswordAlterClick = Lua.CoWrap(AUIPlugin.AUIWebLoginManager.HandlePasswordAlterClick)

function AUIPlugin.AUIWebLoginManager:HandlePasswordCancelClick(event)
	self:HidePasswordDialog()
end

function AUIPlugin.AUIWebLoginManager:IsLogin()
	return self._is_login
end

function AUIPlugin.AUIWebLoginManager.__getter:account_name()
	return self._account_name
end

function AUIPlugin.AUIWebLoginManager.__getter:account_id()
	return self._account_info.account_id
end

function AUIPlugin.AUIWebLoginManager.__getter:session_id()
	return self._session_id
end

function AUIPlugin.AUIWebLoginManager.__getter:http_ip()
	return self._server_info.http_ip
end

function AUIPlugin.AUIWebLoginManager.__getter:http_port()
	return self._server_info.http_port
end

function AUIPlugin.AUIWebLoginManager.__getter:version_ip()
	return self._version_ip
end

function AUIPlugin.AUIWebLoginManager.__getter:version_port()
	return self._version_port
end

function AUIPlugin.HandleMsgNForceLogout(client, msg)
	local manager = client._user_data
	if manager == nil then
		return
	end
	manager:HandleMsgNForceLogout()
end

ALittle.RegMsgCallback(1391512615, AUIPlugin.HandleMsgNForceLogout)
function AUIPlugin.HandleMsgNWebSession(client, msg)
	local manager = client._user_data
	if manager == nil then
		return
	end
	manager:HandleMsgNWebSession(msg)
end

ALittle.RegMsgCallback(1809602374, AUIPlugin.HandleMsgNWebSession)
function AUIPlugin.HandleMsgNWebAccountInfo(client, msg)
	local manager = client._user_data
	if manager == nil then
		return
	end
	manager:HandleMsgNWebAccountInfo(msg)
end

ALittle.RegMsgCallback(-417093574, AUIPlugin.HandleMsgNWebAccountInfo)
function AUIPlugin.HandleMsgNWebServerInfo(client, msg)
	local manager = client._user_data
	if manager == nil then
		return
	end
	manager:HandleMsgNWebServerInfo(msg)
end

ALittle.RegMsgCallback(-300988017, AUIPlugin.HandleMsgNWebServerInfo)
end