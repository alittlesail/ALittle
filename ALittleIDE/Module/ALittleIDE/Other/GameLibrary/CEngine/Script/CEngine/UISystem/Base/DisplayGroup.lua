-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __remove = ALittle.List_Remove
local __insert = ALittle.List_Insert
local __splice = ALittle.List_Splice
local __cos = ALittle.Math_Cos
local __sin = ALittle.Math_Sin
assert(ALittle.DisplayObject, " extends class:ALittle.DisplayObject is nil")
ALittle.DisplayGroup = Lua.Class(ALittle.DisplayObject, "ALittle.DisplayGroup")

function ALittle.DisplayGroup:Ctor(ctrl_sys)
	___rawset(self, "_childs", {})
	___rawset(self, "_child_count", 0)
	___rawset(self, "_show", __CPPAPIDisplayObjects())
	___rawset(self, "_pickup_rect", false)
	___rawset(self, "_pickup_child", true)
	___rawset(self, "_pickup_this", false)
end

function ALittle.DisplayGroup:GetChildIndex(child)
	if child == nil then
		return 0
	end
	if child._show_parent ~= self and child._logic_parent ~= self then
		return 0
	end
	for index, value in ___ipairs(self._childs) do
		if value == child then
			return index
		end
	end
	return 0
end

function ALittle.DisplayGroup:SetChildIndex(child, index)
	local cur_index = self:GetChildIndex(child)
	if cur_index == 0 then
		return false
	end
	if cur_index == index then
		return true
	end
	if index < 1 then
		index = 1
	end
	if index > self._child_count then
		index = self._child_count
	end
	__remove(self._childs, cur_index)
	self._show:RemoveChild(child._show)
	local back_child = self._childs[index]
	if back_child ~= nil then
		self._show:AddChildBefore(back_child._show, child._show)
	else
		self._show:AddChild(child._show)
	end
	__insert(self._childs, index, child)
	return true
end

function ALittle.DisplayGroup:GetChildByIndex(index)
	return self._childs[index]
end

function ALittle.DisplayGroup.__getter:childs()
	return self._childs
end

function ALittle.DisplayGroup.__getter:child_count()
	return self._child_count
end

function ALittle.DisplayGroup:AddChild(child, index)
	if child == nil or child == self then
		return false
	end
	if child._show_parent == self or child._logic_parent == self then
		return true
	end
	if child._logic_parent ~= nil then
		child._logic_parent:RemoveChild(child)
	elseif child._show_parent ~= nil then
		child._show_parent:RemoveChild(child)
	end
	child._show_parent = self
	child._logic_parent = nil
	if index == nil or index > self._child_count or self._child_count < 1 then
		self._child_count = self._child_count + 1
		self._childs[self._child_count] = child
		self._show:AddChild(child._show)
	else
		if index < 1 then
			index = 1
		end
		local back_child = self._childs[index]
		self._show:AddChildBefore(back_child._show, child._show)
		__insert(self._childs, index, child)
		self._child_count = self._child_count + 1
	end
	child.visible = child._visible
	child.alpha = child._alpha
	child.disabled = child._disabled
	child:UpdateLayout()
	return true
end

function ALittle.DisplayGroup:RemoveChild(child)
	if child == nil then
		return false
	end
	if child._show_parent ~= self and child._logic_parent ~= self then
		return false
	end
	for index, value in ___ipairs(self._childs) do
		if value == child then
			__remove(self._childs, index)
			self._show:RemoveChild(child._show)
			child._show_parent = nil
			child._logic_parent = nil
			self._child_count = self._child_count - 1
			return true
		end
	end
	return false
end

function ALittle.DisplayGroup:SpliceChild(index, count)
	local remain_count = self._child_count - index + 1
	if count == nil then
		count = remain_count
	elseif count > remain_count then
		count = remain_count
	end
	if count <= 0 then
		return 0
	end
	local old_count = self._child_count
	local endv = index + count
	local i = index
	while true do
		if not(i < endv) then break end
		local child = self._childs[i]
		if child == nil then
			break
		end
		self._show:RemoveChild(child._show)
		child._show_parent = nil
		child._logic_parent = nil
		self._child_count = self._child_count - 1
		i = i+(1)
	end
	__splice(self._childs, index, count)
	return old_count - self._child_count
end

function ALittle.DisplayGroup:HasChild(child)
	if child == nil then
		return false
	end
	return child._show_parent == self or child._logic_parent == self
end

function ALittle.DisplayGroup:RemoveAllChild()
	for index, value in ___ipairs(self._childs) do
		value._show_parent = nil
		value._logic_parent = nil
	end
	self._show:RemoveAllChild()
	self._childs = {}
	self._child_count = 0
end

function ALittle.DisplayGroup.__setter:alpha(value)
	self._alpha = value
	if self._show_parent ~= nil then
		self._abs_alpha = self._show_parent._abs_alpha * value
	else
		self._abs_alpha = value
	end
	for index, child in ___ipairs(self._childs) do
		child.alpha = child.alpha
	end
