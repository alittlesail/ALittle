-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.SuperMarioBros == nil then _G.SuperMarioBros = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


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
		self._cur_data.mask = {}
		self._cur_data.object = {}
	end
	for row, submap in ___pairs(self._cur_data.background) do
		for col, index in ___pairs(submap) do
			local show_row = ALittle.Math_Floor(index / self._select_tile.col_count) + 1
			local show_col = index % self._select_tile.col_count + 1
			self:SetTileShow(row, col, show_row, show_col)
		end
	end
	self._scroll_screen.container.width = self._tile_linear.width + self._scroll_screen.view_width
	self._scroll_screen:RejustScrollBar()
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
	local rflct = ___all_struct[-876795489]
	local factory
	factory = __CPPAPIMessageWriteFactory()
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

function SuperMarioBros.EditScene:HandleTileQuadClick(event)
	local shift = A_UISystem.sym_map[1073742049] ~= nil
	local col = ALittle.Math_Floor((event.rel_x - self._scroll_screen.container_x) / self._select_tile.width)
	local row = ALittle.Math_Floor((event.rel_y - self._scroll_screen.container_y) / self._select_tile.height)
	if shift then
		self:RemoveTileShow(row, col)
	else
		self:SetTileShow(row, col, self._select_tile.row_index, self._select_tile.col_index)
	end
end

function SuperMarioBros.EditScene:HandleTileQuadDrag(event)
	local shift = A_UISystem.sym_map[1073742049] ~= nil
	local col = ALittle.Math_Floor((event.rel_x - self._scroll_screen.container_x) / self._select_tile.width)
	local row = ALittle.Math_Floor((event.rel_y - self._scroll_screen.container_y) / self._select_tile.height)
	if shift then
		self:RemoveTileShow(row, col)
	else
		self:SetTileShow(row, col, self._select_tile.row_index, self._select_tile.col_index)
	end
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
		self._scroll_screen:RejustScrollBar()
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
	self._scroll_screen:RejustScrollBar()
	self._scroll_screen:RefreshClipDisLine()
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
	self._scroll_screen:RejustScrollBar()
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