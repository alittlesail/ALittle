-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.GBRMaker == nil then _G.GBRMaker = {} end
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
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
GBRMaker.MainLayerList = Lua.Class(ALittle.DisplayLayout, "GBRMaker.MainLayerList")

function GBRMaker.MainLayerList:Init()
	self._floor_scroll_screen:RemoveAllChild()
	local group = {}
	for index, floor_info in ___ipairs(g_GCenter.cur_file.map_info.floor_list) do
		local info = {}
		info.edit_item = self:CreateFloorEdit(floor_info)
		g_GCenter.cur_edit_layer:AddChild(info.edit_item)
		info.select_item = GBRMaker.g_Control:CreateControl("ide_common_item_radiobutton", info)
		info.select_item._user_data = info
		info.select_item.group = group
		info.select_item.text = floor_info.floor_data.name
		info.select_item:AddEventListener(___all_struct[958494922], self, self.HandleSelectFloor)
		info.select_item:AddEventListener(___all_struct[-641444818], self, self.HandleFloorRButtonDown)
		info.floor_info = floor_info
		self._floor_scroll_screen:AddChild(info.select_item)
		info.edit_item.alpha = 0.5
		if index == 1 then
			info.select_item.selected = true
			info.edit_item.alpha = 1
			g_GCenter.cur_floor = info
		end
	end
end

function GBRMaker.MainLayerList:HandleNewFloorClick(event)
	local cur_file = g_GCenter.cur_file
	if cur_file == nil then
		g_AUITool:ShowNotice("提示", "请先打开文件")
		return
	end
	local x, y = event.target:LocalToGlobal()
	local name = g_AUITool:ShowRename("", x, y + event.target.height, 200)
	if name == "" or name == nil then
		return
	end
	local floor_data = {}
	floor_data.name = name
	floor_data.data = {}
	local floor_info = {}
	floor_info.floor_data = floor_data
	floor_info.file_info = cur_file
	floor_info.visible = true
	floor_info.child_map = {}
	ALittle.List_Insert(cur_file.map_data.floor_list, 1, floor_data)
	ALittle.List_Insert(cur_file.map_info.floor_list, 1, floor_info)
	local group = nil
	if self._floor_scroll_screen.child_count > 0 then
		group = self._floor_scroll_screen.childs[1].group
	else
		group = {}
	end
	local info = {}
	info.edit_item = self:CreateFloorEdit(floor_info)
	g_GCenter.cur_edit_layer:AddChild(info.edit_item, 1)
	info.select_item = GBRMaker.g_Control:CreateControl("ide_common_item_radiobutton", info)
	info.select_item._user_data = info
	info.select_item.group = group
	info.select_item.text = floor_info.floor_data.name
	info.select_item:AddEventListener(___all_struct[958494922], self, self.HandleSelectFloor)
	info.select_item:AddEventListener(___all_struct[-641444818], self, self.HandleFloorRButtonDown)
	info.floor_info = floor_info
	self._floor_scroll_screen:AddChild(info.select_item, 1)
	g_GCenter:SaveCurEdit(false)
end
GBRMaker.MainLayerList.HandleNewFloorClick = Lua.CoWrap(GBRMaker.MainLayerList.HandleNewFloorClick)

function GBRMaker.MainLayerList:HandleSelectFloor(event)
	local info = event.target._user_data
	if event.target.selected then
		info.edit_item.alpha = 1
	else
		info.edit_item.alpha = 0.5
	end
	g_GCenter.cur_floor = info
end

function GBRMaker.MainLayerList:HandleFloorRButtonDown(event)
	local info = event.target._user_data
	local index = self._floor_scroll_screen:GetChildIndex(info.select_item)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("上移", Lua.Bind(self.HandleLayerMoveUp, self, info, index))
	menu:AddItem("下移", Lua.Bind(self.HandleLayerMoveDown, self, info, index))
	menu:AddItem("隐藏", Lua.Bind(self.HandleLayerHide, self, info), not info.floor_info.visible)
	menu:AddItem("显示", Lua.Bind(self.HandleLayerShow, self, info), info.floor_info.visible)
	menu:AddItem("删除", Lua.Bind(self.HandleLayerDelete, self, info, index))
	menu:Show()
