{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.LinearS = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_linear";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		let list = ALittleIDE.g_IDEEnum.hv_type;
		this.LoadTypeSelectData("type", list);
		this.LoadBoolData("size_fixed", true, ALittleIDE.g_IDEEnum.yn_type);
		this.LoadValueData("gap");
	},
	HandleLinearTypeSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.hv_rtype;
		this.TypeSelectChange("type", list, true);
	},
	HandleLinearSizeFixedSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.yn_rtype;
		this.TypeSelectChange("size_fixed", list, true);
	},
	HandleLinearGapFOCUSOUT : function(event) {
		this.ValueNumInputChange("gap", false);
	},
}, "ALittleIDE.LinearS");

}