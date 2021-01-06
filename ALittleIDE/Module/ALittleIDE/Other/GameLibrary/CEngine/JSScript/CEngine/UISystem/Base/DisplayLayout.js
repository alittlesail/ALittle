{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittle.DisplayLayout = JavaScript.Class(ALittle.DisplayGroup, {
	Ctor : function(ctrl_sys) {
		this._pickup_rect = true;
		this._pickup_child = true;
	},
	set width(value) {
		if (value === this._width) {
			return;
		}
		this._width = value;
		if (this._width_type === 1) {
			this._width_value = this._width;
		}
		let ___OBJECT_1 = this._childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			this.UpdateWidthLayout(child);
			this.UpdateXLayout(child);
		}
		this._show.SetWidth(value);
	},
	set height(value) {
		if (value === this._height) {
			return;
		}
		this._height = value;
		if (this._height_type === 1) {
			this._height_value = this._height;
		}
		let ___OBJECT_2 = this._childs;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let child = ___OBJECT_2[index - 1];
			if (child === undefined) break;
			this.UpdateHeightLayout(child);
			this.UpdateYLayout(child);
		}
		this._show.SetHeight(value);
	},
	UpdateXLayout : function(child) {
		if (child === undefined || child._show_parent !== this) {
			return;
		}
		let x_type = child._x_type;
		if (x_type === 1) {
			child.x = child._x_value;
		} else if (x_type === 2) {
			child.x = child._x_value;
		} else if (x_type === 3) {
			child.x = (this._width - child.width) / 2 + child._x_value;
		} else if (x_type === 4) {
			child.x = this._width - child.width - child._x_value;
		} else if (x_type === 7) {
			child.x = this._width * child._x_value;
		} else if (x_type === 8) {
			child.x = (this._width - child.width) / 2 + this._width * child._x_value;
		} else if (x_type === 9) {
			child.x = (this._width - child.width) * (1 - child._x_value);
		}
	},
	UpdateYLayout : function(child) {
		if (child === undefined || child._show_parent !== this) {
			return;
		}
		let y_type = child._y_type;
		if (y_type === 1) {
			child.y = child._y_value;
		} else if (y_type === 2) {
			child.y = child._y_value;
		} else if (y_type === 3) {
			child.y = (this._height - child.height) / 2 + child._y_value;
		} else if (y_type === 4) {
			child.y = this._height - child.height - child._y_value;
		} else if (y_type === 7) {
			child.y = this._height * child._y_value;
		} else if (y_type === 8) {
			child.y = (this._height - child.height) / 2 + this._height * child._y_value;
		} else if (y_type === 9) {
			child.y = (this._height - child.height) * (1 - child._y_value);
		}
	},
	UpdateWidthLayout : function(child) {
		if (child === undefined || child._show_parent !== this) {
			return;
		}
		let width_type = child._width_type;
		if (width_type === 2) {
			let real_width = this._width * child._width_value;
			if (real_width < 0) {
				real_width = 0;
			}
			child.width = real_width;
		} else if (width_type === 4) {
			let real_width = this._width - child._width_value;
			if (real_width < 0) {
				real_width = 0;
			}
			child.width = real_width;
		} else if (width_type === 1) {
			let real_width = child._width_value;
			if (real_width < 0) {
				real_width = 0;
			}
			child.width = real_width;
		}
	},
	UpdateHeightLayout : function(child) {
		if (child === undefined || child._show_parent !== this) {
			return;
		}
		let height_type = child._height_type;
		if (height_type === 2) {
			let real_height = this._height * child._height_value;
			if (real_height < 0) {
				real_height = 0;
			}
			child.height = real_height;
		} else if (height_type === 4) {
			let real_height = this._height - child._height_value;
			if (real_height < 0) {
				real_height = 0;
			}
			child.height = real_height;
		} else if (height_type === 1) {
			let real_height = child._height_value;
			if (real_height < 0) {
				real_height = 0;
			}
			child.height = real_height;
		}
	},
	get max_right() {
		return this._width;
	},
	get max_bottom() {
		return this._height;
	},
}, "ALittle.DisplayLayout");

}