{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.IDEAttrControlDialog = JavaScript.Class(undefined, {
	get dialog() {
		if (this._dialog === undefined) {
			this.CreateDialog();
		}
		return this._dialog;
	},
	CreateDialog : function() {
		this._dialog = ALittleIDE.g_Control.CreateControl("ide_control_attr_dialog", this);
		ALittleIDE.g_DialogLayer.AddChild(this._dialog);
		this._dialog.visible = false;
	},
	SetTitle : function(title) {
		if (this._dialog === undefined) {
			this.CreateDialog();
		}
		this._dialog.title = title;
	},
	ShowDialog : function(target) {
		if (this._dialog === undefined) {
			this.CreateDialog();
		}
		this._dialog.visible = true;
		this._dialog.x = A_UISystem.mouse_x + 50;
		this._dialog.y = A_UISystem.mouse_y - (this._dialog.height - target.height) / 2;
		if (this._dialog.y < 0) {
			this._dialog.y = 0;
		}
		if (this._dialog.x + this._dialog.width > A_UISystem.view_width) {
			this._dialog.x = A_UISystem.view_width - this._dialog.width;
		}
		if (this._dialog.y + this._dialog.height > A_UISystem.view_height) {
			this._dialog.y = A_UISystem.view_height - this._dialog.height;
		}
	},
	HideDialog : function() {
		if (this._dialog === undefined) {
			return;
		}
		this._dialog.visible = false;
	},
}, "ALittleIDE.IDEAttrControlDialog");

ALittleIDE.g_IDEAttrControlDialog = ALittle.NewObject(ALittleIDE.IDEAttrControlDialog);
}