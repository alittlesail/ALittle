{
if (typeof ALittleIDE === "undefined") ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-2082638860, "ALittleIDE.IDEQuickInfo", {
name : "ALittleIDE.IDEQuickInfo", ns_name : "ALittleIDE", rl_name : "IDEQuickInfo", hash_code : -2082638860,
name_list : ["scroll_list","item_map"],
type_list : ["ALittle.ScrollList","Map<string,ALittle.DisplayObject>"],
option_map : {}
})
ALittle.RegStruct(-57691431, "ALittleIDE.IDEQuickItemInfo", {
name : "ALittleIDE.IDEQuickItemInfo", ns_name : "ALittleIDE", rl_name : "IDEQuickItemInfo", hash_code : -57691431,
name_list : ["image","button","name","frame"],
type_list : ["ALittle.Image","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(2079069064, "ALittleIDE.IDEQuickItemUserData", {
name : "ALittleIDE.IDEQuickItemUserData", ns_name : "ALittleIDE", rl_name : "IDEQuickItemUserData", hash_code : 2079069064,
name_list : ["path","flag_type","name","directory"],
type_list : ["string","string","string","bool"],
option_map : {}
})
ALittle.RegStruct(220740939, "ALittleIDE.IDEQuickLoadingInfo", {
name : "ALittleIDE.IDEQuickLoadingInfo", ns_name : "ALittleIDE", rl_name : "IDEQuickLoadingInfo", hash_code : 220740939,
name_list : ["map","loop"],
type_list : ["Map<ALittleIDE.IDEQuickItemInfo,bool>","int"],
option_map : {}
})
ALittle.RegStruct(884272790, "ALittleIDE.IDEQuickConfigInfo", {
name : "ALittleIDE.IDEQuickConfigInfo", ns_name : "ALittleIDE", rl_name : "IDEQuickConfigInfo", hash_code : 884272790,
name_list : ["name","time"],
type_list : ["string","int"],
option_map : {}
})
ALittle.RegStruct(2050097508, "ALittleIDE.IDEQuickSearchRunTime", {
name : "ALittleIDE.IDEQuickSearchRunTime", ns_name : "ALittleIDE", rl_name : "IDEQuickSearchRunTime", hash_code : 2050097508,
name_list : ["cur_count","total_count","item_count"],
type_list : ["int","int","int"],
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
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name : "ALittle.UIClickEvent", ns_name : "ALittle", rl_name : "UIClickEvent", hash_code : -449066808,
name_list : ["target","is_drag"],
type_list : ["ALittle.DisplayObject","bool"],
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

ALittleIDE.IDEQuickManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._flag_type_list = ["常用按钮", "常用图片", "常用文本", "其他常用"];
		this._quick_map = {};
		let ___OBJECT_1 = this._flag_type_list;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let flag_type = ___OBJECT_1[k - 1];
			if (flag_type === undefined) break;
			this._quick_map[flag_type] = {};
		}
		this._first_tab = undefined;
		this._real_size = 80;
		this._loading = {};
	},
	Setup : function(project_quick_tab) {
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(1962591044), this, this.HandleDeleteControl);
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(374071006), this, this.HandleChangeControl);
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-975432877), this, this.HandleOpenProject);
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-332308624), this, this.HandleCloseProject);
		this._project_quick_tab = project_quick_tab;
		this._first_tab = ALittleIDE.g_Control.CreateControl("ide_main_project_quick_search", this);
		this._project_quick_tab.AddChild(this._first_tab);
		this._project_quick_tab.SetChildText(this._first_tab, "控件选择器");
		let ___OBJECT_2 = this._flag_type_list;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let flag_type = ___OBJECT_2[k - 1];
			if (flag_type === undefined) break;
			let item = ALittleIDE.g_Control.CreateControl("ide_common_scroll_list", this);
			this._project_quick_tab.AddChild(item);
			this._project_quick_tab.SetChildText(item, flag_type);
			this._quick_map[flag_type].scroll_list = item;
		}
	},
	CreateItemDelay : function(control, abs_path) {
		ALittleIDE.g_Control.SaveControlToFile(control, abs_path);
		let loading = this._loading[abs_path];
		if (loading === undefined) {
			return;
		}
		for (let [info, v] of loading.map) {
			if (v === undefined) continue;
			info.image.SetTextureCut(abs_path, ALittle.Math_Floor(info.frame.width), ALittle.Math_Floor(info.frame.height), true);
		}
	},
	CreateItem : function(control_info, flag_type) {
		let info = {};
		let item = ALittleIDE.g_Control.CreateControl("ide_quick_select_item", info);
		info.name.text = control_info.name;
		if (ALittle.File_GetFileAttr(this._base_path) === undefined) {
			ALittle.File_MakeDeepDir(this._base_path);
		}
		let abs_path = this._base_path + "/" + control_info.name + ".png";
		let width = undefined;
		let height = undefined;
		let surface = ALittle.System_LoadSurface(abs_path);
		if (surface !== undefined) {
			width = ALittle.System_GetSurfaceWidth(surface);
			height = ALittle.System_GetSurfaceHeight(surface);
			ALittle.System_FreeSurface(surface);
		}
		if (width === undefined) {
			let control = ALittleIDE.g_IDEProject.project.control.CreateControl(control_info.name);
			if (control === undefined) {
				return undefined;
			}
			width = control.width;
			height = control.height;
			if (width <= 0) {
				control.width = ALittleIDE.g_IDEProject.project.config.GetConfig("default_show_width", 800);
				width = control.width;
			}
			if (height <= 0) {
				control.height = ALittleIDE.g_IDEProject.project.config.GetConfig("default_show_height", 800);
				height = control.height;
			}
			let loading = this._loading[abs_path];
			if (loading === undefined) {
				loading = {};
				loading.map = new Map();
				this._loading[abs_path] = loading;
				loading.loop = A_LoopSystem.AddTimer(2000, this.CreateItemDelay.bind(this, control, abs_path));
			}
			loading.map.set(info, true);
		} else {
			info.image.SetTextureCut(abs_path, ALittle.Math_Floor(info.frame.width), ALittle.Math_Floor(info.frame.height), true);
		}
		if (width < height) {
			let rate = width / height;
			height = info.frame.height;
			width = rate * height;
		} else {
			let rate = height / width;
			width = info.frame.width;
			height = rate * width;
		}
		info.image.width = width;
		info.image.height = height;
		info.image.UpdateLayout();
		info.button.AddEventListener(___all_struct.get(-449066808), this, this.HandleItemClick);
		info.button.AddEventListener(___all_struct.get(-641444818), this, this.HandleItemRButtonDown);
		info.button.AddEventListener(___all_struct.get(544684311), this, this.HandleItemMoveIn);
		info.button.AddEventListener(___all_struct.get(-1202439334), this, this.HandleItemMoveOut);
		info.button.AddEventListener(___all_struct.get(-1001723540), this, this.HandleItemMouseMove);
		info.button.AddEventListener(___all_struct.get(1301789264), this, this.HandleItemDragBegin);
		info.button.AddEventListener(___all_struct.get(1337289812), this, this.HandleItemDrag);
		info.button.AddEventListener(___all_struct.get(150587926), this, this.HandleItemDragEnd);
		let user_data = {};
		user_data.path = abs_path;
		user_data.flag_type = flag_type;
		user_data.name = control_info.name;
		user_data.directory = false;
		info.button._user_data = user_data;
		item._user_data = user_data;
		return item;
	},
	CreateItemAndAddToList : function(scroll_list, item_list) {
		let col_count = ALittle.Math_Floor(scroll_list.width / this._real_size);
		let remain_count = 0;
		let container = undefined;
		let ___OBJECT_3 = item_list;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let item = ___OBJECT_3[index - 1];
			if (item === undefined) break;
			if (remain_count === 0) {
				container = ALittle.NewObject(ALittle.Linear, ALittleIDE.g_Control);
				container.type = 1;
				container.height = item.height;
				scroll_list.AddChild(container);
				container.AddChild(item);
				remain_count = col_count - 1;
			} else {
				remain_count = remain_count - 1;
				container.AddChild(item);
			}
		}
	},
	AddToList : function(scroll_list, item) {
		let col_count = ALittle.Math_Floor(scroll_list.width / this._real_size);
		let container = scroll_list.GetChildByIndex(scroll_list.child_count);
		if (container !== undefined && container.child_count >= col_count) {
			container = undefined;
		}
		if (container === undefined) {
			container = ALittle.NewObject(ALittle.Linear, ALittleIDE.g_Control);
			container.type = 1;
			container.height = item.height;
			scroll_list.AddChild(container);
		}
		container.AddChild(item);
	},
	RemoveFromList : function(scroll_list, item) {
		let item_list = [];
		let item_count = 0;
		let childs = scroll_list.childs;
		let ___OBJECT_4 = childs;
		for (let k = 1; k <= ___OBJECT_4.length; ++k) {
			let child = ___OBJECT_4[k - 1];
			if (child === undefined) break;
			let ___OBJECT_5 = child.childs;
			for (let _ = 1; _ <= ___OBJECT_5.length; ++_) {
				let child_item = ___OBJECT_5[_ - 1];
				if (child_item === undefined) break;
				if (child_item !== item) {
					++ item_count;
					item_list[item_count - 1] = child_item;
				}
			}
		}
		scroll_list.RemoveAllChild();
		this.CreateItemAndAddToList(scroll_list, item_list);
	},
	SearchCollect : function(search_type, key, item_list, run_time) {
		if (item_list === undefined) {
			item_list = [];
		}
		if (run_time === undefined) {
			run_time = {};
			run_time.cur_count = 0;
			run_time.total_count = 100;
			run_time.item_count = 0;
		}
		if (key === "" || key === undefined) {
			return [item_list, run_time];
		}
		let project = ALittleIDE.g_IDEProject.project;
		if (project === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("提示", "当前没有打开的项目");
			return [undefined, undefined];
		}
		let control_map = project.control_map;
		let ___OBJECT_6 = control_map;
		for (let control_name in ___OBJECT_6) {
			let control_info = ___OBJECT_6[control_name];
			if (control_info === undefined) continue;
			if (search_type === "控件名|描述") {
				if (key === "" || ALittle.String_Find(control_name, key) !== undefined || (control_info.info.description !== undefined && ALittle.String_Find(control_info.info.description, key) !== undefined)) {
					let item = this.CreateItem(control_info, "控件选择器");
					if (item !== undefined) {
						++ run_time.item_count;
						item_list[run_time.item_count - 1] = item;
					}
				}
			} else if (search_type === "插件名") {
				if (ALittleIDE.IDEUtility_HasTargetClass(control_info.info, key)) {
					let item = this.CreateItem(control_info, "控件选择器");
					if (item !== undefined) {
						++ run_time.item_count;
						item_list[run_time.item_count - 1] = item;
					}
				}
			} else if (search_type === "事件设置") {
				if (ALittleIDE.IDEUtility_HasEventCallback(control_info.info, key)) {
					let item = this.CreateItem(control_info, "控件选择器");
					if (item !== undefined) {
						++ run_time.item_count;
						item_list[run_time.item_count - 1] = item;
					}
				}
			}
			if (run_time.cur_count >= run_time.total_count) {
				return [item_list, run_time];
			}
		}
		return [item_list, run_time];
	},
	SearchCmp : function(a, b) {
		let a_user_data = a._user_data;
		let b_user_data = b._user_data;
		return a_user_data.path < b_user_data.path;
	},
	Search : function(search_type, name) {
		this._scroll_list.RemoveAllChild();
		let [item_list, run_time] = this.SearchCollect(search_type, name);
		let title = "控件选择器";
		if (run_time.cur_count >= run_time.total_count) {
			title = title + "(筛选出来的数量太多，只显示前" + run_time.total_count + "个)";
		}
		ALittle.List_Sort(item_list, ALittleIDE.IDEQuickManager.SearchCmp);
		this._project_quick_tab.SetChildText(this._first_tab, title);
		this.CreateItemAndAddToList(this._scroll_list, item_list);
	},
	HandleSearchClick : function(event) {
		this.Search(this._search_type.text, this._search_input.text);
	},
	HandleItemClick : function(event) {
	},
	HandleItemRButtonDown : function(event) {
		if (this._quick_right_menu === undefined) {
			this._quick_right_menu = ALittleIDE.g_Control.CreateControl("ide_quick_right_menu", this);
		}
		A_LayerManager.ShowFromRight(this._quick_right_menu);
		this._quick_right_menu.x = A_UISystem.mouse_x;
		this._quick_right_menu.y = A_UISystem.mouse_y;
		if (this._quick_right_menu.x + this._quick_right_menu.width > A_UISystem.view_width) {
			this._quick_right_menu.x = A_UISystem.view_width - this._quick_right_menu.width;
		}
		if (this._quick_right_menu.y + this._quick_right_menu.height > A_UISystem.view_height) {
			this._quick_right_menu.y = A_UISystem.view_height - this._quick_right_menu.height;
		}
		this._quick_right_menu._user_data = event.target;
	},
	HandleQuickRightMenuCopyName : function(event) {
		A_LayerManager.HideFromRight(this._quick_right_menu);
		let target = this._quick_right_menu._user_data;
		this._quick_right_menu._user_data = undefined;
		let user_data = target._user_data;
		ALittle.System_SetClipboardText(user_data.name);
	},
	HandleQuickRightMenuCopyExtends : function(event) {
		A_LayerManager.HideFromRight(this._quick_right_menu);
		let target = this._quick_right_menu._user_data;
		this._quick_right_menu._user_data = undefined;
		let user_data = target._user_data;
		let display_info = {};
		display_info.__extends = user_data.name;
		let info = {};
		info.index = 1;
		info.info = display_info;
		let copy_list = [];
		copy_list[1 - 1] = info;
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list));
	},
	HandleQuickRightMenuDelete : function(event) {
		A_LayerManager.HideFromRight(this._quick_right_menu);
		let target = this._quick_right_menu._user_data;
		this._quick_right_menu._user_data = undefined;
		let user_data = target._user_data;
		let control_name = user_data.name;
		let flag_type = user_data.flag_type;
		let cfg_quick_map = ALittleIDE.g_IDEProject.project.config.GetConfig("quick_map", {});
		let cfg_info_map = cfg_quick_map[flag_type];
		if (cfg_info_map === undefined) {
			return;
		}
		if (cfg_info_map[control_name] === undefined) {
			return;
		}
		delete cfg_info_map[control_name];
		ALittleIDE.g_IDEProject.project.config.SetConfig("quick_map", cfg_quick_map);
		let quick_info = this._quick_map[flag_type];
		if (quick_info.item_map !== undefined) {
			let item = quick_info.item_map[control_name];
			if (item !== undefined) {
				delete quick_info.item_map[control_name];
				this.RemoveFromList(quick_info.scroll_list, item);
			}
		}
	},
	HandleItemDragBegin : function(event) {
		this._drag_image = ALittle.NewObject(ALittle.Image, ALittleIDE.g_Control);
		let user_data = event.target._user_data;
		this._drag_image._user_data = user_data;
		A_LayerManager.AddToTip(this._drag_image);
		this._drag_image.alpha = 0.5;
		this._drag_image.SetTextureCut(user_data.path, 0, 0, true, this.HandleItemDragViewCallback.bind(this));
		if (this._quick_pre_dialog !== undefined) {
			A_LayerManager.RemoveFromTip(this._quick_pre_dialog);
		}
	},
	HandleItemDragViewCallback : function(image, result) {
		image.width = image.texture_width;
		image.height = image.texture_height;
		image.x = A_UISystem.mouse_x - image.width / 2;
		image.y = A_UISystem.mouse_y - image.height / 2;
	},
	HandleItemDrag : function(event) {
		this._drag_image.x = this._drag_image.x + event.delta_x;
		this._drag_image.y = this._drag_image.y + event.delta_y;
	},
	HandleItemDragEnd : function(event) {
		A_LayerManager.RemoveFromTip(this._drag_image);
		let abs_x = this._drag_image.x;
		let abs_y = this._drag_image.y;
		this._drag_image = undefined;
		let user_data = event.target._user_data;
		let cur_tab_child = ALittleIDE.g_IDETabManager.cur_tab_child;
		if (cur_tab_child === undefined) {
			return;
		}
		cur_tab_child.QuickDragAddControl(abs_x, abs_y, user_data.name);
	},
	HandleItemMoveIn : function(event) {
		if (this._quick_pre_dialog === undefined) {
			this._quick_pre_dialog = ALittleIDE.g_Control.CreateControl("ide_quick_pre_dialog", this);
		}
		A_LayerManager.AddToTip(this._quick_pre_dialog);
		let user_data = event.target._user_data;
		this._pre_image.SetTextureCut(user_data.path, 0, 0, true, this.HandleItemPreViewCallback.bind(this));
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
		this._quick_pre_dialog.width = width;
		image.x = (width - image.width) / 2;
		let height = image.texture_height;
		image.height = height;
		if (height < 50) {
			height = 50;
		}
		if (height > A_UISystem.view_height - this._quick_pre_dialog.head_size) {
			height = A_UISystem.view_height - this._quick_pre_dialog.head_size;
			image.height = height;
		}
		image.y = (height - image.height) / 2;
		this._quick_pre_dialog.height = this._quick_pre_dialog.head_size + height;
	},
	HandleItemMoveOut : function(event) {
		A_LayerManager.RemoveFromTip(this._quick_pre_dialog);
	},
	HandleItemMouseMove : function(event) {
		this.UpdateImagePreDialogPos();
	},
	UpdateImagePreDialogPos : function() {
		if (this._quick_pre_dialog === undefined) {
			return;
		}
		let x = A_UISystem.mouse_x + 20;
		if (x + this._quick_pre_dialog.width > A_UISystem.view_width) {
			x = A_UISystem.view_width - this._quick_pre_dialog.width;
		}
		let y = A_UISystem.mouse_y + 20;
		if (y + this._quick_pre_dialog.height > A_UISystem.view_height) {
			y = A_UISystem.view_height - this._quick_pre_dialog.height;
		}
		this._quick_pre_dialog.x = x;
		this._quick_pre_dialog.y = y;
	},
	HandleOpenProject : function(event) {
		this._base_path = ALittleIDE.g_IDEProject.project.base_path + "IDETemp/QuickManager";
		let control_map = ALittleIDE.g_IDEProject.project.control_map;
		let cfg_quick_map = ALittleIDE.g_IDEProject.project.config.GetConfig("quick_map", {});
		let ___OBJECT_7 = cfg_quick_map;
		for (let flag_type in ___OBJECT_7) {
			let cfg_map = ___OBJECT_7[flag_type];
			if (cfg_map === undefined) continue;
			let quick_info = this._quick_map[flag_type];
			if (quick_info !== undefined) {
				let item_list = [];
				let item_list_count = 0;
				quick_info.item_map = {};
				let ___OBJECT_8 = cfg_map;
				for (let k in ___OBJECT_8) {
					let cfg_info = ___OBJECT_8[k];
					if (cfg_info === undefined) continue;
					let control_info = control_map[cfg_info.name];
					if (control_info !== undefined) {
						let item = this.CreateItem(control_info, flag_type);
						if (item !== undefined) {
							++ item_list_count;
							item_list[item_list_count - 1] = item;
							quick_info.item_map[cfg_info.name] = item;
						}
					}
				}
				this.CreateItemAndAddToList(quick_info.scroll_list, item_list);
			}
		}
	},
	HandleCloseProject : function(event) {
		let ___OBJECT_9 = this._quick_map;
		for (let k in ___OBJECT_9) {
			let quick_info = ___OBJECT_9[k];
			if (quick_info === undefined) continue;
			quick_info.scroll_list.RemoveAllChild();
			quick_info.item_map = {};
		}
		this._scroll_list.RemoveAllChild();
	},
	HandleDeleteControl : function(event) {
		let control_name = event.name;
		let abs_path = ALittleIDE.g_IDEProject.project.base_path + "IDETemp/QuickManager/" + control_name + ".png";
		ALittle.File_DeleteFile(abs_path);
		let loading = this._loading[abs_path];
		delete this._loading[abs_path];
		if (loading !== undefined) {
			A_LoopSystem.RemoveTimer(loading.loop);
			loading.loop = undefined;
		}
		let cfg_quick_map = ALittleIDE.g_IDEProject.project.config.GetConfig("quick_map", {});
		let has_changed = false;
		let ___OBJECT_10 = cfg_quick_map;
		for (let flag_type in ___OBJECT_10) {
			let cfg_info_map = ___OBJECT_10[flag_type];
			if (cfg_info_map === undefined) continue;
			if (cfg_info_map[control_name] !== undefined) {
				delete cfg_info_map[control_name];
				has_changed = true;
			}
		}
		if (has_changed) {
			ALittleIDE.g_IDEProject.project.config.SetConfig("quick_map", cfg_quick_map);
		}
		let ___OBJECT_11 = this._quick_map;
		for (let flag_type in ___OBJECT_11) {
			let quick_info = ___OBJECT_11[flag_type];
			if (quick_info === undefined) continue;
			if (quick_info.item_map !== undefined) {
				let item = quick_info.item_map[control_name];
				if (item !== undefined) {
					delete quick_info.item_map[control_name];
					this.RemoveFromList(quick_info.scroll_list, item);
				}
			}
		}
	},
	HandleChangeControl : function(event) {
	},
	FlagImage : function(control_name) {
		this.FlagImpl("常用图片", control_name);
	},
	FlagButton : function(control_name) {
		this.FlagImpl("常用按钮", control_name);
	},
	FlagText : function(control_name) {
		this.FlagImpl("常用文本", control_name);
	},
	FlagOther : function(control_name) {
		this.FlagImpl("其他常用", control_name);
	},
	FlagImpl : function(flag_type, control_name) {
		let control_map = ALittleIDE.g_IDEProject.project.control_map;
		let control_info = control_map[control_name];
		if (control_info === undefined) {
			return;
		}
		let quick_info = this._quick_map[flag_type];
		if (quick_info === undefined) {
			return;
		}
		let cfg_quick_map = ALittleIDE.g_IDEProject.project.config.GetConfig("quick_map", {});
		let cfg_info_map = cfg_quick_map[flag_type];
		if (cfg_info_map === undefined) {
			cfg_info_map = {};
			cfg_quick_map[flag_type] = cfg_info_map;
		}
		if (cfg_info_map[control_name] !== undefined) {
			return;
		}
		let item = this.CreateItem(control_info, flag_type);
		if (item === undefined) {
			return;
		}
		this.AddToList(quick_info.scroll_list, item);
		if (quick_info.item_map === undefined) {
			quick_info.item_map = {};
		}
		quick_info.item_map[control_name] = item;
		let info = {};
		info.name = control_name;
		info.time = ALittle.Time_GetCurTime();
		cfg_info_map[control_name] = info;
		ALittleIDE.g_IDEProject.project.config.SetConfig("quick_map", cfg_quick_map);
	},
}, "ALittleIDE.IDEQuickManager");

ALittleIDE.g_IDEQuickManager = ALittle.NewObject(ALittleIDE.IDEQuickManager);
}