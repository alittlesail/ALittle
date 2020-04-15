{
if (typeof ALittleIDE === "undefined") ALittleIDE = {};

ALittle.RegStruct(1255897792, "ALittleIDE.IDEMainMenuImageInfo", {
name : "ALittleIDE.IDEMainMenuImageInfo", ns_name : "ALittleIDE", rl_name : "IDEMainMenuImageInfo", hash_code : 1255897792,
name_list : ["file_name","x","y","width","height"],
type_list : ["string","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(1020446174, "ALittleIDE.IDEMainMenuFramePlayInfo", {
name : "ALittleIDE.IDEMainMenuFramePlayInfo", ns_name : "ALittleIDE", rl_name : "IDEMainMenuFramePlayInfo", hash_code : 1020446174,
name_list : ["width","height","root_path","image_list","image_count"],
type_list : ["double","double","string","List<ALittleIDE.IDEMainMenuImageInfo>","int"],
option_map : {}
})

ALittleIDE.IDEMainMenu = JavaScript.Class(undefined, {
	ShowFileMenu : function(event) {
		if (this._menu_file_menu === undefined) {
			this._menu_file_menu = ALittleIDE.g_Control.CreateControl("ide_file_menu", this);
		}
		let [x, y] = event.target.LocalToGlobal();
		this._menu_file_menu.x = x;
		this._menu_file_menu.y = y + event.target.height;
		A_LayerManager.ShowFromRight(this._menu_file_menu);
	},
	HandleNewProject : function(event) {
		A_LayerManager.HideFromRight(this._menu_file_menu);
		ALittleIDE.g_IDEProjectManager.ShowNewProject();
	},
	HandleOpenProject : function(event) {
		A_LayerManager.HideFromRight(this._menu_file_menu);
		ALittleIDE.g_IDEProjectManager.ShowOpenProject();
	},
	HandleSettingProject : function(event) {
		A_LayerManager.HideFromRight(this._menu_file_menu);
		ALittleIDE.g_IDEProjectManager.ShowSettingProject(undefined);
	},
	HandleSaveProject : function(event) {
		A_LayerManager.HideFromRight(this._menu_file_menu);
		ALittleIDE.g_IDETabManager.SaveAllTab();
	},
	HandleRefreshProject : function(event) {
		A_LayerManager.HideFromRight(this._menu_file_menu);
		ALittleIDE.g_IDEProjectManager.RefreshProject();
	},
	HandleExportProject : function(event) {
		A_LayerManager.HideFromRight(this._menu_file_menu);
		ALittleIDE.g_IDEProjectManager.ShowExportProject();
	},
	HandleRun : function(event) {
		A_LayerManager.HideFromRight(this._menu_file_menu);
		ALittleIDE.g_IDEProjectManager.RunProject();
	},
	ShowEditMenu : function(event) {
		if (this._menu_edit_menu === undefined) {
			this._menu_edit_menu = ALittleIDE.g_Control.CreateControl("ide_edit_menu", this);
		}
		let [x, y] = event.target.LocalToGlobal();
		this._menu_edit_menu.x = x;
		this._menu_edit_menu.y = y + event.target.height;
		A_LayerManager.ShowFromRight(this._menu_edit_menu);
	},
	HandleNewControl : function(event) {
		A_LayerManager.HideFromRight(this._menu_edit_menu);
		ALittleIDE.g_IDEControlManager.ShowNewControl();
	},
	HandleUndoRevoke : function(event) {
		A_LayerManager.HideFromRight(this._menu_edit_menu);
		ALittleIDE.g_IDEUICenter.HandleUndoRevoke(undefined);
	},
	HandleDoRevoke : function(event) {
		A_LayerManager.HideFromRight(this._menu_edit_menu);
		ALittleIDE.g_IDEUICenter.HandleDoRevoke(undefined);
	},
	ShowToolMenu : function(event) {
		if (this._menu_tool_menu === undefined) {
			this._menu_tool_menu = ALittleIDE.g_Control.CreateControl("ide_tool_menu", this);
		}
		let [x, y] = event.target.LocalToGlobal();
		this._menu_tool_menu.x = x;
		this._menu_tool_menu.y = y + event.target.height;
		A_LayerManager.ShowFromRight(this._menu_tool_menu);
	},
	HandleGenUIAllInOneClick : function(event) {
		A_LayerManager.HideFromRight(this._menu_tool_menu);
		if (ALittleIDE.g_IDEProject.project === undefined) {
			ALittleIDE.g_IDETool.ShowNotice("提示", "没有加载项目");
			return;
		}
		let all_in_one = {};
		let map = ALittle.File_GetFileAttrByDir("Module/" + ALittleIDE.g_IDEProject.project.name + "/UI");
		let ___OBJECT_1 = map;
		for (let path in ___OBJECT_1) {
			let _ = ___OBJECT_1[path];
			if (_ === undefined) continue;
			let [json] = ALittle.File_ReadJsonFromStdFile(path);
			let ___OBJECT_2 = json;
			for (let name in ___OBJECT_2) {
				let o = ___OBJECT_2[name];
				if (o === undefined) continue;
				all_in_one[name] = o;
			}
		}
		let result = ALittle.File_WriteJsonFromStdFile(all_in_one, "Module/" + ALittleIDE.g_IDEProject.project.name + "/ui_all_in_one.json");
		if (result) {
			ALittleIDE.g_IDETool.ShowNotice("提示", "生成成功");
		} else {
			ALittleIDE.g_IDETool.ShowNotice("提示", "生成失败");
		}
	},
	HandleFramePlayFromPList : function(event) {
		A_LayerManager.HideFromRight(this._menu_tool_menu);
		if (this._frameplay_plist_dialog === undefined) {
			this._frameplay_plist_dialog = ALittleIDE.g_Control.CreateControl("ide_frameplay_plist_dialog", this, ALittleIDE.g_IDECenter.dialog_layer);
		}
		this._frameplay_plist_dialog.visible = true;
	},
	ImageListInFramePlayCmp : function(a, b) {
		return a.file_name < a.file_name;
	},
	HandleViewLog : function(event) {
		A_LayerManager.HideFromRight(this._menu_tool_menu);
		if (this._view_log_dialog === undefined) {
			this._view_log_dialog = ALittleIDE.g_Control.CreateControl("ide_view_log_dialog", this, ALittleIDE.g_IDECenter.dialog_layer);
			this.HandleViewLogRefresh(undefined);
		}
		this._view_log_dialog.visible = true;
	},
	HandleViewLogRefresh : function(event) {
		let file_name = ALittle.Time_GetCurYMD(ALittle.Time_GetCurTime()) + ".log";
		let file_path = ALittle.File_BaseFilePath() + "Log/" + file_name;
		let content = ALittle.File_ReadTextFromFile(file_path, false);
		if (content === undefined) {
			return;
		}
		let content_list = ALittle.String_Split(content, "\n");
		let content_len = ALittle.List_MaxN(content_list);
		let copy_len = content_len - 100;
		if (copy_len < 1) {
			copy_len = 1;
		}
		let log_list = [];
		let log_list_count = 0;
		for (let i = content_len; i >= copy_len; i += -1) {
			++ log_list_count;
			log_list[log_list_count - 1] = content_list[i - 1];
		}
		this._view_log_content.text = ALittle.String_Join(log_list, "\n");
	},
	HandleViewLogClose : function(event) {
		this._view_log_dialog.visible = false;
	},
}, "ALittleIDE.IDEMainMenu");

ALittleIDE.g_IDEMainMenu = ALittle.NewObject(ALittleIDE.IDEMainMenu);
}