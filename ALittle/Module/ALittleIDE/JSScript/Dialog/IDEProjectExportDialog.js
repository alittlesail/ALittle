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
		}
		this._export_dialog.visible = true;
		this._export_windows.LoadConfigImpl();
		this._export_android.LoadConfigImpl();
		this._export_ios.LoadConfigImpl();
		this._export_web.LoadConfigImpl();
		this._export_wechat.LoadConfigImpl();
	},
}, "ALittleIDE.IDEProjectExportDialog");

ALittleIDE.g_IDEProjectExportDialog = ALittle.NewObject(ALittleIDE.IDEProjectExportDialog);
}