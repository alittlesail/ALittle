{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.ScrollScreenS = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_scrollscreen";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		this.LoadShowTypeDataForExtends("container");
		this.LoadShowTypeDataForExtends("right_scrollbar");
		this.LoadShowTypeDataForExtends("bottom_scrollbar");
		this.LoadBoolData("open_extends_drag", true, ALittleIDE.g_IDEEnum.yn_type);
	},
	HandleContainerFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForExtends("container", this._container.text, false);
	},
	HandleRightSFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForExtends("right_scrollbar", this._right_scrollbar.text, false);
	},
	HandleBottomBFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForExtends("bottom_scrollbar", this._bottom_scrollbar.text, false);
	},
	HandleHandOpenExtendsDragSELECT_CHANGE : function(event) {
		this.BoolSelectChange("open_extends_drag", false, ALittleIDE.g_IDEEnum.yn_type);
	},
}, "ALittleIDE.ScrollScreenS");

}