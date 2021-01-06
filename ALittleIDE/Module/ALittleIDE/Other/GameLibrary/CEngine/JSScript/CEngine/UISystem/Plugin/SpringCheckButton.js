{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.SpringCheckButton = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._big_or_small = false;
		this._selected = false;
		this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(349963892), this, this.HandleMButtonDown);
		this.AddEventListener(___all_struct.get(683647260), this, this.HandleMButtonUp);
		this._pickup_rect = true;
		this._pickup_child = false;
	},
	set disabled(value) {
		ALittle.DisplayObject.__setter.disabled.call(this, value);
		if (this._abs_disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp();
		}
	},
	HandleMoveIn : function(event) {
		this.ShowOver();
	},
	HandleMoveOut : function(event) {
		this.ShowUp();
	},
	HandleLButtonDown : function(event) {
		this.ShowDown();
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			this._selected = (this._selected === false);
			let e = {};
			e.is_drag = event.is_drag;
			e.count = event.count;
			this.DispatchEvent(___all_struct.get(-449066808), e);
			this.DispatchEvent(___all_struct.get(958494922), {});
			if (ALittle.System_IsPhone() === false) {
				this.ShowOver();
			} else {
				this.ShowUp();
			}
		} else {
			this.ShowUp();
		}
	},
	HandleMButtonDown : function(event) {
		this.ShowDown();
	},
	HandleMButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-1330840), e);
			if (ALittle.System_IsPhone() === false) {
				this.ShowOver();
			} else {
				this.ShowUp();
			}
		} else {
			this.ShowUp();
		}
	},
	set selected(value) {
		if (this._selected === value) {
			return;
		}
		this._selected = value;
		if (this._abs_disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp();
		}
	},
	get selected() {
		return this._selected;
	},
	ScaleTo : function(big_or_small, time_in_ms) {
		if (this._big_or_small === big_or_small) {
			return;
		}
		this._big_or_small = big_or_small;
		let scale = 1.0;
		if (this._big_or_small) {
			scale = 1.2;
		}
		if (this._anti_loop !== undefined) {
			this._anti_loop.Stop();
			this._anti_loop = undefined;
		}
		this._anti_loop = ALittle.NewObject(ALittle.LoopGroup);
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "scale_x", scale, time_in_ms, 1));
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "scale_y", scale, time_in_ms, 1));
		this._anti_loop.Start();
	},
	ShowUp : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._selected) {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.visible = true;
			}
			if (this._show_up !== undefined) {
				this._show_up.visible = false;
			}
		} else {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.visible = false;
			}
			if (this._show_up !== undefined) {
				this._show_up.visible = true;
			}
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.visible = false;
		}
		this.ScaleTo(false, 200);
	},
	ShowDown : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._selected) {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.visible = true;
			}
			if (this._show_up !== undefined) {
				this._show_up.visible = false;
			}
		} else {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.visible = false;
			}
			if (this._show_up !== undefined) {
				this._show_up.visible = true;
			}
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.visible = false;
		}
		this.ScaleTo(true, 200);
	},
	ShowOver : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._selected) {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.visible = true;
			}
			if (this._show_up !== undefined) {
				this._show_up.visible = false;
			}
		} else {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.visible = false;
			}
			if (this._show_up !== undefined) {
				this._show_up.visible = true;
			}
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
		this.ScaleTo(false, 200);
	},
	ShowDisabled : function() {
		this.ScaleTo(false, 200);
		if (this._show_up !== undefined) {
			this._show_up.visible = false;
		}
		if (this._show_selected_up !== undefined) {
			this._show_selected_up.visible = false;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.visible = true;
		} else {
			if (this._selected) {
				this._show_selected_up.visible = true;
			} else {
				this._show_up.visible = true;
			}
		}
	},
}, "ALittle.SpringCheckButton");

}