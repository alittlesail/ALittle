{
if (typeof ALittleIDE === "undefined") ALittleIDE = {};


if (ALittleIDE.TextCheckButtonS === undefined) throw new Error(" extends class:ALittleIDE.TextCheckButtonS is undefined");
ALittleIDE.TextRadioButtonS = JavaScript.Class(ALittleIDE.TextCheckButtonS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_textradiobutton";
	},
	LoadNatureBase : function() {
		ALittleIDE.TextCheckButtonS.LoadNatureBase.call(this);
		this.LoadDefaultNilString("group_name");
	},
	HandleGroupNameFOCUSOUT : function(event) {
		this.DefaultNilStringInputChange("group_name", false);
	},
	HandleGroupNameAutoClick : function(event) {
		this._group_name.text = ALittle.Time_GetCurDate() + ALittle.Math_RandomInt(1, 1000);
		this.DefaultNilStringInputChange("group_name", false);
	},
}, "ALittleIDE.TextRadioButtonS");

}