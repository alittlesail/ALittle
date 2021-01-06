{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1949279026, "ALittle.RichEditFontChangedEvent", {
name : "ALittle.RichEditFontChangedEvent", ns_name : "ALittle", rl_name : "RichEditFontChangedEvent", hash_code : 1949279026,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1053992999, "ALittle.RichEditCursorClickEvent", {
name : "ALittle.RichEditCursorClickEvent", ns_name : "ALittle", rl_name : "RichEditCursorClickEvent", hash_code : -1053992999,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-923963966, "ALittle.RichEditCharInfo", {
name : "ALittle.RichEditCharInfo", ns_name : "ALittle", rl_name : "RichEditCharInfo", hash_code : -923963966,
name_list : ["acc_width","pre_width","text_info","text_object","text","ctrl_info","ctrl"],
type_list : ["double","double","ALittle.DisplayInfo","ALittle.Text","string","ALittle.DisplayInfo","ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(774620468, "ALittle.UIRichEditLongClickEvent", {
name : "ALittle.UIRichEditLongClickEvent", ns_name : "ALittle", rl_name : "UIRichEditLongClickEvent", hash_code : 774620468,
name_list : ["target","abs_x","abs_y","rel_x","rel_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(556044369, "ALittle.RichEditLineInfo", {
name : "ALittle.RichEditLineInfo", ns_name : "ALittle", rl_name : "RichEditLineInfo", hash_code : 556044369,
name_list : ["char_list","char_count","child_list","child_count","container","acc_height","pre_height","force_line"],
type_list : ["List<ALittle.RichEditCharInfo>","int","List<ALittle.DisplayObject>","int","ALittle.DisplayLayout","double","double","bool"],
option_map : {}
})
ALittle.RegStruct(291295687, "ALittle.RichEditMultiDragEvent", {
name : "ALittle.RichEditMultiDragEvent", ns_name : "ALittle", rl_name : "RichEditMultiDragEvent", hash_code : 291295687,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-203792390, "ALittle.RichEditMultiDragEndEvent", {
name : "ALittle.RichEditMultiDragEndEvent", ns_name : "ALittle", rl_name : "RichEditMultiDragEndEvent", hash_code : -203792390,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(9565867, "ALittle.RichEditMultiDragBeginEvent", {
name : "ALittle.RichEditMultiDragBeginEvent", ns_name : "ALittle", rl_name : "RichEditMultiDragBeginEvent", hash_code : 9565867,
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
ALittle.RichEdit = JavaScript.Class(ALittle.DisplayLayout, {
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
	UpdateFontText : function() {
		let line_list = this._line_list;
		let char_info = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1];
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
			this.DispatchEvent(___all_struct.get(1949279026), {});
		}
	},
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
	GetCharInfoList : function() {
		let char_info_list = [];
		let char_info_list_count = 0;
		let ___OBJECT_3 = this._line_list;
		for (let line_index = 1; line_index <= ___OBJECT_3.length; ++line_index) {
			let line_info = ___OBJECT_3[line_index - 1];
			if (line_info === undefined) break;
			let ___OBJECT_4 = line_info.char_list;
			for (let char_index = 1; char_index <= ___OBJECT_4.length; ++char_index) {
				let char_info = ___OBJECT_4[char_index - 1];
				if (char_info === undefined) break;
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = char_info;
			}
		}
		return char_info_list;
	},
	JoinCharInfoList : function(char_info_list) {
		let new_char_info_list = [];
		let new_char_info_list_count = 0;
		let text_info = undefined;
		let text_list = undefined;
		let text_list_count = 0;
		let ___OBJECT_5 = char_info_list;
		for (let char_index = 1; char_index <= ___OBJECT_5.length; ++char_index) {
			let char_info = ___OBJECT_5[char_index - 1];
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
							let new_char_info = {};
							new_char_info.acc_width = 0;
							new_char_info.pre_width = 0;
							new_char_info.text_info = text_info;
							new_char_info.text_object = undefined;
							new_char_info.text = text;
							new_char_info.ctrl_info = undefined;
							new_char_info.ctrl = undefined;
							++ new_char_info_list_count;
							new_char_info_list[new_char_info_list_count - 1] = new_char_info;
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
						let new_char_info = {};
						new_char_info.acc_width = 0;
						new_char_info.pre_width = 0;
						new_char_info.text_info = text_info;
						new_char_info.text_object = undefined;
						new_char_info.text = text;
						new_char_info.ctrl_info = undefined;
						new_char_info.ctrl = undefined;
						++ new_char_info_list_count;
						new_char_info_list[new_char_info_list_count - 1] = new_char_info;
					}
					text_info = undefined;
					text_list = undefined;
					text_list_count = 0;
				}
				let new_char_info = {};
				new_char_info.acc_width = 0;
				new_char_info.pre_width = 0;
				new_char_info.text_info = text_info;
				new_char_info.text_object = undefined;
				new_char_info.text = undefined;
				new_char_info.ctrl_info = char_info.ctrl_info;
				new_char_info.ctrl = char_info.ctrl;
				++ new_char_info_list_count;
				new_char_info_list[new_char_info_list_count - 1] = new_char_info;
			}
		}
		if (text_info !== undefined) {
			let text = ALittle.String_Join(text_list, "");
			if (text !== "") {
				let new_char_info = {};
				new_char_info.acc_width = 0;
				new_char_info.pre_width = 0;
				new_char_info.text_info = text_info;
				new_char_info.text_object = undefined;
				new_char_info.text = text;
				new_char_info.ctrl_info = undefined;
				new_char_info.ctrl = undefined;
				++ new_char_info_list_count;
				new_char_info_list[new_char_info_list_count - 1] = new_char_info;
			}
		}
		return new_char_info_list;
	},
	CharInfoListToDisplayList : function(list) {
		let display_list = [];
		let display_list_count = 0;
		let text_info = undefined;
		let text_list = undefined;
		let text_list_count = 0;
		let ___OBJECT_6 = list;
		for (let char_index = 1; char_index <= ___OBJECT_6.length; ++char_index) {
			let char_info = ___OBJECT_6[char_index - 1];
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
		let ___OBJECT_7 = list;
		for (let char_index = 1; char_index <= ___OBJECT_7.length; ++char_index) {
			let char_info = ___OBJECT_7[char_index - 1];
			if (char_info === undefined) break;
			if (char_info.ctrl_info === undefined) {
				++ text_list_count;
				text_list[text_list_count - 1] = char_info.text;
			}
		}
		return ALittle.String_Join(text_list, "");
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
				let new_char_info = ALittle.String_CopyTable(char_info);
				new_char_info.text = __sub(text, 1, start_index_1 - 1);
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				new_char_info = ALittle.String_CopyTable(char_info);
				new_char_info.text = "\n";
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				text = __sub(text, start_index_1 + 1);
			} else if (start_index_2 !== undefined) {
				let new_char_info = ALittle.String_CopyTable(char_info);
				new_char_info.text = __sub(text, 1, start_index_2 - 1);
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				new_char_info = ALittle.String_CopyTable(char_info);
				new_char_info.text = "\t";
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				text = __sub(text, start_index_2 + 1);
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
		this._enter_key_height = 20;
		this._line_list = [];
		this._line_count = 0;
		this._font_text = ALittle.NewObject(ALittle.Text, this._ctrl_sys);
		this._draw_text = ALittle.NewObject(ALittle.Text, this._ctrl_sys);
		this._line_start_it = undefined;
		this._line_cursor_it = undefined;
		this._char_cursor_it = undefined;
		this._line_select_it = undefined;
		this._char_select_it = undefined;
		this._scroll_list = ALittle.NewObject(ALittle.ScrollList, this._ctrl_sys);
		this._scroll_list.right_scrollbar = ALittle.NewObject(ALittle.ScrollBar, this._ctrl_sys);
		this._scroll_list.width_type = 4;
		this._scroll_list.height_type = 4;
		this._scroll_list.x_type = 3;
		this._scroll_list.y_type = 3;
		this.AddChild(this._scroll_list);
		this._current_flash_alpha = 1;
		this._current_flash_dir = -0.05;
		this._cursor = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this.AddChild(this._cursor);
		this._cursor.visible = false;
		this._cursor.width = 1;
		this._select_1 = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this.AddChild(this._select_1);
		this._select_1.visible = false;
		this._select_1.alpha = 0.5;
		this._select_2 = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this.AddChild(this._select_2);
		this._select_2.visible = false;
		this._select_2.alpha = 0.5;
		this._select_3 = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this.AddChild(this._select_3);
		this._select_3.visible = false;
		this._select_3.alpha = 0.5;
		this._start_cursor = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this._start_cursor.width = 1;
		this._end_cursor = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this._end_cursor.width = 1;
		this._start_cursor_data = undefined;
		this._end_cursor_data = undefined;
		this._focus_cursor = true;
		this._is_focus = false;
		this._event_start_x = 0;
		this._event_end_x = 0;
		this._event_start_y = 0;
		this._event_end_y = 0;
		this._start_it_delta = 0;
		this._click_drag_delta_x = 0;
		this._click_drag_delta_y = 0;
		this._is_click = false;
		this._is_longclick = false;
		this._is_click_cursor = false;
		this._is_click_cursor_name = "";
		this._drag_delta_x = 0;
		this._drag_delta_y = 0;
		this.AddChild(this._start_cursor);
		this.AddChild(this._end_cursor);
		this._start_cursor.visible = false;
		this._end_cursor.visible = false;
		this._cursor_margin_up = 0;
		this._cursor_margin_down = 0;
		this._margin_halign = 0;
		this._margin_valign = 0;
		this._line_spacing = 0;
		this._is_drag_begin = false;
		this._ims_padding = 0;
		this._default_text_area = ALittle.NewObject(ALittle.TextArea, this._ctrl_sys);
		this._default_text_area.width_type = 4;
		this._default_text_area.height = 0;
		this._default_text_area.x_type = 3;
		this._default_text_area.y = 0;
		this.AddChild(this._default_text_area);
		this._link_map = ALittle.CreateValueWeakMap();
		this._pickup_rect = true;
		this._pickup_child = false;
		this._pickup_this = true;
		this._editable = true;
		this._is_selecting = false;
		this._can_drag_text = true;
		this._auto_ims = true;
		this._multi_cursor = false;
		this._can_scroll = true;
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
		this.AddEventListener(___all_struct.get(-1737121315), this, this.HandleMButtonWheel);
		this.AddEventListener(___all_struct.get(-439548260), this, this.HandleLongLButtonDown);
		this.ClearText();
		if (this._loop === undefined) {
			this._loop = ALittle.NewObject(ALittle.LoopFunction, this.Update.bind(this), -1, 1, 1);
		}
		A_LoopSystem.AddUpdater(this._loop);
	},
	GetCursor : function() {
		return this._cursor;
	},
	get link_map() {
		return this._link_map;
	},
	ClearLinkMap : function() {
		this._link_map = ALittle.CreateValueWeakMap();
	},
	get real_height() {
		return this._line_list[this._line_count - 1].acc_height;
	},
	get real_edit_height() {
		let line_list = this._line_list;
		let last_line = line_list[this._line_count - 1];
		if (last_line.acc_height !== last_line.pre_height) {
			return last_line.acc_height;
		}
		return last_line.acc_height + this._enter_key_height;
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
		let char_info_list = this.GetCharInfoList();
		this.ClearText();
		this.InsertTextImpl(char_info_list, false);
		this.ResetCursor();
	},
	set height(value) {
		if (this.height === value) {
			return;
		}
		ALittle.DisplayLayout.__setter.height.call(this, value);
		this._default_text_area.y = this._scroll_list.y;
		this._default_text_area.height = this._default_text_area.real_height;
		if (this._default_text_area.height > this._scroll_list.height) {
			this._default_text_area.height = this._scroll_list.height;
		}
		this.ResetCursorLine();
		this.ResetCursor();
	},
	set cursor_red(value) {
		this._cursor.red = value;
		this._select_1.red = value;
		this._select_2.red = value;
		this._select_3.red = value;
	},
	get cursor_red() {
		return this._cursor.red;
	},
	set cursor_green(value) {
		this._cursor.green = value;
		this._select_1.green = value;
		this._select_2.green = value;
		this._select_3.green = value;
	},
	get cursor_green() {
		return this._cursor.green;
	},
	set cursor_blue(value) {
		this._cursor.blue = value;
		this._select_1.blue = value;
		this._select_2.blue = value;
		this._select_3.blue = value;
	},
	get cursor_blue() {
		return this._cursor.blue;
	},
	ShowCursor : function(value) {
		if (this._multi_cursor === false) {
			if (value) {
				if (this._select_1.visible === false) {
					this._cursor.visible = value;
				} else {
					this._cursor.visible = false;
				}
			} else {
				this._cursor.visible = (this._select_1.visible === false);
			}
		}
	},
	set font_bold(value) {
		if (this._font_text.bold === value) {
			return;
		}
		this._font_text.bold = value;
		this._default_text_area.bold = value;
		let char_info_list = this.GetCharInfoList();
		this.ClearText();
		this.InsertTextImpl(char_info_list, false);
		this.ResetCursor();
	},
	set font_underline(value) {
		if (this._font_text.underline === value) {
			return;
		}
		this._font_text.underline = value;
		this._default_text_area.underline = value;
	},
	set font_deleteline(value) {
		if (this._font_text.deleteline === value) {
			return;
		}
		this._font_text.deleteline = value;
		this._default_text_area.deleteline = value;
	},
	set font_italic(value) {
		if (this._font_text.italic === value) {
			return;
		}
		this._font_text.italic = value;
		this._default_text_area.italic = value;
	},
	set font_path(value) {
		if (this._font_text.font_path === value) {
			return;
		}
		this._font_text.font_path = value;
		this._default_text_area.font_path = value;
		this._default_text_area.height = this._default_text_area.real_height;
		if (this._default_text_area.height > this._scroll_list.height) {
			this._default_text_area.height = this._scroll_list.height;
		}
		if (this._font_text.font_path !== undefined && this._font_text.font_size !== undefined) {
			this._enter_key_height = this._font_text.native_show.GetFontHeight();
			let char_info_list = this.GetCharInfoList();
			this.ClearText();
			this.InsertTextImpl(char_info_list, false);
			this.ResetCursor();
		}
	},
	set font_size(value) {
		if (this._font_text.font_size === value) {
			return;
		}
		this._font_text.font_size = value;
		this._default_text_area.font_size = value;
		this._default_text_area.height = this._default_text_area.real_height;
		if (this._default_text_area.height > this._scroll_list.height) {
			this._default_text_area.height = this._scroll_list.height;
		}
		if (this._font_text.font_path !== undefined && this._font_text.font_size !== undefined) {
			this._enter_key_height = this._font_text.native_show.GetFontHeight();
			let char_info_list = this.GetCharInfoList();
			this.ClearText();
			this.InsertTextImpl(char_info_list, false);
			this.ResetCursor();
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
		this._default_text_area.red = value;
	},
	get font_red() {
		return this._font_text.red;
	},
	set font_green(value) {
		if (this._font_text.green === value) {
			return;
		}
		this._font_text.green = value;
		this._default_text_area.green = value;
	},
	get font_green() {
		return this._font_text.green;
	},
	set font_blue(value) {
		if (this._font_text.blue === value) {
			return;
		}
		this._font_text.blue = value;
		this._default_text_area.blue = value;
	},
	get font_blue() {
		return this._font_text.blue;
	},
	set default_text(value) {
		this._default_text_area.text = value;
		this._default_text_area.height = this._default_text_area.real_height;
		if (this._default_text_area.height > this._scroll_list.height) {
			this._default_text_area.height = this._scroll_list.height;
		}
	},
	set text(value) {
		this.ClearText();
		this.InsertTextNative(value);
		this.ShowDefaultText();
	},
	get text() {
		let displaylist = this.CharInfoListToDisplayList(this.GetCharInfoList());
		let text = "";
		let ___OBJECT_8 = displaylist;
		for (let k = 1; k <= ___OBJECT_8.length; ++k) {
			let v = ___OBJECT_8[k - 1];
			if (v === undefined) break;
			if (v.__class === "Text") {
				text = text + v.text;
			}
		}
		return text;
	},
	get default_text() {
		return this._default_text_area.text;
	},
	set default_text_alpha(value) {
		this._default_text_area.alpha = value;
	},
	get default_text_alpha() {
		return this._default_text_area.alpha;
	},
	set display_list(value) {
		let char_info_list = this.DisplayListToCharInfoList(value);
		this.ClearText();
		this.InsertTextImpl(char_info_list, false);
		this.ResetCursor();
		this.ShowDefaultText();
	},
	get display_list() {
		return this.CharInfoListToDisplayList(this.GetCharInfoList());
	},
	set start_cursor(value) {
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
		this._scroll_list.width_value = this._margin_halign * 2;
		this._default_text_area.width_value = this._margin_halign * 2;
		let char_info_list = this.GetCharInfoList();
		this.ClearText();
		this.InsertTextImpl(char_info_list, false);
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
		this._scroll_list.height_value = this._margin_valign * 2;
		this._default_text_area.y = this._scroll_list.y;
		this._default_text_area.height = this._default_text_area.real_height;
		if (this._default_text_area.height > this._scroll_list.height) {
			this._default_text_area.height = this._scroll_list.height;
		}
		let char_info_list = this.GetCharInfoList();
		this.ClearText();
		this.InsertTextImpl(char_info_list, false);
		this.ResetCursor();
	},
	set line_spacing(value) {
		if (this._line_spacing === this._line_spacing) {
			return;
		}
		this._line_spacing = value;
		this._scroll_list.gap = value;
	},
	get line_spacing() {
		return this._line_spacing;
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
	GetLineWidth : function(value) {
		let line = this._line_list[value - 1];
		if (line === undefined) {
			return 0;
		}
		return line.char_list[line.char_count - 1].acc_width;
	},
	GetScrollOffset : function() {
		if (this._line_start_it === undefined) {
			return 0;
		}
		return this._line_list[this._line_start_it - 1].pre_height + this._start_it_delta;
	},
	GetLineCount : function() {
		return this._line_count;
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
	GetSelectText : function() {
		let line_list = this._line_list;
		let select_text = [];
		let select_text_count = 0;
		if (this._char_select_it > line_list[this._line_select_it - 1].char_count) {
			return [];
		}
		if (line_list[this._line_select_it - 1].pre_height > line_list[this._line_cursor_it - 1].pre_height) {
			let line_it = this._line_cursor_it;
			while (true) {
				let char_it = undefined;
				let char_end = undefined;
				if (line_it === this._line_cursor_it) {
					char_it = this._char_cursor_it;
					char_it = char_it + 1;
				} else {
					char_it = 1;
				}
				if (line_it === this._line_select_it) {
					char_end = this._char_select_it;
					char_end = char_end + 1;
				} else {
					char_end = line_list[line_it - 1].char_count + 1;
				}
				let line = line_list[line_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
				if (line_it === this._line_select_it) {
					break;
				}
				line_it = line_it + 1;
			}
		} else if (line_list[this._line_select_it - 1].pre_height < line_list[this._line_cursor_it - 1].pre_height) {
			let line_it = this._line_select_it;
			while (true) {
				let char_it = undefined;
				let char_end = undefined;
				if (line_it === this._line_select_it) {
					char_it = this._char_select_it;
					char_it = char_it + 1;
				} else {
					char_it = 1;
				}
				if (line_it === this._line_cursor_it) {
					char_end = this._char_cursor_it;
					char_end = char_end + 1;
				} else {
					char_end = line_list[line_it - 1].char_count + 1;
				}
				let line = line_list[line_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
				if (line_it === this._line_cursor_it) {
					break;
				}
				line_it = line_it + 1;
			}
		} else {
			if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width > line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				let char_it = this._char_select_it;
				let char_end = this._char_cursor_it;
				char_end = char_end + 1;
				char_it = char_it + 1;
				let line = line_list[this._line_cursor_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
			} else if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width < line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				let char_it = this._char_cursor_it;
				let char_end = this._char_select_it;
				char_end = char_end + 1;
				char_it = char_it + 1;
				let line = line_list[this._line_cursor_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
			}
		}
		return this.CharInfoListToDisplayList(select_text);
	},
	GetSelectWord : function() {
		let line_list = this._line_list;
		let select_text = [];
		let select_text_count = 0;
		if (this._char_select_it > line_list[this._line_select_it - 1].char_count) {
			return "";
		}
		if (line_list[this._line_select_it - 1].pre_height > line_list[this._line_cursor_it - 1].pre_height) {
			let line_it = this._line_cursor_it;
			while (true) {
				let char_it = undefined;
				let char_end = undefined;
				if (line_it === this._line_cursor_it) {
					char_it = this._char_cursor_it;
					char_it = char_it + 1;
				} else {
					char_it = 1;
				}
				if (line_it === this._line_select_it) {
					char_end = this._char_select_it;
					char_end = char_end + 1;
				} else {
					char_end = line_list[line_it - 1].char_count + 1;
				}
				let line = line_list[line_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
				if (line_it === this._line_select_it) {
					break;
				}
				line_it = line_it + 1;
			}
		} else if (line_list[this._line_select_it - 1].pre_height < line_list[this._line_cursor_it - 1].pre_height) {
			let line_it = this._line_select_it;
			while (true) {
				let char_it = undefined;
				let char_end = undefined;
				if (line_it === this._line_select_it) {
					char_it = this._char_select_it;
					char_it = char_it + 1;
				} else {
					char_it = 1;
				}
				if (line_it === this._line_cursor_it) {
					char_end = this._char_cursor_it;
					char_end = char_end + 1;
				} else {
					char_end = line_list[line_it - 1].char_count + 1;
				}
				let line = line_list[line_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
				if (line_it === this._line_cursor_it) {
					break;
				}
				line_it = line_it + 1;
			}
		} else {
			if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width > line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				let char_it = this._char_select_it;
				let char_end = this._char_cursor_it;
				char_end = char_end + 1;
				char_it = char_it + 1;
				let line = line_list[this._line_cursor_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
			} else if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width < line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				let char_it = this._char_cursor_it;
				let char_end = this._char_select_it;
				char_end = char_end + 1;
				char_it = char_it + 1;
				let line = line_list[this._line_cursor_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
			}
		}
		return this.CharInfoListToWord(select_text);
	},
	DeleteSelectText : function() {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return false;
		}
		let line_list = this._line_list;
		if (this._char_select_it > line_list[this._line_select_it - 1].char_count) {
			return false;
		}
		let line_begin_it = undefined;
		let begin_it = undefined;
		let line_end_it = undefined;
		let end_it = undefined;
		if (line_list[this._line_select_it - 1].pre_height > line_list[this._line_cursor_it - 1].pre_height) {
			line_begin_it = this._line_cursor_it;
			begin_it = this._char_cursor_it;
			line_end_it = this._line_select_it;
			end_it = this._char_select_it;
		} else if (line_list[this._line_select_it - 1].pre_height < line_list[this._line_cursor_it - 1].pre_height) {
			line_begin_it = this._line_select_it;
			begin_it = this._char_select_it;
			line_end_it = this._line_cursor_it;
			end_it = this._char_cursor_it;
		} else {
			line_begin_it = this._line_select_it;
			line_end_it = this._line_cursor_it;
			begin_it = this._char_select_it;
			end_it = this._char_cursor_it;
			if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width > line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				begin_it = this._char_select_it;
				end_it = this._char_cursor_it;
			} else if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width < line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				begin_it = this._char_cursor_it;
				end_it = this._char_select_it;
			}
		}
		if (begin_it === 1) {
			if (line_begin_it !== 1 && line_list[line_begin_it - 1].force_line === false) {
				line_begin_it = line_begin_it - 1;
				begin_it = line_list[line_begin_it - 1].char_count + 1;
				begin_it = begin_it - 1;
			}
		}
		this.DeleteTextImpl(line_begin_it, begin_it, line_end_it, end_it);
		this.ResetCursor();
		return true;
	},
	CheckTextRegexLimit : function(text) {
		if (this._limit_len !== 0) {
			let text_len = ALittle.String_GetWordCount(text);
			if (text_len > this._limit_len) {
				return false;
			}
			let select_len = 0;
			let displaylist = this.GetSelectText();
			let ___OBJECT_9 = displaylist;
			for (let k = 1; k <= ___OBJECT_9.length; ++k) {
				let v = ___OBJECT_9[k - 1];
				if (v === undefined) break;
				if (v.__class === "Text") {
					select_len = select_len + ALittle.String_GetWordCount(v.text);
				}
			}
			displaylist = this.display_list;
			let total_len = 0;
			let ___OBJECT_10 = displaylist;
			for (let k = 1; k <= ___OBJECT_10.length; ++k) {
				let v = ___OBJECT_10[k - 1];
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
		let char_info_list_count = 0;
		let new_char_info = {};
		new_char_info.acc_width = 0;
		new_char_info.pre_width = 0;
		new_char_info.text_info = this.InitTextInfo();
		new_char_info.text_object = undefined;
		new_char_info.text = text;
		new_char_info.ctrl_info = undefined;
		new_char_info.ctrl = undefined;
		++ char_info_list_count;
		char_info_list[char_info_list_count - 1] = new_char_info;
		this.InsertTextImpl(char_info_list, false);
		this.ResetCursorLine();
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
		let line_list = this._line_list;
		let char_info = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1];
		let char_info_list = this.DisplayListToCharInfoList(display_list, char_info.text_info);
		this.InsertTextImpl(char_info_list, selected);
		this.UpdateFontText();
		this.ResetCursorLine();
		this.ResetCursor();
		return true;
	},
	DeleteText : function(left) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return false;
		}
		if (this.DeleteSelectText()) {
			return true;
		}
		let line_list = this._line_list;
		if (left) {
			if (this._line_cursor_it === 1 && this._char_cursor_it === 1) {
				return false;
			}
			let line_begin_it = this._line_cursor_it;
			let begin_it = this._char_cursor_it;
			let line_end_it = this._line_cursor_it;
			let end_it = this._char_cursor_it;
			if (begin_it === 1) {
				if (line_begin_it !== 1) {
					line_begin_it = line_begin_it - 1;
					begin_it = line_list[line_begin_it - 1].char_count + 1;
					begin_it = begin_it - 1;
				}
			} else {
				begin_it = begin_it - 1;
				if (begin_it === 1 && line_list[line_begin_it - 1].force_line === false) {
					if (line_begin_it !== 1) {
						line_begin_it = line_begin_it - 1;
						begin_it = line_list[line_begin_it - 1].char_count + 1;
						begin_it = begin_it - 1;
					}
				}
			}
			this.DeleteTextImpl(line_begin_it, begin_it, line_end_it, end_it);
		} else {
			let end_line = this._line_count + 1;
			end_line = end_line - 1;
			let end_char = line_list[end_line - 1].char_count + 1;
			end_char = end_char - 1;
			if (this._line_cursor_it === end_line && this._char_cursor_it === end_char) {
				return false;
			}
			let line_begin_it = this._line_cursor_it;
			let begin_it = this._char_cursor_it;
			let line_end_it = this._line_cursor_it;
			let end_it = this._char_cursor_it;
			end_char = line_list[line_end_it - 1].char_count + 1;
			end_char = end_char - 1;
			if (end_it === end_char) {
				if (line_end_it !== end_line) {
					line_end_it = line_end_it + 1;
					end_it = 1;
					if (line_list[line_end_it - 1].force_line === false) {
						end_it = end_it + 1;
						if (end_it > line_list[line_end_it - 1].char_count) {
							end_it = end_it - 1;
						}
					}
				}
			} else {
				end_it = end_it + 1;
			}
			this.DeleteTextImpl(line_begin_it, begin_it, line_end_it, end_it);
		}
		this.ResetCursorLine();
		this.ResetCursor();
		return true;
	},
	ClearText : function() {
		this._line_list = [];
		this._line_count = 0;
		let line_info = {};
		line_info.char_list = [];
		line_info.child_list = [];
		line_info.char_count = 0;
		line_info.child_count = 0;
		line_info.pre_height = 0;
		line_info.acc_height = 0;
		line_info.force_line = false;
		line_info.container = undefined;
		++ this._line_count;
		this._line_list[this._line_count - 1] = line_info;
		let char_info = {};
		char_info.acc_width = 0;
		char_info.pre_width = 0;
		char_info.text_info = this.InitTextInfo();
		char_info.text_object = undefined;
		char_info.text = "";
		char_info.ctrl_info = undefined;
		char_info.ctrl = undefined;
		++ line_info.char_count;
		line_info.char_list[line_info.char_count - 1] = char_info;
		this._line_start_it = 1;
		this._start_it_delta = 0;
		this._line_cursor_it = 1;
		this._char_cursor_it = 1;
		this._line_select_it = 1;
		this._char_select_it = 2;
		this.Draw();
	},
	SetStartIt : function(line_index) {
		if (line_index < 1 || line_index > this._line_count) {
			return;
		}
		this._line_start_it = line_index;
		this._start_it_delta = 0;
		this.AdjustContentY();
	},
	ResetCursor : function() {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return;
		}
		let line_list = this._line_list;
		if ((this._char_select_it > line_list[this._line_select_it - 1].char_count) || (this._line_select_it === this._line_cursor_it && this._char_select_it === this._char_cursor_it)) {
			this._select_1.visible = false;
			this._select_2.visible = false;
			this._select_3.visible = false;
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
			let cursor_width = 0.0;
			let line = line_list[this._line_cursor_it - 1];
			let char = line.char_list[this._char_cursor_it - 1];
			if (char.ctrl !== undefined) {
				this._cursor.height = char.ctrl.height;
				cursor_width = 2;
			} else {
				if (char.text_object !== undefined) {
					this._cursor.height = char.text_object.height;
					cursor_width = this.GetCursorWidth(char.text_object.font_size);
				} else {
					let next_char = line.char_list[this._char_cursor_it + 1 - 1];
					if (next_char !== undefined) {
						if (next_char.ctrl !== undefined) {
							this._cursor.height = next_char.ctrl.height;
							cursor_width = 2;
						} else if (next_char.text_object !== undefined) {
							this._cursor.height = next_char.text_object.height;
							cursor_width = this.GetCursorWidth(next_char.text_object.font_size);
						} else {
							this._cursor.height = this._font_text.native_show.GetFontHeight();
							cursor_width = this.GetCursorWidth(this._font_text.font_size);
						}
					} else {
						this._cursor.height = this._font_text.native_show.GetFontHeight();
						cursor_width = this.GetCursorWidth(this._font_text.font_size);
					}
				}
			}
			this._cursor.width = cursor_width;
			let line_height = line_list[this._line_cursor_it - 1].acc_height - line_list[this._line_cursor_it - 1].pre_height;
			let offset_y = line_height - this._cursor.height;
			if (offset_y <= 0) {
				offset_y = 0;
			}
			this._cursor.y = this._scroll_list.y + line_list[this._line_cursor_it - 1].pre_height - line_list[this._line_start_it - 1].pre_height + offset_y - this._start_it_delta;
			this._cursor.x = this._scroll_list.x + line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
			return;
		}
		if (this._multi_cursor === false) {
			this._cursor.visible = false;
		}
		if (line_list[this._line_select_it - 1].pre_height > line_list[this._line_cursor_it - 1].pre_height) {
			let line_it = this._line_cursor_it;
			this._select_1.visible = true;
			let select_1_y = line_list[this._line_cursor_it - 1].pre_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
			let select_1_height = line_list[this._line_cursor_it - 1].acc_height - line_list[this._line_cursor_it - 1].pre_height;
			if (select_1_y < 0) {
				select_1_height = select_1_y + select_1_height;
				select_1_y = 0;
			}
			if (select_1_y + select_1_height > this._scroll_list.height) {
				select_1_height = this._scroll_list.height - select_1_y;
			}
			if (select_1_height <= 0) {
				this._select_1.visible = false;
			}
			this._select_1.y = this._scroll_list.y + select_1_y;
			this._select_1.x = this._scroll_list.x + line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
			this._select_1.height = select_1_height;
			this._select_1.width = this._scroll_list.width - line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
			this._select_3.visible = (line_list[this._line_cursor_it - 1].acc_height !== line_list[this._line_select_it - 1].pre_height);
			let select_3_y = line_list[this._line_cursor_it - 1].acc_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
			let select_3_height = line_list[this._line_select_it - 1].pre_height - line_list[this._line_cursor_it - 1].acc_height;
			if (select_3_y < 0) {
				select_3_height = select_3_y + select_3_height;
				select_3_y = 0;
			}
			if (select_3_y + select_3_height > this._scroll_list.height) {
				select_3_height = this._scroll_list.height - select_3_y;
			}
			if (select_3_height <= 0) {
				this._select_3.visible = false;
			}
			this._select_3.y = this._scroll_list.y + select_3_y;
			this._select_3.x = this._scroll_list.x;
			this._select_3.height = select_3_height;
			this._select_3.width = this._scroll_list.width;
			line_it = this._line_select_it;
			this._select_2.visible = true;
			let select_2_y = line_list[this._line_select_it - 1].pre_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
			let select_2_height = line_list[this._line_select_it - 1].acc_height - line_list[this._line_select_it - 1].pre_height;
			if (select_2_y < 0) {
				select_2_height = select_2_y + select_2_height;
				select_2_y = 0;
			}
			if (select_2_y + select_2_height > this._scroll_list.height) {
				select_2_height = this._scroll_list.height - select_2_y;
			}
			if (select_2_height <= 0) {
				this._select_2.visible = false;
			}
			this._select_2.y = this._scroll_list.y + select_2_y;
			this._select_2.x = this._scroll_list.x;
			this._select_2.height = select_2_height;
			this._select_2.width = line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width;
			if (this._multi_cursor === true) {
				this._cursor.visible = false;
				this._start_cursor.x = this._select_1.x - this._start_cursor.width;
				this._start_cursor.height = this._select_1.height + this._cursor_margin_up + this._cursor_margin_down;
				this._start_cursor.y = this._select_1.y - this._cursor_margin_up;
				this._end_cursor.x = this._select_2.x + this._select_2.width;
				this._end_cursor.height = this._select_2.height + this._cursor_margin_up + this._cursor_margin_down;
				this._end_cursor.y = this._select_2.y - this._cursor_margin_up;
				this._start_cursor.visible = this._select_1.visible;
				this._end_cursor.visible = this._select_2.visible;
				this._start_cursor_data = "cursor";
				this._end_cursor_data = "select";
				this._event_start_x = this._select_1.x;
				this._event_start_y = this._select_1.y;
				this._event_end_x = this._select_2.x + this._select_2.width;
				this._event_end_y = this._select_2.y + this._select_2.height;
			}
		} else if (line_list[this._line_select_it - 1].pre_height < line_list[this._line_cursor_it - 1].pre_height) {
			let line_it = this._line_select_it;
			this._select_1.visible = true;
			let select_1_y = line_list[this._line_select_it - 1].pre_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
			let select_1_height = line_list[this._line_select_it - 1].acc_height - line_list[this._line_select_it - 1].pre_height;
			if (select_1_y < 0) {
				select_1_height = select_1_y + select_1_height;
				select_1_y = 0;
			}
			if (select_1_y + select_1_height > this._scroll_list.height) {
				select_1_height = this._scroll_list.height - select_1_y;
			}
			if (select_1_height <= 0) {
				this._select_1.visible = false;
			}
			this._select_1.y = this._scroll_list.y + select_1_y;
			this._select_1.x = this._scroll_list.x + line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width;
			this._select_1.height = select_1_height;
			this._select_1.width = this._scroll_list.width - line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width;
			line_it = this._line_cursor_it;
			this._select_2.visible = true;
			let select_2_y = line_list[this._line_cursor_it - 1].pre_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
			let select_2_height = line_list[this._line_cursor_it - 1].acc_height - line_list[this._line_cursor_it - 1].pre_height;
			if (select_2_y < 0) {
				select_2_height = select_2_y + select_2_height;
				select_2_y = 0;
			}
			if (select_2_y + select_2_height > this._scroll_list.height) {
				select_2_height = this._scroll_list.height - select_2_y;
			}
			if (select_2_height <= 0) {
				this._select_2.visible = false;
			}
			this._select_2.y = this._scroll_list.y + select_2_y;
			this._select_2.x = this._scroll_list.x;
			this._select_2.height = select_2_height;
			this._select_2.width = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
			this._select_3.visible = (line_list[this._line_select_it - 1].acc_height !== line_list[this._line_cursor_it - 1].pre_height);
			let select_3_y = line_list[this._line_select_it - 1].acc_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
			let select_3_height = line_list[this._line_cursor_it - 1].pre_height - line_list[this._line_select_it - 1].acc_height;
			if (select_3_y < 0) {
				select_3_height = select_3_y + select_3_height;
				select_3_y = 0;
			}
			if (select_3_y + select_3_height > this._scroll_list.height) {
				select_3_height = this._scroll_list.height - select_3_y;
			}
			if (select_3_height <= 0) {
				this._select_3.visible = false;
			}
			this._select_3.y = this._scroll_list.y + select_3_y;
			this._select_3.x = this._scroll_list.x;
			this._select_3.width = this._scroll_list.width;
			this._select_3.height = select_3_height;
			if (this._multi_cursor === true) {
				this._cursor.visible = false;
				this._start_cursor.x = this._select_1.x - this._start_cursor.width;
				this._start_cursor.height = this._select_1.height + this._cursor_margin_up + this._cursor_margin_down;
				this._start_cursor.y = this._select_1.y - this._cursor_margin_up;
				this._end_cursor.x = this._select_2.x + this._select_2.width;
				this._end_cursor.height = this._select_2.height + this._cursor_margin_up + this._cursor_margin_down;
				this._end_cursor.y = this._select_2.y - this._cursor_margin_up;
				this._start_cursor.visible = this._select_1.visible;
				this._end_cursor.visible = this._select_2.visible;
				this._start_cursor_data = "select";
				this._end_cursor_data = "cursor";
				this._event_start_x = this._select_1.x;
				this._event_start_y = this._select_1.y;
				this._event_end_x = this._select_2.x + this._select_2.width;
				this._event_end_y = this._select_2.y + this._select_2.height;
			}
		} else {
			this._select_1.visible = false;
			this._select_2.visible = false;
			this._select_3.visible = false;
			if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width > line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				this._select_1.visible = true;
				let select_1_y = line_list[this._line_cursor_it - 1].pre_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
				let select_1_height = line_list[this._line_cursor_it - 1].acc_height - line_list[this._line_cursor_it - 1].pre_height;
				if (select_1_y < 0) {
					select_1_height = select_1_y + select_1_height;
					select_1_y = 0;
				}
				if (select_1_y + select_1_height > this._scroll_list.height) {
					select_1_height = this._scroll_list.height - select_1_y;
				}
				if (select_1_height <= 0) {
					this._select_1.visible = false;
				}
				this._select_1.x = this._scroll_list.x + line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width;
				this._select_1.y = this._scroll_list.y + select_1_y;
				this._select_1.height = select_1_height;
				this._select_1.width = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width - line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width;
				if (this._multi_cursor === true) {
					this._cursor.visible = false;
					this._start_cursor.x = this._select_1.x - this._start_cursor.width;
					this._start_cursor.height = this._select_1.height + this._cursor_margin_up + this._cursor_margin_down;
					this._start_cursor.y = this._select_1.y - this._cursor_margin_up;
					this._end_cursor.x = this._select_1.x + this._select_1.width;
					this._end_cursor.height = this._start_cursor.height;
					this._end_cursor.y = this._start_cursor.y;
					this._start_cursor.visible = this._select_1.visible;
					this._end_cursor.visible = this._select_1.visible;
					this._start_cursor_data = "select";
					this._end_cursor_data = "cursor";
					this._event_start_x = this._select_1.x;
					this._event_start_y = this._select_1.y;
					this._event_end_x = this._select_1.x + this._select_1.width;
					this._event_end_y = this._select_1.y + this._select_1.height;
				}
			} else if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width < line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				this._select_1.visible = true;
				let select_1_y = line_list[this._line_cursor_it - 1].pre_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
				let select_1_height = line_list[this._line_cursor_it - 1].acc_height - line_list[this._line_cursor_it - 1].pre_height;
				if (select_1_y < 0) {
					select_1_height = select_1_y + select_1_height;
					select_1_y = 0;
				}
				if (select_1_y + select_1_height > this._scroll_list.height) {
					select_1_height = this._scroll_list.height - select_1_y;
				}
				if (select_1_height <= 0) {
					this._select_1.visible = false;
				}
				this._select_1.x = this._scroll_list.x + line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
				this._select_1.y = this._scroll_list.y + select_1_y;
				this._select_1.height = select_1_height;
				this._select_1.width = line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width - line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
				if (this._multi_cursor === true) {
					this._cursor.visible = false;
					this._start_cursor.x = this._select_1.x - this._start_cursor.width;
					this._start_cursor.height = this._select_1.height + this._cursor_margin_up + this._cursor_margin_down;
					this._start_cursor.y = this._select_1.y - this._cursor_margin_up;
					this._end_cursor.x = this._select_1.x + this._select_1.width;
					this._end_cursor.height = this._start_cursor.height;
					this._end_cursor.y = this._start_cursor.y;
					this._start_cursor.visible = this._select_1.visible;
					this._end_cursor.visible = this._select_1.visible;
					this._start_cursor_data = "cursor";
					this._end_cursor_data = "select";
					this._event_start_x = this._select_1.x;
					this._event_start_y = this._select_1.y;
					this._event_end_x = this._select_1.x + this._select_1.width;
					this._event_end_y = this._select_1.y + this._select_1.height;
				}
			}
		}
	},
	DeleteTextImpl : function(line_begin_it, begin_it, line_end_it, end_it) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return;
		}
		let line_list = this._line_list;
		let line_delete_begin = line_begin_it;
		let line_delete_end = line_end_it;
		let char_delete_begin = begin_it;
		let char_delete_end = end_it;
		if (line_list[line_begin_it - 1].pre_height > line_list[line_end_it - 1].pre_height) {
			line_delete_begin = line_end_it;
			char_delete_begin = end_it;
			line_delete_end = line_begin_it;
			char_delete_end = begin_it;
		} else if (line_list[line_begin_it - 1].pre_height === line_list[line_end_it - 1].pre_height) {
			if (line_list[line_begin_it - 1].char_list[begin_it - 1].acc_width > line_list[line_end_it - 1].char_list[end_it - 1].acc_width) {
				char_delete_begin = end_it;
				char_delete_end = begin_it;
			}
		}
		if (line_list[this._line_start_it - 1].pre_height >= line_list[line_delete_begin - 1].pre_height) {
			this._line_start_it = line_delete_begin;
			this._start_it_delta = 0;
		}
		let calc_text_1 = [];
		let calc_text_1_count = 0;
		let char_it = 1;
		char_it = char_it + 1;
		char_delete_begin = char_delete_begin + 1;
		let line = line_list[line_delete_begin - 1];
		while (char_it !== char_delete_begin) {
			++ calc_text_1_count;
			calc_text_1[calc_text_1_count - 1] = line.char_list[char_it - 1];
			char_it = char_it + 1;
		}
		let calc_text_2 = [];
		let calc_text_2_count = 0;
		char_it = char_delete_end;
		char_it = char_it + 1;
		line = line_list[line_delete_end - 1];
		while (char_it <= line.char_count) {
			++ calc_text_2_count;
			calc_text_2[calc_text_2_count - 1] = line.char_list[char_it - 1];
			char_it = char_it + 1;
		}
		let line_it = line_delete_end;
		line_it = line_it + 1;
		let free_line_it = 0;
		while (line_it <= this._line_count) {
			char_it = 1;
			line = line_list[line_it - 1];
			if (line.force_line) {
				free_line_it = line_it;
				break;
			}
			while (char_it <= line.char_count) {
				++ calc_text_2_count;
				calc_text_2[calc_text_2_count - 1] = line.char_list[char_it - 1];
				char_it = char_it + 1;
			}
			line_it = line_it + 1;
		}
		let char_info = line_list[line_delete_begin - 1].char_list[1 - 1];
		line_list[line_delete_begin - 1].char_list = [];
		line_list[line_delete_begin - 1].char_count = 1;
		line_list[line_delete_begin - 1].char_list[1 - 1] = char_info;
		line_list[line_delete_begin - 1].child_list = [];
		line_list[line_delete_begin - 1].child_count = 0;
		line_list[line_delete_begin - 1].acc_height = line_list[line_delete_begin - 1].pre_height;
		line_list[line_delete_begin - 1].container = undefined;
		let free_line_list = undefined;
		let free_line_list_count = 0;
		if (free_line_it > 0) {
			free_line_list = [];
			for (let i = free_line_it; i <= this._line_count; i += 1) {
				++ free_line_list_count;
				free_line_list[free_line_list_count - 1] = line_list[i - 1];
			}
		}
		line_it = line_delete_begin;
		line_it = line_it + 1;
		for (let i = line_it; i <= this._line_count; i += 1) {
			line_list[i - 1] = undefined;
		}
		this._line_count = line_delete_begin;
		calc_text_1 = this.JoinCharInfoList(calc_text_1);
		calc_text_2 = this.JoinCharInfoList(calc_text_2);
		[this._line_cursor_it, this._char_cursor_it] = this.InsertTextUtil(calc_text_1);
		this.InsertTextUtil(calc_text_2);
		if (free_line_list !== undefined) {
			let last_line = line_list[this._line_count - 1];
			if (last_line.char_count === 1 && last_line.force_line) {
				last_line.acc_height = last_line.pre_height + this._enter_key_height;
			}
			let start_y = last_line.acc_height;
			let ___OBJECT_12 = free_line_list;
			for (let k = 1; k <= ___OBJECT_12.length; ++k) {
				let line_v = ___OBJECT_12[k - 1];
				if (line_v === undefined) break;
				this._line_count = this._line_count + 1;
				line_list[this._line_count - 1] = line_v;
				let line_height = line_v.acc_height - line_v.pre_height;
				line_v.pre_height = start_y;
				start_y = start_y + line_height;
				line_v.acc_height = start_y;
			}
		}
		this._line_select_it = this._line_count + 1;
		this._line_select_it = this._line_select_it - 1;
		this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		this.Draw();
	},
	InsertTextImpl : function(char_info_list, selected) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return;
		}
		if (char_info_list[1 - 1] === undefined) {
			return;
		}
		let line_list = this._line_list;
		let line_cursor_it_tmp = this._line_cursor_it;
		let char_cursor_it_tmp = this._char_cursor_it;
		let calc_text_1 = [];
		let calc_text_1_count = 0;
		let char_it = 1;
		char_it = char_it + 1;
		let char_end_it = this._char_cursor_it;
		char_end_it = char_end_it + 1;
		let line = line_list[this._line_cursor_it - 1];
		while (char_it !== char_end_it) {
			++ calc_text_1_count;
			calc_text_1[calc_text_1_count - 1] = line.char_list[char_it - 1];
			char_it = char_it + 1;
		}
		let ___OBJECT_13 = char_info_list;
		for (let k = 1; k <= ___OBJECT_13.length; ++k) {
			let v = ___OBJECT_13[k - 1];
			if (v === undefined) break;
			++ calc_text_1_count;
			calc_text_1[calc_text_1_count - 1] = v;
		}
		let calc_text_2 = [];
		let calc_text_2_count = 0;
		char_it = this._char_cursor_it;
		char_it = char_it + 1;
		line = line_list[this._line_cursor_it - 1];
		while (char_it <= line.char_count) {
			++ calc_text_2_count;
			calc_text_2[calc_text_2_count - 1] = line.char_list[char_it - 1];
			char_it = char_it + 1;
		}
		let line_it = this._line_cursor_it;
		line_it = line_it + 1;
		let free_line_it = 0;
		while (line_it <= this._line_count) {
			char_it = 1;
			line = line_list[line_it - 1];
			if (line.force_line) {
				free_line_it = line_it;
				break;
			}
			while (char_it <= line.char_count) {
				++ calc_text_2_count;
				calc_text_2[calc_text_2_count - 1] = line.char_list[char_it - 1];
				char_it = char_it + 1;
			}
			line_it = line_it + 1;
		}
		let char_info = line_list[this._line_cursor_it - 1].char_list[1 - 1];
		line_list[this._line_cursor_it - 1].char_list = [];
		line_list[this._line_cursor_it - 1].char_count = 1;
		line_list[this._line_cursor_it - 1].char_list[1 - 1] = char_info;
		line_list[this._line_cursor_it - 1].child_list = [];
		line_list[this._line_cursor_it - 1].child_count = 0;
		line_list[this._line_cursor_it - 1].acc_height = line_list[this._line_cursor_it - 1].pre_height;
		line_list[this._line_cursor_it - 1].container = undefined;
		let free_line_list = undefined;
		let free_line_list_count = 0;
		if (free_line_it > 0) {
			free_line_list = [];
			for (let i = free_line_it; i <= this._line_count; i += 1) {
				++ free_line_list_count;
				free_line_list[free_line_list_count - 1] = line_list[i - 1];
			}
		}
		line_it = this._line_cursor_it;
		line_it = line_it + 1;
		for (let i = line_it; i <= this._line_count; i += 1) {
			line_list[i - 1] = undefined;
		}
		this._line_count = this._line_cursor_it;
		calc_text_1 = this.JoinCharInfoList(calc_text_1);
		calc_text_2 = this.JoinCharInfoList(calc_text_2);
		[this._line_cursor_it, this._char_cursor_it] = this.InsertTextUtil(calc_text_1);
		this.InsertTextUtil(calc_text_2);
		if (free_line_list !== undefined) {
			let last_line = line_list[this._line_count - 1];
			if (last_line.char_count === 1 && last_line.force_line) {
				last_line.acc_height = last_line.pre_height + this._enter_key_height;
			}
			let start_y = last_line.acc_height;
			let ___OBJECT_14 = free_line_list;
			for (let k1 = 1; k1 <= ___OBJECT_14.length; ++k1) {
				let line_v = ___OBJECT_14[k1 - 1];
				if (line_v === undefined) break;
				this._line_count = this._line_count + 1;
				line_list[this._line_count - 1] = line_v;
				let line_height = line_v.acc_height - line_v.pre_height;
				line_v.pre_height = start_y;
				start_y = start_y + line_height;
				line_v.acc_height = start_y;
			}
		}
		if (selected) {
			this._line_select_it = line_cursor_it_tmp;
			this._char_select_it = char_cursor_it_tmp;
		} else {
			this._line_select_it = this._line_count + 1;
			this._line_select_it = this._line_select_it - 1;
			this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		}
		this.Draw();
	},
	InsertTextUtil : function(char_info_list) {
		let line_list = this._line_list;
		let total_width = this._scroll_list.width;
		let new_char_info_list = [];
		let new_char_info_list_count = 0;
		let ___OBJECT_15 = char_info_list;
		for (let index = 1; index <= ___OBJECT_15.length; ++index) {
			let char_info = ___OBJECT_15[index - 1];
			if (char_info === undefined) break;
			if (char_info.ctrl_info === undefined) {
				new_char_info_list_count = this.SplitText(char_info, new_char_info_list, new_char_info_list_count);
			} else {
				++ new_char_info_list_count;
				new_char_info_list[new_char_info_list_count - 1] = char_info;
			}
		}
		char_info_list = new_char_info_list;
		let line_it = this._line_count + 1;
		line_it = line_it - 1;
		let line_info = line_list[line_it - 1];
		let begin_it = line_info.char_count + 1;
		begin_it = begin_it - 1;
		if (line_it === 1 && begin_it === 1) {
			line_info.char_list[1 - 1].text_info = this.InitTextInfo();
		}
		let display_info = undefined;
		let display_object = undefined;
		let display_index = 1;
		let remain_width = total_width - line_info.char_list[line_info.char_count - 1].acc_width;
		while (true) {
			if (display_info === undefined) {
				display_info = char_info_list[display_index - 1];
				if (display_info === undefined) {
					break;
				}
			}
			if (display_info.ctrl_info === undefined) {
				if (display_info.text === "\n") {
					if (line_info.char_count === 1) {
						line_info.acc_height = line_info.pre_height + this._enter_key_height;
					}
					let new_line_info = {};
					new_line_info.char_list = [];
					new_line_info.child_list = [];
					new_line_info.char_count = 0;
					new_line_info.child_count = 0;
					new_line_info.pre_height = line_info.acc_height + this._line_spacing;
					new_line_info.acc_height = line_info.acc_height;
					new_line_info.force_line = true;
					new_line_info.container = undefined;
					this._line_count = this._line_count + 1;
					line_list[this._line_count - 1] = new_line_info;
					let char_info = {};
					char_info.acc_width = 0;
					char_info.pre_width = 0;
					char_info.text_info = display_info.text_info;
					char_info.text_object = undefined;
					char_info.text = "\n";
					char_info.ctrl_info = undefined;
					char_info.ctrl = undefined;
					new_line_info.char_count = new_line_info.char_count + 1;
					new_line_info.char_list[new_line_info.char_count - 1] = char_info;
					line_info = new_line_info;
					display_info = undefined;
					display_object = undefined;
					display_index = display_index + 1;
					remain_width = total_width;
				} else if (display_info.text === "\t") {
					if (display_object === undefined) {
						let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
						this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info.text_info));
						display_object = this._ctrl_sys.CreateControl(name, this._link_map);
						this._ctrl_sys.UnRegisterInfo(name);
						display_object.text = "    ";
					}
					let object_width = display_object.width;
					let object_height = display_object.height;
					this.SetDrawText(display_object);
					let calc_text = "\t";
					while (calc_text !== "") {
						let byte_count = ALittle.String_GetByteCount(calc_text, 1);
						let sub_text = __sub(calc_text, 1, byte_count);
						let text_width = this._draw_text.native_show.CalcTextWidth("    ");
						let char_info = {};
						char_info.pre_width = line_info.char_list[line_info.char_count - 1].acc_width;
						char_info.acc_width = char_info.pre_width + text_width;
						char_info.text_info = display_info.text_info;
						char_info.text_object = display_object;
						char_info.text = sub_text;
						char_info.ctrl_info = undefined;
						char_info.ctrl = undefined;
						line_info.char_count = line_info.char_count + 1;
						line_info.char_list[line_info.char_count - 1] = char_info;
						calc_text = __sub(calc_text, byte_count + 1);
					}
					++ line_info.child_count;
					line_info.child_list[line_info.child_count - 1] = display_object;
					if (line_info.acc_height - line_info.pre_height < object_height) {
						line_info.acc_height = line_info.pre_height + object_height;
					}
					remain_width = remain_width - object_width;
					if (remain_width <= 0) {
						let new_line_info = {};
						new_line_info.char_list = [];
						new_line_info.child_list = [];
						new_line_info.char_count = 0;
						new_line_info.child_count = 0;
						new_line_info.pre_height = line_info.acc_height + this._line_spacing;
						new_line_info.acc_height = line_info.acc_height;
						new_line_info.force_line = false;
						new_line_info.container = undefined;
						this._line_count = this._line_count + 1;
						line_list[this._line_count - 1] = new_line_info;
						let char_info = {};
						char_info.acc_width = 0;
						char_info.pre_width = 0;
						char_info.text_info = display_info.text_info;
						char_info.text_object = undefined;
						char_info.text = "";
						char_info.ctrl_info = undefined;
						char_info.ctrl = undefined;
						new_line_info.char_count = new_line_info.char_count + 1;
						new_line_info.char_list[new_line_info.char_count - 1] = char_info;
						line_info = new_line_info;
						remain_width = total_width;
					}
					display_object = undefined;
					display_info = undefined;
					display_index = display_index + 1;
				} else {
					while (true) {
						if (display_info.text === "") {
							display_info = undefined;
							display_index = display_index + 1;
							break;
						}
						if (display_object === undefined) {
							let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
							this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info.text_info));
							display_object = this._ctrl_sys.CreateControl(name, this._link_map);
							this._ctrl_sys.UnRegisterInfo(name);
						}
						let count = display_object._show.CutTextByWidth(__floor(remain_width), display_info.text, __floor(total_width));
						if (count === 0 && line_info.char_count <= 1) {
							count = ALittle.String_GetByteCount(display_info.text, 1);
						}
						if (count === 0) {
							remain_width = 0;
						} else {
							let calc_text = __sub(display_info.text, 1, count);
							display_object.text = calc_text;
							let object_width = display_object.width;
							let object_height = display_object.height;
							this.SetDrawText(display_object);
							let char_count = display_object._show.GetCutWidthListCount();
							for (let i = 1; i <= char_count; i += 1) {
								let byte_count = ALittle.String_GetByteCount(calc_text, 1);
								let sub_text = __sub(calc_text, 1, byte_count);
								let text_width = display_object._show.GetCutWidthByIndex(i - 1);
								let char_info = {};
								char_info.pre_width = line_info.char_list[line_info.char_count - 1].acc_width;
								char_info.acc_width = text_width;
								char_info.text_info = display_info.text_info;
								char_info.text_object = display_object;
								char_info.text = sub_text;
								char_info.ctrl_info = undefined;
								char_info.ctrl = undefined;
								line_info.char_count = line_info.char_count + 1;
								line_info.char_list[line_info.char_count - 1] = char_info;
								calc_text = __sub(calc_text, byte_count + 1);
							}
							remain_width = remain_width - object_width;
							display_object._show.ClearCutWidthCache();
							let new_display_info = ALittle.String_CopyTable(display_info);
							new_display_info.text = __sub(display_info.text, count + 1);
							++ line_info.child_count;
							line_info.child_list[line_info.child_count - 1] = display_object;
							if (line_info.acc_height - line_info.pre_height < object_height) {
								line_info.acc_height = line_info.pre_height + object_height;
							}
							display_info = new_display_info;
							display_object = undefined;
						}
						if (remain_width <= 0) {
							let new_line_info = {};
							new_line_info.char_list = [];
							new_line_info.child_list = [];
							new_line_info.char_count = 0;
							new_line_info.child_count = 0;
							new_line_info.pre_height = line_info.acc_height + this._line_spacing;
							new_line_info.acc_height = line_info.acc_height;
							new_line_info.force_line = false;
							new_line_info.container = undefined;
							this._line_count = this._line_count + 1;
							line_list[this._line_count - 1] = new_line_info;
							let char_info = {};
							char_info.acc_width = 0;
							char_info.pre_width = 0;
							char_info.text_info = display_info.text_info;
							char_info.text_object = undefined;
							char_info.text = "";
							char_info.ctrl_info = undefined;
							char_info.ctrl = undefined;
							new_line_info.char_count = new_line_info.char_count + 1;
							new_line_info.char_list[new_line_info.char_count - 1] = char_info;
							line_info = new_line_info;
							remain_width = total_width;
						}
					}
				}
			} else {
				if (display_object === undefined) {
					if (display_info.ctrl === undefined) {
						let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
						this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info.ctrl_info));
						display_object = this._ctrl_sys.CreateControl(name, this._link_map);
						this._ctrl_sys.UnRegisterInfo(name);
					} else {
						display_object = display_info.ctrl;
					}
				}
				let object_width = display_object.width;
				let object_height = display_object.height;
				if (remain_width >= object_width || (line_info.char_count === 1 && total_width <= object_width)) {
					let char_info = {};
					char_info.pre_width = line_info.char_list[line_info.char_count - 1].acc_width;
					char_info.acc_width = char_info.pre_width + display_object.width;
					char_info.text_info = line_info.char_list[line_info.char_count - 1].text_info;
					char_info.text_object = undefined;
					char_info.text = undefined;
					char_info.ctrl_info = display_info.ctrl_info;
					char_info.ctrl = display_object;
					line_info.char_count = line_info.char_count + 1;
					line_info.char_list[line_info.char_count - 1] = char_info;
					++ line_info.child_count;
					line_info.child_list[line_info.child_count - 1] = display_object;
					if (line_info.acc_height - line_info.pre_height < object_height) {
						line_info.acc_height = line_info.pre_height + object_height;
					}
					remain_width = remain_width - object_width;
					if (remain_width <= 0) {
						let new_line_info = {};
						new_line_info.char_list = [];
						new_line_info.child_list = [];
						new_line_info.char_count = 0;
						new_line_info.child_count = 0;
						new_line_info.pre_height = line_info.acc_height + this._line_spacing;
						new_line_info.acc_height = line_info.acc_height;
						new_line_info.force_line = false;
						new_line_info.container = undefined;
						this._line_count = this._line_count + 1;
						line_list[this._line_count - 1] = new_line_info;
						char_info = {};
						char_info.acc_width = 0;
						char_info.pre_width = 0;
						char_info.text_info = line_info.char_list[line_info.char_count - 1].text_info;
						char_info.text_object = undefined;
						char_info.text = "";
						char_info.ctrl_info = undefined;
						char_info.ctrl = undefined;
						new_line_info.char_count = new_line_info.char_count + 1;
						new_line_info.char_list[new_line_info.char_count - 1] = char_info;
						line_info = new_line_info;
						remain_width = total_width;
					}
					display_object = undefined;
					display_info = undefined;
					display_index = display_index + 1;
				} else {
					let new_line_info = {};
					new_line_info.char_list = [];
					new_line_info.child_list = [];
					new_line_info.char_count = 0;
					new_line_info.child_count = 0;
					new_line_info.pre_height = line_info.acc_height + this._line_spacing;
					new_line_info.acc_height = line_info.acc_height;
					new_line_info.force_line = false;
					new_line_info.container = undefined;
					this._line_count = this._line_count + 1;
					line_list[this._line_count - 1] = new_line_info;
					let char_info = {};
					char_info.acc_width = 0;
					char_info.pre_width = 0;
					char_info.text_info = line_info.char_list[line_info.char_count - 1].text_info;
					char_info.text_object = undefined;
					char_info.text = "";
					char_info.ctrl_info = undefined;
					char_info.ctrl = undefined;
					new_line_info.char_count = new_line_info.char_count + 1;
					new_line_info.char_list[new_line_info.char_count - 1] = char_info;
					line_info = new_line_info;
					remain_width = total_width;
				}
			}
		}
		if (line_info.char_count === 1) {
			line_info.acc_height = line_info.pre_height + this._enter_key_height;
		}
		let line_begin_it = this._line_count + 1;
		line_begin_it = line_begin_it - 1;
		begin_it = line_list[line_begin_it - 1].char_count + 1;
		begin_it = begin_it - 1;
		return [line_begin_it, begin_it];
	},
	DrawImpl : function() {
		this._scroll_list.RemoveAllChild();
		let ___OBJECT_16 = this._line_list;
		for (let line_index = 1; line_index <= ___OBJECT_16.length; ++line_index) {
			let line_info = ___OBJECT_16[line_index - 1];
			if (line_info === undefined) break;
			let displayout = line_info.container;
			if (displayout === undefined) {
				displayout = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
				line_info.container = displayout;
				displayout.width_type = 4;
				displayout.height = line_info.acc_height - line_info.pre_height;
				let offset_x = 0.0;
				let ___OBJECT_17 = line_info.child_list;
				for (let child_index = 1; child_index <= ___OBJECT_17.length; ++child_index) {
					let child = ___OBJECT_17[child_index - 1];
					if (child === undefined) break;
					child.x = offset_x;
					offset_x = offset_x + child.width;
					child.y = displayout.height - child.height;
					displayout.AddChild(child);
				}
			}
			this._scroll_list.AddChild(displayout);
		}
		let child = this._scroll_list.GetChildByIndex(this._line_start_it);
		this._scroll_list.scroll_offset = -child.y - this._start_it_delta;
		this._scroll_list.RefreshClipDisLine();
		this._scroll_list.AdjustScrollBar();
		this._draw_loop = undefined;
	},
	AdjustContentY : function() {
		if (this._draw_loop !== undefined) {
			return;
		}
		let child = this._scroll_list.GetChildByIndex(this._line_start_it);
		this._scroll_list.scroll_offset = -child.y - this._start_it_delta;
		this._scroll_list.RefreshClipDisLine();
		this._scroll_list.AdjustScrollBar();
	},
	Draw : function() {
		if (this._draw_loop !== undefined) {
			return;
		}
		this._draw_loop = ALittle.NewObject(ALittle.LoopFunction, this.DrawImpl.bind(this), 1, 0, 1);
		A_LoopSystem.AddUpdater(this._draw_loop);
	},
	CursorOffsetLR : function(left) {
		let line_list = this._line_list;
		if (this._char_select_it <= line_list[this._line_select_it - 1].char_count) {
			this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
			this.ResetCursor();
			return;
		}
		this.CursorOffsetLRImpl(left);
	},
	CursorOffsetUD : function(up) {
		let line_list = this._line_list;
		if (this._char_select_it <= line_list[this._line_select_it - 1].char_count) {
			this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
			this.ResetCursor();
			return;
		}
		this.CursorOffsetUDImpl(up);
	},
	SelectCursorOffsetLR : function(left) {
		let line_list = this._line_list;
		if (this._char_select_it > line_list[this._line_select_it - 1].char_count) {
			this._line_select_it = this._line_cursor_it;
			this._char_select_it = this._char_cursor_it;
		}
		this.CursorOffsetLRImpl(left);
	},
	SelectCursorOffsetUD : function(up) {
		let line_list = this._line_list;
		if (this._char_select_it > line_list[this._line_select_it - 1].char_count) {
			this._line_select_it = this._line_cursor_it;
			this._char_select_it = this._char_cursor_it;
		}
		this.CursorOffsetUDImpl(up);
	},
	SetCursorToHome : function() {
		let line_list = this._line_list;
		this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		this._char_cursor_it = 1;
		this.ResetCursor();
	},
	SetCursorToEnd : function() {
		let line_list = this._line_list;
		this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count + 1;
		this._char_cursor_it = this._char_cursor_it - 1;
		this.ResetCursor();
	},
	SelectAll : function() {
		let line_list = this._line_list;
		this._line_select_it = 1;
		this._char_select_it = 1;
		this._line_cursor_it = this._line_count + 1;
		this._line_cursor_it = this._line_cursor_it - 1;
		this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count + 1;
		this._char_cursor_it = this._char_cursor_it - 1;
		this.ResetCursorLine();
		this.ResetCursor();
	},
	ResetCursorLine : function() {
		let line_list = this._line_list;
		if (this._line_cursor_it === this._line_count) {
			if (line_list[this._line_cursor_it - 1].acc_height > this._scroll_list.height && this._scroll_list.scroll_offset < 0) {
				this._scroll_list.scroll_offset = this._scroll_list.height - line_list[this._line_cursor_it - 1].acc_height;
				this._scroll_list.RefreshClipDisLine();
				this._scroll_list.AdjustScrollBar();
				while (line_list[this._line_start_it - 1].pre_height > -this._scroll_list.scroll_offset) {
					this._line_start_it = this._line_start_it - 1;
				}
				this._start_it_delta = -this._scroll_list.scroll_offset - line_list[this._line_start_it - 1].pre_height;
				return;
			}
			if (line_list[this._line_cursor_it - 1].acc_height <= this._scroll_list.height) {
				this._scroll_list.scroll_offset = 0;
				this._scroll_list.RefreshClipDisLine();
				this._scroll_list.AdjustScrollBar();
				this._line_start_it = 1;
				this._start_it_delta = 0;
				return;
			}
		}
		if (line_list[this._line_cursor_it - 1].pre_height <= -this._scroll_list.scroll_offset) {
			this._scroll_list.scroll_offset = -line_list[this._line_cursor_it - 1].pre_height;
			this._scroll_list.RefreshClipDisLine();
			this._scroll_list.AdjustScrollBar();
			this._line_start_it = this._line_cursor_it;
		} else if (line_list[this._line_cursor_it - 1].acc_height >= this._scroll_list.height - this._scroll_list.scroll_offset) {
			this._scroll_list.scroll_offset = this._scroll_list.height - line_list[this._line_cursor_it - 1].acc_height;
			this._scroll_list.RefreshClipDisLine();
			this._scroll_list.AdjustScrollBar();
			while (line_list[this._line_start_it - 1].acc_height <= -this._scroll_list.scroll_offset) {
				this._line_start_it = this._line_start_it + 1;
			}
		}
		this._start_it_delta = -this._scroll_list.scroll_offset - line_list[this._line_start_it - 1].pre_height;
	},
	ClickCursor : function(offset_x, offset_y) {
		let line_list = this._line_list;
		this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		[this._line_cursor_it, this._char_cursor_it] = this.GetIteratorByOffset(offset_x, offset_y);
		this.ResetCursorLine();
		this.UpdateFontText();
		this.ResetCursor();
	},
	ClickWordCursor : function(offset_x, offset_y) {
		let line_list = this._line_list;
		[this._line_cursor_it, this._char_cursor_it] = this.GetIteratorByOffset(offset_x, offset_y);
		this._char_select_it = this._char_cursor_it;
		this._line_select_it = this._line_cursor_it;
		while (true) {
			let has_find = false;
			while (true) {
				let str = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].text;
				if (str !== undefined && __len(str) === 1 && str !== "_" && this.CharIsNumber(str) === false && this.CharIsLetter(str) === false) {
					has_find = true;
					break;
				}
				if (this._char_cursor_it === 1) {
					break;
				}
				this._char_cursor_it = this._char_cursor_it - 1;
			}
			if (has_find) {
				break;
			}
			if (this._line_cursor_it === 1) {
				break;
			}
			this._line_cursor_it = this._line_cursor_it - 1;
			this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count + 1;
			this._char_cursor_it = this._char_cursor_it - 1;
		}
		let cursor_tmp = this._char_select_it;
		let line_cursor_tmp = this._line_select_it;
		while (true) {
			cursor_tmp = cursor_tmp + 1;
			if (cursor_tmp > line_list[this._line_select_it - 1].char_count) {
				line_cursor_tmp = line_cursor_tmp + 1;
				if (line_cursor_tmp > this._line_count) {
					break;
				}
				cursor_tmp = 1;
			}
			let str = line_list[line_cursor_tmp - 1].char_list[cursor_tmp - 1].text;
			if (str !== undefined && __len(str) === 1 && str !== "_" && this.CharIsNumber(str) === false && this.CharIsLetter(str) === false) {
				break;
			}
			this._char_select_it = cursor_tmp;
			this._line_select_it = line_cursor_tmp;
		}
		if (this._line_select_it > this._line_count) {
			this._line_select_it = this._line_select_it - 1;
			this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		}
		if (this._char_select_it > line_list[this._line_select_it - 1].char_count) {
			this._char_select_it = this._char_select_it - 1;
		}
		if (this._line_select_it === this._line_cursor_it && this._char_select_it === this._char_cursor_it) {
			this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		}
		this.ResetCursorLine();
		this.UpdateFontText();
		this.ResetCursor();
		return this._char_select_it <= line_list[this._line_select_it - 1].char_count;
	},
	DragCursorBegin : function() {
		let line_list = this._line_list;
		this._line_select_it = this._line_cursor_it;
		this._char_select_it = this._char_cursor_it;
	},
	DragCursor : function(offset_x, offset_y) {
		let line_list = this._line_list;
		[this._line_cursor_it, this._char_cursor_it] = this.GetIteratorByOffset(offset_x, offset_y);
		if (line_list[this._line_cursor_it - 1].pre_height === -this._scroll_list.scroll_offset && this._line_cursor_it !== 1 && offset_y < 0) {
			this._line_cursor_it = this._line_cursor_it - 1;
			if (this._char_cursor_it > line_list[this._line_cursor_it - 1].char_count) {
				this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
			}
		}
		if (this._line_cursor_it === this._line_count && line_list[this._line_cursor_it - 1].pre_height === line_list[this._line_cursor_it - 1].acc_height && this._line_cursor_it !== 1) {
			this._line_cursor_it = this._line_cursor_it - 1;
			this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
		}
		this.ResetCursorLine();
		this.ResetCursor();
	},
	DragEdit : function(delta_y) {
		let event = {};
		event.target = this._scroll_list;
		event.delta_x = 0;
		event.delta_y = delta_y;
		this._scroll_list.HandleDrag(event);
		let line_list = this._line_list;
		if (line_list[this._line_start_it - 1].acc_height <= -this._scroll_list.scroll_offset) {
			this._line_start_it = this._line_start_it + 1;
			while (line_list[this._line_start_it - 1].acc_height <= -this._scroll_list.scroll_offset) {
				this._line_start_it = this._line_start_it + 1;
			}
		} else if (line_list[this._line_start_it - 1].pre_height > -this._scroll_list.scroll_offset) {
			this._line_start_it = this._line_start_it - 1;
			while (line_list[this._line_start_it - 1].pre_height > -this._scroll_list.scroll_offset) {
				this._line_start_it = this._line_start_it - 1;
			}
		}
		this._start_it_delta = -this._scroll_list.scroll_offset - line_list[this._line_start_it - 1].pre_height;
		this.ResetCursor();
	},
	CheckMultiCursor : function(offset_x, offset_y, trans) {
		let line_list = this._line_list;
		let line_cursor_it = undefined;
		let char_cursor_it = undefined;
		if (trans) {
			line_cursor_it = this._line_cursor_it;
			char_cursor_it = this._char_cursor_it;
		} else {
			[line_cursor_it, char_cursor_it] = this.GetIteratorByOffset(offset_x, offset_y);
		}
		if (char_cursor_it !== 1) {
			this._line_cursor_it = line_cursor_it;
			this._char_cursor_it = char_cursor_it;
			this._line_select_it = line_cursor_it;
			this._char_select_it = char_cursor_it - 1;
		} else {
			if (line_list[line_cursor_it - 1].char_count > 1) {
				this._line_cursor_it = line_cursor_it;
				this._char_cursor_it = char_cursor_it + 1;
				this._line_select_it = line_cursor_it;
				this._char_select_it = char_cursor_it;
			} else {
				if (line_cursor_it > 1) {
					this._line_cursor_it = line_cursor_it;
					this._char_cursor_it = char_cursor_it;
					this._line_select_it = line_cursor_it - 1;
					this._char_select_it = line_list[this._line_select_it - 1].char_count - 1;
					if (this._char_select_it === 0) {
						this._char_select_it = 1;
					}
				} else {
					if (this._line_count > 1) {
						this._line_cursor_it = line_cursor_it + 1;
						if (line_list[this._line_cursor_it - 1].char_count === 1) {
							this._char_cursor_it = 1;
						} else {
							this._char_cursor_it = 2;
						}
						this._line_select_it = line_cursor_it;
						this._char_select_it = char_cursor_it;
					} else {
						return false;
					}
				}
			}
		}
		return true;
	},
	ClickMultiCursor : function() {
		this.UpdateFontText();
		this.ResetCursorLine();
		this.ResetCursor();
	},
	DragMultiCursor : function(offset_x, offset_y) {
		let line_list = this._line_list;
		offset_x = offset_x + this._drag_delta_x;
		offset_y = offset_y + this._drag_delta_y;
		[this._line_cursor_it, this._char_cursor_it] = this.GetIteratorByOffset(offset_x, offset_y);
		if (line_list[this._line_cursor_it - 1].pre_height === -this._scroll_list.scroll_offset && this._line_cursor_it !== 1 && offset_y < 0) {
			this._line_cursor_it = this._line_cursor_it - 1;
			if (this._char_cursor_it > line_list[this._line_cursor_it - 1].char_count) {
				this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
			}
		}
		if (this._line_cursor_it === this._line_count && line_list[this._line_cursor_it - 1].pre_height === line_list[this._line_cursor_it - 1].acc_height && this._line_cursor_it !== 1) {
			this._line_cursor_it = this._line_cursor_it - 1;
			this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
		}
		this.ResetCursorLine();
		this.ResetCursor();
	},
	ShowDefaultText : function() {
		if (this._is_focus === false) {
			if (this._focus_cursor && this.is_empty) {
				this._default_text_area.visible = true;
			} else {
				this._default_text_area.visible = false;
			}
		} else {
			this._default_text_area.visible = false;
		}
	},
	CursorOffsetLRImpl : function(left) {
		let line_list = this._line_list;
		if (left) {
			if (this._line_cursor_it === 1 && this._char_cursor_it === 1) {
				return;
			}
			if (this._line_cursor_it === this._line_start_it) {
				if (this._char_cursor_it === 1) {
					this._line_cursor_it = this._line_cursor_it - 1;
					this._line_start_it = this._line_start_it - 1;
					this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count + 1;
					this._char_cursor_it = this._char_cursor_it - 1;
				} else {
					this._char_cursor_it = this._char_cursor_it - 1;
				}
			} else {
				if (this._char_cursor_it === 1) {
					this._line_cursor_it = this._line_cursor_it - 1;
					this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count + 1;
					this._char_cursor_it = this._char_cursor_it - 1;
				} else {
					this._char_cursor_it = this._char_cursor_it - 1;
				}
			}
			if (this._line_cursor_it === this._line_count && line_list[this._line_cursor_it - 1].pre_height === line_list[this._line_cursor_it - 1].acc_height && this._line_cursor_it !== 1) {
				this._line_cursor_it = this._line_cursor_it - 1;
				this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
			}
			this.ResetCursorLine();
			this.ResetCursor();
			return;
		}
		let end_line_it = this._line_count + 1;
		end_line_it = end_line_it - 1;
		let end_char_it = line_list[end_line_it - 1].char_count + 1;
		end_char_it = end_char_it - 1;
		if (this._line_cursor_it === end_line_it && this._char_cursor_it === end_char_it) {
			return;
		}
		end_char_it = line_list[this._line_cursor_it - 1].char_count + 1;
		end_char_it = end_char_it - 1;
		if (this._char_cursor_it === end_char_it) {
			this._line_cursor_it = this._line_cursor_it + 1;
			this._char_cursor_it = 1;
		} else {
			this._char_cursor_it = this._char_cursor_it + 1;
		}
		if (this._line_cursor_it === this._line_count && line_list[this._line_cursor_it - 1].pre_height === line_list[this._line_cursor_it - 1].acc_height && this._line_cursor_it !== 1) {
			this._line_cursor_it = this._line_cursor_it - 1;
			this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
		}
		this.ResetCursorLine();
		this.ResetCursor();
	},
	CursorOffsetUDImpl : function(up) {
		let line_list = this._line_list;
		if (up) {
			if (this._line_cursor_it === 1) {
				return;
			}
			let offset_x = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
			if (this._line_cursor_it === this._line_start_it) {
				this._line_start_it = this._line_start_it - 1;
			}
			this._line_cursor_it = this._line_cursor_it - 1;
			this._char_cursor_it = 1;
			let end_char_it = line_list[this._line_cursor_it - 1].char_count + 1;
			while (this._char_cursor_it !== end_char_it) {
				if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width >= offset_x) {
					break;
				}
				this._char_cursor_it = this._char_cursor_it + 1;
			}
			if (this._char_cursor_it === end_char_it) {
				end_char_it = end_char_it - 1;
				this._char_cursor_it = end_char_it;
			}
			if (this._line_cursor_it === this._line_count && line_list[this._line_cursor_it - 1].pre_height === line_list[this._line_cursor_it - 1].acc_height && this._line_cursor_it !== 1) {
				this._line_cursor_it = this._line_cursor_it - 1;
				this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
			}
			this.ResetCursorLine();
			this.ResetCursor();
			return;
		}
		let line_end_test_it = this._line_count + 1;
		line_end_test_it = line_end_test_it - 1;
		if (this._line_cursor_it === line_end_test_it) {
			this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
			this.ResetCursorLine();
			this.ResetCursor();
			return;
		}
		let offset_x = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
		this._line_cursor_it = this._line_cursor_it + 1;
		this._char_cursor_it = 1;
		let end_char_it = line_list[this._line_cursor_it - 1].char_count + 1;
		while (this._char_cursor_it !== end_char_it) {
			if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width >= offset_x) {
				break;
			}
			this._char_cursor_it = this._char_cursor_it + 1;
		}
		if (this._char_cursor_it === end_char_it) {
			end_char_it = end_char_it - 1;
			this._char_cursor_it = end_char_it;
		}
		if (this._line_cursor_it === this._line_count && line_list[this._line_cursor_it - 1].pre_height === line_list[this._line_cursor_it - 1].acc_height && this._line_cursor_it !== 1) {
			this._line_cursor_it = this._line_cursor_it - 1;
			this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
		}
		this.ResetCursorLine();
		this.ResetCursor();
	},
	GetIteratorByOffset : function(offset_x, offset_y) {
		let line_list = this._line_list;
		let line_it = this._line_start_it;
		let line_end_it = this._line_count + 1;
		let real_offset_y = offset_y + line_list[this._line_start_it - 1].pre_height + this._start_it_delta;
		while (line_it !== line_end_it) {
			if (real_offset_y <= line_list[line_it - 1].acc_height) {
				let half_line_height = (line_list[line_it - 1].acc_height - line_list[line_it - 1].pre_height) * 0.5;
				if (real_offset_y - line_list[line_it - 1].acc_height > half_line_height) {
					line_it = line_it + 1;
				}
				break;
			} else {
				line_it = line_it + 1;
			}
		}
		if (line_it === line_end_it) {
			line_end_it = line_end_it - 1;
			line_it = line_end_it;
		}
		let line_it_result = line_it;
		let real_offset_x = offset_x;
		let char_it = 1;
		let char_end_it = line_list[line_it - 1].char_count + 1;
		let line = line_list[line_it - 1];
		while (char_it !== char_end_it) {
			if (real_offset_x <= line.char_list[char_it - 1].acc_width) {
				let half_char_width = (line.char_list[char_it - 1].acc_width - line.char_list[char_it - 1].pre_width) * 0.5;
				if (real_offset_x - line.char_list[char_it - 1].pre_width < half_char_width && char_it !== 1) {
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
		let char_it_result = char_it;
		return [line_it_result, char_it_result];
	},
	get is_input() {
		return true;
	},
	get is_empty() {
		return this._line_count === 1 && this._line_list[1 - 1].char_count === 1;
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
			this.ClickCursor(rel_x - this._scroll_list.x, rel_y - this._scroll_list.y);
		} else {
			this.ClickCursor(rel_x - this._scroll_list.x, rel_y - this._scroll_list.y);
		}
	},
	SetMultiCursor : function(rel_x, rel_y) {
		if (this._auto_ims) {
			this.OpenIME();
		}
		let result = this.CheckMultiCursor(rel_x - this._scroll_list.x, rel_y - this._scroll_list.y, false);
		if (result === false) {
			return false;
		}
		this._is_selecting = true;
		if (this._multi_cursor === false) {
			this._multi_cursor = true;
			this._cursor.visible = false;
			this._start_cursor.visible = true;
			this._end_cursor.visible = true;
			this.ClickMultiCursor();
		} else {
			this.ClickMultiCursor();
		}
		return true;
	},
	TransToCursor : function() {
		if (this._multi_cursor === false) {
			return;
		}
		let line_list = this._line_list;
		if (this._end_cursor_data === "select") {
			this._line_cursor_it = this._line_select_it;
			this._char_cursor_it = this._char_select_it;
		}
		this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		this._is_selecting = false;
		this._multi_cursor = false;
		this._start_cursor.visible = false;
		this._end_cursor.visible = false;
		this._cursor.visible = true;
		this.UpdateFontText();
		this.ResetCursorLine();
		this.ResetCursor();
	},
	TransToMulti : function() {
		if (this._multi_cursor) {
			return false;
		}
		let result = this.CheckMultiCursor(undefined, undefined, true);
		if (result === false) {
			return false;
		}
		this._is_selecting = true;
		this._multi_cursor = true;
		this._cursor.visible = false;
		this._start_cursor.visible = true;
		this._end_cursor.visible = true;
		this.UpdateFontText();
		this.ResetCursorLine();
		this.ResetCursor();
		return true;
	},
	OpenIME : function(x, y, width, height) {
		if (this._editable) {
			this.ResetCursor();
			if (x !== undefined && y !== undefined && width !== undefined && height !== undefined) {
				ALittle.System_SetIMERect(__floor(x), __floor(y), __floor(width), __floor(height));
			} else {
				let [global_x, global_y] = this.LocalToGlobal();
				global_x = global_x + this.cursor_x;
				global_y = global_y + (this.cursor_y + this.font_size) * this.scale_y;
				ALittle.System_SetIMERect(__floor(global_x), __floor(global_y), 10, __floor(5 + this._ims_padding));
			}
			ALittle.System_OpenIME();
		}
	},
	CloseIME : function() {
		ALittle.System_CloseIME();
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
		if (this._multi_cursor === false) {
			this._cursor.visible = true;
		}
		this.ShowDefaultText();
	},
	HandleLButtonDown : function(event) {
		if (this._multi_cursor === false) {
			this._is_longclick = false;
			if (event.rel_x >= this._scroll_list.x && event.rel_x <= this._scroll_list.x + this._scroll_list.width && event.rel_y >= this._scroll_list.y && event.rel_y <= this._scroll_list.y + this._scroll_list.height) {
				if (event.count % 3 === 1) {
					this._is_selecting = false;
					this.ClickCursor(event.rel_x - this._scroll_list.x, event.rel_y - this._scroll_list.y);
					this.DispatchEvent(___all_struct.get(-1053992999), {});
				} else if (event.count % 3 === 2) {
					this._is_selecting = this.ClickWordCursor(event.rel_x - this._scroll_list.x, event.rel_y - this._scroll_list.y);
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
				if (event.rel_x >= this._scroll_list.x && event.rel_x <= this._scroll_list.x + this._scroll_list.width && event.rel_y >= this._scroll_list.y && event.rel_y <= this._scroll_list.y + this._scroll_list.height) {
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
				this.ClickCursor(event.rel_x - this._scroll_list.x, event.rel_y - this._scroll_list.y);
				this.DispatchEvent(___all_struct.get(-1053992999), {});
			}
		}
	},
	HandleLongLButtonDown : function(event) {
		if (this._is_click) {
			if (this.editable === false) {
				let result = this.CheckMultiCursor(event.rel_x - this._scroll_list.x, event.rel_y - this._scroll_list.y, false);
				if (result) {
					this._is_selecting = true;
					if (this._multi_cursor === false) {
						this._multi_cursor = true;
						this._cursor.visible = false;
						this._start_cursor.visible = true;
						this._end_cursor.visible = true;
						this.ClickMultiCursor();
					} else {
						this.ClickMultiCursor();
					}
				}
			} else {
				this._multi_cursor = false;
				this._start_cursor.visible = false;
				this._end_cursor.visible = false;
				this._cursor.visible = true;
				this.ClickCursor(event.rel_x - this._scroll_list.x, event.rel_y - this._scroll_list.y);
			}
			let e = {};
			e.target = this;
			e.abs_x = event.abs_x;
			e.abs_y = event.abs_y;
			e.rel_x = event.rel_x;
			e.rel_y = event.rel_y;
			this.DispatchEvent(___all_struct.get(774620468), e);
			this._is_longclick = true;
		}
	},
	CheckAtKeyInput : function(input_text) {
		if (input_text !== "@") {
			return false;
		}
		let line_list = this._line_list;
		let line_cursor_it = this._line_cursor_it;
		let char_cursor_it = this._char_cursor_it;
		if (this._line_cursor_it === 1 && this._char_cursor_it === 1) {
			this.DispatchEvent(___all_struct.get(1816229739), {});
			return true;
		}
		if (this._line_cursor_it > 1 && this._char_cursor_it === 1) {
			line_cursor_it = line_cursor_it - 1;
			char_cursor_it = line_list[line_cursor_it - 1].char_count;
		}
		let char_info = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1];
		let forward_text = char_info.text;
		if (forward_text === undefined || !(this.CharIsNumber(forward_text) || this.CharIsLetter(forward_text))) {
			this.DispatchEvent(___all_struct.get(1816229739), {});
			return true;
		}
		return false;
	},
	HandleTextInput : function(event) {
		if (this._multi_cursor === false) {
			if ((this._editable || event.custom)) {
				if (this.CheckAtKeyInput(event.text)) {
					return;
				}
				this._is_selecting = false;
				let is_change = this.InsertTextNative(event.text);
				if (is_change) {
					this.DispatchEvent(___all_struct.get(958494922), {});
					this.ShowDefaultText();
				}
			}
		} else {
			if (this._is_selecting && this._editable) {
				this._is_selecting = false;
				let is_change = this.InsertTextNative(event.text);
				if (is_change) {
					this.DispatchEvent(___all_struct.get(958494922), {});
					this.ShowDefaultText();
				}
				this._multi_cursor = false;
			}
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
					let line_temp_it = this._line_select_it;
					let char_temp_it = this._char_select_it;
					this._line_select_it = this._line_cursor_it;
					this._char_select_it = this._char_cursor_it;
					this._line_cursor_it = line_temp_it;
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
				this.DispatchEvent(___all_struct.get(9565867), {});
			} else if (this._is_click) {
				this._is_drag_begin = true;
				this.DispatchEvent(___all_struct.get(9565867), {});
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
			this.DragCursor(event.rel_x - this._scroll_list.x, event.rel_y - this._scroll_list.y);
		} else {
			if (this._is_click_cursor) {
				this.DragMultiCursor(event.rel_x - this._scroll_list.x, event.rel_y - this._scroll_list.y);
			} else {
				if (this._line_list[1 - 1] !== undefined && this._line_list[1 - 1].acc_height !== this._line_list[1 - 1].pre_height) {
					this._click_drag_delta_x = this._click_drag_delta_x + __abs(event.delta_x);
					this._click_drag_delta_y = this._click_drag_delta_y + __abs(event.delta_y);
					this.DragEdit(event.delta_y);
				}
			}
			this.DispatchEvent(___all_struct.get(291295687), {});
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
			this.DispatchEvent(___all_struct.get(-203792390), {});
		}
	},
	HandleMButtonWheel : function(event) {
		if (this._multi_cursor === false) {
			if (event.delta_y > 0) {
				this._is_selecting = false;
				this.CursorOffsetUD(true);
			} else if (event.delta_y < 0) {
				this._is_selecting = false;
				this.CursorOffsetUD(false);
			}
			if (event.delta_x > 0) {
				this._is_selecting = false;
				this.SelectCursorOffsetLR(true);
			} else if (event.delta_x < 0) {
				this._is_selecting = false;
				this.SelectCursorOffsetLR(false);
			}
		} else {
			this.DragEdit(event.delta_y);
		}
	},
	HandleMoveIn : function(event) {
		ALittle.System_SetEditCursor();
	},
	HandleMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleKeyDown : function(event) {
		let is_change = false;
		if (event.sym === 9) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					is_change = this.InsertTextNative("\t");
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					is_change = this.InsertTextNative("\t");
					event.handled = true;
					this._multi_cursor = false;
				}
			}
		} else if (event.sym === 1073741904) {
			if (this._multi_cursor === false) {
				if (event.mod & 0x0003 === 0) {
					this._is_selecting = false;
					this.CursorOffsetLR(true);
					this.UpdateFontText();
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
					this.UpdateFontText();
				} else {
					this._is_selecting = true;
					this.SelectCursorOffsetLR(false);
				}
			}
			event.handled = true;
		} else if (event.sym === 1073741906) {
			if (this._multi_cursor === false) {
				if (event.mod & 0x0003 === 0) {
					this._is_selecting = false;
					this.CursorOffsetUD(true);
					this.UpdateFontText();
				} else {
					this._is_selecting = true;
					this.SelectCursorOffsetUD(true);
				}
			}
			event.handled = true;
		} else if (event.sym === 1073741905) {
			if (this._multi_cursor === false) {
				if (event.mod & 0x0003 === 0) {
					this._is_selecting = false;
					this.CursorOffsetUD(false);
					this.UpdateFontText();
				} else {
					this._is_selecting = true;
					this.SelectCursorOffsetUD(false);
				}
			}
			event.handled = true;
		} else if (event.sym === 8) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					is_change = this.DeleteText(true);
					event.handled = true;
					this.UpdateFontText();
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					is_change = this.DeleteText(true);
					event.handled = true;
					this.UpdateFontText();
					this._multi_cursor = false;
				}
			}
		} else if (event.sym === 127) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					is_change = this.DeleteText(false);
					event.handled = true;
					this.UpdateFontText();
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					is_change = this.DeleteText(false);
					event.handled = true;
					this.UpdateFontText();
					this._multi_cursor = false;
				}
			}
		} else if (event.sym === 1073741898) {
			this._is_selecting = false;
			this.SetCursorToHome();
			event.handled = true;
			this.UpdateFontText();
		} else if (event.sym === 1073741901) {
			this._is_selecting = false;
			this.SetCursorToEnd();
			event.handled = true;
			this.UpdateFontText();
		} else if (event.sym === 13 || event.sym === 1073741912) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					is_change = this.InsertTextNative("\n");
					event.handled = true;
					this.UpdateFontText();
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					is_change = this.InsertTextNative("\n");
					event.handled = true;
					this.UpdateFontText();
					this._multi_cursor = false;
				}
			}
		} else if (event.sym === 120 && event.mod & 0x00c0 !== 0) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					let select_text = this.GetSelectText();
					if (select_text[1 - 1] !== undefined) {
						ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text));
						is_change = this.DeleteSelectText();
					}
					this.UpdateFontText();
					event.handled = true;
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					let select_text = this.GetSelectText();
					if (select_text[1 - 1] !== undefined) {
						ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text));
						is_change = this.DeleteSelectText();
					}
					this.UpdateFontText();
					event.handled = true;
					this._multi_cursor = false;
				}
			}
		} else if (event.sym === 99 && event.mod & 0x00c0 !== 0) {
			let select_text = this.GetSelectText();
			if (select_text[1 - 1] !== undefined) {
				ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text));
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
					event.handled = true;
					this._multi_cursor = false;
				}
			}
		} else if (event.sym === 97 && event.mod & 0x00c0 !== 0) {
			this._is_selecting = true;
			this.SelectAll();
			event.handled = true;
		}
		if (is_change) {
			this.DispatchEvent(___all_struct.get(958494922), {});
			this._current_flash_alpha = 1.5;
			this.ShowDefaultText();
		}
	},
	InsertText : function(display_list, selected) {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		this.InsertDisplayListNative(display_list, selected);
		this._multi_cursor = false;
		this.ShowDefaultText();
	},
	InsertWord : function(word_text) {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		this.InsertTextNative(word_text);
		this.TransToCursor();
		this.ShowDefaultText();
	},
	CopyText : function(return_cursor) {
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
			this.UpdateFontText();
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	CutWord : function() {
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
			this.UpdateFontText();
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
		this.ClearText();
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
}, "ALittle.RichEdit");

}
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
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __floor = ALittle.Math_Floor;
let __remove = ALittle.List_Remove;
let __sin = ALittle.Math_Sin;
if (ALittle.DisplayView === undefined) throw new Error(" extends class:ALittle.DisplayView is undefined");
ALittle.ScrollList = JavaScript.Class(ALittle.DisplayView, {
	Ctor : function(ctrl_sys) {
		this._width = 0;
		this._height = 0;
		this._drag_delta_x = 0;
		this._drag_delta_y = 0;
		this._drag_delta_table = [];
		this._drag_delta_table_count = 0;
		this._drag_rate = 0.2;
		this._open_extends_drag = false;
		this._clip_atonce = false;
		this._drag_time = 0;
		this._max_speed = 40;
		this._type = 2;
		this._scroll_linear = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
		this._scroll_linear.width_type = 4;
		this._scroll_linear.type = 2;
		ALittle.DisplayView.AddChild.call(this, this._scroll_linear);
		this._scroll_linear.AddEventListener(___all_struct.get(-431205740), this, this.HandleLinearResize);
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
	GetChildIndex : function(child) {
		return this._scroll_linear.GetChildIndex(child);
	},
	SetChildIndex : function(child, index) {
		this._scroll_linear.SetChildIndex(child, index);
		this.RefreshClipDisLine();
		return true;
	},
	GetChildByIndex : function(index) {
		return this._scroll_linear.GetChildByIndex(index);
	},
	get childs() {
		return this._scroll_linear.childs;
	},
	get child_count() {
		return this._scroll_linear.child_count;
	},
	set type(value) {
		if (this._type === value) {
			return;
		}
		this._type = value;
		if (this._type === 1) {
			this._scroll_linear.width_type = 1;
			this._scroll_linear.height_type = 4;
			this._scroll_linear.type = 1;
		} else {
			this._scroll_linear.width_type = 4;
			this._scroll_linear.height_type = 1;
			this._scroll_linear.type = 2;
		}
		this.RefreshChild(false);
	},
	get type() {
		return this._type;
	},
	AddChild : function(child, index) {
		if (child === undefined) {
			return false;
		}
		if (this._scroll_linear.AddChild(child, index) === false) {
			return false;
		}
		this.RefreshChild(false);
		return true;
	},
	RemoveChild : function(child) {
		if (child === undefined) {
			return false;
		}
		if (this._scroll_linear.RemoveChild(child) === false) {
			return false;
		}
		this.RefreshChild(false);
		return true;
	},
	SpliceChild : function(index, count) {
		let result = this._scroll_linear.SpliceChild(index, count);
		if (result !== 0) {
			this.RefreshChild(false);
		}
		return result;
	},
	AddChildEffect : function(child, up) {
		if (child === undefined) {
			return false;
		}
		if (up) {
			if (this._type === 1) {
				let target_value = this._scroll_linear.x + this._scroll_linear.width;
				if (this._scroll_linear.AddChild(child, 1) === false) {
					return false;
				}
				this._scroll_linear.x = target_value - this._scroll_linear.width;
			} else {
				let target_value = this._scroll_linear.y + this._scroll_linear.height;
				if (this._scroll_linear.AddChild(child, 1) === false) {
					return false;
				}
				this._scroll_linear.y = target_value - this._scroll_linear.height;
			}
		} else {
			if (this._scroll_linear.AddChild(child) === false) {
				return false;
			}
		}
		this.RefreshChild(false);
		return true;
	},
	RemoveChildEffect : function(up, loop) {
		if (up) {
			if (this._type === 1) {
				let child = this._scroll_linear.GetChildByIndex(1);
				let target_value = this._scroll_linear.x + this._scroll_linear.width;
				if (this._scroll_linear.RemoveChild(child) === false) {
					return false;
				}
				this._scroll_linear.x = target_value - this._scroll_linear.width;
			} else {
				let child = this._scroll_linear.GetChildByIndex(1);
				let target_value = this._scroll_linear.y + this._scroll_linear.height;
				if (this._scroll_linear.RemoveChild(child) === false) {
					return false;
				}
				this._scroll_linear.y = target_value - this._scroll_linear.height;
			}
		} else {
			let child = this._scroll_linear.GetChildByIndex(this._scroll_linear.child_count);
			if (this._scroll_linear.RemoveChild(child) === false) {
				return false;
			}
		}
		if (loop) {
			this.RefreshChild(true);
		} else {
			this.RefreshChild(false);
		}
		return true;
	},
	HasChild : function(child) {
		return this._scroll_linear.HasChild(child);
	},
	RemoveAllChild : function() {
		if (this._type === 1) {
			A_LoopSystem.RemoveUpdater(this._drag_loop_x);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
			this._scroll_linear.x = 0;
		} else {
			A_LoopSystem.RemoveUpdater(this._drag_loop_y);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
			this._scroll_linear.y = 0;
		}
		this._scroll_linear.RemoveAllChild();
		this.UpdateLoadingShow();
		this.AdjustScrollBar();
	},
	RefreshChild : function(loop) {
		if (this._type === 1) {
			let linear_width = this._scroll_linear.width;
			let target_x = undefined;
			if (linear_width >= this._width) {
				if (this._scroll_linear.x > 0) {
					target_x = 0;
				} else if (this._scroll_linear.x < -linear_width + this._width) {
					target_x = -linear_width + this._width;
				}
			} else {
				target_x = 0;
			}
			if (target_x === undefined || target_x === this._scroll_linear.x) {
				A_LoopSystem.RemoveUpdater(this._drag_loop_x);
				this.RefreshClipDisLine();
				this.AdjustScrollBar();
				return;
			}
			if (this._drag_loop_x !== undefined && this._drag_loop_x.IsCompleted() === false) {
				let speed = this._drag_loop_x.speed;
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				A_LoopSystem.RemoveUpdater(this._drag_loop_x);
				let time = (target_x - this._scroll_linear.x) / speed;
				this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", target_x, __floor(time), 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_x);
			} else {
				if (loop) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_x);
					this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", target_x, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_x);
				} else {
					this._scroll_linear.x = target_x;
				}
			}
		} else {
			let linear_height = this._scroll_linear.height;
			let target_y = undefined;
			if (linear_height >= this._height) {
				if (this._scroll_linear.y > 0) {
					target_y = 0;
				} else if (this._scroll_linear.y < -linear_height + this._height) {
					target_y = -linear_height + this._height;
				}
			} else {
				target_y = 0;
			}
			if (target_y === undefined || target_y === this._scroll_linear.y) {
				A_LoopSystem.RemoveUpdater(this._drag_loop_y);
				this.RefreshClipDisLine();
				this.AdjustScrollBar();
				return;
			}
			if (this._drag_loop_y !== undefined && this._drag_loop_y.IsCompleted() === false) {
				let speed = this._drag_loop_y.speed;
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				A_LoopSystem.RemoveUpdater(this._drag_loop_y);
				let time = (target_y - this._scroll_linear.y) / speed;
				this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", target_y, __floor(time), 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_y);
			} else {
				if (loop) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_y);
					this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", target_y, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_y);
				} else {
					this._scroll_linear.y = target_y;
				}
			}
		}
		this.RefreshClipDisLine();
		this.AdjustScrollBar();
	},
	set clip_atonce(value) {
		this._clip_atonce = value;
	},
	get clip_atonce() {
		return this._clip_atonce;
	},
	set scroll_offset(value) {
		if (this._type === 1) {
			A_LoopSystem.RemoveUpdater(this._drag_loop_x);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
			if (value > 0) {
				value = 0;
			}
			let total_width = this.width;
			let linear_width = this._scroll_linear.width;
			if (total_width < linear_width) {
				let delta = total_width - linear_width;
				if (value < delta) {
					value = delta;
				}
			}
			this._scroll_linear.x = value;
			this.AdjustScrollBar();
		} else {
			A_LoopSystem.RemoveUpdater(this._drag_loop_y);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
			if (value > 0) {
				value = 0;
			}
			let total_height = this.height;
			let linear_height = this._scroll_linear.height;
			if (total_height < linear_height) {
				let delta = total_height - linear_height;
				if (value < delta) {
					value = delta;
				}
			}
			this._scroll_linear.y = value;
			this.AdjustScrollBar();
		}
	},
	get scroll_offset() {
		if (this._type === 1) {
			return this._scroll_linear.x;
		}
		return this._scroll_linear.y;
	},
	ScrollToBottom : function() {
		if (this.height >= this.real_height) {
			return;
		}
		this.scroll_offset = this.height - this.real_height;
	},
	set gap(value) {
		if (value === undefined) {
			value = 0;
		}
		this._scroll_linear.gap = value;
		this.RefreshClipDisLine();
		this.AdjustScrollBar();
	},
	get gap() {
		return this._scroll_linear.gap;
	},
	get real_height() {
		return this._scroll_linear.height;
	},
	get real_width() {
		return this._scroll_linear.width;
	},
	set width(value) {
		if (this._type === 2) {
			ALittle.DisplayView.__setter.width.call(this, value);
			return;
		}
		if (this._width === value) {
			return;
		}
		this._width = value;
		if (this._width_type === 1) {
			this._width_value = this._width;
		}
		this._show.SetWidth(this._width);
		if (this._scroll_bar !== undefined) {
			let linear_width = this._scroll_linear.width;
			let rate = this._scroll_bar.offset_rate;
			if (linear_width < this._width) {
				rate = 0;
			}
			this._scroll_bar.width = this._width;
			this._scroll_bar.total_size = linear_width;
			this._scroll_bar.show_size = this._width;
			this._scroll_bar.offset_rate = rate;
			this._scroll_bar.offset_step = 0.1;
			let x = 0.0;
			if (linear_width > this._width) {
				let total_width = linear_width - this._width;
				x = -total_width * rate;
			}
			this._scroll_linear.x = x;
		}
		this.RefreshClipDisLine();
	},
	set height(value) {
		if (this._type === 1) {
			ALittle.DisplayView.__setter.height.call(this, value);
			return;
		}
		if (this._height === value) {
			return;
		}
		this._height = value;
		if (this._height_type === 1) {
			this._height_value = this._height;
		}
		this._show.SetHeight(this._height);
		if (this._scroll_bar !== undefined) {
			let linear_height = this._scroll_linear.height;
			let rate = this._scroll_bar.offset_rate;
			if (linear_height < this._height) {
				rate = 0;
			}
			this._scroll_bar.height = this._height;
			this._scroll_bar.total_size = linear_height;
			this._scroll_bar.show_size = this._height;
			this._scroll_bar.offset_rate = rate;
			this._scroll_bar.offset_step = 0.1;
			let y = 0.0;
			if (linear_height > this._height) {
				let total_height = linear_height - this._height;
				y = -total_height * rate;
			}
			this._scroll_linear.y = y;
		}
		this.RefreshClipDisLine();
	},
	set right_scrollbar(value) {
		if (this._scroll_bar !== undefined) {
			A_LoopSystem.RemoveUpdater(this._scroll_bar_loop);
			ALittle.DisplayView.RemoveChild.call(this, this._scroll_bar);
			this._scroll_bar.RemoveEventListener(___all_struct.get(958494922), this, this.HandleRightScrollBarChange);
			this._scroll_bar.RemoveEventListener(___all_struct.get(1309977874), this, this.HandleRightScrollBarChangeEnd);
		}
		this._scroll_bar = value;
		if (this._scroll_bar !== undefined) {
			if (this._type === 1) {
				this._scroll_bar.alpha = 0;
				this._scroll_bar.visible = false;
				this._scroll_bar.type = 1;
				this._scroll_bar.y_type = 4;
				ALittle.DisplayView.AddChild.call(this, this._scroll_bar);
				this._scroll_bar.AddEventListener(___all_struct.get(958494922), this, this.HandleRightScrollBarChange);
				this._scroll_bar.AddEventListener(___all_struct.get(1309977874), this, this.HandleRightScrollBarChangeEnd);
				this._scroll_bar.width = this._width;
				this._scroll_bar.x = 0;
				this._scroll_bar.total_size = this._scroll_linear.width;
				this._scroll_bar.show_size = this._width;
				this._scroll_bar.offset_rate = 0;
				this._scroll_bar.offset_step = 0.1;
			} else {
				this._scroll_bar.alpha = 0;
				this._scroll_bar.visible = false;
				this._scroll_bar.type = 2;
				this._scroll_bar.x_type = 4;
				ALittle.DisplayView.AddChild.call(this, this._scroll_bar);
				this._scroll_bar.AddEventListener(___all_struct.get(958494922), this, this.HandleRightScrollBarChange);
				this._scroll_bar.AddEventListener(___all_struct.get(1309977874), this, this.HandleRightScrollBarChangeEnd);
				this._scroll_bar.height = this._height;
				this._scroll_bar.y = 0;
				this._scroll_bar.total_size = this._scroll_linear.height;
				this._scroll_bar.show_size = this._height;
				this._scroll_bar.offset_rate = 0;
				this._scroll_bar.offset_step = 0.1;
			}
		}
	},
	get right_scrollbar() {
		return this._scroll_bar;
	},
	AdjustScrollBar : function() {
		if (this._type === 1) {
			let linear_width = this._scroll_linear.width;
			if (this._scroll_bar !== undefined) {
				let rate = 0.0;
				if (linear_width <= this._width) {
					rate = 0;
				} else {
					rate = -this._scroll_linear.x / (linear_width - this._width);
				}
				this._scroll_bar.width = this._width;
				this._scroll_bar.total_size = linear_width;
				this._scroll_bar.show_size = this._width;
				this._scroll_bar.offset_rate = rate;
				this._scroll_bar.offset_step = 0.1;
			}
		} else {
			let linear_height = this._scroll_linear.height;
			if (this._scroll_bar !== undefined) {
				let rate = 0.0;
				if (linear_height <= this._height) {
					rate = 0;
				} else {
					rate = -this._scroll_linear.y / (linear_height - this._height);
				}
				this._scroll_bar.height = this._height;
				this._scroll_bar.total_size = linear_height;
				this._scroll_bar.show_size = this._height;
				this._scroll_bar.offset_rate = rate;
				this._scroll_bar.offset_step = 0.1;
			}
		}
	},
	get loading_show_up() {
		return this._loading_show_up;
	},
	set loading_show_up(value) {
		if (this._loading_show_up !== value) {
			ALittle.DisplayView.RemoveChild.call(this, this._loading_show_up);
			this._loading_show_up = undefined;
		}
		if (value !== undefined) {
			this._loading_show_up = value;
			ALittle.DisplayView.AddChild.call(this, this._loading_show_up);
			if (this._type === 1) {
				this._loading_show_up.x = this._scroll_linear.x - this._loading_show_up.width;
			} else {
				this._loading_show_up.y = this._scroll_linear.y - this._loading_show_up.height;
			}
		}
	},
	get loading_show_down() {
		return this._loading_show_down;
	},
	set loading_show_down(value) {
		if (this._loading_show_down !== value) {
			ALittle.DisplayView.RemoveChild.call(this, this._loading_show_down);
			this._loading_show_down = undefined;
		}
		if (value !== undefined) {
			this._loading_show_down = value;
			ALittle.DisplayView.AddChild.call(this, this._loading_show_down);
			if (this._type === 1) {
				this._loading_show_down.x = this._scroll_linear.x + this._scroll_linear.width;
			} else {
				this._loading_show_down.y = this._scroll_linear.y + this._scroll_linear.height;
			}
		}
	},
	UpdateLoadingShow : function() {
		if (this._type === 1) {
			if (this._loading_show_up !== undefined) {
				this._loading_show_up.x = this._scroll_linear.x - this._loading_show_up.width;
			}
			if (this._loading_show_down !== undefined) {
				this._loading_show_down.x = this._scroll_linear.x + this._scroll_linear.width;
			}
		} else {
			if (this._loading_show_up !== undefined) {
				this._loading_show_up.y = this._scroll_linear.y - this._loading_show_up.height;
			}
			if (this._loading_show_down !== undefined) {
				this._loading_show_down.y = this._scroll_linear.y + this._scroll_linear.height;
			}
		}
	},
	Layout : function(index) {
		this._scroll_linear.Layout(index);
		this.RefreshClipDisLine();
	},
	DeepLayout : function() {
		this._scroll_linear.DeepLayout();
		this.RefreshClipDisLine();
	},
	HandleLinearResize : function(event) {
		this.AdjustScrollBar();
		this.RefreshClipDisLine();
	},
	HandleRightScrollBarChange : function(event) {
		if (this._type === 1) {
			let rate = this._scroll_bar.offset_rate;
			let x = 0.0;
			let linear_width = this._scroll_linear.width;
			if (linear_width > this._width) {
				let total_width = linear_width - this._width;
				x = -total_width * rate;
			}
			this._scroll_linear.x = x;
		} else {
			let rate = this._scroll_bar.offset_rate;
			let y = 0.0;
			let linear_height = this._scroll_linear.height;
			if (linear_height > this._height) {
				let total_height = linear_height - this._height;
				y = -total_height * rate;
			}
			this._scroll_linear.y = y;
		}
		this.RefreshClipDisLine();
		this.ShowRightScrollBar();
	},
	HandleRightScrollBarChangeEnd : function(event) {
		this.HideRightScrollBar();
	},
	HandleMButtonWheel : function(event) {
		if (this._scroll_bar !== undefined && event.delta_y !== 0) {
			let offset = this._scroll_linear.height * 0.1 * event.delta_y;
			if (offset > 60) {
				offset = 60;
			} else if (offset < -60) {
				offset = -60;
			}
			if (offset !== 0) {
				this._scroll_bar.offset_rate = this._scroll_bar.offset_rate - offset / this._scroll_linear.height;
			}
			this.HandleRightScrollBarChange(undefined);
			this.HideRightScrollBar();
		}
	},
	get open_extends_drag() {
		return this._open_extends_drag;
	},
	set open_extends_drag(value) {
		this._open_extends_drag = value;
	},
	HandleDragBegin : function(event) {
		this._drag_delta_table = [];
		this._drag_delta_table_count = 0;
		A_LoopSystem.RemoveUpdater(this._scroll_bar_loop);
		if (this._scroll_bar !== undefined) {
			this._scroll_bar.visible = true;
			this._scroll_bar.alpha = 1;
		}
		if (this._type === 1) {
			A_LoopSystem.RemoveUpdater(this._drag_loop_x);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
		} else {
			A_LoopSystem.RemoveUpdater(this._drag_loop_y);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
		}
	},
	HandleDrag : function(event) {
		if (this._type === 1) {
			if (this._drag_delta_table_count < 3) {
				++ this._drag_delta_table_count;
				this._drag_delta_table[this._drag_delta_table_count - 1] = event.delta_x;
			} else {
				__remove(this._drag_delta_table, 1);
				this._drag_delta_table[this._drag_delta_table_count - 1] = event.delta_x;
			}
			this._drag_time = ALittle.Time_GetCurTime();
			let linear_width = this._scroll_linear.width;
			if (event.delta_x !== 0 && this._scroll_bar !== undefined) {
				if (event.delta_x > 0) {
					let min_x = 0.0;
					let max_x = this._width * this._drag_rate;
					let x = this._scroll_linear.x;
					if (x > min_x) {
						x = x + event.delta_x * __sin((1 - x / (this._width * this._drag_rate)) * 1.57);
						if (x > max_x) {
							x = max_x;
						}
					} else {
						x = x + (event.delta_x);
					}
					if (x >= min_x && !this._open_extends_drag) {
						x = min_x;
					}
					this._scroll_linear.x = x;
					if (this._scroll_bar !== undefined) {
						this._scroll_bar.offset_rate = -x / (linear_width - this._width);
					}
				} else {
					let x = this._scroll_linear.x;
					if (linear_width < this._width) {
						x = x + (event.delta_x);
						if (x < 0) {
							x = 0;
						}
					} else {
						let max_x = -linear_width + this._width;
						let min_x = max_x - this._width * this._drag_rate;
						if (x < max_x) {
							x = x + (event.delta_x * __sin((x - min_x) / (this._width * this._drag_rate) * 1.57));
							if (x < min_x) {
								x = min_x;
							}
						} else {
							x = x + (event.delta_x);
						}
						if (x <= max_x && !this._open_extends_drag) {
							x = max_x;
						}
					}
					this._scroll_linear.x = x;
					if (this._scroll_bar !== undefined) {
						this._scroll_bar.offset_rate = -x / (linear_width - this._width);
					}
				}
				this.RefreshClipDisLine(event.delta_x);
			}
		} else {
			if (this._drag_delta_table_count < 3) {
				++ this._drag_delta_table_count;
				this._drag_delta_table[this._drag_delta_table_count - 1] = event.delta_y;
			} else {
				__remove(this._drag_delta_table, 1);
				this._drag_delta_table[this._drag_delta_table_count - 1] = event.delta_y;
			}
			this._drag_time = ALittle.Time_GetCurTime();
			let linear_height = this._scroll_linear.height;
			if (event.delta_y !== 0 && this._scroll_bar !== undefined) {
				if (event.delta_y > 0) {
					let min_y = 0.0;
					let max_y = this._height * this._drag_rate;
					let y = this._scroll_linear.y;
					if (y > min_y) {
						y = y + event.delta_y * __sin((1 - y / (this._height * this._drag_rate)) * 1.57);
						if (y > max_y) {
							y = max_y;
						}
					} else {
						y = y + (event.delta_y);
					}
					if (y >= min_y && !this._open_extends_drag) {
						y = min_y;
					}
					this._scroll_linear.y = y;
					if (this._scroll_bar !== undefined) {
						this._scroll_bar.offset_rate = -y / (linear_height - this._height);
					}
				} else {
					let y = this._scroll_linear.y;
					if (linear_height < this._height) {
						y = y + (event.delta_y);
						if (y < 0) {
							y = 0;
						}
					} else {
						let max_y = -linear_height + this._height;
						let min_y = max_y - this._height * this._drag_rate;
						if (y < max_y) {
							y = y + (event.delta_y * __sin((y - min_y) / (this._height * this._drag_rate) * 1.57));
							if (y < min_y) {
								y = min_y;
							}
						} else {
							y = y + (event.delta_y);
						}
						if (y <= max_y && !this._open_extends_drag) {
							y = max_y;
						}
					}
					this._scroll_linear.y = y;
					if (this._scroll_bar !== undefined) {
						this._scroll_bar.offset_rate = -y / (linear_height - this._height);
					}
				}
				this.RefreshClipDisLine(event.delta_y);
			}
		}
	},
	HandleDragEnd : function(event) {
		if (this._type === 1) {
			let linear_width = this._scroll_linear.width;
			if (this._scroll_linear.x > 0) {
				A_LoopSystem.RemoveUpdater(this._drag_loop_x);
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", 0, 200, 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_x);
				this.HideRightScrollBar();
				if (this._scroll_linear.x >= this._width * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(1848466169), {});
				}
			} else if (this._scroll_linear.x < -linear_width + this._width) {
				if (this._scroll_linear.x < 0) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_x);
					this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", -linear_width + this._width, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_x);
					this.HideRightScrollBar();
				}
				if (this._scroll_linear.x <= -linear_width + this._width - this._width * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(809518110), {});
				}
			} else if (this._scroll_linear.x !== 0 && this._scroll_linear.x !== -linear_width + this._width) {
				let count = this._drag_delta_table_count;
				let drag_delta_x = 0.0;
				let drag_end_time = ALittle.Time_GetCurTime() - this._drag_time;
				if (drag_end_time < 50) {
					if (count === 1 || count === 2) {
						drag_delta_x = this._drag_delta_table[1 - 1];
					} else if (count === 3) {
						drag_delta_x = __floor((this._drag_delta_table[count - 1 - 1] + this._drag_delta_table[count - 2 - 1]) / 2);
					} else {
						drag_delta_x = 0;
					}
				} else {
					if (count !== 0) {
						drag_delta_x = this._drag_delta_table[count - 1];
					} else {
						drag_delta_x = 0;
					}
				}
				if (drag_delta_x < 0 && drag_delta_x < -this._max_speed) {
					drag_delta_x = -this._max_speed;
				} else if (drag_delta_x > 0 && drag_delta_x > this._max_speed) {
					drag_delta_x = this._max_speed;
				}
				this._drag_delta_x = drag_delta_x;
				A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
				this._drag_delta_loop_x = ALittle.NewObject(ALittle.LoopFunction, this.RefreshLinearX.bind(this), -1, 1, 0);
				A_LoopSystem.AddUpdater(this._drag_delta_loop_x);
			}
		} else {
			let linear_height = this._scroll_linear.height;
			if (this._scroll_linear.y > 0) {
				A_LoopSystem.RemoveUpdater(this._drag_loop_y);
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", 0, 200, 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_y);
				this.HideRightScrollBar();
				if (this._scroll_linear.y >= this._height * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(1848466169), {});
				}
			} else if (this._scroll_linear.y < -linear_height + this._height) {
				if (this._scroll_linear.y < 0) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_y);
					this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", -linear_height + this._height, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_y);
					this.HideRightScrollBar();
				}
				if (this._scroll_linear.y <= -linear_height + this._height - this._height * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(809518110), {});
				}
			} else if (this._scroll_linear.y !== 0 && this._scroll_linear.y !== -linear_height + this._height) {
				let count = this._drag_delta_table_count;
				let drag_delta_y = 0.0;
				let drag_end_time = ALittle.Time_GetCurTime() - this._drag_time;
				if (drag_end_time < 50) {
					if (count === 1 || count === 2) {
						drag_delta_y = this._drag_delta_table[1 - 1];
					} else if (count === 3) {
						drag_delta_y = __floor((this._drag_delta_table[count - 1 - 1] + this._drag_delta_table[count - 2 - 1]) / 2);
					} else {
						drag_delta_y = 0;
					}
				} else {
					if (count !== 0) {
						drag_delta_y = this._drag_delta_table[count - 1];
					} else {
						drag_delta_y = 0;
					}
				}
				if (drag_delta_y < 0 && drag_delta_y < -this._max_speed) {
					drag_delta_y = -this._max_speed;
				} else if (drag_delta_y > 0 && drag_delta_y > this._max_speed) {
					drag_delta_y = this._max_speed;
				}
				this._drag_delta_y = drag_delta_y;
				A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
				this._drag_delta_loop_y = ALittle.NewObject(ALittle.LoopFunction, this.RefreshLinearY.bind(this), -1, 1, 0);
				A_LoopSystem.AddUpdater(this._drag_delta_loop_y);
			}
		}
	},
	RefreshLinearX : function() {
		this._scroll_linear.x = this._scroll_linear.x + this._drag_delta_x;
		let linear_width = this._scroll_linear.width;
		let loop_end = false;
		if (this._drag_delta_x !== 0 && this._scroll_bar !== undefined) {
			if (this._drag_delta_x > 0) {
				let min_x = 0.0;
				let max_x = this._width * this._drag_rate;
				let x = this._scroll_linear.x;
				if (x > min_x) {
					x = x + this._drag_delta_x * __sin((1 - x / (this._width * this._drag_rate)) * 1.57);
					if (x > max_x) {
						x = max_x;
						loop_end = true;
					}
				} else {
					x = x + (this._drag_delta_x);
				}
				if (x >= min_x && !this._open_extends_drag) {
					x = min_x;
				}
				this._scroll_linear.x = x;
				if (this._scroll_bar !== undefined) {
					this._scroll_bar.offset_rate = -x / (linear_width - this._width);
				}
			} else {
				let x = this._scroll_linear.x;
				if (linear_width < this._width) {
					x = x + (this._drag_delta_x);
					if (x < 0) {
						x = 0;
					}
				} else {
					let max_x = -linear_width + this._width;
					let min_x = max_x - this._width * this._drag_rate;
					if (x < max_x) {
						x = x + (this._drag_delta_x * __sin((x - min_x) / (this._width * this._drag_rate) * 1.57));
						if (x < min_x) {
							x = min_x;
							loop_end = true;
						}
					} else {
						x = x + (this._drag_delta_x);
					}
					if (x <= max_x && !this._open_extends_drag) {
						x = max_x;
					}
				}
				this._scroll_linear.x = x;
				if (this._scroll_bar !== undefined) {
					this._scroll_bar.offset_rate = -x / (linear_width - this._width);
				}
			}
			this.RefreshClipDisLine();
		}
		if (this._drag_delta_x < 0) {
			this._drag_delta_x = this._drag_delta_x + 1;
			if (this._drag_delta_x >= 0) {
				loop_end = true;
			}
		} else if (this._drag_delta_x > 0) {
			this._drag_delta_x = this._drag_delta_x - 1;
			if (this._drag_delta_x <= 0) {
				loop_end = true;
			}
		} else {
			loop_end = true;
		}
		if (loop_end) {
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
			if (this._scroll_linear.x > 0) {
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				A_LoopSystem.RemoveUpdater(this._drag_loop_x);
				this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", 0, 200, 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_x);
				if (this._scroll_linear.x >= this._width * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(1848466169), {});
				}
			} else if (this._scroll_linear.x < -linear_width + this._width) {
				if (this._scroll_linear.x < 0) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_x);
					this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", -linear_width + this._width, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_x);
				}
				if (this._scroll_linear.x <= -linear_width + this._width - this._width * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(809518110), {});
				}
			}
			this.HideRightScrollBar();
		}
	},
	RefreshLinearY : function() {
		this._scroll_linear.y = this._scroll_linear.y + this._drag_delta_y;
		let linear_height = this._scroll_linear.height;
		let loop_end = false;
		if (this._drag_delta_y !== 0 && this._scroll_bar !== undefined) {
			if (this._drag_delta_y > 0) {
				let min_y = 0.0;
				let max_y = this._height * this._drag_rate;
				let y = this._scroll_linear.y;
				if (y > min_y) {
					y = y + (this._drag_delta_y * __sin((1 - y / (this._height * this._drag_rate)) * 1.57));
					if (y > max_y) {
						y = max_y;
						loop_end = true;
					}
				} else {
					y = y + (this._drag_delta_y);
				}
				if (y >= min_y && !this._open_extends_drag) {
					y = min_y;
				}
				this._scroll_linear.y = y;
				if (this._scroll_bar !== undefined) {
					this._scroll_bar.offset_rate = -y / (linear_height - this._height);
				}
			} else {
				let y = this._scroll_linear.y;
				if (linear_height < this._height) {
					y = y + (this._drag_delta_y);
					if (y < 0) {
						y = 0;
					}
				} else {
					let max_y = -linear_height + this._height;
					let min_y = max_y - this._height * this._drag_rate;
					if (y < max_y) {
						y = y + (this._drag_delta_y * __sin((y - min_y) / (this._height * this._drag_rate) * 1.57));
						if (y < min_y) {
							y = min_y;
							loop_end = true;
						}
					} else {
						y = y + (this._drag_delta_y);
					}
					if (y <= max_y && !this._open_extends_drag) {
						y = max_y;
					}
				}
				this._scroll_linear.y = y;
				if (this._scroll_bar !== undefined) {
					this._scroll_bar.offset_rate = -y / (linear_height - this._height);
				}
			}
			this.RefreshClipDisLine();
		}
		if (this._drag_delta_y < 0) {
			this._drag_delta_y = this._drag_delta_y + 1;
			if (this._drag_delta_y >= 0) {
				loop_end = true;
			}
		} else if (this._drag_delta_y > 0) {
			this._drag_delta_y = this._drag_delta_y - 1;
			if (this._drag_delta_y <= 0) {
				loop_end = true;
			}
		} else {
			loop_end = true;
		}
		if (loop_end) {
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
			if (this._scroll_linear.y > 0) {
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				A_LoopSystem.RemoveUpdater(this._drag_loop_y);
				this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", 0, 200, 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_y);
				if (this._scroll_linear.y >= this._height * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(1848466169), {});
				}
			} else if (this._scroll_linear.y < -linear_height + this._height) {
				if (this._scroll_linear.y < 0) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_y);
					this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", -linear_height + this._height, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_y);
				}
				if (this._scroll_linear.y <= -linear_height + this._height - this._height * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(809518110), {});
				}
			}
			this.HideRightScrollBar();
		}
	},
	YScrollBarChange : function() {
		this._scroll_bar.offset_rate = -this._scroll_linear.y / (this._linear_height - this._height);
	},
	XScrollBarChange : function() {
		this._scroll_bar.offset_rate = -this._scroll_linear.x / (this._linear_width - this._width);
	},
	RefreshClipDisLineImpl : function(v_move) {
		this._scroll_linear.ClipRect(0, 0, this.width, this.height, undefined, v_move);
		this._clip_loop = undefined;
	},
	RefreshClipDisLine : function(v_move) {
		this.UpdateLoadingShow();
		if (this._clip_atonce) {
			this._scroll_linear.ClipRect(0, 0, this.width, this.height, undefined, undefined);
			return;
		}
		if (this._clip_loop !== undefined && this._clip_loop._user_data === undefined) {
			return;
		}
		this._clip_loop = ALittle.NewObject(ALittle.LoopFunction, this.RefreshClipDisLineImpl.bind(this, v_move), 1, 0, 1);
		this._clip_loop._user_data = v_move;
		A_LoopSystem.AddUpdater(this._clip_loop);
	},
	HideRightScrollBar : function() {
		if (this._scroll_bar !== undefined) {
			this._scroll_bar_loop = ALittle.NewObject(ALittle.LoopList);
			this._scroll_bar_loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._scroll_bar, "alpha", 0, 2000, 1000));
			this._scroll_bar_loop.AddUpdater(ALittle.NewObject(ALittle.LoopAttribute, this._scroll_bar, "visible", false, 1));
			A_LoopSystem.AddUpdater(this._scroll_bar_loop);
		}
	},
	ShowRightScrollBar : function() {
		if (this._scroll_bar_loop !== undefined) {
			A_LoopSystem.RemoveUpdater(this._scroll_bar_loop);
			this._scroll_bar_loop = undefined;
			if (this._scroll_bar !== undefined) {
				this._scroll_bar.visible = true;
				this._scroll_bar.alpha = 1;
			}
		}
	},
}, "ALittle.ScrollList");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-2129379001, "ALittle.ScrollButtonDragBeginEvent", {
name : "ALittle.ScrollButtonDragBeginEvent", ns_name : "ALittle", rl_name : "ScrollButtonDragBeginEvent", hash_code : -2129379001,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(2101017097, "ALittle.ScrollButtonDragEndEvent", {
name : "ALittle.ScrollButtonDragEndEvent", ns_name : "ALittle", rl_name : "ScrollButtonDragEndEvent", hash_code : 2101017097,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(-646882501, "ALittle.ScrollButtonDragEvent", {
name : "ALittle.ScrollButtonDragEvent", ns_name : "ALittle", rl_name : "ScrollButtonDragEvent", hash_code : -646882501,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})

let __abs = ALittle.Math_Abs;
if (ALittle.TextButton === undefined) throw new Error(" extends class:ALittle.TextButton is undefined");
ALittle.ScrollButton = JavaScript.Class(ALittle.TextButton, {
	Ctor : function(ctrl_sys) {
		this.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		this.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this.AddEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
		this._button_down = false;
		this._drag_begin_x = 0;
		this._drag_begin_y = 0;
		this._btn_drag = false;
		this._can_drag_trans = true;
		this._can_set_drag_trans = true;
	},
	set can_drag_trans(value) {
		if (this._can_set_drag_trans === false) {
			return;
		}
		this._can_drag_trans = value;
	},
	get can_drag_trans() {
		return this._can_drag_trans;
	},
	HandleDragBegin : function(event) {
		this._drag_begin_x = event.abs_x;
		this._drag_begin_y = event.abs_y;
	},
	HandleDrag : function(event) {
		if (this._btn_drag === false) {
			if (__abs(event.abs_x - this._drag_begin_x) > 2 || __abs(event.abs_y - this._drag_begin_y) > 2) {
				this._button_down = false;
				this.ShowUp(undefined);
				let e = {};
				e.target = this;
				e.delta_x = event.delta_x;
				e.delta_y = event.delta_y;
				e.abs_x = event.abs_x;
				e.abs_y = event.abs_y;
				this.DispatchEvent(___all_struct.get(-2129379001), e);
				this._can_set_drag_trans = false;
				if (this._can_drag_trans && this._trans_target.get("drag") !== undefined) {
					let ue = {};
					ue.target = this._trans_target.get("drag");
					ue.delta_x = event.delta_x;
					ue.delta_y = event.delta_y;
					ue.abs_x = event.abs_x;
					ue.abs_y = event.abs_y;
					this._trans_target.get("drag").DispatchEvent(___all_struct.get(-2129379001), e);
				}
				this._btn_drag = true;
			}
		} else if (this._btn_drag === true) {
			let e = {};
			e.target = this;
			e.delta_x = event.delta_x;
			e.delta_y = event.delta_y;
			e.abs_x = event.abs_x;
			e.abs_y = event.abs_y;
			this.DispatchEvent(___all_struct.get(-646882501), e);
			if (this._can_drag_trans && this._trans_target.get("drag") !== undefined) {
				let ue = {};
				ue.target = this._trans_target.get("drag");
				ue.delta_x = event.delta_x;
				ue.delta_y = event.delta_y;
				ue.abs_x = event.abs_x;
				ue.abs_y = event.abs_y;
				this.DispatchEvent(___all_struct.get(-646882501), e);
			}
		}
	},
	HandleDragEnd : function(event) {
		if (this._btn_drag) {
			if (this._can_drag_trans && this._trans_target.get("drag") !== undefined) {
				let e = {};
				e.target = this._trans_target.get("drag");
				e.delta_x = event.delta_x;
				e.delta_y = event.delta_y;
				e.abs_x = event.abs_x;
				e.abs_y = event.abs_y;
				this._trans_target.get("drag").DispatchEvent(___all_struct.get(150587926), e);
			}
			this._can_set_drag_trans = true;
			let e = {};
			e.target = this;
			e.delta_x = event.delta_x;
			e.delta_y = event.delta_y;
			e.abs_x = event.abs_x;
			e.abs_y = event.abs_y;
			this.DispatchEvent(___all_struct.get(2101017097), e);
		}
	},
	HandleLButtonDown : function(event) {
		this._drag_begin_x = 0;
		this._drag_begin_y = 0;
		this._btn_drag = false;
		this._button_down = true;
		this._button_down_loop = ALittle.NewObject(ALittle.LoopFunction, this.HandleLButtonDownFunc.bind(this, undefined), 1, 0, 100);
		A_LoopSystem.AddUpdater(this._button_down_loop);
	},
	HandleLButtonUp : function(event) {
		if (this._btn_drag) {
			return;
		}
		if (this._button_down === false) {
			this.HandleLButtonUpFunc(event);
		} else {
			this.ShowDown();
			this._button_up_loop = ALittle.NewObject(ALittle.LoopFunction, this.HandleLButtonUpFunc.bind(this, event), 1, 0, 60);
			this._button_up_loop.Start();
		}
	},
	DispatchEvent : function(T, event) {
		let rflt = T;
		let event_target = this;
		if (this._trans_target.get("event") !== undefined) {
			event_target = this._trans_target.get("event");
		}
		if (event_target._abs_disabled) {
			return;
		}
		if (event_target._abs_disabled) {
			return;
		}
		let callback_table = event_target._listeners[rflt.name];
		if (callback_table === undefined) {
			return;
		}
		for (let [object, callback_value] of callback_table) {
			if (callback_value === undefined) continue;
			for (let [func, _] of callback_value) {
				if (_ === undefined) continue;
				func(object, event);
			}
		}
	},
	HandleLButtonDownFunc : function(event) {
		if (this._button_down === true) {
			this.ShowDown();
			this._button_down = false;
		}
		A_LoopSystem.RemoveUpdater(this._button_down_loop);
	},
	HandleLButtonUpFunc : function(event) {
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
		A_LoopSystem.RemoveUpdater(this._button_up_loop);
	},
}, "ALittle.ScrollButton");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.SpringTextButton = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._show_text = ({});
		this._show_text.width = 0;
		this._show_text.height = 0;
		this._show_text.text = "";
		this._show_text.visible = true;
		this._show_disabled_text = ({});
		this._show_disabled_text.width = 0;
		this._show_disabled_text.height = 0;
		this._show_disabled_text.text = "";
		this._show_disabled_text.visible = false;
		this._big_or_small = false;
		this._file_select = false;
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
			if (this._file_select) {
				A_OtherSystem.SystemSelectFile(this);
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
		this._show_disabled_text.text = value;
	},
	get text() {
		return this._show_text.text;
	},
	ShowUp : function(event) {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 1;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
		this._show_text.visible = true;
		this._show_disabled_text.visible = false;
		this.ScaleTo(false, 200);
	},
	ShowDown : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 1;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
		this._show_text.visible = true;
		this._show_disabled_text.visible = false;
		this.ScaleTo(true, 200);
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
	ShowOver : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 1;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
		this._show_text.visible = true;
		this._show_disabled_text.visible = false;
		this.ScaleTo(false, 200);
	},
	ShowDisabled : function() {
		this.ScaleTo(false, 200);
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 1;
		}
		this._show_text.visible = false;
		this._show_disabled_text.visible = true;
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
			return;
		}
		value.text = this._show_text.text;
		value.visible = this._show_text.visible;
		this.RemoveChild(this._show_text);
		this._show_text = value;
		this._show_text.x_type = 3;
		this._show_text.y_type = 3;
		this.AddChild(this._show_text, 6);
	},
	get show_text() {
		if (this._show_text._show === undefined) {
			return undefined;
		}
		return this._show_text;
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
			return;
		}
		value.text = this._show_disabled_text.text;
		value.visible = this._show_disabled_text.visible;
		this.RemoveChild(this._show_disabled_text);
		this._show_disabled_text = value;
		this._show_disabled_text.x_type = 3;
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
}, "ALittle.SpringTextButton");

}
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
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.SpringDialog = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._is_show = false;
		this.visible = false;
	},
	get show() {
		return this._is_show;
	},
	set show(value) {
		if (this._is_show === value) {
			return;
		}
		this._is_show = value;
		if (this._anti_loop !== undefined) {
			this._anti_loop.SetCompleted();
			this._anti_loop.Stop();
			this._anti_loop = undefined;
		}
		if (value) {
			this.ShowAnti(1.1, 200, 200);
		} else {
			this.HideAnti(1.1, 200);
		}
	},
	ShowAnti : function(scale, scale_big_ms, scale_return_ms) {
		if (this._show_dialog === undefined) {
			return;
		}
		this.visible = true;
		this.alpha = 0;
		this._show_dialog.scale_x = 1;
		this._show_dialog.scale_y = 1;
		this._anti_loop = ALittle.NewObject(ALittle.LoopList);
		let group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_x", scale, scale_big_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_y", scale, scale_big_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "alpha", 1, scale_big_ms, 1));
		this._anti_loop.AddUpdater(group);
		group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_x", 1, scale_return_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_y", 1, scale_return_ms, 1));
		this._anti_loop.AddUpdater(group);
		this._anti_loop.Start();
	},
	HideAnti : function(scale, scale_big_ms) {
		if (this._show_dialog === undefined) {
			return;
		}
		this._anti_loop = ALittle.NewObject(ALittle.LoopList);
		let group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_x", scale, scale_big_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_y", scale, scale_big_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "alpha", 0, scale_big_ms, 1));
		this._anti_loop.AddUpdater(group);
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopAttribute, this, "visible", false, 1));
		this._anti_loop.Start();
	},
}, "ALittle.SpringDialog");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.SpringCheckButton === undefined) throw new Error(" extends class:ALittle.SpringCheckButton is undefined");
ALittle.SpringRadioButton = JavaScript.Class(ALittle.SpringCheckButton, {
	Ctor : function(ctrl_sys) {
		this._cancel_select = false;
	},
	set group(group) {
		if (this._group === group) {
			return;
		}
		if (this._group !== undefined) {
			this._group.delete(this);
		}
		this._group = group;
		if (this._group !== undefined) {
			this._group.set(this, true);
		}
	},
	get group() {
		return this._group;
	},
	SetGroup : function(list) {
		let group = ALittle.CreateKeyWeakMap();
		let ___OBJECT_1 = list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let button = ___OBJECT_1[index - 1];
			if (button === undefined) break;
			if (button._group !== undefined) {
				button._group.delete(button);
			}
			button._group = group;
			group.set(button, true);
		}
	},
	set cancel_select(value) {
		this._cancel_select = value;
	},
	get cancel_select() {
		return this._cancel_select;
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			if (this._selected === false) {
				this._selected = true;
				if (this._group !== undefined) {
					for (let [k, _] of this._group) {
						if (_ === undefined) continue;
						if (k !== this && k._selected === true) {
							k._selected = false;
							k.ShowUp();
							k.DispatchEvent(___all_struct.get(958494922), {});
						}
					}
				}
				this.DispatchEvent(___all_struct.get(958494922), {});
			} else if (this._cancel_select) {
				this._selected = false;
				this.DispatchEvent(___all_struct.get(958494922), {});
			}
			let e = {};
			e.is_drag = event.is_drag;
			e.count = event.count;
			this.DispatchEvent(___all_struct.get(-449066808), e);
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
		if (this._selected === false) {
			return;
		}
		if (this._group !== undefined) {
			for (let [k, _] of this._group) {
				if (_ === undefined) continue;
				if (k !== this && k._selected === true) {
					k._selected = false;
					k.ShowUp();
				}
			}
		}
	},
}, "ALittle.SpringRadioButton");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.DynamicImage = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._real_width = 0;
		this._real_height = 0;
		this._show = ALittle.NewObject(JavaScript.JImage);
	},
	GetSurface : function(redraw) {
		return this._texture.GetSurface(redraw);
	},
	SetRangeColor : function(buffer) {
		if (this._base_texture !== undefined) {
			let width = this._real_width;
			let height = this._real_height;
			for (let x = 0; x < width; x += 1) {
				for (let y = 0; y < height; y += 1) {
					let index = y * width + x;
					this._data[index - 1] = buffer.get(index);
				}
			}
			this._base_texture.update();
		}
	},
	SetSurfaceSize : function(width, height, color) {
		this._real_width = width;
		this._real_height = height;
		{
			if (this._texture !== undefined && (this._texture.GetWidth() !== width || this._texture.GetHeight() !== height)) {
				this._show.ClearTexture();
				this._texture = undefined;
			}
			let len = width * height;
			let buffer = new ArrayBuffer(len * 4);
			let array = new Uint32Array(buffer);
			this._data = array;
			for (let i = 0; i < len; i += 1) {
				this._data[i - 1] = color;
			}
			let res_options = {};
			res_options.width = width;
			res_options.height = height;
			let resource = new PIXI.BufferResource(new Uint8Array(buffer), res_options);
			let tex_options = {};
			tex_options.width = width;
			tex_options.height = height;
			tex_options.scaleMode = 0;
			this._base_texture = new PIXI.BaseTexture(resource, tex_options);
			let texture = new PIXI.Texture(this._base_texture);
			this._texture = ALittle.NewObject(JavaScript.JTexture, texture, width, height);
			this._show.SetTexture(this._texture);
		}
	},
	SetRenderMode : function(mode) {
		this._texture.SetRenderMode(mode);
	},
	Clear : function() {
		if (this._texture === undefined) {
			return;
		}
		this._texture.Clear();
	},
}, "ALittle.DynamicImage");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.EffectImage = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
	},
	Action : function(control) {
		if (control === undefined) {
			return;
		}
		this._show = ALittle.NewObject(lua.__CPPAPIImage);
		this._texture = ALittle.NewObject(lua.__CPPAPIRenderTexture);
		this.x = control.x;
		this.y = control.y;
		this.width = control.width;
		this.height = control.height;
		control._show.SetX(0);
		control._show.SetY(0);
		control.visible = true;
		control.clip = false;
		let result = this._texture.Draw(control._show, lua.math.floor(this.width), lua.math.floor(this.height), 1);
		control._show.SetX(this._x);
		control._show.SetY(this._y);
		if (result) {
			this._show.SetTexture(this._texture);
		}
		this._show.SetTextureCoord(0, 1, 0, 1);
		this.disabled = true;
	},
	Clear : function() {
		if (this._texture === undefined) {
			return;
		}
		this._texture.Clear();
	},
}, "ALittle.EffectImage");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(-1281734132, "ALittle.TileMap", {
name : "ALittle.TileMap", ns_name : "ALittle", rl_name : "TileMap", hash_code : -1281734132,
name_list : ["tile_type","side_len","tile_width","tile_height","tile_x","tile_y","col_count","row_count","tex_map","layer_list"],
type_list : ["int","int","int","int","int","int","int","int","Map<int,string>","List<ALittle.TileLayer>"],
option_map : {}
})
ALittle.RegStruct(-343663763, "ALittle.TileLayer", {
name : "ALittle.TileLayer", ns_name : "ALittle", rl_name : "TileLayer", hash_code : -343663763,
name_list : ["name","cell_map"],
type_list : ["string","Map<int,Map<int,ALittle.TileCell>>"],
option_map : {}
})
ALittle.RegStruct(7944876, "ALittle.TileCell", {
name : "ALittle.TileCell", ns_name : "ALittle", rl_name : "TileCell", hash_code : 7944876,
name_list : ["tex_id"],
type_list : ["int"],
option_map : {}
})

