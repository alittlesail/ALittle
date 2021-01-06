-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


assert(ALittle.TextCheckButton, " extends class:ALittle.TextCheckButton is nil")
ALittle.DropDown = Lua.Class(ALittle.TextCheckButton, "ALittle.DropDown")

function ALittle.DropDown:Ctor(ctrl_sys)
	___rawset(self, "_body", ALittle.DisplayLayout(self._ctrl_sys))
	self._body.__right_data = self
	self._body.visible = false
	___rawset(self, "_linear", ALittle.Linear(self._ctrl_sys))
	self._linear.type = 2
	self._linear.width_type = 4
	self._linear.width_value = 0
	self._linear.height_type = 4
	self._linear.height_value = 0
	___rawset(self, "_scroll_screen", ALittle.ScrollScreen(self._ctrl_sys))
	self._scroll_screen.width_type = 4
	self._scroll_screen.width_value = 0
	self._scroll_screen.height_type = 4
	self._scroll_screen.height_value = 0
	self._scroll_screen.container = self._linear
	self._body:AddChild(self._scroll_screen)
	___rawset(self, "_body_margin", 0)
	___rawset(self, "_screen_margin_left", 0)
	___rawset(self, "_screen_margin_right", 0)
	___rawset(self, "_screen_margin_top", 0)
	___rawset(self, "_screen_margin_bottom", 0)
	___rawset(self, "_show_count", 0)
	self:AddEventListener(___all_struct[958494922], self, self.HandleButtonChange)
	self._body:AddEventListener(___all_struct[348388800], self, self.HandleBodyHide)
end

function ALittle.DropDown.__setter:show_background(value)
	if self._background == value then
		return
	end
	self._body:RemoveChild(self._background)
	self._background = value
	if self._background ~= nil then
		self._background.width_type = 4
		self._background.height_type = 4
		self._background.width_value = 0
		self._background.height_value = 0
		self._body:AddChild(self._background, 0)
	end
end

function ALittle.DropDown.__getter:show_background()
	return self._background
end

function ALittle.DropDown.__setter:show_scrollbar(value)
	if self._scrollbar == value then
		return
	end
	self._scrollbar = value
	if self._scrollbar == nil then
		self._scroll_screen.right_scrollbar = nil
	end
	self:Layout()
end

function ALittle.DropDown.__getter:show_scrollbar()
	return self._scrollbar
end

function ALittle.DropDown.__setter:show_count(value)
	if self._show_count == value then
		return
	end
	self._show_count = value
	self:Layout()
end

function ALittle.DropDown.__getter:show_count()
	return self._show_count
end

function ALittle.DropDown.__setter:button_style(value)
	if self._button_style == value then
		return
	end
	local child_list = self._scroll_screen.childs
	for k, v in ___ipairs(child_list) do
		v:RemoveEventListener(___all_struct[-449066808], self, self.HandleItemButtonClick)
	end
	self._scroll_screen:RemoveAllChild()
	self._button_style = value
	local button = nil
	if self._button_style ~= nil and self._data_list ~= nil then
		for k, v in ___ipairs(self._data_list) do
			button = self._ctrl_sys:CreateControl(self._button_style, nil, self._scroll_screen)
			button:AddEventListener(___all_struct[-449066808], self, self.HandleItemButtonClick)
			button.text = v
			button.drag_trans_target = self._scroll_screen
		end
	end
	if self._show_count == 0 or self._show_count >= self._linear.child_count then
		self._body.height = self._linear.height + self._screen_margin_top + self._screen_margin_bottom
	elseif button ~= nil then
		self._body.height = button.height * self._show_count + self._screen_margin_top + self._screen_margin_bottom
	else
		self._body.height = 0
	end
end

function ALittle.DropDown.__getter:button_style()
	return self._button_style
end

function ALittle.DropDown.__setter:body_margin(value)
	self._body_margin = value
end

function ALittle.DropDown.__getter:body_margin()
	return self._body_margin
end

function ALittle.DropDown.__setter:screen_margin_left(value)
	self._screen_margin_left = value
end

function ALittle.DropDown.__getter:screen_margin_left()
	return self._screen_margin_left
end

function ALittle.DropDown.__setter:screen_margin_right(value)
	self._screen_margin_right = value
end

function ALittle.DropDown.__getter:screen_margin_right()
	return self._screen_margin_right
end

function ALittle.DropDown.__setter:screen_margin_top(value)
	self._screen_margin_top = value
end

function ALittle.DropDown.__getter:screen_margin_top()
	return self._screen_margin_top
end

function ALittle.DropDown.__setter:screen_margin_bottom(value)
	self._screen_margin_bottom = value
end

function ALittle.DropDown.__getter:screen_margin_bottom()
	return self._screen_margin_bottom
end

function ALittle.DropDown.__setter:data_list(value)
	if value == nil then
		value = {}
	end
	local button_style = self._button_style
	self._button_style = nil
	self._data_list = value
	self.button_style = button_style
	if ALittle.List_Len(value) > 0 then
		self.text = value[1]
	else
		self.text = ""
	end
	self:Layout()
end

function ALittle.DropDown.__getter:data_list()
	return self._data_list
end

function ALittle.DropDown:HandleItemButtonClick(event)
	A_LayerManager:HideFromRight(self._body)
	if self.text == event.target.text then
		return
	end
	self.text = event.target.text
	self:DispatchEvent(___all_struct[444989011], {})
end

function ALittle.DropDown:HandleButtonChange(event)
	if event.target.selected == false then
		A_LayerManager:HideFromRight(self._body)
	else
		local abs_x, abs_y = self:LocalToGlobal()
		local adjust_y = abs_y + self.height * self.scale_y
		if A_UISystem.view_height < adjust_y + self._scroll_screen.height * self.scale_y then
			adjust_y = abs_y - self._scroll_screen.height * self.scale_y
		end
		self._body.y = adjust_y
		self._body.width = self.width - self._body_margin
		self._body.x = abs_x + self._body_margin / 2
		self._body.scale_x = self.scale_x
		self._body.scale_y = self.scale_y
		self._scroll_screen.x = self._screen_margin_left
		self._scroll_screen.y = self._screen_margin_top
		self._scroll_screen.width_value = self._screen_margin_left + self._screen_margin_right
		self._scroll_screen.height_value = self._screen_margin_top + self._screen_margin_bottom
		A_LayerManager:ShowFromRight(self._body)
		A_UISystem.focus = self._scroll_screen
	end
end

function ALittle.DropDown:HandleBodyHide(event)
	if self.selected == false then
		return
	end
	self.selected = false
end

function ALittle.DropDown:Layout()
	if self._show_count == 0 or self._scrollbar == nil or self._show_count >= self._linear.child_count then
		self._scroll_screen.right_scrollbar = nil
		self._body.height = self._linear.height + self._screen_margin_top + self._screen_margin_bottom
	else
		self._scroll_screen.right_scrollbar = self._scrollbar
		local button = self._linear.childs[1]
		if button ~= nil then
			self._body.height = button.height * self._show_count + self._screen_margin_top + self._screen_margin_bottom
		else
			self._body.height = 0
		end
	end
end

end