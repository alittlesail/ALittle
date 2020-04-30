{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.Grid3S = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_grid3";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		let list = ALittleIDE.g_IDEEnum.hv_type;
		this.LoadTypeSelectData("type", list);
		this.LoadValueData("gap");
		this.LoadValueData("up_size");
		this.LoadValueData("down_size");
	},
	HandleGrid3TypeSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.hv_rtype;
		this.TypeSelectChange("type", list, false);
	},
	HandleGrid3GapFOCUSOUT : function(event) {
		this.ValueNumInputChange("gap", false);
	},
	HandleGrid3UpFOCUSOUT : function(event) {
		this.ValueNumInputChange("up_size", false);
	},
	HandleGrid3DownFOCUSOUT : function(event) {
		this.ValueNumInputChange("down_size", false);
	},
}, "ALittleIDE.Grid3S");

}