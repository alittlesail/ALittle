{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};

ALittle.RegStruct(-1815237140, "ALittleIDE.TileCell", {
name : "ALittleIDE.TileCell", ns_name : "ALittleIDE", rl_name : "TileCell", hash_code : -1815237140,
name_list : ["tex_id"],
type_list : ["int"],
option_map : {}
})
ALittle.RegStruct(-1623996580, "ALittleIDE.TileLayer", {
name : "ALittleIDE.TileLayer", ns_name : "ALittleIDE", rl_name : "TileLayer", hash_code : -1623996580,
name_list : ["cell_map"],
type_list : ["Map<int,Map<int,ALittleIDE.TileCell>>"],
option_map : {}
})
ALittle.RegStruct(382591071, "ALittleIDE.TileMap", {
name : "ALittleIDE.TileMap", ns_name : "ALittleIDE", rl_name : "TileMap", hash_code : 382591071,
name_list : ["tile_type","side_len","tex_map","layer_list"],
type_list : ["int","int","Map<int,string>","List<ALittleIDE.TileLayer>"],
option_map : {}
})

ALittleIDE.TileType = {
	SQUARE : 0,
	HEX_V : 1,
	HEX_H : 2,
}

}