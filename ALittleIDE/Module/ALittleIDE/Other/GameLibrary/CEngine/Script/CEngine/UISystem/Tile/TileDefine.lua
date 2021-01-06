-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1281734132, "ALittle.TileMap", {
name = "ALittle.TileMap", ns_name = "ALittle", rl_name = "TileMap", hash_code = -1281734132,
name_list = {"tile_type","side_len","tile_width","tile_height","tile_x","tile_y","col_count","row_count","tex_map","layer_list"},
type_list = {"int","int","int","int","int","int","int","int","Map<int,string>","List<ALittle.TileLayer>"},
option_map = {}
})
ALittle.RegStruct(-343663763, "ALittle.TileLayer", {
name = "ALittle.TileLayer", ns_name = "ALittle", rl_name = "TileLayer", hash_code = -343663763,
name_list = {"name","cell_map"},
type_list = {"string","Map<int,Map<int,ALittle.TileCell>>"},
option_map = {}
})
ALittle.RegStruct(7944876, "ALittle.TileCell", {
name = "ALittle.TileCell", ns_name = "ALittle", rl_name = "TileCell", hash_code = 7944876,
name_list = {"tex_id"},
type_list = {"int"},
option_map = {}
})

ALittle.TileType = {
	NONE = 0,
	SQUARE = 1,
	HEX_V = 2,
	HEX_H = 3,
}

local floor = ALittle.Math_Floor
local ceil = ALittle.Math_Ceil
assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittle.TileMapContainer = Lua.Class(ALittle.DisplayLayout, "ALittle.TileMapContainer")

function ALittle.TileMapContainer:Ctor(ctrl_sys)
	___rawset(self, "_row_count", 0)
	___rawset(self, "_col_count", 0)
	___rawset(self, "_cell_width", 0.0)
	___rawset(self, "_cell_height", 0.0)
	___rawset(self, "_linear_x", 0.0)
	___rawset(self, "_linear_y", 0.0)
	___rawset(self, "_tile_layout", ALittle.TileLayoutContainer(ctrl_sys))
	self._tile_layout.width_type = 4
	self._tile_layout.height_type = 4
	self:AddChild(self._tile_layout)
	___rawset(self, "_user_layout", ALittle.TileLayoutContainer(ctrl_sys))
	self._user_layout.width_type = 4
	self._user_layout.height_type = 4
	self:AddChild(self._user_layout)
end

function ALittle.TileMapContainer:ClipRect(x, y, width, height, h_move, v_move)
	for index, child in ___ipairs(self.childs) do
		child:ClipRect(x - self._x, y - self._y, width - self._x, height - self._y, h_move, v_move)
	end
end

function ALittle.TileMapContainer:Init(tile_map, row_count, col_count)
	self._tile_layout:RemoveAllChild()
	self._tile_map = tile_map
	self._row_count = row_count
	self._col_count = col_count
	self._image_cache = {}
	self._cell_width = ALittle.Tile_CalcCellWidth(tile_map)
	self._cell_height = ALittle.Tile_CalcCellHeight(tile_map)
	self._linear_x = ALittle.Tile_CalcLinear2OffsetX(tile_map)
	self._linear_y = ALittle.Tile_CalcLinear2OffsetY(tile_map)
	local grid_map_width = self._cell_width * col_count
	local linear_1
	local linear_2
	for index, layer in ___ipairs(tile_map.layer_list) do
		local group = ALittle.TileGroupContainer(self._ctrl_sys)
		linear_1 = ALittle.Linear(self._ctrl_sys)
		linear_1.type = 2
		linear_1.width = grid_map_width
		group:AddChild(linear_1)
		linear_2 = ALittle.Linear(self._ctrl_sys)
		linear_2.type = 2
		linear_2.width = grid_map_width
		linear_2.x = self._linear_x
		linear_2.y = self._linear_y
		group:AddChild(linear_2)
		self:ResizeLinear(linear_1, linear_2, index)
		self._tile_layout:AddChild(group)
	end
	local width_1 = 0.0
	if linear_1 ~= nil then
		width_1 = linear_1.x + linear_1.width
	end
	local width_2 = 0.0
	if linear_2 ~= nil then
		width_2 = linear_2.x + linear_2.width
	end
	local height_1 = 0.0
	if height_1 ~= nil then
		height_1 = linear_1.y + linear_1.height
	end
	local height_2 = 0.0
	if linear_2 ~= nil then
		height_2 = linear_2.y + linear_2.height
	end
	self.width = ALittle.Math_Max(width_1, width_2)
	self.height = ALittle.Math_Max(height_1, height_2)
end

function ALittle.TileMapContainer.__getter:user_layout()
	return self._user_layout
end

