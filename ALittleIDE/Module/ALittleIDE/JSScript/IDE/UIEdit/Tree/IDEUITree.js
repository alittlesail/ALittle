{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1883782801, "ALittle.UILButtonDownEvent", {
name : "ALittle.UILButtonDownEvent", ns_name : "ALittle", rl_name : "UILButtonDownEvent", hash_code : 1883782801,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
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
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name : "ALittle.UIResizeEvent", ns_name : "ALittle", rl_name : "UIResizeEvent", hash_code : -431205740,
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

if (ALittleIDE.IDEUITreeLogic === undefined) throw new Error(" extends class:ALittleIDE.IDEUITreeLogic is undefined");
ALittleIDE.IDEUITree = JavaScript.Class(ALittleIDE.IDEUITreeLogic, {
	Ctor : function(ctrl_sys, user_info, tab_child) {
		if (this._user_info.extends) {
			this._head = ctrl_sys.CreateControl("tree_head_disabled", this);
		} else {
			this._head = ctrl_sys.CreateControl("tree_head", this);
		}
		ALittle.DisplayGroup.AddChild.call(this, this._head);
		this._extends_icon.visible = this._user_info.extends_root;
		this._item_button.selected = false;
		this._item_button.group = this._tab_child.group;
		this._item_button.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this._item_button.AddEventListener(___all_struct.get(-449066808), this, this.HandleClick);
		this._item_button.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		this._item_button.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this._item_button.AddEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
		this._item_button.AddEventListener(___all_struct.get(-641444818), ALittleIDE.g_IDECenter.center.control_tree, ALittleIDE.g_IDECenter.center.control_tree.HandleControlTreeItemRightClick);
		this._item_button._user_data = this;
		this._body = ALittle.NewObject(ALittle.Linear, ctrl_sys);
		this._body.type = 2;
		this._body.x = 8;
		this._body.y = this._head.height;
		this._body.width = this._head.width;
		this._item_checkbutton.selected = true;
		ALittle.DisplayGroup.AddChild.call(this, this._body);
		this._body.AddEventListener(___all_struct.get(-431205740), this, this.HandleChildResize);
		this._pickup_rect = false;
		this._pickup_child = true;
		this.fold = false;
	},
	UpdateDesc : function() {
		let title = "";
		if (this._user_info.child_type !== undefined && this._user_info.child_type !== "child") {
			title = title + "[" + this._user_info.child_type + "]";
		}
		title = title + "[" + this._user_info.default.__class + "]";
		let link = this._user_info.base.__link;
		if (link === undefined) {
			link = this._user_info.default.__link;
		}
		if (this._user_info.base.description !== undefined) {
			title = title + this._user_info.base.description;
		} else if (this._user_info.default.description !== undefined) {
			title = title + this._user_info.default.description;
		} else if (link !== undefined) {
			title = title + link;
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
	HandleLButtonDown : function(event) {
		if (event.count === 1) {
			return;
		}
		this.fold = !this.fold;
	},
	get is_tree() {
		return true;
	},
	GetDataListForAdd : function() {
		let data_list = [];
		let data_list_count = 0;
		let clazz = this._user_info.default.__class;
		if (ALittleIDE.g_IDEEnum.can_add_child_map[clazz]) {
			let can_add = true;
			let ___OBJECT_1 = this._body.childs;
			for (let index = 1; index <= ___OBJECT_1.length; ++index) {
				let child = ___OBJECT_1[index - 1];
				if (child === undefined) break;
				if (child.user_info.child_type === "child" && child.user_info.extends) {
					can_add = false;
					break;
				}
			}
			if (can_add) {
				++ data_list_count;
				data_list[data_list_count - 1] = "child";
			}
		}
		let show_list = ALittleIDE.g_IDEEnum.child_show_map[clazz];
		let show_list_count = 0;
		if (show_list !== undefined) {
			let ___OBJECT_2 = show_list;
			for (let k = 1; k <= ___OBJECT_2.length; ++k) {
				let v = ___OBJECT_2[k - 1];
				if (v === undefined) break;
				let can_add = true;
				let ___OBJECT_3 = this._body.childs;
				for (let index = 1; index <= ___OBJECT_3.length; ++index) {
					let child = ___OBJECT_3[index - 1];
					if (child === undefined) break;
					if (child.user_info.child_type === v && child.user_info.extends) {
						can_add = false;
						break;
					}
				}
				if (can_add) {
					++ data_list_count;
					data_list[data_list_count - 1] = v;
				}
			}
		}
		return data_list;
	},
	CanAddChild : function() {
		let clazz = this._user_info.default.__class;
		if (ALittleIDE.g_IDEEnum.can_add_child_map[clazz]) {
			let can_add = true;
			let ___OBJECT_4 = this._body.childs;
			for (let index = 1; index <= ___OBJECT_4.length; ++index) {
				let child = ___OBJECT_4[index - 1];
				if (child === undefined) break;
				if (child.user_info.child_type === "child" && child.user_info.extends) {
					can_add = false;
					break;
				}
			}
			if (can_add) {
				return true;
			}
		}
		return false;
	},
	CalcInfo : function() {
		let info = ALittle.String_CopyTable(this._user_info.base);
		info.__childs = undefined;
		let child_count = 0;
		let ___OBJECT_5 = this._body.childs;
		for (let k = 1; k <= ___OBJECT_5.length; ++k) {
			let v = ___OBJECT_5[k - 1];
			if (v === undefined) break;
			let child_type = undefined;
			if (v._user_info.extends === false) {
				child_type = v._user_info.child_type;
			}
			if (child_type === "child") {
				if (info.__childs === undefined) {
					info.__childs = [];
				}
				++ child_count;
				info.__childs[child_count - 1] = v.CalcInfo();
			} else if (child_type !== undefined) {
				info[child_type] = v.CalcInfo();
			}
		}
		return info;
	},
	GenerateClassMember : function(list) {
		let link = this._user_info.base.__link;
		if (link === undefined) {
			link = this._user_info.default.__link;
		}
		if (link !== undefined) {
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
		}
		if (this._user_info.base.__target_class !== undefined || this._user_info.default.__target_class !== undefined) {
			return;
		}
		let ___OBJECT_6 = this._body.childs;
		for (let k = 1; k <= ___OBJECT_6.length; ++k) {
			let child = ___OBJECT_6[k - 1];
			if (child === undefined) break;
			child.GenerateClassMember(list);
		}
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
			}
		}
		let ___OBJECT_7 = this._body.childs;
		for (let k = 1; k <= ___OBJECT_7.length; ++k) {
			let child = ___OBJECT_7[k - 1];
			if (child === undefined) break;
			child.SearchLink(name, list);
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
			let ___OBJECT_8 = event;
			for (let k = 1; k <= ___OBJECT_8.length; ++k) {
				let v = ___OBJECT_8[k - 1];
				if (v === undefined) break;
				if (ALittle.String_Find(v.func, name) !== undefined) {
					ALittle.List_Push(list, this);
					break;
				}
			}
		}
		let ___OBJECT_9 = this._body.childs;
		for (let k = 1; k <= ___OBJECT_9.length; ++k) {
			let child = ___OBJECT_9[k - 1];
			if (child === undefined) break;
			child.SearchEvent(name, list);
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
			}
		}
		let ___OBJECT_10 = this._body.childs;
		for (let k = 1; k <= ___OBJECT_10.length; ++k) {
			let child = ___OBJECT_10[k - 1];
			if (child === undefined) break;
			child.SearchDescription(name, list);
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
			let target_class_str = ALittle.String_Join(target_class, "");
			if (ALittle.String_Find(target_class_str, name) !== undefined) {
				ALittle.List_Push(list, this);
			}
		}
		let ___OBJECT_11 = this._body.childs;
		for (let k = 1; k <= ___OBJECT_11.length; ++k) {
			let child = ___OBJECT_11[k - 1];
			if (child === undefined) break;
			child.SearchTargetClass(name, list);
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
			}
		}
		let ___OBJECT_12 = this._body.childs;
		for (let k = 1; k <= ___OBJECT_12.length; ++k) {
			let child = ___OBJECT_12[k - 1];
			if (child === undefined) break;
			child.SearchTextureName(name, list);
		}
		return list;
	},
	EditPickUp : function(x, y) {
		if (this._user_info.extends) {
			return undefined;
		}
		let object = this._user_info.object;
		let [pick_this, rel_x, rel_y] = object.PickUpSelf(x, y);
		let [offset_x, offset_y] = object.GetChildOffset();
		rel_x = rel_x - offset_x;
		rel_y = rel_y - offset_y;
		let child_count = this._body.child_count;
		let child_list = this._body.childs;
		for (let i = child_count; i >= 1; i += -1) {
			let child = child_list[i - 1];
			let target = child.EditPickUp(rel_x, rel_y);
			if (target !== undefined) {
				return target;
			}
		}
		if (pick_this !== undefined) {
			return this;
		}
		return undefined;
	},
	QuickPickUp : function(x, y, list) {
		if (this._user_info.extends) {
			return;
		}
		let object = this._user_info.object;
		let [pick_this, rel_x, rel_y] = object.PickUpSelf(x, y);
		if (pick_this !== undefined) {
			ALittle.List_Push(list, this);
		}
		let child_count = this._body.child_count;
		let child_list = this._body.childs;
		for (let i = child_count; i >= 1; i += -1) {
			let child = child_list[i - 1];
			child.QuickPickUp(rel_x, rel_y, list);
		}
	},
	SelectPickUp : function(x, y) {
		if (this._user_info.extends) {
			return [undefined, undefined];
		}
		let [pick_this, rel_x, rel_y] = this._item_button.PickUpSelf(x, y);
		if (this._body.visible) {
			let child_count = this._body.child_count;
			let child_list = this._body.childs;
			for (let i = child_count; i >= 1; i += -1) {
				let [parent, child] = child_list[i - 1].SelectPickUp(rel_x, rel_y);
				if (parent !== undefined || child !== undefined) {
					return [parent, child];
				}
			}
		}
		if (pick_this !== undefined) {
			return [this, undefined];
		}
		return [undefined, undefined];
	},
	HandleChildResize : function(event) {
		this.DispatchEvent(___all_struct.get(-431205740), {});
	},
	HandleHeadChanged : function(event) {
		this._body.visible = event.target.selected;
		this.DispatchEvent(___all_struct.get(-431205740), {});
	},
	GetChildIndex : function(child) {
		return this._body.GetChildIndex(child);
	},
	SetChildIndex : function(child, index) {
		return this._body.SetChildIndex(child, index);
	},
	GetChildByIndex : function(index) {
		return this._body.GetChildByIndex(index);
	},
	GetChildIndex : function(child) {
		return this._body.GetChildIndex(child);
	},
	get childs() {
		return this._body.childs;
	},
	get child_count() {
		return this._body.child_count;
	},
	HasChild : function(child) {
		return this._body.HasChild(child);
	},
	AddChild : function(child, index) {
		if (this._body.AddChild(child, index) === false) {
			return false;
		}
		child._logic_parent = this;
		if (this._body.abs_visible) {
			this.DispatchEvent(___all_struct.get(-431205740), {});
		}
		return true;
	},
	RemoveChild : function(child) {
		if (this._body.RemoveChild(child) === false) {
			return false;
		}
		if (this._body.abs_visible) {
			this.DispatchEvent(___all_struct.get(-431205740), {});
		}
		return true;
	},
	SpliceChild : function(index, count) {
		let result = this._body.SpliceChild(index, count);
		if (result === 0) {
			return 0;
		}
		if (this._body.abs_visible) {
			this.DispatchEvent(___all_struct.get(-431205740), {});
		}
		return result;
	},
	RemoveAllChild : function() {
		this._body.RemoveAllChild();
		if (this._body.abs_visible) {
			this.DispatchEvent(___all_struct.get(-431205740), {});
		}
	},
	get width() {
		let head_width = 0.0;
		if (this._head !== undefined) {
			head_width = this._head.width;
		}
		let body_width = 0.0;
		if (this._body.visible) {
			let start_x = this._body.x;
			body_width = start_x + this._body.width;
			let childs = this._body.childs;
			let ___OBJECT_13 = childs;
			for (let k = 1; k <= ___OBJECT_13.length; ++k) {
				let v = ___OBJECT_13[k - 1];
				if (v === undefined) break;
				let child_width = start_x + v.x + v.width;
				if (body_width < child_width) {
					body_width = child_width;
				}
			}
		}
		if (head_width > body_width) {
			return head_width;
		}
		return body_width;
	},
	get height() {
		let head_height = 0.0;
		if (this._head !== undefined) {
			head_height = this._head.height;
		}
		if (this._body.visible) {
			return head_height + this._body.height;
		}
		return head_height;
	},
	get fold() {
		return this._body.visible;
	},
	set fold(value) {
		if (value === this._body.visible) {
			return;
		}
		this._body.visible = value;
		this._item_checkbutton.selected = value;
		this.DispatchEvent(___all_struct.get(-431205740), {});
	},
	get max_right() {
		return this.width;
	},
	get max_bottom() {
		return this.height;
	},
}, "ALittleIDE.IDEUITree");

}