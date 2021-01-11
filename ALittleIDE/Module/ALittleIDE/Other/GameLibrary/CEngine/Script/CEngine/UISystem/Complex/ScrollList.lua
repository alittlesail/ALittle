-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


local __floor = ALittle.Math_Floor
local __remove = ALittle.List_Remove
local __sin = ALittle.Math_Sin
assert(ALittle.DisplayView, " extends class:ALittle.DisplayView is nil")
ALittle.ScrollList = Lua.Class(ALittle.DisplayView, "ALittle.ScrollList")

function ALittle.ScrollList:Ctor(ctrl_sys)
	___rawset(self, "_width", 0)
	___rawset(self, "_height", 0)
	___rawset(self, "_drag_delta_x", 0)
	___rawset(self, "_drag_delta_y", 0)
	___rawset(self, "_drag_delta_table", {})
	___rawset(self, "_drag_delta_table_count", 0)
	___rawset(self, "_drag_rate", 0.2)
	___rawset(self, "_open_extends_drag", false)
	___rawset(self, "_clip_atonce", false)
	___rawset(self, "_drag_time", 0)
	___rawset(self, "_max_speed", 40)
	___rawset(self, "_type", 2)
	___rawset(self, "_scroll_linear", ALittle.Linear(self._ctrl_sys))
	self._scroll_linear.width_type = 4
	self._scroll_linear.type = 2
	ALittle.DisplayView.AddChild(self, self._scroll_linear)
	self._scroll_linear:AddEventListener(___all_struct[-431205740], self, self.HandleLinearResize)
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

function ALittle.ScrollList:GetChildIndex(child)
	return self._scroll_linear:GetChildIndex(child)
end

function ALittle.ScrollList:SetChildIndex(child, index)
	self._scroll_linear:SetChildIndex(child, index)
	self:RefreshClipDisLine()
	return true
end

function ALittle.ScrollList:GetChildByIndex(index)
	return self._scroll_linear:GetChildByIndex(index)
end

function ALittle.ScrollList.__getter:childs()
	return self._scroll_linear.childs
end

function ALittle.ScrollList.__getter:child_count()
	return self._scroll_linear.child_count
end

function ALittle.ScrollList.__setter:type(value)
	if self._type == value then
		return
	end
	self._type = value
	if self._type == 1 then
		self._scroll_linear.width_type = 1
		self._scroll_linear.height_type = 4
		self._scroll_linear.type = 1
	else
		self._scroll_linear.width_type = 4
		self._scroll_linear.height_type = 1
		self._scroll_linear.type = 2
	end
	self:RefreshChild(false)
end

function ALittle.ScrollList.__getter:type()
	return self._type
end

function ALittle.ScrollList:AddChild(child, index)
	if child == nil then
		return false
	end
	if self._scroll_linear:AddChild(child, index) == false then
		return false
	end
	child._logic_parent = self
	self:RefreshChild(false)
	return true
end

function ALittle.ScrollList:RemoveChild(child)
	if child == nil then
		return false
	end
	if self._scroll_linear:RemoveChild(child) == false then
		return false
	end
	self:RefreshChild(false)
	return true
end

function ALittle.ScrollList:SpliceChild(index, count)
	local result = self._scroll_linear:SpliceChild(index, count)
	if result ~= 0 then
		self:RefreshChild(false)
	end
	return result
end

function ALittle.ScrollList:AddChildEffect(child, up)
	if child == nil then
		return false
	end
	if up then
		if self._type == 1 then
			local target_value = self._scroll_linear.x + self._scroll_linear.width
			if self._scroll_linear:AddChild(child, 1) == false then
				return false
			end
			self._scroll_linear.x = target_value - self._scroll_linear.width
		else
			local target_value = self._scroll_linear.y + self._scroll_linear.height
			if self._scroll_linear:AddChild(child, 1) == false then
				return false
			end
			self._scroll_linear.y = target_value - self._scroll_linear.height
		end
	else
		if self._scroll_linear:AddChild(child) == false then
			return false
		end
	end
	self:RefreshChild(false)
	return true
end

function ALittle.ScrollList:RemoveChildEffect(up, loop)
	if up then
		if self._type == 1 then
			local child = self._scroll_linear:GetChildByIndex(1)
			local target_value = self._scroll_linear.x + self._scroll_linear.width
			if self._scroll_linear:RemoveChild(child) == false then
				return false
			end
			self._scroll_linear.x = target_value - self._scroll_linear.width
		else
			local child = self._scroll_linear:GetChildByIndex(1)
			local target_value = self._scroll_linear.y + self._scroll_linear.height
			if self._scroll_linear:RemoveChild(child) == false then
				return false
			end
			self._scroll_linear.y = target_value - self._scroll_linear.height
		end
	else
		local child = self._scroll_linear:GetChildByIndex(self._scroll_linear.child_count)
		if self._scroll_linear:RemoveChild(child) == false then
			return false
		end
	end
	if loop then
		self:RefreshChild(true)
	else
		self:RefreshChild(false)
	end
	return true
