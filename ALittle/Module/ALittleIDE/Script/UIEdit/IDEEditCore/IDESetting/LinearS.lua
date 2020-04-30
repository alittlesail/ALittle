-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
LinearS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.LinearS")

function LinearS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_linear")
end

function LinearS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	local list = g_IDEEnum.hv_type
	self:LoadTypeSelectData("type", list)
	self:LoadBoolData("size_fixed", true, g_IDEEnum.yn_type)
	self:LoadValueData("gap")
end

function LinearS:HandleLinearTypeSELECT_CHANGE(event)
	local list = g_IDEEnum.hv_rtype
	self:TypeSelectChange("type", list, true)
end

function LinearS:HandleLinearSizeFixedSELECT_CHANGE(event)
	local list = g_IDEEnum.yn_rtype
	self:TypeSelectChange("size_fixed", list, true)
end

function LinearS:HandleLinearGapFOCUSOUT(event)
	self:ValueNumInputChange("gap", false)
end

