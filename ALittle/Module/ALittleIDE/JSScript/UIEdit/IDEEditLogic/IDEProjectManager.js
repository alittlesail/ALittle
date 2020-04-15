{
if (typeof ALittleIDE === "undefined") ALittleIDE = {};
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

ALittleIDE.IDEProjectManager = JavaScript.Class(undefined, {
	OpenLastProject : function() {
		if (ALittleIDE.g_IDEProject.project !== undefined) {
			return;
		}
		let project_name = ALittleIDE.g_IDEConfig.GetConfig("last_project", "");
		if (project_name === "") {
			return;
		}
		this.OpenProjectImpl(project_name);
	},
	HandleProjectSearchClick : function(event) {
		this._project_scroll_screen.RemoveAllChild();
		let key = this._project_search_key.text;
		let project_map = ALittleIDE.g_IDEConfig.GetConfig("project_map", {});
		let ___OBJECT_1 = project_map;
		for (let k in ___OBJECT_1) {
			let v = ___OBJECT_1[k];
			if (v === undefined) continue;
			if (key === "" || ALittle.String_Find(v, key) !== undefined) {
				let item = ALittleIDE.g_Control.CreateControl("ide_common_item_button");
				item.text = v;
				item.drag_trans_target = this._project_scroll_screen;
				item.AddEventListener(___all_struct.get(-641444818), this, this.HandleProjectItemRightClick);
				this._project_scroll_screen.AddChild(item);
			}
		}
	},
	ShowNewProject : function() {
		if (this._project_new_dialog === undefined) {
			this._project_new_dialog = ALittleIDE.g_Control.CreateControl("ide_new_project_dialog", this);
			A_LayerManager.AddToModal(this._project_new_dialog);
		}
		this._project_new_name.text = "";
		this._project_new_dialog.visible = true;
		A_UISystem.focus = this._project_new_name.show_input;
	},
	HandleNewProjectCancel : function(event) {
		this._project_new_dialog.visible = false;
	},
	HandleNewProjectConfirm : function(event) {
		let name = this._project_new_name.text;
		if (name === "") {
			ALittleIDE.g_IDETool.ShowNotice("错误", "请输入项目名");
			return;
		}
		if (ALittleIDE.IDEUtility_CheckName(name) === false) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "项目名不合法:" + name);
			return;
		}
		if (ALittle.File_GetFileAttr(ALittle.File_BaseFilePath() + name) !== undefined) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "项目已存在:" + name);
			return;
		}
		let size_list = ALittle.String_Split(this._view_size_dropdown.text, "x");
		let window_width = ALittle.Math_ToInt(size_list[1 - 1]);
		if (window_width === undefined) {
			window_width = 800;
		}
		let window_height = ALittle.Math_ToInt(size_list[2 - 1]);
		if (window_height === undefined) {
			window_height = 600;
		}
		let font_path = this._default_font_path.text;
		let font_size = ALittle.Math_ToInt(this._default_font_size.text);
		if (font_size === undefined) {
			font_size = 25;
		}
		ALittleIDE.g_IDEProject.NewProject(name, ALittle.Math_Floor(window_width), ALittle.Math_Floor(window_height), font_path, ALittle.Math_Floor(font_size));
		ALittleIDE.g_IDECenter.UpdateProjectList();
		if (ALittleIDE.g_IDEProject.project === undefined) {
			ALittleIDE.g_IDECenter.OpenProject(name);
		}
		this._project_new_dialog.visible = false;
	},
	OpenProjectImpl : function(name) {
		if (name === "") {
			ALittleIDE.g_IDETool.ShowNotice("错误", "请输入项目名");
			return;
		}
		if (ALittle.File_GetFileAttr(ALittle.File_BaseFilePath() + "Module/" + name) === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "项目不存在:" + name);
			return;
		}
		ALittleIDE.g_IDECenter.CloseProject();
		ALittleIDE.g_IDECenter.OpenProject(name);
	},
	ShowOpenProject : function() {
		if (this._project_open_dialog === undefined) {
			this._project_open_dialog = ALittleIDE.g_Control.CreateControl("ide_open_project_dialog", this);
			A_LayerManager.AddToModal(this._project_open_dialog);
		}
		this._project_open_name.text = "";
		this._project_open_dialog.visible = true;
		A_UISystem.focus = this._project_open_name.show_input;
	},
	HandleOpenProjectCancel : function(event) {
		this._project_open_dialog.visible = false;
	},
	HandleOpenProjectConfirm : function(event) {
		this._project_open_dialog.visible = false;
		let name = this._project_open_name.text;
		if (ALittleIDE.g_IDETabManager.IsSaveAll()) {
			this.OpenProjectImpl(name);
			return;
		}
		let cancel_callback = this.OpenProjectImpl.bind(this, name);
		let confirm_callback = ALittleIDE.g_IDETabManager.SaveAllTab.bind(ALittleIDE.g_IDETabManager);
		ALittleIDE.g_IDETool.SaveNotice("提示", "是否保存当前项目?", cancel_callback, confirm_callback);
	},
	ShowSettingProject : function(event) {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "当前没有打开的项目");
			return;
		}
		if (this._project_setting_dialog === undefined) {
			this._project_setting_dialog = ALittleIDE.g_Control.CreateControl("ide_setting_project_dialog", this);
			A_LayerManager.AddToModal(this._project_setting_dialog);
		}
		this._project_setting_dialog.visible = true;
		this._default_show_width.text = ALittleIDE.g_IDEProject.project.config.GetConfig("default_show_width", 800);
		this._default_show_height.text = ALittleIDE.g_IDEProject.project.config.GetConfig("default_show_height", 600);
		this._default_font_path.text = ALittleIDE.g_IDEProject.project.config.GetConfig("default_font_path", "");
		this._default_font_size.text = ALittleIDE.g_IDEProject.project.config.GetConfig("default_font_size", 15);
		this._core_path_input.text = "Module/ALittleIDE/Other/Server/Core/";
		this._modules_edit.text = "Module/ALittleIDE/Other/Server/GatewayServer/\n" + "Module/ALittleIDE/Other/Server/VersionServer/";
	},
	HandleSettingProjectCancel : function(event) {
		this._project_setting_dialog.visible = false;
	},
	HandleSettingProjectConfirm : function(event) {
		let default_show_width = ALittle.Math_ToInt(this._default_show_width.text);
		if (default_show_width === undefined || default_show_width <= 0) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "默认宽度不合法");
			return;
		}
		let default_show_height = ALittle.Math_ToInt(this._default_show_height.text);
		if (default_show_height === undefined || default_show_height <= 0) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "默认高度不合法");
			return;
		}
		let default_font_path = this._default_font_path.text;
		let default_font_size = ALittle.Math_ToInt(this._default_font_size.text);
		if (default_font_size === undefined || default_font_size <= 0) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "默认字体大小不合法");
			return;
		}
		let core_path = this._core_path_input.text;
		if (core_path !== "" && ALittle.File_GetFileAttr(core_path) === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "服务端引擎路径不存在");
			return;
		}
		let modules = this._modules_edit.text;
		if (core_path !== "") {
			let module_split = ALittle.String_SplitSepList(modules, ["\n", "\r"]);
			let ___OBJECT_2 = module_split;
			for (let index = 1; index <= ___OBJECT_2.length; ++index) {
				let module = ___OBJECT_2[index - 1];
				if (module === undefined) break;
				let split = ALittle.String_Split(module, ",");
				if (ALittle.List_MaxN(split) !== 2) {
					ALittleIDE.g_IDETool.ShowNotice("错误", "服务端模块格式错误:" + module);
					return;
				}
				if (ALittle.File_GetFileAttr(split[1 - 1]) === undefined) {
					ALittleIDE.g_IDETool.ShowNotice("错误", "服务端模块路径不存在:" + split[1 - 1]);
					return;
				}
			}
		}
		ALittleIDE.g_IDEProject.project.config.SetConfig("default_show_width", default_show_width);
		ALittleIDE.g_IDEProject.project.config.SetConfig("default_show_height", default_show_height);
		ALittleIDE.g_IDEProject.project.config.SetConfig("default_font_path", default_font_path);
		ALittleIDE.g_IDEProject.project.config.SetConfig("default_font_size", default_font_size);
		ALittleIDE.g_IDEProject.project.config.SetConfig("core_path", core_path);
		ALittleIDE.g_IDEProject.project.config.SetConfig("modules", modules);
		ALittleIDE.g_IDETabManager.SetTabChildWH(default_show_width, default_show_height);
		this._project_setting_dialog.visible = false;
	},
	HandleProjectItemRightClick : function(event) {
		if (this._project_search_menu === undefined) {
			this._project_search_menu = ALittleIDE.g_Control.CreateControl("ide_search_project_menu", this);
		}
		this._project_search_menu.x = A_UISystem.mouse_x;
		this._project_search_menu.y = A_UISystem.mouse_y;
		if (this._project_search_menu.y + this._project_search_menu.height > A_UISystem.view_height) {
			this._project_search_menu.y = A_UISystem.view_height - this._project_search_menu.height;
		}
		this._project_search_menu._user_data = event.target;
		A_LayerManager.ShowFromRight(this._project_search_menu);
	},
	HandleRightProjectOpen : function(event) {
		A_LayerManager.HideFromRight(this._project_search_menu);
		let target = this._project_search_menu._user_data;
		this._project_search_menu._user_data = undefined;
		let project_name = target.text;
		if (ALittleIDE.g_IDETabManager.IsSaveAll()) {
			this.OpenProjectImpl(project_name);
			return;
		}
		let cancel_callback = this.OpenProjectImpl.bind(this, project_name);
		let confirm_callback = ALittleIDE.g_IDETabManager.SaveAllTab.bind(ALittleIDE.g_IDETabManager);
		ALittleIDE.g_IDETool.SaveNotice("提示", "是否保存当前项目?", cancel_callback, confirm_callback);
	},
	HandleRightProjectRemove : function(event) {
		A_LayerManager.HideFromRight(this._project_search_menu);
		let target = this._project_search_menu._user_data;
		this._project_search_menu._user_data = undefined;
		let project_name = target.text;
		if (ALittleIDE.g_IDEProject.project !== undefined && ALittleIDE.g_IDEProject.project.name === project_name) {
			ALittleIDE.g_IDETool.ShowNotice("提示", "当前项目正在编辑，请先关闭");
			return;
		}
		ALittleIDE.g_IDEProject.RemoveProject(project_name);
		this._project_scroll_screen.RemoveChild(target);
		ALittleIDE.g_IDECenter.UpdateProjectList();
	},
	HandleRightProjectClose : function(event) {
		A_LayerManager.HideFromRight(this._project_search_menu);
		let target = this._project_search_menu._user_data;
		this._project_search_menu._user_data = undefined;
		let project_name = target.text;
		if (ALittleIDE.g_IDEProject.project === undefined || ALittleIDE.g_IDEProject.project.name !== project_name) {
			return;
		}
		if (ALittleIDE.g_IDETabManager.IsSaveAll()) {
			ALittleIDE.g_IDECenter.CloseProject();
			return;
		}
		let cancel_callback = ALittleIDE.g_IDECenter.CloseProject.bind(ALittleIDE.g_IDECenter);
		let confirm_callback = ALittleIDE.g_IDETabManager.SaveAllTab.bind(ALittleIDE.g_IDETabManager);
		ALittleIDE.g_IDETool.SaveNotice("提示", "是否保存当前项目?", cancel_callback, confirm_callback);
	},
	RefreshProject : function() {
		if (ALittleIDE.g_IDETabManager.IsSaveAll()) {
			ALittleIDE.g_IDECenter.RefreshProject();
			return;
		}
		let cancel_callback = ALittleIDE.g_IDECenter.RefreshProject.bind(ALittleIDE.g_IDECenter);
		let confirm_callback = ALittleIDE.g_IDETabManager.SaveAllTab.bind(ALittleIDE.g_IDETabManager);
		ALittleIDE.g_IDETool.SaveNotice("提示", "是否保存当前项目?", cancel_callback, confirm_callback);
	},
	HandleRightProjectRefresh : function(event) {
		A_LayerManager.HideFromRight(this._project_search_menu);
		let target = this._project_search_menu._user_data;
		this._project_search_menu._user_data = undefined;
		let project_name = target.text;
		if (ALittleIDE.g_IDEProject.project === undefined || ALittleIDE.g_IDEProject.project.name !== project_name) {
			return;
		}
		this.RefreshProject();
	},
	ShowExportProject : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("错误", "当前没有打开的项目");
			return;
		}
		if (this._export_dialog === undefined) {
			this._export_dialog = ALittleIDE.g_Control.CreateControl("ide_export_dialog", this);
			ALittleIDE.g_IDECenter.dialog_layer.AddChild(this._export_dialog);
			this._main_export_tab.DisableAllCloseButton();
			this._main_export_tab.tab_index = 1;
			this._export_windows_official.config_key = "export_windows_official";
			this._export_android_official.config_key = "export_android_official";
			this._export_ios_official.config_key = "export_ios_official";
		}
		this._export_dialog.visible = true;
		this._export_windows_official.LoadConfigImpl();
		this._export_android_official.LoadConfigImpl();
		this._export_ios_official.LoadConfigImpl();
	},
	RunProject : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("提示", "当前没有打开的项目");
			return;
		}
		ALittleIDE.g_IDETool.ShowAlertDialog("提示", "JavaScript不支持运行项目");
	},
}, "ALittleIDE.IDEProjectManager");

ALittleIDE.g_IDEProjectManager = ALittle.NewObject(ALittleIDE.IDEProjectManager);
}