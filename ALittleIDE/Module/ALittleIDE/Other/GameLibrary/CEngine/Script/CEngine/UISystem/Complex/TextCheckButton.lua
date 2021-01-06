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
ALittle.TextCheckButton = Lua.Class(ALittle.DisplayLayout, "ALittle.TextCheckButton")

function ALittle.TextCheckButton:Ctor(ctrl_sys)
	___rawset(self, "_show_text", ({}))
	self._show_text.width = 0
	self._show_text.height = 0
	self._show_text.text = ""
	self._show_text.x_type = 3
	self._show_text.x_value = 0
	self._show_text.visible = true
	___rawset(self, "_show_over_text", ({}))
	self._show_over_text.width = 0
	self._show_over_text.height = 0
	self._show_over_text.text = ""
	self._show_over_text.x_type = 3
	self._show_over_text.x_value = 0
	self._show_over_text.visible = false
	___rawset(self, "_show_down_text", ({}))
	self._show_down_text.width = 0
	self._show_down_text.height = 0
	self._show_down_text.text = ""
	self._show_down_text.x_type = 3
	self._show_down_text.x_value = 0
	self._show_down_text.visible = false
	___rawset(self, "_show_disabled_text", ({}))
	self._show_disabled_text.width = 0
	self._show_disabled_text.height = 0
	self._show_disabled_text.text = ""
	self._show_disabled_text.x_type = 3
	self._show_disabled_text.x_value = 0
	self._show_disabled_text.visible = false
	___rawset(self, "_show_selected_text", ({}))
	self._show_selected_text.width = 0
	self._show_selected_text.height = 0
	self._show_selected_text.text = ""
	self._show_selected_text.x_type = 3
	self._show_selected_text.x_value = 0
	self._show_selected_text.visible = false
	___rawset(self, "_show_selected_over_text", ({}))
	self._show_selected_over_text.width = 0
	self._show_selected_over_text.height = 0
	self._show_selected_over_text.text = ""
	self._show_selected_over_text.x_type = 3
	self._show_selected_over_text.x_value = 0
	self._show_selected_over_text.visible = false
	___rawset(self, "_show_selected_down_text", ({}))
	self._show_selected_down_text.width = 0
	self._show_selected_down_text.height = 0
	self._show_selected_down_text.text = ""
	self._show_selected_down_text.x_type = 3
	self._show_selected_down_text.x_value = 0
	self._show_selected_down_text.visible = false
	___rawset(self, "_show_selected_disabled_text", ({}))
	self._show_selected_disabled_text.width = 0
	self._show_selected_disabled_text.height = 0
	self._show_selected_disabled_text.text = ""
	self._show_selected_disabled_text.x_type = 3
	self._show_selected_disabled_text.x_value = 0
	self._show_selected_disabled_text.visible = false
	___rawset(self, "_selected", false)
	self:AddEventListener(___all_struct[544684311], self, self.HandleMoveIn)
	self:AddEventListener(___all_struct[-1202439334], self, self.HandleMoveOut)
	self:AddEventListener(___all_struct[1883782801], self, self.HandleLButtonDown)
	self:AddEventListener(___all_struct[40651933], self, self.HandleLButtonUp)
	self:AddEventListener(___all_struct[349963892], self, self.HandleMButtonDown)
	self:AddEventListener(___all_struct[683647260], self, self.HandleMButtonUp)
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", false)
end

function ALittle.TextCheckButton.__setter:disabled(value)
	ALittle.DisplayObject.__setter.disabled(self, value)
	if self._abs_disabled then
		self:ShowDisabled()
	else
		self:ShowUp()
	end
end

function ALittle.TextCheckButton:HandleMoveIn(event)
	self:ShowOver()
end

function ALittle.TextCheckButton:HandleMoveOut(event)
	self:ShowUp()
end

function ALittle.TextCheckButton:HandleLButtonDown(event)
	self:ShowDown()
end

