{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.IDEProjectNewDialog = JavaScript.Class(undefined, {
	ShowNewProject : function() {
		if (this._project_new_dialog === undefined) {
			this._project_new_dialog = ALittleIDE.g_Control.CreateControl("ide_new_project_dialog", this);
			A_LayerManager.AddToModal(this._project_new_dialog);
		}
		this._project_new_name.text = "";
		this._project_new_dialog.visible = true;
		A_UISystem.focus = this._project_new_name.show_input;
	},
	HandleNewProjectCancel : function(event) {
		this._project_new_dialog.visible = false;
	},
	HandleNewProjectConfirm : function(event) {
		let name = this._project_new_name.text;
		if (name === "") {
			g_AUITool.ShowNotice("错误", "请输入项目名");
			return;
		}
		if (ALittleIDE.IDEUtility_CheckName(name) !== undefined) {
			g_AUITool.ShowNotice("错误", "项目名不合法:" + name);
			return;
		}
		if (ALittle.File_GetFileAttr(ALittle.File_BaseFilePath() + name) !== undefined) {
			g_AUITool.ShowNotice("错误", "项目已存在:" + name);
			return;
		}
		let size_list = ALittle.String_Split(this._view_size_dropdown.text, "x");
		let window_width = ALittle.Math_ToInt(size_list[1 - 1]);
		if (window_width === undefined) {
			window_width = 800;
		}
		let window_height = ALittle.Math_ToInt(size_list[2 - 1]);
		if (window_height === undefined) {
			window_height = 600;
		}
		let font_path = this._default_font_path.text;
		let font_size = ALittle.Math_ToInt(this._default_font_size.text);
		if (font_size === undefined) {
			font_size = 25;
		}
		ALittleIDE.g_IDEProject.NewProject(name, ALittle.Math_Floor(window_width), ALittle.Math_Floor(window_height), font_path, ALittle.Math_Floor(font_size));
		if (ALittleIDE.g_IDEProject.project === undefined) {
			ALittleIDE.g_IDEProject.OpenProject(name);
		}
		this._project_new_dialog.visible = false;
	},
}, "ALittleIDE.IDEProjectNewDialog");

ALittleIDE.g_IDEProjectNewDialog = ALittle.NewObject(ALittleIDE.IDEProjectNewDialog);
}