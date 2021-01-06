{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1818243950, "ALittle.RichInputCharInfo", {
name : "ALittle.RichInputCharInfo", ns_name : "ALittle", rl_name : "RichInputCharInfo", hash_code : 1818243950,
name_list : ["acc_width","pre_width","text_info","text","password_text","text_object","ctrl_info","ctrl"],
type_list : ["double","double","ALittle.DisplayInfo","string","string","ALittle.Text","ALittle.DisplayInfo","ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1640499878, "ALittle.UIRichInputLongClickEvent", {
name : "ALittle.UIRichInputLongClickEvent", ns_name : "ALittle", rl_name : "UIRichInputLongClickEvent", hash_code : 1640499878,
name_list : ["target","abs_x","abs_y","rel_x","rel_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(1424993548, "ALittle.RichInputMultiDragBeginEvent", {
name : "ALittle.RichInputMultiDragBeginEvent", ns_name : "ALittle", rl_name : "RichInputMultiDragBeginEvent", hash_code : 1424993548,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-884368490, "ALittle.RichInputMultiDragEndEvent", {
name : "ALittle.RichInputMultiDragEndEvent", ns_name : "ALittle", rl_name : "RichInputMultiDragEndEvent", hash_code : -884368490,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-683607428, "ALittle.RichInputCursorClickEvent", {
name : "ALittle.RichInputCursorClickEvent", ns_name : "ALittle", rl_name : "RichInputCursorClickEvent", hash_code : -683607428,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-605767802, "ALittle.RichInputMultiDragEvent", {
name : "ALittle.RichInputMultiDragEvent", ns_name : "ALittle", rl_name : "RichInputMultiDragEvent", hash_code : -605767802,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-256576702, "ALittle.RichInputFontChangedEvent", {
name : "ALittle.RichInputFontChangedEvent", ns_name : "ALittle", rl_name : "RichInputFontChangedEvent", hash_code : -256576702,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

let __byte = ALittle.String_Byte;
let __sub = ALittle.String_Sub;
let __find = ALittle.String_Find;
let __floor = ALittle.Math_Floor;
let __len = ALittle.String_Len;
let __abs = ALittle.Math_Abs;
let __type = ALittle.String_Type;
if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.RichInput = JavaScript.Class(ALittle.DisplayLayout, {
	CheckDisplayList : function(content) {
		let ___OBJECT_1 = content;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			if (v.__class === undefined) {
				return false;
			}
		}
		return true;
	},
	CharIsNumber : function(str) {
		let c = __byte(str, 1);
		return c >= 48 && c <= 57;
	},
	CharIsLetter : function(str) {
		let c = __byte(str, 1);
		return c >= 65 && c <= 90 || c >= 97 && c <= 122;
	},
	CompareTextInfo : function(a, b) {
		if (a.font_path !== b.font_path) {
			return false;
		}
		if (a.font_size !== b.font_size) {
			return false;
		}
		if (a.red !== b.red) {
			return false;
		}
		if (a.green !== b.green) {
			return false;
		}
		if (a.blue !== b.blue) {
			return false;
		}
		if (a.bold !== b.bold) {
			return false;
		}
		if (a.italic !== b.italic) {
			return false;
		}
		if (a.underline !== b.underline) {
			return false;
		}
		if (a.deleteline !== b.deleteline) {
			return false;
		}
		return true;
	},
	CopyTextInfo : function(b) {
		let a = {};
		a.__class = "Text";
		a.font_path = b.font_path;
		a.font_size = b.font_size;
		a.red = b.red;
		a.green = b.green;
		a.blue = b.blue;
		a.bold = b.bold;
		a.italic = b.italic;
		a.underline = b.underline;
		a.deleteline = b.deleteline;
		return a;
	},
	InitTextInfo : function() {
		let font_text = this._font_text;
		let a = {};
		a.__class = "Text";
		a.font_path = font_text.font_path;
		a.font_size = font_text.font_size;
		a.red = font_text.red;
		a.green = font_text.green;
		a.blue = font_text.blue;
		a.bold = font_text.bold;
		a.italic = font_text.italic;
		a.underline = font_text.underline;
		a.deleteline = font_text.deleteline;
		return a;
	},
	SetDrawText : function(font_text) {
		let draw_text = this._draw_text;
		draw_text.font_path = font_text.font_path;
		draw_text.font_size = font_text.font_size;
		draw_text.red = font_text.red;
		draw_text.green = font_text.green;
		draw_text.blue = font_text.blue;
		draw_text.bold = font_text.bold;
		draw_text.italic = font_text.italic;
		draw_text.underline = font_text.underline;
		draw_text.deleteline = font_text.deleteline;
	},
	SplitText : function(char_info, char_info_list, char_info_list_count) {
		let text = char_info.text;
		while (true) {
			let start_index_1 = __find(text, "\n");
			let start_index_2 = __find(text, "\t");
			if (start_index_1 !== undefined && start_index_2 !== undefined) {
				if (start_index_1 < start_index_2) {
					start_index_2 = undefined;
				} else {
					start_index_1 = undefined;
				}
			}
			if (start_index_1 !== undefined) {
				let sub_text = __sub(text, 1, start_index_1 - 1);
				text = __sub(text, start_index_1 + 1);
				if (sub_text !== "") {
					let new_char_info = ALittle.String_CopyTable(char_info);
					new_char_info.text = sub_text;
					++ char_info_list_count;
					char_info_list[char_info_list_count - 1] = new_char_info;
				}
			} else if (start_index_2 !== undefined) {
				let sub_text = __sub(text, 1, start_index_2 - 1);
				text = __sub(text, start_index_2 + 1);
				if (sub_text !== "") {
					let new_char_info = ALittle.String_CopyTable(char_info);
					new_char_info.text = sub_text;
					++ char_info_list_count;
					char_info_list[char_info_list_count - 1] = new_char_info;
				}
			} else {
				if (text !== "") {
					let new_char_info = ALittle.String_CopyTable(char_info);
					new_char_info.text = text;
					++ char_info_list_count;
					char_info_list[char_info_list_count - 1] = new_char_info;
				}
				break;
			}
		}
		return char_info_list_count;
	},
	DisplayListToCharInfoList : function(display_list, default_text_info) {
		let char_info_list = [];
		let char_info_list_count = 0;
		let last_text_info = default_text_info;
		let ___OBJECT_2 = display_list;
		for (let display_index = 1; display_index <= ___OBJECT_2.length; ++display_index) {
			let display_info = ___OBJECT_2[display_index - 1];
			if (display_info === undefined) break;
			if (display_info.__class === "Text") {
				let new_char_info = {};
				new_char_info.acc_width = 0;
				new_char_info.pre_width = 0;
				new_char_info.text_info = this.CopyTextInfo(display_info);
				new_char_info.text_object = undefined;
				new_char_info.text = display_info.text;
				new_char_info.ctrl_info = undefined;
				new_char_info.ctrl = undefined;
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				last_text_info = new_char_info.text_info;
			} else {
				if (last_text_info === undefined) {
					last_text_info = this.InitTextInfo();
				}
				let new_char_info = {};
				new_char_info.acc_width = 0;
				new_char_info.pre_width = 0;
				new_char_info.text_info = last_text_info;
				new_char_info.text_object = undefined;
				new_char_info.text = "";
				new_char_info.ctrl_info = display_info;
				new_char_info.ctrl = undefined;
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
			}
		}
		return char_info_list;
	},
	CharInfoListToDisplayList : function(list) {
		let display_list = [];
		let display_list_count = 0;
		let text_info = undefined;
		let text_list = undefined;
		let text_list_count = 0;
		let ___OBJECT_3 = list;
		for (let char_index = 1; char_index <= ___OBJECT_3.length; ++char_index) {
			let char_info = ___OBJECT_3[char_index - 1];
			if (char_info === undefined) break;
			if (char_info.ctrl_info === undefined) {
				if (text_info === undefined) {
					text_info = char_info.text_info;
					text_list = [];
					text_list_count = 1;
					text_list[text_list_count - 1] = char_info.text;
				} else if (text_info === char_info.text_info) {
					++ text_list_count;
					text_list[text_list_count - 1] = char_info.text;
				} else {
					if (this.CompareTextInfo(text_info, char_info.text_info)) {
						++ text_list_count;
						text_list[text_list_count - 1] = char_info.text;
					} else {
						let text = ALittle.String_Join(text_list, "");
						if (text !== "") {
							let text_ctrl = ALittle.String_CopyTable(text_info);
							text_ctrl.__class = "Text";
							text_ctrl.text = text;
							++ display_list_count;
							display_list[display_list_count - 1] = text_ctrl;
						}
						text_info = char_info.text_info;
						text_list = [];
						text_list_count = 1;
						text_list[text_list_count - 1] = char_info.text;
					}
				}
			} else {
				if (text_info !== undefined) {
					let text = ALittle.String_Join(text_list, "");
					if (text !== "") {
						let text_ctrl = ALittle.String_CopyTable(text_info);
						text_ctrl.__class = "Text";
						text_ctrl.text = text;
						++ display_list_count;
						display_list[display_list_count - 1] = text_ctrl;
					}
					text_info = undefined;
					text_list = undefined;
					text_list_count = 0;
				}
				++ display_list_count;
				display_list[display_list_count - 1] = ALittle.String_CopyTable(char_info.ctrl_info);
			}
		}
		if (text_info !== undefined) {
			let text = ALittle.String_Join(text_list, "");
			if (text !== "") {
				let text_ctrl = ALittle.String_CopyTable(text_info);
				text_ctrl.__class = "Text";
				text_ctrl.text = text;
				++ display_list_count;
				display_list[display_list_count - 1] = text_ctrl;
			}
		}
		return display_list;
	},
	CharInfoListToWord : function(list) {
		let text_list = [];
		let text_list_count = 0;
		let ___OBJECT_4 = list;
		for (let char_index = 1; char_index <= ___OBJECT_4.length; ++char_index) {
			let char_info = ___OBJECT_4[char_index - 1];
			if (char_info === undefined) break;
			if (char_info.ctrl_info === undefined) {
				++ text_list_count;
				text_list[text_list_count - 1] = char_info.text;
			}
		}
		return ALittle.String_Join(text_list, "");
	},
	UpdateFontText : function() {
		let char_info = this._char_info_list[this._char_cursor_it - 1];
		let is_change = false;
		let font_text = this._font_text;
		let text_info = char_info.text_info;
		if (font_text.font_path !== text_info.font_path) {
			font_text.font_path = text_info.font_path;
			is_change = true;
		}
		if (font_text.font_size !== text_info.font_size) {
			font_text.font_size = text_info.font_size;
			is_change = true;
		}
		if (font_text.red !== text_info.red) {
			font_text.red = text_info.red;
			is_change = true;
		}
		if (font_text.green !== text_info.green) {
			font_text.green = text_info.green;
			is_change = true;
		}
		if (font_text.blue !== text_info.blue) {
			font_text.blue = text_info.blue;
			is_change = true;
		}
		if (font_text.bold !== text_info.bold) {
			font_text.bold = text_info.bold;
			is_change = true;
		}
		if (font_text.italic !== text_info.italic) {
			font_text.italic = text_info.italic;
			is_change = true;
		}
		if (font_text.underline !== text_info.underline) {
			font_text.underline = text_info.underline;
			is_change = true;
		}
		if (font_text.deleteline !== text_info.deleteline) {
			font_text.deleteline = text_info.deleteline;
			is_change = true;
		}
		if (is_change) {
			this.DispatchEvent(___all_struct.get(-256576702), {});
		}
	},
	GetCursorWidth : function(font_size) {
		if (font_size === undefined || font_size < 15) {
			return 1;
		}
		if (font_size > 100) {
			return 10;
		}
		return __floor((font_size / 100) * 10);
	},
	Ctor : function(ctrl_sys) {
		this._char_info_list = [];
		this._char_count = 0;
		this._font_text = ALittle.NewObject(ALittle.Text, this._ctrl_sys);
		this._draw_text = ALittle.NewObject(ALittle.Text, this._ctrl_sys);
		this._char_cursor_it = 1;
		this._char_select_it = 1;
		this._display_view = ALittle.NewObject(ALittle.DisplayView, this._ctrl_sys);
		this._display_view.width_type = 4;
		this._display_view.height_type = 4;
		this._display_view.x_type = 3;
		this._display_view.y_type = 3;
		this.AddChild(this._display_view);
		this._display_show = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
		this._display_show.width = 0;
		this._display_show.height = 0;
		this._display_show.x = 0;
		this._display_show.y_type = 4;
		this._display_show.y_value = 0;
		this._display_view.AddChild(this._display_show);
		this._current_flash_alpha = 1;
		this._current_flash_dir = -0.05;
		this._cursor = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this._cursor.width = 1;
		this.AddChild(this._cursor);
		this._cursor.visible = false;
		this._select = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this.AddChild(this._select);
		this._select.visible = false;
		this._select.alpha = 0.5;
		this._start_cursor = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this._start_cursor.width = 1;
		this.AddChild(this._start_cursor);
		this._start_cursor.visible = false;
		this._end_cursor = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this._end_cursor.width = 1;
		this.AddChild(this._end_cursor);
		this._end_cursor.visible = false;
		this._start_cursor_data = undefined;
		this._end_cursor_data = undefined;
		this._focus_cursor = true;
		this._is_focus = false;
		this._event_start_x = 0;
		this._event_end_x = 0;
		this._event_start_y = 0;
		this._event_end_y = 0;
		this._click_drag_delta_x = 0;
		this._click_drag_delta_y = 0;
		this._is_click = false;
		this._is_longclick = false;
		this._is_click_cursor = false;
		this._is_click_cursor_name = "";
		this._drag_delta_x = 0;
		this._drag_delta_y = 0;
		this._cursor_margin_up = 0;
		this._cursor_margin_down = 0;
		this._margin_halign = 0;
		this._margin_valign = 0;
		this._is_drag_begin = false;
		this._password_mode = false;
		this._ims_padding = 0;
		this._default_text = ALittle.NewObject(ALittle.Text, this._ctrl_sys);
		this._default_text.y_type = 4;
		this._default_text.y_value = 0;
		this._display_view.AddChild(this._default_text);
		this._default_font_height = 20;
		this._link_map = ALittle.CreateValueWeakMap();
		this._pickup_rect = true;
		this._pickup_child = false;
		this._pickup_this = true;
		this._editable = true;
		this._is_selecting = false;
		this._can_drag_text = true;
		this._auto_ims = true;
		this._multi_cursor = false;
		this._input_align = false;
		this._regex = "";
		this._limit_len = 0;
		this.AddEventListener(___all_struct.get(292776509), this, this.HandleFocusOut);
		this.AddEventListener(___all_struct.get(-644464135), this, this.HandleFocusIn);
		this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(-1234078962), this, this.HandleTextInput);
		this.AddEventListener(___all_struct.get(-1604617962), this, this.HandleKeyDown);
		this.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		this.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this.AddEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
		this.AddEventListener(___all_struct.get(-439548260), this, this.HandleLongLButtonDown);
		this.ClearCharInfo();
		if (this._loop === undefined) {
			this._loop = ALittle.NewObject(ALittle.LoopFunction, this.Update.bind(this), -1, 1, 1);
		}
		A_LoopSystem.AddUpdater(this._loop);
	},
	GetCursor : function() {
		return this._cursor;
	},
	ClearLinkMap : function() {
		this._link_map = ALittle.CreateValueWeakMap();
	},
	get real_width() {
		return this._char_info_list[this._char_count - 1].acc_width;
	},
	get real_height() {
		return this._display_show.height;
	},
	get can_drag_text() {
		return this._can_drag_text;
	},
	set can_drag_text(value) {
		this._can_drag_text = value;
	},
	set auto_ims(value) {
		this._auto_ims = value;
	},
	get auto_ims() {
		return this._auto_ims;
	},
	get multi_cursor() {
		return this._multi_cursor;
	},
	set width(value) {
		if (this.width === value) {
			return;
		}
		ALittle.DisplayLayout.__setter.width.call(this, value);
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	set height(value) {
		if (this.height === value) {
			return;
		}
		ALittle.DisplayLayout.__setter.height.call(this, value);
		this.ResetCursor();
	},
	set cursor_red(value) {
		this._cursor.red = value;
		this._select.red = value;
	},
	get cursor_red() {
		return this._cursor.red;
	},
	set cursor_green(value) {
		this._cursor.green = value;
		this._select.green = value;
	},
	get cursor_green() {
		return this._cursor.green;
	},
	set cursor_blue(value) {
		this._cursor.blue = value;
		this._select.blue = value;
	},
	get cursor_blue() {
		return this._cursor.blue;
	},
	set font_bold(value) {
		if (this._font_text.bold === value) {
			return;
		}
		this._font_text.bold = value;
		this._default_text.bold = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.bold = value;
		}
	},
	set font_underline(value) {
		if (this._font_text.underline === value) {
			return;
		}
		this._font_text.underline = value;
		this._default_text.underline = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.underline = value;
		}
	},
	set font_deleteline(value) {
		if (this._font_text.deleteline === value) {
			return;
		}
		this._font_text.deleteline = value;
		this._default_text.deleteline = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.deleteline = value;
		}
	},
	set font_italic(value) {
		if (this._font_text.italic === value) {
			return;
		}
		this._font_text.italic = value;
		this._default_text.italic = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.italic = value;
		}
	},
	set font_path(value) {
		if (this._font_text.font_path === value) {
			return;
		}
		this._font_text.font_path = value;
		this._default_text.font_path = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.font_path = value;
		}
	},
	set font_size(value) {
		if (this._font_text.font_size === value) {
			return;
		}
		this._font_text.font_size = value;
		this._default_text.font_size = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.font_size = value;
		}
	},
	get font_path() {
		return this._font_text.font_path;
	},
	get font_size() {
		return this._font_text.font_size;
	},
	set font_red(value) {
		if (this._font_text.red === value) {
			return;
		}
		this._font_text.red = value;
		this._default_text.red = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.red = value;
		}
	},
	get font_red() {
		return this._font_text.red;
	},
	set font_green(value) {
		if (this._font_text.green === value) {
			return;
		}
		this._font_text.green = value;
		this._default_text.green = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.green = value;
		}
	},
	get font_green() {
		return this._font_text.green;
	},
	set font_blue(value) {
		if (this._font_text.blue === value) {
			return;
		}
		this._font_text.blue = value;
		this._default_text.blue = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.blue = value;
		}
	},
	get font_blue() {
		return this._font_text.blue;
	},
	set text(value) {
		this.ClearCharInfo();
		this.InsertTextNative(value);
		this.ResetShowXByCursor();
		this.ShowDefaultText();
	},
	get text() {
		let displaylist = this.CharInfoListToDisplayList(this._char_info_list);
		let text = "";
		let ___OBJECT_5 = displaylist;
		for (let k = 1; k <= ___OBJECT_5.length; ++k) {
			let v = ___OBJECT_5[k - 1];
			if (v === undefined) break;
			if (v.__class === "Text") {
				text = text + v.text;
			}
		}
		return text;
	},
	set default_text(value) {
		this._default_text.text = value;
	},
	get default_text() {
		return this._default_text.text;
	},
	set default_text_alpha(value) {
		this._default_text.alpha = value;
	},
	get default_text_alpha() {
		return this._default_text.alpha;
	},
	set display_list(value) {
		let char_info_list = this.DisplayListToCharInfoList(value);
		this.ClearCharInfo();
		this.InsertCharInfo(char_info_list, false);
		this.ResetCursor();
		this.ShowDefaultText();
	},
	get display_list() {
		return this.CharInfoListToDisplayList(this._char_info_list);
	},
	set start_cursor(value) {
		if (value === undefined) {
			return;
		}
		if (value === this._start_cursor) {
			return;
		}
		this.RemoveChild(this._start_cursor);
		value.x_type = 1;
		value.y_type = 1;
		value.width_type = 1;
		value.height_type = 1;
		this._start_cursor = value;
		this.AddChild(this._start_cursor);
		this._start_cursor.visible = false;
		this.ResetCursor();
	},
	get start_cursor() {
		return this._start_cursor;
	},
	set end_cursor(value) {
		if (value === undefined) {
			return;
		}
		if (value === this._end_cursor) {
			return;
		}
		this.RemoveChild(this._end_cursor);
		value.x_type = 1;
		value.y_type = 1;
		value.width_type = 1;
		value.height_type = 1;
		this._end_cursor = value;
		this.AddChild(this._end_cursor);
		this._end_cursor.visible = false;
		this.ResetCursor();
	},
	get end_cursor() {
		return this._end_cursor;
	},
	set cursor_margin_up(value) {
		if (value === this._cursor_margin_up) {
			return;
		}
		this._cursor_margin_up = value;
		this.ResetCursor();
	},
	get cursor_margin_up() {
		return this._cursor_margin_up;
	},
	set cursor_margin_down(value) {
		if (value === this._cursor_margin_down) {
			return;
		}
		this._cursor_margin_down = value;
		this.ResetCursor();
	},
	get cursor_margin_down() {
		return this._cursor_margin_down;
	},
	set margin_halign(value) {
		if (value === this._margin_halign) {
			return;
		}
		this._margin_halign = value;
		this._display_view.width_value = this._margin_halign * 2;
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	get margin_halign() {
		return this._margin_halign;
	},
	set margin_valign(value) {
		if (value === this._margin_valign) {
			return;
		}
		this._margin_valign = value;
		this._display_view.height_value = this._margin_valign * 2;
		this.ResetCursor();
	},
	get margin_valign() {
		return this._margin_valign;
	},
	set focus_cursor(value) {
		this._focus_cursor = value;
	},
	get focus_cursor() {
		return this._focus_cursor;
	},
	get cursor_x() {
		return this._cursor.x;
	},
	get cursor_y() {
		return this._cursor.y;
	},
	get cursor_b() {
		return (this._cursor.y + this._cursor.height) * this.scale_y + this._ims_padding;
	},
	get start_cursor_x() {
		return this._event_start_x;
	},
	get start_cursor_y() {
		return this._event_start_y;
	},
	get end_cursor_x() {
		return this._event_end_x;
	},
	get end_cursor_y() {
		return this._event_end_y;
	},
	get is_input() {
		return true;
	},
	get is_empty() {
		return this._char_count === 1;
	},
	get editable() {
		return this._editable;
	},
	set editable(value) {
		this._editable = value;
	},
	set ims_padding(value) {
		this._ims_padding = value;
	},
	get ims_padding() {
		return this._ims_padding;
	},
	set password_mode(value) {
		if (this._password_mode === value) {
			return;
		}
		this._password_mode = value;
		let display_list = this.CharInfoListToDisplayList(this._char_info_list);
		let char_info_list = this.DisplayListToCharInfoList(display_list);
		this.ClearCharInfo();
		this.InsertCharInfo(char_info_list, false);
		this.ResetCursor();
		this.ShowDefaultText();
	},
	get password_mode() {
		return this._password_mode;
	},
	get regex() {
		return this._regex;
	},
	set regex(value) {
		if (value === undefined) {
			value = "";
		}
		this._regex = value;
	},
	get limit_len() {
		return this._limit_len;
	},
	set limit_len(value) {
		if (value === undefined) {
			value = 0;
		}
		this._limit_len = value;
	},
	set input_align(value) {
		if (this._input_align === value) {
			return;
		}
		this._input_align = value;
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	get input_align() {
		return this._input_align;
	},
	Update : function() {
		if (this._cursor.abs_visible) {
			this._current_flash_alpha = this._current_flash_alpha + this._current_flash_dir;
			if ((this._current_flash_dir < 0 && this._current_flash_alpha < -0.05) || (this._current_flash_dir > 0 && this._current_flash_alpha > 1.5)) {
				this._current_flash_dir = -this._current_flash_dir;
			}
			this._cursor.alpha = this._current_flash_alpha;
		}
	},
	Draw : function() {
		if (this._draw_loop !== undefined) {
			return;
		}
		this._draw_loop = ALittle.NewObject(ALittle.LoopFunction, this.DrawImpl.bind(this), 1, 0, 1);
		A_LoopSystem.AddUpdater(this._draw_loop);
	},
	DrawImpl : function() {
		this._display_show.RemoveAllChild();
		let real_height = 0.0;
		let offset_x = 0.0;
		let last_child = undefined;
		let ___OBJECT_6 = this._char_info_list;
		for (let k = 1; k <= ___OBJECT_6.length; ++k) {
			let char_info = ___OBJECT_6[k - 1];
			if (char_info === undefined) break;
			let child = char_info.text_object;
			if (child === undefined) {
				child = char_info.ctrl;
			}
			if (child !== undefined && child !== last_child) {
				last_child = child;
				child.x_type = 2;
				child.x_value = offset_x;
				child.y_type = 4;
				child.y_value = 0;
				this._display_show.AddChild(child);
				offset_x = offset_x + child.width;
				if (child.height > real_height) {
					real_height = child.height;
				}
			}
		}
		this._display_show.height_value = real_height;
		this._draw_loop = undefined;
	},
	ClearCharInfo : function() {
		this._char_info_list = [];
		this._char_count = 0;
		let char_info = {};
		char_info.acc_width = 0;
		char_info.pre_width = 0;
		char_info.text_info = this.InitTextInfo();
		char_info.text_object = undefined;
		char_info.text = "";
		char_info.password_text = "";
		char_info.ctrl_info = undefined;
		char_info.ctrl = undefined;
		this._char_count = this._char_count + 1;
		this._char_info_list[this._char_count - 1] = char_info;
		this._char_cursor_it = 1;
		this._char_select_it = 2;
		this.Draw();
	},
	InsertCharInfo : function(char_info_list, selected) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return;
		}
		if (char_info_list[1 - 1] === undefined) {
			return;
		}
		let char_cursor_it_tmp = this._char_cursor_it;
		let x_char_info_list = [];
		let x_char_info_list_count = 0;
		let ___OBJECT_7 = char_info_list;
		for (let index = 1; index <= ___OBJECT_7.length; ++index) {
			let char_info = ___OBJECT_7[index - 1];
			if (char_info === undefined) break;
			if (char_info.ctrl_info === undefined) {
				x_char_info_list_count = this.SplitText(char_info, x_char_info_list, x_char_info_list_count);
			} else {
				++ x_char_info_list_count;
				x_char_info_list[x_char_info_list_count - 1] = char_info;
			}
		}
		char_info_list = x_char_info_list;
		let new_char_info_list = [];
		let new_char_count = 0;
		let text_info = undefined;
		let text_object = undefined;
		let char_acc_width = 0.0;
		for (let i = 1; i <= char_cursor_it_tmp; i += 1) {
			let char_info = this._char_info_list[i - 1];
			if (i !== 1 && char_info.ctrl_info === undefined) {
				text_info = char_info.text_info;
				text_object = char_info.text_object;
			} else {
				text_info = undefined;
				text_object = undefined;
			}
			char_acc_width = char_info.acc_width;
			new_char_count = new_char_count + 1;
			new_char_info_list[new_char_count - 1] = char_info;
		}
		let insert_count = 0;
		let ___OBJECT_8 = char_info_list;
		for (let key = 1; key <= ___OBJECT_8.length; ++key) {
			let display_info = ___OBJECT_8[key - 1];
			if (display_info === undefined) break;
			if (display_info.ctrl_info === undefined) {
				let display_object = undefined;
				if (text_info !== undefined && this.CompareTextInfo(display_info.text_info, text_info)) {
					display_object = text_object;
				} else {
					text_info = display_info.text_info;
					let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
					this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info.text_info));
					text_object = this._ctrl_sys.CreateControl(name, this._link_map);
					this._ctrl_sys.UnRegisterInfo(name);
					display_object = text_object;
				}
				this.SetDrawText(display_object);
				let object_text = "";
				let calc_text = display_info.text;
				let password_width = undefined;
				while (calc_text !== "") {
					let byte_count = ALittle.String_GetByteCount(calc_text, 1);
					let real_text = __sub(calc_text, 1, byte_count);
					let password_text = "*";
					let text_width = 0.0;
					calc_text = __sub(calc_text, byte_count + 1);
					if (this._password_mode) {
						if (password_width === undefined) {
							password_width = this._draw_text.native_show.CalcTextWidth(password_text);
						}
						text_width = password_width;
					} else {
						password_text = real_text;
						text_width = this._draw_text.native_show.CalcTextWidth(real_text);
					}
					let char_info = {};
					char_info.pre_width = char_acc_width;
					char_info.acc_width = char_info.pre_width + text_width;
					char_info.text_info = display_info.text_info;
					char_info.text_object = display_object;
					char_info.text = real_text;
					char_info.password_text = password_text;
					char_info.ctrl_info = undefined;
					char_info.ctrl = undefined;
					object_text = object_text + char_info.password_text;
					char_acc_width = char_info.acc_width;
					new_char_count = new_char_count + 1;
					new_char_info_list[new_char_count - 1] = char_info;
					insert_count = insert_count + 1;
				}
			} else if (display_info.ctrl_info !== undefined) {
				text_info = undefined;
				text_object = undefined;
				let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
				this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info.ctrl_info));
				let display_object = this._ctrl_sys.CreateControl(name, this._link_map);
				this._ctrl_sys.UnRegisterInfo(name);
				let char_info = {};
				char_info.pre_width = char_acc_width;
				char_info.acc_width = char_info.pre_width + display_object.width;
				char_info.text_info = display_info.text_info;
				char_info.text_object = undefined;
				char_info.text = undefined;
				char_info.password_text = undefined;
				char_info.ctrl_info = display_info.ctrl_info;
				char_info.ctrl = display_object;
				char_acc_width = char_info.acc_width;
				new_char_count = new_char_count + 1;
				new_char_info_list[new_char_count - 1] = char_info;
				insert_count = insert_count + 1;
			}
		}
		for (let i = char_cursor_it_tmp + 1; i <= this._char_count; i += 1) {
			let char_info = this._char_info_list[i - 1];
			if (char_info.ctrl_info === undefined && text_info !== undefined && this.CompareTextInfo(char_info.text_info, text_info)) {
				char_info.text_object = text_object;
			} else {
				text_info = undefined;
				text_object = undefined;
			}
			let width = char_info.acc_width - char_info.pre_width;
			char_info.pre_width = char_acc_width;
			char_info.acc_width = char_info.pre_width + width;
			char_acc_width = char_info.acc_width;
			new_char_count = new_char_count + 1;
			new_char_info_list[new_char_count - 1] = char_info;
		}
		let text = "";
		let object = undefined;
		let ___OBJECT_9 = new_char_info_list;
		for (let i = 1; i <= ___OBJECT_9.length; ++i) {
			let char_info = ___OBJECT_9[i - 1];
			if (char_info === undefined) break;
			if (object === undefined) {
				if (char_info.text_object !== undefined) {
					object = char_info.text_object;
					text = char_info.password_text;
				}
			} else {
				if (char_info.text_object === undefined) {
					object.text = text;
					object = undefined;
					text = "";
				} else if (char_info.text_object !== object) {
					object.text = text;
					object = char_info.text_object;
					text = char_info.password_text;
				} else {
					text = text + char_info.password_text;
				}
			}
		}
		if (object !== undefined) {
			object.text = text;
		}
		this._char_info_list = new_char_info_list;
		this._char_count = new_char_count;
		this._char_cursor_it = char_cursor_it_tmp + insert_count;
		if (selected) {
			this._char_select_it = char_cursor_it_tmp;
		} else {
			this._char_select_it = this._char_count + 1;
		}
		this.Draw();
	},
	DeleteCharInfo : function(begin_char_it, end_char_it) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return;
		}
		let new_char_info_list = [];
		let new_char_count = 0;
		let text_info = undefined;
		let text_object = undefined;
		let char_acc_width = 0.0;
		for (let i = 1; i <= begin_char_it; i += 1) {
			let char_info = this._char_info_list[i - 1];
			if (i !== 1 && char_info.ctrl_info === undefined) {
				text_info = char_info.text_info;
				text_object = char_info.text_object;
			}
			char_acc_width = char_info.acc_width;
			new_char_count = new_char_count + 1;
			new_char_info_list[new_char_count - 1] = char_info;
		}
		for (let i = end_char_it + 1; i <= this._char_count; i += 1) {
			let char_info = this._char_info_list[i - 1];
			if (char_info.ctrl_info === undefined && text_info !== undefined && this.CompareTextInfo(char_info.text_info, text_info)) {
				char_info.text_object = text_object;
			} else {
				text_info = undefined;
				text_object = undefined;
			}
			let width = char_info.acc_width - char_info.pre_width;
			char_info.pre_width = char_acc_width;
			char_info.acc_width = char_info.pre_width + width;
			char_acc_width = char_info.acc_width;
			new_char_count = new_char_count + 1;
			new_char_info_list[new_char_count - 1] = char_info;
		}
		let text = "";
		let object = undefined;
		let ___OBJECT_10 = new_char_info_list;
		for (let i = 1; i <= ___OBJECT_10.length; ++i) {
			let char_info = ___OBJECT_10[i - 1];
			if (char_info === undefined) break;
			if (object === undefined) {
				if (char_info.text_object !== undefined) {
					object = char_info.text_object;
					text = char_info.password_text;
				}
			} else {
				if (char_info.text_object === undefined) {
					object.text = text;
					object = undefined;
					text = "";
				} else if (char_info.text_object !== object) {
					object.text = text;
					object = char_info.text_object;
					text = char_info.password_text;
				} else {
					text = text + char_info.password_text;
				}
			}
		}
		if (object !== undefined) {
			object.text = text;
		}
		this._char_info_list = new_char_info_list;
		this._char_count = new_char_count;
		this._char_cursor_it = begin_char_it;
		this._char_select_it = this._char_count + 1;
		this.Draw();
	},
	GetIteratorByOffset : function(offset_x) {
		let real_offset_x = offset_x - this._display_show.x;
		if (real_offset_x < 0) {
			return 1;
		}
		let char_it = 1;
		let char_end_it = this._char_count + 1;
		while (char_it !== char_end_it) {
			let char_info = this._char_info_list[char_it - 1];
			if (real_offset_x <= char_info.acc_width) {
				let half_char_width = (char_info.acc_width - char_info.pre_width) * 0.5;
				if (real_offset_x - char_info.pre_width < half_char_width && char_it !== 1) {
					char_it = char_it - 1;
				}
				break;
			} else {
				char_it = char_it + 1;
			}
		}
		if (char_it === char_end_it) {
			char_end_it = char_end_it - 1;
			char_it = char_end_it;
		}
		return char_it;
	},
	ClickCursorToHome : function() {
		this._char_select_it = this._char_count + 1;
		this._char_cursor_it = 1;
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	ClickCursorToEnd : function() {
		this._char_select_it = this._char_count + 1;
		this._char_cursor_it = this._char_count;
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	ClickCursor : function(offset_x) {
		this._char_select_it = this._char_count + 1;
		this._char_cursor_it = this.GetIteratorByOffset(offset_x);
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	ClickMultiCursor : function(offset_x, trans) {
		let char_cursor_it = undefined;
		if (trans) {
			char_cursor_it = this._char_cursor_it;
		} else {
			char_cursor_it = this.GetIteratorByOffset(offset_x);
		}
		if (char_cursor_it !== 1) {
			this._char_cursor_it = char_cursor_it;
			this._char_select_it = char_cursor_it - 1;
		} else {
			if (this._char_count !== 1) {
				this._char_cursor_it = char_cursor_it + 1;
				this._char_select_it = char_cursor_it;
			} else {
				this._char_cursor_it = 1;
				this._char_select_it = 2;
			}
		}
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	ClickWordCursor : function(offset_x) {
		this._char_cursor_it = this.GetIteratorByOffset(offset_x);
		this._char_select_it = this._char_cursor_it;
		while (true) {
			let str = this._char_info_list[this._char_select_it - 1].password_text;
			if (str !== undefined && __len(str) === 1 && str !== "_" && this.CharIsNumber(str) === false && this.CharIsLetter(str) === false) {
				break;
			}
			if (this._char_select_it === 1) {
				break;
			}
			this._char_select_it = this._char_select_it - 1;
		}
		while (true) {
			let str = this._char_info_list[this._char_cursor_it - 1].password_text;
			if (str !== undefined && __len(str) === 1 && str !== "_" && this.CharIsNumber(str) === false && this.CharIsLetter(str) === false) {
				this._char_cursor_it = this._char_cursor_it - 1;
				break;
			}
			if (this._char_cursor_it === this._char_count) {
				break;
			}
			this._char_cursor_it = this._char_cursor_it + 1;
		}
		if (this._char_select_it < 1) {
			this._char_select_it = this._char_count + 1;
		}
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
		return this._char_select_it <= this._char_count;
	},
	SelectAll : function() {
		this._char_select_it = 1;
		this._char_cursor_it = this._char_count;
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	CursorOffsetLR : function(left) {
		if (this._char_select_it <= this._char_count && this._char_select_it !== this._char_cursor_it) {
			if (this._char_cursor_it > this._char_select_it && left) {
				this._char_cursor_it = this._char_select_it;
			} else if (this._char_cursor_it < this._char_select_it && !left) {
				this._char_cursor_it = this._char_select_it;
			}
			this._char_select_it = this._char_count + 1;
			return;
		}
		if (left) {
			if (this._char_cursor_it === 1) {
				return;
			}
			this._char_cursor_it = this._char_cursor_it - 1;
		} else {
			if (this._char_cursor_it === this._char_count) {
				return;
			}
			this._char_cursor_it = this._char_cursor_it + 1;
		}
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	SelectCursorOffsetLR : function(left) {
		if (this._char_select_it > this._char_count) {
			this._char_select_it = this._char_cursor_it;
		}
		if (left) {
			if (this._char_cursor_it === 1) {
				return;
			}
			this._char_cursor_it = this._char_cursor_it - 1;
		} else {
			if (this._char_cursor_it === this._char_count) {
				return;
			}
			this._char_cursor_it = this._char_cursor_it + 1;
		}
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	DragCursorBegin : function() {
		this._char_select_it = this._char_cursor_it;
	},
	DragCursor : function(offset_x) {
		this._char_cursor_it = this.GetIteratorByOffset(offset_x);
		if (this._char_info_list[this._char_cursor_it - 1].pre_width === -this._display_show.x && this._char_cursor_it !== 1 && offset_x < 0) {
			this._char_cursor_it = this._char_cursor_it - 1;
		}
		if (this._char_info_list[this._char_cursor_it - 1].acc_width === this._display_view.width - this._display_show.x && this._char_cursor_it !== this._char_count && offset_x > this._display_view.width) {
			this._char_cursor_it = this._char_cursor_it - 1;
		}
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	DragMultiCursor : function(offset_x) {
		offset_x = offset_x + this._drag_delta_x;
		this._char_cursor_it = this.GetIteratorByOffset(offset_x);
		if (this._char_info_list[this._char_cursor_it - 1].pre_width === -this._display_show.x && this._char_cursor_it !== 1 && offset_x < 0) {
			this._char_cursor_it = this._char_cursor_it - 1;
		}
		if (this._char_info_list[this._char_cursor_it - 1].acc_width === this._display_view.width - this._display_show.x && this._char_cursor_it !== this._char_count && offset_x > this._display_view.width) {
			this._char_cursor_it = this._char_cursor_it - 1;
		}
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	DragInput : function(delta_x) {
		let display_show_x = this._display_show.x + delta_x;
		let display_show_width = this._char_info_list[this._char_count - 1].acc_width;
		if (this._display_show.width < this._display_view.width || display_show_x > 0) {
			display_show_x = 0;
		} else if (display_show_x < this._display_view.width - display_show_width) {
			display_show_x = this._display_view.width - display_show_width;
		}
		this._display_show.x = display_show_x;
		this.ResetCursor();
	},
	ResetShowXByCursor : function() {
		let char_info = this._char_info_list[this._char_cursor_it - 1];
		let next_char_info = this._char_info_list[this._char_cursor_it + 1 - 1];
		let max_char_info = this._char_info_list[this._char_count - 1];
		if (next_char_info === undefined) {
			next_char_info = char_info;
		}
		let display_show_x = 0.0;
		if (char_info.pre_width < -this._display_show.x) {
			this._display_show.x = -char_info.pre_width;
		} else if (next_char_info.acc_width > this._display_view.width - this._display_show.x) {
			this._display_show.x = this._display_view.width - next_char_info.acc_width;
		} else if (max_char_info.acc_width + this._display_show.x < this._display_view.width && this._display_show.x < 0) {
			let display_x = this._display_view.width - max_char_info.acc_width;
			if (display_x > 0) {
				display_x = 0;
			}
			this._display_show.x = display_x;
		} else if (this._input_align && max_char_info.acc_width < this._display_view.width) {
			this._display_show.x = this._display_view.width - max_char_info.acc_width;
		}
	},
	ResetCursor : function() {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return;
		}
		let max_height = this._display_show.height;
		if (max_height > this._display_view.height) {
			max_height = this._display_view.height;
		}
		if (this._char_select_it > this._char_count || this._char_select_it === this._char_cursor_it) {
			this._select.visible = false;
			this._start_cursor.visible = false;
			this._end_cursor.visible = false;
			this._start_cursor_data = undefined;
			this._end_cursor_data = undefined;
			this._event_start_x = 0;
			this._event_end_x = 0;
			this._event_start_y = 0;
			this._event_end_y = 0;
			if (this._focus_cursor) {
				this._cursor.visible = this._is_focus;
			} else {
				this._cursor.visible = true;
			}
			let cursor_x = this._display_view.x + this._char_info_list[this._char_cursor_it - 1].acc_width + this._display_show.x;
			if (cursor_x < this._display_view.x || cursor_x > this._display_view.x + this._display_view.width) {
				this._cursor.visible = false;
			}
			let cursor_height = 0.0;
			let cursor_width = 0.0;
			let char = this._char_info_list[this._char_cursor_it - 1];
			if (char.ctrl !== undefined) {
				cursor_height = char.ctrl.height;
				cursor_width = 2;
			} else {
				if (char.text_object !== undefined) {
					cursor_height = char.text_object.height;
					cursor_width = this.GetCursorWidth(char.text_object.font_size);
				} else {
					let next_char = this._char_info_list[this._char_cursor_it + 1 - 1];
					if (next_char !== undefined) {
						if (next_char.ctrl !== undefined) {
							cursor_height = next_char.ctrl.height;
							cursor_width = 2;
						} else if (next_char.text_object !== undefined) {
							cursor_height = next_char.text_object.height;
							cursor_width = this.GetCursorWidth(next_char.text_object.font_size);
						} else {
							cursor_height = this._font_text.native_show.GetFontHeight();
							cursor_width = this.GetCursorWidth(this._font_text.font_size);
						}
					} else {
						cursor_height = this._font_text.native_show.GetFontHeight();
						cursor_width = this.GetCursorWidth(this._font_text.font_size);
					}
				}
			}
			if (cursor_height > max_height) {
				cursor_height = max_height;
			}
			if (cursor_height === 0) {
				cursor_height = this._default_text.font_height;
				if (cursor_height === 0) {
					cursor_height = this._default_font_height;
				}
			}
			this._cursor.width = cursor_width;
			this._cursor.height = cursor_height;
			this._cursor.x = cursor_x;
			this._cursor.y = this._margin_valign + (this._display_view.height - cursor_height);
			return;
		}
		if (this._multi_cursor === false) {
			this._cursor.visible = false;
		}
		this._select.visible = true;
		let select_x = this._display_view.x + this._char_info_list[this._char_select_it - 1].acc_width + this._display_show.x;
		let cursor_x = this._display_view.x + this._char_info_list[this._char_cursor_it - 1].acc_width + this._display_show.x;
		if (this._char_cursor_it > this._char_select_it) {
			if (cursor_x < this._display_view.x) {
				this._select.visible = false;
			}
			if (select_x > this._display_view.x + this._display_view.width) {
				this._select.visible = false;
			}
			let select_x_1 = select_x;
			let cursor_x_1 = cursor_x;
			if (select_x_1 < this._display_view.x) {
				select_x_1 = this._display_view.x;
			}
			if (cursor_x_1 > this._display_view.x + this._display_view.width) {
				cursor_x_1 = this._display_view.x + this._display_view.width;
			}
			this._select.y = this._margin_valign + (this._display_view.height - max_height);
			this._select.height = max_height;
			this._select.x = select_x_1;
			this._select.width = cursor_x_1 - select_x_1;
			if (this._multi_cursor === true) {
				this._cursor.visible = false;
				if (select_x < this._display_view.x || select_x > this._display_view.x + this._display_view.width) {
					this._start_cursor.visible = false;
				} else {
					this._start_cursor.visible = true;
					this._start_cursor.x = select_x - this._start_cursor.width;
					this._start_cursor.height = this._select.height + this._cursor_margin_up + this._cursor_margin_down;
					this._start_cursor.y = this._select.y - this._cursor_margin_up;
				}
				if (cursor_x > this._display_view.x + this._display_view.width || cursor_x < this._display_view.x) {
					this._end_cursor.visible = false;
				} else {
					this._end_cursor.visible = true;
					this._end_cursor.x = cursor_x;
					this._end_cursor.height = this._select.height + this._cursor_margin_up + this._cursor_margin_down;
					this._end_cursor.y = this._select.y - this._cursor_margin_up;
				}
				this._start_cursor_data = "select";
				this._end_cursor_data = "cursor";
				this._event_start_x = this._select.x;
				this._event_start_y = this._select.y;
				this._event_end_x = this._select.x + this._select.width;
				this._event_end_y = this._select.y;
			}
		} else if (this._char_cursor_it < this._char_select_it) {
			if (select_x < this._display_view.x) {
				this._select.visible = false;
			}
			if (cursor_x > this._display_view.x + this._display_view.width) {
				this._select.visible = false;
			}
			let select_x_1 = select_x;
			let cursor_x_1 = cursor_x;
			if (cursor_x_1 < this._display_view.x) {
				cursor_x_1 = this._display_view.x;
			}
			if (select_x_1 > this._display_view.x + this._display_view.width) {
				select_x_1 = this._display_view.x + this._display_view.width;
			}
			this._select.y = this._margin_valign + (this._display_view.height - max_height);
			this._select.height = max_height;
			this._select.x = cursor_x_1;
			this._select.width = select_x_1 - cursor_x_1;
			if (this._multi_cursor === true) {
				this._cursor.visible = false;
				if (cursor_x < this._display_view.x || cursor_x > this._display_view.x + this._display_view.width) {
					this._start_cursor.visible = false;
				} else {
					this._start_cursor.visible = true;
					this._start_cursor.x = cursor_x - this._start_cursor.width;
					this._start_cursor.height = this._select.height + this._cursor_margin_up + this._cursor_margin_down;
					this._start_cursor.y = this._select.y - this._cursor_margin_up;
				}
				if (select_x > this._display_view.x + this._display_view.width || select_x < this._display_view.x) {
					this._end_cursor.visible = false;
				} else {
					this._end_cursor.visible = true;
					this._end_cursor.x = select_x;
					this._end_cursor.height = this._select.height + this._cursor_margin_up + this._cursor_margin_down;
					this._end_cursor.y = this._select.y - this._cursor_margin_up;
				}
				this._start_cursor_data = "cursor";
				this._end_cursor_data = "select";
				this._event_start_x = this._select.x;
				this._event_start_y = this._select.y;
				this._event_end_x = this._select.x + this._select.width;
				this._event_end_y = this._select.y;
			}
		}
	},
	ShowDefaultText : function() {
		if (this._is_focus === false) {
			if (this._focus_cursor && this.is_empty) {
				this._default_text.visible = true;
			} else {
				this._default_text.visible = false;
			}
		} else {
			this._default_text.visible = false;
		}
	},
	DeleteSelectText : function() {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return false;
		}
		if (this._char_select_it > this._char_count) {
			return false;
		}
		if (this._char_select_it === this._char_cursor_it) {
			return false;
		}
		let begin_char_it = undefined;
		let end_char_it = undefined;
		if (this._char_select_it > this._char_cursor_it) {
			begin_char_it = this._char_cursor_it;
			end_char_it = this._char_select_it;
		} else {
			end_char_it = this._char_cursor_it;
			begin_char_it = this._char_select_it;
		}
		this.DeleteCharInfo(begin_char_it, end_char_it);
		this.ResetCursor();
		return true;
	},
	CheckDisplayListRegexLimit : function(display_list) {
		if (this._regex === "") {
			return false;
		}
		let text = "";
		let ___OBJECT_11 = display_list;
		for (let k = 1; k <= ___OBJECT_11.length; ++k) {
			let v = ___OBJECT_11[k - 1];
			if (v === undefined) break;
			if (v.__class !== "Text") {
				return false;
			}
			text = text + v.text;
		}
		return this.CheckTextRegexLimit(text);
	},
	InsertDisplayListNative : function(display_list, selected) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return false;
		}
		if (this.CheckDisplayListRegexLimit(display_list) === false) {
			return false;
		}
		this.DeleteSelectText();
		let char_info = this._char_info_list[this._char_cursor_it - 1];
		let char_info_list = this.DisplayListToCharInfoList(display_list, char_info.text_info);
		this.InsertCharInfo(char_info_list, selected);
		return true;
	},
	CheckTextRegexLimit : function(text) {
		if (this._limit_len > 0) {
			let text_len = ALittle.String_GetWordCount(text);
			if (text_len > this._limit_len) {
				return false;
			}
			let select_len = 0;
			let displaylist = this.GetSelectText();
			let ___OBJECT_12 = displaylist;
			for (let k = 1; k <= ___OBJECT_12.length; ++k) {
				let v = ___OBJECT_12[k - 1];
				if (v === undefined) break;
				if (v.__class === "Text") {
					select_len = select_len + ALittle.String_GetWordCount(v.text);
				}
			}
			displaylist = this.display_list;
			let total_len = 0;
			let ___OBJECT_13 = displaylist;
			for (let k = 1; k <= ___OBJECT_13.length; ++k) {
				let v = ___OBJECT_13[k - 1];
				if (v === undefined) break;
				if (v.__class === "Text") {
					total_len = total_len + ALittle.String_GetWordCount(v.text);
				}
			}
			if (total_len - select_len + text_len > this._limit_len) {
				return false;
			}
		}
		if (this._regex !== "") {
			while (text !== "") {
				let byte_count = ALittle.String_GetByteCount(text, 1);
				let sub_text = __sub(text, 1, byte_count);
				let start_it = __find(sub_text, this._regex);
				if (start_it === undefined) {
					return false;
				}
				text = __sub(text, byte_count + 1);
			}
		}
		return true;
	},
	InsertTextNative : function(text) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return false;
		}
		if (this.CheckTextRegexLimit(text) === false) {
			return false;
		}
		this.DeleteSelectText();
		let char_info_list = [];
		let new_char_info = {};
		new_char_info.acc_width = 0;
		new_char_info.pre_width = 0;
		new_char_info.text_info = this.InitTextInfo();
		new_char_info.text_object = undefined;
		new_char_info.text = text;
		new_char_info.ctrl_info = undefined;
		new_char_info.ctrl = undefined;
		char_info_list[1 - 1] = new_char_info;
		this.InsertCharInfo(char_info_list, false);
		return true;
	},
	GetSelectText : function() {
		let select_text = [];
		let select_text_count = 0;
		if (this._char_select_it > this._char_count) {
			return [];
		}
		if (this._char_select_it === this._char_cursor_it) {
			return [];
		}
		let char_it = undefined;
		let char_end = undefined;
		if (this._char_select_it > this._char_cursor_it) {
			char_it = this._char_cursor_it + 1;
			char_end = this._char_select_it;
		} else {
			char_end = this._char_cursor_it;
			char_it = this._char_select_it + 1;
		}
		while (char_it <= char_end) {
			++ select_text_count;
			select_text[select_text_count - 1] = this._char_info_list[char_it - 1];
			char_it = char_it + 1;
		}
		return this.CharInfoListToDisplayList(select_text);
	},
	GetSelectWord : function() {
		let select_text = [];
		let select_text_count = 0;
		if (this._char_select_it > this._char_count) {
			return "";
		}
		if (this._char_select_it === this._char_cursor_it) {
			return "";
		}
		let char_it = undefined;
		let char_end = undefined;
		if (this._char_select_it > this._char_cursor_it) {
			char_it = this._char_cursor_it + 1;
			char_end = this._char_select_it;
		} else {
			char_end = this._char_cursor_it;
			char_it = this._char_select_it + 1;
		}
		while (char_it <= char_end) {
			++ select_text_count;
			select_text[select_text_count - 1] = this._char_info_list[char_it - 1];
			char_it = char_it + 1;
		}
		return this.CharInfoListToWord(select_text);
	},
	DeleteText : function(left) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return false;
		}
		if (this.DeleteSelectText()) {
			return true;
		}
		if (left) {
			if (this._char_cursor_it === 1) {
				return false;
			}
			let end_it = this._char_cursor_it;
			let begin_it = this._char_cursor_it - 1;
			this.DeleteCharInfo(begin_it, end_it);
		} else {
			if (this._char_cursor_it === this._char_count) {
				return false;
			}
			let begin_it = this._char_cursor_it;
			let end_it = this._char_cursor_it + 1;
			this.DeleteCharInfo(begin_it, end_it);
		}
		return true;
	},
	SetCursor : function(rel_x, rel_y) {
		if (this._auto_ims) {
			this.OpenIME();
		}
		this._is_selecting = false;
		if (this._multi_cursor) {
			this._multi_cursor = false;
			this._start_cursor.visible = false;
			this._end_cursor.visible = false;
			this._cursor.visible = true;
			this.ClickCursor(rel_x - this._display_view.x);
		} else {
			this.ClickCursor(rel_x - this._display_view.x);
		}
	},
	SetMultiCursor : function(rel_x, rel_y) {
		if (this._auto_ims) {
			this.OpenIME();
		}
		this._is_selecting = true;
		if (this._multi_cursor === false) {
			this._multi_cursor = true;
			this._cursor.visible = false;
			this._start_cursor.visible = true;
			this._end_cursor.visible = true;
			this.ClickMultiCursor(rel_x - this._display_view.x, false);
		} else {
			this.ClickMultiCursor(rel_x - this._display_view.x, false);
		}
	},
	TransToCursor : function() {
		if (this._end_cursor_data === "select") {
			this._char_cursor_it = this._char_select_it;
		}
		this._char_select_it = this._char_count + 1;
		this._is_selecting = false;
		this._multi_cursor = false;
		this._start_cursor.visible = false;
		this._end_cursor.visible = false;
		this._cursor.visible = true;
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	TransToMulti : function() {
		if (this._multi_cursor) {
			return;
		}
		this._is_selecting = true;
		this._multi_cursor = true;
		this._cursor.visible = false;
		this._start_cursor.visible = true;
		this._end_cursor.visible = true;
		this.ClickMultiCursor(undefined, true);
	},
	OpenIME : function(x, y, width, height) {
		if (this._editable) {
			if (x !== undefined && y !== undefined && width !== undefined && height !== undefined) {
				ALittle.System_SetIMERect(__floor(x), __floor(y), __floor(width), __floor(height));
			} else {
				let [global_x, global_y] = this.LocalToGlobal();
				global_x = global_x + this.cursor_x;
				global_y = global_y + (this.cursor_y + this.font_size) * this.scale_y;
				ALittle.System_SetIMERect(__floor(global_x), __floor(global_y), 10, __floor(5 + this._ims_padding));
			}
			ALittle.System_OpenIME();
			this.ResetCursor();
		}
	},
	CloseIME : function() {
		ALittle.System_CloseIME();
	},
	InsertText : function(display_list, selected) {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this.InsertDisplayListNative(display_list, selected);
		this._is_selecting = false;
		this._multi_cursor = false;
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
		this.ShowDefaultText();
	},
	InsertWord : function(word_text) {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this.InsertTextNative(word_text);
		this._is_selecting = false;
		this.TransToCursor();
		this.ShowDefaultText();
	},
	CopyText : function(return_cursor) {
		if (this._password_mode) {
			return;
		}
		let select_text = this.GetSelectText();
		if (select_text[1 - 1] !== undefined) {
			ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text));
		}
		if (return_cursor) {
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	CopyWord : function(return_cursor) {
		if (this._password_mode) {
			return;
		}
		let select_text = this.GetSelectWord();
		if (select_text !== undefined) {
			ALittle.System_SetClipboardText(select_text);
		}
		if (return_cursor) {
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	CutText : function() {
		if (this._password_mode) {
			return;
		}
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		let select_text = this.GetSelectText();
		if (select_text[1 - 1] !== undefined) {
			ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text));
			this.DeleteSelectText();
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	CutWord : function() {
		if (this._password_mode) {
			return;
		}
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		let select_text = this.GetSelectWord();
		if (select_text !== undefined) {
			ALittle.System_SetClipboardText(select_text);
			this.DeleteSelectText();
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	PasteText : function() {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		if (ALittle.System_HasClipboardText()) {
			let content = ALittle.System_GetClipboardText();
			let [error, new_content] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (error === undefined && __type(new_content) === "table" && this.CheckDisplayList(new_content)) {
				if (this.CheckAtKeyInput(new_content)) {
					return;
				}
				this.InsertDisplayListNative(new_content, false);
			} else {
				if (this.CheckAtKeyInput(content)) {
					return;
				}
				this.InsertTextNative(content);
			}
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	PasteWord : function() {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		if (ALittle.System_HasClipboardText()) {
			let content = ALittle.System_GetClipboardText();
			this.InsertTextNative(content);
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	Clear : function() {
		this.ClearCharInfo();
		this.ShowDefaultText();
	},
	Delete : function() {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		this.DeleteText(true);
		this.TransToCursor();
		this.ShowDefaultText();
	},
	GetWord : function() {
		return this.CharInfoListToWord(this._char_info_list);
	},
	HandleFocusOut : function(event) {
		if (this._auto_ims) {
			ALittle.System_CloseIME();
		}
		this._is_focus = false;
		if (this._focus_cursor) {
			if (this._multi_cursor === false) {
				this._cursor.visible = false;
			}
		}
		this.ShowDefaultText();
	},
	HandleFocusIn : function(event) {
		if (this._auto_ims) {
			this.OpenIME();
		}
		this._is_focus = true;
		this.ResetShowXByCursor();
		this.ResetCursor();
		this.ShowDefaultText();
	},
	HandleMoveIn : function(event) {
		ALittle.System_SetEditCursor();
	},
	HandleMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleLButtonDown : function(event) {
		if (this._multi_cursor === false) {
			this._is_longclick = false;
			if (event.rel_x > this._display_view.x && event.rel_x <= this._display_view.x + this._display_view.width && event.rel_y >= this._display_view.y && event.rel_y <= this._display_view.y + this._display_view.height) {
				if (event.count % 3 === 1) {
					this._is_selecting = false;
					this.ClickCursor(event.rel_x - this._display_view.x);
					this.DispatchEvent(___all_struct.get(-683607428), {});
				} else if (event.count % 3 === 2) {
					this._is_selecting = this.ClickWordCursor(event.rel_x - this._display_view.x);
				} else {
					this._is_selecting = true;
					this.SelectAll();
				}
				this._is_click = true;
			} else {
				this._is_click = false;
			}
		} else {
			this._click_drag_delta_x = 0;
			this._click_drag_delta_y = 0;
			this._is_click = false;
			this._is_click_cursor = false;
			this._is_click_cursor_name = "";
			this._is_longclick = false;
			if (this._start_cursor.visible && event.rel_x >= this._start_cursor.x && event.rel_x <= this._start_cursor.x + this._start_cursor.width && event.rel_y >= this._start_cursor.y && event.rel_y <= this._start_cursor.y + this._start_cursor.height) {
				this._is_click_cursor = true;
				this._is_click_cursor_name = "start";
			} else if (this._end_cursor.visible && event.rel_x >= this._end_cursor.x && event.rel_x <= this._end_cursor.x + this._end_cursor.width && event.rel_y >= this._end_cursor.y && event.rel_y <= this._end_cursor.y + this._end_cursor.height) {
				this._is_click_cursor = true;
				this._is_click_cursor_name = "end";
			} else {
				if (event.rel_x >= this._display_view.x && event.rel_x <= this._display_view.x + this._display_view.width && event.rel_y >= this._display_view.y && event.rel_y <= this._display_view.y + this._display_view.height) {
					this._is_click = true;
				}
			}
		}
	},
	HandleLButtonUp : function(event) {
		if (this._multi_cursor === true) {
			if (this._is_click && this._is_longclick === false && this._click_drag_delta_x < 2 && this._click_drag_delta_y < 2) {
				this._multi_cursor = false;
				this._start_cursor.visible = false;
				this._end_cursor.visible = false;
				this._cursor.visible = true;
				this.ClickCursor(event.rel_x - this._display_view.x);
				this.DispatchEvent(___all_struct.get(-683607428), {});
			}
		}
	},
	CheckAtKeyInput : function(input_text) {
		if (input_text !== "@") {
			return false;
		}
		let char_cursor_it = this._char_cursor_it;
		if (this._char_cursor_it === 1) {
			this.DispatchEvent(___all_struct.get(1816229739), {});
			return true;
		}
		let char_info = this._char_info_list[this._char_cursor_it - 1];
		let forward_text = char_info.text;
		if (!(this.CharIsNumber(forward_text) || this.CharIsLetter(forward_text))) {
			this.DispatchEvent(___all_struct.get(1816229739), {});
			return true;
		}
		return false;
	},
	HandleTextInput : function(event) {
		let is_change = false;
		if (this._multi_cursor === false) {
			if ((this._editable || event.custom)) {
				if (this.CheckAtKeyInput(event.text)) {
					return;
				}
				this._is_selecting = false;
				is_change = this.InsertTextNative(event.text);
			}
		} else {
			if (this._is_selecting && this._editable) {
				this._is_selecting = false;
				is_change = this.InsertTextNative(event.text);
				this._multi_cursor = false;
			}
		}
		if (is_change) {
			this.DispatchEvent(___all_struct.get(958494922), {});
			this.UpdateFontText();
			this.ResetShowXByCursor();
			this.ResetCursor();
			this.ShowDefaultText();
		}
	},
	HandleKeyDown : function(event) {
		let is_change = false;
		if (event.sym === 1073741904) {
			if (this._multi_cursor === false) {
				if (event.mod & 0x0003 === 0) {
					this._is_selecting = false;
					this.CursorOffsetLR(true);
				} else {
					this._is_selecting = true;
					this.SelectCursorOffsetLR(true);
				}
			}
			event.handled = true;
		} else if (event.sym === 1073741903) {
			if (this._multi_cursor === false) {
				if (event.mod & 0x0003 === 0) {
					this._is_selecting = false;
					this.CursorOffsetLR(false);
				} else {
					this._is_selecting = true;
					this.SelectCursorOffsetLR(false);
				}
			}
			event.handled = true;
		} else if (event.sym === 8) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					is_change = this.DeleteText(true);
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					is_change = this.DeleteText(true);
					this._multi_cursor = false;
				}
			}
			event.handled = true;
		} else if (event.sym === 127) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					is_change = this.DeleteText(false);
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					is_change = this.DeleteText(false);
					this._multi_cursor = false;
				}
			}
			event.handled = true;
		} else if (event.sym === 1073741898) {
			this._is_selecting = false;
			this.ClickCursorToHome();
			event.handled = true;
		} else if (event.sym === 1073741901) {
			this._is_selecting = false;
			this.ClickCursorToEnd();
			event.handled = true;
		} else if (event.sym === 13 || event.sym === 1073741912) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				this.DispatchEvent(___all_struct.get(776398171), {});
				event.handled = true;
			}
		} else if (event.sym === 120 && event.mod & 0x00c0 !== 0) {
			if (this._multi_cursor === false) {
				if ((this._editable || event.custom) && !this._password_mode) {
					this._is_selecting = false;
					let select_text = this.GetSelectText();
					if (select_text[1 - 1] !== undefined) {
						ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text));
						is_change = this.DeleteSelectText();
					}
				}
			} else {
				if ((this._is_selecting && this._editable) && !this._password_mode) {
					this._is_selecting = false;
					let select_text = this.GetSelectText();
					if (select_text[1 - 1] !== undefined) {
						ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text));
						is_change = this.DeleteSelectText();
					}
					this._multi_cursor = false;
				}
			}
			event.handled = true;
		} else if (event.sym === 99 && event.mod & 0x00c0 !== 0) {
			if (!this._password_mode) {
				let select_text = this.GetSelectText();
				if (select_text[1 - 1] !== undefined) {
					ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text));
				}
			}
			event.handled = true;
		} else if (event.sym === 118 && event.mod & 0x00c0 !== 0) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					if (ALittle.System_HasClipboardText()) {
						let content = ALittle.System_GetClipboardText();
						let [error, new_content] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
						if (error === undefined && __type(new_content) === "table" && this.CheckDisplayList(new_content)) {
							if (this.CheckAtKeyInput(new_content)) {
								return;
							}
							is_change = this.InsertDisplayListNative(new_content, false);
						} else {
							if (this.CheckAtKeyInput(content)) {
								return;
							}
							is_change = this.InsertTextNative(content);
						}
					}
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					if (ALittle.System_HasClipboardText()) {
						let content = ALittle.System_GetClipboardText();
						let [error, new_content] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
						if (error === undefined && __type(new_content) === "table" && this.CheckDisplayList(new_content)) {
							is_change = this.InsertDisplayListNative(new_content, false);
						} else {
							is_change = this.InsertTextNative(content);
						}
					}
					this._multi_cursor = false;
				}
			}
			event.handled = true;
		} else if (event.sym === 97 && event.mod & 0x00c0 !== 0) {
			this._is_selecting = true;
			this.SelectAll();
			event.handled = true;
		}
		if (is_change) {
			this.DispatchEvent(___all_struct.get(958494922), {});
			this._current_flash_alpha = 1.5;
			this.UpdateFontText();
			this.ResetShowXByCursor();
			this.ResetCursor();
			this.ShowDefaultText();
		}
	},
	HandleDragBegin : function(event) {
		if (this._can_drag_text === false) {
			return;
		}
		if (this._multi_cursor === false) {
			if (this._is_click) {
				this._is_drag_begin = true;
				this._is_selecting = true;
				this.DragCursorBegin();
			} else {
				this._is_drag_begin = false;
			}
		} else {
			if (this._is_click_cursor) {
				if ((this._is_click_cursor_name === "start" && this._start_cursor_data === "select") || (this._is_click_cursor_name === "end" && this._end_cursor_data === "select")) {
					let char_temp_it = this._char_select_it;
					this._char_select_it = this._char_cursor_it;
					this._char_cursor_it = char_temp_it;
				}
				if (this._is_click_cursor_name === "start") {
					this._drag_delta_x = this._start_cursor.x + this._start_cursor.width - event.rel_x;
					this._drag_delta_y = this._start_cursor.y + this._cursor_margin_up + (this._start_cursor.height - this._cursor_margin_up - this._cursor_margin_down) / 2 - event.rel_y;
				} else if (this._is_click_cursor_name === "end") {
					this._drag_delta_x = this._end_cursor.x - event.rel_x;
					this._drag_delta_y = this._end_cursor.y + this._cursor_margin_up + (this._end_cursor.height - this._cursor_margin_up - this._cursor_margin_down) / 2 - event.rel_y;
				}
				this._is_drag_begin = true;
				this.DispatchEvent(___all_struct.get(1424993548), {});
			} else if (this._is_click) {
				this._is_drag_begin = true;
				this.DispatchEvent(___all_struct.get(1424993548), {});
			} else {
				this._is_drag_begin = false;
			}
		}
	},
	HandleDrag : function(event) {
		if (this._can_drag_text === false) {
			return;
		}
		if (this._is_drag_begin === false) {
			return;
		}
		if (this._multi_cursor === false) {
			if (this._is_selecting === false) {
				return;
			}
			this.DragCursor(event.rel_x - this._display_view.x);
		} else {
			if (this._is_click_cursor) {
				this.DragMultiCursor(event.rel_x - this._display_view.x);
			} else {
				this._click_drag_delta_x = this._click_drag_delta_x + __abs(event.delta_x);
				this._click_drag_delta_y = this._click_drag_delta_y + __abs(event.delta_y);
				this.DragInput(event.delta_x);
			}
			this.DispatchEvent(___all_struct.get(-605767802), {});
		}
	},
	HandleDragEnd : function(event) {
		if (this._can_drag_text === false) {
			return;
		}
		if (this._is_drag_begin === false) {
			return;
		}
		if (this._multi_cursor) {
			if (this._cursor.visible) {
				this._multi_cursor = false;
			}
			this.DispatchEvent(___all_struct.get(-884368490), {});
		}
	},
	HandleLongLButtonDown : function(event) {
		if (this._is_click) {
			if (this.editable === false) {
				this._is_selecting = true;
				if (this._multi_cursor === false) {
					this._multi_cursor = true;
					this._cursor.visible = false;
					this._start_cursor.visible = true;
					this._end_cursor.visible = true;
					this.ClickMultiCursor(event.rel_x - this._display_view.x, false);
				} else {
					this.ClickMultiCursor(event.rel_x - this._display_view.x, false);
				}
			} else {
				this._multi_cursor = false;
				this._start_cursor.visible = false;
				this._end_cursor.visible = false;
				this._cursor.visible = true;
				this.ClickCursor(event.rel_x - this._display_view.x);
			}
			let e = {};
			e.target = this;
			e.abs_x = event.abs_x;
			e.abs_y = event.abs_y;
			e.rel_x = event.rel_x;
			e.rel_y = event.rel_y;
			this.DispatchEvent(___all_struct.get(1640499878), e);
			this._is_longclick = true;
		}
	},
}, "ALittle.RichInput");

}