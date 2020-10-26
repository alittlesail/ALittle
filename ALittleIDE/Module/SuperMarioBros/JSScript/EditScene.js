{
if (typeof SuperMarioBros === "undefined") window.SuperMarioBros = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1883782801, "ALittle.UILButtonDownEvent", {
name : "ALittle.UILButtonDownEvent", ns_name : "ALittle", rl_name : "UILButtonDownEvent", hash_code : 1883782801,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1349734647, "SuperMarioBros.EditEntityInfo", {
name : "SuperMarioBros.EditEntityInfo", ns_name : "SuperMarioBros", rl_name : "EditEntityInfo", hash_code : -1349734647,
name_list : ["ui","type","width","height","center_x","center_y"],
type_list : ["string","int","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name : "ALittle.UIButtonEvent", ns_name : "ALittle", rl_name : "UIButtonEvent", hash_code : -1347278145,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
SuperMarioBros.EditContainer = JavaScript.Class(ALittle.DisplayLayout, {
	Init : function(tile_linear) {
		this._tile_linear = tile_linear;
	},
	ClipRect : function(x, y, width, height, h_move, v_move) {
		this._tile_linear.ClipRect(x - this._x, y - this._y, width - this._x, height - this._y, h_move, v_move);
	},
}, "SuperMarioBros.EditContainer");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
SuperMarioBros.EditScene = JavaScript.Class(ALittle.DisplayLayout, {
	TCtor : function() {
		this._scroll_screen.container.Init(this._tile_linear);
		this._entity_panel.visible = false;
		this._entity_info_map = new Map();
		this._entity_map = new Map();
		this.AddEntity("wall_1", SuperMarioBros.EntityType.ET_WALL_1, this._entity_wall_1);
		this.AddEntity("hide_wall_1", SuperMarioBros.EntityType.ET_HIDE_WALL_1, this._entity_hide_wall_1);
		this.AddEntity("random_wall_1", SuperMarioBros.EntityType.ET_RANDOM_WALL_1, this._entity_random_wall_1);
		this.AddEntity("enemy_1", SuperMarioBros.EntityType.ET_ENEMY_1, this._entity_enemy_1);
		this.AddEntity("enemy_2", SuperMarioBros.EntityType.ET_ENEMY_2, this._entity_enemy_2);
		this.AddEntity("flag_1", SuperMarioBros.EntityType.ET_FLAG_1, this._entity_flag_1);
		this.AddEntity("flag_2", SuperMarioBros.EntityType.ET_FLAG_2, this._entity_flag_2);
		this.AddEntity("flag_3", SuperMarioBros.EntityType.ET_FLAG_3, this._entity_flag_3);
		this.AddEntity("flag_4", SuperMarioBros.EntityType.ET_FLAG_4, this._entity_flag_4);
		this.AddEntity("flag_5", SuperMarioBros.EntityType.ET_FLAG_5, this._entity_flag_5);
		this.AddEntity("born_1", SuperMarioBros.EntityType.ET_BORN_1, this._entity_born_1);
		this._select_frame._user_data = this._entity_info_map.get(SuperMarioBros.EntityType.ET_RANDOM_WALL_1);
	},
	AddEntity : function(ui, type, object) {
		let info = {};
		info.ui = ui;
		info.type = type;
		info.width = object.width;
		info.height = object.height;
		info.center_x = object.center_x;
		info.center_y = object.center_y;
		object._user_data = info;
		object.AddEventListener(___all_struct.get(1883782801), this, this.HandleEntitySelectClick);
		this._entity_info_map.set(type, info);
	},
	Show : function() {
		this.visible = true;
		this.Load(1, 1);
		ALittle.File_MakeDeepDir(SuperMarioBros.g_ModuleBasePath + "Other/Map");
		ALittle.System_SetViewSize(ALittle.Math_Floor(this.width), ALittle.Math_Floor(this.height));
	},
	Hide : function() {
		this.visible = false;
	},
	Load : async function(world, subworld) {
		this.Save();
		this._world_input.text = world;
		this._subworld_input.text = subworld;
		this._path = "Other/Map/world_" + world + "_" + subworld + ".map";
		this._cur_data = await SuperMarioBros.g_Control.LoadMessageFromFile(___all_struct.get(-876795489), this._path);
		if (this._cur_data === undefined) {
			this._cur_data = {};
			this._cur_data.row_count = 0;
			this._cur_data.col_count = 0;
			this._cur_data.background = new Map();
			this._cur_data.object = new Map();
		}
		this._tile_linear.RemoveAllChild();
		this._entity_container.RemoveAllChild();
		this._entity_map = new Map();
		for (let [row, submap] of this._cur_data.background) {
			if (submap === undefined) continue;
			for (let [col, index] of submap) {
				if (index === undefined) continue;
				let show_row = ALittle.Math_Floor(index / this._select_tile.col_count) + 1;
				let show_col = index % this._select_tile.col_count + 1;
				this.SetTileShow(row, col, show_row, show_col);
			}
		}
		for (let [row, submap] of this._cur_data.object) {
			if (submap === undefined) continue;
			for (let [col, type] of submap) {
				if (type === undefined) continue;
				this.SetEntityShow(row, col, type);
			}
		}
		this._scroll_screen.container.width = this._tile_linear.width + this._scroll_screen.view_width;
		this._scroll_screen.AdjustScrollBar();
	},
	Save : function() {
		if (this._cur_data === undefined) {
			return;
		}
		this._cur_data.row_count = 0;
		this._cur_data.col_count = 0;
		this._cur_data.background = new Map();
		let ___OBJECT_1 = this._tile_linear.childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let linear = ___OBJECT_1[index - 1];
			if (linear === undefined) break;
			let col = index - 1;
			let ___OBJECT_2 = linear.childs;
			for (let subindex = 1; subindex <= ___OBJECT_2.length; ++subindex) {
				let sprite = ___OBJECT_2[subindex - 1];
				if (sprite === undefined) break;
				if (sprite.visible) {
					let row = subindex - 1;
					let submap = this._cur_data.background.get(row);
					if (submap === undefined) {
						submap = new Map();
						this._cur_data.background.set(row, submap);
					}
					submap.set(col, (sprite.row_index - 1) * this._select_tile.col_count + (sprite.col_index - 1));
					if (this._cur_data.row_count < row + 1) {
						this._cur_data.row_count = row + 1;
					}
					if (this._cur_data.col_count < col + 1) {
						this._cur_data.col_count = col + 1;
					}
				}
			}
		}
		this._cur_data.object = new Map();
		for (let [row, entity_submap] of this._entity_map) {
			if (entity_submap === undefined) continue;
			for (let [col, object] of entity_submap) {
				if (object === undefined) continue;
				let submap = this._cur_data.object.get(row);
				if (submap === undefined) {
					submap = new Map();
					this._cur_data.object.set(row, submap);
				}
				submap.set(col, object._user_data.type);
			}
		}
		let rflct = ___all_struct.get(-876795489);
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
		factory.WriteToStdFile(ALittle.File_BaseFilePath() + SuperMarioBros.g_ModuleBasePath + this._path);
	},
	HandleEntitySelectClick : function(event) {
		this._select_frame.x = event.target.x;
		this._select_frame.y = event.target.y;
		this._select_frame._user_data = event.target._user_data;
	},
	HandleTileTabClick : function(event) {
		this._entity_panel.visible = false;
		this._tile_image.visible = true;
		this._select_tile.visible = true;
	},
	HandleEntityTabClick : function(event) {
		this._entity_panel.visible = true;
		this._tile_image.visible = false;
		this._select_tile.visible = false;
	},
	CursorHandleImpl : function(rel_x, rel_y) {
		let shift = A_UISystem.sym_map.get(1073742049) !== undefined;
		let col = ALittle.Math_Floor((rel_x - this._scroll_screen.container_x) / this._select_tile.width);
		let row = ALittle.Math_Floor((rel_y - this._scroll_screen.container_y) / this._select_tile.height);
		if (this._tile_image.visible) {
			if (shift) {
				this.RemoveTileShow(row, col);
			} else {
				this.SetTileShow(row, col, this._select_tile.row_index, this._select_tile.col_index);
			}
		} else if (this._entity_panel.visible) {
			let info = this._select_frame._user_data;
			if (info === undefined) {
				return;
			}
			if (shift) {
				this.RemoveEntityShow(row, col);
			} else {
				this.SetEntityShow(row, col, info.type);
			}
		}
	},
	HandleTileQuadClick : function(event) {
		this.CursorHandleImpl(event.rel_x, event.rel_y);
	},
	HandleTileQuadDrag : function(event) {
		this.CursorHandleImpl(event.rel_x, event.rel_y);
	},
	SetTileShow : function(row, col, show_row, show_col) {
		if (this._tile_linear.child_count < col + 1) {
			for (let i = this._tile_linear.child_count; i < col + 1; i += 1) {
				let linear = ALittle.NewObject(ALittle.Linear, SuperMarioBros.g_Control);
				linear.type = 2;
				linear.width = this._select_tile.width;
				this._tile_linear.AddChild(linear);
			}
			this._scroll_screen.container.width = this._tile_linear.width + this._scroll_screen.view_width;
			this._scroll_screen.AdjustScrollBar();
		}
		let linear = this._tile_linear.GetChildByIndex(col + 1);
		if (linear === undefined) {
			return;
		}
		if (linear.child_count < row + 1) {
			for (let i = linear.child_count; i < row + 1; i += 1) {
				let sprite = ALittle.NewObject(ALittle.Sprite, SuperMarioBros.g_Control);
				sprite.texture_name = this._select_tile.texture_name;
				sprite.row_count = this._select_tile.row_count;
				sprite.col_count = this._select_tile.col_count;
				sprite.width = this._select_tile.width;
				sprite.height = this._select_tile.height;
				sprite.visible = false;
				linear.AddChild(sprite);
			}
		}
		let sprite = linear.GetChildByIndex(row + 1);
		sprite.row_index = show_row;
		sprite.col_index = show_col;
		sprite.visible = true;
		this._scroll_screen.AdjustScrollBar();
		this._scroll_screen.RefreshClipDisLine();
	},
	SetEntityShow : function(row, col, type) {
		this.RemoveEntityShow(row, col);
		let info = this._entity_info_map.get(type);
		if (info === undefined) {
			return;
		}
		let submap = this._entity_map.get(row);
		if (submap === undefined) {
			submap = new Map();
			this._entity_map.set(row, submap);
		}
		let object = SuperMarioBros.g_Control.CreateControl(info.ui);
		object._user_data = info;
		object.width = info.width;
		object.height = info.height;
		object.center_x = info.center_x;
		object.center_y = info.center_y;
		object.x = col * this._select_tile.width;
		object.y = row * this._select_tile.height;
		this._entity_container.AddChild(object);
		submap.set(col, object);
	},
	RemoveEntityShow : function(row, col) {
		let submap = this._entity_map.get(row);
		if (submap === undefined) {
			return;
		}
		let object = submap.get(col);
		if (object === undefined) {
			return;
		}
		submap.delete(col);
		this._entity_container.RemoveChild(object);
	},
	RemoveTileShow : function(row, col) {
		let linear = this._tile_linear.GetChildByIndex(col + 1);
		if (linear === undefined) {
			return;
		}
		let sprite = linear.GetChildByIndex(row + 1);
		if (sprite === undefined) {
			return;
		}
		sprite.visible = false;
		if (col + 1 !== this._tile_linear.child_count) {
			return;
		}
		for (let i = this._tile_linear.child_count; i >= 1; i += -1) {
			let remove = true;
			linear = this._tile_linear.childs[i - 1];
			let ___OBJECT_3 = linear.childs;
			for (let index = 1; index <= ___OBJECT_3.length; ++index) {
				let child = ___OBJECT_3[index - 1];
				if (child === undefined) break;
				if (child.visible) {
					remove = false;
					break;
				}
			}
			if (remove) {
				this._tile_linear.RemoveChild(linear);
			} else {
				break;
			}
		}
		this._scroll_screen.container.width = this._tile_linear.width + this._scroll_screen.view_width;
		this._scroll_screen.AdjustScrollBar();
		this._scroll_screen.RefreshClipDisLine();
	},
	HandleTileSelected : function(event) {
		let col = ALittle.Math_Floor(event.rel_x / this._select_tile.width) + 1;
		let row = ALittle.Math_Floor(event.rel_y / this._select_tile.height) + 1;
		this._select_tile.col_index = col;
		this._select_tile.row_index = row;
	},
	HandleWorldChanged : function(event) {
		let world = ALittle.Math_ToInt(this._world_input.text);
		if (world === undefined || world < 0) {
			return;
		}
		let subworld = ALittle.Math_ToInt(this._subworld_input.text);
		if (subworld === undefined || world < 0) {
			return;
		}
		this.Load(world, subworld);
	},
	HandleSaveClick : function(event) {
		this.Save();
	},
	HandleBackClick : function(event) {
		this.Save();
		this.Hide();
		ALittle.System_SetViewSize(ALittle.Math_Floor(g_GCenter.login_scene.width), ALittle.Math_Floor(g_GCenter.login_scene.height));
		g_GCenter.login_scene.Show();
	},
}, "SuperMarioBros.EditScene");

}