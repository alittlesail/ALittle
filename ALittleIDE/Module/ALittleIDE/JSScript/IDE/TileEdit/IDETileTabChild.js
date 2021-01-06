{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
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
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name : "ALittle.UIButtonEvent", ns_name : "ALittle", rl_name : "UIButtonEvent", hash_code : -1347278145,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(1337289812, "ALittle.UIButtonDragEvent", {
name : "ALittle.UIButtonDragEvent", ns_name : "ALittle", rl_name : "UIButtonDragEvent", hash_code : 1337289812,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(1301789264, "ALittle.UIButtonDragBeginEvent", {
name : "ALittle.UIButtonDragBeginEvent", ns_name : "ALittle", rl_name : "UIButtonDragBeginEvent", hash_code : 1301789264,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
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
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name : "ALittle.UIButtonDragEndEvent", ns_name : "ALittle", rl_name : "UIButtonDragEndEvent", hash_code : 150587926,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(7944876, "ALittle.TileCell", {
name : "ALittle.TileCell", ns_name : "ALittle", rl_name : "TileCell", hash_code : 7944876,
name_list : ["tex_id"],
type_list : ["int"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDETileContainer = JavaScript.Class(ALittle.DisplayLayout, {
	ClipRect : function(x, y, width, height, h_move, v_move) {
		let ___OBJECT_1 = this.childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			child.ClipRect(x - this._x, y - this._y, width - this._x, height - this._y, h_move, v_move);
		}
	},
}, "ALittleIDE.IDETileContainer");

if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittleIDE.IDETileGroupContainer = JavaScript.Class(ALittle.DisplayGroup, {
	ClipRect : function(x, y, width, height, h_move, v_move) {
		let ___OBJECT_2 = this.childs;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let child = ___OBJECT_2[index - 1];
			if (child === undefined) break;
			child.ClipRect(x - this._x, y - this._y, width - this._x, height - this._y, h_move, v_move);
		}
	},
}, "ALittleIDE.IDETileGroupContainer");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDETileLinearContainer = JavaScript.Class(ALittle.DisplayLayout, {
	ClipRect : function(x, y, width, height, h_move, v_move) {
		this._linear_grid_1.ClipRect(x - this._x, y - this._y, width - this._x, height - this._y, h_move, v_move);
		this._linear_grid_2.ClipRect(x - this._x, y - this._y, width - this._x, height - this._y, h_move, v_move);
		let ___OBJECT_3 = this._group_tile.childs;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let child = ___OBJECT_3[index - 1];
			if (child === undefined) break;
			child.ClipRect(x - this._x, y - this._y, width - this._x, height - this._y, h_move, v_move);
		}
	},
}, "ALittleIDE.IDETileLinearContainer");

if (ALittleIDE.IDETabChild === undefined) throw new Error(" extends class:ALittleIDE.IDETabChild is undefined");
ALittleIDE.IDETileTabChild = JavaScript.Class(ALittleIDE.IDETabChild, {
	Ctor : function(ctrl_sys, module, name, save, user_info) {
		this._user_info = user_info;
		this._tab_screen = ALittleIDE.g_Control.CreateControl("ide_tile_tab_screen", this);
		this._tab_screen._user_data = this;
		this._tab_screen.container = ALittle.NewObject(ALittleIDE.IDETileContainer, ALittleIDE.g_Control);
		this._linear_grid_1 = ALittle.NewObject(ALittle.Linear, ALittleIDE.g_Control);
		this._linear_grid_1.type = 2;
		this._tile_container._linear_grid_1 = this._linear_grid_1;
		this._tile_container.AddChild(this._linear_grid_1);
		this._linear_grid_2 = ALittle.NewObject(ALittle.Linear, ALittleIDE.g_Control);
		this._linear_grid_2.type = 2;
		this._tile_container._linear_grid_2 = this._linear_grid_2;
		this._tile_container.AddChild(this._linear_grid_2);
		this._group_tile = ALittle.NewObject(ALittle.DisplayGroup, ALittleIDE.g_Control);
		this._tile_container._group_tile = this._group_tile;
		this._tile_container.AddChild(this._group_tile);
		this._layer_edit = ALittleIDE.g_Control.CreateControl("ide_tile_layer_detail_layout");
		ALittleIDE.g_IDECenter.center.AddEventListener(___all_struct.get(-751714957), this, this.HandleHandDrag);
		this._tab_rb_quad.AddEventListener(___all_struct.get(1883782801), this, this.HandleQuadLButtonDown);
		this._tab_rb_quad.AddEventListener(___all_struct.get(1301789264), this, this.HandleQuadDragBegin);
		this._tab_rb_quad.AddEventListener(___all_struct.get(1337289812), this, this.HandleQuadDrag);
		this._tab_rb_quad.AddEventListener(___all_struct.get(150587926), this, this.HandleQuadDragEnd);
	},
	HandleHandDrag : function(event) {
		this._tab_rb_quad.hand_cursor = event.value;
	},
	HandleQuadLButtonDown : function(event) {
		if (ALittleIDE.g_IDECenter.center.tile_brush) {
			let brush_info = ALittleIDE.g_IDECenter.center.tile_brush_edit.GetBrush();
			if (brush_info === undefined) {
				g_AUITool.ShowNotice("提示", "请先从地块库选择地块");
				return;
			}
			let [layer_info, layer_index] = this._layer_edit.GetCurLayerInfo();
			if (layer_info === undefined) {
				g_AUITool.ShowNotice("提示", "请先选择图层");
				return;
			}
			let [row, col] = ALittle.Tile_CalcRowColByPos(this._user_info.tile_map, event.rel_x, event.rel_y);
			if (row <= 0 || col <= 0) {
				return;
			}
			this.ResizeGridMap(row, col);
			this._drag_cell_row = row;
			this._drag_cell_col = col;
			let col_map = layer_info._layer.cell_map.get(row);
			if (col_map === undefined) {
				col_map = new Map();
				layer_info._layer.cell_map.set(row, col_map);
			}
			let cell = col_map.get(col);
			if (cell === undefined) {
				cell = {};
				col_map.set(col, cell);
			}
			let old_tex_path = undefined;
			if (cell.tex_id !== undefined) {
				old_tex_path = layer_info._user_info.tile_map.tex_map.get(cell.tex_id);
			}
			let tex_id = layer_info._user_info.tex_id_map[brush_info.tex_path];
			if (tex_id === undefined) {
				tex_id = layer_info._user_info.tex_id_max + 1;
				layer_info._user_info.tex_id_max = tex_id;
				layer_info._user_info.tex_id_map[brush_info.tex_path] = tex_id;
				layer_info._user_info.tile_map.tex_map.set(tex_id, brush_info.tex_path);
			}
			cell.tex_id = tex_id;
			let image = this.GetImage(layer_index, row, col);
			image.SetTextureCut(brush_info.module_path, 0, 0, true);
			let revoke = ALittle.NewObject(ALittleIDE.IDETileBrushCellRevoke, this, layer_info, cell, image, old_tex_path, brush_info.tex_path);
			this._revoke_list.PushRevoke(revoke);
			this.save = false;
		} else if (ALittleIDE.g_IDECenter.center.tile_erase) {
			let [layer_info, layer_index] = this._layer_edit.GetCurLayerInfo();
			if (layer_info === undefined) {
				g_AUITool.ShowNotice("提示", "请先选择图层");
				return;
			}
			let [row, col] = ALittle.Tile_CalcRowColByPos(this._user_info.tile_map, event.rel_x, event.rel_y);
			if (row <= 0 || col <= 0) {
				return;
			}
			this.ResizeGridMap(row, col);
			this._drag_cell_row = row;
			this._drag_cell_col = col;
			let col_map = layer_info._layer.cell_map.get(row);
			if (col_map === undefined) {
				return;
			}
			let cell = col_map.get(col);
			if (cell === undefined) {
				return;
			}
			if (cell.tex_id === undefined) {
				return;
			}
			let old_tex_path = layer_info._user_info.tile_map.tex_map.get(cell.tex_id);
			cell.tex_id = undefined;
			let image = this.GetImage(layer_index, row, col);
			image.SetTextureCut(undefined, 0, 0, true);
			let revoke = ALittle.NewObject(ALittleIDE.IDETileBrushCellRevoke, this, layer_info, cell, image, old_tex_path, undefined);
			this._revoke_list.PushRevoke(revoke);
			this.save = false;
		}
	},
	HandleQuadDragBegin : function(event) {
		if (ALittleIDE.g_IDECenter.center.tile_handdrag) {
			event.target = this._tab_screen;
			this._tab_screen.DispatchEvent(___all_struct.get(1301789264), event);
		}
	},
	HandleQuadDrag : function(event) {
		if (ALittleIDE.g_IDECenter.center.tile_brush) {
			let brush_info = ALittleIDE.g_IDECenter.center.tile_brush_edit.GetBrush();
			if (brush_info === undefined) {
				return;
			}
			let [layer_info, layer_index] = this._layer_edit.GetCurLayerInfo();
			if (layer_info === undefined) {
				return;
			}
			let [row, col] = ALittle.Tile_CalcRowColByPos(this._user_info.tile_map, event.rel_x, event.rel_y);
			if (row <= 0 || col <= 0) {
				return;
			}
			this.ResizeGridMap(row, col);
			if (this._drag_cell_row === row && this._drag_cell_col === col) {
				return;
			}
			this._drag_cell_row = row;
			this._drag_cell_col = col;
			let col_map = layer_info._layer.cell_map.get(row);
			if (col_map === undefined) {
				col_map = new Map();
				layer_info._layer.cell_map.set(row, col_map);
			}
			let cell = col_map.get(col);
			if (cell === undefined) {
				cell = {};
				col_map.set(col, cell);
			}
			let old_tex_path = undefined;
			if (cell.tex_id !== undefined) {
				old_tex_path = layer_info._user_info.tile_map.tex_map.get(cell.tex_id);
			}
			let tex_id = layer_info._user_info.tex_id_map[brush_info.tex_path];
			if (tex_id === undefined) {
				tex_id = layer_info._user_info.tex_id_max + 1;
				layer_info._user_info.tex_id_max = tex_id;
				layer_info._user_info.tex_id_map[brush_info.tex_path] = tex_id;
				layer_info._user_info.tile_map.tex_map.set(tex_id, brush_info.tex_path);
			}
			cell.tex_id = tex_id;
			let image = this.GetImage(layer_index, row, col);
			image.SetTextureCut(brush_info.module_path, 0, 0, true);
			let revoke = ALittle.NewObject(ALittleIDE.IDETileBrushCellRevoke, this, layer_info, cell, image, old_tex_path, brush_info.tex_path);
			this._revoke_list.PushRevoke(revoke);
			this.save = false;
		} else if (ALittleIDE.g_IDECenter.center.tile_handdrag) {
			event.target = this._tab_screen;
			this._tab_screen.DispatchEvent(___all_struct.get(1337289812), event);
		} else if (ALittleIDE.g_IDECenter.center.tile_erase) {
			let [layer_info, layer_index] = this._layer_edit.GetCurLayerInfo();
			if (layer_info === undefined) {
				return;
			}
			let [row, col] = ALittle.Tile_CalcRowColByPos(this._user_info.tile_map, event.rel_x, event.rel_y);
			if (row <= 0 || col <= 0) {
				return;
			}
			this.ResizeGridMap(row, col);
			if (this._drag_cell_row === row && this._drag_cell_col === col) {
				return;
			}
			this._drag_cell_row = row;
			this._drag_cell_col = col;
			let col_map = layer_info._layer.cell_map.get(row);
			if (col_map === undefined) {
				return;
			}
			let cell = col_map.get(col);
			if (cell === undefined) {
				return;
			}
			if (cell.tex_id === undefined) {
				return;
			}
			let old_tex_path = layer_info._user_info.tile_map.tex_map.get(cell.tex_id);
			cell.tex_id = undefined;
			let image = this.GetImage(layer_index, row, col);
			image.SetTextureCut(undefined, 0, 0, true);
			let revoke = ALittle.NewObject(ALittleIDE.IDETileBrushCellRevoke, this, layer_info, cell, image, old_tex_path, undefined);
			this._revoke_list.PushRevoke(revoke);
			this.save = false;
		}
	},
	HandleQuadDragEnd : function(event) {
		if (ALittleIDE.g_IDECenter.center.tile_brush) {
		} else if (ALittleIDE.g_IDECenter.center.tile_handdrag) {
			event.target = this._tab_screen;
			this._tab_screen.DispatchEvent(___all_struct.get(150587926), event);
		} else if (ALittleIDE.g_IDECenter.center.tile_erase) {
		}
		this._drag_cell_row = undefined;
		this._drag_cell_col = undefined;
	},
	get layer_edit() {
		return this._layer_edit;
	},
	OnUndo : function() {
	},
	OnRedo : function() {
	},
	OnHide : function() {
		ALittleIDE.g_IDECenter.center.tool_tile.visible = false;
		this._layer_edit.visible = false;
	},
	OnShow : function() {
		ALittleIDE.g_IDECenter.center.tool_tile.visible = true;
		this._layer_edit.visible = true;
		ALittleIDE.g_IDECenter.center.detail_tree_tab.tab = ALittleIDE.g_IDECenter.center.tile_brush_edit;
		ALittleIDE.g_IDECenter.center.project_edit_tab.tab = ALittleIDE.g_IDECenter.center.tile_brush_list;
	},
	OnClose : function() {
		ALittleIDE.g_IDECenter.center.tile_brush_edit.layer_container.RemoveChild(this._layer_edit);
	},
	OnOpen : function() {
		this._revoke_list = ALittle.NewObject(ALittle.RevokeList, 10000);
		ALittleIDE.g_IDECenter.center.tile_brush_edit.layer_container.AddChild(this._layer_edit);
	},
	OnTabRightMenu : function(menu) {
		menu.AddItem("获取焦点", this.ShowTileFocus.bind(this));
	},
	ShowTileFocus : function() {
		let tree = ALittleIDE.g_IDECenter.center.tile_list.GetFileTree(this._user_info.info.path);
		if (tree === undefined) {
			return;
		}
		ALittleIDE.g_IDECenter.center.project_edit_tab.tab = ALittleIDE.g_IDECenter.center.tile_list;
		ALittleIDE.g_IDECenter.center.tile_list.ShowTreeItemFocus(tree);
	},
	CreateLayer : function() {
		let group = ALittle.NewObject(ALittle.DisplayGroup, ALittleIDE.g_Control);
		let linear_1 = ALittle.NewObject(ALittle.Linear, ALittleIDE.g_Control);
		linear_1.type = 2;
		group.AddChild(linear_1);
		let linear_2 = ALittle.NewObject(ALittle.Linear, ALittleIDE.g_Control);
		linear_2.type = 2;
		linear_2.x = ALittle.Tile_CalcLinear2OffsetX(this._user_info.tile_map);
		linear_2.y = ALittle.Tile_CalcLinear2OffsetY(this._user_info.tile_map);
		group.AddChild(linear_2);
		this._group_tile.AddChild(group);
		let row_count = this._linear_grid_1.child_count;
		let col_count = this._linear_grid_1.childs[1 - 1].child_count;
		this.ResizeLinear(linear_1, linear_2, row_count, col_count, this._group_tile.child_count);
		return [group, linear_1, linear_2];
	},
	GetLayer : function(index) {
		let group = this._group_tile.GetChildByIndex(index);
		if (group === undefined) {
			return [undefined, undefined, undefined];
		}
		let linear_1 = group.GetChildByIndex(1);
		let linear_2 = group.GetChildByIndex(2);
		return [group, linear_1, linear_2];
	},
	GetImage : function(layer, row, col) {
		let [group, linear_1, linear_2] = this.GetLayer(layer);
		if (group === undefined) {
			return undefined;
		}
		let tile_type = this._user_info.tile_map.tile_type;
		if (tile_type === 2) {
			if (row % 2 === 1) {
				return linear_1.childs[ALittle.Math_Floor(row / 2) + 1 - 1].childs[col - 1]._user_data;
			}
			return linear_2.childs[ALittle.Math_Floor(row / 2) - 1].childs[col - 1]._user_data;
		} else {
			if (col % 2 === 1) {
				return linear_1.childs[row - 1].childs[ALittle.Math_Floor(col / 2) + 1 - 1]._user_data;
			}
			return linear_2.childs[row - 1].childs[ALittle.Math_Floor(col / 2) - 1]._user_data;
		}
	},
	AddLayer : function(group, index) {
		this._group_tile.AddChild(group, index);
	},
	RemoveLayer : function(group) {
		this._group_tile.RemoveChild(group);
	},
	SetLayerIndex : function(group, index) {
		this._group_tile.SetChildIndex(group, index);
	},
	get tab_body() {
		return this._tab_screen;
	},
	set save(value) {
		if (this._save === value) {
			return;
		}
		if (value === false) {
			this._save = false;
			this.UpdateTitle();
			return;
		}
		let ui = ALittleIDE.g_IDEProject.project.ui[ALittleIDE.g_IDEProject.project.name];
		if (ui === undefined) {
			g_AUITool.ShowNotice("提示", "ui不存在");
			return;
		}
		let row_count = 0;
		let col_count = 0;
		let ___OBJECT_4 = this._user_info.tile_map.layer_list;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let layer = ___OBJECT_4[index - 1];
			if (layer === undefined) break;
			for (let [row, cell_map] of layer.cell_map) {
				if (cell_map === undefined) continue;
				for (let [col, cell] of cell_map) {
					if (cell === undefined) continue;
					if (col > col_count) {
						col_count = col;
					}
				}
				if (row > row_count) {
					row_count = row;
				}
			}
		}
		this._user_info.tile_map.row_count = row_count;
		this._user_info.tile_map.col_count = col_count;
		ui.control.WriteMessageToFile(___all_struct.get(-1281734132), this._user_info.tile_map, this._user_info.info.path);
		this._save = value;
		this.UpdateTitle();
	},
	get id() {
		return this._user_info.info.path;
	},
	Rename : function(name) {
		this._name = name;
		this.UpdateTitle();
	},
	UpdateTitle : function() {
		let text = this._name;
		if (this._save === false) {
			text = text + " *";
		}
		ALittleIDE.g_IDECenter.center.content_edit.main_tab.SetChildText(this._tab_screen, text);
	},
	get title() {
		return this._name;
	},
	UpdateUserInfo : function(info) {
		this._user_info = info;
	},
	CreateBySelect : function(info) {
		this._user_info = info;
		info.tex_id_map = {};
		info.tex_id_max = 0;
		for (let [tex_id, tex_path] of info.tile_map.tex_map) {
			if (tex_path === undefined) continue;
			info.tex_id_map[tex_path] = tex_id;
			if (info.tex_id_max < tex_id) {
				info.tex_id_max = tex_id;
			}
		}
		let col_count = info.tile_map.col_count;
		if (col_count < 10) {
			col_count = 10;
		}
		let row_count = info.tile_map.row_count;
		if (row_count < 10) {
			row_count = 10;
		}
		let grid_map_width = ALittle.Tile_CalcCellWidth(this._user_info.tile_map) * col_count;
		this._linear_grid_1.width = grid_map_width;
		this._linear_grid_2.width = grid_map_width;
		this._linear_grid_2.x = ALittle.Tile_CalcLinear2OffsetX(this._user_info.tile_map);
		this._linear_grid_2.y = ALittle.Tile_CalcLinear2OffsetY(this._user_info.tile_map);
		let ___OBJECT_5 = info.tile_map.layer_list;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let layer = ___OBJECT_5[index - 1];
			if (layer === undefined) break;
			let group = ALittle.NewObject(ALittle.DisplayGroup, ALittleIDE.g_Control);
			let linear_1 = ALittle.NewObject(ALittle.Linear, ALittleIDE.g_Control);
			linear_1.type = 2;
			linear_1.width = grid_map_width;
			group.AddChild(linear_1);
			let linear_2 = ALittle.NewObject(ALittle.Linear, ALittleIDE.g_Control);
			linear_2.type = 2;
			linear_2.width = grid_map_width;
			linear_2.x = ALittle.Tile_CalcLinear2OffsetX(this._user_info.tile_map);
			linear_2.y = ALittle.Tile_CalcLinear2OffsetY(this._user_info.tile_map);
			group.AddChild(linear_2);
			this._group_tile.AddChild(group);
		}
		this.ResizeGridMap(row_count, col_count);
		let ___OBJECT_6 = this._user_info.tile_map.layer_list;
		for (let index = 1; index <= ___OBJECT_6.length; ++index) {
			let layer = ___OBJECT_6[index - 1];
			if (layer === undefined) break;
			for (let [row, col_map] of layer.cell_map) {
				if (col_map === undefined) continue;
				for (let [col, cell] of col_map) {
					if (cell === undefined) continue;
					if (cell.tex_id !== undefined) {
						let texture_name = this._user_info.tile_map.tex_map.get(cell.tex_id);
						if (texture_name !== undefined) {
							let image = this.GetImage(index, row, col);
							image.SetTextureCut("Module/" + ALittleIDE.g_IDEProject.project.name + "/Texture/" + texture_name, 0, 0, true);
						}
					}
				}
			}
		}
		this._layer_edit.Init(this, this._user_info);
		this._tab_screen.RefreshClipDisLine();
	},
	ResizeLinear : function(linear_1, linear_2, row_count, col_count, layer) {
		if (this._user_info.tile_map.tile_type === 2) {
			if (row_count <= linear_1.child_count + linear_2.child_count && col_count <= linear_1.childs[1 - 1].child_count) {
				return;
			}
			linear_1.width = ALittle.Tile_CalcCellWidth(this._user_info.tile_map) * col_count;
			linear_2.width = linear_1.width;
			let linear_height = ALittle.Tile_CalcCellHeight(this._user_info.tile_map);
			let ___OBJECT_7 = linear_1.childs;
			for (let index = 1; index <= ___OBJECT_7.length; ++index) {
				let child = ___OBJECT_7[index - 1];
				if (child === undefined) break;
				for (let col = child.child_count + 1; col <= col_count; col += 1) {
					if (layer === 0) {
						child.AddChild(this.CreateGrid());
					} else {
						child.AddChild(this.CreateImage());
					}
				}
			}
			let ___OBJECT_8 = linear_2.childs;
			for (let index = 1; index <= ___OBJECT_8.length; ++index) {
				let child = ___OBJECT_8[index - 1];
				if (child === undefined) break;
				for (let col = child.child_count + 1; col <= col_count; col += 1) {
					if (layer === 0) {
						child.AddChild(this.CreateGrid());
					} else {
						child.AddChild(this.CreateImage());
					}
				}
			}
			for (let row = linear_1.child_count + linear_2.child_count + 1; row <= row_count; row += 1) {
				let linear = ALittle.NewObject(ALittle.Linear, ALittleIDE.g_Control);
				linear.type = 1;
				linear.height = linear_height;
				for (let col = 1; col <= col_count; col += 1) {
					if (layer === 0) {
						linear.AddChild(this.CreateGrid());
					} else {
						linear.AddChild(this.CreateImage());
					}
				}
				if (row % 2 === 1) {
					linear_1.AddChild(linear);
				} else {
					linear_2.AddChild(linear);
				}
			}
		} else {
			if (row_count <= linear_1.child_count && col_count <= linear_1.childs[1 - 1].child_count + linear_2.childs[1 - 1].child_count) {
				return;
			}
			let cell_width = ALittle.Tile_CalcCellWidth(this._user_info.tile_map);
			let linear_height = ALittle.Tile_CalcCellHeight(this._user_info.tile_map);
			let col_count_1 = ALittle.Math_Ceil(col_count / 2);
			linear_1.width = cell_width * col_count_1;
			let ___OBJECT_9 = linear_1.childs;
			for (let index = 1; index <= ___OBJECT_9.length; ++index) {
				let child = ___OBJECT_9[index - 1];
				if (child === undefined) break;
				for (let col = child.child_count + 1; col <= col_count_1; col += 1) {
					if (layer === 0) {
						child.AddChild(this.CreateGrid());
					} else {
						child.AddChild(this.CreateImage());
					}
				}
			}
			let col_count_2 = ALittle.Math_Floor(col_count / 2);
			linear_2.width = cell_width * col_count_2;
			let ___OBJECT_10 = linear_2.childs;
			for (let index = 1; index <= ___OBJECT_10.length; ++index) {
				let child = ___OBJECT_10[index - 1];
				if (child === undefined) break;
				for (let col = child.child_count + 1; col <= col_count_2; col += 1) {
					if (layer === 0) {
						child.AddChild(this.CreateGrid());
					} else {
						child.AddChild(this.CreateImage());
					}
				}
			}
			for (let row = linear_1.child_count + 1; row <= row_count; row += 1) {
				let linear = ALittle.NewObject(ALittle.Linear, ALittleIDE.g_Control);
				linear.type = 1;
				linear.height = linear_height;
				for (let col = 1; col <= col_count_1; col += 1) {
					if (layer === 0) {
						linear.AddChild(this.CreateGrid());
					} else {
						linear.AddChild(this.CreateImage());
					}
				}
				linear_1.AddChild(linear);
			}
			for (let row = linear_2.child_count + 1; row <= row_count; row += 1) {
				let linear = ALittle.NewObject(ALittle.Linear, ALittleIDE.g_Control);
				linear.type = 1;
				linear.height = linear_height;
				for (let col = 1; col <= col_count_2; col += 1) {
					if (layer === 0) {
						linear.AddChild(this.CreateGrid());
					} else {
						linear.AddChild(this.CreateImage());
					}
				}
				linear_2.AddChild(linear);
			}
		}
	},
	ResizeGridMap : function(row_count, col_count) {
		let cur_row_count = 0;
		let cur_col_count = 0;
		if (this._user_info.tile_map.tile_type === 2) {
			cur_row_count = this._linear_grid_1.child_count + this._linear_grid_2.child_count;
			if (cur_row_count > 0) {
				cur_col_count = this._linear_grid_1.childs[1 - 1].child_count;
			}
		} else {
			cur_row_count = this._linear_grid_1.child_count;
			if (cur_row_count > 0) {
				cur_col_count = this._linear_grid_1.childs[1 - 1].child_count + this._linear_grid_2.childs[1 - 1].child_count;
			}
		}
		if (row_count < cur_row_count) {
			row_count = cur_row_count;
		}
		if (col_count < cur_col_count) {
			col_count = cur_col_count;
		}
		this.ResizeLinear(this._linear_grid_1, this._linear_grid_2, row_count, col_count, 0);
		let ___OBJECT_11 = this._group_tile.childs;
		for (let index = 1; index <= ___OBJECT_11.length; ++index) {
			let group = ___OBJECT_11[index - 1];
			if (group === undefined) break;
			this.ResizeLinear(group.GetChildByIndex(1), group.GetChildByIndex(2), row_count, col_count, index);
		}
		let width_1 = this._linear_grid_1.x + this._linear_grid_1.width;
		let width_2 = this._linear_grid_2.x + this._linear_grid_2.width;
		let height_1 = this._linear_grid_1.y + this._linear_grid_1.height;
		let height_2 = this._linear_grid_2.y + this._linear_grid_2.height;
		this._tab_screen.container.width = ALittle.Math_Max(width_1, width_2) + 100;
		this._tab_screen.container.height = ALittle.Math_Max(height_1, height_2) + 100;
		this._tab_screen.AdjustScrollBar();
	},
	CreateGrid : function() {
		let tile_type = this._user_info.tile_map.tile_type;
		let side_len = this._user_info.tile_map.side_len;
		if (tile_type === 1) {
			let cell = ALittle.NewObject(ALittle.DisplayLayout, ALittleIDE.g_Control);
			cell.width = ALittle.Tile_CalcCellWidth(this._user_info.tile_map);
			let grid = ALittleIDE.g_Control.CreateControl("ide_tile_square_grid");
			grid.width = side_len;
			grid.height = side_len;
			cell.AddChild(grid);
			return cell;
		}
		if (tile_type === 2) {
			let cell = ALittle.NewObject(ALittle.DisplayLayout, ALittleIDE.g_Control);
			cell.width = ALittle.Tile_CalcCellWidth(this._user_info.tile_map);
			let grid = ALittleIDE.g_Control.CreateControl("ide_tile_hex_v_grid");
			grid.width = side_len * 1.732;
			grid.height = side_len * 2;
			cell.AddChild(grid);
			return cell;
		}
		if (tile_type === 3) {
			let cell = ALittle.NewObject(ALittle.DisplayLayout, ALittleIDE.g_Control);
			cell.width = ALittle.Tile_CalcCellWidth(this._user_info.tile_map);
			let grid = ALittleIDE.g_Control.CreateControl("ide_tile_hex_h_grid");
			grid.width = side_len * 2;
			grid.height = side_len * 1.732;
			cell.AddChild(grid);
			return cell;
		}
		return undefined;
	},
	CreateImage : function() {
		let tile_type = this._user_info.tile_map.tile_type;
		let side_len = this._user_info.tile_map.side_len;
		if (tile_type === 1) {
			let cell = ALittle.NewObject(ALittle.DisplayLayout, ALittleIDE.g_Control);
			cell.width = ALittle.Tile_CalcCellWidth(this._user_info.tile_map);
			let grid = ALittle.NewObject(ALittle.Image, ALittleIDE.g_Control);
			cell._user_data = grid;
			grid.width = this._user_info.tile_map.tile_width;
			grid.height = this._user_info.tile_map.tile_height;
			grid.x = this._user_info.tile_map.tile_x;
			grid.y = this._user_info.tile_map.tile_y;
			cell.AddChild(grid);
			return cell;
		}
		if (tile_type === 2) {
			let cell = ALittle.NewObject(ALittle.DisplayLayout, ALittleIDE.g_Control);
			cell.width = ALittle.Tile_CalcCellWidth(this._user_info.tile_map);
			let grid = ALittle.NewObject(ALittle.Image, ALittleIDE.g_Control);
			cell._user_data = grid;
			grid.width = this._user_info.tile_map.tile_width;
			grid.height = this._user_info.tile_map.tile_height;
			grid.x = this._user_info.tile_map.tile_x;
			grid.y = this._user_info.tile_map.tile_y;
			cell.AddChild(grid);
			return cell;
		}
		if (tile_type === 3) {
			let cell = ALittle.NewObject(ALittle.DisplayLayout, ALittleIDE.g_Control);
			cell.width = ALittle.Tile_CalcCellWidth(this._user_info.tile_map);
			let grid = ALittle.NewObject(ALittle.Image, ALittleIDE.g_Control);
			cell._user_data = grid;
			grid.width = this._user_info.tile_map.tile_width;
			grid.height = this._user_info.tile_map.tile_height;
			grid.x = this._user_info.tile_map.tile_x;
			grid.y = this._user_info.tile_map.tile_y;
			cell.AddChild(grid);
			return cell;
		}
		return undefined;
	},
}, "ALittleIDE.IDETileTabChild");

}