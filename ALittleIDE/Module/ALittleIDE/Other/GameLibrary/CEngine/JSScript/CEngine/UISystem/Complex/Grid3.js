{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittle.Grid3 = JavaScript.Class(ALittle.DisplayGroup, {
	Ctor : function(ctrl_sys) {
		this._type = 2;
		this._child_map = [];
		this._logic_up = 0;
		this._logic_down = 0;
		this._logic_gap = 0;
		this._real_up = 0;
		this._real_down = 0;
		this._real_gap = 0;
		this._pickup_rect = true;
		this._pickup_child = true;
	},
	set type(value) {
		if (this._type === value) {
			return;
		}
		this._type = value;
		this.CalcRealWidthCutting();
		this.CalcRealHeightCutting();
	},
	get type() {
		return this._type;
	},
	set show_up(child) {
		this.SetShow(1, child);
	},
	get show_up() {
		return this._child_map[1 - 1];
	},
	set show_center(child) {
		this.SetShow(2, child);
	},
	get show_center() {
		return this._child_map[2 - 1];
	},
	set show_down(child) {
		this.SetShow(3, child);
	},
	get show_down() {
		return this._child_map[3 - 1];
	},
	SetShow : function(index, child) {
		if (this._child_map[index - 1] !== undefined) {
			ALittle.DisplayGroup.RemoveChild.call(this, this._child_map[index - 1]);
		}
		this._child_map[index - 1] = undefined;
		if (child === undefined) {
			return;
		}
		this._child_map[index - 1] = child;
		ALittle.DisplayGroup.AddChild.call(this, child);
		if (this._type === 2) {
			child.x = 0;
			child.width = this._width;
			let y = 0.0;
			let height = 0.0;
			if (index === 1) {
				y = 0;
				height = this._real_up;
			} else if (index === 2) {
				y = this._real_up + this._real_gap;
				height = this._height - this._real_gap * 2 - this._real_up - this._real_down;
			} else if (index === 3) {
				y = this._height - this._real_down;
				height = this._real_down;
			}
			child.y = y;
			child.height = height;
		} else {
			child.y = 0;
			child.height = this._height;
			let x = 0.0;
			let width = 0.0;
			if (index === 1) {
				x = 0;
				width = this._real_up;
			} else if (index === 2) {
				x = this._real_up + this._real_gap;
				width = this._width - this._real_gap * 2 - this._real_up - this._real_down;
			} else if (index === 3) {
				x = this._width - this._real_down;
				width = this._real_down;
			}
			child.x = x;
			child.width = width;
		}
	},
	get center_size() {
		let size = 0.0;
		if (this._type === 2) {
			size = this._height - this._real_gap * 2 - this._real_up - this._real_down;
		} else {
			size = this._width - this._real_gap * 2 - this._real_up - this._real_down;
		}
		return size;
	},
	get real_gap() {
		return this._real_gap;
	},
	get gap() {
		return this._logic_gap;
	},
	get real_up_size() {
		return this._real_up;
	},
	get up_size() {
		return this._logic_up;
	},
	get real_down_size() {
		return this._real_down;
	},
	get down_size() {
		return this._logic_down;
	},
	set up_size(value) {
		this._logic_up = value;
		this.CalcRealWidthCutting();
		this.CalcRealHeightCutting();
	},
	set down_size(value) {
		this._logic_down = value;
		this.CalcRealWidthCutting();
		this.CalcRealHeightCutting();
	},
	set gap(value) {
		this._logic_gap = value;
		this.CalcRealWidthCutting();
		this.CalcRealHeightCutting();
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
	CalcRealWidthCutting : function() {
		if (this._type === 2) {
			for (let index = 1; index <= 3; index += 1) {
				if (this._child_map[index - 1] !== undefined) {
					this._child_map[index - 1].x = 0;
					this._child_map[index - 1].width = this._width;
				}
			}
			return;
		}
		if (this._width === 0) {
			this._real_up = 0;
			this._real_down = 0;
			this._real_gap = 0;
		} else if (this._width >= this._logic_up + this._logic_down + this._logic_gap * 2) {
			this._real_up = this._logic_up;
			this._real_down = this._logic_down;
			this._real_gap = this._logic_gap;
		} else if (this._width >= this._logic_up + this._logic_down) {
			let last_gap = this._width - this._logic_up - this._logic_down;
			this._real_up = this._logic_up;
			this._real_down = this._logic_down;
			this._real_gap = last_gap / 2;
		} else {
			let logic_up_add_down = this._logic_up + this._logic_down;
			if (logic_up_add_down === 0) {
				this._real_up = 0;
				this._real_down = 0;
				this._real_gap = 0;
			} else {
				let rate_up = this._logic_up / logic_up_add_down;
				let rate_down = this._logic_down / logic_up_add_down;
				this._real_up = this._width * rate_up;
				this._real_down = this._width * rate_down;
				this._real_gap = 0;
			}
		}
		let offset_list = [];
		offset_list[1 - 1] = 0;
		offset_list[2 - 1] = this._real_up + this._real_gap;
		offset_list[3 - 1] = this._width - this._real_down;
		let width_list = [];
		width_list[1 - 1] = this._real_up;
		width_list[2 - 1] = this._width - this._real_gap * 2 - this._real_up - this._real_down;
		width_list[3 - 1] = this._real_down;
		for (let index = 1; index <= 3; index += 1) {
			if (this._child_map[index - 1] !== undefined) {
				this._child_map[index - 1].x = offset_list[index - 1];
				this._child_map[index - 1].width = width_list[index - 1];
			}
		}
	},
	CalcRealHeightCutting : function() {
		if (this._type === 1) {
			for (let index = 1; index <= 3; index += 1) {
				if (this._child_map[index - 1] !== undefined) {
					this._child_map[index - 1].y = 0;
					this._child_map[index - 1].height = this._height;
				}
			}
			return;
		}
		if (this._height === 0) {
			this._real_up = 0;
			this._real_down = 0;
			this._real_gap = 0;
		} else if (this._height >= this._logic_up + this._logic_down + this._logic_gap * 2) {
			this._real_up = this._logic_up;
			this._real_down = this._logic_down;
			this._real_gap = this._logic_gap;
		} else if (this._height >= this._logic_up + this._logic_down) {
			let last_gap = this._height - this._logic_up - this._logic_down;
			this._real_up = this._logic_up;
			this._real_down = this._logic_down;
			this._real_gap = last_gap / 2;
		} else {
			let logic_up_add_down = this._logic_up + this._logic_down;
			if (logic_up_add_down === 0) {
				this._real_up = 0;
				this._real_down = 0;
				this._real_gap = 0;
			} else {
				let rate_up = this._logic_up / logic_up_add_down;
				let rate_down = this._logic_down / logic_up_add_down;
				this._real_up = this._height * rate_up;
				this._real_down = this._height * rate_down;
				this._real_gap = 0;
			}
		}
		let offset_list = [];
		offset_list[1 - 1] = 0;
		offset_list[2 - 1] = this._real_up + this._real_gap;
		offset_list[3 - 1] = this._height - this._real_down;
		let height_list = [];
		height_list[1 - 1] = this._real_up;
		height_list[2 - 1] = this._height - this._real_gap * 2 - this._real_up - this._real_down;
		height_list[3 - 1] = this._real_down;
		for (let index = 1; index <= 3; index += 1) {
			if (this._child_map[index - 1] !== undefined) {
				this._child_map[index - 1].y = offset_list[index - 1];
				this._child_map[index - 1].height = height_list[index - 1];
			}
		}
	},
}, "ALittle.Grid3");

}