ALittle.TileType = {
	NONE : 0,
	SQUARE : 1,
	HEX_V : 2,
	HEX_H : 3,
}

let floor = ALittle.Math_Floor;
let ceil = ALittle.Math_Ceil;
if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.TileMapContainer = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._row_count = 0;
		this._col_count = 0;
		this._cell_width = 0.0;
		this._cell_height = 0.0;
		this._linear_x = 0.0;
		this._linear_y = 0.0;
		this._tile_layout = ALittle.NewObject(ALittle.TileLayoutContainer, ctrl_sys);
		this._tile_layout.width_type = 4;
		this._tile_layout.height_type = 4;
		this.AddChild(this._tile_layout);
		this._user_layout = ALittle.NewObject(ALittle.TileLayoutContainer, ctrl_sys);
		this._user_layout.width_type = 4;
		this._user_layout.height_type = 4;
		this.AddChild(this._user_layout);
	},
	ClipRect : function(x, y, width, height, h_move, v_move) {
		let ___OBJECT_1 = this.childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			child.ClipRect(x - this._x, y - this._y, width - this._x, height - this._y, h_move, v_move);
		}
	},
	Init : function(tile_map, row_count, col_count) {
		this._tile_layout.RemoveAllChild();
		this._tile_map = tile_map;
		this._row_count = row_count;
		this._col_count = col_count;
		this._image_cache = new Map();
		this._cell_width = ALittle.Tile_CalcCellWidth(tile_map);
		this._cell_height = ALittle.Tile_CalcCellHeight(tile_map);
		this._linear_x = ALittle.Tile_CalcLinear2OffsetX(tile_map);
		this._linear_y = ALittle.Tile_CalcLinear2OffsetY(tile_map);
		let grid_map_width = this._cell_width * col_count;
		let linear_1 = undefined;
		let linear_2 = undefined;
		let ___OBJECT_2 = tile_map.layer_list;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let layer = ___OBJECT_2[index - 1];
			if (layer === undefined) break;
			let group = ALittle.NewObject(ALittle.TileGroupContainer, this._ctrl_sys);
			linear_1 = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
			linear_1.type = 2;
			linear_1.width = grid_map_width;
			group.AddChild(linear_1);
			linear_2 = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
			linear_2.type = 2;
			linear_2.width = grid_map_width;
			linear_2.x = this._linear_x;
			linear_2.y = this._linear_y;
			group.AddChild(linear_2);
			this.ResizeLinear(linear_1, linear_2, index);
			this._tile_layout.AddChild(group);
		}
		let width_1 = 0.0;
		if (linear_1 !== undefined) {
			width_1 = linear_1.x + linear_1.width;
		}
		let width_2 = 0.0;
		if (linear_2 !== undefined) {
			width_2 = linear_2.x + linear_2.width;
		}
		let height_1 = 0.0;
		if (height_1 !== undefined) {
			height_1 = linear_1.y + linear_1.height;
		}
		let height_2 = 0.0;
		if (linear_2 !== undefined) {
			height_2 = linear_2.y + linear_2.height;
		}
		this.width = ALittle.Math_Max(width_1, width_2);
		this.height = ALittle.Math_Max(height_1, height_2);
	},
	get user_layout() {
		return this._user_layout;
	},
	GetImage : function(layer, row, col) {
		let layer_map = this._image_cache.get(layer);
		if (layer_map === undefined) {
			layer_map = new Map();
			this._image_cache.set(layer, layer_map);
		}
		let row_map = layer_map.get(row);
		if (row_map === undefined) {
			row_map = new Map();
			layer_map.set(row, row_map);
		}
		let image = row_map.get(col);
		if (image !== undefined) {
			return image;
		}
		let group = this._tile_layout.GetChildByIndex(layer);
		if (group === undefined) {
			return undefined;
		}
		let linear_1 = group.GetChildByIndex(1);
		let linear_2 = group.GetChildByIndex(2);
		let tile_type = this._tile_map.tile_type;
		if (tile_type === 2) {
			if (row % 2 === 1) {
				image = linear_1.childs[floor(row / 2) + 1 - 1].childs[col - 1]._user_data;
				row_map.set(col, image);
				return image;
			}
			image = linear_2.childs[floor(row / 2) - 1].childs[col - 1]._user_data;
			row_map.set(col, image);
			return image;
		} else {
			if (col % 2 === 1) {
				image = linear_1.childs[row - 1].childs[floor(col / 2) + 1 - 1]._user_data;
				row_map.set(col, image);
				return image;
			}
			image = linear_2.childs[row - 1].childs[floor(col / 2) - 1]._user_data;
			row_map.set(col, image);
			return image;
		}
	},
	RefreshTexture : function(start_row, start_col) {
		let tile_map = this._tile_map;
		let row_count = this._row_count;
		let col_count = this._col_count;
		let childs = this._tile_layout._childs;
		let ___OBJECT_3 = childs;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let group = ___OBJECT_3[index - 1];
			if (group === undefined) break;
			let layer = tile_map.layer_list[index - 1];
			for (let row = 1; row <= row_count; row += 1) {
				for (let col = 1; col <= col_count; col += 1) {
					let image = this.GetImage(index, row, col);
					let cells = layer.cell_map.get(row + start_row - 1);
					if (cells === undefined) {
						image.texture_name = undefined;
					} else {
						let cell = cells.get(col + start_col - 1);
						if (cell === undefined) {
							image.texture_name = undefined;
						} else {
							image.texture_name = tile_map.tex_map.get(cell.tex_id);
						}
					}
				}
			}
		}
	},
	ResizeLinear : function(linear_1, linear_2, layer) {
		let tile_map = this._tile_map;
		let col_count = this._col_count;
		let row_count = this._row_count;
		if (tile_map.tile_type === 2) {
			linear_1.width = this._cell_width * col_count;
			linear_2.width = linear_1.width;
			for (let row = 1; row <= row_count; row += 1) {
				let linear = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
				linear.type = 1;
				linear.height = this._cell_height;
				for (let col = 1; col <= col_count; col += 1) {
					linear.AddChild(this.CreateCell());
				}
				if (row % 2 === 1) {
					linear_1.AddChild(linear);
				} else {
					linear_2.AddChild(linear);
				}
			}
		} else {
			let col_count_1 = ceil(col_count / 2);
			for (let row = 1; row <= row_count; row += 1) {
				let linear = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
				linear.type = 1;
				linear.height = this._cell_height;
				for (let col = 1; col <= col_count_1; col += 1) {
					linear.AddChild(this.CreateCell());
				}
				linear_1.AddChild(linear);
			}
			let col_count_2 = floor(col_count / 2);
			for (let row = linear_2.child_count + 1; row <= row_count; row += 1) {
				let linear = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
				linear.type = 1;
				linear.height = this._cell_height;
				for (let col = 1; col <= col_count_2; col += 1) {
					linear.AddChild(this.CreateCell());
				}
				linear_2.AddChild(linear);
			}
		}
	},
	CreateCell : function() {
		let tile_map = this._tile_map;
		let tile_type = tile_map.tile_type;
		let side_len = tile_map.side_len;
		if (tile_type === 2) {
			let cell = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
			cell.width = this._cell_width;
			let image = ALittle.NewObject(ALittle.Image, this._ctrl_sys);
			cell._user_data = image;
			image.width = tile_map.tile_width;
			image.height = tile_map.tile_height;
			image.x = tile_map.tile_x;
			image.y = tile_map.tile_y;
			cell.AddChild(image);
			return cell;
		}
		if (tile_type === 1) {
			let cell = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
			cell.width = this._cell_width;
			let image = ALittle.NewObject(ALittle.Image, this._ctrl_sys);
			cell._user_data = image;
			image.width = tile_map.tile_width;
			image.height = tile_map.tile_height;
			image.x = tile_map.tile_x;
			image.y = tile_map.tile_y;
			cell.AddChild(image);
			return cell;
		}
		if (tile_type === 3) {
			let cell = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
			cell.width = this._cell_width;
			let image = ALittle.NewObject(ALittle.Image, this._ctrl_sys);
			cell._user_data = image;
			image.width = tile_map.tile_width;
			image.height = tile_map.tile_height;
			image.x = tile_map.tile_x;
			image.y = tile_map.tile_y;
			cell.AddChild(image);
			return cell;
		}
		return undefined;
	},
}, "ALittle.TileMapContainer");

