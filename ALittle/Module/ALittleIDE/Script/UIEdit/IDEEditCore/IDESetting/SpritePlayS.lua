
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


assert(SpriteS, " extends class:SpriteS is nil")
SpritePlayS = ALittle.Class(SpriteS, "ALittleIDE.SpritePlayS")

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

