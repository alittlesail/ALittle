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
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name : "ALittle.UIMoveInEvent", ns_name : "ALittle", rl_name : "UIMoveInEvent", hash_code : 544684311,
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
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name : "ALittle.UIMoveOutEvent", ns_name : "ALittle", rl_name : "UIMoveOutEvent", hash_code : -1202439334,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

ALittleIDE.IDEImageManager = JavaScript.Class(undefined, {
	HandleImageSearchClick : function(event) {
		this._image_scroll_screen.RemoveAllChild();
		let project = ALittleIDE.g_IDEProject.project;
		if (project === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("提示", "当前没有打开的项目");
			return;
		}
		let key = this._image_search_key.text;
		let image_info_list = [];
		let image_info_count = 0;
		let path = project.base_path + "Texture";
		let file_map = ALittle.File_GetFileAttrByDir(path);
		let ___OBJECT_1 = file_map;
		for (let file_path in ___OBJECT_1) {
			let attr = ___OBJECT_1[file_path];
			if (attr === undefined) continue;
			let file_name = ALittle.File_GetFileNameByPath(file_path);
			if (key === "" || ALittle.String_Find(file_name, key) !== undefined) {
				++ image_info_count;
				image_info_list[image_info_count - 1] = file_path;
			}
		}
		ALittle.List_Sort(image_info_list);
		let ___OBJECT_2 = image_info_list;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let file_path = ___OBJECT_2[index - 1];
			if (file_path === undefined) break;
			let file_name = ALittle.File_GetFileNameByPath(file_path);
			let item = ALittleIDE.g_Control.CreateControl("ide_common_item_button");
			item.text = file_name;
			item._user_data = ALittle.String_Sub(file_path, ALittle.String_Len(path) + 2);
			item.AddEventListener(___all_struct.get(-641444818), this, this.HandleImageItemRightClick);
			item.AddEventListener(___all_struct.get(544684311), this, this.HandleImageItemMoveIn);
			item.AddEventListener(___all_struct.get(-1001723540), this, this.HandleImageItemMouseMove);
			item.AddEventListener(___all_struct.get(-1202439334), this, this.HandleImageItemMoveOut);
			item.drag_trans_target = this._image_scroll_screen;
			this._image_scroll_screen.AddChild(item);
		}
	},
	ClearImageItem : function() {
		this._image_scroll_screen.RemoveAllChild();
	},
	HandleImageItemMoveIn : function(event) {
		if (this._image_tip_dialog === undefined) {
			this._image_tip_dialog = ALittle.NewObject(ALittle.Image, ALittleIDE.g_IDEProject.project.control);
			this._image_tip_dialog.width = 100;
			this._image_tip_dialog.height = 100;
			A_LayerManager.AddToTip(this._image_tip_dialog);
		}
		this._image_tip_dialog.texture_name = event.target._user_data;
		this._image_tip_dialog.visible = true;
	},
	HandleImageItemMouseMove : function(event) {
		if (this._image_tip_dialog === undefined) {
			return;
		}
		let x = A_UISystem.mouse_x + 10;
		let y = A_UISystem.mouse_y + 10;
		if (y + this._image_tip_dialog.height > A_UISystem.view_height) {
			y = A_UISystem.view_height - this._image_tip_dialog.height;
		}
		this._image_tip_dialog.x = x;
		this._image_tip_dialog.y = y;
	},
	HandleImageItemMoveOut : function(event) {
		if (this._image_tip_dialog === undefined) {
			return;
		}
		this._image_tip_dialog.visible = false;
	},
	HandleImageItemRightClick : function(event) {
		if (this._image_right_menu === undefined) {
			this._image_right_menu = ALittleIDE.g_Control.CreateControl("ide_image_right_menu", this);
		}
		A_LayerManager.ShowFromRight(this._image_right_menu);
		this._image_right_menu.x = A_UISystem.mouse_x;
		this._image_right_menu.y = A_UISystem.mouse_y;
		if (this._image_right_menu.x + this._image_right_menu.width > A_UISystem.view_width) {
			this._image_right_menu.x = A_UISystem.view_width - this._image_right_menu.width;
		}
		if (this._image_right_menu.y + this._image_right_menu.height > A_UISystem.view_height) {
			this._image_right_menu.y = A_UISystem.view_height - this._image_right_menu.height;
		}
		this._image_right_menu._user_data = event.target;
	},
	DeleteControlImpl : function(target) {
		ALittleIDE.g_IDEUICenter.image_scroll_screen.RemoveChild(target);
		ALittle.File_DeleteFile(target._user_data);
	},
	HandleImageRightMenuDelete : function(event) {
		A_LayerManager.HideFromRight(this._image_right_menu);
		let target = this._image_right_menu._user_data;
		this._image_right_menu._user_data = undefined;
		let callback = this.DeleteControlImpl.bind(this, target);
		ALittleIDE.g_IDETool.DeleteNotice("提示", "确定要删除" + target.text + "吗?", callback);
	},
	HandleImageRightMenuCopyPath : function(event) {
		A_LayerManager.HideFromRight(this._image_right_menu);
		let target = this._image_right_menu._user_data;
		this._image_right_menu._user_data = undefined;
		ALittle.System_SetClipboardText(target._user_data);
	},
	HandleImageRightMenuCopyCode : function(event) {
		A_LayerManager.HideFromRight(this._image_right_menu);
		let target = this._image_right_menu._user_data;
		this._image_right_menu._user_data = undefined;
		this.CopyImageCodeImpl(target._user_data);
	},
	CopyImageCodeImpl : function(file_path) {
		let width = 100;
		let height = 100;
		let surface = ALittle.System_LoadSurface(ALittleIDE.g_IDEProject.project.base_path + "Texture/" + file_path);
		if (surface !== undefined) {
			width = ALittle.System_GetSurfaceWidth(surface);
			height = ALittle.System_GetSurfaceHeight(surface);
			ALittle.System_FreeSurface(surface);
		}
		let display_info = {};
		display_info.__class = "Image";
		display_info.texture_name = file_path;
		display_info.width_type = 1;
		display_info.width_value = width;
		display_info.height_type = 1;
		display_info.height_value = height;
		let info = {};
		info.index = 1;
		info.info = display_info;
		let copy_list = [];
		copy_list[1 - 1] = info;
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list));
	},
	HandleImageRightMenuGrid9 : function(event) {
		A_LayerManager.HideFromRight(this._image_right_menu);
		let target = this._image_right_menu._user_data;
		this._image_right_menu._user_data = undefined;
		let display_info = ALittleIDE.IDEUtility_GenerateGrid9ImageInfo(ALittleIDE.g_IDEProject.project.base_path + "Texture/", target._user_data);
		if (display_info === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "图片加载失败:" + target._user_data);
			return;
		}
		let copy_list = [];
		let info = {};
		info.index = 1;
		info.info = display_info;
		copy_list[1 - 1] = info;
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list));
	},
	HandleImageRightMenuRepair : function(event) {
		A_LayerManager.HideFromRight(this._image_right_menu);
		let target = this._image_right_menu._user_data;
		this._image_right_menu._user_data = undefined;
		let full_path = ALittleIDE.g_IDEProject.project.base_path + "Texture/" + target._user_data;
		let surface = ALittle.System_LoadSurface(full_path);
		if (surface !== undefined) {
			ALittle.System_SaveSurface(surface, full_path);
			ALittle.System_FreeSurface(surface);
		}
	},
	HandleImageRightMenuCutEmpty : function(event) {
		A_LayerManager.HideFromRight(this._image_right_menu);
		let target = this._image_right_menu._user_data;
		this._image_right_menu._user_data = undefined;
		let full_path = ALittleIDE.g_IDEProject.project.base_path + "Texture/" + target._user_data;
		let surface = ALittle.System_LoadSurface(full_path);
		if (surface !== undefined) {
			let width = ALittle.System_GetSurfaceWidth(surface);
			let height = ALittle.System_GetSurfaceHeight(surface);
			let left = 0;
			for (let i = 1; i <= width; i += 1) {
				left = i - 1;
				let flag = false;
				for (let j = 1; j <= height; j += 1) {
					let color = ALittle.System_GetSurfacePixel(surface, i - 1, j - 1);
					if (color !== 0) {
						flag = true;
						break;
					}
				}
				if (flag === true) {
					break;
				}
			}
			let right = 0;
			for (let i = width; i >= 1; i += -1) {
				right = i - 1;
				let flag = false;
				for (let j = 1; j <= height; j += 1) {
					let color = ALittle.System_GetSurfacePixel(surface, i - 1, j - 1);
					if (color !== 0) {
						flag = true;
						break;
					}
				}
				if (flag === true) {
					break;
				}
			}
			let top = 0;
			for (let j = 1; j <= height; j += 1) {
				top = j - 1;
				let flag = false;
				for (let i = 1; i <= width; i += 1) {
					let color = ALittle.System_GetSurfacePixel(surface, i - 1, j - 1);
					if (color !== 0) {
						flag = true;
						break;
					}
				}
				if (flag === true) {
					break;
				}
			}
			let bottom = 0;
			for (let j = height; j >= 1; j += -1) {
				bottom = j - 1;
				let flag = false;
				for (let i = 1; i <= width; i += 1) {
					let color = ALittle.System_GetSurfacePixel(surface, i - 1, j - 1);
					if (color !== 0) {
						flag = true;
						break;
					}
				}
				if (flag === true) {
					break;
				}
			}
			if (left <= right && top <= bottom) {
				let new_width = right - left + 1;
				let new_height = bottom - top + 1;
				let new_surface = ALittle.System_CreateSurface(new_width, new_height);
				ALittle.System_CutBlitSurface(new_surface, surface, "0,0," + new_width + "," + new_height, left + "," + top + "," + new_width + "," + new_height);
				ALittle.System_SaveSurface(new_surface, full_path);
			}
			ALittle.System_FreeSurface(surface);
		}
	},
}, "ALittleIDE.IDEImageManager");

ALittleIDE.g_IDEImageManager = ALittle.NewObject(ALittleIDE.IDEImageManager);
}