function ALittle.TextCheckButton:HandleLButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		self._selected = (self._selected == false)
		local e = {}
		e.is_drag = event.is_drag
		e.count = event.count
		self:DispatchEvent(___all_struct[-449066808], e)
		self:DispatchEvent(___all_struct[958494922], {})
		if ALittle.System_IsPhone() == false then
			self:ShowOver()
		else
			self:ShowUp()
		end
	else
		self:ShowUp()
	end
end

function ALittle.TextCheckButton:HandleMButtonDown(event)
	self:ShowDown()
end

function ALittle.TextCheckButton:HandleMButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local e = {}
		e.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[-1330840], e)
		if ALittle.System_IsPhone() == false then
			self:ShowOver()
		else
			self:ShowUp()
		end
	else
		self:ShowUp()
	end
end

function ALittle.TextCheckButton.__setter:text(value)
	self._show_text.text = value
	self._show_over_text.text = value
	self._show_down_text.text = value
	self._show_disabled_text.text = value
	self._show_selected_text.text = value
	self._show_selected_over_text.text = value
	self._show_selected_down_text.text = value
	self._show_selected_disabled_text.text = value
end

function ALittle.TextCheckButton.__getter:text()
	return self._show_text.text
end

function ALittle.TextCheckButton.__setter:text_x_type(value)
	self._show_text.x_type = value
	self._show_over_text.x_type = value
	self._show_down_text.x_type = value
	self._show_disabled_text.x_type = value
	self._show_selected_text.x_type = value
	self._show_selected_over_text.x_type = value
	self._show_selected_down_text.x_type = value
	self._show_selected_disabled_text.x_type = value
end

function ALittle.TextCheckButton.__getter:text_x_type()
	return self._show_text.x_type
end

function ALittle.TextCheckButton.__setter:text_x_value(value)
	self._show_text.x_value = value
	self._show_over_text.x_value = value
	self._show_down_text.x_value = value
	self._show_disabled_text.x_value = value
	self._show_selected_text.x_value = value
	self._show_selected_over_text.x_value = value
	self._show_selected_down_text.x_value = value
	self._show_selected_disabled_text.x_value = value
end

function ALittle.TextCheckButton.__getter:text_x_value()
	return self._show_text.x_value
end

function ALittle.TextCheckButton.__setter:selected(value)
	if self._selected == value then
		return
	end
	self._selected = value
	if self._abs_disabled then
		self:ShowDisabled()
	else
		self:ShowUp()
	end
end

function ALittle.TextCheckButton.__getter:selected()
	return self._selected
end

function ALittle.TextCheckButton:HideAllShow()
	if self._show_selected_up ~= nil then
		self._show_selected_up.alpha = 0
	end
	if self._show_selected_over ~= nil then
		self._show_selected_over.alpha = 0
	end
	if self._show_selected_down ~= nil then
		self._show_selected_down.alpha = 0
	end
	if self._show_selected_disabled ~= nil then
		self._show_selected_disabled.alpha = 0
	end
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
		self._show_disabled.alpha = 0
	end
end

function ALittle.TextCheckButton:ShowUp()
	if self._abs_disabled or self._disabled then
		return
	end
	self:HideAllShow()
	if self._selected then
		if self._show_selected_up ~= nil then
			self._show_selected_up.alpha = 1
		end
		if self._show_up ~= nil then
			self._show_up.alpha = 0
		end
	else
		if self._show_selected_up ~= nil then
			self._show_selected_up.alpha = 0
		end
		if self._show_up ~= nil then
			self._show_up.alpha = 1
		end
	end
	if self._selected then
		self._show_text.visible = true
		self._show_down_text.visible = false
		self._show_over_text.visible = false
		self._show_disabled_text.visible = false
		if self._show_selected_text._show ~= nil then
			self._show_text.visible = false
		end
		self._show_selected_text.visible = true
		self._show_selected_down_text.visible = false
		self._show_selected_over_text.visible = false
		self._show_selected_disabled_text.visible = false
	else
		self._show_text.visible = true
		self._show_down_text.visible = false
		self._show_over_text.visible = false
		self._show_disabled_text.visible = false
		self._show_selected_text.visible = false
		self._show_selected_down_text.visible = false
		self._show_selected_over_text.visible = false
		self._show_selected_disabled_text.visible = false
	end
