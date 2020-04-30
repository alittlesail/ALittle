{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.TextEditS === undefined) throw new Error(" extends class:ALittleIDE.TextEditS is undefined");
ALittleIDE.TextInputS = JavaScript.Class(ALittleIDE.TextEditS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_textinput";
	},
	LoadNatureBase : function() {
		ALittleIDE.TextEditS.LoadNatureBase.call(this);
		this.LoadBoolData("password_mode", false, ALittleIDE.g_IDEEnum.yn_type);
		this.LoadDefaultNilString("default_text");
		this.LoadValueData("default_text_alpha");
		this.LoadValueData("ims_padding");
	},
	HandlePasswordModeSELECT_CHANGE : function(event) {
		this.BoolSelectChange("password_mode", false, ALittleIDE.g_IDEEnum.yn_type);
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
}, "ALittleIDE.TextInputS");

}