if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittle.TileGroupContainer = JavaScript.Class(ALittle.DisplayGroup, {
	ClipRect : function(x, y, width, height, h_move, v_move) {
		let ___OBJECT_4 = this.childs;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let child = ___OBJECT_4[index - 1];
			if (child === undefined) break;
			child.ClipRect(x - this._x, y - this._y, width - this._x, height - this._y, h_move, v_move);
		}
	},
}, "ALittle.TileGroupContainer");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.TileLayoutContainer = JavaScript.Class(ALittle.DisplayLayout, {
	ClipRect : function(x, y, width, height, h_move, v_move) {
		let ___OBJECT_5 = this.childs;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let child = ___OBJECT_5[index - 1];
			if (child === undefined) break;
			child.ClipRect(x - this._x, y - this._y, width - this._x, height - this._y, h_move, v_move);
		}
	},
}, "ALittle.TileLayoutContainer");

ALittle.Tile_CalcLinear2OffsetX = function(tile_map) {
	let tile_type = tile_map.tile_type;
	let side_len = tile_map.side_len;
	if (tile_type === 1) {
		return side_len;
	}
	if (tile_type === 2) {
		return side_len * 1.732 / 2;
	}
	if (tile_type === 3) {
		return side_len * 3 / 2;
	}
	return 0;
}

