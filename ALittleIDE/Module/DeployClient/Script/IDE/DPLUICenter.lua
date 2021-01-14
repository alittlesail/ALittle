-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployClient == nil then _G.DeployClient = {} end
local DeployClient = DeployClient
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
DeployClient.DPLUICenter = Lua.Class(ALittle.DisplayLayout, "DeployClient.DPLUICenter")

function DeployClient.DPLUICenter:TCtor()
	self._main_tab.tab_index = 1
	self._main_tab:DisableAllCloseButton()
end

function DeployClient.DPLUICenter.__getter:task_center()
	return self._task_center
end

function DeployClient.DPLUICenter:HandleShortcutKey()
end

end