{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})

ALittleIDE.IDEProjectSettingDialog = JavaScript.Class(undefined, {
	ShowSettingProject : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return;
		}
		if (this._project_setting_dialog === undefined) {
			this._project_setting_dialog = ALittleIDE.g_Control.CreateControl("ide_setting_project_dialog", this);
			A_LayerManager.AddToModal(this._project_setting_dialog);
		}
		this._project_setting_dialog.visible = true;
		this._default_show_width.text = ALittleIDE.g_IDEProject.project.config.GetConfig("default_show_width", 800);
		this._default_show_height.text = ALittleIDE.g_IDEProject.project.config.GetConfig("default_show_height", 600);
		this._default_font_path.text = ALittleIDE.g_IDEProject.project.config.GetConfig("default_font_path", "");
		this._default_font_size.text = ALittleIDE.g_IDEProject.project.config.GetConfig("default_font_size", 15);
	},
	HandleSettingProjectCancel : function(event) {
		this._project_setting_dialog.visible = false;
	},
	HandleSettingProjectConfirm : function(event) {
		let default_show_width = ALittle.Math_ToInt(this._default_show_width.text);
		if (default_show_width === undefined || default_show_width <= 0) {
			g_AUITool.ShowNotice("错误", "默认宽度不合法");
			return;
		}
		let default_show_height = ALittle.Math_ToInt(this._default_show_height.text);
		if (default_show_height === undefined || default_show_height <= 0) {
			g_AUITool.ShowNotice("错误", "默认高度不合法");
			return;
		}
		let default_font_path = this._default_font_path.text;
		let default_font_size = ALittle.Math_ToInt(this._default_font_size.text);
		if (default_font_size === undefined || default_font_size <= 0) {
			g_AUITool.ShowNotice("错误", "默认字体大小不合法");
			return;
		}
		ALittleIDE.g_IDEProject.project.config.SetConfig("default_show_width", default_show_width);
		ALittleIDE.g_IDEProject.project.config.SetConfig("default_show_height", default_show_height);
		ALittleIDE.g_IDEProject.project.config.SetConfig("default_font_path", default_font_path);
		ALittleIDE.g_IDEProject.project.config.SetConfig("default_font_size", default_font_size);
		let changed_event = {};
		changed_event.default_show_width = default_show_width;
		changed_event.default_show_height = default_show_height;
		changed_event.default_font_path = default_font_path;
		changed_event.default_font_size = default_font_size;
		ALittleIDE.g_IDEProject.DispatchEvent(___all_struct.get(1787992834), changed_event);
		this._project_setting_dialog.visible = false;
	},
}, "ALittleIDE.IDEProjectSettingDialog");

ALittleIDE.g_IDEProjectSettingDialog = ALittle.NewObject(ALittleIDE.IDEProjectSettingDialog);
}