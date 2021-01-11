-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


local __sin = ALittle.Math_Sin
assert(ALittle.DisplayGroup, " extends class:ALittle.DisplayGroup is nil")
ALittle.ScrollScreen = Lua.Class(ALittle.DisplayGroup, "ALittle.ScrollScreen")

function ALittle.ScrollScreen:Ctor(ctrl_sys)
	___rawset(self, "_width", 0)
	___rawset(self, "_height", 0)
	___rawset(self, "_content_width", 0)
	___rawset(self, "_content_height", 0)
	___rawset(self, "_drag_rate", 0.2)
	___rawset(self, "_open_extends_drag", false)
	___rawset(self, "_drag_delta_x", 0)
	___rawset(self, "_drag_delta_y", 0)
	___rawset(self, "_scroll_view", ALittle.DisplayView(self._ctrl_sys))
	ALittle.DisplayGroup.AddChild(self, self._scroll_view)
	___rawset(self, "_scroll_content", ALittle.DisplayGroup(self._ctrl_sys))
	self._scroll_view:AddChild(self._scroll_content)
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", true)
	___rawset(self, "_pickup_this", true)
	___rawset(self, "_can_scroll", true)
	self:AddEventListener(___all_struct[-1737121315], self, self.HandleMButtonWheel)
	self:AddEventListener(___all_struct[1337289812], self, self.HandleDrag)
	self:AddEventListener(___all_struct[150587926], self, self.HandleDragEnd)
	self:AddEventListener(___all_struct[1301789264], self, self.HandleDragBegin)
	self:RefreshClipDisLine()
end

function ALittle.ScrollScreen:HandleMButtonWheel(event)
	if self._bottom_scroll_bar ~= nil and event.delta_x ~= 0 then
		self._bottom_scroll_bar.offset_rate = self._bottom_scroll_bar.offset_rate - 0.1 * event.delta_x
	end
	if self._right_scroll_bar ~= nil and event.delta_y ~= 0 then
		local offset = self._content_height * 0.1 * event.delta_y
		if offset > 60 then
			offset = 60
		elseif offset < -60 then
			offset = -60
		end
		if offset ~= 0 then
			self._right_scroll_bar.offset_rate = self._right_scroll_bar.offset_rate - offset / self._content_height
		end
	end
	self:AdjustScrollBar()
end

function ALittle.ScrollScreen:EnableDrag(value)
	if value then
		self:AddEventListener(___all_struct[1337289812], self, self.HandleDrag)
		self:AddEventListener(___all_struct[150587926], self, self.HandleDragEnd)
		self:AddEventListener(___all_struct[1301789264], self, self.HandleDragBegin)
	else
		self:RemoveEventListener(___all_struct[1337289812], self, self.HandleDrag)
		self:RemoveEventListener(___all_struct[150587926], self, self.HandleDragEnd)
		self:RemoveEventListener(___all_struct[1301789264], self, self.HandleDragBegin)
	end
end

function ALittle.ScrollScreen.__getter:open_extends_drag()
	return self._open_extends_drag
end

function ALittle.ScrollScreen.__setter:open_extends_drag(value)
	self._open_extends_drag = value
end

function ALittle.ScrollScreen.__getter:container()
	return self._scroll_content
end

function ALittle.ScrollScreen.__getter:view()
	return self._scroll_view
end

function ALittle.ScrollScreen.__setter:container(value)
	if value == nil then
		value = ALittle.DisplayGroup(self._ctrl_sys)
	end
	local child_list = {}
	local child_list_count = 0
	local old_child_list = self._scroll_content.childs
	for k, v in ___ipairs(old_child_list) do
		child_list_count = child_list_count + 1
		child_list[child_list_count] = v
	end
	self._scroll_content:RemoveAllChild()
	self._scroll_content:RemoveEventListener(___all_struct[-431205740], self, self.HandleContainerResize)
	self._scroll_view:RemoveChild(self._scroll_content)
	self._scroll_content = value
	for k, v in ___ipairs(child_list) do
		value:AddChild(v)
	end
	for k, child in ___ipairs(value.childs) do
		child._logic_parent = self
	end
	self._scroll_content:AddEventListener(___all_struct[-431205740], self, self.HandleContainerResize)
	self._scroll_view:AddChild(self._scroll_content, 1)
	self:AdjustScrollBar()
