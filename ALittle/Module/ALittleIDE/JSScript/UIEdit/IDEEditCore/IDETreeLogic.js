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
ALittleIDE.IDETreeLogic = JavaScript.Class(ALittle.DisplayLayout, {
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
	IsRoot : function() {
		return this._user_info.root;
	},
	IsTree : function() {
		return false;
	},
	get attr_panel() {
		return this._attr_panel;
	},
	get title() {
		return this._item_title.text;
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
		this._tab_child.Save(false);
		this.UpdateDesc();
	},
	UpdateDesc : function() {
	},
	RemoveAttributePanel : function() {
		if (this._attr_panel === undefined) {
			return;
		}
		this._tab_child.control_screen.RemoveChild(this._attr_panel.layer);
		ALittleIDE.g_IDEAttributeManager.SetTitle("");
	},
	ShowAttributePanel : function() {
		this._tab_child.control_screen.RemoveAllChild();
		this._item_button.selected = true;
		if (this._attr_panel === undefined) {
			let class_name = this._user_info.default.__class + "S";
			let clazz = ALittleIDE[class_name];
			this._attr_panel = ALittle.NewObject(clazz, this._user_info, this._tab_child, this);
			this._attr_panel.layer._user_data = this._attr_panel;
			this._attr_panel.layer.disabled = this._user_info.extends;
		}
		ALittleIDE.g_IDEAttributeManager.SetTitle(this._attr_panel.title);
		this._tab_child.control_screen.AddChild(this._attr_panel.layer);
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
	HandleMoveIn : function(event) {
	},
	HandleMouseMove : function(event) {
	},
	HandleMoveOut : function(event) {
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
			ALittle.Log("IDETreeLogic:HandleDrag} target null");
			return;
		}
		let tree = target._user_data;
		if (tree.IsGrandParent(this)) {
			ALittleIDE.g_IDETool.ShowNotice("提示", "目标是自己的子控件，移动失败");
			return;
		}
		if (tree._user_info.extends) {
			ALittleIDE.g_IDETool.ShowNotice("提示", "目标控件不能操作，移动失败");
			return;
		}
		let copy_list = [];
		let info = {};
		info.index = 1;
		info.info = this.CalcInfo();
		copy_list[1 - 1] = info;
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list));
		let revoke_bind = ALittle.NewObject(ALittleIDE.IDERevokeBind);
		if (tree.IsTree()) {
			this._tab_child.RightControlTreePasteImpl(tree, undefined, 1, revoke_bind, this.HandleDragEndAndCut.bind(this, revoke_bind));
		} else {
			let common_parent = tree._logic_parent;
			if (common_parent === undefined) {
				ALittleIDE.g_IDETool.ShowNotice("提示", "当前是根节点，并且不是容器，移动失败");
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
		this.tab_child.Save(false);
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
		this.tab_child.Save(false);
		let revoke = ALittle.NewObject(ALittleIDE.IDEChildUpDownRevoke, parent, this, "down");
		this._tab_child.revoke_list.PushRevoke(revoke);
	},
	TreePaste : function(info, child_type, child_index, is_group, revoke_bind) {
		let inner_revoke_bind = ALittle.NewObject(ALittleIDE.IDERevokeBind);
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
		let control_name = "alittleide201601291343";
		ALittleIDE.g_IDEProject.project.control.RegisterInfo(control_name, ALittle.String_CopyTable(info));
		let object = ALittleIDE.g_IDEProject.project.control.CreateControl(control_name);
		ALittleIDE.g_IDEProject.project.control.UnRegisterInfo(control_name);
		if (child_type === "child") {
			this._user_info.object.AddChild(object, child_index);
		} else {
			this._user_info.object[child_type] = object;
		}
		let tree_object = ALittleIDE.IDEUtility_CreateTree(info, false, object, child_type, this._tab_child, false);
		this.AddChild(tree_object, child_index);
		this._tab_child.Save(false);
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
	TreeAdd : function(extends_name, class_name, child_type) {
		let extends_info = ALittleIDE.g_IDEProject.project.control_map[extends_name];
		if (extends_name !== "" && extends_info === undefined) {
			return undefined;
		}
		let revoke_bind = ALittle.NewObject(ALittleIDE.IDERevokeBind);
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
		if (extends_info === undefined) {
			let info = {};
			info.__class = class_name;
			let object = ALittle.NewObject(ALittle[info.__class], ALittleIDE.g_IDEProject.project.control);
			ALittleIDE.IDEUtility_NewGiveBaseCase(info, object);
			if (child_type === "child") {
				this._user_info.object.AddChild(object);
			} else {
				this._user_info.object[child_type] = object;
			}
			tree_object = ALittleIDE.IDEUtility_CreateTree(info, false, object, child_type, this._tab_child, false);
			this.AddChild(tree_object);
			this._tab_child.Save(false);
			let index = this.GetChildIndex(tree_object);
			let revoke = ALittle.NewObject(ALittleIDE.IDEChildShowRevoke, this, tree_object, index);
			revoke_bind.PushRevoke(revoke);
			tree_object.ShowAttributePanel();
			this._tab_child.ShowTreeItemFocus(tree_object);
		} else {
			let info = {};
			info.__extends = extends_name;
			let object = ALittleIDE.g_IDEProject.project.control.CreateControl(extends_name);
			if (child_type === "child") {
				this._user_info.object.AddChild(object);
			} else {
				this._user_info.object[child_type] = object;
			}
			tree_object = ALittleIDE.IDEUtility_CreateTree(info, false, object, child_type, this._tab_child, false);
			this.AddChild(tree_object);
			this._tab_child.Save(false);
			let index = this.GetChildIndex(tree_object);
			let revoke = ALittle.NewObject(ALittleIDE.IDEChildShowRevoke, this, tree_object, index);
			revoke_bind.PushRevoke(revoke);
			tree_object.ShowAttributePanel();
			this._tab_child.ShowTreeItemFocus(tree_object);
		}
		this._tab_child.revoke_list.PushRevoke(revoke_bind);
		return tree_object;
	},
	TreeReplace : function(extends_name, class_name, child_type) {
		let extends_info = ALittleIDE.g_IDEProject.project.control_map[extends_name];
		if (extends_name !== "" && extends_info === undefined) {
			return;
		}
		let revoke_bind = ALittle.NewObject(ALittleIDE.IDERevokeBind);
		let target_parent = this._logic_parent;
		let child_index = undefined;
		if (this._user_info.child_type !== "child") {
			delete target_parent._user_info.object[child_type];
			let ___OBJECT_3 = target_parent.childs;
			for (let k = 1; k <= ___OBJECT_3.length; ++k) {
				let v = ___OBJECT_3[k - 1];
				if (v === undefined) break;
				if (v._user_info.child_type === child_type) {
					target_parent.RemoveChild(v);
					let revoke = ALittle.NewObject(ALittleIDE.IDEDeleteRevoke, target_parent, v, k);
					revoke_bind.PushRevoke(revoke);
					break;
				}
			}
		} else {
			child_index = target_parent.GetChildIndex(this);
			target_parent._user_info.object.RemoveChild(this._user_info.object);
			target_parent.RemoveChild(this);
			let revoke = ALittle.NewObject(ALittleIDE.IDEDeleteRevoke, target_parent, this, child_index);
			revoke_bind.PushRevoke(revoke);
		}
		let tree_object = undefined;
		if (extends_info === undefined) {
			let info = {};
			info.__class = class_name;
			let object = ALittle.NewObject(ALittle[info.__class], ALittleIDE.g_IDEProject.project.control);
			ALittleIDE.IDEUtility_NewGiveBaseCase(info, object);
			if (child_type === "child") {
				target_parent._user_info.object.AddChild(object, child_index);
			} else {
				target_parent._user_info.object[child_type] = object;
			}
			tree_object = ALittleIDE.IDEUtility_CreateTree(info, false, object, child_type, target_parent._tab_child, false);
			target_parent.AddChild(tree_object, child_index);
			target_parent._tab_child.Save(false);
			let index = target_parent.GetChildIndex(tree_object);
			let revoke = ALittle.NewObject(ALittleIDE.IDEChildShowRevoke, target_parent, tree_object, index);
			revoke_bind.PushRevoke(revoke);
		} else {
			let info = {};
			info.__extends = extends_name;
			let object = ALittleIDE.g_IDEProject.project.control.CreateControl(extends_name);
			if (child_type === "child") {
				target_parent._user_info.object.AddChild(object, child_index);
			} else {
				target_parent._user_info.object[child_type] = object;
			}
			tree_object = ALittleIDE.IDEUtility_CreateTree(info, false, object, child_type, target_parent._tab_child, false);
			target_parent.AddChild(tree_object, child_index);
			target_parent._tab_child.Save(false);
			let index = target_parent.GetChildIndex(tree_object);
			let revoke = ALittle.NewObject(ALittleIDE.IDEChildShowRevoke, target_parent, tree_object, index);
			revoke_bind.PushRevoke(revoke);
		}
		tree_object.ShowAttributePanel();
		if (this._user_info.base.x_type !== undefined) {
			tree_object._attr_panel.SetXType(this._user_info.base.x_type, revoke_bind);
		} else {
			tree_object._attr_panel.SetXType(this._user_info.default.x_type, revoke_bind);
		}
		if (this._user_info.base.y_type !== undefined) {
			tree_object._attr_panel.SetYType(this._user_info.base.y_type, revoke_bind);
		} else {
			tree_object._attr_panel.SetYType(this._user_info.default.y_type, revoke_bind);
		}
		if (this._user_info.base.x_value !== undefined) {
			tree_object._attr_panel.SetXValue(this._user_info.base.x_value, revoke_bind);
		} else {
			tree_object._attr_panel.SetXValue(this._user_info.default.x_value, revoke_bind);
		}
		if (this._user_info.base.y_value !== undefined) {
			tree_object._attr_panel.SetYValue(this._user_info.base.y_value, revoke_bind);
		} else {
			tree_object._attr_panel.SetYValue(this._user_info.default.y_value, revoke_bind);
		}
		if (this._user_info.base.width_type !== undefined) {
			tree_object._attr_panel.SetWType(this._user_info.base.width_type, revoke_bind);
		} else {
			tree_object._attr_panel.SetWType(this._user_info.default.width_type, revoke_bind);
		}
		if (this._user_info.base.height_type !== undefined) {
			tree_object._attr_panel.SetHType(this._user_info.base.height_type, revoke_bind);
		} else {
			tree_object._attr_panel.SetHType(this._user_info.default.height_type, revoke_bind);
		}
		if (this._user_info.base.width_value !== undefined) {
			tree_object._attr_panel.SetWValue(this._user_info.base.width_value, revoke_bind);
		} else {
			tree_object._attr_panel.SetWValue(this._user_info.default.width_value, revoke_bind);
		}
		if (this._user_info.base.height_value !== undefined) {
			tree_object._attr_panel.SetHValue(this._user_info.base.height_value, revoke_bind);
		} else {
			tree_object._attr_panel.SetHValue(this._user_info.default.height_value, revoke_bind);
		}
		if (this._user_info.base.alpha !== undefined) {
			tree_object._attr_panel.SetAlpha(this._user_info.base.alpha * 255, revoke_bind);
		} else {
			tree_object._attr_panel.SetAlpha(this._user_info.default.alpha * 255, revoke_bind);
		}
		if (this._user_info.base.red !== undefined) {
			tree_object._attr_panel.SetRed(this._user_info.base.red * 255, revoke_bind);
		} else {
			tree_object._attr_panel.SetRed(this._user_info.default.red * 255, revoke_bind);
		}
		if (this._user_info.base.green !== undefined) {
			tree_object._attr_panel.SetGreen(this._user_info.base.green * 255, revoke_bind);
		} else {
			tree_object._attr_panel.SetGreen(this._user_info.default.green * 255, revoke_bind);
		}
		if (this._user_info.base.blue !== undefined) {
			tree_object._attr_panel.SetBlue(this._user_info.base.blue * 255, revoke_bind);
		} else {
			tree_object._attr_panel.SetBlue(this._user_info.default.blue * 255, revoke_bind);
		}
		if (this._user_info.base.scale_x !== undefined) {
			tree_object._attr_panel.SetScaleX(this._user_info.base.scale_x, revoke_bind);
		} else {
			tree_object._attr_panel.SetScaleX(this._user_info.default.scale_x, revoke_bind);
		}
		if (this._user_info.base.scale_y !== undefined) {
			tree_object._attr_panel.SetScaleY(this._user_info.base.scale_y, revoke_bind);
		} else {
			tree_object._attr_panel.SetScaleY(this._user_info.default.scale_y, revoke_bind);
		}
		if (this._user_info.base.center_x !== undefined) {
			tree_object._attr_panel.SetCenterX(this._user_info.base.center_x, revoke_bind);
		} else {
			tree_object._attr_panel.SetCenterX(this._user_info.default.center_x, revoke_bind);
		}
		if (this._user_info.base.center_y !== undefined) {
			tree_object._attr_panel.SetCenterY(this._user_info.base.center_y, revoke_bind);
		} else {
			tree_object._attr_panel.SetCenterY(this._user_info.default.center_y, revoke_bind);
		}
		if (this._user_info.base.angle !== undefined) {
			tree_object._attr_panel.SetAngle(this._user_info.base.angle, revoke_bind);
		} else {
			tree_object._attr_panel.SetAngle(this._user_info.default.angle, revoke_bind);
		}
		if (this._user_info.base.hand_cursor !== undefined) {
			tree_object._attr_panel.SetHandCursor(this._user_info.base.hand_cursor, revoke_bind);
		} else {
			tree_object._attr_panel.SetHandCursor(this._user_info.default.hand_cursor, revoke_bind);
		}
		if (this._user_info.base.visible !== undefined) {
			tree_object._attr_panel.SetVisible(this._user_info.base.visible, revoke_bind);
		} else {
			tree_object._attr_panel.SetVisible(this._user_info.default.visible, revoke_bind);
		}
		if (this._user_info.base.disabled !== undefined) {
			tree_object._attr_panel.SetDisabled(this._user_info.base.disabled, revoke_bind);
		} else {
			tree_object._attr_panel.SetDisabled(this._user_info.default.disabled, revoke_bind);
		}
		if (this._user_info.base.description !== undefined) {
			tree_object._attr_panel.SetDescription(this._user_info.base.description, revoke_bind);
		} else {
			tree_object._attr_panel.SetDescription(this._user_info.default.description, revoke_bind);
		}
		if (this._user_info.base.__link !== undefined) {
			tree_object._attr_panel.SetLink(this._user_info.base.__link, revoke_bind);
		} else {
			tree_object._attr_panel.SetLink(this._user_info.default.__link, revoke_bind);
		}
		if (this._user_info.base.__target_class !== undefined) {
			tree_object._attr_panel.SetTargetClass(this._user_info.base.__target_class, revoke_bind);
		} else {
			tree_object._attr_panel.SetTargetClass(this._user_info.default.__target_class, revoke_bind);
		}
		if (this._user_info.base.__event !== undefined) {
			tree_object._attr_panel.SetEvent(this._user_info.base.__event, revoke_bind);
		} else {
			tree_object._attr_panel.SetEvent(this._user_info.default.__event, revoke_bind);
		}
		this._tab_child.ShowTreeItemFocus(tree_object);
		target_parent._tab_child.revoke_list.PushRevoke(revoke_bind);
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
		this._tab_child.Save(false);
		parent.RemoveChild(this);
		this.RemoveAttributePanel();
		this._tab_child.UpdateHandleQuadRemove(this);
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
		this._tab_child.Save(false);
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
		this._tab_child.Save(false);
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
	GetDataListForAdd : function() {
		return undefined;
	},
}, "ALittleIDE.IDETreeLogic");

}