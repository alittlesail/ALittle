{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.FramePlayS = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_frameplay";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		this.LoadValueData("interval");
		this.LoadValueData("play_loop_count");
		this.LoadValueData("base_y");
		this.LoadBoolData("auto_play", true, ALittleIDE.g_IDEEnum.yn_type);
	},
	HandleIntervalFOCUSOUT : function(event) {
		this.ValueNumZInputChange("interval", false);
	},
	HandleFramePlay : function(event) {
		this._object.Play();
	},
	HandleFrameStop : function(event) {
		this._object.Stop();
		this._object.ShowAllChild();
	},
	HandleBaseYFOCUSOUT : function(event) {
		this.ValueNumZInputChange("base_y", false);
	},
	HandleAutoPlaySELECT_CHANGE : function(event) {
		this.BoolSelectChange("auto_play", false, ALittleIDE.g_IDEEnum.yn_type);
	},
	HandlePlayLoopCountFOCUSOUT : function(event) {
		this.ValueNumZInputChange("play_loop_count", false);
	},
}, "ALittleIDE.FramePlayS");

}