end

function ALittle.ScrollScreen.__setter:container_y(value)
	if self._scroll_content == nil then
		return
	end
	self._scroll_content.y = value
	self:YScrollBarChange()
	self:AdjustScrollBar()
end

function ALittle.ScrollScreen.__getter:container_y()
	if self._scroll_content == nil then
		return 0
	end
	return self._scroll_content.y
end

function ALittle.ScrollScreen.__setter:container_x(value)
	if self._scroll_content == nil then
		return
	end
	self._scroll_content.x = value
	self:XScrollBarChange()
	self:AdjustScrollBar()
end

function ALittle.ScrollScreen.__getter:container_x()
	if self._scroll_content == nil then
		return 0
	end
	return self._scroll_content.x
end

function ALittle.ScrollScreen.__getter:static_object_h()
	return self._static_object_h
end

function ALittle.ScrollScreen.__setter:static_object_h(value)
	if self._static_object_h == value then
		return
	end
	self._scroll_view:RemoveChild(self._static_object_h)
	self._static_object_h = value
	if self._static_object_h == nil then
		return
	end
	self._scroll_view:AddChild(self._static_object_h, 3)
	self._static_object_h.y = 0
	self._static_object_h.x = self._scroll_content.x
end

function ALittle.ScrollScreen.__getter:static_object_v()
	return self._static_object_v
end

function ALittle.ScrollScreen.__setter:static_object_v(value)
	if self._static_object_v == value then
		return
	end
	self._scroll_view:RemoveChild(self._static_object_v)
	self._static_object_v = value
	if self._static_object_v == nil then
		return
	end
	self._scroll_view:AddChild(self._static_object_v, 2)
	self._static_object_v.y = self._scroll_content.y
	self._static_object_v.x = 0
end

function ALittle.ScrollScreen.__getter:static_object_hv()
	return self._static_object_hv
end

function ALittle.ScrollScreen.__setter:static_object_hv(value)
	if self._static_object_hv == value then
		return
	end
	self._scroll_view:RemoveChild(self._static_object_hv)
	self._static_object_hv = value
	if self._static_object_hv == nil then
		return
	end
	self._scroll_view:AddChild(self._static_object_hv, 3)
	self._static_object_hv.y = 0
	self._static_object_hv.x = 0
end

function ALittle.ScrollScreen:GetChildIndex(child)
	return self._scroll_content:GetChildIndex(child)
end

function ALittle.ScrollScreen:SetChildIndex(child, index)
	local result = self._scroll_content:SetChildIndex(child, index)
	self:RefreshClipDisLine()
	return result
end

function ALittle.ScrollScreen:GetChildByIndex(index)
	return self._scroll_content:GetChildByIndex(index)
end

function ALittle.ScrollScreen.__getter:childs()
	return self._scroll_content.childs
end

function ALittle.ScrollScreen.__getter:child_count()
	return self._scroll_content.child_count
end

function ALittle.ScrollScreen:AddChild(child, index)
	if child == nil then
		return false
	end
	if self._scroll_content:AddChild(child, index) == false then
		return false
	end
	child._logic_parent = self
	self:AdjustScrollBar()
	return true
end

function ALittle.ScrollScreen:RemoveChild(child)
	if child == nil then
		return false
	end
	if self._scroll_content:RemoveChild(child) == false then
		return false
	end
	self:AdjustScrollBar()
	return true
end

function ALittle.ScrollScreen:SpliceChild(index, count)
	local result = self._scroll_content:SpliceChild(index, count)
	if result ~= 0 then
		self:AdjustScrollBar()
	end
	return result
end

function ALittle.ScrollScreen:HasChild(child)
	return self._scroll_content:HasChild(child)
end

function ALittle.ScrollScreen:RemoveAllChild()
	A_LoopSystem:RemoveUpdater(self._drag_loop_x)
	A_LoopSystem:RemoveUpdater(self._drag_loop_y)
	A_LoopSystem:RemoveUpdater(self._drag_delta_loop_x)
	A_LoopSystem:RemoveUpdater(self._drag_delta_loop_y)
	A_LoopSystem:RemoveUpdater(self._x_type_dispatch)
	A_LoopSystem:RemoveUpdater(self._y_type_dispatch)
	self._scroll_content:RemoveAllChild()
	self:AdjustScrollBar()
