-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDETileContainer = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDETileContainer")

function ALittleIDE.IDETileContainer:ClipRect(x, y, width, height, h_move, v_move)
	for index, child in ___ipairs(self.childs) do
		child:ClipRect(x - self._x, y - self._y, width - self._x, height - self._y, h_move, v_move)
	end
end

assert(ALittleIDE.IDETabChild, " extends class:ALittleIDE.IDETabChild is nil")
ALittleIDE.IDETileTabChild = Lua.Class(ALittleIDE.IDETabChild, "ALittleIDE.IDETileTabChild")

function ALittleIDE.IDETileTabChild:Ctor(ctrl_sys, module, name, save, user_info)
	___rawset(self, "_user_info", user_info)
	___rawset(self, "_tab_screen", ALittleIDE.g_Control:CreateControl("ide_tile_tab_screen", self))
	self._tab_screen._user_data = self
	self._tab_screen.container = ALittleIDE.IDETileContainer(ALittleIDE.g_Control)
	___rawset(self, "_linear_grid_1", ALittle.Linear(ALittleIDE.g_Control))
	self._linear_grid_1.type = 2
	self._tab_screen:AddChild(self._linear_grid_1)
	___rawset(self, "_linear_grid_2", ALittle.Linear(ALittleIDE.g_Control))
	self._linear_grid_2.type = 2
	self._tab_screen:AddChild(self._linear_grid_2)
	___rawset(self, "_linear_tile_1", ALittle.DisplayGroup(ALittleIDE.g_Control))
	self._tab_screen:AddChild(self._linear_tile_1)
	___rawset(self, "_linear_tile_2", ALittle.DisplayGroup(ALittleIDE.g_Control))
	self._tab_screen:AddChild(self._linear_tile_2)
	___rawset(self, "_layer_edit", ALittleIDE.g_Control:CreateControl("ide_tile_layer_detail_layout"))
	self._layer_edit:Init(self, user_info)
end

function ALittleIDE.IDETileTabChild.__getter:layer_edit()
	return self._layer_edit
end

function ALittleIDE.IDETileTabChild:OnUndo()
end

function ALittleIDE.IDETileTabChild:OnRedo()
end

function ALittleIDE.IDETileTabChild:OnHide()
	ALittleIDE.g_IDECenter.center.tool_tile.visible = false
	self._layer_edit.visible = false
end

function ALittleIDE.IDETileTabChild:OnShow()
	ALittleIDE.g_IDECenter.center.tool_tile.visible = true
	self._layer_edit.visible = true
	ALittleIDE.g_IDECenter.center.detail_tree_tab.tab = ALittleIDE.g_IDECenter.center.tile_brush_edit
	ALittleIDE.g_IDECenter.center.project_edit_tab.tab = ALittleIDE.g_IDECenter.center.tile_brush_list
end

function ALittleIDE.IDETileTabChild:OnClose()
	ALittleIDE.g_IDECenter.center.tile_brush_edit.layer_container:RemoveChild(self._layer_edit)
end

function ALittleIDE.IDETileTabChild:OnOpen()
	self._revoke_list = ALittle.RevokeList()
	ALittleIDE.g_IDECenter.center.tile_brush_edit.layer_container:AddChild(self._layer_edit)
end

function ALittleIDE.IDETileTabChild:OnTabRightMenu(menu)
	menu:AddItem("获取焦点", Lua.Bind(self.ShowTileFocus, self))
end

function ALittleIDE.IDETileTabChild:ShowTileFocus()
	local tree = ALittleIDE.g_IDECenter.center.tile_list:GetFileTree(self._user_info.info.path)
	if tree == nil then
		return
	end
	ALittleIDE.g_IDECenter.center.project_edit_tab.tab = ALittleIDE.g_IDECenter.center.tile_list
	ALittleIDE.g_IDECenter.center.tile_list:ShowTreeItemFocus(tree)
end

function ALittleIDE.IDETileTabChild.__getter:tab_body()
	return self._tab_screen
end

function ALittleIDE.IDETileTabChild.__setter:save(value)
	if self._save == value then
		return
	end
	if value == false then
		self._save = false
		self:UpdateTitle()
		return
	end
	self._save = value
	self:UpdateTitle()
end

function ALittleIDE.IDETileTabChild.__getter:id()
	return self._user_info.info.path
end

function ALittleIDE.IDETileTabChild:Rename(name)
	self._name = name
	self:UpdateTitle()
end

function ALittleIDE.IDETileTabChild:UpdateTitle()
	local text = self._name
	if self._save == false then
		text = text .. " *"
	end
	ALittleIDE.g_IDECenter.center.content_edit.main_tab:SetChildText(self._tab_screen, text)
end

function ALittleIDE.IDETileTabChild.__getter:title()
	return self._name
end

function ALittleIDE.IDETileTabChild:UpdateUserInfo(info)
	self._user_info = info
end

function ALittleIDE.IDETileTabChild:CreateBySelect(info)
	self._user_info = info
	local col_count = info.tile_map.col_count + 10
	local row_count = info.tile_map.row_count + 10
	local grid_map_width = self:CalcCellWidth() * col_count
	self._linear_grid_1.width = grid_map_width
	self._linear_grid_2.width = grid_map_width
	self._linear_grid_2.x = self:CalcLinear2OffsetX()
	self._linear_grid_2.y = self:CalcLinear2OffsetY()
	self:ResizeGridMap(row_count, col_count)
end

