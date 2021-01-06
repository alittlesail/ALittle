{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1821709712, "AUIPlugin.AUIFileSelectRightButtonDownEvent", {
name : "AUIPlugin.AUIFileSelectRightButtonDownEvent", ns_name : "AUIPlugin", rl_name : "AUIFileSelectRightButtonDownEvent", hash_code : 1821709712,
name_list : ["target","path","directory"],
type_list : ["ALittle.EventDispatcher","string","bool"],
option_map : {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

if (ALittle.EventDispatcher === undefined) throw new Error(" extends class:ALittle.EventDispatcher is undefined");
AUIPlugin.AUIFileSelectDialog = JavaScript.Class(ALittle.EventDispatcher, {
	Ctor : function(title, layer, ext_list) {
		this._title = title;
		this._layer = layer;
		this._ext_list = ext_list;
	},
	Shutdown : function() {
		if (this._layout !== undefined) {
			this._layout.Release();
		}
		if (this._dialog !== undefined) {
			if (this._layer !== undefined) {
				this._layer.RemoveChild(this._dialog);
			} else {
				A_LayerManager.RemoveFromModal(this._dialog);
			}
			this._dialog = undefined;
		}
	},
	HideDialog : function() {
		if (this._layout !== undefined) {
			this._layout.Release();
		}
		if (this._dialog !== undefined) {
			this._dialog.visible = false;
		}
	},
	ShowDialog : function() {
		if (this._layout !== undefined) {
			this._layout.Release();
		}
		this.CreateDialog();
		this._dialog.visible = true;
	},
	CreateDialog : function() {
		if (this._dialog === undefined) {
			this._dialog = AUIPlugin.g_Control.CreateControl("file_select_dialog", this);
			this._dialog.title = this._title;
			if (this._layer !== undefined) {
				this._layer.AddChild(this._dialog);
			} else {
				A_LayerManager.AddToModal(this._dialog);
			}
			this._dialog.close_callback = this.HandleDialogClose.bind(this);
			this._layout.Init(this._ext_list);
			this._layout.AddEventListener(___all_struct.get(-1265378424), this, this.HandleItemRButtonDown);
		}
	},
	HandleItemRButtonDown : function(event) {
		let e = {};
		e.path = event.path;
		e.directory = event.directory;
		this.DispatchEvent(___all_struct.get(1821709712), e);
	},
	get base_path() {
		if (this._layout === undefined) {
			return undefined;
		}
		return this._layout.base_path;
	},
	ShowSelect : function() {
		return new Promise((async function(___COROUTINE, ___) {
			this.ShowDialog();
			let result = await this._layout.ShowSelect();
			this._dialog.visible = false;
			___COROUTINE(result); return;
		}).bind(this));
	},
	HandleDialogClose : function() {
		if (this._layout !== undefined) {
			this._layout.Release();
		}
		return true;
	},
	System_SetVDragCursor : function(event) {
		ALittle.System_SetVDragCursor();
	},
	System_SetNormalCursor : function(event) {
		ALittle.System_SetNormalCursor();
	},
	System_SetHDragCursor : function(event) {
		ALittle.System_SetHDragCursor();
	},
	System_SetHVDragCursor : function(event) {
		ALittle.System_SetHVDragCursor();
	},
	SetPath : function(base_path, rel_path) {
		this.CreateDialog();
		return this._layout.SetPath(base_path, rel_path);
	},
	SetBasePath : function(base_path) {
		if (this.base_path === base_path) {
			return true;
		}
		return this.SetPath(base_path, "");
	},
	Refresh : function() {
		if (this._layout !== undefined) {
			this._layout.Refresh();
		}
	},
	HandleDialogDrag : function(event) {
		let delta_x = event.delta_x;
		let delta_y = event.delta_y;
		if (event.target === this._drag_lr_quad) {
			delta_y = 0;
		} else if (event.target === this._drag_ud_quad) {
			delta_x = 0;
		}
		if (this._dialog.width + delta_x < 506) {
			delta_x = 506 - this._dialog.width;
		}
		if (this._dialog.height + delta_y < 200) {
			delta_y = 200 - this._dialog.height;
		}
		this._dialog.width = this._dialog.width + delta_x;
		this._dialog.height = this._dialog.height + delta_y;
	},
	HandleDialogDragEnd : function(event) {
		this._layout.Refresh();
	},
	CheckResourceName : function(name) {
		let len = ALittle.String_Len(name);
		if (len === 0) {
			return [false, "命名只能支持字母数字下划线"];
		}
		for (let i = 1; i <= len; i += 1) {
			let byte = ALittle.String_Byte(name, i);
			let check_all = byte >= 65 && byte <= 90 || byte >= 97 && byte <= 122 || byte >= 48 && byte <= 57 || byte === 95;
			if (check_all === false) {
				return [false, "命名只能支持字母数字下划线"];
			}
		}
		return [true, undefined];
	},
}, "AUIPlugin.AUIFileSelectDialog");

}