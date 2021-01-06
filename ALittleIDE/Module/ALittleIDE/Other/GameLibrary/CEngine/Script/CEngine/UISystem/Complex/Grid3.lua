-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayGroup, " extends class:ALittle.DisplayGroup is nil")
ALittle.Grid3 = Lua.Class(ALittle.DisplayGroup, "ALittle.Grid3")

function ALittle.Grid3:Ctor(ctrl_sys)
	___rawset(self, "_type", 2)
	___rawset(self, "_child_map", {})
	___rawset(self, "_logic_up", 0)
	___rawset(self, "_logic_down", 0)
	___rawset(self, "_logic_gap", 0)
	___rawset(self, "_real_up", 0)
	___rawset(self, "_real_down", 0)
	___rawset(self, "_real_gap", 0)
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", true)
end

function ALittle.Grid3.__setter:type(value)
	if self._type == value then
		return
	end
	self._type = value
	self:CalcRealWidthCutting()
	self:CalcRealHeightCutting()
end

function ALittle.Grid3.__getter:type()
	return self._type
end

function ALittle.Grid3.__setter:show_up(child)
	self:SetShow(1, child)
end

function ALittle.Grid3.__getter:show_up()
	return self._child_map[1]
end

function ALittle.Grid3.__setter:show_center(child)
	self:SetShow(2, child)
end

function ALittle.Grid3.__getter:show_center()
	return self._child_map[2]
end

function ALittle.Grid3.__setter:show_down(child)
	self:SetShow(3, child)
end

function ALittle.Grid3.__getter:show_down()
	return self._child_map[3]
end

function ALittle.Grid3:SetShow(index, child)
	if self._child_map[index] ~= nil then
		ALittle.DisplayGroup.RemoveChild(self, self._child_map[index])
	end
	self._child_map[index] = nil
	if child == nil then
		return
	end
	self._child_map[index] = child
	ALittle.DisplayGroup.AddChild(self, child)
	if self._type == 2 then
		child.x = 0
		child.width = self._width
		local y = 0.0
		local height = 0.0
		if index == 1 then
			y = 0
			height = self._real_up
		elseif index == 2 then
			y = self._real_up + self._real_gap
			height = self._height - self._real_gap * 2 - self._real_up - self._real_down
		elseif index == 3 then
			y = self._height - self._real_down
			height = self._real_down
		end
		child.y = y
		child.height = height
	else
		child.y = 0
		child.height = self._height
		local x = 0.0
		local width = 0.0
		if index == 1 then
			x = 0
			width = self._real_up
		elseif index == 2 then
			x = self._real_up + self._real_gap
			width = self._width - self._real_gap * 2 - self._real_up - self._real_down
		elseif index == 3 then
			x = self._width - self._real_down
			width = self._real_down
		end
		child.x = x
		child.width = width
	end
end

function ALittle.Grid3.__getter:center_size()
	local size = 0.0
	if self._type == 2 then
		size = self._height - self._real_gap * 2 - self._real_up - self._real_down
	else
		size = self._width - self._real_gap * 2 - self._real_up - self._real_down
	end
	return size
end

function ALittle.Grid3.__getter:real_gap()
	return self._real_gap
end

function ALittle.Grid3.__getter:gap()
	return self._logic_gap
end

function ALittle.Grid3.__getter:real_up_size()
	return self._real_up
end

function ALittle.Grid3.__getter:up_size()
	return self._logic_up
end

function ALittle.Grid3.__getter:real_down_size()
	return self._real_down
end

function ALittle.Grid3.__getter:down_size()
	return self._logic_down
end

function ALittle.Grid3.__setter:up_size(value)
	self._logic_up = value
	self:CalcRealWidthCutting()
	self:CalcRealHeightCutting()
end

function ALittle.Grid3.__setter:down_size(value)
	self._logic_down = value
	self:CalcRealWidthCutting()
	self:CalcRealHeightCutting()
end

function ALittle.Grid3.__setter:gap(value)
	self._logic_gap = value
	self:CalcRealWidthCutting()
	self:CalcRealHeightCutting()
end

