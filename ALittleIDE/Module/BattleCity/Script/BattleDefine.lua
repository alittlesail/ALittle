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
name_list = {"level","life","score"},
type_list = {"int","int","int"},
option_map = {}
})

BattleCity.BrushType = {
	BT_WALL = 1,
	BT_IRON = 2,
	BT_GRASS = 3,
	BT_RIVER = 4,
	BT_RIVER2 = 5,
	BT_CASTLE = 6,
	BT_CASTLE2 = 7,
}

BattleCity.DirType = {
	DT_UP = 1,
	DT_DOWN = 2,
	DT_LEFT = 3,
	DT_RIGHT = 4,
}

BattleCity.ItemType = {
	IT_LIFE = 1,
	IT_STOP = 2,
	IT_IRON = 3,
	IT_BOMB = 4,
	IT_STAR = 5,
	IT_SHIELD = 6,
}

end