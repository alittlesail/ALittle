{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __ceil = ALittle.Math_Ceil;
if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittle.Linear = JavaScript.Class(ALittle.DisplayGroup, {
	Ctor : function(ctrl_sys) {
		this._type = 1;
		this._size_fixed = true;
		this._gap = 0;
		this._clip_up_index = 0;
		this._clip_down_index = 0;
		this._child_width_map = ALittle.CreateKeyWeakMap();
		this._child_height_map = ALittle.CreateKeyWeakMap();
		this._show_child_map = ALittle.CreateKeyWeakMap();
		this._pickup_rect = false;
		this._pickup_child = true;
	},
	get clip_up_index() {
		return this._clip_up_index;
	},
	get clip_down_index() {
		return this._clip_down_index;
	},
	get size_fixed() {
		return this._size_fixed;
	},
	set size_fixed(value) {
		if (this._size_fixed === value) {
			return;
		}
		this._size_fixed = value;
		this.UpdateSize();
	},
	set type(value) {
		if (this._type === value) {
			return;
		}
		this._type = value;
		this.UpdateSize();
		this.Layout(1);
	},
	get type() {
		return this._type;
	},
	set gap(value) {
		if (this._gap === value) {
			return;
		}
		this._gap = value;
		this.Layout(1);
	},
	get gap() {
		return this._gap;
	},
	GetShowMap : function() {
		return this._show_child_map;
	},
	AddChild : function(child, index) {
		if (ALittle.DisplayGroup.AddChild.call(this, child, index) === false) {
			return false;
		}
		if (index === undefined) {
			this.Layout(this.child_count);
		} else {
			this.Layout(index);
		}
		this._child_width_map.set(child, child.width);
		this._child_height_map.set(child, child.height);
		if (this._size_fixed) {
			if (this._type === 1) {
				child.height = this._height;
			} else {
				child.width = this._width;
			}
		}
		child.AddEventListener(___all_struct.get(-431205740), this, this.HandleChildResize);
		return true;
	},
	RemoveChild : function(child) {
		let child_index = this.GetChildIndex(child);
		if (child_index === 0) {
			return false;
		}
		if (ALittle.DisplayGroup.RemoveChild.call(this, child) === false) {
			return false;
		}
		this._child_width_map.delete(child);
		this._child_height_map.delete(child);
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
			this._child_width_map.delete(child);
			this._child_height_map.delete(child);
			this._show_child_map.delete(child);
			child.RemoveEventListener(___all_struct.get(-431205740), this);
		}
		let result = ALittle.DisplayGroup.SpliceChild.call(this, index, count);
		if (result !== 0) {
			this.Layout(index);
		}
		this._clip_up_index = 0;
		this._clip_down_index = 0;
		return result;
	},
	RemoveAllChild : function() {
		let ___OBJECT_1 = this._childs;
		for (let i = 1; i <= ___OBJECT_1.length; ++i) {
			let child = ___OBJECT_1[i - 1];
			if (child === undefined) break;
			child.RemoveEventListener(___all_struct.get(-431205740), this);
		}
		this._child_width_map = ALittle.CreateKeyWeakMap();
		this._child_height_map = ALittle.CreateKeyWeakMap();
		this._show_child_map = ALittle.CreateKeyWeakMap();
		this._clip_up_index = 0;
		this._clip_down_index = 0;
		ALittle.DisplayGroup.RemoveAllChild.call(this);
	},
	SetChildIndex : function(child, index) {
		ALittle.DisplayGroup.SetChildIndex.call(this, child, index);
		this.Layout(1);
		return true;
	},
	set width(value) {
		if (this._width === value) {
			return;
		}
		this._width = value;
		if (this._width_type === 1) {
			this._width_value = this._width;
		}
		if (this._type !== 1 && this._size_fixed) {
			let ___OBJECT_2 = this._childs;
			for (let index = 1; index <= ___OBJECT_2.length; ++index) {
				let child = ___OBJECT_2[index - 1];
				if (child === undefined) break;
				child.width = value;
			}
		}
	},
	get width() {
		if (this._size_fixed) {
			if (this._type === 1) {
				if (this._child_count === 0) {
					return 0;
				}
				let child = this._childs[this._child_count - 1];
				return child.x + child.width;
			}
			return this._width;
		}
		return ALittle.DisplayGroup.__getter.max_right.call(this);
	},
	set height(value) {
		if (this._height === value) {
			return;
		}
		this._height = value;
		if (this._height_type === 1) {
			this._height_value = this._height;
		}
		if (this._type !== 2 && this._size_fixed) {
			let ___OBJECT_3 = this._childs;
			for (let index = 1; index <= ___OBJECT_3.length; ++index) {
				let child = ___OBJECT_3[index - 1];
				if (child === undefined) break;
				child.height = value;
			}
		}
	},
	get height() {
		if (this._size_fixed) {
			if (this._type === 2) {
				if (this._child_count === 0) {
					return 0;
				}
				let child = this._childs[this._child_count - 1];
				return child.y + child.height;
			}
			return this._height;
		}
		return ALittle.DisplayGroup.__getter.max_bottom.call(this);
	},
	UpdateSize : function() {
		if (this._size_fixed) {
			if (this._type === 1) {
				for (let [k, v] of this._child_width_map) {
					if (v === undefined) continue;
					k.width = v;
					k.height = this._height;
				}
			} else {
				for (let [k, v] of this._child_height_map) {
					if (v === undefined) continue;
					k.width = this._width;
					k.height = v;
				}
			}
		} else {
			for (let [k, v] of this._child_width_map) {
				if (v === undefined) continue;
				k.width = v;
			}
			for (let [k, v] of this._child_height_map) {
				if (v === undefined) continue;
				k.height = v;
			}
		}
	},
	Layout : function(index) {
		this._clip_up_index = 0;
		this._clip_down_index = 0;
		let child_count = this.child_count;
		if (index <= 0 || index > child_count) {
			return;
		}
		if (this._type === 1) {
			let offset = 0.0;
			if (index > 1) {
				offset = this._childs[index - 1 - 1].x + this._childs[index - 1 - 1].width + this._gap;
			}
			for (let i = index; i <= child_count; i += 1) {
				this._childs[i - 1].x = offset;
				this._childs[i - 1].y = 0;
				offset = offset + this._childs[i - 1].width + this._gap;
			}
		} else {
			let offset = 0.0;
			if (index > 1) {
				offset = this._childs[index - 1 - 1].y + this._childs[index - 1 - 1].height + this._gap;
			}
			for (let i = index; i <= child_count; i += 1) {
				this._childs[i - 1].y = offset;
				this._childs[i - 1].x = 0;
				offset = offset + this._childs[i - 1].height + this._gap;
			}
		}
	},
	DeepLayout : function() {
		this._clip_up_index = 0;
		this._clip_down_index = 0;
		let child_count = this.child_count;
		if (child_count === 0) {
			return;
		}
		if (this._type === 1) {
			let offset = 0.0;
			for (let i = 1; i <= child_count; i += 1) {
				let child = this._childs[i - 1];
				if (child.DeepLayout !== undefined) {
					child.DeepLayout();
				}
				child.x = offset;
				child.y = 0;
				offset = offset + child.width + this._gap;
			}
		} else {
			let offset = 0.0;
			for (let i = 1; i <= child_count; i += 1) {
				let child = this._childs[i - 1];
				if (child.DeepLayout !== undefined) {
					child.DeepLayout();
				}
				child.y = offset;
				child.x = 0;
				offset = offset + child.height + this._gap;
			}
		}
	},
	HandleChildResize : function(event) {
		this.Layout(this.GetChildIndex(event.target));
		if (this._show_parent !== undefined) {
			if (this._type === 1) {
				this._show_parent.UpdateXLayout(this);
			} else {
				this._show_parent.UpdateYLayout(this);
			}
		}
		this.DispatchEvent(___all_struct.get(-431205740), {});
	},
	get max_right() {
		if (this._size_fixed) {
			return this.width;
		}
		return ALittle.DisplayGroup.__getter.max_right.call(this);
	},
	get max_bottom() {
		if (this._size_fixed) {
			return this.height;
		}
		return ALittle.DisplayGroup.__getter.max_bottom.call(this);
	},
	UpdateWidthLayout : function(child) {
		this.Layout(this.GetChildIndex(child));
	},
	UpdateHeightLayout : function(child) {
		this.Layout(this.GetChildIndex(child));
	},
	ClipRect : function(left, top, right, bottom, h_move, v_move) {
		left = left - this._x;
		if (left < 0) {
			left = 0;
		}
		top = top - (this._y);
		if (top < 0) {
			top = 0;
		}
		right = right - (this._x);
		if (right > this.width) {
			right = this.width;
		}
		bottom = bottom - (this._y);
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
		let max_index = child_count;
		let min_index = 1;
		let index = min_index;
		if (this._type === 1) {
			if (h_move === undefined || this._clip_up_index === 0) {
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
				index = this._clip_up_index;
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
			this._clip_up_index = index;
			for (let i = index; i <= child_count; i += 1) {
				if (childs[i - 1].x < right) {
					this._show.AddChild(childs[i - 1]._show);
					new_show_map.set(childs[i - 1], true);
					childs[i - 1].ClipRect(left, top, right, bottom, h_move, v_move);
					this._clip_down_index = i;
				} else {
					break;
				}
			}
		} else {
			if (v_move === undefined || this._clip_up_index === 0) {
				do {
					if (childs[index - 1].y > top) {
						max_index = index;
						index = __ceil((max_index + min_index) / 2);
					} else if (childs[index - 1].y + childs[index - 1].height < top) {
						min_index = index;
						index = __ceil((max_index + min_index) / 2);
					} else {
						break;
					}
				} while (index !== min_index && index !== max_index);
			} else {
				index = this._clip_up_index;
				if (v_move < 0) {
					while (index < max_index) {
						if (childs[index - 1].y + childs[index - 1].height >= top) {
							break;
						}
						++ index;
					}
				} else if (v_move > 0) {
					while (index > min_index) {
						if (childs[index - 1].y <= top) {
							break;
						}
						-- index;
					}
				}
			}
			this._clip_up_index = index;
			for (let i = index; i <= child_count; i += 1) {
				if (childs[i - 1].y < bottom) {
					this._show.AddChild(childs[i - 1]._show);
					new_show_map.set(childs[i - 1], true);
					childs[i - 1].ClipRect(left, top, right, bottom, h_move, v_move);
					this._clip_down_index = i;
				} else {
					break;
				}
			}
		}
		for (let [child, v] of new_show_map) {
			if (v === undefined) continue;
			if (this._show_child_map.get(child) === undefined) {
				child.DispatchEvent(___all_struct.get(1862557463), {});
			} else {
				this._show_child_map.delete(child);
			}
		}
		for (let [child, v] of this._show_child_map) {
			if (v === undefined) continue;
			child.DispatchEvent(___all_struct.get(348388800), {});
		}
		this._show_child_map = new_show_map;
	},
}, "ALittle.Linear");

}