-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


local __cos = ALittle.Math_Cos
local __sin = ALittle.Math_Sin
assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittle.ImageInput = Lua.Class(ALittle.DisplayLayout, "ALittle.ImageInput")

function ALittle.ImageInput:Ctor(ctrl_sys)
	___rawset(self, "_show_input", ALittle.TextInput(self._ctrl_sys))
	self._show_input.x_type = 2
	self._show_input.y_type = 2
	self._show_input.width_type = 4
	self._show_input.width_value = 0
	self._show_input.height_type = 4
	self._show_input.height_value = 0
	self:AddChild(self._show_input, 5)
	___rawset(self, "_logic_left", 0)
	___rawset(self, "_logic_right", 0)
	___rawset(self, "_logic_top", 0)
	___rawset(self, "_logic_bottom", 0)
	___rawset(self, "_ims_padding", 0)
	___rawset(self, "_show_disabled", nil)
	___rawset(self, "_pickup_this", true)
	self._show_input:AddEventListener(___all_struct[-644464135], self, self.HandleFocusIn)
	self._show_input:AddEventListener(___all_struct[292776509], self, self.HandleFocusOut)
	self._show_input:AddEventListener(___all_struct[544684311], self, self.HandleMoveIn)
	self._show_input:AddEventListener(___all_struct[-1202439334], self, self.HandleMoveOut)
	self._show_input:AddEventListener(___all_struct[1883782801], self, self.HandleImageInputTransformLButtonDown)
	self._show_input:AddEventListener(___all_struct[-1234078962], self, self.HandleImageInputTransformTextInput)
	self._show_input:AddEventListener(___all_struct[-1604617962], self, self.HandleImageInputTransformKeyDown)
	self._show_input:AddEventListener(___all_struct[1301789264], self, self.HandleImageInputTransformDragBegin)
	self._show_input:AddEventListener(___all_struct[1337289812], self, self.HandleImageInputTransformDrag)
	self._show_input:AddEventListener(___all_struct[150587926], self, self.HandleImageInputTransformDragEnd)
	self._show_input:AddEventListener(___all_struct[-1737121315], self, self.HandleImageInputTransformMButtonWheel)
	self._show_input:AddEventListener(___all_struct[958494922], self, self.HandleImageInputTransformChangd)
	self._show_input:AddEventListener(___all_struct[776398171], self, self.HandleImageInputTransformEnterKey)
	self._show_input:AddEventListener(___all_struct[2024735182], self, self.HandleImageInputTransformTabKey)
	self._show_input:AddEventListener(___all_struct[1637310579], self, self.HandleImageInputTransformEscKey)
	self._show_input:AddEventListener(___all_struct[-641444818], self, self.HandleImageInputTransformRButtonDown)
	self._show_input:AddEventListener(___all_struct[-569321214], self, self.HandleImageInputTransformRButtonUp)
	self._show_input:AddEventListener(___all_struct[-439548260], self, self.HandleImageInputTransformLongButtonDown)
end

function ALittle.ImageInput.__setter:disabled(value)
	ALittle.DisplayObject.__setter.disabled(self, value)
	if value then
		self:ShowDisabled()
	else
		self:ShowUp()
	end
end

function ALittle.ImageInput.__getter:is_focus()
	return A_UISystem.focus == self._show_input
end

function ALittle.ImageInput.__setter:focus(value)
	if value then
		A_UISystem.focus = self._show_input
	else
		if A_UISystem.focus == self._show_input then
			A_UISystem.focus = nil
		end
	end
end

function ALittle.ImageInput.__getter:is_input()
	return true
end

function ALittle.ImageInput.__getter:regex()
	return self._show_input.regex
end

function ALittle.ImageInput.__setter:regex(value)
	if value == nil then
		value = ""
	end
	self._show_input.regex = value
end

function ALittle.ImageInput.__getter:limit_len()
	return self._show_input.limit_len
end

function ALittle.ImageInput.__setter:limit_len(value)
	if value == nil then
		value = 0
	end
	self._show_input.limit_len = value
end

function ALittle.ImageInput.__setter:default_text(value)
	self._show_input.default_text = value
end

function ALittle.ImageInput.__getter:default_text()
	return self._show_input.default_text