end

function GBRMaker.MainLayerList:HandleLayerMoveUp(info, index)
	self._floor_scroll_screen:SetChildIndex(info.select_item, index - 1)
	g_GCenter.cur_edit_layer:SetChildIndex(info.edit_item, index - 1)
	local floor_data = info.floor_info.file_info.map_data.floor_list[index]
	ALittle.List_Remove(info.floor_info.file_info.map_data.floor_list, index)
	ALittle.List_Insert(info.floor_info.file_info.map_data.floor_list, index - 1, floor_data)
	local floor_info = info.floor_info.file_info.map_info.floor_list[index]
	ALittle.List_Remove(info.floor_info.file_info.map_info.floor_list, index)
	ALittle.List_Insert(info.floor_info.file_info.map_info.floor_list, index - 1, floor_info)
	g_GCenter:SaveCurEdit(false)
end

function GBRMaker.MainLayerList:HandleLayerMoveDown(info, index)
	self._floor_scroll_screen:SetChildIndex(info.select_item, index + 1)
	g_GCenter.cur_edit_layer:SetChildIndex(info.edit_item, index + 1)
	local floor_data = info.floor_info.file_info.map_data.floor_list[index]
	ALittle.List_Remove(info.floor_info.file_info.map_data.floor_list, index)
	ALittle.List_Insert(info.floor_info.file_info.map_data.floor_list, index + 1, floor_data)
	local floor_info = info.floor_info.file_info.map_info.floor_list[index]
	ALittle.List_Remove(info.floor_info.file_info.map_info.floor_list, index)
	ALittle.List_Insert(info.floor_info.file_info.map_info.floor_list, index + 1, floor_info)
	g_GCenter:SaveCurEdit(false)
end

function GBRMaker.MainLayerList:HandleLayerHide(info)
	info.select_item.text = info.floor_info.floor_data.name .. "(隐藏)"
	info.edit_item.visible = false
	info.floor_info.visible = false
end

function GBRMaker.MainLayerList:HandleLayerShow(info)
	info.select_item.text = info.floor_info.floor_data.name
	info.edit_item.visible = true
	info.floor_info.visible = true
end

function GBRMaker.MainLayerList:HandleLayerDelete(info, index)
	self._floor_scroll_screen:RemoveChild(info.select_item)
	g_GCenter.cur_edit_layer:RemoveChild(info.edit_item)
	ALittle.List_Remove(info.floor_info.file_info.map_data.floor_list, index)
	ALittle.List_Remove(info.floor_info.file_info.map_info.floor_list, index)
	g_GCenter:SaveCurEdit(false)
end

function GBRMaker.MainLayerList:CreateFloorEdit(floor_info)
	local setting_data = g_GCenter.setting_dialog.data
	local layer = ALittle.DisplayLayout(g_GCenter.control)
	for x, y_data in ___pairs(floor_info.floor_data.data) do
		for y, tex_id in ___pairs(y_data) do
			local image = ALittle.Image(g_GCenter.control)
			image.texture_name = floor_info.file_info.map_data.tex_map[tex_id]
			image.width = setting_data.image_w
			image.height = setting_data.image_h
			local center_x, center_y = GBRMaker.IDECoordVirtual2Show(x, y, setting_data.unit_length)
			image.x = center_x - setting_data.center_x
			image.y = center_y - setting_data.center_y
			layer:AddChild(image)
			local y_info = floor_info.child_map[x]
			if y_info == nil then
				y_info = {}
				floor_info.child_map[x] = y_info
			end
			y_info[y] = image
		end
	end
	return layer
end

function GBRMaker.MainLayerList:UpdateFloorAlpha()
	for index, child in ___ipairs(self._floor_scroll_screen.childs) do
		local info = child._user_data
		if info.select_item.selected then
			info.edit_item.alpha = 1
		else
			info.edit_item.alpha = 0.5
		end
	end
end

end