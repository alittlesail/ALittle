{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(2117383637, "AUIPlugin.AUIFileSelectFileEvent", {
name : "AUIPlugin.AUIFileSelectFileEvent", ns_name : "AUIPlugin", rl_name : "AUIFileSelectFileEvent", hash_code : 2117383637,
name_list : ["target","info"],
type_list : ["ALittle.DisplayObject","AUIPlugin.AUIFileTreeUserInfo"],
option_map : {}
})
ALittle.RegStruct(-2082217254, "AUIPlugin.AUIFileCreateFileEvent", {
name : "AUIPlugin.AUIFileCreateFileEvent", ns_name : "AUIPlugin", rl_name : "AUIFileCreateFileEvent", hash_code : -2082217254,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
option_map : {}
})
ALittle.RegStruct(1883782801, "ALittle.UILButtonDownEvent", {
name : "ALittle.UILButtonDownEvent", ns_name : "ALittle", rl_name : "UILButtonDownEvent", hash_code : 1883782801,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-1718818319, "AUIPlugin.AUIFileDeleteDirEvent", {
name : "AUIPlugin.AUIFileDeleteDirEvent", ns_name : "AUIPlugin", rl_name : "AUIFileDeleteDirEvent", hash_code : -1718818319,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
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
ALittle.RegStruct(821610974, "AUIPlugin.AUIFileSearchInfo", {
name : "AUIPlugin.AUIFileSearchInfo", ns_name : "AUIPlugin", rl_name : "AUIFileSearchInfo", hash_code : 821610974,
name_list : ["list","count","index","name"],
type_list : ["List<AUIPlugin.AUIFileTreeLogic>","int","int","string"],
option_map : {}
})
ALittle.RegStruct(-686652419, "AUIPlugin.AUIFileTreeUserInfo", {
name : "AUIPlugin.AUIFileTreeUserInfo", ns_name : "AUIPlugin", rl_name : "AUIFileTreeUserInfo", hash_code : -686652419,
name_list : ["path","name","root","group","on_right_menu","on_select_file","on_delete_file","on_create_file","on_delete_dir"],
type_list : ["string","string","bool","Map<ALittle.TextRadioButton,bool>","Functor<(AUIPlugin.AUIFileTreeUserInfo,AUIPlugin.AUIRightMenu)>","Functor<(AUIPlugin.AUIFileTreeUserInfo)>","Functor<(string)>","Functor<(string)>","Functor<(string)>"],
option_map : {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-545221029, "AUIPlugin.AUIFileDeleteFileEvent", {
name : "AUIPlugin.AUIFileDeleteFileEvent", ns_name : "AUIPlugin", rl_name : "AUIFileDeleteFileEvent", hash_code : -545221029,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
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

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
AUIPlugin.AUIFileTreeLogic = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys, user_info) {
		this._user_info = user_info;
	},
	get user_info() {
		return this._user_info;
	},
	get is_tree() {
		return false;
	},
	get is_root() {
		return this._user_info.root;
	},
	set fold(value) {
	},
	ShowSelect : function() {
		if (this._item_button !== undefined) {
			this._item_button.selected = true;
		}
	},
	Refresh : function() {
	},
	SearchFile : function(name, list) {
		if (list === undefined) {
			list = [];
		}
		return list;
	},
	FindFile : function(full_path) {
		return undefined;
	},
}, "AUIPlugin.AUIFileTreeLogic");

if (AUIPlugin.AUIFileTreeLogic === undefined) throw new Error(" extends class:AUIPlugin.AUIFileTreeLogic is undefined");
AUIPlugin.AUIFileTree = JavaScript.Class(AUIPlugin.AUIFileTreeLogic, {
	Ctor : function(ctrl_sys, user_info) {
		this._head = ctrl_sys.CreateControl("file_tree_head", this);
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
		this._item_button.text = this._user_info.name;
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
		menu.AddItem("新建文件", this.HandleCreateFile.bind(this));
		menu.AddItem("新建文件夹", this.HandleCreateDir.bind(this));
		menu.AddItem("刷新", this.Refresh.bind(this));
		if (!this._user_info.root) {
			menu.AddItem("删除", this.HandleDeleteDir.bind(this));
		}
		menu.Show();
	},
	HandleCreateFile : async function() {
		let [x, y] = this._head.LocalToGlobal();
		let name = await g_AUITool.ShowRename("", x, y + this._head.height, 200);
		if (name === undefined || name === "") {
			return;
		}
		if (ALittle.File_GetFileAttr(this._user_info.path + "/" + name) !== undefined) {
			g_AUITool.ShowNotice("提示", "文件名已存在");
			return;
		}
		ALittle.File_WriteTextToFile("", this._user_info.path + "/" + name);
		this.Refresh();
		if (this._user_info.on_create_file !== undefined) {
			this._user_info.on_create_file(this._user_info.path + "/" + name);
		}
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
	HandleDeleteDir : async function() {
		let file_name = ALittle.File_GetFileNameByPath(this._user_info.path);
		let result = await g_AUITool.DeleteNotice("删除", "确定要删除" + file_name + "，以及子文件和子文件夹吗?");
		if (result !== "YES") {
			return;
		}
		if (this._user_info.on_delete_dir !== undefined) {
			this._user_info.on_delete_dir(this._user_info.path);
		}
		ALittle.File_DeleteDeepDir(this._user_info.path);
		this.RemoveFromParent();
	},
	get is_tree() {
		return true;
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
				info.name = name;
				info.path = this._user_info.path + "/" + name;
				info.group = this._user_info.group;
				info.root = false;
				info.on_select_file = this._user_info.on_select_file;
				info.on_create_file = this._user_info.on_create_file;
				info.on_delete_file = this._user_info.on_delete_file;
				info.on_delete_dir = this._user_info.on_delete_dir;
				info.on_right_menu = this._user_info.on_right_menu;
				this.AddChild(ALittle.NewObject(AUIPlugin.AUIFileTree, this._ctrl_sys, info));
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
				info.name = name;
				info.path = this._user_info.path + "/" + name;
				info.group = this._user_info.group;
				info.root = false;
				info.on_select_file = this._user_info.on_select_file;
				info.on_create_file = this._user_info.on_create_file;
				info.on_delete_file = this._user_info.on_delete_file;
				info.on_delete_dir = this._user_info.on_delete_dir;
				info.on_right_menu = this._user_info.on_right_menu;
				this.AddChild(ALittle.NewObject(AUIPlugin.AUIFileTreeItem, this._ctrl_sys, info));
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
		let ___OBJECT_8 = this.childs;
		for (let index = 1; index <= ___OBJECT_8.length; ++index) {
			let child = ___OBJECT_8[index - 1];
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
			let ___OBJECT_9 = childs;
			for (let k = 1; k <= ___OBJECT_9.length; ++k) {
				let v = ___OBJECT_9[k - 1];
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
}, "AUIPlugin.AUIFileTree");

if (AUIPlugin.AUIFileTreeLogic === undefined) throw new Error(" extends class:AUIPlugin.AUIFileTreeLogic is undefined");
AUIPlugin.AUIFileTreeItem = JavaScript.Class(AUIPlugin.AUIFileTreeLogic, {
	Ctor : function(ctrl_sys, user_info) {
		this._item = ctrl_sys.CreateControl("file_tree_item", this);
		this.AddChild(this._item);
		this.width = this._item.width;
		this.height = this._item.height;
		this._item_button.selected = false;
		this._item_button.group = user_info.group;
		this._item_button.AddEventListener(___all_struct.get(-449066808), this, this.HandleClick);
		this._item_button.AddEventListener(___all_struct.get(-641444818), this, this.HandleRButtonDown);
		this._item_button.AddEventListener(___all_struct.get(-1604617962), this, this.HandleKeyDown);
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
		if (this._user_info.on_select_file !== undefined) {
			this._user_info.on_select_file(this._user_info);
		}
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
		if (this._user_info.on_right_menu !== undefined) {
			this._user_info.on_right_menu(this._user_info, menu);
		}
		menu.AddItem("重命名", this.HandleRenameFile.bind(this));
		menu.AddItem("删除", this.HandleDeleteFile.bind(this));
		menu.Show();
	},
	HandleKeyDown : function(event) {
		if (event.sym === 1073741883) {
			this.HandleRenameFile();
		}
	},
	HandleDeleteFile : async function() {
		let file_name = ALittle.File_GetFileNameByPath(this._user_info.path);
		let result = await g_AUITool.DeleteNotice("删除", "确定要删除" + file_name + "吗?");
		if (result !== "YES") {
			return;
		}
		if (this._user_info.on_delete_file !== undefined) {
			this._user_info.on_delete_file(this._user_info.path);
		}
		ALittle.File_DeleteFile(this._user_info.path);
		let parent = this.parent;
		this.RemoveFromParent();
		if (parent !== undefined) {
			parent.DispatchEvent(___all_struct.get(-431205740), {});
		}
	},
	HandleRenameFile : async function() {
		let old_name = this._user_info.name;
		let old_path = this._user_info.path;
		let file_name = ALittle.File_GetFileNameByPath(this._user_info.path);
		let [x, y] = this.LocalToGlobal();
		let new_name = await g_AUITool.ShowRename(file_name, x, y, 200);
		if (new_name === undefined || new_name === "") {
			return;
		}
		let new_path = ALittle.File_GetFilePathByPath(old_path) + "/" + new_name;
		if (ALittle.File_GetFileAttr(new_path) !== undefined) {
			g_AUITool.ShowNotice("提示", "文件名已存在");
			return;
		}
		this._user_info.path = new_path;
		this._user_info.name = new_name;
		this._item_button.text = this._user_info.name;
		if (this._user_info.on_delete_file !== undefined) {
			this._user_info.on_delete_file(old_path);
		}
		ALittle.File_RenameFile(old_path, new_path);
		let create_event = {};
		create_event.path = new_path;
		this.DispatchEvent(___all_struct.get(-2082217254), create_event);
	},
}, "AUIPlugin.AUIFileTreeItem");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
AUIPlugin.AUIFileTreeLayout = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._group = new Map();
	},
	SetRoot : function(path, on_right_menu) {
		this._file_scroll_screen.RemoveAllChild();
		if (path === undefined || path === "") {
			return;
		}
		let attr = ALittle.File_GetFileAttr(path);
		if (attr === undefined || !attr.directory) {
			return;
		}
		let info = {};
		info.name = ALittle.File_GetFileNameByPath(path);
		info.path = path;
		info.group = this._group;
		info.root = true;
		info.on_right_menu = on_right_menu;
		info.on_select_file = this.HandleSelectFile.bind(this);
		info.on_delete_file = this.HandleDeleteFile.bind(this);
		info.on_create_file = this.HandleCreateFile.bind(this);
		info.on_delete_dir = this.HandleDeleteDir.bind(this);
		let tree = ALittle.NewObject(AUIPlugin.AUIFileTree, AUIPlugin.g_Control, info);
		this._file_scroll_screen.AddChild(tree);
	},
	HandleSelectFile : function(user_info) {
		let select_event = {};
		select_event.info = user_info;
		this.DispatchEvent(___all_struct.get(2117383637), select_event);
	},
	HandleCreateFile : function(path) {
		let select_event = {};
		select_event.path = path;
		this.DispatchEvent(___all_struct.get(-2082217254), select_event);
	},
	HandleDeleteFile : function(path) {
		let select_event = {};
		select_event.path = path;
		this.DispatchEvent(___all_struct.get(-545221029), select_event);
	},
	HandleDeleteDir : function(path) {
		let select_event = {};
		select_event.path = path;
		this.DispatchEvent(___all_struct.get(-1718818319), select_event);
	},
	SetFold : function(index, fold) {
		let tree = ALittle.Cast(AUIPlugin.AUIFileTree, ALittle.DisplayObject, this._file_scroll_screen.GetChildByIndex(index));
		if (tree === undefined) {
			return;
		}
		tree.fold = fold;
	},
	GetFileTree : function(full_path) {
		let ___OBJECT_10 = this._file_scroll_screen.childs;
		for (let index = 1; index <= ___OBJECT_10.length; ++index) {
			let child = ___OBJECT_10[index - 1];
			if (child === undefined) break;
			let item = child.FindFile(full_path);
			if (item !== undefined) {
				return item;
			}
		}
		return undefined;
	},
	ShowTreeItemFocus : function(target) {
		target.ShowSelect();
		if (target !== this._file_scroll_screen) {
			let parent = target.logic_parent;
			while (parent !== undefined && parent !== this._file_scroll_screen) {
				parent.fold = true;
				parent = parent.logic_parent;
			}
		}
		this._file_scroll_screen.AdjustScrollBar();
		let [x, y] = target.LocalToGlobal(this._file_scroll_screen.container);
		let target_x = (this._file_scroll_screen.view_width - target.width / 2) / 2 - x;
		let target_y = (this._file_scroll_screen.view_height - target.height) / 2 - y;
		if (this._tree_loop_x !== undefined) {
			this._tree_loop_x.Stop();
			this._tree_loop_x = undefined;
		}
		if (this._tree_loop_y !== undefined) {
			this._tree_loop_y.Stop();
			this._tree_loop_y = undefined;
		}
		this._tree_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._file_scroll_screen, "container_x", target_x, 300, 0);
		this._tree_loop_x.Start();
		this._tree_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._file_scroll_screen, "container_y", target_y, 300, 0);
		this._tree_loop_y.Start();
	},
	HandleFileSearchClick : function(event) {
		if (this._search_info === undefined || this._search_info.name !== this._file_search_key.text) {
			this._search_info = {};
			this._search_info.name = this._file_search_key.text;
			this._search_info.index = 0;
			this._search_info.list = [];
			let ___OBJECT_11 = this._file_scroll_screen.childs;
			for (let index = 1; index <= ___OBJECT_11.length; ++index) {
				let child = ___OBJECT_11[index - 1];
				if (child === undefined) break;
				child.SearchFile(this._search_info.name, this._search_info.list);
			}
			this._search_info.count = ALittle.List_Len(this._search_info.list);
		}
		if (this._search_info.count <= 0) {
			return;
		}
		this._search_info.index = this._search_info.index + (1);
		if (this._search_info.index > this._search_info.count) {
			this._search_info.index = 1;
		}
		let item = this._search_info.list[this._search_info.index - 1];
		this.ShowTreeItemFocus(item);
	},
}, "AUIPlugin.AUIFileTreeLayout");

}