ALittle.Tile_CalcLinear2OffsetY = function(tile_map) {
	let tile_type = tile_map.tile_type;
	let side_len = tile_map.side_len;
	if (tile_type === 1) {
		return 0;
	}
	if (tile_type === 2) {
		return side_len * 3 / 2;
	}
	if (tile_type === 3) {
		return side_len * 1.732 / 2;
	}
	return 0;
}

ALittle.Tile_CalcRowColByPosInHexV = function(tile_map, x, y) {
	let tile_type = tile_map.tile_type;
	let side_len = tile_map.side_len;
	let half_width = side_len * 1.732 / 2;
	let split_x = floor(x / half_width);
	let offset_x = x - split_x * half_width;
	if (split_x % 2 === 0) {
		let split_y = floor(y / (side_len * 3));
		let offset_y = y - split_y * (side_len * 3);
		if (offset_y < side_len / 2) {
			let row = split_y * 2;
			let col = floor(split_x / 2);
			let test_y = -1 / 1.732 * offset_x + side_len / 2;
			if (offset_y < test_y) {
				row = row - (1);
				col = col - (1);
			}
			return [row + 1, col + 1];
		}
		if (offset_y < side_len * 3 / 2) {
			let row = split_y * 2;
			let col = floor(split_x / 2);
			return [row + 1, col + 1];
		}
		if (offset_y < side_len * 2) {
			let row = split_y * 2;
			let col = floor(split_x / 2);
			let test_y = 1 / 1.732 * offset_x;
			if (offset_y - side_len * 3 / 2 > test_y) {
				row = row + (1);
				col = col - (1);
			}
			return [row + 1, col + 1];
		}
		{
			let row = split_y * 2 + 1;
			let col = floor(split_x / 2) - 1;
			return [row + 1, col + 1];
		}
	} else {
		let split_y = floor(y / (side_len * 3));
		let offset_y = y - split_y * (side_len * 3);
		if (offset_y < side_len / 2) {
			let row = split_y * 2;
			let col = floor(split_x / 2);
			let test_y = 1 / 1.732 * offset_x;
			if (offset_y < test_y) {
				row = row - (1);
			}
			return [row + 1, col + 1];
		}
		if (offset_y < side_len * 3 / 2) {
			let row = split_y * 2;
			let col = floor(split_x / 2);
			return [row + 1, col + 1];
		}
		if (offset_y < side_len * 2) {
			let row = split_y * 2;
			let col = floor(split_x / 2);
			let test_y = -1 / 1.732 * offset_x + side_len / 2;
			if (offset_y - side_len * 3 / 2 > test_y) {
				row = row + (1);
			}
			return [row + 1, col + 1];
		}
		{
			let row = split_y * 2 + 1;
			let col = floor(split_x / 2);
			return [row + 1, col + 1];
		}
	}
}

