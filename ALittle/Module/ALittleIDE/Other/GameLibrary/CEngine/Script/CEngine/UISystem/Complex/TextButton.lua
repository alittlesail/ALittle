-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = GetAllStruct()


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
TextButton = Lua.Class(ALittle.DisplayLayout, "ALittle.TextButton")

function TextButton:Ctor(ctrl_sys)
	___rawset(self, "_show_text", ({}))
	self._show_text.width = 0
	self._show_text.height = 0
	self._show_text.text = ""
	self._show_text.visible = true
	___rawset(self, "_show_down_text", ({}))
	self._show_down_text.width = 0
	self._show_down_text.height = 0
	self._show_down_text.text = ""
	self._show_down_text.visible = false
	___rawset(self, "_show_over_text", ({}))
	self._show_over_text.width = 0
	self._show_over_text.height = 0
	self._show_over_text.text = ""
	self._show_over_text.visible = false
	___rawset(self, "_show_disabled_text", ({}))
	self._show_disabled_text.width = 0
	self._show_disabled_text.height = 0
	self._show_disabled_text.text = ""
	self._show_disabled_text.visible = false
	___rawset(self, "_file_select", false)
	self:AddEventListener(___all_struct[544684311], self, self.HandleMoveIn)
	self:AddEventListener(___all_struct[-1202439334], self, self.HandleMoveOut)
	self:AddEventListener(___all_struct[1883782801], self, self.HandleLButtonDown)
	self:AddEventListener(___all_struct[40651933], self, self.HandleLButtonUp)
	self:AddEventListener(___all_struct[349963892], self, self.HandleMButtonDown)
	self:AddEventListener(___all_struct[683647260], self, self.HandleMButtonUp)
	self:AddEventListener(___all_struct[292776509], self, self.ShowUp)
	self:AddEventListener(___all_struct[-1233353463], self, self.HandleFButtonDown)
	self:AddEventListener(___all_struct[734860930], self, self.HandleFButtonUp)
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", false)
end

function TextButton.__setter:disabled(value)
	DisplayObject.__setter.disabled(self, value)
	if value then
		self:ShowDisabled()
	else
		self:ShowUp(nil)
	end
end

function TextButton:HandleMoveIn(event)
	self:ShowOver()
end

function TextButton:HandleMoveOut(event)
	self:ShowUp(nil)
end

function TextButton:HandleLButtonDown(event)
	self:ShowDown()
end

function TextButton:HandleLButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local e = {}
		e.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[-449066808], e)
		if self._file_select then
			A_OtherSystem:SystemSelectFile(self)
		end
		if System_IsPhone == false then
			self:ShowOver()
		else
			self:ShowUp(nil)
		end
	else
		self:ShowUp(nil)
	end
end

function TextButton:HandleMButtonDown(event)
	self:ShowDown()
end

function TextButton:HandleMButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local e = {}
		e.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[-1330840], e)
		if System_IsPhone == false then
			self:ShowOver()
		else
			self:ShowUp(nil)
		end
	else
		self:ShowUp(nil)
	end
end

function TextButton:HandleFButtonDown(event)
	if event.is_sfc == false then
		self:ShowDown()
	end
end

function TextButton:HandleFButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local e = {}
		e.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[286797479], e)
	end
	if event.is_sfc == false then
		self:ShowUp(nil)
	end
end

function TextButton.__setter:text(value)
	self._show_text.text = value
	self._show_over_text.text = value
	self._show_disabled_text.text = value
	self._show_down_text.text = value
end

function TextButton.__getter:text()
	return self._show_text.text
end

function TextButton:ShowUp(event)
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
	self._show_text.visible = true
	self._show_down_text.visible = false
	self._show_over_text.visible = false
	self._show_disabled_text.visible = false
end

function TextButton:ShowDown()
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
	self._show_text.visible = true
	if self._show_down_text._show ~= nil then
		self._show_text.visible = false
	end
	self._show_down_text.visible = true
	self._show_over_text.visible = false
	self._show_disabled_text.visible = false
end

function TextButton:ShowOver()
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
	self._show_text.visible = true
	if self._show_over_text._show ~= nil then
		self._show_text.visible = false
	end
	self._show_down_text.visible = false
	self._show_over_text.visible = true
	self._show_disabled_text.visible = false
end

function TextButton:ShowDisabled()
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
	self._show_text.visible = true
	if self._show_disabled_text._show ~= nil then
		self._show_text.visible = false
	end
	self._show_disabled_text.visible = true
	self._show_over_text.visible = false
	self._show_down_text.visible = false
end

function TextButton.__setter:show_text(value)
	if value == nil then
		local show = self._show_text
		self:RemoveChild(show)
		self._show_text = ({})
		self._show_text.width = 0
		self._show_text.height = 0
		self._show_text.text = show.text
		self._show_text.visible = show.visible
		return
	end
	value.text = self._show_text.text
	value.visible = self._show_text.visible
	self:RemoveChild(self._show_text)
	self._show_text = value
	self._show_text.x_type = UIEnumTypes.POS_ALIGN_CENTER
	self._show_text.y_type = UIEnumTypes.POS_ALIGN_CENTER
	self:AddChild(self._show_text, 6)
end

function TextButton.__getter:show_text()
	if self._show_text._show == nil then
		return nil
	end
	return self._show_text
