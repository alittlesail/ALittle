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
ALittle.ImageEdit = Lua.Class(ALittle.DisplayLayout, "ALittle.ImageEdit")

function ALittle.ImageEdit:Ctor(ctrl_sys)
	___rawset(self, "_show_edit", ALittle.TextEdit(self._ctrl_sys))
	self._show_edit.x_type = 2
	self._show_edit.y_type = 2
	self._show_edit.width_type = 4
	self._show_edit.width_value = 0
	self._show_edit.height_type = 4
	self._show_edit.height_value = 0
	self:AddChild(self._show_edit, 5)
	___rawset(self, "_logic_left", 0)
	___rawset(self, "_logic_right", 0)
	___rawset(self, "_logic_top", 0)
	___rawset(self, "_logic_bottom", 0)
	self._show_edit:AddEventListener(___all_struct[-644464135], self, self.HandleFocusIn)
	self._show_edit:AddEventListener(___all_struct[292776509], self, self.HandleFocusOut)
	self._show_edit:AddEventListener(___all_struct[544684311], self, self.HandleMoveIn)
	self._show_edit:AddEventListener(___all_struct[-1202439334], self, self.HandleMoveOut)
	self._show_edit:AddEventListener(___all_struct[1883782801], self, self.HandleImageEditTransformLButtonDown)
	self._show_edit:AddEventListener(___all_struct[-1234078962], self, self.HandleImageEditTransformTextInput)
	self._show_edit:AddEventListener(___all_struct[-1604617962], self, self.HandleImageEditTransformKeyDown)
	self._show_edit:AddEventListener(___all_struct[1301789264], self, self.HandleImageEditTransformDragBegin)
	self._show_edit:AddEventListener(___all_struct[1337289812], self, self.HandleImageEditTransformDrag)
	self._show_edit:AddEventListener(___all_struct[150587926], self, self.HandleImageEditTransformDragEnd)
	self._show_edit:AddEventListener(___all_struct[-1737121315], self, self.HandleImageEditTransformMButtonWheel)
	self._show_edit:AddEventListener(___all_struct[958494922], self, self.HandleImageEditTransformChangd)
	self._show_edit:AddEventListener(___all_struct[776398171], self, self.HandleImageEditTransformEnterKey)
	self._show_edit:AddEventListener(___all_struct[2024735182], self, self.HandleImageEditTransformTabKey)
	self._show_edit:AddEventListener(___all_struct[-641444818], self, self.HandleImageEditTransformRButtonDown)
	self._show_edit:AddEventListener(___all_struct[-569321214], self, self.HandleImageEditTransformRButtonUp)
	self._show_edit:AddEventListener(___all_struct[-439548260], self, self.HandleImageEditTransformLongButtonDown)
end

function ALittle.ImageEdit.__setter:disabled(value)
	ALittle.DisplayObject.__setter.disabled(self, value)
	if value then
		self:ShowDisabled()
	else
		self:ShowUp()
	end
end

function ALittle.ImageEdit.__getter:is_focus()
	return A_UISystem.focus == self._show_edit
end

function ALittle.ImageEdit.__setter:focus(value)
	if value then
		A_UISystem.focus = self._show_edit
	else
		if A_UISystem.focus == self._show_edit then
			A_UISystem.focus = nil
		end
	end
end

function ALittle.ImageEdit.__getter:is_input()
	return true
end

function ALittle.ImageEdit.__getter:show_edit()
	return self._show_edit
end

function ALittle.ImageEdit.__getter:cursor_x()
	return self._show_edit.cursor_x
end

function ALittle.ImageEdit.__getter:cursor_y()
	return self._show_edit.cursor_y
end

function ALittle.ImageEdit.__setter:editable(value)
	self._show_edit.editable = value
end

function ALittle.ImageEdit.__getter:editable()
	return self._show_edit.editable
end

function ALittle.ImageEdit.__setter:font_path(value)
	self._show_edit.font_path = value
end

function ALittle.ImageEdit.__setter:font_size(value)
	self._show_edit.font_size = value
end

function ALittle.ImageEdit.__getter:font_path()
	return self._show_edit.font_path
end

function ALittle.ImageEdit.__getter:font_size()
	return self._show_edit.font_size
end

function ALittle.ImageEdit.__getter:regex()
	return self._show_edit.regex
end

function ALittle.ImageEdit.__setter:regex(value)
	if value == nil then
		value = ""
	end
	self._show_edit.regex = value
end

function ALittle.ImageEdit.__getter:limit_len()
	return self._show_edit.limit_len
end

function ALittle.ImageEdit.__setter:limit_len(value)
	if value == nil then
		value = 0
	end
	self._show_edit.limit_len = value
end

function ALittle.ImageEdit.__setter:text(value)
	self._show_edit.text = value
end