end

function ALittle.ScrollScreen.__setter:width(value)
	if self._width == value then
		return
	end
	self._width = value
	if self._width_type == 1 then
		self._width_value = self._width
	end
	local width = 0.0
	if self._right_scroll_bar ~= nil then
		width = self._right_scroll_bar.width
	end
	local remain_width = self._width - width
	if remain_width < 0 then
		self._scroll_view.width = self._width
		if self._right_scroll_bar ~= nil then
			self._right_scroll_bar.visible = false
			self._right_scroll_bar.x = self._width
			self._right_scroll_bar.y = 0
		end
	else
		self._scroll_view.width = remain_width
		if self._right_scroll_bar ~= nil then
			self._right_scroll_bar.visible = true
			self._right_scroll_bar.x = remain_width
			self._right_scroll_bar.y = 0
		end
	end
	if self._right_scroll_bar ~= nil then
		self._right_scroll_bar.height = self._scroll_view.height
	end
	if self._bottom_scroll_bar ~= nil then
		local rate = self._bottom_scroll_bar.offset_rate
		if self._content_width < self._scroll_view.width then
			rate = 0
		end
		self._bottom_scroll_bar.width = self._scroll_view.width
		self._bottom_scroll_bar.total_size = self._content_width
		self._bottom_scroll_bar.show_size = self._scroll_view.width
		self._bottom_scroll_bar.offset_rate = rate
		self._bottom_scroll_bar.offset_step = 0.1
		local x = 0.0
		local content_width = self._content_width
		if content_width > self._scroll_view.width then
			local total_width = content_width - self._scroll_view.width
			x = -total_width * rate
		end
		self._scroll_content.x = x
		if self._static_object_h ~= nil then
			self._static_object_h.x = x
		end
	end
	self:RefreshClipDisLine()
end

function ALittle.ScrollScreen.__getter:width()
	return self._width
end

function ALittle.ScrollScreen.__setter:height(value)
	if self._height == value then
		return
	end
	self._height = value
	if self._height_type == 1 then
		self._height_value = self._height
	end
	local height = 0.0
	if self._bottom_scroll_bar ~= nil then
		height = self._bottom_scroll_bar.height
	end
	local remain_height = self._height - height
	if remain_height < 0 then
		self._scroll_view.height = self._height
		if self._bottom_scroll_bar ~= nil then
			self._bottom_scroll_bar.visible = false
			self._bottom_scroll_bar.y = self._height
		end
	else
		self._scroll_view.height = remain_height
		if self._bottom_scroll_bar ~= nil then
			self._bottom_scroll_bar.visible = true
			self._bottom_scroll_bar.y = remain_height
		end
	end
	if self._bottom_scroll_bar ~= nil then
		self._bottom_scroll_bar.width = self._scroll_view.width
	end
	if self._right_scroll_bar ~= nil then
		local rate = self._right_scroll_bar.offset_rate
		if self._content_height < self._scroll_view.height then
			rate = 0
		end
		self._right_scroll_bar.height = self._scroll_view.height
		self._right_scroll_bar.total_size = self._content_height
		self._right_scroll_bar.show_size = self._scroll_view.height
		self._right_scroll_bar.offset_rate = rate
		self._right_scroll_bar.offset_step = 0.1
		local y = 0.0
		local content_height = self._content_height
		if content_height > self._scroll_view.height then
			local total_height = content_height - self._scroll_view.height
			y = -total_height * rate
		end
		self._scroll_content.y = y
		if self._static_object_v ~= nil then
			self._static_object_v.y = y
		end
	end
	self:RefreshClipDisLine()
end

function ALittle.ScrollScreen.__getter:height()
	return self._height
end

function ALittle.ScrollScreen.__getter:view_width()
	return self._scroll_view.width
end

function ALittle.ScrollScreen.__getter:view_height()
	return self._scroll_view.height
end

