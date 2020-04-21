
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-784531223, "ABrowser.S2CWebAccountInfo", {
name = "ABrowser.S2CWebAccountInfo", ns_name = "ABrowser", rl_name = "S2CWebAccountInfo", hash_code = -784531223,
name_list = {"account_id","account_name","role_id","role_name","permission_map"},
type_list = {"string","string","string","string","Map<string,bool>"},
option_map = {}
})
ALittle.RegStruct(-1303214865, "ABrowser.S2CWebServerInfo", {
name = "ABrowser.S2CWebServerInfo", ns_name = "ABrowser", rl_name = "S2CWebServerInfo", hash_code = -1303214865,
name_list = {"http_protocol","http_ip","http_port"},
type_list = {"string","string","int"},
option_map = {}
})
ALittle.RegStruct(-684632393, "ABrowser.C2SWebLogin", {
name = "ABrowser.C2SWebLogin", ns_name = "ABrowser", rl_name = "C2SWebLogin", hash_code = -684632393,
name_list = {"account_name","account_pwd"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(-2014336675, "ABrowser.S2CWebLogin", {
name = "ABrowser.S2CWebLogin", ns_name = "ABrowser", rl_name = "S2CWebLogin", hash_code = -2014336675,
name_list = {"result","reason"},
type_list = {"bool","string"},
option_map = {}
})
ALittle.RegStruct(-1066332471, "ABrowser.C2SWebLogout", {
name = "ABrowser.C2SWebLogout", ns_name = "ABrowser", rl_name = "C2SWebLogout", hash_code = -1066332471,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1961622727, "ABrowser.S2CWebLogout", {
name = "ABrowser.S2CWebLogout", ns_name = "ABrowser", rl_name = "S2CWebLogout", hash_code = 1961622727,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1695716690, "ABrowser.S2CWebForceLogout", {
name = "ABrowser.S2CWebForceLogout", ns_name = "ABrowser", rl_name = "S2CWebForceLogout", hash_code = -1695716690,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1989838258, "ABrowser.S2CWebSession", {
name = "ABrowser.S2CWebSession", ns_name = "ABrowser", rl_name = "S2CWebSession", hash_code = -1989838258,
name_list = {"session_id"},
type_list = {"string"},
option_map = {}
})

OPSLogin = Lua.Class(nil, "ABrowser.OPSLogin")

function OPSLogin:Ctor(center, login_ip, login_port, module_name)
	___rawset(self, "_center", center)
	___rawset(self, "_show_loop", nil)
	___rawset(self, "_session_id", "")
	___rawset(self, "_account_info", {})
	self._account_info.permission_map = {}
	___rawset(self, "_server_info", {})
	self._server_info.http_ip = ""
	self._server_info.http_port = 0
	___rawset(self, "_account_name", "")
	___rawset(self, "_account_pwd", "")
	___rawset(self, "_first_login", true)
	___rawset(self, "_is_login", false)
	___rawset(self, "_login_ip", login_ip)
	___rawset(self, "_login_port", login_port)
end

function OPSLogin:Start()
	self._net_client = ALittle.CreateMsgSender(30, false)
	self._net_client:Connect(self._login_ip, self._login_port)
end
OPSLogin.Start = Lua.CoWrap(OPSLogin.Start)

function OPSLogin:Close()
	self._net_client:Close()
	self._net_client = nil
end

function OPSLogin:HideScene()
	if self._scene ~= nil then
		self._scene.visible = false
	end
end

function OPSLogin:ShowScene()
	if self._scene == nil then
		self._scene = g_Control:CreateControl("ops_login", self)
		self._center.main_layer:AddChild(self._scene)
		if self._center.config ~= nil and self._center.config.base ~= nil then
			local icon_path = self._center.config.base.icon_path
			local icon = ALittle.Image(self._center.control)
			icon.x_type = 3
			icon.y_type = 3
			icon.texture_name = icon_path
			if self._center.config.base.icon_width == nil then
				icon.width = self._icon_container.width
			else
				icon.width = self._center.config.base.icon_width
			end
			if self._center.config.base.icon_height == nil then
				icon.height = self._icon_container.height
			else
				icon.height = self._center.config.base.icon_height
			end
			self._icon_container:AddChild(icon)
		end
		self._save_password = self._center.config_user:GetConfig("save_password", false)
		self._var_login = self._center.config_user:GetConfig("var_login", false)
		if self._save_password then
			self._account_name = self._center.config_user:GetConfig("account_name", "")
			self._account_pwd = ALittle.String_DecryptPassword(self._account_name, self._center.config_user:GetConfig("account_pwd", ""))
			if self._account_pwd == nil then
				self._account_pwd = ""
			end
		end
		self._login_account.text = self._account_name
		self._login_password.text = ""
		self._save_password_check.selected = self._save_password
		self._var_login_check.selected = self._var_login
	end
	if self._show_loop ~= nil then
		A_LoopSystem:RemoveUpdater(self._show_loop)
		self._show_loop = nil
	end
	self._scene.visible = true
	self._container.alpha = 0
	self._container.y_value = -50
	if self._show_loop == nil then
		self._show_loop = ALittle.LoopGroup()
		self._show_loop:AddUpdater(ALittle.LoopLinear(self._container, "y_value", 0, 500, 1))
		self._show_loop:AddUpdater(ALittle.LoopLinear(self._container, "alpha", 1, 500, 1))
	end
	A_LoopSystem:AddUpdater(self._show_loop)
	self._center.dialog_logic:Close()
end

function OPSLogin:HandleTabKeyDown(event)
	if self._login_password ~= nil then
		self._login_password.focus = true
	end
end

function OPSLogin:HandleLoginClick(event)
	if self._login_button.disabled then
		return
	end
	self._login_button.disabled = true
	if self._net_client:IsConnected() == false then
		return
	end
	self._account_name = self._login_account.text
	if self._login_password.text ~= "" then
		self._account_pwd = ALittle.String_MD5(self._login_password.text)
	end
	self._save_password = self._save_password_check.selected
	self._var_login = self._var_login_check.selected
	self:LoginImpl()
end

function OPSLogin:LoginImpl()
	if self._net_client == nil then
		return
	end
	self._first_login = false
	local msg = {}
	msg.account_name = self._account_name
	msg.account_pwd = self._account_pwd
	self._net_client:SendMsg(___all_struct[-684632393], msg)
end

function OPSLogin:Logout()
	local msg = {}
	self._net_client:SendMsg(___all_struct[-1066332471], msg)
end

function OPSLogin:CheckPermission(permission)
	if permission == nil then
		return false
	end
	if self._account_info.role_id == "alittle" then
		return true
	end
	return self._account_info.permission_map[permission] == true
end

function OPSLogin:HttpPostRequest(method, param, target_ip, target_port)
local ___COROUTINE = coroutine.running()
	param["__account_id"] = self._account_info.account_id
	param["__session_id"] = self._session_id
	local ip = self._server_info.http_ip
	local port = self._server_info.http_port
	if target_ip ~= nil and target_port ~= nil then
		ip = target_ip
		port = target_port
	end
	local sender = ALittle.CreateHttpSender(ip, port)
	return ALittle.IHttpSender.Invoke(method, sender, ALittle.String_JsonEncode(param))
end

function OPSLogin:HttpFileRequest(method, param, file_path, target_ip, target_port)
local ___COROUTINE = coroutine.running()
	param["__account_id"] = self._account_info.account_id
	param["__session_id"] = self._session_id
	local ip = self._server_info.http_ip
	local port = self._server_info.http_port
	if target_ip ~= nil and target_port ~= nil then
		ip = target_ip
		port = target_port
	end
	local sender = ALittle.CreateHttpFileSender(ip, port, file_path, 0)
	return ALittle.IHttpFileSender.InvokeDownload(method, sender, param)
end

function OPSLogin:Global_HandleNetConnectSucceed()
	if (self._first_login and self._var_login) or (self._login_button ~= nil and self._login_button.disabled) or self._is_login then
		self:LoginImpl()
	end
end

function OPSLogin:Global_HandleNetDisconnect()
	self._center.tool_logic:ShowWeakNotice("网络断开连接，正在重连")
end

function OPSLogin:Global_HandleNetConnectFailed()
	self._center.tool_logic:ShowWeakNotice("当前网络不可用, 正在尝试重连!")
end

function OPSLogin:Global_JsonHandleS2CWebLoginMessage(msg)
	if self._login_button ~= nil then
		self._login_button.disabled = false
	end
	self._is_login = msg.result
	if msg.result == false then
		self._center.tool_logic:ShowWeakNotice(msg.reason)
		return
	end
	if self._save_password then
		self._center.config_user:SetConfig("account_name", self._account_name)
		self._center.config_user:SetConfig("account_pwd", ALittle.String_CryptPassword(self._account_name, self._account_pwd))
	end
	self._center.config_user:SetConfig("save_password", self._save_password)
	self._center.config_user:SetConfig("var_login", self._var_login)
	self:SwitchLoginToMain()
end
OPSLogin.Global_JsonHandleS2CWebLoginMessage = Lua.CoWrap(OPSLogin.Global_JsonHandleS2CWebLoginMessage)

function OPSLogin:Global_JsonHandleS2CWebLogoutMessage(msg)
	self._is_login = false
	if self._login_button ~= nil then
		self._login_password.text = ""
		self._account_name = ""
		self._account_pwd = ""
	end
	self:ShowScene()
	self._center.main_logic:HideScene()
	self._center.main_logic:Clear()
end

function OPSLogin:Global_JsonHandleS2CWebForceLogoutMessage(msg)
	self._is_login = false
	self._center.tool_logic:ShowWeakNotice("您的账号在另一个地方登录")
	if self._login_button ~= nil then
		self._login_password.text = ""
		self._account_name = ""
		self._account_pwd = ""
	end
	self:ShowScene()
	self._center.main_logic:HideScene()
	self._center.main_logic:Clear()
end

function OPSLogin:Global_JsonHandleS2CWebSessionMessage(msg)
	self._session_id = msg.session_id
end

function OPSLogin:Global_JsonHandleS2CWebAccountInfoMessage(msg)
	self._account_info = msg
end

function OPSLogin:Global_JsonHandleS2CWebServerInfoMessage(msg)
	self._server_info = msg
end

function OPSLogin:SwitchLoginToMain()
local ___COROUTINE = coroutine.running()
	local config_md5 = ""
	if ALittle.File_GetFileAttr(self._center.temp_path .. "Client.cfg") ~= nil then
		config_md5 = ALittle.File_MD5(self._center.temp_path .. "Client.cfg")
	end
	local param = {}
	param["config_md5"] = config_md5
	local error, content = self:HttpPostRequest("QCheckOPSConfig", param)
	if error ~= nil then
		self:Logout()
		self._center.tool_logic:ShowWeakNotice("配置文件检查失败，请稍后再试")
		return
	end
	local result, json_object = Lua.TCall(ALittle.String_JsonDecode, content)
	if result ~= nil then
		self:Logout()
		self._center.tool_logic:ShowWeakNotice("配置文件检查失败，请稍后再试")
		return
	end
	if json_object["error"] ~= nil then
		self:Logout()
		self._center.tool_logic:ShowWeakNotice(json_object["error"])
		return
	end
	if json_object["result"] == true then
		self:HideScene()
		self._center.main_logic:ShowScene()
		return
	end
	param = {}
	error = self:HttpFileRequest("QDownloadOPSConfig", param, self._center.temp_path .. "Client.cfg")
	if error ~= nil then
		self:Logout()
		self._center.tool_logic:ShowWeakNotice("配置文件下载失败，请稍后再试")
	else
		self._center:ReloadConfig()
		self:HideScene()
		self._center.main_logic:ShowScene()
	end
end

