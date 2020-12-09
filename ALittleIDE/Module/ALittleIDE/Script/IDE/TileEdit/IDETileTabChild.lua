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

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDETileCell = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDETileCell")

function ALittleIDE.IDETileCell:Init(user_info)
	self._user_info = user_info
	self.width = ALittleIDE.IDETileTabChild.CalcCellWidth(self._user_info)
	self._grid = self:CreateGrid()
	self:AddChild(self._grid)
	self._cells = ALittle.DisplayLayout(ALittleIDE.g_Control)
	self:AddChild(self._cells)
end

function ALittleIDE.IDETileCell:CreateGrid()
	local tile_type = self._user_info.tile_map.tile_type
	local side_len = self._user_info.tile_map.side_len
	if tile_type == 1 then
		local grid = ALittleIDE.g_Control:CreateControl("ide_tile_square_grid")
		grid.width = side_len
		grid.height = side_len
		return grid
	end
	if tile_type == 2 then
		local grid = ALittleIDE.g_Control:CreateControl("ide_tile_hex_v_grid")
		grid.width = side_len * 1.732
		grid.height = side_len * 2
		return grid
	end
	if tile_type == 3 then
		local grid = ALittleIDE.g_Control:CreateControl("ide_tile_hex_h_grid")
		grid.width = side_len * 2
		grid.height = side_len * 1.732
		return grid
	end
	return nil
end

assert(ALittleIDE.IDETabChild, " extends class:ALittleIDE.IDETabChild is nil")
ALittleIDE.IDETileTabChild = Lua.Class(ALittleIDE.IDETabChild, "ALittleIDE.IDETileTabChild")

function ALittleIDE.IDETileTabChild:Ctor(ctrl_sys, module, name, save, user_info)
	___rawset(self, "_user_info", user_info)
	___rawset(self, "_tab_screen", ALittleIDE.g_Control:CreateControl("ide_tile_tab_screen", self))
	self._tab_screen._user_data = self
	self._tab_screen.container = ALittleIDE.IDETileContainer(ALittleIDE.g_Control)
	___rawset(self, "_linear_1", ALittle.Linear(ALittleIDE.g_Control))
	self._linear_1.type = 2
	self._tab_screen:AddChild(self._linear_1)
	___rawset(self, "_linear_2", ALittle.Linear(ALittleIDE.g_Control))
	self._linear_2.type = 2
	self._tab_screen:AddChild(self._linear_2)
end

function ALittleIDE.IDETileTabChild:OnUndo()
end

function ALittleIDE.IDETileTabChild:OnRedo()
end

function ALittleIDE.IDETileTabChild:OnHide()
	ALittleIDE.g_IDECenter.center.tool_tile.visible = false
end

function ALittleIDE.IDETileTabChild:OnShow()
	ALittleIDE.g_IDECenter.center.tool_tile.visible = true
end

function ALittleIDE.IDETileTabChild:OnClose()
end

function ALittleIDE.IDETileTabChild:OnOpen()
	self._revoke_list = ALittle.RevokeList()
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
	local grid_map_width = ALittleIDE.IDETileTabChild.CalcCellWidth(self._user_info) * col_count
	self._linear_1.width = grid_map_width
	self._linear_2.width = grid_map_width
	self._linear_2.x = self:CalcLinear2OffsetX()
	self._linear_2.y = self:CalcLinear2OffsetY()
	self:ResizeGridMap(row_count, col_count)
end

function ALittleIDE.IDETileTabChild:ResizeGridMap(row_count, col_count)
	if row_count < 10 then
		row_count = 10
	end
	if col_count < 10 then
		col_count = 10
	end
	if row_count <= self._linear_1.child_count + self._linear_2.child_count and self._linear_1.childs[0].child_count <= col_count then
		return
	end
	local linear_height = ALittleIDE.IDETileTabChild.CalcCellHeight(self._user_info)
	for index, child in ___ipairs(self._linear_1.childs) do
		local col = child.child_count + 1
		while true do
			if not(col <= col_count) then break end
			local cell = ALittleIDE.IDETileCell(ALittleIDE.g_Control)
			cell:Init(self._user_info)
			child:AddChild(cell)
			col = col+(1)
		end
	end
	for index, child in ___ipairs(self._linear_2.childs) do
		local col = child.child_count + 1
		while true do
			if not(col <= col_count) then break end
			local cell = ALittleIDE.IDETileCell(ALittleIDE.g_Control)
			cell:Init(self._user_info)
			child:AddChild(cell)
			col = col+(1)
		end
	end
	local row = self._linear_1.child_count + self._linear_2.child_count
	while true do
		if not(row < row_count) then break end
		local linear = ALittle.Linear(ALittleIDE.g_Control)
		linear.type = 1
		linear.height = linear_height
		local col = 1
		while true do
			if not(col <= col_count) then break end
			local cell = ALittleIDE.IDETileCell(ALittleIDE.g_Control)
			cell:Init(self._user_info)
			linear:AddChild(cell)
			col = col+(1)
		end
		if row % 2 == 1 then
			self._linear_1:AddChild(linear)
		else
			self._linear_2:AddChild(linear)
		end
		row = row+(1)
	end
	self._tab_screen.container.width = self._linear_2.x + self._linear_2.width
	self._tab_screen.container.height = self._linear_2.y + self._linear_2.height
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

function ALittleIDE.IDETileTabChild.CalcCellWidth(user_info)
	local tile_type = user_info.tile_map.tile_type
	local side_len = user_info.tile_map.side_len
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

end