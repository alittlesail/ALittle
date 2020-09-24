-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
BattleCity.EditScene = Lua.Class(ALittle.DisplayLayout, "BattleCity.EditScene")

function BattleCity.EditScene:Ctor()
	___rawset(self, "_size", 4)
	___rawset(self, "_cell_size", 0)
end

function BattleCity.EditScene:TCtor()
	self._tile_range.visible = false
end

function BattleCity.EditScene:Show()
	self.visible = true
	self:Load(1)
	ALittle.File_MakeDeepDir(BattleCity.g_ModuleBasePath .. "Other/Map")
	self._cell_size = self._tile_container.width / (13 * 4)
	self._size_input.text = self._size
	self._tile_range.width = self._size * self._cell_size
	self._tile_range.height = self._size * self._cell_size
end

function BattleCity.EditScene:Load(stage)
	self:Save()
	self._stage_input.text = stage
	self._path = "Other/Map/stage_" .. stage .. ".map"
	self._cur_data = BattleCity.g_Control:LoadMessageFromFile(___all_struct[-922796193], self._path)
	if self._cur_data == nil then
		self._cur_data = {}
		self._cur_data.tile_map = {}
	end
	self._tile_container:RemoveAllChild()
	self._sprite_map = {}
	for row, sub_map in ___pairs(self._cur_data.tile_map) do
		for col, type in ___pairs(sub_map) do
			self:SetTileShow(row, col, type)
		end
	end
end
BattleCity.EditScene.Load = Lua.CoWrap(BattleCity.EditScene.Load)

function BattleCity.EditScene:Save()
	if self._cur_data == nil then
		return
	end
	local rflct = ___all_struct[-922796193]
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
	factory:WriteToStdFile(ALittle.File_BaseFilePath() .. BattleCity.g_ModuleBasePath .. self._path)
end

function BattleCity.EditScene:HandleTileSelect(event)
	self._select_sripte.col_index = event.target.col_index
end

function BattleCity.EditScene:HandleStageInputChanged(event)
	local num = ALittle.Math_ToInt(self._stage_input.text)
	if num == nil or num < 0 or num > 255 then
		return
	end
	self:Load(num)
end

function BattleCity.EditScene:SetTileShow(row, col, type)
	local sub_map = self._sprite_map[row]
	if sub_map == nil then
		sub_map = {}
		self._sprite_map[row] = sub_map
	end
	if sub_map[col] ~= nil then
		self._tile_container:RemoveChild(sub_map[col])
	end
	local sprite = ALittle.Sprite(BattleCity.g_Control)
	sprite.texture_name = "tile.png"
	sprite.width = 32 / 4
	sprite.height = 32 / 4
	sprite.x = col * sprite.width
	sprite.y = row * sprite.height
	sprite.row_count = 4
	sprite.col_count = 7 * 4
	sprite.row_index = row % 4 + 1
	sprite.col_index = col % 4 + 1 + (type - 1) * 4
	self._tile_container:AddChild(sprite)
	sub_map[col] = sprite
end

function BattleCity.EditScene:RemoveTileShow(row, col)
	local sub_map = self._sprite_map[row]
	if sub_map == nil then
		return
	end
	if sub_map[col] ~= nil then
		self._tile_container:RemoveChild(sub_map[col])
		sub_map[col] = nil
	end
end

function BattleCity.EditScene:WriteCell(x, y, brush_type)
	local left_col, right_col, top_row, bottom_row = self:CalcRangeRowCol(x, y)
	local row = top_row
	while true do
		if not(row <= bottom_row) then break end
		local col = left_col
		while true do
			if not(col <= right_col) then break end
			local sub_map = self._cur_data.tile_map[row]
			if sub_map == nil then
				sub_map = {}
				self._cur_data.tile_map[row] = sub_map
			end
			sub_map[col] = brush_type
			self:SetTileShow(row, col, brush_type)
			col = col+(1)
		end
		row = row+(1)
	end
end

function BattleCity.EditScene:CalcRangeRowCol(x, y)
	local center_col = ALittle.Math_Floor(x / self._cell_size)
	local center_row = ALittle.Math_Floor(y / self._cell_size)
	local size_offset = ALittle.Math_Floor((self._size - 1) / 2)
	local left_col = center_col - size_offset
	local right_col = left_col + self._size - 1
	local top_row = center_row - size_offset
	local bottom_row = top_row + self._size - 1
	if left_col < 0 then
		left_col = 0
	end
	if left_col >= 13 * 4 then
		left_col = 13 * 4 - 1
	end
	if right_col < 0 then
		right_col = 0
	end
	if right_col >= 13 * 4 then
		right_col = 13 * 4 - 1
	end
	if top_row < 0 then
		top_row = 0
	end
	if top_row >= 13 * 4 then
		top_row = 13 * 4 - 1
	end
	if bottom_row < 0 then
		bottom_row = 0
	end
	if bottom_row >= 13 * 4 then
		bottom_row = 13 * 4 - 1
	end
	return left_col, right_col, top_row, bottom_row
end

function BattleCity.EditScene:EraseCell(x, y)
	local left_col, right_col, top_row, bottom_row = self:CalcRangeRowCol(x, y)
	local row = top_row
	while true do
		if not(row <= bottom_row) then break end
		local col = left_col
		while true do
			if not(col <= right_col) then break end
			local sub_map = self._cur_data.tile_map[row]
			if sub_map ~= nil then
				sub_map[col] = nil
				if ALittle.IsEmpty(sub_map) then
					self._cur_data.tile_map[row] = nil
				end
				self:RemoveTileShow(row, col)
			end
			col = col+(1)
		end
		row = row+(1)
	end
end

function BattleCity.EditScene:HandleBrushLButtonDown(event)
	if A_UISystem.sym_map[1073742049] ~= nil then
		self:EraseCell(event.rel_x, event.rel_y)
	else
		self:WriteCell(event.rel_x, event.rel_y, self._select_sripte.col_index)
	end
end

function BattleCity.EditScene:HandleBrushDrag(event)
	local left_col, right_col, top_row, bottom_row = self:CalcRangeRowCol(event.rel_x, event.rel_y)
	self._tile_range.x = left_col * self._cell_size
	self._tile_range.y = top_row * self._cell_size
	if A_UISystem.sym_map[1073742049] ~= nil then
		self:EraseCell(event.rel_x, event.rel_y)
	else
		self:WriteCell(event.rel_x, event.rel_y, self._select_sripte.col_index)
	end
end

function BattleCity.EditScene:HandleSaveClick(event)
	self:Save()
end

function BattleCity.EditScene:HandleBackClick(event)
	self:Save()
	self.visible = false
	g_GCenter:Restart()
end

function BattleCity.EditScene:HandleSizeInputChanged(event)
	self._size = ALittle.Math_ToInt(event.target.text)
	if self._size == nil or self._size <= 0 then
		self._size = 1
		event.target.text = self._size
	end
	self._tile_range.width = self._size * self._cell_size
	self._tile_range.height = self._size * self._cell_size
end

function BattleCity.EditScene:HandleBrushMoveIn(event)
	self._tile_range.visible = true
end

function BattleCity.EditScene:HandleBrushMoveOut(event)
	self._tile_range.visible = false
end

function BattleCity.EditScene:HandleBrushMove(event)
	local left_col, right_col, top_row, bottom_row = self:CalcRangeRowCol(event.rel_x, event.rel_y)
	self._tile_range.x = left_col * self._cell_size
	self._tile_range.y = top_row * self._cell_size
end

end