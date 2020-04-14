{
if (typeof ALittleIDE === "undefined") ALittleIDE = {};


ALittleIDE.IDEEditImageDialog = JavaScript.Class(undefined, {
	HideDialog : function() {
		if (this._dialog !== undefined) {
			this._dialog.visible = false;
			this._cut_plugin.Clear();
		}
	},
	ShowDialog : function(path) {
		if (this._dialog === undefined) {
			this._dialog = ALittleIDE.g_Control.CreateControl("ide_image_edit_dialog", this);
			A_LayerManager.AddToModal(this._dialog);
		}
		this._cut_plugin.EditTexture(path);
		this._dialog.visible = true;
	},
	HandleCancelClick : function(event) {
		this.HideDialog();
	},
	HandleSaveClick : function(event) {
		this._cut_plugin.Cut();
	},
	HandleSaveToClick : function(event) {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("提示", "当前没有打开项目");
			return;
		}
		A_OtherSystem.SystemSaveFile(event.target, "input_file_name.png", ALittleIDE.g_IDEProject.project.base_path + "Texture");
	},
	HandleSystemSaveFile : function(event) {
		this._cut_plugin.Cut(event.path);
	},
}, "ALittleIDE.IDEEditImageDialog");

ALittleIDE.g_IDEEditImageDialog = ALittle.NewObject(ALittleIDE.IDEEditImageDialog);
}