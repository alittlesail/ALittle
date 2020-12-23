-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
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
ALittle.RegStruct(1686540930, "AUIPlugin.AUIFileSelectItemInfo", {
name = "AUIPlugin.AUIFileSelectItemInfo", ns_name = "AUIPlugin", rl_name = "AUIFileSelectItemInfo", hash_code = 1686540930,
name_list = {"name","frame","image","file","dir","button"},
type_list = {"ALittle.DisplayObject","ALittle.DisplayObject","ALittle.Image","ALittle.Image","ALittle.Image","ALittle.TextRadioButton"},
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
ALittle.RegStruct(-1265378424, "AUIPlugin.AUIFileSelectRightButtonDownUIEvent", {
name = "AUIPlugin.AUIFileSelectRightButtonDownUIEvent", ns_name = "AUIPlugin", rl_name = "AUIFileSelectRightButtonDownUIEvent", hash_code = -1265378424,
name_list = {"target","path","directory"},
type_list = {"ALittle.DisplayObject","string","bool"},
option_map = {}
})
ALittle.RegStruct(1206110359, "AUIPlugin.AUIFileSelectFileClickUIEvent", {
name = "AUIPlugin.AUIFileSelectFileClickUIEvent", ns_name = "AUIPlugin", rl_name = "AUIFileSelectFileClickUIEvent", hash_code = 1206110359,
name_list = {"target","path","ctrl"},
type_list = {"ALittle.DisplayObject","string","bool"},
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
ALittle.RegStruct(-989784577, "AUIPlugin.AUIFileSelectDirClickUIEvent", {
name = "AUIPlugin.AUIFileSelectDirClickUIEvent", ns_name = "AUIPlugin", rl_name = "AUIFileSelectDirClickUIEvent", hash_code = -989784577,
name_list = {"target","path","ctrl"},
type_list = {"ALittle.DisplayObject","string","bool"},
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
name_list = {"target","is_drag","count"},
type_list = {"ALittle.DisplayObject","bool","int"},
option_map = {}
})
ALittle.RegStruct(-338112738, "ALittle.UIDropFileEvent", {
name = "ALittle.UIDropFileEvent", ns_name = "ALittle", rl_name = "UIDropFileEvent", hash_code = -338112738,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUIPlugin.AUIFileSelectLayout = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUIFileSelectLayout")

function AUIPlugin.AUIFileSelectLayout:Ctor()
	___rawset(self, "_group", {})
end

function AUIPlugin.AUIFileSelectLayout:Init(ext_list)
	self._real_size = 100
	self._thread = nil
	self._base_path = nil
	self._real_path = nil
	if ext_list ~= nil then
		self._ext_map = {}
		for index, ext in ___ipairs(ext_list) do
			self._ext_map[ALittle.String_Upper(ext)] = true
		end
	end
end

function AUIPlugin.AUIFileSelectLayout:Release()
	if self._thread ~= nil then
		ALittle.Coroutine.Resume(self._thread, nil)
		self._thread = nil
	end
end

function AUIPlugin.AUIFileSelectLayout.__getter:base_path()
	return self._base_path
end

function AUIPlugin.AUIFileSelectLayout:ShowSelect()
	local ___COROUTINE = coroutine.running()
	self._thread = ___COROUTINE
	return coroutine.yield()
end

function AUIPlugin.AUIFileSelectLayout:System_SetVDragCursor(event)
	ALittle.System_SetVDragCursor()
end

function AUIPlugin.AUIFileSelectLayout:System_SetNormalCursor(event)
	ALittle.System_SetNormalCursor()
end

function AUIPlugin.AUIFileSelectLayout:System_SetHDragCursor(event)
	ALittle.System_SetHDragCursor()
end

function AUIPlugin.AUIFileSelectLayout:System_SetHVDragCursor(event)
	ALittle.System_SetHVDragCursor()
end

function AUIPlugin.AUIFileSelectLayout:CreateFileItem(file_name, rel_path, abs_path)
	local ext = ALittle.File_GetFileExtByPath(file_name)
	if self._ext_map ~= nil then
		ext = ALittle.String_Upper(ext)
		if self._ext_map[ext] == nil then
			return nil
		end
	end
	local info = {}
	local item = AUIPlugin.g_Control:CreateControl("file_select_item", info)
	info.name.text = file_name
	info.dir.visible = false
	info.file.visible = false
	info.image.visible = false
	if ext == "PNG" or ext == "JPG" or ext == "BMP" then
		local width = nil
		local height = nil
		local surface = carp.LoadCarpSurface(abs_path)
		if surface ~= nil then
			width = carp.GetCarpSurfaceWidth(surface)
			height = carp.GetCarpSurfaceHeight(surface)
			carp.FreeCarpSurface(surface)
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
	info.button.group = self._group
	local user_data = {}
	user_data.path = rel_path
	user_data.directory = false
	info.button._user_data = user_data
	item._user_data = user_data
	return item
end

function AUIPlugin.AUIFileSelectLayout:CreateDirItem(file_name, rel_path, abs_path)
	local info = {}
	local item = AUIPlugin.g_Control:CreateControl("file_select_item", info)
	info.name.text = file_name
	info.image.visible = false
	info.file.visible = false
	info.dir.visible = true
	info.button.drag_trans_target = self._scroll_list
	info.button:AddEventListener(___all_struct[-449066808], self, self.HandleItemClick)
	info.button:AddEventListener(___all_struct[-641444818], self, self.HandleItemRButtonDown)
	info.button:AddEventListener(___all_struct[-338112738], self, self.HandleItemDropFile)
	info.button.group = self._group
	local user_data = {}
	user_data.path = rel_path
	user_data.directory = true
	info.button._user_data = user_data
	item._user_data = user_data
	return item
end

function AUIPlugin.AUIFileSelectLayout:BrowserCollect(browser_path)
	local item_list_dir = {}
	local item_list_img = {}
	local file_map = ALittle.File_GetNameListByDir(browser_path)
	for file, info in ___pairs(file_map) do
		local path = browser_path .. "/" .. file
		local rel_path = ALittle.String_Sub(path, ALittle.String_Len(self._base_path) + 2)
		local attr = ALittle.File_GetFileAttr(path)
		if attr.directory then
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

function AUIPlugin.AUIFileSelectLayout:SearchCollect(search_path, name, item_list, run_time)
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
	local file_map = ALittle.File_GetNameListByDir(search_path)
	for file, info in ___pairs(file_map) do
		local path = search_path .. "/" .. file
		local rel_path = ALittle.String_Sub(path, ALittle.String_Len(self._base_path) + 2)
		local attr = ALittle.File_GetFileAttr(path)
		if attr.directory then
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

function AUIPlugin.AUIFileSelectLayout.ItemListCmp(a, b)
	local a_user_data = a._user_data
	local b_user_data = b._user_data
	return a_user_data.path < b_user_data.path
end

function AUIPlugin.AUIFileSelectLayout:CreateItemAndAddToList(item_list_dir, item_list_img)
	ALittle.List_Sort(item_list_dir, AUIPlugin.AUIFileSelectLayout.ItemListCmp)
	ALittle.List_Sort(item_list_img, AUIPlugin.AUIFileSelectLayout.ItemListCmp)
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

function AUIPlugin.AUIFileSelectLayout:Refresh()
	self._scroll_list:RemoveAllChild()
	self._path_input.text = ALittle.String_Sub(self._real_path, ALittle.String_Len(self._base_path) + 2)
	self._search_input.text = ""
	local item_list_dir, item_list_img = self:BrowserCollect(self._real_path)
	self:CreateItemAndAddToList(item_list_dir, item_list_img)
end

function AUIPlugin.AUIFileSelectLayout:Search(name)
	self._scroll_list:RemoveAllChild()
	local item_list_img, run_time = self:SearchCollect(self._real_path, name)
	self:CreateItemAndAddToList({}, item_list_img)
end

function AUIPlugin.AUIFileSelectLayout:SetPath(base_path, rel_path)
	if base_path ~= nil and rel_path ~= nil then
		local attr = ALittle.File_GetFileAttr(base_path .. "/" .. rel_path)
		if attr == nil or attr.directory ~= true then
			g_AUITool:ShowNotice("错误", "无效路径")
			return false
		end
	end
	self._base_path = base_path
	self._real_path = base_path
	if rel_path ~= nil and rel_path ~= "" then
		self._real_path = self._real_path .. "/" .. rel_path
	end
	if self._base_path ~= nil then
		self:Refresh()
	else
		self._scroll_list:RemoveAllChild()
	end
	return true
end

function AUIPlugin.AUIFileSelectLayout:SetBasePath(base_path)
	if self._base_path == base_path then
		return true
	end
	return self:SetPath(base_path, "")
end

function AUIPlugin.AUIFileSelectLayout:HandleSetPathClick(event)
	self:SetPath(self._base_path, self._path_input.text)
end

function AUIPlugin.AUIFileSelectLayout:HandleSetPrePathClick(event)
	local rel_path = ALittle.String_Sub(self._real_path, ALittle.String_Len(self._base_path) + 2)
	if rel_path == "" then
		return
	end
	self:SetPath(self._base_path, ALittle.File_GetFilePathByPath(rel_path))
end

function AUIPlugin.AUIFileSelectLayout:HandleSearchClick(event)
	self:Search(self._search_input.text)
end

function AUIPlugin.AUIFileSelectLayout:HandleItemRButtonDown(event)
	A_LayerManager:RemoveFromTip(self._image_pre_dialog)
	local user_data = event.target._user_data
	local r_event = {}
	r_event.path = user_data.path
	r_event.directory = user_data.directory
	self:DispatchEvent(___all_struct[-1265378424], r_event)
end

function AUIPlugin.AUIFileSelectLayout:HandleItemDropFile(event)
	local real_path = self._real_path
	local user_data = event.target._user_data
	if user_data ~= nil and user_data.directory then
		real_path = self._base_path .. "/" .. user_data.path
	end
	local name = ALittle.File_GetFileNameByPath(event.path)
	local path = event.path
	local attr = ALittle.File_GetFileAttr(path)
	if attr == nil then
		return
	end
	if attr.directory then
		local check, error = self:CheckResourceName(name)
		if not check then
			g_AUITool:ShowNotice("提示", error)
			return
		end
		ALittle.File_MakeDir(real_path .. "/" .. name)
		if self._ext_map == nil then
			ALittle.File_CopyDeepDir(path, real_path .. "/" .. name)
		else
			for ext, _ in ___pairs(self._ext_map) do
				ALittle.File_CopyDeepDir(path, real_path .. "/" .. name, ext)
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

function AUIPlugin.AUIFileSelectLayout:HandleNewDirectoryClick(event)
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
	ALittle.File_MakeDir(self._real_path .. "/" .. name)
	if ALittle.File_GetFileAttr(self._real_path .. "/" .. name) == nil then
		g_AUITool:ShowNotice("错误", "文件夹创建失败")
		return
	end
	self:Refresh()
end
AUIPlugin.AUIFileSelectLayout.HandleNewDirectoryClick = Lua.CoWrap(AUIPlugin.AUIFileSelectLayout.HandleNewDirectoryClick)

function AUIPlugin.AUIFileSelectLayout:HandleItemClick(event)
	local user_data = event.target._user_data
	if event.count <= 1 then
		if user_data.directory then
			local e = {}
			e.path = user_data.path
			e.ctrl = A_UISystem.sym_map[1073742048] ~= nil
			self:DispatchEvent(___all_struct[-989784577], e)
		else
			if self._thread ~= nil then
				ALittle.Coroutine.Resume(self._thread, user_data.path)
				self._thread = nil
			end
			local e = {}
			e.path = user_data.path
			e.ctrl = A_UISystem.sym_map[1073742048] ~= nil
			self:DispatchEvent(___all_struct[1206110359], e)
		end
	elseif event.count <= 2 then
		if user_data.directory then
			self._real_path = self._base_path .. "/" .. user_data.path
			self:Refresh()
		end
	end
end

function AUIPlugin.AUIFileSelectLayout:HandleItemMoveIn(event)
	if self._image_pre_dialog == nil then
		self._image_pre_dialog = AUIPlugin.g_Control:CreateControl("file_select_image_pre_dialog", self)
	end
	A_LayerManager:AddToTip(self._image_pre_dialog)
	local user_data = event.target._user_data
	local path = self._base_path .. "/" .. user_data.path
	self._pre_image:SetTextureCut(path, 0, 0, true, Lua.Bind(self.HandleItemPreViewCallback, self))
	self:UpdateImagePreDialogPos()
end

function AUIPlugin.AUIFileSelectLayout:HandleItemPreViewCallback(image, result)
	local width = image.texture_width
	image.width = width
	if width < 100 then
		width = 100
	end
	if width > A_UISystem.view_width then
		width = A_UISystem.view_width
		image.width = width
	end
	self._image_pre_dialog.width = width + 10
	image.x = (self._image_pre_dialog.width - image.width) / 2
	local height = image.texture_height
	image.height = height
	if height < 50 then
		height = 50
	end
	if height > A_UISystem.view_height - self._image_pre_dialog.head_size then
		height = A_UISystem.view_height - self._image_pre_dialog.head_size
		image.height = height
	end
	image.y = (height + 5 - image.height) / 2
	self._image_pre_dialog.height = self._image_pre_dialog.head_size + height + 10
end

function AUIPlugin.AUIFileSelectLayout:HandleItemMoveOut(event)
	A_LayerManager:RemoveFromTip(self._image_pre_dialog)
end

function AUIPlugin.AUIFileSelectLayout:HandleItemMouseMove(event)
	self:UpdateImagePreDialogPos()
end

function AUIPlugin.AUIFileSelectLayout:UpdateImagePreDialogPos()
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

function AUIPlugin.AUIFileSelectLayout:CheckResourceName(name)
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