end

function ALittle.ScrollList:HasChild(child)
	return self._scroll_linear:HasChild(child)
end

function ALittle.ScrollList:RemoveAllChild()
	if self._type == 1 then
		A_LoopSystem:RemoveUpdater(self._drag_loop_x)
		A_LoopSystem:RemoveUpdater(self._drag_delta_loop_x)
		self._scroll_linear.x = 0
	else
		A_LoopSystem:RemoveUpdater(self._drag_loop_y)
		A_LoopSystem:RemoveUpdater(self._drag_delta_loop_y)
		self._scroll_linear.y = 0
	end
	self._scroll_linear:RemoveAllChild()
	self:UpdateLoadingShow()
	self:AdjustScrollBar()
end

function ALittle.ScrollList:RefreshChild(loop)
	if self._type == 1 then
		local linear_width = self._scroll_linear.width
		local target_x = nil
		if linear_width >= self._width then
			if self._scroll_linear.x > 0 then
				target_x = 0
			elseif self._scroll_linear.x < -linear_width + self._width then
				target_x = -linear_width + self._width
			end
		else
			target_x = 0
		end
		if target_x == nil or target_x == self._scroll_linear.x then
			A_LoopSystem:RemoveUpdater(self._drag_loop_x)
			self:RefreshClipDisLine()
			self:AdjustScrollBar()
			return
		end
		if self._drag_loop_x ~= nil and self._drag_loop_x:IsCompleted() == false then
			local speed = self._drag_loop_x.speed
			local func = Lua.Bind(ALittle.ScrollList.RefreshClipDisLine, self, nil)
			A_LoopSystem:RemoveUpdater(self._drag_loop_x)
			local time = (target_x - self._scroll_linear.x) / speed
			self._drag_loop_x = ALittle.LoopLinear(self._scroll_linear, "x", target_x, __floor(time), 0, func)
			A_LoopSystem:AddUpdater(self._drag_loop_x)
		else
			if loop then
				local func = Lua.Bind(ALittle.ScrollList.RefreshClipDisLine, self, nil)
				A_LoopSystem:RemoveUpdater(self._drag_loop_x)
				self._drag_loop_x = ALittle.LoopLinear(self._scroll_linear, "x", target_x, 200, 0, func)
				A_LoopSystem:AddUpdater(self._drag_loop_x)
			else
				self._scroll_linear.x = target_x
			end
		end
	else
		local linear_height = self._scroll_linear.height
		local target_y = nil
		if linear_height >= self._height then
			if self._scroll_linear.y > 0 then
				target_y = 0
			elseif self._scroll_linear.y < -linear_height + self._height then
				target_y = -linear_height + self._height
			end
		else
			target_y = 0
		end
		if target_y == nil or target_y == self._scroll_linear.y then
			A_LoopSystem:RemoveUpdater(self._drag_loop_y)
			self:RefreshClipDisLine()
			self:AdjustScrollBar()
			return
		end
		if self._drag_loop_y ~= nil and self._drag_loop_y:IsCompleted() == false then
			local speed = self._drag_loop_y.speed
			local func = Lua.Bind(ALittle.ScrollList.RefreshClipDisLine, self, nil)
			A_LoopSystem:RemoveUpdater(self._drag_loop_y)
			local time = (target_y - self._scroll_linear.y) / speed
			self._drag_loop_y = ALittle.LoopLinear(self._scroll_linear, "y", target_y, __floor(time), 0, func)
			A_LoopSystem:AddUpdater(self._drag_loop_y)
		else
			if loop then
				local func = Lua.Bind(ALittle.ScrollList.RefreshClipDisLine, self, nil)
				A_LoopSystem:RemoveUpdater(self._drag_loop_y)
				self._drag_loop_y = ALittle.LoopLinear(self._scroll_linear, "y", target_y, 200, 0, func)
				A_LoopSystem:AddUpdater(self._drag_loop_y)
			else
				self._scroll_linear.y = target_y
			end
		end
	end
	self:RefreshClipDisLine()
	self:AdjustScrollBar()
end

function ALittle.ScrollList.__setter:clip_atonce(value)
	self._clip_atonce = value
end

function ALittle.ScrollList.__getter:clip_atonce()
	return self._clip_atonce
end

function ALittle.ScrollList.__setter:scroll_offset(value)
	if self._type == 1 then
		A_LoopSystem:RemoveUpdater(self._drag_loop_x)
		A_LoopSystem:RemoveUpdater(self._drag_delta_loop_x)
		if value > 0 then
			value = 0
		end
		local total_width = self.width
		local linear_width = self._scroll_linear.width
		if total_width < linear_width then
			local delta = total_width - linear_width
			if value < delta then
				value = delta
			end
		end
		self._scroll_linear.x = value
		self:AdjustScrollBar()
	else
		A_LoopSystem:RemoveUpdater(self._drag_loop_y)
		A_LoopSystem:RemoveUpdater(self._drag_delta_loop_y)
		if value > 0 then
			value = 0
		end
		local total_height = self.height
		local linear_height = self._scroll_linear.height
		if total_height < linear_height then
			local delta = total_height - linear_height
			if value < delta then
				value = delta
			end
		end
		self._scroll_linear.y = value
		self:AdjustScrollBar()
	end
