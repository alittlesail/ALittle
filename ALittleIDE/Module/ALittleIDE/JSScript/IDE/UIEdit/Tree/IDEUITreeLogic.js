{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
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
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name : "ALittle.UIButtonDragEndEvent", ns_name : "ALittle", rl_name : "UIButtonDragEndEvent", hash_code : 150587926,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEUITreeLogic = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys, user_info, tab_child) {
		this._tab_child = tab_child;
		this._user_info = user_info;
		this._attr_panel = undefined;
		this._drag_effect = undefined;
		this._drag_ctrl = false;
	},
	get user_info() {
		return this._user_info;
	},
	get tab_child() {
		return this._tab_child;
	},
	get is_root() {
		return this._user_info.root;
	},
	get is_tree() {
		return false;
	},
	get attr_panel() {
		return this._attr_panel;
	},
	get title() {
		return this._item_button.text;
	},
	CanAddChild : function() {
		return false;
	},
	set fold(value) {
	},
	GetDesc : function() {
		let desc = this._user_info.base.description;
		if (desc !== undefined) {
			return desc;
		}
		desc = this._user_info.default.description;
		if (desc !== undefined) {
			return desc;
		}
		return "";
	},
	SetDesc : function(text) {
		this._user_info.base.description = text;
		if (this._user_info.base.description === "" || this._user_info.base.description === this._user_info.default.description) {
			this._user_info.base.description = undefined;
		}
		this._tab_child.save = false;
		this.UpdateDesc();
	},
	UpdateDesc : function() {
	},
	get attr_panel() {
		return this._attr_panel;
	},
	RemoveAttributePanel : function() {
		if (this._attr_panel === undefined) {
			return;
		}
		this._tab_child.attr_screen.RemoveChild(this._attr_panel.layer);
		ALittleIDE.g_IDEAttrControlDialog.SetTitle("");
	},
	ShowAttributePanel : function() {
		this._tab_child.attr_screen.RemoveAllChild();
		this._item_button.selected = true;
		if (this._attr_panel === undefined) {
			let class_name = this._user_info.default.__class + "S";
			let clazz = ALittleIDE[class_name];
			this._attr_panel = ALittle.NewObject(clazz, this._user_info, this._tab_child, this);
			this._attr_panel.layer._user_data = this._attr_panel;
			this._attr_panel.layer.disabled = this._user_info.extends;
		}
		ALittleIDE.g_IDEAttrControlDialog.SetTitle(this._attr_panel.title);
		this._tab_child.attr_screen.AddChild(this._attr_panel.layer);
	},
	ShowFocus : function(is_group) {
		this.ShowAttributePanel();
		this._tab_child.ShowTreeItemFocus(this);
		this._tab_child.ShowHandleQuad(this, is_group);
	},
	HandleClick : function(event) {
		if (this._user_info.extends) {
			this.ShowAttributePanel();
			return;
		}
		let shift = (A_UISystem.sym_map.get(1073742049) !== undefined || A_UISystem.sym_map.get(1073742053) !== undefined);
		if (shift && this._tab_child.IsShowHandleQuad(this)) {
			this._tab_child.HideHandleQuad(this);
		} else {
			this._tab_child.ShowHandleQuad(this);
		}
	},
	HandleDragBegin : function(event) {
		this._drag_ctrl = (A_UISystem.sym_map.get(1073742048) !== undefined || A_UISystem.sym_map.get(1073742052) !== undefined);
		if (this._drag_ctrl === false) {
			event.target = this._tab_child.tree_screen;
			this._tab_child.tree_screen.DispatchEvent(___all_struct.get(1301789264), event);
			return;
		}
		let button = this._head;
		if (button === undefined) {
			button = this._item;
		}
		let [x, y] = button.LocalToGlobal();
		this._drag_effect = ALittle.NewObject(ALittle.EffectImage, ALittleIDE.g_Control);
		this._drag_effect.Action(button);
		A_LayerManager.AddToTip(this._drag_effect);
		this._drag_effect.x = x;
		this._drag_effect.y = y;
		this._drag_effect.alpha = 0.6;
	},
	HandleDrag : function(event) {
		if (this._drag_ctrl === false) {
			event.target = this._tab_child.tree_screen;
			this._tab_child.tree_screen.DispatchEvent(___all_struct.get(1337289812), event);
			return;
		}
		if (this._drag_effect === undefined) {
			return;
		}
		this._drag_effect.x = this._drag_effect.x + event.delta_x;
		this._drag_effect.y = this._drag_effect.y + event.delta_y;
	},
	HandleDragEnd : function(event) {
		if (this._drag_ctrl === false) {
			event.target = this._tab_child.tree_screen;
			this._tab_child.tree_screen.DispatchEvent(___all_struct.get(150587926), event);
			return;
		}
		if (this._drag_effect !== undefined) {
			A_LayerManager.RemoveFromTip(this._drag_effect);
			this._drag_effect.Clear();
			this._drag_effect = undefined;
		}
		if (this._tab_child.tree_object === this) {
			return;
		}
		let [x, y] = this._tab_child.tree_object.LocalToGlobal();
		let delta_x = event.abs_x - x;
		let delta_y = event.abs_y - y;
		let [target] = this._tab_child.tree_object.PickUp(delta_x, delta_y);
		if (target === undefined) {
			ALittle.Log("IDEUITreeLogic:HandleDragEnd target null");
			return;
		}
		let tree = target._user_data;
		if (tree.IsGrandParent(this)) {
			g_AUITool.ShowNotice("提示", "目标是自己的子控件，移动失败");
			return;
		}
		if (tree._user_info.extends) {
			g_AUITool.ShowNotice("提示", "目标控件不能操作，移动失败");
			return;
		}
		let copy_list = [];
		let info = {};
		info.module = this._user_info.module;
		info.index = 1;
		info.info = this.CalcInfo();
		copy_list[1 - 1] = info;
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list));
		let revoke_bind = ALittle.NewObject(ALittle.RevokeBind);
		if (tree.is_tree) {
			this._tab_child.RightControlTreePasteImpl(tree, undefined, 1, revoke_bind, this.HandleDragEndAndCut.bind(this, revoke_bind));
		} else {
			let common_parent = tree._logic_parent;
			if (common_parent === undefined) {
				g_AUITool.ShowNotice("提示", "当前是根节点，并且不是容器，移动失败");
				return;
			}
			let child_index = common_parent.GetChildIndex(tree);
			[x, y] = target.LocalToGlobal();
			y = y + target.height / 2;
			if (event.abs_y > y) {
				child_index = child_index + 1;
			}
			this._tab_child.RightControlTreePasteImpl(common_parent, undefined, child_index, revoke_bind, this.HandleDragEndAndCut.bind(this, revoke_bind));
		}
	},
	HandleDragEndAndCut : function(revoke_bind, result, list) {
		if (result === false) {
			return;
		}
		this.TreeCut(revoke_bind);
		this._tab_child.revoke_list.PushRevoke(revoke_bind);
	},
	TransferUp : function() {
		let parent = this._logic_parent;
		if (parent === undefined) {
			return;
		}
		let index = parent.GetChildIndex(this);
		if (index === 1) {
			return;
		}
		index = index - 1;
		parent.SetChildIndex(this, index);
		parent.user_info.object.SetChildIndex(this._user_info.object, index);
		this.tab_child.save = false;
		let revoke = ALittle.NewObject(ALittleIDE.IDEChildUpDownRevoke, parent, this, "up");
		this._tab_child.revoke_list.PushRevoke(revoke);
	},
	TransferDown : function() {
		let parent = this._logic_parent;
		if (parent === undefined) {
			return;
		}
		let index = parent.GetChildIndex(this);
		if (index === parent.child_count) {
			return;
		}
		index = index + 1;
		parent.SetChildIndex(this, index);
		parent.user_info.object.SetChildIndex(this._user_info.object, index);
		this.tab_child.save = false;
		let revoke = ALittle.NewObject(ALittleIDE.IDEChildUpDownRevoke, parent, this, "down");
		this._tab_child.revoke_list.PushRevoke(revoke);
	},
	TreePaste : function(info, child_type, child_index, is_group, revoke_bind) {
		let inner_revoke_bind = ALittle.NewObject(ALittle.RevokeBind);
		if (child_type !== "child" && this._user_info.object[child_type] !== undefined) {
			delete this._user_info.object[child_type];
			let ___OBJECT_1 = this.childs;
			for (let k = 1; k <= ___OBJECT_1.length; ++k) {
				let v = ___OBJECT_1[k - 1];
				if (v === undefined) break;
				if (v.user_info.child_type === child_type) {
					this.RemoveChild(v);
					let revoke = ALittle.NewObject(ALittleIDE.IDEDeleteRevoke, this, v, k);
					inner_revoke_bind.PushRevoke(revoke);
					break;
				}
			}
		}
		let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(this._user_info.module);
		if (ui_manager === undefined) {
			return undefined;
		}
		let control_name = "alittleide201601291343";
		ui_manager.control.RegisterInfo(control_name, ALittle.String_CopyTable(info));
		let object = ui_manager.control.CreateControl(control_name);
		ui_manager.control.UnRegisterInfo(control_name);
		if (child_type === "child") {
			this._user_info.object.AddChild(object, child_index);
		} else {
			this._user_info.object[child_type] = object;
		}
		let tree_object = ALittleIDE.IDEUIUtility_CreateTree(info, this._user_info.module, false, object, child_type, this._tab_child, false);
		this.AddChild(tree_object, child_index);
		this._tab_child.save = false;
		let index = this.GetChildIndex(tree_object);
		let revoke = ALittle.NewObject(ALittleIDE.IDEChildShowRevoke, this, tree_object, index);
		inner_revoke_bind.PushRevoke(revoke);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(inner_revoke_bind);
		} else {
			this.tab_child.revoke_list.PushRevoke(inner_revoke_bind);
		}
		tree_object.ShowFocus(is_group);
		return tree_object;
	},
	TreeAdd : function(extends_module, extends_name, class_name, child_type) {
		let revoke_bind = ALittle.NewObject(ALittle.RevokeBind);
		if (child_type !== "child" && this._user_info.object[child_type] !== undefined) {
			delete this._user_info.object[child_type];
			let ___OBJECT_2 = this.childs;
			for (let k = 1; k <= ___OBJECT_2.length; ++k) {
				let v = ___OBJECT_2[k - 1];
				if (v === undefined) break;
				if (v.user_info.child_type === child_type) {
					this.RemoveChild(v);
					let revoke = ALittle.NewObject(ALittleIDE.IDEDeleteRevoke, this, v, k);
					revoke_bind.PushRevoke(revoke);
					break;
				}
			}
		}
		let tree_object = undefined;
		let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(this._user_info.module);
		if (ui_manager === undefined) {
			return undefined;
		}
		if (extends_name === undefined || extends_name === "") {
			let info = {};
			info.__class = class_name;
			let object = ALittle.NewObject(ALittle[info.__class], ui_manager.control);
			ALittleIDE.IDEUIUtility_NewGiveBaseCase(info, object);
			if (child_type === "child") {
				this._user_info.object.AddChild(object);
			} else {
				this._user_info.object[child_type] = object;
			}
			tree_object = ALittleIDE.IDEUIUtility_CreateTree(info, this._user_info.module, false, object, child_type, this._tab_child, false);
			this.AddChild(tree_object);
			this._tab_child.save = false;
			let index = this.GetChildIndex(tree_object);
			let revoke = ALittle.NewObject(ALittleIDE.IDEChildShowRevoke, this, tree_object, index);
			revoke_bind.PushRevoke(revoke);
			tree_object.ShowAttributePanel();
			this._tab_child.ShowTreeItemFocus(tree_object);
		} else {
			let extends_ui = ALittleIDE.g_IDEProject.GetUIManager(extends_module);
			if (extends_ui === undefined) {
				return undefined;
			}
			let extends_info = ui_manager.control_map[extends_name];
			if (extends_name !== "" && extends_info === undefined) {
				return undefined;
			}
			let info = {};
			info.__module = extends_module;
			info.__extends = extends_name;
			let object = ui_manager.control.CreateControl(extends_name);
			if (child_type === "child") {
				this._user_info.object.AddChild(object);
			} else {
				this._user_info.object[child_type] = object;
			}
			tree_object = ALittleIDE.IDEUIUtility_CreateTree(info, this._user_info.module, false, object, child_type, this._tab_child, false);
			this.AddChild(tree_object);
			this._tab_child.save = false;
			let index = this.GetChildIndex(tree_object);
			let revoke = ALittle.NewObject(ALittleIDE.IDEChildShowRevoke, this, tree_object, index);
			revoke_bind.PushRevoke(revoke);
			tree_object.ShowAttributePanel();
			this._tab_child.ShowTreeItemFocus(tree_object);
		}
		this._tab_child.revoke_list.PushRevoke(revoke_bind);
		return tree_object;
	},
	TreeDelete : function(revoke_bind) {
		let parent = this._logic_parent;
		if (parent === undefined) {
			return;
		}
		let child_type = this._user_info.child_type;
		if (child_type === "child") {
			parent.user_info.object.RemoveChild(this._user_info.object);
		} else {
			delete parent.user_info.object[child_type];
		}
		let index = parent.GetChildIndex(this);
		let revoke = ALittle.NewObject(ALittleIDE.IDEDeleteRevoke, parent, this, index);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
		this._tab_child.save = false;
		parent.RemoveChild(this);
		this.RemoveAttributePanel();
		this._tab_child.UpdateHandleQuadRemove(this);
		this._tab_child.HideHandleQuad(this, true);
		parent.tab_child.UpdateHandleQuadLayout(parent);
	},
	TreeCut : function(revoke_bind) {
		let parent = this._logic_parent;
		if (parent === undefined) {
			return;
		}
		let child_type = this._user_info.child_type;
		if (child_type === "child") {
			parent._user_info.object.RemoveChild(this._user_info.object);
		} else {
			delete parent._user_info.object[child_type];
		}
		let index = parent.GetChildIndex(this);
		let revoke = ALittle.NewObject(ALittleIDE.IDEDeleteRevoke, parent, this, index);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
		this._tab_child.save = false;
		parent.RemoveChild(this);
		this._tab_child.UpdateHandleQuadRemove(this);
		parent.tab_child.UpdateHandleQuadLayout(parent);
	},
	ChangeText : function(text) {
		let object = this._user_info.object;
		let old_base = this._user_info.base.text;
		let old_object = object.text;
		object.text = text;
		this._user_info.base.text = object.text;
		if (this._user_info.base.text === this._user_info.default.text) {
			this._user_info.base.text = undefined;
		}
		if (this._attr_panel !== undefined) {
			let text_object = this._attr_panel["_text"];
			text_object.text = object.text;
		}
		this._tab_child.UpdateHandleQuadLayout(this);
		this._tab_child.save = false;
		let new_base = this._user_info.base.text;
		let new_object = object.text;
		let old_text = undefined;
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this, "text", old_base, new_base, old_object, new_object, old_text, true);
		this._tab_child.revoke_list.PushRevoke(revoke);
	},
	DragXY : function(x, y) {
		let object = this._user_info.object;
		let old_x = object.x;
		let old_y = object.y;
		let target_x = old_x + x;
		let target_y = old_y + y;
		if (object.x_type === 1) {
			object.x_value = target_x;
		} else if (object.x_type === 2) {
			object.x_value = target_x;
		} else if (object.x_type === 3) {
			object.x_value = target_x - (object._show_parent.width - object.width) / 2;
		} else if (object.x_type === 4) {
			object.x_value = object._show_parent.width - object.width - target_x;
		} else if (object.x_type === 7) {
			if (object._show_parent.width === 0) {
				object.x_value = 0;
			} else {
				object.x_value = target_x / object._show_parent.width;
			}
		} else if (object.x_type === 8) {
			if (object._show_parent.width === 0) {
				object.x_value = 0;
			} else {
				object.x_value = (target_x - (object._show_parent.width - object.width) / 2) / object._show_parent.width;
			}
		} else if (object.x_type === 9) {
			if (object._show_parent.width - object.width === 0) {
				object.x_value = 0;
			} else {
				object.x_value = 1 - target_x / (object._show_parent.width - object.width);
			}
		}
		this._user_info.base.x_value = object.x_value;
		if (this._user_info.base.x_value === this._user_info.default.x_value) {
			this._user_info.base.x_value = undefined;
		}
		if (object.y_type === 1) {
			object.y_value = target_y;
		} else if (object.y_type === 2) {
			object.y_value = target_y;
		} else if (object.y_type === 3) {
			object.y_value = target_y - (object._show_parent.height - object.height) / 2;
		} else if (object.y_type === 4) {
			object.y_value = object._show_parent.height - object.height - target_y;
		} else if (object.y_type === 7) {
			if (object._show_parent.height === 0) {
				object.y_value = 0;
			} else {
				object.y_value = target_y / object._show_parent.height;
			}
		} else if (object.y_type === 8) {
			if (object._show_parent.height === 0) {
				object.y_value = 0;
			} else {
				object.y_value = (target_y - (object._show_parent.height - object.height) / 2) / object._show_parent.height;
			}
		} else if (object.y_type === 9) {
			if (object._show_parent.height - object.height === 0) {
				object.y_value = 0;
			} else {
				object.y_value = 1 - target_y / (object._show_parent.height - object.height);
			}
		}
		this._user_info.base.y_value = object.y_value;
		if (this._user_info.base.y_value === this._user_info.default.y_value) {
			this._user_info.base.y_value = undefined;
		}
		if (this._attr_panel !== undefined) {
			this._attr_panel.x_value.text = object.x_value;
			this._attr_panel.y_value.text = object.y_value;
		}
	},
	DragWH : function(width, height) {
		let object = this._user_info.object;
		let old_width = object.width;
		let old_height = object.height;
		let target_width = old_width + width;
		let target_height = old_height + height;
		if (object.width_type === 1) {
			object.width_value = target_width;
		} else if (object.width_type === 4) {
			object.width_value = object._show_parent.width - target_width;
		} else if (object.width_type === 2) {
			if (object._show_parent.width === 0) {
				object.width_value = 0;
			} else {
				object.width_value = target_width / object._show_parent.width;
			}
		}
		this._user_info.base.width_value = object.width_value;
		if (this._user_info.base.width_value === this._user_info.default.width_value) {
			this._user_info.base.width_value = undefined;
		}
		if (object.height_type === 1) {
			object.height_value = target_height;
		} else if (object.height_type === 4) {
			object.height_value = object._show_parent.height - target_height;
		} else if (object.height_type === 2) {
			if (object._show_parent.height === 0) {
				object.height_value = 0;
			} else {
				object.height_value = target_height / object._show_parent.height;
			}
		}
		this._user_info.base.height_value = object.height_value;
		if (this._user_info.base.height_value === this._user_info.default.height_value) {
			this._user_info.base.height_value = undefined;
		}
		if (this._attr_panel !== undefined) {
			this._attr_panel.width_value.text = object.width_value;
			this._attr_panel.height_value.text = object.height_value;
		}
	},
	CopyToClipboard : function() {
		let info = {};
		info.module = this._user_info.module;
		info.index = 1;
		info.info = this.CalcInfo();
		let copy_list = [];
		copy_list[1 - 1] = info;
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list));
	},
	CutToClipboard : function() {
		let info = {};
		info.module = this._user_info.module;
		info.index = 1;
		info.info = this.CalcInfo();
		let copy_list = [];
		copy_list[1 - 1] = info;
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list));
		this.TreeCut();
	},
	PasteFromClipboard : function() {
		if (this.is_tree) {
			this.tab_child.RightControlTreePasteImpl(this);
		} else {
			let common_parent = this.logic_parent;
			let child_index = 1;
			if (common_parent === undefined) {
				common_parent = this;
			} else {
				child_index = common_parent.GetChildIndex(this) + 1;
			}
			this.tab_child.RightControlTreePasteImpl(common_parent, undefined, child_index);
		}
	},
	CalcInfo : function() {
		return undefined;
	},
	SearchLink : function(name, list) {
		return undefined;
	},
	SearchEvent : function(name, list) {
		return undefined;
	},
	SearchDescription : function(name, list) {
		return undefined;
	},
	SearchTargetClass : function(name, list) {
		return undefined;
	},
	SearchTextureName : function(name, list) {
		return undefined;
	},
	EditPickUp : function(x, y) {
		return undefined;
	},
	QuickPickUp : function(x, y, list) {
	},
	SelectPickUp : function(x, y) {
		return [undefined, undefined];
	},
	SelectPickRange : function(min_x, min_y, max_x, max_y) {
		if (this._user_info.extends) {
			return false;
		}
		let object = this._user_info.object;
		let [pick_this_1, rel_min_x, rel_min_y] = object.PickUpSelf(min_x, min_y);
		let [pick_this_2, rel_max_x, rel_max_y] = object.PickUpSelf(max_x, max_y);
		if (rel_min_x >= object.width) {
			return false;
		}
		if (rel_max_x < 0) {
			return false;
		}
		if (rel_min_y >= object.height) {
			return false;
		}
		if (rel_max_y < 0) {
			return false;
		}
		return true;
	},
	GetDataListForAdd : function() {
		return undefined;
	},
	GenerateClassMember : function(list) {
	},
}, "ALittleIDE.IDEUITreeLogic");

}