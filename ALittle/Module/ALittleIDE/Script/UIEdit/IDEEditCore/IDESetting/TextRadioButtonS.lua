
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.TextCheckButtonS, " extends class:ALittleIDE.TextCheckButtonS is nil")
TextRadioButtonS = Lua.Class(ALittleIDE.TextCheckButtonS, "ALittleIDE.TextRadioButtonS")

function TextRadioButtonS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_textradiobutton")
end

function TextRadioButtonS:LoadNatureBase()
	TextCheckButtonS.LoadNatureBase(self)
	self:LoadDefaultNilString("group_name")
end

function TextRadioButtonS:HandleGroupNameFOCUSOUT(event)
	self:DefaultNilStringInputChange("group_name", false)
end

function TextRadioButtonS:HandleGroupNameAutoClick(event)
	self._group_name.text = ALittle.Time_GetCurDate() .. ALittle.Math_RandomInt(1, 1000)
	self:DefaultNilStringInputChange("group_name", false)
end

