{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
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
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name : "ALittle.UIButtonEvent", ns_name : "ALittle", rl_name : "UIButtonEvent", hash_code : -1347278145,
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
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(444989011, "ALittle.UISelectChangedEvent", {
name : "ALittle.UISelectChangedEvent", ns_name : "ALittle", rl_name : "UISelectChangedEvent", hash_code : 444989011,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-338112738, "ALittle.UIDropFileEvent", {
name : "ALittle.UIDropFileEvent", ns_name : "ALittle", rl_name : "UIDropFileEvent", hash_code : -338112738,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
option_map : {}
})

if (ALittle.UIEventDispatcher === undefined) throw new Error(" extends class:ALittle.UIEventDispatcher is undefined");
ALittleIDE.IDETabChild = JavaScript.Class(ALittle.UIEventDispatcher, {
	Ctor : function(ctrl_sys, module, name, save) {
		this._name = name;
		this._module = module;
		this._save = save;
		this._revoke_list = ALittle.NewObject(ALittle.RevokeList, 10000);
	},
	get id() {
		return this._name;
	},
	get name() {
		return this._name;
	},
	get module() {
		return this._module;
	},
	get save() {
		return this._save;
	},
	set save(value) {
	},
	Save : function() {
		this.save = true;
	},
	get revoke_list() {
		return this._revoke_list;
	},
	get title() {
		return this._name;
	},
	get tab_body() {
		return undefined;
	},
	OnUndo : function() {
	},
	OnRedo : function() {
	},
	OnHide : function() {
	},
	OnShow : function() {
	},
	OnClose : function() {
	},
	OnOpen : function() {
	},
	OnTabRightMenu : function(menu) {
	},
}, "ALittleIDE.IDETabChild");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEContentEdit = JavaScript.Class(ALittle.DisplayLayout, {
	TCtor : function() {
		this._main_tab.AddEventListener(___all_struct.get(444989011), this, this.HandleMainTabSelectChange);
		this._main_tab.AddEventListener(___all_struct.get(-641444818), this, this.HandleMainTabRightClick);
		this._main_tab.AddEventListener(___all_struct.get(-1604617962), this, this.HandleMainTabKeyDown);
		this._main_tab_bg.AddEventListener(___all_struct.get(-338112738), this, this.HandleMainTabDropFile);
		this._main_tab.close_callback = this.MainTabTabCloseYesOrNot.bind(this);
		this._main_tab.close_post_callback = this.MainTabTabClose.bind(this);
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-332308624), this, this.HandleProjectClose);
	},
	get cur_tab() {
		return this._cur_tab;
	},
	get main_tab() {
		return this._main_tab;
	},
	get cur_tab_child() {
		if (this._cur_tab === undefined) {
			return undefined;
		}
		return this._cur_tab._user_data;
	},
	HandleProjectClose : function(event) {
		this.CloseAllTab();
	},
	GetTabById : function(T, id) {
		let tab_childs = this._main_tab.childs;
		let ___OBJECT_1 = tab_childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			let tab_child = ALittle.Cast(T, ALittleIDE.IDETabChild, child._user_data);
			if (tab_child !== undefined && tab_child.id === id) {
				return child;
			}
		}
		return undefined;
	},
	GetTabChildById : function(T, id) {
		let tab_childs = this._main_tab.childs;
		let ___OBJECT_2 = tab_childs;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let child = ___OBJECT_2[index - 1];
			if (child === undefined) break;
			let tab_child = ALittle.Cast(T, ALittleIDE.IDETabChild, child._user_data);
			if (tab_child !== undefined && tab_child.id === id) {
				return tab_child;
			}
		}
		return undefined;
	},
	GetTabIdMap : function(T) {
		let info = {};
		let tab_childs = this._main_tab.childs;
		let ___OBJECT_3 = tab_childs;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let child = ___OBJECT_3[index - 1];
			if (child === undefined) break;
			let tab_child = ALittle.Cast(T, ALittleIDE.IDETabChild, child._user_data);
			if (tab_child !== undefined) {
				info[tab_child.id] = tab_child;
			}
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
		this.ChangeTabEdit(this._cur_tab, this._main_tab.tab);
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
	ChangeTabEdit : function(child_from, child_to) {
		if (child_from === child_to) {
			return;
		}
		if (child_from !== undefined) {
			let tab_child = child_from._user_data;
			tab_child.OnHide();
		}
		if (child_to !== undefined) {
			let tab_child = child_to._user_data;
			tab_child.OnShow();
		}
		this._cur_tab = child_to;
	},
	CloseTab : function(child) {
		let tab_child = child._user_data;
		if (this._main_tab.tab === child) {
			tab_child.OnHide();
		}
		tab_child.OnClose();
		this._main_tab.RemoveChild(child);
		this.ChangeTabEdit(undefined, this._main_tab.tab);
	},
	CloseTabChild : function(tab_child) {
		this.CloseTab(tab_child.tab_body);
	},
	CloseTabByName : function(T, name) {
		let ___OBJECT_5 = this._main_tab.childs;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let child = ___OBJECT_5[index - 1];
			if (child === undefined) break;
			let tab_child = child._user_data;
			let target_child = ALittle.Cast(T, ALittleIDE.IDETabChild, tab_child);
			if (target_child !== undefined && this._main_tab.GetChildText(child) === name) {
				this.CloseTab(tab_child.tab_body);
				break;
			}
		}
	},
	SaveTab : function(child) {
		let tab_child = child._user_data;
		tab_child.save = true;
	},
	CloseAllTab : function() {
		this.ChangeTabEdit(this._main_tab.tab, undefined);
		let ___OBJECT_6 = this._main_tab.childs;
		for (let k = 1; k <= ___OBJECT_6.length; ++k) {
			let child = ___OBJECT_6[k - 1];
			if (child === undefined) break;
			let tab_child = child._user_data;
			tab_child.OnClose();
		}
		this._main_tab.RemoveAllChild();
	},
	SaveAllTab : function() {
		let ___OBJECT_7 = this._main_tab.childs;
		for (let k = 1; k <= ___OBJECT_7.length; ++k) {
			let child = ___OBJECT_7[k - 1];
			if (child === undefined) break;
			let tab_child = child._user_data;
			tab_child.save = true;
		}
	},
	HandleMainTabSelectChange : function(event) {
		this.ChangeTabEdit(this._cur_tab, this._main_tab.tab);
	},
	MainTabTabClose : function(child) {
		this.CloseTab(child);
	},
	MainTabTabCloseYesOrNot : function(child) {
		let tab_child = child._user_data;
		if (tab_child.save) {
			if (this._main_tab.tab === child) {
				tab_child.OnHide();
			}
			tab_child.OnClose();
			return true;
		}
		this.MainTabTabCloseImpl(tab_child, child);
		return false;
	},
	MainTabTabCloseImpl : async function(tab_child, child) {
		let cancel_callback = this.CloseTab.bind(this, child);
		let result = await g_AUITool.SaveNotice("提示", "是否保存?");
		if (result === "CANCEL") {
			return;
		}
		if (result === "YES") {
			tab_child.save = true;
		}
		this.CloseTab(child);
	},
	HandleMainTabRightClick : function(event) {
		let tab_child = event.target._user_data;
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("保存", tab_child.Save.bind(tab_child));
		tab_child.OnTabRightMenu(menu);
		menu.AddItem("关闭自己", this.CloseTabWithAsk.bind(this, tab_child.tab_body));
		menu.AddItem("关闭左侧", this.CloseLeftTab.bind(this, tab_child.tab_body));
		menu.AddItem("关闭右侧", this.CloseRightTab.bind(this, tab_child.tab_body));
		menu.Show();
	},
	HandleMainTabKeyDown : async function(event) {
	},
	HandleMainTabDropFile : function(event) {
		let name = ALittle.File_GetFileNameByPath(event.path);
		let user_info = {};
		user_info.path = event.path;
		user_info.name = name;
		this.StartEditCodeBySelect(name, user_info);
	},
	HandleTabRightExMenu : function(event) {
		let tab_childs = this._main_tab.childs;
		if (tab_childs[1 - 1] === undefined) {
			return;
		}
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		let ___OBJECT_8 = tab_childs;
		for (let index = 1; index <= ___OBJECT_8.length; ++index) {
			let child = ___OBJECT_8[index - 1];
			if (child === undefined) break;
			let tab_child = child._user_data;
			menu.AddItem(tab_child.title, this.SelectItemClick.bind(this, child));
		}
		menu.Show();
	},
	SelectItemClick : function(child_to) {
		let child_from = this._main_tab.tab;
		this._main_tab.SetChildIndex(child_to, 1);
		this._main_tab.tab = child_to;
		this.ChangeTabEdit(child_from, child_to);
	},
	CloseTabWithAsk : async function(child) {
		let tab_child = child._user_data;
		if (tab_child.save) {
			this.CloseTab(child);
			return;
		}
		let result = await g_AUITool.SaveNotice("提示", "是否保存当前标签页?");
		if (result === "CANCEL") {
			return;
		}
		if (result === "YES") {
			tab_child.save = true;
		}
		this.CloseTab(child);
	},
	CloseLeftTab : function(child) {
		let close_list = [];
		let ___OBJECT_9 = this._main_tab.childs;
		for (let index = 1; index <= ___OBJECT_9.length; ++index) {
			let child_v = ___OBJECT_9[index - 1];
			if (child_v === undefined) break;
			if (child_v === child) {
				break;
			}
			let tab_child = child_v._user_data;
			if (tab_child.save) {
				ALittle.List_Push(close_list, child_v);
			}
		}
		let ___OBJECT_10 = close_list;
		for (let index = 1; index <= ___OBJECT_10.length; ++index) {
			let child_v = ___OBJECT_10[index - 1];
			if (child_v === undefined) break;
			this.CloseTab(child_v);
		}
	},
	CloseRightTab : function(child) {
		let close_list = [];
		let child_list = this._main_tab.childs;
		let cur_index = this._main_tab.GetChildIndex(child);
		let child_count = this._main_tab.child_count;
		for (let index = cur_index + 1; index <= child_count; index += 1) {
			let child_v = child_list[index - 1];
			let tab_child = child_v._user_data;
			if (tab_child.save) {
				ALittle.List_Push(close_list, child_v);
			}
		}
		let ___OBJECT_11 = close_list;
		for (let index = 1; index <= ___OBJECT_11.length; ++index) {
			let child_v = ___OBJECT_11[index - 1];
			if (child_v === undefined) break;
			this.CloseTab(child_v);
		}
	},
	StartEditControlByNew : function(module, name, type) {
		let child_from = this._main_tab.tab;
		let tab_child = ALittle.NewObject(ALittleIDE.IDEUITabChild, ALittleIDE.g_Control, module, name, false);
		tab_child.CreateByNew(type);
		this._main_tab.AddChild(tab_child.tab_body);
		tab_child.OnOpen();
		this._main_tab.tab = tab_child.tab_body;
		this.ChangeTabEdit(child_from, this._main_tab.tab);
		tab_child.UpdateTitle();
		tab_child.ShowHandleQuad(tab_child.tree_object);
		return tab_child;
	},
	StartEditControlByExtends : function(module, name, extends_module, extends_name) {
		let child_from = this._main_tab.tab;
		let tab_child = ALittle.NewObject(ALittleIDE.IDEUITabChild, ALittleIDE.g_Control, module, name, false);
		if (!tab_child.CreateByExtends(extends_module, extends_name)) {
			return undefined;
		}
		this._main_tab.AddChild(tab_child.tab_body);
		tab_child.OnOpen();
		this._main_tab.tab = tab_child.tab_body;
		this.ChangeTabEdit(child_from, this._main_tab.tab);
		tab_child.UpdateTitle();
		tab_child.ShowHandleQuad(tab_child.tree_object);
		return tab_child;
	},
	StartEditControlBySelect : function(module, name) {
		let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(module);
		if (ui_manager === undefined) {
			g_AUITool.ShowNotice("错误", "ui_manager获取失败");
			return undefined;
		}
		let control_info = ui_manager.control_map[name];
		if (control_info === undefined) {
			g_AUITool.ShowNotice("错误", "控件不存在");
			return undefined;
		}
		let info = control_info.info;
		let child = this.GetTabById(ALittleIDE.IDEUITabChild, name);
		if (child !== undefined) {
			let child_from = this._main_tab.tab;
			this._main_tab.tab = child;
			this.ChangeTabEdit(child_from, this._main_tab.tab);
			return child._user_data;
		}
		let child_from = this._main_tab.tab;
		let tab_child = ALittle.NewObject(ALittleIDE.IDEUITabChild, ALittleIDE.g_Control, module, name, true);
		tab_child.CreateBySelect(info);
		this._main_tab.AddChild(tab_child.tab_body, 1);
		tab_child.OnOpen();
		this._main_tab.tab = tab_child.tab_body;
		this.ChangeTabEdit(child_from, this._main_tab.tab);
		tab_child.UpdateTitle();
		if (!tab_child.tree_object.is_tree) {
			tab_child.ShowHandleQuad(tab_child.tree_object);
		}
		return tab_child;
	},
	StartEditCodeBySelect : function(name, info) {
		let child = this.GetTabById(ALittleIDE.IDECodeTabChild, info.path);
		if (child !== undefined) {
			let child_from = this._main_tab.tab;
			this._main_tab.tab = child;
			this.ChangeTabEdit(child_from, this._main_tab.tab);
			return child._user_data;
		}
		let child_from = this._main_tab.tab;
		let tab_child = ALittle.NewObject(ALittleIDE.IDECodeTabChild, ALittleIDE.g_Control, info.module_name, name, true, info);
		tab_child.CreateBySelect(info);
		this._main_tab.AddChild(tab_child.tab_body, 1);
		tab_child.OnOpen();
		this._main_tab.tab = tab_child.tab_body;
		this.ChangeTabEdit(child_from, this._main_tab.tab);
		tab_child.UpdateTitle();
		return tab_child;
	},
	StartEditTileBySelect : function(name, info) {
		let child = this.GetTabById(ALittleIDE.IDETileTabChild, info.info.path);
		if (child !== undefined) {
			let child_from = this._main_tab.tab;
			this._main_tab.tab = child;
			this.ChangeTabEdit(child_from, this._main_tab.tab);
			return child._user_data;
		}
		let child_from = this._main_tab.tab;
		let tab_child = ALittle.NewObject(ALittleIDE.IDETileTabChild, ALittleIDE.g_Control, info.module_name, name, true, info);
		tab_child.CreateBySelect(info);
		this._main_tab.AddChild(tab_child.tab_body, 1);
		tab_child.OnOpen();
		this._main_tab.tab = tab_child.tab_body;
		this.ChangeTabEdit(child_from, this._main_tab.tab);
		tab_child.UpdateTitle();
		return tab_child;
	},
}, "ALittleIDE.IDEContentEdit");

}