function ALittle.Grid3.__setter:width(value)
	if value == self._width then
		return
	end
	self._width = value
	if self._width_type == 1 then
		self._width_value = self._width
	end
	self:CalcRealWidthCutting()
end

function ALittle.Grid3.__setter:height(value)
	if value == self._height then
		return
	end
	self._height = value
	if self._height_type == 1 then
		self._height_value = self._height
	end
	self:CalcRealHeightCutting()
end

function ALittle.Grid3:CalcRealWidthCutting()
	if self._type == 2 then
		local index = 1
		while true do
			if not(index <= 3) then break end
			if self._child_map[index] ~= nil then
				self._child_map[index].x = 0
				self._child_map[index].width = self._width
			end
			index = index+(1)
		end
		return
	end
	if self._width == 0 then
		self._real_up = 0
		self._real_down = 0
		self._real_gap = 0
	elseif self._width >= self._logic_up + self._logic_down + self._logic_gap * 2 then
		self._real_up = self._logic_up
		self._real_down = self._logic_down
		self._real_gap = self._logic_gap
	elseif self._width >= self._logic_up + self._logic_down then
		local last_gap = self._width - self._logic_up - self._logic_down
		self._real_up = self._logic_up
		self._real_down = self._logic_down
		self._real_gap = last_gap / 2
	else
		local logic_up_add_down = self._logic_up + self._logic_down
		if logic_up_add_down == 0 then
			self._real_up = 0
			self._real_down = 0
			self._real_gap = 0
		else
			local rate_up = self._logic_up / logic_up_add_down
			local rate_down = self._logic_down / logic_up_add_down
			self._real_up = self._width * rate_up
			self._real_down = self._width * rate_down
			self._real_gap = 0
		end
	end
	local offset_list = {}
	offset_list[1] = 0
	offset_list[2] = self._real_up + self._real_gap
	offset_list[3] = self._width - self._real_down
	local width_list = {}
	width_list[1] = self._real_up
	width_list[2] = self._width - self._real_gap * 2 - self._real_up - self._real_down
	width_list[3] = self._real_down
	local index = 1
	while true do
		if not(index <= 3) then break end
		if self._child_map[index] ~= nil then
			self._child_map[index].x = offset_list[index]
			self._child_map[index].width = width_list[index]
		end
		index = index+(1)
	end
end

function ALittle.Grid3:CalcRealHeightCutting()
	if self._type == 1 then
		local index = 1
		while true do
			if not(index <= 3) then break end
			if self._child_map[index] ~= nil then
				self._child_map[index].y = 0
				self._child_map[index].height = self._height
			end
			index = index+(1)
		end
		return
	end
	if self._height == 0 then
		self._real_up = 0
		self._real_down = 0
		self._real_gap = 0
	elseif self._height >= self._logic_up + self._logic_down + self._logic_gap * 2 then
		self._real_up = self._logic_up
		self._real_down = self._logic_down
		self._real_gap = self._logic_gap
	elseif self._height >= self._logic_up + self._logic_down then
		local last_gap = self._height - self._logic_up - self._logic_down
		self._real_up = self._logic_up
		self._real_down = self._logic_down
		self._real_gap = last_gap / 2
	else
		local logic_up_add_down = self._logic_up + self._logic_down
		if logic_up_add_down == 0 then
			self._real_up = 0
			self._real_down = 0
			self._real_gap = 0
		else
			local rate_up = self._logic_up / logic_up_add_down
			local rate_down = self._logic_down / logic_up_add_down
			self._real_up = self._height * rate_up
			self._real_down = self._height * rate_down
			self._real_gap = 0
		end
	end
	local offset_list = {}
	offset_list[1] = 0
	offset_list[2] = self._real_up + self._real_gap
	offset_list[3] = self._height - self._real_down
	local height_list = {}
	height_list[1] = self._real_up
	height_list[2] = self._height - self._real_gap * 2 - self._real_up - self._real_down
	height_list[3] = self._real_down
	local index = 1
	while true do
		if not(index <= 3) then break end
		if self._child_map[index] ~= nil then
			self._child_map[index].y = offset_list[index]
			self._child_map[index].height = height_list[index]
		end
		index = index+(1)
	end
end

end