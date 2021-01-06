{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1810358206, "ALittleIDE.IDEVersionCloseItemUserData", {
name : "ALittleIDE.IDEVersionCloseItemUserData", ns_name : "ALittleIDE", rl_name : "IDEVersionCloseItemUserData", hash_code : -1810358206,
name_list : ["info","data"],
type_list : ["VersionServer.AVersionInfo","VersionServer.D_VersionClose"],
option_map : {}
})
ALittle.RegStruct(1657250345, "VersionServer.D_VersionInfo", {
name : "VersionServer.D_VersionInfo", ns_name : "VersionServer", rl_name : "D_VersionInfo", hash_code : 1657250345,
name_list : ["version_id","account_id","module_name","platform","big_version","version_number","install_version","plugin_list","install_size","status","small_version_time","small_version_index","create_time","create_index","update_time","update_index"],
type_list : ["string","string","string","string","string","string","string","string","int","int","int","int","int","int","int","int"],
option_map : {}
})
ALittle.RegStruct(-1510712093, "ALittleIDE.IDEVersionInfoItemUserData", {
name : "ALittleIDE.IDEVersionInfoItemUserData", ns_name : "ALittleIDE", rl_name : "IDEVersionInfoItemUserData", hash_code : -1510712093,
name_list : ["info","data"],
type_list : ["VersionServer.AVersionInfo","VersionServer.D_VersionInfo"],
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
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name : "ALittle.UIChangedEvent", ns_name : "ALittle", rl_name : "UIChangedEvent", hash_code : 958494922,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(929252339, "VersionServer.D_VersionClose", {
name : "VersionServer.D_VersionClose", ns_name : "VersionServer", rl_name : "D_VersionClose", hash_code : 929252339,
name_list : ["account_id","module_name","platform","close_version","submit_platform","create_time","create_index","update_time","update_index"],
type_list : ["string","string","string","string","string","int","int","int","int"],
option_map : {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-637772875, "VersionServer.D_VersionLog", {
name : "VersionServer.D_VersionLog", ns_name : "VersionServer", rl_name : "D_VersionLog", hash_code : -637772875,
name_list : ["version_id","account_id","module_name","platform","content","create_time","create_index","update_time","update_index"],
type_list : ["string","string","string","string","string","int","int","int","int"],
option_map : {}
})
ALittle.RegStruct(-590627586, "ALittleIDE.IDEVersionInfoItem", {
name : "ALittleIDE.IDEVersionInfoItem", ns_name : "ALittleIDE", rl_name : "IDEVersionInfoItem", hash_code : -590627586,
name_list : ["_item_button","_item_title"],
type_list : ["ALittle.TextRadioButton","ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(129933683, "VersionServer.AVersionInfo", {
name : "VersionServer.AVersionInfo", ns_name : "VersionServer", rl_name : "AVersionInfo", hash_code : 129933683,
name_list : ["version_list","close_list","log_list"],
type_list : ["List<VersionServer.D_VersionInfo>","List<VersionServer.D_VersionClose>","List<VersionServer.D_VersionLog>"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEVersionList = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._platform = "Windows";
		this._config_key = "";
	},
	TCtor : function() {
	},
	set platform(value) {
		this._platform = value;
	},
	get platform() {
		return this._platform;
	},
	set config_key(value) {
		this._config_key = value;
	},
	get config_key() {
		return this._config_key;
	},
	get export_old_log() {
		return this._export_old_log;
	},
	HandleRefreshVersionList : async function(event) {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return;
		}
		if (!ALittleIDE.g_IDEWebLoginManager.IsLogin()) {
			g_AUITool.ShowNotice("错误", "请先登陆");
			return;
		}
		this._export_refresh_btn.disabled = true;
		this._version_list.RemoveAllChild();
		this._close_list.RemoveAllChild();
		let group = ALittle.CreateKeyWeakMap();
		let param = {};
		param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id;
		param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id;
		param.platform = this._platform;
		param.module_name = ALittleIDE.g_IDEProject.project.name;
		let client = ALittle.CreateHttpSender(ALittleIDE.g_IDEWebLoginManager.http_ip, ALittleIDE.g_IDEWebLoginManager.http_port);
		let [error, result] = await ALittle.IHttpSender.Invoke("VersionServer.QVersionInfo", client, param);
		this._export_refresh_btn.disabled = false;
		if (error !== undefined) {
			g_AUITool.ShowNotice("错误", "刷新失败:" + error);
			return;
		}
		let version_list = result.version_list;
		if (version_list === undefined) {
			version_list = [];
		}
		ALittle.List_Sort(version_list, ALittleIDE.IDEVersionList.VersionInfoCmp);
		let first_version_info = undefined;
		let ___OBJECT_1 = version_list;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			let control_line = {};
			let item = ALittleIDE.g_Control.CreateControl("ide_version_item", control_line, this._version_list);
			control_line._item_button.group = group;
			let user_data = {};
			control_line._item_button._user_data = user_data;
			user_data.info = result;
			user_data.data = v;
			control_line._item_button.drag_trans_target = this._version_list;
			control_line._item_button.AddEventListener(___all_struct.get(958494922), this, this.HandleVersionListSelectChange);
			control_line._item_button.AddEventListener(___all_struct.get(-641444818), this, this.HandleVersionListMenu);
			let status_str = "上传失败";
			if (v.status === 1) {
				status_str = "上传成功";
			}
			control_line._item_title.text = "版本时间:" + ALittle.Time_GetCurDate(v.update_time) + "(" + status_str + ")";
			if (first_version_info === undefined) {
				control_line._item_button.selected = true;
				first_version_info = user_data;
			}
		}
		let close_list = result.close_list;
		if (close_list === undefined) {
			close_list = [];
		}
		let ___OBJECT_2 = close_list;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let v = ___OBJECT_2[k - 1];
			if (v === undefined) break;
			let control_line = {};
			let item = this._ctrl_sys.CreateControl("tree_item", control_line, this._close_list);
			control_line._item_button.group = group;
			let user_data = {};
			control_line._item_button._user_data = user_data;
			user_data.info = result;
			user_data.data = v;
			control_line._item_button.drag_trans_target = this._close_list;
			control_line._item_button.AddEventListener(___all_struct.get(-641444818), this, this.HandleVersionCloseListMenu);
			control_line._item_title.text = v.close_version + "(" + v.submit_platform + ")";
		}
		if (first_version_info !== undefined) {
			this.ShowVersionInfo(first_version_info);
		}
	},
	VersionInfoCmp : function(a, b) {
		if (a.update_time !== b.update_time) {
			return a.update_time > b.update_time;
		}
		return a.update_index > b.update_index;
	},
	HandleVersionListMenu : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("删除", this.HandleVersionDelete.bind(this, event.target._user_data));
		menu.Show();
	},
	HandleVersionDelete : async function(version_info) {
		let delete_result = await g_AUITool.DeleteNotice("删除", "确定要删除" + ALittle.Time_GetCurDate(version_info.data.update_time) + "(版本时间)这个版本吗?");
		if (delete_result !== "YES") {
			return;
		}
		let param = {};
		param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id;
		param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id;
		param.platform = this._platform;
		param.module_name = ALittleIDE.g_IDEProject.project.name;
		param.version_id = version_info.data.version_id;
		let client = ALittle.CreateHttpSender(ALittleIDE.g_IDEWebLoginManager.http_ip, ALittleIDE.g_IDEWebLoginManager.http_port);
		let [error, result] = await ALittle.IHttpSender.Invoke("VersionServer.QDeleteVersionInfo", client, param);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", "删除失败:" + error);
			return;
		}
		this.HandleRefreshVersionList(undefined);
	},
	HandleVersionListSelectChange : function(event) {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			return;
		}
		if (event.target.selected === false) {
			return;
		}
		let version_info = event.target._user_data;
		if (version_info === undefined) {
			this.LoadConfig();
			return;
		}
		this.ShowVersionInfo(version_info);
	},
	ShowVersionInfo : function(version_info) {
		if (version_info.data.big_version !== undefined) {
			this._export_big_version.text = version_info.data.big_version;
		} else {
			this._export_big_version.text = "";
		}
		if (version_info.data.install_version !== undefined) {
			this._export_install_version.text = version_info.data.install_version;
		} else {
			this._export_install_version.text = "";
		}
		if (version_info.data.version_number !== undefined) {
			this._export_version_number.text = version_info.data.version_number;
		} else {
			this._export_version_number.text = "";
		}
		if (version_info.data.plugin_list !== undefined) {
			this._export_plugin_list.text = version_info.data.plugin_list;
		} else {
			this._export_plugin_list.text = "";
		}
		let log_list = [];
		let last_create_time = 0;
		let log_index = 1;
		let ___OBJECT_3 = version_info.info.log_list;
		for (let k = 1; k <= ___OBJECT_3.length; ++k) {
			let v = ___OBJECT_3[k - 1];
			if (v === undefined) break;
			if (v.create_time !== last_create_time) {
				last_create_time = v.create_time;
				log_index = 1;
				log_list[log_index - 1] = ALittle.Time_GetCurDate(last_create_time);
			}
			log_list[log_index + 1 - 1] = "\t" + log_index + "." + v.content;
			log_index = log_index + 1;
		}
		this._export_old_log.text = ALittle.String_Join(log_list, "\n");
	},
	HandleVersionCloseListMenu : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("删除", this.HandleVersionCloseDelete.bind(this, event.target._user_data));
		menu.Show();
	},
	HandleVersionCloseDelete : async function(version_info) {
		let delete_result = await g_AUITool.DeleteNotice("删除", "确定要删除" + version_info.data.close_version + "(" + version_info.data.submit_platform + ")这个拦截版本吗?");
		if (delete_result !== "YES") {
			return;
		}
		let param = {};
		param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id;
		param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id;
		param.platform = this._platform;
		param.module_name = ALittleIDE.g_IDEProject.project.name;
		param.close_version = version_info.data.close_version;
		let client = ALittle.CreateHttpSender(ALittleIDE.g_IDEWebLoginManager.http_ip, ALittleIDE.g_IDEWebLoginManager.http_port);
		let [error, result] = await ALittle.IHttpSender.Invoke("VersionServer.QDeleteVersionClose", client, param);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", "删除失败:" + error);
			return;
		}
		this.HandleRefreshVersionList(undefined);
	},
	HandleAddVersionClose : function(event) {
		if (this._version_close_dialog === undefined) {
			this._version_close_dialog = this._ctrl_sys.CreateControl("ide_add_version_close_dialog", this);
			ALittleIDE.g_DialogLayer.AddChild(this._version_close_dialog);
		}
		this._version_close_version.text = "";
		this._version_submit_platform.text = "";
		this._version_close_dialog.visible = true;
		this._version_close_dialog.MoveToTop();
	},
	HandleAddVersionCloseClick : async function(event) {
		this._version_close_dialog.visible = false;
		let param = {};
		param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id;
		param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id;
		param.platform = this._platform;
		param.module_name = ALittleIDE.g_IDEProject.project.name;
		param.close_version = this._version_close_version.text;
		param.submit_platform = this._version_submit_platform.text;
		let client = ALittle.CreateHttpSender(ALittleIDE.g_IDEWebLoginManager.http_ip, ALittleIDE.g_IDEWebLoginManager.http_port);
		let [error, result] = await ALittle.IHttpSender.Invoke("VersionServer.QAddVersionClose", client, param);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", "添加失败:" + error);
			return;
		}
		this.HandleRefreshVersionList(undefined);
	},
	LoadConfig : function() {
		let export_info = ALittleIDE.g_IDEProject.project.config.GetConfig(this._config_key, {});
		let version_info = export_info.version_info;
		if (version_info === undefined) {
			version_info = {};
		}
		let version = ALittle.Time_GetCurDate(ALittle.Time_GetCurTime());
		if (version_info.big_version !== undefined) {
			this._export_big_version.text = version_info.big_version;
		} else {
			this._export_big_version.text = version;
		}
		if (version_info.install_version !== undefined) {
			this._export_install_version.text = version_info.install_version;
		} else {
			this._export_install_version.text = version;
		}
		if (version_info.version_number !== undefined) {
			this._export_version_number.text = version_info.version_number;
		} else {
			this._export_version_number.text = "";
		}
		if (version_info.plugin_list !== undefined) {
			this._export_plugin_list.text = version_info.plugin_list;
		} else {
			this._export_plugin_list.text = "";
		}
	},
	CheckDateString : function(content) {
		let list = ALittle.String_Split(content, "-");
		if (ALittle.List_Len(list) !== 6) {
			return false;
		}
		if (ALittle.String_Len(list[1 - 1]) !== 4) {
			return false;
		}
		if (ALittle.Math_ToInt(list[1 - 1]) === undefined) {
			return false;
		}
		for (let i = 2; i <= 6; i += 1) {
			if (ALittle.String_Len(list[i - 1]) !== 2) {
				return false;
			}
			if (ALittle.Math_ToInt(list[i - 1]) === undefined) {
				return false;
			}
		}
		return true;
	},
	CheckVersionString : function(content) {
		let list = ALittle.String_Split(content, ".");
		if (ALittle.List_Len(list) !== 3) {
			return false;
		}
		for (let i = 1; i <= 2; i += 1) {
			if (ALittle.Math_ToInt(list[i - 1]) === undefined) {
				return false;
			}
		}
		return true;
	},
	GetConfig : function() {
		let version_info = {};
		version_info.big_version = this._export_big_version.text;
		if (this.CheckDateString(version_info.big_version) === false) {
			g_AUITool.ShowNotice("错误", "大版本格式不正确，请调整格式为：YYYY-mm-dd-HH-MM-SS");
			return undefined;
		}
		version_info.install_version = this._export_install_version.text;
		if (this.CheckDateString(version_info.install_version) === false) {
			g_AUITool.ShowNotice("错误", "安装包版本格式不正确，请调整格式为：YYYY-mm-dd-HH-MM-SS");
			return undefined;
		}
		version_info.version_number = this._export_version_number.text;
		if (this.CheckVersionString(version_info.version_number) === false) {
			g_AUITool.ShowNotice("错误", "软件版本号格式不正确，请调整格式为：数字.数字.数字");
			return undefined;
		}
		version_info.plugin_list = this._export_plugin_list.text;
		let module_list = ALittle.String_Split(version_info.plugin_list, ",");
		let ___OBJECT_4 = module_list;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let module = ___OBJECT_4[index - 1];
			if (module === undefined) break;
			if (ALittle.File_GetFileAttr(ALittle.File_BaseFilePath() + "Module/" + module) === undefined) {
				g_AUITool.ShowNotice("错误", "引入的插件不存在:" + module);
				return undefined;
			}
		}
		return version_info;
	},
	HandleGenBigVersion : async function(event) {
		let result = await g_AUITool.DeleteNotice("更新大版本号", "更新大版本号会引起强制更新，确定更新吗？");
		if (result === "YES") {
			this._export_big_version.text = ALittle.Time_GetCurDate();
		}
	},
	HandleGenInstallVersion : async function(event) {
		let result = await g_AUITool.DeleteNotice("更新安装包版本号", "更新安装包版本号会引起重新安装，确定更新吗？");
		if (result === "YES") {
			this._export_install_version.text = ALittle.Time_GetCurDate();
		}
	},
}, "ALittleIDE.IDEVersionList");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEVersionWindows = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
	},
	TCtor : function() {
		this._version_list.platform = "Windows";
		this._version_list.config_key = "windows_export_info";
	},
	set config_key(value) {
		this._version_list.config_key = value;
	},
	get config_key() {
		return this._version_list.config_key;
	},
	LoadConfigImpl : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return false;
		}
		this._version_list.LoadConfig();
		this._version_list.HandleRefreshVersionList(undefined);
		this._version_list.export_old_log.text = "";
		let export_info = ALittleIDE.g_IDEProject.project.config.GetConfig(this.config_key, {});
		let install_info = export_info.install_info;
		if (install_info === undefined) {
			install_info = {};
		}
		if (install_info.install_name !== undefined) {
			this._export_install_name.text = install_info.install_name;
		} else {
			this._export_install_name.text = "";
		}
		if (install_info.auto_start) {
			this._export_auto_start.text = "是";
		} else {
			this._export_auto_start.text = "否";
		}
		if (install_info.new_log !== undefined) {
			this._export_new_log.text = install_info.new_log;
		} else {
			this._export_new_log.text = "";
		}
		return true;
	},
	SaveConfigImpl : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return false;
		}
		let version_info = this._version_list.GetConfig();
		if (version_info === undefined) {
			return false;
		}
		let export_info = {};
		export_info.version_info = version_info;
		let install_info = {};
		export_info.install_info = install_info;
		install_info.file_name = "Install.exe";
		install_info.install_name = this._export_install_name.text;
		if (this._export_auto_start.text === "是") {
			install_info.auto_start = true;
		} else {
			install_info.auto_start = false;
		}
		if (install_info.install_name === "") {
			g_AUITool.ShowNotice("错误", "安装包名不能为空");
			return false;
		}
		install_info.new_log = this._export_new_log.text;
		ALittleIDE.g_IDEProject.project.config.SetConfig(this.config_key, export_info);
		return true;
	},
	HandleSaveConfig : function(event) {
		if (this.SaveConfigImpl() === false) {
			return;
		}
		g_AUITool.ShowNotice("提示", "配置保存成功");
	},
	HandleExport : async function(event) {
		if (this.SaveConfigImpl() === false) {
			return;
		}
		let export_info = ALittleIDE.g_IDEProject.project.config.GetConfig(this.config_key, undefined);
		if (export_info === undefined) {
			return;
		}
		g_AUITool.ShowNotice("提示", "JavaScript版本不支持导出项目功能");
	},
	HandleSubmit : async function(event) {
		await ALittleIDE.g_IDEExport.SubmitPlatform(ALittleIDE.g_IDEProject.project.name, "Windows");
	},
}, "ALittleIDE.IDEVersionWindows");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEVersionAndroid = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
	},
	TCtor : function() {
		this._version_list.platform = "Android";
		this._version_list.config_key = "android_export_info";
	},
	set config_key(value) {
		this._version_list.config_key = value;
	},
	get config_key() {
		return this._version_list.config_key;
	},
	LoadConfigImpl : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return false;
		}
		this._version_list.LoadConfig();
		this._version_list.HandleRefreshVersionList(undefined);
		this._version_list.export_old_log.text = "";
		let export_info = ALittleIDE.g_IDEProject.project.config.GetConfig(this.config_key, {});
		let install_info = export_info.install_info;
		if (install_info === undefined) {
			install_info = {};
		}
		if (install_info.install_name !== undefined) {
			this._export_install_name.text = install_info.install_name;
		} else {
			this._export_install_name.text = "";
		}
		if (install_info.package_name !== undefined) {
			this._export_package_name.text = install_info.package_name;
		} else {
			this._export_package_name.text = "";
		}
		if (install_info.screen !== undefined) {
			this._export_screen.text = install_info.screen;
		} else {
			this._export_screen.text = "竖屏";
		}
		if (install_info.fullscreen) {
			this._export_full_screen.text = "是";
		} else {
			this._export_full_screen.text = "否";
		}
		if (install_info.new_log !== undefined) {
			this._export_new_log.text = install_info.new_log;
		} else {
			this._export_new_log.text = "";
		}
		return true;
	},
	SaveConfigImpl : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return false;
		}
		let version_info = this._version_list.GetConfig();
		if (version_info === undefined) {
			return false;
		}
		let export_info = {};
		export_info.version_info = version_info;
		let install_info = {};
		export_info.install_info = install_info;
		install_info.file_name = "Install.apk";
		install_info.install_name = this._export_install_name.text;
		install_info.package_name = this._export_package_name.text;
		install_info.screen = this._export_screen.text;
		install_info.fullscreen = (this._export_full_screen.text === "是");
		if (install_info.install_name === "") {
			g_AUITool.ShowNotice("错误", "安装包名不能为空");
			return false;
		}
		if (install_info.package_name === "") {
			g_AUITool.ShowNotice("错误", "Android包名不能为空");
			return false;
		}
		install_info.new_log = this._export_new_log.text;
		ALittleIDE.g_IDEProject.project.config.SetConfig(this.config_key, export_info);
		return true;
	},
	HandleSaveConfig : function(event) {
		if (this.SaveConfigImpl() === false) {
			return;
		}
		g_AUITool.ShowNotice("提示", "配置保存成功");
	},
	HandleExport : async function(event) {
		if (this.SaveConfigImpl() === false) {
			return;
		}
		let export_info = ALittleIDE.g_IDEProject.project.config.GetConfig(this.config_key, undefined);
		if (export_info === undefined) {
			return;
		}
		g_AUITool.ShowNotice("提示", "JavaScript版本不支持导出项目功能");
	},
	HandleSubmit : async function(event) {
		await ALittleIDE.g_IDEExport.SubmitPlatform(ALittleIDE.g_IDEProject.project.name, "Android");
	},
}, "ALittleIDE.IDEVersionAndroid");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEVersioniOS = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
	},
	TCtor : function() {
		this._version_list.platform = "iOS";
		this._version_list.config_key = "ios_export_info";
	},
	set config_key(value) {
		this._version_list.config_key = value;
	},
	get config_key() {
		return this._version_list.config_key;
	},
	LoadConfigImpl : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return false;
		}
		this._version_list.LoadConfig();
		this._version_list.HandleRefreshVersionList(undefined);
		this._version_list.export_old_log.text = "";
		let export_info = ALittleIDE.g_IDEProject.project.config.GetConfig(this.config_key, {});
		let install_info = export_info.install_info;
		if (install_info === undefined) {
			install_info = {};
		}
		if (install_info.install_name !== undefined) {
			this._export_install_name.text = install_info.install_name;
		} else {
			this._export_install_name.text = "";
		}
		if (install_info.package_name !== undefined) {
			this._export_package_name.text = install_info.package_name;
		} else {
			this._export_package_name.text = "";
		}
		if (install_info.screen !== undefined) {
			this._export_screen.text = install_info.screen;
		} else {
			this._export_screen.text = "竖屏";
		}
		if (install_info.fullscreen) {
			this._export_full_screen.text = "是";
		} else {
			this._export_full_screen.text = "否";
		}
		if (install_info.new_log !== undefined) {
			this._export_new_log.text = install_info.new_log;
		} else {
			this._export_new_log.text = "";
		}
		return true;
	},
	SaveConfigImpl : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return false;
		}
		let version_info = this._version_list.GetConfig();
		if (version_info === undefined) {
			return false;
		}
		let export_info = {};
		export_info.version_info = version_info;
		let install_info = {};
		export_info.install_info = install_info;
		install_info.file_name = "Install.ipa";
		install_info.install_name = this._export_install_name.text;
		install_info.package_name = this._export_package_name.text;
		install_info.screen = this._export_screen.text;
		install_info.fullscreen = (this._export_full_screen.text === "是");
		if (install_info.install_name === "") {
			g_AUITool.ShowNotice("错误", "安装包名不能为空");
			return false;
		}
		if (install_info.package_name === "") {
			g_AUITool.ShowNotice("错误", "iOS包名不能为空");
			return false;
		}
		install_info.new_log = this._export_new_log.text;
		ALittleIDE.g_IDEProject.project.config.SetConfig(this.config_key, export_info);
		return true;
	},
	HandleSaveConfig : function(event) {
		if (this.SaveConfigImpl() === false) {
			return;
		}
		g_AUITool.ShowNotice("提示", "配置保存成功");
	},
	HandleExport : async function(event) {
		if (this.SaveConfigImpl() === false) {
			return;
		}
		let export_info = ALittleIDE.g_IDEProject.project.config.GetConfig(this.config_key, undefined);
		if (export_info === undefined) {
			return;
		}
		g_AUITool.ShowNotice("提示", "JavaScript版本不支持导出项目功能");
	},
	HandleSubmit : async function(event) {
		await ALittleIDE.g_IDEExport.SubmitPlatform(ALittleIDE.g_IDEProject.project.name, "iOS");
	},
}, "ALittleIDE.IDEVersioniOS");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEVersionWeb = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
	},
	TCtor : function() {
		this._version_list.platform = "Web";
		this._version_list.config_key = "web_export_info";
	},
	set config_key(value) {
		this._version_list.config_key = value;
	},
	get config_key() {
		return this._version_list.config_key;
	},
	LoadConfigImpl : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return false;
		}
		this._version_list.LoadConfig();
		this._version_list.HandleRefreshVersionList(undefined);
		this._version_list.export_old_log.text = "";
		let export_info = ALittleIDE.g_IDEProject.project.config.GetConfig(this.config_key, {});
		let install_info = export_info.install_info;
		if (install_info === undefined) {
			install_info = {};
		}
		if (install_info.new_log !== undefined) {
			this._export_new_log.text = install_info.new_log;
		} else {
			this._export_new_log.text = "";
		}
		return true;
	},
	SaveConfigImpl : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return false;
		}
		let version_info = this._version_list.GetConfig();
		if (version_info === undefined) {
			return false;
		}
		let export_info = {};
		export_info.version_info = version_info;
		let install_info = {};
		export_info.install_info = install_info;
		install_info.file_name = "Install.html";
		install_info.new_log = this._export_new_log.text;
		ALittleIDE.g_IDEProject.project.config.SetConfig(this.config_key, export_info);
		return true;
	},
	HandleSaveConfig : function(event) {
		if (this.SaveConfigImpl() === false) {
			return;
		}
		g_AUITool.ShowNotice("提示", "配置保存成功");
	},
	HandleExport : async function(event) {
		if (this.SaveConfigImpl() === false) {
			return;
		}
		let export_info = ALittleIDE.g_IDEProject.project.config.GetConfig(this.config_key, undefined);
		if (export_info === undefined) {
			return;
		}
		g_AUITool.ShowNotice("提示", "JavaScript版本不支持导出项目功能");
	},
	HandleSubmit : async function(event) {
		await ALittleIDE.g_IDEExport.SubmitPlatform(ALittleIDE.g_IDEProject.project.name, "Web");
	},
}, "ALittleIDE.IDEVersionWeb");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEVersionWeChat = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
	},
	TCtor : function() {
		this._version_list.platform = "WeChat";
		this._version_list.config_key = "wechat_export_info";
	},
	set config_key(value) {
		this._version_list.config_key = value;
	},
	get config_key() {
		return this._version_list.config_key;
	},
	LoadConfigImpl : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return false;
		}
		this._version_list.LoadConfig();
		this._version_list.HandleRefreshVersionList(undefined);
		this._version_list.export_old_log.text = "";
		let export_info = ALittleIDE.g_IDEProject.project.config.GetConfig(this.config_key, {});
		let install_info = export_info.install_info;
		if (install_info === undefined) {
			install_info = {};
		}
		if (install_info.new_log !== undefined) {
			this._export_new_log.text = install_info.new_log;
		} else {
			this._export_new_log.text = "";
		}
		if (install_info.res_ip !== undefined) {
			this._export_res_ip.text = install_info.res_ip;
		} else {
			this._export_res_ip.text = "";
		}
		if (install_info.res_port !== undefined) {
			this._export_res_port.text = install_info.res_port;
		} else {
			this._export_res_port.text = "";
		}
		if (install_info.res_base_path !== undefined) {
			this._export_res_base_path.text = install_info.res_base_path;
		} else {
			this._export_res_base_path.text = "";
		}
		if (install_info.screen !== undefined) {
			this._export_screen.text = install_info.screen;
		} else {
			this._export_screen.text = "竖屏";
		}
		return true;
	},
	SaveConfigImpl : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return false;
		}
		let version_info = this._version_list.GetConfig();
		if (version_info === undefined) {
			return false;
		}
		let export_info = {};
		export_info.version_info = version_info;
		let install_info = {};
		export_info.install_info = install_info;
		install_info.file_name = "Install.js";
		install_info.new_log = this._export_new_log.text;
		install_info.res_ip = this._export_res_ip.text;
		install_info.res_port = ALittle.Math_ToIntOrZero(this._export_res_port.text);
		install_info.res_base_path = this._export_res_base_path.text;
		install_info.screen = this._export_screen.text;
		ALittleIDE.g_IDEProject.project.config.SetConfig(this.config_key, export_info);
		return true;
	},
	HandleSaveConfig : function(event) {
		if (this.SaveConfigImpl() === false) {
			return;
		}
		g_AUITool.ShowNotice("提示", "配置保存成功");
	},
	HandleExport : async function(event) {
		if (this.SaveConfigImpl() === false) {
			return;
		}
		let export_info = ALittleIDE.g_IDEProject.project.config.GetConfig(this.config_key, undefined);
		if (export_info === undefined) {
			return;
		}
		g_AUITool.ShowNotice("提示", "JavaScript版本不支持导出项目功能");
	},
	HandleSubmit : async function(event) {
		await ALittleIDE.g_IDEExport.SubmitPlatform(ALittleIDE.g_IDEProject.project.name, "WeChat");
	},
}, "ALittleIDE.IDEVersionWeChat");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEVersionEmscripten = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
	},
	TCtor : function() {
		this._version_list.platform = "Emscripten";
		this._version_list.config_key = "emscripten_export_info";
	},
	set config_key(value) {
		this._version_list.config_key = value;
	},
	get config_key() {
		return this._version_list.config_key;
	},
	LoadConfigImpl : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return false;
		}
		this._version_list.LoadConfig();
		this._version_list.HandleRefreshVersionList(undefined);
		this._version_list.export_old_log.text = "";
		let export_info = ALittleIDE.g_IDEProject.project.config.GetConfig(this.config_key, {});
		let install_info = export_info.install_info;
		if (install_info === undefined) {
			install_info = {};
		}
		if (install_info.new_log !== undefined) {
			this._export_new_log.text = install_info.new_log;
		} else {
			this._export_new_log.text = "";
		}
		return true;
	},
	SaveConfigImpl : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return false;
		}
		let version_info = this._version_list.GetConfig();
		if (version_info === undefined) {
			return false;
		}
		let export_info = {};
		export_info.version_info = version_info;
		let install_info = {};
		export_info.install_info = install_info;
		install_info.file_name = "Install.html";
		if (install_info.install_name === "") {
			g_AUITool.ShowNotice("错误", "安装包名不能为空");
			return false;
		}
		install_info.new_log = this._export_new_log.text;
		ALittleIDE.g_IDEProject.project.config.SetConfig(this.config_key, export_info);
		return true;
	},
	HandleSaveConfig : function(event) {
		if (this.SaveConfigImpl() === false) {
			return;
		}
		g_AUITool.ShowNotice("提示", "配置保存成功");
	},
	HandleExport : async function(event) {
		if (this.SaveConfigImpl() === false) {
			return;
		}
		let export_info = ALittleIDE.g_IDEProject.project.config.GetConfig(this.config_key, undefined);
		if (export_info === undefined) {
			return;
		}
		g_AUITool.ShowNotice("提示", "JavaScript版本不支持导出项目功能");
	},
	HandleSubmit : async function(event) {
		await ALittleIDE.g_IDEExport.SubmitPlatform(ALittleIDE.g_IDEProject.project.name, "Emscripten");
	},
}, "ALittleIDE.IDEVersionEmscripten");

}