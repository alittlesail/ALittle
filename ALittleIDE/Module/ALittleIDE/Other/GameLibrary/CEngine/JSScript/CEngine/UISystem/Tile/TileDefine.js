{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(-1281734132, "ALittle.TileMap", {
name : "ALittle.TileMap", ns_name : "ALittle", rl_name : "TileMap", hash_code : -1281734132,
name_list : ["tile_type","side_len","tile_width","tile_height","tile_x","tile_y","col_count","row_count","tex_map","layer_list"],
type_list : ["int","int","int","int","int","int","int","int","Map<int,string>","List<ALittle.TileLayer>"],
option_map : {}
})
ALittle.RegStruct(-343663763, "ALittle.TileLayer", {
name : "ALittle.TileLayer", ns_name : "ALittle", rl_name : "TileLayer", hash_code : -343663763,
name_list : ["name","cell_map"],
type_list : ["string","Map<int,Map<int,ALittle.TileCell>>"],
option_map : {}
})
ALittle.RegStruct(7944876, "ALittle.TileCell", {
name : "ALittle.TileCell", ns_name : "ALittle", rl_name : "TileCell", hash_code : 7944876,
name_list : ["tex_id"],
type_list : ["int"],
option_map : {}
})

ALittle.TileType = {
	NONE : 0,
	SQUARE : 1,
	HEX_V : 2,
	HEX_H : 3,
}

let floor = ALittle.Math_Floor;
let ceil = ALittle.Math_Ceil;
if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.TileMapContainer = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._row_count = 0;
		this._col_count = 0;
		this._cell_width = 0.0;
		this._cell_height = 0.0;
		this._linear_x = 0.0;
		this._linear_y = 0.0;
		this._tile_layout = ALittle.NewObject(ALittle.TileLayoutContainer, ctrl_sys);
		this._tile_layout.width_type = 4;
		this._tile_layout.height_type = 4;
		this.AddChild(this._tile_layout);
		this._user_layout = ALittle.NewObject(ALittle.TileLayoutContainer, ctrl_sys);
		this._user_layout.width_type = 4;
		this._user_layout.height_type = 4;
		this.AddChild(this._user_layout);
	},
	ClipRect : function(x, y, width, height, h_move, v_move) {
		let ___OBJECT_1 = this.childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			child.ClipRect(x - this._x, y - this._y, width - this._x, height - this._y, h_move, v_move);
		}
	},
	Init : function(tile_map, row_count, col_count) {
		this._tile_layout.RemoveAllChild();
		this._tile_map = tile_map;
		this._row_count = row_count;
		this._col_count = col_count;
		this._image_cache = new Map();
		this._cell_width = ALittle.Tile_CalcCellWidth(tile_map);
		this._cell_height = ALittle.Tile_CalcCellHeight(tile_map);
		this._linear_x = ALittle.Tile_CalcLinear2OffsetX(tile_map);
		this._linear_y = ALittle.Tile_CalcLinear2OffsetY(tile_map);
		let grid_map_width = this._cell_width * col_count;
		let linear_1 = undefined;
		let linear_2 = undefined;
		let ___OBJECT_2 = tile_map.layer_list;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let layer = ___OBJECT_2[index - 1];
			if (layer === undefined) break;
			let group = ALittle.NewObject(ALittle.TileGroupContainer, this._ctrl_sys);
			linear_1 = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
			linear_1.type = 2;
			linear_1.width = grid_map_width;
			group.AddChild(linear_1);
			linear_2 = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
			linear_2.type = 2;
			linear_2.width = grid_map_width;
			linear_2.x = this._linear_x;
			linear_2.y = this._linear_y;
			group.AddChild(linear_2);
			this.ResizeLinear(linear_1, linear_2, index);
			this._tile_layout.AddChild(group);
		}
		let width_1 = 0.0;
		if (linear_1 !== undefined) {
			width_1 = linear_1.x + linear_1.width;
		}
		let width_2 = 0.0;
		if (linear_2 !== undefined) {
			width_2 = linear_2.x + linear_2.width;
		}
		let height_1 = 0.0;
		if (height_1 !== undefined) {
			height_1 = linear_1.y + linear_1.height;
		}
		let height_2 = 0.0;
		if (linear_2 !== undefined) {
			height_2 = linear_2.y + linear_2.height;
		}
		this.width = ALittle.Math_Max(width_1, width_2);
		this.height = ALittle.Math_Max(height_1, height_2);
	},
	get user_layout() {
		return this._user_layout;
	},
	GetImage : function(layer, row, col) {
		let layer_map = this._image_cache.get(layer);
		if (layer_map === undefined) {
			layer_map = new Map();
			this._image_cache.set(layer, layer_map);
		}
		let row_map = layer_map.get(row);
		if (row_map === undefined) {
			row_map = new Map();
			layer_map.set(row, row_map);
		}
		let image = row_map.get(col);
		if (image !== undefined) {
			return image;
		}
		let group = this._tile_layout.GetChildByIndex(layer);
		if (group === undefined) {
			return undefined;
		}
		let linear_1 = group.GetChildByIndex(1);
		let linear_2 = group.GetChildByIndex(2);
		let tile_type = this._tile_map.tile_type;
		if (tile_type === 2) {
			if (row % 2 === 1) {
				image = linear_1.childs[floor(row / 2) + 1 - 1].childs[col - 1]._user_data;
				row_map.set(col, image);
				return image;
			}
			image = linear_2.childs[floor(row / 2) - 1].childs[col - 1]._user_data;
			row_map.set(col, image);
			return image;
		} else {
			if (col % 2 === 1) {
				image = linear_1.childs[row - 1].childs[floor(col / 2) + 1 - 1]._user_data;
				row_map.set(col, image);
				return image;
			}
			image = linear_2.childs[row - 1].childs[floor(col / 2) - 1]._user_data;
			row_map.set(col, image);
			return image;
		}
	},
	RefreshTexture : function(start_row, start_col) {
		let tile_map = this._tile_map;
		let row_count = this._row_count;
		let col_count = this._col_count;
		let childs = this._tile_layout._childs;
		let ___OBJECT_3 = childs;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let group = ___OBJECT_3[index - 1];
			if (group === undefined) break;
			let layer = tile_map.layer_list[index - 1];
			for (let row = 1; row <= row_count; row += 1) {
				for (let col = 1; col <= col_count; col += 1) {
					let image = this.GetImage(index, row, col);
					let cells = layer.cell_map.get(row + start_row - 1);
					if (cells === undefined) {
						image.texture_name = undefined;
					} else {
						let cell = cells.get(col + start_col - 1);
						if (cell === undefined) {
							image.texture_name = undefined;
						} else {
							image.texture_name = tile_map.tex_map.get(cell.tex_id);
						}
					}
				}
			}
		}
	},
	ResizeLinear : function(linear_1, linear_2, layer) {
		let tile_map = this._tile_map;
		let col_count = this._col_count;
		let row_count = this._row_count;
		if (tile_map.tile_type === 2) {
			linear_1.width = this._cell_width * col_count;
			linear_2.width = linear_1.width;
			for (let row = 1; row <= row_count; row += 1) {
				let linear = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
				linear.type = 1;
				linear.height = this._cell_height;
				for (let col = 1; col <= col_count; col += 1) {
					linear.AddChild(this.CreateCell());
				}
				if (row % 2 === 1) {
					linear_1.AddChild(linear);
				} else {
					linear_2.AddChild(linear);
				}
			}
		} else {
			let col_count_1 = ceil(col_count / 2);
			for (let row = 1; row <= row_count; row += 1) {
				let linear = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
				linear.type = 1;
				linear.height = this._cell_height;
				for (let col = 1; col <= col_count_1; col += 1) {
					linear.AddChild(this.CreateCell());
				}
				linear_1.AddChild(linear);
			}
			let col_count_2 = floor(col_count / 2);
			for (let row = linear_2.child_count + 1; row <= row_count; row += 1) {
				let linear = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
				linear.type = 1;
				linear.height = this._cell_height;
				for (let col = 1; col <= col_count_2; col += 1) {
					linear.AddChild(this.CreateCell());
				}
				linear_2.AddChild(linear);
			}
		}
	},
	CreateCell : function() {
		let tile_map = this._tile_map;
		let tile_type = tile_map.tile_type;
		let side_len = tile_map.side_len;
		if (tile_type === 2) {
			let cell = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
			cell.width = this._cell_width;
			let image = ALittle.NewObject(ALittle.Image, this._ctrl_sys);
			cell._user_data = image;
			image.width = tile_map.tile_width;
			image.height = tile_map.tile_height;
			image.x = tile_map.tile_x;
			image.y = tile_map.tile_y;
			cell.AddChild(image);
			return cell;
		}
		if (tile_type === 1) {
			let cell = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
			cell.width = this._cell_width;
			let image = ALittle.NewObject(ALittle.Image, this._ctrl_sys);
			cell._user_data = image;
			image.width = tile_map.tile_width;
			image.height = tile_map.tile_height;
			image.x = tile_map.tile_x;
			image.y = tile_map.tile_y;
			cell.AddChild(image);
			return cell;
		}
		if (tile_type === 3) {
			let cell = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
			cell.width = this._cell_width;
			let image = ALittle.NewObject(ALittle.Image, this._ctrl_sys);
			cell._user_data = image;
			image.width = tile_map.tile_width;
			image.height = tile_map.tile_height;
			image.x = tile_map.tile_x;
			image.y = tile_map.tile_y;
			cell.AddChild(image);
			return cell;
		}
		return undefined;
	},
}, "ALittle.TileMapContainer");