end

function ALittle.TextCheckButton:ShowDown()
	if self._abs_disabled or self._disabled then
		return
	end
	self:HideAllShow()
	if self._selected then
		if self._show_selected_down ~= nil then
			self._show_selected_down.alpha = 1
		end
		if self._show_down ~= nil then
			self._show_down.alpha = 0
		end
	else
		if self._show_selected_down ~= nil then
			self._show_selected_down.alpha = 0
		end
		if self._show_down ~= nil then
			self._show_down.alpha = 1
		end
	end
	if self._selected then
		self._show_text.visible = true
		self._show_down_text.visible = false
		self._show_over_text.visible = false
		self._show_disabled_text.visible = false
		self._show_selected_text.visible = false
		if self._show_selected_down_text._show ~= nil then
			self._show_text.visible = false
		end
		self._show_selected_down_text.visible = true
		self._show_selected_over_text.visible = false
		self._show_selected_disabled_text.visible = false
	else
		self._show_text.visible = true
		if self._show_down_text._show ~= nil then
			self._show_text.visible = false
		end
		self._show_down_text.visible = true
		self._show_over_text.visible = false
		self._show_disabled_text.visible = false
		self._show_selected_text.visible = false
		self._show_selected_down_text.visible = false
		self._show_selected_over_text.visible = false
		self._show_selected_disabled_text.visible = false
	end
end

function ALittle.TextCheckButton:ShowOver()
	if self._abs_disabled or self._disabled then
		return
	end
	self:HideAllShow()
	if self._selected then
		if self._show_selected_over ~= nil then
			self._show_selected_over.alpha = 1
		end
		if self._show_over ~= nil then
			self._show_over.alpha = 0
		end
	else
		if self._show_selected_over ~= nil then
			self._show_selected_over.alpha = 0
		end
		if self._show_over ~= nil then
			self._show_over.alpha = 1
		end
	end
	if self._selected then
		self._show_text.visible = true
		self._show_down_text.visible = false
		self._show_over_text.visible = false
		self._show_disabled_text.visible = false
		self._show_selected_text.visible = false
		self._show_selected_down_text.visible = false
		if self._show_selected_over_text._show ~= nil then
			self._show_text.visible = false
		end
		self._show_selected_over_text.visible = true
		self._show_selected_disabled_text.visible = false
	else
		self._show_text.visible = true
		self._show_down_text.visible = false
		if self._show_over_text._show ~= nil then
			self._show_text.visible = false
		end
		self._show_over_text.visible = true
		self._show_disabled_text.visible = false
		self._show_selected_text.visible = false
		self._show_selected_down_text.visible = false
		self._show_selected_over_text.visible = false
		self._show_selected_disabled_text.visible = false
	end
end

function ALittle.TextCheckButton:ShowDisabled()
	self:HideAllShow()
	if self._selected then
		if self._show_selected_disabled ~= nil then
			self._show_selected_disabled.alpha = 1
		end
		if self._show_disabled ~= nil then
			self._show_disabled.alpha = 0
		end
	else
		if self._show_selected_disabled ~= nil then
			self._show_selected_disabled.alpha = 0
		end
		if self._show_disabled ~= nil then
			self._show_disabled.alpha = 1
		end
	end
	if self._selected then
		self._show_text.visible = true
		self._show_down_text.visible = false
		self._show_over_text.visible = false
		self._show_disabled_text.visible = false
		self._show_selected_text.visible = false
		self._show_selected_down_text.visible = false
		self._show_selected_over_text.visible = false
		if self._show_selected_disabled_text._show ~= nil then
			self._show_text.visible = false
		end
		self._show_selected_disabled_text.visible = true
	else
		self._show_text.visible = true
		self._show_down_text.visible = false
		self._show_over_text.visible = false
		if self._show_disabled_text._show ~= nil then
			self._show_text.visible = false
		end
		self._show_disabled_text.visible = true
		self._show_selected_text.visible = false
		self._show_selected_down_text.visible = false
		self._show_selected_over_text.visible = false
		self._show_selected_disabled_text.visible = false
	end
