{
if (typeof ALittleIDE === "undefined") ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(444989011, "ALittle.UISelectChangedEvent", {
name : "ALittle.UISelectChangedEvent", ns_name : "ALittle", rl_name : "UISelectChangedEvent", hash_code : 444989011,
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
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(882286932, "ALittle.UIKeyEvent", {
name : "ALittle.UIKeyEvent", ns_name : "ALittle", rl_name : "UIKeyEvent", hash_code : 882286932,
name_list : ["target","mod","sym","scancode","custom","handled"],
type_list : ["ALittle.DisplayObject","int","int","int","bool","bool"],
option_map : {}
})
ALittle.RegStruct(-1604617962, "ALittle.UIKeyDownEvent", {
name : "ALittle.UIKeyDownEvent", ns_name : "ALittle", rl_name : "UIKeyDownEvent", hash_code : -1604617962,
name_list : ["target","mod","sym","scancode","custom","handled"],
type_list : ["ALittle.DisplayObject","int","int","int","bool","bool"],
option_map : {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name : "ALittle.UIClickEvent", ns_name : "ALittle", rl_name : "UIClickEvent", hash_code : -449066808,
name_list : ["target","is_drag"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})

ALittleIDE.IDETabManager = JavaScript.Class(undefined, {
	Setup : function(tab, tree, control, anti) {
		this._main_tab = tab;
		this._main_tree = tree;
		this._main_control = control;
		this._main_anti = anti;
		this._main_tab.AddEventListener(___all_struct.get(444989011), this, this.HandleMainTabSelectChange);
		this._main_tab.AddEventListener(___all_struct.get(-641444818), this, this.HandleMainTabRightClick);
		this._main_tab.AddEventListener(___all_struct.get(-1604617962), this, this.HandleMainTabKeyDown);
		this._main_tab.close_callback = this.MainTabTabCloseYesOrNot.bind(this);
		this._main_tab.close_post_callback = this.MainTabTabClose.bind(this);
		this._cur_tab = undefined;
	},
	Shutdown : function() {
	},
	get main_control() {
		return this._main_control;
	},
	get main_anti() {
		return this._main_anti;
	},
	get main_tab() {
		return this._main_tab;
	},
	get cur_tab() {
		return this._cur_tab;
	},
	get cur_tab_child() {
		if (this._cur_tab === undefined) {
			return undefined;
		}
		return this._cur_tab._user_data;
	},
	GetTabByName : function(name) {
		let tab_childs = this._main_tab.childs;
		let ___OBJECT_1 = tab_childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			if (child._user_data.name === name) {
				return child;
			}
		}
		return undefined;
	},
	GetTabNameMap : function() {
		let info = {};
		let tab_childs = this._main_tab.childs;
		let ___OBJECT_2 = tab_childs;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let child = ___OBJECT_2[index - 1];
			if (child === undefined) break;
			info[child._user_data.name] = true;
		}
		return info;
	},
	GetTabNameList : function() {
		let info = [];
		let tab_childs = this._main_tab.childs;
		let ___OBJECT_3 = tab_childs;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let child = ___OBJECT_3[index - 1];
			if (child === undefined) break;
			ALittle.List_Push(info, child._user_data.name);
		}
		return info;
	},
	GetCurTabIndex : function() {
		return this._main_tab.tab_index;
	},
	SetCurTabIndex : function(index) {
		if (this._main_tab.tab_index === index) {
			return;
		}
		this._main_tab.tab_index = index;
		this.ChangeTabEditControl(this._cur_tab, this._main_tab.tab);
	},
	IsSaveAll : function() {
		let tab_childs = this._main_tab.childs;
		let ___OBJECT_4 = tab_childs;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let child = ___OBJECT_4[index - 1];
			if (child === undefined) break;
			if (child._user_data.save === false) {
				return false;
			}
		}
		return true;
	},
	ChangeTabEditControl : function(child_from, child_to) {
		if (child_from === child_to) {
			return;
		}
		if (child_from !== undefined) {
			let tab_child = child_from._user_data;
			tab_child.tree_screen.visible = false;
			tab_child.control_screen.visible = false;
			tab_child.anti_panel.visible = false;
			ALittleIDE.g_IDEAttributeManager.SetTitle("");
		}
		if (child_to !== undefined) {
			let tab_child = child_to._user_data;
			tab_child.tree_screen.visible = true;
			tab_child.control_screen.visible = true;
			tab_child.anti_panel.visible = true;
			let panel_childs = tab_child.control_screen.childs;
			if (panel_childs[1 - 1] !== undefined) {
				ALittleIDE.g_IDEAttributeManager.SetTitle(panel_childs[1 - 1]._user_data.title);
			}
			ALittleIDE.g_IDEUICenter.UpdateToolScale(tab_child.GetScale());
		}
		this._cur_tab = child_to;
	},
	CloseTab : function(child) {
		let tab_child = child._user_data;
		this._main_tree.RemoveChild(tab_child.tree_screen);
		this._main_control.RemoveChild(tab_child.control_screen);
		this._main_anti.RemoveChild(tab_child.anti_panel);
		this._main_tab.RemoveChild(child);
		this.ChangeTabEditControl(child, this._main_tab.tab);
	},
	RefreshTab : function(child) {
		let tab_child = child._user_data;
		let tab_index = this._main_tab.GetChildIndex(child);
		this.CloseTab(child);
		let name = tab_child.name;
		let control_info = ALittleIDE.g_IDEProject.project.control_map[name];
		let new_tab_child = this.StartEditControlBySelect(control_info.name, control_info.info);
		this._main_tab.SetChildIndex(new_tab_child.tab_body, tab_index);
	},
	CloseAllTab : function() {
		this.ChangeTabEditControl(this._main_tab.tab, undefined);
		let ___OBJECT_5 = this._main_tab.childs;
		for (let k = 1; k <= ___OBJECT_5.length; ++k) {
			let child = ___OBJECT_5[k - 1];
			if (child === undefined) break;
			let tab_child = child._user_data;
			this._main_tree.RemoveChild(tab_child.tree_screen);
			this._main_control.RemoveChild(tab_child.control_screen);
			this._main_anti.RemoveChild(tab_child.anti_panel);
		}
		this._main_tab.RemoveAllChild();
	},
	SaveAllTab : function() {
		let ___OBJECT_6 = this._main_tab.childs;
		for (let k = 1; k <= ___OBJECT_6.length; ++k) {
			let child = ___OBJECT_6[k - 1];
			if (child === undefined) break;
			let tab_child = child._user_data;
			tab_child.Save(true);
		}
	},
	SetTabChildWH : function(width, height) {
		let ___OBJECT_7 = this._main_tab.childs;
		for (let k = 1; k <= ___OBJECT_7.length; ++k) {
			let child = ___OBJECT_7[k - 1];
			if (child === undefined) break;
			let tab_child = child._user_data;
			tab_child.SetEditWH(width, height);
		}
	},
	ShowTabChildSelectLayer : function(value) {
		let ___OBJECT_8 = this._main_tab.childs;
		for (let k = 1; k <= ___OBJECT_8.length; ++k) {
			let child = ___OBJECT_8[k - 1];
			if (child === undefined) break;
			let tab_child = child._user_data;
			tab_child.ShowSelectLayer(value);
		}
	},
	ShowTabChildHandDragLayer : function(value) {
		let ___OBJECT_9 = this._main_tab.childs;
		for (let k = 1; k <= ___OBJECT_9.length; ++k) {
			let child = ___OBJECT_9[k - 1];
			if (child === undefined) break;
			let tab_child = child._user_data;
			tab_child.ShowHandDragLayer(value);
		}
	},
	ShowTabChildScaleLayer : function(value) {
		let ___OBJECT_10 = this._main_tab.childs;
		for (let k = 1; k <= ___OBJECT_10.length; ++k) {
			let child = ___OBJECT_10[k - 1];
			if (child === undefined) break;
			let tab_child = child._user_data;
			tab_child.ShowScaleLayer(value);
		}
	},
	CanDelete : function(name) {
		let ___OBJECT_11 = this._main_tab.childs;
		for (let k = 1; k <= ___OBJECT_11.length; ++k) {
			let child = ___OBJECT_11[k - 1];
			if (child === undefined) break;
			let tab_child = child._user_data;
			let [result, content] = tab_child.CanDeleteControl(name);
			if (result === false) {
				return [result, content];
			}
		}
		return [true, undefined];
	},
	HandleMainTabSelectChange : function(event) {
		this.ChangeTabEditControl(this._cur_tab, this._main_tab.tab);
	},
	MainTabTabClose : function(child) {
		this.CloseTab(child);
	},
	TabChildSave : function(tab_child, save) {
		tab_child.Save(save);
	},
	MainTabTabCloseYesOrNot : function(child) {
		let tab_child = child._user_data;
		if (tab_child.save) {
			return true;
		}
		let cancel_callback = this.CloseTab.bind(this, child);
		let confirm_callback = ALittleIDE.IDETabManager.TabChildSave.bind(undefined, tab_child, true);
		ALittleIDE.g_IDETool.SaveNotice("提示", "是否保存当前控件?", cancel_callback, confirm_callback);
		return false;
	},
	HandleMainTabRightClick : function(event) {
		this.ShowTabRightMenu(event.target);
	},
	HandleMainTabKeyDown : function(event) {
		if (event.sym === 1073741883) {
			this.ControlRenameImpl(event.target);
			event.handled = true;
			return;
		}
		if (event.sym === 1073741886) {
			let child = event.target;
			let tab_child = child._user_data;
			if (tab_child.save) {
				this.RefreshTab(child);
				event.handled = true;
				return;
			}
			let cancel_callback = this.RefreshTab.bind(this, child);
			let confirm_callback = ALittleIDE.IDETabManager.TabChildSave.bind(undefined, tab_child, true);
			ALittleIDE.g_IDETool.SaveNotice("提示", "是否保存当前控件?", cancel_callback, confirm_callback);
			event.handled = true;
			return;
		}
	},
	ShowTabRightMenu : function(child) {
		if (this._main_tab_menu === undefined) {
			this._main_tab_menu = ALittleIDE.g_Control.CreateControl("ide_tab_right_menu", this);
		}
		this._main_tab_menu.x = A_UISystem.mouse_x;
		this._main_tab_menu.y = A_UISystem.mouse_y;
		this._main_tab_menu._user_data = child;
		A_LayerManager.ShowFromRight(this._main_tab_menu);
	},
	ShowTabRightExMenu : function(x, y) {
		let tab_childs = this._main_tab.childs;
		if (tab_childs[1 - 1] === undefined) {
			return;
		}
		if (this._tab_right_exmenu === undefined) {
			this._tab_right_exmenu = ALittleIDE.g_Control.CreateControl("ide_dynamic_menu", this);
		}
		this._tab_right_exlinear.RemoveAllChild();
		let ___OBJECT_12 = tab_childs;
		for (let index = 1; index <= ___OBJECT_12.length; ++index) {
			let child = ___OBJECT_12[index - 1];
			if (child === undefined) break;
			let item = ALittleIDE.g_Control.CreateControl("ide_common_item_button");
			item.AddEventListener(___all_struct.get(-449066808), this, this.HandleTabRightExItemClick);
			item._user_data = child;
			let tab_child = child._user_data;
			item.text = tab_child.total_title;
			this._tab_right_exlinear.AddChild(item);
		}
		this._tab_right_exmenu.height = this._tab_right_exlinear.height + 2;
		if (x + this._tab_right_exmenu.width > A_UISystem.view_width) {
			x = A_UISystem.view_width - this._tab_right_exmenu.width;
		}
		this._tab_right_exmenu.x = x;
		this._tab_right_exmenu.y = y;
		A_LayerManager.ShowFromRight(this._tab_right_exmenu);
	},
	HandleTabRightExItemClick : function(event) {
		A_LayerManager.HideFromRight(this._tab_right_exmenu);
		let child_from = this._main_tab.tab;
		let child_to = event.target._user_data;
		this._main_tab.SetChildIndex(child_to, 1);
		this._main_tab.tab = child_to;
		this.ChangeTabEditControl(child_from, child_to);
	},
	HandleTabRightMenu : function(event) {
		let child = this._main_tab_menu._user_data;
		let tab_child = child._user_data;
		this._main_tab_menu._user_data = undefined;
		A_LayerManager.HideFromRight(this._main_tab_menu);
		let handle_name = event.target.text;
		if (handle_name === "保存") {
			tab_child.Save(true);
			return;
		}
		if (handle_name === "刷新") {
			if (tab_child.save) {
				this.RefreshTab(child);
				return;
			}
			let cancel_callback = this.RefreshTab.bind(this, child);
			let confirm_callback = ALittleIDE.IDETabManager.TabChildSave.bind(undefined, tab_child, true);
			ALittleIDE.g_IDETool.SaveNotice("提示", "是否保存当前控件?", cancel_callback, confirm_callback);
			return;
		}
		if (handle_name === "关闭自己") {
			if (tab_child.save) {
				this.CloseTab(child);
				return;
			}
			let cancel_callback = this.CloseTab.bind(this, child);
			let confirm_callback = ALittleIDE.IDETabManager.TabChildSave.bind(undefined, tab_child, true);
			ALittleIDE.g_IDETool.SaveNotice("提示", "是否保存当前控件?", cancel_callback, confirm_callback);
			return;
		}
		if (handle_name === "复制控件名") {
			ALittle.System_SetClipboardText(tab_child.name);
			return;
		}
		if (handle_name === "复制继承代码") {
			let name = tab_child.name;
			let display_info = {};
			display_info.__extends = name;
			let copy_list = [];
			let info = {};
			info.index = 1;
			info.info = display_info;
			copy_list[1 - 1] = info;
			ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list));
			return;
		}
		if (handle_name === "关闭左侧") {
			let close_list = [];
			let ___OBJECT_13 = this._main_tab.childs;
			for (let index = 1; index <= ___OBJECT_13.length; ++index) {
				let child_v = ___OBJECT_13[index - 1];
				if (child_v === undefined) break;
				if (child_v === child) {
					break;
				}
				tab_child = child_v._user_data;
				if (tab_child.save) {
					ALittle.List_Push(close_list, child_v);
				}
			}
			let ___OBJECT_14 = close_list;
			for (let index = 1; index <= ___OBJECT_14.length; ++index) {
				let child_v = ___OBJECT_14[index - 1];
				if (child_v === undefined) break;
				this.CloseTab(child_v);
			}
			return;
		}
		if (handle_name === "关闭右侧") {
			let close_list = [];
			let child_list = this._main_tab.childs;
			let cur_index = this._main_tab.GetChildIndex(child);
			let child_count = this._main_tab.child_count;
			for (let index = cur_index + 1; index <= child_count; index += 1) {
				let child_v = child_list[index - 1];
				tab_child = child_v._user_data;
				if (tab_child.save) {
					ALittle.List_Push(close_list, child_v);
				}
			}
			let ___OBJECT_15 = close_list;
			for (let index = 1; index <= ___OBJECT_15.length; ++index) {
				let child_v = ___OBJECT_15[index - 1];
				if (child_v === undefined) break;
				this.CloseTab(child_v);
			}
			return;
		}
		if (handle_name === "运行") {
			ALittleIDE.g_IDEControlManager.ControlRunImpl(tab_child.name);
			return;
		}
		if (handle_name === "修改控件名") {
			this.ControlRenameImpl(child);
			return;
		}
	},
	ControlRenameImpl : function(child) {
		let tab_child = child._user_data;
		let name = tab_child.name;
		let [result, content] = ALittleIDE.g_IDEProject.CanDelete(name);
		if (result === false) {
			ALittleIDE.g_IDETool.ShowNotice("错误", content);
			return;
		}
		[result, content] = ALittleIDE.g_IDETabManager.CanDelete(name);
		if (result === false) {
			ALittleIDE.g_IDETool.ShowNotice("错误", content);
			return;
		}
		let layout = this._main_tab.GetChildHead(child);
		let [x, y] = layout.LocalToGlobal();
		let width = layout.width;
		if (width < 150) {
			width = 150;
		}
		let callback = this.ControlRename.bind(this, name);
		ALittleIDE.g_IDETool.ShowRename(callback, name, x, y, width);
	},
	ControlRename : function(old_name, new_name) {
		if (old_name === new_name) {
			return;
		}
		let [result, content] = ALittleIDE.g_IDEProject.RenameControl(old_name, new_name);
		if (result === false) {
			ALittleIDE.g_IDETool.ShowNotice("错误", content);
			return;
		}
		let tab = ALittleIDE.g_IDETabManager.GetTabByName(old_name);
		if (tab === undefined) {
			return;
		}
		let tab_child = tab._user_data;
		tab_child.Rename(new_name);
	},
	StartEditControlByNew : function(name, type) {
		let child_from = this._main_tab.tab;
		let tab_child = ALittle.NewObject(ALittleIDE.IDETabChild, name, false);
		tab_child.CreateByNew(type);
		this._main_tab.AddChild(tab_child.tab_body);
		this._main_tree.AddChild(tab_child.tree_screen);
		this._main_control.AddChild(tab_child.control_screen);
		this._main_anti.AddChild(tab_child.anti_panel);
		this._main_tab.tab = tab_child.tab_body;
		this.ChangeTabEditControl(child_from, tab_child.tab_body);
		tab_child.UpdateTitle();
		tab_child.ShowHandleQuad(tab_child.tree_object);
		return tab_child;
	},
	StartEditControlByExtends : function(name, extends_v) {
		let child_from = this._main_tab.tab;
		let tab_child = ALittle.NewObject(ALittleIDE.IDETabChild, name, false);
		tab_child.CreateByExtends(extends_v);
		this._main_tab.AddChild(tab_child.tab_body);
		this._main_tree.AddChild(tab_child.tree_screen);
		this._main_control.AddChild(tab_child.control_screen);
		this._main_anti.AddChild(tab_child.anti_panel);
		this._main_tab.tab = tab_child.tab_body;
		this.ChangeTabEditControl(child_from, tab_child.tab_body);
		tab_child.UpdateTitle();
		tab_child.ShowHandleQuad(tab_child.tree_object);
		return tab_child;
	},
	StartEditControlBySelect : function(name, info) {
		let child = this.GetTabByName(name);
		if (child !== undefined) {
			let child_from = this._main_tab.tab;
			this._main_tab.tab = child;
			this.ChangeTabEditControl(child_from, child);
			return child._user_data;
		}
		let child_from = this._main_tab.tab;
		let tab_child = ALittle.NewObject(ALittleIDE.IDETabChild, name, true);
		tab_child.CreateBySelect(info);
		this._main_tab.AddChild(tab_child.tab_body, 1);
		this._main_tree.AddChild(tab_child.tree_screen);
		this._main_control.AddChild(tab_child.control_screen);
		this._main_anti.AddChild(tab_child.anti_panel);
		this._main_tab.tab = tab_child.tab_body;
		this.ChangeTabEditControl(child_from, tab_child.tab_body);
		tab_child.UpdateTitle();
		if (tab_child.tree_object.IsTree() === false) {
			tab_child.ShowHandleQuad(tab_child.tree_object);
		}
		return tab_child;
	},
}, "ALittleIDE.IDETabManager");

ALittleIDE.g_IDETabManager = ALittle.NewObject(ALittleIDE.IDETabManager);
}