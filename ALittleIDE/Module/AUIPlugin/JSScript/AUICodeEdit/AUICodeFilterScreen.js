{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};
let ___all_struct = ALittle.GetAllStruct();

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
ALittle.RegStruct(-1149003083, "lua.ABnfQueryCompleteInfo", {
name : "lua.ABnfQueryCompleteInfo", ns_name : "lua", rl_name : "ABnfQueryCompleteInfo", hash_code : -1149003083,
name_list : ["display","insert","descriptor","tag"],
type_list : ["string","string","string","int"],
option_map : {}
})
ALittle.RegStruct(882286932, "ALittle.UIKeyEvent", {
name : "ALittle.UIKeyEvent", ns_name : "ALittle", rl_name : "UIKeyEvent", hash_code : 882286932,
name_list : ["target","mod","sym","scancode","custom","handled"],
type_list : ["ALittle.DisplayObject","int","int","int","bool","bool"],
option_map : {}
})
ALittle.RegStruct(-352292202, "AUIPlugin.AUICodeFilterItemInfo", {
name : "AUIPlugin.AUICodeFilterItemInfo", ns_name : "AUIPlugin", rl_name : "AUICodeFilterItemInfo", hash_code : -352292202,
name_list : ["_item_button","_item_title","_tag_image","_item","pos","upper","complete"],
type_list : ["ALittle.TextRadioButton","ALittle.Text","ALittle.Image","ALittle.DisplayObject","int","string","lua.ABnfQueryCompleteInfo"],
option_map : {}
})
ALittle.RegStruct(348388800, "ALittle.UIHideEvent", {
name : "ALittle.UIHideEvent", ns_name : "ALittle", rl_name : "UIHideEvent", hash_code : 348388800,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

AUIPlugin.AUICodeFilterScreen = JavaScript.Class(undefined, {
	Ctor : function() {
		this._item_pool = [];
		this._item_pool_count = 0;
		this._item_height = 0;
	},
	ShowComplete : async function(project, pre_input, edit) {
		if (this._edit !== edit) {
			if (this._edit !== undefined) {
				this._edit.RemoveEventListener(___all_struct.get(-1604617962), this, this.HandleEditKeyDown);
			}
			this._edit = edit;
			if (this._edit !== undefined) {
				this._edit.AddEventListener(___all_struct.get(-1604617962), this, this.HandleEditKeyDown);
			}
		}
		let text = this._edit.text;
		let split = ALittle.String_Split(text, ".");
		let split_len = ALittle.List_Len(split);
		if (split_len > 0) {
			if (split[split_len - 1] === "") {
				this._complete = undefined;
			}
			split[split_len - 1] = undefined;
		}
		this._project = project;
		if (this._complete === undefined) {
			if (!await this.ReInit(pre_input, ALittle.String_Join(split, "."))) {
				this.Hide();
				return;
			}
		}
		if (!this.Fliter(text)) {
			this.Hide();
			return;
		}
	},
	HandleEditKeyDown : function(event) {
		if (event.sym === 13) {
			this.DoSelect();
		} else if (event.sym === 1073741906) {
			this.SelectUp();
		} else if (event.sym === 1073741905) {
			this.SelectDown();
		}
	},
	IsShow : function() {
		return this._edit !== undefined;
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
		let item = this._screen.childs[target - 1];
		let text = undefined;
		let complete = item._user_data.complete;
		if (complete.insert !== undefined) {
			text = complete.insert;
		} else {
			text = complete.display;
		}
		this._edit.text = text;
		this.Hide();
		return true;
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
	ReInit : function(pre_input, input) {
		return new Promise((async function(___COROUTINE, ___) {
			if (this._project === undefined) {
				___COROUTINE(false); return;
			}
			this._complete = await this._project.FindDefine(pre_input, input);
			if (this._complete === undefined) {
				___COROUTINE(false); return;
			}
			let [x, y] = this._edit.LocalToGlobal();
			y = y + (this._edit.height);
			if (this._screen === undefined) {
				this._screen = AUIPlugin.g_Control.CreateControl("code_scroll_screen");
				this._screen.width = 200;
				this._screen.AddEventListener(___all_struct.get(348388800), this, this.HandleHide);
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
			let ___OBJECT_3 = this._complete;
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
				item_info._tag_image.texture_name = this._project.QueryCompleteIcon(info.tag);
				item_info._item._user_data = item_info;
				item_info.complete = info;
				this._item_list[index - 1] = item_info;
				let title_wdith = item_info._item_title.width + item_info._item_title.x + 5;
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
	HandleHide : function(event) {
		this.HideImpl();
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
		ALittle.List_Sort(sort_list, AUIPlugin.AUICodeFilterScreen.ItemInfoSort);
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
		this.HideImpl();
		A_LayerManager.HideFromRight(this._screen);
	},
	HideImpl : function() {
		this.HideTip();
		if (this._edit !== undefined) {
			this._edit.RemoveEventListener(___all_struct.get(-1604617962), this, this.HandleEditKeyDown);
		}
		this._edit = undefined;
		this._complete = undefined;
		if (this._screen !== undefined) {
			this._screen.RemoveAllChild();
		}
	},
	ShowTip : function(content) {
		if (this._tip_dialog === undefined) {
			this._tip_dialog = AUIPlugin.g_Control.CreateControl("code_area_tip", this);
			this._tip_dialog.width = 200;
		}
		A_LayerManager.AddToTip(this._tip_dialog);
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
		A_LayerManager.RemoveFromTip(this._tip_dialog);
	},
	Shutdown : function() {
		this.Hide();
	},
}, "AUIPlugin.AUICodeFilterScreen");

window.g_AUICodeFilterScreen = ALittle.NewObject(AUIPlugin.AUICodeFilterScreen);
}