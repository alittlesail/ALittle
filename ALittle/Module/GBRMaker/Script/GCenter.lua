-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.GBRMaker == nil then _G.GBRMaker = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1988329150, "GBRMaker.FloorSelectItemInfo", {
name = "GBRMaker.FloorSelectItemInfo", ns_name = "GBRMaker", rl_name = "FloorSelectItemInfo", hash_code = 1988329150,
name_list = {"select_item","floor_info","edit_item"},
type_list = {"ALittle.TextRadioButton","GBRMaker.FloorInfo","ALittle.DisplayLayout"},
option_map = {}
})
ALittle.RegStruct(1883782801, "ALittle.UILButtonDownEvent", {
name = "ALittle.UILButtonDownEvent", ns_name = "ALittle", rl_name = "UILButtonDownEvent", hash_code = 1883782801,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-1481607580, "GBRMaker.MapData", {
name = "GBRMaker.MapData", ns_name = "GBRMaker", rl_name = "MapData", hash_code = -1481607580,
name_list = {"floor_list","tex_map","y_max","x_max","nx_max"},
type_list = {"List<GBRMaker.FloorData>","Map<int,string>","int","int","int"},
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
ALittle.RegStruct(1337289812, "ALittle.UIButtonDragEvent", {
name = "ALittle.UIButtonDragEvent", ns_name = "ALittle", rl_name = "UIButtonDragEvent", hash_code = 1337289812,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(-1328202806, "GBRMaker.FloorInfo", {
name = "GBRMaker.FloorInfo", ns_name = "GBRMaker", rl_name = "FloorInfo", hash_code = -1328202806,
name_list = {"file_info","floor_data","visible","child_map"},
type_list = {"GBRMaker.FileSelectItemInfo","GBRMaker.FloorData","bool","Map<int,Map<int,ALittle.Image>>"},
option_map = {}
})
ALittle.RegStruct(1301789264, "ALittle.UIButtonDragBeginEvent", {
name = "ALittle.UIButtonDragBeginEvent", ns_name = "ALittle", rl_name = "UIButtonDragBeginEvent", hash_code = 1301789264,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(-1261197262, "GBRMaker.ImageSelectItemInfo", {
name = "GBRMaker.ImageSelectItemInfo", ns_name = "GBRMaker", rl_name = "ImageSelectItemInfo", hash_code = -1261197262,
name_list = {"item","image","name","button","frame","upper_file_name","file_path"},
type_list = {"ALittle.DisplayLayout","ALittle.Image","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayLayout","string","string"},
option_map = {}
})
ALittle.RegStruct(996973755, "GBRMaker.BrushSelectItemInfo", {
name = "GBRMaker.BrushSelectItemInfo", ns_name = "GBRMaker", rl_name = "BrushSelectItemInfo", hash_code = 996973755,
name_list = {"item","image","name","button","frame","upper_file_name","texture_name"},
type_list = {"ALittle.DisplayLayout","ALittle.Image","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayLayout","string","string"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-869410065, "GBRMaker.FloorData", {
name = "GBRMaker.FloorData", ns_name = "GBRMaker", rl_name = "FloorData", hash_code = -869410065,
name_list = {"name","data"},
type_list = {"string","Map<int,Map<int,int>>"},
option_map = {}
})
ALittle.RegStruct(-838616264, "GBRMaker.FileSelectItemInfo", {
name = "GBRMaker.FileSelectItemInfo", ns_name = "GBRMaker", rl_name = "FileSelectItemInfo", hash_code = -838616264,
name_list = {"item","file_path","upper_file_name","map_data","map_info","save"},
type_list = {"ALittle.TextRadioButton","string","string","GBRMaker.MapData","GBRMaker.MapInfo","bool"},
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
ALittle.RegStruct(-439548260, "ALittle.UILongButtonDownEvent", {
name = "ALittle.UILongButtonDownEvent", ns_name = "ALittle", rl_name = "UILongButtonDownEvent", hash_code = -439548260,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(339827246, "GBRMaker.MapInfo", {
name = "GBRMaker.MapInfo", ns_name = "GBRMaker", rl_name = "MapInfo", hash_code = 339827246,
name_list = {"floor_list","tex_map","tex_max_id"},
type_list = {"List<GBRMaker.FloorInfo>","Map<string,int>","int"},
option_map = {}
})

GBRMaker.g_GConfig = nil
GBRMaker.GCenter = Lua.Class(nil, "GBRMaker.GCenter")

function GBRMaker.GCenter:Ctor()
end

function GBRMaker.GCenter:Setup()
	GBRMaker.g_GConfig = ALittle.CreateConfigSystem(GBRMaker.g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1, 2)
	self._main_layer = ALittle.DisplayLayout(GBRMaker.g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	GBRMaker.g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(GBRMaker.g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	GBRMaker.g_LayerGroup:AddChild(self._dialog_layer, nil)
	self._setting_dialog = GBRMaker.g_Control:CreateControl("main_setting_dialog", self)
	self._setting_dialog:AddEventListener(___all_struct[-1302885650], self, self.HandleSettingChanged)
	A_LayerManager:AddToModal(self._setting_dialog)
	GBRMaker.g_Control:CreateControl("main_scene", self, self._main_layer)
	self._right_grad3_ud.up_size = GBRMaker.g_GConfig:GetDouble("right_grid3_up_size", self._right_grad3_ud.up_size)
	self._main_grid3_lr.down_size = GBRMaker.g_GConfig:GetDouble("main_grid3_down_size", self._main_grid3_lr.down_size)
	local tool_group = {}
	self._tool_brush.group = tool_group
	self._tool_erase.group = tool_group
	self._tool_scale.group = tool_group
	self._tool_drag.group = tool_group
	self._tool_brush.selected = true
	self._layer_brush_info.visible = true
	self._layer_drag_info.visible = false
	self._layer_scale_info.visible = false
	self._layer_erase_info.visible = false
	A_UISystem.keydown_callback = Lua.Bind(self.HandleKeyDown, self)
	local setting_data = self._setting_dialog.data
	local module_path = "Module/" .. setting_data.project_name
	if ALittle.File_GetFileAttr(module_path) == nil or ALittle.File_GetFileAttr(module_path .. "/Texture/" .. setting_data.texture_path) == nil or ALittle.File_GetFileAttr(module_path .. "/Texture/" .. setting_data.texture_path .. "/" .. setting_data.empty_name) == nil or ALittle.File_GetFileAttr(module_path .. "/Other/" .. setting_data.data_path) == nil then
		self._setting_dialog.visible = true
	else
		self._control = ALittle.ControlSystem(setting_data.project_name)
		self._real_size = 100
		self._file_base_path = module_path .. "/Other/" .. setting_data.data_path
		self._tex_name_base_path = setting_data.texture_path .. "/"
		self._texture_base_path = module_path .. "/Texture/" .. setting_data.texture_path
		self:RefreshTexture()
		self:RefreshFile()
	end
end

function GBRMaker.GCenter:HandleShowSettingDialog(event)
	self._setting_dialog.visible = true
end

function GBRMaker.GCenter:HandleSettingChanged(event)
	local module_path = "Module/" .. event.data.project_name
	self._file_base_path = module_path .. "/Other/" .. event.data.data_path
	self._tex_name_base_path = event.data.texture_path .. "/"
	self._texture_base_path = module_path .. "/Texture/" .. event.data.texture_path
	self._control = ALittle.ControlSystem(event.data.project_name)
	self:RefreshTexture()
	self:RefreshFile()
end

function GBRMaker.GCenter:HandleFileNewClick(event)
	local x, y = event.target:LocalToGlobal()
	local file_name = g_AUITool:ShowRename("", x, y + event.target.height, 200)
	if file_name == "" or file_name == nil then
		return
	end
	local check, error = GBRMaker.IDEUtility_CheckResourceName(file_name)
	if not check then
		g_AUITool:ShowNotice("提示", error)
		return
	end
	local file_path = self._file_base_path .. "/" .. file_name .. ".map"
	if ALittle.File_GetFileAttr(file_path) ~= nil then
		g_AUITool:ShowNotice("提示", "文件已存在")
		return
	end
	ALittle.File_WriteTextToFile("", file_path)
end
GBRMaker.GCenter.HandleFileNewClick = Lua.CoWrap(GBRMaker.GCenter.HandleFileNewClick)

function GBRMaker.GCenter:HandleSelectFile(event)
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
		info.map_info.tex_map = {}
		info.map_info.tex_max_id = 0
		for id, path in ___pairs(info.map_data.tex_map) do
			info.map_info.tex_map[path] = id
			if info.map_info.tex_max_id < id then
				info.map_info.tex_max_id = id
			end
		end
		info.map_info.floor_list = {}
		for index, floor_data in ___ipairs(info.map_data.floor_list) do
			local floor_info = {}
			floor_info.floor_data = floor_data
			floor_info.file_info = info
			floor_info.visible = true
			floor_info.child_map = {}
			ALittle.List_Push(info.map_info.floor_list, floor_info)
		end
	end
	self:StartEdit(info)
end

function GBRMaker.GCenter:RefreshFile()
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
		info.item = GBRMaker.g_Control:CreateControl("ide_common_item_radiobutton", info)
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

function GBRMaker.GCenter:HandleFileSearchClick(event)
	self._file_scroll_screen:RemoveAllChild()
	local upper_key = ALittle.String_Upper(self._file_search_key.text)
	for index, info in ___ipairs(self._file_cache_list) do
		if ALittle.String_Find(info.upper_file_name, upper_key) ~= nil then
			self._file_scroll_screen:AddChild(info.item)
		end
	end
end

function GBRMaker.GCenter:RefreshTexture()
	self._image_cache_list = {}
	self._texture_scroll_list:RemoveAllChild()
	if ALittle.File_GetFileAttr(self._texture_base_path) == nil then
		return
	end
	local file_list = ALittle.File_GetFileListByDir(self._texture_base_path)
	ALittle.List_Sort(file_list)
	for index, file_path in ___ipairs(file_list) do
		local rel_path = ALittle.String_Sub(file_path, ALittle.String_Len(self._texture_base_path) + 2)
		local texture_name = self._tex_name_base_path .. rel_path
		local info = {}
		info.item = GBRMaker.g_Control:CreateControl("ide_image_select_item", info)
		info.button._user_data = info
		info.image:SetTextureCut(file_path, ALittle.Math_Floor(info.frame.width), ALittle.Math_Floor(info.frame.height), true)
		info.name.text = ALittle.File_GetJustFileNameByPath(rel_path)
		info.upper_file_name = ALittle.String_Upper(info.name.text)
		info.file_path = file_path
		info.button.drag_trans_target = self._texture_scroll_list
		info.button:AddEventListener(___all_struct[-449066808], self, self.HandleTextureSelectClick)
		self._image_cache_list[index] = info
	end
	self:HandleTextureSearchClick(nil)
end

function GBRMaker.GCenter:HandleTextureSearchClick(event)
	self._texture_scroll_list:RemoveAllChild()
	local upper_key = ALittle.String_Upper(self._texture_search_key.text)
	local col_count = ALittle.Math_Floor(self._texture_scroll_list.width / self._real_size)
	local remain_count = 0
	local container = nil
	for index, info in ___ipairs(self._image_cache_list) do
		if ALittle.String_Find(info.upper_file_name, upper_key) ~= nil then
			if remain_count == 0 then
				container = ALittle.Linear(GBRMaker.g_Control)
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

function GBRMaker.GCenter:HandleTextureSelectClick(event)
	local ctrl = A_UISystem.sym_map[1073742048]
	if ctrl == nil then
		self._brush_scroll_screen:RemoveAllChild()
	end
	local image_info = event.target._user_data
	local rel_path = ALittle.String_Sub(image_info.file_path, ALittle.String_Len(self._texture_base_path) + 2)
	local texture_name = self._tex_name_base_path .. rel_path
	for index, child in ___ipairs(self._brush_scroll_screen.childs) do
		local info = child._user_data
		if info.texture_name == texture_name then
			return
		end
	end
	local info = {}
	info.item = GBRMaker.g_Control:CreateControl("ide_image_select_item", info)
	info.button._user_data = info
	info.item._user_data = info
	info.image:SetTextureCut(image_info.file_path, ALittle.Math_Floor(info.frame.width), ALittle.Math_Floor(info.frame.height), true)
	info.name.text = ALittle.File_GetJustFileNameByPath(rel_path)
	info.upper_file_name = ALittle.String_Upper(info.name.text)
	info.texture_name = texture_name
	info.button.drag_trans_target = self._brush_scroll_screen
	info.button:AddEventListener(___all_struct[-449066808], self, self.HandleBrushCancelClick)
	info.button:AddEventListener(___all_struct[-439548260], self, self.HandleBrushAllCancelClick)
	self._brush_scroll_screen:AddChild(info.item)
end

function GBRMaker.GCenter:HandleBrushCancelClick(event)
	local info = event.target._user_data
	self._brush_scroll_screen:RemoveChild(info.item)
end

function GBRMaker.GCenter:HandleBrushAllCancelClick(event)
	self._brush_scroll_screen:RemoveAllChild()
end

function GBRMaker.GCenter:EraseCell(floor, virtual_x, virtual_y)
	if floor == nil then
		return
	end
	do
		local y_info = floor.floor_info.child_map[virtual_x]
		if y_info ~= nil and y_info[virtual_y] ~= nil then
			floor.edit_item:RemoveChild(y_info[virtual_y])
			y_info[virtual_y] = nil
			if ALittle.IsEmpty(y_info) then
				floor.floor_info.child_map[virtual_x] = nil
			end
		end
	end
	do
		local y_data = floor.floor_info.floor_data.data[virtual_x]
		if y_data ~= nil then
			y_data[virtual_y] = nil
			if ALittle.IsEmpty(y_data) then
				floor.floor_info.floor_data.data[virtual_x] = nil
			end
		end
	end
end

function GBRMaker.GCenter:SetCell(file, floor, virtual_x, virtual_y, info)
	local tex_id = file.map_info.tex_map[info.texture_name]
	if tex_id == nil then
		file.map_info.tex_max_id = file.map_info.tex_max_id + 1
		tex_id = file.map_info.tex_max_id
		file.map_info.tex_map[info.texture_name] = tex_id
		file.map_data.tex_map[tex_id] = info.texture_name
	end
	do
		local y_info = floor.floor_info.child_map[virtual_x]
		if y_info == nil then
			y_info = {}
			floor.floor_info.child_map[virtual_x] = y_info
		end
		local setting_data = self._setting_dialog.data
		local image = ALittle.Image(self._control)
		image.texture_name = info.texture_name
		image.width = setting_data.unit_width
		image.height = setting_data.unit_height
		local show_x, show_y = GBRMaker.IDECoordVirtual2Show(virtual_x, virtual_y, setting_data.unit_real_width, setting_data.unit_width, setting_data.unit_real_height, setting_data.unit_height)
		image.x = show_x
		image.y = show_y
		floor.edit_item:AddChild(image)
		y_info[virtual_y] = image
	end
	do
		local y_data = floor.floor_info.floor_data.data[virtual_x]
		if y_data == nil then
			y_data = {}
			floor.floor_info.floor_data.data[virtual_x] = y_data
		end
		y_data[virtual_y] = tex_id
	end
	self:SaveCurEdit(false)
end

function GBRMaker.GCenter:OverWriteCell(file, floor, virtual_x, virtual_y)
	self:EraseCell(floor, virtual_x, virtual_y)
	local index = ALittle.Math_RandomInt(1, self._brush_scroll_screen.child_count)
	local info = self._brush_scroll_screen.childs[index]._user_data
	self:SetCell(file, floor, virtual_x, virtual_y, info)
end

function GBRMaker.GCenter:HandleBrushQuadLButtonDown(event)
	if self._brush_scroll_screen.child_count == 0 then
		return
	end
	if self._cur_file == nil then
		return
	end
	if self._cur_floor == nil then
		return
	end
	local setting_data = self._setting_dialog.data
	local virtual_x, virtual_y = GBRMaker.IDECoordShow2Virtual(event.rel_x, event.rel_y, setting_data.unit_real_width, setting_data.unit_width, setting_data.unit_real_height, setting_data.unit_height)
	self:OverWriteCell(self._cur_file, self._cur_floor, virtual_x, virtual_y)
end

function GBRMaker.GCenter:HandleBrushQuadDragBegin(event)
	self._cur_brush_virtual_x = nil
	self._cur_brush_virtual_y = nil
end

function GBRMaker.GCenter:HandleBrushQuadDrag(event)
	if self._brush_scroll_screen.child_count == 0 then
		return
	end
	if self._cur_file == nil then
		return
	end
	if self._cur_floor == nil then
		return
	end
	local setting_data = self._setting_dialog.data
	local virtual_x, virtual_y = GBRMaker.IDECoordShow2Virtual(event.rel_x, event.rel_y, setting_data.unit_real_width, setting_data.unit_width, setting_data.unit_real_height, setting_data.unit_height)
	if self._cur_brush_virtual_x == virtual_x and self._cur_brush_virtual_y == virtual_y then
		return
	end
	self._cur_brush_virtual_x = virtual_x
	self._cur_brush_virtual_y = virtual_y
	self:OverWriteCell(self._cur_file, self._cur_floor, virtual_x, virtual_y)
end

function GBRMaker.GCenter:HandleEraseQuadLButtonDown(event)
	if self._cur_floor == nil then
		return
	end
	local setting_data = self._setting_dialog.data
	local virtual_x, virtual_y = GBRMaker.IDECoordShow2Virtual(event.rel_x, event.rel_y, setting_data.unit_real_width, setting_data.unit_width, setting_data.unit_real_height, setting_data.unit_height)
	self:EraseCell(self._cur_floor, virtual_x, virtual_y)
end

function GBRMaker.GCenter:HandleEraseQuadDragBegin(event)
	self._cur_erase_virtual_x = nil
	self._cur_erase_virtual_y = nil
end

function GBRMaker.GCenter:HandleEraseQuadDrag(event)
	if self._cur_floor == nil then
		return
	end
	local setting_data = self._setting_dialog.data
	local virtual_x, virtual_y = GBRMaker.IDECoordShow2Virtual(event.rel_x, event.rel_y, setting_data.unit_real_width, setting_data.unit_width, setting_data.unit_real_height, setting_data.unit_height)
	if self._cur_erase_virtual_x == virtual_x and self._cur_erase_virtual_y == virtual_y then
		return
	end
	self._cur_erase_virtual_x = virtual_x
	self._cur_erase_virtual_y = virtual_y
	self:EraseCell(self._cur_floor, virtual_x, virtual_y)
end

function GBRMaker.GCenter:HandleNewFloorClick(event)
	if self._cur_file == nil then
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
	local floor_info = {}
	floor_info.floor_data = floor_data
	floor_info.file_info = self._cur_file
	floor_info.visible = true
	ALittle.List_Insert(self._cur_file.map_data.floor_list, 1, floor_data)
	ALittle.List_Insert(self._cur_file.map_info.floor_list, 1, floor_info)
	local group = nil
	if self._floor_scroll_screen.child_count > 0 then
		group = self._floor_scroll_screen.childs[1].group
	else
		group = {}
	end
	local info = {}
	info.select_item = GBRMaker.g_Control:CreateControl("ide_common_item_radiobutton", info)
	info.select_item._user_data = info
	info.select_item.group = group
	info.select_item.text = floor_info.floor_data.name
	info.select_item:AddEventListener(___all_struct[958494922], self, self.HandleSelectFloor)
	info.select_item:AddEventListener(___all_struct[-641444818], self, self.HandleFloorRButtonDown)
	info.floor_info = floor_info
	self._floor_scroll_screen:AddChild(info.select_item, 1)
	info.edit_item = self:CreateFloorEdit(info)
	self._cur_edit_layer:AddChild(info.edit_item, 1)
	self:SaveCurEdit(false)
end
GBRMaker.GCenter.HandleNewFloorClick = Lua.CoWrap(GBRMaker.GCenter.HandleNewFloorClick)

function GBRMaker.GCenter:HandleSelectFloor(event)
	local info = event.target._user_data
	if event.target.selected then
		info.edit_item.alpha = 1
	else
		info.edit_item.alpha = 0.5
	end
	self._cur_floor = info
end

function GBRMaker.GCenter:HandleFloorRButtonDown(event)
	if self._floor_right_menu == nil then
		self._floor_right_menu = GBRMaker.g_Control:CreateControl("ide_floor_right_menu", self)
	end
	self._floor_right_menu.x = A_UISystem.mouse_x
	self._floor_right_menu.y = A_UISystem.mouse_y
	A_LayerManager:ShowFromRight(self._floor_right_menu)
	self._floor_right_menu._user_data = event.target._user_data
	local info = event.target._user_data
	self._floor_right_hide_btn.disabled = not info.floor_info.visible
	self._floor_right_show_btn.disabled = info.floor_info.visible
end

function GBRMaker.GCenter:HandleFloorRightMenu(event)
	local info = self._floor_right_menu._user_data
	self._floor_right_menu._user_data = nil
	A_LayerManager:HideFromRight(self._floor_right_menu)
	local index = self._floor_scroll_screen:GetChildIndex(info.select_item)
	if event.target.text == "上移" then
		self._floor_scroll_screen:SetChildIndex(info.select_item, index - 1)
		self._cur_edit_layer:SetChildIndex(info.edit_item, index - 1)
		local floor_data = info.floor_info.file_info.map_data.floor_list[index]
		ALittle.List_Remove(info.floor_info.file_info.map_data.floor_list, index)
		ALittle.List_Insert(info.floor_info.file_info.map_data.floor_list, index - 1, floor_data)
		local floor_info = info.floor_info.file_info.map_info.floor_list[index]
		ALittle.List_Remove(info.floor_info.file_info.map_info.floor_list, index)
		ALittle.List_Insert(info.floor_info.file_info.map_info.floor_list, index - 1, floor_info)
		self:SaveCurEdit(false)
	elseif event.target.text == "下移" then
		self._floor_scroll_screen:SetChildIndex(info.select_item, index + 1)
		self._cur_edit_layer:SetChildIndex(info.edit_item, index + 1)
		local floor_data = info.floor_info.file_info.map_data.floor_list[index]
		ALittle.List_Remove(info.floor_info.file_info.map_data.floor_list, index)
		ALittle.List_Insert(info.floor_info.file_info.map_data.floor_list, index + 1, floor_data)
		local floor_info = info.floor_info.file_info.map_info.floor_list[index]
		ALittle.List_Remove(info.floor_info.file_info.map_info.floor_list, index)
		ALittle.List_Insert(info.floor_info.file_info.map_info.floor_list, index + 1, floor_info)
		self:SaveCurEdit(false)
	elseif event.target.text == "隐藏" then
		info.select_item.text = info.floor_info.floor_data.name .. "(隐藏)"
		info.edit_item.visible = false
		info.floor_info.visible = false
	elseif event.target.text == "显示" then
		info.select_item.text = info.floor_info.floor_data.name
		info.edit_item.visible = true
		info.floor_info.visible = true
	elseif event.target.text == "删除" then
		self._floor_scroll_screen:RemoveChild(info.select_item)
		self._cur_edit_layer:RemoveChild(info.edit_item)
		ALittle.List_Remove(info.floor_info.file_info.map_data.floor_list, index)
		ALittle.List_Remove(info.floor_info.file_info.map_info.floor_list, index)
		self:SaveCurEdit(false)
	end
end

function GBRMaker.GCenter:StartEdit(file_info)
	local setting_data = self._setting_dialog.data
	self._cur_file = file_info
	self._cur_floor = nil
	self._edit_title.text = file_info.item.text
	self._floor_scroll_screen:RemoveAllChild()
	self._edit_scroll_screen:RemoveAllChild()
	local x_max = file_info.map_data.x_max
	if x_max < 10 then
		x_max = 10
	end
	local y_max = file_info.map_data.y_max
	if y_max < 10 then
		y_max = 10
	end
	local nx_max = file_info.map_data.nx_max
	if nx_max > -10 then
		nx_max = -10
	end
	local layer_width = 0.0
	local layer_height = 0.0
	self._cur_layer = ALittle.DisplayLayout(GBRMaker.g_Control)
	self._cur_grid_layer = ALittle.DisplayLayout(GBRMaker.g_Control)
	self._cur_grid_layer.width_type = 4
	self._cur_grid_layer.height_type = 4
	self._cur_layer:AddChild(self._cur_grid_layer)
	self._cur_grid_layer.disabled = true
	local x = 0
	while true do
		if not(x < x_max) then break end
		local y = 0
		while true do
			if not(y < y_max) then break end
			local image = ALittle.Image(self._control)
			image.texture_name = self._tex_name_base_path .. setting_data.empty_name
			image.width = setting_data.unit_width
			image.height = setting_data.unit_height
			local show_x, show_y = GBRMaker.IDECoordVirtual2Show(x, y, setting_data.unit_real_width, setting_data.unit_width, setting_data.unit_real_height, setting_data.unit_height)
			image.x = show_x
			image.y = show_y
			self._cur_grid_layer:AddChild(image)
			if image.x + image.width > layer_width then
				layer_width = image.x + image.width
			end
			if image.y + image.height > layer_height then
				layer_height = image.y + image.height
			end
			y = y+(1)
		end
		x = x+(1)
	end
	local x = -1
	while true do
		if not(x > nx_max) then break end
		local y = 0
		while true do
			if not(y < y_max) then break end
			local show_x, show_y = GBRMaker.IDECoordVirtual2Show(x, y, setting_data.unit_real_width, setting_data.unit_width, setting_data.unit_real_height, setting_data.unit_height)
			if show_x + setting_data.unit_width / 2 >= 0 then
				local image = ALittle.Image(self._control)
				image.texture_name = self._tex_name_base_path .. setting_data.empty_name
				image.width = setting_data.unit_width
				image.height = setting_data.unit_height
				image.x = show_x
				image.y = show_y
				self._cur_grid_layer:AddChild(image)
				if image.x + image.width > layer_width then
					layer_width = image.x + image.width
				end
				if image.y + image.height > layer_height then
					layer_height = image.y + image.height
				end
			end
			y = y+(1)
		end
		x = x+(-1)
	end
	self._cur_brush_quad = ALittle.Quad(GBRMaker.g_Control)
	self._cur_brush_quad.alpha = 0
	self._cur_brush_quad.width_type = 4
	self._cur_brush_quad.height_type = 4
	self._cur_layer:AddChild(self._cur_brush_quad)
	self._cur_brush_quad:AddEventListener(___all_struct[1883782801], self, self.HandleBrushQuadLButtonDown)
	self._cur_brush_quad:AddEventListener(___all_struct[1301789264], self, self.HandleBrushQuadDragBegin)
	self._cur_brush_quad:AddEventListener(___all_struct[1337289812], self, self.HandleBrushQuadDrag)
	self._cur_erase_quad = ALittle.Quad(GBRMaker.g_Control)
	self._cur_erase_quad.alpha = 0
	self._cur_erase_quad.visible = false
	self._cur_erase_quad.width_type = 4
	self._cur_erase_quad.height_type = 4
	self._cur_layer:AddChild(self._cur_erase_quad)
	self._cur_erase_quad:AddEventListener(___all_struct[1883782801], self, self.HandleEraseQuadLButtonDown)
	self._cur_erase_quad:AddEventListener(___all_struct[1301789264], self, self.HandleEraseQuadDragBegin)
	self._cur_erase_quad:AddEventListener(___all_struct[1337289812], self, self.HandleEraseQuadDrag)
	self._cur_drag_quad = ALittle.Quad(GBRMaker.g_Control)
	self._cur_drag_quad.alpha = 0
	self._cur_drag_quad.visible = false
	self._cur_drag_quad.width_type = 4
	self._cur_drag_quad.height_type = 4
	self._cur_layer:AddChild(self._cur_drag_quad)
	self._cur_drag_quad.drag_trans_target = self._edit_scroll_screen
	self._cur_edit_layer = ALittle.DisplayLayout(GBRMaker.g_Control)
	self._cur_edit_layer.width_type = 4
	self._cur_edit_layer.height_type = 4
	self._cur_layer:AddChild(self._cur_edit_layer)
	self._cur_edit_layer.disabled = true
	self._edit_scroll_screen.container.width = layer_width
	self._edit_scroll_screen.container.height = layer_height
	self._cur_layer.width = layer_width
	self._cur_layer.height = layer_height
	self._edit_scroll_screen:AddChild(self._cur_layer)
	self._edit_scroll_screen:RejustScrollBar()
	local group = {}
	for index, floor_info in ___ipairs(self._cur_file.map_info.floor_list) do
		local info = {}
		info.select_item = GBRMaker.g_Control:CreateControl("ide_common_item_radiobutton", info)
		info.select_item._user_data = info
		info.select_item.group = group
		info.select_item.text = floor_info.floor_data.name
		info.select_item:AddEventListener(___all_struct[958494922], self, self.HandleSelectFloor)
		info.select_item:AddEventListener(___all_struct[-641444818], self, self.HandleFloorRButtonDown)
		info.floor_info = floor_info
		self._floor_scroll_screen:AddChild(info.select_item)
		info.edit_item = self:CreateFloorEdit(info)
		self._cur_edit_layer:AddChild(info.edit_item)
		info.edit_item.alpha = 0.5
		if index == 1 then
			info.select_item.selected = true
			info.edit_item.alpha = 1
			self._cur_floor = info
		end
	end
end

function GBRMaker.GCenter:CreateFloorEdit(info)
	local setting_data = self._setting_dialog.data
	local layer = ALittle.DisplayLayout(self._control)
	for x, y_data in ___pairs(info.floor_info.floor_data.data) do
		for y, tex_id in ___pairs(y_data) do
			local image = ALittle.Image(self._control)
			image.texture_name = info.floor_info.file_info.map_data.tex_map[tex_id]
			image.width = setting_data.unit_width
			image.height = setting_data.unit_height
			local show_x, show_y = GBRMaker.IDECoordVirtual2Show(x, y, setting_data.unit_real_width, setting_data.unit_width, setting_data.unit_real_height, setting_data.unit_height)
			image.x = show_x
			image.y = show_y
			layer:AddChild(image)
			local y_info = info.floor_info.child_map[x]
			if y_info == nil then
				y_info = {}
				info.floor_info.child_map[x] = y_info
			end
			y_info[y] = image
		end
	end
	return layer
end

function GBRMaker.GCenter:UpdateFloorAlpha()
	for index, child in ___ipairs(self._floor_scroll_screen.childs) do
		local info = child._user_data
		if info.select_item.selected then
			info.edit_item.alpha = 1
		else
			info.edit_item.alpha = 0.5
		end
	end
end

function GBRMaker.GCenter:HandleToolBrushSelect(event)
	self._layer_brush_info.visible = event.target.selected
	if self._cur_brush_quad ~= nil then
		self._cur_brush_quad.visible = event.target.selected
	end
	self:UpdateFloorAlpha()
end

function GBRMaker.GCenter:HandleToolEraseSelect(event)
	self._layer_erase_info.visible = event.target.selected
	if self._cur_erase_quad ~= nil then
		self._cur_erase_quad.visible = event.target.selected
	end
	self:UpdateFloorAlpha()
end

function GBRMaker.GCenter:HandleToolScaleSelect(event)
	self._layer_scale_info.visible = event.target.selected
	self:UpdateFloorAlpha()
end

function GBRMaker.GCenter:HandleToolDragSelect(event)
	self._layer_drag_info.visible = event.target.selected
	if self._cur_drag_quad ~= nil then
		self._cur_drag_quad.visible = event.target.selected
	end
	if self._cur_edit_layer ~= nil then
		for index, child in ___ipairs(self._cur_edit_layer.childs) do
			child.alpha = 1
		end
	end
end

function GBRMaker.GCenter:SaveCurEdit(save)
	if self._cur_file == nil then
		return
	end
	if self._cur_file.save == save then
		return
	end
	if not save then
		self._cur_file.save = false
		self._edit_title.text = self._cur_file.item.text .. "*"
		return
	end
	local rflct = ___all_struct[-1481607580]
	local factory = __CPPAPIMessageWriteFactory()
	local invoke_info = ALittle.CreateMessageInfo(rflct.name)
	if invoke_info == nil then
		return
	end
	ALittle.PS_WriteMessage(factory, invoke_info, nil, self._cur_file.map_data)
	if not factory:WriteToStdFile(self._cur_file.file_path) then
		g_AUITool:ShowNotice("提示", "保存失败")
		return
	end
	self._cur_file.save = true
	self._edit_title.text = self._cur_file.item.text
end

function GBRMaker.GCenter:HandleKeyDown(mod, sym, scancode)
	if sym == 115 and ALittle.BitAnd(mod, 0x00c0) ~= 0 then
		self:SaveCurEdit(true)
	end
	local tool_changed = false
	if A_UISystem.sym_map[32] ~= nil then
		self._tool_drag.selected = true
		tool_changed = true
	elseif A_UISystem.sym_map[98] ~= nil then
		self._tool_brush.selected = true
		tool_changed = true
	elseif A_UISystem.sym_map[101] ~= nil then
		self._tool_erase.selected = true
		tool_changed = true
	elseif A_UISystem.sym_map[122] ~= nil then
		self._tool_scale.selected = true
		tool_changed = true
	end
	if tool_changed then
		self._tool_drag:DispatchEvent(___all_struct[958494922], {})
		self._tool_brush:DispatchEvent(___all_struct[958494922], {})
		self._tool_erase:DispatchEvent(___all_struct[958494922], {})
		self._tool_scale:DispatchEvent(___all_struct[958494922], {})
	end
end

function GBRMaker.GCenter:HandleDragRightQuadUD(event)
	self._right_grad3_ud.up_size = self._right_grad3_ud.up_size + (event.delta_y)
end

function GBRMaker.GCenter:HandleDragEndRightQuadUD(event)
	GBRMaker.g_GConfig:SetConfig("right_grid3_up_size", self._right_grad3_ud.up_size)
end

function GBRMaker.GCenter:HandleDragRightQuadLR(event)
	self._main_grid3_lr.down_size = self._main_grid3_lr.down_size - (event.delta_x)
end

function GBRMaker.GCenter:HandleDragEndRightQuadLR(event)
	GBRMaker.g_GConfig:SetConfig("main_grid3_down_size", self._main_grid3_lr.down_size)
end

function GBRMaker.GCenter:HandleSetVDragCursor(event)
	ALittle.System_SetVDragCursor()
end

function GBRMaker.GCenter:HandleSetHDragCursor(event)
	ALittle.System_SetHDragCursor()
end

function GBRMaker.GCenter:HandleSetNormalCursor(event)
	ALittle.System_SetNormalCursor()
end

function GBRMaker.GCenter:Shutdown()
end

_G.g_GCenter = GBRMaker.GCenter()
end