function ALittle.ScrollScreen.__setter:right_scrollbar(value)
	if self._right_scroll_bar ~= nil then
		ALittle.DisplayGroup.RemoveChild(self, self._right_scroll_bar)
		self._right_scroll_bar:RemoveEventListener(___all_struct[958494922], self, self.HandleRightScrollBarChange)
	end
	self._right_scroll_bar = value
	local width = 0.0
	if self._right_scroll_bar ~= nil then
		self._right_scroll_bar.type = 2
		width = self._right_scroll_bar.width
		ALittle.DisplayGroup.AddChild(self, self._right_scroll_bar)
		self._right_scroll_bar:AddEventListener(___all_struct[958494922], self, self.HandleRightScrollBarChange)
		self._right_scroll_bar.height = self._scroll_view.height
		self._right_scroll_bar.y = 0
	end
	local remain_width = self._width - width
	if remain_width < 0 then
		self._scroll_view.width = self._width
		if self._right_scroll_bar ~= nil then
			self._right_scroll_bar.visible = false
			self._right_scroll_bar.x = self._width
		end
	else
		self._scroll_view.width = remain_width
		if self._right_scroll_bar ~= nil then
			self._right_scroll_bar.visible = true
			self._right_scroll_bar.x = remain_width
		end
	end
	if self._right_scroll_bar ~= nil then
		self._right_scroll_bar.total_size = self._content_height
		self._right_scroll_bar.show_size = self._scroll_view.height
		self._right_scroll_bar.offset_rate = 0
		self._right_scroll_bar.offset_step = 0.1
	end
	if self._bottom_scroll_bar ~= nil then
		local rate = self._bottom_scroll_bar.offset_rate
		if self._content_width < self._scroll_view.width then
			rate = 0
		end
		self._bottom_scroll_bar.width = self._scroll_view.width
		self._bottom_scroll_bar.total_size = self._content_width
		self._bottom_scroll_bar.show_size = self._scroll_view.width
		self._bottom_scroll_bar.offset_rate = rate
		self._bottom_scroll_bar.offset_step = 0.1
	end
end

function ALittle.ScrollScreen.__getter:right_scrollbar()
	return self._right_scroll_bar
end

function ALittle.ScrollScreen:ScrollToBottom()
	if self._right_scroll_bar == nil then
		return
	end
	self._right_scroll_bar.offset_rate = 1
	self._right_scroll_bar:DispatchEvent(___all_struct[958494922], {})
end

function ALittle.ScrollScreen:ScrollToRight()
	if self._bottom_scroll_bar == nil then
		return
	end
	self._bottom_scroll_bar.offset_rate = 1
	self._bottom_scroll_bar:DispatchEvent(___all_struct[958494922], {})
end

function ALittle.ScrollScreen.__setter:bottom_scrollbar(value)
	if self._bottom_scroll_bar ~= nil then
		ALittle.DisplayGroup.RemoveChild(self, self._bottom_scroll_bar)
		self._bottom_scroll_bar:RemoveEventListener(___all_struct[958494922], self, self.HandleBottomScrollBarChange)
	end
	self._bottom_scroll_bar = value
	local height = 0.0
	if self._bottom_scroll_bar ~= nil then
		self._bottom_scroll_bar.type = 1
		height = self._bottom_scroll_bar.height
		ALittle.DisplayGroup.AddChild(self, self._bottom_scroll_bar)
		self._bottom_scroll_bar:AddEventListener(___all_struct[958494922], self, self.HandleBottomScrollBarChange)
		self._bottom_scroll_bar.width = self._scroll_view.width
		self._bottom_scroll_bar.x = 0
	end
	local remain_height = self._height - height
	if remain_height < 0 then
		self._scroll_view.height = self._height
		if self._bottom_scroll_bar ~= nil then
			self._bottom_scroll_bar.visible = false
			self._bottom_scroll_bar.y = self._height
		end
	else
		self._scroll_view.height = remain_height
		if self._bottom_scroll_bar ~= nil then
			self._bottom_scroll_bar.visible = true
			self._bottom_scroll_bar.y = remain_height
		end
	end
	if self._bottom_scroll_bar ~= nil then
		self._bottom_scroll_bar.total_size = self._content_width
		self._bottom_scroll_bar.show_size = self._scroll_view.width
		self._bottom_scroll_bar.offset_rate = 0
		self._bottom_scroll_bar.offset_step = 0.1
	end
	if self._right_scroll_bar ~= nil then
		local rate = self._right_scroll_bar.offset_rate
		if self._content_height < self._scroll_view.height then
			rate = 0
		end
		self._right_scroll_bar.height = self._scroll_view.height
		self._right_scroll_bar.total_size = self._content_height
		self._right_scroll_bar.show_size = self._scroll_view.height
		self._right_scroll_bar.offset_rate = rate
		self._right_scroll_bar.offset_step = 0.1
	end
