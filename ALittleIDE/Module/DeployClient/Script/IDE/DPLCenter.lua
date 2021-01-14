-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployClient == nil then _G.DeployClient = {} end
local DeployClient = DeployClient
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


DeployClient.DPLCenter = Lua.Class(nil, "DeployClient.DPLCenter")

function DeployClient.DPLCenter:Setup()
	local ___COROUTINE = coroutine.running()
	DeployClient.g_Control:CreateControl("dpl_main_scene", self, DeployClient.g_MainLayer)
	A_UISystem.keydown_callback = Lua.Bind(self.HandleShortcutKey, self)
	A_UISystem.quit_callback = Lua.Bind(self.HandleQuit, self)
end

function DeployClient.DPLCenter:CreateHttpFileSender(file_path)
	local http_ip = DeployClient.g_DPLServerConfig:GetConfig("http_ip", "139.159.176.119")
	local http_port = DeployClient.g_DPLServerConfig:GetConfig("http_port", 1801)
	return ALittle.CreateHttpFileSender(http_ip, http_port, file_path, 0)
end

function DeployClient.DPLCenter:CreateHttpSender()
	local http_ip = DeployClient.g_DPLServerConfig:GetConfig("http_ip", "139.159.176.119")
	local http_port = DeployClient.g_DPLServerConfig:GetConfig("http_port", 1801)
	return ALittle.CreateHttpSender(http_ip, http_port)
end

function DeployClient.DPLCenter:Shutdown()
	if self._account ~= nil then
		self._account:Shutdown()
	end
	if self._main_menu ~= nil then
		self._main_menu:Shutdown()
	end
end

function DeployClient.DPLCenter.__getter:center()
	return self._center
end

function DeployClient.DPLCenter:HandleShortcutKey(mod, sym, scancode)
	if A_UISystem.sym_map[1073741886] then
		return
	end
	if A_UISystem.sym_map[1073741887] then
		return
	end
	if A_UISystem.sym_map[1073741891] then
		return
	end
	if self._center ~= nil then
		self._center:HandleShortcutKey()
	end
end

function DeployClient.DPLCenter:HandleQuit()
	self:HandleQuitImpl()
	return false
end

function DeployClient.DPLCenter:HandleQuitImpl()
	ALittle.System_Exit()
end
DeployClient.DPLCenter.HandleQuitImpl = Lua.CoWrap(DeployClient.DPLCenter.HandleQuitImpl)

DeployClient.g_DPLCenter = DeployClient.DPLCenter()
end