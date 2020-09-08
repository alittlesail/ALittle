{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};


if (ALittle.Quad === undefined) throw new Error(" extends class:ALittle.Quad is undefined");
AUIPlugin.AUICodeQuad = JavaScript.Class(ALittle.Quad, {
	Ctor : function() {
		this._ediable = true;
	},
	get is_input() {
		return true;
	},
	get editable() {
		return this._ediable;
	},
	set editable(value) {
		this._ediable = value;
	},
	get font_size() {
		return AUIPlugin.CODE_FONT_SIZE;
	},
	get cursor_x() {
		let tab_child = this._user_data;
		return tab_child.cursor.x;
	},
	get cursor_y() {
		let tab_child = this._user_data;
		return tab_child.cursor.y;
	},
	get cursor_b() {
		let tab_child = this._user_data;
		return tab_child.cursor.y + tab_child.cursor.height;
	},
}, "AUIPlugin.AUICodeQuad");

if (ALittle.Linear === undefined) throw new Error(" extends class:ALittle.Linear is undefined");
AUIPlugin.AUICodeLinear = JavaScript.Class(ALittle.Linear, {
}, "AUIPlugin.AUICodeLinear");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
AUIPlugin.AUICodeEditContainer = JavaScript.Class(ALittle.DisplayLayout, {
	ClipRect : function(x, y, width, height, h_move, v_move) {
		this._user_data.ClipRect(x - this._x, y - this._y, width - this._x, height - this._y, h_move, v_move);
	},
}, "AUIPlugin.AUICodeEditContainer");

}