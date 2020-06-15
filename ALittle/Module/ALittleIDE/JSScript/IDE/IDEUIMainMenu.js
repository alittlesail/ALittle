{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittle.Linear === undefined) throw new Error(" extends class:ALittle.Linear is undefined");
ALittleIDE.IDEUIMainMenu = JavaScript.Class(ALittle.Linear, {
	TCtor : function() {
		let version_ip = ALittleIDE.g_IDEServerConfig.GetConfig("version_ip", "139.159.176.119");
		let version_port = ALittleIDE.g_IDEServerConfig.GetConfig("version_port", 1011);
		this._version_manager = ALittle.NewObject(AUIPlugin.AUIVersionManager, version_ip, version_port, "alittle", "ALittleIDE");
	},
	Shutdown : function() {
	},
	HandleFileMenuClick : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("新建", ALittleIDE.g_IDEProjectNewDialog.ShowNewProject.bind(ALittleIDE.g_IDEProjectNewDialog));
		menu.AddItem("打开", ALittleIDE.g_IDEProjectOpenDialog.ShowOpenProject.bind(ALittleIDE.g_IDEProjectOpenDialog));
		menu.AddItem("设置", ALittleIDE.g_IDEProjectSettingDialog.ShowSettingProject.bind(ALittleIDE.g_IDEProjectSettingDialog));
		menu.AddItem("保存", ALittleIDE.g_IDECenter.center.content_edit.SaveAllTab.bind(ALittleIDE.g_IDECenter.center.content_edit));
		menu.AddItem("刷新", ALittleIDE.g_IDECenter.center.project_list.RefreshProject.bind(ALittleIDE.g_IDECenter.center.project_list));
		menu.AddItem("导出项目", ALittleIDE.g_IDEProjectExportDialog.ShowExportProject.bind(ALittleIDE.g_IDEProjectExportDialog));
		menu.Show(event.target);
	},
	HandleEditMenuClick : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("新建控件", ALittleIDE.g_IDECenter.center.control_list.ShowNewControl.bind(ALittleIDE.g_IDECenter.center.control_list));
		menu.AddItem("重做", ALittleIDE.g_IDECenter.center.HandleDoRevoke.bind(ALittleIDE.g_IDECenter.center, undefined));
		menu.AddItem("撤销", ALittleIDE.g_IDECenter.center.HandleUndoRevoke.bind(ALittleIDE.g_IDECenter.center, undefined));
		menu.Show(event.target);
	},
	HandleToolMenuClick : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("生成ui_all_in_one", this.HandleGenUIAllInOneClick.bind(this));
		menu.AddItem("生成core_all_in_one", this.HandleGenCoreAllInOneClick.bind(this));
		menu.AddItem("生成std_all_in_one", this.HandleGenStdAllInOneClick.bind(this));
		menu.AddItem("生成cengine_all_in_one", this.HandleGenCEngineAllInOneClick.bind(this));
		menu.Show(event.target);
	},
	HandleVersionMenuClick : function(event) {
	},
	HandleRunMenuClick : function(event) {
		ALittleIDE.g_IDEProject.RunProject();
	},
	HandleGenUIAllInOneClick : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("提示", "没有加载项目");
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
		ALittle.File_MakeDeepDir("Module/" + ALittleIDE.g_IDEProject.project.name + "/JSUI");
		let result = ALittle.File_WriteJsonFromStdFile(all_in_one, "Module/" + ALittleIDE.g_IDEProject.project.name + "/JSUI/ui_all_in_one.json");
		if (result) {
			g_AUITool.ShowNotice("提示", "生成成功");
		} else {
			g_AUITool.ShowNotice("提示", "生成失败");
		}
	},
	HandleGenCoreAllInOneClick : function() {
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
			all_in_one[index - 1] = ALittle.File_ReadTextFromStdFile(path);
			if (all_in_one[index - 1] === undefined) {
				g_AUITool.ShowNotice("提示", "生成失败");
				return;
			}
		}
		let result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/Core/JSNative/Core.js");
		if (result) {
			g_AUITool.ShowNotice("提示", "生成成功");
		} else {
			g_AUITool.ShowNotice("提示", "生成失败");
		}
	},
	HandleGenStdAllInOneClick : function() {
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
			all_in_one[index - 1] = ALittle.File_ReadTextFromStdFile(path);
			if (all_in_one[index - 1] === undefined) {
				g_AUITool.ShowNotice("提示", "生成失败");
				return;
			}
		}
		let result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/JSNative/Std.js");
		if (result) {
			g_AUITool.ShowNotice("提示", "生成成功");
		} else {
			g_AUITool.ShowNotice("提示", "生成失败");
		}
	},
	HandleGenCEngineAllInOneClick : function() {
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
			all_in_one[index - 1] = ALittle.File_ReadTextFromStdFile(path);
			if (all_in_one[index - 1] === undefined) {
				g_AUITool.ShowNotice("提示", "生成失败");
				return;
			}
		}
		let result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/JSNative/CEngine.js");
		if (result) {
			g_AUITool.ShowNotice("提示", "生成成功");
		} else {
			g_AUITool.ShowNotice("提示", "生成失败");
		}
	},
}, "ALittleIDE.IDEUIMainMenu");

}