function ALittle.ImageEdit.__getter:text()
	return self._show_edit.text
end

function ALittle.ImageEdit.__setter:bold(value)
	self._show_edit.bold = value
end

function ALittle.ImageEdit.__getter:bold()
	return self._show_edit.bold
end

function ALittle.ImageEdit.__setter:italic(value)
	self._show_edit.italic = value
end

function ALittle.ImageEdit.__getter:italic()
	return self._show_edit.italic
end

function ALittle.ImageEdit.__setter:underline(value)
	self._show_edit.underline = value
end

function ALittle.ImageEdit.__getter:underline()
	return self._show_edit.underline
end

function ALittle.ImageEdit.__setter:deleteline(value)
	self._show_edit.deleteline = value
end

function ALittle.ImageEdit.__getter:deleteline()
	return self._show_edit.deleteline
end

function ALittle.ImageEdit.__setter:cursor_red(value)
	self._show_edit.cursor_red = value
end

function ALittle.ImageEdit.__getter:cursor_red()
	return self._show_edit.cursor_red
end

function ALittle.ImageEdit.__setter:cursor_green(value)
	self._show_edit.cursor_green = value
end

function ALittle.ImageEdit.__getter:cursor_green()
	return self._show_edit.cursor_green
end

function ALittle.ImageEdit.__setter:cursor_blue(value)
	self._show_edit.cursor_blue = value
end

function ALittle.ImageEdit.__getter:cursor_blue()
	return self._show_edit.cursor_blue
end

function ALittle.ImageEdit.__setter:red(value)
	self._show_edit.red = value
end

function ALittle.ImageEdit.__getter:red()
	return self._show_edit.red
end

function ALittle.ImageEdit.__setter:green(value)
	self._show_edit.green = value
end

function ALittle.ImageEdit.__getter:green()
	return self._show_edit.green
end

function ALittle.ImageEdit.__setter:blue(value)
	self._show_edit.blue = value
end

function ALittle.ImageEdit.__getter:blue()
	return self._show_edit.blue
end

function ALittle.ImageEdit.__setter:ims_padding(value)
	self._show_edit.ims_padding = value
end

function ALittle.ImageEdit.__getter:ims_padding()
	return self._show_edit.ims_padding
end

function ALittle.ImageEdit:HandleFocusIn(event)
	event.target = self
	self:DispatchEvent(___all_struct[-644464135], event)
	self:ShowDown()
end

function ALittle.ImageEdit:HandleFocusOut(event)
	event.target = self
	self:DispatchEvent(___all_struct[292776509], event)
	self:ShowUp()
end

function ALittle.ImageEdit:HandleImageEditTransformLButtonDown(event)
	event.target = self
	self:DispatchEvent(___all_struct[1883782801], event)
end

function ALittle.ImageEdit:HandleImageEditTransformTextInput(event)
	event.target = self
	self:DispatchEvent(___all_struct[-1234078962], event)
end

function ALittle.ImageEdit:HandleImageEditTransformKeyDown(event)
	event.target = self
	self:DispatchEvent(___all_struct[-1604617962], event)
end

function ALittle.ImageEdit:HandleImageEditTransformDragBegin(event)
	event.target = self
	self:DispatchEvent(___all_struct[1301789264], event)
end

function ALittle.ImageEdit:HandleImageEditTransformDrag(event)
	event.target = self
	self:DispatchEvent(___all_struct[1337289812], event)
end

function ALittle.ImageEdit:HandleImageEditTransformDragEnd(event)
	event.target = self
	self:DispatchEvent(___all_struct[150587926], event)
end

function ALittle.ImageEdit:HandleImageEditTransformMButtonWheel(event)
	event.target = self
	self:DispatchEvent(___all_struct[-1737121315], event)
end

function ALittle.ImageEdit:HandleImageEditTransformChangd(event)
	event.target = self
	self:DispatchEvent(___all_struct[958494922], event)
end

function ALittle.ImageEdit:HandleImageEditTransformEnterKey(event)
	event.target = self
	self:DispatchEvent(___all_struct[776398171], event)
end

function ALittle.ImageEdit:HandleImageEditTransformTabKey(event)
	event.target = self
	self:DispatchEvent(___all_struct[2024735182], event)
end

function ALittle.ImageEdit:HandleImageEditTransformRButtonDown(event)
	event.target = self
	self:DispatchEvent(___all_struct[-641444818], event)
end

function ALittle.ImageEdit:HandleImageEditTransformRButtonUp(event)
	event.target = self
	self:DispatchEvent(___all_struct[-569321214], event)
end

function ALittle.ImageEdit:HandleImageEditTransformLongButtonDown(event)
	event.target = self
	self:DispatchEvent(___all_struct[-439548260], event)
end