ALittle.Tile_CalcRowColByPos = function(tile_map, x, y) {
	let tile_type = tile_map.tile_type;
	let side_len = tile_map.side_len;
	if (tile_type === 1) {
		let row = floor(y / side_len);
		let col = floor(x / side_len);
		return [row + 1, col + 1];
	}
	if (tile_type === 3) {
		let [col, row] = ALittle.Tile_CalcRowColByPosInHexV(tile_map, y, x);
		return [row, col];
	}
	if (tile_type === 2) {
		return [ALittle.Tile_CalcRowColByPosInHexV(tile_map, x, y)];
	}
	return [0, 0];
}

ALittle.Tile_CalcCellHeight = function(tile_map) {
	let tile_type = tile_map.tile_type;
	let side_len = tile_map.side_len;
	if (tile_type === 1) {
		return side_len;
	}
	if (tile_type === 2) {
		return side_len * 3;
	}
	if (tile_type === 3) {
		return side_len * 1.732;
	}
	return 0;
}

ALittle.Tile_CalcCellWidth = function(tile_map) {
	let tile_type = tile_map.tile_type;
	let side_len = tile_map.side_len;
	if (tile_type === 1) {
		return side_len * 2;
	}
	if (tile_type === 2) {
		return side_len * 1.732;
	}
	if (tile_type === 3) {
		return side_len * 3;
	}
	return 0;
}

