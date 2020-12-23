-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.SpriteS, " extends class:ALittleIDE.SpriteS is nil")
ALittleIDE.SpritePlayS = Lua.Class(ALittleIDE.SpriteS, "ALittleIDE.SpritePlayS")

function ALittleIDE.SpritePlayS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_spriteplay")
end

function ALittleIDE.SpritePlayS:LoadNatureBase()
	ALittleIDE.SpriteS.LoadNatureBase(self)
	self:LoadValueData("interval")
end

function ALittleIDE.SpritePlayS:HandleIntervalFOCUSOUT(event)
	self:ValueNumZInputChange("interval", false)
end

end