{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1883782801, "ALittle.UILButtonDownEvent", {
name : "ALittle.UILButtonDownEvent", ns_name : "ALittle", rl_name : "UILButtonDownEvent", hash_code : 1883782801,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-1604617962, "ALittle.UIKeyDownEvent", {
name : "ALittle.UIKeyDownEvent", ns_name : "ALittle", rl_name : "UIKeyDownEvent", hash_code : -1604617962,
name_list : ["target","mod","sym","scancode","custom","handled"],
type_list : ["ALittle.DisplayObject","int","int","int","bool","bool"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name : "ALittle.UIButtonEvent", ns_name : "ALittle", rl_name : "UIButtonEvent", hash_code : -1347278145,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(1337289812, "ALittle.UIButtonDragEvent", {
name : "ALittle.UIButtonDragEvent", ns_name : "ALittle", rl_name : "UIButtonDragEvent", hash_code : 1337289812,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(1301789264, "ALittle.UIButtonDragBeginEvent", {
name : "ALittle.UIButtonDragBeginEvent", ns_name : "ALittle", rl_name : "UIButtonDragBeginEvent", hash_code : 1301789264,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(-1234078962, "ALittle.UITextInputEvent", {
name : "ALittle.UITextInputEvent", ns_name : "ALittle", rl_name : "UITextInputEvent", hash_code : -1234078962,
name_list : ["target","text","custom"],
type_list : ["ALittle.DisplayObject","string","bool"],
option_map : {}
})
ALittle.RegStruct(1213009422, "ALittle.UIKeyUpEvent", {
name : "ALittle.UIKeyUpEvent", ns_name : "ALittle", rl_name : "UIKeyUpEvent", hash_code : 1213009422,
name_list : ["target","mod","sym","scancode","custom","handled"],
type_list : ["ALittle.DisplayObject","int","int","int","bool","bool"],
option_map : {}
})
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name : "ALittle.UIMoveOutEvent", ns_name : "ALittle", rl_name : "UIMoveOutEvent", hash_code : -1202439334,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1001723540, "ALittle.UIMouseMoveEvent", {
name : "ALittle.UIMouseMoveEvent", ns_name : "ALittle", rl_name : "UIMouseMoveEvent", hash_code : -1001723540,
name_list : ["target","abs_x","abs_y","rel_x","rel_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name : "ALittle.UIChangedEvent", ns_name : "ALittle", rl_name : "UIChangedEvent", hash_code : 958494922,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(882286932, "ALittle.UIKeyEvent", {
name : "ALittle.UIKeyEvent", ns_name : "ALittle", rl_name : "UIKeyEvent", hash_code : 882286932,
name_list : ["target","mod","sym","scancode","custom","handled"],
type_list : ["ALittle.DisplayObject","int","int","int","bool","bool"],
option_map : {}
})
ALittle.RegStruct(-644464135, "ALittle.UIFocusInEvent", {
name : "ALittle.UIFocusInEvent", ns_name : "ALittle", rl_name : "UIFocusInEvent", hash_code : -644464135,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name : "ALittle.UIMoveInEvent", ns_name : "ALittle", rl_name : "UIMoveInEvent", hash_code : 544684311,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-338112738, "ALittle.UIDropFileEvent", {
name : "ALittle.UIDropFileEvent", ns_name : "ALittle", rl_name : "UIDropFileEvent", hash_code : -338112738,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
option_map : {}
})
ALittle.RegStruct(292776509, "ALittle.UIFocusOutEvent", {
name : "ALittle.UIFocusOutEvent", ns_name : "ALittle", rl_name : "UIFocusOutEvent", hash_code : 292776509,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name : "ALittle.UIButtonDragEndEvent", ns_name : "ALittle", rl_name : "UIButtonDragEndEvent", hash_code : 150587926,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})

let List_Insert = ALittle.List_Insert;
let List_Splice = ALittle.List_Splice;
if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
AUIPlugin.AUICodeEdit = JavaScript.Class(ALittle.DisplayLayout, {
	Create : function() {
		return AUIPlugin.g_Control.CreateControl("code_tab_screen");
	},
	Ctor : function(ctrl_sys) {
		this._editable = true;
		this._in_query_info = false;
		this._move_in = false;
		this._line_list = [];
		this._line_count = 0;
		this._in_drag = false;
		this._force_query_error = false;
		this._complete_screen = ALittle.NewObject(AUIPlugin.AUICodeCompleteScreen, this);
		this._param_dialog = ALittle.NewObject(AUIPlugin.AUICodeParamList, this);
	},
	TCtor : function() {
		this._code_screen.AddEventListener(___all_struct.get(-644464135), this, this.HandleFocusIn);
		this._code_screen.AddEventListener(___all_struct.get(292776509), this, this.HandleFocusOut);
		this._code_screen.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this._code_screen.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this._code_screen.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this._code_screen.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		this._code_screen.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this._code_screen.AddEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
		this._code_screen.AddEventListener(___all_struct.get(-1604617962), this, this.HandleKeyDown);
		this._code_screen.AddEventListener(___all_struct.get(1213009422), this, this.HandleKeyUp);
		this._code_screen.AddEventListener(___all_struct.get(-1234078962), this, this.HandleTextInput);
		this._code_screen.AddEventListener(___all_struct.get(-1001723540), this, this.HandleMouseMove);
		this._code_screen.AddEventListener(___all_struct.get(-338112738), this, this.HandleDropFile);
		this._code_screen.EnableDrag(false);
		this.AddEventListener(___all_struct.get(958494922), this, this.HandleChangedEvent);
		this._find_dialog.visible = false;
		this._find_dialog.close_callback = this.HandleFindDialogClose.bind(this);
		this._gotoline_dialog.visible = false;
		this._error_btn.visible = false;
		this._code_screen.container = ALittle.NewObject(AUIPlugin.AUICodeEditContainer, this._ctrl_sys);
		this._edit_quad._user_data = this;
		this._goto_quad.visible = false;
		this._code_screen.container._user_data = this._code_linear;
		this._line_number = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
		this._line_number.type = 2;
		this._line_number.width = AUIPlugin.CODE_LINE_NUMBER_WIDTH;
		this._code_screen.static_object_v = this._line_number;
		this._cursor = ALittle.NewObject(AUIPlugin.AUICodeCursor, this._ctrl_sys, this);
		this._cursor.width = 1;
		this._cursor.height = AUIPlugin.CODE_LINE_HEIGHT;
		this._cursor_container.AddChild(this._cursor);
		this._cursor.disabled = true;
		this._cursor.Hide();
		this._select_cursor = ALittle.NewObject(AUIPlugin.AUICodeSelectCursor, this);
		this._text_show = ALittle.NewObject(ALittle.Text, this._ctrl_sys);
		this._text_show.font_path = AUIPlugin.CODE_FONT_PATH;
		this._text_show.font_size = AUIPlugin.CODE_FONT_SIZE;
		this._ascii_width = this._text_show.native_show.CalcTextWidth("A");
		this._word_width = this._text_show.native_show.CalcTextWidth("测");
	},
	get is_input() {
		return true;
	},
	get editable() {
		return this._editable;
	},
	set editable(value) {
		this._editable = value;
		this._edit_quad.editable = value;
	},
	get cursor_x() {
		return this._edit_quad.cursor_x;
	},
	get cursor_y() {
		return this._edit_quad.cursor_y;
	},
	get cursor_b() {
		return this._edit_quad.cursor_b;
	},
	get code_screen() {
		return this._code_screen;
	},
	get code_linear() {
		return this._code_linear;
	},
	get cursor() {
		return this._cursor;
	},
	get select_cursor() {
		return this._select_cursor;
	},
	get language() {
		return this._language;
	},
	get ascii_width() {
		return this._ascii_width;
	},
	get word_width() {
		return this._word_width;
	},
	set line_count(count) {
		this._line_count = count;
	},
	get line_count() {
		return this._line_count;
	},
	get line_list() {
		return this._line_list;
	},
	get revoke_list() {
		return this._revoke_list;
	},
	get help_container() {
		return this._help_container;
	},
	DispatchJumpEvent : function() {
		let event = {};
		event.file_path = this._file_path;
		event.it_line = this._cursor.line;
		event.it_char = this._cursor.char;
		this.DispatchEvent(___all_struct.get(-1898137181), event);
	},
	get file_path() {
		return this._file_path;
	},
	GetBreakPoint : function(line_number) {
		if (this._break_points === undefined) {
			return false;
		}
		return this._break_points.get(line_number);
	},
	AddBreakPoint : function(line_number) {
		if (this._break_points === undefined) {
			this._break_points = new Map();
		}
		this._break_points.set(line_number, true);
		let break_event = {};
		break_event.file_path = this._file_path;
		break_event.file_line = line_number;
		break_event.add_or_remove = true;
		this.DispatchEvent(___all_struct.get(1575183661), break_event);
	},
	RemoveBreakPoint : function(line_number) {
		if (this._break_points === undefined) {
			this._break_points = new Map();
		}
		this._break_points.set(line_number, false);
		let break_event = {};
		break_event.file_path = this._file_path;
		break_event.file_line = line_number;
		break_event.add_or_remove = false;
		this.DispatchEvent(___all_struct.get(1575183661), break_event);
	},
	FocusLineCharToCenter : function(it_line, it_char) {
		let line = this._line_list[it_line - 1];
		if (line === undefined) {
			return false;
		}
		let char = line.char_list[it_char - 1];
		if (char === undefined) {
			char = line.char_list[1 - 1];
		}
		if (char === undefined) {
			return false;
		}
		let y = (it_line - 1) * AUIPlugin.CODE_LINE_HEIGHT;
		let x = char.pre_width;
		let real_width = this._code_screen.container.width - this._code_screen.view_width;
		if (real_width > 0) {
			if (this._cursor.x <= -this._code_screen.container_x || this._cursor.x >= -this._code_screen.container_x + this._code_screen.view_width) {
				let view_x = this._code_screen.view_width / 2;
				let center_x = x;
				this._code_screen.bottom_scrollbar.offset_rate = (center_x - view_x) / real_width;
			}
		}
		let real_height = this._code_screen.container.height - this._code_screen.view_height;
		if (real_height > 0) {
			if (this._cursor.y <= -this._code_screen.container_y || this._cursor.y + AUIPlugin.CODE_LINE_HEIGHT >= -this._code_screen.container_y + this._code_screen.view_height) {
				let view_y = this._code_screen.view_height / 2;
				let center_y = y;
				this._code_screen.right_scrollbar.offset_rate = (center_y - view_y) / real_height;
			}
		}
		this._code_screen.AdjustScrollBar();
		return true;
	},
	FocusLineCharToUp : function(it_line, it_char) {
		let line = this._line_list[it_line - 1];
		if (line === undefined) {
			return;
		}
		let real_height = this._code_screen.container.height - this._code_screen.view_height;
		if (real_height > 0) {
			this._code_screen.right_scrollbar.offset_rate = (it_line - 1) * AUIPlugin.CODE_LINE_HEIGHT / real_height;
			this._code_screen.AdjustScrollBar();
		}
	},
	FocusLineCharToDown : function(it_line, it_char) {
		let line = this._line_list[it_line - 1];
		if (line === undefined) {
			return;
		}
		let real_height = this._code_screen.container.height - this._code_screen.view_height;
		if (real_height > 0) {
			this._code_screen.right_scrollbar.offset_rate = (it_line * AUIPlugin.CODE_LINE_HEIGHT - this._code_screen.view_height) / real_height;
			this._code_screen.AdjustScrollBar();
		}
	},
	HandleFocusIn : function(event) {
		ALittle.System_OpenIME();
		this._cursor.Show();
	},
	HandleFocusOut : function(event) {
		ALittle.System_CloseIME();
		this._cursor.Hide();
	},
	HandleMoveIn : function(event) {
		this._move_in = true;
		ALittle.System_SetEditCursor();
	},
	HandleMoveOut : function(event) {
		this.StopQueryInfo();
		this._move_in = false;
		ALittle.System_SetNormalCursor();
	},
	HandleLButtonDown : function(event) {
		let rel_x = event.rel_x;
		let rel_y = event.rel_y;
		if (event.target === this._code_screen) {
			rel_x = rel_x - (this._code_linear.x);
			rel_y = rel_y - (this._code_screen.container_y);
		}
		if (A_UISystem.sym_map.get(1073742049) || A_UISystem.sym_map.get(1073742053)) {
			this._select_cursor.StartLineChar(this._cursor.line, this._cursor.char);
			this._cursor.SetOffsetXY(rel_x, rel_y);
			this._select_cursor.UpdateLineChar(this._cursor.line, this._cursor.char);
		} else {
			this._select_cursor.Hide();
			this._cursor.SetOffsetXY(rel_x, rel_y);
		}
		if (event.count > 1) {
			let [it_start, it_end] = this._cursor.CalcSelectWord();
			if (it_start === undefined) {
				return;
			}
			this._cursor.SetLineChar(this._cursor.line, it_end);
			this._select_cursor.StartLineChar(this._cursor.line, it_start);
			this._select_cursor.UpdateLineChar(this._cursor.line, it_end);
		}
		if (A_UISystem.sym_map.get(1073742048) && this._query_info !== undefined && this._language !== undefined) {
			let [it_line, it_char] = this.CalcLineAndChar(rel_x, rel_y);
			this.DoQueryGoto(it_line, it_char);
			this.StopQueryInfo();
		}
		this._complete_screen.TryHide();
		this._param_dialog.TryHide();
		this._cursor.AdjustShowCursor();
		this.DispatchJumpEvent();
	},
	DoQueryGoto : async function(it_line, it_char) {
		let info = await this._language.QueryGoto(it_line, it_char);
		if (info !== undefined) {
			if (info.file_path === this._file_path) {
				this._cursor.SetLineChar(info.line_start, info.char_start - 1);
				this._select_cursor.StartLineChar(info.line_start, info.char_start - 1);
				this._select_cursor.UpdateLineChar(info.line_end, info.char_end);
				this.FocusLineCharToCenter(this._cursor.line, this._cursor.char);
				this.DispatchJumpEvent();
			} else {
				let goto_event = {};
				goto_event.file_path = info.file_path;
				goto_event.line_start = info.line_start;
				goto_event.char_start = info.char_start;
				goto_event.line_end = info.line_end;
				goto_event.char_end = info.char_end;
				this.DispatchEvent(___all_struct.get(631224630), goto_event);
			}
		}
	},
	HandleDragBegin : function(event) {
		if (this._error_quad_move_in !== undefined) {
			g_AUITool.HideTip();
			this._error_quad_move_in = undefined;
		}
		let rel_x = event.rel_x;
		let rel_y = event.rel_y;
		if (event.target === this._code_screen) {
			rel_x = rel_x - (this._code_linear.x);
			rel_y = rel_y - (this._code_screen.container_y);
		}
		this._in_drag = true;
		this._cursor.SetOffsetXY(rel_x, rel_y);
		this._select_cursor.StartLineChar(this._cursor.line, this._cursor.char);
	},
	HandleDrag : function(event) {
		let rel_x = event.rel_x;
		let rel_y = event.rel_y;
		if (event.target === this._code_screen) {
			rel_x = rel_x - (this._code_linear.x);
			rel_y = rel_y - (this._code_screen.container_y);
		}
		this._cursor.SetOffsetXY(rel_x, rel_y);
		this._select_cursor.UpdateLineChar(this._cursor.line, this._cursor.char);
	},
	HandleDragEnd : function(event) {
		this._select_cursor.TryHide();
		this._in_drag = false;
	},
	HandleMouseMove : function(event) {
		let rel_x = event.rel_x;
		if (event.target === this._code_screen) {
			rel_x = rel_x - (this._code_linear.x);
		}
		if (!this._in_drag) {
			let it_line = ALittle.Math_Floor(event.rel_y / AUIPlugin.CODE_LINE_HEIGHT) + 1;
			let line = this._line_list[it_line - 1];
			if (line !== undefined) {
				let rel_y = event.rel_y - (it_line - 1) * AUIPlugin.CODE_LINE_HEIGHT;
				let [item] = line.container._error.PickUp(rel_x, rel_y);
				if (item !== this._error_quad_move_in) {
					if (this._error_quad_move_in !== undefined) {
						g_AUITool.HideTip();
					}
					this._error_quad_move_in = item;
					if (item !== undefined) {
						let info = item._user_data;
						let [x, y] = item.LocalToGlobal();
						let center_x = x + item.width / 2;
						let center_y = y;
						g_AUITool.ShowTip(info.error);
						let [tip_width, tip_height] = g_AUITool.GetTipSize();
						g_AUITool.MoveTip(center_x - tip_width / 2, center_y - tip_height);
					}
				}
			}
		}
		if (!A_UISystem.sym_map.get(1073742048)) {
			return;
		}
		this.UpdateQueryInfo(rel_x, event.rel_y);
	},
	HandleDropFile : function(event) {
		let goto_event = {};
		goto_event.file_path = event.path;
		this.DispatchEvent(___all_struct.get(631224630), goto_event);
	},
	UpdateLineNumber : function() {
		let child_count = this._line_count + AUIPlugin.CODE_PAD_LINES;
		let delta = this._line_number.child_count - child_count;
		if (delta >= 0 && delta <= 10) {
			return;
		}
		if (delta > 0) {
			this._line_number.SpliceChild(child_count);
			return;
		}
		for (let index = this._line_number.child_count + 1; index <= child_count; index += 1) {
			let text = ALittle.NewObject(AUIPlugin.AUICodeLineNumber, this._ctrl_sys, AUIPlugin.CODE_FONT_PATH, AUIPlugin.CODE_FONT_SIZE, this._ascii_width, this._word_width, this);
			text.height = AUIPlugin.CODE_LINE_HEIGHT;
			text.red = AUIPlugin.CODE_LINE_NUMBER_RED;
			text.green = AUIPlugin.CODE_LINE_NUMBER_GREEN;
			text.blue = AUIPlugin.CODE_LINE_NUMBER_BLUE;
			text.SetLineNumber(index);
			this._line_number.AddChild(text);
		}
	},
	UpdateQueryInfo : async function(x, y) {
		if (this._language === undefined) {
			ALittle.System_SetEditCursor();
			return;
		}
		if (this._in_query_info) {
			if (this._query_info === undefined) {
				ALittle.System_SetEditCursor();
			} else {
				ALittle.System_SetHandCursor();
			}
			return;
		}
		let [it_line, it_char] = this.CalcLineAndChar(x, y);
		this._in_query_info = true;
		let info = await this._language.QueryInfo(it_line, it_char);
		if (this._in_query_info === false || info === undefined) {
			if (this._query_info !== undefined) {
				g_AUITool.HideTip();
				this._goto_quad.visible = false;
				let line_container = this._code_linear.GetChildByIndex(this._query_info.line_start);
				if (line_container !== undefined) {
					line_container.RestoreColor();
				}
				this._query_info = undefined;
			}
			ALittle.System_SetEditCursor();
			return;
		}
		this._in_query_info = false;
		if (this._query_info !== undefined && this._query_info.line_start === info.line_start && this._query_info.char_start === info.char_start && this._query_info.line_end === info.line_end && this._query_info.char_end === info.char_end && this._query_info_version === this._language.version) {
			ALittle.System_SetHandCursor();
			return;
		}
		if (this._query_info !== undefined) {
			g_AUITool.HideTip();
			this._goto_quad.visible = false;
			let line_container = this._code_linear.GetChildByIndex(this._query_info.line_start);
			if (line_container !== undefined) {
				line_container.RestoreColor();
			}
			this._query_info = undefined;
		}
		let line = this._line_list[info.line_start - 1];
		let [quad_x, quad_y] = this._edit_quad.LocalToGlobal();
		let char_end = info.char_end;
		if (line !== undefined && info.line_start !== info.line_end) {
			info.char_end = line.char_count;
		}
		let [rect_x, rect_y, rect_width] = this.CalcRect(info.line_start, info.char_start, char_end);
		if (A_UISystem.mouse_x < quad_x + rect_x || A_UISystem.mouse_x >= quad_x + rect_x + rect_width || A_UISystem.mouse_y < quad_y + rect_y || A_UISystem.mouse_y >= quad_y + rect_y + AUIPlugin.CODE_LINE_HEIGHT) {
			ALittle.System_SetEditCursor();
			return;
		}
		this._query_info_version = this._language.version;
		this._query_info = info;
		let line_container = this._code_linear.GetChildByIndex(info.line_start);
		if (line !== undefined && line_container !== undefined) {
			if (info.line_start === info.line_end) {
				line_container.SetColor(info.char_start, info.char_end, AUIPlugin.CODE_FOCUS_RED, AUIPlugin.CODE_FOCUS_GREEN, AUIPlugin.CODE_FOCUS_BLUE);
			} else {
				line_container.SetColor(info.char_start, line.char_count, AUIPlugin.CODE_FOCUS_RED, AUIPlugin.CODE_FOCUS_GREEN, AUIPlugin.CODE_FOCUS_BLUE);
			}
		}
		g_AUITool.ShowTip(info.info);
		let center_x = rect_x + rect_width / 2 + quad_x;
		let center_y = rect_y + quad_y;
		let [tip_width, tip_height] = g_AUITool.GetTipSize();
		g_AUITool.MoveTip(center_x - tip_width / 2, center_y - tip_height);
		this._goto_quad.x = rect_x;
		this._goto_quad.y = rect_y;
		this._goto_quad.width = rect_width;
		this._goto_quad.height = AUIPlugin.CODE_LINE_HEIGHT;
		this._goto_quad.visible = true;
		ALittle.System_SetHandCursor();
	},
	StopQueryInfo : function() {
		if (this._language === undefined) {
			return;
		}
		this._in_query_info = false;
		this._query_info_version = undefined;
		if (this._query_info !== undefined) {
			let line_container = this._code_linear.GetChildByIndex(this._query_info.line_start);
			if (line_container !== undefined) {
				line_container.RestoreColor();
			}
		}
		g_AUITool.HideTip();
		this._query_info = undefined;
		this._goto_quad.visible = false;
	},
	UpdateErrorInfo : async function() {
		g_AUITool.HideTip();
		this._error_quad_move_in = undefined;
		if (this._error_map !== undefined) {
			for (let [info, _] of this._error_map) {
				if (_ === undefined) continue;
				info.item.RemoveFromParent();
			}
		}
		this._error_map = undefined;
		let list = await this._language.QueryError(this._force_query_error);
		if (list === undefined) {
			this._error_btn.visible = false;
			return;
		}
		this._error_map = new Map();
		let error_count = 0;
		let ___OBJECT_1 = list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let info = ___OBJECT_1[index - 1];
			if (info === undefined) break;
			let item_info = {};
			let item = AUIPlugin.g_Control.CreateControl("code_error_item", item_info);
			let line = this._line_list[info.line_start - 1];
			let char_end = info.char_end;
			if (info.line_start !== info.line_end) {
				info.char_end = line.char_count;
			}
			item_info.info = info;
			let [x, y, width] = this.CalcRect(info.line_start, info.char_start, char_end);
			if (width <= 0) {
				width = this._ascii_width;
			}
			item.x = x;
			item.width = width;
			item.height = AUIPlugin.CODE_LINE_HEIGHT;
			item_info._focus_quad._user_data = info;
			item_info.item = item;
			item_info.info = info;
			item._user_data = info;
			line.container._error.AddChild(item);
			error_count = error_count + (1);
			this._error_map.set(item_info, true);
		}
		this._error_btn.visible = error_count > 0;
	},
	HandleErrorNextClick : function(event) {
		if (this.ErrorNextImpl(this._cursor.line, true)) {
			return;
		}
		this.ErrorNextImpl(1, false);
	},
	ErrorNextImpl : function(start_line, check_cursor) {
		let line_index = start_line;
		while (line_index <= this._line_count) {
			let line = this._line_list[line_index - 1];
			let ___OBJECT_2 = line.container._error.childs;
			for (let index = 1; index <= ___OBJECT_2.length; ++index) {
				let child = ___OBJECT_2[index - 1];
				if (child === undefined) break;
				let info = child._user_data;
				if (!check_cursor || line_index !== this._cursor.line || info.char_start > this._cursor.char + 1) {
					this.EditFocus(info.line_start, info.char_start, undefined, undefined, false);
					return true;
				}
			}
			line_index = line_index + (1);
		}
		return false;
	},
	SetFindInput : function(text) {
		this._find_input.text = text;
		this.HandleFindInputChanged(undefined);
	},
	HandleFindInputChanged : function(event) {
		this.ClearFindInfo();
		let content = this._find_input.text;
		this._find_text = ALittle.String_SplitUTF8(content);
		let find_len = ALittle.List_Len(this._find_text);
		if (find_len === 0) {
			return;
		}
		this._find_map = new Map();
		this._find_quad_container.RemoveAllChild();
		let has_find = false;
		let ___OBJECT_3 = this._line_list;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let line = ___OBJECT_3[index - 1];
			if (line === undefined) break;
			if (line.char_count >= find_len) {
				let char_index = 1;
				while (char_index <= line.char_count) {
					let find = true;
					let ___OBJECT_4 = this._find_text;
					for (let i = 1; i <= ___OBJECT_4.length; ++i) {
						let char = ___OBJECT_4[i - 1];
						if (char === undefined) break;
						if (char !== line.char_list[char_index + i - 1 - 1].char) {
							find = false;
							break;
						}
					}
					if (find) {
						let item = ALittle.NewObject(ALittle.Quad, AUIPlugin.g_Control);
						item.red = AUIPlugin.CODE_FIND_RED;
						item.green = AUIPlugin.CODE_FIND_GREEN;
						item.blue = AUIPlugin.CODE_FIND_BLUE;
						item.x = line.char_list[char_index - 1].pre_width;
						item.width = line.char_list[char_index + find_len - 1].pre_width - line.char_list[char_index - 1].pre_width;
						item.height = AUIPlugin.CODE_LINE_HEIGHT;
						line.container._find.AddChild(item);
						let info = {};
						info._focus_quad = item;
						info.it_char_start = char_index;
						info.it_char_end = char_index + find_len - 1;
						item._user_data = info;
						let highlight_quad = ALittle.NewObject(ALittle.Quad, AUIPlugin.g_Control);
						highlight_quad.width_type = 4;
						highlight_quad.height = 2;
						highlight_quad.red = AUIPlugin.CODE_FIND_RED;
						highlight_quad.green = AUIPlugin.CODE_FIND_GREEN;
						highlight_quad.blue = AUIPlugin.CODE_FIND_BLUE;
						highlight_quad.y = (index - 1) / this.line_count * this._find_quad_container.height;
						this._find_quad_container.AddChild(highlight_quad);
						this._find_map.set(info, highlight_quad);
						char_index = char_index + (find_len);
						has_find = true;
					} else {
						char_index = char_index + (1);
					}
				}
			}
		}
		if (has_find) {
			this.FindNextImpl(this._cursor.line, true);
		}
	},
	HandleFindNextClick : function(event) {
		this.FindNext(undefined);
	},
	FindNext : function(content) {
		if (content !== undefined && this._find_input.text !== content) {
			this.SetFindInput(content);
			return;
		}
		if (this.FindNextImpl(this._cursor.line, true)) {
			return;
		}
		this.FindNextImpl(1, false);
	},
	FindNextImpl : function(start_line, check_cursor) {
		let line_index = start_line;
		while (line_index <= this._line_count) {
			let line = this._line_list[line_index - 1];
			let ___OBJECT_5 = line.container._find.childs;
			for (let index = 1; index <= ___OBJECT_5.length; ++index) {
				let child = ___OBJECT_5[index - 1];
				if (child === undefined) break;
				let info = child._user_data;
				if (!check_cursor || line_index !== this._cursor.line || info.it_char_start > this._cursor.char + 1) {
					this.EditFocus(line_index, info.it_char_start, line_index, info.it_char_end, false);
					return true;
				}
			}
			line_index = line_index + (1);
		}
		return false;
	},
	HandleGotoLineClick : function(evnet) {
		let number = ALittle.Math_ToInt(this._gotoline_input.text);
		if (number === undefined) {
			return;
		}
		if (number > this._line_count) {
			number = this._line_count;
		}
		this.EditFocus(number, 1, undefined, undefined, true);
		this._gotoline_dialog.visible = false;
	},
	HandleGotoLineEscClick : function(event) {
		this._gotoline_dialog.visible = false;
	},
	UpdateLineFind : function(it_line) {
		if (this._find_map === undefined) {
			return;
		}
		let line = this._line_list[it_line - 1];
		if (line === undefined) {
			return;
		}
		let ___OBJECT_6 = line.container._find.childs;
		for (let index = 1; index <= ___OBJECT_6.length; ++index) {
			let child = ___OBJECT_6[index - 1];
			if (child === undefined) break;
			let quad = this._find_map.get(child._user_data);
			this._find_map.delete(child._user_data);
			if (quad !== undefined) {
				this._find_quad_container.RemoveChild(quad);
			}
		}
		line.container._find.RemoveAllChild();
		let find_len = ALittle.List_Len(this._find_text);
		if (find_len === 0) {
			return;
		}
		if (line.char_count < find_len) {
			return;
		}
		let char_index = 1;
		while (char_index <= line.char_count) {
			let find = true;
			let ___OBJECT_7 = this._find_text;
			for (let i = 1; i <= ___OBJECT_7.length; ++i) {
				let char = ___OBJECT_7[i - 1];
				if (char === undefined) break;
				if (char !== line.char_list[char_index + i - 1 - 1].char) {
					find = false;
					break;
				}
			}
			if (find) {
				let item = ALittle.NewObject(ALittle.Quad, AUIPlugin.g_Control);
				item.red = AUIPlugin.CODE_FIND_RED;
				item.green = AUIPlugin.CODE_FIND_GREEN;
				item.blue = AUIPlugin.CODE_FIND_BLUE;
				item.x = line.char_list[char_index - 1].pre_width;
				item.width = line.char_list[char_index + find_len - 1].pre_width - line.char_list[char_index - 1].pre_width;
				item.height = AUIPlugin.CODE_LINE_HEIGHT;
				line.container._find.AddChild(item);
				let info = {};
				info._focus_quad = item;
				info.it_char_start = char_index;
				info.it_char_end = char_index + find_len - 1;
				item._user_data = info;
				let highlight_quad = ALittle.NewObject(ALittle.Quad, AUIPlugin.g_Control);
				highlight_quad.width_type = 4;
				highlight_quad.height = 2;
				highlight_quad.red = AUIPlugin.CODE_FIND_RED;
				highlight_quad.green = AUIPlugin.CODE_FIND_GREEN;
				highlight_quad.blue = AUIPlugin.CODE_FIND_BLUE;
				highlight_quad.y = (it_line - 1) / this.line_count * this._find_quad_container.height;
				this._find_quad_container.AddChild(highlight_quad);
				this._find_map.set(info, highlight_quad);
				char_index = char_index + (find_len);
			} else {
				char_index = char_index + (1);
			}
		}
	},
	HandleFindDialogClose : function() {
		this.HandleFindEscClick(undefined);
		return true;
	},
	HandleFindEscClick : function(event) {
		this._find_dialog.visible = false;
		this.ClearFindInfo();
	},
	ClearFindInfo : function() {
		if (this._find_map !== undefined) {
			for (let [info, _] of this._find_map) {
				if (_ === undefined) continue;
				info._focus_quad.RemoveFromParent();
			}
		}
		this._find_quad_container.RemoveAllChild();
		this._find_map = undefined;
	},
	HandleChangedEvent : function(event) {
		if (this._language === undefined) {
			return;
		}
		let map = this._code_linear.GetShowMap();
		for (let [object, _] of map) {
			if (_ === undefined) continue;
			object.RestoreColor();
		}
		this.StartErrorLoop(false);
	},
	StartErrorLoop : function(force) {
		if (this._language === undefined) {
			return;
		}
		this._force_query_error = force;
		if (this._error_loop === undefined) {
			this._error_loop = ALittle.NewObject(ALittle.LoopTimer, this.UpdateErrorInfo.bind(this), 1000);
		}
		this._error_loop.Stop();
		this._error_loop.Reset();
		this._error_loop.Start();
	},
	CalcLineAndChar : function(x, y) {
		let it_line = ALittle.Math_Floor(y / AUIPlugin.CODE_LINE_HEIGHT) + 1;
		if (it_line < 1) {
			it_line = 1;
		} else if (it_line > this._line_count) {
			it_line = this._line_count;
		}
		let it_char = 0;
		let line = this._line_list[it_line - 1];
		if (line === undefined) {
			return [it_line, it_char];
		}
		if (line.char_count === 0) {
			return [it_line, 0];
		}
		let pre_width = line.char_list[1 - 1].width / 2;
		if (x < line.char_list[1 - 1].width / 2) {
			return [it_line, 0];
		}
		for (let index = 1; index < line.char_count; index += 1) {
			let next_width = pre_width + line.char_list[index - 1].width / 2 + line.char_list[index + 1 - 1].width / 2;
			if (x >= pre_width && x < next_width) {
				return [it_line, index];
			}
			pre_width = next_width;
		}
		let count = line.char_count;
		while (count > 0 && line.char_list[count - 1].width <= 0) {
			-- count;
		}
		return [it_line, count];
	},
	CalcRect : function(it_line, char_start, char_end) {
		let line = this._line_list[it_line - 1];
		if (line === undefined) {
			return [0, 0, 0];
		}
		let y = (it_line - 1) * AUIPlugin.CODE_LINE_HEIGHT;
		let x = 0.0;
		if (line.char_list[char_start - 1] !== undefined) {
			x = line.char_list[char_start - 1].pre_width;
		}
		let width = 0.0;
		let char_e = line.char_list[char_end - 1];
		if (char_e !== undefined) {
			width = char_e.pre_width + char_e.width - x;
		}
		return [x, y, width];
	},
	CalcPosition : function(it_line, it_char, pre) {
		let line = this._line_list[it_line - 1];
		if (line === undefined) {
			return [0, 0];
		}
		let y = (it_line - 1) * AUIPlugin.CODE_LINE_HEIGHT;
		let x = 0.0;
		if (it_char > 0) {
			x = line.char_list[it_char - 1].pre_width;
			if (!pre) {
				x = x + (line.char_list[it_char - 1].width);
			}
		}
		return [x, y];
	},
	BrushColor : function(line_start, char_start, line_end, char_end, red, green, blue) {
		if (line_start === line_end) {
			let line = this._line_list[line_start - 1];
			for (let it_char = char_start + 1; it_char <= char_end; it_char += 1) {
				let char = line.char_list[it_char - 1];
				char.red = red;
				char.green = green;
				char.blue = blue;
				if (char.text !== undefined) {
					char.text.red = red;
					char.text.green = green;
					char.text.blue = blue;
				}
			}
			return;
		}
		for (let it_line = line_start; it_line <= line_end; it_line += 1) {
			let line = this._line_list[it_line - 1];
			if (it_line === line_start) {
				for (let it_char = char_start + 1; it_char <= line.char_count; it_char += 1) {
					let char = line.char_list[it_char - 1];
					char.red = red;
					char.green = green;
					char.blue = blue;
					if (char.text !== undefined) {
						char.text.red = red;
						char.text.green = green;
						char.text.blue = blue;
					}
				}
			} else if (it_line === line_end) {
				for (let it_char = 1; it_char <= char_end; it_char += 1) {
					let char = line.char_list[it_char - 1];
					char.red = red;
					char.green = green;
					char.blue = blue;
					if (char.text !== undefined) {
						char.text.red = red;
						char.text.green = green;
						char.text.blue = blue;
					}
				}
			} else {
				for (let it_char = 1; it_char <= line.char_count; it_char += 1) {
					let char = line.char_list[it_char - 1];
					char.red = red;
					char.green = green;
					char.blue = blue;
					if (char.text !== undefined) {
						char.text.red = red;
						char.text.green = green;
						char.text.blue = blue;
					}
				}
			}
		}
	},
	DeleteSelectText : function() {
		let [result, it_line, it_char] = this._select_cursor.DeleteSelect(true);
		if (result) {
			this._cursor.SetLineChar(it_line, it_char);
		}
		return result;
	},
	HandleTextInput : function(event) {
		if (!this._editable) {
			return;
		}
		let text = this._cursor.virtual_indent + event.text;
		if (this.InsertText(text, true)) {
			if (this._language !== undefined) {
				let auto_pair = this._language.QueryAutoPair(this._cursor.line, this._cursor.char, event.text);
				if (auto_pair !== undefined) {
					if (this._cursor.GetNextCharInLine() !== auto_pair) {
						let old_line = this._cursor.line;
						let old_char = this._cursor.char;
						this.InsertText(auto_pair, true);
						this._cursor.SetLineChar(old_line, old_char);
					}
				} else if (this._language.QueryAutoFormat(event.text)) {
					this.MultiLineFormat(this._cursor.line, this._cursor.line);
				}
			}
			this.DispatchEvent(___all_struct.get(958494922), {});
			if (text !== " ") {
				if (text === ".") {
					this._complete_screen.Hide();
				}
				this._complete_screen.ShowComplete();
			} else {
				this._complete_screen.Hide();
			}
			this._param_dialog.ShowParamList();
		}
	},
	HandleKeyDown : function(event) {
		let is_change = false;
		if (event.sym === 1073741904) {
			if ((event.mod & 0x0003) === 0) {
				if (this._select_cursor.line_start !== undefined) {
					let [it_line, it_char] = this._select_cursor.GetLineCharCloseToHome();
					this._cursor.SetLineChar(it_line, it_char);
					this._select_cursor.Hide();
				} else {
					this._cursor.OffsetLeft((event.mod & 0x00c0) !== 0);
				}
				this._cursor.AdjustShowCursor();
				this._complete_screen.TryHide();
				this._param_dialog.TryHide();
			} else {
				if (this._select_cursor.line_start === undefined) {
					this._select_cursor.StartLineChar(this._cursor.line, this._cursor.char);
				}
				this._cursor.OffsetLeft((event.mod & 0x00c0) !== 0);
				if (this._cursor.line === this._select_cursor.line_start && this._cursor.char === this._select_cursor.char_start) {
					this._cursor.OffsetLeft((event.mod & 0x00c0) !== 0);
				}
				this._select_cursor.UpdateLineChar(this._cursor.line, this._cursor.char);
				this._complete_screen.Hide();
				this._param_dialog.Hide();
			}
			event.handled = true;
		} else if (event.sym === 1073741906) {
			if (this._complete_screen.IsShow()) {
				this._complete_screen.SelectUp();
			} else {
				if ((event.mod & 0x0003) === 0) {
					if (this._select_cursor.line_start !== undefined) {
						let [it_line, it_char] = this._select_cursor.GetLineCharCloseToHome();
						this._cursor.SetLineChar(it_line, it_char);
						this._select_cursor.Hide();
					} else {
						this._cursor.OffsetUp();
					}
					this._cursor.AdjustShowCursor();
				} else {
					if (this._select_cursor.line_start === undefined) {
						this._select_cursor.StartLineChar(this._cursor.line, this._cursor.char);
					}
					this._cursor.OffsetUp();
					if (this._cursor.line === this._select_cursor.line_start && this._cursor.char === this._select_cursor.char_start) {
						this._cursor.OffsetUp();
					}
					this._select_cursor.UpdateLineChar(this._cursor.line, this._cursor.char);
				}
				let offset_y = this._cursor.y + this._code_screen.container_y;
				if (offset_y < 0) {
					this.FocusLineCharToUp(this._cursor.line, this._cursor.char);
				}
				this._complete_screen.Hide();
				this._param_dialog.Hide();
			}
			event.handled = true;
		} else if (event.sym === 1073741905) {
			if (this._complete_screen.IsShow()) {
				this._complete_screen.SelectDown();
			} else {
				if ((event.mod & 0x0003) === 0) {
					if (this._select_cursor.line_start !== undefined) {
						let [it_line, it_char] = this._select_cursor.GetLineCharCloseToEnd();
						this._cursor.SetLineChar(it_line, it_char);
						this._select_cursor.Hide();
					} else {
						this._cursor.OffsetDown();
					}
					this._cursor.AdjustShowCursor();
				} else {
					if (this._select_cursor.line_start === undefined) {
						this._select_cursor.StartLineChar(this._cursor.line, this._cursor.char);
					}
					this._cursor.OffsetDown();
					if (this._cursor.line === this._select_cursor.line_start && this._cursor.char === this._select_cursor.char_start) {
						this._cursor.OffsetDown();
					}
					this._select_cursor.UpdateLineChar(this._cursor.line, this._cursor.char);
				}
				let offset_y = this._cursor.y + this._cursor.height + this._code_screen.container_y;
				if (offset_y > this._code_screen.view_height) {
					this.FocusLineCharToDown(this._cursor.line, this._cursor.char);
				}
				this._complete_screen.Hide();
				this._param_dialog.Hide();
			}
			event.handled = true;
		} else if (event.sym === 1073741903) {
			if ((event.mod & 0x0003) === 0) {
				if (this._select_cursor.line_start !== undefined) {
					let [it_line, it_char] = this._select_cursor.GetLineCharCloseToEnd();
					this._cursor.SetLineChar(it_line, it_char);
					this._select_cursor.Hide();
				} else {
					this._cursor.OffsetRight((event.mod & 0x00c0) !== 0);
				}
				this._cursor.AdjustShowCursor();
				this._complete_screen.TryHide();
				this._param_dialog.TryHide();
			} else {
				if (this._select_cursor.line_start === undefined) {
					this._select_cursor.StartLineChar(this._cursor.line, this._cursor.char);
				}
				this._cursor.OffsetRight((event.mod & 0x00c0) !== 0);
				if (this._cursor.line === this._select_cursor.line_start && this._cursor.char === this._select_cursor.char_start) {
					this._cursor.OffsetRight((event.mod & 0x00c0) !== 0);
				}
				this._select_cursor.UpdateLineChar(this._cursor.line, this._cursor.char);
				this._complete_screen.Hide();
				this._param_dialog.Hide();
			}
			event.handled = true;
		} else if (event.sym === 8) {
			if (this._editable) {
				if (this._select_cursor.line_start === undefined) {
					is_change = this._cursor.DeleteLeft(true);
					this._cursor.AdjustShowCursor();
					this._complete_screen.TryHide();
					if (this._complete_screen.IsShow()) {
						this._complete_screen.ShowComplete();
					}
					this._param_dialog.TryHide();
					if (this._param_dialog.IsShow()) {
						this._param_dialog.ShowParamList();
					}
				} else {
					is_change = this.DeleteSelectText();
					this._complete_screen.Hide();
					this._param_dialog.Hide();
				}
				event.handled = true;
			}
		} else if (event.sym === 127) {
			if (this._editable) {
				if (this._select_cursor.line_start === undefined) {
					is_change = this._cursor.DeleteRight(true);
				} else {
					is_change = this.DeleteSelectText();
				}
				event.handled = true;
			}
		} else if (event.sym === 1073741898) {
			if ((event.mod & 0x0003) === 0) {
				if (this._select_cursor.line_start !== undefined) {
					let [it_line, it_char] = this._select_cursor.GetLineCharCloseToHome();
					this._cursor.SetLineChar(it_line, it_char);
					this._select_cursor.Hide();
				} else {
					this._cursor.OffsetHome();
				}
				this._complete_screen.TryHide();
				this._param_dialog.TryHide();
			} else {
				if (this._select_cursor.line_start === undefined) {
					this._select_cursor.StartLineChar(this._cursor.line, this._cursor.char);
				}
				this._cursor.OffsetHome();
				this._select_cursor.UpdateLineChar(this._cursor.line, this._cursor.char);
				this._complete_screen.Hide();
				this._param_dialog.Hide();
			}
			event.handled = true;
		} else if (event.sym === 1073741901) {
			if ((event.mod & 0x0003) === 0) {
				if (this._select_cursor.line_start !== undefined) {
					let [it_line, it_char] = this._select_cursor.GetLineCharCloseToEnd();
					this._cursor.SetLineChar(it_line, it_char);
					this._select_cursor.Hide();
				} else {
					this._cursor.OffsetEnd();
				}
				this._complete_screen.TryHide();
				this._param_dialog.TryHide();
			} else {
				if (this._select_cursor.line_start === undefined) {
					this._select_cursor.StartLineChar(this._cursor.line, this._cursor.char);
				}
				this._cursor.OffsetEnd();
				this._select_cursor.UpdateLineChar(this._cursor.line, this._cursor.char);
				this._complete_screen.Hide();
				this._param_dialog.Hide();
			}
			event.handled = true;
		} else if (event.sym === 13 || event.sym === 1073741912) {
			if (this._editable) {
				if (this._complete_screen.IsShow()) {
					is_change = this._complete_screen.DoSelect();
				} else {
					let old_line = this._cursor.line;
					let old_char = this._cursor.char;
					let revoke_bind = ALittle.NewObject(ALittle.RevokeBind);
					is_change = this.InsertText("\n", true, revoke_bind);
					if (this._cursor.CurLineHasChar()) {
						this._cursor.UpdateVirtualIndent();
						let text = this._cursor.virtual_indent;
						if (text !== "") {
							is_change = this.InsertText(text, true, revoke_bind);
						}
						if (this._cursor.GetCurCharInLine() === "}") {
							this._cursor.SetLineChar(old_line, old_char);
							is_change = this.InsertText("\n", true, revoke_bind);
							this._cursor.AdjustShowCursor();
						}
					} else {
						this._cursor.AdjustShowCursor();
					}
					revoke_bind.complete = this.DispatchChangedEvent.bind(this);
					this._revoke_list.PushRevoke(revoke_bind);
				}
				event.handled = true;
			}
		} else if (event.sym === 9) {
			if (this._editable) {
				if (this._select_cursor.line_start !== this._select_cursor.line_end) {
					if ((event.mod & 0x0003) !== 0) {
						is_change = this.MultiTabDelete(true);
					} else {
						is_change = this.MultiTabInsert(true);
					}
				} else {
					let text = this._cursor.virtual_indent + "\t";
					is_change = this.InsertText(text, true);
				}
				this._complete_screen.Hide();
				this._param_dialog.Hide();
				event.handled = true;
			}
		} else if (event.sym === 120 && event.mod & 0x00c0 !== 0) {
			if (this._editable) {
				let select_text = this._select_cursor.GetSelectText();
				if (select_text !== undefined) {
					ALittle.System_SetClipboardText(select_text);
				}
				is_change = this.DeleteSelectText();
				this._complete_screen.Hide();
				this._param_dialog.Hide();
				event.handled = true;
			}
		} else if (event.sym === 99 && event.mod & 0x00c0 !== 0) {
			let select_text = this._select_cursor.GetSelectText();
			if (select_text !== undefined) {
				ALittle.System_SetClipboardText(select_text);
			}
			event.handled = true;
		} else if (event.sym === 118 && event.mod & 0x00c0 !== 0) {
			if (this._editable) {
				if (ALittle.System_HasClipboardText()) {
					let old_line = this._cursor.line;
					is_change = this.InsertText(ALittle.System_GetClipboardText(), true);
					let new_line = this._cursor.line;
					this._complete_screen.Hide();
					this._param_dialog.Hide();
					this.MultiLineFormat(old_line, new_line);
				}
				event.handled = true;
			}
		} else if (event.sym === 97 && event.mod & 0x00c0 !== 0) {
			if (this._line_count > 0) {
				this._cursor.SetLineChar(this._line_count, this._line_list[this._line_count - 1].char_count);
				this._select_cursor.StartLineChar(1, 0);
				this._select_cursor.UpdateLineChar(this._cursor.line, this._cursor.char);
				this._complete_screen.Hide();
				this._param_dialog.Hide();
			}
			event.handled = true;
		} else if (event.sym === 102 && event.mod & 0x00c0 !== 0) {
			this._find_dialog.visible = true;
			this._find_input.DelayFocus();
			this._find_input.SelectAll();
		} else if (event.sym === 103 && event.mod & 0x00c0 !== 0) {
			this._gotoline_dialog.visible = true;
			this._gotoline_input.DelayFocus();
			this._gotoline_input.SelectAll();
		} else if (event.sym === 1073742048) {
			if (this._move_in && !this._in_query_info) {
				let [x, y] = this._edit_quad.LocalToGlobal();
				this.UpdateQueryInfo(A_UISystem.mouse_x - x, A_UISystem.mouse_y - y);
			}
		} else if (event.sym === 27) {
			if (this._find_dialog !== undefined && this._find_dialog.visible) {
				this._find_dialog.visible = false;
				event.handled = true;
			}
			if (this._gotoline_dialog !== undefined && this._gotoline_dialog.visible) {
				this._gotoline_dialog.visible = false;
				event.handled = true;
			}
		} else if (event.sym === 1073741893) {
			this.DoQueryGoto(this._cursor.line, this._cursor.char);
			this.StopQueryInfo();
			event.handled = true;
		}
		if (is_change) {
			this.DispatchEvent(___all_struct.get(958494922), {});
		}
	},
	DispatchChangedEvent : function() {
		this.DispatchEvent(___all_struct.get(958494922), {});
	},
	HandleKeyUp : function(event) {
		if (event.sym === 1073742048) {
			if (this._move_in) {
				ALittle.System_SetEditCursor();
				this.StopQueryInfo();
			} else {
				ALittle.System_SetNormalCursor();
			}
		}
	},
	OnUnDo : function() {
		this._complete_screen.Hide();
		this._param_dialog.Hide();
	},
	OnTabRightMenu : function(menu) {
		if (this._language !== undefined) {
			this._language.OnTabRightMenu(menu);
		}
	},
	OnHide : function() {
		this._cursor.Hide();
		if (this._language !== undefined) {
			this._language.OnHide();
		}
	},
	OnShow : function() {
		this._edit_quad.DelayFocus();
		if (this._language !== undefined) {
			this._language.OnShow();
		}
		this.StartErrorLoop(true);
	},
	OnSave : function() {
		if (this._language !== undefined) {
			this._language.OnSave();
		}
	},
	OnClose : function() {
		if (this._error_loop !== undefined) {
			this._error_loop.Stop();
			this._error_loop = undefined;
		}
		this._cursor.Hide();
		this._file_path = undefined;
		ALittle.System_CloseIME();
		if (this._language !== undefined) {
			this._language.OnClose();
		}
	},
	Load : function(file_path, content, revoke_list, language, break_points) {
		this._language = language;
		if (break_points !== undefined) {
			this._break_points = new Map();
			let ___OBJECT_8 = break_points;
			for (let index = 1; index <= ___OBJECT_8.length; ++index) {
				let value = ___OBJECT_8[index - 1];
				if (value === undefined) break;
				this._break_points.set(value, true);
			}
		}
		let upper_ext = ALittle.File_GetFileExtByPathAndUpper(file_path);
		if (this._language === undefined && upper_ext === "ABNF") {
			this._language = ALittle.NewObject(AUIPlugin.AUICodeABnf, undefined, file_path);
		}
		if (this._language === undefined && AUIPlugin.AUICodeProject.SupportUpperExt(upper_ext)) {
			this._language = ALittle.NewObject(AUIPlugin.AUICodeCommon, undefined, file_path);
		}
		if (this._language !== undefined) {
			this._language.OnOpen(content);
		}
		if (content === undefined) {
			content = ALittle.File_ReadTextFromStdFile(file_path);
		}
		if (content === undefined) {
			return false;
		}
		this.SetText(content);
		this._file_path = file_path;
		this._revoke_list = revoke_list;
		if (this._revoke_list === undefined) {
			this._revoke_list = ALittle.NewObject(ALittle.RevokeList, 10000);
		}
		return true;
	},
	CreateLines : function(content) {
		let line_list = [];
		let line_count = 0;
		let max_width = 0.0;
		let line = undefined;
		let len = ALittle.String_Len(content);
		let index = 1;
		let pre_width = 0.0;
		let UTF8ByteCount = carp.UTF8ByteCount;
		let sub = lua.String.sub;
		let ascii_width = this._ascii_width;
		let word_width = this._word_width;
		while (index <= len) {
			let is_asicc = true;
			let byte_count = 1;
			let char_text = undefined;
			{
				let code = content.charCodeAt(index - 1);
				if (code > 255) {
					is_asicc = false;
				}
				char_text = content.substring(index - 1, index);
			}
			index = index + (byte_count);
			let char = {};
			if (is_asicc) {
				if (char_text === "\t") {
					char.width = ascii_width * 4;
				} else if (char_text === "\r" || char_text === "\n") {
					char.width = 0;
				} else {
					char.width = ascii_width;
				}
			} else {
				char.width = word_width;
			}
			char.red = AUIPlugin.CODE_FONT_RED;
			char.green = AUIPlugin.CODE_FONT_GREEN;
			char.blue = AUIPlugin.CODE_FONT_BLUE;
			char.char = char_text;
			char.pre_width = pre_width;
			pre_width = pre_width + (char.width);
			if (line === undefined) {
				line = {};
				line.edit = this;
				line.char_count = 0;
				line.char_list = [];
				line.container = ALittle.NewObject(AUIPlugin.AUICodeLineContainer, AUIPlugin.g_Control);
				line.container._user_data = line;
				line.container.height = AUIPlugin.CODE_LINE_HEIGHT;
			}
			line.char_count = line.char_count + (1);
			line.char_list[line.char_count - 1] = char;
			if (char_text === "\n") {
				line_count = line_count + (1);
				line_list[line_count - 1] = line;
				line = undefined;
				pre_width = 0;
			}
		}
		if (line !== undefined) {
			line_count = line_count + (1);
			line_list[line_count - 1] = line;
		}
		let last_line = line_list[line_count - 1];
		if (last_line === undefined) {
			return [line_list, line_count, max_width];
		}
		let last_char = last_line.char_list[last_line.char_count - 1];
		if (last_char === undefined) {
			return [line_list, line_count, max_width];
		}
		if (last_char.char === "\n") {
			line = {};
			line.edit = this;
			line.char_count = 0;
			line.char_list = [];
			line.container = ALittle.NewObject(AUIPlugin.AUICodeLineContainer, AUIPlugin.g_Control);
			line.container._user_data = line;
			line.container.height = AUIPlugin.CODE_LINE_HEIGHT;
			line_count = line_count + (1);
			line_list[line_count - 1] = line;
		}
		let ___OBJECT_9 = line_list;
		for (let i = 1; i <= ___OBJECT_9.length; ++i) {
			let line_info = ___OBJECT_9[i - 1];
			if (line_info === undefined) break;
			last_char = line_info.char_list[line_info.char_count - 1];
			if (last_char !== undefined) {
				line_info.container.width = last_char.pre_width + last_char.width;
			}
			if (line_info.container.width > max_width) {
				max_width = line_info.container.width;
			}
		}
		return [line_list, line_count, max_width];
	},
	SetText : function(content) {
		this._code_linear.RemoveAllChild();
		let max_width = 0.0;
		[this._line_list, this._line_count, max_width] = this.CreateLines(content);
		let ___OBJECT_10 = this._line_list;
		for (let index = 1; index <= ___OBJECT_10.length; ++index) {
			let line = ___OBJECT_10[index - 1];
			if (line === undefined) break;
			this._code_linear.AddChild(line.container);
		}
		this.AdjustCodeScreen(max_width);
		this._cursor.SetLineChar(1, 0);
		if (this._language !== undefined) {
			this._language.SetText(content);
		}
		this.UpdateLineNumber();
	},
	AdjustCodeScreen : function(max_width) {
		this._code_screen.container.width = max_width + AUIPlugin.CODE_LINE_NUMBER_WIDTH;
		this._code_screen.container.height = this._line_count * AUIPlugin.CODE_LINE_HEIGHT + AUIPlugin.CODE_PAD_LINES * AUIPlugin.CODE_LINE_HEIGHT;
		this._code_screen.AdjustScrollBar();
	},
	MultiTabInsert : function(need_revoke, revoke_bind) {
		let insert_revoke = undefined;
		if (need_revoke) {
			if (revoke_bind !== undefined) {
				insert_revoke = revoke_bind;
			} else {
				insert_revoke = ALittle.NewObject(ALittle.RevokeBind);
			}
		}
		if (this._select_cursor.line_start === undefined || this._select_cursor.line_end === undefined) {
			return false;
		}
		let old_line_start = this._select_cursor.line_start;
		let old_char_start = this._select_cursor.char_start;
		let old_line_end = this._select_cursor.line_end;
		let old_char_end = this._select_cursor.char_end;
		let old_line = this._cursor.line;
		let old_char = this._cursor.char;
		let line_min = this._select_cursor.line_start;
		let line_max = this._select_cursor.line_end;
		if (line_min > line_max) {
			let temp = line_min;
			line_min = line_max;
			line_max = temp;
		}
		for (let index = line_min; index <= line_max; index += 1) {
			if (this._language !== undefined) {
				this._language.InsertText("    ", index, 1);
			}
			let line = this._line_list[index - 1];
			let ___OBJECT_11 = line.char_list;
			for (let char_index = 1; char_index <= ___OBJECT_11.length; ++char_index) {
				let char = ___OBJECT_11[char_index - 1];
				if (char === undefined) break;
				char.pre_width = char.pre_width + (this._ascii_width * 4);
				if (char.text !== undefined) {
					char.text.x = char.text.x + (this._ascii_width * 4);
				}
			}
			line.container.width = line.container.width + (this._ascii_width * 4);
			for (let i = 1; i <= 4; i += 1) {
				let char = {};
				char.pre_width = (i - 1) * this._ascii_width;
				char.char = " ";
				char.width = this._ascii_width;
				List_Insert(line.char_list, i, char);
			}
			line.char_count = line.char_count + (4);
		}
		let max_width = 0.0;
		let ___OBJECT_12 = this._line_list;
		for (let index = 1; index <= ___OBJECT_12.length; ++index) {
			let line = ___OBJECT_12[index - 1];
			if (line === undefined) break;
			if (line.container.width > max_width) {
				max_width = line.container.width;
			}
		}
		this._code_screen.container.width = max_width + AUIPlugin.CODE_LINE_NUMBER_WIDTH;
		this._code_screen.AdjustScrollBar();
		this._cursor.SetLineChar(old_line, old_char + 4);
		this._select_cursor.StartLineChar(old_line_start, old_char_start + 4);
		this._select_cursor.UpdateLineChar(old_line_end, old_char_end + 4);
		if (this._find_map !== undefined) {
			for (let index = line_min; index <= line_max; index += 1) {
				this.UpdateLineFind(index);
			}
		}
		if (need_revoke) {
			let revoke = ALittle.NewObject(AUIPlugin.AUICodeMultiTabInsertRevoke, this, this._cursor, this._select_cursor, old_line_start, old_char_start, old_line_end, old_char_end, this._select_cursor.line_start, this._select_cursor.char_start, this._select_cursor.line_end, this._select_cursor.char_end, revoke_bind === undefined);
			insert_revoke.PushRevoke(revoke);
			if (revoke_bind === undefined) {
				this._revoke_list.PushRevoke(insert_revoke);
			}
		}
		return true;
	},
	MultiLineFormat : function(line_start, line_end) {
		if (this._language === undefined || !this._language.NeedAutoFormat()) {
			return;
		}
		if (line_start > line_end) {
			let temp = line_start;
			line_start = line_end;
			line_end = temp;
		}
		let old_line = this._cursor.line;
		let old_char = this._cursor.char;
		let revoke_bind = ALittle.NewObject(ALittle.RevokeBind);
		let old_indent_list = new Map();
		let indent_list = new Map();
		let delete_list = new Map();
		for (let index = line_start; index <= line_end; index += 1) {
			let line = this._line_list[index - 1];
			let old_indent = 0;
			let delete_count = 0;
			let ___OBJECT_13 = line.char_list;
			for (let i = 1; i <= ___OBJECT_13.length; ++i) {
				let char = ___OBJECT_13[i - 1];
				if (char === undefined) break;
				if (char.char === " ") {
					old_indent = old_indent + (1);
					delete_count = delete_count + (1);
				} else if (char.char === "\t") {
					old_indent = old_indent + (4);
					delete_count = delete_count + (1);
				} else {
					break;
				}
			}
			old_indent_list.set(index, old_indent);
			delete_list.set(index, delete_count);
			let first_char = line.char_list[1 - 1];
			if (first_char === undefined || first_char.char === "\r" || first_char.char === "\n") {
				indent_list.set(index, 0);
			} else {
				indent_list.set(index, this._language.QueryFormateIndent(index, delete_count));
			}
		}
		let changed = false;
		for (let index = line_start; index <= line_end; index += 1) {
			let line = this._line_list[index - 1];
			let old_indent = old_indent_list.get(index);
			let delete_count = delete_list.get(index);
			let indent = indent_list.get(index);
			if (old_indent !== indent) {
				this._select_cursor.StartLineChar(index, 0);
				this._select_cursor.UpdateLineChar(index, delete_count);
				this._cursor.SetLineChar(index, 0);
				let new_indent = "";
				for (let i = 1; i <= indent; i += 1) {
					new_indent = new_indent + " ";
				}
				this.InsertText(new_indent, true, revoke_bind);
				changed = true;
				if (old_line === index) {
					old_char = old_char + (indent - delete_count);
				}
			}
		}
		if (changed) {
			revoke_bind.complete = this.DispatchChangedEvent.bind(this);
			this._revoke_list.PushRevoke(revoke_bind);
			this._cursor.SetLineChar(old_line, old_char);
		}
	},
	MultiTabDelete : function(need_revoke, revoke_bind) {
		let insert_revoke = undefined;
		if (need_revoke) {
			insert_revoke = ALittle.NewObject(ALittle.RevokeBind);
		}
		if (this._select_cursor.line_start === undefined || this._select_cursor.line_end === undefined) {
			return false;
		}
		let old_line_start = this._select_cursor.line_start;
		let old_char_start = this._select_cursor.char_start;
		let old_line_end = this._select_cursor.line_end;
		let old_char_end = this._select_cursor.char_end;
		let old_line = this._cursor.line;
		let old_char = this._cursor.char;
		let line_min = this._select_cursor.line_start;
		let line_max = this._select_cursor.line_end;
		if (line_min > line_max) {
			let temp = line_min;
			line_min = line_max;
			line_max = temp;
		}
		let changed = false;
		for (let index = line_min; index <= line_max; index += 1) {
			let line = this._line_list[index - 1];
			let delete_count = 0;
			for (let i = 1; i <= 4; i += 1) {
				if (line.char_list[i - 1].char === "\t") {
					if (i === 1) {
						delete_count = 1;
						break;
					} else {
						break;
					}
				} else if (line.char_list[i - 1].char === " ") {
					delete_count = delete_count + (1);
				} else {
					break;
				}
			}
			if (delete_count > 0) {
				changed = true;
				if (this._language !== undefined) {
					this._language.DeleteText(index, 1, index, delete_count);
				}
				let ___OBJECT_14 = line.char_list;
				for (let char_index = 1; char_index <= ___OBJECT_14.length; ++char_index) {
					let char = ___OBJECT_14[char_index - 1];
					if (char === undefined) break;
					char.pre_width = char.pre_width - (this._ascii_width * 4);
					if (char.text !== undefined) {
						char.text.x = char.text.x - (this._ascii_width * 4);
					}
				}
				line.container.width = line.container.width - (this._ascii_width * 4);
				List_Splice(line.char_list, 1, delete_count);
				line.char_count = line.char_count - (delete_count);
				if (index === old_line_start) {
					old_char_start = old_char_start - (delete_count);
				} else if (index === old_line_end) {
					old_char_end = old_char_end - (delete_count);
				}
				if (index === old_line) {
					old_char = old_char - (delete_count);
				}
			}
		}
		if (changed) {
			this._cursor.SetLineChar(old_line, old_char);
			this._select_cursor.StartLineChar(old_line_start, old_char_start);
			this._select_cursor.UpdateLineChar(old_line_end, old_char_end);
			let max_width = 0.0;
			let ___OBJECT_15 = this._line_list;
			for (let index = 1; index <= ___OBJECT_15.length; ++index) {
				let line = ___OBJECT_15[index - 1];
				if (line === undefined) break;
				if (line.container.width > max_width) {
					max_width = line.container.width;
				}
			}
			this._code_screen.container.width = max_width + AUIPlugin.CODE_LINE_NUMBER_WIDTH;
			this._code_screen.AdjustScrollBar();
			if (this._find_map !== undefined) {
				for (let index = line_min; index <= line_max; index += 1) {
					this.UpdateLineFind(index);
				}
			}
			if (need_revoke) {
				let revoke = ALittle.NewObject(AUIPlugin.AUICodeMultiTabDeleteRevoke, this, this._cursor, this._select_cursor, old_line_start, old_char_start, old_line_end, old_char_end, this._select_cursor.line_start, this._select_cursor.char_start, this._select_cursor.line_end, this._select_cursor.char_end, revoke_bind === undefined);
				insert_revoke.PushRevoke(revoke);
				if (revoke_bind === undefined) {
					this._revoke_list.PushRevoke(insert_revoke);
				}
			}
		}
		return true;
	},
	InsertText : function(content, need_revoke, revoke_bind) {
		let insert_revoke = undefined;
		if (need_revoke) {
			if (revoke_bind !== undefined) {
				insert_revoke = revoke_bind;
			} else {
				insert_revoke = ALittle.NewObject(ALittle.RevokeBind);
			}
		}
		let [is_changed, delete_it_line, delete_it_char] = this._select_cursor.DeleteSelect(need_revoke, insert_revoke);
		if (is_changed) {
			this._cursor.SetLineChar(delete_it_line, delete_it_char);
		}
		let [line_list, line_count, max_width] = this.CreateLines(content);
		if (line_count === 0) {
			return is_changed;
		}
		is_changed = true;
		if (this._language !== undefined) {
			this._language.InsertText(content, this._cursor.line, this._cursor.char);
		}
		let old_it_line = this._cursor.line;
		let old_it_char = this._cursor.char;
		let split_pre_line = this._line_list[this._cursor.line - 1];
		let split_it_char = this._cursor.char;
		let line_map = new Map();
		if (split_pre_line === undefined) {
			split_pre_line = {};
			split_pre_line.edit = this;
			split_pre_line.char_count = 0;
			split_pre_line.char_list = [];
			split_pre_line.container = ALittle.NewObject(AUIPlugin.AUICodeLineContainer, AUIPlugin.g_Control);
			split_pre_line.container._user_data = split_pre_line;
			split_pre_line.container.height = AUIPlugin.CODE_LINE_HEIGHT;
			this._code_linear.AddChild(split_pre_line.container);
			this._line_count = this._line_count + (1);
			this._line_list[this._line_count - 1] = split_pre_line;
			line_map.set(this._line_count, true);
		}
		let split_next_line = split_pre_line;
		let it_cursor_line = this._cursor.line;
		let it_cursor_char = this._cursor.char;
		line_map.set(this._cursor.line, true);
		if (line_count > 1) {
			if (line_count <= 20) {
				let this_line_list = this._line_list;
				let this_line_count = this._line_count;
				let new_line_index = this._cursor.line;
				{
					split_next_line = {};
					split_next_line.edit = this;
					split_next_line.char_count = 0;
					split_next_line.char_list = [];
					split_next_line.container = ALittle.NewObject(AUIPlugin.AUICodeLineContainer, AUIPlugin.g_Control);
					split_next_line.container._user_data = split_next_line;
					split_next_line.container.height = AUIPlugin.CODE_LINE_HEIGHT;
					for (let i = this._cursor.char + 1; i <= split_pre_line.char_count; i += 1) {
						split_next_line.char_count = split_next_line.char_count + (1);
						split_next_line.char_list[split_next_line.char_count - 1] = split_pre_line.char_list[i - 1];
						if (split_pre_line.char_list[i - 1].text !== undefined) {
							split_next_line.container.AddChild(split_pre_line.char_list[i - 1].text);
						}
					}
					let split_count = split_pre_line.char_count - this._cursor.char;
					List_Splice(split_pre_line.char_list, this._cursor.char + 1, split_count);
					split_pre_line.char_count = split_pre_line.char_count - (split_count);
				}
				let code_linear = this._code_linear;
				for (let i = 2; i < line_count; i += 1) {
					let line = line_list[i - 1];
					new_line_index = new_line_index + (1);
					code_linear.AddChild(line.container, new_line_index);
					this_line_count = this_line_count + (1);
					List_Insert(this_line_list, new_line_index, line);
					line_map.set(new_line_index, true);
				}
				{
					new_line_index = new_line_index + (1);
					code_linear.AddChild(split_next_line.container, new_line_index);
					List_Insert(this_line_list, new_line_index, split_next_line);
					this_line_count = this_line_count + (1);
					it_cursor_line = new_line_index;
					it_cursor_char = 0;
					line_map.set(new_line_index, true);
				}
				this._line_count = this_line_count;
			} else {
				let this_line_list = this._line_list;
				let this_line_count = this._line_count;
				let new_line_list = [];
				let new_line_count = 0;
				let cursor_line = this._cursor.line;
				this._code_linear.SpliceChild(cursor_line);
				for (let i = 1; i < cursor_line; i += 1) {
					new_line_count = new_line_count + (1);
					new_line_list[new_line_count - 1] = this_line_list[i - 1];
				}
				{
					split_next_line = {};
					split_next_line.edit = this;
					split_next_line.char_count = 0;
					split_next_line.char_list = [];
					split_next_line.container = ALittle.NewObject(AUIPlugin.AUICodeLineContainer, AUIPlugin.g_Control);
					split_next_line.container._user_data = split_next_line;
					split_next_line.container.height = AUIPlugin.CODE_LINE_HEIGHT;
					for (let i = this._cursor.char + 1; i <= split_pre_line.char_count; i += 1) {
						split_next_line.char_count = split_next_line.char_count + (1);
						split_next_line.char_list[split_next_line.char_count - 1] = split_pre_line.char_list[i - 1];
						if (split_pre_line.char_list[i - 1].text !== undefined) {
							split_next_line.container.AddChild(split_pre_line.char_list[i - 1].text);
						}
					}
					let split_count = split_pre_line.char_count - this._cursor.char;
					List_Splice(split_pre_line.char_list, this._cursor.char + 1, split_count);
					split_pre_line.char_count = split_pre_line.char_count - (split_count);
					let result = this._code_linear.AddChild(split_pre_line.container);
					new_line_count = new_line_count + (1);
					new_line_list[new_line_count - 1] = split_pre_line;
				}
				let code_linear = this._code_linear;
				for (let i = 2; i < line_count; i += 1) {
					let line = line_list[i - 1];
					let result = code_linear.AddChild(line.container);
					new_line_count = new_line_count + (1);
					new_line_list[new_line_count - 1] = line;
					line_map.set(new_line_count, true);
				}
				{
					let result = code_linear.AddChild(split_next_line.container);
					new_line_count = new_line_count + (1);
					new_line_list[new_line_count - 1] = split_next_line;
					it_cursor_line = new_line_count;
					it_cursor_char = 0;
					line_map.set(new_line_count, true);
				}
				for (let i = this._cursor.line + 1; i <= this_line_count; i += 1) {
					let line = this_line_list[i - 1];
					code_linear.AddChild(line.container);
					new_line_count = new_line_count + (1);
					new_line_list[new_line_count - 1] = line;
				}
				this._line_list = new_line_list;
				this._line_count = new_line_count;
			}
		}
		if (line_count > 0) {
			let line = line_list[1 - 1];
			let char_list = [];
			let char_count = 0;
			split_pre_line.container._text.RemoveAllChild();
			let pre_width = 0.0;
			for (let i = 1; i <= split_it_char; i += 1) {
				let char = split_pre_line.char_list[i - 1];
				char.pre_width = pre_width;
				if (char.text !== undefined) {
					char.text.x = pre_width;
				}
				split_pre_line.container.AddChar(char);
				char_count = char_count + (1);
				char_list[char_count - 1] = char;
				pre_width = pre_width + (char.width);
			}
			for (let i = 1; i <= line.char_count; i += 1) {
				let char = line.char_list[i - 1];
				char.pre_width = pre_width;
				if (char.text !== undefined) {
					char.text.x = pre_width;
				}
				split_pre_line.container.AddChar(char);
				char_count = char_count + (1);
				char_list[char_count - 1] = char;
				pre_width = pre_width + (char.width);
			}
			if (line_count <= 1) {
				it_cursor_char = char_count;
			}
			for (let i = split_it_char + 1; i <= split_pre_line.char_count; i += 1) {
				let char = split_pre_line.char_list[i - 1];
				char.pre_width = pre_width;
				if (char.text !== undefined) {
					char.text.x = pre_width;
				}
				split_pre_line.container.AddChar(char);
				char_count = char_count + (1);
				char_list[char_count - 1] = char;
				pre_width = pre_width + (char.width);
			}
			split_pre_line.char_count = char_count;
			split_pre_line.char_list = char_list;
			split_pre_line.container.width = pre_width;
		}
		if (line_count > 1) {
			let line = line_list[line_count - 1];
			let char_list = [];
			let char_count = 0;
			split_next_line.container._text.RemoveAllChild();
			let pre_width = 0.0;
			for (let i = 1; i <= line.char_count; i += 1) {
				let char = line.char_list[i - 1];
				char.pre_width = pre_width;
				if (char.text !== undefined) {
					char.text.x = pre_width;
				}
				split_next_line.container.AddChar(char);
				char_count = char_count + (1);
				char_list[char_count - 1] = char;
				pre_width = pre_width + (char.width);
			}
			it_cursor_char = char_count;
			for (let i = 1; i <= split_next_line.char_count; i += 1) {
				let char = split_next_line.char_list[i - 1];
				char.pre_width = pre_width;
				if (char.text !== undefined) {
					char.text.x = pre_width;
				}
				split_next_line.container.AddChar(char);
				char_count = char_count + (1);
				char_list[char_count - 1] = char;
				pre_width = pre_width + (char.width);
			}
			split_next_line.char_count = char_count;
			split_next_line.char_list = char_list;
			split_next_line.container.width = pre_width;
		}
		max_width = 0.0;
		let this_line_list = this._line_list;
		let ___OBJECT_16 = this_line_list;
		for (let index = 1; index <= ___OBJECT_16.length; ++index) {
			let line = ___OBJECT_16[index - 1];
			if (line === undefined) break;
			if (line.container.width > max_width) {
				max_width = line.container.width;
			}
		}
		this._code_screen.container.width = max_width + AUIPlugin.CODE_LINE_NUMBER_WIDTH;
		this._code_screen.container.height = this._line_count * AUIPlugin.CODE_LINE_HEIGHT + AUIPlugin.CODE_PAD_LINES * AUIPlugin.CODE_LINE_HEIGHT;
		this._code_screen.AdjustScrollBar();
		this._cursor.SetLineChar(it_cursor_line, it_cursor_char);
		if (need_revoke) {
			let revoke = ALittle.NewObject(AUIPlugin.AUICodeInsertTextRevoke, this, this._cursor, this._select_cursor, old_it_line, old_it_char, it_cursor_line, it_cursor_char, content, revoke_bind === undefined);
			insert_revoke.PushRevoke(revoke);
			if (revoke_bind === undefined) {
				this._revoke_list.PushRevoke(insert_revoke);
			}
		}
		if (this._find_map !== undefined) {
			for (let [line_index, _] of line_map) {
				if (_ === undefined) continue;
				this.UpdateLineFind(line_index);
			}
		}
		this.UpdateLineNumber();
		return is_changed;
	},
	GetText : function() {
		if (this._file_path === undefined) {
			return "";
		}
		let text_list = [];
		let text_count = 0;
		let ___OBJECT_17 = this._line_list;
		for (let i = 1; i <= ___OBJECT_17.length; ++i) {
			let line = ___OBJECT_17[i - 1];
			if (line === undefined) break;
			let ___OBJECT_18 = line.char_list;
			for (let j = 1; j <= ___OBJECT_18.length; ++j) {
				let char = ___OBJECT_18[j - 1];
				if (char === undefined) break;
				text_count = text_count + (1);
				text_list[text_count - 1] = char.char;
			}
		}
		return ALittle.String_Join(text_list, "");
	},
	GetSelectText : function() {
		return this._select_cursor.GetSelectText();
	},
	GetTargetText : function(line_start, char_start, line_end, char_end) {
		return this._select_cursor.GetTargetText(line_start, char_start, line_end, char_end);
	},
	Save : function() {
		if (this._file_path === undefined) {
			return false;
		}
		let text_list = [];
		let text_count = 0;
		let ___OBJECT_19 = this._line_list;
		for (let i = 1; i <= ___OBJECT_19.length; ++i) {
			let line = ___OBJECT_19[i - 1];
			if (line === undefined) break;
			let ___OBJECT_20 = line.char_list;
			for (let j = 1; j <= ___OBJECT_20.length; ++j) {
				let char = ___OBJECT_20[j - 1];
				if (char === undefined) break;
				text_count = text_count + (1);
				text_list[text_count - 1] = char.char;
			}
		}
		ALittle.File_WriteTextToFile(ALittle.String_Join(text_list, ""), this._file_path);
		this.OnSave();
		return true;
	},
	EditFocus : function(line_start, char_start, line_end, char_end, edit_focus) {
		if (edit_focus) {
			this._edit_quad.DelayFocus();
		}
		if (this._line_count <= 0) {
			this._select_cursor.Hide();
			this._cursor.SetLineChar(1, 0);
			this.FocusLineCharToCenter(this._cursor.line, this._cursor.char);
			return;
		}
		if (line_start === undefined || char_start === undefined) {
			return;
		}
		if (char_start > 0) {
			char_start = char_start - (1);
		}
		if (line_end === undefined || char_end === undefined) {
			this._select_cursor.Hide();
			if (line_start > this._line_count) {
				this._cursor.SetLineChar(1, 0);
				this.FocusLineCharToCenter(this._cursor.line, this._cursor.char);
				return;
			}
			let line = this._line_list[line_start - 1];
			let count = line.char_count;
			while (count > 0 && line.char_list[count - 1].width <= 0) {
				-- count;
			}
			if (char_start > count) {
				char_start = count;
			}
			this._cursor.SetLineChar(line_start, char_start);
			this.FocusLineCharToCenter(this._cursor.line, this._cursor.char);
			return;
		}
		if (line_start > this._line_count || line_end > this._line_count) {
			this._select_cursor.Hide();
			this._cursor.SetLineChar(1, 0);
			this.FocusLineCharToCenter(this._cursor.line, this._cursor.char);
			return;
		}
		{
			let line = this._line_list[line_start - 1];
			let count = line.char_count;
			while (count > 0 && line.char_list[count - 1].width <= 0) {
				-- count;
			}
			if (char_start > count) {
				char_start = count;
			}
		}
		{
			let line = this._line_list[line_end - 1];
			let count = line.char_count;
			while (count > 0 && line.char_list[count - 1].width <= 0) {
				-- count;
			}
			if (char_end > count) {
				char_end = count;
			}
		}
		if (line_start === line_end && char_start === char_end) {
			this._select_cursor.Hide();
			this._cursor.SetLineChar(line_start, char_start);
			this.FocusLineCharToCenter(this._cursor.line, this._cursor.char);
			return;
		}
		this._cursor.SetLineChar(line_start, char_start);
		this._select_cursor.StartLineChar(line_start, char_start);
		this._select_cursor.UpdateLineChar(line_end, char_end);
		this.FocusLineCharToCenter(this._cursor.line, this._cursor.char);
	},
}, "AUIPlugin.AUICodeEdit");

}