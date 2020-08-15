-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.G2048 == nil then _G.G2048 = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1842382794, "G2048.ItemInfo", {
name = "G2048.ItemInfo", ns_name = "G2048", rl_name = "ItemInfo", hash_code = -1842382794,
name_list = {"item","row","col"},
type_list = {"ALittle.DisplayObject","int","int"},
option_map = {}
})

G2048.g_GConfig = nil
G2048.GCenter = Lua.Class(nil, "G2048.GCenter")

function G2048.GCenter:Ctor()
	___rawset(self, "_loop_group", {})
end

function G2048.GCenter:ClearAnti()
	for k, v in ___pairs(self._loop_group) do
		if v:IsCompleted() == false then
			v:SetCompleted()
		end
	end
	self._loop_group = {}
end

function G2048.GCenter:Setup()
	G2048.g_GConfig = ALittle.CreateConfigSystem(G2048.g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(5, 2)
	self._main_layer = ALittle.DisplayLayout(G2048.g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	G2048.g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(G2048.g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	G2048.g_LayerGroup:AddChild(self._dialog_layer, nil)
	G2048.g_Control:PrepareTexture({"item_2", "item_4", "item_8", "item_16", "item_32", "item_64", "item_128", "item_256", "item_512", "item_1024", "item_2048"}, nil)
	G2048.g_Control:CreateControl("main_scene", self, self._main_layer)
	self._max_score_text._user_data = G2048.g_GConfig:GetConfig("max_score", 0)
	self._max_score_text.text = self._max_score_text._user_data
	self:Restart()
end

function G2048.GCenter:ShowMainMenu(content, show_back)
	if self._main_menu == nil then
		self._main_menu = G2048.g_Control:CreateControl("main_menu", self, nil)
		self._dialog_layer:AddChild(self._main_menu, nil)
	end
	self._main_menu.visible = true
	self._menu_content.text = content
	self._menu_back.visible = show_back
end

function G2048.GCenter:Restart()
	if self._main_menu ~= nil then
		self._main_menu.visible = false
	end
	self._score_text.text = "0"
	self._score_text._user_data = 0
	self._data_map = {}
	self._data_map[1] = {}
	self._data_map[2] = {}
	self._data_map[3] = {}
	self._data_map[4] = {}
	self._loop_group = {}
	self._tile_container:RemoveAllChild()
	self:GenerateItem(0)
	self:GenerateItem(0)
	self._item_moved = false
	self._loop_delay = 0
	self._drag_quad:DelayFocus()
end

function G2048.GCenter:GenerateItem(delay_time)
	local list = {}
	local list_count = 0
	local i = 1
	while true do
		if not(i <= 4) then break end
		local j = 1
		while true do
			if not(j <= 4) then break end
			if self._data_map[i][j] == nil then
				local data = {}
				data[1] = i
				data[2] = j
				list_count = list_count + 1
				list[list_count] = data
			end
			j = j+(1)
		end
		i = i+(1)
	end
	if list_count == 0 then
		return false
	end
	local rand1 = ALittle.Math_RandomInt(1, 100)
	local number = 2
	if rand1 > 50 then
		number = 4
	end
	local rand2 = ALittle.Math_RandomInt(1, list_count)
	local row = list[rand2][1]
	local col = list[rand2][2]
	self:BornItem(number, row, col, delay_time, true)
	return true
end

function G2048.GCenter:CalcLeft()
	local moved = false
	local i = 1
	while true do
		if not(i <= 4) then break end
		local list = {}
		local list_count = 0
		local j = 1
		while true do
			if not(j <= 4) then break end
			if self._data_map[i][j] ~= nil then
				local info = {}
				info.item = self._data_map[i][j]
				info.row = i
				info.col = j
				list_count = list_count + 1
				list[list_count] = info
			end
			j = j+(1)
		end
		local new_list = {}
		if list_count == 1 then
			self:TransItem(list[1], i, 1)
		elseif list_count == 2 then
			if list[1].item._user_data == list[2].item._user_data then
				self:CombineItems(list[1], list[2], i, 1)
			else
				self:TransItem(list[1], i, 1)
				self:TransItem(list[2], i, 2)
			end
		elseif list_count == 3 then
			if list[1].item._user_data == list[2].item._user_data then
				self:CombineItems(list[1], list[2], i, 1)
				self:TransItem(list[3], i, 2)
			elseif list[2].item._user_data == list[3].item._user_data then
				self:TransItem(list[1], i, 1)
				self:CombineItems(list[2], list[3], i, 2)
			else
				self:TransItem(list[1], i, 1)
				self:TransItem(list[2], i, 2)
				self:TransItem(list[3], i, 3)
			end
		elseif list_count == 4 then
			if list[1].item._user_data == list[2].item._user_data then
				self:CombineItems(list[1], list[2], i, 1)
				if list[3].item._user_data == list[4].item._user_data then
					self:CombineItems(list[3], list[4], i, 2)
				else
					self:TransItem(list[3], i, 2)
					self:TransItem(list[4], i, 3)
				end
			elseif list[2].item._user_data == list[3].item._user_data then
				self:TransItem(list[1], i, 1)
				self:CombineItems(list[2], list[3], i, 2)
				self:TransItem(list[4], i, 3)
			elseif list[3].item._user_data == list[4].item._user_data then
				self:TransItem(list[1], i, 1)
				self:TransItem(list[2], i, 2)
				self:CombineItems(list[3], list[4], i, 3)
			end
		end
		i = i+(1)
	end
end

function G2048.GCenter:CalcRight()
	local i = 1
	while true do
		if not(i <= 4) then break end
		local list = {}
		local list_count = 0
		local j = 4
		while true do
			if not(j >= 1) then break end
			if self._data_map[i][j] ~= nil then
				local info = {}
				info.item = self._data_map[i][j]
				info.row = i
				info.col = j
				list_count = list_count + 1
				list[list_count] = info
			end
			j = j+(-1)
		end
		local new_list = {}
		if list_count == 1 then
			self:TransItem(list[1], i, 5 - 1)
		elseif list_count == 2 then
			if list[1].item._user_data == list[2].item._user_data then
				self:CombineItems(list[1], list[2], i, 5 - 1)
			else
				self:TransItem(list[1], i, 5 - 1)
				self:TransItem(list[2], i, 5 - 2)
			end
		elseif list_count == 3 then
			if list[1].item._user_data == list[2].item._user_data then
				self:CombineItems(list[1], list[2], i, 5 - 1)
				self:TransItem(list[3], i, 5 - 2)
			elseif list[2].item._user_data == list[3].item._user_data then
				self:TransItem(list[1], i, 5 - 1)
				self:CombineItems(list[2], list[3], i, 5 - 2)
			else
				self:TransItem(list[1], i, 5 - 1)
				self:TransItem(list[2], i, 5 - 2)
				self:TransItem(list[3], i, 5 - 3)
			end
		elseif list_count == 4 then
			if list[1].item._user_data == list[2].item._user_data then
				self:CombineItems(list[1], list[2], i, 5 - 1)
				if list[3].item._user_data == list[4].item._user_data then
					self:CombineItems(list[3], list[4], i, 5 - 2)
				else
					self:TransItem(list[3], i, 5 - 2)
					self:TransItem(list[4], i, 5 - 3)
				end
			elseif list[2].item._user_data == list[3].item._user_data then
				self:TransItem(list[1], i, 5 - 1)
				self:CombineItems(list[2], list[3], i, 5 - 2)
				self:TransItem(list[4], i, 5 - 3)
			elseif list[3].item._user_data == list[4].item._user_data then
				self:TransItem(list[1], i, 5 - 1)
				self:TransItem(list[2], i, 5 - 2)
				self:CombineItems(list[3], list[4], i, 5 - 3)
			end
		end
		i = i+(1)
	end
end

function G2048.GCenter:CalcUp()
	local j = 1
	while true do
		if not(j <= 4) then break end
		local list = {}
		local list_count = 0
		local i = 1
		while true do
			if not(i <= 4) then break end
			if self._data_map[i][j] ~= nil then
				local info = {}
				info.item = self._data_map[i][j]
				info.row = i
				info.col = j
				list_count = list_count + 1
				list[list_count] = info
			end
			i = i+(1)
		end
		local new_list = {}
		if list_count == 1 then
			self:TransItem(list[1], 1, j)
		elseif list_count == 2 then
			if list[1].item._user_data == list[2].item._user_data then
				self:CombineItems(list[1], list[2], 1, j)
			else
				self:TransItem(list[1], 1, j)
				self:TransItem(list[2], 2, j)
			end
		elseif list_count == 3 then
			if list[1].item._user_data == list[2].item._user_data then
				self:CombineItems(list[1], list[2], 1, j)
				self:TransItem(list[3], 2, j)
			elseif list[2].item._user_data == list[3].item._user_data then
				self:TransItem(list[1], 1, j)
				self:CombineItems(list[2], list[3], 2, j)
			else
				self:TransItem(list[1], 1, j)
				self:TransItem(list[2], 2, j)
				self:TransItem(list[3], 3, j)
			end
		elseif list_count == 4 then
			if list[1].item._user_data == list[2].item._user_data then
				self:CombineItems(list[1], list[2], 1, j)
				if list[3].item._user_data == list[4].item._user_data then
					self:CombineItems(list[3], list[4], 2, j)
				else
					self:TransItem(list[3], 2, j)
					self:TransItem(list[4], 3, j)
				end
			elseif list[2].item._user_data == list[3].item._user_data then
				self:TransItem(list[1], 1, j)
				self:CombineItems(list[2], list[3], 2, j)
				self:TransItem(list[4], 3, j)
			elseif list[3].item._user_data == list[4].item._user_data then
				self:TransItem(list[1], 1, j)
				self:TransItem(list[2], 2, j)
				self:CombineItems(list[3], list[4], 3, j)
			end
		end
		j = j+(1)
	end
end

function G2048.GCenter:CalcDown()
	local j = 1
	while true do
		if not(j <= 4) then break end
		local list = {}
		local list_count = 0
		local i = 4
		while true do
			if not(i >= 1) then break end
			if self._data_map[i][j] ~= nil then
				local info = {}
				info.item = self._data_map[i][j]
				info.row = i
				info.col = j
				list_count = list_count + 1
				list[list_count] = info
			end
			i = i+(-1)
		end
		local new_list = {}
		if list_count == 1 then
			self:TransItem(list[1], 5 - 1, j)
		elseif list_count == 2 then
			if list[1].item._user_data == list[2].item._user_data then
				self:CombineItems(list[1], list[2], 5 - 1, j)
			else
				self:TransItem(list[1], 5 - 1, j)
				self:TransItem(list[2], 5 - 2, j)
			end
		elseif list_count == 3 then
			if list[1].item._user_data == list[2].item._user_data then
				self:CombineItems(list[1], list[2], 5 - 1, j)
				self:TransItem(list[3], 5 - 2, j)
			elseif list[2].item._user_data == list[3].item._user_data then
				self:TransItem(list[1], 5 - 1, j)
				self:CombineItems(list[2], list[3], 5 - 2, j)
			else
				self:TransItem(list[1], 5 - 1, j)
				self:TransItem(list[2], 5 - 2, j)
				self:TransItem(list[3], 5 - 3, j)
			end
		elseif list_count == 4 then
			if list[1].item._user_data == list[2].item._user_data then
				self:CombineItems(list[1], list[2], 5 - 1, j)
				if list[3].item._user_data == list[4].item._user_data then
					self:CombineItems(list[3], list[4], 5 - 2, j)
				else
					self:TransItem(list[3], 5 - 2, j)
					self:TransItem(list[4], 5 - 3, j)
				end
			elseif list[2].item._user_data == list[3].item._user_data then
				self:TransItem(list[1], 5 - 1, j)
				self:CombineItems(list[2], list[3], 5 - 2, j)
				self:TransItem(list[4], 5 - 3, j)
			elseif list[3].item._user_data == list[4].item._user_data then
				self:TransItem(list[1], 5 - 1, j)
				self:TransItem(list[2], 5 - 2, j)
				self:CombineItems(list[3], list[4], 5 - 3, j)
			end
		end
		j = j+(1)
	end
end

function G2048.GCenter:BornItem(number, row, col, delay_time, anti)
	local target = self["_tile" .. row .. col]
	local ui_name = "item_" .. number
	local item = G2048.g_Control:CreateControl(ui_name, nil, nil)
	self._data_map[row][col] = item
	item._user_data = number
	self._tile_container:AddChild(item, nil)
	local target_x = target.x
	local target_y = target.y
	local target_width = target.width
	local target_height = target.height
	if anti == true then
		item.width = 0
		item.height = 0
		item.x = target_x + target_width / 2
		item.y = target_y + target_height / 2
		item.visible = false
		local loop = ALittle.LoopAttribute(item, "visible", true, delay_time)
		self._loop_group[loop] = loop
		A_LoopSystem:AddUpdater(loop)
		loop = ALittle.LoopLinear(item, "x", target_x, 100, delay_time, nil)
		self._loop_group[loop] = loop
		A_LoopSystem:AddUpdater(loop)
		loop = ALittle.LoopLinear(item, "y", target_y, 100, delay_time, nil)
		self._loop_group[loop] = loop
		A_LoopSystem:AddUpdater(loop)
		loop = ALittle.LoopLinear(item, "width", target_width, 100, delay_time, nil)
		self._loop_group[loop] = loop
		A_LoopSystem:AddUpdater(loop)
		loop = ALittle.LoopLinear(item, "height", target_height, 100, delay_time, nil)
		self._loop_group[loop] = loop
		A_LoopSystem:AddUpdater(loop)
	else
		item.width = target_width
		item.height = target_height
		item.x = target_x
		item.y = target_y
		item.visible = false
		local loop = ALittle.LoopAttribute(item, "visible", true, delay_time)
		self._loop_group[loop] = loop
		A_LoopSystem:AddUpdater(loop)
	end
end

function G2048.GCenter:TransItem(item_info, to_row, to_col)
	local target = self["_tile" .. to_row .. to_col]
	local target_x = target.x
	local target_y = target.y
	if item_info.col ~= to_col then
		local loop = ALittle.LoopLinear(item_info.item, "x", target_x, 200, 0, nil)
		self._loop_group[loop] = loop
		A_LoopSystem:AddUpdater(loop)
		self._item_moved = true
	end
	if item_info.row ~= to_row then
		local loop = ALittle.LoopLinear(item_info.item, "y", target_y, 200, 0, nil)
		self._loop_group[loop] = loop
		A_LoopSystem:AddUpdater(loop)
		self._item_moved = true
	end
	self._data_map[item_info.row][item_info.col] = nil
	self._data_map[to_row][to_col] = item_info.item
	if self._loop_delay < 200 then
		self._loop_delay = 200
	end
end

function G2048.GCenter:CombineItems(item1_info, item2_info, to_row, to_col)
	self:TransAndRemoveItem(item1_info.item, item1_info.row, item1_info.col, to_row, to_col)
	self:TransAndRemoveItem(item2_info.item, item2_info.row, item2_info.col, to_row, to_col)
	self:BornItem(item1_info.item._user_data * 2, to_row, to_col, 200, false)
	self._score_text._user_data = self._score_text._user_data + item1_info.item._user_data * 2
	self._score_text.text = self._score_text._user_data
	self._item_moved = true
	if self._loop_delay < 300 then
		self._loop_delay = 300
	end
end

function G2048.GCenter:TransAndRemoveItem(item, from_row, from_col, to_row, to_col)
	local target = self["_tile" .. to_row .. to_col]
	local target_x = target.x
	local target_y = target.y
	if from_col ~= to_col then
		local loop = ALittle.LoopLinear(item, "x", target_x, 200, 0, nil)
		self._loop_group[loop] = loop
		A_LoopSystem:AddUpdater(loop)
	end
	if from_row ~= to_row then
		local loop = ALittle.LoopLinear(item, "y", target_y, 200, 0, nil)
		self._loop_group[loop] = loop
		A_LoopSystem:AddUpdater(loop)
	end
	local loop = ALittle.LoopTimer(Lua.Bind(self.EraseItem, self, item), 200)
	self._loop_group[loop] = loop
	A_LoopSystem:AddUpdater(loop)
	self._data_map[from_row][from_col] = nil
end

function G2048.GCenter:EraseItem(item)
	self._tile_container:RemoveChild(item)
end

function G2048.GCenter:HandleKeyDown(event)
	self:ClearAnti()
	self._item_moved = false
	self._loop_delay = 0
	if event.sym == 1073741904 then
		self:CalcLeft()
	elseif event.sym == 1073741903 then
		self:CalcRight()
	elseif event.sym == 1073741906 then
		self:CalcUp()
	elseif event.sym == 1073741905 then
		self:CalcDown()
	end
	if self:CheckGameOver() then
		return
	end
	if self._item_moved == false then
		return
	end
	self:GenerateItem(self._loop_delay)
	if self:CheckGameOver() then
		return
	end
end

function G2048.GCenter:HandleDragBegin(event)
	self._drag_total_x = 0
	self._drag_total_y = 0
end

function G2048.GCenter:HandleDrag(event)
	self._drag_total_x = self._drag_total_x + event.delta_x
	self._drag_total_y = self._drag_total_y + event.delta_y
end

function G2048.GCenter:HandleDragEnd(event)
	self:ClearAnti()
	self._item_moved = false
	self._loop_delay = 0
	if ALittle.Math_Abs(self._drag_total_x) > ALittle.Math_Abs(self._drag_total_y) then
		if self._drag_total_x < 0 then
			self:CalcLeft()
		else
			self:CalcRight()
		end
	else
		if self._drag_total_y < 0 then
			self:CalcUp()
		else
			self:CalcDown()
		end
	end
	if self:CheckGameOver() then
		return
	end
	if self._item_moved == false then
		return
	end
	self:GenerateItem(self._loop_delay)
	if self:CheckGameOver() then
		return
	end
end

function G2048.GCenter:CheckGameOver()
	local i = 1
	while true do
		if not(i <= 4) then break end
		local j = 1
		while true do
			if not(j <= 4) then break end
			local item = self._data_map[i][j]
			if item ~= nil and item._user_data == 2048 then
				self:ShowMainMenu("Victory", false)
				if self._max_score_text._user_data < self._score_text._user_data then
					self._max_score_text._user_data = self._score_text._user_data
					self._max_score_text.text = self._max_score_text._user_data
					G2048.g_GConfig:SetConfig("max_score", self._max_score_text._user_data, nil)
				end
				return true
			end
			j = j+(1)
		end
		i = i+(1)
	end
	local i = 1
	while true do
		if not(i <= 4) then break end
		local j = 1
		while true do
			if not(j <= 4) then break end
			local item = self._data_map[i][j]
			if item == nil then
				return false
			end
			if j > 1 and (self._data_map[i][j - 1] == nil or self._data_map[i][j - 1]._user_data == item._user_data) then
				return false
			end
			if j < 4 and (self._data_map[i][j + 1] == nil or self._data_map[i][j + 1]._user_data == item._user_data) then
				return false
			end
			if i > 1 and (self._data_map[i - 1][j] == nil or self._data_map[i - 1][j]._user_data == item._user_data) then
				return false
			end
			if i < 4 and (self._data_map[i + 1][j] == nil or self._data_map[i + 1][j]._user_data == item._user_data) then
				return false
			end
			j = j+(1)
		end
		i = i+(1)
	end
	self:ShowMainMenu("GameOver", false)
	return true
end

function G2048.GCenter:HandleRestartClick(event)
	self:Restart()
end

function G2048.GCenter:HandleBackClick(event)
	self._main_menu.visible = false
end

function G2048.GCenter:HandleMenuClick(event)
	self:ShowMainMenu("", true)
end

function G2048.GCenter:Shutdown()
end

G2048.g_GCenter = G2048.GCenter()
end