-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


local __ceil = ALittle.Math_Ceil
assert(ALittle.DisplayGroup, " extends class:ALittle.DisplayGroup is nil")
ALittle.TileTable = Lua.Class(ALittle.DisplayGroup, "ALittle.TileTable")

function ALittle.TileTable:Ctor(ctrl_sys)
	___rawset(self, "_x_gap", 0)
	___rawset(self, "_y_gap", 0)
	___rawset(self, "_x_start_gap", 0)
	___rawset(self, "_y_start_gap", 0)
	___rawset(self, "_col_count", 1)
	___rawset(self, "_clip_left_index", 0)
	___rawset(self, "_clip_right_index", 0)
	___rawset(self, "_clip_top_index", 0)
	___rawset(self, "_clip_bottom_index", 0)
	___rawset(self, "_show_child_map", ALittle.CreateKeyWeakMap())
	___rawset(self, "_pickup_rect", false)
	___rawset(self, "_pickup_child", true)
	___rawset(self, "_width", 0)
	___rawset(self, "_height", 0)
end

function ALittle.TileTable.__getter:width()
	return self._width
end

function ALittle.TileTable.__getter:height()
	return self._height
end

function ALittle.TileTable.__setter:x_start_gap(value)
	if self._x_start_gap == value then
		return
	end
	self._x_start_gap = value
	self:Layout(1)
end

function ALittle.TileTable.__getter:x_start_gap()
	return self._x_start_gap
end

function ALittle.TileTable.__setter:y_start_gap(value)
	if self._y_start_gap == value then
		return
	end
	self._y_start_gap = value
	self:Layout(1)
end

function ALittle.TileTable.__getter:y_start_gap()
	return self._y_start_gap
end

function ALittle.TileTable.__setter:x_gap(value)
	if self._x_gap == value then
		return
	end
	self._x_gap = value
	self:Layout(1)
end

function ALittle.TileTable.__getter:x_gap()
	return self._x_gap
end

function ALittle.TileTable.__setter:y_gap(value)
	if self._y_gap == value then
		return
	end
	self._y_gap = value
	self:Layout(1)
end

function ALittle.TileTable.__getter:y_gap()
	return self._y_gap
end

function ALittle.TileTable.__setter:col_count(value)
	if value <= 0 or self._col_count == value then
		return
	end
	self._col_count = value
	self:Layout(1)
end

function ALittle.TileTable.__getter:col_count()
	return self._col_count
end

function ALittle.TileTable:AddChild(child, index)
	local result = ALittle.DisplayGroup.AddChild(self, child, index)
	if result == false then
		return false
	end
	if index == nil then
		self:Layout(self.child_count)
	else
		self:Layout(index)
	end
	child:AddEventListener(___all_struct[-431205740], self, self.HandleChildResize)
	return true
end

function ALittle.TileTable:RemoveChild(child)
	local child_index = self:GetChildIndex(child)
	if child_index == 0 then
		return false
	end
	local result = ALittle.DisplayGroup.RemoveChild(self, child)
	if result == false then
		return false
	end
	self._show_child_map[child] = nil
	child:RemoveEventListener(___all_struct[-431205740], self)
	self:Layout(child_index)
	return true
end

function ALittle.TileTable:SpliceChild(index, count)
	local remain_count = self._child_count - index + 1
	if count == nil then
		count = remain_count
	elseif count > remain_count then
		count = remain_count
	end
	if count <= 0 then
		return 0
	end
	local endv = index + count
	local i = index
	while true do
		if not(i < endv) then break end
		local child = self._childs[i]
		if child == nil then
			break
		end
		self._show_child_map[child] = nil
		child:RemoveEventListener(___all_struct[-431205740], self)
		i = i+(1)
	end
	local result = ALittle.DisplayGroup.SpliceChild(self, index, count)
	if result ~= 0 then
		self:Layout(index)
	end
	return result
end

function ALittle.TileTable:RemoveAllChild()
	for k, child in ___ipairs(self._childs) do
		child:RemoveEventListener(___all_struct[-431205740], self)
	end
	self._show_child_map = ALittle.CreateKeyWeakMap()
	self._clip_left_index = 0
	self._clip_right_index = 0
	self._clip_top_index = 0
	self._clip_bottom_index = 0
	ALittle.DisplayGroup.RemoveAllChild(self)
end

function ALittle.TileTable:SetChildIndex(child, index)
	local result = ALittle.DisplayGroup.SetChildIndex(self, child, index)
	self:Layout(1)
	return result
end

