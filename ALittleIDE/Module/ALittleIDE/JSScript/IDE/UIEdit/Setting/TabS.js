{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.TabS = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_tab";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		this.LoadDefaultNilString("radiobutton_style");
		this.LoadDefaultNilString("closebutton_style");
		this.LoadDefaultNilString("text_style");
		this.LoadDefaultNilString("selected_closebutton_style");
		this.LoadDefaultNilString("selected_text_style");
		this.LoadShowTypeDataForImage("show_head_background");
		this.LoadValueData("button_gap");
		this.LoadValueData("button_start");
		this.LoadValueData("button_margin");
		this.LoadValueData("head_size");
		this.LoadValueData("tab_index");
		this.LoadValueData("view_margin");
		this.LoadValueData("child_width_margin");
	},
	HandleRBSttyleFOCUSOUT : function(event) {
		this.DefaultNilStringInputChange("radiobutton_style", false);
	},
	HandleCBStyleFOCUSOUT : function(event) {
		this.DefaultNilStringInputChange("closebutton_style", false);
	},
	HandleTStyleFOCUSOUT : function(event) {
		this.DefaultNilStringInputChange("text_style", false);
	},
	HandleSCBStyleFOCUSOUT : function(event) {
		this.DefaultNilStringInputChange("selected_closebutton_style", false);
	},
	HandleSTStyleFOCUSOUT : function(event) {
		this.DefaultNilStringInputChange("selected_text_style", false);
	},
	HandleShowHeadBFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_head_background", this._show_head_background.text, this._show_head_background.selected, false);
	},
	HandleShowHeadBSelect : async function(event) {
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
		this.ImagePathSelectCallback("show_head_background", this.HandleShowHeadBFOCUSOUT, undefined, path, false);
	},
	HandleBGapFOCUSOUT : function(event) {
		this.ValueNumInputChange("button_gap", false);
	},
	HandleBStartFOCUSOUT : function(event) {
		this.ValueNumInputChange("button_start", false);
	},
	HandleBMarginFOCUSOUT : function(event) {
		this.ValueNumInputChange("button_margin", false);
	},
	HandleHeadSizeFOCUSOUT : function(event) {
		this.ValueNumInputChange("head_size", false);
	},
	HandleTabIndexFOCUSOUT : function(event) {
		this.ValueNumZInputChange("tab_index", false);
	},
	HandleViewMarginFOCUSOUT : function(event) {
		this.ValueNumInputChange("view_margin", false);
	},
	HandleChildWidthMarginFOCUSOUT : function(event) {
		this.ValueNumInputChange("child_width_margin", false);
	},
}, "ALittleIDE.TabS");

}