{
if (typeof ALittle === "undefined") window.ALittle = {};


let __remove = ALittle.List_Remove;
let __insert = ALittle.List_Insert;
let __splice = ALittle.List_Splice;
let __cos = ALittle.Math_Cos;
let __sin = ALittle.Math_Sin;
if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.DisplayGroup = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._childs = [];
		this._child_count = 0;
		this._show = ALittle.NewObject(JavaScript.JDisplayObjects);
		this._pickup_rect = false;
		this._pickup_child = true;
		this._pickup_this = false;
	},
	GetChildIndex : function(child) {
		if (child === undefined) {
			return 0;
		}
		if (child._show_parent !== this && child._logic_parent !== this) {
			return 0;
		}
		let ___OBJECT_1 = this._childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let value = ___OBJECT_1[index - 1];
			if (value === undefined) break;
			if (value === child) {
				return index;
			}
		}
		return 0;
	},
	SetChildIndex : function(child, index) {
		let cur_index = this.GetChildIndex(child);
		if (cur_index === 0) {
			return false;
		}
		if (cur_index === index) {
			return true;
		}
		if (index < 1) {
			index = 1;
		}
		if (index > this._child_count) {
			index = this._child_count;
		}
		__remove(this._childs, cur_index);
		this._show.RemoveChild(child._show);
		let back_child = this._childs[index - 1];
		if (back_child !== undefined) {
			this._show.AddChildBefore(back_child._show, child._show);
		} else {
			this._show.AddChild(child._show);
		}
		__insert(this._childs, index, child);
		return true;
	},
	GetChildByIndex : function(index) {
		return this._childs[index - 1];
	},
	get childs() {
		return this._childs;
	},
	get child_count() {
		return this._child_count;
	},
	AddChild : function(child, index) {
		if (child === undefined || child === this) {
			return false;
		}
		if (child._show_parent === this || child._logic_parent === this) {
			return true;
		}
		if (child._logic_parent !== undefined) {
			child._logic_parent.RemoveChild(child);
		} else if (child._show_parent !== undefined) {
			child._show_parent.RemoveChild(child);
		}
		child._show_parent = this;
		child._logic_parent = undefined;
		if (index === undefined || index > this._child_count || this._child_count < 1) {
			++ this._child_count;
			this._childs[this._child_count - 1] = child;
			this._show.AddChild(child._show);
		} else {
			if (index < 1) {
				index = 1;
			}
			let back_child = this._childs[index - 1];
			this._show.AddChildBefore(back_child._show, child._show);
			__insert(this._childs, index, child);
			++ this._child_count;
		}
		child.visible = child._visible;
		child.alpha = child._alpha;
		child.disabled = child._disabled;
		child.UpdateLayout();
		return true;
	},
	RemoveChild : function(child) {
		if (child === undefined) {
			return false;
		}
		if (child._show_parent !== this && child._logic_parent !== this) {
			return false;
		}
		let ___OBJECT_2 = this._childs;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let value = ___OBJECT_2[index - 1];
			if (value === undefined) break;
			if (value === child) {
				__remove(this._childs, index);
				this._show.RemoveChild(child._show);
				child._show_parent = undefined;
				child._logic_parent = undefined;
				-- this._child_count;
				return true;
			}
		}
		return false;
	},
	SpliceChild : function(index, count) {
		let remain_count = this._child_count - index + 1;
		if (count === undefined) {
			count = remain_count;
		} else if (count > remain_count) {
			count = remain_count;
		}
		if (count <= 0) {
			return 0;
		}
		let old_count = this._child_count;
		let endv = index + count;
		for (let i = index; i < endv; i += 1) {
			let child = this._childs[i - 1];
			if (child === undefined) {
				break;
			}
			this._show.RemoveChild(child._show);
			child._show_parent = undefined;
			child._logic_parent = undefined;
			-- this._child_count;
		}
		__splice(this._childs, index, count);
		return old_count - this._child_count;
	},
	HasChild : function(child) {
		if (child === undefined) {
			return false;
		}
		return child._show_parent === this || child._logic_parent === this;
	},
	get parent() {
		if (this._logic_parent !== undefined) {
			return this._logic_parent;
		}
		return this._show_parent;
	},
	RemoveAllChild : function() {
		let ___OBJECT_3 = this._childs;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let value = ___OBJECT_3[index - 1];
			if (value === undefined) break;
			value._show_parent = undefined;
			value._logic_parent = undefined;
		}
		this._show.RemoveAllChild();
		this._childs = [];
		this._child_count = 0;
	},
	set alpha(value) {
		this._alpha = value;
		if (this._show_parent !== undefined) {
			this._abs_alpha = this._show_parent._abs_alpha * value;
		} else {
			this._abs_alpha = value;
		}
		let ___OBJECT_4 = this._childs;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let child = ___OBJECT_4[index - 1];
			if (child === undefined) break;
			child.alpha = child.alpha;
		}
	},
	set visible(value) {
		this._visible = value;
		if (this._show_parent !== undefined) {
			this._abs_visible = this._show_parent._abs_visible && value;
		} else {
			this._abs_visible = value;
		}
		this._show.SetVisible(this._abs_visible);
		let ___OBJECT_5 = this._childs;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let child = ___OBJECT_5[index - 1];
			if (child === undefined) break;
			child.visible = child.visible;
		}
	},
	set disabled(value) {
		this._disabled = value;
		if (this._show_parent !== undefined) {
			this._abs_disabled = this._show_parent._abs_disabled || value;
		} else {
			this._abs_disabled = value;
		}
		let ___OBJECT_6 = this._childs;
		for (let index = 1; index <= ___OBJECT_6.length; ++index) {
			let child = ___OBJECT_6[index - 1];
			if (child === undefined) break;
			child.disabled = child.disabled;
		}
	},
	PickUp : function(x, y) {
		if (this._ignore || this._abs_disabled || this._abs_visible === false) {
			return [undefined, undefined, undefined];
		}
		let xx = x - this._x;
		let yy = y - this._y;
		if (this._angle !== 0) {
			let rad = 3.1415926 * -this._angle / 180.0;
			let cos = __cos(rad);
			let sin = __sin(rad);
			let xxx = xx * cos + yy * -sin;
			let yyy = xx * sin + yy * cos;
			xx = xxx;
			yy = yyy;
		}
		if (this._scale_x > 0) {
			xx = xx / (this._scale_x);
		}
		if (this._scale_y > 0) {
			yy = yy / (this._scale_y);
		}
		let rel_x = xx + this._center_x;
		let rel_y = yy + this._center_y;
		if (this._scale_x <= 0 || this._scale_y <= 0) {
			if (this._modal) {
				return [this, rel_x, rel_y];
			}
			return [undefined, rel_x, rel_y];
		}
		if (this._pickup_rect && (rel_x < 0 || rel_y < 0 || rel_x >= this._width || rel_y >= this._height)) {
			if (this._modal) {
				return [this, rel_x, rel_y];
			}
			return [undefined, rel_x, rel_y];
		}
		if (this._pickup_child) {
			let childs = this._childs;
			for (let index = this._child_count; index >= 1; index += -1) {
				let [v_focus, v_x, v_y] = childs[index - 1].PickUp(rel_x, rel_y);
				if (v_focus !== undefined) {
					return [v_focus, v_x, v_y];
				}
			}
		}
		if (this._modal || (this._pickup_rect && this._pickup_child === false) || this._pickup_this) {
			return [this, rel_x, rel_y];
		}
		return [undefined, undefined, undefined];
	},
	set width(value) {
		this._show.SetWidth(value);
	},
	set height(value) {
		this._show.SetHeight(value);
	},
	get width() {
		if (this._pickup_rect) {
			return this._width;
		}
		return this.bound_width;
	},
	get height() {
		if (this._pickup_rect) {
			return this._height;
		}
		return this.bound_height;
	},
	get bound_width() {
		let min_x = undefined;
		let max_x = undefined;
		let ___OBJECT_7 = this._childs;
		for (let index = 1; index <= ___OBJECT_7.length; ++index) {
			let value = ___OBJECT_7[index - 1];
			if (value === undefined) break;
			if (min_x === undefined || min_x > value._x) {
				min_x = value._x;
			}
			let width = value.width;
			let right = width + value._x;
			if (max_x === undefined || max_x < right) {
				max_x = right;
			}
		}
		if (max_x === undefined) {
			max_x = 0;
		}
		if (min_x === undefined) {
			min_x = 0;
		}
		let real_width = max_x - min_x;
		if (real_width < 0) {
			real_width = 0;
		}
		return real_width;
	},
	get bound_height() {
		let min_y = undefined;
		let max_y = undefined;
		let ___OBJECT_8 = this._childs;
		for (let index = 1; index <= ___OBJECT_8.length; ++index) {
			let value = ___OBJECT_8[index - 1];
			if (value === undefined) break;
			if (min_y === undefined || min_y > value._y) {
				min_y = value._y;
			}
			let height = value.height;
			let bottom = height + value._y;
			if (max_y === undefined || max_y < bottom) {
				max_y = bottom;
			}
		}
		if (max_y === undefined) {
			max_y = 0;
		}
		if (min_y === undefined) {
			min_y = 0;
		}
		let real_height = max_y - min_y;
		if (real_height < 0) {
			real_height = 0;
		}
		return real_height;
	},
	get max_right() {
		let max_x = undefined;
		let ___OBJECT_9 = this._childs;
		for (let index = 1; index <= ___OBJECT_9.length; ++index) {
			let value = ___OBJECT_9[index - 1];
			if (value === undefined) break;
			let width = value.width;
			let right = width + value.x;
			if (max_x === undefined || max_x < right) {
				max_x = right;
			}
		}
		if (max_x === undefined) {
			max_x = 0;
		}
		return max_x;
	},
	get max_bottom() {
		let max_y = undefined;
		let ___OBJECT_10 = this._childs;
		for (let index = 1; index <= ___OBJECT_10.length; ++index) {
			let value = ___OBJECT_10[index - 1];
			if (value === undefined) break;
			let height = value.height;
			let bottom = height + value.y;
			if (max_y === undefined || max_y < bottom) {
				max_y = bottom;
			}
		}
		if (max_y === undefined) {
			max_y = 0;
		}
		return max_y;
	},
	UpdateXLayout : function(child) {
	},
	UpdateYLayout : function(child) {
	},
	UpdateWidthLayout : function(child) {
	},
	UpdateHeightLayout : function(child) {
	},
}, "ALittle.DisplayGroup");

}