{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};

ALittle.RegStruct(1773085126, "AUIPlugin.AUICodeCompleteItemInfo", {
name : "AUIPlugin.AUICodeCompleteItemInfo", ns_name : "AUIPlugin", rl_name : "AUICodeCompleteItemInfo", hash_code : 1773085126,
name_list : ["_item_button","_item_title","_tag_image","_item","pos","upper","complete"],
type_list : ["ALittle.TextRadioButton","ALittle.Text","ALittle.Image","ALittle.DisplayObject","List<int>","string","lua.ABnfQueryCompleteInfo"],
option_map : {}
})
ALittle.RegStruct(-1149003083, "lua.ABnfQueryCompleteInfo", {
name : "lua.ABnfQueryCompleteInfo", ns_name : "lua", rl_name : "ABnfQueryCompleteInfo", hash_code : -1149003083,
name_list : ["display","insert","descriptor","tag"],
type_list : ["string","string","string","int"],
option_map : {}
})

AUIPlugin.AUICodeCompleteScreen = JavaScript.Class(undefined, {
	Ctor : function(edit) {
		this._item_pool = [];
		this._item_pool_count = 0;
		this._item_height = 0;
		this._edit = edit;
	},
	ShowComplete : async function() {
		if (this._complete === undefined) {
			if (!await this.ReInit()) {
				this.Hide();
				return;
			}
		}
		this._line_end = this._edit.cursor.line;
		this._char_end = this._edit.cursor.char;
		let text = this._edit.GetTargetText(this._complete.line_start, this._complete.char_start - 1, this._edit.cursor.line, this._edit.cursor.char);
		if (text === undefined || text === "") {
			this.Hide();
			return;
		}
		if (!this.Fliter(text)) {
			this.Hide();
			if (!await this.ReInit()) {
				return;
			}
			this._line_end = this._edit.cursor.line;
			this._char_end = this._edit.cursor.char;
			text = this._edit.GetTargetText(this._complete.line_start, this._complete.char_start - 1, this._edit.cursor.line, this._edit.cursor.char);
			if (text === undefined || text === "") {
				return;
			}
			if (!this.Fliter(text)) {
				this.Hide();
			}
		}
	},
	IsShow : function() {
		return this._complete !== undefined;
	},
	SelectUp : function() {
		let target = this.GetSelectIndex();
		target = target - (1);
		if (target < 1) {
			return;
		}
		let item = this._screen.childs[target - 1];
		let info = item._user_data;
		info._item_button.selected = true;
		if (info.complete.descriptor !== undefined) {
			this.ShowTip(info.complete.descriptor);
		} else {
			this.HideTip();
		}
		let delta = this._screen.container.height - this._screen.height;
		if (delta > 0) {
			let offset = (target - 1) * this._item_height + this._screen.container_y;
			if (offset < 0) {
				this._screen.right_scrollbar.offset_rate = ((target - 1) * this._item_height) / delta;
				this._screen.AdjustScrollBar();
			}
		}
	},
	SelectDown : function() {
		let target = this.GetSelectIndex();
		target = target + (1);
		if (target > this._screen.child_count) {
			return;
		}
		let item = this._screen.childs[target - 1];
		let info = item._user_data;
		info._item_button.selected = true;
		if (info.complete.descriptor !== undefined) {
			this.ShowTip(info.complete.descriptor);
		} else {
			this.HideTip();
		}
		let delta = this._screen.container.height - this._screen.height;
		if (delta > 0) {
			let offset = target * this._item_height + this._screen.container_y;
			if (offset > this._screen.height) {
				this._screen.right_scrollbar.offset_rate = (target * this._item_height - this._screen.height) / delta;
				this._screen.AdjustScrollBar();
			}
		}
	},
	DoSelect : function() {
		let target = this.GetSelectIndex();
		if (target === undefined) {
			return false;
		}
		this._edit.select_cursor.StartLineChar(this._complete.line_start, this._complete.char_start - 1);
		this._edit.select_cursor.UpdateLineChar(this._edit.cursor.line, this._edit.cursor.char);
		let item = this._screen.childs[target - 1];
		let text = undefined;
		let complete = item._user_data.complete;
		if (complete.insert !== undefined) {
			text = complete.insert;
		} else {
			text = complete.display;
		}
		let result = this._edit.InsertText(text, true);
		this.Hide();
		return result;
	},
	GetSelectIndex : function() {
		let target = undefined;
		let ___OBJECT_1 = this._screen.childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			if (child._user_data._item_button.selected) {
				target = index;
				break;
			}
		}
		return target;
	},
	ReInit : function() {
		return new Promise((async function(___COROUTINE, ___) {
			if (this._edit.language === undefined) {
				___COROUTINE(false); return;
			}
			this._complete = await this._edit.language.QueryComplete(this._edit.cursor.line, this._edit.cursor.char - 1);
			if (this._complete === undefined) {
				___COROUTINE(false); return;
			}
			let [x, y] = this._edit.CalcPosition(this._complete.line_start, this._complete.char_start, true);
			y = y + (AUIPlugin.CODE_LINE_HEIGHT);
			if (this._screen === undefined) {
				this._screen = AUIPlugin.g_Control.CreateControl("code_scroll_screen");
				this._screen.width = 200;
			}
			this._screen.RemoveAllChild();
			this._screen.x = x;
			this._screen.y = y;
			if (this._item_list !== undefined) {
				let ___OBJECT_2 = this._item_list;
				for (let index = 1; index <= ___OBJECT_2.length; ++index) {
					let info = ___OBJECT_2[index - 1];
					if (info === undefined) break;
					this._item_pool_count = this._item_pool_count + (1);
					this._item_pool[this._item_pool_count - 1] = info;
				}
			}
			let max_width = 200.0;
			this._item_group = new Map();
			this._item_list = [];
			let ___OBJECT_3 = this._complete.complete_list;
			for (let index = 1; index <= ___OBJECT_3.length; ++index) {
				let info = ___OBJECT_3[index - 1];
				if (info === undefined) break;
				let item_info = undefined;
				if (this._item_pool_count > 0) {
					item_info = this._item_pool[this._item_pool_count - 1];
					this._item_pool[this._item_pool_count - 1] = undefined;
					this._item_pool_count = this._item_pool_count - (1);
				} else {
					item_info = {};
					item_info._item = AUIPlugin.g_Control.CreateControl("code_complete_item", item_info);
				}
				item_info._item_button.group = this._item_group;
				item_info._item_title.text = info.display;
				if (info.insert === undefined) {
					item_info.upper = ALittle.String_Upper(info.display);
				} else {
					item_info.upper = ALittle.String_Upper(info.insert);
				}
				item_info._tag_image.texture_name = this._edit.language.QueryCompleteIcon(info.tag);
				item_info._item._user_data = item_info;
				item_info.complete = info;
				this._item_list[index - 1] = item_info;
				let title_wdith = item_info._item_title.width + item_info._item_title.x + 5;
				if (max_width < title_wdith) {
					max_width = title_wdith;
				}
				this._item_height = item_info._item.height;
			}
			this._screen.width = max_width + this._screen.right_scrollbar.width;
			this._edit.help_container.AddChild(this._screen);
			___COROUTINE(true); return;
		}).bind(this));
	},
	ItemInfoSort : function(a, b) {
		let ___OBJECT_4 = a.pos;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let pos = ___OBJECT_4[index - 1];
			if (pos === undefined) break;
			if (b.pos[index - 1] === undefined) {
				return true;
			}
			if (pos !== b.pos[index - 1]) {
				return pos < b.pos[index - 1];
			}
		}
		return false;
	},
	Fliter : function(text) {
		let upper_text = ALittle.String_Upper(text);
		let first_split = ALittle.String_Find(upper_text, "_");
		if (first_split === undefined) {
			first_split = 1;
		} else {
			first_split = first_split + (1);
		}
		let upper_list = ALittle.String_Split(upper_text, "_", first_split);
		if (first_split > 1) {
			ALittle.List_Insert(upper_list, 1, ALittle.String_Sub(upper_text, 1, first_split - 1));
		}
		let upper_list_count = ALittle.List_Len(upper_list);
		if (upper_list_count > 1 && upper_list[upper_list_count - 1] === "") {
			upper_list[upper_list_count - 1] = undefined;
		}
		let sort_list = [];
		let count = 0;
		this._screen.RemoveAllChild();
		let ___OBJECT_5 = this._item_list;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let info = ___OBJECT_5[index - 1];
			if (info === undefined) break;
			info.pos = undefined;
			let pos = 1;
			let ___OBJECT_6 = upper_list;
			for (let _ = 1; _ <= ___OBJECT_6.length; ++_) {
				let upper = ___OBJECT_6[_ - 1];
				if (upper === undefined) break;
				pos = ALittle.String_Find(info.upper, upper, pos);
				if (pos !== undefined) {
					if (info.pos === undefined) {
						info.pos = [];
						++ count;
						sort_list[count - 1] = info;
					}
					ALittle.List_Push(info.pos, pos);
				}
			}
		}
		ALittle.List_Sort(sort_list, AUIPlugin.AUICodeCompleteScreen.ItemInfoSort);
		count = 0;
		let descriptor = undefined;
		let ___OBJECT_7 = sort_list;
		for (let index = 1; index <= ___OBJECT_7.length; ++index) {
			let info = ___OBJECT_7[index - 1];
			if (info === undefined) break;
			if (this._screen.child_count === 0) {
				info._item_button.selected = true;
				descriptor = info.complete.descriptor;
			}
			this._screen.AddChild(info._item);
			if (count >= 50) {
				break;
			}
		}
		if (this._screen.child_count === 0) {
			return false;
		}
		let height = this._screen.child_count * this._item_height;
		if (height < 200) {
			this._screen.height = height;
		} else {
			this._screen.height = 200;
		}
		if (descriptor !== undefined) {
			this.ShowTip(descriptor);
		} else {
			this.HideTip();
		}
		return true;
	},
	Hide : function() {
		this.HideTip();
		this._complete = undefined;
		if (this._screen !== undefined) {
			this._screen.RemoveAllChild();
		}
		this._edit.help_container.RemoveChild(this._screen);
	},
	TryHide : function() {
		if (this._complete === undefined) {
			return;
		}
		if (this._edit.cursor.line < this._complete.line_start || this._edit.cursor.line > this._line_end) {
			this.Hide();
			return;
		}
		if (this._edit.cursor.line === this._complete.line_start && this._edit.cursor.char < this._complete.char_start) {
			this.Hide();
			return;
		}
		if (this._edit.cursor.line === this._line_end && this._edit.cursor.char > this._char_end) {
			this.Hide();
			return;
		}
	},
	ShowTip : function(content) {
		if (this._tip_dialog === undefined) {
			this._tip_dialog = AUIPlugin.g_Control.CreateControl("code_area_tip", this);
			this._tip_dialog.width = 200;
		}
		this._edit.help_container.AddChild(this._tip_dialog);
		this._tip_dialog.visible = true;
		this._tip_text.text = content;
		this._tip_dialog.height = this._tip_text.real_height + 16;
		this._tip_dialog.x = this._screen.x + this._screen.width;
		this._tip_dialog.y = this._screen.y;
		if (this._tip_dialog.x + this._tip_dialog.width > A_UISystem.view_width) {
			this._tip_dialog.x = this._screen.x;
			this._tip_dialog.y = this._screen.y + this._screen.height;
		}
	},
	HideTip : function() {
		if (this._tip_dialog === undefined) {
			return;
		}
		this._tip_dialog.visible = false;
		this._edit.help_container.RemoveChild(this._tip_dialog);
	},
}, "AUIPlugin.AUICodeCompleteScreen");

}