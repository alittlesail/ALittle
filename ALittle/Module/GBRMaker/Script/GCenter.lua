-- ALittle Generate Lua And Do Not Edit This Line!
module("GBRMaker", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(2142748786, "GBRMaker.CellData", {
name = "GBRMaker.CellData", ns_name = "GBRMaker", rl_name = "CellData", hash_code = 2142748786,
name_list = {"tex_id","mask"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(-869410065, "GBRMaker.FloorData", {
name = "GBRMaker.FloorData", ns_name = "GBRMaker", rl_name = "FloorData", hash_code = -869410065,
name_list = {"name","data"},
type_list = {"string","Map<int,Map<int,GBRMaker.CellData>>"},
option_map = {}
})
ALittle.RegStruct(-1481607580, "GBRMaker.MapData", {
name = "GBRMaker.MapData", ns_name = "GBRMaker", rl_name = "MapData", hash_code = -1481607580,
name_list = {"floor_list","tex_map","tex_max_id","y_max","x_max","nx_max"},
type_list = {"List<GBRMaker.FloorData>","Map<string,int>","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(-1328202806, "GBRMaker.FloorInfo", {
name = "GBRMaker.FloorInfo", ns_name = "GBRMaker", rl_name = "FloorInfo", hash_code = -1328202806,
name_list = {"parent","data","visible"},
type_list = {"GBRMaker.FileSelectItemInfo","GBRMaker.FloorData","bool"},
option_map = {}
})
ALittle.RegStruct(-838616264, "GBRMaker.FileSelectItemInfo", {
name = "GBRMaker.FileSelectItemInfo", ns_name = "GBRMaker", rl_name = "FileSelectItemInfo", hash_code = -838616264,
name_list = {"item","file_path","upper_file_name","map_data","map_info","save"},
type_list = {"ALittle.TextRadioButton","string","string","GBRMaker.MapData","GBRMaker.MapInfo","bool"},
option_map = {}
})
ALittle.RegStruct(339827246, "GBRMaker.MapInfo", {
name = "GBRMaker.MapInfo", ns_name = "GBRMaker", rl_name = "MapInfo", hash_code = 339827246,
name_list = {"floor_list"},
type_list = {"List<GBRMaker.FloorInfo>"},
option_map = {}
})
ALittle.RegStruct(1988329150, "GBRMaker.FloorSelectItemInfo", {
name = "GBRMaker.FloorSelectItemInfo", ns_name = "GBRMaker", rl_name = "FloorSelectItemInfo", hash_code = 1988329150,
name_list = {"select_item","floor_info","edit_item"},
type_list = {"ALittle.TextRadioButton","GBRMaker.FloorInfo","ALittle.DisplayLayout"},
option_map = {}
})
ALittle.RegStruct(-1261197262, "GBRMaker.ImageSelectItemInfo", {
name = "GBRMaker.ImageSelectItemInfo", ns_name = "GBRMaker", rl_name = "ImageSelectItemInfo", hash_code = -1261197262,
name_list = {"item","image","name","button","frame","upper_file_name"},
type_list = {"ALittle.DisplayLayout","ALittle.Image","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayLayout","string"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
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

g_GConfig = nil
GCenter = Lua.Class(nil, "GBRMaker.GCenter")

function GCenter:Ctor()
end

function GCenter:Setup()
	g_GConfig = ALittle.CreateConfigSystem(g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1, 2)
	self._main_layer = ALittle.DisplayLayout(g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	g_LayerGroup:AddChild(self._dialog_layer, nil)
	self._setting_dialog = g_Control:CreateControl("main_setting_dialog", self)
	A_LayerManager:AddToModal(self._setting_dialog)
	g_Control:CreateControl("main_scene", self, self._main_layer)
	A_UISystem.keydown_callback = Lua.Bind(self.HandleKeyDown, self)
	self._setting_project_name_input.text = g_GConfig:GetString("project_name", "")
	self._setting_texture_path_input.text = g_GConfig:GetString("texture_path", "")
	self._unit_empty_name_input.text = g_GConfig:GetString("empty_name", "")
	self._setting_data_path_input.text = g_GConfig:GetString("data_path", "")
	self._unit_width_input.text = g_GConfig:GetInt("unit_width", 100)
	self._unit_height_input.text = g_GConfig:GetInt("unit_height", 100)
	self._unit_left_input.text = g_GConfig:GetInt("unit_left", 0)
	self._unit_right_input.text = g_GConfig:GetInt("unit_right", 0)
	self._unit_top_input.text = g_GConfig:GetInt("unit_top", 0)
	self._unit_bottom_input.text = g_GConfig:GetInt("unit_bottom", 0)
	local module_path = "Module/" .. self._setting_project_name_input.text
	if ALittle.File_GetFileAttr(module_path) == nil or ALittle.File_GetFileAttr(module_path .. "/Texture/" .. self._setting_texture_path_input.text) == nil or ALittle.File_GetFileAttr(module_path .. "/Texture/" .. self._setting_texture_path_input.text .. "/" .. self._unit_empty_name_input.text) == nil or ALittle.File_GetFileAttr(module_path .. "/Other/" .. self._setting_data_path_input.text) == nil then
		self._setting_dialog.visible = true
	else
		self._control = ALittle.ControlSystem(self._setting_project_name_input.text)
		self._real_size = 100
		self._file_base_path = module_path .. "/Other/" .. self._setting_data_path_input.text
		self._tex_name_base_path = self._setting_texture_path_input.text
		self._texture_base_path = module_path .. "/Texture/" .. self._setting_texture_path_input.text
		self:RefreshTexture()
		self:RefreshFile()
	end
end

function GCenter:HandleShowSettingDialog(event)
	self._setting_dialog.visible = true
end

function GCenter:HandleSettingCancelClick(event)
	self._setting_dialog.visible = false
end

function GCenter:HandleSettingConfirmClick(event)
	local unit_width = ALittle.Math_ToInt(self._unit_width_input.text)
	local unit_height = ALittle.Math_ToInt(self._unit_height_input.text)
	local unit_left = ALittle.Math_ToInt(self._unit_left_input.text)
	local unit_right = ALittle.Math_ToInt(self._unit_right_input.text)
	local unit_top = ALittle.Math_ToInt(self._unit_top_input.text)
	local unit_bottom = ALittle.Math_ToInt(self._unit_bottom_input.text)
	if unit_width == nil or unit_width < 0 or unit_height == nil or unit_height < 0 or unit_left == nil or unit_left < 0 or unit_right == nil or unit_right < 0 or unit_top == nil or unit_top < 0 or unit_bottom == nil or unit_bottom < 0 then
		g_IDETool:ShowNotice("提示", "请输入正整数")
		return
	end
	local module_path = "Module/" .. self._setting_project_name_input.text
	if ALittle.File_GetFileAttr(module_path) == nil then
		g_IDETool:ShowNotice("提示", "项目不存在")
		return
	end
	if ALittle.File_GetFileAttr(module_path .. "/Texture/" .. self._setting_texture_path_input.text) == nil then
		g_IDETool:ShowNotice("提示", "格子图片路径不存在")
		return
	end
	if ALittle.File_GetFileAttr(module_path .. "/Other/" .. self._setting_data_path_input.text) == nil then
		g_IDETool:ShowNotice("提示", "场景数据路径不存在")
		return
	end
	if ALittle.File_GetFileAttr(module_path .. "/Texture/" .. self._setting_texture_path_input.text .. "/" .. self._unit_empty_name_input.text) == nil then
		g_IDETool:ShowNotice("提示", "空格子图片不存在")
		return
	end
	self._file_base_path = module_path .. "/Other/" .. self._setting_data_path_input.text
	self._tex_name_base_path = self._setting_texture_path_input.text
	self._texture_base_path = module_path .. "/Texture/" .. self._setting_texture_path_input.text
	g_GConfig:SetConfig("unit_width", unit_width)
	g_GConfig:SetConfig("unit_height", unit_height)
	g_GConfig:SetConfig("unit_left", unit_left)
	g_GConfig:SetConfig("unit_right", unit_right)
	g_GConfig:SetConfig("unit_top", unit_top)
	g_GConfig:SetConfig("unit_bottom", unit_bottom)
	g_GConfig:SetConfig("project_name", self._setting_project_name_input.text)
	g_GConfig:SetConfig("texture_path", self._setting_texture_path_input.text)
	g_GConfig:SetConfig("empty_name", self._unit_empty_name_input.text)
	g_GConfig:SetConfig("data_path", self._setting_data_path_input.text)
	self._setting_dialog.visible = false
	self._control = ALittle.ControlSystem(self._setting_project_name_input.text)
	self:RefreshTexture()
	self:RefreshFile()
end

function GCenter:HandleFileNewClick(event)
	local x, y = event.target:LocalToGlobal()
	g_IDETool:ShowRename(Lua.Bind(self.HandleNewFile, self), "", x, y + event.target.height, 200)
end

function GCenter:HandleNewFile(file_name)
	if file_name == "" then
		return
	end
	local check, error = IDEUtility_CheckResourceName(file_name)
	if not check then
		g_IDETool:ShowNotice("提示", error)
		return
	end
	local file_path = self._file_base_path .. "/" .. file_name .. ".map"
	if ALittle.File_GetFileAttr(file_path) ~= nil then
		g_IDETool:ShowNotice("提示", "文件已存在")
		return
	end
	ALittle.File_WriteTextToFile("", file_path)
end

function GCenter:HandleSelectFile(event)
	if not event.target.selected then
		return
	end
	self:SaveCurEdit(true)
	local info = event.target._user_data
	if info.map_data == nil then
		local rflct = ___all_struct[-1481607580]
		local factory = __CPPAPIMessageReadFactory()
		if not factory:ReadFromStdFile(info.file_path) then
			return
		end
		local invoke_info = ALittle.CreateMessageInfo(rflct.name)
		if invoke_info == nil then
			return
		end
		info.map_data = ALittle.PS_ReadMessage(factory, invoke_info, nil, factory:GetDataSize())
		info.map_info = {}
		info.map_info.floor_list = {}
		for index, floor_data in ___ipairs(info.map_data.floor_list) do
			local floor_info = {}
			floor_info.data = floor_data
			floor_info.parent = info
			floor_info.visible = true
			ALittle.List_Push(info.map_info.floor_list, floor_info)
		end
	end
	self:StartEdit(info)
end

function GCenter:RefreshFile()
	self._file_cache_list = {}
	self._file_radio_group = {}
	self._file_scroll_screen:RemoveAllChild()
	if ALittle.File_GetFileAttr(self._file_base_path) == nil then
		return
	end
	local file_list = ALittle.File_GetFileListByDir(self._file_base_path)
	ALittle.List_Sort(file_list)
	for index, file_path in ___ipairs(file_list) do
		local rel_path = ALittle.String_Sub(file_path, ALittle.String_Len(self._file_base_path) + 2)
		local info = {}
		info.item = g_Control:CreateControl("ide_common_item_radiobutton", info)
		info.item._user_data = info
		info.item.group = self._file_radio_group
		info.item.text = ALittle.File_GetJustFileNameByPath(rel_path)
		info.upper_file_name = ALittle.String_Upper(info.item.text)
		info.file_path = file_path
		info.save = true
		info.item:AddEventListener(___all_struct[958494922], self, self.HandleSelectFile)
		info.item.drag_trans_target = self._file_scroll_screen
		self._file_cache_list[index] = info
	end
	self:HandleFileSearchClick(nil)
end

function GCenter:HandleFileSearchClick(event)
	self._file_scroll_screen:RemoveAllChild()
	local upper_key = ALittle.String_Upper(self._file_search_key.text)
	for index, info in ___ipairs(self._file_cache_list) do
		if ALittle.String_Find(info.upper_file_name, upper_key) ~= nil then
			self._file_scroll_screen:AddChild(info.item)
		end
	end
end

function GCenter:RefreshTexture()
	self._image_cache_list = {}
	self._texture_scroll_list:RemoveAllChild()
	if ALittle.File_GetFileAttr(self._texture_base_path) == nil then
		return
	end
	local file_list = ALittle.File_GetFileListByDir(self._texture_base_path)
	ALittle.List_Sort(file_list)
	for index, file_path in ___ipairs(file_list) do
		local rel_path = ALittle.String_Sub(file_path, ALittle.String_Len(self._texture_base_path) + 2)
		local texture_name = self._tex_name_base_path .. "/" .. rel_path
		local info = {}
		info.item = g_Control:CreateControl("ide_image_select_item", info)
		info.button._user_data = info
		info.image:SetTextureCut(file_path, ALittle.Math_Floor(info.frame.width), ALittle.Math_Floor(info.frame.height), true)
		info.name.text = ALittle.File_GetJustFileNameByPath(rel_path)
		info.upper_file_name = ALittle.String_Upper(info.name.text)
		info.button.drag_trans_target = self._texture_scroll_list
		self._image_cache_list[index] = info
	end
	self:HandleTextureSearchClick(nil)
end

function GCenter:HandleTextureSearchClick(event)
	self._texture_scroll_list:RemoveAllChild()
	local upper_key = ALittle.String_Upper(self._texture_search_key.text)
	local col_count = ALittle.Math_Floor(self._texture_scroll_list.width / self._real_size)
	local remain_count = 0
	local container = nil
	for index, info in ___ipairs(self._image_cache_list) do
		if ALittle.String_Find(info.upper_file_name, upper_key) ~= nil then
			if remain_count == 0 then
				container = ALittle.Linear(g_Control)
				container.type = 1
				container.height = info.item.height
				self._texture_scroll_list:AddChild(container)
				container:AddChild(info.item)
				remain_count = col_count - 1
			else
				remain_count = remain_count - 1
				container:AddChild(info.item)
			end
		end
	end
end

function GCenter:HandleNewFloorClick(event)
	if self._cur_edit == nil then
		g_IDETool:ShowNotice("提示", "请先打开文件")
		return
	end
	local x, y = event.target:LocalToGlobal()
	g_IDETool:ShowRename(Lua.Bind(self.HandleNewFloor, self), "", x, y + event.target.height, 200)
end

function GCenter:HandleNewFloor(name)
	if name == "" then
		return
	end
	local floor_data = {}
	floor_data.name = name
	local floor_info = {}
	floor_info.data = floor_data
	floor_info.parent = self._cur_edit
	floor_info.visible = true
	ALittle.List_Insert(self._cur_edit.map_data.floor_list, 1, floor_data)
	ALittle.List_Insert(self._cur_edit.map_info.floor_list, 1, floor_info)
	local group = nil
	if self._floor_scroll_screen.child_count > 0 then
		group = self._floor_scroll_screen.childs[1].group
	else
		group = {}
	end
	local info = {}
	info.select_item = g_Control:CreateControl("ide_common_item_radiobutton", info)
	info.select_item._user_data = info
	info.select_item.group = group
	info.select_item.text = floor_info.data.name
	info.select_item:AddEventListener(___all_struct[958494922], self, self.HandleSelectFloor)
	info.select_item:AddEventListener(___all_struct[-641444818], self, self.HandleFloorRButtonDown)
	info.floor_info = floor_info
	self._floor_scroll_screen:AddChild(info.select_item, 1)
	self:SaveCurEdit(false)
end

function GCenter:HandleSelectFloor(event)
	local info = event.target._user_data
	if event.target.selected then
		info.edit_item.alpha = 1
	else
		info.edit_item.alpha = 0.5
	end
end

function GCenter:HandleFloorRButtonDown(event)
	if self._floor_right_menu == nil then
		self._floor_right_menu = g_Control:CreateControl("ide_floor_right_menu", self)
	end
	self._floor_right_menu.x = A_UISystem.mouse_x
	self._floor_right_menu.y = A_UISystem.mouse_y
	A_LayerManager:ShowFromRight(self._floor_right_menu)
	self._floor_right_menu._user_data = event.target._user_data
	local info = event.target._user_data
	self._floor_right_hide_btn.disabled = not info.floor_info.visible
	self._floor_right_show_btn.disabled = info.floor_info.visible
end

function GCenter:HandleFloorRightMenu(event)
	local info = self._floor_right_menu._user_data
	self._floor_right_menu._user_data = nil
	A_LayerManager:HideFromRight(self._floor_right_menu)
	local index = self._floor_scroll_screen:GetChildIndex(info.select_item)
	if event.target.text == "上移" then
		self._floor_scroll_screen:SetChildIndex(info.select_item, index - 1)
		self._edit_scroll_screen:SetChildIndex(info.edit_item, index - 1)
		local floor_data = info.floor_info.parent.map_data.floor_list[index]
		ALittle.List_Remove(info.floor_info.parent.map_data.floor_list, index)
		ALittle.List_Insert(info.floor_info.parent.map_data.floor_list, index - 1, floor_data)
		local floor_info = info.floor_info.parent.map_info.floor_list[index]
		ALittle.List_Remove(info.floor_info.parent.map_info.floor_list, index)
		ALittle.List_Insert(info.floor_info.parent.map_info.floor_list, index - 1, floor_info)
		self:SaveCurEdit(false)
	elseif event.target.text == "下移" then
		self._floor_scroll_screen:SetChildIndex(info.select_item, index + 1)
		self._edit_scroll_screen:SetChildIndex(info.edit_item, index + 1)
		local floor_data = info.floor_info.parent.map_data.floor_list[index]
		ALittle.List_Remove(info.floor_info.parent.map_data.floor_list, index)
		ALittle.List_Insert(info.floor_info.parent.map_data.floor_list, index + 1, floor_data)
		local floor_info = info.floor_info.parent.map_info.floor_list[index]
		ALittle.List_Remove(info.floor_info.parent.map_info.floor_list, index)
		ALittle.List_Insert(info.floor_info.parent.map_info.floor_list, index + 1, floor_info)
		self:SaveCurEdit(false)
	elseif event.target.text == "隐藏" then
		info.select_item.text = info.floor_info.data.name .. "(隐藏)"
		info.edit_item.visible = false
		info.floor_info.visible = false
	elseif event.target.text == "显示" then
		info.select_item.text = info.floor_info.data.name
		info.edit_item.visible = true
		info.floor_info.visible = true
	elseif event.target.text == "删除" then
		self._floor_scroll_screen:RemoveChild(info.select_item)
		self._edit_scroll_screen:RemoveChild(info.edit_item)
		ALittle.List_Remove(info.floor_info.parent.map_data.floor_list, index)
		ALittle.List_Remove(info.floor_info.parent.map_info.floor_list, index)
		self:SaveCurEdit(false)
	end
end

function GCenter:StartEdit(file_info)
	self._cur_edit = file_info
	self._edit_title.text = file_info.item.text
	self._floor_scroll_screen:RemoveAllChild()
	self._edit_scroll_screen:RemoveAllChild()
	local grid_layer = ALittle.DisplayLayout(g_Control)
	local x = 0
	while true do
		if not(x < file_info.map_data.x_max) then break end
		local y = 0
		while true do
			if not(y < file_info.map_data.y_max) then break end
			y = y+(1)
		end
		x = x+(1)
	end
	local x = file_info.map_data.nx_max
	while true do
		if not(x < 0) then break end
		local y = 0
		while true do
			if not(y < file_info.map_data.y_max) then break end
			y = y+(1)
		end
		x = x+(1)
	end
	self._edit_scroll_screen:AddChild(grid_layer)
	local group = {}
	for index, floor_info in ___ipairs(self._cur_edit.map_info.floor_list) do
		local info = {}
		info.select_item = g_Control:CreateControl("ide_common_item_radiobutton", info)
		info.select_item._user_data = info
		info.select_item.group = group
		info.select_item.text = floor_info.data.name
		info.select_item:AddEventListener(___all_struct[958494922], self, self.HandleSelectFloor)
		info.select_item:AddEventListener(___all_struct[-641444818], self, self.HandleFloorRButtonDown)
		info.floor_info = floor_info
		self._floor_scroll_screen:AddChild(info.select_item)
		info.edit_item = self:CreateFloorEdit(info)
		self._floor_scroll_screen:AddChild(info.edit_item)
	end
end

function GCenter:CreateFloorEdit(info)
	for row, col_info in ___pairs(info.floor_info.data.data) do
		for col, cell in ___pairs(col_info) do
		end
	end
	return nil
end

function GCenter:SaveCurEdit(save)
	if self._cur_edit == nil then
		return
	end
	if self._cur_edit.save == save then
		return
	end
	if not save then
		self._cur_edit.save = false
		self._edit_title.text = self._cur_edit.item.text .. "*"
		return
	end
	local rflct = ___all_struct[-1481607580]
	local factory = __CPPAPIMessageWriteFactory()
	local invoke_info = ALittle.CreateMessageInfo(rflct.name)
	if invoke_info == nil then
		return
	end
	ALittle.PS_WriteMessage(factory, invoke_info, nil, self._cur_edit.map_data)
	if not factory:WriteToStdFile(self._cur_edit.file_path) then
		g_IDETool:ShowNotice("提示", "保存失败")
		return
	end
	self._cur_edit.save = true
	self._edit_title.text = self._cur_edit.item.text
end

function GCenter:HandleKeyDown(mod, sym, scancode)
	if sym == 115 and ALittle.BitAnd(mod, 0x00c0) ~= 0 then
		self:SaveCurEdit(true)
	end
end

function GCenter:Shutdown()
end

_G.g_GCenter = GCenter()