function ALittle.TileMapContainer:GetImage(layer, row, col)
	local layer_map = self._image_cache[layer]
	if layer_map == nil then
		layer_map = {}
		self._image_cache[layer] = layer_map
	end
	local row_map = layer_map[row]
	if row_map == nil then
		row_map = {}
		layer_map[row] = row_map
	end
	local image = row_map[col]
	if image ~= nil then
		return image
	end
	local group = self._tile_layout:GetChildByIndex(layer)
	if group == nil then
		return nil
	end
	local linear_1 = group:GetChildByIndex(1)
	local linear_2 = group:GetChildByIndex(2)
	local tile_type = self._tile_map.tile_type
	if tile_type == 2 then
		if row % 2 == 1 then
			image = linear_1.childs[floor(row / 2) + 1].childs[col]._user_data
			row_map[col] = image
			return image
		end
		image = linear_2.childs[floor(row / 2)].childs[col]._user_data
		row_map[col] = image
		return image
	else
		if col % 2 == 1 then
			image = linear_1.childs[row].childs[floor(col / 2) + 1]._user_data
			row_map[col] = image
			return image
		end
		image = linear_2.childs[row].childs[floor(col / 2)]._user_data
		row_map[col] = image
		return image
	end
end

function ALittle.TileMapContainer:RefreshTexture(start_row, start_col)
	local tile_map = self._tile_map
	local row_count = self._row_count
	local col_count = self._col_count
	local childs = self._tile_layout._childs
	for index, group in ___ipairs(childs) do
		local layer = tile_map.layer_list[index]
		local row = 1
		while true do
			if not(row <= row_count) then break end
			local col = 1
			while true do
				if not(col <= col_count) then break end
				local image = self:GetImage(index, row, col)
				local cells = layer.cell_map[row + start_row - 1]
				if cells == nil then
					image.texture_name = nil
				else
					local cell = cells[col + start_col - 1]
					if cell == nil then
						image.texture_name = nil
					else
						image.texture_name = tile_map.tex_map[cell.tex_id]
					end
				end
				col = col+(1)
			end
			row = row+(1)
		end
	end
end

function ALittle.TileMapContainer:ResizeLinear(linear_1, linear_2, layer)
	local tile_map = self._tile_map
	local col_count = self._col_count
	local row_count = self._row_count
	if tile_map.tile_type == 2 then
		linear_1.width = self._cell_width * col_count
		linear_2.width = linear_1.width
		local row = 1
		while true do
			if not(row <= row_count) then break end
			local linear = ALittle.Linear(self._ctrl_sys)
			linear.type = 1
			linear.height = self._cell_height
			local col = 1
			while true do
				if not(col <= col_count) then break end
				linear:AddChild(self:CreateCell())
				col = col+(1)
			end
			if row % 2 == 1 then
				linear_1:AddChild(linear)
			else
				linear_2:AddChild(linear)
			end
			row = row+(1)
		end
	else
		local col_count_1 = ceil(col_count / 2)
		local row = 1
		while true do
			if not(row <= row_count) then break end
			local linear = ALittle.Linear(self._ctrl_sys)
			linear.type = 1
			linear.height = self._cell_height
			local col = 1
			while true do
				if not(col <= col_count_1) then break end
				linear:AddChild(self:CreateCell())
				col = col+(1)
			end
			linear_1:AddChild(linear)
			row = row+(1)
		end
		local col_count_2 = floor(col_count / 2)
		local row = linear_2.child_count + 1
		while true do
			if not(row <= row_count) then break end
			local linear = ALittle.Linear(self._ctrl_sys)
			linear.type = 1
			linear.height = self._cell_height
			local col = 1
			while true do
				if not(col <= col_count_2) then break end
				linear:AddChild(self:CreateCell())
				col = col+(1)
			end
			linear_2:AddChild(linear)
			row = row+(1)
		end
	end
end

function ALittle.TileMapContainer:CreateCell()
	local tile_map = self._tile_map
	local tile_type = tile_map.tile_type
	local side_len = tile_map.side_len
	if tile_type == 2 then
		local cell = ALittle.DisplayLayout(self._ctrl_sys)
		cell.width = self._cell_width
		local image = ALittle.Image(self._ctrl_sys)
		cell._user_data = image
		image.width = tile_map.tile_width
		image.height = tile_map.tile_height
		image.x = tile_map.tile_x
		image.y = tile_map.tile_y
		cell:AddChild(image)
		return cell
	end
	if tile_type == 1 then
		local cell = ALittle.DisplayLayout(self._ctrl_sys)
		cell.width = self._cell_width
		local image = ALittle.Image(self._ctrl_sys)
		cell._user_data = image
		image.width = tile_map.tile_width
		image.height = tile_map.tile_height
		image.x = tile_map.tile_x
		image.y = tile_map.tile_y
		cell:AddChild(image)
		return cell
	end
	if tile_type == 3 then
		local cell = ALittle.DisplayLayout(self._ctrl_sys)
		cell.width = self._cell_width
		local image = ALittle.Image(self._ctrl_sys)
		cell._user_data = image
		image.width = tile_map.tile_width
		image.height = tile_map.tile_height
		image.x = tile_map.tile_x
		image.y = tile_map.tile_y
		cell:AddChild(image)
		return cell
	end
	return nil
end

assert(ALittle.DisplayGroup, " extends class:ALittle.DisplayGroup is nil")
ALittle.TileGroupContainer = Lua.Class(ALittle.DisplayGroup, "ALittle.TileGroupContainer")

