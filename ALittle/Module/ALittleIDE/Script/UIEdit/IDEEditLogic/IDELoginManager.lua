
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1598450085, "ALittle.QWebLogout", {
name = "ALittle.QWebLogout", ns_name = "ALittle", rl_name = "QWebLogout", hash_code = 1598450085,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-344058063, "ALittle.AWebLogout", {
name = "ALittle.AWebLogout", ns_name = "ALittle", rl_name = "AWebLogout", hash_code = -344058063,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(898014419, "ALittle.QWebLogin", {
name = "ALittle.QWebLogin", ns_name = "ALittle", rl_name = "QWebLogin", hash_code = 898014419,
name_list = {"device_id","client_platform","third_platform","account_name","account_pwd"},
type_list = {"string","string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(-303211063, "ALittle.AWebLogin", {
name = "ALittle.AWebLogin", ns_name = "ALittle", rl_name = "AWebLogin", hash_code = -303211063,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1373673802, "ALittle.QWebChangePassword", {
name = "ALittle.QWebChangePassword", ns_name = "ALittle", rl_name = "QWebChangePassword", hash_code = -1373673802,
name_list = {"old_password","new_password"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(1652964636, "ALittle.AWebChangePassword", {
name = "ALittle.AWebChangePassword", ns_name = "ALittle", rl_name = "AWebChangePassword", hash_code = 1652964636,
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
ALittle.RegStruct(1809602374, "ALittle.S2CWebSession", {
name = "ALittle.S2CWebSession", ns_name = "ALittle", rl_name = "S2CWebSession", hash_code = 1809602374,
name_list = {"session_id"},
type_list = {"string"},
option_map = {}
})
ALittle.RegStruct(-417093574, "ALittle.S2CWebAccountInfo", {
name = "ALittle.S2CWebAccountInfo", ns_name = "ALittle", rl_name = "S2CWebAccountInfo", hash_code = -417093574,
name_list = {"account_id","account_name","role_id","role_name","permission_map"},
type_list = {"string","string","string","string","Map<string,bool>"},
option_map = {}
})
ALittle.RegStruct(-300988017, "ALittle.S2CWebServerInfo", {
name = "ALittle.S2CWebServerInfo", ns_name = "ALittle", rl_name = "S2CWebServerInfo", hash_code = -300988017,
name_list = {"http_ip","http_port"},
type_list = {"string","int"},
option_map = {}
})

IDELoginManager = Lua.Class(nil, "ALittleIDE.IDELoginManager")

function IDELoginManager:Ctor()
	local config = ALittle.CreateConfigSystem(g_ModuleBasePath .. "/Other/Server.cfg")
	___rawset(self, "_logingate_ip", config:GetConfig("logingate_ip", "139.159.176.119"))
	___rawset(self, "_logingate_port", config:GetConfig("logingate_port", 1000))
	___rawset(self, "_version_ip", config:GetConfig("version_ip", "139.159.176.119"))
	___rawset(self, "_version_port", config:GetConfig("version_port", 1011))
	___rawset(self, "_msg_client", ALittle.CreateMsgSender(30, true))
	___rawset(self, "_session_id", "")
	___rawset(self, "_account_info", {})
	___rawset(self, "_server_info", {})
	self._server_info.http_ip = ""
	self._server_info.http_port = 0
	___rawset(self, "_account_name", "")
	___rawset(self, "_account_pwd", "")
	___rawset(self, "_first_login", true)
	___rawset(self, "_is_login", false)
end

function IDELoginManager.__getter:account_name()
	return self._account_name
end

function IDELoginManager:Setup()
	self._save_password = g_IDEConfig:GetConfig("save_password", false)
	self._auto_login = g_IDEConfig:GetConfig("auto_login", false)
	if self._save_password then
		self._account_name = g_IDEConfig:GetConfig("account_name", "")
		self._account_pwd = ALittle.String_DecryptPassword(self._account_name, g_IDEConfig:GetConfig("account_pwd", ""))
	end
	self:Connect()
end

function IDELoginManager:Shutdown()
	if self._msg_client ~= nil then
		self._msg_client:Close()
		self._msg_client = nil
	end
end

function IDELoginManager:Connect()
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
	self._msg_client = ALittle.CreateMsgSender(60, true, Lua.Bind(self.OnDisconnected, self))
	error = self._msg_client:Connect(result.client_ip, result.client_port)
	if error ~= nil then
		self._msg_client = nil
		self:OnConnectFailed()
		A_LoopSystem:AddTimer(5000, Lua.Bind(self.Connect, self))
		return
	end
	self:OnConnectSucceed()
end
IDELoginManager.Connect = Lua.CoWrap(IDELoginManager.Connect)

function IDELoginManager:OnConnectFailed()
	g_IDECenter:AccountInReConnect()
	self:HidePasswordDialog()
end

function IDELoginManager:OnConnectSucceed()
	if (self._first_login and self._auto_login) or (self._login_button ~= nil and self._login_button.disabled) or self._is_login then
		self:LoginImpl()
	else
		g_IDECenter:AccountInLogout()
	end
end

function IDELoginManager:OnDisconnected()
	g_IDECenter:AccountInReConnect()
	self:HidePasswordDialog()
	A_LoopSystem:AddTimer(5000, Lua.Bind(self.Connect, self))
end

function IDELoginManager:ShowLoginDialog()
	if self._login_dialog == nil then
		self._login_dialog = g_Control:CreateControl("ide_account_login_dialog", self)
		g_IDECenter.dialog_layer:AddChild(self._login_dialog)
		self._login_account.text = self._account_name
		self._login_password.text = ""
		self._save_password_check.selected = self._save_password
		self._auto_login_check.selected = self._auto_login
	end
	self._login_dialog.visible = true
end

function IDELoginManager:HideLoginDialog()
	if self._login_dialog == nil then
		return
	end
	self._login_dialog.visible = false
end

function IDELoginManager:ShowPasswordDialog()
	if self._password_dialog == nil then
		self._password_dialog = g_Control:CreateControl("ide_account_password_dialog", self)
		g_IDECenter.dialog_layer:AddChild(self._password_dialog)
	end
	self._password_dialog.visible = true
	self._pas_old_password.text = ""
	self._pas_new_password.text = ""
	self._pas_repeat_password.text = ""
end

function IDELoginManager:HidePasswordDialog()
	if self._password_dialog == nil then
		return
	end
	self._password_dialog.visible = false
end

function IDELoginManager:HandleLoginClick(event)
	if self._login_button.disabled then
		return
	end
	self._login_button.disabled = true
	if self._msg_client:IsConnected() == false then
		return
	end
	self._account_name = self._login_account.text
	if self._login_password.text ~= "" then
		self._account_pwd = ALittle.String_MD5(self._login_password.text)
	end
	self._save_password = self._save_password_check.selected
	self._auto_login = self._auto_login_check.selected
	self:LoginImpl()
end

function IDELoginManager:Logout()
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
	g_IDECenter:AccountInLogout()
end
IDELoginManager.Logout = Lua.CoWrap(IDELoginManager.Logout)

function IDELoginManager:HandleMsgNForceLogout()
	self._is_login = false
	g_IDETool:ShowNotice("提示", "您的账号在另一个地方登录")
	if self._login_button ~= nil then
		self._login_password.text = ""
		self._account_name = ""
		self._account_pwd = ""
	end
	if self._change_pas_confirm ~= nil then
		self._change_pas_confirm.disabled = false
	end
	g_IDECenter:AccountInLogout()
end

function IDELoginManager:HandleMsgNWebSession(msg)
	self._session_id = msg.session_id
end

function IDELoginManager:HandleMsgNWebAccountInfo(msg)
	self._account_info = msg
end

function IDELoginManager:HandleMsgNWebServerInfo(msg)
	self._server_info = msg
end

function IDELoginManager:LoginImpl()
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
		g_IDETool:ShowNotice("提示", error)
		return
	end
	if self._save_password then
		g_IDEConfig:SetConfig("account_name", self._account_name)
		g_IDEConfig:SetConfig("account_pwd", ALittle.String_CryptPassword(self._account_name, self._account_pwd))
	end
	g_IDEConfig:SetConfig("save_password", self._save_password)
	g_IDEConfig:SetConfig("auto_login", self._auto_login)
	self:HideLoginDialog()
	g_IDECenter:AccountInLogin()
end
IDELoginManager.LoginImpl = Lua.CoWrap(IDELoginManager.LoginImpl)

function IDELoginManager:HandlePasswordAlterClick(event)
	local old_password = self._pas_old_password.text
	local new_password = self._pas_new_password.text
	local repeat_password = self._pas_repeat_password.text
	if new_password ~= repeat_password then
		g_IDETool:ShowNotice("提示", "新密码和重复密码不一致")
		return
	end
	self._change_pas_confirm.disabled = true
	local param = {}
	param.old_password = ALittle.String_MD5(old_password)
	param.new_password = ALittle.String_MD5(new_password)
	local error, result = ALittle.IMsgCommon.InvokeRPC(-1373673802, self._msg_client, param)
	self._change_pas_confirm.disabled = false
	if g_IDELoginManager._change_pas_confirm ~= nil then
		g_IDELoginManager._change_pas_confirm.disabled = false
	end
	if error ~= nil then
		g_IDETool:ShowNotice("提示", error)
		return
	end
	g_IDETool:ShowNotice("提示", "密码修改成功")
	g_IDELoginManager:HidePasswordDialog()
end
IDELoginManager.HandlePasswordAlterClick = Lua.CoWrap(IDELoginManager.HandlePasswordAlterClick)

function IDELoginManager:HandlePasswordCancelClick(event)
	self:HidePasswordDialog()
end

function IDELoginManager:IsLogin()
	return self._is_login
end

function IDELoginManager.__getter:account_id()
	return self._account_info.account_id
end

function IDELoginManager.__getter:session_id()
	return self._session_id
end

function IDELoginManager.__getter:http_ip()
	return self._server_info.http_ip
end

function IDELoginManager.__getter:http_port()
	return self._server_info.http_port
end

function IDELoginManager.__getter:version_ip()
	return self._version_ip
end

function IDELoginManager.__getter:version_port()
	return self._version_port
end

g_IDELoginManager = IDELoginManager()
function HandleMsgNForceLogout(client, msg)
	g_IDELoginManager:HandleMsgNForceLogout()
end

ALittle.RegMsgCallback(1391512615, HandleMsgNForceLogout)
function HandleMsgNWebSession(client, msg)
	g_IDELoginManager:HandleMsgNWebSession(msg)
end

ALittle.RegMsgCallback(1809602374, HandleMsgNWebSession)
function HandleMsgNWebAccountInfo(client, msg)
	g_IDELoginManager:HandleMsgNWebAccountInfo(msg)
end

ALittle.RegMsgCallback(-417093574, HandleMsgNWebAccountInfo)
function HandleMsgNWebServerInfo(client, msg)
	g_IDELoginManager:HandleMsgNWebServerInfo(msg)
end

ALittle.RegMsgCallback(-300988017, HandleMsgNWebServerInfo)
