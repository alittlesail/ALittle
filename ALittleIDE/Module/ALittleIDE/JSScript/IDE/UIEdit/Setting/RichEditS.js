{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.RichEditS = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_richedit";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		this.LoadDefaultNilString("font_path");
		this.LoadDefaultNilString("font_size");
		this.LoadShowTypeData("display_list");
		this.LoadBoolData("editable", true, ALittleIDE.g_IDEEnum.yn_type);
		this.LoadBoolData("can_drag_text", true, ALittleIDE.g_IDEEnum.yn_type);
		this.LoadBoolData("focus_cursor", true, ALittleIDE.g_IDEEnum.yn_type);
		this.LoadDefaultNilString("default_text");
		this.LoadValueData("default_text_alpha");
		this.LoadColorData("cursor_red");
		this.LoadColorData("cursor_green");
		this.LoadColorData("cursor_blue");
		this.LoadColorData("font_red");
		this.LoadColorData("font_green");
		this.LoadColorData("font_blue");
		this.LoadValueData("margin_halign");
		this.LoadValueData("margin_valign");
		this.LoadValueData("cursor_margin_up");
		this.LoadValueData("cursor_margin_down");
		this.LoadValueData("ims_padding");
		this.LoadShowTypeDataForExtends("start_cursor");
		this.LoadShowTypeDataForExtends("end_cursor");
	},
	HandleFontPathFOCUSOUT : function(event) {
		this.SpecialFontPathInputChange("font_path", false);
	},
	HandleFontSizeFOCUSOUT : function(event) {
		this.ValueNumZInputChange("font_size", false);
	},
	HandleFontRedFOCUSOUT : function(event) {
		this.ColorValueInputChange("font_red", false);
	},
	HandleFontGreenFOCUSOUT : function(event) {
		this.ColorValueInputChange("font_green", false);
	},
	HandleFontBlueFOCUSOUT : function(event) {
		this.ColorValueInputChange("font_blue", false);
	},
	HandleCursorRedFOCUSOUT : function(event) {
		this.ColorValueInputChange("cursor_red", false);
	},
	HandleCursorGreenFOCUSOUT : function(event) {
		this.ColorValueInputChange("cursor_green", false);
	},
	HandleCursorBlueFOCUSOUT : function(event) {
		this.ColorValueInputChange("cursor_blue", false);
	},
	HandleDisplayListFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.TableDataSet("display_list", true);
	},
	HandleEditableSELECT_CHANGE : function(event) {
		this.BoolSelectChange("editable", false, ALittleIDE.g_IDEEnum.yn_type);
	},
	HandleFocusCurosrSELECT_CHANGE : function(event) {
		this.BoolSelectChange("focus_cursor", false, ALittleIDE.g_IDEEnum.yn_type);
	},
	HandleCanDragTextSELECT_CHANGE : function(event) {
		this.BoolSelectChange("can_drag_text", false, ALittleIDE.g_IDEEnum.yn_type);
	},
	HandleMarginHalignFOCUSOUT : function(event) {
		this.ValueNumInputChange("margin_halign", false);
	},
	HandleMarginValignFOCUSOUT : function(event) {
		this.ValueNumInputChange("margin_valign", false);
	},
	HandleCursorMarginUpFOCUSOUT : function(event) {
		this.ValueNumInputChange("cursor_margin_up", false);
	},
	HandleCursorMarginDownFOCUSOUT : function(event) {
		this.ValueNumInputChange("cursor_margin_down", false);
	},
	HandleStartCursorFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForExtends("start_cursor", this._start_cursor.text, false);
	},
	HandleEndCursorFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForExtends("end_cursor", this._end_cursor.text, false);
	},
	HandleDefaultTextFOCUSOUT : function(event) {
		this.DefaultNoStringInputChange("default_text", false);
	},
	HandleDefaultTextAlphaFOCUSOUT : function(event) {
		this.Z2OValueInputChange("default_text_alpha", false);
	},
	HandleImsPaddingFOCUSOUT : function(event) {
		this.ValueNumInputChange("ims_padding", false);
	},
	HandleRegexFOCUSOUT : function(event) {
		this.DefaultNoStringInputChange("regex", false);
	},
	HandleLimitLenFOCUSOUT : function(event) {
		this.ValueNumInputChange("limit_len", false);
	},
}, "ALittleIDE.RichEditS");

}