if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittle.TileGroupContainer = JavaScript.Class(ALittle.DisplayGroup, {
	ClipRect : function(x, y, width, height, h_move, v_move) {
		let ___OBJECT_4 = this.childs;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let child = ___OBJECT_4[index - 1];
			if (child === undefined) break;
			child.ClipRect(x - this._x, y - this._y, width - this._x, height - this._y, h_move, v_move);
		}
	},
}, "ALittle.TileGroupContainer");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.TileLayoutContainer = JavaScript.Class(ALittle.DisplayLayout, {
	ClipRect : function(x, y, width, height, h_move, v_move) {
		let ___OBJECT_5 = this.childs;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let child = ___OBJECT_5[index - 1];
			if (child === undefined) break;
			child.ClipRect(x - this._x, y - this._y, width - this._x, height - this._y, h_move, v_move);
		}
	},
}, "ALittle.TileLayoutContainer");

ALittle.Tile_CalcLinear2OffsetX = function(tile_map) {
	let tile_type = tile_map.tile_type;
	let side_len = tile_map.side_len;
	if (tile_type === 1) {
		return side_len;
	}
	if (tile_type === 2) {
		return side_len * 1.732 / 2;
	}
	if (tile_type === 3) {
		return side_len * 3 / 2;
	}
	return 0;
}