end

function ALittle.ImageInput.__setter:default_text_alpha(value)
	self._show_input.default_text_alpha = value
end

function ALittle.ImageInput.__getter:default_text_alpha()
	return self._show_input.default_text_alpha
end

function ALittle.ImageInput.__getter:cursor_x()
	return self._show_input.cursor_x
end

function ALittle.ImageInput.__getter:cursor_y()
	return self._show_input.cursor_y
end

function ALittle.ImageInput.__setter:editable(value)
	self._show_input.editable = value
end

function ALittle.ImageInput.__getter:editable()
	return self._show_input.editable
end

function ALittle.ImageInput.__setter:font_path(value)
	self._show_input.font_path = value
end

function ALittle.ImageInput.__setter:font_size(value)
	self._show_input.font_size = value
end

function ALittle.ImageInput.__getter:font_path()
	return self._show_input.font_path
end

function ALittle.ImageInput.__getter:font_size()
	return self._show_input.font_size
end

function ALittle.ImageInput.__setter:text(value)
	self._show_input.text = value
end

function ALittle.ImageInput.__getter:text()
	return self._show_input.text
end

function ALittle.ImageInput.__setter:bold(value)
	self._show_input.bold = value
end

function ALittle.ImageInput.__getter:bold()
	return self._show_input.bold
end

function ALittle.ImageInput.__setter:italic(value)
	self._show_input.italic = value
end

function ALittle.ImageInput.__getter:italic()
	return self._show_input.italic
end

function ALittle.ImageInput.__setter:underline(value)
	self._show_input.underline = value
end

function ALittle.ImageInput.__getter:underline()
	return self._show_input.underline
end

function ALittle.ImageInput.__setter:deleteline(value)
	self._show_input.deleteline = value
end

function ALittle.ImageInput.__getter:deleteline()
	return self._show_input.deleteline
end

function ALittle.ImageInput.__setter:password_mode(value)
	self._show_input.password_mode = value
end

function ALittle.ImageInput.__getter:password_mode()
	return self._show_input.password_mode
end

function ALittle.ImageInput.__setter:cursor_red(value)
	self._show_input.cursor_red = value
end

function ALittle.ImageInput.__getter:cursor_red()
	return self._show_input.cursor_red
end

function ALittle.ImageInput.__setter:cursor_green(value)
	self._show_input.cursor_green = value
end

function ALittle.ImageInput.__getter:cursor_green()
	return self._show_input.cursor_green
end

function ALittle.ImageInput.__setter:cursor_blue(value)
	self._show_input.cursor_blue = value
end

function ALittle.ImageInput.__getter:cursor_blue()
	return self._show_input.cursor_blue
end

function ALittle.ImageInput.__setter:red(value)
	self._show_input.red = value
end

function ALittle.ImageInput.__getter:red()
	return self._show_input.red
end

function ALittle.ImageInput.__setter:green(value)
	self._show_input.green = value
end

function ALittle.ImageInput.__getter:green()
	return self._show_input.green
end

function ALittle.ImageInput.__setter:blue(value)
	self._show_input.blue = value
end

function ALittle.ImageInput.__getter:blue()
	return self._show_input.blue
end

function ALittle.ImageInput.__setter:ims_padding(value)
	self._ims_padding = value
	self._show_input.ims_padding = ALittle.Math_Floor(value + self._logic_bottom)
end

function ALittle.ImageInput.__getter:ims_padding()
	return self._ims_padding
end

function ALittle.ImageInput:HandleFocusIn(event)
	event.target = self
	self:DispatchEvent(___all_struct[-644464135], event)
	self:ShowDown()
end

function ALittle.ImageInput:HandleFocusOut(event)
	event.target = self
	self:DispatchEvent(___all_struct[292776509], event)
	self:ShowUp()
end

function ALittle.ImageInput:HandleImageInputTransformLButtonDown(event)
	event.target = self
	self:DispatchEvent(___all_struct[1883782801], event)
end

function ALittle.ImageInput:HandleImageInputTransformTextInput(event)
	event.target = self
	self:DispatchEvent(___all_struct[-1234078962], event)
end

function ALittle.ImageInput:HandleImageInputTransformKeyDown(event)
	event.target = self
	self:DispatchEvent(___all_struct[-1604617962], event)
