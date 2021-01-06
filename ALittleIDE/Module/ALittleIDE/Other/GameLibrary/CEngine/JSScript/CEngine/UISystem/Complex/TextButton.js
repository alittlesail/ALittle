{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.TextButton = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._show_text = ({});
		this._show_text.width = 0;
		this._show_text.height = 0;
		this._show_text.text = "";
		this._show_text.x_type = 3;
		this._show_text.x_value = 0;
		this._show_text.visible = true;
		this._show_down_text = ({});
		this._show_down_text.width = 0;
		this._show_down_text.height = 0;
		this._show_down_text.text = "";
		this._show_down_text.x_type = 3;
		this._show_down_text.x_value = 0;
		this._show_down_text.visible = false;
		this._show_over_text = ({});
		this._show_over_text.width = 0;
		this._show_over_text.height = 0;
		this._show_over_text.text = "";
		this._show_over_text.x_type = 3;
		this._show_over_text.x_value = 0;
		this._show_over_text.visible = false;
		this._show_disabled_text = ({});
		this._show_disabled_text.width = 0;
		this._show_disabled_text.height = 0;
		this._show_disabled_text.text = "";
		this._show_disabled_text.x_type = 3;
		this._show_disabled_text.x_value = 0;
		this._show_disabled_text.visible = false;
		this._file_select = 0;
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
			if (this._file_select === 1) {
				A_OtherSystem.SystemSelectFile(this);
			} else if (this._file_select === 2) {
				A_OtherSystem.SystemSelectDirectory(this);
			}
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
	set text(value) {
		this._show_text.text = value;
		this._show_over_text.text = value;
		this._show_disabled_text.text = value;
		this._show_down_text.text = value;
	},
	get text() {
		return this._show_text.text;
	},
	set text_x_type(value) {
		this._show_text.x_type = value;
		this._show_over_text.x_type = value;
		this._show_disabled_text.x_type = value;
		this._show_down_text.x_type = value;
	},
	get text_x_type() {
		return this._show_text.x_type;
	},
	set text_x_value(value) {
		this._show_text.x_value = value;
		this._show_over_text.x_value = value;
		this._show_disabled_text.x_value = value;
		this._show_down_text.x_value = value;
	},
	get text_x_value() {
		return this._show_text.x_value;
	},
	ShowUp : function(event) {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 1;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 0;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
		this._show_text.visible = true;
		this._show_down_text.visible = false;
		this._show_over_text.visible = false;
		this._show_disabled_text.visible = false;
	},
	ShowDown : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 0;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 1;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
		this._show_text.visible = true;
		if (this._show_down_text._show !== undefined) {
			this._show_text.visible = false;
		}
		this._show_down_text.visible = true;
		this._show_over_text.visible = false;
		this._show_disabled_text.visible = false;
	},
	ShowOver : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 1;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
		this._show_text.visible = true;
		if (this._show_over_text._show !== undefined) {
			this._show_text.visible = false;
		}
		this._show_down_text.visible = false;
		this._show_over_text.visible = true;
		this._show_disabled_text.visible = false;
	},
	ShowDisabled : function() {
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 0;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 1;
		}
		this._show_text.visible = true;
		if (this._show_disabled_text._show !== undefined) {
			this._show_text.visible = false;
		}
		this._show_disabled_text.visible = true;
		this._show_over_text.visible = false;
		this._show_down_text.visible = false;
	},
	set show_text(value) {
		if (value === undefined) {
			let show = this._show_text;
			this.RemoveChild(show);
			this._show_text = ({});
			this._show_text.width = 0;
			this._show_text.height = 0;
			this._show_text.text = show.text;
			this._show_text.visible = show.visible;
			this._show_text.x_type = show.x_type;
			this._show_text.x_value = show.x_value;
			return;
		}
		value.text = this._show_text.text;
		value.visible = this._show_text.visible;
		value.x_type = this._show_text.x_type;
		value.x_value = this._show_text.x_value;
		this.RemoveChild(this._show_text);
		this._show_text = value;
		this._show_text.y_type = 3;
		this.AddChild(this._show_text, 6);
	},
	get show_text() {
		if (this._show_text._show === undefined) {
			return undefined;
		}
		return this._show_text;
	},
	set show_over_text(value) {
		if (value === undefined) {
			let show = this._show_over_text;
			this.RemoveChild(show);
			this._show_over_text = ({});
			this._show_over_text.width = 0;
			this._show_over_text.height = 0;
			this._show_over_text.text = show.text;
			this._show_over_text.visible = show.visible;
			this._show_over_text.x_type = show.x_type;
			this._show_over_text.x_value = show.x_value;
			return;
		}
		value.text = this._show_over_text.text;
		value.visible = this._show_over_text.visible;
		value.x_type = this._show_over_text.x_type;
		value.x_value = this._show_over_text.x_value;
		this.RemoveChild(this._show_over_text);
		this._show_over_text = value;
		this._show_over_text.y_type = 3;
		this.AddChild(this._show_over_text, 6);
	},
	get show_over_text() {
		if (this._show_over_text._show === undefined) {
			return undefined;
		}
		return this._show_over_text;
	},
	set show_down_text(value) {
		if (value === undefined) {
			let show = this.show_down_text;
			this.RemoveChild(show);
			this._show_down_text = ({});
			this._show_down_text.width = 0;
			this._show_down_text.height = 0;
			this._show_down_text.text = show.text;
			this._show_down_text.visible = show.visible;
			this._show_down_text.x_type = show.x_type;
			this._show_down_text.x_value = show.x_value;
			return;
		}
		value.text = this._show_down_text.text;
		value.visible = this._show_down_text.visible;
		value.x_type = this._show_down_text.x_type;
		value.x_value = this._show_down_text.x_value;
		this.RemoveChild(this._show_down_text);
		this._show_down_text = value;
		this._show_down_text.y_type = 3;
		this.AddChild(this._show_down_text, 6);
	},
	get show_down_text() {
		if (this._show_down_text._show === undefined) {
			return undefined;
		}
		return this._show_down_text;
	},
	set show_disabled_text(value) {
		if (value === undefined) {
			let show = this._show_disabled_text;
			this.RemoveChild(show);
			this._show_disabled_text = ({});
			this._show_disabled_text.width = 0;
			this._show_disabled_text.height = 0;
			this._show_disabled_text.text = show.text;
			this._show_disabled_text.visible = show.visible;
			this._show_disabled_text.x_type = show.x_type;
			this._show_disabled_text.x_value = show.x_value;
			return;
		}
		value.text = this._show_disabled_text.text;
		value.visible = this._show_disabled_text.visible;
		value.x_type = this._show_disabled_text.x_type;
		value.x_value = this._show_disabled_text.x_value;
		this.RemoveChild(this._show_disabled_text);
		this._show_disabled_text = value;
		this._show_disabled_text.y_type = 3;
		this.AddChild(this._show_disabled_text, 6);
	},
	get show_disabled_text() {
		if (this._show_disabled_text._show === undefined) {
			return undefined;
		}
		return this._show_disabled_text;
	},
	set show_up(value) {
		this.RemoveChild(this._show_up);
		this._show_up = value;
		if (this._show_up !== undefined) {
			this._show_up.width_type = 4;
			this._show_up.height_type = 4;
			this._show_up.width_value = 0;
			this._show_up.height_value = 0;
			this.AddChild(this._show_up, 1);
		}
		if (this._abs_disabled || this._disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp(undefined);
		}
	},
	get show_up() {
		return this._show_up;
	},
	set show_down(value) {
		this.RemoveChild(this._show_down);
		this._show_down = value;
		if (this._show_down !== undefined) {
			this._show_down.width_type = 4;
			this._show_down.height_type = 4;
			this._show_down.width_value = 0;
			this._show_down.height_value = 0;
			this.AddChild(this._show_down, 1);
		}
		if (this._abs_disabled || this._disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp(undefined);
		}
	},
	get show_down() {
		return this._show_down;
	},
	set show_over(value) {
		this.RemoveChild(this._show_over);
		this._show_over = value;
		if (this._show_over !== undefined) {
			this._show_over.width_type = 4;
			this._show_over.height_type = 4;
			this._show_over.width_value = 0;
			this._show_over.height_value = 0;
			this.AddChild(this._show_over, 1);
		}
		if (this._abs_disabled || this._disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp(undefined);
		}
	},
	get show_over() {
		return this._show_over;
	},
	set show_disabled(value) {
		this.RemoveChild(this._show_disabled);
		this._show_disabled = value;
		if (this._show_disabled !== undefined) {
			this._show_disabled.width_type = 4;
			this._show_disabled.height_type = 4;
			this._show_disabled.width_value = 0;
			this._show_disabled.height_value = 0;
			this.AddChild(this._show_disabled, 1);
		}
		if (this._abs_disabled || this._disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp(undefined);
		}
	},
	get show_disabled() {
		return this._show_disabled;
	},
	set file_select(value) {
		this._file_select = value;
	},
	get file_select() {
		return this._file_select;
	},
}, "ALittle.TextButton");

}