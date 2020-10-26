{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.IDEAttrTextDialog = JavaScript.Class(undefined, {
	ShowDialog : function(target_panel, text, need_reset) {
		if (this._dialog === undefined) {
			this._dialog = ALittleIDE.g_Control.CreateControl("ide_text_edit_dialog", this);
			A_LayerManager.AddToModal(this._dialog);
		}
		this._dialog.visible = true;
		this._target_panel = target_panel;
		this._target_text = text;
		this._target_need_reset = need_reset;
		this.ResetText();
	},
	HideDialog : function() {
		this._dialog.visible = false;
	},
	ReadColor : function(text) {
		let display_object = this["_" + text];
		let value = ALittle.Math_ToDouble(display_object.text);
		if (value === undefined || value < 0) {
			display_object.text = "0";
			return 0;
		} else if (value > 255) {
			display_object.text = "255";
			return 1;
		} else {
			value = value / 255;
			return value;
		}
	},
	HandleEditChanged : function(event) {
		let info = {};
		info.__class = "Text";
		if (this._bold.text === "是") {
			info.bold = true;
		}
		if (this._underline.text === "是") {
			info.underline = true;
		}
		if (this._deleteline.text === "是") {
			info.deleteline = true;
		}
		if (this._italic.text === "是") {
			info.italic = true;
		}
		if (this._font_path.text !== "") {
			info.font_path = this._font_path.text;
		}
		if (this._font_size.text !== "") {
			info.font_size = ALittle.Math_ToInt(this._font_size.text);
		}
		info.red = this.ReadColor("red");
		if (info.red === 1) {
			info.red = undefined;
		}
		info.green = this.ReadColor("green");
		if (info.green === 1) {
			info.green = undefined;
		}
		info.blue = this.ReadColor("blue");
		if (info.blue === 1) {
			info.blue = undefined;
		}
		let info_json = ALittle.String_JsonEncode(info);
		this._target_panel["_" + this._target_text].text = info_json;
		this._target_panel.RemoverToNilShowSet(this._target_text, info_json, this._target_need_reset);
	},
	ResetText : function() {
		let info = this._target_panel.base[this._target_text];
		if (info === undefined) {
			info = this._target_panel.default[this._target_text];
		}
		if (info === undefined) {
			info = {};
		}
		this._bold.text = "否";
		if (info.bold) {
			this._bold.text = "是";
		}
		this._underline.text = "否";
		if (info.underline) {
			this._underline.text = "是";
		}
		this._deleteline.text = "否";
		if (info.deleteline) {
			this._deleteline.text = "是";
		}
		this._italic.text = "否";
		if (info.italic) {
			this._italic.text = "是";
		}
		this._font_path.text = "";
		if (ALittleIDE.g_IDEProject.project !== undefined) {
			this._font_path.text = ALittleIDE.g_IDEProject.project.config.GetConfig("default_font_path", "");
		}
		if (info.font_path !== undefined) {
			this._font_path.text = info.font_path;
		}
		this._font_size.text = "";
		if (ALittleIDE.g_IDEProject.project !== undefined) {
			this._font_size.text = ALittleIDE.g_IDEProject.project.config.GetConfig("default_font_size", 15);
		}
		if (info.font_size !== undefined) {
			this._font_size.text = info.font_size;
		}
		if (info.red === undefined) {
			this._red.text = 255;
		} else {
			this._red.text = ALittle.Math_Floor(info.red * 255);
		}
		if (info.green === undefined) {
			this._green.text = 255;
		} else {
			this._green.text = ALittle.Math_Floor(info.green * 255);
		}
		if (info.blue === undefined) {
			this._blue.text = 255;
		} else {
			this._blue.text = ALittle.Math_Floor(info.blue * 255);
		}
	},
}, "ALittleIDE.IDEAttrTextDialog");

ALittleIDE.g_IDEAttrTextDialog = ALittle.NewObject(ALittleIDE.IDEAttrTextDialog);
}