-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.IDETabChild, " extends class:ALittleIDE.IDETabChild is nil")
ALittleIDE.IDETileTabChild = Lua.Class(ALittleIDE.IDETabChild, "ALittleIDE.IDETileTabChild")

function ALittleIDE.IDETileTabChild:Ctor(ctrl_sys, module, name, save, user_info)
	___rawset(self, "_user_info", user_info)
	___rawset(self, "_tab_screen", ALittleIDE.g_Control:CreateControl("ide_tile_tab_screen", self))
	self._tab_screen._user_data = self
end

function ALittleIDE.IDETileTabChild:OnUndo()
end

function ALittleIDE.IDETileTabChild:OnRedo()
end

function ALittleIDE.IDETileTabChild:OnHide()
end

function ALittleIDE.IDETileTabChild:OnShow()
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
	local width = 10
	if width < info.tile_map.width then
		width = info.tile_map.width
	end
	local height = 10
	if height < info.tile_map.height then
		height = info.tile_map.height
	end
	local row = 1
	while true do
		if not(row <= height) then break end
		local col = 1
		while true do
			if not(col <= width) then break end
			local grid = self:CreateGrid()
			local x, y = self:CalcPosByRC(row, col)
			grid.x = x
			grid.y = y
			self._tab_grid_container:AddChild(grid)
			col = col+(1)
		end
		row = row+(1)
	end
end

function ALittleIDE.IDETileTabChild:CreateGrid()
	local tile_type = self._user_info.tile_map.tile_type
	local side_len = self._user_info.tile_map.side_len
	if tile_type == 1 then
		local grid = ALittleIDE.g_Control:CreateControl("ide_tile_square_grid")
		grid.width = side_len
		grid.height = side_len
		grid.center_x = side_len / 2
		grid.center_y = side_len / 2
		return grid
	end
	if tile_type == 2 then
		local grid = ALittleIDE.g_Control:CreateControl("ide_tile_hex_v_grid")
		grid.width = side_len * 1.732
		grid.height = side_len * 2
		grid.center_x = side_len / 2
		grid.center_y = side_len / 2
		return grid
	end
	if tile_type == 3 then
		local grid = ALittleIDE.g_Control:CreateControl("ide_tile_hex_h_grid")
		grid.width = side_len * 2
		grid.height = side_len * 1.732
		grid.center_x = side_len / 2
		grid.center_y = side_len / 2
		return grid
	end
	return nil
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