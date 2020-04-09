
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayGroup, " extends class:ALittle.DisplayGroup is nil")
DisplayLayout = Lua.Class(ALittle.DisplayGroup, "ALittle.DisplayLayout")

function DisplayLayout:Ctor(ctrl_sys)
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", true)
end

function DisplayLayout.__setter:width(value)
	if value == self._width then
		return
	end
	self._width = value
	if self._width_type == UIEnumTypes.SIZE_ABS then
		self._width_value = self._width
	end
	for index, value in ___ipairs(self._childs) do
		self:UpdateWidthLayout(value)
		self:UpdateXLayout(value)
	end
	self._show:SetWidth(value)
end

function DisplayLayout.__setter:height(value)
	if value == self._height then
		return
	end
	self._height = value
	if self._height_type == UIEnumTypes.SIZE_ABS then
		self._height_value = self._height
	end
	for index, value in ___ipairs(self._childs) do
		self:UpdateHeightLayout(value)
		self:UpdateYLayout(value)
	end
	self._show:SetHeight(value)
end

function DisplayLayout:UpdateXLayout(child)
	if child == nil or child._show_parent ~= self then
		return
	end
	if child._x_type == UIEnumTypes.POS_ABS then
		child.x = child._x_value
	elseif child._x_type == UIEnumTypes.POS_ALIGN_STARTING then
		child.x = child._x_value
	elseif child._x_type == UIEnumTypes.POS_ALIGN_CENTER then
		child.x = (self._width - child.width) / 2 + child._x_value
	elseif child._x_type == UIEnumTypes.POS_ALIGN_ENDING then
		child.x = self._width - child.width - child._x_value
	elseif child._x_type == UIEnumTypes.POS_PERCENT_STARTING then
		child.x = self._width * child._x_value
	elseif child._x_type == UIEnumTypes.POS_PERCENT_CENTER then
		child.x = (self._width - child.width) / 2 + self._width * child._x_value
	elseif child._x_type == UIEnumTypes.POS_PERCENT_ENDING then
		child.x = (self._width - child.width) * (1 - child._x_value)
	end
end

function DisplayLayout:UpdateYLayout(child)
	if child == nil or child._show_parent ~= self then
		return
	end
	if child._y_type == UIEnumTypes.POS_ABS then
		child.y = child._y_value
	elseif child._y_type == UIEnumTypes.POS_ALIGN_STARTING then
		child.y = child._y_value
	elseif child._y_type == UIEnumTypes.POS_ALIGN_CENTER then
		child.y = (self._height - child.height) / 2 + child._y_value
	elseif child._y_type == UIEnumTypes.POS_ALIGN_ENDING then
		child.y = self._height - child.height - child._y_value
	elseif child._y_type == UIEnumTypes.POS_PERCENT_STARTING then
		child.y = self._height * child._y_value
	elseif child._y_type == UIEnumTypes.POS_PERCENT_CENTER then
		child.y = (self._height - child.height) / 2 + self._height * child._y_value
	elseif child._y_type == UIEnumTypes.POS_PERCENT_ENDING then
		child.y = (self._height - child.height) * (1 - child._y_value)
	end
end

function DisplayLayout:UpdateWidthLayout(child)
	if child == nil or child._show_parent ~= self then
		return
	end
	if child._width_type == UIEnumTypes.SIZE_PERCENT then
		local real_width = self._width * child._width_value
		if real_width < 0 then
			real_width = 0
		end
		child.width = real_width
	elseif child._width_type == UIEnumTypes.SIZE_MARGIN then
		local real_width = self._width - child._width_value
		if real_width < 0 then
			real_width = 0
		end
		child.width = real_width
	elseif child._width_type == UIEnumTypes.SIZE_ABS then
		local real_width = child._width_value
		if real_width < 0 then
			real_width = 0
		end
		child.width = real_width
	end
end

function DisplayLayout:UpdateHeightLayout(child)
	if child == nil or child._show_parent ~= self then
		return
	end
	if child._height_type == UIEnumTypes.SIZE_PERCENT then
		local real_height = self._height * child._height_value
		if real_height < 0 then
			real_height = 0
		end
		child.height = real_height
	elseif child._height_type == UIEnumTypes.SIZE_MARGIN then
		local real_height = self._height - child._height_value
		if real_height < 0 then
			real_height = 0
		end
		child.height = real_height
	elseif child._height_type == UIEnumTypes.SIZE_ABS then
		local real_height = child._height_value
		if real_height < 0 then
			real_height = 0
		end
		child.height = real_height
	end
end

function DisplayLayout.__getter:max_right()
	return self._width
end

function DisplayLayout.__getter:max_bottom()
	return self._height
end

