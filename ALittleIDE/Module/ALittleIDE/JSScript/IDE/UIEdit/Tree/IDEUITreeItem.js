{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

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
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name : "ALittle.UIClickEvent", ns_name : "ALittle", rl_name : "UIClickEvent", hash_code : -449066808,
name_list : ["target","is_drag","count"],
type_list : ["ALittle.DisplayObject","bool","int"],
option_map : {}
})
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name : "ALittle.UIButtonDragEndEvent", ns_name : "ALittle", rl_name : "UIButtonDragEndEvent", hash_code : 150587926,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})

if (ALittleIDE.IDEUITreeLogic === undefined) throw new Error(" extends class:ALittleIDE.IDEUITreeLogic is undefined");
ALittleIDE.IDEUITreeItem = JavaScript.Class(ALittleIDE.IDEUITreeLogic, {
	Ctor : function(ctrl_sys, user_info, tab_child) {
		if (this._user_info.extends) {
			this._item = ctrl_sys.CreateControl("tree_item_disabled", this);
		} else {
			this._item = ctrl_sys.CreateControl("tree_item", this);
		}
		this.AddChild(this._item);
		this.width = this._item.width;
		this.height = this._item.height;
		this._text_icon.visible = false;
		this._image_icon.visible = false;
		this._check_icon.visible = false;
		this._button_icon.visible = false;
		this._radio_icon.visible = false;
		this._quad_icon.visible = false;
		this._dropdown_icon.visible = false;
		this._input_icon.visible = false;
		let name_map = {};
		name_map["Text"] = this._text_icon;
		name_map["TextArea"] = this._text_icon;
		name_map["RichArea"] = this._text_icon;
		name_map["TextInput"] = this._input_icon;
		name_map["TextEdit"] = this._input_icon;
		name_map["ImageInput"] = this._input_icon;
		name_map["ImageEdit"] = this._input_icon;
		name_map["RichEdit"] = this._input_icon;
		name_map["RichInput"] = this._input_icon;
		name_map["Quad"] = this._quad_icon;
		name_map["Image"] = this._image_icon;
		name_map["Grid9Image"] = this._image_icon;
		name_map["Sprite"] = this._image_icon;
		name_map["ImagePlay"] = this._image_icon;
		name_map["SpritePlay"] = this._image_icon;
		name_map["FramePlay"] = this._image_icon;
		name_map["Piechart"] = this._image_icon;
		name_map["Triangle"] = this._image_icon;
		name_map["TextButton"] = this._button_icon;
		name_map["ScrollButton"] = this._button_icon;
		name_map["SpringTextButton"] = this._button_icon;
		name_map["Slider"] = this._button_icon;
		name_map["TextCheckButton"] = this._check_icon;
		name_map["TextRadioButton"] = this._radio_icon;
		name_map["DropDown"] = this._dropdown_icon;
		let icon = name_map[this._user_info.default.__class];
		if (icon !== undefined) {
			icon.visible = true;
		}
		this._extends_icon.visible = this._user_info.extends_root;
		this._item_button.selected = false;
		this._item_button.group = this._tab_child.group;
		this._item_button.AddEventListener(___all_struct.get(-449066808), this, this.HandleClick);
		this._item_button.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		this._item_button.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this._item_button.AddEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
		this._item_button.AddEventListener(___all_struct.get(-641444818), ALittleIDE.g_IDECenter.center.control_tree, ALittleIDE.g_IDECenter.center.control_tree.HandleControlTreeItemRightClick);
		this._item_button._user_data = this;
	},
	UpdateDesc : function() {
		let title = "";
		if (this._user_info.child_type !== undefined && this._user_info.child_type !== "child") {
			title = title + "[" + this._user_info.child_type + "]";
		}
		let link = this._user_info.base.__link;
		if (link === undefined) {
			link = this._user_info.default.__link;
		}
		if (link !== undefined) {
			title = title + link;
		} else if (this._user_info.base.description !== undefined) {
			title = title + this._user_info.base.description;
		} else if (this._user_info.default.description !== undefined) {
			title = title + this._user_info.default.description;
		} else if (this._user_info.base.text !== undefined) {
			title = title + this._user_info.base.text;
		} else if (this._user_info.default.text !== undefined) {
			title = title + this._user_info.default.text;
		}
		this._item_button.text = title;
		if (this._user_info.child_type === undefined) {
			this._tab_child.UpdateTitle();
		}
	},
	get is_tree() {
		return false;
	},
	get fold() {
		return false;
	},
	set fold(value) {
	},
	GetDataListForAdd : function() {
		return [];
	},
	CalcInfo : function() {
		return ALittle.String_CopyTable(this._user_info.base);
	},
	SearchLink : function(name, list) {
		if (list === undefined) {
			list = [];
		}
		let link = this._user_info.base.__link;
		if (link === undefined) {
			link = this._user_info.default.__link;
		}
		if (link !== undefined) {
			if (ALittle.String_Find(link, name) !== undefined) {
				ALittle.List_Push(list, this);
				return list;
			}
		}
		return list;
	},
	SearchEvent : function(name, list) {
		if (list === undefined) {
			list = [];
		}
		let event = this._user_info.base.__event;
		if (event === undefined) {
			event = this._user_info.default.__event;
		}
		if (event !== undefined) {
			let ___OBJECT_1 = event;
			for (let k = 1; k <= ___OBJECT_1.length; ++k) {
				let v = ___OBJECT_1[k - 1];
				if (v === undefined) break;
				if (ALittle.String_Find(v.func, name) !== undefined) {
					ALittle.List_Push(list, this);
					return list;
				}
			}
		}
		return list;
	},
	SearchDescription : function(name, list) {
		if (list === undefined) {
			list = [];
		}
		let description = this._user_info.base.description;
		if (description === undefined) {
			description = this._user_info.default.description;
		}
		if (description !== undefined) {
			if (ALittle.String_Find(description, name) !== undefined) {
				ALittle.List_Push(list, this);
				return list;
			}
		}
		return list;
	},
	SearchTargetClass : function(name, list) {
		if (list === undefined) {
			list = [];
		}
		let target_class = this._user_info.base.__target_class;
		if (target_class === undefined) {
			target_class = this._user_info.default.__target_class;
		}
		if (target_class !== undefined) {
			let target_class_str = ALittle.String_Join(target_class, ".");
			if (ALittle.String_Find(target_class_str, name) !== undefined) {
				ALittle.List_Push(list, this);
				return list;
			}
		}
		return list;
	},
	SearchTextureName : function(name, list) {
		if (list === undefined) {
			list = [];
		}
		let texture_name = this._user_info.base.texture_name;
		if (texture_name === undefined) {
			texture_name = this._user_info.default.texture_name;
		}
		if (texture_name !== undefined) {
			if (ALittle.String_Find(texture_name, name) !== undefined) {
				ALittle.List_Push(list, this);
				return list;
			}
		}
		return list;
	},
	EditPickUp : function(x, y) {
		if (this._user_info.extends) {
			return undefined;
		}
		let object = this._user_info.object;
		let [pick_this, rel_x, rel_y] = object.PickUpSelf(x, y);
		if (pick_this !== undefined) {
			return this;
		}
		return undefined;
	},
	QuickPickUp : function(x, y, list) {
	},
	SelectPickUp : function(x, y) {
		if (this._user_info.extends) {
			return [undefined, undefined];
		}
		let [pick_this, rel_x, rel_y] = this._item_button.PickUpSelf(x, y);
		if (pick_this !== undefined) {
			return [undefined, this];
		}
		return [undefined, undefined];
	},
	GenerateClassMember : function(list) {
		let link = this._user_info.base.__link;
		if (link === undefined) {
			link = this._user_info.default.__link;
		}
		if (link === undefined) {
			return;
		}
		let member = "\tprivate ";
		if (this._user_info.base.__target_class !== undefined) {
			member = member + ALittle.String_Join(this._user_info.base.__target_class, ".");
		} else if (this._user_info.default.__target_class !== undefined) {
			member = member + ALittle.String_Join(this._user_info.default.__target_class, ".");
		} else if (this._user_info.base.__class !== undefined) {
			member = member + "ALittle." + this._user_info.base.__class;
		} else {
			member = member + "ALittle." + this._user_info.default.__class;
		}
		member = member + " " + link + ";";
		let desc = this._user_info.base.description;
		if (desc === undefined || desc === "") {
			desc = this._user_info.default.description;
		}
		if (desc !== undefined && desc !== "") {
			member = member + " // " + desc;
		}
		member = member + "\n";
		ALittle.List_Push(list, member);
	},
}, "ALittleIDE.IDEUITreeItem");

}