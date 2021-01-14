{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};


AUIPlugin.AUIEditImageDialog = JavaScript.Class(undefined, {
	HideDialog : function() {
		if (this._dialog !== undefined) {
			this._dialog.visible = false;
			this._cut_plugin.Clear();
		}
	},
	ShowDialog : function(path, save_dir) {
		if (this._dialog === undefined) {
			this._dialog = AUIPlugin.g_Control.CreateControl("aui_image_edit_dialog", this);
			A_LayerManager.AddToModal(this._dialog);
		}
		this._save_dir = save_dir;
		this._cut_plugin.EditTexture(path);
		this._dialog.visible = true;
	},
	Shutdown : function() {
		if (this._dialog !== undefined) {
			A_LayerManager.RemoveFromModal(this._dialog);
			this._dialog = undefined;
		}
	},
	HandleCancelClick : function(event) {
		this.HideDialog();
	},
	HandleSaveClick : function(event) {
		this._cut_plugin.Cut();
	},
	HandleSaveToClick : function(event) {
		A_OtherSystem.SystemSaveFile(event.target, "input_file_name.png", this._save_dir);
	},
	HandleSystemSaveFile : function(event) {
		this._cut_plugin.Cut(event.path);
	},
}, "AUIPlugin.AUIEditImageDialog");

}