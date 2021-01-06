{
if (typeof ALittle === "undefined") window.ALittle = {};


let __tostring = ALittle.String_ToString;
if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.TextArea = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._text = "";
		this._bold = false;
		this._italic = false;
		this._underline = false;
		this._deleteline = false;
		this._flip = 0;
		this._halign_type = 0;
		this._valign_type = 0;
		this._show = ALittle.NewObject(JavaScript.JTextArea);
	},
	Redraw : function() {
		this._show.NeedDraw();
	},
	set font_path(value) {
		this._font_path = value;
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this._ctrl_sys.SetFont(this, this._font_path, this._font_size);
	},
	set font_size(value) {
		this._font_size = value;
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this._ctrl_sys.SetFont(this, this._font_path, this._font_size);
	},
	get font_path() {
		return this._font_path;
	},
	get font_size() {
		return this._font_size;
	},
	set text(value) {
		if (value === undefined) {
			return;
		}
		value = __tostring(value);
		if (this._text === value) {
			return;
		}
		this._text = value;
		this._show.SetText(value);
	},
	get text() {
		return this._text;
	},
	set bold(value) {
		if (this._bold === value) {
			return;
		}
		this._bold = value;
		this._show.SetBold(value);
	},
	get bold() {
		return this._bold;
	},
	set italic(value) {
		if (this._italic === value) {
			return;
		}
		this._italic = value;
		this._show.SetItalic(value);
	},
	get italic() {
		return this._italic;
	},
	set underline(value) {
		if (this._underline === value) {
			return;
		}
		this._underline = value;
		this._show.SetUnderline(value);
	},
	get underline() {
		return this._underline;
	},
	set deleteline(value) {
		if (this._deleteline === value) {
			return;
		}
		this._deleteline = value;
		this._show.SetDeleteline(value);
	},
	get deleteline() {
		return this._deleteline;
	},
	set halign(value) {
		if (this._halign_type === value) {
			return;
		}
		this._halign_type = value;
		this._show.SetHAlign(value);
	},
	get halign() {
		return this._halign_type;
	},
	set valign(value) {
		if (this._valign_type === value) {
			return;
		}
		this._valign_type = value;
		this._show.SetVAlign(value);
	},
	get valign() {
		return this._valign_type;
	},
	get real_height() {
		return this._show.GetRealHeight();
	},
	get flip() {
		return this._flip;
	},
	set flip(value) {
		this._flip = value;
		this._show.SetFlip(value);
	},
}, "ALittle.TextArea");

}