ALittle.Tile_GetLayerByName = function(tile_map, name) {
	let ___OBJECT_6 = tile_map.layer_list;
	for (let index = 1; index <= ___OBJECT_6.length; ++index) {
		let layer = ___OBJECT_6[index - 1];
		if (layer === undefined) break;
		if (layer.name === name) {
			return index;
		}
	}
	return undefined;
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1031172931, "ALittle.FingerInfo", {
name : "ALittle.FingerInfo", ns_name : "ALittle", rl_name : "FingerInfo", hash_code : 1031172931,
name_list : ["key","mouse_x","mouse_y","last_mouse_x","last_mouse_y","dl","mfc","mfc_rel_x","mfc_rel_y","is_sfc"],
type_list : ["string","double","double","double","double","bool","ALittle.DisplayObject","double","double","bool"],
option_map : {}
})

let __abs = ALittle.Math_Abs;
ALittle.UISystem = JavaScript.Class(undefined, {
	Ctor : function() {
		this._view_width = 0;
		this._view_height = 0;
		this._mouse_x = 0;
		this._mouse_y = 0;
		this._last_mouse_x = 0;
		this._last_mouse_y = 0;
		this._lbutton_down = false;
		this._lbutton_count = 0;
		this._lbutton_finger_id = undefined;
		this._lbutton_touch_id = undefined;
		this._mfc = undefined;
		this._mfc_rel_x = 0;
		this._mfc_rel_y = 0;
		this._mfd = undefined;
		this._sfc = undefined;
		this._wfc = undefined;
		this._pfc = undefined;
		this._button_type = undefined;
		this._sl = false;
		this._dl = false;
		this._dl_delta_x = 0;
		this._dl_delta_y = 0;
		this._max_dl_delta = 10;
		this._max_lp_delta = 2;
		if (ALittle.System_GetPlatform() === "Windows") {
			this._max_dl_delta = 1;
			this._max_lp_delta = 0;
		}
		this._ime_editing = false;
		this._ime_editing_callback = undefined;
		this._sym_map = new Map();
		this._keydown_callback = undefined;
		this._keyup_callback = undefined;
		this._view_resize_callback = undefined;
		this._long_press = undefined;
		this._finger_info = {};
	},
	set view_resize_callback(value) {
		this._view_resize_callback = value;
	},
	get view_resize_callback() {
		return this._view_resize_callback;
	},
	set keydown_callback(value) {
		this._keydown_callback = value;
	},
	get keydown_callback() {
		return this._keydown_callback;
	},
	set keyup_callback(value) {
		this._keyup_callback = value;
	},
	get keyup_callback() {
		return this._keyup_callback;
	},
	set quit_callback(value) {
		this._quit_callback = value;
	},
	get quit_callback() {
		return this._quit_callback;
	},
	get sym_map() {
		return this._sym_map;
	},
	set ime_callback(value) {
		this._ime_editing_callback = value;
	},
	get ime_callback() {
		return this._ime_editing_callback;
	},
	get mouse_x() {
		return this._mouse_x;
	},
	get mouse_y() {
		return this._mouse_y;
	},
	set focus(control) {
		if (this._sfc === control) {
			return;
		}
		this._wfc = undefined;
		if (this._sfc !== undefined) {
			if (this._dl === true) {
				this._dl = false;
				this._dl_delta_x = 0;
				this._dl_delta_y = 0;
				if (this._button_type === "ALittle.UILButtonDownEvent") {
					let event = {};
					event.target = this._sfc;
					event.rel_x = this._mfc_rel_x;
					event.rel_y = this._mfc_rel_y;
					if (this._mfc !== this._sfc) {
						[event.rel_x, event.rel_y] = this._sfc.GlobalToLocalMatrix2D(this._mouse_x, this._mouse_y);
					}
					event.delta_x = this._mouse_x - this._last_mouse_x;
					event.delta_y = this._mouse_y - this._last_mouse_y;
					event.abs_x = this._mouse_x;
					event.abs_y = this._mouse_y;
					this._sfc.DispatchEvent(___all_struct.get(150587926), event);
				}
			}
			let sfc = this._sfc;
			if (this._ime_editing_callback !== undefined) {
				this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
			}
			this._sfc = undefined;
			this._sl = false;
			sfc.DispatchEvent(___all_struct.get(292776509), {});
		}
		this._sfc = control;
		if (this._sfc !== undefined) {
			this._sfc.DispatchEvent(___all_struct.get(-644464135), {});
		}
	},
	get focus() {
		return this._sfc;
	},
	set pick(control) {
		if (this._pfc !== undefined) {
			A_LayerManager.RemoveFromTip(this._pfc);
		}
		this._pfc = control;
		if (this._pfc !== undefined) {
			A_LayerManager.AddToTip(this._pfc);
		}
	},
	get pick() {
		return this._pfc;
	},
	get view_width() {
		return this._view_width;
	},
	get view_height() {
		return this._view_height;
	},
	HandleMouseMoved : function(x, y) {
		let delta_x = x - this._mouse_x;
		let delta_y = y - this._mouse_y;
		this._last_mouse_x = this._mouse_x;
		this._last_mouse_y = this._mouse_y;
		this._mouse_x = x;
		this._mouse_y = y;
		if (this._long_press !== undefined && __abs(delta_x) <= this._max_lp_delta && __abs(delta_y) <= this._max_lp_delta) {
			return false;
		}
		if (this._long_press !== undefined) {
			this._long_press.Stop();
			this._long_press = undefined;
		}
		if (this._pfc !== undefined) {
			this._pfc.x = this._pfc.x + (delta_x);
			this._pfc.y = this._pfc.y + (delta_y);
		}
		if (this._sl && this._button_type === "ALittle.UILButtonDownEvent") {
			if (this._dl === true) {
				let event = {};
				event.target = this._sfc;
				[event.rel_x, event.rel_y] = this._sfc.GlobalToLocalMatrix2D(x, y);
				if (this._dl_delta_x > 0) {
					delta_x = this._dl_delta_x + delta_x;
					this._dl_delta_x = 0;
				}
				if (this._dl_delta_y > 0) {
					delta_y = this._dl_delta_y + delta_y;
					this._dl_delta_y = 0;
				}
				event.abs_x = x;
				event.abs_y = y;
				event.delta_x = delta_x;
				event.delta_y = delta_y;
				this._sfc.DispatchEvent(___all_struct.get(1337289812), event);
				return true;
			}
			if (this._dl === false) {
				this._dl_delta_x = this._dl_delta_x + (delta_x);
				this._dl_delta_y = this._dl_delta_y + (delta_y);
				if (__abs(this._dl_delta_x) >= this._max_dl_delta || __abs(this._dl_delta_y) >= this._max_dl_delta) {
					this._dl = true;
					let event = {};
					event.target = this._sfc;
					let mouse_x = x - delta_x;
					let mouse_y = y - delta_y;
					[event.rel_x, event.rel_y] = this._sfc.GlobalToLocalMatrix2D(mouse_x, mouse_y);
					event.abs_x = mouse_x;
					event.abs_y = mouse_y;
					event.delta_x = 0;
					event.delta_y = 0;
					this._sfc.DispatchEvent(___all_struct.get(1301789264), event);
				}
			}
			return true;
		}
		this.UpdateMoveFocus(x, y);
		return this._mfc !== undefined;
	},
	HandleLButtonDown : function(x, y, count) {
		this._lbutton_down = true;
		this._lbutton_count = count;
		this._lbutton_finger_id = undefined;
		this._lbutton_touch_id = undefined;
		return this.HandleButtonDown(___all_struct.get(1883782801), x, y, count);
	},
	HandleLButtonUp : function(x, y) {
		this._lbutton_down = false;
		return this.HandleButtonUp(___all_struct.get(40651933), x, y, this._lbutton_count);
	},
	HandleMButtonDown : function(x, y, count) {
		return this.HandleButtonDown(___all_struct.get(349963892), x, y, count);
	},
	HandleMButtonUp : function(x, y) {
		return this.HandleButtonUp(___all_struct.get(683647260), x, y, 1);
	},
	HandleButtonDown : function(T, x, y, count) {
		let rflt = T;
		this._wfc = undefined;
		A_LayerManager.HandleLRButtonDown(x, y);
		this.UpdateMoveFocus(x, y);
		if (this._mfc !== undefined) {
			this._sl = true;
			this._button_type = rflt.name;
			if (this._pfc !== undefined && rflt.name === "ALittle.UILButtonDownEvent") {
				let event = {};
				event.target = this._mfc;
				event.drop_target = this._pfc;
				this._mfc.DispatchEvent(___all_struct.get(1354499457), event);
				A_LayerManager.RemoveFromTip(this._pfc);
				this._pfc = undefined;
			}
			if (this._mfd !== undefined) {
				let layer = this._mfd.show_parent;
				layer.SetChildIndex(this._mfd, layer.child_count);
			}
			let event = {};
			event.target = this._mfc;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = this._mfc_rel_x;
			event.rel_y = this._mfc_rel_y;
			event.count = count;
			event.is_drag = false;
			this._mfc.DispatchEvent(T, event);
			if (rflt.name === "ALittle.UILButtonDownEvent") {
				if (this._long_press !== undefined) {
					this._long_press.Stop();
				}
				let long_event = {};
				long_event.target = this._mfc;
				long_event.abs_x = x;
				long_event.abs_y = y;
				long_event.rel_x = this._mfc_rel_x;
				long_event.rel_y = this._mfc_rel_y;
				long_event.is_drag = false;
				this._long_press = ALittle.NewObject(ALittle.LoopFunction, ALittle.UISystem.DispatchLongButtonEvent.bind(undefined, this._mfc, long_event), 1, 500, 1);
				this._long_press.Start();
			}
			if (this._sfc === undefined) {
				this._sfc = this._mfc;
				this._sfc.DispatchEvent(___all_struct.get(-644464135), {});
			} else if (this._mfc !== this._sfc) {
				this._sfc.DispatchEvent(___all_struct.get(292776509), {});
				if (this._ime_editing_callback !== undefined) {
					this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
				}
				this._sfc = this._mfc;
				this._sfc.DispatchEvent(___all_struct.get(-644464135), {});
			}
			return true;
		} else {
			if (this._sfc !== undefined) {
				this._sfc.DispatchEvent(___all_struct.get(292776509), {});
				if (this._ime_editing_callback !== undefined) {
					this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
				}
				this._sfc = undefined;
				this._sl = false;
			}
		}
		return false;
	},
	DispatchLongButtonEvent : function(mfc, event) {
		mfc.DispatchEvent(___all_struct.get(-439548260), event);
	},
	HandleButtonUp : function(T, x, y, count) {
		if (this._sl === false) {
			return false;
		}
		if (this._long_press !== undefined) {
			this._long_press.Stop();
			this._long_press = undefined;
		}
		this._sl = false;
		let [rel_x, rel_y] = this._sfc.GlobalToLocalMatrix2D(x, y);
		let save_dl = this._dl;
		if (this._dl === true) {
			this._dl = false;
			this._dl_delta_x = 0;
			this._dl_delta_y = 0;
			let event = {};
			event.target = this._sfc;
			event.abs_x = x;
			event.abs_y = y;
			event.delta_x = this._mouse_x - this._last_mouse_x;
			event.delta_y = this._mouse_y - this._last_mouse_y;
			event.rel_x = rel_x;
			event.rel_y = rel_y;
			this._sfc.DispatchEvent(___all_struct.get(150587926), event);
		}
		if (this._sfc !== undefined) {
			let event = {};
			event.target = this._sfc;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = rel_x;
			event.rel_y = rel_y;
			event.is_drag = save_dl;
			event.count = count;
			this._sfc.DispatchEvent(T, event);
		}
		this.UpdateMoveFocus(x, y);
		return this._mfc !== undefined;
	},
	HandleRButtonDown : function(x, y, count) {
		A_LayerManager.HandleLRButtonDown(x, y);
		if (this._sl) {
			return false;
		}
		this.UpdateMoveFocus(x, y);
		if (this._mfc !== undefined) {
			let event = {};
			event.target = this._mfc;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = this._mfc_rel_x;
			event.rel_y = this._mfc_rel_y;
			event.count = count;
			event.is_drag = false;
			this._mfc.DispatchEvent(___all_struct.get(-641444818), event);
			return true;
		}
		return false;
	},
	HandleRButtonUp : function(x, y) {
		return false;
	},
	HandleTextInput : function(text) {
		this._ime_editing = false;
		if (this._ime_editing_callback !== undefined) {
			this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
		}
		if (this._sfc !== undefined) {
			let event = {};
			event.target = this._sfc;
			event.text = text;
			this._sfc.DispatchEvent(___all_struct.get(-1234078962), event);
			return true;
		}
		return false;
	},
	HandleTextEditing : function(text, start) {
		if (text === "") {
			if (this._ime_editing === false) {
				return;
			}
			this._ime_editing = false;
			if (this._ime_editing_callback !== undefined) {
				this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
			}
		} else {
			this._ime_editing = true;
			if (this._sfc === undefined || this._sfc.is_input === false || this._sfc.editable === false || this._sfc.font_size === undefined) {
				return;
			}
			if (this._ime_editing_callback !== undefined) {
				let list = ALittle.String_Split(ALittle.System_GetIMESelectList(), " ");
				let new_list = [];
				let count = 0;
				let ___OBJECT_1 = list;
				for (let index = 1; index <= ___OBJECT_1.length; ++index) {
					let value = ___OBJECT_1[index - 1];
					if (value === undefined) break;
					if (value !== "") {
						++ count;
						new_list[count - 1] = value;
					}
				}
				this._ime_editing_callback(true, text, start, new_list, this._sfc);
				ALittle.System_SetIMEPos(ALittle.System_GetScreenWidth(), ALittle.System_GetScreenHeight());
			} else {
				let [abs_x, abs_y] = this._sfc.LocalToGlobal();
				abs_x = abs_x + (this._sfc.cursor_x);
				abs_y = abs_y + ((this._sfc.cursor_y + this._sfc.font_size) * this._sfc.scale_y);
				ALittle.System_SetIMEPos(ALittle.Math_Floor(abs_x), ALittle.Math_Floor(abs_y));
			}
		}
	},
	HandleKeyDown : function(mod, sym, scancode) {
		this._sym_map.set(sym, true);
		if (ALittle.System_GetIMESelectList() === "" && this._ime_editing) {
			this._ime_editing = false;
			if (this._ime_editing_callback !== undefined) {
				this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
			}
			return;
		}
		let event = {};
		event.target = this._sfc;
		event.mod = mod;
		event.sym = sym;
		event.scancode = scancode;
		if (this._sfc !== undefined && this._ime_editing === false) {
			this._sfc.DispatchEvent(___all_struct.get(-1604617962), event);
		}
		if (!event.handled && this._ime_editing === false && this._keydown_callback !== undefined) {
			this._keydown_callback(mod, sym, scancode);
		}
	},
	HandleKeyUp : function(mod, sym, scancode) {
		this._sym_map.delete(sym);
		let event = {};
		event.target = this._sfc;
		event.mod = mod;
		event.sym = sym;
		event.scancode = scancode;
		if (this._sfc !== undefined && this._ime_editing === false) {
			this._sfc.DispatchEvent(___all_struct.get(1213009422), event);
		}
		if (this._ime_editing === false && this._keyup_callback !== undefined) {
			this._keyup_callback(mod, sym, scancode);
		}
	},
	HandleMouseWheel : function(x, y) {
		if (this._mfc === undefined) {
			return false;
		}
		if (this._wfc === undefined) {
			let control = this._mfc;
			while (control !== undefined) {
				if (control.can_scroll === true) {
					this._wfc = control;
					break;
				}
				control = control.show_parent;
			}
		}
		if (this._wfc !== undefined) {
			let event = {};
			event.target = this._wfc;
			event.delta_x = x;
			event.delta_y = y;
			this._wfc.DispatchEvent(___all_struct.get(-1737121315), event);
		}
		return true;
	},
	UpdateMoveFocus : function(x, y) {
		let mfc = undefined;
		let mfd = undefined;
		[mfc, mfd, this._mfc_rel_x, this._mfc_rel_y] = A_LayerManager.PickUp(x, y);
		this._mfd = mfd;
		if (this._mfc === mfc) {
			if (mfc !== undefined) {
				let event = {};
				event.target = mfc;
				event.abs_x = x;
				event.abs_y = y;
				event.rel_x = this._mfc_rel_x;
				event.rel_y = this._mfc_rel_y;
				mfc.DispatchEvent(___all_struct.get(-1001723540), event);
			}
			return;
		}
		if (this._mfc !== undefined) {
			this._mfc.DispatchEvent(___all_struct.get(-1202439334), {});
		}
		if (mfc !== undefined) {
			mfc.DispatchEvent(___all_struct.get(544684311), {});
		}
		this._mfc = mfc;
		this._wfc = undefined;
	},
	HandleViewResized : function(width, height) {
		if (this._view_width === width && this._view_height === height) {
			return;
		}
		this._view_width = width;
		this._view_height = height;
		A_LayerManager.HandleViewResized(width, height);
		if (this._view_resize_callback !== undefined) {
			this._view_resize_callback(width, height);
		}
	},
	HandleDropFile : function(path) {
		let x = ALittle.System_GetCursorX();
		let y = ALittle.System_GetCursorY();
		this.HandleMouseMoved(x, y);
		if (this._mfc === undefined) {
			return;
		}
		let event = {};
		event.target = this._mfc;
		event.path = path;
		this._mfc.DispatchEvent(___all_struct.get(-338112738), event);
	},
	HandleWindowEnter : function() {
	},
	HandleWindowLeave : function() {
		if (this._lbutton_down) {
			this.HandleLButtonUp(this._mouse_x, this._mouse_y);
		}
	},
	HandleQuit : function() {
		if (this._quit_callback !== undefined && !this._quit_callback()) {
			return;
		}
		ALittle.System_Exit();
	},
	HandleFingerDown : function(x, y, finger_id, touch_id) {
		if (this._lbutton_down === false) {
			this._lbutton_down = true;
			this._lbutton_count = 1;
			this._lbutton_finger_id = finger_id;
			this._lbutton_touch_id = touch_id;
			this._mouse_x = x;
			this._mouse_y = y;
			return this.HandleButtonDown(___all_struct.get(1883782801), x, y, 1);
		}
		let key = finger_id + "_" + touch_id;
		let info = {};
		info.key = key;
		info.mouse_x = x;
		info.mouse_y = y;
		info.last_mouse_x = 0;
		info.last_mouse_y = 0;
		info.dl = false;
		info.mfc = undefined;
		info.mfc_rel_x = 0;
		info.mfc_rel_y = 0;
		info.is_sfc = false;
		let mfd = undefined;
		[info.mfc, mfd, info.mfc_rel_x, info.mfc_rel_y] = A_LayerManager.PickUp(x, y);
		if (info.mfc === undefined) {
			return false;
		}
		info.is_sfc = (this._sl && (info.mfc === this._mfc || info.mfc === this._sfc));
		let event = {};
		event.target = info.mfc;
		event.abs_x = x;
		event.abs_y = y;
		event.rel_x = info.mfc_rel_x;
		event.rel_y = info.mfc_rel_y;
		event.finger_key = info.key;
		event.is_sfc = info.is_sfc;
		event.is_drag = false;
		info.mfc.DispatchEvent(___all_struct.get(-1233353463), event);
		this._finger_info[key] = info;
		return true;
	},
	HandleFingerUp : function(x, y, finger_id, touch_id) {
		if (this._lbutton_down && this._lbutton_finger_id === finger_id && this._lbutton_touch_id === touch_id) {
			this._lbutton_down = false;
			return this.HandleButtonUp(___all_struct.get(40651933), x, y, this._lbutton_count);
		}
		let key = finger_id + "_" + touch_id;
		let info = this._finger_info[key];
		if (info === undefined) {
			return false;
		}
		delete this._finger_info[key];
		info.last_mouse_x = info.mouse_x;
		info.last_mouse_y = info.mouse_y;
		info.mouse_x = x;
		info.mouse_y = y;
		let save_dl = info.dl;
		if (info.dl === true) {
			info.dl = false;
			let event = {};
			event.target = info.mfc;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = info.mfc_rel_x;
			event.rel_y = info.mfc_rel_y;
			event.delta_x = info.mouse_x - info.last_mouse_x;
			event.delta_y = info.mouse_y - info.last_mouse_y;
			event.finger_key = key;
			event.is_sfc = info.is_sfc;
			info.mfc.DispatchEvent(___all_struct.get(-2050069067), event);
		}
		let event = {};
		event.target = info.mfc;
		event.abs_x = x;
		event.abs_y = y;
		event.rel_x = info.mfc_rel_x;
		event.rel_y = info.mfc_rel_y;
		event.finger_key = info.key;
		event.is_sfc = info.is_sfc;
		event.is_drag = save_dl;
		info.mfc.DispatchEvent(___all_struct.get(734860930), event);
		return true;
	},
	HandleFingerMoved : function(x, y, finger_id, touch_id) {
		if (this._lbutton_down && this._lbutton_finger_id === finger_id && this._lbutton_touch_id === touch_id) {
			return this.HandleMouseMoved(x, y);
		}
		let key = finger_id + "_" + touch_id;
		let info = this._finger_info[key];
		if (info === undefined) {
			return false;
		}
		let delta_x = x - info.mouse_x;
		let delta_y = y - info.mouse_y;
		info.last_mouse_x = info.mouse_x;
		info.last_mouse_y = info.mouse_y;
		info.mouse_x = x;
		info.mouse_y = y;
		if (info.mfc !== undefined) {
			[info.mfc_rel_x, info.mfc_rel_y] = info.mfc.GlobalToLocalMatrix2D(x, y);
		}
		if (info.dl === true) {
			let event = {};
			event.target = info.mfc;
			event.delta_x = delta_x;
			event.delta_y = delta_y;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = info.mfc_rel_x;
			event.rel_y = info.mfc_rel_y;
			event.finger_key = info.key;
			event.is_sfc = info.is_sfc;
			info.mfc.DispatchEvent(___all_struct.get(-51419723), event);
			return true;
		}
		if (info.dl === false) {
			info.dl = true;
			let event = {};
			event.target = info.mfc;
			event.delta_x = delta_x;
			event.delta_y = delta_y;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = info.mfc_rel_x;
			event.rel_y = info.mfc_rel_y;
			event.finger_key = info.key;
			event.is_sfc = info.is_sfc;
			info.mfc.DispatchEvent(___all_struct.get(1598008698), event);
			return true;
		}
		return false;
	},
}, "ALittle.UISystem");

