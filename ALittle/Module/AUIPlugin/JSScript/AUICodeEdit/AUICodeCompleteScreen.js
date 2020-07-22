{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1773085126, "AUIPlugin.AUICodeCompleteItemInfo", {
name : "AUIPlugin.AUICodeCompleteItemInfo", ns_name : "AUIPlugin", rl_name : "AUICodeCompleteItemInfo", hash_code : 1773085126,
name_list : ["_item_button","_item_title","_tag_image","_item","pos","upper","complete"],
type_list : ["ALittle.TextRadioButton","ALittle.Text","ALittle.Image","ALittle.DisplayObject","int","string","lua.ABnfQueryCompleteInfo"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1149003083, "lua.ABnfQueryCompleteInfo", {
name : "lua.ABnfQueryCompleteInfo", ns_name : "lua", rl_name : "ABnfQueryCompleteInfo", hash_code : -1149003083,
name_list : ["display","insert","descriptor","tag"],
type_list : ["string","string","string","int"],
option_map : {}
})
ALittle.RegStruct(348388800, "ALittle.UIHideEvent", {
name : "ALittle.UIHideEvent", ns_name : "ALittle", rl_name : "UIHideEvent", hash_code : 348388800,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

AUIPlugin.AUICodeCompleteScreen = JavaScript.Class(undefined, {
	Ctor : function() {
		this._item_pool = [];
		this._item_pool_count = 0;
		this._item_height = 0;
	},
	get edit() {
		return this._edit;
	},
	Shutdown : function() {
		this.Hide();
	},
	ShowComplete : async function(edit) {
		this._edit = edit;
		if (this._complete === undefined) {
			if (!await this.ReInit(edit)) {
				this.Hide();
				return;
			}
		}
		this._line_end = edit.cursor.line;
		this._char_end = edit.cursor.char;
		let text = edit.GetTargetText(this._complete.line_start, this._complete.char_start - 1, edit.cursor.line, edit.cursor.char);
		if (text === undefined || text === "") {
			this.Hide();
			return;
		}
		if (!this.Fliter(text)) {
			this.Hide();
			this._edit = edit;
			if (!await this.ReInit(edit)) {
				return;
			}
			this._line_end = edit.cursor.line;
			this._char_end = edit.cursor.char;
			text = edit.GetTargetText(this._complete.line_start, this._complete.char_start - 1, edit.cursor.line, edit.cursor.char);
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
				this._screen.RejustScrollBar();
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
				this._screen.RejustScrollBar();
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
	ReInit : function(edit) {
		return new Promise((async function(___COROUTINE, ___) {
			if (edit.language === undefined) {
				___COROUTINE(false); return;
			}
			this._complete = await edit.language.QueryComplete(edit.cursor.line, edit.cursor.char - 1);
			if (this._complete === undefined) {
				___COROUTINE(false); return;
			}
			let [x, y] = edit.CalcAbsPosition(this._complete.line_start, this._complete.char_start, true);
			y = y + (edit.line_height);
			if (this._screen === undefined) {
				this._screen = AUIPlugin.g_Control.CreateControl("ide_code_scroll_screen");
				this._screen.width = 200;
				this._screen.AddEventListener(___all_struct.get(348388800), this, this.HandleHideEvent);
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
					item_info._item = AUIPlugin.g_Control.CreateControl("ide_code_complete_item", item_info);
				}
				item_info._item_button.group = this._item_group;
				item_info._item_title.text = info.display;
				if (info.insert === undefined) {
					item_info.upper = ALittle.String_Upper(info.display);
				} else {
					item_info.upper = ALittle.String_Upper(info.insert);
				}
				item_info._tag_image.texture_name = edit.language.QueryCompleteIcon(info.tag);
				item_info._item._user_data = item_info;
				item_info.complete = info;
				this._item_list[index - 1] = item_info;
				let title_wdith = edit.ascii_width * ALittle.String_Len(info.display);
				if (max_width < title_wdith) {
					max_width = title_wdith;
				}
				this._item_height = item_info._item.height;
			}
			this._screen.width = max_width;
			A_LayerManager.ShowFromRight(this._screen, false);
			___COROUTINE(true); return;
		}).bind(this));
	},
	ItemInfoSort : function(a, b) {
		return a.pos < b.pos;
	},
	Fliter : function(text) {
		let descriptor = undefined;
		let upper = ALittle.String_Upper(text);
		let sort_list = [];
		let count = 0;
		this._screen.RemoveAllChild();
		let ___OBJECT_4 = this._item_list;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let info = ___OBJECT_4[index - 1];
			if (info === undefined) break;
			info.pos = ALittle.String_Find(info.upper, upper);
			if (info.pos !== undefined) {
				++ count;
				sort_list[count - 1] = info;
			}
		}
		ALittle.List_Sort(sort_list, AUIPlugin.AUICodeCompleteScreen.ItemInfoSort);
		count = 0;
		let ___OBJECT_5 = sort_list;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let info = ___OBJECT_5[index - 1];
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
		this._edit = undefined;
		this._complete = undefined;
		if (this._screen !== undefined) {
			this._screen.RemoveAllChild();
		}
		A_LayerManager.HideFromRight(this._screen);
	},
	TryHide : function(edit) {
		if (this._edit !== edit) {
			return;
		}
		if (this._complete === undefined) {
			return;
		}
		if (edit.cursor.line < this._complete.line_start || edit.cursor.line > this._line_end) {
			this.Hide();
			return;
		}
		if (edit.cursor.line === this._complete.line_start && edit.cursor.char < this._complete.char_start) {
			this.Hide();
			return;
		}
		if (edit.cursor.line === this._line_end && edit.cursor.char > this._char_end) {
			this.Hide();
			return;
		}
	},
	HandleHideEvent : function(event) {
		this.HideTip();
		this._edit = undefined;
		this._complete = undefined;
	},
	ShowTip : function(content) {
		if (this._tip_dialog === undefined) {
			this._tip_dialog = AUIPlugin.g_Control.CreateControl("ide_tool_area_tip", this);
			this._tip_dialog.width = 200;
		}
		A_LayerManager.AddToTip(this._tip_dialog);
		this._tip_dialog.visible = true;
		this._tip_text.text = content;
		this._tip_dialog.height = this._tip_text.real_height + 6;
		this._tip_dialog.x = this._screen.x;
		this._tip_dialog.y = this._screen.y + this._screen.height;
	},
	HideTip : function() {
		if (this._tip_dialog === undefined) {
			return;
		}
		this._tip_dialog.visible = false;
		A_LayerManager.RemoveFromTip(this._tip_dialog);
	},
}, "AUIPlugin.AUICodeCompleteScreen");

AUIPlugin.g_AUICodeCompleteScreen = ALittle.NewObject(AUIPlugin.AUICodeCompleteScreen);
}