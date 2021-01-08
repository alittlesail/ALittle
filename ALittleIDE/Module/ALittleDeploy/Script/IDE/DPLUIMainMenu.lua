-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.Linear, " extends class:ALittle.Linear is nil")
ALittleDeploy.DPLUIMainMenu = Lua.Class(ALittle.Linear, "ALittleDeploy.DPLUIMainMenu")

function ALittleDeploy.DPLUIMainMenu:TCtor()
	local group = {}
	for index, child in ___ipairs(self._childs) do
		child.group = group
	end
	local version_ip = ALittleDeploy.g_DPLServerConfig:GetConfig("version_ip", "139.159.176.119")
	local version_port = ALittleDeploy.g_DPLServerConfig:GetConfig("version_port", 1100)
	self._version_manager = AUIPlugin.AUIVersionManager(version_ip, version_port, "alittle", "ALittleDeploy")
	if not ALittleDeploy.g_Control.crypt_mode then
		self._version_manager:CheckVersionUpdate()
	end
end

function ALittleDeploy.DPLUIMainMenu:Shutdown()
	self._version_manager:Shutdown()
end

function ALittleDeploy.DPLUIMainMenu:HandleMenuHide(button)
	button.selected = false
end

function ALittleDeploy.DPLUIMainMenu:HandleHelpMenuClick(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("版本检查", Lua.Bind(self._version_manager.ShowDialog, self._version_manager))
	menu:Show(event.target, Lua.Bind(self.HandleMenuHide, self, event.target))
end

end