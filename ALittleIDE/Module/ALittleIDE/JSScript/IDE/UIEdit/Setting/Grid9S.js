{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.Grid9S = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_grid9";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		this.LoadValueData("left_size");
		this.LoadValueData("right_size");
		this.LoadValueData("top_size");
		this.LoadValueData("bottom_size");
	},
	HandleGrid9LeftFOCUSOUT : function(event) {
		this.ValueNumInputChange("left_size", false);
	},
	HandleGrid9RightFOCUSOUT : function(event) {
		this.ValueNumInputChange("right_size", false);
	},
	HandleGrid9TopFOCUSOUT : function(event) {
		this.ValueNumInputChange("top_size", false);
	},
	HandleGrid9BottomFOCUSOUT : function(event) {
		this.ValueNumInputChange("bottom_size", false);
	},
	HandleAutoCut : function(event) {
		let revoke_bind = ALittle.NewObject(ALittle.RevokeBind);
		this._left_size.text = 0;
		this.ValueNumInputChange("left_size", false, revoke_bind);
		this._right_size.text = 0;
		this.ValueNumInputChange("right_size", false, revoke_bind);
		this._top_size.text = 0;
		this.ValueNumInputChange("top_size", false, revoke_bind);
		this._bottom_size.text = 0;
		this.ValueNumInputChange("bottom_size", false, revoke_bind);
		this._tab_child.revoke_list.PushRevoke(revoke_bind);
	},
}, "ALittleIDE.Grid9S");

}