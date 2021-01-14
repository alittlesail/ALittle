{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};

ALittle.RegStruct(-1275923985, "AUIPlugin.AUICodeParamItemInfo", {
name : "AUIPlugin.AUICodeParamItemInfo", ns_name : "AUIPlugin", rl_name : "AUICodeParamItemInfo", hash_code : -1275923985,
name_list : ["text_list"],
type_list : ["List<ALittle.DisplayObject>"],
option_map : {}
})

AUIPlugin.AUICodeParamList = JavaScript.Class(undefined, {
	Ctor : function(edit) {
		this._edit = edit;
	},
	ShowParamList : async function() {
		if (this._param_info === undefined) {
			if (!await this.ReInit()) {
				this.Hide();
				return;
			}
		}
		let [param_index, start_offset] = this._edit.language.QueryParamIndex(this._edit.cursor.line, this._edit.cursor.char - 1);
		if (param_index < 1) {
			this.Hide();
			return;
		}
		if (this._start_offset === undefined) {
			this._start_offset = start_offset;
		} else if (this._start_offset !== start_offset) {
			this.Hide();
			if (!await this.ReInit()) {
				this.Hide();
				return;
			}
			this._start_offset = start_offset;
		}
		if (this._param_index === param_index) {
			return;
		}
		if (param_index > this._param_count) {
			this.Hide();
			return;
		}
		let item_info = this._item_list[this._param_index - 1];
		if (item_info !== undefined) {
			let ___OBJECT_1 = item_info.text_list;
			for (let index = 1; index <= ___OBJECT_1.length; ++index) {
				let text = ___OBJECT_1[index - 1];
				if (text === undefined) break;
				text.red = AUIPlugin.CODE_PARAMLIST_RED;
				text.green = AUIPlugin.CODE_PARAMLIST_GREEN;
				text.blue = AUIPlugin.CODE_PARAMLIST_BLUE;
			}
		}
		this._param_index = param_index;
		item_info = this._item_list[this._param_index - 1];
		if (item_info !== undefined) {
			let ___OBJECT_2 = item_info.text_list;
			for (let index = 1; index <= ___OBJECT_2.length; ++index) {
				let text = ___OBJECT_2[index - 1];
				if (text === undefined) break;
				text.red = AUIPlugin.CODE_PARAMLIST_FOCUS_RED;
				text.green = AUIPlugin.CODE_PARAMLIST_FOCUS_GREEN;
				text.blue = AUIPlugin.CODE_PARAMLIST_FOCUS_BLUE;
			}
		}
	},
	IsShow : function() {
		return this._param_info !== undefined;
	},
	ReInit : function() {
		return new Promise((async function(___COROUTINE, ___) {
			if (this._edit.language === undefined) {
				___COROUTINE(false); return;
			}
			this._param_info = await this._edit.language.QueryParamList(this._edit.cursor.line, this._edit.cursor.char - 1);
			if (this._param_info === undefined) {
				___COROUTINE(false); return;
			}
			this._param_count = ALittle.List_Len(this._param_info.param_list);
			if (this._param_count === 0) {
				___COROUTINE(false); return;
			}
			let [x, y] = this._edit.CalcPosition(this._param_info.line_start, this._param_info.char_start, true);
			if (this._dialog === undefined) {
				this._dialog = AUIPlugin.g_Control.CreateControl("code_paramlist_tip", this);
				this._dialog.width = 200;
				this._dialog.height = AUIPlugin.CODE_LINE_HEIGHT + this._text_container.height_value;
			}
			y = y - (this._dialog.height);
			this._text_container.RemoveAllChild();
			this._dialog.x = x;
			this._dialog.y = y;
			this._item_list = [];
			this._param_index = 0;
			let offset = 0.0;
			let param_len = ALittle.List_Len(this._param_info.param_list);
			let ___OBJECT_3 = this._param_info.param_list;
			for (let param_index = 1; param_index <= ___OBJECT_3.length; ++param_index) {
				let param = ___OBJECT_3[param_index - 1];
				if (param === undefined) break;
				let info = {};
				info.text_list = [];
				let text_count = 0;
				let param_name = param.name;
				if (param_index !== param_len) {
					param_name = param_name + ", ";
				}
				let text_list = ALittle.String_SplitUTF8(param_name);
				let ___OBJECT_4 = text_list;
				for (let index = 1; index <= ___OBJECT_4.length; ++index) {
					let char = ___OBJECT_4[index - 1];
					if (char === undefined) break;
					if (char === "\t") {
						offset = offset + (this._edit.ascii_width * 4);
					} else if (char === " ") {
						offset = offset + (this._edit.ascii_width);
					} else if (char !== "\r" && char !== "\n") {
						let is_asicc = true;
						{
							let code = char.charCodeAt(0);
							if (code > 255) {
								is_asicc = false;
							}
						}
						let text = ALittle.NewObject(ALittle.Text, AUIPlugin.g_Control);
						text.red = AUIPlugin.CODE_PARAMLIST_RED;
						text.green = AUIPlugin.CODE_PARAMLIST_GREEN;
						text.blue = AUIPlugin.CODE_PARAMLIST_BLUE;
						text.text = char;
						text.x = offset;
						text.font_path = AUIPlugin.CODE_FONT_PATH;
						text.font_size = AUIPlugin.CODE_FONT_SIZE;
						this._text_container.AddChild(text);
						if (is_asicc) {
							offset = offset + (this._edit.ascii_width);
						} else {
							offset = offset + (this._edit.word_width);
						}
						++ text_count;
						info.text_list[text_count - 1] = text;
					}
				}
				this._item_list[param_index - 1] = info;
			}
			this._dialog.width = offset + this._text_container.width_value;
			this._edit.help_container.AddChild(this._dialog);
			___COROUTINE(true); return;
		}).bind(this));
	},
	Hide : function() {
		this._param_info = undefined;
		this._start_offset = undefined;
		this._param_count = 0;
		this._param_index = 0;
		this._edit.help_container.RemoveChild(this._dialog);
	},
	TryHide : function() {
		if (this._param_info === undefined) {
			return;
		}
		if (this._edit.cursor.line < this._param_info.line_start || this._edit.cursor.line > this._param_info.line_end) {
			this.Hide();
			return;
		}
		if (this._edit.cursor.line === this._param_info.line_start && this._edit.cursor.char < this._param_info.char_start) {
			this.Hide();
			return;
		}
		if (this._edit.cursor.line === this._param_info.line_end && this._edit.cursor.char > this._param_info.char_end) {
			this.Hide();
			return;
		}
	},
}, "AUIPlugin.AUICodeParamList");

}