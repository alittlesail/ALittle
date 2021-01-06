{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __cos = ALittle.Math_Cos;
let __sin = ALittle.Math_Sin;
if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.ImageInput = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._show_input = ALittle.NewObject(ALittle.TextInput, this._ctrl_sys);
		this._show_input.x_type = 2;
		this._show_input.y_type = 2;
		this._show_input.width_type = 4;
		this._show_input.width_value = 0;
		this._show_input.height_type = 4;
		this._show_input.height_value = 0;
		this.AddChild(this._show_input, 5);
		this._logic_left = 0;
		this._logic_right = 0;
		this._logic_top = 0;
		this._logic_bottom = 0;
		this._ims_padding = 0;
		this._show_disabled = undefined;
		this._pickup_this = true;
		this._show_input.AddEventListener(___all_struct.get(-644464135), this, this.HandleFocusIn);
		this._show_input.AddEventListener(___all_struct.get(292776509), this, this.HandleFocusOut);
		this._show_input.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this._show_input.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this._show_input.AddEventListener(___all_struct.get(1883782801), this, this.HandleImageInputTransformLButtonDown);
		this._show_input.AddEventListener(___all_struct.get(-1234078962), this, this.HandleImageInputTransformTextInput);
		this._show_input.AddEventListener(___all_struct.get(-1604617962), this, this.HandleImageInputTransformKeyDown);
		this._show_input.AddEventListener(___all_struct.get(1301789264), this, this.HandleImageInputTransformDragBegin);
		this._show_input.AddEventListener(___all_struct.get(1337289812), this, this.HandleImageInputTransformDrag);
		this._show_input.AddEventListener(___all_struct.get(150587926), this, this.HandleImageInputTransformDragEnd);
		this._show_input.AddEventListener(___all_struct.get(-1737121315), this, this.HandleImageInputTransformMButtonWheel);
		this._show_input.AddEventListener(___all_struct.get(958494922), this, this.HandleImageInputTransformChangd);
		this._show_input.AddEventListener(___all_struct.get(776398171), this, this.HandleImageInputTransformEnterKey);
		this._show_input.AddEventListener(___all_struct.get(2024735182), this, this.HandleImageInputTransformTabKey);
		this._show_input.AddEventListener(___all_struct.get(1637310579), this, this.HandleImageInputTransformEscKey);
		this._show_input.AddEventListener(___all_struct.get(-641444818), this, this.HandleImageInputTransformRButtonDown);
		this._show_input.AddEventListener(___all_struct.get(-569321214), this, this.HandleImageInputTransformRButtonUp);
		this._show_input.AddEventListener(___all_struct.get(-439548260), this, this.HandleImageInputTransformLongButtonDown);
	},
	set disabled(value) {
		ALittle.DisplayObject.__setter.disabled.call(this, value);
		if (value) {
			this.ShowDisabled();
		} else {
			this.ShowUp();
		}
	},
	get is_focus() {
		return A_UISystem.focus === this._show_input;
	},
	set focus(value) {
		if (value) {
			A_UISystem.focus = this._show_input;
		} else {
			if (A_UISystem.focus === this._show_input) {
				A_UISystem.focus = undefined;
			}
		}
	},
	get is_input() {
		return true;
	},
	get regex() {
		return this._show_input.regex;
	},
	set regex(value) {
		if (value === undefined) {
			value = "";
		}
		this._show_input.regex = value;
	},
	get limit_len() {
		return this._show_input.limit_len;
	},
	set limit_len(value) {
		if (value === undefined) {
			value = 0;
		}
		this._show_input.limit_len = value;
	},
	set default_text(value) {
		this._show_input.default_text = value;
	},
	get default_text() {
		return this._show_input.default_text;
	},
	set default_text_alpha(value) {
		this._show_input.default_text_alpha = value;
	},
	get default_text_alpha() {
		return this._show_input.default_text_alpha;
	},
	get cursor_x() {
		return this._show_input.cursor_x;
	},
	get cursor_y() {
		return this._show_input.cursor_y;
	},
	set editable(value) {
		this._show_input.editable = value;
	},
	get editable() {
		return this._show_input.editable;
	},
	set font_path(value) {
		this._show_input.font_path = value;
	},
	set font_size(value) {
		this._show_input.font_size = value;
	},
	get font_path() {
		return this._show_input.font_path;
	},
	get font_size() {
		return this._show_input.font_size;
	},
	set text(value) {
		this._show_input.text = value;
	},
	get text() {
		return this._show_input.text;
	},
	set bold(value) {
		this._show_input.bold = value;
	},
	get bold() {
		return this._show_input.bold;
	},
	set italic(value) {
		this._show_input.italic = value;
	},
	get italic() {
		return this._show_input.italic;
	},
	set underline(value) {
		this._show_input.underline = value;
	},
	get underline() {
		return this._show_input.underline;
	},
	set deleteline(value) {
		this._show_input.deleteline = value;
	},
	get deleteline() {
		return this._show_input.deleteline;
	},
	set password_mode(value) {
		this._show_input.password_mode = value;
	},
	get password_mode() {
		return this._show_input.password_mode;
	},
	set cursor_red(value) {
		this._show_input.cursor_red = value;
	},
	get cursor_red() {
		return this._show_input.cursor_red;
	},
	set cursor_green(value) {
		this._show_input.cursor_green = value;
	},
	get cursor_green() {
		return this._show_input.cursor_green;
	},
	set cursor_blue(value) {
		this._show_input.cursor_blue = value;
	},
	get cursor_blue() {
		return this._show_input.cursor_blue;
	},
	set red(value) {
		this._show_input.red = value;
	},
	get red() {
		return this._show_input.red;
	},
	set green(value) {
		this._show_input.green = value;
	},
	get green() {
		return this._show_input.green;
	},
	set blue(value) {
		this._show_input.blue = value;
	},
	get blue() {
		return this._show_input.blue;
	},
	set ims_padding(value) {
		this._ims_padding = value;
		this._show_input.ims_padding = ALittle.Math_Floor(value + this._logic_bottom);
	},
	get ims_padding() {
		return this._ims_padding;
	},
	HandleFocusIn : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-644464135), event);
		this.ShowDown();
	},
	HandleFocusOut : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(292776509), event);
		this.ShowUp();
	},
	HandleImageInputTransformLButtonDown : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(1883782801), event);
	},
	HandleImageInputTransformTextInput : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-1234078962), event);
	},
	HandleImageInputTransformKeyDown : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-1604617962), event);
	},
	HandleImageInputTransformDragBegin : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(1301789264), event);
	},
	HandleImageInputTransformDrag : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(1337289812), event);
	},
	HandleImageInputTransformDragEnd : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(150587926), event);
	},
	HandleImageInputTransformMButtonWheel : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-1737121315), event);
	},
	HandleImageInputTransformChangd : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(958494922), event);
	},
	HandleImageInputTransformEnterKey : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(776398171), event);
	},
	HandleImageInputTransformTabKey : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(2024735182), event);
	},
	HandleImageInputTransformEscKey : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(1637310579), event);
	},
	HandleImageInputTransformRButtonDown : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-641444818), event);
	},
	HandleImageInputTransformRButtonUp : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-569321214), event);
	},
	HandleImageInputTransformLongButtonDown : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-439548260), event);
	},
	HandleMoveIn : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(544684311), event);
		if (A_UISystem.focus !== this._show_input) {
			this.ShowOver();
		}
	},
	HandleMoveOut : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-1202439334), event);
		if (A_UISystem.focus !== this._show_input) {
			this.ShowUp();
		}
	},
	ShowUp : function() {
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
	},
	set show_up(value) {
		this.RemoveChild(this._show_up);
		this._show_up = value;
		if (this._show_up !== undefined) {
			this._show_up.width_type = 4;
			this._show_up.height_type = 4;
			this._show_up.width_value = 0;
			this._show_up.height_value = 0;
			this._show_up.disabled = true;
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
			this._show_down.disabled = true;
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
			this._show_over.disabled = true;
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
			this._show_disabled.disabled = true;
			this.AddChild(this._show_disabled, 1);
		}
		this.ShowUp();
	},
	get show_disabled() {
		return this._show_disabled;
	},
	get show_input() {
		return this._show_input;
	},
	set margin_left(value) {
		this._logic_left = value;
		this.Layout();
	},
	get margin_left() {
		return this._logic_left;
	},
	set margin_right(value) {
		this._logic_right = value;
		this.Layout();
	},
	get margin_right() {
		return this._logic_right;
	},
	set margin_top(value) {
		this._logic_top = value;
		this.Layout();
	},
	get margin_top() {
		return this._logic_top;
	},
	set margin_bottom(value) {
		this._logic_bottom = value;
		this.Layout();
		this._show_input.ims_padding = ALittle.Math_Floor(this._ims_padding + this._logic_bottom);
	},
	get margin_bottom() {
		return this._logic_bottom;
	},
	Layout : function() {
		this.SetChildIndex(this._show_input, 5);
		this._show_input.x_value = this._logic_left;
		this._show_input.y_value = this._logic_top;
		this._show_input.width_value = this._logic_left + this._logic_right;
		this._show_input.height_value = this._logic_top + this._logic_bottom;
	},
	PickUp : function(x, y) {
		if (this._ignore || this._abs_disabled || this._abs_visible === false) {
			return [undefined, undefined, undefined];
		}
		let xx = x - this._x;
		let yy = y - this._y;
		if (this._angle !== 0) {
			let rad = 3.1415926 * -this._angle / 180.0;
			let cos = __cos(rad);
			let sin = __sin(rad);
			let xxx = xx * cos + yy * -sin;
			let yyy = xx * sin + yy * cos;
			xx = xxx;
			yy = yyy;
		}
		if (this._scale_x > 0) {
			xx = xx / (this._scale_x);
		}
		if (this._scale_y > 0) {
			yy = yy / (this._scale_y);
		}
		let rel_x = xx + this._center_x;
		let rel_y = yy + this._center_y;
		if (this._scale_x <= 0 || this._scale_y <= 0) {
			if (this._modal) {
				return [this, rel_x, rel_y];
			}
			return [undefined, rel_x, rel_y];
		}
		if (this._pickup_rect && (rel_x < 0 || rel_y < 0 || rel_x >= this._width || rel_y >= this._height)) {
			if (this._modal) {
				return [this, rel_x, rel_y];
			}
			return [undefined, undefined, undefined];
		}
		if (this._pickup_child) {
			let [v_focus, v_x, v_y] = this._show_input.PickUp(rel_x, rel_y);
			return [this._show_input, v_x, v_y];
		}
		if (this._modal || (this._pickup_rect && this._pickup_child === false) || this._pickup_this) {
			return [this, rel_x, rel_y];
		}
		return [undefined, undefined, undefined];
	},
	SetCursorToHome : function() {
		this._show_input.SetCursorToHome();
	},
	SetCursorToEnd : function() {
		this._show_input.SetCursorToEnd();
	},
	SelectAll : function() {
		this._show_input.SelectAll();
	},
	CopyText : function() {
		this._show_input.CopyText();
	},
	PasteText : function() {
		this._show_input.PasteText();
	},
	CutText : function() {
		this._show_input.CutText();
	},
	InsertText : function(text) {
		this._show_input.InsertText(text);
	},
}, "ALittle.ImageInput");

}