-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1255897792, "ALittleIDE.IDEMainMenuImageInfo", {
name = "ALittleIDE.IDEMainMenuImageInfo", ns_name = "ALittleIDE", rl_name = "IDEMainMenuImageInfo", hash_code = 1255897792,
name_list = {"file_name","x","y","width","height"},
type_list = {"string","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1020446174, "ALittleIDE.IDEMainMenuFramePlayInfo", {
name = "ALittleIDE.IDEMainMenuFramePlayInfo", ns_name = "ALittleIDE", rl_name = "IDEMainMenuFramePlayInfo", hash_code = 1020446174,
name_list = {"width","height","root_path","image_list","image_count"},
type_list = {"double","double","string","List<ALittleIDE.IDEMainMenuImageInfo>","int"},
option_map = {}
})

IDEMainMenu = Lua.Class(nil, "ALittleIDE.IDEMainMenu")

function IDEMainMenu:ShowFileMenu(event)
	if self._menu_file_menu == nil then
		self._menu_file_menu = g_Control:CreateControl("ide_file_menu", self)
	end
	local x, y = event.target:LocalToGlobal()
	self._menu_file_menu.x = x
	self._menu_file_menu.y = y + event.target.height
	A_LayerManager:ShowFromRight(self._menu_file_menu)
end

function IDEMainMenu:HandleNewProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:ShowNewProject()
end

function IDEMainMenu:HandleOpenProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:ShowOpenProject()
end

function IDEMainMenu:HandleSettingProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:ShowSettingProject(nil)
end

function IDEMainMenu:HandleSaveProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDETabManager:SaveAllTab()
end

function IDEMainMenu:HandleRefreshProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:RefreshProject()
end

function IDEMainMenu:HandleExportProject(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:ShowExportProject()
end

function IDEMainMenu:HandleRun(event)
	A_LayerManager:HideFromRight(self._menu_file_menu)
	g_IDEProjectManager:RunProject()
end

function IDEMainMenu:ShowEditMenu(event)
	if self._menu_edit_menu == nil then
		self._menu_edit_menu = g_Control:CreateControl("ide_edit_menu", self)
	end
	local x, y = event.target:LocalToGlobal()
	self._menu_edit_menu.x = x
	self._menu_edit_menu.y = y + event.target.height
	A_LayerManager:ShowFromRight(self._menu_edit_menu)
end

function IDEMainMenu:HandleNewControl(event)
	A_LayerManager:HideFromRight(self._menu_edit_menu)
	g_IDEControlManager:ShowNewControl()
end

function IDEMainMenu:HandleUndoRevoke(event)
	A_LayerManager:HideFromRight(self._menu_edit_menu)
	g_IDEUICenter:HandleUndoRevoke(nil)
end

function IDEMainMenu:HandleDoRevoke(event)
	A_LayerManager:HideFromRight(self._menu_edit_menu)
	g_IDEUICenter:HandleDoRevoke(nil)
end

function IDEMainMenu:ShowToolMenu(event)
	if self._menu_tool_menu == nil then
		self._menu_tool_menu = g_Control:CreateControl("ide_tool_menu", self)
	end
	local x, y = event.target:LocalToGlobal()
	self._menu_tool_menu.x = x
	self._menu_tool_menu.y = y + event.target.height
	A_LayerManager:ShowFromRight(self._menu_tool_menu)
end

function IDEMainMenu:HandleGenUIAllInOneClick(event)
	A_LayerManager:HideFromRight(self._menu_tool_menu)
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("提示", "没有加载项目")
		return
	end
	local all_in_one = {}
	local map = ALittle.File_GetFileAttrByDir("Module/" .. g_IDEProject.project.name .. "/UI")
	for path, _ in ___pairs(map) do
		local json = ALittle.File_ReadJsonFromStdFile(path)
		for name, o in ___pairs(json) do
			all_in_one[name] = o
		end
	end
	local result = ALittle.File_WriteJsonFromStdFile(all_in_one, "Module/" .. g_IDEProject.project.name .. "/ui_all_in_one.json")
	if result then
		g_IDETool:ShowNotice("提示", "生成成功")
	else
		g_IDETool:ShowNotice("提示", "生成失败")
	end
end

function IDEMainMenu:HandleGenCoreAllInOneClick(event)
	A_LayerManager:HideFromRight(self._menu_tool_menu)
	local all_in_one = {}
	local base_path = "Module/ALittleIDE/Other/GameLibrary/Core/JSScript/"
	local file_list = {}
	ALittle.List_Push(file_list, base_path .. "ALittle.js")
	ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path .. "Core/JavaScript/"))
	ALittle.List_Push(file_list, base_path .. "Core/Reflect/ReflectRegister.js")
	ALittle.List_Push(file_list, base_path .. "Core/Reflect/ReflectDefine.js")
	ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path .. "Core/Utility/"))
	ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path .. "Core/Net/"))
	for index, path in ___ipairs(file_list) do
		local error = nil
		error, all_in_one[index] = ALittle.File_ReadTextFromStdFile(path)
		if error ~= nil then
			g_IDETool:ShowNotice("提示", "生成失败:" .. error)
			return
		end
	end
	local result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/Core/Core.js")
	if result then
		g_IDETool:ShowNotice("提示", "生成成功")
	else
		g_IDETool:ShowNotice("提示", "生成失败")
	end
