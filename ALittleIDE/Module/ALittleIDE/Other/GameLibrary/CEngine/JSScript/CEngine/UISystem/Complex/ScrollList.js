{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __floor = ALittle.Math_Floor;
let __remove = ALittle.List_Remove;
let __sin = ALittle.Math_Sin;
if (ALittle.DisplayView === undefined) throw new Error(" extends class:ALittle.DisplayView is undefined");
ALittle.ScrollList = JavaScript.Class(ALittle.DisplayView, {
	Ctor : function(ctrl_sys) {
		this._width = 0;
		this._height = 0;
		this._drag_delta_x = 0;
		this._drag_delta_y = 0;
		this._drag_delta_table = [];
		this._drag_delta_table_count = 0;
		this._drag_rate = 0.2;
		this._open_extends_drag = false;
		this._clip_atonce = false;
		this._drag_time = 0;
		this._max_speed = 40;
		this._type = 2;
		this._scroll_linear = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
		this._scroll_linear.width_type = 4;
		this._scroll_linear.type = 2;
		ALittle.DisplayView.AddChild.call(this, this._scroll_linear);
		this._scroll_linear.AddEventListener(___all_struct.get(-431205740), this, this.HandleLinearResize);
		this._pickup_rect = true;
		this._pickup_child = true;
		this._pickup_this = true;
		this._can_scroll = true;
		this.AddEventListener(___all_struct.get(-1737121315), this, this.HandleMButtonWheel);
		this.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this.AddEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
		this.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		this.RefreshClipDisLine();
	},
	GetChildIndex : function(child) {
		return this._scroll_linear.GetChildIndex(child);
	},
	SetChildIndex : function(child, index) {
		this._scroll_linear.SetChildIndex(child, index);
		this.RefreshClipDisLine();
		return true;
	},
	GetChildByIndex : function(index) {
		return this._scroll_linear.GetChildByIndex(index);
	},
	get childs() {
		return this._scroll_linear.childs;
	},
	get child_count() {
		return this._scroll_linear.child_count;
	},
	set type(value) {
		if (this._type === value) {
			return;
		}
		this._type = value;
		if (this._type === 1) {
			this._scroll_linear.width_type = 1;
			this._scroll_linear.height_type = 4;
			this._scroll_linear.type = 1;
		} else {
			this._scroll_linear.width_type = 4;
			this._scroll_linear.height_type = 1;
			this._scroll_linear.type = 2;
		}
		this.RefreshChild(false);
	},
	get type() {
		return this._type;
	},
	AddChild : function(child, index) {
		if (child === undefined) {
			return false;
		}
		if (this._scroll_linear.AddChild(child, index) === false) {
			return false;
		}
		this.RefreshChild(false);
		return true;
	},
	RemoveChild : function(child) {
		if (child === undefined) {
			return false;
		}
		if (this._scroll_linear.RemoveChild(child) === false) {
			return false;
		}
		this.RefreshChild(false);
		return true;
	},
	SpliceChild : function(index, count) {
		let result = this._scroll_linear.SpliceChild(index, count);
		if (result !== 0) {
			this.RefreshChild(false);
		}
		return result;
	},
	AddChildEffect : function(child, up) {
		if (child === undefined) {
			return false;
		}
		if (up) {
			if (this._type === 1) {
				let target_value = this._scroll_linear.x + this._scroll_linear.width;
				if (this._scroll_linear.AddChild(child, 1) === false) {
					return false;
				}
				this._scroll_linear.x = target_value - this._scroll_linear.width;
			} else {
				let target_value = this._scroll_linear.y + this._scroll_linear.height;
				if (this._scroll_linear.AddChild(child, 1) === false) {
					return false;
				}
				this._scroll_linear.y = target_value - this._scroll_linear.height;
			}
		} else {
			if (this._scroll_linear.AddChild(child) === false) {
				return false;
			}
		}
		this.RefreshChild(false);
		return true;
	},
	RemoveChildEffect : function(up, loop) {
		if (up) {
			if (this._type === 1) {
				let child = this._scroll_linear.GetChildByIndex(1);
				let target_value = this._scroll_linear.x + this._scroll_linear.width;
				if (this._scroll_linear.RemoveChild(child) === false) {
					return false;
				}
				this._scroll_linear.x = target_value - this._scroll_linear.width;
			} else {
				let child = this._scroll_linear.GetChildByIndex(1);
				let target_value = this._scroll_linear.y + this._scroll_linear.height;
				if (this._scroll_linear.RemoveChild(child) === false) {
					return false;
				}
				this._scroll_linear.y = target_value - this._scroll_linear.height;
			}
		} else {
			let child = this._scroll_linear.GetChildByIndex(this._scroll_linear.child_count);
			if (this._scroll_linear.RemoveChild(child) === false) {
				return false;
			}
		}
		if (loop) {
			this.RefreshChild(true);
		} else {
			this.RefreshChild(false);
		}
		return true;
	},
	HasChild : function(child) {
		return this._scroll_linear.HasChild(child);
	},
	RemoveAllChild : function() {
		if (this._type === 1) {
			A_LoopSystem.RemoveUpdater(this._drag_loop_x);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
			this._scroll_linear.x = 0;
		} else {
			A_LoopSystem.RemoveUpdater(this._drag_loop_y);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
			this._scroll_linear.y = 0;
		}
		this._scroll_linear.RemoveAllChild();
		this.UpdateLoadingShow();
		this.AdjustScrollBar();
	},
	RefreshChild : function(loop) {
		if (this._type === 1) {
			let linear_width = this._scroll_linear.width;
			let target_x = undefined;
			if (linear_width >= this._width) {
				if (this._scroll_linear.x > 0) {
					target_x = 0;
				} else if (this._scroll_linear.x < -linear_width + this._width) {
					target_x = -linear_width + this._width;
				}
			} else {
				target_x = 0;
			}
			if (target_x === undefined || target_x === this._scroll_linear.x) {
				A_LoopSystem.RemoveUpdater(this._drag_loop_x);
				this.RefreshClipDisLine();
				this.AdjustScrollBar();
				return;
			}
			if (this._drag_loop_x !== undefined && this._drag_loop_x.IsCompleted() === false) {
				let speed = this._drag_loop_x.speed;
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				A_LoopSystem.RemoveUpdater(this._drag_loop_x);
				let time = (target_x - this._scroll_linear.x) / speed;
				this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", target_x, __floor(time), 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_x);
			} else {
				if (loop) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_x);
					this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", target_x, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_x);
				} else {
					this._scroll_linear.x = target_x;
				}
			}
		} else {
			let linear_height = this._scroll_linear.height;
			let target_y = undefined;
			if (linear_height >= this._height) {
				if (this._scroll_linear.y > 0) {
					target_y = 0;
				} else if (this._scroll_linear.y < -linear_height + this._height) {
					target_y = -linear_height + this._height;
				}
			} else {
				target_y = 0;
			}
			if (target_y === undefined || target_y === this._scroll_linear.y) {
				A_LoopSystem.RemoveUpdater(this._drag_loop_y);
				this.RefreshClipDisLine();
				this.AdjustScrollBar();
				return;
			}
			if (this._drag_loop_y !== undefined && this._drag_loop_y.IsCompleted() === false) {
				let speed = this._drag_loop_y.speed;
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				A_LoopSystem.RemoveUpdater(this._drag_loop_y);
				let time = (target_y - this._scroll_linear.y) / speed;
				this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", target_y, __floor(time), 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_y);
			} else {
				if (loop) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_y);
					this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", target_y, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_y);
				} else {
					this._scroll_linear.y = target_y;
				}
			}
		}
		this.RefreshClipDisLine();
		this.AdjustScrollBar();
	},
	set clip_atonce(value) {
		this._clip_atonce = value;
	},
	get clip_atonce() {
		return this._clip_atonce;
	},
	set scroll_offset(value) {
		if (this._type === 1) {
			A_LoopSystem.RemoveUpdater(this._drag_loop_x);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
			if (value > 0) {
				value = 0;
			}
			let total_width = this.width;
			let linear_width = this._scroll_linear.width;
			if (total_width < linear_width) {
				let delta = total_width - linear_width;
				if (value < delta) {
					value = delta;
				}
			}
			this._scroll_linear.x = value;
			this.AdjustScrollBar();
		} else {
			A_LoopSystem.RemoveUpdater(this._drag_loop_y);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
			if (value > 0) {
				value = 0;
			}
			let total_height = this.height;
			let linear_height = this._scroll_linear.height;
			if (total_height < linear_height) {
				let delta = total_height - linear_height;
				if (value < delta) {
					value = delta;
				}
			}
			this._scroll_linear.y = value;
			this.AdjustScrollBar();
		}
	},
	get scroll_offset() {
		if (this._type === 1) {
			return this._scroll_linear.x;
		}
		return this._scroll_linear.y;
	},
	ScrollToBottom : function() {
		if (this.height >= this.real_height) {
			return;
		}
		this.scroll_offset = this.height - this.real_height;
	},
	set gap(value) {
		if (value === undefined) {
			value = 0;
		}
		this._scroll_linear.gap = value;
		this.RefreshClipDisLine();
		this.AdjustScrollBar();
	},
	get gap() {
		return this._scroll_linear.gap;
	},
	get real_height() {
		return this._scroll_linear.height;
	},
	get real_width() {
		return this._scroll_linear.width;
	},
	set width(value) {
		if (this._type === 2) {
			ALittle.DisplayView.__setter.width.call(this, value);
			return;
		}
		if (this._width === value) {
			return;
		}
		this._width = value;
		if (this._width_type === 1) {
			this._width_value = this._width;
		}
		this._show.SetWidth(this._width);
		if (this._scroll_bar !== undefined) {
			let linear_width = this._scroll_linear.width;
			let rate = this._scroll_bar.offset_rate;
			if (linear_width < this._width) {
				rate = 0;
			}
			this._scroll_bar.width = this._width;
			this._scroll_bar.total_size = linear_width;
			this._scroll_bar.show_size = this._width;
			this._scroll_bar.offset_rate = rate;
			this._scroll_bar.offset_step = 0.1;
			let x = 0.0;
			if (linear_width > this._width) {
				let total_width = linear_width - this._width;
				x = -total_width * rate;
			}
			this._scroll_linear.x = x;
		}
		this.RefreshClipDisLine();
	},
	set height(value) {
		if (this._type === 1) {
			ALittle.DisplayView.__setter.height.call(this, value);
			return;
		}
		if (this._height === value) {
			return;
		}
		this._height = value;
		if (this._height_type === 1) {
			this._height_value = this._height;
		}
		this._show.SetHeight(this._height);
		if (this._scroll_bar !== undefined) {
			let linear_height = this._scroll_linear.height;
			let rate = this._scroll_bar.offset_rate;
			if (linear_height < this._height) {
				rate = 0;
			}
			this._scroll_bar.height = this._height;
			this._scroll_bar.total_size = linear_height;
			this._scroll_bar.show_size = this._height;
			this._scroll_bar.offset_rate = rate;
			this._scroll_bar.offset_step = 0.1;
			let y = 0.0;
			if (linear_height > this._height) {
				let total_height = linear_height - this._height;
				y = -total_height * rate;
			}
			this._scroll_linear.y = y;
		}
		this.RefreshClipDisLine();
	},
	set right_scrollbar(value) {
		if (this._scroll_bar !== undefined) {
			A_LoopSystem.RemoveUpdater(this._scroll_bar_loop);
			ALittle.DisplayView.RemoveChild.call(this, this._scroll_bar);
			this._scroll_bar.RemoveEventListener(___all_struct.get(958494922), this, this.HandleRightScrollBarChange);
			this._scroll_bar.RemoveEventListener(___all_struct.get(1309977874), this, this.HandleRightScrollBarChangeEnd);
		}
		this._scroll_bar = value;
		if (this._scroll_bar !== undefined) {
			if (this._type === 1) {
				this._scroll_bar.alpha = 0;
				this._scroll_bar.visible = false;
				this._scroll_bar.type = 1;
				this._scroll_bar.y_type = 4;
				ALittle.DisplayView.AddChild.call(this, this._scroll_bar);
				this._scroll_bar.AddEventListener(___all_struct.get(958494922), this, this.HandleRightScrollBarChange);
				this._scroll_bar.AddEventListener(___all_struct.get(1309977874), this, this.HandleRightScrollBarChangeEnd);
				this._scroll_bar.width = this._width;
				this._scroll_bar.x = 0;
				this._scroll_bar.total_size = this._scroll_linear.width;
				this._scroll_bar.show_size = this._width;
				this._scroll_bar.offset_rate = 0;
				this._scroll_bar.offset_step = 0.1;
			} else {
				this._scroll_bar.alpha = 0;
				this._scroll_bar.visible = false;
				this._scroll_bar.type = 2;
				this._scroll_bar.x_type = 4;
				ALittle.DisplayView.AddChild.call(this, this._scroll_bar);
				this._scroll_bar.AddEventListener(___all_struct.get(958494922), this, this.HandleRightScrollBarChange);
				this._scroll_bar.AddEventListener(___all_struct.get(1309977874), this, this.HandleRightScrollBarChangeEnd);
				this._scroll_bar.height = this._height;
				this._scroll_bar.y = 0;
				this._scroll_bar.total_size = this._scroll_linear.height;
				this._scroll_bar.show_size = this._height;
				this._scroll_bar.offset_rate = 0;
				this._scroll_bar.offset_step = 0.1;
			}
		}
	},
	get right_scrollbar() {
		return this._scroll_bar;
	},
	AdjustScrollBar : function() {
		if (this._type === 1) {
			let linear_width = this._scroll_linear.width;
			if (this._scroll_bar !== undefined) {
				let rate = 0.0;
				if (linear_width <= this._width) {
					rate = 0;
				} else {
					rate = -this._scroll_linear.x / (linear_width - this._width);
				}
				this._scroll_bar.width = this._width;
				this._scroll_bar.total_size = linear_width;
				this._scroll_bar.show_size = this._width;
				this._scroll_bar.offset_rate = rate;
				this._scroll_bar.offset_step = 0.1;
			}
		} else {
			let linear_height = this._scroll_linear.height;
			if (this._scroll_bar !== undefined) {
				let rate = 0.0;
				if (linear_height <= this._height) {
					rate = 0;
				} else {
					rate = -this._scroll_linear.y / (linear_height - this._height);
				}
				this._scroll_bar.height = this._height;
				this._scroll_bar.total_size = linear_height;
				this._scroll_bar.show_size = this._height;
				this._scroll_bar.offset_rate = rate;
				this._scroll_bar.offset_step = 0.1;
			}
		}
	},
	get loading_show_up() {
		return this._loading_show_up;
	},
	set loading_show_up(value) {
		if (this._loading_show_up !== value) {
			ALittle.DisplayView.RemoveChild.call(this, this._loading_show_up);
			this._loading_show_up = undefined;
		}
		if (value !== undefined) {
			this._loading_show_up = value;
			ALittle.DisplayView.AddChild.call(this, this._loading_show_up);
			if (this._type === 1) {
				this._loading_show_up.x = this._scroll_linear.x - this._loading_show_up.width;
			} else {
				this._loading_show_up.y = this._scroll_linear.y - this._loading_show_up.height;
			}
		}
	},
	get loading_show_down() {
		return this._loading_show_down;
	},
	set loading_show_down(value) {
		if (this._loading_show_down !== value) {
			ALittle.DisplayView.RemoveChild.call(this, this._loading_show_down);
			this._loading_show_down = undefined;
		}
		if (value !== undefined) {
			this._loading_show_down = value;
			ALittle.DisplayView.AddChild.call(this, this._loading_show_down);
			if (this._type === 1) {
				this._loading_show_down.x = this._scroll_linear.x + this._scroll_linear.width;
			} else {
				this._loading_show_down.y = this._scroll_linear.y + this._scroll_linear.height;
			}
		}
	},
	UpdateLoadingShow : function() {
		if (this._type === 1) {
			if (this._loading_show_up !== undefined) {
				this._loading_show_up.x = this._scroll_linear.x - this._loading_show_up.width;
			}
			if (this._loading_show_down !== undefined) {
				this._loading_show_down.x = this._scroll_linear.x + this._scroll_linear.width;
			}
		} else {
			if (this._loading_show_up !== undefined) {
				this._loading_show_up.y = this._scroll_linear.y - this._loading_show_up.height;
			}
			if (this._loading_show_down !== undefined) {
				this._loading_show_down.y = this._scroll_linear.y + this._scroll_linear.height;
			}
		}
	},
	Layout : function(index) {
		this._scroll_linear.Layout(index);
		this.RefreshClipDisLine();
	},
	DeepLayout : function() {
		this._scroll_linear.DeepLayout();
		this.RefreshClipDisLine();
	},
	HandleLinearResize : function(event) {
		this.AdjustScrollBar();
		this.RefreshClipDisLine();
	},
	HandleRightScrollBarChange : function(event) {
		if (this._type === 1) {
			let rate = this._scroll_bar.offset_rate;
			let x = 0.0;
			let linear_width = this._scroll_linear.width;
			if (linear_width > this._width) {
				let total_width = linear_width - this._width;
				x = -total_width * rate;
			}
			this._scroll_linear.x = x;
		} else {
			let rate = this._scroll_bar.offset_rate;
			let y = 0.0;
			let linear_height = this._scroll_linear.height;
			if (linear_height > this._height) {
				let total_height = linear_height - this._height;
				y = -total_height * rate;
			}
			this._scroll_linear.y = y;
		}
		this.RefreshClipDisLine();
		this.ShowRightScrollBar();
	},
	HandleRightScrollBarChangeEnd : function(event) {
		this.HideRightScrollBar();
	},
	HandleMButtonWheel : function(event) {
		if (this._scroll_bar !== undefined && event.delta_y !== 0) {
			let offset = this._scroll_linear.height * 0.1 * event.delta_y;
			if (offset > 60) {
				offset = 60;
			} else if (offset < -60) {
				offset = -60;
			}
			if (offset !== 0) {
				this._scroll_bar.offset_rate = this._scroll_bar.offset_rate - offset / this._scroll_linear.height;
			}
			this.HandleRightScrollBarChange(undefined);
			this.HideRightScrollBar();
		}
	},
	get open_extends_drag() {
		return this._open_extends_drag;
	},
	set open_extends_drag(value) {
		this._open_extends_drag = value;
	},
	HandleDragBegin : function(event) {
		this._drag_delta_table = [];
		this._drag_delta_table_count = 0;
		A_LoopSystem.RemoveUpdater(this._scroll_bar_loop);
		if (this._scroll_bar !== undefined) {
			this._scroll_bar.visible = true;
			this._scroll_bar.alpha = 1;
		}
		if (this._type === 1) {
			A_LoopSystem.RemoveUpdater(this._drag_loop_x);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
		} else {
			A_LoopSystem.RemoveUpdater(this._drag_loop_y);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
		}
	},
	HandleDrag : function(event) {
		if (this._type === 1) {
			if (this._drag_delta_table_count < 3) {
				++ this._drag_delta_table_count;
				this._drag_delta_table[this._drag_delta_table_count - 1] = event.delta_x;
			} else {
				__remove(this._drag_delta_table, 1);
				this._drag_delta_table[this._drag_delta_table_count - 1] = event.delta_x;
			}
			this._drag_time = ALittle.Time_GetCurTime();
			let linear_width = this._scroll_linear.width;
			if (event.delta_x !== 0 && this._scroll_bar !== undefined) {
				if (event.delta_x > 0) {
					let min_x = 0.0;
					let max_x = this._width * this._drag_rate;
					let x = this._scroll_linear.x;
					if (x > min_x) {
						x = x + event.delta_x * __sin((1 - x / (this._width * this._drag_rate)) * 1.57);
						if (x > max_x) {
							x = max_x;
						}
					} else {
						x = x + (event.delta_x);
					}
					if (x >= min_x && !this._open_extends_drag) {
						x = min_x;
					}
					this._scroll_linear.x = x;
					if (this._scroll_bar !== undefined) {
						this._scroll_bar.offset_rate = -x / (linear_width - this._width);
					}
				} else {
					let x = this._scroll_linear.x;
					if (linear_width < this._width) {
						x = x + (event.delta_x);
						if (x < 0) {
							x = 0;
						}
					} else {
						let max_x = -linear_width + this._width;
						let min_x = max_x - this._width * this._drag_rate;
						if (x < max_x) {
							x = x + (event.delta_x * __sin((x - min_x) / (this._width * this._drag_rate) * 1.57));
							if (x < min_x) {
								x = min_x;
							}
						} else {
							x = x + (event.delta_x);
						}
						if (x <= max_x && !this._open_extends_drag) {
							x = max_x;
						}
					}
					this._scroll_linear.x = x;
					if (this._scroll_bar !== undefined) {
						this._scroll_bar.offset_rate = -x / (linear_width - this._width);
					}
				}
				this.RefreshClipDisLine(event.delta_x);
			}
		} else {
			if (this._drag_delta_table_count < 3) {
				++ this._drag_delta_table_count;
				this._drag_delta_table[this._drag_delta_table_count - 1] = event.delta_y;
			} else {
				__remove(this._drag_delta_table, 1);
				this._drag_delta_table[this._drag_delta_table_count - 1] = event.delta_y;
			}
			this._drag_time = ALittle.Time_GetCurTime();
			let linear_height = this._scroll_linear.height;
			if (event.delta_y !== 0 && this._scroll_bar !== undefined) {
				if (event.delta_y > 0) {
					let min_y = 0.0;
					let max_y = this._height * this._drag_rate;
					let y = this._scroll_linear.y;
					if (y > min_y) {
						y = y + event.delta_y * __sin((1 - y / (this._height * this._drag_rate)) * 1.57);
						if (y > max_y) {
							y = max_y;
						}
					} else {
						y = y + (event.delta_y);
					}
					if (y >= min_y && !this._open_extends_drag) {
						y = min_y;
					}
					this._scroll_linear.y = y;
					if (this._scroll_bar !== undefined) {
						this._scroll_bar.offset_rate = -y / (linear_height - this._height);
					}
				} else {
					let y = this._scroll_linear.y;
					if (linear_height < this._height) {
						y = y + (event.delta_y);
						if (y < 0) {
							y = 0;
						}
					} else {
						let max_y = -linear_height + this._height;
						let min_y = max_y - this._height * this._drag_rate;
						if (y < max_y) {
							y = y + (event.delta_y * __sin((y - min_y) / (this._height * this._drag_rate) * 1.57));
							if (y < min_y) {
								y = min_y;
							}
						} else {
							y = y + (event.delta_y);
						}
						if (y <= max_y && !this._open_extends_drag) {
							y = max_y;
						}
					}
					this._scroll_linear.y = y;
					if (this._scroll_bar !== undefined) {
						this._scroll_bar.offset_rate = -y / (linear_height - this._height);
					}
				}
				this.RefreshClipDisLine(event.delta_y);
			}
		}
	},
	HandleDragEnd : function(event) {
		if (this._type === 1) {
			let linear_width = this._scroll_linear.width;
			if (this._scroll_linear.x > 0) {
				A_LoopSystem.RemoveUpdater(this._drag_loop_x);
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", 0, 200, 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_x);
				this.HideRightScrollBar();
				if (this._scroll_linear.x >= this._width * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(1848466169), {});
				}
			} else if (this._scroll_linear.x < -linear_width + this._width) {
				if (this._scroll_linear.x < 0) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_x);
					this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", -linear_width + this._width, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_x);
					this.HideRightScrollBar();
				}
				if (this._scroll_linear.x <= -linear_width + this._width - this._width * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(809518110), {});
				}
			} else if (this._scroll_linear.x !== 0 && this._scroll_linear.x !== -linear_width + this._width) {
				let count = this._drag_delta_table_count;
				let drag_delta_x = 0.0;
				let drag_end_time = ALittle.Time_GetCurTime() - this._drag_time;
				if (drag_end_time < 50) {
					if (count === 1 || count === 2) {
						drag_delta_x = this._drag_delta_table[1 - 1];
					} else if (count === 3) {
						drag_delta_x = __floor((this._drag_delta_table[count - 1 - 1] + this._drag_delta_table[count - 2 - 1]) / 2);
					} else {
						drag_delta_x = 0;
					}
				} else {
					if (count !== 0) {
						drag_delta_x = this._drag_delta_table[count - 1];
					} else {
						drag_delta_x = 0;
					}
				}
				if (drag_delta_x < 0 && drag_delta_x < -this._max_speed) {
					drag_delta_x = -this._max_speed;
				} else if (drag_delta_x > 0 && drag_delta_x > this._max_speed) {
					drag_delta_x = this._max_speed;
				}
				this._drag_delta_x = drag_delta_x;
				A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
				this._drag_delta_loop_x = ALittle.NewObject(ALittle.LoopFunction, this.RefreshLinearX.bind(this), -1, 1, 0);
				A_LoopSystem.AddUpdater(this._drag_delta_loop_x);
			}
		} else {
			let linear_height = this._scroll_linear.height;
			if (this._scroll_linear.y > 0) {
				A_LoopSystem.RemoveUpdater(this._drag_loop_y);
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", 0, 200, 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_y);
				this.HideRightScrollBar();
				if (this._scroll_linear.y >= this._height * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(1848466169), {});
				}
			} else if (this._scroll_linear.y < -linear_height + this._height) {
				if (this._scroll_linear.y < 0) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_y);
					this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", -linear_height + this._height, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_y);
					this.HideRightScrollBar();
				}
				if (this._scroll_linear.y <= -linear_height + this._height - this._height * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(809518110), {});
				}
			} else if (this._scroll_linear.y !== 0 && this._scroll_linear.y !== -linear_height + this._height) {
				let count = this._drag_delta_table_count;
				let drag_delta_y = 0.0;
				let drag_end_time = ALittle.Time_GetCurTime() - this._drag_time;
				if (drag_end_time < 50) {
					if (count === 1 || count === 2) {
						drag_delta_y = this._drag_delta_table[1 - 1];
					} else if (count === 3) {
						drag_delta_y = __floor((this._drag_delta_table[count - 1 - 1] + this._drag_delta_table[count - 2 - 1]) / 2);
					} else {
						drag_delta_y = 0;
					}
				} else {
					if (count !== 0) {
						drag_delta_y = this._drag_delta_table[count - 1];
					} else {
						drag_delta_y = 0;
					}
				}
				if (drag_delta_y < 0 && drag_delta_y < -this._max_speed) {
					drag_delta_y = -this._max_speed;
				} else if (drag_delta_y > 0 && drag_delta_y > this._max_speed) {
					drag_delta_y = this._max_speed;
				}
				this._drag_delta_y = drag_delta_y;
				A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
				this._drag_delta_loop_y = ALittle.NewObject(ALittle.LoopFunction, this.RefreshLinearY.bind(this), -1, 1, 0);
				A_LoopSystem.AddUpdater(this._drag_delta_loop_y);
			}
		}
	},
	RefreshLinearX : function() {
		this._scroll_linear.x = this._scroll_linear.x + this._drag_delta_x;
		let linear_width = this._scroll_linear.width;
		let loop_end = false;
		if (this._drag_delta_x !== 0 && this._scroll_bar !== undefined) {
			if (this._drag_delta_x > 0) {
				let min_x = 0.0;
				let max_x = this._width * this._drag_rate;
				let x = this._scroll_linear.x;
				if (x > min_x) {
					x = x + this._drag_delta_x * __sin((1 - x / (this._width * this._drag_rate)) * 1.57);
					if (x > max_x) {
						x = max_x;
						loop_end = true;
					}
				} else {
					x = x + (this._drag_delta_x);
				}
				if (x >= min_x && !this._open_extends_drag) {
					x = min_x;
				}
				this._scroll_linear.x = x;
				if (this._scroll_bar !== undefined) {
					this._scroll_bar.offset_rate = -x / (linear_width - this._width);
				}
			} else {
				let x = this._scroll_linear.x;
				if (linear_width < this._width) {
					x = x + (this._drag_delta_x);
					if (x < 0) {
						x = 0;
					}
				} else {
					let max_x = -linear_width + this._width;
					let min_x = max_x - this._width * this._drag_rate;
					if (x < max_x) {
						x = x + (this._drag_delta_x * __sin((x - min_x) / (this._width * this._drag_rate) * 1.57));
						if (x < min_x) {
							x = min_x;
							loop_end = true;
						}
					} else {
						x = x + (this._drag_delta_x);
					}
					if (x <= max_x && !this._open_extends_drag) {
						x = max_x;
					}
				}
				this._scroll_linear.x = x;
				if (this._scroll_bar !== undefined) {
					this._scroll_bar.offset_rate = -x / (linear_width - this._width);
				}
			}
			this.RefreshClipDisLine();
		}
		if (this._drag_delta_x < 0) {
			this._drag_delta_x = this._drag_delta_x + 1;
			if (this._drag_delta_x >= 0) {
				loop_end = true;
			}
		} else if (this._drag_delta_x > 0) {
			this._drag_delta_x = this._drag_delta_x - 1;
			if (this._drag_delta_x <= 0) {
				loop_end = true;
			}
		} else {
			loop_end = true;
		}
		if (loop_end) {
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
			if (this._scroll_linear.x > 0) {
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				A_LoopSystem.RemoveUpdater(this._drag_loop_x);
				this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", 0, 200, 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_x);
				if (this._scroll_linear.x >= this._width * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(1848466169), {});
				}
			} else if (this._scroll_linear.x < -linear_width + this._width) {
				if (this._scroll_linear.x < 0) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_x);
					this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", -linear_width + this._width, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_x);
				}
				if (this._scroll_linear.x <= -linear_width + this._width - this._width * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(809518110), {});
				}
			}
			this.HideRightScrollBar();
		}
	},
	RefreshLinearY : function() {
		this._scroll_linear.y = this._scroll_linear.y + this._drag_delta_y;
		let linear_height = this._scroll_linear.height;
		let loop_end = false;
		if (this._drag_delta_y !== 0 && this._scroll_bar !== undefined) {
			if (this._drag_delta_y > 0) {
				let min_y = 0.0;
				let max_y = this._height * this._drag_rate;
				let y = this._scroll_linear.y;
				if (y > min_y) {
					y = y + (this._drag_delta_y * __sin((1 - y / (this._height * this._drag_rate)) * 1.57));
					if (y > max_y) {
						y = max_y;
						loop_end = true;
					}
				} else {
					y = y + (this._drag_delta_y);
				}
				if (y >= min_y && !this._open_extends_drag) {
					y = min_y;
				}
				this._scroll_linear.y = y;
				if (this._scroll_bar !== undefined) {
					this._scroll_bar.offset_rate = -y / (linear_height - this._height);
				}
			} else {
				let y = this._scroll_linear.y;
				if (linear_height < this._height) {
					y = y + (this._drag_delta_y);
					if (y < 0) {
						y = 0;
					}
				} else {
					let max_y = -linear_height + this._height;
					let min_y = max_y - this._height * this._drag_rate;
					if (y < max_y) {
						y = y + (this._drag_delta_y * __sin((y - min_y) / (this._height * this._drag_rate) * 1.57));
						if (y < min_y) {
							y = min_y;
							loop_end = true;
						}
					} else {
						y = y + (this._drag_delta_y);
					}
					if (y <= max_y && !this._open_extends_drag) {
						y = max_y;
					}
				}
				this._scroll_linear.y = y;
				if (this._scroll_bar !== undefined) {
					this._scroll_bar.offset_rate = -y / (linear_height - this._height);
				}
			}
			this.RefreshClipDisLine();
		}
		if (this._drag_delta_y < 0) {
			this._drag_delta_y = this._drag_delta_y + 1;
			if (this._drag_delta_y >= 0) {
				loop_end = true;
			}
		} else if (this._drag_delta_y > 0) {
			this._drag_delta_y = this._drag_delta_y - 1;
			if (this._drag_delta_y <= 0) {
				loop_end = true;
			}
		} else {
			loop_end = true;
		}
		if (loop_end) {
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
			if (this._scroll_linear.y > 0) {
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				A_LoopSystem.RemoveUpdater(this._drag_loop_y);
				this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", 0, 200, 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_y);
				if (this._scroll_linear.y >= this._height * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(1848466169), {});
				}
			} else if (this._scroll_linear.y < -linear_height + this._height) {
				if (this._scroll_linear.y < 0) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_y);
					this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", -linear_height + this._height, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_y);
				}
				if (this._scroll_linear.y <= -linear_height + this._height - this._height * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(809518110), {});
				}
			}
			this.HideRightScrollBar();
		}
	},
	YScrollBarChange : function() {
		this._scroll_bar.offset_rate = -this._scroll_linear.y / (this._linear_height - this._height);
	},
	XScrollBarChange : function() {
		this._scroll_bar.offset_rate = -this._scroll_linear.x / (this._linear_width - this._width);
	},
	RefreshClipDisLineImpl : function(v_move) {
		this._scroll_linear.ClipRect(0, 0, this.width, this.height, undefined, v_move);
		this._clip_loop = undefined;
	},
	RefreshClipDisLine : function(v_move) {
		this.UpdateLoadingShow();
		if (this._clip_atonce) {
			this._scroll_linear.ClipRect(0, 0, this.width, this.height, undefined, undefined);
			return;
		}
		if (this._clip_loop !== undefined && this._clip_loop._user_data === undefined) {
			return;
		}
		this._clip_loop = ALittle.NewObject(ALittle.LoopFunction, this.RefreshClipDisLineImpl.bind(this, v_move), 1, 0, 1);
		this._clip_loop._user_data = v_move;
		A_LoopSystem.AddUpdater(this._clip_loop);
	},
	HideRightScrollBar : function() {
		if (this._scroll_bar !== undefined) {
			this._scroll_bar_loop = ALittle.NewObject(ALittle.LoopList);
			this._scroll_bar_loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._scroll_bar, "alpha", 0, 2000, 1000));
			this._scroll_bar_loop.AddUpdater(ALittle.NewObject(ALittle.LoopAttribute, this._scroll_bar, "visible", false, 1));
			A_LoopSystem.AddUpdater(this._scroll_bar_loop);
		}
	},
	ShowRightScrollBar : function() {
		if (this._scroll_bar_loop !== undefined) {
			A_LoopSystem.RemoveUpdater(this._scroll_bar_loop);
			this._scroll_bar_loop = undefined;
			if (this._scroll_bar !== undefined) {
				this._scroll_bar.visible = true;
				this._scroll_bar.alpha = 1;
			}
		}
	},
}, "ALittle.ScrollList");

}