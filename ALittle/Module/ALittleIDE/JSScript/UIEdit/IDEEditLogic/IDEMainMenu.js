{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};

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
	HandleGenCoreAllInOneClick : function(event) {
		A_LayerManager.HideFromRight(this._menu_tool_menu);
		let all_in_one = [];
		let base_path = "Module/ALittleIDE/Other/GameLibrary/Core/JSScript/";
		let file_list = [];
		ALittle.List_Push(file_list, base_path + "ALittle.js");
		ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path + "Core/JavaScript/"));
		ALittle.List_Push(file_list, base_path + "Core/Reflect/ReflectRegister.js");
		ALittle.List_Push(file_list, base_path + "Core/Reflect/ReflectDefine.js");
		ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path + "Core/Utility/"));
		ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path + "Core/Net/"));
		let ___OBJECT_3 = file_list;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let path = ___OBJECT_3[index - 1];
			if (path === undefined) break;
			let error = undefined;
			[error, all_in_one[index - 1]] = ALittle.File_ReadTextFromStdFile(path);
			if (error !== undefined) {
				ALittleIDE.g_IDETool.ShowNotice("提示", "生成失败:" + error);
				return;
			}
		}
		let result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/Core/Core.js");
		if (result) {
			ALittleIDE.g_IDETool.ShowNotice("提示", "生成成功");
		} else {
			ALittleIDE.g_IDETool.ShowNotice("提示", "生成失败");
		}
	},
	HandleGenStdAllInOneClick : function(event) {
		A_LayerManager.HideFromRight(this._menu_tool_menu);
		let all_in_one = [];
		let base_path = "Module/ALittleIDE/Other/GameLibrary/Std/JSScript/";
		let file_list = [];
		ALittle.List_Push(file_list, base_path + "ALittle.js");
		ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path + "Std/Reflect/"));
		ALittle.List_Push(file_list, base_path + "Std/Loop/LoopObject.js");
		ALittle.List_Push(file_list, base_path + "Std/Loop/ILoopSystem.js");
		ALittle.List_Push(file_list, base_path + "Std/Loop/LoopFrame.js");
		ALittle.List_Push(file_list, base_path + "Std/Loop/LoopFunction.js");
		ALittle.List_Push(file_list, base_path + "Std/Loop/LoopGroup.js");
		ALittle.List_Push(file_list, base_path + "Std/Loop/LoopList.js");
		ALittle.List_Push(file_list, base_path + "Std/Loop/LoopTimer.js");
		ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path + "Std/Utility/"));
		ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path + "Std/Net/"));
		ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path + "Adapter/JavaScript/"));
		ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path + "Std/Singleton/"));
		let ___OBJECT_4 = file_list;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let path = ___OBJECT_4[index - 1];
			if (path === undefined) break;
			let error = undefined;
			[error, all_in_one[index - 1]] = ALittle.File_ReadTextFromStdFile(path);
			if (error !== undefined) {
				ALittleIDE.g_IDETool.ShowNotice("提示", "生成失败:" + error);
				return;
			}
		}
		let result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/Std/Std.js");
		if (result) {
			ALittleIDE.g_IDETool.ShowNotice("提示", "生成成功");
		} else {
			ALittleIDE.g_IDETool.ShowNotice("提示", "生成失败");
		}
	},
	HandleGenCEngineAllInOneClick : function(event) {
		A_LayerManager.HideFromRight(this._menu_tool_menu);
		let all_in_one = [];
		let base_path = "Module/ALittleIDE/Other/GameLibrary/CEngine/JSScript/";
		let file_list = [];
		ALittle.List_Push(file_list, base_path + "ALittle.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/IShow.js");
		ALittle.List_Push(file_list, base_path + "Adapter/PIXI/JSystem.js");
		ALittle.List_Push(file_list, base_path + "Adapter/PIXI/JShow.js");
		ALittle.List_Push(file_list, base_path + "Adapter/PIXI/JCsvLoader.js");
		ALittle.List_Push(file_list, base_path + "CEngine/Utility/String.js");
		ALittle.List_Push(file_list, base_path + "CEngine/Utility/File.js");
		ALittle.List_Push(file_list, base_path + "CEngine/Utility/System.js");
		ALittle.List_Push(file_list, base_path + "CEngine/Utility/ConfigSystem.js");
		ALittle.List_Push(file_list, base_path + "CEngine/Utility/OtherSystem.js");
		ALittle.List_Push(file_list, base_path + "CEngine/Utility/AudioSystem.js");
		ALittle.List_Push(file_list, base_path + "CEngine/Utility/ModuleSystem.js");
		ALittle.List_Push(file_list, base_path + "CEngine/Utility/CsvConfigManager.js");
		ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path + "CEngine/LoopSystem/"));
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/UIEnumTypes.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/UIEventDispatcher.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Base/Matrix2D.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Base/DisplayObject.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Base/DisplayGroup.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Base/DisplayLayout.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Base/DisplayView.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Base/Quad.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Base/Image.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Base/Sprite.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Base/Text.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Base/TextArea.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Base/TextEdit.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Base/TextInput.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Base/Triangle.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/Grid9Image.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/TextButton.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/TextCheckButton.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/TextRadioButton.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/Grid3.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/Grid9.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/Linear.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/Tab.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/DropDown.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/Slider.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/ScrollBar.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/ScrollScreen.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/Dialog.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/TileTable.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/ImagePlay.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/SpritePlay.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/FramePlay.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/Piechart.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/ImageInput.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/ImageEdit.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/RichArea.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/RichEdit.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/RichInput.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/ScrollList.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/ScrollButton.js");
		ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path + "CEngine/UISystem/Special/"));
		ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path + "CEngine/UISystem/Plugin/"));
		ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path + "CEngine/UISystem/Effect/"));
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/UISystem.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/LayerManager.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/TextureManager.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/ControlSystem.js");
		let ___OBJECT_5 = file_list;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let path = ___OBJECT_5[index - 1];
			if (path === undefined) break;
			let error = undefined;
			[error, all_in_one[index - 1]] = ALittle.File_ReadTextFromStdFile(path);
			if (error !== undefined) {
				ALittleIDE.g_IDETool.ShowNotice("提示", "生成失败:" + error);
				return;
			}
		}
		let result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/CEngine/CEngine.js");
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