{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.SpriteS === undefined) throw new Error(" extends class:ALittleIDE.SpriteS is undefined");
ALittleIDE.SpritePlayS = JavaScript.Class(ALittleIDE.SpriteS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_spriteplay";
	},
	LoadNatureBase : function() {
		ALittleIDE.SpriteS.LoadNatureBase.call(this);
		this.LoadValueData("interval");
	},
	HandleIntervalFOCUSOUT : function(event) {
		this.ValueNumZInputChange("interval", false);
	},
}, "ALittleIDE.SpritePlayS");

}