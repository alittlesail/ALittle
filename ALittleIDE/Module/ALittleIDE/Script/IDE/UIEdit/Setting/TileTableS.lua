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
ALittleIDE.TileTableS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.TileTableS")

function ALittleIDE.TileTableS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_tiletable")
end

function ALittleIDE.TileTableS:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("x_gap")
	self:LoadValueData("y_gap")
	self:LoadValueData("x_start_gap")
	self:LoadValueData("y_start_gap")
	self:LoadValueData("col_count")
end

function ALittleIDE.TileTableS:HandleXStartGapFOCUSOUT(event)
	self:ValueNumInputChange("x_start_gap", false)
end

function ALittleIDE.TileTableS:HandleYStartGapFOCUSOUT(event)
	self:ValueNumInputChange("y_start_gap", false)
end

function ALittleIDE.TileTableS:HandleXGapFOCUSOUT(event)
	self:ValueNumInputChange("x_gap", false)
end

function ALittleIDE.TileTableS:HandleYGapFOCUSOUT(event)
	self:ValueNumInputChange("y_gap", false)
end

function ALittleIDE.TileTableS:HandleColCountFOCUSOUT(event)
	self:ValueNumZInputChange("col_count", false)
end

end