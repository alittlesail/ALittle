-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.TextS, " extends class:ALittleIDE.TextS is nil")
TextAreaS = Lua.Class(ALittleIDE.TextS, "ALittleIDE.TextAreaS")

function TextAreaS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_textarea")
end

function TextAreaS:LoadNatureBase()
	TextS.LoadNatureBase(self)
	self:LoadTypeSelectData("halign", g_IDEEnum.HALIGN_type)
	self:LoadTypeSelectData("valign", g_IDEEnum.VALIGN_type)
end

function TextAreaS:HandleHalignSELECT_CHANGE(event)
	local list = g_IDEEnum.HALIGN_rtype
	self:TypeSelectChange("halign", list, false)
end

function TextAreaS:HandleValignSELECT_CHANGE(event)
	local list = g_IDEEnum.VALIGN_rtype
	self:TypeSelectChange("valign", list, false)
end

