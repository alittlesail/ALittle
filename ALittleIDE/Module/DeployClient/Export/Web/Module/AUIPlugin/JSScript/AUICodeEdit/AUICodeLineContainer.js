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
ALittle.RegStruct(348388800, "ALittle.UIHideEvent", {
name : "ALittle.UIHideEvent", ns_name : "ALittle", rl_name : "UIHideEvent", hash_code : 348388800,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
AUIPlugin.AUICodeLineContainer = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._showd = false;
		this._version = 0;
		this._delay_loop = undefined;
		let find = ALittle.NewObject(ALittle.DisplayLayout, ctrl_sys);
		find.width_type = 4;
		find.height_type = 4;
		this.AddChild(find);
		this._find = find;
		let quad = ALittle.NewObject(ALittle.Quad, ctrl_sys);
		quad = ALittle.NewObject(ALittle.Quad, AUIPlugin.g_Control);
		quad.red = AUIPlugin.CODE_SELECT_RED;
		quad.green = AUIPlugin.CODE_SELECT_GREEN;
		quad.blue = AUIPlugin.CODE_SELECT_BLUE;
		quad.height = AUIPlugin.CODE_LINE_HEIGHT;
		quad.visible = false;
		this.AddChild(quad);
		this._select = quad;
		let text = ALittle.NewObject(ALittle.DisplayLayout, ctrl_sys);
		text.width_type = 4;
		text.height_type = 4;
		this.AddChild(text);
		this._text = text;
		let error = ALittle.NewObject(ALittle.DisplayLayout, ctrl_sys);
		error.width_type = 4;
		error.height_type = 4;
		this.AddChild(error);
		this._error = error;
		this.AddEventListener(___all_struct.get(348388800), this, this.HandleHide);
		this.AddEventListener(___all_struct.get(1862557463), this, this.HandleShow);
	},
	AddChar : function(char) {
		if (char.text !== undefined) {
			this._text.AddChild(char.text);
		}
		if (!this._showd) {
			return;
		}
		if (char.text === undefined && char.width > 0 && char.char !== " " && char.char !== "\t") {
			char.text = ALittle.NewObject(ALittle.Text, AUIPlugin.g_Control);
			char.text.disabled = true;
			char.text.red = char.red;
			char.text.green = char.green;
			char.text.blue = char.blue;
			char.text.font_path = AUIPlugin.CODE_FONT_PATH;
			char.text.font_size = AUIPlugin.CODE_FONT_SIZE;
			char.text.text = char.char;
			char.text.x = char.pre_width;
			this._text.AddChild(char.text);
		}
		let line = this._user_data;
		if (this._delay_loop === undefined && line.edit.language !== undefined && line.edit.language.version !== this._version) {
			this._delay_loop = ALittle.NewObject(ALittle.LoopTimer, this.HandleColor.bind(this), 1);
			this._delay_loop.Start();
		}
	},
	RestoreColor : function() {
		this._set_color = undefined;
		if (this._delay_loop !== undefined) {
			return;
		}
		this._version = 0;
		this._delay_loop = ALittle.NewObject(ALittle.LoopTimer, this.HandleColor.bind(this), 1);
		this._delay_loop.Start();
	},
	SetColor : function(char_start, char_end, red, green, blue) {
		if (this._delay_loop !== undefined) {
			this._set_color = this.SetColor.bind(this, char_start, char_end, red, green, blue);
			return;
		}
		let line = this._user_data;
		for (let i = char_start; i <= char_end; i += 1) {
			let child = line.char_list[i - 1];
			if (child !== undefined && child.text !== undefined) {
				child.text.red = red;
				child.text.green = green;
				child.text.blue = blue;
			}
		}
	},
	HandleColor : async function() {
		this._delay_loop = undefined;
		if (this.parent === undefined) {
			return;
		}
		let line = this._user_data;
		if (this._version === line.edit.language.version) {
			return;
		}
		this._version = line.edit.language.version;
		let line_index = ALittle.Math_Floor(this.y / AUIPlugin.CODE_LINE_HEIGHT) + 1;
		if (line_index < 1 || line_index > line.edit.line_count) {
			return;
		}
		let list = await line.edit.language.QueryColor(line_index);
		let ___OBJECT_1 = list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let info = ___OBJECT_1[index - 1];
			if (info === undefined) break;
			let char_start = 1;
			if (info.line_start === line_index) {
				char_start = info.char_start;
			}
			let char_end = line.char_count;
			if (info.line_end === line_index) {
				char_end = info.char_end;
			}
			let color = line.edit.language.QueryColorValue(info.tag);
			if (color === undefined) {
				color = AUIPlugin.CODE_DEFAULT_COLOR;
			}
			for (let i = char_start; i <= char_end; i += 1) {
				let child = line.char_list[i - 1];
				if (child !== undefined && child.text !== undefined) {
					child.text.red = color.red;
					child.text.green = color.green;
					child.text.blue = color.blue;
					if (info.blur) {
						child.text.alpha = 0.5;
					} else {
						child.text.alpha = 1;
					}
				}
			}
		}
		if (this._set_color !== undefined) {
			this._set_color();
			this._set_color = undefined;
		}
	},
	HandleHide : function(event) {
	},
	HandleShow : function(event) {
		if (!this._showd) {
			this._showd = true;
			let line = this._user_data;
			let ___OBJECT_2 = line.char_list;
			for (let index = 1; index <= ___OBJECT_2.length; ++index) {
				let char = ___OBJECT_2[index - 1];
				if (char === undefined) break;
				if (char.text === undefined && char.width > 0 && char.char !== " " && char.char !== "\t") {
					char.text = ALittle.NewObject(ALittle.Text, AUIPlugin.g_Control);
					char.text.disabled = true;
					char.text.red = AUIPlugin.CODE_FONT_RED;
					char.text.green = AUIPlugin.CODE_FONT_GREEN;
					char.text.blue = AUIPlugin.CODE_FONT_BLUE;
					char.text.font_path = AUIPlugin.CODE_FONT_PATH;
					char.text.font_size = AUIPlugin.CODE_FONT_SIZE;
					char.text.text = char.char;
					char.text.x = char.pre_width;
					this._text.AddChild(char.text);
				}
			}
		}
		let line = this._user_data;
		if (this._delay_loop === undefined && line.edit.language !== undefined && line.edit.language.version !== this._version) {
			this._delay_loop = ALittle.NewObject(ALittle.LoopTimer, this.HandleColor.bind(this), 1);
			this._delay_loop.Start();
		}
	},
}, "AUIPlugin.AUICodeLineContainer");

}