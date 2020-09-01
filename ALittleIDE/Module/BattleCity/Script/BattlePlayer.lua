-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(BattleCity.BattleRole, " extends class:BattleCity.BattleRole is nil")
BattleCity.BattlePlayer = Lua.Class(BattleCity.BattleRole, "BattleCity.BattlePlayer")

function BattleCity.BattlePlayer:LevelUp()
	if self._level >= 4 then
		return
	end
	self._level = self._level + (1)
	self:UpdateSprite(0)
end

end