-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1821709712, "AUIPlugin.AUIFileSelectRightButtonDownEvent", {
name = "AUIPlugin.AUIFileSelectRightButtonDownEvent", ns_name = "AUIPlugin", rl_name = "AUIFileSelectRightButtonDownEvent", hash_code = 1821709712,
name_list = {"target","path","directory"},
type_list = {"ALittle.EventDispatcher","string","bool"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

assert(AUIPlugin.AUIFileSelectDialog, " extends class:AUIPlugin.AUIFileSelectDialog is nil")
ALittleIDE.IDEImageSelectDialog = Lua.Class(AUIPlugin.AUIFileSelectDialog, "ALittleIDE.IDEImageSelectDialog")

function ALittleIDE.IDEImageSelectDialog:Ctor(title, layer, ext_list)
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-332308624], self, self.HandleCloseProject)
	self:AddEventListener(___all_struct[1821709712], self, self.HandleImageSelectRButtonDown)
end

function ALittleIDE.IDEImageSelectDialog:HandleCloseProject(event)
	if self._dialog == nil then
		return
	end
	self:HideDialog()
end

function ALittleIDE.IDEImageSelectDialog:HandleImageSelectRButtonDown(event)
	local ext = ALittle.File_GetFileExtByPathAndUpper(event.path)
	if ext ~= "PNG" and ext ~= "JPG" then
		local menu = AUIPlugin.AUIRightMenu()
		menu:AddItem("删除", Lua.Bind(self.HandleImageDeleteClick, self, event))
		menu:Show()
		return
	end
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("复制九宫格代码", Lua.Bind(self.HandleImageCopyGrid9ImageCodeClick, self, event))
	menu:AddItem("复制图片代码", Lua.Bind(self.HandleImageCopyImageCodeClick, self, event))
	menu:AddItem("图片裁剪", Lua.Bind(self.HandleImageEditClick, self, event))
	menu:AddItem("删除", Lua.Bind(self.HandleImageDeleteClick, self, event))
	menu:Show()
end

function ALittleIDE.IDEImageSelectDialog:HandleImageCopyGrid9ImageCodeClick(event)
	local display_info = ALittleIDE.IDEUIUtility_GenerateGrid9ImageInfo(self.base_path .. "/", event.path)
	if display_info == nil then
		g_AUITool:ShowNotice("错误", "图片加载失败:" .. event.path)
		return
	end
	local copy_list = {}
	local info = {}
	info.index = 1
	info.info = display_info
	copy_list[1] = info
	ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
end

function ALittleIDE.IDEImageSelectDialog:HandleImageCopyImageCodeClick(event)
	local width = 100
	local height = 100
	local surface = carp.LoadCarpSurface(self.base_path .. "/" .. event.path)
	if surface ~= nil then
		width = carp.GetCarpSurfaceWidth(surface)
		height = carp.GetCarpSurfaceHeight(surface)
		carp.FreeCarpSurface(surface)
	end
	local display_info = {}
	display_info.__class = "Image"
	display_info.texture_name = event.path
	display_info.width_type = 1
	display_info.width_value = width
	display_info.height_type = 1
	display_info.height_value = height
	local info = {}
	info.index = 1
	info.info = display_info
	local copy_list = {}
	copy_list[1] = info
	ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
end

function ALittleIDE.IDEImageSelectDialog:HandleImageEditClick(event)
	ALittleIDE.g_IDEEditImageDialog:ShowDialog(self.base_path .. "/" .. event.path, self.base_path)
end

function ALittleIDE.IDEImageSelectDialog:HandleImageDeleteClick(event)
	local tittle = "确定要永久删除该文件吗？"
	if event.directory then
		tittle = "确定要永久删除该文件夹，以及子文件吗？"
	end
	local result = g_AUITool:DeleteNotice("删除", tittle)
	if result == "YES" then
		if event.directory then
			ALittle.File_DeleteDeepDir(self.base_path .. "/" .. event.path)
		else
			ALittle.File_DeleteFile(self.base_path .. "/" .. event.path)
		end
		self:Refresh()
	end
end
ALittleIDE.IDEImageSelectDialog.HandleImageDeleteClick = Lua.CoWrap(ALittleIDE.IDEImageSelectDialog.HandleImageDeleteClick)

ALittleIDE.g_IDEImageManagerDialog = ALittleIDE.IDEImageSelectDialog("图片选择器", nil, {"PNG", "JPG"})
ALittleIDE.g_IDEImageSelectDialog = ALittleIDE.IDEImageSelectDialog("图片选择器", ALittleIDE.g_DialogLayer, {"PNG", "JPG"})
ALittleIDE.g_IDEEditImageDialog = AUIPlugin.AUIEditImageDialog()
end