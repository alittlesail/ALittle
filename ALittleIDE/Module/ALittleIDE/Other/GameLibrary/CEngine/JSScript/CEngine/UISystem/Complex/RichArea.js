{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(485812343, "ALittle.RichAreaLineInfo", {
name : "ALittle.RichAreaLineInfo", ns_name : "ALittle", rl_name : "RichAreaLineInfo", hash_code : 485812343,
name_list : ["childs","child_count","height","width"],
type_list : ["List<ALittle.DisplayObject>","int","double","double"],
option_map : {}
})

let __find = ALittle.String_Find;
let __sub = ALittle.String_Sub;
let __floor = ALittle.Math_Floor;
if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.RichArea = JavaScript.Class(ALittle.DisplayLayout, {
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
	Ctor : function(ctrl_sys) {
		this._enter_key_height = 20;
		this._line_spacing = 0;
		this._halign = 0;
		this._valign = 0;
		this._display_list = undefined;
		this._line_list = [];
		this._line_count = 0;
		this._real_height = 0;
		this._link_map = ALittle.CreateValueWeakMap();
		this._max_line_count = 0;
	},
	get link_map() {
		return this._link_map;
	},
	ClearLinkMap : function() {
		this._link_map = ALittle.CreateValueWeakMap();
	},
	set width(value) {
		if (this.width === value) {
			return;
		}
		ALittle.DisplayLayout.__setter.width.call(this, value);
		this.Refresh();
	},
	set display_list(value) {
		this._display_list = value;
		this.Refresh();
	},
	get display_list() {
		return this._display_list;
	},
	set halign(value) {
		if (this._halign === value) {
			return;
		}
		this._halign = value;
		this.RefreshX();
	},
	get halign() {
		return this._halign;
	},
	set valign(value) {
		if (this._valign === value) {
			return;
		}
		this._valign = value;
		this.RefreshY();
	},
	get valign() {
		return this._valign;
	},
	get lin_count() {
		return this._line_count;
	},
	get max_line_count() {
		return this._max_line_count;
	},
	set max_line_count(value) {
		if (this._max_line_count === value) {
			return;
		}
		this._max_line_count = value;
		this.Refresh();
	},
	GetLineWidth : function(line_index) {
		let count = this._line_count;
		if (line_index < 1 || line_index > count) {
			return 0;
		}
		let line = this._line_list[line_index - 1];
		return line.width;
	},
	get real_height() {
		return this._real_height;
	},
	set line_spacing(line_spacing) {
		if (this._line_spacing === line_spacing) {
			return;
		}
		this._line_spacing = line_spacing;
		this.RefreshY();
	},
	get line_spacing() {
		return this._line_spacing;
	},
	Refresh : function() {
		this.RemoveAllChild();
		this._line_list = [];
		this._line_count = 0;
		let total_width = this.width;
		if (total_width === 0) {
			return;
		}
		if (this._display_list === undefined) {
			return;
		}
		let display_list = [];
		let display_list_count = 0;
		let ___OBJECT_1 = this._display_list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let display_info = ___OBJECT_1[index - 1];
			if (display_info === undefined) break;
			if (display_info.__class === "Text") {
				display_list_count = this.SplitText(display_info, display_list, display_list_count);
			} else {
				++ display_list_count;
				display_list[display_list_count - 1] = display_info;
			}
		}
		let line_info = undefined;
		let display_info = undefined;
		let display_object = undefined;
		let display_index = 1;
		let remain_width = total_width;
		while (true) {
			if (display_info === undefined) {
				display_info = display_list[display_index - 1];
				if (display_info === undefined) {
					break;
				}
			}
			if (line_info === undefined) {
				if (this._max_line_count > 0 && this._line_count >= this._max_line_count) {
					break;
				}
				line_info = {};
				line_info.childs = [];
				line_info.child_count = 0;
				line_info.height = 0;
				line_info.width = 0;
			}
			if (display_info.__class === "Text") {
				if (display_info.text === "\n") {
					if (line_info.height < this._enter_key_height) {
						line_info.height = this._enter_key_height;
					}
					++ this._line_count;
					this._line_list[this._line_count - 1] = line_info;
					line_info = undefined;
					display_info = undefined;
					display_object = undefined;
					++ display_index;
					remain_width = total_width;
				} else if (display_info.text === "\t") {
					if (display_object === undefined) {
						let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
						this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info));
						display_object = this._ctrl_sys.CreateControl(name, this._link_map);
						this._ctrl_sys.UnRegisterInfo(name);
						display_object.text = "    ";
					}
					let object_width = display_object.width;
					let object_height = display_object.height;
					if (remain_width >= object_width) {
						++ line_info.child_count;
						line_info.childs[line_info.child_count - 1] = display_object;
						this.AddChild(display_object);
						line_info.width = line_info.width + object_width;
						if (line_info.height < object_height) {
							line_info.height = object_height;
						}
						remain_width = remain_width - object_width;
						if (remain_width <= 0) {
							++ this._line_count;
							this._line_list[this._line_count - 1] = line_info;
							line_info = undefined;
							remain_width = total_width;
						}
						display_object = undefined;
						display_info = undefined;
						++ display_index;
					} else {
						let count = display_object._show.CutTextByWidth(__floor(remain_width), display_info.text, __floor(total_width));
						if (count > 0) {
							display_object.text = __sub(display_info.text, 1, count);
							let new_display_info = ALittle.String_CopyTable(display_info);
							new_display_info.text = __sub(display_info.text, count + 1);
							++ line_info.child_count;
							line_info.childs[line_info.child_count - 1] = display_object;
							this.AddChild(display_object);
							line_info.width = line_info.width + display_object.width;
							if (line_info.height < object_height) {
								line_info.height = object_height;
							}
							++ this._line_count;
							this._line_list[this._line_count - 1] = line_info;
							line_info = undefined;
							remain_width = total_width;
							display_object = undefined;
							display_info = new_display_info;
						} else {
							++ this._line_count;
							this._line_list[this._line_count - 1] = line_info;
							line_info = undefined;
							remain_width = total_width;
						}
					}
				} else {
					if (display_info.text === "") {
						display_info = undefined;
						++ display_index;
					} else {
						if (display_object === undefined) {
							let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
							this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info));
							display_object = this._ctrl_sys.CreateControl(name, this._link_map);
							this._ctrl_sys.UnRegisterInfo(name);
						}
						let object_width = display_object.width;
						let object_height = display_object.height;
						let count = display_object._show.CutTextByWidth(__floor(remain_width), display_info.text, __floor(total_width));
						if (count === 0 && line_info.child_count === 0) {
							count = ALittle.String_GetByteCount(display_info.text, 1);
						}
						if (count === 0) {
							remain_width = 0;
						} else {
							display_object.text = __sub(display_info.text, 1, count);
							let new_display_info = ALittle.String_CopyTable(display_info);
							new_display_info.text = __sub(display_info.text, count + 1);
							++ line_info.child_count;
							line_info.childs[line_info.child_count - 1] = display_object;
							this.AddChild(display_object);
							line_info.width = line_info.width + display_object.width;
							if (line_info.height < object_height) {
								line_info.height = object_height;
							}
							remain_width = remain_width - display_object.width;
							display_object = undefined;
							display_info = new_display_info;
						}
						if (remain_width <= 0) {
							++ this._line_count;
							this._line_list[this._line_count - 1] = line_info;
							line_info = undefined;
							remain_width = total_width;
						}
					}
				}
			} else {
				if (display_object === undefined) {
					let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
					this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info));
					display_object = this._ctrl_sys.CreateControl(name, this._link_map);
					this._ctrl_sys.UnRegisterInfo(name);
				}
				let object_width = display_object.width;
				let object_height = display_object.height;
				if (remain_width >= object_width || (line_info.child_count === 0 && total_width <= object_width)) {
					++ line_info.child_count;
					line_info.childs[line_info.child_count - 1] = display_object;
					this.AddChild(display_object);
					line_info.width = line_info.width + display_object.width;
					if (line_info.height < object_height) {
						line_info.height = object_height;
					}
					remain_width = remain_width - object_width;
					if (remain_width <= 0) {
						++ this._line_count;
						this._line_list[this._line_count - 1] = line_info;
						line_info = undefined;
						remain_width = total_width;
					}
					display_object = undefined;
					display_info = undefined;
					++ display_index;
				} else {
					++ this._line_count;
					this._line_list[this._line_count - 1] = line_info;
					line_info = undefined;
					remain_width = total_width;
				}
			}
		}
		if (line_info !== undefined) {
			++ this._line_count;
			this._line_list[this._line_count - 1] = line_info;
		}
		this.RefreshX();
		this.RefreshY();
	},
	RefreshX : function() {
		if (this._line_list === undefined) {
			return;
		}
		let ___OBJECT_2 = this._line_list;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let line = ___OBJECT_2[k - 1];
			if (line === undefined) break;
			let offset_x = 0.0;
			if (this._halign === 1) {
				offset_x = (this.width - line.width) / 2;
			} else if (this._halign === 2) {
				offset_x = this.width - line.width;
			}
			let ___OBJECT_3 = line.childs;
			for (let index = 1; index <= ___OBJECT_3.length; ++index) {
				let child = ___OBJECT_3[index - 1];
				if (child === undefined) break;
				child.x = offset_x;
				offset_x = offset_x + child.width;
			}
		}
	},
	RefreshY : function() {
		if (this._line_list === undefined) {
			return;
		}
		this._real_height = 0;
		let line_count = 0;
		let ___OBJECT_4 = this._line_list;
		for (let k = 1; k <= ___OBJECT_4.length; ++k) {
			let line = ___OBJECT_4[k - 1];
			if (line === undefined) break;
			this._real_height = this._real_height + line.height;
			++ line_count;
		}
		this._real_height = this._real_height + (line_count - 1) * this._line_spacing;
		let offset_y = 0.0;
		if (this._valign === 1) {
			offset_y = (this.height - this._real_height) / 2;
		} else if (this._valign === 2) {
			offset_y = this.height - this._real_height;
		}
		let ___OBJECT_5 = this._line_list;
		for (let k = 1; k <= ___OBJECT_5.length; ++k) {
			let line = ___OBJECT_5[k - 1];
			if (line === undefined) break;
			let ___OBJECT_6 = line.childs;
			for (let index = 1; index <= ___OBJECT_6.length; ++index) {
				let child = ___OBJECT_6[index - 1];
				if (child === undefined) break;
				child.y = line.height - child.height + offset_y;
			}
			offset_y = offset_y + line.height + this._line_spacing;
		}
	},
}, "ALittle.RichArea");

}