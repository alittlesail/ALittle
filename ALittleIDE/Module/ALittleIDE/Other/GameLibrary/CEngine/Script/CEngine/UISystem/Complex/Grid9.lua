-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __ceil = ALittle.Math_Ceil
assert(ALittle.DisplayGroup, " extends class:ALittle.DisplayGroup is nil")
ALittle.Grid9 = Lua.Class(ALittle.DisplayGroup, "ALittle.Grid9")

function ALittle.Grid9:Ctor(ctrl_sys)
	___rawset(self, "_child_map", {})
	self._child_map[1] = {}
	self._child_map[2] = {}
	self._child_map[3] = {}
	___rawset(self, "_logic_left", 0)
	___rawset(self, "_logic_top", 0)
	___rawset(self, "_logic_right", 0)
	___rawset(self, "_logic_bottom", 0)
	___rawset(self, "_real_left", 0)
	___rawset(self, "_real_top", 0)
	___rawset(self, "_real_right", 0)
	___rawset(self, "_real_bottom", 0)
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", true)
end

function ALittle.Grid9.__setter:show_left_top(child)
	self:SetShow(1, 1, child)
end

function ALittle.Grid9.__getter:show_left_top()
	return self._child_map[1][1]
end

function ALittle.Grid9.__setter:show_left_center(child)
	self:SetShow(1, 2, child)
end

function ALittle.Grid9.__getter:show_left_center()
	return self._child_map[1][2]
end

function ALittle.Grid9.__setter:show_left_bottom(child)
	self:SetShow(1, 3, child)
end

function ALittle.Grid9.__getter:show_left_bottom()
	return self._child_map[1][3]
end

function ALittle.Grid9.__setter:show_center_top(child)
	self:SetShow(2, 1, child)
end

function ALittle.Grid9.__getter:show_center_top()
	return self._child_map[2][1]
end

function ALittle.Grid9.__setter:show_center_center(child)
	self:SetShow(2, 2, child)
end

function ALittle.Grid9.__getter:show_center_center()
	return self._child_map[2][2]
end

function ALittle.Grid9.__setter:show_center_bottom(child)
	self:SetShow(2, 3, child)
end

function ALittle.Grid9.__getter:show_center_bottom()
	return self._child_map[2][3]
end

function ALittle.Grid9.__setter:show_right_top(child)
	self:SetShow(3, 1, child)
end

function ALittle.Grid9.__getter:show_right_top()
	return self._child_map[3][1]
end

function ALittle.Grid9.__setter:show_right_center(child)
	self:SetShow(3, 2, child)
end

function ALittle.Grid9.__getter:show_right_center()
	return self._child_map[3][2]
end

function ALittle.Grid9.__setter:show_right_bottom(child)
	self:SetShow(3, 3, child)
end

function ALittle.Grid9.__getter:show_right_bottom()
	return self._child_map[3][3]
end

function ALittle.Grid9:SetShow(col, row, child)
	if self._child_map[col][row] ~= nil then
		self:RemoveChild(self._child_map[col][row])
	end
	self._child_map[col][row] = child
	if child == nil then
		return
	end
	self:AddChild(child)
	local x = 0.0
	local y = 0.0
	local width = 0.0
	local height = 0.0
	if col == 1 then
		x = 0
		width = self._real_left
	elseif col == 2 then
		x = self._real_left
		width = self._width - self._real_left - self._real_right
	elseif col == 3 then
		x = self._width - self._real_right
		width = self._real_right
	end
	if row == 1 then
		y = 0
		height = self._real_top
	elseif row == 2 then
		y = self._real_top
		height = self._height - self._real_top - self._real_bottom
	elseif row == 3 then
		y = self._height - self._real_bottom
		height = self._real_bottom
	end
	child.x = x
	child.y = y
	child.width = width
	child.height = height
end

function ALittle.Grid9.__setter:width(value)
	if value == self._width then
		return
	end
	self._width = value
	if self._width_type == 1 then
		self._width_value = self._width
	end
	self:CalcRealWidthCutting()
end

