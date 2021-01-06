{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};

ALittle.RegStruct(-2110455927, "ALittle.EventInfo", {
name : "ALittle.EventInfo", ns_name : "ALittle", rl_name : "EventInfo", hash_code : -2110455927,
name_list : ["type","func"],
type_list : ["string","string"],
option_map : {}
})
ALittle.RegStruct(-1741432339, "ALittle.LoopListInfo", {
name : "ALittle.LoopListInfo", ns_name : "ALittle", rl_name : "LoopListInfo", hash_code : -1741432339,
name_list : ["link","attribute","init","childs"],
type_list : ["string","string","any","List<ALittle.LoopChildInfo>"],
option_map : {}
})
ALittle.RegStruct(1653869333, "ALittle.LoopGroupInfo", {
name : "ALittle.LoopGroupInfo", ns_name : "ALittle", rl_name : "LoopGroupInfo", hash_code : 1653869333,
name_list : ["childs"],
type_list : ["List<ALittle.LoopListInfo>"],
option_map : {}
})
ALittle.RegStruct(1025287370, "ALittleIDE.IDEPasteControlUserData", {
name : "ALittleIDE.IDEPasteControlUserData", ns_name : "ALittleIDE", rl_name : "IDEPasteControlUserData", hash_code : 1025287370,
name_list : ["target","info","child_index","revoke_bind","callback"],
type_list : ["ALittleIDE.IDEUITreeLogic","ALittle.DisplayInfo","int","ALittle.RevokeBind","Functor<(bool,List<ALittleIDE.IDEUITreeLogic>)>"],
option_map : {}
})
ALittle.RegStruct(-925381158, "ALittle.LoopChildInfo", {
name : "ALittle.LoopChildInfo", ns_name : "ALittle", rl_name : "LoopChildInfo", hash_code : -925381158,
name_list : ["clazz","target","total_time","delay_time"],
type_list : ["string","any","int","int"],
option_map : {}
})
ALittle.RegStruct(-4982446, "ALittle.DisplayInfo", {
name : "ALittle.DisplayInfo", ns_name : "ALittle", rl_name : "DisplayInfo", hash_code : -4982446,
name_list : ["__target_class","__class_func","__base_attr","__show_attr","loop_map","__module","__class","__include","__extends","__childs","__event","__link","__shows_included","__childs_included","__extends_included","description","text","font_path","font_size","red","green","blue","alpha","bold","italic","underline","deleteline","x","y","x_type","x_value","y_type","y_value","width","height","width_type","width_value","height_type","height_value","scale_x","scale_y","center_x","center_y","angle","flip","hand_cursor","visible","disabled","left_size","right_size","top_size","bottom_size","texture_name","interval","play_loop_count","var_play","base_y","head_size","gap","up_size","down_size","cursor_red","cursor_green","cursor_blue","default_text_alpha","ims_padding","margin_left","margin_right","margin_top","margin_bottom","show_count","body_margin","screen_margin_left","screen_margin_right","screen_margin_top","screen_margin_bottom","start_degree","end_degree","line_spacing","max_line_count","font_red","font_green","font_blue","margin_halign","margin_valign","cursor_margin_up","cursor_margin_down","total_size","show_size","offset_rate","offset_step","grade","row_count","col_count","row_index","col_index","u1","v1","u2","v2","u3","v3","x1","y1","x2","y2","x3","y3","x_gap","y_gap","x_start_gap","y_start_gap","button_gap","button_start","button_margin","tab_index","view_margin","child_width_margin"],
type_list : ["List<string>","any","Map<string,any>","Map<string,ALittle.DisplayInfo>","Map<string,ALittle.LoopGroupInfo>","string","string","string","string","List<ALittle.DisplayInfo>","List<ALittle.EventInfo>","string","bool","bool","bool","string","string","string","int","double","double","double","double","bool","bool","bool","bool","double","double","int","double","int","double","double","double","int","double","int","double","double","double","double","double","double","int","bool","bool","bool","double","double","double","double","string","int","int","bool","double","double","double","double","double","double","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","double","double","double","int","int","int","int","int","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEUIControlTree = JavaScript.Class(ALittle.DisplayLayout, {
	HandleControlTreeItemRightClick : function(event) {
		let target = event.target._user_data;
		if (target.user_info.extends) {
			return;
		}
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("设置", this.ShowSettingDialog.bind(this, target));
		menu.AddItem("上移", target.TransferUp.bind(target), target.user_info.root || target.user_info.child_type !== "child", false);
		menu.AddItem("下移", target.TransferDown.bind(target), target.user_info.root || target.user_info.child_type !== "child", false);
		menu.AddItem("添加", this.ShowAddDialog.bind(this, target), !target.is_tree);
		menu.AddItem("添加Image", this.ShowAddImageDialog.bind(this, target), !target.is_tree);
		menu.AddItem("添加Text", this.ShowAddTextDialog.bind(this, target), !target.is_tree);
		menu.AddItem("复制", target.CopyToClipboard.bind(target));
		menu.AddItem("粘贴", target.PasteFromClipboard.bind(target));
		menu.AddItem("剪切", target.CutToClipboard.bind(target), target.user_info.root);
		menu.AddItem("删除", target.TreeDelete.bind(target, undefined), target.user_info.root);
		menu.AddItem("跳转", this.ControlTreeJump.bind(this, target), !target.user_info.extends_root);
		menu.AddItem("描述", this.ControlTreeDesc.bind(this, target));
		menu.Show();
	},
	ShowSettingDialog : function(item) {
		item.ShowFocus(false);
		ALittleIDE.g_IDEAttrControlDialog.ShowDialog(item.user_info.object);
	},
	ShowAddImageDialog : async function(target) {
		let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(target.user_info.module);
		if (ui_manager === undefined) {
			g_AUITool.ShowNotice("错误", "模块不存在:" + target.user_info.module);
			return;
		}
		ALittleIDE.g_IDEImageSelectDialog.SetBasePath(ui_manager.texture_path);
		let path = await ALittleIDE.g_IDEImageSelectDialog.ShowSelect();
		if (path === undefined) {
			return;
		}
		if (target.CanAddChild() === false) {
			g_AUITool.ShowNotice("提示", "当前控件不能添加子控件");
			return;
		}
		let tree_object = target.TreeAdd(undefined, "", "Image", "child");
		if (tree_object === undefined) {
			g_AUITool.ShowNotice("提示", "添加失败");
			return;
		}
		tree_object.attr_panel.SetTextureName(path, undefined);
		tree_object.ShowFocus(false);
	},
	ShowAddTextDialog : function(target) {
		if (target.CanAddChild() === false) {
			g_AUITool.ShowNotice("提示", "当前控件不能添加子控件");
			return;
		}
		let tree_object = target.TreeAdd(undefined, "", "Text", "child");
		if (tree_object === undefined) {
			g_AUITool.ShowNotice("提示", "添加失败");
			return;
		}
		tree_object.ShowFocus(false);
	},
	ShowAddDialog : function(target) {
		if (this._control_add_dialog === undefined) {
			this._control_add_dialog = ALittleIDE.g_Control.CreateControl("ide_add_control_dialog", this);
			this._control_add_new_type.data_list = ALittleIDE.g_IDEEnum.child_type_list;
			A_LayerManager.AddToModal(this._control_add_dialog);
			this._control_add_dialog.visible = false;
		}
		let data_list = target.GetDataListForAdd();
		if (ALittle.List_Len(data_list) === 0) {
			g_AUITool.ShowNotice("提示", "当前控件不能添加子控件");
			return;
		}
		this._control_add_dialog._user_data = target;
		this._control_add_type.data_list = data_list;
		this._control_add_dialog.visible = true;
	},
	HandleAddControlCancel : function(event) {
		this._control_add_dialog.visible = false;
		this._control_add_dialog._user_data = undefined;
	},
	HandleAddControlConfirm : function(event) {
		let target = this._control_add_dialog._user_data;
		this._control_add_dialog._user_data = undefined;
		this._control_add_dialog.visible = false;
		let child_type = this._control_add_type.text;
		let class_name = this._control_add_new_type.text;
		let tree_object = target.TreeAdd(undefined, "", class_name, child_type);
		if (tree_object !== undefined) {
			tree_object.ShowFocus(false);
		}
	},
	ShowPasteDialog : function(target, info, child_index, revoke_bind, callback) {
		let data_list = target.GetDataListForAdd();
		if (ALittle.List_Len(data_list) === 0) {
			g_AUITool.ShowNotice("提示", "当前控件不能添加子控件");
			if (callback !== undefined) {
				callback(false, undefined);
			}
			return;
		}
		if (this._paste_control_dialog === undefined) {
			this._paste_control_dialog = ALittleIDE.g_Control.CreateControl("ide_paste_control_dialog", this);
			A_LayerManager.AddToModal(this._paste_control_dialog);
		}
		this._paste_control_dialog.visible = true;
		this._control_paste_type.data_list = data_list;
		let user_data = {};
		this._paste_control_dialog._user_data = user_data;
		user_data.target = target;
		user_data.info = info;
		user_data.child_index = child_index;
		user_data.revoke_bind = revoke_bind;
		user_data.callback = callback;
	},
	HandlePasteControlCancel : function(event) {
		this._paste_control_dialog.visible = false;
		let user_data = this._paste_control_dialog._user_data;
		let callback = user_data.callback;
		if (callback !== undefined) {
			callback(false, undefined);
		}
		this._paste_control_dialog._user_data = undefined;
	},
	HandlePasteControlConfirm : function(event) {
		this._paste_control_dialog.visible = false;
		let user_data = this._paste_control_dialog._user_data;
		this._paste_control_dialog._user_data = undefined;
		user_data.target.tab_child.ClearHandQuad();
		let add_list = [];
		let child_index = undefined;
		if (user_data.child_index !== undefined) {
			child_index = user_data.child_index + 1;
		}
		let tree_object = user_data.target.TreePaste(user_data.info, this._control_paste_type.text, child_index, false, user_data.revoke_bind);
		add_list[1 - 1] = tree_object;
		if (user_data.callback !== undefined) {
			user_data.callback(true, add_list);
		}
	},
	ControlTreeJump : function(target) {
		let extends_module = target.user_info.base.__module;
		if (extends_module === undefined) {
			extends_module = target.user_info.module;
		}
		let extends_name = target.user_info.base.__extends;
		let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(extends_module);
		if (ui_manager === undefined) {
			g_AUITool.ShowNotice("错误", "模块不存在:" + extends_module);
			return;
		}
		let control_info = ui_manager.control_map[extends_name];
		if (control_info === undefined) {
			g_AUITool.ShowNotice("错误", "控件不存在:" + extends_name);
			return;
		}
		ALittleIDE.g_IDECenter.center.content_edit.StartEditControlBySelect(extends_module, extends_name);
	},
	ControlTreeDesc : async function(target) {
		let [x, y] = target.LocalToGlobal();
		let desc = target.GetDesc();
		let name = await g_AUITool.ShowRename(desc, x, y, target.width);
		if (name === undefined) {
			return;
		}
		target.SetDesc(name);
	},
	HandleTreeSearchClick : function(event) {
		let tab = ALittleIDE.g_IDECenter.center.content_edit.cur_tab;
		if (tab === undefined) {
			return;
		}
		let tab_child = tab._user_data;
		let search_key = this._tree_search_key.text;
		let search_type = this._tree_search_type.text;
		if (search_type === "描述") {
			tab_child.SearchDescription(search_key);
		} else if (search_type === "绑定设置") {
			tab_child.SearchLink(search_key);
		} else if (search_type === "事件设置") {
			tab_child.SearchEvent(search_key);
		} else if (search_type === "插件名") {
			tab_child.SearchTargetClass(search_key);
		} else if (search_type === "图片路径") {
			tab_child.SearchTextureName(search_key);
		}
	},
}, "ALittleIDE.IDEUIControlTree");

}