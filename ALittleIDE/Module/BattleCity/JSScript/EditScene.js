{
if (typeof BattleCity === "undefined") window.BattleCity = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
BattleCity.EditScene = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._size = 4;
		this._cell_size = 0;
	},
	TCtor : function() {
		this._tile_range.visible = false;
	},
	Show : function() {
		this.visible = true;
		this.Load(1);
		ALittle.File_MakeDeepDir(BattleCity.g_ModuleBasePath + "Other/Map");
		this._cell_size = this._tile_container.width / (13 * 4);
		this._size_input.text = this._size;
		this._tile_range.width = this._size * this._cell_size;
		this._tile_range.height = this._size * this._cell_size;
	},
	Load : async function(stage) {
		this.Save();
		this._stage_input.text = stage;
		this._path = "Other/Map/stage_" + stage + ".map";
		this._cur_data = await BattleCity.g_Control.LoadMessageFromFile(___all_struct.get(-922796193), this._path);
		if (this._cur_data === undefined) {
			this._cur_data = {};
			this._cur_data.tile_map = new Map();
		}
		this._tile_container.RemoveAllChild();
		this._sprite_map = new Map();
		for (let [row, sub_map] of this._cur_data.tile_map) {
			if (sub_map === undefined) continue;
			for (let [col, type] of sub_map) {
				if (type === undefined) continue;
				this.SetTileShow(row, col, type);
			}
		}
	},
	Save : function() {
		if (this._cur_data === undefined) {
			return;
		}
		let rflct = ___all_struct.get(-922796193);
		let factory = undefined;
		factory = ALittle.NewObject(JavaScript.JMessageWriteFactory, 1024);
		if (factory === undefined) {
			ALittle.Error("factory create failed");
			return;
		}
		let invoke_info = ALittle.CreateMessageInfo(rflct.name);
		if (invoke_info === undefined) {
			ALittle.Error("create message info failed:" + rflct.name);
			return;
		}
		ALittle.PS_WriteMessage(factory, invoke_info, undefined, this._cur_data);
		factory.WriteToStdFile(ALittle.File_BaseFilePath() + BattleCity.g_ModuleBasePath + this._path);
	},
	HandleTileSelect : function(event) {
		this._select_sripte.col_index = event.target.col_index;
	},
	HandleStageInputChanged : function(event) {
		let num = ALittle.Math_ToInt(this._stage_input.text);
		if (num === undefined || num < 0 || num > 255) {
			return;
		}
		this.Load(num);
	},
	SetTileShow : function(row, col, type) {
		let sub_map = this._sprite_map.get(row);
		if (sub_map === undefined) {
			sub_map = new Map();
			this._sprite_map.set(row, sub_map);
		}
		if (sub_map.get(col) !== undefined) {
			this._tile_container.RemoveChild(sub_map.get(col));
		}
		let sprite = ALittle.NewObject(ALittle.Sprite, BattleCity.g_Control);
		sprite.texture_name = "tile.png";
		sprite.width = 32 / 4;
		sprite.height = 32 / 4;
		sprite.x = col * sprite.width;
		sprite.y = row * sprite.height;
		sprite.row_count = 4;
		sprite.col_count = 7 * 4;
		sprite.row_index = row % 4 + 1;
		sprite.col_index = col % 4 + 1 + (type - 1) * 4;
		this._tile_container.AddChild(sprite);
		sub_map.set(col, sprite);
	},
	RemoveTileShow : function(row, col) {
		let sub_map = this._sprite_map.get(row);
		if (sub_map === undefined) {
			return;
		}
		if (sub_map.get(col) !== undefined) {
			this._tile_container.RemoveChild(sub_map.get(col));
			sub_map.delete(col);
		}
	},
	WriteCell : function(x, y, brush_type) {
		let [left_col, right_col, top_row, bottom_row] = this.CalcRangeRowCol(x, y);
		for (let row = top_row; row <= bottom_row; row += 1) {
			for (let col = left_col; col <= right_col; col += 1) {
				let sub_map = this._cur_data.tile_map.get(row);
				if (sub_map === undefined) {
					sub_map = new Map();
					this._cur_data.tile_map.set(row, sub_map);
				}
				sub_map.set(col, brush_type);
				this.SetTileShow(row, col, brush_type);
			}
		}
	},
	CalcRangeRowCol : function(x, y) {
		let center_col = ALittle.Math_Floor(x / this._cell_size);
		let center_row = ALittle.Math_Floor(y / this._cell_size);
		let size_offset = ALittle.Math_Floor((this._size - 1) / 2);
		let left_col = center_col - size_offset;
		let right_col = left_col + this._size - 1;
		let top_row = center_row - size_offset;
		let bottom_row = top_row + this._size - 1;
		if (left_col < 0) {
			left_col = 0;
		}
		if (left_col >= 13 * 4) {
			left_col = 13 * 4 - 1;
		}
		if (right_col < 0) {
			right_col = 0;
		}
		if (right_col >= 13 * 4) {
			right_col = 13 * 4 - 1;
		}
		if (top_row < 0) {
			top_row = 0;
		}
		if (top_row >= 13 * 4) {
			top_row = 13 * 4 - 1;
		}
		if (bottom_row < 0) {
			bottom_row = 0;
		}
		if (bottom_row >= 13 * 4) {
			bottom_row = 13 * 4 - 1;
		}
		return [left_col, right_col, top_row, bottom_row];
	},
	EraseCell : function(x, y) {
		let [left_col, right_col, top_row, bottom_row] = this.CalcRangeRowCol(x, y);
		for (let row = top_row; row <= bottom_row; row += 1) {
			for (let col = left_col; col <= right_col; col += 1) {
				let sub_map = this._cur_data.tile_map.get(row);
				if (sub_map !== undefined) {
					sub_map.delete(col);
					if (ALittle.IsEmpty(sub_map)) {
						this._cur_data.tile_map.delete(row);
					}
					this.RemoveTileShow(row, col);
				}
			}
		}
	},
	HandleBrushLButtonDown : function(event) {
		if (A_UISystem.sym_map.get(1073742049) !== undefined) {
			this.EraseCell(event.rel_x, event.rel_y);
		} else {
			this.WriteCell(event.rel_x, event.rel_y, this._select_sripte.col_index);
		}
	},
	HandleBrushDrag : function(event) {
		let [left_col, right_col, top_row, bottom_row] = this.CalcRangeRowCol(event.rel_x, event.rel_y);
		this._tile_range.x = left_col * this._cell_size;
		this._tile_range.y = top_row * this._cell_size;
		if (A_UISystem.sym_map.get(1073742049) !== undefined) {
			this.EraseCell(event.rel_x, event.rel_y);
		} else {
			this.WriteCell(event.rel_x, event.rel_y, this._select_sripte.col_index);
		}
	},
	HandleSaveClick : function(event) {
		this.Save();
	},
	HandleBackClick : function(event) {
		this.Save();
		this.visible = false;
		g_GCenter.Restart();
	},
	HandleSizeInputChanged : function(event) {
		this._size = ALittle.Math_ToInt(event.target.text);
		if (this._size === undefined || this._size <= 0) {
			this._size = 1;
			event.target.text = this._size;
		}
		this._tile_range.width = this._size * this._cell_size;
		this._tile_range.height = this._size * this._cell_size;
	},
	HandleBrushMoveIn : function(event) {
		this._tile_range.visible = true;
	},
	HandleBrushMoveOut : function(event) {
		this._tile_range.visible = false;
	},
	HandleBrushMove : function(event) {
		let [left_col, right_col, top_row, bottom_row] = this.CalcRangeRowCol(event.rel_x, event.rel_y);
		this._tile_range.x = left_col * this._cell_size;
		this._tile_range.y = top_row * this._cell_size;
	},
}, "BattleCity.EditScene");

}