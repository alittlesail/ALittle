{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};


AUIPlugin.AUIIMEManager = JavaScript.Class(undefined, {
	Ctor : function() {
	},
	Setup : function() {
		if (A_UISystem.ime_callback !== undefined) {
			return;
		}
		if (this._ime_dialog === undefined) {
			this._ime_dialog = AUIPlugin.g_Control.CreateControl("aui_ime_dialog", this);
			A_LayerManager.AddToTip(this._ime_dialog);
			this._ime_dialog.visible = false;
			this._ime_dialog_init_width = this._ime_dialog.width;
		}
		this._callback = this.HandleImeEditingCallback.bind(this);
		A_UISystem.ime_callback = this._callback;
	},
	Shutdown : function() {
		if (this._ime_dialog !== undefined) {
			A_LayerManager.RemoveFromTip(this._ime_dialog);
			this._ime_dialog = undefined;
		}
		if (A_UISystem.ime_callback === this._callback) {
			A_UISystem.ime_callback = undefined;
		}
		this._callback = undefined;
	},
	HandleImeEditingCallback : function(open, text, start, list, target) {
		if (this._ime_dialog === undefined) {
			return;
		}
		if (open && target !== undefined) {
			let class_info = (target).__class;
			if (class_info.__name === "ALittle.TextInput" && target.password_mode) {
				return;
			}
		}
		this._ime_dialog.visible = open;
		if (open && target !== undefined) {
			this._ime_dialog.title = text;
			let new_list = [];
			let new_list_count = 0;
			let ___OBJECT_1 = list;
			for (let k = 1; k <= ___OBJECT_1.length; ++k) {
				let v = ___OBJECT_1[k - 1];
				if (v === undefined) break;
				++ new_list_count;
				new_list[new_list_count - 1] = k + "." + v;
			}
			this._ime_editing_list.text = ALittle.String_Join(new_list, " ");
			let [global_x, global_y] = target.LocalToGlobal();
			let cursor_x = target.cursor_x;
			let cursor_b = target.cursor_b;
			if (cursor_x !== undefined && cursor_b !== undefined) {
				this._ime_dialog.x = global_x + cursor_x;
				this._ime_dialog.y = global_y + cursor_b;
			} else {
				this._ime_dialog.x = global_x;
				this._ime_dialog.y = global_y + target.height;
			}
			let width = this._ime_editing_list.width + this._ime_editing_list.x * 2;
			if (width < this._ime_dialog_init_width) {
				width = this._ime_dialog_init_width;
			}
			if (this._ime_dialog.width !== width) {
				this._ime_dialog.width = width;
			}
			if (this._ime_dialog.y + this._ime_dialog.height > A_UISystem.view_height) {
				this._ime_dialog.y = global_y - this._ime_dialog.height;
			}
			if (this._ime_dialog.x + this._ime_dialog.width > A_UISystem.view_width) {
				this._ime_dialog.x = A_UISystem.view_width - this._ime_dialog.width;
			}
		}
	},
}, "AUIPlugin.AUIIMEManager");

AUIPlugin.g_AUIIMEManager = ALittle.NewObject(AUIPlugin.AUIIMEManager);
}