end

function ALittle.ImageInput:HandleImageInputTransformDragBegin(event)
	event.target = self
	self:DispatchEvent(___all_struct[1301789264], event)
end

function ALittle.ImageInput:HandleImageInputTransformDrag(event)
	event.target = self
	self:DispatchEvent(___all_struct[1337289812], event)
end

function ALittle.ImageInput:HandleImageInputTransformDragEnd(event)
	event.target = self
	self:DispatchEvent(___all_struct[150587926], event)
end

function ALittle.ImageInput:HandleImageInputTransformMButtonWheel(event)
	event.target = self
	self:DispatchEvent(___all_struct[-1737121315], event)
end

function ALittle.ImageInput:HandleImageInputTransformChangd(event)
	event.target = self
	self:DispatchEvent(___all_struct[958494922], event)
end

function ALittle.ImageInput:HandleImageInputTransformEnterKey(event)
	event.target = self
	self:DispatchEvent(___all_struct[776398171], event)
end

function ALittle.ImageInput:HandleImageInputTransformTabKey(event)
	event.target = self
	self:DispatchEvent(___all_struct[2024735182], event)
end

function ALittle.ImageInput:HandleImageInputTransformEscKey(event)
	event.target = self
	self:DispatchEvent(___all_struct[1637310579], event)
end

function ALittle.ImageInput:HandleImageInputTransformRButtonDown(event)
	event.target = self
	self:DispatchEvent(___all_struct[-641444818], event)
end

function ALittle.ImageInput:HandleImageInputTransformRButtonUp(event)
	event.target = self
	self:DispatchEvent(___all_struct[-569321214], event)
end

function ALittle.ImageInput:HandleImageInputTransformLongButtonDown(event)
	event.target = self
	self:DispatchEvent(___all_struct[-439548260], event)
end

function ALittle.ImageInput:HandleMoveIn(event)
	event.target = self
	self:DispatchEvent(___all_struct[544684311], event)
	if A_UISystem.focus ~= self._show_input then
		self:ShowOver()
	end
end

function ALittle.ImageInput:HandleMoveOut(event)
	event.target = self
	self:DispatchEvent(___all_struct[-1202439334], event)
	if A_UISystem.focus ~= self._show_input then
		self:ShowUp()
	end
end

function ALittle.ImageInput:ShowUp()
	if self._abs_disabled or self._disabled then
		return
	end
	if self._show_up ~= nil then
		self._show_up.alpha = 1
	end
	if self._show_over ~= nil then
		self._show_over.alpha = 0
	end
	if self._show_down ~= nil then
		self._show_down.alpha = 0
	end
	if self._show_disabled ~= nil then
		self._show_disabled.alpha = 0
	end
end

function ALittle.ImageInput:ShowDown()
	if self._abs_disabled or self._disabled then
		return
	end
	if self._show_up ~= nil then
		self._show_up.alpha = 0
	end
	if self._show_over ~= nil then
		self._show_over.alpha = 0
	end
	if self._show_down ~= nil then
		self._show_down.alpha = 1
	end
	if self._show_disabled ~= nil then
		self._show_disabled.alpha = 0
	end
end

function ALittle.ImageInput:ShowOver()
	if self._abs_disabled or self._disabled then
		return
	end
	if self._show_up ~= nil then
		self._show_up.alpha = 0
	end
	if self._show_over ~= nil then
		self._show_over.alpha = 1
	end
	if self._show_down ~= nil then
		self._show_down.alpha = 0
	end
	if self._show_disabled ~= nil then
		self._show_disabled.alpha = 0
	end
end

function ALittle.ImageInput:ShowDisabled()
	if self._show_up ~= nil then
		self._show_up.alpha = 0
	end
	if self._show_over ~= nil then
		self._show_over.alpha = 0
	end
	if self._show_down ~= nil then
		self._show_down.alpha = 0
	end
	if self._show_disabled ~= nil then
		self._show_disabled.alpha = 1
	end
end