ALittle.Tile_CalcLinear2OffsetY = function(tile_map) {
	let tile_type = tile_map.tile_type;
	let side_len = tile_map.side_len;
	if (tile_type === 1) {
		return 0;
	}
	if (tile_type === 2) {
		return side_len * 3 / 2;
	}
	if (tile_type === 3) {
		return side_len * 1.732 / 2;
	}
	return 0;
}

ALittle.Tile_CalcRowColByPosInHexV = function(tile_map, x, y) {
	let tile_type = tile_map.tile_type;
	let side_len = tile_map.side_len;
	let half_width = side_len * 1.732 / 2;
	let split_x = floor(x / half_width);
	let offset_x = x - split_x * half_width;
	if (split_x % 2 === 0) {
		let split_y = floor(y / (side_len * 3));
		let offset_y = y - split_y * (side_len * 3);
		if (offset_y < side_len / 2) {
			let row = split_y * 2;
			let col = floor(split_x / 2);
			let test_y = -1 / 1.732 * offset_x + side_len / 2;
			if (offset_y < test_y) {
				row = row - (1);
				col = col - (1);
			}
			return [row + 1, col + 1];
		}
		if (offset_y < side_len * 3 / 2) {
			let row = split_y * 2;
			let col = floor(split_x / 2);
			return [row + 1, col + 1];
		}
		if (offset_y < side_len * 2) {
			let row = split_y * 2;
			let col = floor(split_x / 2);
			let test_y = 1 / 1.732 * offset_x;
			if (offset_y - side_len * 3 / 2 > test_y) {
				row = row + (1);
				col = col - (1);
			}
			return [row + 1, col + 1];
		}
		{
			let row = split_y * 2 + 1;
			let col = floor(split_x / 2) - 1;
			return [row + 1, col + 1];
		}
	} else {
		let split_y = floor(y / (side_len * 3));
		let offset_y = y - split_y * (side_len * 3);
		if (offset_y < side_len / 2) {
			let row = split_y * 2;
			let col = floor(split_x / 2);
			let test_y = 1 / 1.732 * offset_x;
			if (offset_y < test_y) {
				row = row - (1);
			}
			return [row + 1, col + 1];
		}
		if (offset_y < side_len * 3 / 2) {
			let row = split_y * 2;
			let col = floor(split_x / 2);
			return [row + 1, col + 1];
		}
		if (offset_y < side_len * 2) {
			let row = split_y * 2;
			let col = floor(split_x / 2);
			let test_y = -1 / 1.732 * offset_x + side_len / 2;
			if (offset_y - side_len * 3 / 2 > test_y) {
				row = row + (1);
			}
			return [row + 1, col + 1];
		}
		{
			let row = split_y * 2 + 1;
			let col = floor(split_x / 2);
			return [row + 1, col + 1];
		}
	}
}

