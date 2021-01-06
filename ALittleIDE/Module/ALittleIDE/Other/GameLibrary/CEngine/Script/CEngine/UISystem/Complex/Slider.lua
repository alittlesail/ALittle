-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittle.Slider = Lua.Class(ALittle.DisplayLayout, "ALittle.Slider")

function ALittle.Slider:Ctor(ctrl_sys)
	___rawset(self, "_pickup_rect", false)
	___rawset(self, "_type", 2)
	___rawset(self, "_offset_rate", 0)
	___rawset(self, "_drag_point_rate", 0)
	___rawset(self, "_fixed", 1)
	___rawset(self, "_grade", 2)
	___rawset(self, "_grade_list", {})
end

function ALittle.Slider.__setter:width(value)
	if self._width == value then
		return
	end
	ALittle.DisplayLayout.__setter.width(self, value)
	self:AdjustBarButton()
end

function ALittle.Slider.__setter:height(value)
	if self._height == value then
		return
	end
	ALittle.DisplayLayout.__setter.height(self, value)
	self:AdjustBarButton()
end

function ALittle.Slider.__getter:width()
	return self._width
end

function ALittle.Slider.__getter:height()
	return self._height
end

function ALittle.Slider.__setter:type(value)
	if self._type == value then
		return
	end
	self._type = value
	self:AdjustBarButton()
end

function ALittle.Slider.__getter:type()
	return self._type
end

function ALittle.Slider.__setter:offset_rate(value)
	self._offset_rate = value
	if self._offset_rate < 0 then
		self._offset_rate = 0
	elseif self._offset_rate > 1 then
		self._offset_rate = 1
	end
	self:AdjustBarButton()
end

function ALittle.Slider.__getter:offset_rate()
	return self._offset_rate
end

function ALittle.Slider.__setter:grade_value(value)
	if self._fixed == 1 then
		self.offset_rate = value
		return
	end
	self.offset_rate = (math.floor(value) - 1) / (self.grade - 1)
end

function ALittle.Slider.__getter:grade_value()
	if self._fixed == 1 then
		return self._offset_rate
	end
	return math.floor(self._offset_rate * (self._grade - 1)) + 1
end

function ALittle.Slider.__setter:bar_background(value)
	if self._bar_background ~= nil then
		self._bar_background:RemoveEventListener(___all_struct[1883782801], self, self.HandleBarBackgroudLButtonDown)
		self:RemoveChild(self._bar_background)
	end
	self._bar_background = value
	if value ~= nil then
		self:AddChild(value, 1)
		value:AddEventListener(___all_struct[1883782801], self, self.HandleBarBackgroudLButtonDown)
	end
	self:AdjustBarButton()
end

function ALittle.Slider:HandleBarBackgroudLButtonDown(event)
	local rel_x = event.rel_x
	local rel_y = event.rel_y
	local real_width = self.width
	local real_height = self.height
	local bar_width = self._bar_button.width
	local bar_height = self._bar_button.height
	if self._type == 2 then
		local offset = rel_y / real_height
		if offset > 1 then
			offset = 1
		elseif offset < 0 then
			offset = 0
		end
		if self._fixed == 1 then
			if self._offset_rate == offset then
				return
			end
			self._offset_rate = offset
			self._bar_button.y = self._offset_rate * real_height - bar_height / 2
		else
			local offset_grade = (1 / (self._grade - 1)) / 2
			local offset_up = offset + offset_grade
			local offset_down = offset - offset_grade
			for k, v in ___ipairs(self._grade_list) do
				if v > offset_down and v <= offset_up then
					self._offset_rate = v
					self._bar_button.y = self._offset_rate * real_height - bar_height / 2
					break
				end
			end
		end
	else
		local offset = rel_x / real_width
		if offset > 1 then
			offset = 1
		elseif offset < 0 then
			offset = 0
		end
		if self._fixed == 1 then
			if self._offset_rate == offset then
				return
			end
			self._offset_rate = offset
			self._bar_button.x = self._offset_rate * real_width - bar_width / 2
		else
			local offset_grade = (1 / (self._grade - 1)) / 2
			local offset_up = offset + offset_grade
			local offset_down = offset - offset_grade
			for k, v in ___ipairs(self._grade_list) do
				if v > offset_down and v <= offset_up then
					self._offset_rate = v
					self._bar_button.x = self._offset_rate * real_width - bar_width / 2
					break
				end
			end
		end
	end
	self:DispatchEvent(___all_struct[958494922], {})