end

function ALittle.TextCheckButton.__setter:show_text(value)
	if value == nil then
		local show = self._show_text
		self:RemoveChild(show)
		self._show_text = ({})
		self._show_text.width = 0
		self._show_text.height = 0
		self._show_text.text = show.text
		self._show_text.visible = show.visible
		self._show_text.x_type = show.x_type
		self._show_text.x_value = show.x_value
		return
	end
	if self._show_text ~= nil and self._show_text.text ~= "" then
		value.text = self._show_text.text
	end
	value.visible = self._show_text.visible
	value.x_type = self._show_text.x_type
	value.x_value = self._show_text.x_value
	self:RemoveChild(self._show_text)
	self._show_text = value
	self._show_text.y_type = 3
	self:AddChild(self._show_text, 10)
end

function ALittle.TextCheckButton.__getter:show_text()
	if self._show_text._show == nil then
		return nil
	end
	return self._show_text
end

function ALittle.TextCheckButton.__setter:show_over_text(value)
	if value == nil then
		local show = self._show_over_text
		self:RemoveChild(show)
		self._show_over_text = ({})
		self._show_over_text.width = 0
		self._show_over_text.height = 0
		self._show_over_text.text = show.text
		self._show_over_text.visible = show.visible
		self._show_over_text.x_type = show.x_type
		self._show_over_text.x_value = show.x_value
		return
	end
	if self._show_over_text ~= nil and self._show_over_text.text ~= "" then
		value.text = self._show_over_text.text
	end
	value.visible = self._show_over_text.visible
	value.x_type = self._show_over_text.x_type
	value.x_value = self._show_over_text.x_value
	self:RemoveChild(self._show_over_text)
	self._show_over_text = value
	self._show_over_text.y_type = 3
	self:AddChild(self._show_over_text, 10)
end

function ALittle.TextCheckButton.__getter:show_over_text()
	if self._show_over_text._show == nil then
		return nil
	end
	return self._show_over_text
end

function ALittle.TextCheckButton.__setter:show_down_text(value)
	if value == nil then
		local show = self._show_down_text
		self:RemoveChild(show)
		self._show_down_text = ({})
		self._show_down_text.width = 0
		self._show_down_text.height = 0
		self._show_down_text.text = show.text
		self._show_down_text.visible = show.visible
		self._show_down_text.x_type = show.x_type
		self._show_down_text.x_value = show.x_value
		return
	end
	if self._show_down_text ~= nil and self._show_down_text.text ~= "" then
		value.text = self._show_down_text.text
	end
	value.visible = self._show_down_text.visible
	value.x_type = self._show_down_text.x_type
	value.x_value = self._show_down_text.x_value
	self:RemoveChild(self._show_down_text)
	self._show_down_text = value
	self._show_down_text.y_type = 3
	self:AddChild(self._show_down_text, 10)
end

function ALittle.TextCheckButton.__getter:show_down_text()
	if self._show_down_text._show == nil then
		return nil
	end
	return self._show_down_text
end

function ALittle.TextCheckButton.__setter:show_disabled_text(value)
	if value == nil then
		local show = self._show_disabled_text
		self:RemoveChild(show)
		self._show_disabled_text = ({})
		self._show_disabled_text.width = 0
		self._show_disabled_text.height = 0
		self._show_disabled_text.text = show.text
		self._show_disabled_text.visible = show.visible
		self._show_disabled_text.x_type = show.x_type
		self._show_disabled_text.x_value = show.x_value
		return
	end
	if self._show_disabled_text ~= nil and self._show_disabled_text.text ~= "" then
		value.text = self._show_disabled_text.text
	end
	value.visible = self._show_disabled_text.visible
	value.x_type = self._show_disabled_text.x_type
	value.x_value = self._show_disabled_text.x_value
	self:RemoveChild(self._show_disabled_text)
	self._show_disabled_text = value
	self._show_disabled_text.y_type = 3
	self:AddChild(self._show_disabled_text, 10)