end

function ALittle.ScrollScreen.__getter:bottom_scrollbar()
	return self._bottom_scroll_bar
end

function ALittle.ScrollScreen:AdjustScrollBar()
	self._content_width = self._scroll_content.max_right
	if self._static_object_h ~= nil then
		if self._static_object_h.width > self._content_width then
			self._content_width = self._static_object_h.width
		end
	end
	self._content_height = self._scroll_content.max_bottom
	if self._bottom_scroll_bar ~= nil then
		local rate = self._bottom_scroll_bar.offset_rate
		if self._content_width < self._scroll_view.width then
			rate = 0
		end
		self._bottom_scroll_bar.total_size = self._content_width
		self._bottom_scroll_bar.show_size = self._scroll_view.width
		self._bottom_scroll_bar.offset_rate = rate
		self._bottom_scroll_bar.offset_step = 0.1
		self:HandleBottomScrollBarChange(nil)
	end
	if self._right_scroll_bar ~= nil then
		local rate = self._right_scroll_bar.offset_rate
		if self._content_height < self._scroll_view.height then
			rate = 0
		end
		self._right_scroll_bar.height = self._scroll_view.height
		self._right_scroll_bar.total_size = self._content_height
		self._right_scroll_bar.show_size = self._scroll_view.height
		self._right_scroll_bar.offset_rate = rate
		self._right_scroll_bar.offset_step = 0.1
		self:HandleRightScrollBarChange(nil)
	end
end

function ALittle.ScrollScreen:HandleRightScrollBarChange(event)
	local rate = self._right_scroll_bar.offset_rate
	local y = 0.0
	local content_height = self._content_height
	if content_height > self._scroll_view.height then
		local total_height = content_height - self._scroll_view.height
		y = -total_height * rate
	end
	self._scroll_content.y = y
	if self._static_object_v ~= nil then
		self._static_object_v.y = y
	end
	self:RefreshClipDisLine()
end

function ALittle.ScrollScreen:HandleBottomScrollBarChange(event)
	local rate = self._bottom_scroll_bar.offset_rate
	local x = 0.0
	local content_width = self._content_width
	if content_width > self._scroll_view.width then
		local total_width = content_width - self._scroll_view.width
		x = -total_width * rate
	end
	self._scroll_content.x = x
	if self._static_object_h ~= nil then
		self._static_object_h.x = x
	end
	self:RefreshClipDisLine()
end

function ALittle.ScrollScreen:HandleContainerResize(event)
	self:AdjustScrollBar()
end

function ALittle.ScrollScreen:HandleDragBegin(event)
end

