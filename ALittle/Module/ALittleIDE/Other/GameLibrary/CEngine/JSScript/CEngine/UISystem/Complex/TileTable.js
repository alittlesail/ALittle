{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __ceil = ALittle.Math_Ceil;
if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittle.TileTable = JavaScript.Class(ALittle.DisplayGroup, {
	Ctor : function(ctrl_sys) {
		this._x_gap = 0;
		this._y_gap = 0;
		this._x_start_gap = 0;
		this._y_start_gap = 0;
		this._col_count = 1;
		this._clip_left_index = 0;
		this._clip_right_index = 0;
		this._clip_top_index = 0;
		this._clip_bottom_index = 0;
		this._show_child_map = ALittle.CreateKeyWeakMap();
		this._pickup_rect = false;
		this._pickup_child = true;
		this._width = 0;
		this._height = 0;
	},
	get width() {
		return this._width;
	},
	get height() {
		return this._height;
	},
	set x_start_gap(value) {
		if (this._x_start_gap === value) {
			return;
		}
		this._x_start_gap = value;
		this.Layout(1);
	},
	get x_start_gap() {
		return this._x_start_gap;
	},
	set y_start_gap(value) {
		if (this._y_start_gap === value) {
			return;
		}
		this._y_start_gap = value;
		this.Layout(1);
	},
	get y_start_gap() {
		return this._y_start_gap;
	},
	set x_gap(value) {
		if (this._x_gap === value) {
			return;
		}
		this._x_gap = value;
		this.Layout(1);
	},
	get x_gap() {
		return this._x_gap;
	},
	set y_gap(value) {
		if (this._y_gap === value) {
			return;
		}
		this._y_gap = value;
		this.Layout(1);
	},
	get y_gap() {
		return this._y_gap;
	},
	set col_count(value) {
		if (value <= 0 || this._col_count === value) {
			return;
		}
		this._col_count = value;
		this.Layout(1);
	},
	get col_count() {
		return this._col_count;
	},
	AddChild : function(child, index) {
		let result = ALittle.DisplayGroup.AddChild.call(this, child, index);
		if (result === false) {
			return false;
		}
		if (index === undefined) {
			this.Layout(this.child_count);
		} else {
			this.Layout(index);
		}
		child.AddEventListener(___all_struct.get(-431205740), this, this.HandleChildResize);
		return true;
	},
	RemoveChild : function(child) {
		let child_index = this.GetChildIndex(child);
		if (child_index === 0) {
			return false;
		}
		let result = ALittle.DisplayGroup.RemoveChild.call(this, child);
		if (result === false) {
			return false;
		}
		this._show_child_map.delete(child);
		child.RemoveEventListener(___all_struct.get(-431205740), this);
		this.Layout(child_index);
		return true;
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
		let endv = index + count;
		for (let i = index; i < endv; i += 1) {
			let child = this._childs[i - 1];
			if (child === undefined) {
				break;
			}
			this._show_child_map.delete(child);
			child.RemoveEventListener(___all_struct.get(-431205740), this);
		}
		let result = ALittle.DisplayGroup.SpliceChild.call(this, index, count);
		if (result !== 0) {
			this.Layout(index);
		}
		return result;
	},
	RemoveAllChild : function() {
		let ___OBJECT_1 = this._childs;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let child = ___OBJECT_1[k - 1];
			if (child === undefined) break;
			child.RemoveEventListener(___all_struct.get(-431205740), this);
		}
		this._show_child_map = ALittle.CreateKeyWeakMap();
		this._clip_left_index = 0;
		this._clip_right_index = 0;
		this._clip_top_index = 0;
		this._clip_bottom_index = 0;
		ALittle.DisplayGroup.RemoveAllChild.call(this);
	},
	SetChildIndex : function(child, index) {
		let result = ALittle.DisplayGroup.SetChildIndex.call(this, child, index);
		this.Layout(1);
		return result;
	},
	Layout : function(index) {
		let child_count = this.child_count;
		if (child_count === 0) {
			this._width = 0;
			this._height = 0;
			return;
		}
		if (index > child_count) {
			index = child_count;
		}
		let child_list = this.childs;
		let start_index = 1;
		let start_x = this._x_start_gap;
		let start_y = this._y_start_gap;
		if (index > 1) {
			start_index = index;
			let current_child = child_list[index - 1 - 1];
			if ((index - 1) % this._col_count === 0) {
				start_x = this._x_start_gap;
				start_y = current_child.y + current_child.height + this._y_gap;
			} else {
				start_x = current_child.x + current_child.width + this._x_gap;
				start_y = current_child.y;
			}
		}
		for (let i = start_index; i <= child_count; i += 1) {
			child_list[i - 1].x = start_x;
			child_list[i - 1].y = start_y;
			if (i % this._col_count === 0) {
				start_x = this._x_start_gap;
				start_y = start_y + child_list[i - 1].height + this._y_gap;
			} else {
				start_x = start_x + child_list[i - 1].width + this._x_gap;
			}
		}
		this._width = 0;
		this._height = 0;
		let ___OBJECT_2 = child_list;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let child = ___OBJECT_2[k - 1];
			if (child === undefined) break;
			let width = child.x + child.width + this._x_start_gap;
			if (width > this._width) {
				this._width = width;
			}
			let height = child.y + child.height + this._y_start_gap;
			if (height > this._height) {
				this._height = height;
			}
		}
	},
	HandleChildResize : function(event) {
		this.Layout(this.GetChildIndex(event.target));
		this.DispatchEvent(___all_struct.get(-431205740), {});
	},
	ClipRect : function(left, top, right, bottom, h_move, v_move) {
		left = left - this._x;
		if (left < 0) {
			left = 0;
		}
		top = top - this._y;
		if (top < 0) {
			top = 0;
		}
		right = right - this._x;
		if (right > this.width) {
			right = this.width;
		}
		bottom = bottom - this._y;
		if (bottom > this.height) {
			bottom = this.height;
		}
		if (left >= right || top >= bottom) {
			this.clip = true;
			return;
		}
		this.clip = false;
		let child_count = this.child_count;
		if (child_count === 0) {
			return;
		}
		let childs = this.childs;
		let new_show_map = ALittle.CreateKeyWeakMap();
		this._show.RemoveAllChild();
		let max_index = this._col_count;
		if (this._child_count < max_index) {
			max_index = this._child_count;
		}
		let min_index = 1;
		let index = min_index;
		if (h_move === undefined || this._clip_left_index === 0) {
			do {
				if (childs[index - 1].x > left) {
					max_index = index;
					index = __ceil((max_index + min_index) / 2);
				} else if (childs[index - 1].x + childs[index - 1].width < left) {
					min_index = index;
					index = __ceil((max_index + min_index) / 2);
				} else {
					break;
				}
			} while (index !== min_index && index !== max_index);
		} else {
			index = this._clip_left_index;
			if (h_move < 0) {
				while (index < max_index) {
					if (childs[index - 1].x + childs[index - 1].width >= left) {
						break;
					}
					++ index;
				}
			} else if (h_move > 0) {
				while (index > min_index) {
					if (childs[index - 1].x <= left) {
						break;
					}
					-- index;
				}
			}
		}
		this._clip_left_index = index;
		max_index = this._col_count;
		if (this._child_count < max_index) {
			max_index = this._child_count;
		}
		for (let i = index; i <= max_index; i += 1) {
			if (childs[i - 1].x < right) {
				this._clip_right_index = i;
			} else {
				break;
			}
		}
		max_index = __ceil(this._child_count / this._col_count);
		min_index = 1;
		index = min_index;
		if (v_move === undefined || this._clip_top_index === 0) {
			do {
				let child_index = this._col_count * (index - 1) + 1;
				if (childs[child_index - 1].y > top) {
					max_index = index;
					index = __ceil((max_index + min_index) / 2);
				} else if (childs[child_index - 1].y + childs[child_index - 1].height < top) {
					min_index = index;
					index = __ceil((max_index + min_index) / 2);
				} else {
					break;
				}
			} while (index !== min_index && index !== max_index);
		} else {
			index = this._clip_top_index;
			if (v_move < 0) {
				while (index < max_index) {
					let child_index = this._col_count * (index - 1) + 1;
					if (childs[child_index - 1].y + childs[child_index - 1].height >= top) {
						break;
					}
					++ index;
				}
			} else if (v_move > 0) {
				while (index > min_index) {
					let child_index = this._col_count * (index - 1) + 1;
					if (childs[child_index - 1].y <= top) {
						break;
					}
					-- index;
				}
			}
		}
		this._clip_top_index = index;
		max_index = __ceil(this._child_count / this._col_count);
		let child_index = this._col_count * (index - 1) + 1;
		for (let i = index; i <= max_index; i += 1) {
			if (childs[child_index - 1].y < bottom) {
				this._clip_bottom_index = i;
			} else {
				break;
			}
			child_index = child_index + (this._col_count);
		}
		let base_index = this._col_count * (this._clip_top_index - 1);
		for (let i = this._clip_top_index; i <= this._clip_bottom_index; i += 1) {
			for (let j = this._clip_left_index; j <= this._clip_right_index; j += 1) {
				let child = childs[base_index + j - 1];
				if (child !== undefined) {
					this._show.AddChild(child._show);
					new_show_map.set(child, true);
					if (child.ClipRect !== undefined) {
						child.ClipRect(left, top, right, bottom, h_move, v_move);
					}
				}
			}
			base_index = base_index + (this._col_count);
		}
		for (let [child, v] of new_show_map) {
			if (v === undefined) continue;
			if (this._show_child_map.get(child) === undefined) {
				let e = {};
				e.target = child;
				child.DispatchEvent(___all_struct.get(1862557463), e);
			} else {
				this._show_child_map.delete(child);
			}
		}
		for (let [child, v] of this._show_child_map) {
			if (v === undefined) continue;
			let e = {};
			e.target = child;
			child.DispatchEvent(___all_struct.get(348388800), e);
		}
		this._show_child_map = new_show_map;
	},
}, "ALittle.TileTable");

}