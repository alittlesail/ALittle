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

if (ALittleIDE.IDEControlTreeLogic === undefined) throw new Error(" extends class:ALittleIDE.IDEControlTreeLogic is undefined");
ALittleIDE.IDEControlTreeItem = JavaScript.Class(ALittleIDE.IDEControlTreeLogic, {
	Ctor : function(ctrl_sys, user_info) {
		this._item = ctrl_sys.CreateControl("ide_control_tree_item", this);
		this.AddChild(this._item);
		this.width = this._item.width;
		this.height = this._item.height;
		this._item_button.selected = false;
		this._item_button.group = user_info.group;
		this._item_button.AddEventListener(___all_struct.get(-449066808), this, this.HandleClick);
		this._item_button.AddEventListener(___all_struct.get(-641444818), this, this.HandleRButtonDown);
		this._item_button.AddEventListener(___all_struct.get(1301789264), this, this.HandleControlDragBegin);
		this._item_button.AddEventListener(___all_struct.get(1337289812), this, this.HandleControlDrag);
		this._item_button.AddEventListener(___all_struct.get(150587926), this, this.HandleControlDragEnd);
		this._item_button._user_data = this;
		this._item_button.text = this._user_info.name;
	},
	get is_tree() {
		return false;
	},
	get fold() {
		return false;
	},
	set fold(value) {
	},
	HandleClick : function(event) {
		if (event.is_drag) {
			return;
		}
		ALittleIDE.g_IDECenter.center.content_edit.StartEditControlBySelect(this._user_info.module_name, this._user_info.name);
	},
	SearchFile : function(name, list) {
		if (list === undefined) {
			list = [];
		}
		if (ALittle.String_Find(this._user_info.name, name) !== undefined) {
			ALittle.List_Push(list, this);
		}
		return list;
	},
	FindFile : function(full_path) {
		if (this._user_info.path === full_path) {
			return this;
		}
		return undefined;
	},
	HandleRButtonDown : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("复制控件名", this.HandleCopyName.bind(this));
		menu.AddItem("复制并新建控件", this.HandleCopyInfo.bind(this));
		menu.AddItem("继承并新建控件", this.HandleExtendsInfo.bind(this));
		menu.AddItem("复制继承代码", this.HandleCopyExtends.bind(this));
		menu.AddItem("修改控件名", this.HandleControlRename.bind(this));
		menu.AddItem("删除", this.HandleDelete.bind(this));
		menu.Show();
	},
	HandleDelete : async function() {
		let error = this._user_info.ui.CanDelete(this._user_info.name);
		if (error !== undefined) {
			g_AUITool.ShowNotice("错误", error);
			return;
		}
		let del_result = await g_AUITool.DeleteNotice("提示", "确定要删除" + this._user_info.name + "吗?");
		if (del_result !== "YES") {
			return;
		}
		error = this._user_info.ui.DeleteControl(this._user_info.name);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", error);
			return;
		}
		this.OnDelete();
		this.RemoveFromParent();
		ALittleIDE.g_IDECenter.center.content_edit.CloseTabByName(ALittleIDE.IDEUITabChild, this._user_info.name);
	},
	HandleCopyName : function() {
		ALittle.System_SetClipboardText(this._user_info.name);
	},
	HandleCopyInfo : async function() {
		let old_name = this._user_info.name;
		let [x, y] = this.LocalToGlobal();
		let new_name = await g_AUITool.ShowRename(old_name, x, y, this.width);
		if (new_name === undefined || old_name === new_name) {
			return;
		}
		this.ControlCopyInfo(old_name, new_name);
	},
	HandleExtendsInfo : function() {
		ALittleIDE.g_IDECenter.center.control_list.ShowExtendsControl(undefined, this._user_info.module_name, this._user_info.name);
	},
	ControlCopyInfo : function(target_name, new_name) {
		let error = ALittleIDE.IDEUtility_CheckName(new_name);
		if (error !== undefined) {
			g_AUITool.ShowNotice("错误", error);
			return;
		}
		let info = this._user_info.ui.control_map[new_name];
		if (info !== undefined) {
			g_AUITool.ShowNotice("错误", "控件名已存在:" + new_name);
			return;
		}
		info = this._user_info.ui.control_map[target_name];
		if (info === undefined) {
			g_AUITool.ShowNotice("错误", "控件不存在:" + target_name);
			return;
		}
		this._user_info.ui.SaveControl(new_name, ALittle.String_CopyTable(info.info));
		this.parent.Refresh();
		ALittleIDE.g_IDECenter.center.content_edit.StartEditControlBySelect(this._user_info.module_name, new_name);
	},
	HandleControlRename : async function() {
		let error = this._user_info.ui.CanDelete(this._user_info.name);
		if (error !== undefined) {
			g_AUITool.ShowNotice("错误", error);
			return;
		}
		let tab_child = ALittleIDE.g_IDECenter.center.content_edit.GetTabChildById(ALittleIDE.IDEUITabChild, this._user_info.name);
		if (tab_child !== undefined && tab_child.save !== true) {
			g_AUITool.ShowNotice("提示", "请先保存再重命名");
			return;
		}
		let [x, y] = this.LocalToGlobal();
		let new_name = await g_AUITool.ShowRename(this._user_info.name, x, y, this.width);
		if (new_name === undefined || this._user_info.name === new_name) {
			return;
		}
		error = this._user_info.ui.RenameControl(this._user_info.name, new_name);
		if (error !== undefined) {
			g_AUITool.ShowNotice("错误", error);
			return;
		}
		let old_name = this._user_info.name;
		this._user_info.name = new_name;
		this._user_info.path = ALittle.File_GetFilePathByPath(this._user_info.path) + "/" + this._user_info.name;
		this._user_info.name = new_name;
		this._item_button.text = this._user_info.name;
		if (tab_child !== undefined) {
			tab_child.Rename(this._user_info.name);
		}
		ALittleIDE.g_IDECenter.center.content_edit.main_tab.SetChildText(tab_child.tab_body, this._user_info.name);
	},
	HandleCopyExtends : function() {
		let name = this._user_info.name;
		let save_info = {};
		save_info["__extends"] = name;
		save_info["__module"] = this._user_info.module_name;
		let copy_list = [];
		let info = {};
		info["index"] = 1;
		info["info"] = save_info;
		copy_list[1 - 1] = info;
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list));
	},
	OnDelete : function() {
	},
	HandleControlDragBegin : function(event) {
		this._drag_shift = (A_UISystem.sym_map.get(1073742049) !== undefined || A_UISystem.sym_map.get(1073742053) !== undefined);
		if (this._drag_shift === false) {
			event.target = ALittleIDE.g_IDECenter.center.control_list.scroll_screen;
			ALittleIDE.g_IDECenter.center.control_list.scroll_screen.DispatchEvent(___all_struct.get(1301789264), event);
			return;
		}
		let [x, y] = event.target.LocalToGlobal();
		this._drag_effect = ALittle.NewObject(ALittle.EffectImage, ALittleIDE.g_Control);
		this._drag_effect.Action(event.target);
		A_LayerManager.AddToTip(this._drag_effect);
		this._drag_effect.x = x;
		this._drag_effect.y = y;
		this._drag_effect.alpha = 0.6;
	},
	HandleControlDrag : function(event) {
		if (this._drag_shift === false) {
			event.target = ALittleIDE.g_IDECenter.center.control_list.scroll_screen;
			ALittleIDE.g_IDECenter.center.control_list.scroll_screen.DispatchEvent(___all_struct.get(1337289812), event);
			return;
		}
		if (this._drag_effect === undefined) {
			return;
		}
		this._drag_effect.x = this._drag_effect.x + event.delta_x;
		this._drag_effect.y = this._drag_effect.y + event.delta_y;
	},
	HandleControlDragEnd : function(event) {
		if (this._drag_shift === false) {
			event.target = ALittleIDE.g_IDECenter.center.control_list.scroll_screen;
			ALittleIDE.g_IDECenter.center.control_list.scroll_screen.DispatchEvent(___all_struct.get(150587926), event);
			return;
		}
		if (this._drag_effect !== undefined) {
			A_LayerManager.RemoveFromTip(this._drag_effect);
			this._drag_effect.Clear();
			this._drag_effect = undefined;
		}
		let tab_child = ALittle.Cast(ALittleIDE.IDEUITabChild, ALittleIDE.IDETabChild, ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child);
		if (tab_child === undefined) {
			return;
		}
		tab_child.QuickDragAddControl(event.abs_x, event.abs_y, this._user_info.module_name, this._user_info.name);
	},
}, "ALittleIDE.IDEControlTreeItem");

}