function ALittle.TileTable:Layout(index)
	local child_count = self.child_count
	if child_count == 0 then
		self._width = 0
		self._height = 0
		return
	end
	if index > child_count then
		index = child_count
	end
	local child_list = self.childs
	local start_index = 1
	local start_x = self._x_start_gap
	local start_y = self._y_start_gap
	if index > 1 then
		start_index = index
		local current_child = child_list[index - 1]
		if (index - 1) % self._col_count == 0 then
			start_x = self._x_start_gap
			start_y = current_child.y + current_child.height + self._y_gap
		else
			start_x = current_child.x + current_child.width + self._x_gap
			start_y = current_child.y
		end
	end
	local i = start_index
	while true do
		if not(i <= child_count) then break end
		child_list[i].x = start_x
		child_list[i].y = start_y
		if i % self._col_count == 0 then
			start_x = self._x_start_gap
			start_y = start_y + child_list[i].height + self._y_gap
		else
			start_x = start_x + child_list[i].width + self._x_gap
		end
		i = i+(1)
	end
	self._width = 0
	self._height = 0
	for k, child in ___ipairs(child_list) do
		local width = child.x + child.width + self._x_start_gap
		if width > self._width then
			self._width = width
		end
		local height = child.y + child.height + self._y_start_gap
		if height > self._height then
			self._height = height
		end
	end
end

function ALittle.TileTable:HandleChildResize(event)
	self:Layout(self:GetChildIndex(event.target))
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ALittle.TileTable:ClipRect(left, top, right, bottom, h_move, v_move)
	left = left - self._x
	if left < 0 then
		left = 0
	end
	top = top - self._y
	if top < 0 then
		top = 0
	end
	right = right - self._x
	if right > self.width then
		right = self.width
	end
	bottom = bottom - self._y
	if bottom > self.height then
		bottom = self.height
	end
	if left >= right or top >= bottom then
		self.clip = true
		return
	end
	self.clip = false
	local child_count = self.child_count
	if child_count == 0 then
		return
	end
	local childs = self.childs
	local new_show_map = ALittle.CreateKeyWeakMap()
	self._show:RemoveAllChild()
	local max_index = self._col_count
	if self._child_count < max_index then
		max_index = self._child_count
	end
	local min_index = 1
	local index = min_index
	if h_move == nil or self._clip_left_index == 0 then
		repeat
			if childs[index].x > left then
				max_index = index
				index = __ceil((max_index + min_index) / 2)
			elseif childs[index].x + childs[index].width < left then
				min_index = index
				index = __ceil((max_index + min_index) / 2)
			else
				break
			end
		until not(index ~= min_index and index ~= max_index)
	else
		index = self._clip_left_index
		if h_move < 0 then
			while index < max_index do
				if childs[index].x + childs[index].width >= left then
					break
				end
				index = index + 1
			end
		elseif h_move > 0 then
			while index > min_index do
				if childs[index].x <= left then
					break
				end
				index = index - 1
			end
		end
	end
	self._clip_left_index = index
	max_index = self._col_count
	if self._child_count < max_index then
		max_index = self._child_count
	end
	local i = index
	while true do
		if not(i <= max_index) then break end
		if childs[i].x < right then
			self._clip_right_index = i
		else
			break
		end
		i = i+(1)
	end
	max_index = __ceil(self._child_count / self._col_count)
	min_index = 1
	index = min_index
	if v_move == nil or self._clip_top_index == 0 then
		repeat
			local child_index = self._col_count * (index - 1) + 1
			if childs[child_index].y > top then
				max_index = index
				index = __ceil((max_index + min_index) / 2)
			elseif childs[child_index].y + childs[child_index].height < top then
				min_index = index
				index = __ceil((max_index + min_index) / 2)
			else
				break
			end
		until not(index ~= min_index and index ~= max_index)
	else
		index = self._clip_top_index
		if v_move < 0 then
			while index < max_index do
				local child_index = self._col_count * (index - 1) + 1
				if childs[child_index].y + childs[child_index].height >= top then
					break
				end
				index = index + 1
			end
		elseif v_move > 0 then
			while index > min_index do
				local child_index = self._col_count * (index - 1) + 1
				if childs[child_index].y <= top then
					break
				end
				index = index - 1
			end
		end
	end
	self._clip_top_index = index
	max_index = __ceil(self._child_count / self._col_count)
	local child_index = self._col_count * (index - 1) + 1
	local i = index
	while true do
		if not(i <= max_index) then break end
		if childs[child_index].y < bottom then
			self._clip_bottom_index = i
		else
			break
		end
		child_index = child_index + (self._col_count)
		i = i+(1)
	end
	local base_index = self._col_count * (self._clip_top_index - 1)
	local i = self._clip_top_index
	while true do
		if not(i <= self._clip_bottom_index) then break end
		local j = self._clip_left_index
		while true do
			if not(j <= self._clip_right_index) then break end
			local child = childs[base_index + j]
			if child ~= nil then
				self._show:AddChild(child._show)
				new_show_map[child] = true
				if child.ClipRect ~= nil then
					child:ClipRect(left, top, right, bottom, h_move, v_move)
				end
			end
			j = j+(1)
		end
		base_index = base_index + (self._col_count)
		i = i+(1)
	end
	for child, v in ___pairs(new_show_map) do
		if self._show_child_map[child] == nil then
			local e = {}
			e.target = child
			child:DispatchEvent(___all_struct[1862557463], e)
		else
			self._show_child_map[child] = nil
		end
	end
	for child, v in ___pairs(self._show_child_map) do
		local e = {}
		e.target = child
		child:DispatchEvent(___all_struct[348388800], e)
	end
	self._show_child_map = new_show_map
end

end