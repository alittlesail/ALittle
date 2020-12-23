-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
ALittleIDE.Grid3S = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.Grid3S")

function ALittleIDE.Grid3S:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_grid3")
end

function ALittleIDE.Grid3S:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	local list = ALittleIDE.g_IDEEnum.hv_type
	self:LoadTypeSelectData("type", list)
	self:LoadValueData("gap")
	self:LoadValueData("up_size")
	self:LoadValueData("down_size")
end

function ALittleIDE.Grid3S:HandleGrid3TypeSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.hv_rtype
	self:TypeSelectChange("type", list, false)
end

function ALittleIDE.Grid3S:HandleGrid3GapFOCUSOUT(event)
	self:ValueNumInputChange("gap", false)
end

function ALittleIDE.Grid3S:HandleGrid3UpFOCUSOUT(event)
	self:ValueNumInputChange("up_size", false)
end

function ALittleIDE.Grid3S:HandleGrid3DownFOCUSOUT(event)
	self:ValueNumInputChange("down_size", false)
end

end