{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayObjectS === undefined) throw new Error(" extends class:ALittleIDE.DisplayObjectS is undefined");
ALittleIDE.ImagePlayS = JavaScript.Class(ALittleIDE.DisplayObjectS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_imageplay";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayObjectS.LoadNatureBase.call(this);
		this.LoadValueData("interval");
		this.LoadShowTypeData("path_list");
	},
	HandleIntervalFOCUSOUT : function(event) {
		this.ValueNumZInputChange("interval", false);
	},
	HandlePathListFOCUSOUT : function(event) {
		this.TableDataSet("path_list", false);
	},
}, "ALittleIDE.ImagePlayS");

}