window.A_UISystem = ALittle.NewObject(ALittle.UISystem);
}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


ALittle.LayerManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._normal_groups = [];
		this._normal_group_count = 0;
		this._modal_layer = ALittle.NewObject(ALittle.DisplayLayout, undefined);
		A_JDisplaySystem.AddSpecialChild(this._modal_layer.native_show);
		this._right_layer = ALittle.NewObject(ALittle.DisplayLayout, undefined);
		this._right_show = undefined;
		A_JDisplaySystem.AddSpecialChild(this._right_layer.native_show);
		this._tip_layer = ALittle.NewObject(ALittle.DisplayLayout, undefined);
		this._tip_layer.disabled = true;
		A_JDisplaySystem.AddSpecialChild(this._tip_layer.native_show);
	},
	Shutdown : function() {
		A_JDisplaySystem.RemoveAllChild();
	},
	get group_count() {
		return this._normal_group_count;
	},
	AddChild : function(child, index) {
		if (child === undefined) {
			return;
		}
		if (index === undefined || index > this._normal_group_count || this._normal_group_count < 1) {
			++ this._normal_group_count;
			this._normal_groups[this._normal_group_count - 1] = child;
			A_JDisplaySystem.AddChild(child.native_show);
		} else {
			if (index < 1) {
				index = 1;
			}
			let back_child = this._normal_groups[index - 1];
			A_JDisplaySystem.AddChildBefore(back_child.native_show, child.native_show);
			ALittle.List_Insert(this._normal_groups, index, child);
			++ this._normal_group_count;
		}
		child.width = A_UISystem.view_width;
		child.height = A_UISystem.view_height;
	},
	RemoveChild : function(child) {
		if (child === undefined) {
			return;
		}
		let has_layer = false;
		let ___OBJECT_1 = this._normal_groups;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let value = ___OBJECT_1[index - 1];
			if (value === undefined) break;
			if (value === child) {
				ALittle.List_Remove(this._normal_groups, index);
				has_layer = true;
				break;
			}
		}
		if (has_layer === false) {
			return;
		}
		A_JDisplaySystem.RemoveChild(child.native_show);
		-- this._normal_group_count;
	},
	HandleViewResized : function(width, height) {
		let ___OBJECT_2 = this._normal_groups;
		for (let group_index = 1; group_index <= ___OBJECT_2.length; ++group_index) {
			let group = ___OBJECT_2[group_index - 1];
			if (group === undefined) break;
			group.width = width;
			group.height = height;
		}
		this._modal_layer.width = width;
		this._modal_layer.height = height;
		this._right_layer.width = width;
		this._right_layer.height = height;
		this._tip_layer.width = width;
		this._tip_layer.height = height;
		this.HideCurrentFromRight();
	},
	AddToModal : function(dialog, index) {
		if (dialog === undefined) {
			return;
		}
		dialog.x_type = 3;
		dialog.x_value = 0;
		dialog.y_type = 3;
		dialog.y_value = 0;
		dialog.modal = true;
		dialog.visible = false;
		this._modal_layer.AddChild(dialog, index);
	},
	RemoveFromModal : function(dialog) {
		if (dialog === undefined) {
			return;
		}
		dialog.modal = false;
		dialog.visible = true;
		this._modal_layer.RemoveChild(dialog);
	},
	ShowFromRight : function(dialog, focus) {
		if (focus === undefined) {
			focus = true;
		}
		if (this._right_show === dialog) {
			return;
		}
		if (this._right_show !== undefined) {
			this._right_show.DispatchEvent(___all_struct.get(348388800), {});
			this._right_layer.RemoveChild(this._right_show);
			this._right_show = undefined;
		}
		this._right_show = dialog;
		if (this._right_show !== undefined) {
			this._right_layer.AddChild(this._right_show);
			if (focus) {
				this._right_show.focus = true;
			}
			dialog.DispatchEvent(___all_struct.get(1862557463), {});
			dialog.visible = true;
		}
	},
	HideFromRight : function(dialog) {
		if (this._right_show !== dialog) {
			return;
		}
		if (this._right_show === undefined) {
			return;
		}
		this._right_show.DispatchEvent(___all_struct.get(348388800), {});
		this._right_layer.RemoveChild(this._right_show);
		this._right_show.focus = false;
		this._right_show = undefined;
	},
	HideCurrentFromRight : function() {
		if (this._right_show === undefined) {
			return false;
		}
		this.HideFromRight(this._right_show);
		return true;
	},
	IsCurrentRight : function(dialog) {
		return this._right_show === dialog;
	},
	AddToTip : function(dialog) {
		this._tip_layer.AddChild(dialog);
	},
	RemoveFromTip : function(dialog) {
		this._tip_layer.RemoveChild(dialog);
	},
	PickUp : function(x, y) {
		let mfc_rel_x = undefined;
		let mfc_rel_y = undefined;
		let mfc = undefined;
		let mfd = undefined;
		[mfc, mfc_rel_x, mfc_rel_y] = this._right_layer.PickUp(x, y);
		if (mfc !== undefined) {
			return [mfc, undefined, mfc_rel_x, mfc_rel_y];
		}
		[mfc, mfc_rel_x, mfc_rel_y] = this._modal_layer.PickUp(x, y);
		if (mfc !== undefined) {
			return [mfc, undefined, mfc_rel_x, mfc_rel_y];
		}
		let normal_groups = this._normal_groups;
		for (let group_index = this._normal_group_count; group_index > 0; group_index += -1) {
			let normal_layers = normal_groups[group_index - 1];
			let layer_list = normal_layers.childs;
			for (let layer_index = normal_layers.child_count; layer_index > 0; layer_index += -1) {
				let layer = layer_list[layer_index - 1];
				[mfc, mfd, mfc_rel_x, mfc_rel_y] = this.LayerPickup(layer, x, y);
				if (mfc !== undefined) {
					return [mfc, mfd, mfc_rel_x, mfc_rel_y];
				}
			}
		}
		return [undefined, undefined, undefined, undefined];
	},
	LayerPickup : function(layer, x, y) {
		let mfc_rel_x = undefined;
		let mfc_rel_y = undefined;
		let mfc = undefined;
		let mfd = undefined;
		if (layer.visible && layer.disabled === false && layer.childs !== undefined) {
			let rel_x = x - layer.x;
			let rel_y = y - layer.y;
			let child_list = layer.childs;
			for (let index = layer.child_count; index > 0; index += -1) {
				let dialog = child_list[index - 1];
				[mfc, mfc_rel_x, mfc_rel_y] = dialog.PickUp(rel_x, rel_y);
				if (mfc !== undefined) {
					mfd = dialog;
					break;
				}
			}
		}
		return [mfc, mfd, mfc_rel_x, mfc_rel_y];
	},
	HandleLRButtonDown : function(x, y) {
		if (this._right_show === undefined) {
			return;
		}
		let [left, top] = this._right_show.LocalToGlobal();
		let right = this._right_show.width * this._right_show.scale_x + left;
		let bottom = this._right_show.height * this._right_show.scale_y + top;
		if (x >= left && x < right && y >= top && y < bottom) {
			return;
		}
		let link_control = this._right_show.__right_data;
		if (link_control !== undefined) {
			let [abs_x, abs_y] = link_control.LocalToGlobal();
			if (x >= abs_x && x < abs_x + link_control.width * link_control.scale_x && y >= abs_y && y < abs_y + link_control.height * link_control.scale_y) {
				return;
			}
		}
		this._right_show.DispatchEvent(___all_struct.get(348388800), {});
		this._right_show.visible = false;
		this._right_show = undefined;
	},
}, "ALittle.LayerManager");

window.A_LayerManager = ALittle.NewObject(ALittle.LayerManager);
}
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(-1815508639, "ALittle.TextureCutInfo", {
name : "ALittle.TextureCutInfo", ns_name : "ALittle", rl_name : "TextureCutInfo", hash_code : -1815508639,
name_list : ["texture_name","max_width","max_height","cache"],
type_list : ["string","int","int","bool"],
option_map : {}
})
ALittle.RegStruct(1812223610, "ALittle.LoadAtlasInfo", {
name : "ALittle.LoadAtlasInfo", ns_name : "ALittle", rl_name : "LoadAtlasInfo", hash_code : 1812223610,
name_list : ["big_path","atlas","big_width","big_height"],
type_list : ["string","List<string>","int","int"],
option_map : {}
})
ALittle.RegStruct(1754262532, "ALittle.LoadingTextureInfo", {
name : "ALittle.LoadingTextureInfo", ns_name : "ALittle", rl_name : "LoadingTextureInfo", hash_code : 1754262532,
name_list : ["cache","object_map"],
type_list : ["bool","Map<ALittle.DisplayObject,ALittle.LoadingTextureObjectInfo>"],
option_map : {}
})
ALittle.RegStruct(1390702448, "ALittle.AltasCollectInfo", {
name : "ALittle.AltasCollectInfo", ns_name : "ALittle", rl_name : "AltasCollectInfo", hash_code : 1390702448,
name_list : ["count","list"],
type_list : ["int","List<List<any>>"],
option_map : {}
})
ALittle.RegStruct(1305876767, "ALittle.PrepareInfo", {
name : "ALittle.PrepareInfo", ns_name : "ALittle", rl_name : "PrepareInfo", hash_code : 1305876767,
name_list : ["total","succeed","failed","map","callback"],
type_list : ["int","int","int","Map<string,bool>","Functor<(int,int,int)>"],
option_map : {}
})
ALittle.RegStruct(1266404893, "ALittle.LoadTextureInfo", {
name : "ALittle.LoadTextureInfo", ns_name : "ALittle", rl_name : "LoadTextureInfo", hash_code : 1266404893,
name_list : ["loader","cut_loader","texture_mgr"],
type_list : ["ALittle.ITextureLoader","ALittle.ITextureCutLoader","ALittle.TextureManager"],
option_map : {}
})
ALittle.RegStruct(1002517605, "ALittle.LoadingTextureObjectInfo", {
name : "ALittle.LoadingTextureObjectInfo", ns_name : "ALittle", rl_name : "LoadingTextureObjectInfo", hash_code : 1002517605,
name_list : ["callback"],
type_list : ["Functor<(ALittle.DisplayObject,bool)>"],
option_map : {}
})
ALittle.RegStruct(-451991995, "ALittle.AltasTextureInfo", {
name : "ALittle.AltasTextureInfo", ns_name : "ALittle", rl_name : "AltasTextureInfo", hash_code : -451991995,
name_list : ["width","height","path"],
type_list : ["int","int","string"],
option_map : {}
})
ALittle.RegStruct(-60039899, "ALittle.AltasInfo", {
name : "ALittle.AltasInfo", ns_name : "ALittle", rl_name : "AltasInfo", hash_code : -60039899,
name_list : ["big_path","atlas","big_width","big_height","t","b","l","r"],
type_list : ["string","List<string>","int","int","double","double","double","double"],
option_map : {}
})

ALittle.LoadTextureManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._id_map_info = new Map();
		this._path_map_texture_cut = ALittle.CreateValueWeakMap();
		this._path_map_objects_cut = {};
		this._redraw_map_redraw = ALittle.CreateKeyWeakMap();
		this._texmgr_map_texmgr = ALittle.CreateKeyWeakMap();
	},
	CreateTexture : function(texture_mgr, atlas) {
		let loader = undefined;
		loader = ALittle.NewObject(JavaScript.JTextureLoader);
		loader.SetPath(atlas.big_path, ALittle.String_Join(atlas.atlas, ";"), atlas.big_width, atlas.big_height, texture_mgr.crypt_mode);
		let info = {};
		this._id_map_info.set(loader.GetID(), info);
		info.texture_mgr = texture_mgr;
		info.loader = loader;
		loader.Start();
	},
	HandleTextureLoadSucceed : function(loader, texture) {
		let loader_id = loader.GetID();
		let info = this._id_map_info.get(loader_id);
		if (info === undefined) {
			return;
		}
		this._id_map_info.delete(loader_id);
		info.texture_mgr.HandleTextureLoadSucceed(loader, texture);
	},
	HandleTextureLoadFailed : function(loader) {
		let loader_id = loader.GetID();
		let info = this._id_map_info.get(loader_id);
		if (info === undefined) {
			return;
		}
		this._id_map_info.delete(loader_id);
		info.texture_mgr.HandleTextureLoadFailed(loader);
	},
	GetTextureCut : function(path, max_width, max_height) {
		let texture_id = path + "_" + max_width + "_" + max_height;
		return this._path_map_texture_cut[texture_id];
	},
	ClearTextureCut : function(path, max_width, max_height) {
		let texture_id = path + "_" + max_width + "_" + max_height;
		delete this._path_map_texture_cut[texture_id];
	},
	IsLoadingTextureCut : function(path, max_width, max_height) {
		let texture_id = path + "_" + max_width + "_" + max_height;
		return this._path_map_objects_cut[texture_id] !== undefined;
	},
	SetTextureCut : function(object, path, max_width, max_height, cache, callback) {
		object.SetTextureCoord(0, 1, 0, 1);
		if (max_width === undefined) {
			max_width = 0;
		}
		max_width = ALittle.Math_Floor(max_width);
		if (max_height === undefined) {
			max_height = 0;
		}
		max_height = ALittle.Math_Floor(max_height);
		if (cache === undefined) {
			cache = false;
		}
		let texture_id = path + "_" + max_width + "_" + max_height;
		let texture = this._path_map_texture_cut[texture_id];
		if (texture !== undefined) {
			object.texture = texture;
			if (callback !== undefined) {
				callback(object, true);
			}
			return;
		}
		let loading_info = this._path_map_objects_cut[texture_id];
		if (loading_info !== undefined) {
			let object_info = {};
			object_info.callback = callback;
			loading_info.object_map.set(object, object_info);
			return;
		}
		loading_info = {};
		loading_info.cache = cache;
		this._path_map_objects_cut[texture_id] = loading_info;
		loading_info.object_map = ALittle.CreateKeyWeakMap();
		let object_info = {};
		object_info.callback = callback;
		loading_info.object_map.set(object, object_info);
		let loader = undefined;
		loader = ALittle.NewObject(JavaScript.JTextureCutLoader);
		loader.SetPath(path, max_width, max_height);
		let info = {};
		this._id_map_info.set(loader.GetID(), info);
		info.cut_loader = loader;
		loader.Start();
	},
	HandleTextureCutLoadSucceed : function(loader, texture) {
		let loader_id = loader.GetID();
		let info = this._id_map_info.get(loader_id);
		if (info === undefined) {
			return;
		}
		this._id_map_info.delete(loader_id);
		let path = loader.GetPath();
		let max_width = loader.GetMaxWidth();
		let max_height = loader.GetMaxHeight();
		let texture_id = path + "_" + max_width + "_" + max_height;
		let loading_info = this._path_map_objects_cut[texture_id];
		if (loading_info === undefined) {
			return;
		}
		if (loading_info.cache) {
			this._path_map_texture_cut[texture_id] = texture;
		}
		for (let [object, value] of loading_info.object_map) {
			if (value === undefined) continue;
			if (object.texture_name === path) {
				object.texture = texture;
				if (value.callback !== undefined) {
					value.callback(object, true);
				}
			}
		}
		delete this._path_map_objects_cut[texture_id];
	},
	HandleTextureCutLoadFailed : function(loader) {
		let loader_id = loader.GetID();
		let info = this._id_map_info.get(loader_id);
		if (info === undefined) {
			return;
		}
		this._id_map_info.delete(loader_id);
		let path = loader.GetPath();
		let max_width = loader.GetMaxWidth();
		let max_height = loader.GetMaxHeight();
		let texture_id = path + "_" + max_width + "_" + max_height;
		let loading_info = this._path_map_objects_cut[texture_id];
		if (loading_info === undefined) {
			return;
		}
		for (let [object, value] of loading_info.object_map) {
			if (value === undefined) continue;
			if (value.callback !== undefined) {
				value.callback(object, false);
			}
		}
		delete this._path_map_objects_cut[texture_id];
	},
	RegisterRedrawControl : function(control) {
		this._redraw_map_redraw.set(control, true);
	},
	RegisterTexmgrControl : function(control) {
		this._texmgr_map_texmgr.delete(control);
	},
	HandleRenderDeviceReset : function() {
		this._path_map_texture_cut = ALittle.CreateValueWeakMap();
		for (let [texmgr, _] of this._texmgr_map_texmgr) {
			if (_ === undefined) continue;
			texmgr.ClearCache();
		}
		for (let [control, _] of this._redraw_map_redraw) {
			if (_ === undefined) continue;
			control.Redraw();
		}
	},
}, "ALittle.LoadTextureManager");

