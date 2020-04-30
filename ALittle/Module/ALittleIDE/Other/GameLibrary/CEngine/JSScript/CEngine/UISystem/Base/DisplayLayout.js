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
		if (this._width_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._width_value = this._width;
		}
		let ___OBJECT_1 = this._childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let value = ___OBJECT_1[index - 1];
			if (value === undefined) break;
			this.UpdateWidthLayout(value);
			this.UpdateXLayout(value);
		}
		this._show.SetWidth(value);
	},
	set height(value) {
		if (value === this._height) {
			return;
		}
		this._height = value;
		if (this._height_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._height_value = this._height;
		}
		let ___OBJECT_2 = this._childs;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let value = ___OBJECT_2[index - 1];
			if (value === undefined) break;
			this.UpdateHeightLayout(value);
			this.UpdateYLayout(value);
		}
		this._show.SetHeight(value);
	},
	UpdateXLayout : function(child) {
		if (child === undefined || child._show_parent !== this) {
			return;
		}
		if (child._x_type === ALittle.UIEnumTypes.POS_ABS) {
			child.x = child._x_value;
		} else if (child._x_type === ALittle.UIEnumTypes.POS_ALIGN_STARTING) {
			child.x = child._x_value;
		} else if (child._x_type === ALittle.UIEnumTypes.POS_ALIGN_CENTER) {
			child.x = (this._width - child.width) / 2 + child._x_value;
		} else if (child._x_type === ALittle.UIEnumTypes.POS_ALIGN_ENDING) {
			child.x = this._width - child.width - child._x_value;
		} else if (child._x_type === ALittle.UIEnumTypes.POS_PERCENT_STARTING) {
			child.x = this._width * child._x_value;
		} else if (child._x_type === ALittle.UIEnumTypes.POS_PERCENT_CENTER) {
			child.x = (this._width - child.width) / 2 + this._width * child._x_value;
		} else if (child._x_type === ALittle.UIEnumTypes.POS_PERCENT_ENDING) {
			child.x = (this._width - child.width) * (1 - child._x_value);
		}
	},
	UpdateYLayout : function(child) {
		if (child === undefined || child._show_parent !== this) {
			return;
		}
		if (child._y_type === ALittle.UIEnumTypes.POS_ABS) {
			child.y = child._y_value;
		} else if (child._y_type === ALittle.UIEnumTypes.POS_ALIGN_STARTING) {
			child.y = child._y_value;
		} else if (child._y_type === ALittle.UIEnumTypes.POS_ALIGN_CENTER) {
			child.y = (this._height - child.height) / 2 + child._y_value;
		} else if (child._y_type === ALittle.UIEnumTypes.POS_ALIGN_ENDING) {
			child.y = this._height - child.height - child._y_value;
		} else if (child._y_type === ALittle.UIEnumTypes.POS_PERCENT_STARTING) {
			child.y = this._height * child._y_value;
		} else if (child._y_type === ALittle.UIEnumTypes.POS_PERCENT_CENTER) {
			child.y = (this._height - child.height) / 2 + this._height * child._y_value;
		} else if (child._y_type === ALittle.UIEnumTypes.POS_PERCENT_ENDING) {
			child.y = (this._height - child.height) * (1 - child._y_value);
		}
	},
	UpdateWidthLayout : function(child) {
		if (child === undefined || child._show_parent !== this) {
			return;
		}
		if (child._width_type === ALittle.UIEnumTypes.SIZE_PERCENT) {
			let real_width = this._width * child._width_value;
			if (real_width < 0) {
				real_width = 0;
			}
			child.width = real_width;
		} else if (child._width_type === ALittle.UIEnumTypes.SIZE_MARGIN) {
			let real_width = this._width - child._width_value;
			if (real_width < 0) {
				real_width = 0;
			}
			child.width = real_width;
		} else if (child._width_type === ALittle.UIEnumTypes.SIZE_ABS) {
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
		if (child._height_type === ALittle.UIEnumTypes.SIZE_PERCENT) {
			let real_height = this._height * child._height_value;
			if (real_height < 0) {
				real_height = 0;
			}
			child.height = real_height;
		} else if (child._height_type === ALittle.UIEnumTypes.SIZE_MARGIN) {
			let real_height = this._height - child._height_value;
			if (real_height < 0) {
				real_height = 0;
			}
			child.height = real_height;
		} else if (child._height_type === ALittle.UIEnumTypes.SIZE_ABS) {
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