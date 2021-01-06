{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.TextCheckButton === undefined) throw new Error(" extends class:ALittle.TextCheckButton is undefined");
ALittle.DropDown = JavaScript.Class(ALittle.TextCheckButton, {
	Ctor : function(ctrl_sys) {
		this._body = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
		this._body.__right_data = this;
		this._body.visible = false;
		this._linear = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
		this._linear.type = 2;
		this._linear.width_type = 4;
		this._linear.width_value = 0;
		this._linear.height_type = 4;
		this._linear.height_value = 0;
		this._scroll_screen = ALittle.NewObject(ALittle.ScrollScreen, this._ctrl_sys);
		this._scroll_screen.width_type = 4;
		this._scroll_screen.width_value = 0;
		this._scroll_screen.height_type = 4;
		this._scroll_screen.height_value = 0;
		this._scroll_screen.container = this._linear;
		this._body.AddChild(this._scroll_screen);
		this._body_margin = 0;
		this._screen_margin_left = 0;
		this._screen_margin_right = 0;
		this._screen_margin_top = 0;
		this._screen_margin_bottom = 0;
		this._show_count = 0;
		this.AddEventListener(___all_struct.get(958494922), this, this.HandleButtonChange);
		this._body.AddEventListener(___all_struct.get(348388800), this, this.HandleBodyHide);
	},
	set show_background(value) {
		if (this._background === value) {
			return;
		}
		this._body.RemoveChild(this._background);
		this._background = value;
		if (this._background !== undefined) {
			this._background.width_type = 4;
			this._background.height_type = 4;
			this._background.width_value = 0;
			this._background.height_value = 0;
			this._body.AddChild(this._background, 0);
		}
	},
	get show_background() {
		return this._background;
	},
	set show_scrollbar(value) {
		if (this._scrollbar === value) {
			return;
		}
		this._scrollbar = value;
		if (this._scrollbar === undefined) {
			this._scroll_screen.right_scrollbar = undefined;
		}
		this.Layout();
	},
	get show_scrollbar() {
		return this._scrollbar;
	},
	set show_count(value) {
		if (this._show_count === value) {
			return;
		}
		this._show_count = value;
		this.Layout();
	},
	get show_count() {
		return this._show_count;
	},
	set button_style(value) {
		if (this._button_style === value) {
			return;
		}
		let child_list = this._scroll_screen.childs;
		let ___OBJECT_1 = child_list;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			v.RemoveEventListener(___all_struct.get(-449066808), this, this.HandleItemButtonClick);
		}
		this._scroll_screen.RemoveAllChild();
		this._button_style = value;
		let button = undefined;
		if (this._button_style !== undefined && this._data_list !== undefined) {
			let ___OBJECT_2 = this._data_list;
			for (let k = 1; k <= ___OBJECT_2.length; ++k) {
				let v = ___OBJECT_2[k - 1];
				if (v === undefined) break;
				button = this._ctrl_sys.CreateControl(this._button_style, undefined, this._scroll_screen);
				button.AddEventListener(___all_struct.get(-449066808), this, this.HandleItemButtonClick);
				button.text = v;
				button.drag_trans_target = this._scroll_screen;
			}
		}
		if (this._show_count === 0 || this._show_count >= this._linear.child_count) {
			this._body.height = this._linear.height + this._screen_margin_top + this._screen_margin_bottom;
		} else if (button !== undefined) {
			this._body.height = button.height * this._show_count + this._screen_margin_top + this._screen_margin_bottom;
		} else {
			this._body.height = 0;
		}
	},
	get button_style() {
		return this._button_style;
	},
	set body_margin(value) {
		this._body_margin = value;
	},
	get body_margin() {
		return this._body_margin;
	},
	set screen_margin_left(value) {
		this._screen_margin_left = value;
	},
	get screen_margin_left() {
		return this._screen_margin_left;
	},
	set screen_margin_right(value) {
		this._screen_margin_right = value;
	},
	get screen_margin_right() {
		return this._screen_margin_right;
	},
	set screen_margin_top(value) {
		this._screen_margin_top = value;
	},
	get screen_margin_top() {
		return this._screen_margin_top;
	},
	set screen_margin_bottom(value) {
		this._screen_margin_bottom = value;
	},
	get screen_margin_bottom() {
		return this._screen_margin_bottom;
	},
	set data_list(value) {
		if (value === undefined) {
			value = [];
		}
		let button_style = this._button_style;
		this._button_style = undefined;
		this._data_list = value;
		this.button_style = button_style;
		if (ALittle.List_Len(value) > 0) {
			this.text = value[1 - 1];
		} else {
			this.text = "";
		}
		this.Layout();
	},
	get data_list() {
		return this._data_list;
	},
	HandleItemButtonClick : function(event) {
		A_LayerManager.HideFromRight(this._body);
		if (this.text === event.target.text) {
			return;
		}
		this.text = event.target.text;
		this.DispatchEvent(___all_struct.get(444989011), {});
	},
	HandleButtonChange : function(event) {
		if (event.target.selected === false) {
			A_LayerManager.HideFromRight(this._body);
		} else {
			let [abs_x, abs_y] = this.LocalToGlobal();
			let adjust_y = abs_y + this.height * this.scale_y;
			if (A_UISystem.view_height < adjust_y + this._scroll_screen.height * this.scale_y) {
				adjust_y = abs_y - this._scroll_screen.height * this.scale_y;
			}
			this._body.y = adjust_y;
			this._body.width = this.width - this._body_margin;
			this._body.x = abs_x + this._body_margin / 2;
			this._body.scale_x = this.scale_x;
			this._body.scale_y = this.scale_y;
			this._scroll_screen.x = this._screen_margin_left;
			this._scroll_screen.y = this._screen_margin_top;
			this._scroll_screen.width_value = this._screen_margin_left + this._screen_margin_right;
			this._scroll_screen.height_value = this._screen_margin_top + this._screen_margin_bottom;
			A_LayerManager.ShowFromRight(this._body);
			A_UISystem.focus = this._scroll_screen;
		}
	},
	HandleBodyHide : function(event) {
		if (this.selected === false) {
			return;
		}
		this.selected = false;
	},
	Layout : function() {
		if (this._show_count === 0 || this._scrollbar === undefined || this._show_count >= this._linear.child_count) {
			this._scroll_screen.right_scrollbar = undefined;
			this._body.height = this._linear.height + this._screen_margin_top + this._screen_margin_bottom;
		} else {
			this._scroll_screen.right_scrollbar = this._scrollbar;
			let button = this._linear.childs[1 - 1];
			if (button !== undefined) {
				this._body.height = button.height * this._show_count + this._screen_margin_top + this._screen_margin_bottom;
			} else {
				this._body.height = 0;
			}
		}
	},
}, "ALittle.DropDown");

}