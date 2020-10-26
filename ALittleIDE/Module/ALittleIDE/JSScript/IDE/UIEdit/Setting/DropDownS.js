{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.TextCheckButtonS === undefined) throw new Error(" extends class:ALittleIDE.TextCheckButtonS is undefined");
ALittleIDE.DropDownS = JavaScript.Class(ALittleIDE.TextCheckButtonS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_dropdown";
	},
	LoadNatureBase : function() {
		ALittleIDE.TextCheckButtonS.LoadNatureBase.call(this);
		this.LoadShowTypeDataForImage("show_background");
		this.LoadShowTypeDataForExtends("show_scrollbar");
		this.LoadDefaultNilString("button_style");
		this.LoadValueData("show_count");
		this.LoadValueData("body_margin");
		this.LoadValueData("screen_margin_left");
		this.LoadValueData("screen_margin_right");
		this.LoadValueData("screen_margin_top");
		this.LoadValueData("screen_margin_bottom");
		this.LoadShowTypeData("data_list");
	},
	HandleShowBackGFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_background", this._show_background.text, this._show_background_grid9.selected, false);
	},
	HandleShowBackGSelect : async function(event) {
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
		this.ImagePathSelectCallback("show_background", this.HandleShowBackGFOCUSOUT, undefined, path, false);
	},
	HandleShowScrollBarFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForExtends("show_scrollbar", this._show_scrollbar.text, false);
	},
	HandleButtonStyleFOCUSOUT : function(event) {
		this.DefaultNilStringInputChange("button_style", false);
	},
	HandleShowCountFOCUSOUT : function(event) {
		this.ValueNumZInputChange("show_count", false);
	},
	HandleBodyMarginFOCUSOUT : function(event) {
		this.ValueNumInputChange("body_margin", false);
	},
	HandleScreenMarginLeftFOCUSOUT : function(event) {
		this.ValueNumInputChange("screen_margin_left", false);
	},
	HandleScreenMarginRightFOCUSOUT : function(event) {
		this.ValueNumInputChange("screen_margin_right", false);
	},
	HandleScreenMarginTopFOCUSOUT : function(event) {
		this.ValueNumInputChange("screen_margin_top", false);
	},
	HandleScreenMarginBottomFOCUSOUT : function(event) {
		this.ValueNumInputChange("screen_margin_bottom", false);
	},
	HandleDatalistFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.TableDataSet("data_list", false);
	},
}, "ALittleIDE.DropDownS");

}