window.A_LoadTextureManager = ALittle.NewObject(ALittle.LoadTextureManager);
ALittle.AltasBinary = JavaScript.Class(undefined, {
	Ctor : function(x, y, width, height) {
		this._width = width;
		this._height = height;
		this._x = x;
		this._y = y;
		this._texture_x = undefined;
		this._texture_y = undefined;
		this._texture_w = undefined;
		this._texture_h = undefined;
		this._texture_path = undefined;
		this._left = undefined;
		this._right = undefined;
	},
	Fill : function(texture_info, padding) {
		if (this._left !== undefined) {
			if (this._left.Fill(texture_info, padding)) {
				return true;
			}
		}
		if (this._right !== undefined) {
			if (this._right.Fill(texture_info, padding)) {
				return true;
			}
		}
		if (this._texture_path === undefined) {
			let real_width = texture_info.width + padding * 2;
			let real_height = texture_info.height + padding * 2;
			if (real_width > this._width) {
				return false;
			}
			if (real_height > this._height) {
				return false;
			}
			this._texture_w = texture_info.width;
			this._texture_h = texture_info.height;
			this._texture_x = this._x + padding;
			this._texture_y = this._y + padding;
			this._texture_path = texture_info.path;
			this._left = ALittle.NewObject(ALittle.AltasBinary, this._x + real_width, this._y, this._width - real_width, real_height);
			this._right = ALittle.NewObject(ALittle.AltasBinary, this._x, this._y + real_height, this._width, this._height - real_height);
			return true;
		}
		return false;
	},
	GetInfo : function(list_info) {
		if (list_info === undefined) {
			list_info = {};
			list_info.count = 0;
			list_info.list = [];
		}
		if (this._texture_path !== undefined) {
			let info = [];
			info[1 - 1] = this._texture_path;
			info[2 - 1] = this._texture_x;
			info[3 - 1] = this._texture_y;
			info[4 - 1] = this._texture_w;
			info[5 - 1] = this._texture_h;
			++ list_info.count;
			list_info.list[list_info.count - 1] = info;
		}
		if (this._left !== undefined) {
			this._left.GetInfo(list_info);
		}
		if (this._right !== undefined) {
			this._right.GetInfo(list_info);
		}
		return list_info.list;
	},
	TextureListComp : function(a, b) {
		if (a.height > b.height) {
			return true;
		} else if (a.height === b.height) {
			if (a.width > b.width) {
				return true;
			} else if (a.width === b.width) {
				if (a.path > b.path) {
					return true;
				}
			}
		}
		return false;
	},
	GenerateAltas : function(texture_list, max_width, max_height, padding) {
		ALittle.List_Sort(texture_list, ALittle.AltasBinary.TextureListComp);
		let big_list = [];
		let big_list_count = 0;
		++ big_list_count;
		big_list[big_list_count - 1] = max_width;
		++ big_list_count;
		big_list[big_list_count - 1] = max_height;
		while (true) {
			let altas = ALittle.NewObject(ALittle.AltasBinary, 0, 0, max_width, max_height);
			let left_list = [];
			let left_list_count = 0;
			let ___OBJECT_1 = texture_list;
			for (let index = 1; index <= ___OBJECT_1.length; ++index) {
				let texture_info = ___OBJECT_1[index - 1];
				if (texture_info === undefined) break;
				let real_width = texture_info.width + padding * 2;
				let real_height = texture_info.height + padding * 2;
				if (real_width <= max_width && real_height <= max_height) {
					if (altas.Fill(texture_info, padding) !== true) {
						++ left_list_count;
						left_list[left_list_count - 1] = texture_info;
					}
				}
			}
			let list = altas.GetInfo();
			if (list[2 - 1] !== undefined) {
				++ big_list_count;
				big_list[big_list_count - 1] = list;
			}
			texture_list = left_list;
			if (texture_list[1 - 1] === undefined) {
				break;
			}
		}
		return big_list;
	},
}, "ALittle.AltasBinary");

ALittle.TextureManager = JavaScript.Class(undefined, {
	Ctor : function(module_name, crypt_mode) {
		this._cache_texture = true;
		this._base_path = "Module/" + module_name + "/Texture/";
		this._crypt_mode = crypt_mode || false;
		this._path_map_texture = ALittle.CreateValueWeakMap();
		this._prepare_map = new Map();
		this._path_map_objects = {};
		this.LoadAtlas();
	},
	LoadAtlas : function() {
		this._name_map_atlas = {};
		if (!this._crypt_mode) {
			return;
		}
		let [big_list] = ALittle.File_ReadJsonFromFile(this._base_path + "Atlas.ali", this._crypt_mode);
		if (big_list === undefined) {
			return;
		}
		let big_list_count = ALittle.List_Len(big_list);
		if (big_list_count < 2) {
			return;
		}
		let texture_width = big_list[1 - 1];
		let texture_height = big_list[2 - 1];
		for (let index = 3; index <= big_list_count; index += 1) {
			let list = big_list[index - 1];
			let big_path = index + ".atlas";
			let info = [];
			let info_count = 0;
			let ___OBJECT_2 = list;
			for (let _ = 1; _ <= ___OBJECT_2.length; ++_) {
				let value = ___OBJECT_2[_ - 1];
				if (value === undefined) break;
				let path = value[1 - 1];
				let x = value[2 - 1];
				let y = value[3 - 1];
				let w = value[4 - 1];
				let h = value[5 - 1];
				let atlas = {};
				atlas.big_path = big_path;
				atlas.t = y / texture_height;
				atlas.b = (y + h) / texture_height;
				atlas.l = x / texture_width;
				atlas.r = (x + w) / texture_width;
				atlas.big_width = texture_width;
				atlas.big_height = texture_height;
				atlas.atlas = info;
				this._name_map_atlas[path] = atlas;
				++ info_count;
				info[info_count - 1] = this._base_path + path + "," + y + "," + ((y + h)) + "," + x + "," + ((x + w)) + "," + w + "," + h;
			}
		}
	},
	GetAtlas : function(name) {
		let atlas = this._name_map_atlas[name];
		if (atlas !== undefined) {
			return atlas;
		}
		atlas = {};
		this._name_map_atlas[name] = atlas;
		atlas.big_path = name;
		atlas.t = 0;
		atlas.b = 1;
		atlas.l = 0;
		atlas.r = 1;
		atlas.big_width = 0;
		atlas.big_height = 0;
		atlas.atlas = [];
		atlas.atlas[1 - 1] = this._base_path + name + ",0,0,0,0,0,0";
		return atlas;
	},
	set cache_texture(cache) {
		this._cache_texture = cache;
	},
	get cache_texture() {
		return this._cache_texture;
	},
	get crypt_mode() {
		return this._crypt_mode;
	},
	ClearCache : function() {
		this._path_map_texture = ALittle.CreateValueWeakMap();
		this._prepare_map = new Map();
	},
	PrepareTexture : function(name_map, callback) {
		let new_name_map = {};
		let ___OBJECT_3 = name_map;
		for (let name in ___OBJECT_3) {
			let value = ___OBJECT_3[name];
			if (value === undefined) continue;
			let atlas = this.GetAtlas(name);
			if (new_name_map[atlas.big_path] === undefined) {
				let texture = this._path_map_texture[atlas.big_path];
				if (texture === undefined) {
					let loading_map = this._path_map_objects[atlas.big_path];
					if (loading_map === undefined) {
						loading_map = ALittle.CreateKeyWeakMap();
						this._path_map_objects[atlas.big_path] = loading_map;
					}
					A_LoadTextureManager.CreateTexture(this, atlas);
					new_name_map[atlas.big_path] = false;
				} else {
					new_name_map[atlas.big_path] = true;
				}
			}
		}
		let prepare_info = {};
		prepare_info.total = 0;
		prepare_info.succeed = 0;
		prepare_info.failed = 0;
		prepare_info.map = new_name_map;
		prepare_info.callback = callback;
		let ___OBJECT_4 = new_name_map;
		for (let name in ___OBJECT_4) {
			let value = ___OBJECT_4[name];
			if (value === undefined) continue;
			++ prepare_info.total;
			if (value) {
				++ prepare_info.succeed;
			}
		}
		if (prepare_info.total > prepare_info.succeed + prepare_info.failed) {
			this._prepare_map.set(prepare_info, true);
		}
		if (callback !== undefined) {
			callback(prepare_info.total, prepare_info.succeed, prepare_info.failed);
		}
	},
	SetTexture : function(object, name) {
		let atlas = this.GetAtlas(name);
		object.SetTextureCoord(atlas.t, atlas.b, atlas.l, atlas.r);
		let texture = this._path_map_texture[atlas.big_path];
		if (texture !== undefined) {
			object.texture = texture;
			return;
		}
		let loading_map = this._path_map_objects[atlas.big_path];
		if (loading_map !== undefined) {
			loading_map.set(object, name);
			return;
		}
		loading_map = ALittle.CreateKeyWeakMap();
		this._path_map_objects[atlas.big_path] = loading_map;
		loading_map.set(object, name);
		A_LoadTextureManager.CreateTexture(this, atlas);
	},
	HandleTextureLoadSucceed : function(loader, texture) {
		let path = loader.GetPath();
		let loading_map = this._path_map_objects[path];
		if (loading_map !== undefined) {
			if (this._cache_texture) {
				this._path_map_texture[path] = texture;
			}
			for (let [k, v] of loading_map) {
				if (v === undefined) continue;
				if (k.texture_name === v) {
					k.texture = texture;
				}
			}
			delete this._path_map_objects[path];
		}
		let copy_map = new Map();
		for (let [k, v] of this._prepare_map) {
			if (v === undefined) continue;
			copy_map.set(k, v);
		}
		let erase_map = new Map();
		for (let [info, v] of copy_map) {
			if (v === undefined) continue;
			if (info.map[path] === false) {
				++ info.succeed;
				info.map[path] = true;
				if (info.callback !== undefined) {
					info.callback(info.total, info.succeed, info.failed);
				}
				if (info.total <= info.succeed + info.failed) {
					erase_map.set(info, true);
				}
			}
		}
		for (let [info, v] of erase_map) {
			if (v === undefined) continue;
			this._prepare_map.delete(info);
		}
	},
	HandleTextureLoadFailed : function(loader) {
		let path = loader.GetPath();
		delete this._path_map_objects[path];
		let erase_map = new Map();
		for (let [info, v] of this._prepare_map) {
			if (v === undefined) continue;
			if (info.map[path] === false) {
				++ info.failed;
				info.map[path] = true;
				if (info.callback !== undefined) {
					info.callback(info.total, info.succeed, info.failed);
				}
				if (info.total <= info.succeed + info.failed) {
					erase_map.set(info, true);
				}
			}
		}
		for (let [info, v] of erase_map) {
			if (v === undefined) continue;
			this._prepare_map.delete(info);
		}
	},
}, "ALittle.TextureManager");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


let __byte = ALittle.String_Byte;
let __type = ALittle.String_Type;
ALittle.ControlSystem = JavaScript.Class(undefined, {
	Ctor : function(module_name, crypt_mode) {
		this._log_error = true;
		this._use_plugin_class = true;
		this._font_map = {};
		this._child_plugin_map = {};
		this._parent_plugin_map = {};
		this._name_map_info = {};
		this._name_map_info_cache = {};
		this._module_name = module_name;
		this._crypt_mode = crypt_mode || false;
		if (window["alittle_hostname"] !== undefined) {
			this._host = window["alittle_hostname"];
		} else {
			this._host = location.hostname;
		}
		if (window["alittle_port"] !== undefined) {
			this._port = window["alittle_port"];
		} else {
			this._port = ALittle.Math_ToInt(location.port);
		}
		if (window["alittle_base_url"] !== undefined) {
			this._base_url = window["alittle_base_url"];
		} else {
			this._base_url = ALittle.File_GetFilePathByPath(location.pathname) + "/";
		}
		if (this._port === undefined) {
			if (location.protocol === "https:") {
				this._port = 443;
			} else {
				this._port = 80;
			}
		}
		this._base_path = "Module/" + module_name + "/";
		this._base_path = this._base_url + this._base_path;
		this._ui_path = this._base_path + "UI/";
		this._font_path = this._base_path + "Font/";
		this._sound_path = this._base_path + "Sound/";
		this._other_path = this._base_path + "Other/";
		this._texture_mgr = ALittle.NewObject(ALittle.TextureManager, module_name, this._crypt_mode);
		A_LoadTextureManager.RegisterTexmgrControl(this._texture_mgr);
	},
	get crypt_mode() {
		return this._crypt_mode;
	},
	get log_error() {
		return this._log_error;
	},
	set log_error(value) {
		this._log_error = value;
	},
	get info_map() {
		return this._name_map_info;
	},
	RegisterFont : function(src, dst) {
		this._font_map[src] = dst;
	},
	RegisterPlugin : function(module_name, plugin) {
		this._child_plugin_map[module_name] = plugin;
		plugin._parent_plugin_map[this._module_name] = this;
	},
	UnRegisterPlugin : function(module_name) {
		let plugin = this._child_plugin_map[module_name];
		if (plugin === undefined) {
			return;
		}
		delete this._child_plugin_map[module_name];
		delete plugin._parent_plugin_map[this._module_name];
	},
	RegisterInfoByHttp : function() {
		return new Promise((async function(___COROUTINE, ___) {
			let path = this._ui_path + "../JSUI/ui_all_in_one.json";
			ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(path));
			let error = await ALittle.HttpDownloadRequest(this._host, this._port, path, path, undefined, true);
			if (error !== undefined) {
				ALittle.Error("ui load failed:" + error);
				___COROUTINE(); return;
			}
			let [content, buffer] = JavaScript.File_LoadFile(path);
			if (buffer === undefined) {
				ALittle.Error("ui load failed:" + error);
				___COROUTINE(); return;
			}
			content = UTF8ArrayToString(new Uint8Array(buffer));
			JavaScript.File_DeleteFile(path);
			let [jerror, json] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (jerror !== undefined) {
				ALittle.Error("ui json decode failed:" + jerror);
				___COROUTINE(); return;
			}
			let ___OBJECT_1 = json;
			for (let name in ___OBJECT_1) {
				let value = ___OBJECT_1[name];
				if (value === undefined) continue;
				this.RegisterInfo(name, value);
			}
			___COROUTINE();
		}).bind(this));
	},
	HttpDownload : function(path) {
		return new Promise((async function(___COROUTINE, ___) {
			let [content, buffer] = JavaScript.File_LoadFile(path);
			if (buffer !== undefined || content !== undefined) {
				___COROUTINE(undefined); return;
			}
			ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(path));
			let error = await ALittle.HttpDownloadRequest(this._host, this._port, path, this._base_url + path, undefined, true);
			if (error !== undefined) {
				___COROUTINE(error); return;
			}
			___COROUTINE(undefined); return;
		}).bind(this));
	},
	LoadMessageFromFile : function(T, path) {
		return new Promise((async function(___COROUTINE, ___) {
			let path_prefix = "Module/" + this._module_name + "/";
			let module_path = path;
			if (ALittle.String_Find(module_path, path_prefix) === 1) {
				path = ALittle.String_Sub(path, ALittle.String_Len(path_prefix) + 1);
			} else {
				module_path = path_prefix + path;
			}
			let factory = undefined;
			{
				let [content, buffer] = JavaScript.File_LoadFile(module_path);
				if (buffer === undefined) {
					ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(module_path));
					let error = await ALittle.HttpDownloadRequest(this._host, this._port, module_path, this._base_path + path, undefined, true);
					if (error !== undefined) {
						ALittle.Error(this._host, this._port, module_path, error);
						___COROUTINE(undefined); return;
					}
					[content, buffer] = JavaScript.File_LoadFile(module_path);
				}
				if (buffer === undefined) {
					ALittle.Error("FileLoad fialed:", module_path);
					___COROUTINE(undefined); return;
				}
				factory = ALittle.NewObject(JavaScript.JMessageReadFactory, new DataView(buffer), 0, false);
			}
			let rflct = T;
			let invoke_info = ALittle.CreateMessageInfo(rflct.name);
			if (invoke_info === undefined) {
				ALittle.Error("CreateMessageInfo fialed:", module_path);
				___COROUTINE(undefined); return;
			}
			let [data] = ALittle.PS_ReadMessage(factory, invoke_info, undefined, factory.GetDataSize());
			if (data === undefined) {
				ALittle.Error("PS_ReadMessage fialed:", module_path);
				___COROUTINE(undefined); return;
			}
			___COROUTINE(data); return;
		}).bind(this));
	},
	WriteMessageToFile : function(T, msg, path) {
		let path_prefix = "Module/" + this._module_name + "/";
		let module_path = path;
		if (ALittle.String_Find(module_path, path_prefix) === 1) {
			path = ALittle.String_Sub(path, ALittle.String_Len(path_prefix) + 1);
		} else {
			module_path = path_prefix + path;
		}
		let factory = undefined;
		factory = ALittle.NewObject(JavaScript.JMessageWriteFactory, 1024);
		if (factory === undefined) {
			return "factory create failed";
		}
		let rflct = T;
		let invoke_info = ALittle.CreateMessageInfo(rflct.name);
		if (invoke_info === undefined) {
			return "create message info failed:" + rflct.name;
		}
		ALittle.PS_WriteMessage(factory, invoke_info, undefined, msg);
		let result = factory.WriteToStdFile(ALittle.File_BaseFilePath() + module_path);
		if (!result) {
			return "WriteToStdFile failed";
		}
		return undefined;
	},
	RegisterInfo : function(name, info) {
		this._name_map_info[name] = info;
		delete this._name_map_info_cache[name];
	},
	UnRegisterInfo : function(name) {
		delete this._name_map_info[name];
		delete this._name_map_info_cache[name];
	},
	ClearAllInfo : function() {
		this._name_map_info = {};
		this._name_map_info_cache = {};
	},
	CreateControlObject : function(info) {
		if (info.__module !== undefined && info.__module !== this._module_name) {
			let plugin = this._child_plugin_map[info.__module];
			if (plugin === undefined) {
				plugin = this._parent_plugin_map[info.__module];
			}
			if (plugin === undefined) {
				ALittle.Log("unknow module " + info.__module + " cur_module:" + this._module_name);
				return undefined;
			}
			return plugin.CreateControlObject(info);
		}
		let target_class = info.__target_class;
		if (this._use_plugin_class && target_class !== undefined) {
			let class_func = info.__class_func;
			if (class_func === undefined) {
				class_func = window;
				let ___OBJECT_2 = target_class;
				for (let index = 1; index <= ___OBJECT_2.length; ++index) {
					let value = ___OBJECT_2[index - 1];
					if (value === undefined) break;
					class_func = class_func[value];
					if (class_func === undefined) {
						break;
					}
				}
				info.__class_func = class_func;
			}
			if (class_func !== undefined) {
				return ALittle.NewObject(class_func, this);
			} else {
				ALittle.Log("unknow target class." + ALittle.String_Join(target_class, "."));
			}
		}
		let clazz = info.__class;
		if (clazz === undefined) {
			ALittle.Log("__class is null");
			return undefined;
		}
		let class_func = info.__class_func;
		if (class_func === undefined) {
			class_func = ALittle[clazz];
			info.__class_func = class_func;
		}
		if (class_func === undefined) {
			ALittle.Log("unknow class." + clazz);
			return undefined;
		}
		return ALittle.NewObject(class_func, this);
	},
	StartChunk : function(file_path, loop, callback) {
		return A_AudioSystem.StartChunk(this._sound_path + file_path, loop, callback);
	},
	StopChunk : function(channel) {
		A_AudioSystem.StopChunk(channel);
	},
	SetTexture : function(object, name) {
		this._texture_mgr.SetTexture(object, name);
	},
	PrepareTexture : function(ui_list, callback) {
		let name_map = {};
		if (ui_list !== undefined) {
			let ___OBJECT_3 = ui_list;
			for (let index = 1; index <= ___OBJECT_3.length; ++index) {
				let ui = ___OBJECT_3[index - 1];
				if (ui === undefined) break;
				this.CollectTextureName(ui, name_map);
			}
		}
		this._texture_mgr.PrepareTexture(name_map, callback);
	},
	PrepareCsv : function(csv_map, callback) {
		let new_csv_map = {};
		let ___OBJECT_4 = csv_map;
		for (let file_path in ___OBJECT_4) {
			let config = ___OBJECT_4[file_path];
			if (config === undefined) continue;
			new_csv_map[this._other_path + file_path] = config;
		}
		A_CsvConfigManager.PrepareCsv(new_csv_map, callback);
	},
	set cache_texture(cache) {
		this._texture_mgr.cache_texture = cache;
	},
	get cache_texture() {
		return this._texture_mgr.cache_texture;
	},
	set use_plugin_class(use) {
		this._use_plugin_class = use;
	},
	get use_plugin_class() {
		return this._use_plugin_class;
	},
	SetFont : function(object, font_path, font_size) {
		let dst = this._font_map[font_path];
		if (dst === undefined) {
			dst = "Arial";
		}
		object.native_show.SetFont(dst, font_size);
	},
	SaveControlToFile : function(control, file_path, scale) {
		if (control === undefined) {
			return false;
		}
		if (scale === undefined) {
			scale = 1;
		}
		let texture = ALittle.NewObject(lua.__CPPAPIRenderTexture);
		let x = control.x;
		let y = control.y;
		let width = control.width;
		let height = control.height;
		let visible = control.visible;
		let clip = control.clip;
		control.native_show.SetX(0);
		control.native_show.SetY(0);
		control.visible = true;
		control.clip = false;
		let result = texture.Save(file_path, control.native_show, ALittle.Math_Floor(width), ALittle.Math_Floor(height), scale);
		control.native_show.SetX(x);
		control.native_show.SetY(y);
		control.visible = visible;
		control.clip = clip;
		texture.Clear();
		return result;
	},
	CreateControlImpl : function(name, target_logic, parent) {
		let info = this.LoadInfo(name);
		if (info === undefined) {
			return undefined;
		}
		let object = this.CreateControlObject(info);
		if (object === undefined) {
			return undefined;
		}
		object.Deserialize(info, target_logic, parent);
		return object;
	},
	CreateControl : function(name, target_logic, parent) {
		let object = this.CreateControlImpl(name, target_logic, parent);
		if (object !== undefined) {
			return object;
		}
		let ___OBJECT_5 = this._child_plugin_map;
		for (let module_name in ___OBJECT_5) {
			let plugin = ___OBJECT_5[module_name];
			if (plugin === undefined) continue;
			object = plugin.CreateControlImpl(name, target_logic, parent);
			if (object !== undefined) {
				return object;
			}
		}
		ALittle.Log("can't find control name:" + name);
		return undefined;
	},
	CollectTextureName : function(name, map) {
		let info = this.LoadInfo(name);
		if (info === undefined) {
			let ___OBJECT_6 = this._child_plugin_map;
			for (let module_name in ___OBJECT_6) {
				let plugin = ___OBJECT_6[module_name];
				if (plugin === undefined) continue;
				info = plugin.LoadInfo(name);
				if (info !== undefined) {
					break;
				}
			}
			let ___OBJECT_7 = this._parent_plugin_map;
			for (let module_name in ___OBJECT_7) {
				let plugin = ___OBJECT_7[module_name];
				if (plugin === undefined) continue;
				info = plugin.LoadInfo(name);
				if (info !== undefined) {
					break;
				}
			}
		}
		if (info === undefined) {
			ALittle.Log("can't find control name:" + name);
			return undefined;
		}
		return this.CollectTextureNameImpl(info, map);
	},
	LoadInfo : function(name) {
		if (this._name_map_info_cache[name]) {
			return this._name_map_info[name];
		}
		let info = this._name_map_info[name];
		if (info === undefined) {
			let [json] = ALittle.File_ReadJsonFromFile(this._ui_path + name + ".json", this._crypt_mode);
			if (json === undefined) {
				return undefined;
			}
			let ___OBJECT_8 = json;
			for (let key in ___OBJECT_8) {
				let value = ___OBJECT_8[key];
				if (value === undefined) continue;
				this.RegisterInfo(key, value);
			}
		}
		info = this.CreateInfo(this._name_map_info[name]);
		this._name_map_info[name] = info;
		this._name_map_info_cache[name] = true;
		return this._name_map_info[name];
	},
	CreateInfo : function(info) {
		if (info === undefined) {
			return undefined;
		}
		if (info.__include !== undefined) {
			if (info.__module === undefined || info.__module === this._module_name) {
				return this.LoadInfo(info.__include);
			}
			let plugin = this._child_plugin_map[info.__module];
			if (plugin === undefined) {
				plugin = this._parent_plugin_map[info.__module];
			}
			if (plugin !== undefined) {
				return plugin.LoadInfo(info.__include);
			}
			return undefined;
		}
		let extendsv = info.__extends;
		if (extendsv !== undefined) {
			if (info.__extends_included !== true) {
				let control = undefined;
				if (info.__module === undefined || info.__module === this._module_name) {
					control = this.LoadInfo(extendsv);
					if (control === undefined) {
						ALittle.Log("ControlSystem CreateInfo extends Failed, can't find control. extends:" + extendsv + " module:" + this._module_name);
						return undefined;
					}
				} else {
					let plugin = this._child_plugin_map[info.__module];
					if (plugin === undefined) {
						plugin = this._parent_plugin_map[info.__module];
					}
					if (plugin === undefined) {
						ALittle.Log("ControlSystem CreateInfo extends Failed, can't find plugin. extends:" + extendsv + " module:" + info.__module);
						return undefined;
					}
					control = plugin.LoadInfo(extendsv);
					if (control === undefined) {
						ALittle.Log("ControlSystem CreateInfo extends Failed, can't find control. extends:" + extendsv + " module:" + info.__module);
						return undefined;
					}
				}
				let copy = {};
				let ___OBJECT_9 = control;
				for (let key in ___OBJECT_9) {
					let value = ___OBJECT_9[key];
					if (value === undefined) continue;
					copy[key] = value;
				}
				let ___OBJECT_10 = info;
				for (let key in ___OBJECT_10) {
					let value = ___OBJECT_10[key];
					if (value === undefined) continue;
					copy[key] = value;
				}
				info = copy;
				info.__extends_included = true;
				info.__shows_included = undefined;
				info.__childs_included = undefined;
				info.__base_attr = undefined;
				info.__show_attr = undefined;
			}
		}
		if (info.__shows_included !== true) {
			let ___OBJECT_11 = info;
			for (let key in ___OBJECT_11) {
				let value = ___OBJECT_11[key];
				if (value === undefined) continue;
				if (__byte(key, 1) !== 95 && __type(value) === "table" && (value.__include !== undefined || value.__extends !== undefined || value.__class !== undefined)) {
					info[key] = this.CreateInfo(value);
				}
			}
			info.__shows_included = true;
		}
		let childs = info.__childs;
		if (childs !== undefined) {
			if (info.__childs_included !== true) {
				let ___OBJECT_12 = childs;
				for (let index = 1; index <= ___OBJECT_12.length; ++index) {
					let child = ___OBJECT_12[index - 1];
					if (child === undefined) break;
					childs[index - 1] = this.CreateInfo(childs[index - 1]);
				}
				info.__childs_included = true;
			}
		}
		return info;
	},
	CollectTextureNameImpl : function(info, map) {
		if (map === undefined) {
			map = {};
		}
		let texture_name = info.texture_name;
		if (texture_name !== undefined && texture_name !== "") {
			map[texture_name] = true;
		}
		let info_t = info;
		let ___OBJECT_13 = info_t;
		for (let key in ___OBJECT_13) {
			let value = ___OBJECT_13[key];
			if (value === undefined) continue;
			if (__type(value) === "table" && value.__class !== undefined) {
				this.CollectTextureNameImpl(value, map);
			}
		}
		let childs = info.__childs;
		if (childs !== undefined) {
			let ___OBJECT_14 = childs;
			for (let index = 1; index <= ___OBJECT_14.length; ++index) {
				let value = ___OBJECT_14[index - 1];
				if (value === undefined) break;
				this.CollectTextureNameImpl(value, map);
			}
		}
		return map;
	},
}, "ALittle.ControlSystem");

}