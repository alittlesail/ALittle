-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployClient == nil then _G.DeployClient = {} end
local DeployClient = DeployClient
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.Linear, " extends class:ALittle.Linear is nil")
DeployClient.DPLUIMainMenu = Lua.Class(ALittle.Linear, "DeployClient.DPLUIMainMenu")

function DeployClient.DPLUIMainMenu:TCtor()
	local group = {}
	for index, child in ___ipairs(self._childs) do
		child.group = group
	end
	local version_ip = DeployClient.g_DPLServerConfig:GetConfig("version_ip", "139.159.176.119")
	local version_port = DeployClient.g_DPLServerConfig:GetConfig("version_port", 1100)
	self._version_manager = AUIPlugin.AUIVersionManager(version_ip, version_port, "alittle", "ALittleDeploy")
	if not DeployClient.g_Control.crypt_mode then
		self._version_manager:CheckVersionUpdate()
	end
end

function DeployClient.DPLUIMainMenu:Shutdown()
	self._version_manager:Shutdown()
end

function DeployClient.DPLUIMainMenu:HandleMenuHide(button)
	button.selected = false
end

function DeployClient.DPLUIMainMenu:HandleHelpMenuClick(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("版本检查", Lua.Bind(self._version_manager.ShowDialog, self._version_manager))
	menu:Show(event.target, Lua.Bind(self.HandleMenuHide, self, event.target))
end

end