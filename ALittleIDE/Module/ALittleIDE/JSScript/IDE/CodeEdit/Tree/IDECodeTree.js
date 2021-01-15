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

if (ALittleIDE.IDECodeTreeLogic === undefined) throw new Error(" extends class:ALittleIDE.IDECodeTreeLogic is undefined");
ALittleIDE.IDECodeTree = JavaScript.Class(ALittleIDE.IDECodeTreeLogic, {
	Ctor : function(ctrl_sys, user_info) {
		this._head = ctrl_sys.CreateControl("ide_code_tree_head", this);
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
		if (this._user_info.project !== undefined) {
			this._user_info.project.OnTreeMenu(this._user_info.path, menu);
		}
		menu.AddItem("新建ALittle文件", this.HandleCreateFile.bind(this));
		menu.AddItem("新建文件夹", this.HandleCreateDir.bind(this));
		menu.AddItem("刷新", this.Refresh.bind(this));
		if (ALittleIDE.g_IDECenter.center.code_list.GetCutTreeItem() !== undefined || ALittleIDE.g_IDECenter.center.code_list.GetCopyTreeItem() !== undefined) {
			menu.AddItem("粘贴", this.PasteFile.bind(this));
		}
		if (!this._user_info.root) {
			menu.AddItem("删除", this.HandleDeleteDir.bind(this));
		}
		if (this._user_info.root) {
			menu.AddItem("添加模块", this.HandleAddModule.bind(this));
			menu.AddItem("添加库", this.HandleAddLibrary.bind(this));
		}
		let can_remove = this._user_info.root && this._user_info.module_name !== "Std" && this._user_info.module_name !== "Core" && this._user_info.module_name !== "CEngine" && this._user_info.module_name !== ALittleIDE.g_IDEProject.project.name;
		if (can_remove) {
			menu.AddItem("移除模块", this.HandleRemoveModule.bind(this));
		}
		menu.Show();
	},
	HandleCreateFile : async function() {
		let [x, y] = this._head.LocalToGlobal();
		let name = await g_AUITool.ShowRename("", x, y + this._head.height, 200);
		if (name === undefined || name === "") {
			return;
		}
		if (ALittle.File_GetFileAttr(this._user_info.path + "/" + name + ".alittle") !== undefined) {
			g_AUITool.ShowNotice("提示", "文件名已存在");
			return;
		}
		let content = "\nnamespace " + ALittleIDE.g_IDEProject.project.name + ";\n\nprotected class " + name + "\n{\n}\n";
		ALittle.File_WriteTextToFile(content, this._user_info.path + "/" + name + ".alittle");
		this.Refresh();
	},
	HandleCreateDir : async function() {
		let [x, y] = this._head.LocalToGlobal();
		let name = await g_AUITool.ShowRename("", x, y + this._head.height, 200);
		if (name === undefined || name === "") {
			return;
		}
		ALittle.File_MakeDir(this._user_info.path + "/" + name);
		this.Refresh();
	},
	HandleAddModule : async function() {
		let [x, y] = this._head.LocalToGlobal();
		let name = await g_AUITool.ShowRename("", x, y + this._head.height, 200);
		if (name === undefined || name === "") {
			return;
		}
		ALittleIDE.g_IDECenter.center.code_list.AddModule(name);
	},
	HandleAddLibrary : async function() {
		let [x, y] = this._head.LocalToGlobal();
		let name = await g_AUITool.ShowRename("", x, y + this._head.height, 200);
		if (name === undefined || name === "") {
			return;
		}
		ALittleIDE.g_IDECenter.center.code_list.AddLibrary(name);
	},
	HandleDeleteDir : async function() {
		let file_name = ALittle.File_GetFileNameByPath(this._user_info.path);
		let result = await g_AUITool.DeleteNotice("删除", "确定要删除" + file_name + "，以及子文件和子文件夹吗?");
		if (result !== "YES") {
			return;
		}
		this.OnDelete();
		ALittle.File_DeleteDeepDir(this._user_info.path);
		this.RemoveFromParent();
	},
	HandleRemoveModule : async function() {
		let file_name = ALittle.File_GetFileNameByPath(this._user_info.path);
		let result = await g_AUITool.DeleteNotice("移除", "确定要移除" + file_name + "模块吗?");
		if (result !== "YES") {
			return;
		}
		this.OnDelete();
		this.RemoveFromParent();
		let module_map = ALittleIDE.g_IDEProject.project.config.GetConfig("code_module", {});
		delete module_map[this._user_info.module_name];
		ALittleIDE.g_IDEProject.project.config.SetConfig("code_module", module_map);
	},
	get is_tree() {
		return true;
	},
	PasteFile : function() {
		let item = ALittleIDE.g_IDECenter.center.code_list.GetCutTreeItem();
		if (item !== undefined) {
			let path = ALittle.File_GetFilePathByPath(item.user_info.path);
			let name = ALittle.File_GetFileNameByPath(item.user_info.path);
			if (path === this._user_info.path) {
				return;
			}
			ALittle.File_RenameFile(item.user_info.path, this._user_info.path + "/" + name);
			item.OnDelete();
			let parent = item.parent;
			item.RemoveFromParent();
			if (parent !== undefined) {
				parent.DispatchEvent(___all_struct.get(-431205740), {});
			}
			ALittleIDE.g_IDECenter.center.content_edit.CloseTabByName(ALittleIDE.IDECodeTabChild, item.user_info.name);
			this.Refresh();
			ALittleIDE.g_IDECenter.center.code_list.ClearCutAndCopy();
			return;
		}
		item = ALittleIDE.g_IDECenter.center.code_list.GetCopyTreeItem();
		if (item !== undefined) {
			let path = ALittle.File_GetFilePathByPath(item.user_info.path);
			let name = ALittle.File_GetFileNameByPath(item.user_info.path);
			if (path === this._user_info.path) {
				return;
			}
			ALittle.File_CopyFile(item.user_info.path, this._user_info.path + "/" + name);
			this.Refresh();
			ALittleIDE.g_IDECenter.center.code_list.ClearCutAndCopy();
			return;
		}
	},
	Refresh : function() {
		let map = ALittle.File_GetNameListByDir(this._user_info.path);
		let remove = undefined;
		let ___OBJECT_1 = this.childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
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
			let ___OBJECT_2 = remove;
			for (let index = 1; index <= ___OBJECT_2.length; ++index) {
				let child = ___OBJECT_2[index - 1];
				if (child === undefined) break;
				if (this._user_info.project !== undefined && ALittle.File_GetFileExtByPathAndUpper(child.user_info.path) === this._user_info.project.upper_ext) {
					this._user_info.project.RemoveFile(child.user_info.path);
				}
				this.RemoveChild(child);
			}
		}
		let add_file = undefined;
		let add_dir = undefined;
		let ___OBJECT_3 = map;
		for (let name in ___OBJECT_3) {
			let attr = ___OBJECT_3[name];
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
			let ___OBJECT_4 = add_dir;
			for (let index = 1; index <= ___OBJECT_4.length; ++index) {
				let name = ___OBJECT_4[index - 1];
				if (name === undefined) break;
				let attr = map[name];
				let info = {};
				info.module_name = this._user_info.module_name;
				info.module_path = this._user_info.module_path;
				info.name = name;
				info.path = this._user_info.path + "/" + name;
				info.group = this._user_info.group;
				info.project = this._user_info.project;
				info.root = false;
				this.AddChild(ALittle.NewObject(ALittleIDE.IDECodeTree, this._ctrl_sys, info));
			}
		}
		if (add_file !== undefined) {
			ALittle.List_Sort(add_file);
			let ___OBJECT_5 = add_file;
			for (let index = 1; index <= ___OBJECT_5.length; ++index) {
				let name = ___OBJECT_5[index - 1];
				if (name === undefined) break;
				let attr = map[name];
				let info = {};
				info.module_name = this._user_info.module_name;
				info.module_path = this._user_info.module_path;
				info.name = name;
				info.path = this._user_info.path + "/" + name;
				info.group = this._user_info.group;
				info.project = this._user_info.project;
				info.root = false;
				this.AddChild(ALittle.NewObject(ALittleIDE.IDECodeTreeItem, this._ctrl_sys, info));
				if (this._user_info.project !== undefined && ALittle.File_GetFileExtByPathAndUpper(info.path) === this._user_info.project.upper_ext) {
					this._user_info.project.UpdateFile(info.module_path, info.path);
				}
			}
		}
		this.DispatchEvent(___all_struct.get(-431205740), {});
	},
	SearchFile : function(name, list) {
		if (list === undefined) {
			list = [];
		}
		let ___OBJECT_6 = this._body.childs;
		for (let k = 1; k <= ___OBJECT_6.length; ++k) {
			let child = ___OBJECT_6[k - 1];
			if (child === undefined) break;
			child.SearchFile(name, list);
		}
		return list;
	},
	FindFile : function(full_path) {
		if (ALittle.String_Find(full_path, this._user_info.path) !== 1) {
			return undefined;
		}
		let ___OBJECT_7 = this._body.childs;
		for (let k = 1; k <= ___OBJECT_7.length; ++k) {
			let child = ___OBJECT_7[k - 1];
			if (child === undefined) break;
			let item = child.FindFile(full_path);
			if (item !== undefined) {
				return item;
			}
		}
		return undefined;
	},
	OnDelete : function() {
		let ___OBJECT_8 = this.childs;
		for (let index = 1; index <= ___OBJECT_8.length; ++index) {
			let child = ___OBJECT_8[index - 1];
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
		let ___OBJECT_9 = this.childs;
		for (let index = 1; index <= ___OBJECT_9.length; ++index) {
			let child = ___OBJECT_9[index - 1];
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
			let ___OBJECT_10 = childs;
			for (let k = 1; k <= ___OBJECT_10.length; ++k) {
				let v = ___OBJECT_10[k - 1];
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
}, "ALittleIDE.IDECodeTree");

}