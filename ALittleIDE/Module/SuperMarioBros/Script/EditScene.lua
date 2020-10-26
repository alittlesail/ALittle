-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.SuperMarioBros == nil then _G.SuperMarioBros = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1883782801, "ALittle.UILButtonDownEvent", {
name = "ALittle.UILButtonDownEvent", ns_name = "ALittle", rl_name = "UILButtonDownEvent", hash_code = 1883782801,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1349734647, "SuperMarioBros.EditEntityInfo", {
name = "SuperMarioBros.EditEntityInfo", ns_name = "SuperMarioBros", rl_name = "EditEntityInfo", hash_code = -1349734647,
name_list = {"ui","type","width","height","center_x","center_y"},
type_list = {"string","int","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
SuperMarioBros.EditContainer = Lua.Class(ALittle.DisplayLayout, "SuperMarioBros.EditContainer")

function SuperMarioBros.EditContainer:Init(tile_linear)
	self._tile_linear = tile_linear
end

function SuperMarioBros.EditContainer:ClipRect(x, y, width, height, h_move, v_move)
	self._tile_linear:ClipRect(x - self._x, y - self._y, width - self._x, height - self._y, h_move, v_move)
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
SuperMarioBros.EditScene = Lua.Class(ALittle.DisplayLayout, "SuperMarioBros.EditScene")

function SuperMarioBros.EditScene:TCtor()
	self._scroll_screen.container:Init(self._tile_linear)
	self._entity_panel.visible = false
	self._entity_info_map = {}
	self._entity_map = {}
	self:AddEntity("wall_1", SuperMarioBros.EntityType.ET_WALL_1, self._entity_wall_1)
	self:AddEntity("hide_wall_1", SuperMarioBros.EntityType.ET_HIDE_WALL_1, self._entity_hide_wall_1)
	self:AddEntity("random_wall_1", SuperMarioBros.EntityType.ET_RANDOM_WALL_1, self._entity_random_wall_1)
	self:AddEntity("enemy_1", SuperMarioBros.EntityType.ET_ENEMY_1, self._entity_enemy_1)
	self:AddEntity("enemy_2", SuperMarioBros.EntityType.ET_ENEMY_2, self._entity_enemy_2)
	self:AddEntity("flag_1", SuperMarioBros.EntityType.ET_FLAG_1, self._entity_flag_1)
	self:AddEntity("flag_2", SuperMarioBros.EntityType.ET_FLAG_2, self._entity_flag_2)
	self:AddEntity("flag_3", SuperMarioBros.EntityType.ET_FLAG_3, self._entity_flag_3)
	self:AddEntity("flag_4", SuperMarioBros.EntityType.ET_FLAG_4, self._entity_flag_4)
	self:AddEntity("flag_5", SuperMarioBros.EntityType.ET_FLAG_5, self._entity_flag_5)
	self:AddEntity("born_1", SuperMarioBros.EntityType.ET_BORN_1, self._entity_born_1)
	self._select_frame._user_data = self._entity_info_map[SuperMarioBros.EntityType.ET_RANDOM_WALL_1]
end

function SuperMarioBros.EditScene:AddEntity(ui, type, object)
	local info = {}
	info.ui = ui
	info.type = type
	info.width = object.width
	info.height = object.height
	info.center_x = object.center_x
	info.center_y = object.center_y
	object._user_data = info
	object:AddEventListener(___all_struct[1883782801], self, self.HandleEntitySelectClick)
	self._entity_info_map[type] = info
end

function SuperMarioBros.EditScene:Show()
	self.visible = true
	self:Load(1, 1)
	ALittle.File_MakeDeepDir(SuperMarioBros.g_ModuleBasePath .. "Other/Map")
	ALittle.System_SetViewSize(ALittle.Math_Floor(self.width), ALittle.Math_Floor(self.height))
end

function SuperMarioBros.EditScene:Hide()
	self.visible = false
end

function SuperMarioBros.EditScene:Load(world, subworld)
	self:Save()
	self._world_input.text = world
	self._subworld_input.text = subworld
	self._path = "Other/Map/world_" .. world .. "_" .. subworld .. ".map"
	self._cur_data = SuperMarioBros.g_Control:LoadMessageFromFile(___all_struct[-876795489], self._path)
	if self._cur_data == nil then
		self._cur_data = {}
		self._cur_data.row_count = 0
		self._cur_data.col_count = 0
		self._cur_data.background = {}
		self._cur_data.object = {}
	end
	self._tile_linear:RemoveAllChild()
	self._entity_container:RemoveAllChild()
	self._entity_map = {}
	for row, submap in ___pairs(self._cur_data.background) do
		for col, index in ___pairs(submap) do
			local show_row = ALittle.Math_Floor(index / self._select_tile.col_count) + 1
			local show_col = index % self._select_tile.col_count + 1
			self:SetTileShow(row, col, show_row, show_col)
		end
	end
	for row, submap in ___pairs(self._cur_data.object) do
		for col, type in ___pairs(submap) do
			self:SetEntityShow(row, col, type)
		end
	end
	self._scroll_screen.container.width = self._tile_linear.width + self._scroll_screen.view_width
	self._scroll_screen:AdjustScrollBar()
end
SuperMarioBros.EditScene.Load = Lua.CoWrap(SuperMarioBros.EditScene.Load)

function SuperMarioBros.EditScene:Save()
	if self._cur_data == nil then
		return
	end
	self._cur_data.row_count = 0
	self._cur_data.col_count = 0
	self._cur_data.background = {}
	for index, linear in ___ipairs(self._tile_linear.childs) do
		local col = index - 1
		for subindex, sprite in ___ipairs(linear.childs) do
			if sprite.visible then
				local row = subindex - 1
				local submap = self._cur_data.background[row]
				if submap == nil then
					submap = {}
					self._cur_data.background[row] = submap
				end
				submap[col] = (sprite.row_index - 1) * self._select_tile.col_count + (sprite.col_index - 1)
				if self._cur_data.row_count < row + 1 then
					self._cur_data.row_count = row + 1
				end
				if self._cur_data.col_count < col + 1 then
					self._cur_data.col_count = col + 1
				end
			end
		end
	end
	self._cur_data.object = {}
	for row, entity_submap in ___pairs(self._entity_map) do
		for col, object in ___pairs(entity_submap) do
			local submap = self._cur_data.object[row]
			if submap == nil then
				submap = {}
				self._cur_data.object[row] = submap
			end
			submap[col] = object._user_data.type
		end
	end
	local rflct = ___all_struct[-876795489]
	local factory
	factory = carp.CarpMessageWriteFactory()
	if factory == nil then
		ALittle.Error("factory create failed")
		return
	end
	local invoke_info = ALittle.CreateMessageInfo(rflct.name)
	if invoke_info == nil then
		ALittle.Error("create message info failed:" .. rflct.name)
		return
	end
	ALittle.PS_WriteMessage(factory, invoke_info, nil, self._cur_data)
	factory:WriteToStdFile(ALittle.File_BaseFilePath() .. SuperMarioBros.g_ModuleBasePath .. self._path)
end

function SuperMarioBros.EditScene:HandleEntitySelectClick(event)
	self._select_frame.x = event.target.x
	self._select_frame.y = event.target.y
	self._select_frame._user_data = event.target._user_data
end

function SuperMarioBros.EditScene:HandleTileTabClick(event)
	self._entity_panel.visible = false
	self._tile_image.visible = true
	self._select_tile.visible = true
end

function SuperMarioBros.EditScene:HandleEntityTabClick(event)
	self._entity_panel.visible = true
	self._tile_image.visible = false
	self._select_tile.visible = false
end

function SuperMarioBros.EditScene:CursorHandleImpl(rel_x, rel_y)
	local shift = A_UISystem.sym_map[1073742049] ~= nil
	local col = ALittle.Math_Floor((rel_x - self._scroll_screen.container_x) / self._select_tile.width)
	local row = ALittle.Math_Floor((rel_y - self._scroll_screen.container_y) / self._select_tile.height)
	if self._tile_image.visible then
		if shift then
			self:RemoveTileShow(row, col)
		else
			self:SetTileShow(row, col, self._select_tile.row_index, self._select_tile.col_index)
		end
	elseif self._entity_panel.visible then
		local info = self._select_frame._user_data
		if info == nil then
			return
		end
		if shift then
			self:RemoveEntityShow(row, col)
		else
			self:SetEntityShow(row, col, info.type)
		end
	end
end

function SuperMarioBros.EditScene:HandleTileQuadClick(event)
	self:CursorHandleImpl(event.rel_x, event.rel_y)
end

function SuperMarioBros.EditScene:HandleTileQuadDrag(event)
	self:CursorHandleImpl(event.rel_x, event.rel_y)
end

function SuperMarioBros.EditScene:SetTileShow(row, col, show_row, show_col)
	if self._tile_linear.child_count < col + 1 then
		local i = self._tile_linear.child_count
		while true do
			if not(i < col + 1) then break end
			local linear = ALittle.Linear(SuperMarioBros.g_Control)
			linear.type = 2
			linear.width = self._select_tile.width
			self._tile_linear:AddChild(linear)
			i = i+(1)
		end
		self._scroll_screen.container.width = self._tile_linear.width + self._scroll_screen.view_width
		self._scroll_screen:AdjustScrollBar()
	end
	local linear = self._tile_linear:GetChildByIndex(col + 1)
	if linear == nil then
		return
	end
	if linear.child_count < row + 1 then
		local i = linear.child_count
		while true do
			if not(i < row + 1) then break end
			local sprite = ALittle.Sprite(SuperMarioBros.g_Control)
			sprite.texture_name = self._select_tile.texture_name
			sprite.row_count = self._select_tile.row_count
			sprite.col_count = self._select_tile.col_count
			sprite.width = self._select_tile.width
			sprite.height = self._select_tile.height
			sprite.visible = false
			linear:AddChild(sprite)
			i = i+(1)
		end
	end
	local sprite = linear:GetChildByIndex(row + 1)
	sprite.row_index = show_row
	sprite.col_index = show_col
	sprite.visible = true
	self._scroll_screen:AdjustScrollBar()
	self._scroll_screen:RefreshClipDisLine()
end

function SuperMarioBros.EditScene:SetEntityShow(row, col, type)
	self:RemoveEntityShow(row, col)
	local info = self._entity_info_map[type]
	if info == nil then
		return
	end
	local submap = self._entity_map[row]
	if submap == nil then
		submap = {}
		self._entity_map[row] = submap
	end
	local object = SuperMarioBros.g_Control:CreateControl(info.ui)
	object._user_data = info
	object.width = info.width
	object.height = info.height
	object.center_x = info.center_x
	object.center_y = info.center_y
	object.x = col * self._select_tile.width
	object.y = row * self._select_tile.height
	self._entity_container:AddChild(object)
	submap[col] = object
end

function SuperMarioBros.EditScene:RemoveEntityShow(row, col)
	local submap = self._entity_map[row]
	if submap == nil then
		return
	end
	local object = submap[col]
	if object == nil then
		return
	end
	submap[col] = nil
	self._entity_container:RemoveChild(object)
end

function SuperMarioBros.EditScene:RemoveTileShow(row, col)
	local linear = self._tile_linear:GetChildByIndex(col + 1)
	if linear == nil then
		return
	end
	local sprite = linear:GetChildByIndex(row + 1)
	if sprite == nil then
		return
	end
	sprite.visible = false
	if col + 1 ~= self._tile_linear.child_count then
		return
	end
	local i = self._tile_linear.child_count
	while true do
		if not(i >= 1) then break end
		local remove = true
		linear = self._tile_linear.childs[i]
		for index, child in ___ipairs(linear.childs) do
			if child.visible then
				remove = false
				break
			end
		end
		if remove then
			self._tile_linear:RemoveChild(linear)
		else
			break
		end
		i = i+(-1)
	end
	self._scroll_screen.container.width = self._tile_linear.width + self._scroll_screen.view_width
	self._scroll_screen:AdjustScrollBar()
	self._scroll_screen:RefreshClipDisLine()
end

function SuperMarioBros.EditScene:HandleTileSelected(event)
	local col = ALittle.Math_Floor(event.rel_x / self._select_tile.width) + 1
	local row = ALittle.Math_Floor(event.rel_y / self._select_tile.height) + 1
	self._select_tile.col_index = col
	self._select_tile.row_index = row
end

function SuperMarioBros.EditScene:HandleWorldChanged(event)
	local world = ALittle.Math_ToInt(self._world_input.text)
	if world == nil or world < 0 then
		return
	end
	local subworld = ALittle.Math_ToInt(self._subworld_input.text)
	if subworld == nil or world < 0 then
		return
	end
	self:Load(world, subworld)
end

function SuperMarioBros.EditScene:HandleSaveClick(event)
	self:Save()
end

function SuperMarioBros.EditScene:HandleBackClick(event)
	self:Save()
	self:Hide()
	ALittle.System_SetViewSize(ALittle.Math_Floor(g_GCenter.login_scene.width), ALittle.Math_Floor(g_GCenter.login_scene.height))
	g_GCenter.login_scene:Show()
end

end