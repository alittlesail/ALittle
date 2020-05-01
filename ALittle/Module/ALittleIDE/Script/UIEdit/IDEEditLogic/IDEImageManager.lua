-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

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
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name = "ALittle.UIMoveInEvent", ns_name = "ALittle", rl_name = "UIMoveInEvent", hash_code = 544684311,
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
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name = "ALittle.UIMoveOutEvent", ns_name = "ALittle", rl_name = "UIMoveOutEvent", hash_code = -1202439334,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

IDEImageManager = Lua.Class(nil, "ALittleIDE.IDEImageManager")

function IDEImageManager:HandleImageSearchClick(event)
	self._image_scroll_screen:RemoveAllChild()
	local project = g_IDEProject.project
	if project == nil then
		g_IDETool:ShowNotice("提示", "当前没有打开的项目")
		return
	end
	local key = self._image_search_key.text
	local image_info_list = {}
	local image_info_count = 0
	local path = project.base_path .. "Texture"
	local file_map = ALittle.File_GetFileAttrByDir(path)
	for file_path, attr in ___pairs(file_map) do
		local file_name = ALittle.File_GetFileNameByPath(file_path)
		if key == "" or ALittle.String_Find(file_name, key) ~= nil then
			image_info_count = image_info_count + 1
			image_info_list[image_info_count] = file_path
		end
	end
	ALittle.List_Sort(image_info_list)
	for index, file_path in ___ipairs(image_info_list) do
		local file_name = ALittle.File_GetFileNameByPath(file_path)
		local item = g_Control:CreateControl("ide_common_item_button")
		item.text = file_name
		item._user_data = ALittle.String_Sub(file_path, ALittle.String_Len(path) + 2)
		item:AddEventListener(___all_struct[-641444818], self, self.HandleImageItemRightClick)
		item:AddEventListener(___all_struct[544684311], self, self.HandleImageItemMoveIn)
		item:AddEventListener(___all_struct[-1001723540], self, self.HandleImageItemMouseMove)
		item:AddEventListener(___all_struct[-1202439334], self, self.HandleImageItemMoveOut)
		item.drag_trans_target = self._image_scroll_screen
		self._image_scroll_screen:AddChild(item)
	end
end

function IDEImageManager:ClearImageItem()
	self._image_scroll_screen:RemoveAllChild()
end

function IDEImageManager:HandleImageItemMoveIn(event)
	if self._image_tip_dialog == nil then
		self._image_tip_dialog = ALittle.Image(g_IDEProject.project.control)
		self._image_tip_dialog.width = 100
		self._image_tip_dialog.height = 100
		A_LayerManager:AddToTip(self._image_tip_dialog)
	end
	self._image_tip_dialog.texture_name = event.target._user_data
	self._image_tip_dialog.visible = true
end

function IDEImageManager:HandleImageItemMouseMove(event)
	if self._image_tip_dialog == nil then
		return
	end
	local x = A_UISystem.mouse_x + 10
	local y = A_UISystem.mouse_y + 10
	if y + self._image_tip_dialog.height > A_UISystem.view_height then
		y = A_UISystem.view_height - self._image_tip_dialog.height
	end
	self._image_tip_dialog.x = x
	self._image_tip_dialog.y = y
end

function IDEImageManager:HandleImageItemMoveOut(event)
	if self._image_tip_dialog == nil then
		return
	end
	self._image_tip_dialog.visible = false
end

function IDEImageManager:HandleImageItemRightClick(event)
	if self._image_right_menu == nil then
		self._image_right_menu = g_Control:CreateControl("ide_image_right_menu", self)
	end
	A_LayerManager:ShowFromRight(self._image_right_menu)
	self._image_right_menu.x = A_UISystem.mouse_x
	self._image_right_menu.y = A_UISystem.mouse_y
	if self._image_right_menu.x + self._image_right_menu.width > A_UISystem.view_width then
		self._image_right_menu.x = A_UISystem.view_width - self._image_right_menu.width
	end
	if self._image_right_menu.y + self._image_right_menu.height > A_UISystem.view_height then
		self._image_right_menu.y = A_UISystem.view_height - self._image_right_menu.height
	end
	self._image_right_menu._user_data = event.target
end

function IDEImageManager:DeleteControlImpl(target)
	g_IDEUICenter.image_scroll_screen:RemoveChild(target)
	ALittle.File_DeleteFile(target._user_data)
end

function IDEImageManager:HandleImageRightMenuDelete(event)
	A_LayerManager:HideFromRight(self._image_right_menu)
	local target = self._image_right_menu._user_data
	self._image_right_menu._user_data = nil
	local callback = Lua.Bind(self.DeleteControlImpl, self, target)
	g_IDETool:DeleteNotice("提示", "确定要删除" .. target.text .. "吗?", callback)
end

