-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
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
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
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
ALittle.RegStruct(-262794256, "AUIPlugin.AUIWebAccountReconnectEvent", {
name = "AUIPlugin.AUIWebAccountReconnectEvent", ns_name = "AUIPlugin", rl_name = "AUIWebAccountReconnectEvent", hash_code = -262794256,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

ALittleDeploy.g_DPLWebLoginManager = nil
assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleDeploy.DPLUIAccount = Lua.Class(ALittle.DisplayLayout, "ALittleDeploy.DPLUIAccount")

function ALittleDeploy.DPLUIAccount:TCtor()
	local client_ip = ALittleDeploy.g_DPLServerConfig:GetConfig("client_ip", "139.159.176.119")
	local client_port = ALittleDeploy.g_DPLServerConfig:GetConfig("client_port", 1800)
	ALittleDeploy.g_DPLWebLoginManager = AUIPlugin.AUIWebLoginManager()
	ALittleDeploy.g_DPLWebLoginManager:AddEventListener(___all_struct[-262794256], self, self.HandleAccountInReconnect)
	ALittleDeploy.g_DPLWebLoginManager:AddEventListener(___all_struct[-1848509213], self, self.HandleAccountInLogout)
	ALittleDeploy.g_DPLWebLoginManager:AddEventListener(___all_struct[-420010531], self, self.HandleAccountInLogin)
	ALittleDeploy.g_DPLWebLoginManager:Setup(client_ip, client_port, false, ALittleDeploy.g_DPLConfig)
end

function ALittleDeploy.DPLUIAccount:Shutdown()
	ALittleDeploy.g_DPLWebLoginManager:Shutdown()
end

function ALittleDeploy.DPLUIAccount:HandleAccountLoginLB(event)
	ALittleDeploy.g_DPLWebLoginManager:ShowLoginDialog()
end

function ALittleDeploy.DPLUIAccount:HandleAccountInLogin(event)
	self._account_login.visible = false
	self._account_dropdown.visible = true
	local data_list = {}
	data_list[1] = "修改密码"
	data_list[2] = "登出"
	self._account_dropdown.data_list = data_list
	self._account_dropdown.text = ALittleDeploy.g_DPLWebLoginManager.account_name
	self._account_icon.x_value = self._account_dropdown.x_value + self._account_dropdown.width + 5
end

function ALittleDeploy.DPLUIAccount:HandleAccountInLogout(event)
	self._account_login.text = "请登录"
	self._account_login.underline = true
	self._account_login.visible = true
	self._account_login.disabled = false
	self._account_dropdown.visible = false
	self._account_icon.x_value = self._account_login.x_value + self._account_login.width + 5
end

function ALittleDeploy.DPLUIAccount:HandleAccountInReconnect(event)
	self._account_login.text = "正在重连"
	self._account_login.underline = false
	self._account_login.visible = true
	self._account_login.disabled = true
	self._account_dropdown.visible = false
	self._account_icon.x_value = self._account_login.x_value + self._account_login.width + 5
end

function ALittleDeploy.DPLUIAccount:HandleAccountDropdownChange(event)
	if event.target.text == "登出" then
		ALittleDeploy.g_DPLWebLoginManager:Logout()
	elseif event.target.text == "修改密码" then
		ALittleDeploy.g_DPLWebLoginManager:ShowPasswordDialog()
	end
	self._account_dropdown.text = ALittleDeploy.g_DPLWebLoginManager.account_name
end

end