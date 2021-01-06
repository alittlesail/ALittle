{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.Slider = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._pickup_rect = false;
		this._type = 2;
		this._offset_rate = 0;
		this._drag_point_rate = 0;
		this._fixed = 1;
		this._grade = 2;
		this._grade_list = [];
	},
	set width(value) {
		if (this._width === value) {
			return;
		}
		ALittle.DisplayLayout.__setter.width.call(this, value);
		this.AdjustBarButton();
	},
	set height(value) {
		if (this._height === value) {
			return;
		}
		ALittle.DisplayLayout.__setter.height.call(this, value);
		this.AdjustBarButton();
	},
	get width() {
		return this._width;
	},
	get height() {
		return this._height;
	},
	set type(value) {
		if (this._type === value) {
			return;
		}
		this._type = value;
		this.AdjustBarButton();
	},
	get type() {
		return this._type;
	},
	set offset_rate(value) {
		this._offset_rate = value;
		if (this._offset_rate < 0) {
			this._offset_rate = 0;
		} else if (this._offset_rate > 1) {
			this._offset_rate = 1;
		}
		this.AdjustBarButton();
	},
	get offset_rate() {
		return this._offset_rate;
	},
	set grade_value(value) {
		if (this._fixed === 1) {
			this.offset_rate = value;
			return;
		}
		this.offset_rate = (lua.math.floor(value) - 1) / (this.grade - 1);
	},
	get grade_value() {
		if (this._fixed === 1) {
			return this._offset_rate;
		}
		return lua.math.floor(this._offset_rate * (this._grade - 1)) + 1;
	},
	set bar_background(value) {
		if (this._bar_background !== undefined) {
			this._bar_background.RemoveEventListener(___all_struct.get(1883782801), this, this.HandleBarBackgroudLButtonDown);
			this.RemoveChild(this._bar_background);
		}
		this._bar_background = value;
		if (value !== undefined) {
			this.AddChild(value, 1);
			value.AddEventListener(___all_struct.get(1883782801), this, this.HandleBarBackgroudLButtonDown);
		}
		this.AdjustBarButton();
	},
	HandleBarBackgroudLButtonDown : function(event) {
		let rel_x = event.rel_x;
		let rel_y = event.rel_y;
		let real_width = this.width;
		let real_height = this.height;
		let bar_width = this._bar_button.width;
		let bar_height = this._bar_button.height;
		if (this._type === 2) {
			let offset = rel_y / real_height;
			if (offset > 1) {
				offset = 1;
			} else if (offset < 0) {
				offset = 0;
			}
			if (this._fixed === 1) {
				if (this._offset_rate === offset) {
					return;
				}
				this._offset_rate = offset;
				this._bar_button.y = this._offset_rate * real_height - bar_height / 2;
			} else {
				let offset_grade = (1 / (this._grade - 1)) / 2;
				let offset_up = offset + offset_grade;
				let offset_down = offset - offset_grade;
				let ___OBJECT_1 = this._grade_list;
				for (let k = 1; k <= ___OBJECT_1.length; ++k) {
					let v = ___OBJECT_1[k - 1];
					if (v === undefined) break;
					if (v > offset_down && v <= offset_up) {
						this._offset_rate = v;
						this._bar_button.y = this._offset_rate * real_height - bar_height / 2;
						break;
					}
				}
			}
		} else {
			let offset = rel_x / real_width;
			if (offset > 1) {
				offset = 1;
			} else if (offset < 0) {
				offset = 0;
			}
			if (this._fixed === 1) {
				if (this._offset_rate === offset) {
					return;
				}
				this._offset_rate = offset;
				this._bar_button.x = this._offset_rate * real_width - bar_width / 2;
			} else {
				let offset_grade = (1 / (this._grade - 1)) / 2;
				let offset_up = offset + offset_grade;
				let offset_down = offset - offset_grade;
				let ___OBJECT_2 = this._grade_list;
				for (let k = 1; k <= ___OBJECT_2.length; ++k) {
					let v = ___OBJECT_2[k - 1];
					if (v === undefined) break;
					if (v > offset_down && v <= offset_up) {
						this._offset_rate = v;
						this._bar_button.x = this._offset_rate * real_width - bar_width / 2;
						break;
					}
				}
			}
		}
		this.DispatchEvent(___all_struct.get(958494922), {});
	},
	get bar_background() {
		return this._bar_background;
	},
	set bar_button(value) {
		if (this._bar_button !== undefined) {
			this._bar_button.RemoveEventListener(___all_struct.get(1337289812), this, this.HandleBarButtonDrag);
			this._bar_button.RemoveEventListener(___all_struct.get(1301789264), this, this.HandleBarButtonDragBegin);
			this._bar_button.RemoveEventListener(___all_struct.get(-1737121315), this, this.HandleBarButtonScroll);
			this.RemoveChild(this._bar_button);
		}
		this._bar_button = value;
		if (value !== undefined) {
			this.AddChild(value);
			value.AddEventListener(___all_struct.get(1337289812), this, this.HandleBarButtonDrag);
			value.AddEventListener(___all_struct.get(1301789264), this, this.HandleBarButtonDragBegin);
			value.AddEventListener(___all_struct.get(-1737121315), this, this.HandleBarButtonScroll);
			value._can_scroll = true;
		}
		this.AdjustBarButton();
	},
	get bar_button() {
		return this._bar_button;
	},
	set fixed(value) {
		if (this._fixed === value) {
			return;
		}
		this._fixed = value;
		if (this._fixed === 2 && this._grade !== undefined) {
			this._grade_list = [];
			this._grade_list[1 - 1] = 0;
			let dist = 1 / (this._grade - 1);
			for (let i = 1; i <= this._grade - 2; i += 1) {
				this._grade_list[i + 1 - 1] = i * dist;
			}
			let num = ALittle.List_Len(this._grade_list);
			this._grade_list[num + 1 - 1] = 1;
		}
		this.AdjustBarButton();
	},
	get fixed() {
		return this._fixed;
	},
	set grade(value) {
		if (this._grade === value || value < 2) {
			return;
		}
		this._grade = value;
		if (this._fixed === 2 && value !== undefined) {
			this._grade_list = [];
			this._grade_list[1 - 1] = 0;
			let dist = 1 / (value - 1);
			for (let i = 1; i <= value - 2; i += 1) {
				this._grade_list[i + 1 - 1] = i * dist;
			}
			let num = ALittle.List_Len(this._grade_list);
			this._grade_list[num + 1 - 1] = 1;
		}
		this.AdjustBarButton();
	},
	get grade() {
		return this._grade;
	},
	HandleBarButtonDragBegin : function(event) {
		let rel_x = undefined;
		let rel_y = undefined;
		[rel_x, rel_y] = this._bar_button.GlobalToLocalMatrix2D(event.abs_x, event.abs_y);
		if (this._type === 2) {
			let height = this._bar_button.height;
			this._drag_point_rate = 0;
			if (height > 0) {
				this._drag_point_rate = rel_y / height;
			}
		} else {
			let width = this._bar_button.width;
			this._drag_point_rate = 0;
			if (width > 0) {
				this._drag_point_rate = rel_x / width;
			}
		}
	},
	HandleBarButtonDrag : function(event) {
		let rel_x = undefined;
		let rel_y = undefined;
		[rel_x, rel_y] = this._bar_button.GlobalToLocalMatrix2D(event.abs_x, event.abs_y);
		let abs_x = undefined;
		let abs_y = undefined;
		[abs_x, abs_y] = this._bar_background.GlobalToLocalMatrix2D(event.abs_x, event.abs_y);
		let real_width = this.width;
		let real_height = this.height;
		let bar_width = this._bar_button.width;
		let bar_height = this._bar_button.height;
		if (this._type === 2) {
			if (this._fixed === 1) {
				if ((event.delta_y > 0 && rel_y < bar_height * this._drag_point_rate) || (event.delta_y < 0 && rel_y > bar_height * this._drag_point_rate)) {
					return;
				}
				let offset = (this._bar_button.y + bar_height / 2 + event.delta_y) / real_height;
				if (offset > 1) {
					offset = 1;
				} else if (offset < 0) {
					offset = 0;
				}
				if (this._offset_rate === offset) {
					return;
				}
				this._offset_rate = offset;
				this._bar_button.y = this._offset_rate * real_height - bar_height / 2;
			} else {
				let offset = abs_y / real_height;
				if (offset > 1) {
					offset = 1;
				} else if (offset < 0) {
					offset = 0;
				}
				let offset_grade = (1 / (this._grade - 1)) / 2;
				let offset_up = offset + offset_grade;
				let offset_down = offset - offset_grade;
				let ___OBJECT_3 = this._grade_list;
				for (let k = 1; k <= ___OBJECT_3.length; ++k) {
					let v = ___OBJECT_3[k - 1];
					if (v === undefined) break;
					if (v > offset_down && v <= offset_up) {
						this._offset_rate = v;
						this._bar_button.y = this._offset_rate * real_height - bar_height / 2;
						break;
					}
				}
			}
		} else {
			if (this._fixed === 1) {
				if ((event.delta_x > 0 && rel_x < bar_height * this._drag_point_rate) || (event.delta_x < 0 && rel_x > bar_height * this._drag_point_rate)) {
					return;
				}
				let offset = (this._bar_button.x + bar_width / 2 + event.delta_x) / real_width;
				if (offset > 1) {
					offset = 1;
				} else if (offset < 0) {
					offset = 0;
				}
				if (this._offset_rate === offset) {
					return;
				}
				this._offset_rate = offset;
				this._bar_button.x = this._offset_rate * real_width - bar_width / 2;
			} else {
				let offset = abs_x / real_width;
				if (offset > 1) {
					offset = 1;
				} else if (offset < 0) {
					offset = 0;
				}
				let offset_grade = (1 / (this._grade - 1)) / 2;
				let offset_up = offset + offset_grade;
				let offset_down = offset - offset_grade;
				let ___OBJECT_4 = this._grade_list;
				for (let k = 1; k <= ___OBJECT_4.length; ++k) {
					let v = ___OBJECT_4[k - 1];
					if (v === undefined) break;
					if (v > offset_down && v <= offset_up) {
						this._offset_rate = v;
						this._bar_button.x = this._offset_rate * real_width - bar_width / 2;
						break;
					}
				}
			}
		}
		this.DispatchEvent(___all_struct.get(958494922), {});
	},
	HandleBarButtonScroll : function(event) {
		let step = undefined;
		if (this._fixed === 1) {
			step = 0.01;
		} else {
			step = 1 / (this._grade - 1);
		}
		if (this._type === 2) {
			if (event.delta_y > 0) {
				this.HandleUpDownButton(-1 * step);
			} else if (event.delta_y < 0) {
				this.HandleUpDownButton(step);
			}
		} else {
			if (event.delta_x > 0) {
				this.HandleUpDownButton(-1 * step);
			} else if (event.delta_x < 0) {
				this.HandleUpDownButton(step);
			}
		}
	},
	HandleUpDownButton : function(step) {
		this._offset_rate = this._offset_rate + step;
		if (this._offset_rate < 0) {
			this._offset_rate = 0;
		}
		if (this._offset_rate > 1) {
			this._offset_rate = 1;
		}
		if (this._type === 2) {
			this._bar_button.y = this._offset_rate * this.height - this._bar_button.height / 2;
		} else {
			this._bar_button.x = this._offset_rate * this.width - this._bar_button.width / 2;
		}
		this.DispatchEvent(___all_struct.get(958494922), {});
	},
	AdjustBarButton : function() {
		if (this._bar_background !== undefined) {
			this._bar_background.x = 0;
			this._bar_background.y = 0;
			this._bar_background.width = this.width;
			this._bar_background.height = this.height;
		}
		if (this._bar_button !== undefined) {
			if (this._type === 2) {
				this._bar_button.x_type = 3;
				this._bar_button.x_value = 0;
				this._bar_button.y_type = 1;
				this._bar_button.y_value = this._offset_rate * this.height - this._bar_button.height / 2;
			} else {
				this._bar_button.x_type = 1;
				this._bar_button.x_value = this._offset_rate * this.width - this._bar_button.width / 2;
				this._bar_button.y_type = 3;
				this._bar_button.y_value = 0;
			}
		}
	},
}, "ALittle.Slider");

}