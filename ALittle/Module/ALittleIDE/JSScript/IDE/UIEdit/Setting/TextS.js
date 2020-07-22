{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayObjectS === undefined) throw new Error(" extends class:ALittleIDE.DisplayObjectS is undefined");
ALittleIDE.TextS = JavaScript.Class(ALittleIDE.DisplayObjectS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_text";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayObjectS.LoadNatureBase.call(this);
		this.LoadBoolData("bold", false, ALittleIDE.g_IDEEnum.yn_type);
		this.LoadBoolData("underline", false, ALittleIDE.g_IDEEnum.yn_type);
		this.LoadBoolData("deleteline", false, ALittleIDE.g_IDEEnum.yn_type);
		this.LoadBoolData("italic", false, ALittleIDE.g_IDEEnum.yn_type);
		this.LoadValueData("text");
		this.LoadDefaultNilString("font_path");
		this.LoadDefaultNilString("font_size");
		this.LoadEnumData("flip", ALittleIDE.g_IDEEnum.flip_type);
	},
	HandleBoldSELECT_CHANGE : function(event) {
		this.BoolSelectChange("bold", false, ALittleIDE.g_IDEEnum.yn_type);
	},
	HandleUnderLineSELECT_CHANGE : function(event) {
		this.BoolSelectChange("underline", false, ALittleIDE.g_IDEEnum.yn_type);
	},
	HandleDeleteLineSELECT_CHANGE : function(event) {
		this.BoolSelectChange("deleteline", false, ALittleIDE.g_IDEEnum.yn_type);
	},
	HandleItalicSELECT_CHANGE : function(event) {
		this.BoolSelectChange("italic", false, ALittleIDE.g_IDEEnum.yn_type);
	},
	HandleTextFOCUSOUT : function(event) {
		if (this._default.__class === "Text") {
			this.DefaultNoStringInputChange("text", true);
		} else {
			this.DefaultNoStringInputChange("text", false);
		}
		this._tree_logic.UpdateDesc();
	},
	HandleFontPathFOCUSOUT : function(event) {
		if (this._default.__class === "Text") {
			this.SpecialFontPathInputChange("font_path", true);
		} else {
			this.SpecialFontPathInputChange("font_path", false);
		}
	},
	HandleFontSizeFOCUSOUT : function(event) {
		if (this._default.__class === "Text") {
			this.ValueNumZInputChange("font_size", true);
		} else {
			this.ValueNumZInputChange("font_size", false);
		}
	},
	HandleFlipSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.flip_rtype;
		this.TypeSelectChange("flip", list, false);
	},
}, "ALittleIDE.TextS");

}