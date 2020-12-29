-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
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
ALittle.RegStruct(1301789264, "ALittle.UIButtonDragBeginEvent", {
name = "ALittle.UIButtonDragBeginEvent", ns_name = "ALittle", rl_name = "UIButtonDragBeginEvent", hash_code = 1301789264,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
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
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name = "ALittle.UIButtonDragEndEvent", ns_name = "ALittle", rl_name = "UIButtonDragEndEvent", hash_code = 150587926,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(7944876, "ALittle.TileCell", {
name = "ALittle.TileCell", ns_name = "ALittle", rl_name = "TileCell", hash_code = 7944876,
name_list = {"tex_id"},
type_list = {"int"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDETileContainer = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDETileContainer")

function ALittleIDE.IDETileContainer:ClipRect(x, y, width, height, h_move, v_move)
	for index, child in ___ipairs(self.childs) do
		child:ClipRect(x - self._x, y - self._y, width - self._x, height - self._y, h_move, v_move)
	end
end

assert(ALittle.DisplayGroup, " extends class:ALittle.DisplayGroup is nil")
ALittleIDE.IDETileGroupContainer = Lua.Class(ALittle.DisplayGroup, "ALittleIDE.IDETileGroupContainer")

function ALittleIDE.IDETileGroupContainer:ClipRect(x, y, width, height, h_move, v_move)
	for index, child in ___ipairs(self.childs) do
		child:ClipRect(x - self._x, y - self._y, width - self._x, height - self._y, h_move, v_move)
	end
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDETileLinearContainer = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDETileLinearContainer")

function ALittleIDE.IDETileLinearContainer:ClipRect(x, y, width, height, h_move, v_move)
	self._linear_grid_1:ClipRect(x - self._x, y - self._y, width - self._x, height - self._y, h_move, v_move)
	self._linear_grid_2:ClipRect(x - self._x, y - self._y, width - self._x, height - self._y, h_move, v_move)
	for index, child in ___ipairs(self._group_tile.childs) do
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
	self._tile_container._linear_grid_1 = self._linear_grid_1
	self._tile_container:AddChild(self._linear_grid_1)
	___rawset(self, "_linear_grid_2", ALittle.Linear(ALittleIDE.g_Control))
	self._linear_grid_2.type = 2
	self._tile_container._linear_grid_2 = self._linear_grid_2
	self._tile_container:AddChild(self._linear_grid_2)
	___rawset(self, "_group_tile", ALittle.DisplayGroup(ALittleIDE.g_Control))
	self._tile_container._group_tile = self._group_tile
	self._tile_container:AddChild(self._group_tile)
	___rawset(self, "_layer_edit", ALittleIDE.g_Control:CreateControl("ide_tile_layer_detail_layout"))
	ALittleIDE.g_IDECenter.center:AddEventListener(___all_struct[-751714957], self, self.HandleHandDrag)
	self._tab_rb_quad:AddEventListener(___all_struct[1883782801], self, self.HandleQuadLButtonDown)
	self._tab_rb_quad:AddEventListener(___all_struct[1301789264], self, self.HandleQuadDragBegin)
	self._tab_rb_quad:AddEventListener(___all_struct[1337289812], self, self.HandleQuadDrag)
	self._tab_rb_quad:AddEventListener(___all_struct[150587926], self, self.HandleQuadDragEnd)
end

function ALittleIDE.IDETileTabChild:HandleHandDrag(event)
	self._tab_rb_quad.hand_cursor = event.value
end

function ALittleIDE.IDETileTabChild:HandleQuadLButtonDown(event)
	if ALittleIDE.g_IDECenter.center.tile_brush then
		local brush_info = ALittleIDE.g_IDECenter.center.tile_brush_edit:GetBrush()
		if brush_info == nil then
			g_AUITool:ShowNotice("提示", "请先从地块库选择地块")
			return
		end
		local layer_info, layer_index = self._layer_edit:GetCurLayerInfo()
		if layer_info == nil then
			g_AUITool:ShowNotice("提示", "请先选择图层")
			return
		end
		local row, col = ALittle.Tile_CalcRowColByPos(self._user_info.tile_map, event.rel_x, event.rel_y)
		if row <= 0 or col <= 0 then
			return
		end
		self:ResizeGridMap(row, col)
		self._drag_cell_row = row
		self._drag_cell_col = col
		local col_map = layer_info._layer.cell_map[row]
		if col_map == nil then
			col_map = {}
			layer_info._layer.cell_map[row] = col_map
		end
		local cell = col_map[col]
		if cell == nil then
			cell = {}
			col_map[col] = cell
		end
		local old_tex_path
		if cell.tex_id ~= nil then
			old_tex_path = layer_info._user_info.tile_map.tex_map[cell.tex_id]
		end
		local tex_id = layer_info._user_info.tex_id_map[brush_info.tex_path]
		if tex_id == nil then
			tex_id = layer_info._user_info.tex_id_max + 1
			layer_info._user_info.tex_id_max = tex_id
			layer_info._user_info.tex_id_map[brush_info.tex_path] = tex_id
			layer_info._user_info.tile_map.tex_map[tex_id] = brush_info.tex_path
		end
		cell.tex_id = tex_id
		local image = self:GetImage(layer_index, row, col)
		image:SetTextureCut(brush_info.module_path, 0, 0, true)
		local revoke = ALittleIDE.IDETileBrushCellRevoke(self, layer_info, cell, image, old_tex_path, brush_info.tex_path)
		self._revoke_list:PushRevoke(revoke)
		self.save = false
	elseif ALittleIDE.g_IDECenter.center.tile_erase then
		local layer_info, layer_index = self._layer_edit:GetCurLayerInfo()
		if layer_info == nil then
			g_AUITool:ShowNotice("提示", "请先选择图层")
			return
		end
		local row, col = ALittle.Tile_CalcRowColByPos(self._user_info.tile_map, event.rel_x, event.rel_y)
		if row <= 0 or col <= 0 then
			return
		end
		self:ResizeGridMap(row, col)
		self._drag_cell_row = row
		self._drag_cell_col = col
		local col_map = layer_info._layer.cell_map[row]
		if col_map == nil then
			return
		end
		local cell = col_map[col]
		if cell == nil then
			return
		end
		if cell.tex_id == nil then
			return
		end
		local old_tex_path = layer_info._user_info.tile_map.tex_map[cell.tex_id]
		cell.tex_id = nil
		local image = self:GetImage(layer_index, row, col)
		image:SetTextureCut(nil, 0, 0, true)
		local revoke = ALittleIDE.IDETileBrushCellRevoke(self, layer_info, cell, image, old_tex_path, nil)
		self._revoke_list:PushRevoke(revoke)
		self.save = false
	end
end

function ALittleIDE.IDETileTabChild:HandleQuadDragBegin(event)
	if ALittleIDE.g_IDECenter.center.tile_handdrag then
		event.target = self._tab_screen
		self._tab_screen:DispatchEvent(___all_struct[1301789264], event)
	end
end

function ALittleIDE.IDETileTabChild:HandleQuadDrag(event)
	if ALittleIDE.g_IDECenter.center.tile_brush then
		local brush_info = ALittleIDE.g_IDECenter.center.tile_brush_edit:GetBrush()
		if brush_info == nil then
			return
		end
		local layer_info, layer_index = self._layer_edit:GetCurLayerInfo()
		if layer_info == nil then
			return
		end
		local row, col = ALittle.Tile_CalcRowColByPos(self._user_info.tile_map, event.rel_x, event.rel_y)
		if row <= 0 or col <= 0 then
			return
		end
		self:ResizeGridMap(row, col)
		if self._drag_cell_row == row and self._drag_cell_col == col then
			return
		end
		self._drag_cell_row = row
		self._drag_cell_col = col
		local col_map = layer_info._layer.cell_map[row]
		if col_map == nil then
			col_map = {}
			layer_info._layer.cell_map[row] = col_map
		end
		local cell = col_map[col]
		if cell == nil then
			cell = {}
			col_map[col] = cell
		end
		local old_tex_path
		if cell.tex_id ~= nil then
			old_tex_path = layer_info._user_info.tile_map.tex_map[cell.tex_id]
		end
		local tex_id = layer_info._user_info.tex_id_map[brush_info.tex_path]
		if tex_id == nil then
			tex_id = layer_info._user_info.tex_id_max + 1
			layer_info._user_info.tex_id_max = tex_id
			layer_info._user_info.tex_id_map[brush_info.tex_path] = tex_id
			layer_info._user_info.tile_map.tex_map[tex_id] = brush_info.tex_path
		end
		cell.tex_id = tex_id
		local image = self:GetImage(layer_index, row, col)
		image:SetTextureCut(brush_info.module_path, 0, 0, true)
		local revoke = ALittleIDE.IDETileBrushCellRevoke(self, layer_info, cell, image, old_tex_path, brush_info.tex_path)
		self._revoke_list:PushRevoke(revoke)
		self.save = false
	elseif ALittleIDE.g_IDECenter.center.tile_handdrag then
		event.target = self._tab_screen
		self._tab_screen:DispatchEvent(___all_struct[1337289812], event)
	elseif ALittleIDE.g_IDECenter.center.tile_erase then
		local layer_info, layer_index = self._layer_edit:GetCurLayerInfo()
		if layer_info == nil then
			return
		end
		local row, col = ALittle.Tile_CalcRowColByPos(self._user_info.tile_map, event.rel_x, event.rel_y)
		if row <= 0 or col <= 0 then
			return
		end
		self:ResizeGridMap(row, col)
		if self._drag_cell_row == row and self._drag_cell_col == col then
			return
		end
		self._drag_cell_row = row
		self._drag_cell_col = col
		local col_map = layer_info._layer.cell_map[row]
		if col_map == nil then
			return
		end
		local cell = col_map[col]
		if cell == nil then
			return
		end
		if cell.tex_id == nil then
			return
		end
		local old_tex_path = layer_info._user_info.tile_map.tex_map[cell.tex_id]
		cell.tex_id = nil
		local image = self:GetImage(layer_index, row, col)
		image:SetTextureCut(nil, 0, 0, true)
		local revoke = ALittleIDE.IDETileBrushCellRevoke(self, layer_info, cell, image, old_tex_path, nil)
		self._revoke_list:PushRevoke(revoke)
		self.save = false
	end
end

function ALittleIDE.IDETileTabChild:HandleQuadDragEnd(event)
	if ALittleIDE.g_IDECenter.center.tile_brush then
	elseif ALittleIDE.g_IDECenter.center.tile_handdrag then
		event.target = self._tab_screen
		self._tab_screen:DispatchEvent(___all_struct[150587926], event)
	elseif ALittleIDE.g_IDECenter.center.tile_erase then
	end
	self._drag_cell_row = nil
	self._drag_cell_col = nil
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
	self._revoke_list = ALittle.RevokeList(10000)
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

function ALittleIDE.IDETileTabChild:CreateLayer()
	local group = ALittle.DisplayGroup(ALittleIDE.g_Control)
	local linear_1 = ALittle.Linear(ALittleIDE.g_Control)
	linear_1.type = 2
	group:AddChild(linear_1)
	local linear_2 = ALittle.Linear(ALittleIDE.g_Control)
	linear_2.type = 2
	linear_2.x = ALittle.Tile_CalcLinear2OffsetX(self._user_info.tile_map)
	linear_2.y = ALittle.Tile_CalcLinear2OffsetY(self._user_info.tile_map)
	group:AddChild(linear_2)
	self._group_tile:AddChild(group)
	local row_count = self._linear_grid_1.child_count
	local col_count = self._linear_grid_1.childs[1].child_count
	self:ResizeLinear(linear_1, linear_2, row_count, col_count, self._group_tile.child_count)
	return group, linear_1, linear_2
end

function ALittleIDE.IDETileTabChild:GetLayer(index)
	local group = self._group_tile:GetChildByIndex(index)
	if group == nil then
		return nil, nil, nil
	end
	local linear_1 = group:GetChildByIndex(1)
	local linear_2 = group:GetChildByIndex(2)
	return group, linear_1, linear_2
end

function ALittleIDE.IDETileTabChild:GetImage(layer, row, col)
	local group, linear_1, linear_2 = self:GetLayer(layer)
	if group == nil then
		return nil
	end
	local tile_type = self._user_info.tile_map.tile_type
	if tile_type == 2 then
		if row % 2 == 1 then
			return linear_1.childs[ALittle.Math_Floor(row / 2) + 1].childs[col]._user_data
		end
		return linear_2.childs[ALittle.Math_Floor(row / 2)].childs[col]._user_data
	else
		if col % 2 == 1 then
			return linear_1.childs[row].childs[ALittle.Math_Floor(col / 2) + 1]._user_data
		end
		return linear_2.childs[row].childs[ALittle.Math_Floor(col / 2)]._user_data
	end
end

function ALittleIDE.IDETileTabChild:AddLayer(group, index)
	self._group_tile:AddChild(group, index)
end

function ALittleIDE.IDETileTabChild:RemoveLayer(group)
	self._group_tile:RemoveChild(group)
end

function ALittleIDE.IDETileTabChild:SetLayerIndex(group, index)
	self._group_tile:SetChildIndex(group, index)
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
	local ui = ALittleIDE.g_IDEProject.project.ui[ALittleIDE.g_IDEProject.project.name]
	if ui == nil then
		g_AUITool:ShowNotice("提示", "ui不存在")
		return
	end
	local row_count = 0
	local col_count = 0
	for index, layer in ___ipairs(self._user_info.tile_map.layer_list) do
		for row, cell_map in ___pairs(layer.cell_map) do
			for col, cell in ___pairs(cell_map) do
				if col > col_count then
					col_count = col
				end
			end
			if row > row_count then
				row_count = row
			end
		end
	end
	self._user_info.tile_map.row_count = row_count
	self._user_info.tile_map.col_count = col_count
	ui.control:WriteMessageToFile(___all_struct[-1281734132], self._user_info.tile_map, self._user_info.info.path)
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
	info.tex_id_map = {}
	info.tex_id_max = 0
	for tex_id, tex_path in ___pairs(info.tile_map.tex_map) do
		info.tex_id_map[tex_path] = tex_id
		if info.tex_id_max < tex_id then
			info.tex_id_max = tex_id
		end
	end
	local col_count = info.tile_map.col_count
	if col_count < 10 then
		col_count = 10
	end
	local row_count = info.tile_map.row_count
	if row_count < 10 then
		row_count = 10
	end
	local grid_map_width = ALittle.Tile_CalcCellWidth(self._user_info.tile_map) * col_count
	self._linear_grid_1.width = grid_map_width
	self._linear_grid_2.width = grid_map_width
	self._linear_grid_2.x = ALittle.Tile_CalcLinear2OffsetX(self._user_info.tile_map)
	self._linear_grid_2.y = ALittle.Tile_CalcLinear2OffsetY(self._user_info.tile_map)
	for index, layer in ___ipairs(info.tile_map.layer_list) do
		local group = ALittle.DisplayGroup(ALittleIDE.g_Control)
		local linear_1 = ALittle.Linear(ALittleIDE.g_Control)
		linear_1.type = 2
		linear_1.width = grid_map_width
		group:AddChild(linear_1)
		local linear_2 = ALittle.Linear(ALittleIDE.g_Control)
		linear_2.type = 2
		linear_2.width = grid_map_width
		linear_2.x = ALittle.Tile_CalcLinear2OffsetX(self._user_info.tile_map)
		linear_2.y = ALittle.Tile_CalcLinear2OffsetY(self._user_info.tile_map)
		group:AddChild(linear_2)
		self._group_tile:AddChild(group)
	end
	self:ResizeGridMap(row_count, col_count)
	for index, layer in ___ipairs(self._user_info.tile_map.layer_list) do
		for row, col_map in ___pairs(layer.cell_map) do
			for col, cell in ___pairs(col_map) do
				if cell.tex_id ~= nil then
					local texture_name = self._user_info.tile_map.tex_map[cell.tex_id]
					if texture_name ~= nil then
						local image = self:GetImage(index, row, col)
						image:SetTextureCut("Module/" .. ALittleIDE.g_IDEProject.project.name .. "/Texture/" .. texture_name, 0, 0, true)
					end
				end
			end
		end
	end
	self._layer_edit:Init(self, self._user_info)
	self._tab_screen:RefreshClipDisLine()
end

function ALittleIDE.IDETileTabChild:ResizeLinear(linear_1, linear_2, row_count, col_count, layer)
	if self._user_info.tile_map.tile_type == 2 then
		if row_count <= linear_1.child_count + linear_2.child_count and col_count <= linear_1.childs[1].child_count then
			return
		end
		linear_1.width = ALittle.Tile_CalcCellWidth(self._user_info.tile_map) * col_count
		linear_2.width = linear_1.width
		local linear_height = ALittle.Tile_CalcCellHeight(self._user_info.tile_map)
		for index, child in ___ipairs(linear_1.childs) do
			local col = child.child_count + 1
			while true do
				if not(col <= col_count) then break end
				if layer == 0 then
					child:AddChild(self:CreateGrid())
				else
					child:AddChild(self:CreateImage())
				end
				col = col+(1)
			end
		end
		for index, child in ___ipairs(linear_2.childs) do
			local col = child.child_count + 1
			while true do
				if not(col <= col_count) then break end
				if layer == 0 then
					child:AddChild(self:CreateGrid())
				else
					child:AddChild(self:CreateImage())
				end
				col = col+(1)
			end
		end
		local row = linear_1.child_count + linear_2.child_count + 1
		while true do
			if not(row <= row_count) then break end
			local linear = ALittle.Linear(ALittleIDE.g_Control)
			linear.type = 1
			linear.height = linear_height
			local col = 1
			while true do
				if not(col <= col_count) then break end
				if layer == 0 then
					linear:AddChild(self:CreateGrid())
				else
					linear:AddChild(self:CreateImage())
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
	else
		if row_count <= linear_1.child_count and col_count <= linear_1.childs[1].child_count + linear_2.childs[1].child_count then
			return
		end
		local cell_width = ALittle.Tile_CalcCellWidth(self._user_info.tile_map)
		local linear_height = ALittle.Tile_CalcCellHeight(self._user_info.tile_map)
		local col_count_1 = ALittle.Math_Ceil(col_count / 2)
		linear_1.width = cell_width * col_count_1
		for index, child in ___ipairs(linear_1.childs) do
			local col = child.child_count + 1
			while true do
				if not(col <= col_count_1) then break end
				if layer == 0 then
					child:AddChild(self:CreateGrid())
				else
					child:AddChild(self:CreateImage())
				end
				col = col+(1)
			end
		end
		local col_count_2 = ALittle.Math_Floor(col_count / 2)
		linear_2.width = cell_width * col_count_2
		for index, child in ___ipairs(linear_2.childs) do
			local col = child.child_count + 1
			while true do
				if not(col <= col_count_2) then break end
				if layer == 0 then
					child:AddChild(self:CreateGrid())
				else
					child:AddChild(self:CreateImage())
				end
				col = col+(1)
			end
		end
		local row = linear_1.child_count + 1
		while true do
			if not(row <= row_count) then break end
			local linear = ALittle.Linear(ALittleIDE.g_Control)
			linear.type = 1
			linear.height = linear_height
			local col = 1
			while true do
				if not(col <= col_count_1) then break end
				if layer == 0 then
					linear:AddChild(self:CreateGrid())
				else
					linear:AddChild(self:CreateImage())
				end
				col = col+(1)
			end
			linear_1:AddChild(linear)
			row = row+(1)
		end
		local row = linear_2.child_count + 1
		while true do
			if not(row <= row_count) then break end
			local linear = ALittle.Linear(ALittleIDE.g_Control)
			linear.type = 1
			linear.height = linear_height
			local col = 1
			while true do
				if not(col <= col_count_2) then break end
				if layer == 0 then
					linear:AddChild(self:CreateGrid())
				else
					linear:AddChild(self:CreateImage())
				end
				col = col+(1)
			end
			linear_2:AddChild(linear)
			row = row+(1)
		end
	end
end

function ALittleIDE.IDETileTabChild:ResizeGridMap(row_count, col_count)
	local cur_row_count = 0
	local cur_col_count = 0
	if self._user_info.tile_map.tile_type == 2 then
		cur_row_count = self._linear_grid_1.child_count + self._linear_grid_2.child_count
		if cur_row_count > 0 then
			cur_col_count = self._linear_grid_1.childs[1].child_count
		end
	else
		cur_row_count = self._linear_grid_1.child_count
		if cur_row_count > 0 then
			cur_col_count = self._linear_grid_1.childs[1].child_count + self._linear_grid_2.childs[1].child_count
		end
	end
	if row_count < cur_row_count then
		row_count = cur_row_count
	end
	if col_count < cur_col_count then
		col_count = cur_col_count
	end
	self:ResizeLinear(self._linear_grid_1, self._linear_grid_2, row_count, col_count, 0)
	for index, group in ___ipairs(self._group_tile.childs) do
		self:ResizeLinear(group:GetChildByIndex(1), group:GetChildByIndex(2), row_count, col_count, index)
	end
	local width_1 = self._linear_grid_1.x + self._linear_grid_1.width
	local width_2 = self._linear_grid_2.x + self._linear_grid_2.width
	local height_1 = self._linear_grid_1.y + self._linear_grid_1.height
	local height_2 = self._linear_grid_2.y + self._linear_grid_2.height
	self._tab_screen.container.width = ALittle.Math_Max(width_1, width_2) + 100
	self._tab_screen.container.height = ALittle.Math_Max(height_1, height_2) + 100
	self._tab_screen:AdjustScrollBar()
end

function ALittleIDE.IDETileTabChild:CreateGrid()
	local tile_type = self._user_info.tile_map.tile_type
	local side_len = self._user_info.tile_map.side_len
	if tile_type == 1 then
		local cell = ALittle.DisplayLayout(ALittleIDE.g_Control)
		cell.width = ALittle.Tile_CalcCellWidth(self._user_info.tile_map)
		local grid = ALittleIDE.g_Control:CreateControl("ide_tile_square_grid")
		grid.width = side_len
		grid.height = side_len
		cell:AddChild(grid)
		return cell
	end
	if tile_type == 2 then
		local cell = ALittle.DisplayLayout(ALittleIDE.g_Control)
		cell.width = ALittle.Tile_CalcCellWidth(self._user_info.tile_map)
		local grid = ALittleIDE.g_Control:CreateControl("ide_tile_hex_v_grid")
		grid.width = side_len * 1.732
		grid.height = side_len * 2
		cell:AddChild(grid)
		return cell
	end
	if tile_type == 3 then
		local cell = ALittle.DisplayLayout(ALittleIDE.g_Control)
		cell.width = ALittle.Tile_CalcCellWidth(self._user_info.tile_map)
		local grid = ALittleIDE.g_Control:CreateControl("ide_tile_hex_h_grid")
		grid.width = side_len * 2
		grid.height = side_len * 1.732
		cell:AddChild(grid)
		return cell
	end
	return nil
end

function ALittleIDE.IDETileTabChild:CreateImage()
	local tile_type = self._user_info.tile_map.tile_type
	local side_len = self._user_info.tile_map.side_len
	if tile_type == 1 then
		local cell = ALittle.DisplayLayout(ALittleIDE.g_Control)
		cell.width = ALittle.Tile_CalcCellWidth(self._user_info.tile_map)
		local grid = ALittle.Image(ALittleIDE.g_Control)
		cell._user_data = grid
		grid.width = self._user_info.tile_map.tile_width
		grid.height = self._user_info.tile_map.tile_height
		grid.x = self._user_info.tile_map.tile_x
		grid.y = self._user_info.tile_map.tile_y
		cell:AddChild(grid)
		return cell
	end
	if tile_type == 2 then
		local cell = ALittle.DisplayLayout(ALittleIDE.g_Control)
		cell.width = ALittle.Tile_CalcCellWidth(self._user_info.tile_map)
		local grid = ALittle.Image(ALittleIDE.g_Control)
		cell._user_data = grid
		grid.width = self._user_info.tile_map.tile_width
		grid.height = self._user_info.tile_map.tile_height
		grid.x = self._user_info.tile_map.tile_x
		grid.y = self._user_info.tile_map.tile_y
		cell:AddChild(grid)
		return cell
	end
	if tile_type == 3 then
		local cell = ALittle.DisplayLayout(ALittleIDE.g_Control)
		cell.width = ALittle.Tile_CalcCellWidth(self._user_info.tile_map)
		local grid = ALittle.Image(ALittleIDE.g_Control)
		cell._user_data = grid
		grid.width = self._user_info.tile_map.tile_width
		grid.height = self._user_info.tile_map.tile_height
		grid.x = self._user_info.tile_map.tile_x
		grid.y = self._user_info.tile_map.tile_y
		cell:AddChild(grid)
		return cell
	end
	return nil
end

end