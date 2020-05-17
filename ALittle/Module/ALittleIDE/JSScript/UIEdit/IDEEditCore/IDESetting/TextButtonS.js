{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.TextButtonS = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_textbutton";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		this.LoadValueData("text");
		this.LoadEnumData("text_x_type", ALittleIDE.g_IDEEnum.xy_type);
		this.LoadValueData("text_x_value");
		this.LoadShowTypeDataForImage("show_up");
		this.LoadShowTypeDataForImage("show_over");
		this.LoadShowTypeDataForImage("show_down");
		this.LoadShowTypeDataForImage("show_disabled");
		this.LoadShowTypeNoNilData("show_text");
		this.LoadShowTypeNoNilData("show_over_text");
		this.LoadShowTypeNoNilData("show_down_text");
		this.LoadShowTypeNoNilData("show_disabled_text");
		this.LoadEnumData("file_select", ALittleIDE.g_IDEEnum.select_type);
	},
	HandleMTextFOCUSOUT : function(event) {
		this.DefaultNoStringInputChange("text", false);
	},
	HandleTextXTypeSELECT_CHANGE : function(event) {
		let object = this._object;
		let target_x = object.text_x_type;
		let new_x = target_x;
		let list = ALittleIDE.g_IDEEnum.xy_rtype;
		let revoke_bind = ALittle.NewObject(ALittleIDE.IDERevokeBind);
		this.TypeSelectChange("text_x_type", list, false, revoke_bind);
	},
	HandleTextXValueFOCUSOUT : function(event) {
		this._base.text_x_value = undefined;
		this.ValueNumInputChange("text_x_value", true);
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
	HandleShowTextFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_text", false);
	},
	HandleShowTextClear : function(event) {
		this.RemoverToNilShowSet("show_text", "", true);
	},
	HandleShowOverTextFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_over_text", false);
	},
	HandleShowOverTextClear : function(event) {
		this.RemoverToNilShowSet("show_over_text", "", true);
	},
	HandleShowDownTextFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_down_text", false);
	},
	HandleShowDownTextClear : function(event) {
		this.RemoverToNilShowSet("show_down_text", "", true);
	},
	HandleShowDisabledTextFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_disabled_text", false);
	},
	HandleShowDisabledTextClear : function(event) {
		this.RemoverToNilShowSet("show_disabled_text", "", true);
	},
	HandleHandFileSelectSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.select_rtype;
		let revoke_bind = ALittle.NewObject(ALittleIDE.IDERevokeBind);
		this.TypeSelectChange("file_select", list, false, revoke_bind);
	},
}, "ALittleIDE.TextButtonS");

}