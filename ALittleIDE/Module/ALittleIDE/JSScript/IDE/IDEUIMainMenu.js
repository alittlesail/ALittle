{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittle.Linear === undefined) throw new Error(" extends class:ALittle.Linear is undefined");
ALittleIDE.IDEUIMainMenu = JavaScript.Class(ALittle.Linear, {
	TCtor : function() {
		let group = new Map();
		let ___OBJECT_1 = this._childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			child.group = group;
		}
		let version_ip = ALittleIDE.g_IDEServerConfig.GetConfig("version_ip", "139.159.176.119");
		let version_port = ALittleIDE.g_IDEServerConfig.GetConfig("version_port", 1100);
		this._version_manager = ALittle.NewObject(AUIPlugin.AUIVersionManager, version_ip, version_port, "alittle", "ALittleIDE");
	},
	Shutdown : function() {
	},
	HandleMenuHide : function(button) {
		button.selected = false;
	},
	HandleFileMenuClick : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("新建", ALittleIDE.g_IDEProjectNewDialog.ShowNewProject.bind(ALittleIDE.g_IDEProjectNewDialog));
		menu.AddItem("打开", ALittleIDE.g_IDEProjectOpenDialog.ShowOpenProject.bind(ALittleIDE.g_IDEProjectOpenDialog));
		menu.AddItem("设置", ALittleIDE.g_IDEProjectSettingDialog.ShowSettingProject.bind(ALittleIDE.g_IDEProjectSettingDialog));
		menu.AddItem("保存", ALittleIDE.g_IDECenter.center.content_edit.SaveAllTab.bind(ALittleIDE.g_IDECenter.center.content_edit));
		menu.AddItem("刷新", ALittleIDE.g_IDECenter.RefreshProject.bind(ALittleIDE.g_IDECenter));
		menu.AddItem("导出项目", ALittleIDE.g_IDEProjectExportDialog.ShowExportProject.bind(ALittleIDE.g_IDEProjectExportDialog));
		menu.Show(event.target, this.HandleMenuHide.bind(this, event.target));
	},
	HandleEditMenuClick : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("新建控件", ALittleIDE.g_IDECenter.center.control_list.ShowNewControl.bind(ALittleIDE.g_IDECenter.center.control_list, undefined));
		menu.AddItem("重做", ALittleIDE.g_IDECenter.center.HandleDoRevoke.bind(ALittleIDE.g_IDECenter.center, undefined));
		menu.AddItem("撤销", ALittleIDE.g_IDECenter.center.HandleUndoRevoke.bind(ALittleIDE.g_IDECenter.center, undefined));
		menu.Show(event.target, this.HandleMenuHide.bind(this, event.target));
	},
	HandleToolMenuClick : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("生成core_all_in_one", this.HandleGenCoreAllInOneClick.bind(this));
		menu.AddItem("生成std_all_in_one", this.HandleGenStdAllInOneClick.bind(this));
		menu.AddItem("生成cengine_all_in_one", this.HandleGenCEngineAllInOneClick.bind(this));
		menu.Show(event.target, this.HandleMenuHide.bind(this, event.target));
	},
	HandleHelpMenuClick : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.Show(event.target, this.HandleMenuHide.bind(this, event.target));
	},
	HandleRunMenuClick : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.Show(event.target, this.HandleMenuHide.bind(this, event.target));
	},
	HandleGenCoreAllInOneClick : function() {
		{
			let all_in_one = [];
			let base_path = "Module/ALittleIDE/Other/GameLibrary/Core/JSScript/";
			let file_list = [];
			ALittle.List_Push(file_list, base_path + "ALittle.js");
			ALittle.List_Push(file_list, base_path + "Core/Base.js");
			ALittle.List_Push(file_list, base_path + "Core/Reflect.js");
			ALittle.List_Push(file_list, base_path + "Core/JavaScript.js");
			ALittle.List_Push(file_list, base_path + "Core/Log.js");
			ALittle.List_Push(file_list, base_path + "Core/List.js");
			ALittle.List_Push(file_list, base_path + "Core/Map.js");
			ALittle.List_Push(file_list, base_path + "Core/Math.js");
			ALittle.List_Push(file_list, base_path + "Core/String.js");
			ALittle.List_Push(file_list, base_path + "Core/Time.js");
			ALittle.List_Push(file_list, base_path + "Core/Coroutine.js");
			ALittle.List_Push(file_list, base_path + "Core/Net.js");
			ALittle.List_Push(file_list, base_path + "Core/Worker.js");
			let ___OBJECT_2 = file_list;
			for (let index = 1; index <= ___OBJECT_2.length; ++index) {
				let path = ___OBJECT_2[index - 1];
				if (path === undefined) break;
				all_in_one[index - 1] = ALittle.File_ReadTextFromStdFile(path);
				if (all_in_one[index - 1] === undefined) {
					g_AUITool.ShowNotice("提示", "生成失败:" + path);
					return;
				}
			}
			let result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/Core/JSNative/Core.js");
			if (!result) {
				g_AUITool.ShowNotice("提示", "生成失败");
				return;
			}
		}
		{
			let all_in_one = [];
			let base_path = "Module/ALittleIDE/Other/GameLibrary/Core/Script/";
			let file_list = [];
			ALittle.List_Push(file_list, base_path + "ALittle.lua");
			ALittle.List_Push(file_list, base_path + "Core/Base.lua");
			ALittle.List_Push(file_list, base_path + "Core/Reflect.lua");
			ALittle.List_Push(file_list, base_path + "Core/Lua.lua");
			ALittle.List_Push(file_list, base_path + "Core/Log.lua");
			ALittle.List_Push(file_list, base_path + "Core/List.lua");
			ALittle.List_Push(file_list, base_path + "Core/Map.lua");
			ALittle.List_Push(file_list, base_path + "Core/Math.lua");
			ALittle.List_Push(file_list, base_path + "Core/String.lua");
			ALittle.List_Push(file_list, base_path + "Core/Time.lua");
			ALittle.List_Push(file_list, base_path + "Core/Coroutine.lua");
			ALittle.List_Push(file_list, base_path + "Core/Net.lua");
			ALittle.List_Push(file_list, base_path + "Core/Worker.lua");
			let ___OBJECT_3 = file_list;
			for (let index = 1; index <= ___OBJECT_3.length; ++index) {
				let path = ___OBJECT_3[index - 1];
				if (path === undefined) break;
				all_in_one[index - 1] = ALittle.File_ReadTextFromStdFile(path);
				if (all_in_one[index - 1] === undefined) {
					g_AUITool.ShowNotice("提示", "生成失败:" + path);
					return;
				}
			}
			let result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/Core/LuaNative/Core.lua");
			if (!result) {
				g_AUITool.ShowNotice("提示", "生成失败");
				return;
			}
		}
		g_AUITool.ShowNotice("提示", "生成成功");
	},
	HandleGenStdAllInOneClick : function() {
		{
			let all_in_one = [];
			let base_path = "Module/ALittleIDE/Other/GameLibrary/Std/JSScript/";
			let file_list = [];
			ALittle.List_Push(file_list, base_path + "ALittle.js");
			ALittle.List_Push(file_list, base_path + "Cmd/ReflectCmd.js");
			ALittle.List_Push(file_list, base_path + "Config/ReflectCsv.js");
			ALittle.List_Push(file_list, base_path + "Net/ReflectMessage.js");
			ALittle.List_Push(file_list, base_path + "Loop/LoopObject.js");
			ALittle.List_Push(file_list, base_path + "Loop/ILoopSystem.js");
			ALittle.List_Push(file_list, base_path + "Loop/LoopFrame.js");
			ALittle.List_Push(file_list, base_path + "Loop/LoopFunction.js");
			ALittle.List_Push(file_list, base_path + "Loop/LoopGroup.js");
			ALittle.List_Push(file_list, base_path + "Loop/LoopList.js");
			ALittle.List_Push(file_list, base_path + "Loop/LoopTimer.js");
			ALittle.List_Push(file_list, base_path + "Config/CsvConfig.js");
			ALittle.List_Push(file_list, base_path + "Config/JsonConfig.js");
			ALittle.List_Push(file_list, base_path + "WeakRef/WeakRef.js");
			ALittle.List_Push(file_list, base_path + "Loop/IHeapTimer.js");
			ALittle.List_Push(file_list, base_path + "Schedule/ISchedule.js");
			ALittle.List_Push(file_list, base_path + "Utility/EventDispatcher.js");
			ALittle.List_Push(file_list, base_path + "Utility/SafeIDCreator.js");
			ALittle.List_Push(file_list, base_path + "String/String.js");
			ALittle.List_Push(file_list, base_path + "File/File.js");
			ALittle.List_Push(file_list, base_path + "Worker/Worker.js");
			ALittle.List_Push(file_list, base_path + "Net/HttpFileReceiverTemplate.js");
			ALittle.List_Push(file_list, base_path + "Net/HttpFileSenderTemplate.js");
			ALittle.List_Push(file_list, base_path + "Net/HttpReceiverTemplate.js");
			ALittle.List_Push(file_list, base_path + "Net/HttpSenderTemplate.js");
			ALittle.List_Push(file_list, base_path + "Net/MsgCommonTemplate.js");
			ALittle.List_Push(file_list, base_path + "Net/MsgReceiverTemplate.js");
			ALittle.List_Push(file_list, base_path + "Net/MsgSenderTemplate.js");
			ALittle.List_Push(file_list, base_path + "Net/MsgSessionTemplate.js");
			ALittle.List_Push(file_list, base_path + "Loop/JavaScript/JHeapTimer.js");
			ALittle.List_Push(file_list, base_path + "File/JavaScript/JFileSystem.js");
			ALittle.List_Push(file_list, base_path + "Net/JavaScript/JHttpFileInterface.js");
			ALittle.List_Push(file_list, base_path + "Net/JavaScript/JHttpFileWxInterface.js");
			ALittle.List_Push(file_list, base_path + "Net/JavaScript/JHttpInterface.js");
			ALittle.List_Push(file_list, base_path + "Net/JavaScript/JHttpWxInterface.js");
			ALittle.List_Push(file_list, base_path + "Net/JavaScript/JMessageFactory.js");
			ALittle.List_Push(file_list, base_path + "Net/JavaScript/JMsgInterface.js");
			ALittle.List_Push(file_list, base_path + "Schedule/JavaScript/JSchedule.js");
			ALittle.List_Push(file_list, base_path + "Config/JavaScript/JCsvFile.js");
			ALittle.List_Push(file_list, base_path + "Loop/LoopSystem.js");
			ALittle.List_Push(file_list, base_path + "Schedule/Schedule.js");
			let ___OBJECT_4 = file_list;
			for (let index = 1; index <= ___OBJECT_4.length; ++index) {
				let path = ___OBJECT_4[index - 1];
				if (path === undefined) break;
				all_in_one[index - 1] = ALittle.File_ReadTextFromStdFile(path);
				if (all_in_one[index - 1] === undefined) {
					g_AUITool.ShowNotice("提示", "生成失败! 文件加载失败:" + path);
					return;
				}
			}
			let result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/Std/JSNative/Std.js");
			if (!result) {
				g_AUITool.ShowNotice("提示", "生成失败");
				return;
			}
		}
		{
			let all_in_one = [];
			let base_path = "Module/ALittleIDE/Other/GameLibrary/Std/Script/";
			let file_list = [];
			ALittle.List_Push(file_list, base_path + "ALittle.lua");
			ALittle.List_Push(file_list, base_path + "Cmd/ReflectCmd.lua");
			ALittle.List_Push(file_list, base_path + "Config/ReflectCsv.lua");
			ALittle.List_Push(file_list, base_path + "Net/ReflectMessage.lua");
			ALittle.List_Push(file_list, base_path + "Loop/LoopObject.lua");
			ALittle.List_Push(file_list, base_path + "Loop/ILoopSystem.lua");
			ALittle.List_Push(file_list, base_path + "Loop/LoopFrame.lua");
			ALittle.List_Push(file_list, base_path + "Loop/LoopFunction.lua");
			ALittle.List_Push(file_list, base_path + "Loop/LoopGroup.lua");
			ALittle.List_Push(file_list, base_path + "Loop/LoopList.lua");
			ALittle.List_Push(file_list, base_path + "Loop/LoopTimer.lua");
			ALittle.List_Push(file_list, base_path + "Config/CsvConfig.lua");
			ALittle.List_Push(file_list, base_path + "Config/JsonConfig.lua");
			ALittle.List_Push(file_list, base_path + "WeakRef/WeakRef.lua");
			ALittle.List_Push(file_list, base_path + "Loop/IHeapTimer.lua");
			ALittle.List_Push(file_list, base_path + "Schedule/ISchedule.lua");
			ALittle.List_Push(file_list, base_path + "Utility/EventDispatcher.lua");
			ALittle.List_Push(file_list, base_path + "Utility/SafeIDCreator.lua");
			ALittle.List_Push(file_list, base_path + "String/String.lua");
			ALittle.List_Push(file_list, base_path + "File/File.lua");
			ALittle.List_Push(file_list, base_path + "Worker/Worker.lua");
			ALittle.List_Push(file_list, base_path + "Net/HttpFileReceiverTemplate.lua");
			ALittle.List_Push(file_list, base_path + "Net/HttpFileSenderTemplate.lua");
			ALittle.List_Push(file_list, base_path + "Net/HttpReceiverTemplate.lua");
			ALittle.List_Push(file_list, base_path + "Net/HttpSenderTemplate.lua");
			ALittle.List_Push(file_list, base_path + "Net/MsgCommonTemplate.lua");
			ALittle.List_Push(file_list, base_path + "Net/MsgReceiverTemplate.lua");
			ALittle.List_Push(file_list, base_path + "Net/MsgSenderTemplate.lua");
			ALittle.List_Push(file_list, base_path + "Net/MsgSessionTemplate.lua");
			ALittle.List_Push(file_list, base_path + "Loop/IHeapTimer.lua");
			ALittle.List_Push(file_list, base_path + "Config/Lua/LuaCsvFile.lua");
			ALittle.List_Push(file_list, base_path + "Net/Lua/LuaHttpFileInterface.lua");
			ALittle.List_Push(file_list, base_path + "Net/Lua/LuaHttpInterface.lua");
			ALittle.List_Push(file_list, base_path + "Net/Lua/LuaMsgInterface.lua");
			ALittle.List_Push(file_list, base_path + "Schedule/Lua/LuaSchedule.lua");
			ALittle.List_Push(file_list, base_path + "Loop/LoopSystem.lua");
			ALittle.List_Push(file_list, base_path + "Schedule/Schedule.lua");
			let ___OBJECT_5 = file_list;
			for (let index = 1; index <= ___OBJECT_5.length; ++index) {
				let path = ___OBJECT_5[index - 1];
				if (path === undefined) break;
				all_in_one[index - 1] = ALittle.File_ReadTextFromStdFile(path);
				if (all_in_one[index - 1] === undefined) {
					g_AUITool.ShowNotice("提示", "生成失败! 文件加载失败:" + path);
					return;
				}
			}
			let result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/Std/LuaNative/Std.lua");
			if (!result) {
				g_AUITool.ShowNotice("提示", "生成失败");
				return;
			}
		}
		g_AUITool.ShowNotice("提示", "生成成功");
	},
	HandleGenCEngineAllInOneClick : function() {
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
		ALittle.List_Push(file_list, base_path + "CEngine/Utility/Revocation.js");
		ALittle.List_Push(file_list, base_path + "CEngine/Utility/Debug.js");
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
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Base/VertexImage.js");
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
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/Complex/SpriteNumber.js");
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
		ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path + "CEngine/UISystem/Tile/"));
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/UISystem.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/LayerManager.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/TextureManager.js");
		ALittle.List_Push(file_list, base_path + "CEngine/UISystem/ControlSystem.js");
		let file_index = 1;
		let file_size = 0;
		let list_index = 1;
		let all_in_one = undefined;
		let ___OBJECT_6 = file_list;
		for (let index = 1; index <= ___OBJECT_6.length; ++index) {
			let path = ___OBJECT_6[index - 1];
			if (path === undefined) break;
			let content = ALittle.File_ReadTextFromStdFile(path);
			if (content === undefined) {
				g_AUITool.ShowNotice("提示", "生成失败");
				return;
			}
			let len = ALittle.String_Len(content);
			if (file_size + len >= 500 * 1024) {
				if (all_in_one !== undefined) {
					let result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/CEngine/JSNative/CEngine" + file_index + ".js");
					if (!result) {
						g_AUITool.ShowNotice("提示", "生成失败");
						return;
					}
				}
				all_in_one = undefined;
				list_index = 1;
				file_size = 0;
				++ file_index;
			}
			if (file_size + len < 500 * 1024) {
				file_size = file_size + (len);
				if (all_in_one === undefined) {
					all_in_one = [];
				}
				all_in_one[list_index - 1] = content;
				++ list_index;
			}
		}
		if (all_in_one !== undefined) {
			let result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/CEngine/JSNative/CEngine" + file_index + ".js");
			if (!result) {
				g_AUITool.ShowNotice("提示", "生成失败");
				return;
			}
		}
		g_AUITool.ShowNotice("提示", "生成成功");
	},
}, "ALittleIDE.IDEUIMainMenu");

}