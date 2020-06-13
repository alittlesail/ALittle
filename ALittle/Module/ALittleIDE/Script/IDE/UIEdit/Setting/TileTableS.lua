-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
TileTableS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.TileTableS")

function TileTableS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_tiletable")
end

function TileTableS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("x_gap")
	self:LoadValueData("y_gap")
	self:LoadValueData("x_start_gap")
	self:LoadValueData("y_start_gap")
	self:LoadValueData("col_count")
end

function TileTableS:HandleXStartGapFOCUSOUT(event)
	self:ValueNumInputChange("x_start_gap", false)
end

function TileTableS:HandleYStartGapFOCUSOUT(event)
	self:ValueNumInputChange("y_start_gap", false)
end

function TileTableS:HandleXGapFOCUSOUT(event)
	self:ValueNumInputChange("x_gap", false)
end

function TileTableS:HandleYGapFOCUSOUT(event)
	self:ValueNumInputChange("y_gap", false)
end

function TileTableS:HandleColCountFOCUSOUT(event)
	self:ValueNumZInputChange("col_count", false)
end