end

function ALittle.TextCheckButton.__getter:show_disabled_text()
	if self._show_disabled_text._show == nil then
		return nil
	end
	return self._show_disabled_text
end

function ALittle.TextCheckButton.__setter:show_selected_text(value)
	if value == nil then
		local show = self._show_selected_text
		self:RemoveChild(show)
		self._show_selected_text = ({})
		self._show_selected_text.width = 0
		self._show_selected_text.height = 0
		self._show_selected_text.text = show.text
		self._show_selected_text.visible = show.visible
		self._show_selected_text.x_type = show.x_type
		self._show_selected_text.x_value = show.x_value
		return
	end
	if self._show_selected_text ~= nil and self._show_selected_text.text ~= "" then
		value.text = self._show_selected_text.text
	end
	value.visible = self._show_selected_text.visible
	value.x_type = self._show_selected_text.x_type
	value.x_value = self._show_selected_text.x_value
	self:RemoveChild(self._show_selected_text)
	self._show_selected_text = value
	self._show_selected_text.y_type = 3
	self:AddChild(self._show_selected_text, 10)
end

function ALittle.TextCheckButton.__getter:show_selected_text()
	if self._show_selected_text._show == nil then
		return nil
	end
	return self._show_selected_text
end

function ALittle.TextCheckButton.__setter:show_selected_over_text(value)
	if value == nil then
		local show = self._show_selected_over_text
		self:RemoveChild(show)
		self._show_selected_over_text = ({})
		self._show_selected_over_text.width = 0
		self._show_selected_over_text.height = 0
		self._show_selected_over_text.text = show.text
		self._show_selected_over_text.visible = show.visible
		self._show_selected_over_text.x_type = show.x_type
		self._show_selected_over_text.x_value = show.x_value
		return
	end
	if self._show_selected_over_text ~= nil and self._show_selected_over_text.text ~= "" then
		value.text = self._show_selected_over_text.text
	end
	value.visible = self._show_selected_over_text.visible
	value.x_type = self._show_selected_over_text.x_type
	value.x_value = self._show_selected_over_text.x_value
	self:RemoveChild(self._show_selected_over_text)
	self._show_selected_over_text = value
	self._show_selected_over_text.y_type = 3
	self:AddChild(self._show_selected_over_text, 10)
end

function ALittle.TextCheckButton.__getter:show_selected_over_text()
	if self._show_selected_over_text._show == nil then
		return nil
	end
	return self._show_selected_over_text
end

function ALittle.TextCheckButton.__setter:show_selected_down_text(value)
	if value == nil then
		local show = self._show_selected_down_text
		self:RemoveChild(show)
		self._show_selected_down_text = ({})
		self._show_selected_down_text.width = 0
		self._show_selected_down_text.height = 0
		self._show_selected_down_text.text = show.text
		self._show_selected_down_text.visible = show.visible
		self._show_selected_down_text.x_type = show.x_type
		self._show_selected_down_text.x_value = show.x_value
		return
	end
	if self._show_selected_down_text ~= nil and self._show_selected_down_text.text ~= "" then
		value.text = self._show_selected_down_text.text
	end
	value.visible = self._show_selected_down_text.visible
	value.x_type = self._show_selected_down_text.x_type
	value.x_value = self._show_selected_down_text.x_value
	self:RemoveChild(self._show_selected_down_text)
	self._show_selected_down_text = value
	self._show_selected_down_text.y_type = 3
	self:AddChild(self._show_selected_down_text, 10)
end

function ALittle.TextCheckButton.__getter:show_selected_down_text()
	if self._show_selected_down_text._show == nil then
		return nil
	end
	return self._show_selected_down_text
end

