{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-2110455927, "ALittle.EventInfo", {
name : "ALittle.EventInfo", ns_name : "ALittle", rl_name : "EventInfo", hash_code : -2110455927,
name_list : ["type","func"],
type_list : ["string","string"],
option_map : {}
})
ALittle.RegStruct(-4982446, "ALittle.DisplayInfo", {
name : "ALittle.DisplayInfo", ns_name : "ALittle", rl_name : "DisplayInfo", hash_code : -4982446,
name_list : ["__target_class","__class_func","__base_attr","__show_attr","loop_map","__module","__class","__include","__extends","__childs","__event","__link","__shows_included","__childs_included","__extends_included","description","text","font_path","font_size","red","green","blue","alpha","bold","italic","underline","deleteline","x","y","x_type","x_value","y_type","y_value","width","height","width_type","width_value","height_type","height_value","scale_x","scale_y","center_x","center_y","angle","flip","hand_cursor","visible","disabled","left_size","right_size","top_size","bottom_size","texture_name","interval","play_loop_count","var_play","base_y","head_size","gap","up_size","down_size","cursor_red","cursor_green","cursor_blue","default_text_alpha","ims_padding","margin_left","margin_right","margin_top","margin_bottom","show_count","body_margin","screen_margin_left","screen_margin_right","screen_margin_top","screen_margin_bottom","start_degree","end_degree","line_spacing","max_line_count","font_red","font_green","font_blue","margin_halign","margin_valign","cursor_margin_up","cursor_margin_down","total_size","show_size","offset_rate","offset_step","grade","row_count","col_count","row_index","col_index","u1","v1","u2","v2","u3","v3","x1","y1","x2","y2","x3","y3","x_gap","y_gap","x_start_gap","y_start_gap","button_gap","button_start","button_margin","tab_index","view_margin","child_width_margin"],
type_list : ["List<string>","any","Map<string,any>","Map<string,ALittle.DisplayInfo>","Map<string,ALittle.LoopGroupInfo>","string","string","string","string","List<ALittle.DisplayInfo>","List<ALittle.EventInfo>","string","bool","bool","bool","string","string","string","int","double","double","double","double","bool","bool","bool","bool","double","double","int","double","int","double","double","double","int","double","int","double","double","double","double","double","double","int","bool","bool","bool","double","double","double","double","string","int","int","bool","double","double","double","double","double","double","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","double","double","double","int","int","int","int","int","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double"],
option_map : {}
})

