-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1876308853, "AUIPlugin.AUIFileSelectItemUserData", {
name = "AUIPlugin.AUIFileSelectItemUserData", ns_name = "AUIPlugin", rl_name = "AUIFileSelectItemUserData", hash_code = 1876308853,
name_list = {"path","directory"},
type_list = {"string","bool"},
option_map = {}
})
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
ALittle.RegStruct(1686540930, "AUIPlugin.AUIFileSelectItemInfo", {
name = "AUIPlugin.AUIFileSelectItemInfo", ns_name = "AUIPlugin", rl_name = "AUIFileSelectItemInfo", hash_code = 1686540930,
name_list = {"name","frame","image","file","dir","button"},
type_list = {"ALittle.DisplayObject","ALittle.DisplayObject","ALittle.Image","ALittle.Image","ALittle.Image","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name = "ALittle.UIMoveOutEvent", ns_name = "ALittle", rl_name = "UIMoveOutEvent", hash_code = -1202439334,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1001723540, "ALittle.UIMouseMoveEvent", {
name = "ALittle.UIMouseMoveEvent", ns_name = "ALittle", rl_name = "UIMouseMoveEvent", hash_code = -1001723540,
name_list = {"target","abs_x","abs_y","rel_x","rel_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-573946464, "AUIPlugin.AUIFileSelectCollectRunTime", {
name = "AUIPlugin.AUIFileSelectCollectRunTime", ns_name = "AUIPlugin", rl_name = "AUIFileSelectCollectRunTime", hash_code = -573946464,
name_list = {"cur_count","total_count"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name = "ALittle.UIMoveInEvent", ns_name = "ALittle", rl_name = "UIMoveInEvent", hash_code = 544684311,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(-338112738, "ALittle.UIDropFileEvent", {
name = "ALittle.UIDropFileEvent", ns_name = "ALittle", rl_name = "UIDropFileEvent", hash_code = -338112738,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})

assert(ALittle.EventDispatcher, " extends class:ALittle.EventDispatcher is nil")
AUIPlugin.AUIFileSelectDialog = Lua.Class(ALittle.EventDispatcher, "AUIPlugin.AUIFileSelectDialog")

function AUIPlugin.AUIFileSelectDialog:Ctor(title, layer, ext_list)
	___rawset(self, "_real_size", 100)
	___rawset(self, "_thread", nil)
	___rawset(self, "_base_path", nil)
	___rawset(self, "_real_path", nil)
	___rawset(self, "_title", title)
	___rawset(self, "_layer", layer)
	if ext_list ~= nil then
		___rawset(self, "_ext_map", {})
		for index, ext in ___ipairs(ext_list) do
			self._ext_map[ALittle.String_Upper(ext)] = true
		end
	end
end

function AUIPlugin.AUIFileSelectDialog:Shutdown()
	if self._thread ~= nil then
		ALittle.Coroutine.Resume(self._thread, nil)
		self._thread = nil
	end
	if self._dialog ~= nil then
		if self._layer ~= nil then
			self._layer:RemoveChild(self._dialog)
		else
			A_LayerManager:RemoveFromModal(self._dialog)
		end
		self._dialog = nil
	end
end

function AUIPlugin.AUIFileSelectDialog:HideDialog()
	if self._thread ~= nil then
		ALittle.Coroutine.Resume(self._thread, nil)
		self._thread = nil
	end
	self._real_path = nil
	if self._dialog ~= nil then
		self._dialog.visible = false
	end
end

function AUIPlugin.AUIFileSelectDialog:CreateDialog()
	if self._dialog == nil then
		self._dialog = AUIPlugin.g_Control:CreateControl("ide_file_select_dialog", self)
		self._dialog.title = self._title
		if self._layer ~= nil then
			self._layer:AddChild(self._dialog)
		else
			A_LayerManager:AddToModal(self._dialog)
		end
	end
end

function AUIPlugin.AUIFileSelectDialog:ShowDialog()
	if self._thread ~= nil then
		ALittle.Coroutine.Resume(self._thread, nil)
		self._thread = nil
	end
	self:CreateDialog()
	self._dialog.visible = true
end

function AUIPlugin.AUIFileSelectDialog.__getter:base_path()
	return self._base_path
end

function AUIPlugin.AUIFileSelectDialog:ShowSelect()
	local ___COROUTINE = coroutine.running()
	self:ShowDialog()
	self._thread = ___COROUTINE
	return coroutine.yield()
end

function AUIPlugin.AUIFileSelectDialog:System_SetVDragCursor(event)
	ALittle.System_SetVDragCursor()
end

function AUIPlugin.AUIFileSelectDialog:System_SetNormalCursor(event)
	ALittle.System_SetNormalCursor()
end

function AUIPlugin.AUIFileSelectDialog:System_SetHDragCursor(event)
	ALittle.System_SetHDragCursor()
end

function AUIPlugin.AUIFileSelectDialog:System_SetHVDragCursor(event)
	ALittle.System_SetHVDragCursor()
end

function AUIPlugin.AUIFileSelectDialog:CreateFileItem(file_name, rel_path, abs_path)
	local ext = ALittle.File_GetFileExtByPath(file_name)
	if self._ext_map ~= nil then
		ext = ALittle.String_Upper(ext)
		if self._ext_map[ext] == nil then
			return nil
		end
	end
	local info = {}
	local item = AUIPlugin.g_Control:CreateControl("ide_file_select_item", info)
	info.name.text = file_name
	info.dir.visible = false
	info.file.visible = false
	info.image.visible = false
	if ext == "PNG" or ext == "JPG" then
		local width = nil
		local height = nil
		local surface = ALittle.System_LoadSurface(abs_path)
		if surface ~= nil then
			width = ALittle.System_GetSurfaceWidth(surface)
			height = ALittle.System_GetSurfaceHeight(surface)
			ALittle.System_FreeSurface(surface)
		end
		if width == nil then
			width = info.frame.width
			height = info.frame.height
		else
			if width < height then
				local rate = width / height
				height = info.frame.height
				width = rate * height
			else
				local rate = height / width
				width = info.frame.width
				height = rate * width
			end
		end
		info.image.visible = true
		info.image:SetTextureCut(abs_path, ALittle.Math_Floor(info.frame.width), ALittle.Math_Floor(info.frame.height), true)
		info.image.width = width
		info.image.height = height
		info.image:UpdateLayout()
	else
		info.file.visible = true
	end
	info.button.drag_trans_target = self._scroll_list
	info.button:AddEventListener(___all_struct[-641444818], self, self.HandleItemRButtonDown)
	info.button:AddEventListener(___all_struct[-449066808], self, self.HandleItemClick)
	info.button:AddEventListener(___all_struct[544684311], self, self.HandleItemMoveIn)
	info.button:AddEventListener(___all_struct[-1202439334], self, self.HandleItemMoveOut)
	info.button:AddEventListener(___all_struct[-1001723540], self, self.HandleItemMouseMove)
	info.button:AddEventListener(___all_struct[-338112738], self, self.HandleItemDropFile)
	local user_data = {}
	user_data.path = rel_path
	user_data.directory = false
	info.button._user_data = user_data
	item._user_data = user_data
	return item
end

function AUIPlugin.AUIFileSelectDialog:CreateDirItem(file_name, rel_path, abs_path)
	local info = {}
	local item = AUIPlugin.g_Control:CreateControl("ide_file_select_item", info)
	info.name.text = file_name
	info.image.visible = false
	info.file.visible = false
	info.dir.visible = true
	info.button.drag_trans_target = self._scroll_list
	info.button:AddEventListener(___all_struct[-449066808], self, self.HandleItemClick)
	info.button:AddEventListener(___all_struct[-641444818], self, self.HandleItemRButtonDown)
	info.button:AddEventListener(___all_struct[-338112738], self, self.HandleItemDropFile)
	local user_data = {}
	user_data.path = rel_path
	user_data.directory = true
	info.button._user_data = user_data
	item._user_data = user_data
	return item
end

function AUIPlugin.AUIFileSelectDialog:BrowserCollect(browser_path)
	local item_list_dir = {}
	local item_list_img = {}
	local file_map = ALittle.File_GetFileNameListByDir(browser_path)
	for file, info in ___pairs(file_map) do
		local path = browser_path .. "/" .. file
		local rel_path = ALittle.String_Sub(path, ALittle.String_Len(self._base_path) + 2)
		local attr = ALittle.File_GetFileAttr(path)
		if attr.mode == "directory" then
			local item = self:CreateDirItem(file, rel_path, path)
			if item ~= nil then
				ALittle.List_Push(item_list_dir, item)
			end
		else
			local item = self:CreateFileItem(file, rel_path, path)
			if item ~= nil then
				ALittle.List_Push(item_list_img, item)
			end
		end
	end
	return item_list_dir, item_list_img
end

function AUIPlugin.AUIFileSelectDialog:SearchCollect(search_path, name, item_list, run_time)
	if item_list == nil then
		item_list = {}
	end
	if run_time == nil then
		run_time = {}
		run_time.cur_count = 0
		run_time.total_count = 100
	end
	if name == "" or name == nil then
		return item_list, run_time
	end
	local file_map = ALittle.File_GetFileNameListByDir(search_path)
	for file, info in ___pairs(file_map) do
		local path = search_path .. "/" .. file
		local rel_path = ALittle.String_Sub(path, ALittle.String_Len(self._base_path) + 2)
		local attr = ALittle.File_GetFileAttr(path)
		if attr.mode == "directory" then
			self:SearchCollect(path, name, item_list, run_time)
		elseif ALittle.String_Find(file, name) ~= nil then
			local item = self:CreateFileItem(file, rel_path, path)
			if item ~= nil then
				run_time.cur_count = run_time.cur_count + 1
				ALittle.List_Push(item_list, item)
			end
		end
		if run_time.cur_count >= run_time.total_count then
			return item_list, run_time
		end
	end
	return item_list, run_time
end

function AUIPlugin.AUIFileSelectDialog.ItemListCmp(a, b)
	local a_user_data = a._user_data
	local b_user_data = b._user_data
	return a_user_data.path < b_user_data.path
end

function AUIPlugin.AUIFileSelectDialog:CreateItemAndAddToList(item_list_dir, item_list_img)
	ALittle.List_Sort(item_list_dir, AUIPlugin.AUIFileSelectDialog.ItemListCmp)
	ALittle.List_Sort(item_list_img, AUIPlugin.AUIFileSelectDialog.ItemListCmp)
	local item_list = {}
	for index, item in ___ipairs(item_list_dir) do
		ALittle.List_Push(item_list, item)
	end
	for index, item in ___ipairs(item_list_img) do
		ALittle.List_Push(item_list, item)
	end
	local col_count = ALittle.Math_Floor(self._scroll_list.width / self._real_size)
	local remain_count = 0
	local container = nil
	for index, item in ___ipairs(item_list) do
		if remain_count == 0 then
			container = ALittle.Linear(AUIPlugin.g_Control)
			container.type = 1
			container.height = item.height
			self._scroll_list:AddChild(container)
			container:AddChild(item)
			remain_count = col_count - 1
		else
			remain_count = remain_count - 1
			container:AddChild(item)
		end
	end
end

function AUIPlugin.AUIFileSelectDialog:Refresh()
	self:CreateDialog()
	self._scroll_list:RemoveAllChild()
	self._path_input.text = ALittle.String_Sub(self._real_path, ALittle.String_Len(self._base_path) + 2)
	self._search_input.text = ""
	self._dialog.title = self._title
	local item_list_dir, item_list_img = self:BrowserCollect(self._real_path)
	self:CreateItemAndAddToList(item_list_dir, item_list_img)
end

function AUIPlugin.AUIFileSelectDialog:Search(name)
	self._scroll_list:RemoveAllChild()
	local item_list_img, run_time = self:SearchCollect(self._real_path, name)
	if run_time.cur_count >= run_time.total_count then
		self._dialog.title = self._title .. "(筛选出来的数量太多，只显示前" .. run_time.total_count .. "个)"
	end
	self:CreateItemAndAddToList({}, item_list_img)
end

function AUIPlugin.AUIFileSelectDialog:SetPath(base_path, rel_path)
	local attr = ALittle.File_GetFileAttr(base_path .. "/" .. rel_path)
	if attr == nil or attr.mode ~= "directory" then
		g_AUITool:ShowNotice("错误", "无效路径")
		return false
	end
	self._base_path = base_path
	self._real_path = base_path
	if rel_path ~= "" then
		self._real_path = self._real_path .. "/" .. rel_path
	end
	self:Refresh()
	return true
end

function AUIPlugin.AUIFileSelectDialog:SetBasePath(base_path)
	if self._base_path == base_path then
		return true
	end
	return self:SetPath(base_path, "")
end

function AUIPlugin.AUIFileSelectDialog:HandleSetPathClick(event)
	self:SetPath(self._base_path, self._path_input.text)
end

function AUIPlugin.AUIFileSelectDialog:HandleSetPrePathClick(event)
	local rel_path = ALittle.String_Sub(self._real_path, ALittle.String_Len(self._base_path) + 2)
	if rel_path == "" then
		return
	end
	self:SetPath(self._base_path, ALittle.File_GetFilePathByPath(rel_path))
end

function AUIPlugin.AUIFileSelectDialog:HandleSearchClick(event)
	self:Search(self._search_input.text)
end

function AUIPlugin.AUIFileSelectDialog:HandleItemRButtonDown(event)
	local user_data = event.target._user_data
	local r_event = {}
	r_event.path = user_data.path
	r_event.directory = user_data.directory
	self:DispatchEvent(___all_struct[1821709712], r_event)
end

function AUIPlugin.AUIFileSelectDialog:HandleItemDropFile(event)
	local real_path = self._real_path
	local user_data = event.target._user_data
	if user_data ~= nil and user_data.directory then
		real_path = self._base_path .. "/" .. user_data.path
	end
	local name = ALittle.File_GetFileNameByPath(event.path)
	local ansi_path = event.path
	ansi_path = utf8.ansi2utf8(ansi_path)
	local attr = ALittle.File_GetFileAttr(ansi_path)
	if attr == nil then
		return
	end
	if attr.mode == "directory" then
		local check, error = self:CheckResourceName(name)
		if not check then
			g_AUITool:ShowNotice("提示", error)
			return
		end
		ALittle.File_MakeDir(real_path .. "/" .. name)
		if self._ext_map == nil then
			ALittle.File_CopyDeepDir(ansi_path, real_path .. "/" .. name)
		else
			for ext, _ in ___pairs(self._ext_map) do
				ALittle.File_CopyDeepDir(ansi_path, real_path .. "/" .. name, ext)
			end
		end
	else
		local upper_ext = ALittle.File_GetFileExtByPathAndUpper(event.path)
		if self._ext_map ~= nil and self._ext_map[upper_ext] == nil then
			g_AUITool:ShowNotice("提示", "不能接受该类型的文件")
			return
		end
		local check, error = self:CheckResourceName(ALittle.File_GetJustFileNameByPath(event.path))
		if not check then
			g_AUITool:ShowNotice("提示", error)
			return
		end
		ALittle.File_CopyFile(event.path, real_path .. "/" .. name)
	end
	self:Refresh()
end

function AUIPlugin.AUIFileSelectDialog:HandleNewDirectoryClick(event)
	local x, y = event.target:LocalToGlobal()
	local name = g_AUITool:ShowRename("", x, y + event.target.height, 200)
	if name == nil or name == "" then
		return
	end
	local check, error = self:CheckResourceName(name)
	if not check then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	local result = ALittle.File_MakeDir(self._real_path .. "/" .. name)
	if not result then
		g_AUITool:ShowNotice("错误", "文件夹创建失败")
		return
	end
	self:Refresh()
end
AUIPlugin.AUIFileSelectDialog.HandleNewDirectoryClick = Lua.CoWrap(AUIPlugin.AUIFileSelectDialog.HandleNewDirectoryClick)

function AUIPlugin.AUIFileSelectDialog:HandleItemClick(event)
	local user_data = event.target._user_data
	if user_data.directory then
		self._real_path = self._base_path .. "/" .. user_data.path
		self:Refresh()
	else
		if self._thread ~= nil then
			self._dialog.visible = false
			ALittle.Coroutine.Resume(self._thread, user_data.path)
			self._thread = nil
		end
	end
end

function AUIPlugin.AUIFileSelectDialog:HandleItemMoveIn(event)
	if self._image_pre_dialog == nil then
		self._image_pre_dialog = AUIPlugin.g_Control:CreateControl("ide_image_pre_dialog", self)
	end
	A_LayerManager:AddToTip(self._image_pre_dialog)
	local user_data = event.target._user_data
	local path = self._base_path .. "/" .. user_data.path
	self._pre_image:SetTextureCut(path, 0, 0, true, Lua.Bind(self.HandleItemPreViewCallback, self))
	self:UpdateImagePreDialogPos()
end

function AUIPlugin.AUIFileSelectDialog:HandleItemPreViewCallback(image, result)
	local width = image.texture_width
	image.width = width
	if width < 100 then
		width = 100
	end
	if width > A_UISystem.view_width then
		width = A_UISystem.view_width
		image.width = width
	end
	self._image_pre_dialog.width = width
	image.x = (width - image.width) / 2
	local height = image.texture_height
	image.height = height
	if height < 50 then
		height = 50
	end
	if height > A_UISystem.view_height - self._image_pre_dialog.head_size then
		height = A_UISystem.view_height - self._image_pre_dialog.head_size
		image.height = height
	end
	image.y = (height - image.height) / 2
	self._image_pre_dialog.height = self._image_pre_dialog.head_size + height
end

function AUIPlugin.AUIFileSelectDialog:HandleItemMoveOut(event)
	A_LayerManager:RemoveFromTip(self._image_pre_dialog)
end

function AUIPlugin.AUIFileSelectDialog:HandleItemMouseMove(event)
	self:UpdateImagePreDialogPos()
end

function AUIPlugin.AUIFileSelectDialog:UpdateImagePreDialogPos()
	if self._image_pre_dialog == nil then
		return
	end
	local x = A_UISystem.mouse_x + 20
	if x + self._image_pre_dialog.width > A_UISystem.view_width then
		x = A_UISystem.view_width - self._image_pre_dialog.width
	end
	local y = A_UISystem.mouse_y + 20
	if y + self._image_pre_dialog.height > A_UISystem.view_height then
		y = A_UISystem.view_height - self._image_pre_dialog.height
	end
	self._image_pre_dialog.x = x
	self._image_pre_dialog.y = y
end

function AUIPlugin.AUIFileSelectDialog:HandleDialogDrag(event)
	local delta_x = event.delta_x
	local delta_y = event.delta_y
	if event.target == self._drag_lr_quad then
		delta_y = 0
	elseif event.target == self._drag_ud_quad then
		delta_x = 0
	end
	if self._dialog.width + delta_x < 506 then
		delta_x = 506 - self._dialog.width
	end
	if self._dialog.height + delta_y < 200 then
		delta_y = 200 - self._dialog.height
	end
	self._dialog.width = self._dialog.width + delta_x
	self._dialog.height = self._dialog.height + delta_y
end

function AUIPlugin.AUIFileSelectDialog:HandleDialogDragEnd(event)
	self:Refresh()
end

function AUIPlugin.AUIFileSelectDialog:CheckResourceName(name)
	local len = ALittle.String_Len(name)
	if len == 0 then
		return false, "命名只能支持字母数字下划线"
	end
	local i = 1
	while true do
		if not(i <= len) then break end
		local byte = ALittle.String_Byte(name, i)
		local check_all = byte >= 65 and byte <= 90 or byte >= 97 and byte <= 122 or byte >= 48 and byte <= 57 or byte == 95
		if check_all == false then
			return false, "命名只能支持字母数字下划线"
		end
		i = i+(1)
	end
	return true, nil
end

end