function ALittle.ScrollScreen:HandleDrag(event)
	self._drag_delta_x = event.delta_x
	self._drag_delta_y = event.delta_y
	self._content_width = self._scroll_content.max_right
	if self._static_object_h ~= nil then
		if self._static_object_h.width > self._content_width then
			self._content_width = self._static_object_h.width
		end
	end
	self._content_height = self._scroll_content.max_bottom
	if event.delta_x ~= 0 then
		if event.delta_x > 0 then
			local min_x = 0.0
			local max_x = self._scroll_view.width * self._drag_rate
			local x = self._scroll_content.x
			if x > min_x then
				x = x + event.delta_x * __sin((1 - x / (self._scroll_view.width * self._drag_rate)) * 1.57)
				if x > max_x then
					x = max_x
				end
			else
				x = x + event.delta_x
			end
			if self._open_extends_drag == false and x > min_x then
				x = min_x
			end
			self._scroll_content.x = x
			if self._static_object_h ~= nil then
				self._static_object_h.x = x
			end
			if self._bottom_scroll_bar ~= nil then
				self._bottom_scroll_bar.offset_rate = -x / (self._content_width - self._scroll_view.width)
			end
		else
			local x = self._scroll_content.x
			if self._content_width < self._scroll_view.width then
				x = x + event.delta_x
				if x < 0 then
					x = 0
				end
			else
				local max_x = -self._content_width + self._scroll_view.width
				local min_x = max_x - self._scroll_view.width * self._drag_rate
				if x < max_x then
					x = x + event.delta_x * __sin((x - min_x) / (self._scroll_view.width * self._drag_rate) * 1.57)
					if x < min_x then
						x = min_x
					end
				else
					x = x + event.delta_x
				end
				if self._open_extends_drag == false and x < max_x then
					x = max_x
				end
			end
			self._scroll_content.x = x
			if self._static_object_h ~= nil then
				self._static_object_h.x = x
			end
			if self._bottom_scroll_bar ~= nil then
				self._bottom_scroll_bar.offset_rate = -x / (self._content_width - self._scroll_view.width)
			end
		end
		self:RefreshClipDisLine(event.delta_x)
	end
	if event.delta_y ~= 0 then
		if event.delta_y > 0 then
			local min_y = 0.0
			local max_y = self._scroll_view.height * self._drag_rate
			local y = self._scroll_content.y
			if y > min_y then
				y = y + event.delta_y * __sin((1 - y / (self._scroll_view.height * self._drag_rate)) * 1.57)
				if y > max_y then
					y = max_y
				end
			else
				y = y + event.delta_y
			end
			if self._open_extends_drag == false and y > min_y then
				y = min_y
			end
			self._scroll_content.y = y
			if self._static_object_v ~= nil then
				self._static_object_v.y = y
			end
			if self._right_scroll_bar ~= nil then
				self._right_scroll_bar.offset_rate = -y / (self._content_height - self._scroll_view.height)
			end
		else
			local y = self._scroll_content.y
			if self._content_height < self._scroll_view.height then
				y = y + event.delta_y
				if y < 0 then
					y = 0
				end
			else
				local max_y = -self._content_height + self._scroll_view.height
				local min_y = max_y - self._scroll_view.height * self._drag_rate
				if y < max_y then
					y = y + event.delta_y * __sin((y - min_y) / (self._scroll_view.height * self._drag_rate) * 1.57)
					if y < min_y then
						y = min_y
					end
				else
					y = y + event.delta_y
				end
				if self._open_extends_drag == false and y < max_y then
					y = max_y
				end
			end
			self._scroll_content.y = y
			if self._static_object_v ~= nil then
				self._static_object_v.y = y
			end
			if self._right_scroll_bar ~= nil then
				self._right_scroll_bar.offset_rate = -y / (self._content_height - self._scroll_view.height)
			end
		end
		self:RefreshClipDisLine(nil, event.delta_y)
	end
end

