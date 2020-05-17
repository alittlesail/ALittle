-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
Grid3S = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.Grid3S")

function Grid3S:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_grid3")
end

function Grid3S:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	local list = g_IDEEnum.hv_type
	self:LoadTypeSelectData("type", list)
	self:LoadValueData("gap")
	self:LoadValueData("up_size")
	self:LoadValueData("down_size")
end

function Grid3S:HandleGrid3TypeSELECT_CHANGE(event)
	local list = g_IDEEnum.hv_rtype
	self:TypeSelectChange("type", list, false)
end

function Grid3S:HandleGrid3GapFOCUSOUT(event)
	self:ValueNumInputChange("gap", false)
end

function Grid3S:HandleGrid3UpFOCUSOUT(event)
	self:ValueNumInputChange("up_size", false)
end

function Grid3S:HandleGrid3DownFOCUSOUT(event)
	self:ValueNumInputChange("down_size", false)
end

