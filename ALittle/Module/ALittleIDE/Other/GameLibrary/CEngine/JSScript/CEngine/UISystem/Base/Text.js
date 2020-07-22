{
if (typeof ALittle === "undefined") window.ALittle = {};


let __tostring = ALittle.String_ToString;
let __byte = ALittle.String_Byte;
let __type = ALittle.String_Type;
if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.Text = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._text = "";
		this._bold = false;
		this._italic = false;
		this._underline = false;
		this._deleteline = false;
		this._flip = 0;
		this._show = ALittle.NewObject(JavaScript.JText);
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
		this.RejuseSize();
	},
	set font_size(value) {
		this._font_size = value;
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this._ctrl_sys.SetFont(this, this._font_path, this._font_size);
		this.RejuseSize();
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
		this.RejuseSize();
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
		this.RejuseSize();
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
		this.RejuseSize();
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
		this.RejuseSize();
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
		this.RejuseSize();
	},
	get deleteline() {
		return this._deleteline;
	},
	RejuseSize : function() {
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this.width = this._show.GetRealWidth();
		this.height = this._show.GetRealHeight();
		this.UpdateLayout();
	},
	set rejust_size(value) {
		if (value !== true) {
			return;
		}
		this.RejuseSize();
	},
	DeserializeSetter : function(info) {
		let base_attr = info.__base_attr;
		if (base_attr === undefined) {
			base_attr = {};
			let ___OBJECT_1 = info;
			for (let key in ___OBJECT_1) {
				let value = ___OBJECT_1[key];
				if (value === undefined) continue;
				if (__byte(key, 1) !== 95 && (__type(value) !== "table" || value.__class === undefined) && key !== "file_path") {
					base_attr[key] = value;
				}
			}
			info.__base_attr = base_attr;
		}
		let ___OBJECT_2 = base_attr;
		for (let key in ___OBJECT_2) {
			let value = ___OBJECT_2[key];
			if (value === undefined) continue;
			this[key] = value;
		}
		if (info.font_path !== undefined) {
			this["font_path"] = info.font_path;
		}
	},
	get font_height() {
		return this._show.GetFontHeight();
	},
	get flip() {
		return this._flip;
	},
	set flip(value) {
		this._flip = value;
		this._show.SetFlip(value);
	},
}, "ALittle.Text");

}