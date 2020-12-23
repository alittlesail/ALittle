-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.TextS, " extends class:ALittleIDE.TextS is nil")
ALittleIDE.TextAreaS = Lua.Class(ALittleIDE.TextS, "ALittleIDE.TextAreaS")

function ALittleIDE.TextAreaS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_textarea")
end

function ALittleIDE.TextAreaS:LoadNatureBase()
	ALittleIDE.TextS.LoadNatureBase(self)
	self:LoadTypeSelectData("halign", ALittleIDE.g_IDEEnum.HALIGN_type)
	self:LoadTypeSelectData("valign", ALittleIDE.g_IDEEnum.VALIGN_type)
end

function ALittleIDE.TextAreaS:HandleHalignSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.HALIGN_rtype
	self:TypeSelectChange("halign", list, false)
end

function ALittleIDE.TextAreaS:HandleValignSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.VALIGN_rtype
	self:TypeSelectChange("valign", list, false)
end

end