let __cos = ALittle.Math_Cos;
let __sin = ALittle.Math_Sin;
let __byte = ALittle.String_Byte;
let __type = ALittle.String_Type;
if (ALittle.UIEventDispatcher === undefined) throw new Error(" extends class:ALittle.UIEventDispatcher is undefined");
ALittle.DisplayObject = JavaScript.Class(ALittle.UIEventDispatcher, {
	Ctor : function(ctrl_sys) {
		this._ctrl_sys = ctrl_sys;
		this._clip = false;
		this._ignore = false;
		this._x = 0;
		this._y = 0;
		this._x_type = 1;
		this._x_value = 0;
		this._y_type = 1;
		this._y_value = 0;
		this._width = 0;
		this._height = 0;
		this._width_type = 1;
		this._width_value = 0;
		this._height_type = 1;
		this._height_value = 0;
		this._scale_x = 1;
		this._scale_y = 1;
		this._angle = 0;
		this._center_x = 0;
		this._center_y = 0;
		this._red = 1;
		this._green = 1;
		this._blue = 1;
		this._alpha = 1;
		this._abs_alpha = 1;
		this._visible = true;
		this._abs_visible = true;
		this._hand_cursor = false;
		this._disabled = false;
		this._modal = false;
		this._pickup_rect = true;
		this._pickup_child = false;
		this._pickup_this = false;
		this._can_scroll = false;
	},
	set hand_cursor(value) {
		if (this._hand_cursor === value) {
			return;
		}
		this._hand_cursor = value;
		if (value) {
			this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveInForCursor);
			this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOutForCursor);
		} else {
			this.RemoveEventListener(___all_struct.get(544684311), this, this.HandleMoveInForCursor);
			this.RemoveEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOutForCursor);
		}
	},
	get hand_cursor() {
		return this._hand_cursor;
	},
	HandleMoveInForCursor : function(event) {
		if (this._hand_cursor === false) {
			return;
		}
		ALittle.System_SetHandCursor();
	},
	HandleMoveOutForCursor : function(event) {
		if (this._hand_cursor === false) {
			return;
		}
		ALittle.System_SetNormalCursor();
	},
	get native_show() {
		return this._show;
	},
	get text() {
		return undefined;
	},
	set text(value) {
	},
	get group() {
		return undefined;
	},
	set group(group) {
	},
	get selected() {
		return undefined;
	},
	set selected(value) {
	},
	get font_height() {
		return undefined;
	},
	SetTextureCoord : function(t, b, l, r) {
	},
	get texture() {
		return undefined;
	},
	set texture(value) {
	},
	get texture_name() {
		return undefined;
	},
	set texture_name(value) {
	},
	Redraw : function() {
	},
	get childs() {
		return undefined;
	},
	get child_count() {
		return undefined;
	},
	SetChildIndex : function(child, index) {
		return false;
	},
	AddChild : function(child, index) {
		return false;
	},
	RemoveChild : function(child) {
		return false;
	},
	SpliceChild : function(index, count) {
		return 0;
	},
	RemoveAllChild : function() {
	},
	GetChildOffset : function() {
		return [0, 0];
	},
	get editable() {
		return false;
	},
	get font_size() {
		return undefined;
	},
	get cursor_x() {
		return undefined;
	},
	get cursor_y() {
		return undefined;
	},
	get cursor_b() {
		return undefined;
	},
	get is_focus() {
		return A_UISystem.focus === this;
	},
	DelayFocus : function() {
		let loop = ALittle.NewObject(ALittle.LoopTimer, this.HandleDelayFocus.bind(this), 1);
		loop.Start();
	},
	HandleDelayFocus : function() {
		this.focus = true;
	},
	DelayDisable : function() {
		let loop = ALittle.NewObject(ALittle.LoopTimer, this.HandleDelayDisable.bind(this), 1);
		loop.Start();
	},
	HandleDelayDisable : function() {
		this.disabled = true;
	},
	set focus(value) {
		if (value) {
			A_UISystem.focus = this;
		} else {
			if (A_UISystem.focus === this) {
				A_UISystem.focus = undefined;
			}
		}
	},
	get is_input() {
		return false;
	},
	set can_scroll(value) {
		this._can_scroll = value;
	},
	get can_scroll() {
		return this._can_scroll;
	},
	set description(value) {
		this._description = value;
	},
	get description() {
		return this._description;
	},
	set loop_map(value) {
		this._loop_map = value;
	},
	get loop_map() {
		return this._loop_map;
	},
	CreateLoopAnimation : function(name) {
		if (this._loop_map === undefined) {
			return undefined;
		}
		let info = this._loop_map[name];
		if (info === undefined) {
			return undefined;
		}
		return ALittle.NewObject(ALittle.LoopAnimation, this, info);
	},
	set modal(value) {
		this._modal = value;
	},
	get modal() {
		return this._modal;
	},
	set clip(value) {
		this._clip = value;
		this._show.SetClip(value);
	},
	get clip() {
		return this._clip;
	},
	set ignore(value) {
		this._ignore = value;
	},
	get ignore() {
		return this._ignore;
	},
	IsMouseIn : function() {
		let [abs_x, abs_y] = this.LocalToGlobal();
		let mouse_x = A_UISystem.mouse_x;
		let mouse_y = A_UISystem.mouse_y;
		if (mouse_x < abs_x) {
			return false;
		}
		if (mouse_y < abs_y) {
			return false;
		}
		if (mouse_x > abs_x + this.width * this.scale_x) {
			return false;
		}
		if (mouse_y > abs_y + this.height * this.scale_y) {
			return false;
		}
		return true;
	},
	LocalToGlobal : function(target) {
		let x = 0.0;
		let y = 0.0;
		let parent = this;
		while (parent !== undefined) {
			let scale_x = 1.0;
			let scale_y = 1.0;
			let show_parent = parent._show_parent;
			if (show_parent !== undefined) {
				scale_x = show_parent.scale_x;
				scale_y = show_parent.scale_y;
			}
			x = x + (scale_x * parent.x);
			y = y + (scale_y * parent.y);
			if (target === show_parent) {
				break;
			}
			parent = show_parent;
		}
		return [x, y];
	},
	LocalToGlobalMatrix2D : function(target) {
		let result = ALittle.NewObject(ALittle.Matrix2D);
		let list = [];
		let count = 0;
		let parent = this;
		while (parent !== undefined) {
			if (target === parent) {
				break;
			}
			++ count;
			list[count - 1] = parent;
			parent = parent._show_parent;
		}
		for (let index = count; index >= 1; index += -1) {
			let object = list[index - 1];
			let m = ALittle.NewObject(ALittle.Matrix2D);
			if (index === 1) {
				m.Scale(object.width, object.height);
			}
			m.Translation(-object.center_x, -object.center_y);
			m.Rotate(3.1415926 * object.angle / 180);
			m.Translation(object.center_x, object.center_y);
			m.Scale(object.scale_x, object.scale_y);
			m.Translation(object.x, object.y);
			m.Multiply(result);
			result = m;
		}
		return result;
	},
	GlobalToLocalMatrix2D : function(x, y, target) {
		let list = [];
		let count = 0;
		let parent = this;
		while (parent !== undefined) {
			if (target === parent) {
				break;
			}
			++ count;
			list[count - 1] = parent;
			parent = parent._show_parent;
		}
		let pick = undefined;
		for (let index = count; index >= 1; index += -1) {
			[pick, x, y] = list[index - 1].PickUpSelf(x, y);
		}
		return [x, y];
	},
	RemoveFromParent : function() {
		let parent = this._show_parent;
		if (parent === undefined) {
			parent = this._logic_parent;
		}
		if (parent === undefined) {
			return;
		}
		parent.RemoveChild(this);
	},
	IsGrandParent : function(target) {
		let parent = this;
		while (parent !== undefined) {
			parent = parent._show_parent;
			if (target === parent) {
				return true;
			}
		}
		return false;
	},
	get parent() {
		if (this._logic_parent !== undefined) {
			return this._logic_parent;
		}
		return this._show_parent;
	},
	get show_parent() {
		return this._show_parent;
	},
	get logic_parent() {
		return this._logic_parent;
	},
	MoveToTop : function() {
		if (this._show_parent !== undefined) {
			this._show_parent.SetChildIndex(this, this._show_parent.child_count);
		}
	},
	set x(value) {
		if (this._x === value) {
			return;
		}
		this._x = value;
		if (this._x_type === 1) {
			this._x_value = value;
		}
		this._show.SetX(value);
	},
	get x() {
		return this._x;
	},
	set x_type(value) {
		if (this._x_type === value) {
			return;
		}
		this._x_type = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateXLayout(this);
		}
	},
	set x_value(value) {
		if (this._x_value === value) {
			return;
		}
		this._x_value = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateXLayout(this);
		}
	},
	get x_type() {
		return this._x_type;
	},
	get x_value() {
		return this._x_value;
	},
	set y(value) {
		if (this._y === value) {
			return;
		}
		this._y = value;
		if (this._y_type === 1) {
			this._y_value = value;
		}
		this._show.SetY(value);
	},
	get y() {
		return this._y;
	},
	set y_type(value) {
		if (this._y_type === value) {
			return;
		}
		this._y_type = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateYLayout(this);
		}
	},
	set y_value(value) {
		if (this._y_value === value) {
			return;
		}
		this._y_value = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateYLayout(this);
		}
	},
	get y_type() {
		return this._y_type;
	},
	get y_value() {
		return this._y_value;
	},
	set width(value) {
		if (this._width === value) {
			return;
		}
		this._width = value;
		if (this._width_type === 1) {
			this._width_value = value;
		}
		this._show.SetWidth(value);
	},
	get width() {
		return this._width;
	},
	set width_type(value) {
		if (this._width_type === value) {
			return;
		}
		this._width_type = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateWidthLayout(this);
			if (this._x_type !== 1 && this._x_type !== 2 && this._x_type !== 7) {
				this._show_parent.UpdateXLayout(this);
			}
		} else if (this._width_type === 1) {
			this.width = this._width_value;
		}
	},
	set width_value(value) {
		if (this._width_value === value) {
			return;
		}
		this._width_value = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateWidthLayout(this);
			if (this._x_type !== 1 && this._x_type !== 2 && this._x_type !== 7) {
				this._show_parent.UpdateXLayout(this);
			}
		} else if (this._width_type === 1) {
			this.width = this._width_value;
		}
	},
	get width_type() {
		return this._width_type;
	},
	get width_value() {
		return this._width_value;
	},
	set height(value) {
		if (this._height === value) {
			return;
		}
		this._height = value;
		if (this._height_type === 1) {
			this._height_value = value;
		}
		this._show.SetHeight(value);
	},
	get height() {
		return this._height;
	},
	set height_type(value) {
		if (this._height_type === value) {
			return;
		}
		this._height_type = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateHeightLayout(this);
			if (this._y_type !== 1 && this._y_type !== 2 && this._y_type !== 7) {
				this._show_parent.UpdateYLayout(this);
			}
		} else if (this._height_type === 1) {
			this.height = this._height_value;
		}
	},
	set height_value(value) {
		if (this._height_value === value) {
			return;
		}
		this._height_value = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateHeightLayout(this);
			if (this._y_type !== 1 && this._y_type !== 2 && this._y_type !== 7) {
				this._show_parent.UpdateYLayout(this);
			}
		} else if (this._height_type === 1) {
			this.height = this._height_value;
		}
	},
	get height_type() {
		return this._height_type;
	},
	get height_value() {
		return this._height_value;
	},
	set scale_x(value) {
		this._scale_x = value;
		this._show.SetScaleX(value);
	},
	get scale_x() {
		return this._scale_x;
	},
	set scale_y(value) {
		this._scale_y = value;
		this._show.SetScaleY(value);
	},
	get scale_y() {
		return this._scale_y;
	},
	set center_x(value) {
		this._center_x = value;
		this._show.SetCenterX(value);
	},
	get center_x() {
		return this._center_x;
	},
	set center_y(value) {
		this._center_y = value;
		this._show.SetCenterY(value);
	},
	get center_y() {
		return this._center_y;
	},
	set angle(value) {
		this._angle = value;
		this._show.SetAngle(value);
	},
	get angle() {
		return this._angle;
	},
	set red(value) {
		this._red = value;
		this._show.SetRed(value);
	},
	get red() {
		return this._red;
	},
	set green(value) {
		this._green = value;
		this._show.SetGreen(value);
	},
	get green() {
		return this._green;
	},
	set blue(value) {
		this._blue = value;
		this._show.SetBlue(value);
	},
	get blue() {
		return this._blue;
	},
	set alpha(value) {
		this._alpha = value;
		this._abs_alpha = 1;
		if (this._show_parent !== undefined) {
			this._abs_alpha = this._show_parent.abs_alpha * value;
		} else {
			this._abs_alpha = value;
		}
		this._show.SetAlpha(this._abs_alpha);
	},
	get alpha() {
		return this._alpha;
	},
	get abs_alpha() {
		return this._abs_alpha;
	},
	set visible(value) {
		if (value === false && this === A_UISystem.focus) {
			A_UISystem.focus = undefined;
		}
		this._visible = value;
		if (this._show_parent !== undefined) {
			this._abs_visible = this._show_parent.abs_visible && value;
		} else {
			this._abs_visible = value;
		}
		this._show.SetVisible(this._abs_visible);
	},
	get visible() {
		return this._visible;
	},
	get abs_visible() {
		return this._abs_visible;
	},
	set disabled(value) {
		if (value === true && this === A_UISystem.focus) {
			A_UISystem.focus = undefined;
		}
		this._disabled = value;
		if (this._show_parent !== undefined) {
			this._abs_disabled = this._show_parent.abs_disabled || value;
		} else {
			this._abs_disabled = value;
		}
	},
	get disabled() {
		return this._disabled;
	},
	get abs_disabled() {
		return this._abs_disabled;
	},
	UpdateLayout : function() {
		if (this._show_parent === undefined) {
			return;
		}
		this._show_parent.UpdateWidthLayout(this);
		this._show_parent.UpdateHeightLayout(this);
		this._show_parent.UpdateXLayout(this);
		this._show_parent.UpdateYLayout(this);
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
		if (this._modal) {
			return [this, rel_x, rel_y];
		}
		if (this._pickup_rect && rel_x >= 0 && rel_y >= 0 && rel_x < this._width && rel_y < this._height) {
			return [this, rel_x, rel_y];
		} else {
			return [undefined, rel_x, rel_y];
		}
	},
	PickUpSelf : function(x, y) {
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
			return [undefined, rel_x, rel_y];
		}
		if (this._abs_visible && rel_x >= 0 && rel_y >= 0 && rel_x < this.width && rel_y < this.height) {
			return [this, rel_x, rel_y];
		}
		return [undefined, rel_x, rel_y];
	},
	ClipRect : function(x, y, width, height, h_move, v_move) {
	},
	DeepLayout : function() {
	},
	DeserializeSetter : function(info) {
		let base_attr = info.__base_attr;
		if (base_attr === undefined) {
			base_attr = {};
			let ___OBJECT_1 = info;
			for (let key in ___OBJECT_1) {
				let value = ___OBJECT_1[key];
				if (value === undefined) continue;
				if (__byte(key, 1) !== 95 && (__type(value) !== "table" || value.__class === undefined)) {
					base_attr[key] = value;
				}
			}
			info.__base_attr = base_attr;
		}
		let ___OBJECT_2 = base_attr;
		for (let key in ___OBJECT_2) {
			let value = ___OBJECT_2[key];
			if (value === undefined) continue;
			this[key] = value;
		}
	},
	DeserializeShowChild : function(info, target_logic) {
		if (info.__target_class !== undefined && this._ctrl_sys._use_plugin_class) {
			target_logic = this;
		}
		let show_attr = info.__show_attr;
		if (show_attr === undefined) {
			show_attr = {};
			let ___OBJECT_3 = info;
			for (let key in ___OBJECT_3) {
				let value = ___OBJECT_3[key];
				if (value === undefined) continue;
				if (__byte(key, 1) !== 95 && __type(value) === "table" && value.__class !== undefined) {
					show_attr[key] = value;
				}
			}
			info.__show_attr = show_attr;
		}
		let ___OBJECT_4 = show_attr;
		for (let key in ___OBJECT_4) {
			let value = ___OBJECT_4[key];
			if (value === undefined) continue;
			let object = this._ctrl_sys.CreateControlObject(value);
			if (object !== undefined) {
				object.DeserializeSetter(value);
				this[key] = object;
				object.DeserializeShowChild(value, target_logic);
				if (target_logic !== undefined) {
					object.DeserializeLinkEvent(value, target_logic);
				}
				if (value.__target_class !== undefined && this._ctrl_sys._use_plugin_class) {
					let tctor = object["TCtor"];
					if (tctor !== undefined) {
						tctor.call(object);
					}
				}
			}
		}
		let childs = info.__childs;
		if (childs !== undefined) {
			let ___OBJECT_5 = childs;
			for (let index = 1; index <= ___OBJECT_5.length; ++index) {
				let value = ___OBJECT_5[index - 1];
				if (value === undefined) break;
				let object = this._ctrl_sys.CreateControlObject(value);
				if (object !== undefined) {
					object.Deserialize(value, target_logic, this);
				}
			}
		}
	},
	DeserializeLinkEvent : function(info, target_logic) {
		let event_list = info.__event;
		if (event_list !== undefined) {
			let ___OBJECT_6 = event_list;
			for (let index = 1; index <= ___OBJECT_6.length; ++index) {
				let einfo = ___OBJECT_6[index - 1];
				if (einfo === undefined) break;
				let func = undefined;
				if (einfo.func !== undefined) {
					func = target_logic[einfo.func];
					if (func === undefined && this._ctrl_sys.log_error) {
						ALittle.Log("can't find event func:\"" + einfo.func + "\" in " + ALittle.String_ToString(target_logic));
					}
				}
				if (einfo.type !== undefined && func !== undefined) {
					this.AddEventListenerImpl(einfo.type, target_logic, func);
				}
			}
		}
		if (info.__link !== undefined) {
			target_logic[info.__link] = this;
		}
	},
	Deserialize : function(info, target_logic, parent) {
		this.DeserializeSetter(info);
		if (this._pickup_rect) {
			if (parent !== undefined) {
				parent.AddChild(this);
			}
			this.DeserializeShowChild(info, target_logic);
			if (target_logic !== undefined) {
				this.DeserializeLinkEvent(info, target_logic);
			}
		} else {
			this.DeserializeShowChild(info, target_logic);
			if (target_logic !== undefined) {
				this.DeserializeLinkEvent(info, target_logic);
			}
			if (parent !== undefined) {
				parent.AddChild(this);
			}
		}
		if (info.__target_class !== undefined && this._ctrl_sys._use_plugin_class) {
			let tctor = this["TCtor"];
			if (tctor !== undefined) {
				tctor.call(this);
			}
		}
	},
}, "ALittle.DisplayObject");

}