end

function ALittle.ScrollList.__getter:scroll_offset()
	if self._type == 1 then
		return self._scroll_linear.x
	end
	return self._scroll_linear.y
end

function ALittle.ScrollList:ScrollToBottom()
	if self.height >= self.real_height then
		return
	end
	self.scroll_offset = self.height - self.real_height
end

function ALittle.ScrollList.__setter:gap(value)
	if value == nil then
		value = 0
	end
	self._scroll_linear.gap = value
	self:RefreshClipDisLine()
	self:AdjustScrollBar()
end

function ALittle.ScrollList.__getter:gap()
	return self._scroll_linear.gap
end

function ALittle.ScrollList.__getter:real_height()
	return self._scroll_linear.height
end

function ALittle.ScrollList.__getter:real_width()
	return self._scroll_linear.width
end

function ALittle.ScrollList.__setter:width(value)
	if self._type == 2 then
		ALittle.DisplayView.__setter.width(self, value)
		return
	end
	if self._width == value then
		return
	end
	self._width = value
	if self._width_type == 1 then
		self._width_value = self._width
	end
	self._show:SetWidth(self._width)
	if self._scroll_bar ~= nil then
		local linear_width = self._scroll_linear.width
		local rate = self._scroll_bar.offset_rate
		if linear_width < self._width then
			rate = 0
		end
		self._scroll_bar.width = self._width
		self._scroll_bar.total_size = linear_width
		self._scroll_bar.show_size = self._width
		self._scroll_bar.offset_rate = rate
		self._scroll_bar.offset_step = 0.1
		local x = 0.0
		if linear_width > self._width then
			local total_width = linear_width - self._width
			x = -total_width * rate
		end
		self._scroll_linear.x = x
	end
	self:RefreshClipDisLine()
end

function ALittle.ScrollList.__setter:height(value)
	if self._type == 1 then
		ALittle.DisplayView.__setter.height(self, value)
		return
	end
	if self._height == value then
		return
	end
	self._height = value
	if self._height_type == 1 then
		self._height_value = self._height
	end
	self._show:SetHeight(self._height)
	if self._scroll_bar ~= nil then
		local linear_height = self._scroll_linear.height
		local rate = self._scroll_bar.offset_rate
		if linear_height < self._height then
			rate = 0
		end
		self._scroll_bar.height = self._height
		self._scroll_bar.total_size = linear_height
		self._scroll_bar.show_size = self._height
		self._scroll_bar.offset_rate = rate
		self._scroll_bar.offset_step = 0.1
		local y = 0.0
		if linear_height > self._height then
			local total_height = linear_height - self._height
			y = -total_height * rate
		end
		self._scroll_linear.y = y
	end
	self:RefreshClipDisLine()
end

function ALittle.ScrollList.__setter:right_scrollbar(value)
	if self._scroll_bar ~= nil then
		A_LoopSystem:RemoveUpdater(self._scroll_bar_loop)
		ALittle.DisplayView.RemoveChild(self, self._scroll_bar)
		self._scroll_bar:RemoveEventListener(___all_struct[958494922], self, self.HandleRightScrollBarChange)
		self._scroll_bar:RemoveEventListener(___all_struct[1309977874], self, self.HandleRightScrollBarChangeEnd)
	end
	self._scroll_bar = value
	if self._scroll_bar ~= nil then
		if self._type == 1 then
			self._scroll_bar.alpha = 0
			self._scroll_bar.visible = false
			self._scroll_bar.type = 1
			self._scroll_bar.y_type = 4
			ALittle.DisplayView.AddChild(self, self._scroll_bar)
			self._scroll_bar:AddEventListener(___all_struct[958494922], self, self.HandleRightScrollBarChange)
			self._scroll_bar:AddEventListener(___all_struct[1309977874], self, self.HandleRightScrollBarChangeEnd)
			self._scroll_bar.width = self._width
			self._scroll_bar.x = 0
			self._scroll_bar.total_size = self._scroll_linear.width
			self._scroll_bar.show_size = self._width
			self._scroll_bar.offset_rate = 0
			self._scroll_bar.offset_step = 0.1
		else
			self._scroll_bar.alpha = 0
			self._scroll_bar.visible = false
			self._scroll_bar.type = 2
			self._scroll_bar.x_type = 4
			ALittle.DisplayView.AddChild(self, self._scroll_bar)
			self._scroll_bar:AddEventListener(___all_struct[958494922], self, self.HandleRightScrollBarChange)
			self._scroll_bar:AddEventListener(___all_struct[1309977874], self, self.HandleRightScrollBarChangeEnd)
			self._scroll_bar.height = self._height
			self._scroll_bar.y = 0
			self._scroll_bar.total_size = self._scroll_linear.height
			self._scroll_bar.show_size = self._height
			self._scroll_bar.offset_rate = 0
			self._scroll_bar.offset_step = 0.1
		end
	end
