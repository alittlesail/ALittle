-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ALittleIDE = ALittleIDE
local ALittle = ALittle
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

ALittleIDE.g_IDEWebLoginManager = nil
assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEUIAccount = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUIAccount")

function ALittleIDE.IDEUIAccount:TCtor()
	local logingate_ip = ALittleIDE.g_IDEServerConfig:GetConfig("logingate_ip", "139.159.176.119")
	local logingate_port = ALittleIDE.g_IDEServerConfig:GetConfig("logingate_port", 1000)
	ALittleIDE.g_IDEWebLoginManager = AUIPlugin.AUIWebLoginManager()
	ALittleIDE.g_IDEWebLoginManager:AddEventListener(___all_struct[-262794256], self, self.HandleAccountInReconnect)
	ALittleIDE.g_IDEWebLoginManager:AddEventListener(___all_struct[-1848509213], self, self.HandleAccountInLogout)
	ALittleIDE.g_IDEWebLoginManager:AddEventListener(___all_struct[-420010531], self, self.HandleAccountInLogin)
	ALittleIDE.g_IDEWebLoginManager:Setup(logingate_ip, logingate_port, ALittleIDE.g_IDEConfig)
end

function ALittleIDE.IDEUIAccount:Shutdown()
	ALittleIDE.g_IDEWebLoginManager:Shutdown()
end

function ALittleIDE.IDEUIAccount:HandleAccountLoginLB(event)
	ALittleIDE.g_IDEWebLoginManager:ShowLoginDialog()
end

function ALittleIDE.IDEUIAccount:HandleAccountInLogin(event)
	self._account_login.visible = false
	self._account_dropdown.visible = true
	local data_list = {}
	data_list[1] = "修改密码"
	data_list[2] = "登出"
	self._account_dropdown.data_list = data_list
	self._account_dropdown.text = ALittleIDE.g_IDEWebLoginManager.account_name
	self._account_icon.x_value = self._account_dropdown.x_value + self._account_dropdown.width + 5
end

function ALittleIDE.IDEUIAccount:HandleAccountInLogout(event)
	self._account_login.text = "请登录"
	self._account_login.underline = true
	self._account_login.visible = true
	self._account_login.disabled = false
	self._account_dropdown.visible = false
	self._account_icon.x_value = self._account_login.x_value + self._account_login.width + 5
end

function ALittleIDE.IDEUIAccount:HandleAccountInReconnect(event)
	self._account_login.text = "正在重连"
	self._account_login.underline = false
	self._account_login.visible = true
	self._account_login.disabled = true
	self._account_dropdown.visible = false
	self._account_icon.x_value = self._account_login.x_value + self._account_login.width + 5
end

function ALittleIDE.IDEUIAccount:HandleAccountDropdownChange(event)
	if event.target.text == "登出" then
		ALittleIDE.g_IDEWebLoginManager:Logout()
	elseif event.target.text == "修改密码" then
		ALittleIDE.g_IDEWebLoginManager:ShowPasswordDialog()
	end
	self._account_dropdown.text = ALittleIDE.g_IDEWebLoginManager.account_name
end

end