function ALittleIDE.IDETileTabChild:ResizeLinear(linear_1, linear_2, row_count, col_count, layer)
	if row_count < 10 then
		row_count = 10
	end
	if col_count < 10 then
		col_count = 10
	end
	if row_count <= linear_1.child_count + linear_2.child_count and linear_1.childs[0].child_count <= col_count then
		return
	end
	local linear_height = ALittleIDE.IDETileTabChild.CalcCellHeight(self._user_info)
	for index, child in ___ipairs(linear_1.childs) do
		local col = child.child_count + 1
		while true do
			if not(col <= col_count) then break end
			if layer == 0 then
				local grid = self:CreateGrid()
				child:AddChild(grid)
			end
			col = col+(1)
		end
	end
	for index, child in ___ipairs(linear_2.childs) do
		local col = child.child_count + 1
		while true do
			if not(col <= col_count) then break end
			if layer == 0 then
				local grid = self:CreateGrid()
				child:AddChild(grid)
			end
			col = col+(1)
		end
	end
	local row = linear_1.child_count + linear_2.child_count
	while true do
		if not(row < row_count) then break end
		local linear = ALittle.Linear(ALittleIDE.g_Control)
		linear.type = 1
		linear.height = linear_height
		local col = 1
		while true do
			if not(col <= col_count) then break end
			if layer == 0 then
				local grid = self:CreateGrid()
				linear:AddChild(grid)
			end
			col = col+(1)
		end
		if row % 2 == 1 then
			linear_1:AddChild(linear)
		else
			linear_2:AddChild(linear)
		end
		row = row+(1)
	end
end

function ALittleIDE.IDETileTabChild:ResizeGridMap(row_count, col_count)
	self:ResizeLinear(self._linear_grid_1, self._linear_grid_2, row_count, col_count, 0)
	for index, linear in ___ipairs(self._linear_tile_1.childs) do
		self:ResizeLinear(linear, self._linear_tile_2.childs[index], row_count, col_count, index)
	end
	self._tab_screen.container.width = self._linear_grid_2.x + self._linear_grid_2.width
	self._tab_screen.container.height = self._linear_grid_2.y + self._linear_grid_2.height
	self._tab_screen:AdjustScrollBar()
end

function ALittleIDE.IDETileTabChild:CalcLinear2OffsetX()
	local tile_type = self._user_info.tile_map.tile_type
	local side_len = self._user_info.tile_map.side_len
	if tile_type == 1 then
		return 0
	end
	if tile_type == 2 then
		return side_len * 1.732 / 2
	end
	if tile_type == 3 then
		return side_len * 3 / 2
	end
	return 0
end

function ALittleIDE.IDETileTabChild:CalcLinear2OffsetY()
	local tile_type = self._user_info.tile_map.tile_type
	local side_len = self._user_info.tile_map.side_len
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

function ALittleIDE.IDETileTabChild.CalcCellHeight(user_info)
	local tile_type = user_info.tile_map.tile_type
	local side_len = user_info.tile_map.side_len
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

function ALittleIDE.IDETileTabChild:CalcCellWidth()
	local tile_type = self._user_info.tile_map.tile_type
	local side_len = self._user_info.tile_map.side_len
	if tile_type == 1 then
		return side_len
	end
	if tile_type == 2 then
		return side_len * 1.732
	end
	if tile_type == 3 then
		return side_len * 3
	end
	return 0
end

function ALittleIDE.IDETileTabChild:CalcPosByRC(row, col)
	local tile_type = self._user_info.tile_map.tile_type
	local side_len = self._user_info.tile_map.side_len
	if tile_type == 1 then
		return (row - 1) * side_len + side_len / 2, (col - 1) * side_len + side_len / 2
	end
	if tile_type == 2 then
		local x = (col - 1) * (side_len * 1.732) + (side_len * 1.732) / 2
		local y = (row - 1) * (side_len * 3 / 2) + side_len
		if row % 2 == 1 then
			x = x + ((side_len * 1.732) / 2)
		end
		return x, y
	end
	if tile_type == 3 then
		local x = (col - 1) * (side_len * 3 / 2) + side_len
		local y = (row - 1) * (side_len * 1.732) + (side_len * 1.732) / 2
		if col % 2 == 1 then
			y = y + ((side_len * 1.732) / 2)
		end
		return x, y
	end
	return 0, 0
end

function ALittleIDE.IDETileTabChild:CreateGrid()
	local tile_type = self._user_info.tile_map.tile_type
	local side_len = self._user_info.tile_map.side_len
	if tile_type == 1 then
		local cell = ALittle.DisplayLayout(ALittleIDE.g_Control)
		cell.width = self:CalcCellWidth()
		local grid = ALittleIDE.g_Control:CreateControl("ide_tile_square_grid")
		grid.width = side_len
		grid.height = side_len
		cell:AddChild(grid)
		return cell
	end
	if tile_type == 2 then
		local cell = ALittle.DisplayLayout(ALittleIDE.g_Control)
		cell.width = self:CalcCellWidth()
		local grid = ALittleIDE.g_Control:CreateControl("ide_tile_hex_v_grid")
		grid.width = side_len * 1.732
		grid.height = side_len * 2
		cell:AddChild(grid)
		return cell
	end
	if tile_type == 3 then
		local cell = ALittle.DisplayLayout(ALittleIDE.g_Control)
		cell.width = self:CalcCellWidth()
		local grid = ALittleIDE.g_Control:CreateControl("ide_tile_hex_h_grid")
		grid.width = side_len * 2
		grid.height = side_len * 1.732
		cell:AddChild(grid)
		return cell
	end
	return nil
end

end