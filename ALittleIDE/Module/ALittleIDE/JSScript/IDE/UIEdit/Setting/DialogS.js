{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.DialogS = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_dialog";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		this.LoadValueData("head_size");
		this.LoadValueData("head_top_margin");
		this.LoadValueData("head_bottom_margin");
		this.LoadValueData("head_left_margin");
		this.LoadValueData("head_right_margin");
		this.LoadDefaultNilString("title");
		this.LoadShowTypeDataForImage("show_background");
		this.LoadShowTypeDataForImage("show_head_drag");
		this.LoadShowTypeDataForExtends("show_close_button");
		this.LoadShowTypeNoNilData("show_title");
	},
	HandleHeadSizeFOCUSOUT : function(event) {
		this.ValueNumInputChange("head_size", false);
	},
	HandleHeadTopMarginFOCUSOUT : function(event) {
		this.ValueNumInputChange("head_top_margin", false);
	},
	HandleHeadBottomMarginFOCUSOUT : function(event) {
		this.ValueNumInputChange("head_bottom_margin", false);
	},
	HandleHeadLeftMarginFOCUSOUT : function(event) {
		this.ValueNumInputChange("head_left_margin", false);
	},
	HandleHeadRightMarginFOCUSOUT : function(event) {
		this.ValueNumInputChange("head_right_margin", false);
	},
	HandleTitleFOCUSOUT : function(event) {
		this.DefaultNoStringInputChange("title", false);
	},
	HandleShowBackgroundFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_background", this._show_background.text, this._show_background_grid9.selected, false);
	},
	HandleShowBackgroundSelect : async function(event) {
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
		this.ImagePathSelectCallback("show_background", this.HandleShowBackgroundFOCUSOUT, undefined, path, false);
	},
	HandleShowHeadDragFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_head_drag", this._show_head_drag.text, this._show_head_drag_grid9.selected, false);
	},
	HandleShowHeadDragSelect : async function(event) {
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
		this.ImagePathSelectCallback("show_head_drag", this.HandleShowHeadDragFOCUSOUT, undefined, path, false);
	},
	HandleShowCloseButtonFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForExtends("show_close_button", this._show_close_button.text, false);
	},
	HandleShowTitleFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_title", false);
	},
	HandleShowTitleClear : function(event) {
		this.RemoverToNilShowSet("show_title", "", true);
	},
}, "ALittleIDE.DialogS");

}