ALittle.Tile_CalcRowColByPos = function(tile_map, x, y) {
	let tile_type = tile_map.tile_type;
	let side_len = tile_map.side_len;
	if (tile_type === 1) {
		let row = floor(y / side_len);
		let col = floor(x / side_len);
		return [row + 1, col + 1];
	}
	if (tile_type === 3) {
		let [col, row] = ALittle.Tile_CalcRowColByPosInHexV(tile_map, y, x);
		return [row, col];
	}
	if (tile_type === 2) {
		return [ALittle.Tile_CalcRowColByPosInHexV(tile_map, x, y)];
	}
	return [0, 0];
}

ALittle.Tile_CalcCellHeight = function(tile_map) {
	let tile_type = tile_map.tile_type;
	let side_len = tile_map.side_len;
	if (tile_type === 1) {
		return side_len;
	}
	if (tile_type === 2) {
		return side_len * 3;
	}
	if (tile_type === 3) {
		return side_len * 1.732;
	}
	return 0;
}

ALittle.Tile_CalcCellWidth = function(tile_map) {
	let tile_type = tile_map.tile_type;
	let side_len = tile_map.side_len;
	if (tile_type === 1) {
		return side_len * 2;
	}
	if (tile_type === 2) {
		return side_len * 1.732;
	}
	if (tile_type === 3) {
		return side_len * 3;
	}
	return 0;
}

ALittle.Tile_GetLayerByName = function(tile_map, name) {
	let ___OBJECT_6 = tile_map.layer_list;
	for (let index = 1; index <= ___OBJECT_6.length; ++index) {
		let layer = ___OBJECT_6[index - 1];
		if (layer === undefined) break;
		if (layer.name === name) {
			return index;
		}
	}
	return undefined;
}

}