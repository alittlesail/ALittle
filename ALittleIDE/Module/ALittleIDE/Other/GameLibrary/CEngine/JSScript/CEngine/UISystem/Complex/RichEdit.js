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