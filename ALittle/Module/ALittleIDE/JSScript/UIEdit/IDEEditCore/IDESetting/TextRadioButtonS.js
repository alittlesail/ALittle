{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.TextCheckButtonS === undefined) throw new Error(" extends class:ALittleIDE.TextCheckButtonS is undefined");
ALittleIDE.TextRadioButtonS = JavaScript.Class(ALittleIDE.TextCheckButtonS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_textradiobutton";
	},
	LoadNatureBase : function() {
		ALittleIDE.TextCheckButtonS.LoadNatureBase.call(this);
	},
}, "ALittleIDE.TextRadioButtonS");

}