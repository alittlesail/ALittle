{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.IDECenter = JavaScript.Class(undefined, {
	Ctor : function() {
	},
	get main_layer() {
		return this._main_layer;
	},
	get dialog_layer() {
		return this._dialog_layer;
	},
	Setup : function() {
		return new Promise((async function(___COROUTINE, ___) {
			await Require(ALittleIDE.g_ScriptBasePath, "IDEProject");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEUICenter");
			ALittleIDE.g_IDEConfig = ALittle.CreateConfigSystem("ALittleIDE.cfg");
			ALittle.Math_RandomSeed(ALittle.Time_GetCurTime());
			ALittle.System_SetThreadCount(5);
			let background_quad = ALittle.NewObject(ALittle.Quad, ALittleIDE.g_Control);
			background_quad.height_type = 4;
			background_quad.width_type = 4;
			background_quad.alpha = 0.8;
			ALittleIDE.g_LayerGroup.AddChild(background_quad);
			this._phone_status_quad = background_quad;
			this._main_layer = ALittle.NewObject(ALittle.DisplayLayout, ALittleIDE.g_Control);
			this._main_layer.width_type = 4;
			this._main_layer.height_type = 4;
			ALittleIDE.g_LayerGroup.AddChild(this._main_layer);
			this._dialog_layer = ALittle.NewObject(ALittle.DisplayLayout, ALittleIDE.g_Control);
			this._dialog_layer.width_type = 4;
			this._dialog_layer.height_type = 4;
			ALittleIDE.g_LayerGroup.AddChild(this._dialog_layer);
			this.ShowPhoneStatusLine(106, 106, 106);
			ALittleIDE.g_Control.CreateControl("ide_main_scene", this, this._main_layer);
			this.UpdateProjectList();
			await ALittleIDE.g_IDEUICenter.Setup(this._edit_container);
			ALittleIDE.g_IDEUICenter.Show();
			A_UISystem.keydown_callback = this.HandleShortcutKey.bind(this);
			ALittleIDE.g_IDEIMEManager.Setup();
			ALittleIDE.g_IDEProjectManager.OpenLastProject();
			ALittleIDE.g_IDELoginManager.Setup();
			___COROUTINE();
		}).bind(this));
	},
	Shutdown : function() {
		ALittleIDE.g_IDEUICenter.Shutdown();
		ALittleIDE.g_IDELoginManager.Shutdown();
		ALittleIDE.g_IDEIMEManager.Shutdown();
	},
	ShowPhoneStatusLine : function(r, g, b) {
		let background_quad = this._phone_status_quad;
		background_quad.red = r / 255;
		background_quad.green = g / 255;
		background_quad.blue = b / 255;
		background_quad.visible = true;
		let status_h = ALittle.System_GetStatusBarHeight();
		this._main_layer.height_value = status_h;
		this._main_layer.y = status_h;
		this._dialog_layer.height_value = status_h;
		this._dialog_layer.y = status_h;
	},
	HidePhoneStatusLine : function() {
		let background_quad = this._phone_status_quad;
		background_quad.visible = false;
		this._main_layer.height_value = 0;
		this._main_layer.y = 0;
		this._dialog_layer.height_value = 0;
		this._dialog_layer.y = 0;
	},
	HandlePeojectSelectChange : function(event) {
		let name = "";
		if (ALittleIDE.g_IDEProject.project !== undefined) {
			name = ALittleIDE.g_IDEProject.project.name;
		}
		let new_name = event.target.text;
		if (new_name === name) {
			return;
		}
		if (ALittleIDE.g_IDETabManager.IsSaveAll()) {
			ALittleIDE.g_IDEProjectManager.OpenProjectImpl(new_name);
			return;
		}
		event.target.text = name;
		let cancel_callback = ALittleIDE.g_IDEProjectManager.OpenProjectImpl.bind(ALittleIDE.g_IDEProjectManager, new_name);
		let confirm_callback = ALittleIDE.g_IDETabManager.SaveAllTab.bind(ALittleIDE.g_IDETabManager);
		ALittleIDE.g_IDETool.SaveNotice("提示", "是否保存当前项目?", cancel_callback, confirm_callback);
	},
	UpdateProjectList : function() {
		if (this._current_project_name === undefined) {
			return;
		}
		let data_list = [];
		let data_list_count = 0;
		let project_map = ALittleIDE.g_IDEConfig.GetConfig("project_map", {});
		let ___OBJECT_1 = project_map;
		for (let k in ___OBJECT_1) {
			let v = ___OBJECT_1[k];
			if (v === undefined) continue;
			++ data_list_count;
			data_list[data_list_count - 1] = v;
		}
		ALittle.List_Sort(data_list);
		let text = this._current_project_name.text;
		this._current_project_name.data_list = data_list;
		this._current_project_name.text = text;
	},
	OpenProject : function(name) {
		if (name === "") {
			this._current_project_name.text = "当前没有打开的项目";
		} else {
			this._current_project_name.text = name;
		}
		ALittleIDE.g_IDEProject.OpenProject(name);
		this.UpdateProjectList();
	},
	CloseProject : function() {
		this._current_project_name.text = "当前没有打开的项目";
		ALittleIDE.g_IDEImageManager.ClearImageItem();
		ALittleIDE.g_IDEControlManager.ClearControlItem();
		ALittleIDE.g_IDETabManager.CloseAllTab();
		ALittleIDE.g_IDEProject.CloseProject();
		ALittleIDE.g_IDEAttrImageDialog.Close();
	},
	RefreshProject : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			return;
		}
		let project_name = ALittleIDE.g_IDEProject.project.name;
		let name_list = ALittleIDE.g_IDETabManager.GetTabNameList();
		let tab_index = ALittleIDE.g_IDETabManager.GetCurTabIndex();
		this.CloseProject();
		this.OpenProject(project_name);
		let count = ALittle.List_MaxN(name_list);
		if (count > 0) {
			for (let i = count; count >= 1; i += -1) {
				let control_info = ALittleIDE.g_IDEProject.project.control_map[name_list[i - 1]];
				if (control_info !== undefined) {
					ALittleIDE.g_IDETabManager.StartEditControlBySelect(control_info.name, control_info.info);
				}
			}
			ALittleIDE.g_IDETabManager.SetCurTabIndex(tab_index);
		}
	},
	HandleFileMenuClick : function(event) {
		ALittleIDE.g_IDEMainMenu.ShowFileMenu(event);
	},
	HandleEditMenuClick : function(event) {
		ALittleIDE.g_IDEMainMenu.ShowEditMenu(event);
	},
	HandleToolMenuClick : function(event) {
		ALittleIDE.g_IDEMainMenu.ShowToolMenu(event);
	},
	HandleVersionMenuClick : function(event) {
	},
	HandleRunMenuClick : function(event) {
		ALittleIDE.g_IDEProjectManager.RunProject();
	},
	HandleShortcutKey : function(mod, sym, scancode) {
		if (A_UISystem.sym_map.get(1073741886)) {
			ALittleIDE.g_IDEProjectManager.RunProject();
			return;
		}
		ALittleIDE.g_IDEUICenter.HandleShortcutKey();
	},
	HandleAccountLoginLB : function(event) {
		ALittleIDE.g_IDELoginManager.ShowLoginDialog();
	},
	AccountInLogin : function() {
		this._account_login.visible = false;
		this._account_dropdown.visible = true;
		let data_list = [];
		data_list[1 - 1] = "修改密码";
		data_list[2 - 1] = "登出";
		this._account_dropdown.data_list = data_list;
		this._account_dropdown.text = ALittleIDE.g_IDELoginManager.account_name;
		this._account_icon.x_value = this._account_dropdown.x_value + this._account_dropdown.width + 5;
	},
	AccountInLogout : function() {
		this._account_login.text = "请登录";
		this._account_login.underline = true;
		this._account_login.visible = true;
		this._account_login.disabled = false;
		this._account_dropdown.visible = false;
		this._account_icon.x_value = this._account_login.x_value + this._account_login.width + 5;
	},
	AccountInReConnect : function() {
		this._account_login.text = "正在重连";
		this._account_login.underline = false;
		this._account_login.visible = true;
		this._account_login.disabled = true;
		this._account_dropdown.visible = false;
		this._account_icon.x_value = this._account_login.x_value + this._account_login.width + 5;
	},
	HandleAccountDropdownChange : function(event) {
		if (event.target.text === "登出") {
			ALittleIDE.g_IDELoginManager.Logout();
		} else if (event.target.text === "修改密码") {
			ALittleIDE.g_IDELoginManager.ShowPasswordDialog();
		}
		this._account_dropdown.text = ALittleIDE.g_IDELoginManager.account_name;
	},
}, "ALittleIDE.IDECenter");

ALittleIDE.g_IDECenter = ALittle.NewObject(ALittleIDE.IDECenter);
}