end

function ALittle.ScrollList.__getter:right_scrollbar()
	return self._scroll_bar
end

function ALittle.ScrollList:AdjustScrollBar()
	if self._type == 1 then
		local linear_width = self._scroll_linear.width
		if self._scroll_bar ~= nil then
			local rate = 0.0
			if linear_width <= self._width then
				rate = 0
			else
				rate = -self._scroll_linear.x / (linear_width - self._width)
			end
			self._scroll_bar.width = self._width
			self._scroll_bar.total_size = linear_width
			self._scroll_bar.show_size = self._width
			self._scroll_bar.offset_rate = rate
			self._scroll_bar.offset_step = 0.1
		end
	else
		local linear_height = self._scroll_linear.height
		if self._scroll_bar ~= nil then
			local rate = 0.0
			if linear_height <= self._height then
				rate = 0
			else
				rate = -self._scroll_linear.y / (linear_height - self._height)
			end
			self._scroll_bar.height = self._height
			self._scroll_bar.total_size = linear_height
			self._scroll_bar.show_size = self._height
			self._scroll_bar.offset_rate = rate
			self._scroll_bar.offset_step = 0.1
		end
	end
end

function ALittle.ScrollList.__getter:loading_show_up()
	return self._loading_show_up
end

function ALittle.ScrollList.__setter:loading_show_up(value)
	if self._loading_show_up ~= value then
		ALittle.DisplayView.RemoveChild(self, self._loading_show_up)
		self._loading_show_up = nil
	end
	if value ~= nil then
		self._loading_show_up = value
		ALittle.DisplayView.AddChild(self, self._loading_show_up)
		if self._type == 1 then
			self._loading_show_up.x = self._scroll_linear.x - self._loading_show_up.width
		else
			self._loading_show_up.y = self._scroll_linear.y - self._loading_show_up.height
		end
	end
end

function ALittle.ScrollList.__getter:loading_show_down()
	return self._loading_show_down
end

function ALittle.ScrollList.__setter:loading_show_down(value)
	if self._loading_show_down ~= value then
		ALittle.DisplayView.RemoveChild(self, self._loading_show_down)
		self._loading_show_down = nil
	end
	if value ~= nil then
		self._loading_show_down = value
		ALittle.DisplayView.AddChild(self, self._loading_show_down)
		if self._type == 1 then
			self._loading_show_down.x = self._scroll_linear.x + self._scroll_linear.width
		else
			self._loading_show_down.y = self._scroll_linear.y + self._scroll_linear.height
		end
	end
end

function ALittle.ScrollList:UpdateLoadingShow()
	if self._type == 1 then
		if self._loading_show_up ~= nil then
			self._loading_show_up.x = self._scroll_linear.x - self._loading_show_up.width
		end
		if self._loading_show_down ~= nil then
			self._loading_show_down.x = self._scroll_linear.x + self._scroll_linear.width
		end
	else
		if self._loading_show_up ~= nil then
			self._loading_show_up.y = self._scroll_linear.y - self._loading_show_up.height
		end
		if self._loading_show_down ~= nil then
			self._loading_show_down.y = self._scroll_linear.y + self._scroll_linear.height
		end
	end
end

function ALittle.ScrollList:Layout(index)
	self._scroll_linear:Layout(index)
	self:RefreshClipDisLine()
end

function ALittle.ScrollList:DeepLayout()
	self._scroll_linear:DeepLayout()
	self:RefreshClipDisLine()
end

function ALittle.ScrollList:HandleLinearResize(event)
	self:AdjustScrollBar()
	self:RefreshClipDisLine()
end

function ALittle.ScrollList:HandleRightScrollBarChange(event)
	if self._type == 1 then
		local rate = self._scroll_bar.offset_rate
		local x = 0.0
		local linear_width = self._scroll_linear.width
		if linear_width > self._width then
			local total_width = linear_width - self._width
			x = -total_width * rate
		end
		self._scroll_linear.x = x
	else
		local rate = self._scroll_bar.offset_rate
		local y = 0.0
		local linear_height = self._scroll_linear.height
		if linear_height > self._height then
			local total_height = linear_height - self._height
			y = -total_height * rate
		end
		self._scroll_linear.y = y
	end
	self:RefreshClipDisLine()
	self:ShowRightScrollBar()
end

function ALittle.ScrollList:HandleRightScrollBarChangeEnd(event)
	self:HideRightScrollBar()
end

