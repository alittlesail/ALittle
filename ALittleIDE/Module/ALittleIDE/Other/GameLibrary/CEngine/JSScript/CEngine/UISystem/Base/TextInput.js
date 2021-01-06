{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __type = ALittle.String_Type;
let __tonumber = ALittle.Math_ToDouble;
let __tostring = ALittle.String_ToString;
let __floor = ALittle.Math_Floor;
let __sub = ALittle.String_Sub;
let __find = ALittle.String_Find;
if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.TextInput = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._show = ALittle.NewObject(JavaScript.JTextInput);
		this._cursor_red = 1;
		this._cursor_green = 1;
		this._cursor_blue = 1;
		this._bold = false;
		this._italic = false;
		this._underline = false;
		this._deleteline = false;
		this._password_mode = false;
		this._default_text = "";
		this._default_text_alpha = 1;
		this._flip = 0;
		this._current_flash_alpha = 1;
		this._current_flash_dir = -0.05;
		this._is_selecting = false;
		this._editable = true;
		this._ims_padding = 0;
		this._regex = "";
		this._limit_len = 0;
		this.AddEventListener(___all_struct.get(-644464135), this, this.HandleFocusIn);
		this.AddEventListener(___all_struct.get(292776509), this, this.HandleFocusOut);
		this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this.AddEventListener(___all_struct.get(-1234078962), this, this.HandleTextInput);
		this.AddEventListener(___all_struct.get(-1604617962), this, this.HandleKeyDown);
		this.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		this.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this._move_in = false;
		this._focus_in = false;
		this._show.native.htmlInput.onchange = this.HandleHtmlInputChanged.bind(this);
	},
	HandleHtmlInputChanged : function() {
		this.DispatchEvent(___all_struct.get(958494922), {});
	},
	Redraw : function() {
		this._show.NeedDraw();
	},
	get is_input() {
		return true;
	},
	set default_text(value) {
		this._default_text = value;
		if (this._default_text === undefined) {
			this._default_text = "";
		}
		if (this._show.IsDefaultText()) {
			this._show.SetDefaultText(true, this._default_text);
		}
	},
	get default_text() {
		return this._default_text;
	},
	set default_text_alpha(value) {
		if (this._default_text_alpha === value) {
			return;
		}
		this._default_text_alpha = value;
		this._show.SetDefaultTextAlpha(value);
	},
	get default_text_alpha() {
		return this._default_text_alpha;
	},
	Update : function() {
		if (this._is_selecting === false) {
			this._current_flash_alpha = this._current_flash_alpha + this._current_flash_dir;
			if ((this._current_flash_dir < 0 && this._current_flash_alpha < -0.05) || (this._current_flash_dir > 0 && this._current_flash_alpha > 1.5)) {
				this._current_flash_dir = -this._current_flash_dir;
			}
		} else {
			this._current_flash_alpha = 0.5;
		}
		this._show.SetCursorAlpha(this._current_flash_alpha);
	},
	get cursor_x() {
		return this._show.GetCursorX();
	},
	get cursor_y() {
		return this._show.GetCursorY();
	},
	get cursor_b() {
		return (this._show.GetCursorY() + this._show.GetCursorHeight()) * this.scale_y + this._ims_padding;
	},
	set editable(value) {
		this._editable = value;
	},
	get editable() {
		return this._editable;
	},
	set font_path(value) {
		this._font_path = value;
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this._ctrl_sys.SetFont(this, this._font_path, this._font_size);
	},
	set font_size(value) {
		this._font_size = value;
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this._ctrl_sys.SetFont(this, this._font_path, this._font_size);
	},
	get font_path() {
		return this._font_path;
	},
	get font_size() {
		return this._font_size;
	},
	set text(value) {
		if (value === undefined) {
			return;
		}
		value = __tostring(value);
		this._is_selecting = false;
		if (value === "") {
			if (this._default_text === undefined) {
				this._default_text = "";
			}
			this._show.SetDefaultText(true, this._default_text);
		} else {
			this._show.SetDefaultText(false, "");
			this._show.SetText(value);
		}
	},
	get text() {
		if (this._show.IsDefaultText()) {
			return "";
		}
		return this._show.GetText();
	},
	set bold(value) {
		if (this._bold === value) {
			return;
		}
		this._bold = value;
		this._show.SetBold(value);
	},
	get bold() {
		return this._bold;
	},
	set italic(value) {
		if (this._italic === value) {
			return;
		}
		this._italic = value;
		this._show.SetItalic(value);
	},
	get italic() {
		return this._italic;
	},
	set underline(value) {
		if (this._underline === value) {
			return;
		}
		this._underline = value;
		this._show.SetUnderline(value);
	},
	get underline() {
		return this._underline;
	},
	set deleteline(value) {
		if (this._deleteline === value) {
			return;
		}
		this._deleteline = value;
		this._show.SetDeleteline(value);
	},
	get deleteline() {
		return this._deleteline;
	},
	set password_mode(value) {
		this._is_selecting = false;
		if (this._password_mode === value) {
			return;
		}
		this._password_mode = value;
		this._show.SetPasswordMode(value);
	},
	get password_mode() {
		return this._password_mode;
	},
	set ims_padding(value) {
		this._ims_padding = value;
	},
	get ims_padding() {
		return this._ims_padding;
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
	HandleFocusIn : function(event) {
		this._show.ShowCursor(true);
		if (this._loop === undefined) {
			this._loop = ALittle.NewObject(ALittle.LoopFunction, this.Update.bind(this), -1, 1, 1);
		}
		A_LoopSystem.AddUpdater(this._loop);
		if (this._editable) {
			let [global_x, global_y] = this.LocalToGlobal();
			ALittle.System_SetIMERect(__floor(global_x), __floor(global_y), __floor(this._width * this.scale_x), __floor(this._height * this.scale_y) + this._ims_padding);
			ALittle.System_OpenIME();
		}
		if (this._show.IsDefaultText()) {
			this._show.SetDefaultText(false, "");
		}
		this._focus_in = true;
		this._show.SetDisabled(false);
	},
	HandleFocusOut : function(event) {
		this._focus_in = false;
		this._show.SetDisabled(!this._move_in);
		this._is_selecting = false;
		this._show.ShowCursor(false);
		A_LoopSystem.RemoveUpdater(this._loop);
		ALittle.System_CloseIME();
		if (this.text === "") {
			if (this._default_text === undefined) {
				this._default_text = "";
			}
			this._show.SetDefaultText(true, this._default_text);
		}
	},
	HandleLButtonDown : function(event) {
		if (this._editable) {
			let [global_x, global_y] = this.LocalToGlobal();
			ALittle.System_SetIMERect(__floor(global_x), __floor(global_y), __floor(this._width * this.scale_x), __floor(this._height * this.scale_y) + this._ims_padding);
			ALittle.System_OpenIME();
		}
		if (event.count % 3 === 1) {
			this._is_selecting = false;
			this._show.ClickCursor(event.rel_x, 0.0);
		} else if (event.count % 3 === 2) {
			this._is_selecting = this._show.ClickWordCursor(event.rel_x, 0.0);
		} else {
			this._is_selecting = true;
			this._show.SelectAll();
		}
	},
	CheckTextRegexLimit : function(text) {
		if (this._limit_len > 0) {
			let text_len = ALittle.String_GetWordCount(text);
			if (text_len > this._limit_len) {
				return false;
			}
			let select_len = ALittle.String_GetWordCount(this._show.GetSelectText());
			let total_len = ALittle.String_GetWordCount(this.text);
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
	HandleTextInput : function(event) {
		if (this._editable || event.custom) {
			this._is_selecting = false;
			if (this.CheckTextRegexLimit(event.text) === false) {
				return;
			}
			let is_change = this._show.InsertText(event.text);
			if (is_change) {
				this.DispatchEvent(___all_struct.get(958494922), {});
			}
		}
	},
	HandleKeyDown : function(event) {
		let is_change = false;
		if (event.sym === 1073741904) {
			if (event.mod & 0x0003 === 0) {
				this._is_selecting = false;
				this._show.CursorOffset(true);
			} else {
				this._is_selecting = true;
				this._show.SelectCursorOffset(true);
			}
			event.handled = true;
		} else if (event.sym === 1073741903) {
			if (event.mod & 0x0003 === 0) {
				this._is_selecting = false;
				this._show.CursorOffset(false);
			} else {
				this._is_selecting = true;
				this._show.SelectCursorOffset(false);
			}
			event.handled = true;
		} else if (event.sym === 8) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				is_change = this._show.DeleteText(true);
				event.handled = true;
			}
		} else if (event.sym === 127) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				is_change = this._show.DeleteText(false);
				event.handled = true;
			}
		} else if (event.sym === 1073741898) {
			this._is_selecting = false;
			this._show.SetCursorToHome();
			event.handled = true;
		} else if (event.sym === 1073741901) {
			this._is_selecting = false;
			this._show.SetCursorToEnd();
			event.handled = true;
		} else if (event.sym === 13 || event.sym === 1073741912) {
			if (this._editable || event.custom) {
				this.DispatchEvent(___all_struct.get(776398171), {});
				event.handled = true;
			}
		} else if (event.sym === 120 && event.mod & 0x00c0 !== 0) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				let select_text = this._show.GetSelectText();
				if (select_text !== "" && (!this._password_mode)) {
					ALittle.System_SetClipboardText(select_text);
					is_change = this._show.DeleteSelectText();
				}
				event.handled = true;
			}
		} else if (event.sym === 99 && event.mod & 0x00c0 !== 0) {
			let select_text = this._show.GetSelectText();
			if (select_text !== "" && (!this._password_mode)) {
				ALittle.System_SetClipboardText(select_text);
			}
			event.handled = true;
		} else if (event.sym === 118 && event.mod & 0x00c0 !== 0) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				if (ALittle.System_HasClipboardText()) {
					let clip_board_text = ALittle.System_GetClipboardText();
					if (this.CheckTextRegexLimit(clip_board_text) === false) {
						return;
					}
					is_change = this._show.InsertText(clip_board_text);
				}
				event.handled = true;
			}
		} else if (event.sym === 97 && event.mod & 0x00c0 !== 0) {
			this._is_selecting = true;
			this._show.SelectAll();
			event.handled = true;
		} else if (event.sym === 9) {
			this.DispatchEvent(___all_struct.get(2024735182), {});
			event.handled = true;
		} else if (event.sym === 27) {
			this.DispatchEvent(___all_struct.get(1637310579), {});
			event.handled = true;
		}
		if (is_change) {
			this.DispatchEvent(___all_struct.get(958494922), {});
			this._current_flash_alpha = 1.5;
		}
	},
	SetCursorToHome : function() {
		this._is_selecting = false;
		this._show.SetCursorToHome();
	},
	SetCursorToEnd : function() {
		this._is_selecting = false;
		this._show.SetCursorToEnd();
	},
	SelectAll : function() {
		this._is_selecting = true;
		this._show.SelectAll();
	},
	CopyText : function() {
		let select_text = this._show.GetSelectText();
		if (select_text === "") {
			select_text = this.text;
		}
		if (select_text !== "") {
			ALittle.System_SetClipboardText(select_text);
		}
	},
	PasteText : function() {
		if (this._editable === false) {
			return;
		}
		if (this._show.IsDefaultText()) {
			this._show.SetDefaultText(false, "");
		}
		this._is_selecting = false;
		if (ALittle.System_HasClipboardText()) {
			let clip_board_text = ALittle.System_GetClipboardText();
			if (this.CheckTextRegexLimit(clip_board_text) === false) {
				return;
			}
			this._show.InsertText(clip_board_text);
		}
	},
	CutText : function() {
		if (this._editable === false) {
			return;
		}
		this._is_selecting = false;
		let select_text = this._show.GetSelectText();
		if (select_text !== "") {
			ALittle.System_SetClipboardText(select_text);
			this._show.DeleteSelectText();
		}
	},
	InsertText : function(text) {
		if (this._editable === false) {
			return;
		}
		if (this._show.IsDefaultText()) {
			this._show.SetDefaultText(false, "");
		}
		this._is_selecting = false;
		if (text !== undefined) {
			if (this.CheckTextRegexLimit(text) === false) {
				return;
			}
			this._show.InsertText(text);
		}
	},
	HandleDragBegin : function(event) {
		this._is_selecting = true;
		this._show.DragCursorBegin();
	},
	HandleDrag : function(event) {
		if (this._is_selecting === false) {
			return;
		}
		this._show.DragCursor(event.rel_x, event.rel_y);
	},
	HandleMoveIn : function(event) {
		this._move_in = true;
		this._show.SetDisabled(false);
		ALittle.System_SetEditCursor();
	},
	HandleMoveOut : function(event) {
		this._move_in = false;
		this._show.SetDisabled(!this._focus_in);
		ALittle.System_SetNormalCursor();
	},
	set cursor_red(value) {
		if (this._cursor_red === value) {
			return;
		}
		this._cursor_red = value;
		this._show.SetCursorRed(value);
	},
	get cursor_red() {
		return this._cursor_red;
	},
	set cursor_green(value) {
		if (this._cursor_green === value) {
			return;
		}
		this._cursor_green = value;
		this._show.SetCursorGreen(value);
	},
	get cursor_green() {
		return this._cursor_green;
	},
	set cursor_blue(value) {
		if (this._cursor_blue === value) {
			return;
		}
		this._cursor_blue = value;
		this._show.SetCursorBlue(value);
	},
	get cursor_blue() {
		return this._cursor_blue;
	},
	get flip() {
		return this._flip;
	},
	set flip(value) {
		this._flip = value;
		this._show.SetFlip(value);
	},
}, "ALittle.TextInput");

}