end

function TextButton.__setter:show_over_text(value)
	if value == nil then
		local show = self._show_over_text
		self:RemoveChild(show)
		self._show_over_text = ({})
		self._show_over_text.width = 0
		self._show_over_text.height = 0
		self._show_over_text.text = show.text
		self._show_over_text.visible = show.visible
		return
	end
	value.text = self._show_over_text.text
	value.visible = self._show_over_text.visible
	self:RemoveChild(self._show_over_text)
	self._show_over_text = value
	self._show_over_text.x_type = UIEnumTypes.POS_ALIGN_CENTER
	self._show_over_text.y_type = UIEnumTypes.POS_ALIGN_CENTER
	self:AddChild(self._show_over_text, 6)
end

function TextButton.__getter:show_over_text()
	if self._show_over_text._show == nil then
		return nil
	end
	return self._show_over_text
end

function TextButton.__setter:show_down_text(value)
	if value == nil then
		local show = self.show_down_text
		self:RemoveChild(show)
		self._show_down_text = ({})
		self._show_down_text.width = 0
		self._show_down_text.height = 0
		self._show_down_text.text = show.text
		self._show_down_text.visible = show.visible
		return
	end
	value.text = self._show_down_text.text
	value.visible = self._show_down_text.visible
	self:RemoveChild(self._show_down_text)
	self._show_down_text = value
	self._show_down_text.x_type = UIEnumTypes.POS_ALIGN_CENTER
	self._show_down_text.y_type = UIEnumTypes.POS_ALIGN_CENTER
	self:AddChild(self._show_down_text, 6)
end

function TextButton.__getter:show_down_text()
	if self._show_down_text._show == nil then
		return nil
	end
	return self._show_down_text
end

function TextButton.__setter:show_disabled_text(value)
	if value == nil then
		local show = self._show_disabled_text
		self:RemoveChild(show)
		self._show_disabled_text = ({})
		self._show_disabled_text.width = 0
		self._show_disabled_text.height = 0
		self._show_disabled_text.text = show.text
		self._show_disabled_text.visible = show.visible
		return
	end
	value.text = self._show_disabled_text.text
	value.visible = self._show_disabled_text.visible
	self:RemoveChild(self._show_disabled_text)
	self._show_disabled_text = value
	self._show_disabled_text.x_type = UIEnumTypes.POS_ALIGN_CENTER
	self._show_disabled_text.y_type = UIEnumTypes.POS_ALIGN_CENTER
	self:AddChild(self._show_disabled_text, 6)
end

function TextButton.__getter:show_disabled_text()
	if self._show_disabled_text._show == nil then
		return nil
	end
	return self._show_disabled_text
end

function TextButton.__setter:show_up(value)
	self:RemoveChild(self._show_up)
	self._show_up = value
	if self._show_up ~= nil then
		self._show_up.width_type = UIEnumTypes.SIZE_MARGIN
		self._show_up.height_type = UIEnumTypes.SIZE_MARGIN
		self._show_up.width_value = 0
		self._show_up.height_value = 0
		self:AddChild(self._show_up, 1)
	end
	if self._abs_disabled or self._disabled then
		self:ShowDisabled()
	else
		self:ShowUp(nil)
	end
end

function TextButton.__getter:show_up()
	return self._show_up
end

function TextButton.__setter:show_down(value)
	self:RemoveChild(self._show_down)
	self._show_down = value
	if self._show_down ~= nil then
		self._show_down.width_type = UIEnumTypes.SIZE_MARGIN
		self._show_down.height_type = UIEnumTypes.SIZE_MARGIN
		self._show_down.width_value = 0
		self._show_down.height_value = 0
		self:AddChild(self._show_down, 1)
	end
	if self._abs_disabled or self._disabled then
		self:ShowDisabled()
	else
		self:ShowUp(nil)
	end
end

function TextButton.__getter:show_down()
	return self._show_down
end

function TextButton.__setter:show_over(value)
	self:RemoveChild(self._show_over)
	self._show_over = value
	if self._show_over ~= nil then
		self._show_over.width_type = UIEnumTypes.SIZE_MARGIN
		self._show_over.height_type = UIEnumTypes.SIZE_MARGIN
		self._show_over.width_value = 0
		self._show_over.height_value = 0
		self:AddChild(self._show_over, 1)
	end
	if self._abs_disabled or self._disabled then
		self:ShowDisabled()
	else
		self:ShowUp(nil)
	end
end

function TextButton.__getter:show_over()
	return self._show_over
end

function TextButton.__setter:show_disabled(value)
	self:RemoveChild(self._show_disabled)
	self._show_disabled = value
	if self._show_disabled ~= nil then
		self._show_disabled.width_type = UIEnumTypes.SIZE_MARGIN
		self._show_disabled.height_type = UIEnumTypes.SIZE_MARGIN
		self._show_disabled.width_value = 0
		self._show_disabled.height_value = 0
		self:AddChild(self._show_disabled, 1)
	end
	if self._abs_disabled or self._disabled then
		self:ShowDisabled()
	else
		self:ShowUp(nil)
	end
end

function TextButton.__getter:show_disabled()
	return self._show_disabled
end

function TextButton.__setter:file_select(value)
	self._file_select = value
end

function TextButton.__getter:file_select()
	return self._file_select
end

