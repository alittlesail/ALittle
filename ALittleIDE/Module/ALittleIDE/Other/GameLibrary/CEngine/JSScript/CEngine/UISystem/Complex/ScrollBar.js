{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.Grid3 === undefined) throw new Error(" extends class:ALittle.Grid3 is undefined");
ALittle.ScrollBar = JavaScript.Class(ALittle.Grid3, {
	Ctor : function(ctrl_sys) {
		this._bar_container = ALittle.NewObject(ALittle.DisplayGroup, this._ctrl_sys);
		this.show_center = this._bar_container;
		this._offset_step = 0;
		this._offset_rate = 0;
		this._show_size = 0;
		this._center_size = 0;
		this._logic_total_size = 0;
		this._logic_show_size = 0;
		this._drag_point_rate = 0;
		this._pickup_rect = true;
		this._pickup_child = true;
	},
	set type(value) {
		ALittle.Grid3.__setter.type.call(this, value);
		this.UpdateShowSize();
		this.AdjustBarButton();
	},
	set up_size(value) {
		ALittle.Grid3.__setter.up_size.call(this, value);
		this.UpdateShowSize();
		this.AdjustBarButton();
	},
	set down_size(value) {
		ALittle.Grid3.__setter.down_size.call(this, value);
		this.UpdateShowSize();
		this.AdjustBarButton();
	},
	set gap(value) {
		ALittle.Grid3.__setter.gap.call(this, value);
		this.UpdateShowSize();
		this.AdjustBarButton();
	},
	set total_size(value) {
		this._logic_total_size = value;
		this.UpdateShowSize();
		this.AdjustBarButton();
	},
	get total_size() {
		return this._logic_total_size;
	},
	set show_size(value) {
		this._logic_show_size = value;
		this.UpdateShowSize();
		this.AdjustBarButton();
	},
	get show_size() {
		return this._logic_show_size;
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
	set offset_step(value) {
		this._offset_step = value;
	},
	get offset_step() {
		return this._offset_step;
	},
	UpdateShowSize : function() {
		this._show_size = 0;
		this._center_size = this.center_size;
		if (this._logic_show_size < this._logic_total_size) {
			this._show_size = this._logic_show_size / this._logic_total_size * this._center_size;
		}
	},
	SetToDown : function() {
		this._offset_rate = 1;
		this.AdjustBarButton();
	},
	set width(value) {
		if (this._width === value) {
			return;
		}
		ALittle.Grid3.__setter.width.call(this, value);
		this.UpdateShowSize();
		this.AdjustBarButton();
	},
	set height(value) {
		if (this._height === value) {
			return;
		}
		ALittle.Grid3.__setter.height.call(this, value);
		this.UpdateShowSize();
		this.AdjustBarButton();
	},
	set up_button(value) {
		if (this._up_button !== undefined) {
			this._up_button.RemoveEventListener(___all_struct.get(-449066808), this, this.HandleUpButtonClick);
		}
		this._up_button = value;
		this.show_up = value;
		if (value !== undefined) {
			value.AddEventListener(___all_struct.get(-449066808), this, this.HandleUpButtonClick);
		}
	},
	get up_button() {
		return this._up_button;
	},
	HandleUpButtonClick : function(event) {
		this._offset_rate = this._offset_rate - this._offset_step;
		if (this._offset_rate < 0) {
			this._offset_rate = 0;
		}
		if (this._bar_button !== undefined) {
			let offset = this._offset_rate * (this._center_size - this._show_size);
			if (this._type === 2) {
				this._bar_button.y = offset;
			} else {
				this._bar_button.x = offset;
			}
		}
		this.DispatchEvent(___all_struct.get(958494922), {});
		this.DispatchEvent(___all_struct.get(1309977874), {});
	},
	set down_button(value) {
		if (this._down_button !== undefined) {
			this._down_button.RemoveEventListener(___all_struct.get(-449066808), this, this.HandleDownButtonClick);
		}
		this._down_button = value;
		this.show_down = value;
		if (value !== undefined) {
			value.AddEventListener(___all_struct.get(-449066808), this, this.HandleDownButtonClick);
		}
	},
	get down_button() {
		return this._down_button;
	},
	HandleDownButtonClick : function(event) {
		this._offset_rate = this._offset_rate + this._offset_step;
		if (this._offset_rate > 1) {
			this._offset_rate = 1;
		}
		if (this._bar_button !== undefined) {
			let offset = this._offset_rate * (this._center_size - this._show_size);
			if (this._type === 2) {
				this._bar_button.y = offset;
			} else {
				this._bar_button.x = offset;
			}
		}
		this.DispatchEvent(___all_struct.get(958494922), {});
		this.DispatchEvent(___all_struct.get(1309977874), {});
	},
	set bar_button(value) {
		if (this._bar_button !== undefined) {
			this._bar_button.RemoveEventListener(___all_struct.get(1337289812), this, this.HandleBarButtonDrag);
			this._bar_button.RemoveEventListener(___all_struct.get(1301789264), this, this.HandleBarButtonDragBegin);
			this._bar_button.RemoveEventListener(___all_struct.get(150587926), this, this.HandleBarButtonDragEnd);
			this._bar_button.RemoveEventListener(___all_struct.get(-1737121315), this, this.HandleBarButtonScroll);
			this._bar_container.RemoveChild(this._bar_button);
		}
		this._bar_button = value;
		if (value !== undefined) {
			this._bar_container.AddChild(value);
			value.AddEventListener(___all_struct.get(1337289812), this, this.HandleBarButtonDrag);
			value.AddEventListener(___all_struct.get(1301789264), this, this.HandleBarButtonDragBegin);
			value.AddEventListener(___all_struct.get(150587926), this, this.HandleBarButtonDragEnd);
			value.AddEventListener(___all_struct.get(-1737121315), this, this.HandleBarButtonScroll);
		}
		this.AdjustBarButton();
	},
	get bar_button() {
		return this._bar_button;
	},
	set bar_background(value) {
		if (this._bar_background !== undefined) {
			this._bar_container.RemoveChild(this._bar_background);
		}
		this._bar_background = value;
		if (value !== undefined) {
			this._bar_container.AddChild(value, 1);
		}
		this.AdjustBarButton();
	},
	get bar_background() {
		return this._bar_background;
	},
	HandleBarButtonDragBegin : function(event) {
		if (this._type === 2) {
			let height = this._bar_button.height;
			this._drag_point_rate = 0;
			if (height > 0) {
				this._drag_point_rate = event.rel_y / height;
			}
		} else {
			let width = this._bar_button.width;
			this._drag_point_rate = 0;
			if (width > 0) {
				this._drag_point_rate = event.rel_x / width;
			}
		}
	},
	HandleBarButtonScroll : function(event) {
		if (this._type === 2) {
			if (event.delta_y > 0) {
				this.HandleUpButtonClick(undefined);
			} else if (event.delta_y < 0) {
				this.HandleDownButtonClick(undefined);
			}
		} else {
			if (event.delta_x > 0) {
				this.HandleUpButtonClick(undefined);
			} else if (event.delta_x < 0) {
				this.HandleDownButtonClick(undefined);
			}
		}
	},
	HandleBarButtonDragEnd : function(event) {
		this.DispatchEvent(___all_struct.get(1309977874), {});
	},
	HandleBarButtonDrag : function(event) {
		let real_size = this._center_size - this._show_size;
		if (this._type === 2) {
			if ((event.delta_y > 0 && event.rel_y < this._show_size * this._drag_point_rate) || (event.delta_y < 0 && event.rel_y > this._show_size * this._drag_point_rate)) {
				return;
			}
			let offset = (this._bar_button.y + event.delta_y) / real_size;
			if (offset > 1) {
				offset = 1;
			} else if (offset < 0) {
				offset = 0;
			}
			if (this._offset_rate === offset) {
				return;
			}
			this._offset_rate = offset;
			this._bar_button.y = this._offset_rate * real_size;
		} else {
			if ((event.delta_x > 0 && event.rel_x < this._show_size * this._drag_point_rate) || (event.delta_x < 0 && event.rel_x > this._show_size * this._drag_point_rate)) {
				return;
			}
			let offset = (this._bar_button.x + event.delta_x) / real_size;
			if (offset > 1) {
				offset = 1;
			} else if (offset < 0) {
				offset = 0;
			}
			if (this._offset_rate === offset) {
				return;
			}
			this._offset_rate = offset;
			this._bar_button.x = this._offset_rate * real_size;
		}
		this.DispatchEvent(___all_struct.get(958494922), {});
	},
	AdjustBarButton : function() {
		let real_size = this._center_size - this._show_size;
		if (this._type === 2) {
			if (this._bar_button !== undefined) {
				this._bar_button.x = 0;
				this._bar_button.width = this._width;
				this._bar_button.y = this._offset_rate * real_size;
				this._bar_button.height = this._show_size;
			}
			if (this._bar_background !== undefined) {
				this._bar_background.x = 0;
				this._bar_background.y = 0;
				this._bar_background.width = this._width;
				this._bar_background.height = this._center_size;
			}
		} else {
			if (this._bar_button !== undefined) {
				this._bar_button.x = this._offset_rate * real_size;
				this._bar_button.width = this._show_size;
				this._bar_button.y = 0;
				this._bar_button.height = this._height;
			}
			if (this._bar_background !== undefined) {
				this._bar_background.x = 0;
				this._bar_background.y = 0;
				this._bar_background.width = this._center_size;
				this._bar_background.height = this._height;
			}
		}
	},
}, "ALittle.ScrollBar");

}