function ALittle.ScrollList:HandleMButtonWheel(event)
	if self._scroll_bar ~= nil and event.delta_y ~= 0 then
		local offset = self._scroll_linear.height * 0.1 * event.delta_y
		if offset > 60 then
			offset = 60
		elseif offset < -60 then
			offset = -60
		end
		if offset ~= 0 then
			self._scroll_bar.offset_rate = self._scroll_bar.offset_rate - offset / self._scroll_linear.height
		end
		self:HandleRightScrollBarChange(nil)
		self:HideRightScrollBar()
	end
end

function ALittle.ScrollList.__getter:open_extends_drag()
	return self._open_extends_drag
end

function ALittle.ScrollList.__setter:open_extends_drag(value)
	self._open_extends_drag = value
end

function ALittle.ScrollList:HandleDragBegin(event)
	self._drag_delta_table = {}
	self._drag_delta_table_count = 0
	A_LoopSystem:RemoveUpdater(self._scroll_bar_loop)
	if self._scroll_bar ~= nil then
		self._scroll_bar.visible = true
		self._scroll_bar.alpha = 1
	end
	if self._type == 1 then
		A_LoopSystem:RemoveUpdater(self._drag_loop_x)
		A_LoopSystem:RemoveUpdater(self._drag_delta_loop_x)
	else
		A_LoopSystem:RemoveUpdater(self._drag_loop_y)
		A_LoopSystem:RemoveUpdater(self._drag_delta_loop_y)
	end
end

function ALittle.ScrollList:HandleDrag(event)
	if self._type == 1 then
		if self._drag_delta_table_count < 3 then
			self._drag_delta_table_count = self._drag_delta_table_count + 1
			self._drag_delta_table[self._drag_delta_table_count] = event.delta_x
		else
			__remove(self._drag_delta_table, 1)
			self._drag_delta_table[self._drag_delta_table_count] = event.delta_x
		end
		self._drag_time = ALittle.Time_GetCurTime()
		local linear_width = self._scroll_linear.width
		if event.delta_x ~= 0 and self._scroll_bar ~= nil then
			if event.delta_x > 0 then
				local min_x = 0.0
				local max_x = self._width * self._drag_rate
				local x = self._scroll_linear.x
				if x > min_x then
					x = x + event.delta_x * __sin((1 - x / (self._width * self._drag_rate)) * 1.57)
					if x > max_x then
						x = max_x
					end
				else
					x = x + (event.delta_x)
				end
				if x >= min_x and not self._open_extends_drag then
					x = min_x
				end
				self._scroll_linear.x = x
				if self._scroll_bar ~= nil then
					self._scroll_bar.offset_rate = -x / (linear_width - self._width)
				end
			else
				local x = self._scroll_linear.x
				if linear_width < self._width then
					x = x + (event.delta_x)
					if x < 0 then
						x = 0
					end
				else
					local max_x = -linear_width + self._width
					local min_x = max_x - self._width * self._drag_rate
					if x < max_x then
						x = x + (event.delta_x * __sin((x - min_x) / (self._width * self._drag_rate) * 1.57))
						if x < min_x then
							x = min_x
						end
					else
						x = x + (event.delta_x)
					end
					if x <= max_x and not self._open_extends_drag then
						x = max_x
					end
				end
				self._scroll_linear.x = x
				if self._scroll_bar ~= nil then
					self._scroll_bar.offset_rate = -x / (linear_width - self._width)
				end
			end
			self:RefreshClipDisLine(event.delta_x)
		end
	else
		if self._drag_delta_table_count < 3 then
			self._drag_delta_table_count = self._drag_delta_table_count + 1
			self._drag_delta_table[self._drag_delta_table_count] = event.delta_y
		else
			__remove(self._drag_delta_table, 1)
			self._drag_delta_table[self._drag_delta_table_count] = event.delta_y
		end
		self._drag_time = ALittle.Time_GetCurTime()
		local linear_height = self._scroll_linear.height
		if event.delta_y ~= 0 and self._scroll_bar ~= nil then
			if event.delta_y > 0 then
				local min_y = 0.0
				local max_y = self._height * self._drag_rate
				local y = self._scroll_linear.y
				if y > min_y then
					y = y + event.delta_y * __sin((1 - y / (self._height * self._drag_rate)) * 1.57)
					if y > max_y then
						y = max_y
					end
				else
					y = y + (event.delta_y)
				end
				if y >= min_y and not self._open_extends_drag then
					y = min_y
				end
				self._scroll_linear.y = y
				if self._scroll_bar ~= nil then
					self._scroll_bar.offset_rate = -y / (linear_height - self._height)
				end
			else
				local y = self._scroll_linear.y
				if linear_height < self._height then
					y = y + (event.delta_y)
					if y < 0 then
						y = 0
					end
				else
					local max_y = -linear_height + self._height
					local min_y = max_y - self._height * self._drag_rate
					if y < max_y then
						y = y + (event.delta_y * __sin((y - min_y) / (self._height * self._drag_rate) * 1.57))
						if y < min_y then
							y = min_y
						end
					else
						y = y + (event.delta_y)
					end
					if y <= max_y and not self._open_extends_drag then
						y = max_y
					end
				end
				self._scroll_linear.y = y
				if self._scroll_bar ~= nil then
					self._scroll_bar.offset_rate = -y / (linear_height - self._height)
				end
			end
			self:RefreshClipDisLine(event.delta_y)
		end
	end
