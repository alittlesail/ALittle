-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-2110455927, "ALittle.EventInfo", {
name = "ALittle.EventInfo", ns_name = "ALittle", rl_name = "EventInfo", hash_code = -2110455927,
name_list = {"type","func"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(-4982446, "ALittle.DisplayInfo", {
name = "ALittle.DisplayInfo", ns_name = "ALittle", rl_name = "DisplayInfo", hash_code = -4982446,
name_list = {"__target_class","__class_func","__base_attr","__show_attr","loop_map","__module","__class","__include","__extends","__childs","__event","__link","__shows_included","__childs_included","__extends_included","description","text","font_path","font_size","red","green","blue","alpha","bold","italic","underline","deleteline","x","y","x_type","x_value","y_type","y_value","width","height","width_type","width_value","height_type","height_value","scale_x","scale_y","center_x","center_y","angle","flip","hand_cursor","visible","disabled","left_size","right_size","top_size","bottom_size","texture_name","interval","play_loop_count","var_play","base_y","head_size","gap","up_size","down_size","cursor_red","cursor_green","cursor_blue","default_text_alpha","ims_padding","margin_left","margin_right","margin_top","margin_bottom","show_count","body_margin","screen_margin_left","screen_margin_right","screen_margin_top","screen_margin_bottom","start_degree","end_degree","line_spacing","max_line_count","font_red","font_green","font_blue","margin_halign","margin_valign","cursor_margin_up","cursor_margin_down","total_size","show_size","offset_rate","offset_step","grade","row_count","col_count","row_index","col_index","u1","v1","u2","v2","u3","v3","x1","y1","x2","y2","x3","y3","x_gap","y_gap","x_start_gap","y_start_gap","button_gap","button_start","button_margin","tab_index","view_margin","child_width_margin"},
type_list = {"List<string>","any","Map<string,any>","Map<string,ALittle.DisplayInfo>","Map<string,ALittle.LoopGroupInfo>","string","string","string","string","List<ALittle.DisplayInfo>","List<ALittle.EventInfo>","string","bool","bool","bool","string","string","string","int","double","double","double","double","bool","bool","bool","bool","double","double","int","double","int","double","double","double","int","double","int","double","double","double","double","double","double","int","bool","bool","bool","double","double","double","double","string","int","int","bool","double","double","double","double","double","double","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","double","double","double","int","int","int","int","int","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double"},
option_map = {}
})

local __cos = ALittle.Math_Cos
local __sin = ALittle.Math_Sin
local __byte = ALittle.String_Byte
local __type = ALittle.String_Type
assert(ALittle.UIEventDispatcher, " extends class:ALittle.UIEventDispatcher is nil")
ALittle.DisplayObject = Lua.Class(ALittle.UIEventDispatcher, "ALittle.DisplayObject")

function ALittle.DisplayObject:Ctor(ctrl_sys)
	___rawset(self, "_ctrl_sys", ctrl_sys)
	___rawset(self, "_clip", false)
	___rawset(self, "_ignore", false)
	___rawset(self, "_x", 0)
	___rawset(self, "_y", 0)
	___rawset(self, "_x_type", 1)
	___rawset(self, "_x_value", 0)
	___rawset(self, "_y_type", 1)
	___rawset(self, "_y_value", 0)
	___rawset(self, "_width", 0)
	___rawset(self, "_height", 0)
	___rawset(self, "_width_type", 1)
	___rawset(self, "_width_value", 0)
	___rawset(self, "_height_type", 1)
	___rawset(self, "_height_value", 0)
	___rawset(self, "_scale_x", 1)
	___rawset(self, "_scale_y", 1)
	___rawset(self, "_angle", 0)
	___rawset(self, "_center_x", 0)
	___rawset(self, "_center_y", 0)
	___rawset(self, "_red", 1)
	___rawset(self, "_green", 1)
	___rawset(self, "_blue", 1)
	___rawset(self, "_alpha", 1)
	___rawset(self, "_abs_alpha", 1)
	___rawset(self, "_visible", true)
	___rawset(self, "_abs_visible", true)
	___rawset(self, "_hand_cursor", false)
	___rawset(self, "_disabled", false)
	___rawset(self, "_modal", false)
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", false)
	___rawset(self, "_pickup_this", false)
	___rawset(self, "_can_scroll", false)
end

function ALittle.DisplayObject.__setter:hand_cursor(value)
	if self._hand_cursor == value then
		return
	end
	self._hand_cursor = value
	if value then
		self:AddEventListener(___all_struct[544684311], self, self.HandleMoveInForCursor)
		self:AddEventListener(___all_struct[-1202439334], self, self.HandleMoveOutForCursor)
	else
		self:RemoveEventListener(___all_struct[544684311], self, self.HandleMoveInForCursor)
		self:RemoveEventListener(___all_struct[-1202439334], self, self.HandleMoveOutForCursor)
	end
end

function ALittle.DisplayObject.__getter:hand_cursor()
	return self._hand_cursor
end

function ALittle.DisplayObject:HandleMoveInForCursor(event)
	if self._hand_cursor == false then
		return
	end
	ALittle.System_SetHandCursor()
end

function ALittle.DisplayObject:HandleMoveOutForCursor(event)
	if self._hand_cursor == false then
		return
	end
	ALittle.System_SetNormalCursor()
end

function ALittle.DisplayObject.__getter:native_show()
	return self._show
end

function ALittle.DisplayObject.__getter:text()
	return nil
end

function ALittle.DisplayObject.__setter:text(value)
end

function ALittle.DisplayObject.__getter:group()
	return nil
end

function ALittle.DisplayObject.__setter:group(group)
end

function ALittle.DisplayObject.__getter:selected()
	return nil
end

function ALittle.DisplayObject.__setter:selected(value)
end

function ALittle.DisplayObject.__getter:font_height()
	return nil
end

function ALittle.DisplayObject:SetTextureCoord(t, b, l, r)
end

function ALittle.DisplayObject.__getter:texture()
	return nil
end

function ALittle.DisplayObject.__setter:texture(value)
end

function ALittle.DisplayObject.__getter:texture_name()
	return nil
end

function ALittle.DisplayObject.__setter:texture_name(value)
end

function ALittle.DisplayObject:Redraw()
end

function ALittle.DisplayObject.__getter:childs()
	return nil
end

function ALittle.DisplayObject.__getter:child_count()
	return nil
end

function ALittle.DisplayObject:SetChildIndex(child, index)
	return false
end

function ALittle.DisplayObject:AddChild(child, index)
	return false
end

function ALittle.DisplayObject:RemoveChild(child)
	return false
end

function ALittle.DisplayObject:SpliceChild(index, count)
	return 0
end

function ALittle.DisplayObject:RemoveAllChild()
end

function ALittle.DisplayObject:GetChildOffset()
	return 0, 0
end

function ALittle.DisplayObject.__getter:editable()
	return false
end

function ALittle.DisplayObject.__getter:font_size()
	return nil
end

function ALittle.DisplayObject.__getter:cursor_x()
	return nil
end

function ALittle.DisplayObject.__getter:cursor_y()
	return nil
end

function ALittle.DisplayObject.__getter:cursor_b()
	return nil
end

function ALittle.DisplayObject.__getter:is_focus()
	return A_UISystem.focus == self
end

function ALittle.DisplayObject:DelayFocus()
	local loop = ALittle.LoopTimer(Lua.Bind(self.HandleDelayFocus, self), 1)
	loop:Start()
end

function ALittle.DisplayObject:HandleDelayFocus()
	self.focus = true
end

function ALittle.DisplayObject:DelayDisable()
	local loop = ALittle.LoopTimer(Lua.Bind(self.HandleDelayDisable, self), 1)
	loop:Start()
end

function ALittle.DisplayObject:HandleDelayDisable()
	self.disabled = true
end

function ALittle.DisplayObject.__setter:focus(value)
	if value then
		A_UISystem.focus = self
	else
		if A_UISystem.focus == self then
			A_UISystem.focus = nil
		end
	end
end

function ALittle.DisplayObject.__getter:is_input()
	return false
end

function ALittle.DisplayObject.__setter:can_scroll(value)
	self._can_scroll = value
end

function ALittle.DisplayObject.__getter:can_scroll()
	return self._can_scroll
end

function ALittle.DisplayObject.__setter:description(value)
	self._description = value
end

function ALittle.DisplayObject.__getter:description()
	return self._description
end

function ALittle.DisplayObject.__setter:loop_map(value)
	self._loop_map = value
end

function ALittle.DisplayObject.__getter:loop_map()
	return self._loop_map
end

function ALittle.DisplayObject:CreateLoopAnimation(name)
	if self._loop_map == nil then
		return nil
	end
	local info = self._loop_map[name]
	if info == nil then
		return nil
	end
	return ALittle.LoopAnimation(self, info)
end

function ALittle.DisplayObject.__setter:modal(value)
	self._modal = value
end

function ALittle.DisplayObject.__getter:modal()
	return self._modal
end

function ALittle.DisplayObject.__setter:clip(value)
	self._clip = value
	self._show:SetClip(value)
end

function ALittle.DisplayObject.__getter:clip()
	return self._clip
end

function ALittle.DisplayObject.__setter:ignore(value)
	self._ignore = value
end

function ALittle.DisplayObject.__getter:ignore()
	return self._ignore
end

function ALittle.DisplayObject:IsMouseIn()
	local abs_x, abs_y = self:LocalToGlobal()
	local mouse_x = A_UISystem.mouse_x
	local mouse_y = A_UISystem.mouse_y
	if mouse_x < abs_x then
		return false
	end
	if mouse_y < abs_y then
		return false
	end
	if mouse_x > abs_x + self.width * self.scale_x then
		return false
	end
	if mouse_y > abs_y + self.height * self.scale_y then
		return false
	end
	return true
end

function ALittle.DisplayObject:LocalToGlobal(target)
	local x = 0.0
	local y = 0.0
	local parent = self
	while parent ~= nil do
		local scale_x = 1.0
		local scale_y = 1.0
		local show_parent = parent._show_parent
		if show_parent ~= nil then
			scale_x = show_parent.scale_x
			scale_y = show_parent.scale_y
		end
		x = x + (scale_x * parent.x)
		y = y + (scale_y * parent.y)
		if target == show_parent then
			break
		end
		parent = show_parent
	end
	return x, y
end

function ALittle.DisplayObject:LocalToGlobalMatrix2D(target)
	local result = ALittle.Matrix2D()
	local list = {}
	local count = 0
	local parent = self
	while parent ~= nil do
		if target == parent then
			break
		end
		count = count + 1
		list[count] = parent
		parent = parent._show_parent
	end
	local index = count
	while true do
		if not(index >= 1) then break end
		local object = list[index]
		local m = ALittle.Matrix2D()
		if index == 1 then
			m:Scale(object.width, object.height)
		end
		m:Translation(-object.center_x, -object.center_y)
		m:Rotate(3.1415926 * object.angle / 180)
		m:Translation(object.center_x, object.center_y)
		m:Scale(object.scale_x, object.scale_y)
		m:Translation(object.x, object.y)
		m:Multiply(result)
		result = m
		index = index+(-1)
	end
	return result
end

function ALittle.DisplayObject:GlobalToLocalMatrix2D(x, y, target)
	local list = {}
	local count = 0
	local parent = self
	while parent ~= nil do
		if target == parent then
			break
		end
		count = count + 1
		list[count] = parent
		parent = parent._show_parent
	end
	local pick
	local index = count
	while true do
		if not(index >= 1) then break end
		pick, x, y = list[index]:PickUpSelf(x, y)
		index = index+(-1)
	end
	return x, y
end

function ALittle.DisplayObject:RemoveFromParent()
	local parent = self.parent
	if parent == nil then
		return
	end
	parent:RemoveChild(self)
end

function ALittle.DisplayObject:IsGrandParent(target)
	local parent = self
	while parent ~= nil do
		parent = parent._show_parent
		if target == parent then
			return true
		end
	end
	return false
end

function ALittle.DisplayObject.__getter:parent()
	if self._logic_parent ~= nil then
		return self._logic_parent
	end
	return self._show_parent
end

function ALittle.DisplayObject.__getter:show_parent()
	return self._show_parent
end

function ALittle.DisplayObject.__getter:logic_parent()
	return self._logic_parent
end

function ALittle.DisplayObject:MoveToTop()
	if self._show_parent ~= nil then
		self._show_parent:SetChildIndex(self, self._show_parent.child_count)
	end
end

function ALittle.DisplayObject.__setter:x(value)
	if self._x == value then
		return
	end
	self._x = value
	if self._x_type == 1 then
		self._x_value = value
	end
	self._show:SetX(value)
end

function ALittle.DisplayObject.__getter:x()
	return self._x
end

function ALittle.DisplayObject.__setter:x_type(value)
	if self._x_type == value then
		return
	end
	self._x_type = value
	if self._show_parent ~= nil then
		self._show_parent:UpdateXLayout(self)
	end
end

function ALittle.DisplayObject.__setter:x_value(value)
	if self._x_value == value then
		return
	end
	self._x_value = value
	if self._show_parent ~= nil then
		self._show_parent:UpdateXLayout(self)
	end
end

function ALittle.DisplayObject.__getter:x_type()
	return self._x_type
end

function ALittle.DisplayObject.__getter:x_value()
	return self._x_value
end

function ALittle.DisplayObject.__setter:y(value)
	if self._y == value then
		return
	end
	self._y = value
	if self._y_type == 1 then
		self._y_value = value
	end
	self._show:SetY(value)
end

function ALittle.DisplayObject.__getter:y()
	return self._y
end

function ALittle.DisplayObject.__setter:y_type(value)
	if self._y_type == value then
		return
	end
	self._y_type = value
	if self._show_parent ~= nil then
		self._show_parent:UpdateYLayout(self)
	end
end

function ALittle.DisplayObject.__setter:y_value(value)
	if self._y_value == value then
		return
	end
	self._y_value = value
	if self._show_parent ~= nil then
		self._show_parent:UpdateYLayout(self)
	end
end

function ALittle.DisplayObject.__getter:y_type()
	return self._y_type
end

function ALittle.DisplayObject.__getter:y_value()
	return self._y_value
end

function ALittle.DisplayObject.__setter:width(value)
	if self._width == value then
		return
	end
	self._width = value
	if self._width_type == 1 then
		self._width_value = value
	end
	self._show:SetWidth(value)
end

function ALittle.DisplayObject.__getter:width()
	return self._width
end

function ALittle.DisplayObject.__setter:width_type(value)
	if self._width_type == value then
		return
	end
	self._width_type = value
	if self._show_parent ~= nil then
		self._show_parent:UpdateWidthLayout(self)
		if self._x_type ~= 1 and self._x_type ~= 2 and self._x_type ~= 7 then
			self._show_parent:UpdateXLayout(self)
		end
	elseif self._width_type == 1 then
		self.width = self._width_value
	end
end

function ALittle.DisplayObject.__setter:width_value(value)
	if self._width_value == value then
		return
	end
	self._width_value = value
	if self._show_parent ~= nil then
		self._show_parent:UpdateWidthLayout(self)
		if self._x_type ~= 1 and self._x_type ~= 2 and self._x_type ~= 7 then
			self._show_parent:UpdateXLayout(self)
		end
	elseif self._width_type == 1 then
		self.width = self._width_value
	end
end

function ALittle.DisplayObject.__getter:width_type()
	return self._width_type
end

function ALittle.DisplayObject.__getter:width_value()
	return self._width_value
end

function ALittle.DisplayObject.__setter:height(value)
	if self._height == value then
		return
	end
	self._height = value
	if self._height_type == 1 then
		self._height_value = value
	end
	self._show:SetHeight(value)
end

function ALittle.DisplayObject.__getter:height()
	return self._height
end

function ALittle.DisplayObject.__setter:height_type(value)
	if self._height_type == value then
		return
	end
	self._height_type = value
	if self._show_parent ~= nil then
		self._show_parent:UpdateHeightLayout(self)
		if self._y_type ~= 1 and self._y_type ~= 2 and self._y_type ~= 7 then
			self._show_parent:UpdateYLayout(self)
		end
	elseif self._height_type == 1 then
		self.height = self._height_value
	end
end

function ALittle.DisplayObject.__setter:height_value(value)
	if self._height_value == value then
		return
	end
	self._height_value = value
	if self._show_parent ~= nil then
		self._show_parent:UpdateHeightLayout(self)
		if self._y_type ~= 1 and self._y_type ~= 2 and self._y_type ~= 7 then
			self._show_parent:UpdateYLayout(self)
		end
	elseif self._height_type == 1 then
		self.height = self._height_value
	end
end

function ALittle.DisplayObject.__getter:height_type()
	return self._height_type
end

function ALittle.DisplayObject.__getter:height_value()
	return self._height_value
end

function ALittle.DisplayObject.__setter:scale_x(value)
	self._scale_x = value
	self._show:SetScaleX(value)
end

function ALittle.DisplayObject.__getter:scale_x()
	return self._scale_x
end

function ALittle.DisplayObject.__setter:scale_y(value)
	self._scale_y = value
	self._show:SetScaleY(value)
end

function ALittle.DisplayObject.__getter:scale_y()
	return self._scale_y
end

function ALittle.DisplayObject.__setter:center_x(value)
	self._center_x = value
	self._show:SetCenterX(value)
end

function ALittle.DisplayObject.__getter:center_x()
	return self._center_x
end

function ALittle.DisplayObject.__setter:center_y(value)
	self._center_y = value
	self._show:SetCenterY(value)
end

function ALittle.DisplayObject.__getter:center_y()
	return self._center_y
end

function ALittle.DisplayObject.__setter:angle(value)
	self._angle = value
	self._show:SetAngle(value)
end

function ALittle.DisplayObject.__getter:angle()
	return self._angle
end

function ALittle.DisplayObject.__setter:red(value)
	self._red = value
	self._show:SetRed(value)
end

function ALittle.DisplayObject.__getter:red()
	return self._red
end

function ALittle.DisplayObject.__setter:green(value)
	self._green = value
	self._show:SetGreen(value)
end

function ALittle.DisplayObject.__getter:green()
	return self._green
end

function ALittle.DisplayObject.__setter:blue(value)
	self._blue = value
	self._show:SetBlue(value)
end

function ALittle.DisplayObject.__getter:blue()
	return self._blue
end

function ALittle.DisplayObject.__setter:alpha(value)
	self._alpha = value
	self._abs_alpha = 1
	if self._show_parent ~= nil then
		self._abs_alpha = self._show_parent.abs_alpha * value
	else
		self._abs_alpha = value
	end
	self._show:SetAlpha(self._abs_alpha)
end

function ALittle.DisplayObject.__getter:alpha()
	return self._alpha
end

function ALittle.DisplayObject.__getter:abs_alpha()
	return self._abs_alpha
end

function ALittle.DisplayObject.__setter:visible(value)
	if value == false and self == A_UISystem.focus then
		A_UISystem.focus = nil
	end
	self._visible = value
	if self._show_parent ~= nil then
		self._abs_visible = self._show_parent.abs_visible and value
	else
		self._abs_visible = value
	end
	self._show:SetVisible(self._abs_visible)
end

function ALittle.DisplayObject.__getter:visible()
	return self._visible
end

function ALittle.DisplayObject.__getter:abs_visible()
	return self._abs_visible
end

function ALittle.DisplayObject.__setter:disabled(value)
	if value == true and self == A_UISystem.focus then
		A_UISystem.focus = nil
	end
	self._disabled = value
	if self._show_parent ~= nil then
		self._abs_disabled = self._show_parent.abs_disabled or value
	else
		self._abs_disabled = value
	end
end

function ALittle.DisplayObject.__getter:disabled()
	return self._disabled
end

function ALittle.DisplayObject.__getter:abs_disabled()
	return self._abs_disabled
end

function ALittle.DisplayObject:UpdateLayout()
	if self._show_parent == nil then
		return
	end
	self._show_parent:UpdateWidthLayout(self)
	self._show_parent:UpdateHeightLayout(self)
	self._show_parent:UpdateXLayout(self)
	self._show_parent:UpdateYLayout(self)
end

function ALittle.DisplayObject:PickUp(x, y)
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
	if self._modal then
		return self, rel_x, rel_y
	end
	if self._pickup_rect and rel_x >= 0 and rel_y >= 0 and rel_x < self._width and rel_y < self._height then
		return self, rel_x, rel_y
	else
		return nil, rel_x, rel_y
	end
end

function ALittle.DisplayObject:PickUpSelf(x, y)
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
		return nil, rel_x, rel_y
	end
	if self._abs_visible and rel_x >= 0 and rel_y >= 0 and rel_x < self.width and rel_y < self.height then
		return self, rel_x, rel_y
	end
	return nil, rel_x, rel_y
end

function ALittle.DisplayObject:ClipRect(x, y, width, height, h_move, v_move)
end

function ALittle.DisplayObject:DeepLayout()
end

function ALittle.DisplayObject:DeserializeSetter(info)
	local base_attr = info.__base_attr
	if base_attr == nil then
		base_attr = {}
		for key, value in ___pairs(info) do
			if __byte(key, 1) ~= 95 and (__type(value) ~= "table" or value.__class == nil) then
				base_attr[key] = value
			end
		end
		info.__base_attr = base_attr
	end
	for key, value in ___pairs(base_attr) do
		self[key] = value
	end
end

function ALittle.DisplayObject:DeserializeShowChild(info, target_logic)
	if info.__target_class ~= nil and self._ctrl_sys._use_plugin_class then
		target_logic = self
	end
	local show_attr = info.__show_attr
	if show_attr == nil then
		show_attr = {}
		for key, value in ___pairs(info) do
			if __byte(key, 1) ~= 95 and __type(value) == "table" and value.__class ~= nil then
				show_attr[key] = value
			end
		end
		info.__show_attr = show_attr
	end
	for key, value in ___pairs(show_attr) do
		local object = self._ctrl_sys:CreateControlObject(value)
		if object ~= nil then
			object:DeserializeSetter(value)
			self[key] = object
			object:DeserializeShowChild(value, target_logic)
			if target_logic ~= nil then
				object:DeserializeLinkEvent(value, target_logic)
			end
			if value.__target_class ~= nil and self._ctrl_sys._use_plugin_class then
				local tctor = object["TCtor"]
				if tctor ~= nil then
					tctor(object)
				end
			end
		end
	end
	local childs = info.__childs
	if childs ~= nil then
		for index, value in ___ipairs(childs) do
			local object = self._ctrl_sys:CreateControlObject(value)
			if object ~= nil then
				object:Deserialize(value, target_logic, self)
			end
		end
	end
end

function ALittle.DisplayObject:DeserializeLinkEvent(info, target_logic)
	local event_list = info.__event
	if event_list ~= nil then
		for index, einfo in ___ipairs(event_list) do
			local func = nil
			if einfo.func ~= nil then
				func = target_logic[einfo.func]
				if func == nil and self._ctrl_sys.log_error then
					ALittle.Log("can't find event func:\"" .. einfo.func .. "\" in " .. ALittle.String_ToString(target_logic))
				end
			end
			if einfo.type ~= nil and func ~= nil then
				self:AddEventListenerImpl(einfo.type, target_logic, func)
			end
		end
	end
	if info.__link ~= nil then
		target_logic[info.__link] = self
	end
end

function ALittle.DisplayObject:Deserialize(info, target_logic, parent)
	self:DeserializeSetter(info)
	if self._pickup_rect then
		if parent ~= nil then
			parent:AddChild(self)
		end
		self:DeserializeShowChild(info, target_logic)
		if target_logic ~= nil then
			self:DeserializeLinkEvent(info, target_logic)
		end
	else
		self:DeserializeShowChild(info, target_logic)
		if target_logic ~= nil then
			self:DeserializeLinkEvent(info, target_logic)
		end
		if parent ~= nil then
			parent:AddChild(self)
		end
	end
	if info.__target_class ~= nil and self._ctrl_sys._use_plugin_class then
		local tctor = self["TCtor"]
		if tctor ~= nil then
			tctor(self)
		end
	end
end

end