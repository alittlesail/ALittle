{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.TileTableS = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_tiletable";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		this.LoadValueData("x_gap");
		this.LoadValueData("y_gap");
		this.LoadValueData("x_start_gap");
		this.LoadValueData("y_start_gap");
		this.LoadValueData("col_count");
	},
	HandleXStartGapFOCUSOUT : function(event) {
		this.ValueNumInputChange("x_start_gap", false);
	},
	HandleYStartGapFOCUSOUT : function(event) {
		this.ValueNumInputChange("y_start_gap", false);
	},
	HandleXGapFOCUSOUT : function(event) {
		this.ValueNumInputChange("x_gap", false);
	},
	HandleYGapFOCUSOUT : function(event) {
		this.ValueNumInputChange("y_gap", false);
	},
	HandleColCountFOCUSOUT : function(event) {
		this.ValueNumZInputChange("col_count", false);
	},
}, "ALittleIDE.TileTableS");

}