function ALittle.TextCheckButton.__setter:show_selected_disabled_text(value)
	if value == nil then
		local show = self._show_selected_disabled_text
		self:RemoveChild(show)
		self._show_selected_disabled_text = ({})
		self._show_selected_disabled_text.width = 0
		self._show_selected_disabled_text.height = 0
		self._show_selected_disabled_text.text = show.text
		self._show_selected_disabled_text.visible = show.visible
		self._show_selected_disabled_text.x_type = show.x_type
		self._show_selected_disabled_text.x_value = show.x_value
		return
	end
	if self._show_selected_disabled_text ~= nil and self._show_selected_disabled_text.text ~= "" then
		value.text = self._show_selected_disabled_text.text
	end
	value.visible = self._show_selected_disabled_text.visible
	value.x_type = self._show_selected_disabled_text.x_type
	value.x_value = self._show_selected_disabled_text.x_value
	self:RemoveChild(self._show_selected_disabled_text)
	self._show_selected_disabled_text = value
	self._show_selected_disabled_text.y_type = 3
	self:AddChild(self._show_selected_disabled_text, 10)
end

function ALittle.TextCheckButton.__getter:show_selected_disabled_text()
	if self._show_selected_disabled_text._show == nil then
		return nil
	end
	return self._show_selected_disabled_text
end

function ALittle.TextCheckButton.__setter:show_up(value)
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

function ALittle.TextCheckButton.__getter:show_up()
	return self._show_up
end

function ALittle.TextCheckButton.__setter:show_down(value)
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

function ALittle.TextCheckButton.__getter:show_down()
	return self._show_down
end

function ALittle.TextCheckButton.__setter:show_over(value)
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

function ALittle.TextCheckButton.__getter:show_over()
	return self._show_over
end

function ALittle.TextCheckButton.__setter:show_disabled(value)
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

function ALittle.TextCheckButton.__getter:show_disabled()
	return self._show_disabled
end

function ALittle.TextCheckButton.__setter:show_selected_up(value)
	self:RemoveChild(self._show_selected_up)
	self._show_selected_up = value
	if self._show_selected_up ~= nil then
		self._show_selected_up.width_type = 4
		self._show_selected_up.height_type = 4
		self._show_selected_up.width_value = 0
		self._show_selected_up.height_value = 0
		self:AddChild(self._show_selected_up, 1)
	end
	self:ShowUp()
end

function ALittle.TextCheckButton.__getter:show_selected_up()
	return self._show_selected_up
end

function ALittle.TextCheckButton.__setter:show_selected_down(value)
	self:RemoveChild(self._show_selected_down)
	self._show_selected_down = value
	if self._show_selected_down ~= nil then
		self._show_selected_down.width_type = 4
		self._show_selected_down.height_type = 4
		self._show_selected_down.width_value = 0
		self._show_selected_down.height_value = 0
		self:AddChild(self._show_selected_down, 1)
	end
	self:ShowUp()
end

function ALittle.TextCheckButton.__getter:show_selected_down()
	return self._show_selected_down
end

function ALittle.TextCheckButton.__setter:show_selected_over(value)
	self:RemoveChild(self._show_selected_over)
	self._show_selected_over = value
	if self._show_selected_over ~= nil then
		self._show_selected_over.width_type = 4
		self._show_selected_over.height_type = 4
		self._show_selected_over.width_value = 0
		self._show_selected_over.height_value = 0
		self:AddChild(self._show_selected_over, 1)
	end
	self:ShowUp()
end

function ALittle.TextCheckButton.__getter:show_selected_over()
	return self._show_selected_over
end

function ALittle.TextCheckButton.__setter:show_selected_disabled(value)
	self:RemoveChild(self._show_selected_disabled)
	self._show_selected_disabled = value
	if self._show_selected_disabled ~= nil then
		self._show_selected_disabled.width_type = 4
		self._show_selected_disabled.height_type = 4
		self._show_selected_disabled.width_value = 0
		self._show_selected_disabled.height_value = 0
		self:AddChild(self._show_selected_disabled, 1)
	end
	self:ShowUp()
end

function ALittle.TextCheckButton.__getter:show_selected_disabled()
	return self._show_selected_disabled
end

end