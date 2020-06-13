-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.SpriteS, " extends class:ALittleIDE.SpriteS is nil")
SpritePlayS = Lua.Class(ALittleIDE.SpriteS, "ALittleIDE.SpritePlayS")

function SpritePlayS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_spriteplay")
end

function SpritePlayS:LoadNatureBase()
	SpriteS.LoadNatureBase(self)
	self:LoadValueData("interval")
end

function SpritePlayS:HandleIntervalFOCUSOUT(event)
	self:ValueNumZInputChange("interval", false)
end

