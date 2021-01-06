{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittle.RevokeObject === undefined) throw new Error(" extends class:ALittle.RevokeObject is undefined");
ALittleIDE.IDETileAddLayerRevoke = JavaScript.Class(ALittle.RevokeObject, {
	Ctor : function(tab_child, layer_info) {
		this._tab_child = tab_child;
		this._layer_info = layer_info;
	},
	Forward : function() {
		this._tab_child.layer_edit.layer_list.AddChild(this._layer_info._item);
		ALittle.List_Push(this._layer_info._user_info.tile_map.layer_list, this._layer_info._layer);
	},
	Back : function() {
		this._tab_child.layer_edit.layer_list.RemoveChild(this._layer_info._item);
		let index = ALittle.List_IndexOf(this._layer_info._user_info.tile_map.layer_list, this._layer_info._layer);
		ALittle.List_Remove(this._layer_info._user_info.tile_map.layer_list, index);
	},
}, "ALittleIDE.IDETileAddLayerRevoke");

if (ALittle.RevokeObject === undefined) throw new Error(" extends class:ALittle.RevokeObject is undefined");
ALittleIDE.IDETileDeleteLayerRevoke = JavaScript.Class(ALittle.RevokeObject, {
	Ctor : function(tab_child, layer_info, index) {
		this._tab_child = tab_child;
		this._layer_info = layer_info;
		this._index = index;
	},
	Forward : function() {
		this._tab_child.layer_edit.layer_list.RemoveChild(this._layer_info._item);
		let index = ALittle.List_IndexOf(this._layer_info._user_info.tile_map.layer_list, this._layer_info._layer);
		ALittle.List_Remove(this._layer_info._user_info.tile_map.layer_list, index);
		this._tab_child.RemoveLayer(this._layer_info._group);
	},
	Back : function() {
		this._tab_child.layer_edit.layer_list.AddChild(this._layer_info._item, this._index);
		ALittle.List_Insert(this._layer_info._user_info.tile_map.layer_list, this._index, this._layer_info._layer);
		this._tab_child.AddLayer(this._layer_info._group, this._index);
	},
}, "ALittleIDE.IDETileDeleteLayerRevoke");

if (ALittle.RevokeObject === undefined) throw new Error(" extends class:ALittle.RevokeObject is undefined");
ALittleIDE.IDETileSetLayerIndexRevoke = JavaScript.Class(ALittle.RevokeObject, {
	Ctor : function(tab_child, layer_info, old_index, new_index) {
		this._tab_child = tab_child;
		this._layer_info = layer_info;
		this._old_index = old_index;
		this._new_index = new_index;
	},
	Forward : function() {
		this._tab_child.layer_edit.layer_list.SetChildIndex(this._layer_info._item, this._new_index);
		ALittle.List_Remove(this._layer_info._user_info.tile_map.layer_list, this._old_index);
		ALittle.List_Insert(this._layer_info._user_info.tile_map.layer_list, this._new_index, this._layer_info._layer);
		this._tab_child.SetLayerIndex(this._layer_info._group, this._new_index);
	},
	Back : function() {
		this._tab_child.layer_edit.layer_list.SetChildIndex(this._layer_info._item, this._old_index);
		ALittle.List_Remove(this._layer_info._user_info.tile_map.layer_list, this._new_index);
		ALittle.List_Insert(this._layer_info._user_info.tile_map.layer_list, this._old_index, this._layer_info._layer);
		this._tab_child.SetLayerIndex(this._layer_info._group, this._old_index);
	},
}, "ALittleIDE.IDETileSetLayerIndexRevoke");

if (ALittle.RevokeObject === undefined) throw new Error(" extends class:ALittle.RevokeObject is undefined");
ALittleIDE.IDETileRenameLayerRevoke = JavaScript.Class(ALittle.RevokeObject, {
	Ctor : function(tab_child, layer_info, old_name, new_name) {
		this._tab_child = tab_child;
		this._layer_info = layer_info;
		this._old_name = old_name;
		this._new_name = new_name;
	},
	Forward : function() {
		this._layer_info._button.text = this._new_name;
		this._layer_info._layer.name = this._new_name;
	},
	Back : function() {
		this._layer_info._button.text = this._old_name;
		this._layer_info._layer.name = this._old_name;
	},
}, "ALittleIDE.IDETileRenameLayerRevoke");

if (ALittle.RevokeObject === undefined) throw new Error(" extends class:ALittle.RevokeObject is undefined");
ALittleIDE.IDETileBrushCellRevoke = JavaScript.Class(ALittle.RevokeObject, {
	Ctor : function(tab_child, layer_info, cell, image, old_tex_path, new_tex_path) {
		this._tab_child = tab_child;
		this._layer_info = layer_info;
		this._cell = cell;
		this._image = image;
		this._old_tex_path = old_tex_path;
		this._new_tex_path = new_tex_path;
	},
	Forward : function() {
		if (this._new_tex_path !== undefined) {
			let tex_id = this._layer_info._user_info.tex_id_map[this._new_tex_path];
			if (tex_id === undefined) {
				tex_id = this._layer_info._user_info.tex_id_max + 1;
				this._layer_info._user_info.tex_id_max = tex_id;
				this._layer_info._user_info.tile_map.tex_map.set(tex_id, this._new_tex_path);
				this._layer_info._user_info.tex_id_map[this._new_tex_path] = tex_id;
			}
			this._cell.tex_id = tex_id;
			this._image.SetTextureCut("Module/" + ALittleIDE.g_IDEProject.project.name + "/Texture/" + this._new_tex_path, 0, 0, true);
		} else {
			this._cell.tex_id = undefined;
			this._image.SetTextureCut(undefined, 0, 0, true);
		}
	},
	Back : function() {
		if (this._old_tex_path !== undefined) {
			let tex_id = this._layer_info._user_info.tex_id_map[this._old_tex_path];
			if (tex_id === undefined) {
				tex_id = this._layer_info._user_info.tex_id_max + 1;
				this._layer_info._user_info.tex_id_max = tex_id;
				this._layer_info._user_info.tile_map.tex_map.set(tex_id, this._old_tex_path);
				this._layer_info._user_info.tex_id_map[this._old_tex_path] = tex_id;
			}
			this._cell.tex_id = tex_id;
			this._image.SetTextureCut("Module/" + ALittleIDE.g_IDEProject.project.name + "/Texture/" + this._old_tex_path, 0, 0, true);
		} else {
			this._cell.tex_id = undefined;
			this._image.SetTextureCut(undefined, 0, 0, true);
		}
	},
}, "ALittleIDE.IDETileBrushCellRevoke");

}