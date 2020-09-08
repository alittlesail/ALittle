{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.TextS === undefined) throw new Error(" extends class:ALittleIDE.TextS is undefined");
ALittleIDE.TextEditS = JavaScript.Class(ALittleIDE.TextS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_textedit";
	},
	LoadNatureBase : function() {
		ALittleIDE.TextS.LoadNatureBase.call(this);
		this.LoadBoolData("editable", true, ALittleIDE.g_IDEEnum.yn_type);
		this.LoadColorData("cursor_red");
		this.LoadColorData("cursor_green");
		this.LoadColorData("cursor_blue");
		this.LoadDefaultNilString("default_text");
		this.LoadValueData("default_text_alpha");
		this.LoadValueData("ims_padding");
	},
	HandleEditableSELECT_CHANGE : function(event) {
		this.BoolSelectChange("editable", false, ALittleIDE.g_IDEEnum.yn_type);
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
}, "ALittleIDE.TextEditS");

}