function ALittle.Grid9.__setter:height(value)
	if value == self._height then
		return
	end
	self._height = value
	if self._height_type == 1 then
		self._height_value = self._height
	end
	self:CalcRealHeightCutting()
end

function ALittle.Grid9.__setter:left_size(value)
	self._logic_left = value
	self:CalcRealWidthCutting()
end

function ALittle.Grid9.__getter:left_size()
	return self._logic_left
end

function ALittle.Grid9.__setter:right_size(value)
	self._logic_right = value
	self:CalcRealWidthCutting()
end

function ALittle.Grid9.__getter:right_size()
	return self._logic_right
end

function ALittle.Grid9.__setter:top_size(value)
	self._logic_top = value
	self:CalcRealHeightCutting()
end

function ALittle.Grid9.__getter:top_size()
	return self._logic_top
end

function ALittle.Grid9.__setter:bottom_size(value)
	self._logic_bottom = value
	self:CalcRealHeightCutting()
end

function ALittle.Grid9.__getter:bottom_size()
	return self._logic_bottom
end

function ALittle.Grid9:CalcRealWidthCutting()
	local real_center = 0.0
	local logic_left = __ceil(self._logic_left)
	local logic_right = __ceil(self._logic_right)
	if self._width == 0 then
		self._real_left = 0
		self._real_right = 0
		real_center = 0
	elseif self._width >= logic_left + logic_right then
		self._real_left = logic_left
		self._real_right = logic_right
		real_center = __ceil(self._width - self._real_left - self._real_right)
	else
		local logic_left_add_right = self._logic_left + self._logic_right
		real_center = 0
		if logic_left_add_right == 0 then
			self._real_left = 0
			self._real_right = 0
		else
			local rate_left = self._logic_left / logic_left_add_right
			local rate_right = self._logic_right / logic_left_add_right
			self._real_left = self._width * rate_left
			self._real_right = self._width * rate_right
		end
	end
	local offset_list = {}
	offset_list[1] = 0
	offset_list[2] = self._real_left
	offset_list[3] = self._real_left + real_center
	local width_list = {}
	width_list[1] = self._real_left
	width_list[2] = real_center
	width_list[3] = self._real_right
	local col = 1
	while true do
		if not(col <= 3) then break end
		local row_childs = self._child_map[col]
		local row = 1
		while true do
			if not(row <= 3) then break end
			if row_childs[row] ~= nil then
				row_childs[row].x = offset_list[col]
				row_childs[row].width = width_list[col]
			end
			row = row+(1)
		end
		col = col+(1)
	end
end

function ALittle.Grid9:CalcRealHeightCutting()
	local real_center = 0.0
	local logic_top = __ceil(self._logic_top)
	local logic_bottom = __ceil(self._logic_bottom)
	if self._height == 0 then
		self._real_top = 0
		self._real_bottom = 0
		real_center = 0
	elseif self._height >= logic_top + logic_bottom then
		self._real_top = logic_top
		self._real_bottom = logic_bottom
		real_center = __ceil(self._height - self._real_top - self._real_bottom)
	else
		local logic_top_add_bottom = self._logic_top + self._logic_bottom
		real_center = 0
		if logic_top_add_bottom == 0 then
			self._real_top = 0
			self._real_bottom = 0
		else
			local rate_top = self._logic_top / logic_top_add_bottom
			local rate_bottom = self._logic_bottom / logic_top_add_bottom
			self._real_top = self._height * rate_top
			self._real_bottom = self._height * rate_bottom
		end
	end
	local offset_list = {}
	offset_list[1] = 0
	offset_list[2] = self._real_top
	offset_list[3] = self._real_top + real_center
	local height_list = {}
	height_list[1] = self._real_top
	height_list[2] = real_center
	height_list[3] = self._real_bottom
	local col = 1
	while true do
		if not(col <= 3) then break end
		local row_childs = self._child_map[col]
		local row = 1
		while true do
			if not(row <= 3) then break end
			if row_childs[row] ~= nil then
				row_childs[row].y = offset_list[row]
				row_childs[row].height = height_list[row]
			end
			row = row+(1)
		end
		col = col+(1)
	end
end

end