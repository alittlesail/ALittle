{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.TextS === undefined) throw new Error(" extends class:ALittleIDE.TextS is undefined");
ALittleIDE.TextAreaS = JavaScript.Class(ALittleIDE.TextS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_textarea";
	},
	LoadNatureBase : function() {
		ALittleIDE.TextS.LoadNatureBase.call(this);
		this.LoadTypeSelectData("halign", ALittleIDE.g_IDEEnum.HALIGN_type);
		this.LoadTypeSelectData("valign", ALittleIDE.g_IDEEnum.VALIGN_type);
	},
	HandleHalignSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.HALIGN_rtype;
		this.TypeSelectChange("halign", list, false);
	},
	HandleValignSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.VALIGN_rtype;
		this.TypeSelectChange("valign", list, false);
	},
}, "ALittleIDE.TextAreaS");

}