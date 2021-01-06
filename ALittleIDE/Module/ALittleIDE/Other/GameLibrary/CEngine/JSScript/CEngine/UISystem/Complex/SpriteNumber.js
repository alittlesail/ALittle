{
if (typeof ALittle === "undefined") window.ALittle = {};


let __tostring = ALittle.String_ToString;
let __len = ALittle.String_Len;
let __byte = ALittle.String_Byte;
if (ALittle.Linear === undefined) throw new Error(" extends class:ALittle.Linear is undefined");
ALittle.SpriteNumber = JavaScript.Class(ALittle.Linear, {
	Ctor : function() {
		this._col_count = 1;
		this._text = "";
		this._cell_width = 0;
		this._sprite_pool = [];
		this._pool_count = 0;
	},
	get texture_name() {
		return this._texture_name;
	},
	get cell_width() {
		return this._cell_width;
	},
	set cell_width(value) {
		this._cell_width = value;
		let ___OBJECT_1 = this._childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			child.width = value;
		}
		let ___OBJECT_2 = this._sprite_pool;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let child = ___OBJECT_2[index - 1];
			if (child === undefined) break;
			child.width = value;
		}
		this.Layout(1);
	},
	set texture_name(value) {
		if (this._texture_name === value) {
			return;
		}
		this._texture_name = value;
		let ___OBJECT_3 = this._childs;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let child = ___OBJECT_3[index - 1];
			if (child === undefined) break;
			child.texture_name = value;
		}
		let ___OBJECT_4 = this._sprite_pool;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let child = ___OBJECT_4[index - 1];
			if (child === undefined) break;
			child.texture_name = value;
		}
	},
	get col_count() {
		return this._col_count;
	},
	set col_count(value) {
		if (value < 1) {
			value = 1;
		}
		this._col_count = value;
		let ___OBJECT_5 = this._childs;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let child = ___OBJECT_5[index - 1];
			if (child === undefined) break;
			child.col_count = value;
		}
		let ___OBJECT_6 = this._sprite_pool;
		for (let index = 1; index <= ___OBJECT_6.length; ++index) {
			let child = ___OBJECT_6[index - 1];
			if (child === undefined) break;
			child.col_count = value;
		}
	},
	get text() {
		return this._text;
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
		let len = __len(value);
		if (this._child_count > len) {
			for (let index = len + 1; index <= this._child_count; index += 1) {
				this._pool_count = this._pool_count + (1);
				this._sprite_pool[this._pool_count - 1] = this._childs[index - 1];
			}
			this.SpliceChild(len + 1);
		} else if (this._child_count < len) {
			for (let index = this._child_count + 1; index <= len; index += 1) {
				let child = undefined;
				if (this._pool_count > 1) {
					child = this._sprite_pool[this._pool_count - 1];
					this._sprite_pool[this._pool_count - 1] = undefined;
					this._pool_count = this._pool_count - (1);
				} else {
					child = ALittle.NewObject(ALittle.Sprite, this._ctrl_sys);
					child.col_count = this._col_count;
					child.texture_name = this._texture_name;
					child.width = this._cell_width;
				}
				this.AddChild(child);
			}
		}
		let byte = 0;
		let ___OBJECT_7 = this._childs;
		for (let index = 1; index <= ___OBJECT_7.length; ++index) {
			let child = ___OBJECT_7[index - 1];
			if (child === undefined) break;
			byte = __byte(value, index);
			if (byte >= 48 && byte <= 57) {
				child.col_index = byte - 47;
			} else if (byte === 43) {
				child.col_index = 11;
			} else if (byte === 45) {
				child.col_index = 12;
			} else if (byte === 46) {
				child.col_index = 13;
			} else if (byte === 47) {
				child.col_index = 14;
			} else {
				child.col_index = 1;
			}
		}
	},
}, "ALittle.SpriteNumber");

}