end

function ALittle.ScrollList:HandleDragEnd(event)
	if self._type == 1 then
		local linear_width = self._scroll_linear.width
		if self._scroll_linear.x > 0 then
			A_LoopSystem:RemoveUpdater(self._drag_loop_x)
			local func = Lua.Bind(ALittle.ScrollList.RefreshClipDisLine, self, nil)
			self._drag_loop_x = ALittle.LoopLinear(self._scroll_linear, "x", 0, 200, 0, func)
			A_LoopSystem:AddUpdater(self._drag_loop_x)
			self:HideRightScrollBar()
			if self._scroll_linear.x >= self._width * self._drag_rate * 0.9 then
				self:DispatchEvent(___all_struct[1848466169], {})
			end
		elseif self._scroll_linear.x < -linear_width + self._width then
			if self._scroll_linear.x < 0 then
				local func = Lua.Bind(ALittle.ScrollList.RefreshClipDisLine, self, nil)
				A_LoopSystem:RemoveUpdater(self._drag_loop_x)
				self._drag_loop_x = ALittle.LoopLinear(self._scroll_linear, "x", -linear_width + self._width, 200, 0, func)
				A_LoopSystem:AddUpdater(self._drag_loop_x)
				self:HideRightScrollBar()
			end
			if self._scroll_linear.x <= -linear_width + self._width - self._width * self._drag_rate * 0.9 then
				self:DispatchEvent(___all_struct[809518110], {})
			end
		elseif self._scroll_linear.x ~= 0 and self._scroll_linear.x ~= -linear_width + self._width then
			local count = self._drag_delta_table_count
			local drag_delta_x = 0.0
			local drag_end_time = ALittle.Time_GetCurTime() - self._drag_time
			if drag_end_time < 50 then
				if count == 1 or count == 2 then
					drag_delta_x = self._drag_delta_table[1]
				elseif count == 3 then
					drag_delta_x = __floor((self._drag_delta_table[count - 1] + self._drag_delta_table[count - 2]) / 2)
				else
					drag_delta_x = 0
				end
			else
				if count ~= 0 then
					drag_delta_x = self._drag_delta_table[count]
				else
					drag_delta_x = 0
				end
			end
			if drag_delta_x < 0 and drag_delta_x < -self._max_speed then
				drag_delta_x = -self._max_speed
			elseif drag_delta_x > 0 and drag_delta_x > self._max_speed then
				drag_delta_x = self._max_speed
			end
			self._drag_delta_x = drag_delta_x
			A_LoopSystem:RemoveUpdater(self._drag_delta_loop_x)
			self._drag_delta_loop_x = ALittle.LoopFunction(Lua.Bind(self.RefreshLinearX, self), -1, 1, 0)
			A_LoopSystem:AddUpdater(self._drag_delta_loop_x)
		end
	else
		local linear_height = self._scroll_linear.height
		if self._scroll_linear.y > 0 then
			A_LoopSystem:RemoveUpdater(self._drag_loop_y)
			local func = Lua.Bind(ALittle.ScrollList.RefreshClipDisLine, self, nil)
			self._drag_loop_y = ALittle.LoopLinear(self._scroll_linear, "y", 0, 200, 0, func)
			A_LoopSystem:AddUpdater(self._drag_loop_y)
			self:HideRightScrollBar()
			if self._scroll_linear.y >= self._height * self._drag_rate * 0.9 then
				self:DispatchEvent(___all_struct[1848466169], {})
			end
		elseif self._scroll_linear.y < -linear_height + self._height then
			if self._scroll_linear.y < 0 then
				local func = Lua.Bind(ALittle.ScrollList.RefreshClipDisLine, self, nil)
				A_LoopSystem:RemoveUpdater(self._drag_loop_y)
				self._drag_loop_y = ALittle.LoopLinear(self._scroll_linear, "y", -linear_height + self._height, 200, 0, func)
				A_LoopSystem:AddUpdater(self._drag_loop_y)
				self:HideRightScrollBar()
			end
			if self._scroll_linear.y <= -linear_height + self._height - self._height * self._drag_rate * 0.9 then
				self:DispatchEvent(___all_struct[809518110], {})
			end
		elseif self._scroll_linear.y ~= 0 and self._scroll_linear.y ~= -linear_height + self._height then
			local count = self._drag_delta_table_count
			local drag_delta_y = 0.0
			local drag_end_time = ALittle.Time_GetCurTime() - self._drag_time
			if drag_end_time < 50 then
				if count == 1 or count == 2 then
					drag_delta_y = self._drag_delta_table[1]
				elseif count == 3 then
					drag_delta_y = __floor((self._drag_delta_table[count - 1] + self._drag_delta_table[count - 2]) / 2)
				else
					drag_delta_y = 0
				end
			else
				if count ~= 0 then
					drag_delta_y = self._drag_delta_table[count]
				else
					drag_delta_y = 0
				end
			end
			if drag_delta_y < 0 and drag_delta_y < -self._max_speed then
				drag_delta_y = -self._max_speed
			elseif drag_delta_y > 0 and drag_delta_y > self._max_speed then
				drag_delta_y = self._max_speed
			end
			self._drag_delta_y = drag_delta_y
			A_LoopSystem:RemoveUpdater(self._drag_delta_loop_y)
			self._drag_delta_loop_y = ALittle.LoopFunction(Lua.Bind(self.RefreshLinearY, self), -1, 1, 0)
			A_LoopSystem:AddUpdater(self._drag_delta_loop_y)
		end
	end
