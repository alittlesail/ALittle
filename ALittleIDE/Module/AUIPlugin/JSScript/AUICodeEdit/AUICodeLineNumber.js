{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1862557463, "ALittle.UIShowEvent", {
name : "ALittle.UIShowEvent", ns_name : "ALittle", rl_name : "UIShowEvent", hash_code : 1862557463,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name : "ALittle.UIChangedEvent", ns_name : "ALittle", rl_name : "UIChangedEvent", hash_code : 958494922,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
AUIPlugin.AUICodeLineNumber = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys, font_path, font_size, ascii_width, word_width, edit) {
		this._showd = false;
		this._text = "";
		this._font_path = font_path;
		this._font_size = font_size;
		this._ascii_width = ascii_width;
		this._word_width = word_width;
		this._edit = edit;
		this.AddEventListener(___all_struct.get(1862557463), this, this.HandleShow);
	},
	SetLineNumber : function(line_number) {
		this._line_number = line_number;
		this.text = ALittle.String_ToString(this._line_number);
	},
	HandleShow : function(event) {
		if (this._showd) {
			return;
		}
		this._showd = true;
		this.UpdateShow();
	},
	HandleBreakChanged : function(event) {
		if (event.target.selected) {
			this._edit.AddBreakPoint(this._line_number);
		} else {
			this._edit.RemoveBreakPoint(this._line_number);
		}
	},
	UpdateShow : function() {
		let text_list = ALittle.String_SplitUTF8(this._text);
		this.RemoveAllChild();
		let quad = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		quad.red = AUIPlugin.CODE_BACKGROUND_RED;
		quad.green = AUIPlugin.CODE_BACKGROUND_GREEN;
		quad.blue = AUIPlugin.CODE_BACKGROUND_BLUE;
		quad.width_type = 4;
		quad.height_type = 4;
		this.AddChild(quad);
		let break_btn = AUIPlugin.g_Control.CreateControl("code_break_check_btn");
		break_btn.y_type = 3;
		break_btn.x = 2;
		break_btn.y_value = 1;
		this.AddChild(break_btn);
		break_btn.AddEventListener(___all_struct.get(958494922), this, this.HandleBreakChanged);
		break_btn.selected = this._edit.GetBreakPoint(this._line_number);
		let offset = 0.0;
		let len = ALittle.List_Len(text_list);
		for (let index = len; index >= 1; index += -1) {
			let char = text_list[index - 1];
			if (char === "\t") {
				offset = offset + (this._ascii_width * 4);
			} else if (char === " ") {
				offset = offset + (this._ascii_width);
			} else if (char !== "\r" && char !== "\n") {
				let is_asicc = true;
				{
					let code = char.charCodeAt(0);
					if (code > 255) {
						is_asicc = false;
					}
				}
				let text = ALittle.NewObject(ALittle.Text, this._ctrl_sys);
				text.red = this._red;
				text.green = this._green;
				text.blue = this._blue;
				text.text = char;
				text.x_value = offset;
				text.x_type = 4;
				text.font_path = this._font_path;
				text.font_size = this._font_size;
				this.y_value = 3;
				this.AddChild(text);
				if (is_asicc) {
					offset = offset + (this._ascii_width);
				} else {
					offset = offset + (this._word_width);
				}
			}
		}
	},
	get text() {
		return this._text;
	},
	set text(value) {
		if (this._text === value) {
			return;
		}
		this._text = value;
	},
	set red(value) {
		this._red = value;
		let ___OBJECT_1 = this._childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			child.red = value;
		}
	},
	set green(value) {
		this._green = value;
		let ___OBJECT_2 = this._childs;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let child = ___OBJECT_2[index - 1];
			if (child === undefined) break;
			child.green = value;
		}
	},
	set blue(value) {
		this._blue = value;
		let ___OBJECT_3 = this._childs;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let child = ___OBJECT_3[index - 1];
			if (child === undefined) break;
			child.blue = value;
		}
	},
}, "AUIPlugin.AUICodeLineNumber");

}