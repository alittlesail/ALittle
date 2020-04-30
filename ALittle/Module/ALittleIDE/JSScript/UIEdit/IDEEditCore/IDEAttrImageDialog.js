{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(766794486, "ALittleIDE.IDEAttrImageSelectItemInfo", {
name : "ALittleIDE.IDEAttrImageSelectItemInfo", ns_name : "ALittleIDE", rl_name : "IDEAttrImageSelectItemInfo", hash_code : 766794486,
name_list : ["name","frame","image","button"],
type_list : ["ALittle.DisplayObject","ALittle.DisplayObject","ALittle.Image","ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(271769996, "ALittleIDE.IDEAttrImageSelectItemUserData", {
name : "ALittleIDE.IDEAttrImageSelectItemUserData", ns_name : "ALittleIDE", rl_name : "IDEAttrImageSelectItemUserData", hash_code : 271769996,
name_list : ["path","directory"],
type_list : ["string","bool"],
option_map : {}
})
ALittle.RegStruct(-894949676, "ALittleIDE.IDEAttrImageSelectCollectRunTime", {
name : "ALittleIDE.IDEAttrImageSelectCollectRunTime", ns_name : "ALittleIDE", rl_name : "IDEAttrImageSelectCollectRunTime", hash_code : -894949676,
name_list : ["cur_count","total_count"],
type_list : ["int","int"],
option_map : {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
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
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name : "ALittle.UIClickEvent", ns_name : "ALittle", rl_name : "UIClickEvent", hash_code : -449066808,
name_list : ["target","is_drag"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name : "ALittle.UIMoveInEvent", ns_name : "ALittle", rl_name : "UIMoveInEvent", hash_code : 544684311,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
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

ALittleIDE.IDEAttrImageDialog = JavaScript.Class(undefined, {
	Ctor : function() {
		this._real_size = 100;
		this._src_title = undefined;
		this._callback = undefined;
		this._base_path = undefined;
		this._real_path = undefined;
	},
	Setup : function() {
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-332308624), this, this.HandleCloseProject);
	},
	HandleCloseProject : function(event) {
		if (this._dialog === undefined) {
			return;
		}
		this._scroll_list.RemoveAllChild();
		this.HideDialog();
	},
	Close : function() {
		this._callback = undefined;
		this._base_path = undefined;
		this._real_path = undefined;
		if (this._dialog !== undefined) {
			this._dialog.visible = false;
		}
	},
	HideDialog : function() {
		this._dialog.visible = false;
		this._callback = undefined;
	},
	ShowDialog : function(path, callback) {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "当前没有项目打开");
			return;
		}
		if (this._dialog === undefined) {
			this._dialog = ALittleIDE.g_Control.CreateControl("ide_image_select_dialog", this);
			A_LayerManager.AddToModal(this._dialog);
			this._src_title = this._dialog.title;
			if (this._src_title === undefined) {
				this._src_title = "图片选择器";
			}
		}
		if (path !== undefined || this._real_path === undefined) {
			if (this.SetPath(path) === false) {
				return;
			}
		}
		this._callback = callback;
		this._dialog.visible = true;
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
	CreateImgItem : function(file_name, rel_path, abs_path) {
		let ext = ALittle.File_GetFileExtByPath(file_name);
		ext = ALittle.String_Upper(ext);
		if (ext === "PNG" || ext === "JPG") {
			let info = {};
			let item = ALittleIDE.g_Control.CreateControl("ide_image_select_item", info);
			info.name.text = file_name;
			let width = undefined;
			let height = undefined;
			let surface = ALittle.System_LoadSurface(abs_path);
			if (surface !== undefined) {
				width = ALittle.System_GetSurfaceWidth(surface);
				height = ALittle.System_GetSurfaceHeight(surface);
				ALittle.System_FreeSurface(surface);
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
			info.image.SetTextureCut(abs_path, ALittle.Math_Floor(info.frame.width), ALittle.Math_Floor(info.frame.height), true);
			info.image.width = width;
			info.image.height = height;
			info.image.UpdateLayout();
			info.button.drag_trans_target = this._scroll_list;
			info.button.AddEventListener(___all_struct.get(-641444818), this, this.HandleItemRButtonDown);
			info.button.AddEventListener(___all_struct.get(-449066808), this, this.HandleItemClick);
			info.button.AddEventListener(___all_struct.get(544684311), this, this.HandleItemMoveIn);
			info.button.AddEventListener(___all_struct.get(-1202439334), this, this.HandleItemMoveOut);
			info.button.AddEventListener(___all_struct.get(-1001723540), this, this.HandleItemMouseMove);
			let user_data = {};
			user_data.path = rel_path;
			user_data.directory = false;
			info.button._user_data = user_data;
			item._user_data = user_data;
			return item;
		}
		return undefined;
	},
	CreateDirItem : function(file_name, rel_path, abs_path) {
		let info = {};
		let item = ALittleIDE.g_Control.CreateControl("ide_image_select_item", info);
		info.name.text = file_name;
		info.button.drag_trans_target = this._scroll_list;
		info.button.AddEventListener(___all_struct.get(-449066808), this, this.HandleItemClick);
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
		let file_map = ALittle.File_GetFileNameListByDir(browser_path);
		let ___OBJECT_1 = file_map;
		for (let file in ___OBJECT_1) {
			let info = ___OBJECT_1[file];
			if (info === undefined) continue;
			let path = browser_path + "/" + file;
			let rel_path = ALittle.String_Sub(path, ALittle.String_Len(this._base_path) + 2);
			let attr = ALittle.File_GetFileAttr(path);
			if (attr.mode === "directory") {
				let item = this.CreateDirItem(file, rel_path, path);
				if (item !== undefined) {
					ALittle.List_Push(item_list_dir, item);
				}
			} else {
				let item = this.CreateImgItem(file, rel_path, path);
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
		let file_map = ALittle.File_GetFileNameListByDir(search_path);
		let ___OBJECT_2 = file_map;
		for (let file in ___OBJECT_2) {
			let info = ___OBJECT_2[file];
			if (info === undefined) continue;
			let path = search_path + "/" + file;
			let rel_path = ALittle.String_Sub(path, ALittle.String_Len(this._base_path) + 2);
			let attr = ALittle.File_GetFileAttr(path);
			if (attr.mode === "directory") {
				this.SearchCollect(path, name, item_list, run_time);
			} else if (ALittle.String_Find(file, name) !== undefined) {
				let item = this.CreateImgItem(file, rel_path, path);
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
		ALittle.List_Sort(item_list_dir, ALittleIDE.IDEAttrImageDialog.ItemListCmp);
		ALittle.List_Sort(item_list_img, ALittleIDE.IDEAttrImageDialog.ItemListCmp);
		let item_list = [];
		let ___OBJECT_3 = item_list_dir;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let item = ___OBJECT_3[index - 1];
			if (item === undefined) break;
			ALittle.List_Push(item_list, item);
		}
		let ___OBJECT_4 = item_list_img;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let item = ___OBJECT_4[index - 1];
			if (item === undefined) break;
			ALittle.List_Push(item_list, item);
		}
		let col_count = ALittle.Math_Floor(this._scroll_list.width / this._real_size);
		let remain_count = 0;
		let container = undefined;
		let ___OBJECT_5 = item_list;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let item = ___OBJECT_5[index - 1];
			if (item === undefined) break;
			if (remain_count === 0) {
				container = ALittle.NewObject(ALittle.Linear, ALittleIDE.g_Control);
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
		this._dialog.title = this._src_title;
		let [item_list_dir, item_list_img] = this.BrowserCollect(this._real_path);
		this.CreateItemAndAddToList(item_list_dir, item_list_img);
	},
	Search : function(name) {
		this._scroll_list.RemoveAllChild();
		let [item_list_img, run_time] = this.SearchCollect(this._real_path, name);
		if (run_time.cur_count >= run_time.total_count) {
			this._dialog.title = this._src_title + "(筛选出来的数量太多，只显示前" + run_time.total_count + "个)";
		}
		this.CreateItemAndAddToList([], item_list_img);
	},
	SetPath : function(path) {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "当前没有项目打开");
			return false;
		}
		let real_path = ALittleIDE.g_IDEProject.project.base_path + "Texture";
		if (path === undefined) {
			path = "";
		}
		if (path !== "") {
			real_path = real_path + "/" + path;
		}
		let attr = ALittle.File_GetFileAttr(real_path);
		if (attr === undefined || attr.mode !== "directory") {
			ALittleIDE.g_IDETool.ShowNotice("错误", "无效路径");
			return false;
		}
		this._base_path = ALittleIDE.g_IDEProject.project.base_path + "Texture";
		this._real_path = real_path;
		this.Refresh();
		return true;
	},
	HandleSetPathClick : function(event) {
		this.SetPath(this._path_input.text);
	},
	HandleSetPrePathClick : function(event) {
		let rel_path = ALittle.String_Sub(this._real_path, ALittle.String_Len(this._base_path) + 2);
		if (rel_path === "") {
			return;
		}
		this.SetPath(ALittle.File_GetFilePathByPath(rel_path));
	},
	HandleSearchClick : function(event) {
		this.Search(this._search_input.text);
	},
	HandleItemRButtonDown : function(event) {
		if (this._image_select_menu === undefined) {
			this._image_select_menu = ALittleIDE.g_Control.CreateControl("ide_image_select_menu", this);
		}
		A_LayerManager.ShowFromRight(this._image_select_menu);
		this._image_select_menu.x = A_UISystem.mouse_x;
		this._image_select_menu.y = A_UISystem.mouse_y;
		this._image_select_menu._user_data = event.target._user_data;
	},
	HandleImageEditClick : function(event) {
		A_LayerManager.HideFromRight(this._image_select_menu);
		let user_data = this._image_select_menu._user_data;
		this._image_select_menu._user_data = undefined;
		ALittleIDE.g_IDEEditImageDialog.ShowDialog(ALittleIDE.g_IDEProject.project.base_path + "Texture/" + user_data.path);
	},
	HandleImageDeleteClick : function(event) {
		A_LayerManager.HideFromRight(this._image_select_menu);
		let user_data = this._image_select_menu._user_data;
		this._image_select_menu._user_data = undefined;
		ALittle.File_DeleteFile(ALittleIDE.g_IDEProject.project.base_path + "Texture/" + user_data.path);
		this.Refresh();
	},
	HandleItemClick : function(event) {
		let user_data = event.target._user_data;
		if (user_data.directory) {
			this._base_path = ALittleIDE.g_IDEProject.project.base_path + "Texture";
			this._real_path = ALittleIDE.g_IDEProject.project.base_path + "Texture/" + user_data.path;
			this.Refresh();
		} else {
			if (this._callback !== undefined) {
				this._callback(user_data.path);
				this._callback = undefined;
				this._dialog.visible = false;
			}
		}
	},
	HandleItemMoveIn : function(event) {
		if (this._image_pre_dialog === undefined) {
			this._image_pre_dialog = ALittleIDE.g_Control.CreateControl("ide_image_pre_dialog", this);
		}
		A_LayerManager.AddToTip(this._image_pre_dialog);
		let user_data = event.target._user_data;
		let path = ALittleIDE.g_IDEProject.project.base_path + "Texture/" + user_data.path;
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
		this._image_pre_dialog.width = width;
		image.x = (width - image.width) / 2;
		let height = image.texture_height;
		image.height = height;
		if (height < 50) {
			height = 50;
		}
		if (height > A_UISystem.view_height - this._image_pre_dialog.head_size) {
			height = A_UISystem.view_height - this._image_pre_dialog.head_size;
			image.height = height;
		}
		image.y = (height - image.height) / 2;
		this._image_pre_dialog.height = this._image_pre_dialog.head_size + height;
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
	HandleDialogDrag : function(event) {
		let delta_x = event.delta_x;
		let delta_y = event.delta_y;
		if (event.target === this._drag_lr_quad) {
			delta_y = 0;
		} else if (event.target === this._drag_ud_quad) {
			delta_x = 0;
		}
		this._dialog.width = this._dialog.width + delta_x;
		this._dialog.height = this._dialog.height + delta_y;
	},
}, "ALittleIDE.IDEAttrImageDialog");

ALittleIDE.g_IDEAttrImageDialog = ALittle.NewObject(ALittleIDE.IDEAttrImageDialog);
}