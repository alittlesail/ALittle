
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = GetAllStruct()


local __ceil = Math_Ceil
assert(ALittle.DisplayGroup, " extends class:ALittle.DisplayGroup is nil")
Linear = Lua.Class(ALittle.DisplayGroup, "ALittle.Linear")

function Linear:Ctor(ctrl_sys)
	___rawset(self, "_type", UIEnumTypes.TYPE_H)
	___rawset(self, "_size_fixed", true)
	___rawset(self, "_gap", 0)
	___rawset(self, "_clip_up_index", 0)
	___rawset(self, "_clip_down_index", 0)
	___rawset(self, "_child_width_map", CreateKeyWeakMap())
	___rawset(self, "_child_height_map", CreateKeyWeakMap())
	___rawset(self, "_show_child_map", CreateKeyWeakMap())
	___rawset(self, "_pickup_rect", false)
	___rawset(self, "_pickup_child", true)
end

function Linear.__getter:clip_up_index()
	return self._clip_up_index
end

function Linear.__getter:clip_down_index()
	return self._clip_down_index
end

function Linear.__getter:size_fixed()
	return self._size_fixed
end

function Linear.__setter:size_fixed(value)
	if self._size_fixed == value then
		return
	end
	self._size_fixed = value
	self:UpdateSize()
end

function Linear.__setter:type(value)
	if self._type == value then
		return
	end
	self._type = value
	self:UpdateSize()
	self:Layout(1)
end

function Linear.__getter:type()
	return self._type
end

function Linear.__setter:gap(value)
	if self._gap == value then
		return
	end
	self._gap = value
	self:Layout(1)
end

function Linear.__getter:gap()
	return self._gap
end

function Linear:AddChild(child, index)
	if DisplayGroup.AddChild(self, child, index) == false then
		return false
	end
	if index == nil then
		self:Layout(self.child_count)
	else
		self:Layout(index)
	end
	self._child_width_map[child] = child.width
	self._child_height_map[child] = child.height
	if self._size_fixed then
		if self._type == UIEnumTypes.TYPE_H then
			child.height = self._height
		else
			child.width = self._width
		end
	end
	child:AddEventListener(___all_struct[-431205740], self, self.HandleChildResize)
	return true
end

function Linear:RemoveChild(child)
	local child_index = self:GetChildIndex(child)
	if child_index == 0 then
		return false
	end
	if DisplayGroup.RemoveChild(self, child) == false then
		return false
	end
	self._child_width_map[child] = nil
	self._child_height_map[child] = nil
	self._show_child_map[child] = nil
	child:RemoveEventListener(___all_struct[-431205740], self)
	self:Layout(child_index)
	return true
end

function Linear:RemoveAllChild()
	for i, child in ___ipairs(self._childs) do
		child:RemoveEventListener(___all_struct[-431205740], self)
	end
	self._child_width_map = CreateKeyWeakMap()
	self._child_height_map = CreateKeyWeakMap()
	self._show_child_map = CreateKeyWeakMap()
	self._clip_up_index = 0
	self._clip_down_index = 0
	DisplayGroup.RemoveAllChild(self)
end

function Linear:SetChildIndex(child, index)
	DisplayGroup.SetChildIndex(self, child, index)
	self:Layout(1)
	return true
end

function Linear.__setter:width(value)
	self._width = value
	if self._width_type == UIEnumTypes.SIZE_ABS then
		self._width_value = self._width
	end
	if self._type ~= UIEnumTypes.TYPE_H and self._size_fixed then
		for index, child in ___ipairs(self._childs) do
			child.width = value
		end
	end
end

function Linear.__getter:width()
	if self._size_fixed then
		if self._type == UIEnumTypes.TYPE_H then
			if self._child_count == 0 then
				return 0
			end
			local child = self._childs[self._child_count]
			return child.x + child.width
		end
		return self._width
	end
	return DisplayGroup.__getter.max_right(self)
end

function Linear.__setter:height(value)
	self._height = value
	if self._height_type == UIEnumTypes.SIZE_ABS then
		self._height_value = self._height
	end
	if self._type ~= UIEnumTypes.TYPE_V and self._size_fixed then
		for index, child in ___ipairs(self._childs) do
			child.height = value
		end
	end
end

function Linear.__getter:height()
	if self._size_fixed then
		if self._type == UIEnumTypes.TYPE_V then
			if self._child_count == 0 then
				return 0
			end
			local child = self._childs[self._child_count]
			return child.y + child.height
		end
		return self._height
	end
	return DisplayGroup.__getter.max_bottom(self)
end

function Linear:UpdateSize()
	if self._size_fixed then
		if self._type == UIEnumTypes.TYPE_H then
			for k, v in ___pairs(self._child_width_map) do
				k.width = v
				k.height = self._height
			end
		else
			for k, v in ___pairs(self._child_height_map) do
				k.width = self._width
				k.height = v
			end
		end
	else
		for k, v in ___pairs(self._child_width_map) do
			k.width = v
		end
		for k, v in ___pairs(self._child_height_map) do
			k.height = v
		end
	end
end