end

function ALittle.DisplayGroup.__setter:visible(value)
	self._visible = value
	if self._show_parent ~= nil then
		self._abs_visible = self._show_parent._abs_visible and value
	else
		self._abs_visible = value
	end
	self._show:SetVisible(self._abs_visible)
	for index, child in ___ipairs(self._childs) do
		child.visible = child.visible
	end
end

function ALittle.DisplayGroup.__setter:disabled(value)
	self._disabled = value
	if self._show_parent ~= nil then
		self._abs_disabled = self._show_parent._abs_disabled or value
	else
		self._abs_disabled = value
	end
	for index, child in ___ipairs(self._childs) do
		child.disabled = child.disabled
	end
end

function ALittle.DisplayGroup:PickUp(x, y)
	if self._ignore or self._abs_disabled or self._abs_visible == false then
		return nil, nil, nil
	end
	local xx = x - self._x
	local yy = y - self._y
	if self._angle ~= 0 then
		local rad = 3.1415926 * -self._angle / 180.0
		local cos = __cos(rad)
		local sin = __sin(rad)
		local xxx = xx * cos + yy * -sin
		local yyy = xx * sin + yy * cos
		xx = xxx
		yy = yyy
	end
	if self._scale_x > 0 then
		xx = xx / (self._scale_x)
	end
	if self._scale_y > 0 then
		yy = yy / (self._scale_y)
	end
	local rel_x = xx + self._center_x
	local rel_y = yy + self._center_y
	if self._scale_x <= 0 or self._scale_y <= 0 then
		if self._modal then
			return self, rel_x, rel_y
		end
		return nil, rel_x, rel_y
	end
	if self._pickup_rect and (rel_x < 0 or rel_y < 0 or rel_x >= self._width or rel_y >= self._height) then
		if self._modal then
			return self, rel_x, rel_y
		end
		return nil, rel_x, rel_y
	end
	if self._pickup_child then
		local childs = self._childs
		local index = self._child_count
		while true do
			if not(index >= 1) then break end
			local v_focus, v_x, v_y = childs[index]:PickUp(rel_x, rel_y)
			if v_focus ~= nil then
				return v_focus, v_x, v_y
			end
			index = index+(-1)
		end
	end
	if self._modal or (self._pickup_rect and self._pickup_child == false) or self._pickup_this then
		return self, rel_x, rel_y
	end
	return nil, nil, nil
end

function ALittle.DisplayGroup.__setter:width(value)
	self._show:SetWidth(value)
end

function ALittle.DisplayGroup.__setter:height(value)
	self._show:SetHeight(value)
end

function ALittle.DisplayGroup.__getter:width()
	if self._pickup_rect then
		return self._width
	end
	return self.bound_width
end

function ALittle.DisplayGroup.__getter:height()
	if self._pickup_rect then
		return self._height
	end
	return self.bound_height
end

function ALittle.DisplayGroup.__getter:bound_width()
	local min_x = nil
	local max_x = nil
	for index, value in ___ipairs(self._childs) do
		if min_x == nil or min_x > value._x then
			min_x = value._x
		end
		local width = value.width
		local right = width + value._x
		if max_x == nil or max_x < right then
			max_x = right
		end
	end
	if max_x == nil then
		max_x = 0
	end
	if min_x == nil then
		min_x = 0
	end
	local real_width = max_x - min_x
	if real_width < 0 then
		real_width = 0
	end
	return real_width
end

function ALittle.DisplayGroup.__getter:bound_height()
	local min_y = nil
	local max_y = nil
	for index, value in ___ipairs(self._childs) do
		if min_y == nil or min_y > value._y then
			min_y = value._y
		end
		local height = value.height
		local bottom = height + value._y
		if max_y == nil or max_y < bottom then
			max_y = bottom
		end
	end
	if max_y == nil then
		max_y = 0
	end
	if min_y == nil then
		min_y = 0
	end
	local real_height = max_y - min_y
	if real_height < 0 then
		real_height = 0
	end
	return real_height
end

function ALittle.DisplayGroup.__getter:max_right()
	local max_x = nil
	for index, value in ___ipairs(self._childs) do
		local width = value.width
		local right = width + value.x
		if max_x == nil or max_x < right then
			max_x = right
		end
	end
	if max_x == nil then
		max_x = 0
	end
	return max_x
end

function ALittle.DisplayGroup.__getter:max_bottom()
	local max_y = nil
	for index, value in ___ipairs(self._childs) do
		local height = value.height
		local bottom = height + value.y
		if max_y == nil or max_y < bottom then
			max_y = bottom
		end
	end
	if max_y == nil then
		max_y = 0
	end
	return max_y
end

function ALittle.DisplayGroup:UpdateXLayout(child)
end

function ALittle.DisplayGroup:UpdateYLayout(child)
end

function ALittle.DisplayGroup:UpdateWidthLayout(child)
end

function ALittle.DisplayGroup:UpdateHeightLayout(child)
end

end