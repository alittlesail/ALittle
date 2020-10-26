{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.IDEProjectOpenDialog = JavaScript.Class(undefined, {
	ShowOpenProject : function() {
		if (this._project_open_dialog === undefined) {
			this._project_open_dialog = ALittleIDE.g_Control.CreateControl("ide_open_project_dialog", this);
			A_LayerManager.AddToModal(this._project_open_dialog);
		}
		this._project_open_name.text = "";
		this._project_open_dialog.visible = true;
		let module_list = [];
		let file_map = ALittle.File_GetNameListByDir(ALittleIDE.g_ModuleBasePath + "..");
		let ___OBJECT_1 = file_map;
		for (let name in ___OBJECT_1) {
			let info = ___OBJECT_1[name];
			if (info === undefined) continue;
			if (info.directory) {
				ALittle.List_Push(module_list, name);
			}
		}
		this._project_dropdown.data_list = module_list;
		this._project_dropdown.text = "";
		A_UISystem.focus = this._project_open_name.show_input;
	},
	HandleOpenProjectSelect : function(event) {
		this._project_open_name.text = event.target.text;
		event.target.text = "";
	},
	HandleOpenProjectCancel : function(event) {
		this._project_open_dialog.visible = false;
	},
	HandleOpenProjectConfirm : async function(event) {
		this._project_open_dialog.visible = false;
		let name = this._project_open_name.text;
		if (!ALittleIDE.g_IDECenter.center.content_edit.IsSaveAll()) {
			let result = await g_AUITool.SaveNotice("提示", "是否保存当前项目?");
			if (result === "YES") {
				ALittleIDE.g_IDECenter.center.content_edit.SaveAllTab();
			}
		}
		let error = ALittleIDE.g_IDEProject.OpenProject(name);
		if (error !== undefined) {
			g_AUITool.ShowNotice("错误", error);
			return;
		}
	},
}, "ALittleIDE.IDEProjectOpenDialog");

ALittleIDE.g_IDEProjectOpenDialog = ALittle.NewObject(ALittleIDE.IDEProjectOpenDialog);
}