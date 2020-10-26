{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.SpringTextButtonS = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_springtextbutton";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		this.LoadValueData("text");
		this.LoadShowTypeDataForImage("show_up");
		this.LoadShowTypeDataForImage("show_disabled");
		this.LoadShowTypeNoNilData("show_text");
		this.LoadShowTypeNoNilData("show_disabled_text");
		this.LoadBoolData("file_select", false, ALittleIDE.g_IDEEnum.yn_type);
	},
	HandleMTextFOCUSOUT : function(event) {
		this.DefaultNoStringInputChange("text", false);
	},
	HandleShowUpFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_up", this._show_up.text, this._show_up_grid9.selected, false);
	},
	HandleShowUpSelect : async function(event) {
		let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(this._tree_logic.user_info.module);
		if (ui_manager === undefined) {
			g_AUITool.ShowNotice("错误", "模块不存在:" + this._tree_logic.user_info.module);
			return;
		}
		ALittleIDE.g_IDEImageSelectDialog.SetBasePath(ui_manager.texture_path);
		let path = await ALittleIDE.g_IDEImageSelectDialog.ShowSelect();
		if (path === undefined) {
			return;
		}
		this.ImagePathSelectCallback("show_up", this.HandleShowUpFOCUSOUT, undefined, path, true);
	},
	HandleShowDisabledFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_disabled", this._show_disabled.text, this._show_disabled_grid9.selected, false);
	},
	HandleShowDisabledSelect : async function(event) {
		let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(this._tree_logic.user_info.module);
		if (ui_manager === undefined) {
			g_AUITool.ShowNotice("错误", "模块不存在:" + this._tree_logic.user_info.module);
			return;
		}
		ALittleIDE.g_IDEImageSelectDialog.SetBasePath(ui_manager.texture_path);
		let path = await ALittleIDE.g_IDEImageSelectDialog.ShowSelect();
		if (path === undefined) {
			return;
		}
		this.ImagePathSelectCallback("show_disabled", this.HandleShowDisabledFOCUSOUT, undefined, path, true);
	},
	HandleShowTextFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_text", false);
	},
	HandleShowTextClear : function(event) {
		this.RemoverToNilShowSet("show_text", "", true);
	},
	HandleShowDisabledTextFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_disabled_text", false);
	},
	HandleShowDisabledTextClear : function(event) {
		this.RemoverToNilShowSet("show_disabled_text", "", true);
	},
	HandleHandFileSelectSELECT_CHANGE : function(event) {
		this.BoolSelectChange("file_select", false, ALittleIDE.g_IDEEnum.yn_type);
	},
}, "ALittleIDE.SpringTextButtonS");

}