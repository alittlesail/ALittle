
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

OPSLogin = ALittle.Class(nil, "OPSLogin")

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
	___rawset(self, "_net_client", ALittle.CommonNetClient("ABrowser", self))
	self._net_client:Connect(login_ip, login_port, module_name)
end

function OPSLogin:Close()
	self._net_client:Close()
	self._net_client = nil
end

function OPSLogin:HideScene()
	if self._scene then
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
			icon.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
			icon.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
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
		self._auto_login = self._center.config_user:GetConfig("auto_login", false)
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
		self._auto_login_check.selected = self._auto_login
	end
	if self._show_loop then
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
	if self._login_password then
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
	self._auto_login = self._auto_login_check.selected
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
	self._net_client:SendJson("C2SWebLogin", msg)
end

function OPSLogin:Logout()
	local msg = {}
	self._net_client:SendJson("C2SWebLogout", msg)
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

function OPSLogin:HttpPostRequest(method, param, callback, target_ip, target_port)
	param["__account_id"] = self._account_info.account_id
	param["__session_id"] = self._session_id
	local url = "http://" .. self._server_info.http_ip .. ":" .. self._server_info.http_port .. "/" .. method
	if target_ip ~= nil and target_port ~= nil then
		url = "http://" .. target_ip .. ":" .. target_port .. "/" .. method
	end
	return A_NetSystem:HttpPostRequest(url, Json.encode(param), callback)
end

function OPSLogin:HttpFileRequest(method, param, file_path, callback, target_ip, target_port)
	local url = "http://" .. self._server_info.http_ip .. ":" .. self._server_info.http_port .. "/" .. method
	if target_ip ~= nil and target_port ~= nil then
		url = "http://" .. target_ip .. ":" .. target_port .. "/" .. method
	end
	url = url .. "?__account_id=" .. self._account_info.account_id
	url = url .. "&__session_id=" .. self._session_id
	for k, v in ___pairs(param) do
		url = url .. "&" .. k .. "=" .. v
	end
	return A_NetSystem:HttpFileRequest(url, file_path, true, callback)
end

function OPSLogin:Global_HandleNetConnectSucceed()
	if (self._first_login and self._auto_login) or (self._login_button ~= nil and self._login_button.disabled) or self._is_login then
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
	if self._login_button then
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
	self._center.config_user:SetConfig("auto_login", self._auto_login)
	self:SwitchLoginToMain()
end

function OPSLogin:Global_JsonHandleS2CWebLogoutMessage(msg)
	self._is_login = false
	if self._login_button then
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
	if self._login_button then
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
	local config_md5 = ""
	if ALittle.File_GetFileAttr(self._center.temp_path .. "Client.cfg") then
		config_md5 = ALittle.String_FileMD5(self._center.temp_path .. "Client.cfg")
	end
	local param = {}
	param["config_md5"] = config_md5
	self:HttpPostRequest("QCheckOPSConfig", param, ALittle.Bind(self.HandleCheckOPSConfig, self))
end

function OPSLogin:HandleCheckOPSConfig(result, client)
	if result == false then
		self:Logout()
		self._center.tool_logic:ShowWeakNotice("配置文件检查失败，请稍后再试")
		return
	end
	local result, json_object = pcall(Json.decode, client:GetResponse())
	if result == false then
		self:Logout()
		self._center.tool_logic:ShowWeakNotice("配置文件检查失败，请稍后再试")
		return
	end
	if json_object["error"] then
		self:Logout()
		self._center.tool_logic:ShowWeakNotice(json_object["error"])
		return
	end
	if json_object["result"] then
		self:HideScene()
		self._center.main_logic:ShowScene()
		return
	end
	local param = {}
	self:HttpFileRequest("QDownloadOPSConfig", param, self._center.temp_path .. "Client.cfg", ALittle.Bind(self.HandleDownloadConfig, self))
end

function OPSLogin:HandleDownloadConfig(file, event_type)
	if event_type == ALittle.NetHttp.HTTP_DOWNLOAD_SUCCEED_EVENT then
		self._center:ReloadConfig()
		self:HideScene()
		self._center.main_logic:ShowScene()
	elseif event_type == ALittle.NetHttp.HTTP_DOWNLOAD_FAILED_EVENT then
		self:Logout()
		self._center.tool_logic:ShowWeakNotice("配置文件下载失败，请稍后再试")
	end
end

