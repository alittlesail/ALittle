{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.TextInputS === undefined) throw new Error(" extends class:ALittleIDE.TextInputS is undefined");
ALittleIDE.ImageInputS = JavaScript.Class(ALittleIDE.TextInputS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_imageinput";
	},
	LoadNatureBase : function() {
		ALittleIDE.TextInputS.LoadNatureBase.call(this);
		this.LoadValueData("margin_left");
		this.LoadValueData("margin_right");
		this.LoadValueData("margin_top");
		this.LoadValueData("margin_bottom");
		this.LoadShowTypeDataForImage("show_up");
		this.LoadShowTypeDataForImage("show_over");
		this.LoadShowTypeDataForImage("show_down");
		this.LoadShowTypeDataForImage("show_disabled");
	},
	HandleMarginLeftFOCUSOUT : function(event) {
		this.ValueNumInputChange("margin_left", false);
	},
	HandleMarginRightFOCUSOUT : function(event) {
		this.ValueNumInputChange("margin_right", false);
	},
	HandleMarginTopFOCUSOUT : function(event) {
		this.ValueNumInputChange("margin_top", false);
	},
	HandleMarginBottomFOCUSOUT : function(event) {
		this.ValueNumInputChange("margin_bottom", false);
	},
	HandleShowUpFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_up", this._show_up.text, this._show_up_grid9.selected, false);
	},
	HandleShowUpSelect : function(event) {
		let func = this.ImagePathSelectCallback.bind(this, "show_up", this.HandleShowUpFOCUSOUT, undefined);
		ALittleIDE.g_IDEAttrImageDialog.ShowDialog(undefined, func);
	},
	HandleShowOverFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_over", this._show_over.text, this._show_over_grid9.selected, false);
	},
	HandleShowOverSelect : function(event) {
		let func = this.ImagePathSelectCallback.bind(this, "show_over", this.HandleShowOverFOCUSOUT, undefined);
		ALittleIDE.g_IDEAttrImageDialog.ShowDialog(undefined, func);
	},
	HandleShowDownFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_down", this._show_down.text, this._show_down_grid9.selected, false);
	},
	HandleShowDownSelect : function(event) {
		let func = this.ImagePathSelectCallback.bind(this, "show_down", this.HandleShowDownFOCUSOUT, undefined);
		ALittleIDE.g_IDEAttrImageDialog.ShowDialog(undefined, func);
	},
	HandleShowDisabledFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_disabled", this._show_disabled.text, this._show_disabled_grid9.selected, false);
	},
	HandleShowDisabledSelect : function(event) {
		let func = this.ImagePathSelectCallback.bind(this, "show_disabled", this.HandleShowDisabledFOCUSOUT, undefined);
		ALittleIDE.g_IDEAttrImageDialog.ShowDialog(undefined, func);
	},
}, "ALittleIDE.ImageInputS");

}