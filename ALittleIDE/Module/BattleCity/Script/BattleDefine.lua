-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-922796193, "BattleCity.BattleMap", {
name = "BattleCity.BattleMap", ns_name = "BattleCity", rl_name = "BattleMap", hash_code = -922796193,
name_list = {"tile_map"},
type_list = {"Map<int,Map<int,int>>"},
option_map = {}
})
ALittle.RegStruct(446914235, "BattleCity.PlayerData", {
name = "BattleCity.PlayerData", ns_name = "BattleCity", rl_name = "PlayerData", hash_code = 446914235,
name_list = {"level","life"},
type_list = {"int","int"},
option_map = {}
})

BattleCity.BrushType = {
	BT_WALL = 1,
	BT_IRON = 2,
	BT_GRASS = 3,
	BT_RIVER = 4,
	BT_CASTLE = 6,
}

BattleCity.DirType = {
	DT_UP = 1,
	DT_DOWN = 2,
	DT_LEFT = 3,
	DT_RIGHT = 4,
}

end