end

function ALittle.Slider.__getter:bar_background()
	return self._bar_background
end

function ALittle.Slider.__setter:bar_button(value)
	if self._bar_button ~= nil then
		self._bar_button:RemoveEventListener(___all_struct[1337289812], self, self.HandleBarButtonDrag)
		self._bar_button:RemoveEventListener(___all_struct[1301789264], self, self.HandleBarButtonDragBegin)
		self._bar_button:RemoveEventListener(___all_struct[-1737121315], self, self.HandleBarButtonScroll)
		self:RemoveChild(self._bar_button)
	end
	self._bar_button = value
	if value ~= nil then
		self:AddChild(value)
		value:AddEventListener(___all_struct[1337289812], self, self.HandleBarButtonDrag)
		value:AddEventListener(___all_struct[1301789264], self, self.HandleBarButtonDragBegin)
		value:AddEventListener(___all_struct[-1737121315], self, self.HandleBarButtonScroll)
		value._can_scroll = true
	end
	self:AdjustBarButton()
end

function ALittle.Slider.__getter:bar_button()
	return self._bar_button
end

function ALittle.Slider.__setter:fixed(value)
	if self._fixed == value then
		return
	end
	self._fixed = value
	if self._fixed == 2 and self._grade ~= nil then
		self._grade_list = {}
		self._grade_list[1] = 0
		local dist = 1 / (self._grade - 1)
		local i = 1
		while true do
			if not(i <= self._grade - 2) then break end
			self._grade_list[i + 1] = i * dist
			i = i+(1)
		end
		local num = ALittle.List_Len(self._grade_list)
		self._grade_list[num + 1] = 1
	end
	self:AdjustBarButton()
end

function ALittle.Slider.__getter:fixed()
	return self._fixed
end

function ALittle.Slider.__setter:grade(value)
	if self._grade == value or value < 2 then
		return
	end
	self._grade = value
	if self._fixed == 2 and value ~= nil then
		self._grade_list = {}
		self._grade_list[1] = 0
		local dist = 1 / (value - 1)
		local i = 1
		while true do
			if not(i <= value - 2) then break end
			self._grade_list[i + 1] = i * dist
			i = i+(1)
		end
		local num = ALittle.List_Len(self._grade_list)
		self._grade_list[num + 1] = 1
	end
	self:AdjustBarButton()
end

function ALittle.Slider.__getter:grade()
	return self._grade
end

function ALittle.Slider:HandleBarButtonDragBegin(event)
	local rel_x
	local rel_y
	rel_x, rel_y = self._bar_button:GlobalToLocalMatrix2D(event.abs_x, event.abs_y)
	if self._type == 2 then
		local height = self._bar_button.height
		self._drag_point_rate = 0
		if height > 0 then
			self._drag_point_rate = rel_y / height
		end
	else
		local width = self._bar_button.width
		self._drag_point_rate = 0
		if width > 0 then
			self._drag_point_rate = rel_x / width
		end
	end
end