end

function ALittle.ScrollList:RefreshLinearX()
	self._scroll_linear.x = self._scroll_linear.x + self._drag_delta_x
	local linear_width = self._scroll_linear.width
	local loop_end = false
	if self._drag_delta_x ~= 0 and self._scroll_bar ~= nil then
		if self._drag_delta_x > 0 then
			local min_x = 0.0
			local max_x = self._width * self._drag_rate
			local x = self._scroll_linear.x
			if x > min_x then
				x = x + self._drag_delta_x * __sin((1 - x / (self._width * self._drag_rate)) * 1.57)
				if x > max_x then
					x = max_x
					loop_end = true
				end
			else
				x = x + (self._drag_delta_x)
			end
			if x >= min_x and not self._open_extends_drag then
				x = min_x
			end
			self._scroll_linear.x = x
			if self._scroll_bar ~= nil then
				self._scroll_bar.offset_rate = -x / (linear_width - self._width)
			end
		else
			local x = self._scroll_linear.x
			if linear_width < self._width then
				x = x + (self._drag_delta_x)
				if x < 0 then
					x = 0
				end
			else
				local max_x = -linear_width + self._width
				local min_x = max_x - self._width * self._drag_rate
				if x < max_x then
					x = x + (self._drag_delta_x * __sin((x - min_x) / (self._width * self._drag_rate) * 1.57))
					if x < min_x then
						x = min_x
						loop_end = true
					end
				else
					x = x + (self._drag_delta_x)
				end
				if x <= max_x and not self._open_extends_drag then
					x = max_x
				end
			end
			self._scroll_linear.x = x
			if self._scroll_bar ~= nil then
				self._scroll_bar.offset_rate = -x / (linear_width - self._width)
			end
		end
		self:RefreshClipDisLine()
	end
	if self._drag_delta_x < 0 then
		self._drag_delta_x = self._drag_delta_x + 1
		if self._drag_delta_x >= 0 then
			loop_end = true
		end
	elseif self._drag_delta_x > 0 then
		self._drag_delta_x = self._drag_delta_x - 1
		if self._drag_delta_x <= 0 then
			loop_end = true
		end
	else
		loop_end = true
	end
	if loop_end then
		A_LoopSystem:RemoveUpdater(self._drag_delta_loop_x)
		if self._scroll_linear.x > 0 then
			local func = Lua.Bind(ALittle.ScrollList.RefreshClipDisLine, self, nil)
			A_LoopSystem:RemoveUpdater(self._drag_loop_x)
			self._drag_loop_x = ALittle.LoopLinear(self._scroll_linear, "x", 0, 200, 0, func)
			A_LoopSystem:AddUpdater(self._drag_loop_x)
			if self._scroll_linear.x >= self._width * self._drag_rate * 0.9 then
				self:DispatchEvent(___all_struct[1848466169], {})
			end
		elseif self._scroll_linear.x < -linear_width + self._width then
			if self._scroll_linear.x < 0 then
				local func = Lua.Bind(ALittle.ScrollList.RefreshClipDisLine, self, nil)
				A_LoopSystem:RemoveUpdater(self._drag_loop_x)
				self._drag_loop_x = ALittle.LoopLinear(self._scroll_linear, "x", -linear_width + self._width, 200, 0, func)
				A_LoopSystem:AddUpdater(self._drag_loop_x)
			end
			if self._scroll_linear.x <= -linear_width + self._width - self._width * self._drag_rate * 0.9 then
				self:DispatchEvent(___all_struct[809518110], {})
			end
		end
		self:HideRightScrollBar()
	end
end

