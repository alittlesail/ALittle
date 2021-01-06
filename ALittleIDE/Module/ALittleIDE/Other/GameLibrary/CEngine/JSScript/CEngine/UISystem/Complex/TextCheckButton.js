{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.TextCheckButton = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._show_text = ({});
		this._show_text.width = 0;
		this._show_text.height = 0;
		this._show_text.text = "";
		this._show_text.x_type = 3;
		this._show_text.x_value = 0;
		this._show_text.visible = true;
		this._show_over_text = ({});
		this._show_over_text.width = 0;
		this._show_over_text.height = 0;
		this._show_over_text.text = "";
		this._show_over_text.x_type = 3;
		this._show_over_text.x_value = 0;
		this._show_over_text.visible = false;
		this._show_down_text = ({});
		this._show_down_text.width = 0;
		this._show_down_text.height = 0;
		this._show_down_text.text = "";
		this._show_down_text.x_type = 3;
		this._show_down_text.x_value = 0;
		this._show_down_text.visible = false;
		this._show_disabled_text = ({});
		this._show_disabled_text.width = 0;
		this._show_disabled_text.height = 0;
		this._show_disabled_text.text = "";
		this._show_disabled_text.x_type = 3;
		this._show_disabled_text.x_value = 0;
		this._show_disabled_text.visible = false;
		this._show_selected_text = ({});
		this._show_selected_text.width = 0;
		this._show_selected_text.height = 0;
		this._show_selected_text.text = "";
		this._show_selected_text.x_type = 3;
		this._show_selected_text.x_value = 0;
		this._show_selected_text.visible = false;
		this._show_selected_over_text = ({});
		this._show_selected_over_text.width = 0;
		this._show_selected_over_text.height = 0;
		this._show_selected_over_text.text = "";
		this._show_selected_over_text.x_type = 3;
		this._show_selected_over_text.x_value = 0;
		this._show_selected_over_text.visible = false;
		this._show_selected_down_text = ({});
		this._show_selected_down_text.width = 0;
		this._show_selected_down_text.height = 0;
		this._show_selected_down_text.text = "";
		this._show_selected_down_text.x_type = 3;
		this._show_selected_down_text.x_value = 0;
		this._show_selected_down_text.visible = false;
		this._show_selected_disabled_text = ({});
		this._show_selected_disabled_text.width = 0;
		this._show_selected_disabled_text.height = 0;
		this._show_selected_disabled_text.text = "";
		this._show_selected_disabled_text.x_type = 3;
		this._show_selected_disabled_text.x_value = 0;
		this._show_selected_disabled_text.visible = false;
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
	set text(value) {
		this._show_text.text = value;
		this._show_over_text.text = value;
		this._show_down_text.text = value;
		this._show_disabled_text.text = value;
		this._show_selected_text.text = value;
		this._show_selected_over_text.text = value;
		this._show_selected_down_text.text = value;
		this._show_selected_disabled_text.text = value;
	},
	get text() {
		return this._show_text.text;
	},
	set text_x_type(value) {
		this._show_text.x_type = value;
		this._show_over_text.x_type = value;
		this._show_down_text.x_type = value;
		this._show_disabled_text.x_type = value;
		this._show_selected_text.x_type = value;
		this._show_selected_over_text.x_type = value;
		this._show_selected_down_text.x_type = value;
		this._show_selected_disabled_text.x_type = value;
	},
	get text_x_type() {
		return this._show_text.x_type;
	},
	set text_x_value(value) {
		this._show_text.x_value = value;
		this._show_over_text.x_value = value;
		this._show_down_text.x_value = value;
		this._show_disabled_text.x_value = value;
		this._show_selected_text.x_value = value;
		this._show_selected_over_text.x_value = value;
		this._show_selected_down_text.x_value = value;
		this._show_selected_disabled_text.x_value = value;
	},
	get text_x_value() {
		return this._show_text.x_value;
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
	HideAllShow : function() {
		if (this._show_selected_up !== undefined) {
			this._show_selected_up.alpha = 0;
		}
		if (this._show_selected_over !== undefined) {
			this._show_selected_over.alpha = 0;
		}
		if (this._show_selected_down !== undefined) {
			this._show_selected_down.alpha = 0;
		}
		if (this._show_selected_disabled !== undefined) {
			this._show_selected_disabled.alpha = 0;
		}
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
			this._show_disabled.alpha = 0;
		}
	},
	ShowUp : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		this.HideAllShow();
		if (this._selected) {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.alpha = 1;
			}
			if (this._show_up !== undefined) {
				this._show_up.alpha = 0;
			}
		} else {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.alpha = 0;
			}
			if (this._show_up !== undefined) {
				this._show_up.alpha = 1;
			}
		}
		if (this._selected) {
			this._show_text.visible = true;
			this._show_down_text.visible = false;
			this._show_over_text.visible = false;
			this._show_disabled_text.visible = false;
			if (this._show_selected_text._show !== undefined) {
				this._show_text.visible = false;
			}
			this._show_selected_text.visible = true;
			this._show_selected_down_text.visible = false;
			this._show_selected_over_text.visible = false;
			this._show_selected_disabled_text.visible = false;
		} else {
			this._show_text.visible = true;
			this._show_down_text.visible = false;
			this._show_over_text.visible = false;
			this._show_disabled_text.visible = false;
			this._show_selected_text.visible = false;
			this._show_selected_down_text.visible = false;
			this._show_selected_over_text.visible = false;
			this._show_selected_disabled_text.visible = false;
		}
	},
	ShowDown : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		this.HideAllShow();
		if (this._selected) {
			if (this._show_selected_down !== undefined) {
				this._show_selected_down.alpha = 1;
			}
			if (this._show_down !== undefined) {
				this._show_down.alpha = 0;
			}
		} else {
			if (this._show_selected_down !== undefined) {
				this._show_selected_down.alpha = 0;
			}
			if (this._show_down !== undefined) {
				this._show_down.alpha = 1;
			}
		}
		if (this._selected) {
			this._show_text.visible = true;
			this._show_down_text.visible = false;
			this._show_over_text.visible = false;
			this._show_disabled_text.visible = false;
			this._show_selected_text.visible = false;
			if (this._show_selected_down_text._show !== undefined) {
				this._show_text.visible = false;
			}
			this._show_selected_down_text.visible = true;
			this._show_selected_over_text.visible = false;
			this._show_selected_disabled_text.visible = false;
		} else {
			this._show_text.visible = true;
			if (this._show_down_text._show !== undefined) {
				this._show_text.visible = false;
			}
			this._show_down_text.visible = true;
			this._show_over_text.visible = false;
			this._show_disabled_text.visible = false;
			this._show_selected_text.visible = false;
			this._show_selected_down_text.visible = false;
			this._show_selected_over_text.visible = false;
			this._show_selected_disabled_text.visible = false;
		}
	},
	ShowOver : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		this.HideAllShow();
		if (this._selected) {
			if (this._show_selected_over !== undefined) {
				this._show_selected_over.alpha = 1;
			}
			if (this._show_over !== undefined) {
				this._show_over.alpha = 0;
			}
		} else {
			if (this._show_selected_over !== undefined) {
				this._show_selected_over.alpha = 0;
			}
			if (this._show_over !== undefined) {
				this._show_over.alpha = 1;
			}
		}
		if (this._selected) {
			this._show_text.visible = true;
			this._show_down_text.visible = false;
			this._show_over_text.visible = false;
			this._show_disabled_text.visible = false;
			this._show_selected_text.visible = false;
			this._show_selected_down_text.visible = false;
			if (this._show_selected_over_text._show !== undefined) {
				this._show_text.visible = false;
			}
			this._show_selected_over_text.visible = true;
			this._show_selected_disabled_text.visible = false;
		} else {
			this._show_text.visible = true;
			this._show_down_text.visible = false;
			if (this._show_over_text._show !== undefined) {
				this._show_text.visible = false;
			}
			this._show_over_text.visible = true;
			this._show_disabled_text.visible = false;
			this._show_selected_text.visible = false;
			this._show_selected_down_text.visible = false;
			this._show_selected_over_text.visible = false;
			this._show_selected_disabled_text.visible = false;
		}
	},
	ShowDisabled : function() {
		this.HideAllShow();
		if (this._selected) {
			if (this._show_selected_disabled !== undefined) {
				this._show_selected_disabled.alpha = 1;
			}
			if (this._show_disabled !== undefined) {
				this._show_disabled.alpha = 0;
			}
		} else {
			if (this._show_selected_disabled !== undefined) {
				this._show_selected_disabled.alpha = 0;
			}
			if (this._show_disabled !== undefined) {
				this._show_disabled.alpha = 1;
			}
		}
		if (this._selected) {
			this._show_text.visible = true;
			this._show_down_text.visible = false;
			this._show_over_text.visible = false;
			this._show_disabled_text.visible = false;
			this._show_selected_text.visible = false;
			this._show_selected_down_text.visible = false;
			this._show_selected_over_text.visible = false;
			if (this._show_selected_disabled_text._show !== undefined) {
				this._show_text.visible = false;
			}
			this._show_selected_disabled_text.visible = true;
		} else {
			this._show_text.visible = true;
			this._show_down_text.visible = false;
			this._show_over_text.visible = false;
			if (this._show_disabled_text._show !== undefined) {
				this._show_text.visible = false;
			}
			this._show_disabled_text.visible = true;
			this._show_selected_text.visible = false;
			this._show_selected_down_text.visible = false;
			this._show_selected_over_text.visible = false;
			this._show_selected_disabled_text.visible = false;
		}
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
		if (this._show_text !== undefined && this._show_text.text !== "") {
			value.text = this._show_text.text;
		}
		value.visible = this._show_text.visible;
		value.x_type = this._show_text.x_type;
		value.x_value = this._show_text.x_value;
		this.RemoveChild(this._show_text);
		this._show_text = value;
		this._show_text.y_type = 3;
		this.AddChild(this._show_text, 10);
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
		if (this._show_over_text !== undefined && this._show_over_text.text !== "") {
			value.text = this._show_over_text.text;
		}
		value.visible = this._show_over_text.visible;
		value.x_type = this._show_over_text.x_type;
		value.x_value = this._show_over_text.x_value;
		this.RemoveChild(this._show_over_text);
		this._show_over_text = value;
		this._show_over_text.y_type = 3;
		this.AddChild(this._show_over_text, 10);
	},
	get show_over_text() {
		if (this._show_over_text._show === undefined) {
			return undefined;
		}
		return this._show_over_text;
	},
	set show_down_text(value) {
		if (value === undefined) {
			let show = this._show_down_text;
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
		if (this._show_down_text !== undefined && this._show_down_text.text !== "") {
			value.text = this._show_down_text.text;
		}
		value.visible = this._show_down_text.visible;
		value.x_type = this._show_down_text.x_type;
		value.x_value = this._show_down_text.x_value;
		this.RemoveChild(this._show_down_text);
		this._show_down_text = value;
		this._show_down_text.y_type = 3;
		this.AddChild(this._show_down_text, 10);
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
		if (this._show_disabled_text !== undefined && this._show_disabled_text.text !== "") {
			value.text = this._show_disabled_text.text;
		}
		value.visible = this._show_disabled_text.visible;
		value.x_type = this._show_disabled_text.x_type;
		value.x_value = this._show_disabled_text.x_value;
		this.RemoveChild(this._show_disabled_text);
		this._show_disabled_text = value;
		this._show_disabled_text.y_type = 3;
		this.AddChild(this._show_disabled_text, 10);
	},
	get show_disabled_text() {
		if (this._show_disabled_text._show === undefined) {
			return undefined;
		}
		return this._show_disabled_text;
	},
	set show_selected_text(value) {
		if (value === undefined) {
			let show = this._show_selected_text;
			this.RemoveChild(show);
			this._show_selected_text = ({});
			this._show_selected_text.width = 0;
			this._show_selected_text.height = 0;
			this._show_selected_text.text = show.text;
			this._show_selected_text.visible = show.visible;
			this._show_selected_text.x_type = show.x_type;
			this._show_selected_text.x_value = show.x_value;
			return;
		}
		if (this._show_selected_text !== undefined && this._show_selected_text.text !== "") {
			value.text = this._show_selected_text.text;
		}
		value.visible = this._show_selected_text.visible;
		value.x_type = this._show_selected_text.x_type;
		value.x_value = this._show_selected_text.x_value;
		this.RemoveChild(this._show_selected_text);
		this._show_selected_text = value;
		this._show_selected_text.y_type = 3;
		this.AddChild(this._show_selected_text, 10);
	},
	get show_selected_text() {
		if (this._show_selected_text._show === undefined) {
			return undefined;
		}
		return this._show_selected_text;
	},
	set show_selected_over_text(value) {
		if (value === undefined) {
			let show = this._show_selected_over_text;
			this.RemoveChild(show);
			this._show_selected_over_text = ({});
			this._show_selected_over_text.width = 0;
			this._show_selected_over_text.height = 0;
			this._show_selected_over_text.text = show.text;
			this._show_selected_over_text.visible = show.visible;
			this._show_selected_over_text.x_type = show.x_type;
			this._show_selected_over_text.x_value = show.x_value;
			return;
		}
		if (this._show_selected_over_text !== undefined && this._show_selected_over_text.text !== "") {
			value.text = this._show_selected_over_text.text;
		}
		value.visible = this._show_selected_over_text.visible;
		value.x_type = this._show_selected_over_text.x_type;
		value.x_value = this._show_selected_over_text.x_value;
		this.RemoveChild(this._show_selected_over_text);
		this._show_selected_over_text = value;
		this._show_selected_over_text.y_type = 3;
		this.AddChild(this._show_selected_over_text, 10);
	},
	get show_selected_over_text() {
		if (this._show_selected_over_text._show === undefined) {
			return undefined;
		}
		return this._show_selected_over_text;
	},
	set show_selected_down_text(value) {
		if (value === undefined) {
			let show = this._show_selected_down_text;
			this.RemoveChild(show);
			this._show_selected_down_text = ({});
			this._show_selected_down_text.width = 0;
			this._show_selected_down_text.height = 0;
			this._show_selected_down_text.text = show.text;
			this._show_selected_down_text.visible = show.visible;
			this._show_selected_down_text.x_type = show.x_type;
			this._show_selected_down_text.x_value = show.x_value;
			return;
		}
		if (this._show_selected_down_text !== undefined && this._show_selected_down_text.text !== "") {
			value.text = this._show_selected_down_text.text;
		}
		value.visible = this._show_selected_down_text.visible;
		value.x_type = this._show_selected_down_text.x_type;
		value.x_value = this._show_selected_down_text.x_value;
		this.RemoveChild(this._show_selected_down_text);
		this._show_selected_down_text = value;
		this._show_selected_down_text.y_type = 3;
		this.AddChild(this._show_selected_down_text, 10);
	},
	get show_selected_down_text() {
		if (this._show_selected_down_text._show === undefined) {
			return undefined;
		}
		return this._show_selected_down_text;
	},
	set show_selected_disabled_text(value) {
		if (value === undefined) {
			let show = this._show_selected_disabled_text;
			this.RemoveChild(show);
			this._show_selected_disabled_text = ({});
			this._show_selected_disabled_text.width = 0;
			this._show_selected_disabled_text.height = 0;
			this._show_selected_disabled_text.text = show.text;
			this._show_selected_disabled_text.visible = show.visible;
			this._show_selected_disabled_text.x_type = show.x_type;
			this._show_selected_disabled_text.x_value = show.x_value;
			return;
		}
		if (this._show_selected_disabled_text !== undefined && this._show_selected_disabled_text.text !== "") {
			value.text = this._show_selected_disabled_text.text;
		}
		value.visible = this._show_selected_disabled_text.visible;
		value.x_type = this._show_selected_disabled_text.x_type;
		value.x_value = this._show_selected_disabled_text.x_value;
		this.RemoveChild(this._show_selected_disabled_text);
		this._show_selected_disabled_text = value;
		this._show_selected_disabled_text.y_type = 3;
		this.AddChild(this._show_selected_disabled_text, 10);
	},
	get show_selected_disabled_text() {
		if (this._show_selected_disabled_text._show === undefined) {
			return undefined;
		}
		return this._show_selected_disabled_text;
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
		this.ShowUp();
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
		this.ShowUp();
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
		this.ShowUp();
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
		this.ShowUp();
	},
	get show_disabled() {
		return this._show_disabled;
	},
	set show_selected_up(value) {
		this.RemoveChild(this._show_selected_up);
		this._show_selected_up = value;
		if (this._show_selected_up !== undefined) {
			this._show_selected_up.width_type = 4;
			this._show_selected_up.height_type = 4;
			this._show_selected_up.width_value = 0;
			this._show_selected_up.height_value = 0;
			this.AddChild(this._show_selected_up, 1);
		}
		this.ShowUp();
	},
	get show_selected_up() {
		return this._show_selected_up;
	},
	set show_selected_down(value) {
		this.RemoveChild(this._show_selected_down);
		this._show_selected_down = value;
		if (this._show_selected_down !== undefined) {
			this._show_selected_down.width_type = 4;
			this._show_selected_down.height_type = 4;
			this._show_selected_down.width_value = 0;
			this._show_selected_down.height_value = 0;
			this.AddChild(this._show_selected_down, 1);
		}
		this.ShowUp();
	},
	get show_selected_down() {
		return this._show_selected_down;
	},
	set show_selected_over(value) {
		this.RemoveChild(this._show_selected_over);
		this._show_selected_over = value;
		if (this._show_selected_over !== undefined) {
			this._show_selected_over.width_type = 4;
			this._show_selected_over.height_type = 4;
			this._show_selected_over.width_value = 0;
			this._show_selected_over.height_value = 0;
			this.AddChild(this._show_selected_over, 1);
		}
		this.ShowUp();
	},
	get show_selected_over() {
		return this._show_selected_over;
	},
	set show_selected_disabled(value) {
		this.RemoveChild(this._show_selected_disabled);
		this._show_selected_disabled = value;
		if (this._show_selected_disabled !== undefined) {
			this._show_selected_disabled.width_type = 4;
			this._show_selected_disabled.height_type = 4;
			this._show_selected_disabled.width_value = 0;
			this._show_selected_disabled.height_value = 0;
			this.AddChild(this._show_selected_disabled, 1);
		}
		this.ShowUp();
	},
	get show_selected_disabled() {
		return this._show_selected_disabled;
	},
}, "ALittle.TextCheckButton");

}