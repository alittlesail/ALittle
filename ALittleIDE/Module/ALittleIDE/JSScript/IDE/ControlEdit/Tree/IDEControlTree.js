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
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name : "ALittle.UIResizeEvent", ns_name : "ALittle", rl_name : "UIResizeEvent", hash_code : -431205740,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

if (ALittleIDE.IDEControlTreeLogic === undefined) throw new Error(" extends class:ALittleIDE.IDEControlTreeLogic is undefined");
ALittleIDE.IDEControlTree = JavaScript.Class(ALittleIDE.IDEControlTreeLogic, {
	Ctor : function(ctrl_sys, user_info) {
		this._head = ctrl_sys.CreateControl("ide_control_tree_head", this);
		ALittle.DisplayGroup.AddChild.call(this, this._head);
		this._item_button.selected = false;
		this._item_button.group = user_info.group;
		this._item_button.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this._item_button.AddEventListener(___all_struct.get(-641444818), this, this.HandleRButtonDown);
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
		if (user_info.root) {
			this._item_button.text = "[" + this._user_info.module_name + "] " + this._user_info.name;
		} else {
			this._item_button.text = this._user_info.name;
		}
		this.Refresh();
	},
	HandleLButtonDown : function(event) {
		if (event.count === 1) {
			return;
		}
		this.fold = !this.fold;
	},
	HandleRButtonDown : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		if (this._user_info.root) {
			menu.AddItem("添加模块", this.HandleAddModule.bind(this));
		}
		menu.AddItem("新建控件", this.HandleNewControl.bind(this));
		menu.AddItem("继承控件", this.HandleExtendsControl.bind(this));
		let can_remove = this._user_info.root && this._user_info.module_name !== ALittleIDE.g_IDEProject.project.name;
		if (can_remove) {
			menu.AddItem("移除模块", this.HandleRemoveModule.bind(this));
		}
		menu.Show();
	},
	HandleAddModule : async function() {
		let [x, y] = this._head.LocalToGlobal();
		let name = await g_AUITool.ShowRename("", x, y + this._head.height, 200);
		if (name === undefined || name === "") {
			return;
		}
		await ALittleIDE.g_IDECenter.center.control_list.AddModule(name);
	},
	HandleRemoveModule : async function() {
		let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(undefined);
		if (ui_manager === undefined) {
			return;
		}
		let remove_list = [];
		let tab_child_map = ALittleIDE.g_IDECenter.center.content_edit.GetTabIdMap(ALittleIDE.IDEUITabChild);
		let ___OBJECT_1 = tab_child_map;
		for (let id in ___OBJECT_1) {
			let tab_child = ___OBJECT_1[id];
			if (tab_child === undefined) continue;
			if (tab_child.module === this._user_info.module_name) {
				if (!tab_child.save) {
					g_AUITool.ShowNotice("错误", "还有UI正在编辑并为保存");
					return;
				}
				ALittle.List_Push(remove_list, tab_child);
			}
		}
		let ___OBJECT_2 = remove_list;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let tab_child = ___OBJECT_2[index - 1];
			if (tab_child === undefined) break;
			ALittleIDE.g_IDECenter.center.content_edit.CloseTabByName(ALittleIDE.IDEUITabChild, tab_child.name);
		}
		let file_name = ALittle.File_GetFileNameByPath(this._user_info.path);
		let result = await g_AUITool.DeleteNotice("移除", "确定要移除" + file_name + "模块吗?");
		if (result !== "YES") {
			return;
		}
		this.OnDelete();
		this.RemoveFromParent();
		let module_map = ALittleIDE.g_IDEProject.project.config.GetConfig("control_module", {});
		delete module_map[this._user_info.module_name];
		ALittleIDE.g_IDEProject.project.config.SetConfig("control_module", module_map);
		delete ALittleIDE.g_IDEProject.project.ui[this._user_info.module_name];
		ui_manager.control.UnRegisterPlugin(this._user_info.module_name);
	},
	HandleNewControl : function() {
		ALittleIDE.g_IDECenter.center.control_list.ShowNewControl(this._user_info.module_name);
	},
	HandleExtendsControl : function() {
		ALittleIDE.g_IDECenter.center.control_list.ShowExtendsControl(this._user_info.module_name);
	},
	get is_tree() {
		return true;
	},
	Refresh : function() {
		let map = ALittle.File_GetNameListByDir(this._user_info.path);
		let remove = undefined;
		let ___OBJECT_3 = this.childs;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let child = ___OBJECT_3[index - 1];
			if (child === undefined) break;
			let attr = map[child._user_info.name];
			if (attr === undefined) {
				if (remove === undefined) {
					remove = [];
				}
				ALittle.List_Push(remove, child);
			}
			delete map[child._user_info.name];
			child.Refresh();
		}
		if (remove !== undefined) {
			let ___OBJECT_4 = remove;
			for (let index = 1; index <= ___OBJECT_4.length; ++index) {
				let child = ___OBJECT_4[index - 1];
				if (child === undefined) break;
				this.RemoveChild(child);
			}
		}
		let add_file = undefined;
		let add_dir = undefined;
		let ___OBJECT_5 = map;
		for (let name in ___OBJECT_5) {
			let attr = ___OBJECT_5[name];
			if (attr === undefined) continue;
			if (attr.directory) {
				if (add_dir === undefined) {
					add_dir = [];
				}
				ALittle.List_Push(add_dir, name);
			} else {
				if (add_file === undefined) {
					add_file = [];
				}
				ALittle.List_Push(add_file, name);
			}
		}
		if (add_dir !== undefined) {
			ALittle.List_Sort(add_dir);
			let ___OBJECT_6 = add_dir;
			for (let index = 1; index <= ___OBJECT_6.length; ++index) {
				let name = ___OBJECT_6[index - 1];
				if (name === undefined) break;
				let attr = map[name];
				let info = {};
				info.module_name = this._user_info.module_name;
				info.module_path = this._user_info.module_path;
				info.name = name;
				info.path = this._user_info.path + "/" + name;
				info.group = this._user_info.group;
				info.root = false;
				info.ui = this._user_info.ui;
				this.AddChild(ALittle.NewObject(ALittleIDE.IDEControlTree, this._ctrl_sys, info));
			}
		}
		if (add_file !== undefined) {
			ALittle.List_Sort(add_file);
			let ___OBJECT_7 = add_file;
			for (let index = 1; index <= ___OBJECT_7.length; ++index) {
				let name = ___OBJECT_7[index - 1];
				if (name === undefined) break;
				let attr = map[name];
				let info = {};
				info.module_name = this._user_info.module_name;
				info.module_path = this._user_info.module_path;
				info.name = ALittle.File_GetJustFileNameByPath(name);
				info.path = this._user_info.path + "/" + name;
				info.group = this._user_info.group;
				info.root = false;
				info.ui = this._user_info.ui;
				this.AddChild(ALittle.NewObject(ALittleIDE.IDEControlTreeItem, this._ctrl_sys, info));
			}
		}
		this.DispatchEvent(___all_struct.get(-431205740), {});
	},
	SearchFile : function(name, list) {
		if (list === undefined) {
			list = [];
		}
		let ___OBJECT_8 = this._body.childs;
		for (let k = 1; k <= ___OBJECT_8.length; ++k) {
			let child = ___OBJECT_8[k - 1];
			if (child === undefined) break;
			child.SearchFile(name, list);
		}
		return list;
	},
	FindFile : function(full_path) {
		if (ALittle.String_Find(full_path, this._user_info.path) !== 1) {
			return undefined;
		}
		let ___OBJECT_9 = this._body.childs;
		for (let k = 1; k <= ___OBJECT_9.length; ++k) {
			let child = ___OBJECT_9[k - 1];
			if (child === undefined) break;
			let item = child.FindFile(full_path);
			if (item !== undefined) {
				return item;
			}
		}
		return undefined;
	},
	OnDelete : function() {
		let ___OBJECT_10 = this.childs;
		for (let index = 1; index <= ___OBJECT_10.length; ++index) {
			let child = ___OBJECT_10[index - 1];
			if (child === undefined) break;
			child.OnDelete();
		}
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
		child.group = undefined;
		if (this._body.abs_visible) {
			this.DispatchEvent(___all_struct.get(-431205740), {});
		}
		return true;
	},
	SpliceChild : function(index, count) {
		let remain_count = this._child_count - index + 1;
		if (count === undefined) {
			count = remain_count;
		} else if (count > remain_count) {
			count = remain_count;
		}
		if (count <= 0) {
			return 0;
		}
		let endv = index + count;
		for (let i = index; i < endv; i += 1) {
			let child = this._childs[i - 1];
			if (child === undefined) {
				break;
			}
			child.group = undefined;
		}
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
		let ___OBJECT_11 = this.childs;
		for (let index = 1; index <= ___OBJECT_11.length; ++index) {
			let child = ___OBJECT_11[index - 1];
			if (child === undefined) break;
			child.group = undefined;
		}
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
			let ___OBJECT_12 = childs;
			for (let k = 1; k <= ___OBJECT_12.length; ++k) {
				let v = ___OBJECT_12[k - 1];
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
}, "ALittleIDE.IDEControlTree");

}