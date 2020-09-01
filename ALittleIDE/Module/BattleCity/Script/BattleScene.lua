-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
BattleCity.BattleScene = Lua.Class(ALittle.DisplayLayout, "BattleCity.BattleScene")

function BattleCity.BattleScene:Show(stage)
	self.visible = true
end

end