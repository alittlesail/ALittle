-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1281734132, "ALittle.TileMap", {
name = "ALittle.TileMap", ns_name = "ALittle", rl_name = "TileMap", hash_code = -1281734132,
name_list = {"tile_type","side_len","col_count","row_count","tex_map","layer_list"},
type_list = {"int","int","int","int","Map<int,string>","List<ALittle.TileLayer>"},
option_map = {}
})
ALittle.RegStruct(-343663763, "ALittle.TileLayer", {
name = "ALittle.TileLayer", ns_name = "ALittle", rl_name = "TileLayer", hash_code = -343663763,
name_list = {"cell_map"},
type_list = {"Map<int,Map<int,ALittle.TileCell>>"},
option_map = {}
})
ALittle.RegStruct(7944876, "ALittle.TileCell", {
name = "ALittle.TileCell", ns_name = "ALittle", rl_name = "TileCell", hash_code = 7944876,
name_list = {"tex_id"},
type_list = {"int"},
option_map = {}
})

ALittle.TileType = {
	NONE = 0,
	SQUARE = 1,
	HEX_V = 2,
	HEX_H = 3,
}

end