function Linear:Layout(index)
	self._clip_up_index = 0
	self._clip_down_index = 0
	local child_count = self.child_count
	if index > child_count then
		return
	end
	if self._type == UIEnumTypes.TYPE_H then
		local offset = 0.0
		if index > 1 then
			offset = self._childs[index - 1].x + self._childs[index - 1].width + self._gap
		end
		local i = index
		while true do
			if not(i <= child_count) then break end
			self._childs[i].x = offset
			self._childs[i].y = 0
			offset = offset + self._childs[i].width + self._gap
			i = i+(1)
		end
	else
		local offset = 0.0
		if index > 1 then
			offset = self._childs[index - 1].y + self._childs[index - 1].height + self._gap
		end
		local i = index
		while true do
			if not(i <= child_count) then break end
			self._childs[i].y = offset
			self._childs[i].x = 0
			offset = offset + self._childs[i].height + self._gap
			i = i+(1)
		end
	end
end

function Linear:DeepLayout()
	self._clip_up_index = 0
	self._clip_down_index = 0
	local child_count = self.child_count
	if child_count == 0 then
		return
	end
	if self._type == UIEnumTypes.TYPE_H then
		local offset = 0.0
		local i = 1
		while true do
			if not(i <= child_count) then break end
			local child = self._childs[i]
			if child.DeepLayout ~= nil then
				child:DeepLayout()
			end
			child.x = offset
			child.y = 0
			offset = offset + child.width + self._gap
			i = i+(1)
		end
	else
		local offset = 0.0
		local i = 1
		while true do
			if not(i <= child_count) then break end
			local child = self._childs[i]
			if child.DeepLayout ~= nil then
				child:DeepLayout()
			end
			child.y = offset
			child.x = 0
			offset = offset + child.height + self._gap
			i = i+(1)
		end
	end
end

function Linear:HandleChildResize(event)
	self:Layout(self:GetChildIndex(event.target))
	if self._show_parent ~= nil then
		if self._type == UIEnumTypes.TYPE_H then
			self._show_parent:UpdateXLayout(self)
		else
			self._show_parent:UpdateYLayout(self)
		end
	end
	self:DispatchEvent(___all_struct[-431205740], {})
end

function Linear.__getter:max_right()
	if self._size_fixed then
		return self.width
	end
	return DisplayGroup.__getter.max_right(self)
end

function Linear.__getter:max_bottom()
	if self._size_fixed then
		return self.height
	end
	return DisplayGroup.__getter.max_bottom(self)
end

function Linear:UpdateWidthLayout(child)
	self:Layout(self:GetChildIndex(child))
end

function Linear:UpdateHeightLayout(child)
	self:Layout(self:GetChildIndex(child))
end

function Linear:ClipRect(left, top, right, bottom, h_move, v_move)
	left = left - self._x
	if left < 0 then
		left = 0
	end
	top = top - (self._y)
	if top < 0 then
		top = 0
	end
	right = right - (self._x)
	if right > self.width then
		right = self.width
	end
	bottom = bottom - (self._y)
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
	local new_show_map = {}
	self._show:RemoveAllChild()
	local max_index = child_count
	local min_index = 1
	local index = min_index
	if self._type == UIEnumTypes.TYPE_H then
		if h_move == nil or self._clip_up_index == 0 then
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
			index = self._clip_up_index
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
		self._clip_up_index = index
		local i = index
		while true do
			if not(i <= child_count) then break end
			if childs[i].x < right then
				self._show:AddChild(childs[i]._show)
				new_show_map[childs[i]] = true
				if childs[i].ClipRect ~= nil then
					childs[i]:ClipRect(left, top, right, bottom, h_move, v_move)
				end
				self._clip_down_index = i
			else
				break
			end
			i = i+(1)
		end
	else
		if v_move == nil or self._clip_up_index == 0 then
			repeat
				if childs[index].y > top then
					max_index = index
					index = __ceil((max_index + min_index) / 2)
				elseif childs[index].y + childs[index].height < top then
					min_index = index
					index = __ceil((max_index + min_index) / 2)
				else
					break
				end
			until not(index ~= min_index and index ~= max_index)
		else
			index = self._clip_up_index
			if v_move < 0 then
				while index < max_index do
					if childs[index].y + childs[index].height >= top then
						break
					end
					index = index + 1
				end
			elseif v_move > 0 then
				while index > min_index do
					if childs[index].y <= top then
						break
					end
					index = index - 1
				end
			end
		end
		self._clip_up_index = index
		local i = index
		while true do
			if not(i <= child_count) then break end
			if childs[i].y < bottom then
				self._show:AddChild(childs[i]._show)
				new_show_map[childs[i]] = true
				if childs[i].ClipRect ~= nil then
					childs[i]:ClipRect(left, top, right, bottom, h_move, v_move)
				end
				self._clip_down_index = i
			else
				break
			end
			i = i+(1)
		end
	end
	for child, v in ___pairs(new_show_map) do
		if self._show_child_map[child] == nil then
			child:DispatchEvent(___all_struct[1862557463], {})
		else
			self._show_child_map[child] = nil
		end
	end
	for child, v in ___pairs(self._show_child_map) do
		child:DispatchEvent(___all_struct[348388800], {})
	end
	self._show_child_map = new_show_map
end