function ALittle.Slider:HandleBarButtonDrag(event)
	local rel_x
	local rel_y
	rel_x, rel_y = self._bar_button:GlobalToLocalMatrix2D(event.abs_x, event.abs_y)
	local abs_x
	local abs_y
	abs_x, abs_y = self._bar_background:GlobalToLocalMatrix2D(event.abs_x, event.abs_y)
	local real_width = self.width
	local real_height = self.height
	local bar_width = self._bar_button.width
	local bar_height = self._bar_button.height
	if self._type == 2 then
		if self._fixed == 1 then
			if (event.delta_y > 0 and rel_y < bar_height * self._drag_point_rate) or (event.delta_y < 0 and rel_y > bar_height * self._drag_point_rate) then
				return
			end
			local offset = (self._bar_button.y + bar_height / 2 + event.delta_y) / real_height
			if offset > 1 then
				offset = 1
			elseif offset < 0 then
				offset = 0
			end
			if self._offset_rate == offset then
				return
			end
			self._offset_rate = offset
			self._bar_button.y = self._offset_rate * real_height - bar_height / 2
		else
			local offset = abs_y / real_height
			if offset > 1 then
				offset = 1
			elseif offset < 0 then
				offset = 0
			end
			local offset_grade = (1 / (self._grade - 1)) / 2
			local offset_up = offset + offset_grade
			local offset_down = offset - offset_grade
			for k, v in ___ipairs(self._grade_list) do
				if v > offset_down and v <= offset_up then
					self._offset_rate = v
					self._bar_button.y = self._offset_rate * real_height - bar_height / 2
					break
				end
			end
		end
	else
		if self._fixed == 1 then
			if (event.delta_x > 0 and rel_x < bar_height * self._drag_point_rate) or (event.delta_x < 0 and rel_x > bar_height * self._drag_point_rate) then
				return
			end
			local offset = (self._bar_button.x + bar_width / 2 + event.delta_x) / real_width
			if offset > 1 then
				offset = 1
			elseif offset < 0 then
				offset = 0
			end
			if self._offset_rate == offset then
				return
			end
			self._offset_rate = offset
			self._bar_button.x = self._offset_rate * real_width - bar_width / 2
		else
			local offset = abs_x / real_width
			if offset > 1 then
				offset = 1
			elseif offset < 0 then
				offset = 0
			end
			local offset_grade = (1 / (self._grade - 1)) / 2
			local offset_up = offset + offset_grade
			local offset_down = offset - offset_grade
			for k, v in ___ipairs(self._grade_list) do
				if v > offset_down and v <= offset_up then
					self._offset_rate = v
					self._bar_button.x = self._offset_rate * real_width - bar_width / 2
					break
				end
			end
		end
	end
	self:DispatchEvent(___all_struct[958494922], {})
end

function ALittle.Slider:HandleBarButtonScroll(event)
	local step = nil
	if self._fixed == 1 then
		step = 0.01
	else
		step = 1 / (self._grade - 1)
	end
	if self._type == 2 then
		if event.delta_y > 0 then
			self:HandleUpDownButton(-1 * step)
		elseif event.delta_y < 0 then
			self:HandleUpDownButton(step)
		end
	else
		if event.delta_x > 0 then
			self:HandleUpDownButton(-1 * step)
		elseif event.delta_x < 0 then
			self:HandleUpDownButton(step)
		end
	end
end

function ALittle.Slider:HandleUpDownButton(step)
	self._offset_rate = self._offset_rate + step
	if self._offset_rate < 0 then
		self._offset_rate = 0
	end
	if self._offset_rate > 1 then
		self._offset_rate = 1
	end
	if self._type == 2 then
		self._bar_button.y = self._offset_rate * self.height - self._bar_button.height / 2
	else
		self._bar_button.x = self._offset_rate * self.width - self._bar_button.width / 2
	end
	self:DispatchEvent(___all_struct[958494922], {})
end

function ALittle.Slider:AdjustBarButton()
	if self._bar_background ~= nil then
		self._bar_background.x = 0
		self._bar_background.y = 0
		self._bar_background.width = self.width
		self._bar_background.height = self.height
	end
	if self._bar_button ~= nil then
		if self._type == 2 then
			self._bar_button.x_type = 3
			self._bar_button.x_value = 0
			self._bar_button.y_type = 1
			self._bar_button.y_value = self._offset_rate * self.height - self._bar_button.height / 2
		else
			self._bar_button.x_type = 1
			self._bar_button.x_value = self._offset_rate * self.width - self._bar_button.width / 2
			self._bar_button.y_type = 3
			self._bar_button.y_value = 0
		end
	end
end

end