function ALittle.ImageInput.__setter:show_up(value)
	self:RemoveChild(self._show_up)
	self._show_up = value
	if self._show_up ~= nil then
		self._show_up.width_type = 4
		self._show_up.height_type = 4
		self._show_up.width_value = 0
		self._show_up.height_value = 0
		self._show_up.disabled = true
		self:AddChild(self._show_up, 1)
	end
	self:ShowUp()
end

function ALittle.ImageInput.__getter:show_up()
	return self._show_up
end

function ALittle.ImageInput.__setter:show_down(value)
	self:RemoveChild(self._show_down)
	self._show_down = value
	if self._show_down ~= nil then
		self._show_down.width_type = 4
		self._show_down.height_type = 4
		self._show_down.width_value = 0
		self._show_down.height_value = 0
		self._show_down.disabled = true
		self:AddChild(self._show_down, 1)
	end
	self:ShowUp()
end

function ALittle.ImageInput.__getter:show_down()
	return self._show_down
end

function ALittle.ImageInput.__setter:show_over(value)
	self:RemoveChild(self._show_over)
	self._show_over = value
	if self._show_over ~= nil then
		self._show_over.width_type = 4
		self._show_over.height_type = 4
		self._show_over.width_value = 0
		self._show_over.height_value = 0
		self._show_over.disabled = true
		self:AddChild(self._show_over, 1)
	end
	self:ShowUp()
end

function ALittle.ImageInput.__getter:show_over()
	return self._show_over
end

function ALittle.ImageInput.__setter:show_disabled(value)
	self:RemoveChild(self._show_disabled)
	self._show_disabled = value
	if self._show_disabled ~= nil then
		self._show_disabled.width_type = 4
		self._show_disabled.height_type = 4
		self._show_disabled.width_value = 0
		self._show_disabled.height_value = 0
		self._show_disabled.disabled = true
		self:AddChild(self._show_disabled, 1)
	end
	self:ShowUp()
end

function ALittle.ImageInput.__getter:show_disabled()
	return self._show_disabled
end

function ALittle.ImageInput.__getter:show_input()
	return self._show_input
end

function ALittle.ImageInput.__setter:margin_left(value)
	self._logic_left = value
	self:Layout()
end

function ALittle.ImageInput.__getter:margin_left()
	return self._logic_left
end

function ALittle.ImageInput.__setter:margin_right(value)
	self._logic_right = value
	self:Layout()
end

function ALittle.ImageInput.__getter:margin_right()
	return self._logic_right
end

function ALittle.ImageInput.__setter:margin_top(value)
	self._logic_top = value
	self:Layout()
end

function ALittle.ImageInput.__getter:margin_top()
	return self._logic_top
end

function ALittle.ImageInput.__setter:margin_bottom(value)
	self._logic_bottom = value
	self:Layout()
	self._show_input.ims_padding = ALittle.Math_Floor(self._ims_padding + self._logic_bottom)
end

function ALittle.ImageInput.__getter:margin_bottom()
	return self._logic_bottom
end

function ALittle.ImageInput:Layout()
	self:SetChildIndex(self._show_input, 5)
	self._show_input.x_value = self._logic_left
	self._show_input.y_value = self._logic_top
	self._show_input.width_value = self._logic_left + self._logic_right
	self._show_input.height_value = self._logic_top + self._logic_bottom
end

function ALittle.ImageInput:PickUp(x, y)
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
		return nil, nil, nil
	end
	if self._pickup_child then
		local v_focus, v_x, v_y = self._show_input:PickUp(rel_x, rel_y)
		return self._show_input, v_x, v_y
	end
	if self._modal or (self._pickup_rect and self._pickup_child == false) or self._pickup_this then
		return self, rel_x, rel_y
	end
	return nil, nil, nil
end

function ALittle.ImageInput:SetCursorToHome()
	self._show_input:SetCursorToHome()
end

function ALittle.ImageInput:SetCursorToEnd()
	self._show_input:SetCursorToEnd()
end

function ALittle.ImageInput:SelectAll()
	self._show_input:SelectAll()
end

function ALittle.ImageInput:CopyText()
	self._show_input:CopyText()
end

function ALittle.ImageInput:PasteText()
	self._show_input:PasteText()
end

function ALittle.ImageInput:CutText()
	self._show_input:CutText()
end

function ALittle.ImageInput:InsertText(text)
	self._show_input:InsertText(text)
end

end