end

function IDEMainMenu:HandleGenStdAllInOneClick(event)
	A_LayerManager:HideFromRight(self._menu_tool_menu)
	local all_in_one = {}
	local base_path = "Module/ALittleIDE/Other/GameLibrary/Std/JSScript/"
	local file_list = {}
	ALittle.List_Push(file_list, base_path .. "ALittle.js")
	ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path .. "Std/Reflect/"))
	ALittle.List_Push(file_list, base_path .. "Std/Loop/LoopObject.js")
	ALittle.List_Push(file_list, base_path .. "Std/Loop/ILoopSystem.js")
	ALittle.List_Push(file_list, base_path .. "Std/Loop/LoopFrame.js")
	ALittle.List_Push(file_list, base_path .. "Std/Loop/LoopFunction.js")
	ALittle.List_Push(file_list, base_path .. "Std/Loop/LoopGroup.js")
	ALittle.List_Push(file_list, base_path .. "Std/Loop/LoopList.js")
	ALittle.List_Push(file_list, base_path .. "Std/Loop/LoopTimer.js")
	ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path .. "Std/Utility/"))
	ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path .. "Std/Net/"))
	ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path .. "Adapter/JavaScript/"))
	ALittle.List_PushList(file_list, ALittle.File_GetFileListByDir(base_path .. "Std/Singleton/"))
	for index, path in ___ipairs(file_list) do
		local error = nil
		error, all_in_one[index] = ALittle.File_ReadTextFromStdFile(path)
		if error ~= nil then
			g_IDETool:ShowNotice("提示", "生成失败:" .. error)
			return
		end
	end
	local result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/Std/Std.js")
	if result then
		g_IDETool:ShowNotice("提示", "生成成功")
	else
		g_IDETool:ShowNotice("提示", "生成失败")
	end
end

function IDEMainMenu:HandleGenCEngineAllInOneClick(event)
	A_LayerManager:HideFromRight(self._menu_tool_menu)
	local all_in_one = {}
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
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/UISystem.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/LayerManager.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/TextureManager.js")
	ALittle.List_Push(file_list, base_path .. "CEngine/UISystem/ControlSystem.js")
	for index, path in ___ipairs(file_list) do
		local error = nil
		error, all_in_one[index] = ALittle.File_ReadTextFromStdFile(path)
		if error ~= nil then
			g_IDETool:ShowNotice("提示", "生成失败:" .. error)
			return
		end
	end
	local result = ALittle.File_WriteTextFromStdFile(ALittle.String_Join(all_in_one, "\n"), "Module/ALittleIDE/Other/GameLibrary/CEngine/CEngine.js")
	if result then
		g_IDETool:ShowNotice("提示", "生成成功")
	else
		g_IDETool:ShowNotice("提示", "生成失败")
	end
end

function IDEMainMenu:HandleFramePlayFromPList(event)
	A_LayerManager:HideFromRight(self._menu_tool_menu)
	if self._frameplay_plist_dialog == nil then
		self._frameplay_plist_dialog = g_Control:CreateControl("ide_frameplay_plist_dialog", self, g_IDECenter.dialog_layer)
	end
	self._frameplay_plist_dialog.visible = true
end

function IDEMainMenu.ImageListInFramePlayCmp(a, b)
	return a.file_name < a.file_name
end

function IDEMainMenu:HandleViewLog(event)
	A_LayerManager:HideFromRight(self._menu_tool_menu)
	if self._view_log_dialog == nil then
		self._view_log_dialog = g_Control:CreateControl("ide_view_log_dialog", self, g_IDECenter.dialog_layer)
		self:HandleViewLogRefresh(nil)
	end
	self._view_log_dialog.visible = true
end

function IDEMainMenu:HandleViewLogRefresh(event)
	local file_name = ALittle.Time_GetCurYMD(ALittle.Time_GetCurTime()) .. ".log"
	local file_path = ALittle.File_BaseFilePath() .. "Log/" .. file_name
	local content = ALittle.File_ReadTextFromFile(file_path, false)
	if content == nil then
		return
	end
	local content_list = ALittle.String_Split(content, "\n")
	local content_len = ALittle.List_MaxN(content_list)
	local copy_len = content_len - 100
	if copy_len < 1 then
		copy_len = 1
	end
	local log_list = {}
	local log_list_count = 0
	local i = content_len
	while true do
		if not(i >= copy_len) then break end
		log_list_count = log_list_count + 1
		log_list[log_list_count] = content_list[i]
		i = i+(-1)
	end
	self._view_log_content.text = ALittle.String_Join(log_list, "\n")
end

function IDEMainMenu:HandleViewLogClose(event)
	self._view_log_dialog.visible = false
end

g_IDEMainMenu = IDEMainMenu()
