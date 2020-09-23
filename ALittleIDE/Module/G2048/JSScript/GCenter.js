{
if (typeof G2048 === "undefined") window.G2048 = {};

ALittle.RegStruct(-1842382794, "G2048.ItemInfo", {
name : "G2048.ItemInfo", ns_name : "G2048", rl_name : "ItemInfo", hash_code : -1842382794,
name_list : ["item","row","col"],
type_list : ["ALittle.DisplayObject","int","int"],
option_map : {}
})

G2048.g_GConfig = undefined;
G2048.GCenter = JavaScript.Class(undefined, {
	Ctor : function() {
		this._loop_group = new Map();
	},
	ClearAnti : function() {
		for (let [k, v] of this._loop_group) {
			if (v === undefined) continue;
			if (v.IsCompleted() === false) {
				v.SetCompleted();
			}
		}
		this._loop_group = new Map();
	},
	Setup : function() {
		G2048.g_GConfig = ALittle.CreateConfigSystem(G2048.g_ModuleBasePath + "/User.cfg");
		ALittle.Math_RandomSeed(ALittle.Time_GetCurTime());
		ALittle.System_SetThreadCount(1);
		this._main_layer = ALittle.NewObject(ALittle.DisplayLayout, G2048.g_Control);
		this._main_layer.width_type = 4;
		this._main_layer.height_type = 4;
		G2048.g_LayerGroup.AddChild(this._main_layer, undefined);
		this._dialog_layer = ALittle.NewObject(ALittle.DisplayLayout, G2048.g_Control);
		this._dialog_layer.width_type = 4;
		this._dialog_layer.height_type = 4;
		G2048.g_LayerGroup.AddChild(this._dialog_layer, undefined);
		G2048.g_Control.PrepareTexture(["item_2", "item_4", "item_8", "item_16", "item_32", "item_64", "item_128", "item_256", "item_512", "item_1024", "item_2048"], undefined);
		G2048.g_Control.CreateControl("main_scene", this, this._main_layer);
		this._max_score_text._user_data = G2048.g_GConfig.GetConfig("max_score", 0);
		this._max_score_text.text = this._max_score_text._user_data;
		this.Restart();
	},
	ShowMainMenu : function(content, show_back) {
		if (this._main_menu === undefined) {
			this._main_menu = G2048.g_Control.CreateControl("main_menu", this, undefined);
			this._dialog_layer.AddChild(this._main_menu, undefined);
		}
		this._main_menu.visible = true;
		this._menu_content.text = content;
		this._menu_back.visible = show_back;
	},
	Restart : function() {
		if (this._main_menu !== undefined) {
			this._main_menu.visible = false;
		}
		this._score_text.text = "0";
		this._score_text._user_data = 0;
		this._data_map = new Map();
		this._data_map.set(1, new Map());
		this._data_map.set(2, new Map());
		this._data_map.set(3, new Map());
		this._data_map.set(4, new Map());
		this._loop_group = new Map();
		this._tile_container.RemoveAllChild();
		this.GenerateItem(0);
		this.GenerateItem(0);
		this._item_moved = false;
		this._loop_delay = 0;
		this._drag_quad.DelayFocus();
	},
	GenerateItem : function(delay_time) {
		let list = [];
		let list_count = 0;
		for (let i = 1; i <= 4; i += 1) {
			for (let j = 1; j <= 4; j += 1) {
				if (this._data_map.get(i).get(j) === undefined) {
					let data = [];
					data[1 - 1] = i;
					data[2 - 1] = j;
					++ list_count;
					list[list_count - 1] = data;
				}
			}
		}
		if (list_count === 0) {
			return false;
		}
		let rand1 = ALittle.Math_RandomInt(1, 100);
		let number = 2;
		if (rand1 > 50) {
			number = 4;
		}
		let rand2 = ALittle.Math_RandomInt(1, list_count);
		let row = list[rand2 - 1][1 - 1];
		let col = list[rand2 - 1][2 - 1];
		this.BornItem(number, row, col, delay_time, true);
		return true;
	},
	CalcLeft : function() {
		let moved = false;
		for (let i = 1; i <= 4; i += 1) {
			let list = [];
			let list_count = 0;
			for (let j = 1; j <= 4; j += 1) {
				if (this._data_map.get(i).get(j) !== undefined) {
					let info = {};
					info.item = this._data_map.get(i).get(j);
					info.row = i;
					info.col = j;
					++ list_count;
					list[list_count - 1] = info;
				}
			}
			let new_list = [];
			if (list_count === 1) {
				this.TransItem(list[1 - 1], i, 1);
			} else if (list_count === 2) {
				if (list[1 - 1].item._user_data === list[2 - 1].item._user_data) {
					this.CombineItems(list[1 - 1], list[2 - 1], i, 1);
				} else {
					this.TransItem(list[1 - 1], i, 1);
					this.TransItem(list[2 - 1], i, 2);
				}
			} else if (list_count === 3) {
				if (list[1 - 1].item._user_data === list[2 - 1].item._user_data) {
					this.CombineItems(list[1 - 1], list[2 - 1], i, 1);
					this.TransItem(list[3 - 1], i, 2);
				} else if (list[2 - 1].item._user_data === list[3 - 1].item._user_data) {
					this.TransItem(list[1 - 1], i, 1);
					this.CombineItems(list[2 - 1], list[3 - 1], i, 2);
				} else {
					this.TransItem(list[1 - 1], i, 1);
					this.TransItem(list[2 - 1], i, 2);
					this.TransItem(list[3 - 1], i, 3);
				}
			} else if (list_count === 4) {
				if (list[1 - 1].item._user_data === list[2 - 1].item._user_data) {
					this.CombineItems(list[1 - 1], list[2 - 1], i, 1);
					if (list[3 - 1].item._user_data === list[4 - 1].item._user_data) {
						this.CombineItems(list[3 - 1], list[4 - 1], i, 2);
					} else {
						this.TransItem(list[3 - 1], i, 2);
						this.TransItem(list[4 - 1], i, 3);
					}
				} else if (list[2 - 1].item._user_data === list[3 - 1].item._user_data) {
					this.TransItem(list[1 - 1], i, 1);
					this.CombineItems(list[2 - 1], list[3 - 1], i, 2);
					this.TransItem(list[4 - 1], i, 3);
				} else if (list[3 - 1].item._user_data === list[4 - 1].item._user_data) {
					this.TransItem(list[1 - 1], i, 1);
					this.TransItem(list[2 - 1], i, 2);
					this.CombineItems(list[3 - 1], list[4 - 1], i, 3);
				}
			}
		}
	},
	CalcRight : function() {
		for (let i = 1; i <= 4; i += 1) {
			let list = [];
			let list_count = 0;
			for (let j = 4; j >= 1; j += -1) {
				if (this._data_map.get(i).get(j) !== undefined) {
					let info = {};
					info.item = this._data_map.get(i).get(j);
					info.row = i;
					info.col = j;
					++ list_count;
					list[list_count - 1] = info;
				}
			}
			let new_list = [];
			if (list_count === 1) {
				this.TransItem(list[1 - 1], i, 5 - 1);
			} else if (list_count === 2) {
				if (list[1 - 1].item._user_data === list[2 - 1].item._user_data) {
					this.CombineItems(list[1 - 1], list[2 - 1], i, 5 - 1);
				} else {
					this.TransItem(list[1 - 1], i, 5 - 1);
					this.TransItem(list[2 - 1], i, 5 - 2);
				}
			} else if (list_count === 3) {
				if (list[1 - 1].item._user_data === list[2 - 1].item._user_data) {
					this.CombineItems(list[1 - 1], list[2 - 1], i, 5 - 1);
					this.TransItem(list[3 - 1], i, 5 - 2);
				} else if (list[2 - 1].item._user_data === list[3 - 1].item._user_data) {
					this.TransItem(list[1 - 1], i, 5 - 1);
					this.CombineItems(list[2 - 1], list[3 - 1], i, 5 - 2);
				} else {
					this.TransItem(list[1 - 1], i, 5 - 1);
					this.TransItem(list[2 - 1], i, 5 - 2);
					this.TransItem(list[3 - 1], i, 5 - 3);
				}
			} else if (list_count === 4) {
				if (list[1 - 1].item._user_data === list[2 - 1].item._user_data) {
					this.CombineItems(list[1 - 1], list[2 - 1], i, 5 - 1);
					if (list[3 - 1].item._user_data === list[4 - 1].item._user_data) {
						this.CombineItems(list[3 - 1], list[4 - 1], i, 5 - 2);
					} else {
						this.TransItem(list[3 - 1], i, 5 - 2);
						this.TransItem(list[4 - 1], i, 5 - 3);
					}
				} else if (list[2 - 1].item._user_data === list[3 - 1].item._user_data) {
					this.TransItem(list[1 - 1], i, 5 - 1);
					this.CombineItems(list[2 - 1], list[3 - 1], i, 5 - 2);
					this.TransItem(list[4 - 1], i, 5 - 3);
				} else if (list[3 - 1].item._user_data === list[4 - 1].item._user_data) {
					this.TransItem(list[1 - 1], i, 5 - 1);
					this.TransItem(list[2 - 1], i, 5 - 2);
					this.CombineItems(list[3 - 1], list[4 - 1], i, 5 - 3);
				}
			}
		}
	},
	CalcUp : function() {
		for (let j = 1; j <= 4; j += 1) {
			let list = [];
			let list_count = 0;
			for (let i = 1; i <= 4; i += 1) {
				if (this._data_map.get(i).get(j) !== undefined) {
					let info = {};
					info.item = this._data_map.get(i).get(j);
					info.row = i;
					info.col = j;
					++ list_count;
					list[list_count - 1] = info;
				}
			}
			let new_list = {};
			if (list_count === 1) {
				this.TransItem(list[1 - 1], 1, j);
			} else if (list_count === 2) {
				if (list[1 - 1].item._user_data === list[2 - 1].item._user_data) {
					this.CombineItems(list[1 - 1], list[2 - 1], 1, j);
				} else {
					this.TransItem(list[1 - 1], 1, j);
					this.TransItem(list[2 - 1], 2, j);
				}
			} else if (list_count === 3) {
				if (list[1 - 1].item._user_data === list[2 - 1].item._user_data) {
					this.CombineItems(list[1 - 1], list[2 - 1], 1, j);
					this.TransItem(list[3 - 1], 2, j);
				} else if (list[2 - 1].item._user_data === list[3 - 1].item._user_data) {
					this.TransItem(list[1 - 1], 1, j);
					this.CombineItems(list[2 - 1], list[3 - 1], 2, j);
				} else {
					this.TransItem(list[1 - 1], 1, j);
					this.TransItem(list[2 - 1], 2, j);
					this.TransItem(list[3 - 1], 3, j);
				}
			} else if (list_count === 4) {
				if (list[1 - 1].item._user_data === list[2 - 1].item._user_data) {
					this.CombineItems(list[1 - 1], list[2 - 1], 1, j);
					if (list[3 - 1].item._user_data === list[4 - 1].item._user_data) {
						this.CombineItems(list[3 - 1], list[4 - 1], 2, j);
					} else {
						this.TransItem(list[3 - 1], 2, j);
						this.TransItem(list[4 - 1], 3, j);
					}
				} else if (list[2 - 1].item._user_data === list[3 - 1].item._user_data) {
					this.TransItem(list[1 - 1], 1, j);
					this.CombineItems(list[2 - 1], list[3 - 1], 2, j);
					this.TransItem(list[4 - 1], 3, j);
				} else if (list[3 - 1].item._user_data === list[4 - 1].item._user_data) {
					this.TransItem(list[1 - 1], 1, j);
					this.TransItem(list[2 - 1], 2, j);
					this.CombineItems(list[3 - 1], list[4 - 1], 3, j);
				}
			}
		}
	},
	CalcDown : function() {
		for (let j = 1; j <= 4; j += 1) {
			let list = [];
			let list_count = 0;
			for (let i = 4; i >= 1; i += -1) {
				if (this._data_map.get(i).get(j) !== undefined) {
					let info = {};
					info.item = this._data_map.get(i).get(j);
					info.row = i;
					info.col = j;
					++ list_count;
					list[list_count - 1] = info;
				}
			}
			let new_list = [];
			if (list_count === 1) {
				this.TransItem(list[1 - 1], 5 - 1, j);
			} else if (list_count === 2) {
				if (list[1 - 1].item._user_data === list[2 - 1].item._user_data) {
					this.CombineItems(list[1 - 1], list[2 - 1], 5 - 1, j);
				} else {
					this.TransItem(list[1 - 1], 5 - 1, j);
					this.TransItem(list[2 - 1], 5 - 2, j);
				}
			} else if (list_count === 3) {
				if (list[1 - 1].item._user_data === list[2 - 1].item._user_data) {
					this.CombineItems(list[1 - 1], list[2 - 1], 5 - 1, j);
					this.TransItem(list[3 - 1], 5 - 2, j);
				} else if (list[2 - 1].item._user_data === list[3 - 1].item._user_data) {
					this.TransItem(list[1 - 1], 5 - 1, j);
					this.CombineItems(list[2 - 1], list[3 - 1], 5 - 2, j);
				} else {
					this.TransItem(list[1 - 1], 5 - 1, j);
					this.TransItem(list[2 - 1], 5 - 2, j);
					this.TransItem(list[3 - 1], 5 - 3, j);
				}
			} else if (list_count === 4) {
				if (list[1 - 1].item._user_data === list[2 - 1].item._user_data) {
					this.CombineItems(list[1 - 1], list[2 - 1], 5 - 1, j);
					if (list[3 - 1].item._user_data === list[4 - 1].item._user_data) {
						this.CombineItems(list[3 - 1], list[4 - 1], 5 - 2, j);
					} else {
						this.TransItem(list[3 - 1], 5 - 2, j);
						this.TransItem(list[4 - 1], 5 - 3, j);
					}
				} else if (list[2 - 1].item._user_data === list[3 - 1].item._user_data) {
					this.TransItem(list[1 - 1], 5 - 1, j);
					this.CombineItems(list[2 - 1], list[3 - 1], 5 - 2, j);
					this.TransItem(list[4 - 1], 5 - 3, j);
				} else if (list[3 - 1].item._user_data === list[4 - 1].item._user_data) {
					this.TransItem(list[1 - 1], 5 - 1, j);
					this.TransItem(list[2 - 1], 5 - 2, j);
					this.CombineItems(list[3 - 1], list[4 - 1], 5 - 3, j);
				}
			}
		}
	},
	BornItem : function(number, row, col, delay_time, anti) {
		let target = this["_tile" + row + col];
		let ui_name = "item_" + number;
		let item = G2048.g_Control.CreateControl(ui_name, undefined, undefined);
		this._data_map.get(row).set(col, item);
		item._user_data = number;
		this._tile_container.AddChild(item, undefined);
		let target_x = target.x;
		let target_y = target.y;
		let target_width = target.width;
		let target_height = target.height;
		if (anti === true) {
			item.width = 0;
			item.height = 0;
			item.x = target_x + target_width / 2;
			item.y = target_y + target_height / 2;
			item.visible = false;
			let loop = ALittle.NewObject(ALittle.LoopAttribute, item, "visible", true, delay_time);
			this._loop_group.set(loop, loop);
			A_LoopSystem.AddUpdater(loop);
			loop = ALittle.NewObject(ALittle.LoopLinear, item, "x", target_x, 100, delay_time, undefined);
			this._loop_group.set(loop, loop);
			A_LoopSystem.AddUpdater(loop);
			loop = ALittle.NewObject(ALittle.LoopLinear, item, "y", target_y, 100, delay_time, undefined);
			this._loop_group.set(loop, loop);
			A_LoopSystem.AddUpdater(loop);
			loop = ALittle.NewObject(ALittle.LoopLinear, item, "width", target_width, 100, delay_time, undefined);
			this._loop_group.set(loop, loop);
			A_LoopSystem.AddUpdater(loop);
			loop = ALittle.NewObject(ALittle.LoopLinear, item, "height", target_height, 100, delay_time, undefined);
			this._loop_group.set(loop, loop);
			A_LoopSystem.AddUpdater(loop);
		} else {
			item.width = target_width;
			item.height = target_height;
			item.x = target_x;
			item.y = target_y;
			item.visible = false;
			let loop = ALittle.NewObject(ALittle.LoopAttribute, item, "visible", true, delay_time);
			this._loop_group.set(loop, loop);
			A_LoopSystem.AddUpdater(loop);
		}
	},
	TransItem : function(item_info, to_row, to_col) {
		let target = this["_tile" + to_row + to_col];
		let target_x = target.x;
		let target_y = target.y;
		if (item_info.col !== to_col) {
			let loop = ALittle.NewObject(ALittle.LoopLinear, item_info.item, "x", target_x, 200, 0, undefined);
			this._loop_group.set(loop, loop);
			A_LoopSystem.AddUpdater(loop);
			this._item_moved = true;
		}
		if (item_info.row !== to_row) {
			let loop = ALittle.NewObject(ALittle.LoopLinear, item_info.item, "y", target_y, 200, 0, undefined);
			this._loop_group.set(loop, loop);
			A_LoopSystem.AddUpdater(loop);
			this._item_moved = true;
		}
		this._data_map.get(item_info.row).delete(item_info.col);
		this._data_map.get(to_row).set(to_col, item_info.item);
		if (this._loop_delay < 200) {
			this._loop_delay = 200;
		}
	},
	CombineItems : function(item1_info, item2_info, to_row, to_col) {
		this.TransAndRemoveItem(item1_info.item, item1_info.row, item1_info.col, to_row, to_col);
		this.TransAndRemoveItem(item2_info.item, item2_info.row, item2_info.col, to_row, to_col);
		this.BornItem(item1_info.item._user_data * 2, to_row, to_col, 200, false);
		this._score_text._user_data = this._score_text._user_data + item1_info.item._user_data * 2;
		this._score_text.text = this._score_text._user_data;
		this._item_moved = true;
		if (this._loop_delay < 300) {
			this._loop_delay = 300;
		}
	},
	TransAndRemoveItem : function(item, from_row, from_col, to_row, to_col) {
		let target = this["_tile" + to_row + to_col];
		let target_x = target.x;
		let target_y = target.y;
		if (from_col !== to_col) {
			let loop = ALittle.NewObject(ALittle.LoopLinear, item, "x", target_x, 200, 0, undefined);
			this._loop_group.set(loop, loop);
			A_LoopSystem.AddUpdater(loop);
		}
		if (from_row !== to_row) {
			let loop = ALittle.NewObject(ALittle.LoopLinear, item, "y", target_y, 200, 0, undefined);
			this._loop_group.set(loop, loop);
			A_LoopSystem.AddUpdater(loop);
		}
		let loop = ALittle.NewObject(ALittle.LoopTimer, this.EraseItem.bind(this, item), 200);
		this._loop_group.set(loop, loop);
		A_LoopSystem.AddUpdater(loop);
		this._data_map.get(from_row).delete(from_col);
	},
	EraseItem : function(item) {
		this._tile_container.RemoveChild(item);
	},
	HandleKeyDown : function(event) {
		this.ClearAnti();
		this._item_moved = false;
		this._loop_delay = 0;
		if (event.sym === 1073741904) {
			this.CalcLeft();
		} else if (event.sym === 1073741903) {
			this.CalcRight();
		} else if (event.sym === 1073741906) {
			this.CalcUp();
		} else if (event.sym === 1073741905) {
			this.CalcDown();
		}
		if (this.CheckGameOver()) {
			return;
		}
		if (this._item_moved === false) {
			return;
		}
		this.GenerateItem(this._loop_delay);
		if (this.CheckGameOver()) {
			return;
		}
	},
	HandleDragBegin : function(event) {
		this._drag_total_x = 0;
		this._drag_total_y = 0;
	},
	HandleDrag : function(event) {
		this._drag_total_x = this._drag_total_x + event.delta_x;
		this._drag_total_y = this._drag_total_y + event.delta_y;
	},
	HandleDragEnd : function(event) {
		this.ClearAnti();
		this._item_moved = false;
		this._loop_delay = 0;
		if (ALittle.Math_Abs(this._drag_total_x) > ALittle.Math_Abs(this._drag_total_y)) {
			if (this._drag_total_x < 0) {
				this.CalcLeft();
			} else {
				this.CalcRight();
			}
		} else {
			if (this._drag_total_y < 0) {
				this.CalcUp();
			} else {
				this.CalcDown();
			}
		}
		if (this.CheckGameOver()) {
			return;
		}
		if (this._item_moved === false) {
			return;
		}
		this.GenerateItem(this._loop_delay);
		if (this.CheckGameOver()) {
			return;
		}
	},
	CheckGameOver : function() {
		for (let i = 1; i <= 4; i += 1) {
			for (let j = 1; j <= 4; j += 1) {
				let item = this._data_map.get(i).get(j);
				if (item !== undefined && item._user_data === 2048) {
					this.ShowMainMenu("Victory", false);
					if (this._max_score_text._user_data < this._score_text._user_data) {
						this._max_score_text._user_data = this._score_text._user_data;
						this._max_score_text.text = this._max_score_text._user_data;
						G2048.g_GConfig.SetConfig("max_score", this._max_score_text._user_data, undefined);
					}
					return true;
				}
			}
		}
		for (let i = 1; i <= 4; i += 1) {
			for (let j = 1; j <= 4; j += 1) {
				let item = this._data_map.get(i).get(j);
				if (item === undefined) {
					return false;
				}
				if (j > 1 && (this._data_map.get(i).get(j - 1) === undefined || this._data_map.get(i).get(j - 1)._user_data === item._user_data)) {
					return false;
				}
				if (j < 4 && (this._data_map.get(i).get(j + 1) === undefined || this._data_map.get(i).get(j + 1)._user_data === item._user_data)) {
					return false;
				}
				if (i > 1 && (this._data_map.get(i - 1).get(j) === undefined || this._data_map.get(i - 1).get(j)._user_data === item._user_data)) {
					return false;
				}
				if (i < 4 && (this._data_map.get(i + 1).get(j) === undefined || this._data_map.get(i + 1).get(j)._user_data === item._user_data)) {
					return false;
				}
			}
		}
		this.ShowMainMenu("GameOver", false);
		return true;
	},
	HandleRestartClick : function(event) {
		this.Restart();
	},
	HandleBackClick : function(event) {
		this._main_menu.visible = false;
	},
	HandleMenuClick : function(event) {
		this.ShowMainMenu("", true);
	},
	Shutdown : function() {
	},
}, "G2048.GCenter");

G2048.g_GCenter = ALittle.NewObject(G2048.GCenter);
}