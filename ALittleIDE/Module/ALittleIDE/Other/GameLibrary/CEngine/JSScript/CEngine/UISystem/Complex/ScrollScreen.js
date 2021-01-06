{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __sin = ALittle.Math_Sin;
if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittle.ScrollScreen = JavaScript.Class(ALittle.DisplayGroup, {
	Ctor : function(ctrl_sys) {
		this._width = 0;
		this._height = 0;
		this._content_width = 0;
		this._content_height = 0;
		this._drag_rate = 0.2;
		this._open_extends_drag = false;
		this._drag_delta_x = 0;
		this._drag_delta_y = 0;
		this._scroll_view = ALittle.NewObject(ALittle.DisplayView, this._ctrl_sys);
		ALittle.DisplayGroup.AddChild.call(this, this._scroll_view);
		this._scroll_content = ALittle.NewObject(ALittle.DisplayGroup, this._ctrl_sys);
		this._scroll_view.AddChild(this._scroll_content);
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
	HandleMButtonWheel : function(event) {
		if (this._bottom_scroll_bar !== undefined && event.delta_x !== 0) {
			this._bottom_scroll_bar.offset_rate = this._bottom_scroll_bar.offset_rate - 0.1 * event.delta_x;
		}
		if (this._right_scroll_bar !== undefined && event.delta_y !== 0) {
			let offset = this._content_height * 0.1 * event.delta_y;
			if (offset > 60) {
				offset = 60;
			} else if (offset < -60) {
				offset = -60;
			}
			if (offset !== 0) {
				this._right_scroll_bar.offset_rate = this._right_scroll_bar.offset_rate - offset / this._content_height;
			}
		}
		this.AdjustScrollBar();
	},
	EnableDrag : function(value) {
		if (value) {
			this.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
			this.AddEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
			this.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		} else {
			this.RemoveEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
			this.RemoveEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
			this.RemoveEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		}
	},
	get open_extends_drag() {
		return this._open_extends_drag;
	},
	set open_extends_drag(value) {
		this._open_extends_drag = value;
	},
	get container() {
		return this._scroll_content;
	},
	get view() {
		return this._scroll_view;
	},
	set container(value) {
		if (value === undefined) {
			value = ALittle.NewObject(ALittle.DisplayGroup, this._ctrl_sys);
		}
		let child_list = [];
		let child_list_count = 0;
		let old_child_list = this._scroll_content.childs;
		let ___OBJECT_1 = old_child_list;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			++ child_list_count;
			child_list[child_list_count - 1] = v;
		}
		this._scroll_content.RemoveEventListener(___all_struct.get(-431205740), this, this.HandleContainerResize);
		this._scroll_view.RemoveChild(this._scroll_content);
		this._scroll_content = value;
		let ___OBJECT_2 = child_list;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let v = ___OBJECT_2[k - 1];
			if (v === undefined) break;
			value.AddChild(v);
		}
		this._scroll_content.AddEventListener(___all_struct.get(-431205740), this, this.HandleContainerResize);
		this._scroll_view.AddChild(this._scroll_content, 1);
		this.AdjustScrollBar();
	},
	SetContainer : function(value) {
		if (value === undefined) {
			value = ALittle.NewObject(ALittle.DisplayGroup, this._ctrl_sys);
		}
		this._scroll_content.RemoveEventListener(___all_struct.get(-431205740), this, this.HandleContainerResize);
		this._scroll_view.RemoveChild(this._scroll_content);
		this._scroll_content = value;
		this._scroll_content.AddEventListener(___all_struct.get(-431205740), this, this.HandleContainerResize);
		this._scroll_view.AddChild(this._scroll_content, 1);
		this.AdjustScrollBar();
	},
	set container_y(value) {
		if (this._scroll_content === undefined) {
			return;
		}
		this._scroll_content.y = value;
		this.YScrollBarChange();
		this.AdjustScrollBar();
	},
	get container_y() {
		if (this._scroll_content === undefined) {
			return 0;
		}
		return this._scroll_content.y;
	},
	set container_x(value) {
		if (this._scroll_content === undefined) {
			return;
		}
		this._scroll_content.x = value;
		this.XScrollBarChange();
		this.AdjustScrollBar();
	},
	get container_x() {
		if (this._scroll_content === undefined) {
			return 0;
		}
		return this._scroll_content.x;
	},
	get static_object_h() {
		return this._static_object_h;
	},
	set static_object_h(value) {
		if (this._static_object_h === value) {
			return;
		}
		this._scroll_view.RemoveChild(this._static_object_h);
		this._static_object_h = value;
		if (this._static_object_h === undefined) {
			return;
		}
		this._scroll_view.AddChild(this._static_object_h, 3);
		this._static_object_h.y = 0;
		this._static_object_h.x = this._scroll_content.x;
	},
	get static_object_v() {
		return this._static_object_v;
	},
	set static_object_v(value) {
		if (this._static_object_v === value) {
			return;
		}
		this._scroll_view.RemoveChild(this._static_object_v);
		this._static_object_v = value;
		if (this._static_object_v === undefined) {
			return;
		}
		this._scroll_view.AddChild(this._static_object_v, 2);
		this._static_object_v.y = this._scroll_content.y;
		this._static_object_v.x = 0;
	},
	get static_object_hv() {
		return this._static_object_hv;
	},
	set static_object_hv(value) {
		if (this._static_object_hv === value) {
			return;
		}
		this._scroll_view.RemoveChild(this._static_object_hv);
		this._static_object_hv = value;
		if (this._static_object_hv === undefined) {
			return;
		}
		this._scroll_view.AddChild(this._static_object_hv, 3);
		this._static_object_hv.y = 0;
		this._static_object_hv.x = 0;
	},
	GetChildIndex : function(child) {
		return this._scroll_content.GetChildIndex(child);
	},
	SetChildIndex : function(child, index) {
		let result = this._scroll_content.SetChildIndex(child, index);
		this.RefreshClipDisLine();
		return result;
	},
	GetChildByIndex : function(index) {
		return this._scroll_content.GetChildByIndex(index);
	},
	get childs() {
		return this._scroll_content.childs;
	},
	get child_count() {
		return this._scroll_content.child_count;
	},
	AddChild : function(child, index) {
		if (child === undefined) {
			return false;
		}
		if (this._scroll_content.AddChild(child, index) === false) {
			return false;
		}
		this.AdjustScrollBar();
		return true;
	},
	RemoveChild : function(child) {
		if (child === undefined) {
			return false;
		}
		if (this._scroll_content.RemoveChild(child) === false) {
			return false;
		}
		this.AdjustScrollBar();
		return true;
	},
	SpliceChild : function(index, count) {
		let result = this._scroll_content.SpliceChild(index, count);
		if (result !== 0) {
			this.AdjustScrollBar();
		}
		return result;
	},
	HasChild : function(child) {
		return this._scroll_content.HasChild(child);
	},
	RemoveAllChild : function() {
		A_LoopSystem.RemoveUpdater(this._drag_loop_x);
		A_LoopSystem.RemoveUpdater(this._drag_loop_y);
		A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
		A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
		A_LoopSystem.RemoveUpdater(this._x_type_dispatch);
		A_LoopSystem.RemoveUpdater(this._y_type_dispatch);
		this._scroll_content.RemoveAllChild();
		this.AdjustScrollBar();
	},
	set width(value) {
		if (this._width === value) {
			return;
		}
		this._width = value;
		if (this._width_type === 1) {
			this._width_value = this._width;
		}
		let width = 0.0;
		if (this._right_scroll_bar !== undefined) {
			width = this._right_scroll_bar.width;
		}
		let remain_width = this._width - width;
		if (remain_width < 0) {
			this._scroll_view.width = this._width;
			if (this._right_scroll_bar !== undefined) {
				this._right_scroll_bar.visible = false;
				this._right_scroll_bar.x = this._width;
				this._right_scroll_bar.y = 0;
			}
		} else {
			this._scroll_view.width = remain_width;
			if (this._right_scroll_bar !== undefined) {
				this._right_scroll_bar.visible = true;
				this._right_scroll_bar.x = remain_width;
				this._right_scroll_bar.y = 0;
			}
		}
		if (this._right_scroll_bar !== undefined) {
			this._right_scroll_bar.height = this._scroll_view.height;
		}
		if (this._bottom_scroll_bar !== undefined) {
			let rate = this._bottom_scroll_bar.offset_rate;
			if (this._content_width < this._scroll_view.width) {
				rate = 0;
			}
			this._bottom_scroll_bar.width = this._scroll_view.width;
			this._bottom_scroll_bar.total_size = this._content_width;
			this._bottom_scroll_bar.show_size = this._scroll_view.width;
			this._bottom_scroll_bar.offset_rate = rate;
			this._bottom_scroll_bar.offset_step = 0.1;
			let x = 0.0;
			let content_width = this._content_width;
			if (content_width > this._scroll_view.width) {
				let total_width = content_width - this._scroll_view.width;
				x = -total_width * rate;
			}
			this._scroll_content.x = x;
			if (this._static_object_h !== undefined) {
				this._static_object_h.x = x;
			}
		}
		this.RefreshClipDisLine();
	},
	get width() {
		return this._width;
	},
	set height(value) {
		if (this._height === value) {
			return;
		}
		this._height = value;
		if (this._height_type === 1) {
			this._height_value = this._height;
		}
		let height = 0.0;
		if (this._bottom_scroll_bar !== undefined) {
			height = this._bottom_scroll_bar.height;
		}
		let remain_height = this._height - height;
		if (remain_height < 0) {
			this._scroll_view.height = this._height;
			if (this._bottom_scroll_bar !== undefined) {
				this._bottom_scroll_bar.visible = false;
				this._bottom_scroll_bar.y = this._height;
			}
		} else {
			this._scroll_view.height = remain_height;
			if (this._bottom_scroll_bar !== undefined) {
				this._bottom_scroll_bar.visible = true;
				this._bottom_scroll_bar.y = remain_height;
			}
		}
		if (this._bottom_scroll_bar !== undefined) {
			this._bottom_scroll_bar.width = this._scroll_view.width;
		}
		if (this._right_scroll_bar !== undefined) {
			let rate = this._right_scroll_bar.offset_rate;
			if (this._content_height < this._scroll_view.height) {
				rate = 0;
			}
			this._right_scroll_bar.height = this._scroll_view.height;
			this._right_scroll_bar.total_size = this._content_height;
			this._right_scroll_bar.show_size = this._scroll_view.height;
			this._right_scroll_bar.offset_rate = rate;
			this._right_scroll_bar.offset_step = 0.1;
			let y = 0.0;
			let content_height = this._content_height;
			if (content_height > this._scroll_view.height) {
				let total_height = content_height - this._scroll_view.height;
				y = -total_height * rate;
			}
			this._scroll_content.y = y;
			if (this._static_object_v !== undefined) {
				this._static_object_v.y = y;
			}
		}
		this.RefreshClipDisLine();
	},
	get height() {
		return this._height;
	},
	get view_width() {
		return this._scroll_view.width;
	},
	get view_height() {
		return this._scroll_view.height;
	},
	set right_scrollbar(value) {
		if (this._right_scroll_bar !== undefined) {
			ALittle.DisplayGroup.RemoveChild.call(this, this._right_scroll_bar);
			this._right_scroll_bar.RemoveEventListener(___all_struct.get(958494922), this, this.HandleRightScrollBarChange);
		}
		this._right_scroll_bar = value;
		let width = 0.0;
		if (this._right_scroll_bar !== undefined) {
			this._right_scroll_bar.type = 2;
			width = this._right_scroll_bar.width;
			ALittle.DisplayGroup.AddChild.call(this, this._right_scroll_bar);
			this._right_scroll_bar.AddEventListener(___all_struct.get(958494922), this, this.HandleRightScrollBarChange);
			this._right_scroll_bar.height = this._scroll_view.height;
			this._right_scroll_bar.y = 0;
		}
		let remain_width = this._width - width;
		if (remain_width < 0) {
			this._scroll_view.width = this._width;
			if (this._right_scroll_bar !== undefined) {
				this._right_scroll_bar.visible = false;
				this._right_scroll_bar.x = this._width;
			}
		} else {
			this._scroll_view.width = remain_width;
			if (this._right_scroll_bar !== undefined) {
				this._right_scroll_bar.visible = true;
				this._right_scroll_bar.x = remain_width;
			}
		}
		if (this._right_scroll_bar !== undefined) {
			this._right_scroll_bar.total_size = this._content_height;
			this._right_scroll_bar.show_size = this._scroll_view.height;
			this._right_scroll_bar.offset_rate = 0;
			this._right_scroll_bar.offset_step = 0.1;
		}
		if (this._bottom_scroll_bar !== undefined) {
			let rate = this._bottom_scroll_bar.offset_rate;
			if (this._content_width < this._scroll_view.width) {
				rate = 0;
			}
			this._bottom_scroll_bar.width = this._scroll_view.width;
			this._bottom_scroll_bar.total_size = this._content_width;
			this._bottom_scroll_bar.show_size = this._scroll_view.width;
			this._bottom_scroll_bar.offset_rate = rate;
			this._bottom_scroll_bar.offset_step = 0.1;
		}
	},
	get right_scrollbar() {
		return this._right_scroll_bar;
	},
	ScrollToBottom : function() {
		if (this._right_scroll_bar === undefined) {
			return;
		}
		this._right_scroll_bar.offset_rate = 1;
		this._right_scroll_bar.DispatchEvent(___all_struct.get(958494922), {});
	},
	ScrollToRight : function() {
		if (this._bottom_scroll_bar === undefined) {
			return;
		}
		this._bottom_scroll_bar.offset_rate = 1;
		this._bottom_scroll_bar.DispatchEvent(___all_struct.get(958494922), {});
	},
	set bottom_scrollbar(value) {
		if (this._bottom_scroll_bar !== undefined) {
			ALittle.DisplayGroup.RemoveChild.call(this, this._bottom_scroll_bar);
			this._bottom_scroll_bar.RemoveEventListener(___all_struct.get(958494922), this, this.HandleBottomScrollBarChange);
		}
		this._bottom_scroll_bar = value;
		let height = 0.0;
		if (this._bottom_scroll_bar !== undefined) {
			this._bottom_scroll_bar.type = 1;
			height = this._bottom_scroll_bar.height;
			ALittle.DisplayGroup.AddChild.call(this, this._bottom_scroll_bar);
			this._bottom_scroll_bar.AddEventListener(___all_struct.get(958494922), this, this.HandleBottomScrollBarChange);
			this._bottom_scroll_bar.width = this._scroll_view.width;
			this._bottom_scroll_bar.x = 0;
		}
		let remain_height = this._height - height;
		if (remain_height < 0) {
			this._scroll_view.height = this._height;
			if (this._bottom_scroll_bar !== undefined) {
				this._bottom_scroll_bar.visible = false;
				this._bottom_scroll_bar.y = this._height;
			}
		} else {
			this._scroll_view.height = remain_height;
			if (this._bottom_scroll_bar !== undefined) {
				this._bottom_scroll_bar.visible = true;
				this._bottom_scroll_bar.y = remain_height;
			}
		}
		if (this._bottom_scroll_bar !== undefined) {
			this._bottom_scroll_bar.total_size = this._content_width;
			this._bottom_scroll_bar.show_size = this._scroll_view.width;
			this._bottom_scroll_bar.offset_rate = 0;
			this._bottom_scroll_bar.offset_step = 0.1;
		}
		if (this._right_scroll_bar !== undefined) {
			let rate = this._right_scroll_bar.offset_rate;
			if (this._content_height < this._scroll_view.height) {
				rate = 0;
			}
			this._right_scroll_bar.height = this._scroll_view.height;
			this._right_scroll_bar.total_size = this._content_height;
			this._right_scroll_bar.show_size = this._scroll_view.height;
			this._right_scroll_bar.offset_rate = rate;
			this._right_scroll_bar.offset_step = 0.1;
		}
	},
	get bottom_scrollbar() {
		return this._bottom_scroll_bar;
	},
	AdjustScrollBar : function() {
		this._content_width = this._scroll_content.max_right;
		if (this._static_object_h !== undefined) {
			if (this._static_object_h.width > this._content_width) {
				this._content_width = this._static_object_h.width;
			}
		}
		this._content_height = this._scroll_content.max_bottom;
		if (this._bottom_scroll_bar !== undefined) {
			let rate = this._bottom_scroll_bar.offset_rate;
			if (this._content_width < this._scroll_view.width) {
				rate = 0;
			}
			this._bottom_scroll_bar.total_size = this._content_width;
			this._bottom_scroll_bar.show_size = this._scroll_view.width;
			this._bottom_scroll_bar.offset_rate = rate;
			this._bottom_scroll_bar.offset_step = 0.1;
			this.HandleBottomScrollBarChange(undefined);
		}
		if (this._right_scroll_bar !== undefined) {
			let rate = this._right_scroll_bar.offset_rate;
			if (this._content_height < this._scroll_view.height) {
				rate = 0;
			}
			this._right_scroll_bar.height = this._scroll_view.height;
			this._right_scroll_bar.total_size = this._content_height;
			this._right_scroll_bar.show_size = this._scroll_view.height;
			this._right_scroll_bar.offset_rate = rate;
			this._right_scroll_bar.offset_step = 0.1;
			this.HandleRightScrollBarChange(undefined);
		}
	},
	HandleRightScrollBarChange : function(event) {
		let rate = this._right_scroll_bar.offset_rate;
		let y = 0.0;
		let content_height = this._content_height;
		if (content_height > this._scroll_view.height) {
			let total_height = content_height - this._scroll_view.height;
			y = -total_height * rate;
		}
		this._scroll_content.y = y;
		if (this._static_object_v !== undefined) {
			this._static_object_v.y = y;
		}
		this.RefreshClipDisLine();
	},
	HandleBottomScrollBarChange : function(event) {
		let rate = this._bottom_scroll_bar.offset_rate;
		let x = 0.0;
		let content_width = this._content_width;
		if (content_width > this._scroll_view.width) {
			let total_width = content_width - this._scroll_view.width;
			x = -total_width * rate;
		}
		this._scroll_content.x = x;
		if (this._static_object_h !== undefined) {
			this._static_object_h.x = x;
		}
		this.RefreshClipDisLine();
	},
	HandleContainerResize : function(event) {
		this.AdjustScrollBar();
	},
	HandleDragBegin : function(event) {
	},
	HandleDrag : function(event) {
		this._drag_delta_x = event.delta_x;
		this._drag_delta_y = event.delta_y;
		this._content_width = this._scroll_content.max_right;
		if (this._static_object_h !== undefined) {
			if (this._static_object_h.width > this._content_width) {
				this._content_width = this._static_object_h.width;
			}
		}
		this._content_height = this._scroll_content.max_bottom;
		if (event.delta_x !== 0) {
			if (event.delta_x > 0) {
				let min_x = 0.0;
				let max_x = this._scroll_view.width * this._drag_rate;
				let x = this._scroll_content.x;
				if (x > min_x) {
					x = x + event.delta_x * __sin((1 - x / (this._scroll_view.width * this._drag_rate)) * 1.57);
					if (x > max_x) {
						x = max_x;
					}
				} else {
					x = x + event.delta_x;
				}
				if (this._open_extends_drag === false && x > min_x) {
					x = min_x;
				}
				this._scroll_content.x = x;
				if (this._static_object_h !== undefined) {
					this._static_object_h.x = x;
				}
				if (this._bottom_scroll_bar !== undefined) {
					this._bottom_scroll_bar.offset_rate = -x / (this._content_width - this._scroll_view.width);
				}
			} else {
				let x = this._scroll_content.x;
				if (this._content_width < this._scroll_view.width) {
					x = x + event.delta_x;
					if (x < 0) {
						x = 0;
					}
				} else {
					let max_x = -this._content_width + this._scroll_view.width;
					let min_x = max_x - this._scroll_view.width * this._drag_rate;
					if (x < max_x) {
						x = x + event.delta_x * __sin((x - min_x) / (this._scroll_view.width * this._drag_rate) * 1.57);
						if (x < min_x) {
							x = min_x;
						}
					} else {
						x = x + event.delta_x;
					}
					if (this._open_extends_drag === false && x < max_x) {
						x = max_x;
					}
				}
				this._scroll_content.x = x;
				if (this._static_object_h !== undefined) {
					this._static_object_h.x = x;
				}
				if (this._bottom_scroll_bar !== undefined) {
					this._bottom_scroll_bar.offset_rate = -x / (this._content_width - this._scroll_view.width);
				}
			}
			this.RefreshClipDisLine(event.delta_x);
		}
		if (event.delta_y !== 0) {
			if (event.delta_y > 0) {
				let min_y = 0.0;
				let max_y = this._scroll_view.height * this._drag_rate;
				let y = this._scroll_content.y;
				if (y > min_y) {
					y = y + event.delta_y * __sin((1 - y / (this._scroll_view.height * this._drag_rate)) * 1.57);
					if (y > max_y) {
						y = max_y;
					}
				} else {
					y = y + event.delta_y;
				}
				if (this._open_extends_drag === false && y > min_y) {
					y = min_y;
				}
				this._scroll_content.y = y;
				if (this._static_object_v !== undefined) {
					this._static_object_v.y = y;
				}
				if (this._right_scroll_bar !== undefined) {
					this._right_scroll_bar.offset_rate = -y / (this._content_height - this._scroll_view.height);
				}
			} else {
				let y = this._scroll_content.y;
				if (this._content_height < this._scroll_view.height) {
					y = y + event.delta_y;
					if (y < 0) {
						y = 0;
					}
				} else {
					let max_y = -this._content_height + this._scroll_view.height;
					let min_y = max_y - this._scroll_view.height * this._drag_rate;
					if (y < max_y) {
						y = y + event.delta_y * __sin((y - min_y) / (this._scroll_view.height * this._drag_rate) * 1.57);
						if (y < min_y) {
							y = min_y;
						}
					} else {
						y = y + event.delta_y;
					}
					if (this._open_extends_drag === false && y < max_y) {
						y = max_y;
					}
				}
				this._scroll_content.y = y;
				if (this._static_object_v !== undefined) {
					this._static_object_v.y = y;
				}
				if (this._right_scroll_bar !== undefined) {
					this._right_scroll_bar.offset_rate = -y / (this._content_height - this._scroll_view.height);
				}
			}
			this.RefreshClipDisLine(undefined, event.delta_y);
		}
	},
	HandleDragEnd : function(event) {
		this._content_width = this._scroll_content.max_right;
		if (this._static_object_h !== undefined) {
			if (this._static_object_h.width > this._content_width) {
				this._content_width = this._static_object_h.width;
			}
		}
		this._content_height = this._scroll_content.max_bottom;
		if (this._scroll_content.x > 0) {
			if (this._scroll_content.x >= this._scroll_view.width * this._drag_rate * 0.9) {
				this.DispatchEvent(___all_struct.get(-839083637), {});
			}
			A_LoopSystem.RemoveUpdater(this._drag_loop_x);
			this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "x", 0, 200, 0, ALittle.ScrollScreen.XScrollBarChange.bind(this));
			A_LoopSystem.AddUpdater(this._drag_loop_x);
		} else if (this._scroll_content.x < -this._content_width + this._scroll_view.width) {
			if (this._scroll_content.x <= -this._content_width + this._scroll_view.width - this._scroll_view.width * this._drag_rate * 0.9) {
				this.DispatchEvent(___all_struct.get(-567702959), {});
			}
			if (this._scroll_content.x < 0) {
				A_LoopSystem.RemoveUpdater(this._drag_loop_x);
				this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "x", -this._content_width + this._scroll_view.width, 200, 0, ALittle.ScrollScreen.XScrollBarChange.bind(this));
				A_LoopSystem.AddUpdater(this._drag_loop_x);
			}
		} else if (this._scroll_content.x !== 0 && this._scroll_content.x !== -this._content_width + this._scroll_view.width) {
			let target_x = this._scroll_content.x + this._drag_delta_x * 10;
			let event_dispatch = undefined;
			if (this._drag_delta_x < 0) {
				let max_x = -this._content_width + this._scroll_view.width;
				let min_x = max_x - this._scroll_view.width * this._drag_rate;
				if (target_x < min_x) {
					target_x = min_x;
					event_dispatch = ALittle.ScrollScreen.ScrollDispatchDragLeftEvent.bind(this);
				}
				if (target_x >= min_x && target_x <= max_x) {
					A_LoopSystem.RemoveUpdater(this._drag_loop_x);
					this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "x", -this._content_width + this._scroll_view.width, 200, 300, ALittle.ScrollScreen.XScrollBarChange.bind(this));
					A_LoopSystem.AddUpdater(this._drag_loop_x);
				}
			} else if (this._drag_delta_x > 0) {
				let max_x = this._scroll_view.width * this._drag_rate;
				let min_x = 0;
				if (target_x > max_x) {
					target_x = max_x;
					event_dispatch = ALittle.ScrollScreen.ScrollDispatchDragRightEvent.bind(this);
				}
				if (target_x >= min_x && target_x <= max_x) {
					A_LoopSystem.RemoveUpdater(this._drag_loop_x);
					this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "x", 0, 200, 300, ALittle.ScrollScreen.XScrollBarChange.bind(this));
					A_LoopSystem.AddUpdater(this._drag_loop_x);
				}
			}
			A_LoopSystem.RemoveUpdater(this._x_type_dispatch);
			if (event_dispatch !== undefined) {
				this._x_type_dispatch = ALittle.NewObject(ALittle.LoopFunction, event_dispatch, 1, 0, 300);
				A_LoopSystem.AddUpdater(this._x_type_dispatch);
			}
			if (this._open_extends_drag === false) {
				if (target_x > 0) {
					target_x = 0;
				} else if (target_x < -this._content_width + this._scroll_view.width) {
					target_x = -this._content_width + this._scroll_view.width;
				}
			}
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
			this._drag_delta_loop_x = ALittle.NewObject(ALittle.LoopRit, this._scroll_content, "x", target_x, 300, 0, ALittle.ScrollScreen.XScrollBarChange.bind(this));
			A_LoopSystem.AddUpdater(this._drag_delta_loop_x);
		}
		if (this._scroll_content.y > 0) {
			if (this._scroll_content.y >= this._scroll_view.height * this._drag_rate * 0.9) {
				this.DispatchEvent(___all_struct.get(1848466169), {});
			}
			A_LoopSystem.RemoveUpdater(this._drag_loop_y);
			this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "y", 0, 200, 0, ALittle.ScrollScreen.YScrollBarChange.bind(this));
			A_LoopSystem.AddUpdater(this._drag_loop_y);
		} else if (this._scroll_content.y < -this._content_height + this._scroll_view.height) {
			if (this._scroll_content.y <= -this._content_height + this._scroll_view.height - this._scroll_view.height * this._drag_rate * 0.9) {
				this.DispatchEvent(___all_struct.get(809518110), {});
			}
			if (this._scroll_content.y < 0) {
				A_LoopSystem.RemoveUpdater(this._drag_loop_y);
				this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "y", -this._content_height + this._scroll_view.height, 200, 0, ALittle.ScrollScreen.YScrollBarChange.bind(this));
				A_LoopSystem.AddUpdater(this._drag_loop_y);
			}
		} else if (this._scroll_content.y !== 0 && this._scroll_content.y !== -this._content_height + this._scroll_view.height) {
			let event_dispatch = undefined;
			let target_y = this._scroll_content.y + this._drag_delta_y * 10;
			if (this._drag_delta_y < 0) {
				let max_y = -this._content_height + this._scroll_view.height;
				let min_y = max_y - this._scroll_view.height * this._drag_rate;
				if (target_y < min_y) {
					target_y = min_y;
					event_dispatch = ALittle.ScrollScreen.ScrollDispatchDragUpEvent.bind(this);
				}
				if (target_y >= min_y && target_y <= max_y) {
					A_LoopSystem.RemoveUpdater(this._drag_loop_y);
					this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "y", -this._content_height + this._scroll_view.height, 200, 300, ALittle.ScrollScreen.YScrollBarChange.bind(this));
					A_LoopSystem.AddUpdater(this._drag_loop_y);
				}
			} else if (this._drag_delta_y > 0) {
				let max_y = this._scroll_view.height * this._drag_rate;
				let min_y = 0.0;
				if (target_y > max_y) {
					target_y = max_y;
					event_dispatch = ALittle.ScrollScreen.ScrollDispatchDragDownEvent.bind(this);
				}
				if (target_y >= min_y && target_y <= max_y) {
					A_LoopSystem.RemoveUpdater(this._drag_loop_y);
					this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "y", 0, 200, 300, ALittle.ScrollScreen.YScrollBarChange.bind(this));
					A_LoopSystem.AddUpdater(this._drag_loop_y);
				}
			}
			A_LoopSystem.RemoveUpdater(this._y_type_dispatch);
			if (event_dispatch !== undefined) {
				this._y_type_dispatch = ALittle.NewObject(ALittle.LoopFunction, event_dispatch, 1, 0, 300);
				A_LoopSystem.AddUpdater(this._y_type_dispatch);
			}
			if (this._open_extends_drag === false) {
				if (target_y > 0) {
					target_y = 0;
				} else if (target_y < -this._content_height + this._scroll_view.height) {
					target_y = -this._content_height + this._scroll_view.height;
				}
			}
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
			this._drag_delta_loop_y = ALittle.NewObject(ALittle.LoopRit, this._scroll_content, "y", target_y, 300, 0, ALittle.ScrollScreen.YScrollBarChange.bind(this));
			A_LoopSystem.AddUpdater(this._drag_delta_loop_y);
		}
		this._drag_delta_x = 0;
		this._drag_delta_y = 0;
	},
	RefreshClipDisLineImpl : function(h_move, v_move) {
		this._scroll_content.ClipRect(0, 0, this._width, this._height, h_move, v_move);
		if (this._static_object_v !== undefined) {
			this._static_object_v.ClipRect(0, 0, this._width, this._height, h_move, v_move);
		}
		if (this._static_object_h !== undefined) {
			this._static_object_h.ClipRect(0, 0, this._width, this._height, h_move, v_move);
		}
		this._clip_loop = undefined;
	},
	RefreshClipDisLine : function(h_move, v_move) {
		if (this._clip_loop !== undefined && this._clip_loop._user_data === undefined) {
			return;
		}
		this._clip_loop = ALittle.NewObject(ALittle.LoopFunction, this.RefreshClipDisLineImpl.bind(this, h_move, v_move), 1, 0, 1);
		this._clip_loop._user_data = v_move;
		A_LoopSystem.AddUpdater(this._clip_loop);
	},
	XScrollBarChange : function() {
		if (this._static_object_h !== undefined) {
			this._static_object_h.x = this._scroll_content.x;
		}
		if (this._bottom_scroll_bar !== undefined) {
			this._bottom_scroll_bar.offset_rate = -this._scroll_content.x / (this._content_width - this._scroll_view.width);
		}
		this.RefreshClipDisLine(undefined, undefined);
	},
	YScrollBarChange : function() {
		if (this._static_object_v !== undefined) {
			this._static_object_v.y = this._scroll_content.y;
		}
		if (this._right_scroll_bar !== undefined) {
			this._right_scroll_bar.offset_rate = -this._scroll_content.y / (this._content_height - this._scroll_view.height);
		}
		this.RefreshClipDisLine(undefined, undefined);
	},
	ScrollDispatchDragDownEvent : function() {
		this.DispatchEvent(___all_struct.get(1848466169), {});
	},
	ScrollDispatchDragUpEvent : function() {
		this.DispatchEvent(___all_struct.get(809518110), {});
	},
	ScrollDispatchDragLeftEvent : function() {
		this.DispatchEvent(___all_struct.get(-567702959), {});
	},
	ScrollDispatchDragRightEvent : function() {
		this.DispatchEvent(___all_struct.get(-839083637), {});
	},
}, "ALittle.ScrollScreen");

}