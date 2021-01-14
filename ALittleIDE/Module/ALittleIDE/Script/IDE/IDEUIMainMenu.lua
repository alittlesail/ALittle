-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.Linear, " extends class:ALittle.Linear is nil")
ALittleIDE.IDEUIMainMenu = Lua.Class(ALittle.Linear, "ALittleIDE.IDEUIMainMenu")

function ALittleIDE.IDEUIMainMenu:TCtor()
	local group = {}
	for index, child in ___ipairs(self._childs) do
		child.group = group
	end
	local version_ip = ALittleIDE.g_IDEServerConfig:GetConfig("version_ip", "139.159.176.119")
	local version_port = ALittleIDE.g_IDEServerConfig:GetConfig("version_port", 1100)
	self._version_manager = AUIPlugin.AUIVersionManager(version_ip, version_port, "alittle", "ALittleIDE")
	if not ALittleIDE.g_Control.crypt_mode then
		self._version_manager:CheckVersionUpdate()
	end
end

function ALittleIDE.IDEUIMainMenu:Shutdown()
	self._version_manager:Shutdown()
end

function ALittleIDE.IDEUIMainMenu:HandleMenuHide(button)
	button.selected = false
end

function ALittleIDE.IDEUIMainMenu:HandleFileMenuClick(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("新建", Lua.Bind(ALittleIDE.g_IDEProjectNewDialog.ShowNewProject, ALittleIDE.g_IDEProjectNewDialog))
	menu:AddItem("打开", Lua.Bind(ALittleIDE.g_IDEProjectOpenDialog.ShowOpenProject, ALittleIDE.g_IDEProjectOpenDialog))
	menu:AddItem("设置", Lua.Bind(ALittleIDE.g_IDEProjectSettingDialog.ShowSettingProject, ALittleIDE.g_IDEProjectSettingDialog))
	menu:AddItem("保存", Lua.Bind(ALittleIDE.g_IDECenter.center.content_edit.SaveAllTab, ALittleIDE.g_IDECenter.center.content_edit))
	menu:AddItem("刷新", Lua.Bind(ALittleIDE.g_IDECenter.RefreshProject, ALittleIDE.g_IDECenter))
	menu:AddItem("导出项目", Lua.Bind(ALittleIDE.g_IDEProjectExportDialog.ShowExportProject, ALittleIDE.g_IDEProjectExportDialog))
	menu:Show(event.target, Lua.Bind(self.HandleMenuHide, self, event.target))
end

function ALittleIDE.IDEUIMainMenu:HandleEditMenuClick(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("新建控件", Lua.Bind(ALittleIDE.g_IDECenter.center.control_list.ShowNewControl, ALittleIDE.g_IDECenter.center.control_list, nil))
	menu:AddItem("重做", Lua.Bind(ALittleIDE.g_IDECenter.center.HandleDoRevoke, ALittleIDE.g_IDECenter.center, nil))
	menu:AddItem("撤销", Lua.Bind(ALittleIDE.g_IDECenter.center.HandleUndoRevoke, ALittleIDE.g_IDECenter.center, nil))
	menu:Show(event.target, Lua.Bind(self.HandleMenuHide, self, event.target))
end

function ALittleIDE.IDEUIMainMenu:HandleToolMenuClick(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("生成core_all_in_one", Lua.Bind(self.HandleGenCoreAllInOneClick, self))
	menu:AddItem("生成std_all_in_one", Lua.Bind(self.HandleGenStdAllInOneClick, self))
	menu:AddItem("生成cengine_all_in_one", Lua.Bind(self.HandleGenCEngineAllInOneClick, self))
	menu:Show(event.target, Lua.Bind(self.HandleMenuHide, self, event.target))
end

function ALittleIDE.IDEUIMainMenu:HandleHelpMenuClick(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("版本检查", Lua.Bind(self._version_manager.ShowDialog, self._version_manager))
	menu:Show(event.target, Lua.Bind(self.HandleMenuHide, self, event.target))
end

function ALittleIDE.IDEUIMainMenu:HandleRunMenuClick(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("启动(F6)", Lua.Bind(ALittleIDE.g_IDEProject.RunProject, ALittleIDE.g_IDEProject, false))
	if not ALittleIDE.g_IDEProject:IsDebug() then
		menu:AddItem("开始调试(F5)", Lua.Bind(ALittleIDE.g_IDEProject.StartDebugProject, ALittleIDE.g_IDEProject))
	else
		menu:AddItem("继续(F5)", Lua.Bind(ALittleIDE.g_IDEProject.StartDebugProject, ALittleIDE.g_IDEProject))
	end
	if ALittleIDE.g_IDEProject:IsDebug() then
		menu:AddItem("下一行(F10)", Lua.Bind(ALittleIDE.g_IDEProject.NextLineDebug, ALittleIDE.g_IDEProject))
	end
	if ALittleIDE.g_IDEProject:IsDebug() then
		menu:AddItem("停止调试", Lua.Bind(ALittleIDE.g_IDEProject.StopDebugProject, ALittleIDE.g_IDEProject))
	end
	menu:Show(event.target, Lua.Bind(self.HandleMenuHide, self, event.target))
end

function ALittleIDE.IDEUIMainMenu:HandleGenCoreAllInOneClick()
	do
		local all_in_one = {}
		local base_path = "Module/ALittleIDE/Other/GameLibrary/Core/JSScript/"
		local file_list = {}
		ALittle.List_Push(file_list, base_path .. "ALittle.js")
		ALittle.List_Push(file_list, base_path .. "Core/Base.js")
		ALittle.List_Push(file_list, base_path .. "Core/Reflect.js")
		ALittle.List_Push(file_list, base_path .. "Core/JavaScript.js")
		ALittle.List_Push(file_list, base_path .. "Core/Log.js")
		ALittle.List_Push(file_list, base_path .. "Core/List.js")
		ALittle.List_Push(file_list, base_path .. "Core/Map.js")
		ALittle.List_Push(file_list, base_path .. "Core/Math.js")
		ALittle.List_Push(file_list, base_path .. "Core/String.js")
		ALittle.List_Push(file_list, base_path .. "Core/Time.js")
		ALittle.List_Push(file_list, base_path .. "Core/Coroutine.js")
		ALittle.List_Push(file_list, base_path .. "Core/Net.js")
		ALittle.List_Push(file_list, base_path .. "Core/Worker.js")
		for index, path in ___ipairs(file_list) do
			all_in_one[index] = ALittle.File_ReadTextFromStdFile(path)
			if all_in_one[index] == nil then
				g_AUITool:ShowNotice("提示", "生成失败:" .. path)
				return
			end
		end
		local result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/Core/JSNative/Core.js")
		if not result then
			g_AUITool:ShowNotice("提示", "生成失败")
			return
		end
	end
	do
		local all_in_one = {}
		local base_path = "Module/ALittleIDE/Other/GameLibrary/Core/Script/"
		local file_list = {}
		ALittle.List_Push(file_list, base_path .. "ALittle.lua")
		ALittle.List_Push(file_list, base_path .. "Core/Base.lua")
		ALittle.List_Push(file_list, base_path .. "Core/Reflect.lua")
		ALittle.List_Push(file_list, base_path .. "Core/Lua.lua")
		ALittle.List_Push(file_list, base_path .. "Core/Log.lua")
		ALittle.List_Push(file_list, base_path .. "Core/List.lua")
		ALittle.List_Push(file_list, base_path .. "Core/Map.lua")
		ALittle.List_Push(file_list, base_path .. "Core/Math.lua")
		ALittle.List_Push(file_list, base_path .. "Core/String.lua")
		ALittle.List_Push(file_list, base_path .. "Core/Time.lua")
		ALittle.List_Push(file_list, base_path .. "Core/Coroutine.lua")
		ALittle.List_Push(file_list, base_path .. "Core/Net.lua")
		ALittle.List_Push(file_list, base_path .. "Core/Worker.lua")
		for index, path in ___ipairs(file_list) do
			all_in_one[index] = ALittle.File_ReadTextFromStdFile(path)
			if all_in_one[index] == nil then
				g_AUITool:ShowNotice("提示", "生成失败:" .. path)
				return
			end
		end
		local result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/Core/LuaNative/Core.lua")
		if not result then
			g_AUITool:ShowNotice("提示", "生成失败")
			return
		end
	end
	g_AUITool:ShowNotice("提示", "生成成功")
end

function ALittleIDE.IDEUIMainMenu:HandleGenStdAllInOneClick()
	do
		local all_in_one = {}
		local base_path = "Module/ALittleIDE/Other/GameLibrary/Std/JSScript/"
		local file_list = {}
		ALittle.List_Push(file_list, base_path .. "ALittle.js")
		ALittle.List_Push(file_list, base_path .. "Cmd/ReflectCmd.js")
		ALittle.List_Push(file_list, base_path .. "Config/ReflectCsv.js")
		ALittle.List_Push(file_list, base_path .. "Net/ReflectMessage.js")
		ALittle.List_Push(file_list, base_path .. "Loop/LoopObject.js")
		ALittle.List_Push(file_list, base_path .. "Loop/ILoopSystem.js")
		ALittle.List_Push(file_list, base_path .. "Loop/LoopFrame.js")
		ALittle.List_Push(file_list, base_path .. "Loop/LoopFunction.js")
		ALittle.List_Push(file_list, base_path .. "Loop/LoopGroup.js")
		ALittle.List_Push(file_list, base_path .. "Loop/LoopList.js")
		ALittle.List_Push(file_list, base_path .. "Loop/LoopTimer.js")
		ALittle.List_Push(file_list, base_path .. "Config/CsvConfig.js")
		ALittle.List_Push(file_list, base_path .. "Config/JsonConfig.js")
		ALittle.List_Push(file_list, base_path .. "WeakRef/WeakRef.js")
		ALittle.List_Push(file_list, base_path .. "Loop/IHeapTimer.js")
		ALittle.List_Push(file_list, base_path .. "Schedule/ISchedule.js")
		ALittle.List_Push(file_list, base_path .. "Utility/EventDispatcher.js")
		ALittle.List_Push(file_list, base_path .. "Utility/SafeIDCreator.js")
		ALittle.List_Push(file_list, base_path .. "String/String.js")
		ALittle.List_Push(file_list, base_path .. "File/File.js")
		ALittle.List_Push(file_list, base_path .. "Worker/Worker.js")
		ALittle.List_Push(file_list, base_path .. "Net/HttpFileReceiverTemplate.js")
		ALittle.List_Push(file_list, base_path .. "Net/HttpFileSenderTemplate.js")
		ALittle.List_Push(file_list, base_path .. "Net/HttpReceiverTemplate.js")
		ALittle.List_Push(file_list, base_path .. "Net/HttpSenderTemplate.js")
		ALittle.List_Push(file_list, base_path .. "Net/MsgCommonTemplate.js")
		ALittle.List_Push(file_list, base_path .. "Net/MsgReceiverTemplate.js")
		ALittle.List_Push(file_list, base_path .. "Net/MsgSenderTemplate.js")
		ALittle.List_Push(file_list, base_path .. "Net/MsgSessionTemplate.js")
		ALittle.List_Push(file_list, base_path .. "Loop/JavaScript/JHeapTimer.js")
		ALittle.List_Push(file_list, base_path .. "File/JavaScript/JFileSystem.js")
		ALittle.List_Push(file_list, base_path .. "Net/JavaScript/JHttpFileInterface.js")
		ALittle.List_Push(file_list, base_path .. "Net/JavaScript/JHttpFileWxInterface.js")
		ALittle.List_Push(file_list, base_path .. "Net/JavaScript/JHttpInterface.js")
		ALittle.List_Push(file_list, base_path .. "Net/JavaScript/JHttpWxInterface.js")
		ALittle.List_Push(file_list, base_path .. "Net/JavaScript/JMessageFactory.js")
		ALittle.List_Push(file_list, base_path .. "Net/JavaScript/JMsgInterface.js")
		ALittle.List_Push(file_list, base_path .. "Schedule/JavaScript/JSchedule.js")
		ALittle.List_Push(file_list, base_path .. "Config/JavaScript/JCsvFile.js")
		ALittle.List_Push(file_list, base_path .. "Loop/LoopSystem.js")
		ALittle.List_Push(file_list, base_path .. "Schedule/Schedule.js")
		for index, path in ___ipairs(file_list) do
			all_in_one[index] = ALittle.File_ReadTextFromStdFile(path)
			if all_in_one[index] == nil then
				g_AUITool:ShowNotice("提示", "生成失败! 文件加载失败:" .. path)
				return
			end
		end
		local result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/Std/JSNative/Std.js")
		if not result then
			g_AUITool:ShowNotice("提示", "生成失败")
			return
		end
	end
	do
		local all_in_one = {}
		local base_path = "Module/ALittleIDE/Other/GameLibrary/Std/Script/"
		local file_list = {}
		ALittle.List_Push(file_list, base_path .. "ALittle.lua")
		ALittle.List_Push(file_list, base_path .. "Cmd/ReflectCmd.lua")
		ALittle.List_Push(file_list, base_path .. "Config/ReflectCsv.lua")
		ALittle.List_Push(file_list, base_path .. "Net/ReflectMessage.lua")
		ALittle.List_Push(file_list, base_path .. "Loop/LoopObject.lua")
		ALittle.List_Push(file_list, base_path .. "Loop/ILoopSystem.lua")
		ALittle.List_Push(file_list, base_path .. "Loop/LoopFrame.lua")
		ALittle.List_Push(file_list, base_path .. "Loop/LoopFunction.lua")
		ALittle.List_Push(file_list, base_path .. "Loop/LoopGroup.lua")
		ALittle.List_Push(file_list, base_path .. "Loop/LoopList.lua")
		ALittle.List_Push(file_list, base_path .. "Loop/LoopTimer.lua")
		ALittle.List_Push(file_list, base_path .. "Config/CsvConfig.lua")
		ALittle.List_Push(file_list, base_path .. "Config/JsonConfig.lua")
		ALittle.List_Push(file_list, base_path .. "WeakRef/WeakRef.lua")
		ALittle.List_Push(file_list, base_path .. "Loop/IHeapTimer.lua")
		ALittle.List_Push(file_list, base_path .. "Schedule/ISchedule.lua")
		ALittle.List_Push(file_list, base_path .. "Utility/EventDispatcher.lua")
		ALittle.List_Push(file_list, base_path .. "Utility/SafeIDCreator.lua")
		ALittle.List_Push(file_list, base_path .. "String/String.lua")
		ALittle.List_Push(file_list, base_path .. "File/File.lua")
		ALittle.List_Push(file_list, base_path .. "Worker/Worker.lua")
		ALittle.List_Push(file_list, base_path .. "Net/HttpFileReceiverTemplate.lua")
		ALittle.List_Push(file_list, base_path .. "Net/HttpFileSenderTemplate.lua")
		ALittle.List_Push(file_list, base_path .. "Net/HttpReceiverTemplate.lua")
		ALittle.List_Push(file_list, base_path .. "Net/HttpSenderTemplate.lua")
		ALittle.List_Push(file_list, base_path .. "Net/MsgCommonTemplate.lua")
		ALittle.List_Push(file_list, base_path .. "Net/MsgReceiverTemplate.lua")
		ALittle.List_Push(file_list, base_path .. "Net/MsgSenderTemplate.lua")
		ALittle.List_Push(file_list, base_path .. "Net/MsgSessionTemplate.lua")
		ALittle.List_Push(file_list, base_path .. "Loop/IHeapTimer.lua")
		ALittle.List_Push(file_list, base_path .. "Config/Lua/LuaCsvFile.lua")
		ALittle.List_Push(file_list, base_path .. "Net/Lua/LuaHttpFileInterface.lua")
		ALittle.List_Push(file_list, base_path .. "Net/Lua/LuaHttpInterface.lua")
		ALittle.List_Push(file_list, base_path .. "Net/Lua/LuaMsgInterface.lua")
		ALittle.List_Push(file_list, base_path .. "Schedule/Lua/LuaSchedule.lua")
		ALittle.List_Push(file_list, base_path .. "Loop/LoopSystem.lua")
		ALittle.List_Push(file_list, base_path .. "Schedule/Schedule.lua")
		for index, path in ___ipairs(file_list) do
			all_in_one[index] = ALittle.File_ReadTextFromStdFile(path)
			if all_in_one[index] == nil then
				g_AUITool:ShowNotice("提示", "生成失败! 文件加载失败:" .. path)
				return
			end
		end
		local result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/Std/LuaNative/Std.lua")
		if not result then
			g_AUITool:ShowNotice("提示", "生成失败")
			return
		end
	end
	g_AUITool:ShowNotice("提示", "生成成功")
end

function ALittleIDE.IDEUIMainMenu:HandleGenCEngineAllInOneClick()
	local base_path = "Module/ALittleIDE/Other/GameLibrary/CEngine/JSScript/"
	local file_list = {}
	ALittle.List_Push(file_list, base_path .. "ALittle.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/IShow.js")
	ALittle.List_Push(file_list, base_path .. "Adapter/PIXI/JSystem.js")
	ALittle.List_Push(file_list, base_path .. "Adapter/PIXI/JShow.js")
	ALittle.List_Push(file_list, base_path .. "Adapter/PIXI/JCsvLoader.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/Utility/String.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/Utility/File.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/Utility/System.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/Utility/ConfigSystem.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/Utility/OtherSystem.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/Utility/AudioSystem.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/Utility/ModuleSystem.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/Utility/CsvConfigManager.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/Utility/Revocation.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/Utility/Debug.js")
	ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path .. "CEngine/LoopSystem/"))
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/UIEnumTypes.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/UIEventDispatcher.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Base/Matrix2D.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Base/DisplayObject.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Base/DisplayGroup.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Base/DisplayLayout.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Base/DisplayView.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Base/Quad.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Base/Image.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Base/Sprite.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Base/Text.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Base/TextArea.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Base/TextEdit.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Base/TextInput.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Base/Triangle.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Base/VertexImage.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/Grid9Image.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/TextButton.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/TextCheckButton.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/TextRadioButton.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/Grid3.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/Grid9.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/Linear.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/Tab.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/DropDown.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/Slider.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/ScrollBar.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/ScrollScreen.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/Dialog.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/TileTable.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/ImagePlay.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/SpritePlay.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/SpriteNumber.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/FramePlay.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/Piechart.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/ImageInput.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/ImageEdit.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/RichArea.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/RichEdit.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/RichInput.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/ScrollList.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/Complex/ScrollButton.js")
	ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path .. "CEngine/UISystem/Special/"))
	ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path .. "CEngine/UISystem/Plugin/"))
	ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path .. "CEngine/UISystem/Effect/"))
	ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path .. "CEngine/UISystem/Tile/"))
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/UISystem.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/LayerManager.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/TextureManager.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/ControlSystem.js")
	local file_index = 1
	local file_size = 0
	local list_index = 1
	local all_in_one = nil
	for index, path in ___ipairs(file_list) do
		local content = ALittle.File_ReadTextFromStdFile(path)
		if content == nil then
			g_AUITool:ShowNotice("提示", "生成失败")
			return
		end
		local len = ALittle.String_Len(content)
		if file_size + len >= 500 * 1024 then
			if all_in_one ~= nil then
				local result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/CEngine/JSNative/CEngine" .. file_index .. ".js")
				if not result then
					g_AUITool:ShowNotice("提示", "生成失败")
					return
				end
			end
			all_in_one = nil
			list_index = 1
			file_size = 0
			file_index = file_index + 1
		end
		if file_size + len < 500 * 1024 then
			file_size = file_size + (len)
			if all_in_one == nil then
				all_in_one = {}
			end
			all_in_one[list_index] = content
			list_index = list_index + 1
		end
	end
	if all_in_one ~= nil then
		local result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/CEngine/JSNative/CEngine" .. file_index .. ".js")
		if not result then
			g_AUITool:ShowNotice("提示", "生成失败")
			return
		end
	end
	g_AUITool:ShowNotice("提示", "生成成功")
end

end