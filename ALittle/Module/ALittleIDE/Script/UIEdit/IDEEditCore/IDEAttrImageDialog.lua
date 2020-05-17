-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(766794486, "ALittleIDE.IDEAttrImageSelectItemInfo", {
name = "ALittleIDE.IDEAttrImageSelectItemInfo", ns_name = "ALittleIDE", rl_name = "IDEAttrImageSelectItemInfo", hash_code = 766794486,
name_list = {"name","frame","image","button"},
type_list = {"ALittle.DisplayObject","ALittle.DisplayObject","ALittle.Image","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(271769996, "ALittleIDE.IDEAttrImageSelectItemUserData", {
name = "ALittleIDE.IDEAttrImageSelectItemUserData", ns_name = "ALittleIDE", rl_name = "IDEAttrImageSelectItemUserData", hash_code = 271769996,
name_list = {"path","directory"},
type_list = {"string","bool"},
option_map = {}
})
ALittle.RegStruct(-894949676, "ALittleIDE.IDEAttrImageSelectCollectRunTime", {
name = "ALittleIDE.IDEAttrImageSelectCollectRunTime", ns_name = "ALittleIDE", rl_name = "IDEAttrImageSelectCollectRunTime", hash_code = -894949676,
name_list = {"cur_count","total_count"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
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
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name = "ALittle.UIMoveInEvent", ns_name = "ALittle", rl_name = "UIMoveInEvent", hash_code = 544684311,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
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

IDEAttrImageDialog = Lua.Class(nil, "ALittleIDE.IDEAttrImageDialog")

function IDEAttrImageDialog:Ctor()
	___rawset(self, "_real_size", 100)
	___rawset(self, "_src_title", nil)
	___rawset(self, "_callback", nil)
	___rawset(self, "_base_path", nil)
	___rawset(self, "_real_path", nil)
end

function IDEAttrImageDialog:Setup()
	g_IDEProject:AddEventListener(___all_struct[-332308624], self, self.HandleCloseProject)
end

function IDEAttrImageDialog:HandleCloseProject(event)
	if self._dialog == nil then
		return
	end
	self._scroll_list:RemoveAllChild()
	self:HideDialog()
end

function IDEAttrImageDialog:Close()
	self._callback = nil
	self._base_path = nil
	self._real_path = nil
	if self._dialog ~= nil then
		self._dialog.visible = false
	end
end

function IDEAttrImageDialog:HideDialog()
	self._dialog.visible = false
	self._callback = nil
end

function IDEAttrImageDialog:ShowDialog(path, callback)
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("错误", "当前没有项目打开")
		return
	end
	if self._dialog == nil then
		self._dialog = g_Control:CreateControl("ide_image_select_dialog", self)
		A_LayerManager:AddToModal(self._dialog)
		self._src_title = self._dialog.title
		if self._src_title == nil then
			self._src_title = "图片选择器"
		end
	end
	if path ~= nil or self._real_path == nil then
		if self:SetPath(path) == false then
			return
		end
	end
	self._callback = callback
	self._dialog.visible = true
end

function IDEAttrImageDialog:System_SetVDragCursor(event)
	ALittle.System_SetVDragCursor()
end

function IDEAttrImageDialog:System_SetNormalCursor(event)
	ALittle.System_SetNormalCursor()
end

function IDEAttrImageDialog:System_SetHDragCursor(event)
	ALittle.System_SetHDragCursor()
end

function IDEAttrImageDialog:System_SetHVDragCursor(event)
	ALittle.System_SetHVDragCursor()
end

function IDEAttrImageDialog:CreateImgItem(file_name, rel_path, abs_path)
	local ext = ALittle.File_GetFileExtByPath(file_name)
	ext = ALittle.String_Upper(ext)
	if ext == "PNG" or ext == "JPG" then
		local info = {}
		local item = g_Control:CreateControl("ide_image_select_item", info)
		info.name.text = file_name
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
		info.image:SetTextureCut(abs_path, ALittle.Math_Floor(info.frame.width), ALittle.Math_Floor(info.frame.height), true)
		info.image.width = width
		info.image.height = height
		info.image:UpdateLayout()
		info.button.drag_trans_target = self._scroll_list
		info.button:AddEventListener(___all_struct[-641444818], self, self.HandleItemRButtonDown)
		info.button:AddEventListener(___all_struct[-449066808], self, self.HandleItemClick)
		info.button:AddEventListener(___all_struct[544684311], self, self.HandleItemMoveIn)
		info.button:AddEventListener(___all_struct[-1202439334], self, self.HandleItemMoveOut)
		info.button:AddEventListener(___all_struct[-1001723540], self, self.HandleItemMouseMove)
		local user_data = {}
		user_data.path = rel_path
		user_data.directory = false
		info.button._user_data = user_data
		item._user_data = user_data
		return item
	end
	return nil
end

function IDEAttrImageDialog:CreateDirItem(file_name, rel_path, abs_path)
	local info = {}
	local item = g_Control:CreateControl("ide_image_select_item", info)
	info.name.text = file_name
	info.button.drag_trans_target = self._scroll_list
	info.button:AddEventListener(___all_struct[-449066808], self, self.HandleItemClick)
	local user_data = {}
	user_data.path = rel_path
	user_data.directory = true
	info.button._user_data = user_data
	item._user_data = user_data
	return item
end

function IDEAttrImageDialog:BrowserCollect(browser_path)
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
			local item = self:CreateImgItem(file, rel_path, path)
			if item ~= nil then
				ALittle.List_Push(item_list_img, item)
			end
		end
	end
	return item_list_dir, item_list_img
end

function IDEAttrImageDialog:SearchCollect(search_path, name, item_list, run_time)
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
			local item = self:CreateImgItem(file, rel_path, path)
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

function IDEAttrImageDialog.ItemListCmp(a, b)
	local a_user_data = a._user_data
	local b_user_data = b._user_data
	return a_user_data.path < b_user_data.path
end

function IDEAttrImageDialog:CreateItemAndAddToList(item_list_dir, item_list_img)
	ALittle.List_Sort(item_list_dir, IDEAttrImageDialog.ItemListCmp)
	ALittle.List_Sort(item_list_img, IDEAttrImageDialog.ItemListCmp)
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
			container = ALittle.Linear(g_Control)
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

function IDEAttrImageDialog:Refresh()
	self._scroll_list:RemoveAllChild()
	self._path_input.text = ALittle.String_Sub(self._real_path, ALittle.String_Len(self._base_path) + 2)
	self._search_input.text = ""
	self._dialog.title = self._src_title
	local item_list_dir, item_list_img = self:BrowserCollect(self._real_path)
	self:CreateItemAndAddToList(item_list_dir, item_list_img)
end

function IDEAttrImageDialog:Search(name)
	self._scroll_list:RemoveAllChild()
	local item_list_img, run_time = self:SearchCollect(self._real_path, name)
	if run_time.cur_count >= run_time.total_count then
		self._dialog.title = self._src_title .. "(筛选出来的数量太多，只显示前" .. run_time.total_count .. "个)"
	end
	self:CreateItemAndAddToList({}, item_list_img)
end

function IDEAttrImageDialog:SetPath(path)
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("错误", "当前没有项目打开")
		return false
	end
	local real_path = g_IDEProject.project.base_path .. "Texture"
	if path == nil then
		path = ""
	end
	if path ~= "" then
		real_path = real_path .. "/" .. path
	end
	local attr = ALittle.File_GetFileAttr(real_path)
	if attr == nil or attr.mode ~= "directory" then
		g_IDETool:ShowNotice("错误", "无效路径")
		return false
	end
	self._base_path = g_IDEProject.project.base_path .. "Texture"
	self._real_path = real_path
	self:Refresh()
	return true
end

function IDEAttrImageDialog:HandleSetPathClick(event)
	self:SetPath(self._path_input.text)
end

function IDEAttrImageDialog:HandleSetPrePathClick(event)
	local rel_path = ALittle.String_Sub(self._real_path, ALittle.String_Len(self._base_path) + 2)
	if rel_path == "" then
		return
	end
	self:SetPath(ALittle.File_GetFilePathByPath(rel_path))
end

function IDEAttrImageDialog:HandleSearchClick(event)
	self:Search(self._search_input.text)
end

function IDEAttrImageDialog:HandleItemRButtonDown(event)
	if self._image_select_menu == nil then
		self._image_select_menu = g_Control:CreateControl("ide_image_select_menu", self)
	end
	A_LayerManager:ShowFromRight(self._image_select_menu)
	self._image_select_menu.x = A_UISystem.mouse_x
	self._image_select_menu.y = A_UISystem.mouse_y
	self._image_select_menu._user_data = event.target._user_data
end

function IDEAttrImageDialog:HandleImageEditClick(event)
	A_LayerManager:HideFromRight(self._image_select_menu)
	local user_data = self._image_select_menu._user_data
	self._image_select_menu._user_data = nil
	g_IDEEditImageDialog:ShowDialog(g_IDEProject.project.base_path .. "Texture/" .. user_data.path)
end

function IDEAttrImageDialog:HandleImageDeleteClick(event)
	A_LayerManager:HideFromRight(self._image_select_menu)
	local user_data = self._image_select_menu._user_data
	self._image_select_menu._user_data = nil
	ALittle.File_DeleteFile(g_IDEProject.project.base_path .. "Texture/" .. user_data.path)
	self:Refresh()
end

function IDEAttrImageDialog:HandleItemClick(event)
	local user_data = event.target._user_data
	if user_data.directory then
		self._base_path = g_IDEProject.project.base_path .. "Texture"
		self._real_path = g_IDEProject.project.base_path .. "Texture/" .. user_data.path
		self:Refresh()
	else
		if self._callback ~= nil then
			self._callback(user_data.path)
			self._callback = nil
			self._dialog.visible = false
		end
	end
end

function IDEAttrImageDialog:HandleItemMoveIn(event)
	if self._image_pre_dialog == nil then
		self._image_pre_dialog = g_Control:CreateControl("ide_image_pre_dialog", self)
	end
	A_LayerManager:AddToTip(self._image_pre_dialog)
	local user_data = event.target._user_data
	local path = g_IDEProject.project.base_path .. "Texture/" .. user_data.path
	self._pre_image:SetTextureCut(path, 0, 0, true, Lua.Bind(self.HandleItemPreViewCallback, self))
	self:UpdateImagePreDialogPos()
end

function IDEAttrImageDialog:HandleItemPreViewCallback(image, result)
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

function IDEAttrImageDialog:HandleItemMoveOut(event)
	A_LayerManager:RemoveFromTip(self._image_pre_dialog)
end

function IDEAttrImageDialog:HandleItemMouseMove(event)
	self:UpdateImagePreDialogPos()
end

function IDEAttrImageDialog:UpdateImagePreDialogPos()
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

function IDEAttrImageDialog:HandleDialogDrag(event)
	local delta_x = event.delta_x
	local delta_y = event.delta_y
	if event.target == self._drag_lr_quad then
		delta_y = 0
	elseif event.target == self._drag_ud_quad then
		delta_x = 0
	end
	self._dialog.width = self._dialog.width + delta_x
	self._dialog.height = self._dialog.height + delta_y
end

g_IDEAttrImageDialog = IDEAttrImageDialog()
