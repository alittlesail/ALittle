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
ALittleIDE.LinearS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.LinearS")

function ALittleIDE.LinearS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_linear")
end

function ALittleIDE.LinearS:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	local list = ALittleIDE.g_IDEEnum.hv_type
	self:LoadTypeSelectData("type", list)
	self:LoadBoolData("size_fixed", true, ALittleIDE.g_IDEEnum.yn_type)
	self:LoadValueData("gap")
end

function ALittleIDE.LinearS:HandleLinearTypeSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.hv_rtype
	self:TypeSelectChange("type", list, true)
end

function ALittleIDE.LinearS:HandleLinearSizeFixedSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.yn_rtype
	self:TypeSelectChange("size_fixed", list, true)
end

function ALittleIDE.LinearS:HandleLinearGapFOCUSOUT(event)
	self:ValueNumInputChange("gap", false)
end

end