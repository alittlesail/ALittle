{
if (typeof ALittle === "undefined") window.ALittle = {};


let __ceil = ALittle.Math_Ceil;
if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittle.Grid9 = JavaScript.Class(ALittle.DisplayGroup, {
	Ctor : function(ctrl_sys) {
		this._child_map = new Map();
		this._child_map.set(1, new Map());
		this._child_map.set(2, new Map());
		this._child_map.set(3, new Map());
		this._logic_left = 0;
		this._logic_top = 0;
		this._logic_right = 0;
		this._logic_bottom = 0;
		this._real_left = 0;
		this._real_top = 0;
		this._real_right = 0;
		this._real_bottom = 0;
		this._pickup_rect = true;
		this._pickup_child = true;
	},
	set show_left_top(child) {
		this.SetShow(1, 1, child);
	},
	get show_left_top() {
		return this._child_map.get(1).get(1);
	},
	set show_left_center(child) {
		this.SetShow(1, 2, child);
	},
	get show_left_center() {
		return this._child_map.get(1).get(2);
	},
	set show_left_bottom(child) {
		this.SetShow(1, 3, child);
	},
	get show_left_bottom() {
		return this._child_map.get(1).get(3);
	},
	set show_center_top(child) {
		this.SetShow(2, 1, child);
	},
	get show_center_top() {
		return this._child_map.get(2).get(1);
	},
	set show_center_center(child) {
		this.SetShow(2, 2, child);
	},
	get show_center_center() {
		return this._child_map.get(2).get(2);
	},
	set show_center_bottom(child) {
		this.SetShow(2, 3, child);
	},
	get show_center_bottom() {
		return this._child_map.get(2).get(3);
	},
	set show_right_top(child) {
		this.SetShow(3, 1, child);
	},
	get show_right_top() {
		return this._child_map.get(3).get(1);
	},
	set show_right_center(child) {
		this.SetShow(3, 2, child);
	},
	get show_right_center() {
		return this._child_map.get(3).get(2);
	},
	set show_right_bottom(child) {
		this.SetShow(3, 3, child);
	},
	get show_right_bottom() {
		return this._child_map.get(3).get(3);
	},
	SetShow : function(col, row, child) {
		if (this._child_map.get(col).get(row) !== undefined) {
			this.RemoveChild(this._child_map.get(col).get(row));
		}
		this._child_map.get(col).set(row, child);
		if (child === undefined) {
			return;
		}
		this.AddChild(child);
		let x = 0.0;
		let y = 0.0;
		let width = 0.0;
		let height = 0.0;
		if (col === 1) {
			x = 0;
			width = this._real_left;
		} else if (col === 2) {
			x = this._real_left;
			width = this._width - this._real_left - this._real_right;
		} else if (col === 3) {
			x = this._width - this._real_right;
			width = this._real_right;
		}
		if (row === 1) {
			y = 0;
			height = this._real_top;
		} else if (row === 2) {
			y = this._real_top;
			height = this._height - this._real_top - this._real_bottom;
		} else if (row === 3) {
			y = this._height - this._real_bottom;
			height = this._real_bottom;
		}
		child.x = x;
		child.y = y;
		child.width = width;
		child.height = height;
	},
	set width(value) {
		if (value === this._width) {
			return;
		}
		this._width = value;
		if (this._width_type === 1) {
			this._width_value = this._width;
		}
		this.CalcRealWidthCutting();
	},
	set height(value) {
		if (value === this._height) {
			return;
		}
		this._height = value;
		if (this._height_type === 1) {
			this._height_value = this._height;
		}
		this.CalcRealHeightCutting();
	},
	set left_size(value) {
		this._logic_left = value;
		this.CalcRealWidthCutting();
	},
	get left_size() {
		return this._logic_left;
	},
	set right_size(value) {
		this._logic_right = value;
		this.CalcRealWidthCutting();
	},
	get right_size() {
		return this._logic_right;
	},
	set top_size(value) {
		this._logic_top = value;
		this.CalcRealHeightCutting();
	},
	get top_size() {
		return this._logic_top;
	},
	set bottom_size(value) {
		this._logic_bottom = value;
		this.CalcRealHeightCutting();
	},
	get bottom_size() {
		return this._logic_bottom;
	},
	CalcRealWidthCutting : function() {
		let real_center = 0.0;
		let logic_left = __ceil(this._logic_left);
		let logic_right = __ceil(this._logic_right);
		if (this._width === 0) {
			this._real_left = 0;
			this._real_right = 0;
			real_center = 0;
		} else if (this._width >= logic_left + logic_right) {
			this._real_left = logic_left;
			this._real_right = logic_right;
			real_center = __ceil(this._width - this._real_left - this._real_right);
		} else {
			let logic_left_add_right = this._logic_left + this._logic_right;
			real_center = 0;
			if (logic_left_add_right === 0) {
				this._real_left = 0;
				this._real_right = 0;
			} else {
				let rate_left = this._logic_left / logic_left_add_right;
				let rate_right = this._logic_right / logic_left_add_right;
				this._real_left = this._width * rate_left;
				this._real_right = this._width * rate_right;
			}
		}
		let offset_list = [];
		offset_list[1 - 1] = 0;
		offset_list[2 - 1] = this._real_left;
		offset_list[3 - 1] = this._real_left + real_center;
		let width_list = [];
		width_list[1 - 1] = this._real_left;
		width_list[2 - 1] = real_center;
		width_list[3 - 1] = this._real_right;
		for (let col = 1; col <= 3; col += 1) {
			let row_childs = this._child_map.get(col);
			for (let row = 1; row <= 3; row += 1) {
				if (row_childs.get(row) !== undefined) {
					row_childs.get(row).x = offset_list[col - 1];
					row_childs.get(row).width = width_list[col - 1];
				}
			}
		}
	},
	CalcRealHeightCutting : function() {
		let real_center = 0.0;
		let logic_top = __ceil(this._logic_top);
		let logic_bottom = __ceil(this._logic_bottom);
		if (this._height === 0) {
			this._real_top = 0;
			this._real_bottom = 0;
			real_center = 0;
		} else if (this._height >= logic_top + logic_bottom) {
			this._real_top = logic_top;
			this._real_bottom = logic_bottom;
			real_center = __ceil(this._height - this._real_top - this._real_bottom);
		} else {
			let logic_top_add_bottom = this._logic_top + this._logic_bottom;
			real_center = 0;
			if (logic_top_add_bottom === 0) {
				this._real_top = 0;
				this._real_bottom = 0;
			} else {
				let rate_top = this._logic_top / logic_top_add_bottom;
				let rate_bottom = this._logic_bottom / logic_top_add_bottom;
				this._real_top = this._height * rate_top;
				this._real_bottom = this._height * rate_bottom;
			}
		}
		let offset_list = [];
		offset_list[1 - 1] = 0;
		offset_list[2 - 1] = this._real_top;
		offset_list[3 - 1] = this._real_top + real_center;
		let height_list = [];
		height_list[1 - 1] = this._real_top;
		height_list[2 - 1] = real_center;
		height_list[3 - 1] = this._real_bottom;
		for (let col = 1; col <= 3; col += 1) {
			let row_childs = this._child_map.get(col);
			for (let row = 1; row <= 3; row += 1) {
				if (row_childs.get(row) !== undefined) {
					row_childs.get(row).y = offset_list[row - 1];
					row_childs.get(row).height = height_list[row - 1];
				}
			}
		}
	},
}, "ALittle.Grid9");

}