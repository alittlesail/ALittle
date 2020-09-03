-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.FramePlay, " extends class:ALittle.FramePlay is nil")
BattleCity.BattleItem = Lua.Class(ALittle.FramePlay, "BattleCity.BattleItem")

function BattleCity.BattleItem.__getter:sprite()
	return self._sprite
end

end