function IDEImageManager:HandleImageRightMenuCopyPath(event)
	A_LayerManager:HideFromRight(self._image_right_menu)
	local target = self._image_right_menu._user_data
	self._image_right_menu._user_data = nil
	ALittle.System_SetClipboardText(target._user_data)
end

function IDEImageManager:HandleImageRightMenuCopyCode(event)
	A_LayerManager:HideFromRight(self._image_right_menu)
	local target = self._image_right_menu._user_data
	self._image_right_menu._user_data = nil
	self:CopyImageCodeImpl(target._user_data)
end

function IDEImageManager:CopyImageCodeImpl(file_path)
	local width = 100
	local height = 100
	local surface = ALittle.System_LoadSurface(g_IDEProject.project.base_path .. "Texture/" .. file_path)
	if surface ~= nil then
		width = ALittle.System_GetSurfaceWidth(surface)
		height = ALittle.System_GetSurfaceHeight(surface)
		ALittle.System_FreeSurface(surface)
	end
	local display_info = {}
	display_info.__class = "Image"
	display_info.texture_name = file_path
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

function IDEImageManager:HandleImageRightMenuGrid9(event)
	A_LayerManager:HideFromRight(self._image_right_menu)
	local target = self._image_right_menu._user_data
	self._image_right_menu._user_data = nil
	local display_info = IDEUtility_GenerateGrid9ImageInfo(g_IDEProject.project.base_path .. "Texture/", target._user_data)
	if display_info == nil then
		g_IDETool:ShowNotice("错误", "图片加载失败:" .. target._user_data)
		return
	end
	local copy_list = {}
	local info = {}
	info.index = 1
	info.info = display_info
	copy_list[1] = info
	ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
end

function IDEImageManager:HandleImageRightMenuRepair(event)
	A_LayerManager:HideFromRight(self._image_right_menu)
	local target = self._image_right_menu._user_data
	self._image_right_menu._user_data = nil
	local full_path = g_IDEProject.project.base_path .. "Texture/" .. target._user_data
	local surface = ALittle.System_LoadSurface(full_path)
	if surface ~= nil then
		ALittle.System_SaveSurface(surface, full_path)
		ALittle.System_FreeSurface(surface)
	end
end

function IDEImageManager:HandleImageRightMenuCutEmpty(event)
	A_LayerManager:HideFromRight(self._image_right_menu)
	local target = self._image_right_menu._user_data
	self._image_right_menu._user_data = nil
	local full_path = g_IDEProject.project.base_path .. "Texture/" .. target._user_data
	local surface = ALittle.System_LoadSurface(full_path)
	if surface ~= nil then
		local width = ALittle.System_GetSurfaceWidth(surface)
		local height = ALittle.System_GetSurfaceHeight(surface)
		local left = 0
		local i = 1
		while true do
			if not(i <= width) then break end
			left = i - 1
			local flag = false
			local j = 1
			while true do
				if not(j <= height) then break end
				local color = ALittle.System_GetSurfacePixel(surface, i - 1, j - 1)
				if color ~= 0 then
					flag = true
					break
				end
				j = j+(1)
			end
			if flag == true then
				break
			end
			i = i+(1)
		end
		local right = 0
		local i = width
		while true do
			if not(i >= 1) then break end
			right = i - 1
			local flag = false
			local j = 1
			while true do
				if not(j <= height) then break end
				local color = ALittle.System_GetSurfacePixel(surface, i - 1, j - 1)
				if color ~= 0 then
					flag = true
					break
				end
				j = j+(1)
			end
			if flag == true then
				break
			end
			i = i+(-1)
		end
		local top = 0
		local j = 1
		while true do
			if not(j <= height) then break end
			top = j - 1
			local flag = false
			local i = 1
			while true do
				if not(i <= width) then break end
				local color = ALittle.System_GetSurfacePixel(surface, i - 1, j - 1)
				if color ~= 0 then
					flag = true
					break
				end
				i = i+(1)
			end
			if flag == true then
				break
			end
			j = j+(1)
		end
		local bottom = 0
		local j = height
		while true do
			if not(j >= 1) then break end
			bottom = j - 1
			local flag = false
			local i = 1
			while true do
				if not(i <= width) then break end
				local color = ALittle.System_GetSurfacePixel(surface, i - 1, j - 1)
				if color ~= 0 then
					flag = true
					break
				end
				i = i+(1)
			end
			if flag == true then
				break
			end
			j = j+(-1)
		end
		if left <= right and top <= bottom then
			local new_width = right - left + 1
			local new_height = bottom - top + 1
			local new_surface = ALittle.System_CreateSurface(new_width, new_height)
			ALittle.System_CutBlitSurface(new_surface, surface, "0,0," .. new_width .. "," .. new_height, left .. "," .. top .. "," .. new_width .. "," .. new_height)
			ALittle.System_SaveSurface(new_surface, full_path)
		end
		ALittle.System_FreeSurface(surface)
	end
end

g_IDEImageManager = IDEImageManager()
