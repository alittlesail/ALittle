{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.IDEProjectExportDialog = JavaScript.Class(undefined, {
	ShowExportProject : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return;
		}
		if (this._export_dialog === undefined) {
			this._export_dialog = ALittleIDE.g_Control.CreateControl("ide_export_dialog", this);
			ALittleIDE.g_DialogLayer.AddChild(this._export_dialog);
			this._main_export_tab.DisableAllCloseButton();
			this._main_export_tab.tab_index = 1;
			this._export_windows_official.config_key = "export_windows_official";
			this._export_android_official.config_key = "export_android_official";
			this._export_ios_official.config_key = "export_ios_official";
		}
		this._export_dialog.visible = true;
		this._export_windows_official.LoadConfigImpl();
		this._export_android_official.LoadConfigImpl();
		this._export_ios_official.LoadConfigImpl();
	},
}, "ALittleIDE.IDEProjectExportDialog");

ALittleIDE.g_IDEProjectExportDialog = ALittle.NewObject(ALittleIDE.IDEProjectExportDialog);
}