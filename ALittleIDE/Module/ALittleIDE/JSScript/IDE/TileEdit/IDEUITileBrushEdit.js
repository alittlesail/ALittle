{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(1575666720, "ALittleIDE.IDEUITileBrushInfo", {
name : "ALittleIDE.IDEUITileBrushInfo", ns_name : "ALittleIDE", rl_name : "IDEUITileBrushInfo", hash_code : 1575666720,
name_list : ["_image","_item","tex_path","module_path"],
type_list : ["ALittle.Image","ALittle.DisplayLayout","string","string"],
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
ALittle.RegStruct(-1281734132, "ALittle.TileMap", {
name : "ALittle.TileMap", ns_name : "ALittle", rl_name : "TileMap", hash_code : -1281734132,
name_list : ["tile_type","side_len","tile_width","tile_height","tile_x","tile_y","col_count","row_count","tex_map","layer_list"],
type_list : ["int","int","int","int","int","int","int","int","Map<int,string>","List<ALittle.TileLayer>"],
option_map : {}
})
ALittle.RegStruct(-686652419, "AUIPlugin.AUIFileTreeUserInfo", {
name : "AUIPlugin.AUIFileTreeUserInfo", ns_name : "AUIPlugin", rl_name : "AUIFileTreeUserInfo", hash_code : -686652419,
name_list : ["path","name","root","group","on_right_menu","on_select_file","on_delete_file","on_create_file","on_delete_dir"],
type_list : ["string","string","bool","Map<ALittle.TextRadioButton,bool>","Functor<(AUIPlugin.AUIFileTreeUserInfo,AUIPlugin.AUIRightMenu)>","Functor<(AUIPlugin.AUIFileTreeUserInfo)>","Functor<(string)>","Functor<(string)>","Functor<(string)>"],
option_map : {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-343663763, "ALittle.TileLayer", {
name : "ALittle.TileLayer", ns_name : "ALittle", rl_name : "TileLayer", hash_code : -343663763,
name_list : ["name","cell_map"],
type_list : ["string","Map<int,Map<int,ALittle.TileCell>>"],
option_map : {}
})
ALittle.RegStruct(274315553, "ALittleIDE.IDEUITileLayerInfo", {
name : "ALittleIDE.IDEUITileLayerInfo", ns_name : "ALittleIDE", rl_name : "IDEUITileLayerInfo", hash_code : 274315553,
name_list : ["_button","_item","_see_image","_layer","_user_info","_group","_linear_1","_linear_2"],
type_list : ["ALittle.TextRadioButton","ALittle.DisplayLayout","ALittle.Image","ALittle.TileLayer","ALittleIDE.IDETileTreeUserInfo","ALittle.DisplayGroup","ALittle.Linear","ALittle.Linear"],
option_map : {}
})
ALittle.RegStruct(7944876, "ALittle.TileCell", {
name : "ALittle.TileCell", ns_name : "ALittle", rl_name : "TileCell", hash_code : 7944876,
name_list : ["tex_id"],
type_list : ["int"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEUITileBrushEdit = JavaScript.Class(ALittle.DisplayLayout, {
	TCtor : function() {
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-975432877), this, this.HandleProjectOpen);
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-332308624), this, this.HandleProjectClose);
	},
	get layer_container() {
		return this._layer_container;
	},
	HandleClearBrushClick : function(event) {
		this._brush_list.RemoveAllChild();
	},
	HandleProjectOpen : function(event) {
		this._brush_list.RemoveAllChild();
	},
	HandleProjectClose : function(event) {
		this._brush_list.RemoveAllChild();
	},
	AddBrushList : function(module_path_list, tex_path_list, ctrl) {
		if (!ctrl) {
			this._brush_list.RemoveAllChild();
		}
		let ___OBJECT_1 = module_path_list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let module_path = ___OBJECT_1[index - 1];
			if (module_path === undefined) break;
			let tex_path = tex_path_list[index - 1];
			let info = {};
			info._item = ALittleIDE.g_Control.CreateControl("ide_tile_brush_item", info);
			info._image.SetTextureCut(module_path, 0, 0, true);
			info.tex_path = tex_path;
			info.module_path = module_path;
			info._item._user_data = info;
			this._brush_list.AddChild(info._item);
		}
	},
	GetBrush : function() {
		let child_count = this._brush_list.child_count;
		if (child_count === 0) {
			return undefined;
		}
		if (child_count === 1) {
			return this._brush_list.childs[1 - 1]._user_data;
		}
		let index = ALittle.Math_RandomInt(1, child_count);
		return this._brush_list.childs[index - 1]._user_data;
	},
}, "ALittleIDE.IDEUITileBrushEdit");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEUITileLayerEdit = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._group = new Map();
	},
	Init : function(tab_child, user_info) {
		this._tab_child = tab_child;
		this._user_info = user_info;
		let ___OBJECT_2 = user_info.tile_map.layer_list;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let layer = ___OBJECT_2[index - 1];
			if (layer === undefined) break;
			let info = {};
			info._user_info = this._user_info;
			info._item = ALittleIDE.g_Control.CreateControl("ide_tile_layer_item", info);
			info._button.text = layer.name;
			info._button.group = this._group;
			info._button._user_data = info;
			info._button.AddEventListener(___all_struct.get(-641444818), this, this.HandleRButtonDown);
			info._item._user_data = info;
			this._layer_list.AddChild(info._item);
			info._layer = layer;
			[info._group, info._linear_1, info._linear_2] = this._tab_child.GetLayer(index);
		}
		if (this._layer_list.child_count > 0) {
			let info = this._layer_list.childs[this._layer_list.child_count - 1]._user_data;
			info._button.selected = true;
		}
	},
	get layer_list() {
		return this._layer_list;
	},
	GetCurLayerInfo : function() {
		let ___OBJECT_3 = this._layer_list.childs;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let child = ___OBJECT_3[index - 1];
			if (child === undefined) break;
			let info = child._user_data;
			if (info._button.selected) {
				return [info, index];
			}
		}
		return [undefined, undefined];
	},
	HandleAddLayerClick : async function(event) {
		let [x, y] = event.target.LocalToGlobal();
		let name = await g_AUITool.ShowRename("", x, y + event.target.height, 200);
		if (name === undefined || name === "") {
			return;
		}
		let info = {};
		info._user_info = this._user_info;
		info._item = ALittleIDE.g_Control.CreateControl("ide_tile_layer_item", info);
		info._button.text = name;
		info._button.group = this._group;
		info._button._user_data = info;
		info._button.AddEventListener(___all_struct.get(-641444818), this, this.HandleRButtonDown);
		info._item._user_data = info;
		this._layer_list.AddChild(info._item);
		if (this._layer_list.child_count === 1) {
			info._button.selected = true;
		}
		info._layer = {};
		info._layer.name = name;
		info._layer.cell_map = new Map();
		ALittle.List_Push(this._user_info.tile_map.layer_list, info._layer);
		[info._group, info._linear_1, info._linear_2] = this._tab_child.CreateLayer();
		let revoke = ALittle.NewObject(ALittleIDE.IDETileAddLayerRevoke, this._tab_child, info);
		this._tab_child.revoke_list.PushRevoke(revoke);
		this._tab_child.save = false;
	},
	HandleRButtonDown : function(event) {
		let info = event.target._user_data;
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("重命名", this.HandleRenameLayer.bind(this, info));
		menu.AddItem("删除", this.HandleDeleteLayer.bind(this, info));
		menu.AddItem("上移", this.HandleUpLayer.bind(this, info));
		menu.AddItem("下移", this.HandleDownLayer.bind(this, info));
		if (info._see_image.visible) {
			menu.AddItem("隐藏", this.HandleHideLayer.bind(this, info));
		} else {
			menu.AddItem("显示", this.HandleShowLayer.bind(this, info));
		}
		menu.Show();
	},
	HandleRenameLayer : async function(info) {
		let [x, y] = info._button.LocalToGlobal();
		let name = await g_AUITool.ShowRename(info._button.text, x, y + info._button.height, 200);
		if (name === undefined || name === "") {
			return;
		}
		let old_name = info._layer.name;
		info._button.text = name;
		info._layer.name = name;
		let revoke = ALittle.NewObject(ALittleIDE.IDETileRenameLayerRevoke, this._tab_child, info, old_name, name);
		this._tab_child.revoke_list.PushRevoke(revoke);
		this._tab_child.save = false;
	},
	HandleDeleteLayer : async function(info) {
		if (await g_AUITool.DeleteNotice("删除", "确定要删除该图层吗?") !== "YES") {
			return;
		}
		let index = this._layer_list.GetChildIndex(info._item);
		this._layer_list.RemoveChild(info._item);
		if (info._button.selected && this._layer_list.child_count > 0) {
			this._layer_list.childs[1 - 1]._user_data._button.selected = true;
		}
		ALittle.List_Remove(info._user_info.tile_map.layer_list, index);
		this._tab_child.RemoveLayer(info._group);
		let revoke = ALittle.NewObject(ALittleIDE.IDETileDeleteLayerRevoke, this._tab_child, info, index);
		this._tab_child.revoke_list.PushRevoke(revoke);
		this._tab_child.save = false;
	},
	HandleUpLayer : function(info) {
		let index = this._layer_list.GetChildIndex(info._item);
		if (index === undefined || index === 1) {
			return;
		}
		this._layer_list.SetChildIndex(info._item, index - 1);
		ALittle.List_Remove(info._user_info.tile_map.layer_list, index);
		ALittle.List_Insert(info._user_info.tile_map.layer_list, index - 1, info._layer);
		this._tab_child.SetLayerIndex(info._group, index);
		let revoke = ALittle.NewObject(ALittleIDE.IDETileSetLayerIndexRevoke, this._tab_child, info, index, index - 1);
		this._tab_child.revoke_list.PushRevoke(revoke);
		this._tab_child.save = false;
	},
	HandleDownLayer : function(info) {
		let index = this._layer_list.GetChildIndex(info._item);
		if (index === undefined || index === this._layer_list.child_count) {
			return;
		}
		this._layer_list.SetChildIndex(info._item, index + 1);
		ALittle.List_Remove(info._user_info.tile_map.layer_list, index);
		ALittle.List_Insert(info._user_info.tile_map.layer_list, index + 1, info._layer);
		this._tab_child.SetLayerIndex(info._group, index + 1);
		let revoke = ALittle.NewObject(ALittleIDE.IDETileSetLayerIndexRevoke, this._tab_child, info, index, index + 1);
		this._tab_child.revoke_list.PushRevoke(revoke);
		this._tab_child.save = false;
	},
	HandleHideLayer : function(info) {
		info._see_image.visible = false;
		info._linear_1.visible = false;
		info._linear_2.visible = false;
	},
	HandleShowLayer : function(info) {
		info._see_image.visible = true;
		info._linear_1.visible = true;
		info._linear_2.visible = true;
	},
}, "ALittleIDE.IDEUITileLayerEdit");

}