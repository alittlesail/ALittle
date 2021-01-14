{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1876308853, "AUIPlugin.AUIFileSelectItemUserData", {
name : "AUIPlugin.AUIFileSelectItemUserData", ns_name : "AUIPlugin", rl_name : "AUIFileSelectItemUserData", hash_code : 1876308853,
name_list : ["path","directory"],
type_list : ["string","bool"],
option_map : {}
})
ALittle.RegStruct(1686540930, "AUIPlugin.AUIFileSelectItemInfo", {
name : "AUIPlugin.AUIFileSelectItemInfo", ns_name : "AUIPlugin", rl_name : "AUIFileSelectItemInfo", hash_code : 1686540930,
name_list : ["name","frame","image","file","dir","button"],
type_list : ["ALittle.DisplayObject","ALittle.DisplayObject","ALittle.Image","ALittle.Image","ALittle.Image","ALittle.TextRadioButton"],
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
ALittle.RegStruct(-1265378424, "AUIPlugin.AUIFileSelectRightButtonDownUIEvent", {
name : "AUIPlugin.AUIFileSelectRightButtonDownUIEvent", ns_name : "AUIPlugin", rl_name : "AUIFileSelectRightButtonDownUIEvent", hash_code : -1265378424,
name_list : ["target","path","directory"],
type_list : ["ALittle.DisplayObject","string","bool"],
option_map : {}
})
ALittle.RegStruct(1206110359, "AUIPlugin.AUIFileSelectFileClickUIEvent", {
name : "AUIPlugin.AUIFileSelectFileClickUIEvent", ns_name : "AUIPlugin", rl_name : "AUIFileSelectFileClickUIEvent", hash_code : 1206110359,
name_list : ["target","path","ctrl"],
type_list : ["ALittle.DisplayObject","string","bool"],
option_map : {}
})
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name : "ALittle.UIMoveOutEvent", ns_name : "ALittle", rl_name : "UIMoveOutEvent", hash_code : -1202439334,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1001723540, "ALittle.UIMouseMoveEvent", {
name : "ALittle.UIMouseMoveEvent", ns_name : "ALittle", rl_name : "UIMouseMoveEvent", hash_code : -1001723540,
name_list : ["target","abs_x","abs_y","rel_x","rel_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(-989784577, "AUIPlugin.AUIFileSelectDirClickUIEvent", {
name : "AUIPlugin.AUIFileSelectDirClickUIEvent", ns_name : "AUIPlugin", rl_name : "AUIFileSelectDirClickUIEvent", hash_code : -989784577,
name_list : ["target","path","ctrl"],
type_list : ["ALittle.DisplayObject","string","bool"],
option_map : {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-573946464, "AUIPlugin.AUIFileSelectCollectRunTime", {
name : "AUIPlugin.AUIFileSelectCollectRunTime", ns_name : "AUIPlugin", rl_name : "AUIFileSelectCollectRunTime", hash_code : -573946464,
name_list : ["cur_count","total_count"],
type_list : ["int","int"],
option_map : {}
})
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name : "ALittle.UIMoveInEvent", ns_name : "ALittle", rl_name : "UIMoveInEvent", hash_code : 544684311,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name : "ALittle.UIClickEvent", ns_name : "ALittle", rl_name : "UIClickEvent", hash_code : -449066808,
name_list : ["target","is_drag","count"],
type_list : ["ALittle.DisplayObject","bool","int"],
option_map : {}
})
ALittle.RegStruct(-338112738, "ALittle.UIDropFileEvent", {
name : "ALittle.UIDropFileEvent", ns_name : "ALittle", rl_name : "UIDropFileEvent", hash_code : -338112738,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
AUIPlugin.AUIFileSelectLayout = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._group = new Map();
	},
	Init : function(ext_list) {
		this._real_size = 100;
		this._thread = undefined;
		this._base_path = undefined;
		this._real_path = undefined;
		if (ext_list !== undefined) {
			this._ext_map = {};
			let ___OBJECT_1 = ext_list;
			for (let index = 1; index <= ___OBJECT_1.length; ++index) {
				let ext = ___OBJECT_1[index - 1];
				if (ext === undefined) break;
				this._ext_map[ALittle.String_Upper(ext)] = true;
			}
		}
	},
	Release : function() {
		if (this._thread !== undefined) {
			ALittle.Coroutine.Resume(this._thread, undefined);
			this._thread = undefined;
		}
	},
	get base_path() {
		return this._base_path;
	},
	ShowSelect : function() {
		return new Promise((function(___COROUTINE, ___) {
			this._thread = ___COROUTINE;
			return;
		}).bind(this));
	},
	System_SetVDragCursor : function(event) {
		ALittle.System_SetVDragCursor();
	},
	System_SetNormalCursor : function(event) {
		ALittle.System_SetNormalCursor();
	},
	System_SetHDragCursor : function(event) {
		ALittle.System_SetHDragCursor();
	},
	System_SetHVDragCursor : function(event) {
		ALittle.System_SetHVDragCursor();
	},
	CreateFileItem : function(file_name, rel_path, abs_path) {
		let ext = ALittle.File_GetFileExtByPath(file_name);
		if (this._ext_map !== undefined) {
			ext = ALittle.String_Upper(ext);
			if (this._ext_map[ext] === undefined) {
				return undefined;
			}
		}
		let info = {};
		let item = AUIPlugin.g_Control.CreateControl("file_select_item", info);
		info.name.text = file_name;
		info.dir.visible = false;
		info.file.visible = false;
		info.image.visible = false;
		if (ext === "PNG" || ext === "JPG" || ext === "BMP") {
			let width = undefined;
			let height = undefined;
			let surface = carp.LoadCarpSurface(abs_path);
			if (surface !== undefined) {
				width = carp.GetCarpSurfaceWidth(surface);
				height = carp.GetCarpSurfaceHeight(surface);
				carp.FreeCarpSurface(surface);
			}
			if (width === undefined) {
				width = info.frame.width;
				height = info.frame.height;
			} else {
				if (width < height) {
					let rate = width / height;
					height = info.frame.height;
					width = rate * height;
				} else {
					let rate = height / width;
					width = info.frame.width;
					height = rate * width;
				}
			}
			info.image.visible = true;
			info.image.SetTextureCut(abs_path, ALittle.Math_Floor(info.frame.width), ALittle.Math_Floor(info.frame.height), true);
			info.image.width = width;
			info.image.height = height;
			info.image.UpdateLayout();
		} else {
			info.file.visible = true;
		}
		info.button.drag_trans_target = this._scroll_list;
		info.button.AddEventListener(___all_struct.get(-641444818), this, this.HandleItemRButtonDown);
		info.button.AddEventListener(___all_struct.get(-449066808), this, this.HandleItemClick);
		info.button.AddEventListener(___all_struct.get(544684311), this, this.HandleItemMoveIn);
		info.button.AddEventListener(___all_struct.get(-1202439334), this, this.HandleItemMoveOut);
		info.button.AddEventListener(___all_struct.get(-1001723540), this, this.HandleItemMouseMove);
		info.button.AddEventListener(___all_struct.get(-338112738), this, this.HandleItemDropFile);
		info.button.group = this._group;
		let user_data = {};
		user_data.path = rel_path;
		user_data.directory = false;
		info.button._user_data = user_data;
		item._user_data = user_data;
		return item;
	},
	CreateDirItem : function(file_name, rel_path, abs_path) {
		let info = {};
		let item = AUIPlugin.g_Control.CreateControl("file_select_item", info);
		info.name.text = file_name;
		info.image.visible = false;
		info.file.visible = false;
		info.dir.visible = true;
		info.button.drag_trans_target = this._scroll_list;
		info.button.AddEventListener(___all_struct.get(-449066808), this, this.HandleItemClick);
		info.button.AddEventListener(___all_struct.get(-641444818), this, this.HandleItemRButtonDown);
		info.button.AddEventListener(___all_struct.get(-338112738), this, this.HandleItemDropFile);
		info.button.group = this._group;
		let user_data = {};
		user_data.path = rel_path;
		user_data.directory = true;
		info.button._user_data = user_data;
		item._user_data = user_data;
		return item;
	},
	BrowserCollect : function(browser_path) {
		let item_list_dir = [];
		let item_list_img = [];
		let file_map = ALittle.File_GetNameListByDir(browser_path);
		let ___OBJECT_2 = file_map;
		for (let file in ___OBJECT_2) {
			let info = ___OBJECT_2[file];
			if (info === undefined) continue;
			let path = browser_path + "/" + file;
			let rel_path = ALittle.String_Sub(path, ALittle.String_Len(this._base_path) + 2);
			let attr = ALittle.File_GetFileAttr(path);
			if (attr.directory) {
				let item = this.CreateDirItem(file, rel_path, path);
				if (item !== undefined) {
					ALittle.List_Push(item_list_dir, item);
				}
			} else {
				let item = this.CreateFileItem(file, rel_path, path);
				if (item !== undefined) {
					ALittle.List_Push(item_list_img, item);
				}
			}
		}
		return [item_list_dir, item_list_img];
	},
	SearchCollect : function(search_path, name, item_list, run_time) {
		if (item_list === undefined) {
			item_list = [];
		}
		if (run_time === undefined) {
			run_time = {};
			run_time.cur_count = 0;
			run_time.total_count = 100;
		}
		if (name === "" || name === undefined) {
			return [item_list, run_time];
		}
		let file_map = ALittle.File_GetNameListByDir(search_path);
		let ___OBJECT_3 = file_map;
		for (let file in ___OBJECT_3) {
			let info = ___OBJECT_3[file];
			if (info === undefined) continue;
			let path = search_path + "/" + file;
			let rel_path = ALittle.String_Sub(path, ALittle.String_Len(this._base_path) + 2);
			let attr = ALittle.File_GetFileAttr(path);
			if (attr.directory) {
				this.SearchCollect(path, name, item_list, run_time);
			} else if (ALittle.String_Find(file, name) !== undefined) {
				let item = this.CreateFileItem(file, rel_path, path);
				if (item !== undefined) {
					run_time.cur_count = run_time.cur_count + 1;
					ALittle.List_Push(item_list, item);
				}
			}
			if (run_time.cur_count >= run_time.total_count) {
				return [item_list, run_time];
			}
		}
		return [item_list, run_time];
	},
	ItemListCmp : function(a, b) {
		let a_user_data = a._user_data;
		let b_user_data = b._user_data;
		return a_user_data.path < b_user_data.path;
	},
	CreateItemAndAddToList : function(item_list_dir, item_list_img) {
		ALittle.List_Sort(item_list_dir, AUIPlugin.AUIFileSelectLayout.ItemListCmp);
		ALittle.List_Sort(item_list_img, AUIPlugin.AUIFileSelectLayout.ItemListCmp);
		let item_list = [];
		let ___OBJECT_4 = item_list_dir;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let item = ___OBJECT_4[index - 1];
			if (item === undefined) break;
			ALittle.List_Push(item_list, item);
		}
		let ___OBJECT_5 = item_list_img;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let item = ___OBJECT_5[index - 1];
			if (item === undefined) break;
			ALittle.List_Push(item_list, item);
		}
		let col_count = ALittle.Math_Floor(this._scroll_list.width / this._real_size);
		let remain_count = 0;
		let container = undefined;
		let ___OBJECT_6 = item_list;
		for (let index = 1; index <= ___OBJECT_6.length; ++index) {
			let item = ___OBJECT_6[index - 1];
			if (item === undefined) break;
			if (remain_count === 0) {
				container = ALittle.NewObject(ALittle.Linear, AUIPlugin.g_Control);
				container.type = 1;
				container.height = item.height;
				this._scroll_list.AddChild(container);
				container.AddChild(item);
				remain_count = col_count - 1;
			} else {
				remain_count = remain_count - 1;
				container.AddChild(item);
			}
		}
	},
	Refresh : function() {
		this._scroll_list.RemoveAllChild();
		this._path_input.text = ALittle.String_Sub(this._real_path, ALittle.String_Len(this._base_path) + 2);
		this._search_input.text = "";
		let [item_list_dir, item_list_img] = this.BrowserCollect(this._real_path);
		this.CreateItemAndAddToList(item_list_dir, item_list_img);
	},
	Search : function(name) {
		this._scroll_list.RemoveAllChild();
		let [item_list_img, run_time] = this.SearchCollect(this._real_path, name);
		this.CreateItemAndAddToList([], item_list_img);
	},
	SetPath : function(base_path, rel_path) {
		if (base_path !== undefined && rel_path !== undefined) {
			let attr = ALittle.File_GetFileAttr(base_path + "/" + rel_path);
			if (attr === undefined || attr.directory !== true) {
				g_AUITool.ShowNotice("错误", "无效路径");
				return false;
			}
		}
		this._base_path = base_path;
		this._real_path = base_path;
		if (rel_path !== undefined && rel_path !== "") {
			this._real_path = this._real_path + "/" + rel_path;
		}
		if (this._base_path !== undefined) {
			this.Refresh();
		} else {
			this._scroll_list.RemoveAllChild();
		}
		return true;
	},
	SetBasePath : function(base_path) {
		if (this._base_path === base_path) {
			return true;
		}
		return this.SetPath(base_path, "");
	},
	HandleSetPathClick : function(event) {
		this.SetPath(this._base_path, this._path_input.text);
	},
	HandleSetPrePathClick : function(event) {
		let rel_path = ALittle.String_Sub(this._real_path, ALittle.String_Len(this._base_path) + 2);
		if (rel_path === "") {
			return;
		}
		this.SetPath(this._base_path, ALittle.File_GetFilePathByPath(rel_path));
	},
	HandleSearchClick : function(event) {
		this.Search(this._search_input.text);
	},
	HandleItemRButtonDown : function(event) {
		A_LayerManager.RemoveFromTip(this._image_pre_dialog);
		let user_data = event.target._user_data;
		let r_event = {};
		r_event.path = user_data.path;
		r_event.directory = user_data.directory;
		this.DispatchEvent(___all_struct.get(-1265378424), r_event);
	},
	HandleItemDropFile : function(event) {
		let real_path = this._real_path;
		let user_data = event.target._user_data;
		if (user_data !== undefined && user_data.directory) {
			real_path = this._base_path + "/" + user_data.path;
		}
		let name = ALittle.File_GetFileNameByPath(event.path);
		let path = event.path;
		let attr = ALittle.File_GetFileAttr(path);
		if (attr === undefined) {
			return;
		}
		if (attr.directory) {
			let [check, error] = this.CheckResourceName(name);
			if (!check) {
				g_AUITool.ShowNotice("提示", error);
				return;
			}
			ALittle.File_MakeDir(real_path + "/" + name);
			if (this._ext_map === undefined) {
				ALittle.File_CopyDeepDir(path, real_path + "/" + name);
			} else {
				let ___OBJECT_7 = this._ext_map;
				for (let ext in ___OBJECT_7) {
					let _ = ___OBJECT_7[ext];
					if (_ === undefined) continue;
					ALittle.File_CopyDeepDir(path, real_path + "/" + name, ext);
				}
			}
		} else {
			let upper_ext = ALittle.File_GetFileExtByPathAndUpper(event.path);
			if (this._ext_map !== undefined && this._ext_map[upper_ext] === undefined) {
				g_AUITool.ShowNotice("提示", "不能接受该类型的文件");
				return;
			}
			let [check, error] = this.CheckResourceName(ALittle.File_GetJustFileNameByPath(event.path));
			if (!check) {
				g_AUITool.ShowNotice("提示", error);
				return;
			}
			ALittle.File_CopyFile(event.path, real_path + "/" + name);
		}
		this.Refresh();
	},
	HandleNewDirectoryClick : async function(event) {
		let [x, y] = event.target.LocalToGlobal();
		let name = await g_AUITool.ShowRename("", x, y + event.target.height, 200);
		if (name === undefined || name === "") {
			return;
		}
		let [check, error] = this.CheckResourceName(name);
		if (!check) {
			g_AUITool.ShowNotice("错误", error);
			return;
		}
		ALittle.File_MakeDir(this._real_path + "/" + name);
		if (ALittle.File_GetFileAttr(this._real_path + "/" + name) === undefined) {
			g_AUITool.ShowNotice("错误", "文件夹创建失败");
			return;
		}
		this.Refresh();
	},
	HandleItemClick : function(event) {
		let user_data = event.target._user_data;
		if (event.count <= 1) {
			if (user_data.directory) {
				let e = {};
				e.path = user_data.path;
				e.ctrl = A_UISystem.sym_map.get(1073742048) !== undefined;
				this.DispatchEvent(___all_struct.get(-989784577), e);
			} else {
				if (this._thread !== undefined) {
					ALittle.Coroutine.Resume(this._thread, user_data.path);
					this._thread = undefined;
				}
				let e = {};
				e.path = user_data.path;
				e.ctrl = A_UISystem.sym_map.get(1073742048) !== undefined;
				this.DispatchEvent(___all_struct.get(1206110359), e);
			}
		} else if (event.count <= 2) {
			if (user_data.directory) {
				this._real_path = this._base_path + "/" + user_data.path;
				this.Refresh();
			}
		}
	},
	HandleItemMoveIn : function(event) {
		if (this._image_pre_dialog === undefined) {
			this._image_pre_dialog = AUIPlugin.g_Control.CreateControl("file_select_image_pre_dialog", this);
		}
		A_LayerManager.AddToTip(this._image_pre_dialog);
		let user_data = event.target._user_data;
		let path = this._base_path + "/" + user_data.path;
		this._pre_image.SetTextureCut(path, 0, 0, true, this.HandleItemPreViewCallback.bind(this));
		this.UpdateImagePreDialogPos();
	},
	HandleItemPreViewCallback : function(image, result) {
		let width = image.texture_width;
		image.width = width;
		if (width < 100) {
			width = 100;
		}
		if (width > A_UISystem.view_width) {
			width = A_UISystem.view_width;
			image.width = width;
		}
		this._image_pre_dialog.width = width + 10;
		image.x = (this._image_pre_dialog.width - image.width) / 2;
		let height = image.texture_height;
		image.height = height;
		if (height < 50) {
			height = 50;
		}
		if (height > A_UISystem.view_height - this._image_pre_dialog.head_size) {
			height = A_UISystem.view_height - this._image_pre_dialog.head_size;
			image.height = height;
		}
		image.y = (height + 5 - image.height) / 2;
		this._image_pre_dialog.height = this._image_pre_dialog.head_size + height + 10;
	},
	HandleItemMoveOut : function(event) {
		A_LayerManager.RemoveFromTip(this._image_pre_dialog);
	},
	HandleItemMouseMove : function(event) {
		this.UpdateImagePreDialogPos();
	},
	UpdateImagePreDialogPos : function() {
		if (this._image_pre_dialog === undefined) {
			return;
		}
		let x = A_UISystem.mouse_x + 20;
		if (x + this._image_pre_dialog.width > A_UISystem.view_width) {
			x = A_UISystem.view_width - this._image_pre_dialog.width;
		}
		let y = A_UISystem.mouse_y + 20;
		if (y + this._image_pre_dialog.height > A_UISystem.view_height) {
			y = A_UISystem.view_height - this._image_pre_dialog.height;
		}
		this._image_pre_dialog.x = x;
		this._image_pre_dialog.y = y;
	},
	CheckResourceName : function(name) {
		let len = ALittle.String_Len(name);
		if (len === 0) {
			return [false, "命名只能支持字母数字下划线"];
		}
		for (let i = 1; i <= len; i += 1) {
			let byte = ALittle.String_Byte(name, i);
			let check_all = byte >= 65 && byte <= 90 || byte >= 97 && byte <= 122 || byte >= 48 && byte <= 57 || byte === 95;
			if (check_all === false) {
				return [false, "命名只能支持字母数字下划线"];
			}
		}
		return [true, undefined];
	},
}, "AUIPlugin.AUIFileSelectLayout");

}