function ALittle.ScrollScreen:HandleDragEnd(event)
	self._content_width = self._scroll_content.max_right
	if self._static_object_h ~= nil then
		if self._static_object_h.width > self._content_width then
			self._content_width = self._static_object_h.width
		end
	end
	self._content_height = self._scroll_content.max_bottom
	if self._scroll_content.x > 0 then
		if self._scroll_content.x >= self._scroll_view.width * self._drag_rate * 0.9 then
			self:DispatchEvent(___all_struct[-839083637], {})
		end
		A_LoopSystem:RemoveUpdater(self._drag_loop_x)
		self._drag_loop_x = ALittle.LoopLinear(self._scroll_content, "x", 0, 200, 0, Lua.Bind(ALittle.ScrollScreen.XScrollBarChange, self))
		A_LoopSystem:AddUpdater(self._drag_loop_x)
	elseif self._scroll_content.x < -self._content_width + self._scroll_view.width then
		if self._scroll_content.x <= -self._content_width + self._scroll_view.width - self._scroll_view.width * self._drag_rate * 0.9 then
			self:DispatchEvent(___all_struct[-567702959], {})
		end
		if self._scroll_content.x < 0 then
			A_LoopSystem:RemoveUpdater(self._drag_loop_x)
			self._drag_loop_x = ALittle.LoopLinear(self._scroll_content, "x", -self._content_width + self._scroll_view.width, 200, 0, Lua.Bind(ALittle.ScrollScreen.XScrollBarChange, self))
			A_LoopSystem:AddUpdater(self._drag_loop_x)
		end
	elseif self._scroll_content.x ~= 0 and self._scroll_content.x ~= -self._content_width + self._scroll_view.width then
		local target_x = self._scroll_content.x + self._drag_delta_x * 10
		local event_dispatch = nil
		if self._drag_delta_x < 0 then
			local max_x = -self._content_width + self._scroll_view.width
			local min_x = max_x - self._scroll_view.width * self._drag_rate
			if target_x < min_x then
				target_x = min_x
				event_dispatch = Lua.Bind(ALittle.ScrollScreen.ScrollDispatchDragLeftEvent, self)
			end
			if target_x >= min_x and target_x <= max_x then
				A_LoopSystem:RemoveUpdater(self._drag_loop_x)
				self._drag_loop_x = ALittle.LoopLinear(self._scroll_content, "x", -self._content_width + self._scroll_view.width, 200, 300, Lua.Bind(ALittle.ScrollScreen.XScrollBarChange, self))
				A_LoopSystem:AddUpdater(self._drag_loop_x)
			end
		elseif self._drag_delta_x > 0 then
			local max_x = self._scroll_view.width * self._drag_rate
			local min_x = 0
			if target_x > max_x then
				target_x = max_x
				event_dispatch = Lua.Bind(ALittle.ScrollScreen.ScrollDispatchDragRightEvent, self)
			end
			if target_x >= min_x and target_x <= max_x then
				A_LoopSystem:RemoveUpdater(self._drag_loop_x)
				self._drag_loop_x = ALittle.LoopLinear(self._scroll_content, "x", 0, 200, 300, Lua.Bind(ALittle.ScrollScreen.XScrollBarChange, self))
				A_LoopSystem:AddUpdater(self._drag_loop_x)
			end
		end
		A_LoopSystem:RemoveUpdater(self._x_type_dispatch)
		if event_dispatch ~= nil then
			self._x_type_dispatch = ALittle.LoopFunction(event_dispatch, 1, 0, 300)
			A_LoopSystem:AddUpdater(self._x_type_dispatch)
		end
		if self._open_extends_drag == false then
			if target_x > 0 then
				target_x = 0
			elseif target_x < -self._content_width + self._scroll_view.width then
				target_x = -self._content_width + self._scroll_view.width
			end
		end
		A_LoopSystem:RemoveUpdater(self._drag_delta_loop_x)
		self._drag_delta_loop_x = ALittle.LoopRit(self._scroll_content, "x", target_x, 300, 0, Lua.Bind(ALittle.ScrollScreen.XScrollBarChange, self))
		A_LoopSystem:AddUpdater(self._drag_delta_loop_x)
	end
	if self._scroll_content.y > 0 then
		if self._scroll_content.y >= self._scroll_view.height * self._drag_rate * 0.9 then
			self:DispatchEvent(___all_struct[1848466169], {})
		end
		A_LoopSystem:RemoveUpdater(self._drag_loop_y)
		self._drag_loop_y = ALittle.LoopLinear(self._scroll_content, "y", 0, 200, 0, Lua.Bind(ALittle.ScrollScreen.YScrollBarChange, self))
		A_LoopSystem:AddUpdater(self._drag_loop_y)
	elseif self._scroll_content.y < -self._content_height + self._scroll_view.height then
		if self._scroll_content.y <= -self._content_height + self._scroll_view.height - self._scroll_view.height * self._drag_rate * 0.9 then
			self:DispatchEvent(___all_struct[809518110], {})
		end
		if self._scroll_content.y < 0 then
			A_LoopSystem:RemoveUpdater(self._drag_loop_y)
			self._drag_loop_y = ALittle.LoopLinear(self._scroll_content, "y", -self._content_height + self._scroll_view.height, 200, 0, Lua.Bind(ALittle.ScrollScreen.YScrollBarChange, self))
			A_LoopSystem:AddUpdater(self._drag_loop_y)
		end
	elseif self._scroll_content.y ~= 0 and self._scroll_content.y ~= -self._content_height + self._scroll_view.height then
		local event_dispatch = nil
		local target_y = self._scroll_content.y + self._drag_delta_y * 10
		if self._drag_delta_y < 0 then
			local max_y = -self._content_height + self._scroll_view.height
			local min_y = max_y - self._scroll_view.height * self._drag_rate
			if target_y < min_y then
				target_y = min_y
				event_dispatch = Lua.Bind(ALittle.ScrollScreen.ScrollDispatchDragUpEvent, self)
			end
			if target_y >= min_y and target_y <= max_y then
				A_LoopSystem:RemoveUpdater(self._drag_loop_y)
				self._drag_loop_y = ALittle.LoopLinear(self._scroll_content, "y", -self._content_height + self._scroll_view.height, 200, 300, Lua.Bind(ALittle.ScrollScreen.YScrollBarChange, self))
				A_LoopSystem:AddUpdater(self._drag_loop_y)
			end
		elseif self._drag_delta_y > 0 then
			local max_y = self._scroll_view.height * self._drag_rate
			local min_y = 0.0
			if target_y > max_y then
				target_y = max_y
				event_dispatch = Lua.Bind(ALittle.ScrollScreen.ScrollDispatchDragDownEvent, self)
			end
			if target_y >= min_y and target_y <= max_y then
				A_LoopSystem:RemoveUpdater(self._drag_loop_y)
				self._drag_loop_y = ALittle.LoopLinear(self._scroll_content, "y", 0, 200, 300, Lua.Bind(ALittle.ScrollScreen.YScrollBarChange, self))
				A_LoopSystem:AddUpdater(self._drag_loop_y)
			end
		end
		A_LoopSystem:RemoveUpdater(self._y_type_dispatch)
		if event_dispatch ~= nil then
			self._y_type_dispatch = ALittle.LoopFunction(event_dispatch, 1, 0, 300)
			A_LoopSystem:AddUpdater(self._y_type_dispatch)
		end
		if self._open_extends_drag == false then
			if target_y > 0 then
				target_y = 0
			elseif target_y < -self._content_height + self._scroll_view.height then
				target_y = -self._content_height + self._scroll_view.height
			end
		end
		A_LoopSystem:RemoveUpdater(self._drag_delta_loop_y)
		self._drag_delta_loop_y = ALittle.LoopRit(self._scroll_content, "y", target_y, 300, 0, Lua.Bind(ALittle.ScrollScreen.YScrollBarChange, self))
		A_LoopSystem:AddUpdater(self._drag_delta_loop_y)
	end
	self._drag_delta_x = 0
	self._drag_delta_y = 0