function ALittle.TileGroupContainer:ClipRect(x, y, width, height, h_move, v_move)
	for index, child in ___ipairs(self.childs) do
		child:ClipRect(x - self._x, y - self._y, width - self._x, height - self._y, h_move, v_move)
	end
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittle.TileLayoutContainer = Lua.Class(ALittle.DisplayLayout, "ALittle.TileLayoutContainer")

function ALittle.TileLayoutContainer:ClipRect(x, y, width, height, h_move, v_move)
	for index, child in ___ipairs(self.childs) do
		child:ClipRect(x - self._x, y - self._y, width - self._x, height - self._y, h_move, v_move)
	end
end

function ALittle.Tile_CalcLinear2OffsetX(tile_map)
	local tile_type = tile_map.tile_type
	local side_len = tile_map.side_len
	if tile_type == 1 then
		return side_len
	end
	if tile_type == 2 then
		return side_len * 1.732 / 2
	end
	if tile_type == 3 then
		return side_len * 3 / 2
	end
	return 0
end

function ALittle.Tile_CalcLinear2OffsetY(tile_map)
	local tile_type = tile_map.tile_type
	local side_len = tile_map.side_len
	if tile_type == 1 then
		return 0
	end
	if tile_type == 2 then
		return side_len * 3 / 2
	end
	if tile_type == 3 then
		return side_len * 1.732 / 2
	end
	return 0
end

function ALittle.Tile_CalcRowColByPosInHexV(tile_map, x, y)
	local tile_type = tile_map.tile_type
	local side_len = tile_map.side_len
	local half_width = side_len * 1.732 / 2
	local split_x = floor(x / half_width)
	local offset_x = x - split_x * half_width
	if split_x % 2 == 0 then
		local split_y = floor(y / (side_len * 3))
		local offset_y = y - split_y * (side_len * 3)
		if offset_y < side_len / 2 then
			local row = split_y * 2
			local col = floor(split_x / 2)
			local test_y = -1 / 1.732 * offset_x + side_len / 2
			if offset_y < test_y then
				row = row - (1)
				col = col - (1)
			end
			return row + 1, col + 1
		end
		if offset_y < side_len * 3 / 2 then
			local row = split_y * 2
			local col = floor(split_x / 2)
			return row + 1, col + 1
		end
		if offset_y < side_len * 2 then
			local row = split_y * 2
			local col = floor(split_x / 2)
			local test_y = 1 / 1.732 * offset_x
			if offset_y - side_len * 3 / 2 > test_y then
				row = row + (1)
				col = col - (1)
			end
			return row + 1, col + 1
		end
		do
			local row = split_y * 2 + 1
			local col = floor(split_x / 2) - 1
			return row + 1, col + 1
		end
	else
		local split_y = floor(y / (side_len * 3))
		local offset_y = y - split_y * (side_len * 3)
		if offset_y < side_len / 2 then
			local row = split_y * 2
			local col = floor(split_x / 2)
			local test_y = 1 / 1.732 * offset_x
			if offset_y < test_y then
				row = row - (1)
			end
			return row + 1, col + 1
		end
		if offset_y < side_len * 3 / 2 then
			local row = split_y * 2
			local col = floor(split_x / 2)
			return row + 1, col + 1
		end
		if offset_y < side_len * 2 then
			local row = split_y * 2
			local col = floor(split_x / 2)
			local test_y = -1 / 1.732 * offset_x + side_len / 2
			if offset_y - side_len * 3 / 2 > test_y then
				row = row + (1)
			end
			return row + 1, col + 1
		end
		do
			local row = split_y * 2 + 1
			local col = floor(split_x / 2)
			return row + 1, col + 1
		end
	end
end

function ALittle.Tile_CalcRowColByPos(tile_map, x, y)
	local tile_type = tile_map.tile_type
	local side_len = tile_map.side_len
	if tile_type == 1 then
		local row = floor(y / side_len)
		local col = floor(x / side_len)
		return row + 1, col + 1
	end
	if tile_type == 3 then
		local col, row = ALittle.Tile_CalcRowColByPosInHexV(tile_map, y, x)
		return row, col
	end
	if tile_type == 2 then
		return ALittle.Tile_CalcRowColByPosInHexV(tile_map, x, y)
	end
	return 0, 0
end

function ALittle.Tile_CalcCellHeight(tile_map)
	local tile_type = tile_map.tile_type
	local side_len = tile_map.side_len
	if tile_type == 1 then
		return side_len
	end
	if tile_type == 2 then
		return side_len * 3
	end
	if tile_type == 3 then
		return side_len * 1.732
	end
	return 0
end

function ALittle.Tile_CalcCellWidth(tile_map)
	local tile_type = tile_map.tile_type
	local side_len = tile_map.side_len
	if tile_type == 1 then
		return side_len * 2
	end
	if tile_type == 2 then
		return side_len * 1.732
	end
	if tile_type == 3 then
		return side_len * 3
	end
	return 0
end

function ALittle.Tile_GetLayerByName(tile_map, name)
	for index, layer in ___ipairs(tile_map.layer_list) do
		if layer.name == name then
			return index
		end
	end
	return nil
end

end