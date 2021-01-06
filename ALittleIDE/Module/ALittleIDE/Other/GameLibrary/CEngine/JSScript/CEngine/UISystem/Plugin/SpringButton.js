{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.SpringButton = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._big_or_small = false;
		this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(349963892), this, this.HandleMButtonDown);
		this.AddEventListener(___all_struct.get(683647260), this, this.HandleMButtonUp);
		this.AddEventListener(___all_struct.get(292776509), this, this.ShowUp);
		this.AddEventListener(___all_struct.get(-1233353463), this, this.HandleFButtonDown);
		this.AddEventListener(___all_struct.get(734860930), this, this.HandleFButtonUp);
		this._pickup_rect = true;
		this._pickup_child = false;
	},
	get text() {
		if (this._show_text === undefined) {
			return "";
		}
		return this._show_text.text;
	},
	set text(text) {
		if (this._show_text === undefined) {
			return;
		}
		this._show_text.text = text;
	},
	set disabled(value) {
		ALittle.DisplayObject.__setter.disabled.call(this, value);
		if (value) {
			this.ShowDisabled();
		} else {
			this.ShowUp(undefined);
		}
	},
	HandleMoveIn : function(event) {
		this.ShowOver();
	},
	HandleMoveOut : function(event) {
		this.ShowUp(undefined);
	},
	HandleLButtonDown : function(event) {
		this.ShowDown();
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			e.count = event.count;
			this.DispatchEvent(___all_struct.get(-449066808), e);
			if (ALittle.System_IsPhone() === false) {
				this.ShowOver();
			} else {
				this.ShowUp(undefined);
			}
		} else {
			this.ShowUp(undefined);
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
				this.ShowUp(undefined);
			}
		} else {
			this.ShowUp(undefined);
		}
	},
	HandleFButtonDown : function(event) {
		if (event.is_sfc === false) {
			this.ShowDown();
		}
	},
	HandleFButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(286797479), e);
		}
		if (event.is_sfc === false) {
			this.ShowUp(undefined);
		}
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
	ShowUp : function(event) {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.visible = true;
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
		if (this._show_up !== undefined) {
			this._show_up.visible = true;
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
		if (this._show_up !== undefined) {
			this._show_up.visible = true;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.visible = false;
		}
		this.ScaleTo(false, 200);
	},
	ShowDisabled : function() {
		this.ScaleTo(false, 200);
		if (this._show_up !== undefined) {
			this._show_up.visible = false;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.visible = true;
		} else {
			this._show_up.visible = true;
		}
	},
}, "ALittle.SpringButton");

}