function ALittle.ImageEdit:HandleMoveIn(event)
	event.target = self
	self:DispatchEvent(___all_struct[544684311], event)
	if A_UISystem.focus ~= self._show_edit then
		self:ShowOver()
	end
end

function ALittle.ImageEdit:HandleMoveOut(event)
	event.target = self
	self:DispatchEvent(___all_struct[-1202439334], event)
	if A_UISystem.focus ~= self._show_edit then
		self:ShowUp()
	end
end

function ALittle.ImageEdit:ShowUp()
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

function ALittle.ImageEdit:ShowDown()
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

function ALittle.ImageEdit:ShowOver()
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

function ALittle.ImageEdit:ShowDisabled()
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

function ALittle.ImageEdit.__setter:show_up(value)
	self:RemoveChild(self._show_up)
	self._show_up = value
	if self._show_up ~= nil then
		self._show_up.width_type = 4
		self._show_up.height_type = 4
		self._show_up.width_value = 0
		self._show_up.height_value = 0
		self:AddChild(self._show_up, 1)
	end
	self:ShowUp()
end

function ALittle.ImageEdit.__getter:show_up()
	return self._show_up
end

function ALittle.ImageEdit.__setter:show_down(value)
	self:RemoveChild(self._show_down)
	self._show_down = value
	if self._show_down ~= nil then
		self._show_down.width_type = 4
		self._show_down.height_type = 4
		self._show_down.width_value = 0
		self._show_down.height_value = 0
		self:AddChild(self._show_down, 1)
	end
	self:ShowUp()
end

function ALittle.ImageEdit.__getter:show_down()
	return self._show_down
end

function ALittle.ImageEdit.__setter:show_over(value)
	self:RemoveChild(self._show_over)
	self._show_over = value
	if self._show_over ~= nil then
		self._show_over.width_type = 4
		self._show_over.height_type = 4
		self._show_over.width_value = 0
		self._show_over.height_value = 0
		self:AddChild(self._show_over, 1)
	end
	self:ShowUp()
end

function ALittle.ImageEdit.__getter:show_over()
	return self._show_over
end

function ALittle.ImageEdit.__setter:show_disabled(value)
	self:RemoveChild(self._show_disabled)
	self._show_disabled = value
	if self._show_disabled ~= nil then
		self._show_disabled.width_type = 4
		self._show_disabled.height_type = 4
		self._show_disabled.width_value = 0
		self._show_disabled.height_value = 0
		self:AddChild(self._show_disabled, 1)
	end
	self:ShowUp()
end

function ALittle.ImageEdit.__getter:show_disabled()
	return self._show_disabled
end

function ALittle.ImageEdit.__setter:margin_left(value)
	self._logic_left = value
	self:Layout()
end

function ALittle.ImageEdit.__getter:margin_left()
	return self._logic_left
end

function ALittle.ImageEdit.__setter:margin_right(value)
	self._logic_right = value
	self:Layout()
end

function ALittle.ImageEdit.__getter:margin_right()
	return self._logic_right
end

function ALittle.ImageEdit.__setter:margin_top(value)
	self._logic_top = value
	self:Layout()
end

function ALittle.ImageEdit.__getter:margin_top()
	return self._logic_top
end

function ALittle.ImageEdit.__setter:margin_bottom(value)
	self._logic_bottom = value
	self:Layout()
end

function ALittle.ImageEdit.__getter:margin_bottom()
	return self._logic_bottom
end

function ALittle.ImageEdit:Layout()
	self:SetChildIndex(self._show_edit, 5)
	self._show_edit.x_value = self._logic_left
	self._show_edit.y_value = self._logic_top
	self._show_edit.width_value = self._logic_left + self._logic_right
	self._show_edit.height_value = self._logic_top + self._logic_bottom
end

function ALittle.ImageEdit:PickUp(x, y)
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
		local v_focus, v_x, v_y = self._show_edit:PickUp(rel_x, rel_y)
		return self._show_edit, v_x, v_y
	end
	if self._modal or (self._pickup_rect and self._pickup_child == false) or self._pickup_this then
		return self, rel_x, rel_y
	end
	return nil, nil, nil
end

function ALittle.ImageEdit:SetCursorToHome()
	self._show_edit:SetCursorToHome()
end

function ALittle.ImageEdit:SetCursorToEnd()
	self._show_edit:SetCursorToEnd()
end

function ALittle.ImageEdit:SelectAll()
	self._show_edit:SelectAll()
end

function ALittle.ImageEdit:CopyText()
	self._show_edit:CopyText()
end

function ALittle.ImageEdit:PasteText()
	self._show_edit:PasteText()
end

function ALittle.ImageEdit:CutText()
	self._show_edit:CutText()
end

function ALittle.ImageEdit:InsertText(value)
	self._show_edit:InsertText(value)
end

end