function ALittle.ScrollList:RefreshLinearY()
	self._scroll_linear.y = self._scroll_linear.y + self._drag_delta_y
	local linear_height = self._scroll_linear.height
	local loop_end = false
	if self._drag_delta_y ~= 0 and self._scroll_bar ~= nil then
		if self._drag_delta_y > 0 then
			local min_y = 0.0
			local max_y = self._height * self._drag_rate
			local y = self._scroll_linear.y
			if y > min_y then
				y = y + (self._drag_delta_y * __sin((1 - y / (self._height * self._drag_rate)) * 1.57))
				if y > max_y then
					y = max_y
					loop_end = true
				end
			else
				y = y + (self._drag_delta_y)
			end
			if y >= min_y and not self._open_extends_drag then
				y = min_y
			end
			self._scroll_linear.y = y
			if self._scroll_bar ~= nil then
				self._scroll_bar.offset_rate = -y / (linear_height - self._height)
			end
		else
			local y = self._scroll_linear.y
			if linear_height < self._height then
				y = y + (self._drag_delta_y)
				if y < 0 then
					y = 0
				end
			else
				local max_y = -linear_height + self._height
				local min_y = max_y - self._height * self._drag_rate
				if y < max_y then
					y = y + (self._drag_delta_y * __sin((y - min_y) / (self._height * self._drag_rate) * 1.57))
					if y < min_y then
						y = min_y
						loop_end = true
					end
				else
					y = y + (self._drag_delta_y)
				end
				if y <= max_y and not self._open_extends_drag then
					y = max_y
				end
			end
			self._scroll_linear.y = y
			if self._scroll_bar ~= nil then
				self._scroll_bar.offset_rate = -y / (linear_height - self._height)
			end
		end
		self:RefreshClipDisLine()
	end
	if self._drag_delta_y < 0 then
		self._drag_delta_y = self._drag_delta_y + 1
		if self._drag_delta_y >= 0 then
			loop_end = true
		end
	elseif self._drag_delta_y > 0 then
		self._drag_delta_y = self._drag_delta_y - 1
		if self._drag_delta_y <= 0 then
			loop_end = true
		end
	else
		loop_end = true
	end
	if loop_end then
		A_LoopSystem:RemoveUpdater(self._drag_delta_loop_y)
		if self._scroll_linear.y > 0 then
			local func = Lua.Bind(ALittle.ScrollList.RefreshClipDisLine, self, nil)
			A_LoopSystem:RemoveUpdater(self._drag_loop_y)
			self._drag_loop_y = ALittle.LoopLinear(self._scroll_linear, "y", 0, 200, 0, func)
			A_LoopSystem:AddUpdater(self._drag_loop_y)
			if self._scroll_linear.y >= self._height * self._drag_rate * 0.9 then
				self:DispatchEvent(___all_struct[1848466169], {})
			end
		elseif self._scroll_linear.y < -linear_height + self._height then
			if self._scroll_linear.y < 0 then
				local func = Lua.Bind(ALittle.ScrollList.RefreshClipDisLine, self, nil)
				A_LoopSystem:RemoveUpdater(self._drag_loop_y)
				self._drag_loop_y = ALittle.LoopLinear(self._scroll_linear, "y", -linear_height + self._height, 200, 0, func)
				A_LoopSystem:AddUpdater(self._drag_loop_y)
			end
			if self._scroll_linear.y <= -linear_height + self._height - self._height * self._drag_rate * 0.9 then
				self:DispatchEvent(___all_struct[809518110], {})
			end
		end
		self:HideRightScrollBar()
	end
end

function ALittle.ScrollList:YScrollBarChange()
	self._scroll_bar.offset_rate = -self._scroll_linear.y / (self._linear_height - self._height)
end

function ALittle.ScrollList:XScrollBarChange()
	self._scroll_bar.offset_rate = -self._scroll_linear.x / (self._linear_width - self._width)
end

function ALittle.ScrollList:RefreshClipDisLineImpl(v_move)
	self._scroll_linear:ClipRect(0, 0, self.width, self.height, nil, v_move)
	self._clip_loop = nil
end

function ALittle.ScrollList:RefreshClipDisLine(v_move)
	self:UpdateLoadingShow()
	if self._clip_atonce then
		self._scroll_linear:ClipRect(0, 0, self.width, self.height, nil, nil)
		return
	end
	if self._clip_loop ~= nil and self._clip_loop._user_data == nil then
		return
	end
	self._clip_loop = ALittle.LoopFunction(Lua.Bind(self.RefreshClipDisLineImpl, self, v_move), 1, 0, 1)
	self._clip_loop._user_data = v_move
	A_LoopSystem:AddUpdater(self._clip_loop)
end

function ALittle.ScrollList:HideRightScrollBar()
	if self._scroll_bar ~= nil then
		self._scroll_bar_loop = ALittle.LoopList()
		self._scroll_bar_loop:AddUpdater(ALittle.LoopLinear(self._scroll_bar, "alpha", 0, 2000, 1000))
		self._scroll_bar_loop:AddUpdater(ALittle.LoopAttribute(self._scroll_bar, "visible", false, 1))
		A_LoopSystem:AddUpdater(self._scroll_bar_loop)
	end
end

function ALittle.ScrollList:ShowRightScrollBar()
	if self._scroll_bar_loop ~= nil then
		A_LoopSystem:RemoveUpdater(self._scroll_bar_loop)
		self._scroll_bar_loop = nil
		if self._scroll_bar ~= nil then
			self._scroll_bar.visible = true
			self._scroll_bar.alpha = 1
		end
	end
end

end