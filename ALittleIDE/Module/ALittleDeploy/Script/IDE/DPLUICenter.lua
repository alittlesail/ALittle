-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleDeploy.DPLUICenter = Lua.Class(ALittle.DisplayLayout, "ALittleDeploy.DPLUICenter")

function ALittleDeploy.DPLUICenter:TCtor()
	self._main_tab.tab_index = 1
	self._main_tab:DisableAllCloseButton()
end

function ALittleDeploy.DPLUICenter:HandleShortcutKey()
end

end