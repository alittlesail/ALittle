-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayGroup, " extends class:ALittle.DisplayGroup is nil")
ALittle.DisplayLayout = Lua.Class(ALittle.DisplayGroup, "ALittle.DisplayLayout")

function ALittle.DisplayLayout:Ctor(ctrl_sys)
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", true)
end

function ALittle.DisplayLayout.__setter:width(value)
	if value == self._width then
		return
	end
	self._width = value
	if self._width_type == 1 then
		self._width_value = self._width
	end
	for index, child in ___ipairs(self._childs) do
		self:UpdateWidthLayout(child)
		self:UpdateXLayout(child)
	end
	self._show:SetWidth(value)
end

function ALittle.DisplayLayout.__setter:height(value)
	if value == self._height then
		return
	end
	self._height = value
	if self._height_type == 1 then
		self._height_value = self._height
	end
	for index, child in ___ipairs(self._childs) do
		self:UpdateHeightLayout(child)
		self:UpdateYLayout(child)
	end
	self._show:SetHeight(value)
end

function ALittle.DisplayLayout:UpdateXLayout(child)
	if child == nil or child._show_parent ~= self then
		return
	end
	local x_type = child._x_type
	if x_type == 1 then
		child.x = child._x_value
	elseif x_type == 2 then
		child.x = child._x_value
	elseif x_type == 3 then
		child.x = (self._width - child.width) / 2 + child._x_value
	elseif x_type == 4 then
		child.x = self._width - child.width - child._x_value
	elseif x_type == 7 then
		child.x = self._width * child._x_value
	elseif x_type == 8 then
		child.x = (self._width - child.width) / 2 + self._width * child._x_value
	elseif x_type == 9 then
		child.x = (self._width - child.width) * (1 - child._x_value)
	end
end

function ALittle.DisplayLayout:UpdateYLayout(child)
	if child == nil or child._show_parent ~= self then
		return
	end
	local y_type = child._y_type
	if y_type == 1 then
		child.y = child._y_value
	elseif y_type == 2 then
		child.y = child._y_value
	elseif y_type == 3 then
		child.y = (self._height - child.height) / 2 + child._y_value
	elseif y_type == 4 then
		child.y = self._height - child.height - child._y_value
	elseif y_type == 7 then
		child.y = self._height * child._y_value
	elseif y_type == 8 then
		child.y = (self._height - child.height) / 2 + self._height * child._y_value
	elseif y_type == 9 then
		child.y = (self._height - child.height) * (1 - child._y_value)
	end
end

function ALittle.DisplayLayout:UpdateWidthLayout(child)
	if child == nil or child._show_parent ~= self then
		return
	end
	local width_type = child._width_type
	if width_type == 2 then
		local real_width = self._width * child._width_value
		if real_width < 0 then
			real_width = 0
		end
		child.width = real_width
	elseif width_type == 4 then
		local real_width = self._width - child._width_value
		if real_width < 0 then
			real_width = 0
		end
		child.width = real_width
	elseif width_type == 1 then
		local real_width = child._width_value
		if real_width < 0 then
			real_width = 0
		end
		child.width = real_width
	end
end

function ALittle.DisplayLayout:UpdateHeightLayout(child)
	if child == nil or child._show_parent ~= self then
		return
	end
	local height_type = child._height_type
	if height_type == 2 then
		local real_height = self._height * child._height_value
		if real_height < 0 then
			real_height = 0
		end
		child.height = real_height
	elseif height_type == 4 then
		local real_height = self._height - child._height_value
		if real_height < 0 then
			real_height = 0
		end
		child.height = real_height
	elseif height_type == 1 then
		local real_height = child._height_value
		if real_height < 0 then
			real_height = 0
		end
		child.height = real_height
	end
end

function ALittle.DisplayLayout.__getter:max_right()
	return self._width
end

function ALittle.DisplayLayout.__getter:max_bottom()
	return self._height
end

end