end

function ALittle.ScrollScreen:RefreshClipDisLineImpl(h_move, v_move)
	self._scroll_content:ClipRect(0, 0, self._width, self._height, h_move, v_move)
	if self._static_object_v ~= nil then
		self._static_object_v:ClipRect(0, 0, self._width, self._height, h_move, v_move)
	end
	if self._static_object_h ~= nil then
		self._static_object_h:ClipRect(0, 0, self._width, self._height, h_move, v_move)
	end
	self._clip_loop = nil
end

function ALittle.ScrollScreen:RefreshClipDisLine(h_move, v_move)
	if self._clip_loop ~= nil and self._clip_loop._user_data == nil then
		return
	end
	self._clip_loop = ALittle.LoopFunction(Lua.Bind(self.RefreshClipDisLineImpl, self, h_move, v_move), 1, 0, 1)
	self._clip_loop._user_data = v_move
	A_LoopSystem:AddUpdater(self._clip_loop)
end

function ALittle.ScrollScreen:XScrollBarChange()
	if self._static_object_h ~= nil then
		self._static_object_h.x = self._scroll_content.x
	end
	if self._bottom_scroll_bar ~= nil then
		self._bottom_scroll_bar.offset_rate = -self._scroll_content.x / (self._content_width - self._scroll_view.width)
	end
	self:RefreshClipDisLine(nil, nil)
end

function ALittle.ScrollScreen:YScrollBarChange()
	if self._static_object_v ~= nil then
		self._static_object_v.y = self._scroll_content.y
	end
	if self._right_scroll_bar ~= nil then
		self._right_scroll_bar.offset_rate = -self._scroll_content.y / (self._content_height - self._scroll_view.height)
	end
	self:RefreshClipDisLine(nil, nil)
end

function ALittle.ScrollScreen:ScrollDispatchDragDownEvent()
	self:DispatchEvent(___all_struct[1848466169], {})
end

function ALittle.ScrollScreen:ScrollDispatchDragUpEvent()
	self:DispatchEvent(___all_struct[809518110], {})
end

function ALittle.ScrollScreen:ScrollDispatchDragLeftEvent()
	self:DispatchEvent(___all_struct[-567702959], {})
end

function ALittle.ScrollScreen:ScrollDispatchDragRightEvent()
	self:DispatchEvent(___all_struct[-839083637], {})
end

end