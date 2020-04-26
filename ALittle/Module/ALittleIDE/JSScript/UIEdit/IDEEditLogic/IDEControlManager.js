{
if (typeof ALittleIDE === "undefined") ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-11865120, "ALittleIDE.IDEControlItemUserData", {
name : "ALittleIDE.IDEControlItemUserData", ns_name : "ALittleIDE", rl_name : "IDEControlItemUserData", hash_code : -11865120,
name_list : ["pre_index","presee","control_info"],
type_list : ["int","bool","ALittleIDE.IDEControlInfo"],
option_map : {}
})
ALittle.RegStruct(-4982446, "ALittle.DisplayInfo", {
name : "ALittle.DisplayInfo", ns_name : "ALittle", rl_name : "DisplayInfo", hash_code : -4982446,
name_list : ["__target_class","__class_func","__base_attr","__show_attr","loop_map","__class","__include","__extends","__childs","__event","__link","__shows_included","__childs_included","__extends_included","description","text","font_path","font_size","red","green","blue","alpha","bold","italic","underline","deleteline","outline","x","y","x_type","x_value","y_type","y_value","width","height","width_type","width_value","height_type","height_value","scale_x","scale_y","center_x","center_y","angle","flip","hand_cursor","visible","disabled","left_size","right_size","top_size","bottom_size","texture_name","interval","play_loop_count","var_play","base_y","head_size","gap","up_size","down_size","cursor_red","cursor_green","cursor_blue","default_text_alpha","ims_padding","margin_left","margin_right","margin_top","margin_bottom","show_count","body_margin","screen_margin_left","screen_margin_right","screen_margin_top","screen_margin_bottom","start_degree","end_degree","line_spacing","max_line_count","font_red","font_green","font_blue","margin_halign","margin_valign","cursor_margin_up","cursor_margin_down","total_size","show_size","offset_rate","offset_step","grade","row_count","col_count","row_index","col_index","u1","v1","u2","v2","u3","v3","x1","y1","x2","y2","x3","y3","x_gap","y_gap","x_start_gap","y_start_gap","button_gap","button_start","button_margin","tab_index","view_margin","child_width_margin"],
type_list : ["List<string>","any","Map<string,any>","Map<string,any>","Map<string,ALittle.LoopGroupInfo>","string","string","string","List<ALittle.DisplayInfo>","List<ALittle.EventInfo>","string","bool","bool","bool","string","string","string","int","double","double","double","double","bool","bool","bool","bool","bool","double","double","int","double","int","double","double","double","int","double","int","double","double","double","double","double","double","int","bool","bool","bool","double","double","double","double","string","int","int","bool","double","double","double","double","double","double","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","double","double","double","int","int","int","int","int","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(1653869333, "ALittle.LoopGroupInfo", {
name : "ALittle.LoopGroupInfo", ns_name : "ALittle", rl_name : "LoopGroupInfo", hash_code : 1653869333,
name_list : ["childs"],
type_list : ["List<ALittle.LoopListInfo>"],
option_map : {}
})
ALittle.RegStruct(-1741432339, "ALittle.LoopListInfo", {
name : "ALittle.LoopListInfo", ns_name : "ALittle", rl_name : "LoopListInfo", hash_code : -1741432339,
name_list : ["link","attribute","init","childs"],
type_list : ["string","string","any","List<ALittle.LoopChildInfo>"],
option_map : {}
})
ALittle.RegStruct(-925381158, "ALittle.LoopChildInfo", {
name : "ALittle.LoopChildInfo", ns_name : "ALittle", rl_name : "LoopChildInfo", hash_code : -925381158,
name_list : ["clazz","target","total_time","delay_time"],
type_list : ["string","any","int","int"],
option_map : {}
})
ALittle.RegStruct(-2110455927, "ALittle.EventInfo", {
name : "ALittle.EventInfo", ns_name : "ALittle", rl_name : "EventInfo", hash_code : -2110455927,
name_list : ["type","func"],
type_list : ["string","string"],
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

ALittleIDE.IDEControlManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._drag_effect = undefined;
		this._drag_shift = false;
		this._item_pool = [];
		this._item_pool_count = 0;
		this._item_used = [];
	},
	ControlInfoCmp : function(a, b) {
		return a.name < b.name;
	},
	HandleControlSearchClick : function(event) {
		this._control_scroll_screen.RemoveAllChild();
		let ___OBJECT_1 = this._item_used;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let item = ___OBJECT_1[k - 1];
			if (item === undefined) break;
			this._item_pool_count = this._item_pool_count + 1;
			this._item_pool[this._item_pool_count - 1] = item;
		}
		this._item_used = [];
		let item_used_count = 0;
		let project = ALittleIDE.g_IDEProject.project;
		if (project === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("提示", "当前没有打开的项目");
			return;
		}
		let key = this._control_search_key.text;
		let search_type = this._control_search_type.text;
		let control_info_list = [];
		let control_info_count = 0;
		let control_map = project.control_map;
		let ___OBJECT_2 = control_map;
		for (let control_name in ___OBJECT_2) {
			let control_info = ___OBJECT_2[control_name];
			if (control_info === undefined) continue;
			if (search_type === "控件名|描述") {
				if (key === "" || ALittle.String_Find(control_name, key) !== undefined || (control_info.info.description !== undefined && ALittle.String_Find(control_info.info.description, key) !== undefined)) {
					++ control_info_count;
					control_info_list[control_info_count - 1] = control_info;
				}
			} else if (search_type === "插件名") {
				if (ALittleIDE.IDEUtility_HasTargetClass(control_info.info, key)) {
					++ control_info_count;
					control_info_list[control_info_count - 1] = control_info;
				}
			} else if (search_type === "事件设置") {
				if (ALittleIDE.IDEUtility_HasEventCallback(control_info.info, key)) {
					++ control_info_count;
					control_info_list[control_info_count - 1] = control_info;
				}
			}
		}
		let tabname_map = ALittleIDE.g_IDETabManager.GetTabNameMap();
		let search_count = 0;
		let last_control_info = undefined;
		ALittle.List_Sort(control_info_list, ALittleIDE.IDEControlManager.ControlInfoCmp);
		let ___OBJECT_3 = control_info_list;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let control_info = ___OBJECT_3[index - 1];
			if (control_info === undefined) break;
			let item = undefined;
			if (this._item_pool_count > 0) {
				item = this._item_pool[this._item_pool_count - 1];
				this._item_pool_count = this._item_pool_count - 1;
			}
			if (item === undefined) {
				item = ALittleIDE.g_Control.CreateControl("ide_common_item_checkbutton");
				item.AddEventListener(___all_struct.get(-449066808), this, this.HandleControlItemClick);
				item.AddEventListener(___all_struct.get(-641444818), this, this.HandleControlItemRightClick);
				item.AddEventListener(___all_struct.get(544684311), this, this.HandleControlPreseeMoveIn);
				item.AddEventListener(___all_struct.get(-1202439334), this, this.HandleControlPreseeMoveOut);
				item.AddEventListener(___all_struct.get(-1604617962), this, this.HandleControlKeyDown);
				item.AddEventListener(___all_struct.get(1301789264), this, this.HandleControlDragBegin);
				item.AddEventListener(___all_struct.get(1337289812), this, this.HandleControlDrag);
				item.AddEventListener(___all_struct.get(150587926), this, this.HandleControlDragEnd);
			}
			++ item_used_count;
			this._item_used[item_used_count - 1] = item;
			if (control_info.info.description !== undefined && control_info.info.description !== "") {
				item.text = control_info.name + "(" + control_info.info.description + ")";
			} else {
				item.text = control_info.name;
			}
			item.selected = tabname_map[control_info.name] !== undefined;
			let user_data = {};
			item._user_data = user_data;
			user_data.presee = false;
			user_data.control_info = control_info;
			this._control_scroll_screen.AddChild(item);
			search_count = search_count + 1;
			last_control_info = control_info;
		}
		if (search_count === 1) {
			ALittleIDE.g_IDETabManager.StartEditControlBySelect(last_control_info.name, last_control_info.info);
		}
	},
	HandleControlItemClick : function(event) {
		let info = event.target._user_data;
		info.presee = false;
		event.target.selected = true;
		ALittleIDE.g_IDETabManager.StartEditControlBySelect(info.control_info.name, info.control_info.info);
	},
	HandleControlPreseeMoveIn : function(event) {
		let info = event.target._user_data;
		info.presee = true;
		if (ALittleIDE.g_IDETabManager.GetTabByName(info.control_info.name) !== undefined) {
			info.presee = false;
			return;
		}
		info.pre_index = ALittleIDE.g_IDETabManager.GetCurTabIndex();
		ALittleIDE.g_IDETabManager.StartEditControlBySelect(info.control_info.name, info.control_info.info);
	},
	HandleControlPreseeMoveOut : function(event) {
		let info = event.target._user_data;
		if (info.presee !== true) {
			return;
		}
		let child = ALittleIDE.g_IDETabManager.GetTabByName(info.control_info.name);
		if (child === undefined) {
			return;
		}
		ALittleIDE.g_IDETabManager.CloseTab(child);
		if (info.pre_index !== undefined) {
			ALittleIDE.g_IDETabManager.SetCurTabIndex(info.pre_index);
		}
	},
	HandleControlKeyDown : function(event) {
		if (event.sym === 1073741883) {
			this.ControlRenameImpl(event.target);
		}
	},
	HandleControlDragBegin : function(event) {
		this._drag_shift = (A_UISystem.sym_map.get(1073742049) !== undefined || A_UISystem.sym_map.get(1073742053) !== undefined);
		if (this._drag_shift === false) {
			event.target = this._control_scroll_screen;
			this._control_scroll_screen.DispatchEvent(___all_struct.get(1301789264), event);
			return;
		}
		let [x, y] = event.target.LocalToGlobal();
		this._drag_effect = ALittle.NewObject(ALittle.EffectImage, ALittleIDE.g_Control);
		this._drag_effect.Action(event.target);
		A_LayerManager.AddToTip(this._drag_effect);
		this._drag_effect.x = x;
		this._drag_effect.y = y;
		this._drag_effect.alpha = 0.6;
		let info = event.target._user_data;
		if (info.presee !== true) {
			return;
		}
		let child = ALittleIDE.g_IDETabManager.GetTabByName(info.control_info.name);
		if (child === undefined) {
			return;
		}
		ALittleIDE.g_IDETabManager.CloseTab(child);
		if (info.pre_index !== undefined) {
			ALittleIDE.g_IDETabManager.SetCurTabIndex(info.pre_index);
		}
	},
	HandleControlDrag : function(event) {
		if (this._drag_shift === false) {
			event.target = this._control_scroll_screen;
			this._control_scroll_screen.DispatchEvent(___all_struct.get(1337289812), event);
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
			event.target = this._control_scroll_screen;
			this._control_scroll_screen.DispatchEvent(___all_struct.get(150587926), event);
			return;
		}
		if (this._drag_effect !== undefined) {
			A_LayerManager.RemoveFromTip(this._drag_effect);
			this._drag_effect.Clear();
			this._drag_effect = undefined;
		}
		let tab_child = ALittleIDE.g_IDETabManager.cur_tab_child;
		let [x, y] = tab_child.tree_object.LocalToGlobal();
		let delta_x = event.abs_x - x;
		let delta_y = event.abs_y - y;
		let [target] = tab_child.tree_object.PickUp(delta_x, delta_y);
		if (target === undefined) {
			ALittle.Log("IDETreeLogic:HandleDrag} target null");
			return;
		}
		let tree = target._user_data;
		let user_data = event.target._user_data;
		let save_info = {};
		save_info["__extends"] = user_data.control_info.name;
		let copy_list = [];
		let info = {};
		info["index"] = 1;
		info["info"] = save_info;
		copy_list[1 - 1] = info;
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list));
		if (tree.IsTree()) {
			tab_child.RightControlTreePasteImpl(tree, undefined, 1);
		} else {
			let common_parent = tree.logic_parent;
			if (common_parent === undefined) {
				ALittleIDE.g_IDETool.ShowNotice("提示", "当前是根节点，并且不是容器，粘帖失败");
				return;
			}
			let child_index = common_parent.GetChildIndex(tree);
			[x, y] = target.LocalToGlobal();
			y = y + target.height / 2;
			if (event.abs_y > y) {
				child_index = child_index + 1;
			}
			tab_child.RightControlTreePasteImpl(common_parent, undefined, child_index);
		}
	},
	ClearControlItem : function() {
		this._control_scroll_screen.RemoveAllChild();
	},
	ShowNewControl : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("提示", "当前没有打开的项目");
			return;
		}
		if (this._control_new_dialog === undefined) {
			this._control_new_dialog = ALittleIDE.g_Control.CreateControl("ide_new_control_dialog", this);
			A_LayerManager.AddToModal(this._control_new_dialog);
			this._control_new_type.data_list = ALittleIDE.g_IDEEnum.child_type_list;
		}
		this._control_new_name.text = "";
		this._control_new_extends_name.text = "";
		this._control_new_dialog.visible = true;
		A_UISystem.focus = this._control_new_name.show_input;
	},
	HandleNewControlCancel : function(event) {
		this._control_new_dialog.visible = false;
	},
	HandleNewControlConfirm : function(event) {
		let project = ALittleIDE.g_IDEProject.project;
		if (project === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "当前没有打开的项目");
			return;
		}
		let name = this._control_new_name.text;
		if (name === "") {
			ALittleIDE.g_IDETool.ShowNotice("错误", "请输入控件名");
			return;
		}
		if (ALittleIDE.IDEUtility_CheckName(name) === false) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "控件名不合法:" + name);
			return;
		}
		if (project.control_map[name] !== undefined) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "控件已存在:" + name);
			return;
		}
		if (ALittleIDE.g_IDETabManager.GetTabByName(name) !== undefined) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "控件名已存在:" + name);
			return;
		}
		let control_type = this._control_new_type.text;
		if (control_type === "") {
			ALittleIDE.g_IDETool.ShowNotice("错误", "请选择控件类型");
			return;
		}
		let extends_name = this._control_new_extends_name.text;
		if (extends_name !== "") {
			ALittleIDE.g_IDETabManager.StartEditControlByExtends(name, extends_name);
		} else {
			ALittleIDE.g_IDETabManager.StartEditControlByNew(name, control_type);
		}
		this._control_new_dialog.visible = false;
	},
	HandleControlItemRightClick : function(event) {
		if (this._control_right_menu === undefined) {
			this._control_right_menu = ALittleIDE.g_Control.CreateControl("ide_control_right_menu", this);
		}
		A_LayerManager.ShowFromRight(this._control_right_menu);
		this._control_right_menu.x = A_UISystem.mouse_x;
		this._control_right_menu.y = A_UISystem.mouse_y;
		if (this._control_right_menu.x + this._control_right_menu.width > A_UISystem.view_width) {
			this._control_right_menu.x = A_UISystem.view_width - this._control_right_menu.width;
		}
		if (this._control_right_menu.y + this._control_right_menu.height > A_UISystem.view_height) {
			this._control_right_menu.y = A_UISystem.view_height - this._control_right_menu.height;
		}
		this._control_right_menu._user_data = event.target;
	},
	DeleteControlImpl : function(target) {
		this._control_scroll_screen.RemoveChild(target);
		let user_data = target._user_data;
		let [result, content] = ALittleIDE.g_IDEProject.DeleteControl(user_data.control_info.name);
		if (result === false) {
			ALittleIDE.g_IDETool.ShowNotice("提示", content);
			return;
		}
		let tab = ALittleIDE.g_IDETabManager.GetTabByName(user_data.control_info.name);
		if (tab === undefined) {
			return;
		}
		ALittleIDE.g_IDETabManager.CloseTab(tab);
	},
	HandleControlRightMenuDelete : function(event) {
		A_LayerManager.HideFromRight(this._control_right_menu);
		let target = this._control_right_menu._user_data;
		this._control_right_menu._user_data = undefined;
		let user_data = target._user_data;
		let name = user_data.control_info.name;
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
		let callback = this.DeleteControlImpl.bind(this, target);
		ALittleIDE.g_IDETool.DeleteNotice("提示", "确定要删除" + target.text + "吗?", callback);
	},
	HandleControlRightMenuCopyName : function(event) {
		A_LayerManager.HideFromRight(this._control_right_menu);
		let target = this._control_right_menu._user_data;
		this._control_right_menu._user_data = undefined;
		let user_data = target._user_data;
		let name = user_data.control_info.name;
		ALittle.System_SetClipboardText(name);
	},
	HandleControlRightMenuCopyInfo : function(event) {
		A_LayerManager.HideFromRight(this._control_right_menu);
		let target = this._control_right_menu._user_data;
		this._control_right_menu._user_data = undefined;
		let user_data = target._user_data;
		let name = user_data.control_info.name;
		let [x, y] = target.LocalToGlobal();
		let callback = this.ControlCopyInfo.bind(this, name);
		ALittleIDE.g_IDETool.ShowRename(callback, name, x, y, target.width);
	},
	ControlCopyInfo : function(target_name, new_name) {
		let [result, content] = ALittleIDE.IDEUtility_CheckName(new_name);
		if (result === false) {
			ALittleIDE.g_IDETool.ShowNotice("错误", content);
			return;
		}
		let info = ALittleIDE.g_IDEProject.project.control_map[new_name];
		if (info !== undefined) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "控件名已存在:" + new_name);
			return;
		}
		info = ALittleIDE.g_IDEProject.project.control_map[target_name];
		if (info === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "控件不存在:" + target_name);
			return;
		}
		ALittleIDE.g_IDEProject.SaveControl(new_name, ALittle.String_CopyTable(info.info));
		info = ALittleIDE.g_IDEProject.project.control_map[new_name];
		if (info === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "控件新建失败:" + new_name);
			return;
		}
		ALittleIDE.g_IDETabManager.StartEditControlBySelect(new_name, info.info);
	},
	ControlRename : function(target, old_name, new_name) {
		if (old_name === new_name) {
			return;
		}
		let [result, content] = ALittleIDE.g_IDEProject.RenameControl(old_name, new_name);
		if (result === false) {
			ALittleIDE.g_IDETool.ShowNotice("错误", content);
			return;
		}
		target.text = new_name;
		let tab = ALittleIDE.g_IDETabManager.GetTabByName(old_name);
		if (tab === undefined) {
			return;
		}
		let tab_child = tab._user_data;
		tab_child.Rename(new_name);
	},
	ControlRenameImpl : function(target) {
		let user_data = target._user_data;
		let name = user_data.control_info.name;
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
		let [x, y] = target.LocalToGlobal();
		let callback = this.ControlRename.bind(this, target, name);
		ALittleIDE.g_IDETool.ShowRename(callback, name, x, y, target.width);
	},
	HandleControlRightMenuRename : function(event) {
		A_LayerManager.HideFromRight(this._control_right_menu);
		let target = this._control_right_menu._user_data;
		this._control_right_menu._user_data = undefined;
		this.ControlRenameImpl(target);
	},
	HandleControlRightMenuCopyExtends : function(event) {
		A_LayerManager.HideFromRight(this._control_right_menu);
		let target = this._control_right_menu._user_data;
		this._control_right_menu._user_data = undefined;
		let user_data = target._user_data;
		let name = user_data.control_info.name;
		let save_info = {};
		save_info["__extends"] = name;
		let copy_list = [];
		let info = {};
		info["index"] = 1;
		info["info"] = save_info;
		copy_list[1 - 1] = info;
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list));
	},
	ControlRunImpl : function(name) {
		let debug = {};
		debug["title"] = name;
		debug["window_width"] = ALittleIDE.g_IDEProject.project.config.GetConfig("default_show_width", 800);
		debug["window_height"] = ALittleIDE.g_IDEProject.project.config.GetConfig("default_show_height", 600);
		debug["ui_name"] = name;
		debug["module_name"] = ALittleIDE.g_IDEProject.project.name;
		let debug_str = ALittle.String_JsonEncode(debug);
		debug_str = "\"" + ALittle.String_Replace(debug_str, "\"", "\\\"") + "\"";
		lua.os.execute("start ALittleClientWin.exe Module/ALittleIDE/Script/ " + debug_str + " " + ALittleIDE.g_IDEProject.project.name + " Engine/MainTemplate/UIViewer");
	},
	HandleControlRightMenuRun : function(event) {
		A_LayerManager.HideFromRight(this._control_right_menu);
		let target = this._control_right_menu._user_data;
		this._control_right_menu._user_data = undefined;
		let user_data = target._user_data;
		ALittleIDE.g_IDETool.ShowAlertDialog("提示", "JavaScript不支持运行");
	},
	HandleControlRightMenuFlagQuickImage : function(event) {
		A_LayerManager.HideFromRight(this._control_right_menu);
		let target = this._control_right_menu._user_data;
		this._control_right_menu._user_data = undefined;
		let user_data = target._user_data;
		ALittleIDE.g_IDEQuickManager.FlagImage(user_data.control_info.name);
	},
	HandleControlRightMenuFlagQuickButton : function(event) {
		A_LayerManager.HideFromRight(this._control_right_menu);
		let target = this._control_right_menu._user_data;
		this._control_right_menu._user_data = undefined;
		let user_data = target._user_data;
		ALittleIDE.g_IDEQuickManager.FlagButton(user_data.control_info.name);
	},
	HandleControlRightMenuFlagQuickText : function(event) {
		A_LayerManager.HideFromRight(this._control_right_menu);
		let target = this._control_right_menu._user_data;
		this._control_right_menu._user_data = undefined;
		let user_data = target._user_data;
		ALittleIDE.g_IDEQuickManager.FlagText(user_data.control_info.name);
	},
	HandleControlRightMenuFlagQuickOther : function(event) {
		A_LayerManager.HideFromRight(this._control_right_menu);
		let target = this._control_right_menu._user_data;
		this._control_right_menu._user_data = undefined;
		let user_data = target._user_data;
		ALittleIDE.g_IDEQuickManager.FlagOther(user_data.control_info.name);
	},
}, "ALittleIDE.IDEControlManager");

ALittleIDE.g_IDEControlManager = ALittle.NewObject(ALittleIDE.IDEControlManager);
}