
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


assert(TextS, " extends class:TextS is nil")
TextAreaS = ALittle.Class(TextS, "ALittleIDE.TextAreaS")

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

