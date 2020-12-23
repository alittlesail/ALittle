-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1031172931, "ALittle.FingerInfo", {
name = "ALittle.FingerInfo", ns_name = "ALittle", rl_name = "FingerInfo", hash_code = 1031172931,
name_list = {"key","mouse_x","mouse_y","last_mouse_x","last_mouse_y","dl","mfc","mfc_rel_x","mfc_rel_y","is_sfc"},
type_list = {"string","double","double","double","double","bool","ALittle.DisplayObject","double","double","bool"},
option_map = {}
})

local __abs = ALittle.Math_Abs
ALittle.UISystem = Lua.Class(nil, "ALittle.UISystem")

function ALittle.UISystem:Ctor()
	___rawset(self, "_view_width", 0)
	___rawset(self, "_view_height", 0)
	___rawset(self, "_mouse_x", 0)
	___rawset(self, "_mouse_y", 0)
	___rawset(self, "_last_mouse_x", 0)
	___rawset(self, "_last_mouse_y", 0)
	___rawset(self, "_lbutton_down", false)
	___rawset(self, "_lbutton_count", 0)
	___rawset(self, "_lbutton_finger_id", nil)
	___rawset(self, "_lbutton_touch_id", nil)
	___rawset(self, "_mfc", nil)
	___rawset(self, "_mfc_rel_x", 0)
	___rawset(self, "_mfc_rel_y", 0)
	___rawset(self, "_mfd", nil)
	___rawset(self, "_sfc", nil)
	___rawset(self, "_wfc", nil)
	___rawset(self, "_pfc", nil)
	___rawset(self, "_button_type", nil)
	___rawset(self, "_sl", false)
	___rawset(self, "_dl", false)
	___rawset(self, "_dl_delta_x", 0)
	___rawset(self, "_dl_delta_y", 0)
	___rawset(self, "_max_dl_delta", 10)
	___rawset(self, "_max_lp_delta", 2)
	if ALittle.System_GetPlatform() == "Windows" then
		___rawset(self, "_max_dl_delta", 1)
		___rawset(self, "_max_lp_delta", 0)
	end
	___rawset(self, "_ime_editing", false)
	___rawset(self, "_ime_editing_callback", nil)
	___rawset(self, "_sym_map", {})
	___rawset(self, "_keydown_callback", nil)
	___rawset(self, "_keyup_callback", nil)
	___rawset(self, "_view_resize_callback", nil)
	___rawset(self, "_long_press", nil)
	___rawset(self, "_finger_info", {})
end

function ALittle.UISystem.__setter:view_resize_callback(value)
	self._view_resize_callback = value
end

function ALittle.UISystem.__getter:view_resize_callback()
	return self._view_resize_callback
end

function ALittle.UISystem.__setter:keydown_callback(value)
	self._keydown_callback = value
end

function ALittle.UISystem.__getter:keydown_callback()
	return self._keydown_callback
end

function ALittle.UISystem.__setter:keyup_callback(value)
	self._keyup_callback = value
end

function ALittle.UISystem.__getter:keyup_callback()
	return self._keyup_callback
end

function ALittle.UISystem.__setter:quit_callback(value)
	self._quit_callback = value
end

function ALittle.UISystem.__getter:quit_callback()
	return self._quit_callback
end

function ALittle.UISystem.__getter:sym_map()
	return self._sym_map
end

function ALittle.UISystem.__setter:ime_callback(value)
	self._ime_editing_callback = value
end

function ALittle.UISystem.__getter:ime_callback()
	return self._ime_editing_callback
end

function ALittle.UISystem.__getter:mouse_x()
	return self._mouse_x
end

function ALittle.UISystem.__getter:mouse_y()
	return self._mouse_y
end

function ALittle.UISystem.__setter:focus(control)
	if self._sfc == control then
		return
	end
	self._wfc = nil
	if self._sfc ~= nil then
		if self._dl == true then
			self._dl = false
			self._dl_delta_x = 0
			self._dl_delta_y = 0
			if self._button_type == "ALittle.UILButtonDownEvent" then
				local event = {}
				event.target = self._sfc
				event.rel_x = self._mfc_rel_x
				event.rel_y = self._mfc_rel_y
				if self._mfc ~= self._sfc then
					event.rel_x, event.rel_y = self._sfc:GlobalToLocalMatrix2D(self._mouse_x, self._mouse_y)
				end
				event.delta_x = self._mouse_x - self._last_mouse_x
				event.delta_y = self._mouse_y - self._last_mouse_y
				event.abs_x = self._mouse_x
				event.abs_y = self._mouse_y
				self._sfc:DispatchEvent(___all_struct[150587926], event)
			end
		end
		local sfc = self._sfc
		if self._ime_editing_callback ~= nil then
			self._ime_editing_callback(false, nil, nil, nil, nil)
		end
		self._sfc = nil
		self._sl = false
		sfc:DispatchEvent(___all_struct[292776509], {})
	end
	self._sfc = control
	if self._sfc ~= nil then
		self._sfc:DispatchEvent(___all_struct[-644464135], {})
	end
end

function ALittle.UISystem.__getter:focus()
	return self._sfc
end

function ALittle.UISystem.__setter:pick(control)
	if self._pfc ~= nil then
		A_LayerManager:RemoveFromTip(self._pfc)
	end
	self._pfc = control
	if self._pfc ~= nil then
		A_LayerManager:AddToTip(self._pfc)
	end
end

function ALittle.UISystem.__getter:pick()
	return self._pfc
end

function ALittle.UISystem.__getter:view_width()
	return self._view_width
end

function ALittle.UISystem.__getter:view_height()
	return self._view_height
end

function ALittle.UISystem:HandleMouseMoved(x, y)
	local delta_x = x - self._mouse_x
	local delta_y = y - self._mouse_y
	self._last_mouse_x = self._mouse_x
	self._last_mouse_y = self._mouse_y
	self._mouse_x = x
	self._mouse_y = y
	if self._long_press ~= nil and __abs(delta_x) <= self._max_lp_delta and __abs(delta_y) <= self._max_lp_delta then
		return false
	end
	if self._long_press ~= nil then
		self._long_press:Stop()
		self._long_press = nil
	end
	if self._pfc ~= nil then
		self._pfc.x = self._pfc.x + (delta_x)
		self._pfc.y = self._pfc.y + (delta_y)
	end
	if self._sl and self._button_type == "ALittle.UILButtonDownEvent" then
		if self._dl == true then
			local event = {}
			event.target = self._sfc
			event.rel_x, event.rel_y = self._sfc:GlobalToLocalMatrix2D(x, y)
			if self._dl_delta_x > 0 then
				delta_x = self._dl_delta_x + delta_x
				self._dl_delta_x = 0
			end
			if self._dl_delta_y > 0 then
				delta_y = self._dl_delta_y + delta_y
				self._dl_delta_y = 0
			end
			event.abs_x = x
			event.abs_y = y
			event.delta_x = delta_x
			event.delta_y = delta_y
			self._sfc:DispatchEvent(___all_struct[1337289812], event)
			return true
		end
		if self._dl == false then
			self._dl_delta_x = self._dl_delta_x + (delta_x)
			self._dl_delta_y = self._dl_delta_y + (delta_y)
			if __abs(self._dl_delta_x) >= self._max_dl_delta or __abs(self._dl_delta_y) >= self._max_dl_delta then
				self._dl = true
				local event = {}
				event.target = self._sfc
				local mouse_x = x - delta_x
				local mouse_y = y - delta_y
				event.rel_x, event.rel_y = self._sfc:GlobalToLocalMatrix2D(mouse_x, mouse_y)
				event.abs_x = mouse_x
				event.abs_y = mouse_y
				event.delta_x = 0
				event.delta_y = 0
				self._sfc:DispatchEvent(___all_struct[1301789264], event)
			end
		end
		return true
	end
	self:UpdateMoveFocus(x, y)
	return self._mfc ~= nil
end

function ALittle.UISystem:HandleLButtonDown(x, y, count)
	self._lbutton_down = true
	self._lbutton_count = count
	self._lbutton_finger_id = nil
	self._lbutton_touch_id = nil
	return self:HandleButtonDown(___all_struct[1883782801], x, y, count)
end

function ALittle.UISystem:HandleLButtonUp(x, y)
	self._lbutton_down = false
	return self:HandleButtonUp(___all_struct[40651933], x, y, self._lbutton_count)
end

function ALittle.UISystem:HandleMButtonDown(x, y, count)
	return self:HandleButtonDown(___all_struct[349963892], x, y, count)
end

function ALittle.UISystem:HandleMButtonUp(x, y)
	return self:HandleButtonUp(___all_struct[683647260], x, y, 1)
end

function ALittle.UISystem:HandleButtonDown(T, x, y, count)
	local rflt = T
	self._wfc = nil
	A_LayerManager:HandleLRButtonDown(x, y)
	self:UpdateMoveFocus(x, y)
	if self._mfc ~= nil then
		self._sl = true
		self._button_type = rflt.name
		if self._pfc ~= nil and rflt.name == "ALittle.UILButtonDownEvent" then
			local event = {}
			event.target = self._mfc
			event.drop_target = self._pfc
			self._mfc:DispatchEvent(___all_struct[1354499457], event)
			A_LayerManager:RemoveFromTip(self._pfc)
			self._pfc = nil
		end
		if self._mfd ~= nil then
			local layer = self._mfd.show_parent
			layer:SetChildIndex(self._mfd, layer.child_count)
		end
		local event = {}
		event.target = self._mfc
		event.abs_x = x
		event.abs_y = y
		event.rel_x = self._mfc_rel_x
		event.rel_y = self._mfc_rel_y
		event.count = count
		event.is_drag = false
		self._mfc:DispatchEvent(T, event)
		if rflt.name == "ALittle.UILButtonDownEvent" then
			if self._long_press ~= nil then
				self._long_press:Stop()
			end
			local long_event = {}
			long_event.target = self._mfc
			long_event.abs_x = x
			long_event.abs_y = y
			long_event.rel_x = self._mfc_rel_x
			long_event.rel_y = self._mfc_rel_y
			long_event.is_drag = false
			self._long_press = ALittle.LoopFunction(Lua.Bind(ALittle.UISystem.DispatchLongButtonEvent, self._mfc, long_event), 1, 500, 1)
			self._long_press:Start()
		end
		if self._sfc == nil then
			self._sfc = self._mfc
			self._sfc:DispatchEvent(___all_struct[-644464135], {})
		elseif self._mfc ~= self._sfc then
			self._sfc:DispatchEvent(___all_struct[292776509], {})
			if self._ime_editing_callback ~= nil then
				self._ime_editing_callback(false, nil, nil, nil, nil)
			end
			self._sfc = self._mfc
			self._sfc:DispatchEvent(___all_struct[-644464135], {})
		end
		return true
	else
		if self._sfc ~= nil then
			self._sfc:DispatchEvent(___all_struct[292776509], {})
			if self._ime_editing_callback ~= nil then
				self._ime_editing_callback(false, nil, nil, nil, nil)
			end
			self._sfc = nil
			self._sl = false
		end
	end
	return false
end

function ALittle.UISystem.DispatchLongButtonEvent(mfc, event)
	mfc:DispatchEvent(___all_struct[-439548260], event)
end

function ALittle.UISystem:HandleButtonUp(T, x, y, count)
	if self._sl == false then
		return false
	end
	if self._long_press ~= nil then
		self._long_press:Stop()
		self._long_press = nil
	end
	self._sl = false
	local rel_x, rel_y = self._sfc:GlobalToLocalMatrix2D(x, y)
	local save_dl = self._dl
	if self._dl == true then
		self._dl = false
		self._dl_delta_x = 0
		self._dl_delta_y = 0
		local event = {}
		event.target = self._sfc
		event.abs_x = x
		event.abs_y = y
		event.delta_x = self._mouse_x - self._last_mouse_x
		event.delta_y = self._mouse_y - self._last_mouse_y
		event.rel_x = rel_x
		event.rel_y = rel_y
		self._sfc:DispatchEvent(___all_struct[150587926], event)
	end
	if self._sfc ~= nil then
		local event = {}
		event.target = self._sfc
		event.abs_x = x
		event.abs_y = y
		event.rel_x = rel_x
		event.rel_y = rel_y
		event.is_drag = save_dl
		event.count = count
		self._sfc:DispatchEvent(T, event)
	end
	self:UpdateMoveFocus(x, y)
	return self._mfc ~= nil
end

function ALittle.UISystem:HandleRButtonDown(x, y, count)
	A_LayerManager:HandleLRButtonDown(x, y)
	if self._sl then
		return false
	end
	self:UpdateMoveFocus(x, y)
	if self._mfc ~= nil then
		local event = {}
		event.target = self._mfc
		event.abs_x = x
		event.abs_y = y
		event.rel_x = self._mfc_rel_x
		event.rel_y = self._mfc_rel_y
		event.count = count
		event.is_drag = false
		self._mfc:DispatchEvent(___all_struct[-641444818], event)
		return true
	end
	return false
end

function ALittle.UISystem:HandleRButtonUp(x, y)
	return false
end

function ALittle.UISystem:HandleTextInput(text)
	self._ime_editing = false
	if self._ime_editing_callback ~= nil then
		self._ime_editing_callback(false, nil, nil, nil, nil)
	end
	if self._sfc ~= nil then
		local event = {}
		event.target = self._sfc
		event.text = text
		self._sfc:DispatchEvent(___all_struct[-1234078962], event)
		return true
	end
	return false
end

function ALittle.UISystem:HandleTextEditing(text, start)
	if text == "" then
		if self._ime_editing == false then
			return
		end
		self._ime_editing = false
		if self._ime_editing_callback ~= nil then
			self._ime_editing_callback(false, nil, nil, nil, nil)
		end
	else
		self._ime_editing = true
		if self._sfc == nil or self._sfc.is_input == false or self._sfc.editable == false or self._sfc.font_size == nil then
			return
		end
		if self._ime_editing_callback ~= nil then
			local list = ALittle.String_Split(ALittle.System_GetIMESelectList(), " ")
			local new_list = {}
			local count = 0
			for index, value in ___ipairs(list) do
				if value ~= "" then
					count = count + 1
					new_list[count] = value
				end
			end
			self._ime_editing_callback(true, text, start, new_list, self._sfc)
			ALittle.System_SetIMEPos(ALittle.System_GetScreenWidth(), ALittle.System_GetScreenHeight())
		else
			local abs_x, abs_y = self._sfc:LocalToGlobal()
			abs_x = abs_x + (self._sfc.cursor_x)
			abs_y = abs_y + ((self._sfc.cursor_y + self._sfc.font_size) * self._sfc.scale_y)
			ALittle.System_SetIMEPos(ALittle.Math_Floor(abs_x), ALittle.Math_Floor(abs_y))
		end
	end
end

function ALittle.UISystem:HandleKeyDown(mod, sym, scancode)
	self._sym_map[sym] = true
	if ALittle.System_GetIMESelectList() == "" and self._ime_editing then
		self._ime_editing = false
		if self._ime_editing_callback ~= nil then
			self._ime_editing_callback(false, nil, nil, nil, nil)
		end
		return
	end
	local event = {}
	event.target = self._sfc
	event.mod = mod
	event.sym = sym
	event.scancode = scancode
	if self._sfc ~= nil and self._ime_editing == false then
		self._sfc:DispatchEvent(___all_struct[-1604617962], event)
	end
	if not event.handled and self._ime_editing == false and self._keydown_callback ~= nil then
		self._keydown_callback(mod, sym, scancode)
	end
end

function ALittle.UISystem:HandleKeyUp(mod, sym, scancode)
	self._sym_map[sym] = nil
	local event = {}
	event.target = self._sfc
	event.mod = mod
	event.sym = sym
	event.scancode = scancode
	if self._sfc ~= nil and self._ime_editing == false then
		self._sfc:DispatchEvent(___all_struct[1213009422], event)
	end
	if self._ime_editing == false and self._keyup_callback ~= nil then
		self._keyup_callback(mod, sym, scancode)
	end
end

function ALittle.UISystem:HandleMouseWheel(x, y)
	if self._mfc == nil then
		return false
	end
	if self._wfc == nil then
		local control = self._mfc
		while control ~= nil do
			if control.can_scroll == true then
				self._wfc = control
				break
			end
			control = control.show_parent
		end
	end
	if self._wfc ~= nil then
		local event = {}
		event.target = self._wfc
		event.delta_x = x
		event.delta_y = y
		self._wfc:DispatchEvent(___all_struct[-1737121315], event)
	end
	return true
end

function ALittle.UISystem:UpdateMoveFocus(x, y)
	local mfc
	local mfd
	mfc, mfd, self._mfc_rel_x, self._mfc_rel_y = A_LayerManager:PickUp(x, y)
	self._mfd = mfd
	if self._mfc == mfc then
		if mfc ~= nil then
			local event = {}
			event.target = mfc
			event.abs_x = x
			event.abs_y = y
			event.rel_x = self._mfc_rel_x
			event.rel_y = self._mfc_rel_y
			mfc:DispatchEvent(___all_struct[-1001723540], event)
		end
		return
	end
	if self._mfc ~= nil then
		self._mfc:DispatchEvent(___all_struct[-1202439334], {})
	end
	if mfc ~= nil then
		mfc:DispatchEvent(___all_struct[544684311], {})
	end
	self._mfc = mfc
	self._wfc = nil
end

function ALittle.UISystem:HandleViewResized(width, height)
	if self._view_width == width and self._view_height == height then
		return
	end
	self._view_width = width
	self._view_height = height
	A_LayerManager:HandleViewResized(width, height)
	if self._view_resize_callback ~= nil then
		self._view_resize_callback(width, height)
	end
end

function ALittle.UISystem:HandleDropFile(path)
	local x = ALittle.System_GetCursorX()
	local y = ALittle.System_GetCursorY()
	self:HandleMouseMoved(x, y)
	if self._mfc == nil then
		return
	end
	local event = {}
	event.target = self._mfc
	event.path = path
	self._mfc:DispatchEvent(___all_struct[-338112738], event)
end

function ALittle.UISystem:HandleWindowEnter()
end

function ALittle.UISystem:HandleWindowLeave()
	if self._lbutton_down then
		self:HandleLButtonUp(self._mouse_x, self._mouse_y)
	end
end

function ALittle.UISystem:HandleQuit()
	if self._quit_callback ~= nil and not self._quit_callback() then
		return
	end
	ALittle.System_Exit()
end

function ALittle.UISystem:HandleFingerDown(x, y, finger_id, touch_id)
	if self._lbutton_down == false then
		self._lbutton_down = true
		self._lbutton_count = 1
		self._lbutton_finger_id = finger_id
		self._lbutton_touch_id = touch_id
		self._mouse_x = x
		self._mouse_y = y
		return self:HandleButtonDown(___all_struct[1883782801], x, y, 1)
	end
	local key = finger_id .. "_" .. touch_id
	local info = {}
	info.key = key
	info.mouse_x = x
	info.mouse_y = y
	info.last_mouse_x = 0
	info.last_mouse_y = 0
	info.dl = false
	info.mfc = nil
	info.mfc_rel_x = 0
	info.mfc_rel_y = 0
	info.is_sfc = false
	local mfd
	info.mfc, mfd, info.mfc_rel_x, info.mfc_rel_y = A_LayerManager:PickUp(x, y)
	if info.mfc == nil then
		return false
	end
	info.is_sfc = (self._sl and (info.mfc == self._mfc or info.mfc == self._sfc))
	local event = {}
	event.target = info.mfc
	event.abs_x = x
	event.abs_y = y
	event.rel_x = info.mfc_rel_x
	event.rel_y = info.mfc_rel_y
	event.finger_key = info.key
	event.is_sfc = info.is_sfc
	event.is_drag = false
	info.mfc:DispatchEvent(___all_struct[-1233353463], event)
	self._finger_info[key] = info
	return true
end

function ALittle.UISystem:HandleFingerUp(x, y, finger_id, touch_id)
	if self._lbutton_down and self._lbutton_finger_id == finger_id and self._lbutton_touch_id == touch_id then
		self._lbutton_down = false
		return self:HandleButtonUp(___all_struct[40651933], x, y, self._lbutton_count)
	end
	local key = finger_id .. "_" .. touch_id
	local info = self._finger_info[key]
	if info == nil then
		return false
	end
	self._finger_info[key] = nil
	info.last_mouse_x = info.mouse_x
	info.last_mouse_y = info.mouse_y
	info.mouse_x = x
	info.mouse_y = y
	local save_dl = info.dl
	if info.dl == true then
		info.dl = false
		local event = {}
		event.target = info.mfc
		event.abs_x = x
		event.abs_y = y
		event.rel_x = info.mfc_rel_x
		event.rel_y = info.mfc_rel_y
		event.delta_x = info.mouse_x - info.last_mouse_x
		event.delta_y = info.mouse_y - info.last_mouse_y
		event.finger_key = key
		event.is_sfc = info.is_sfc
		info.mfc:DispatchEvent(___all_struct[-2050069067], event)
	end
	local event = {}
	event.target = info.mfc
	event.abs_x = x
	event.abs_y = y
	event.rel_x = info.mfc_rel_x
	event.rel_y = info.mfc_rel_y
	event.finger_key = info.key
	event.is_sfc = info.is_sfc
	event.is_drag = save_dl
	info.mfc:DispatchEvent(___all_struct[734860930], event)
	return true
end

function ALittle.UISystem:HandleFingerMoved(x, y, finger_id, touch_id)
	if self._lbutton_down and self._lbutton_finger_id == finger_id and self._lbutton_touch_id == touch_id then
		return self:HandleMouseMoved(x, y)
	end
	local key = finger_id .. "_" .. touch_id
	local info = self._finger_info[key]
	if info == nil then
		return false
	end
	local delta_x = x - info.mouse_x
	local delta_y = y - info.mouse_y
	info.last_mouse_x = info.mouse_x
	info.last_mouse_y = info.mouse_y
	info.mouse_x = x
	info.mouse_y = y
	if info.mfc ~= nil then
		info.mfc_rel_x, info.mfc_rel_y = info.mfc:GlobalToLocalMatrix2D(x, y)
	end
	if info.dl == true then
		local event = {}
		event.target = info.mfc
		event.delta_x = delta_x
		event.delta_y = delta_y
		event.abs_x = x
		event.abs_y = y
		event.rel_x = info.mfc_rel_x
		event.rel_y = info.mfc_rel_y
		event.finger_key = info.key
		event.is_sfc = info.is_sfc
		info.mfc:DispatchEvent(___all_struct[-51419723], event)
		return true
	end
	if info.dl == false then
		info.dl = true
		local event = {}
		event.target = info.mfc
		event.delta_x = delta_x
		event.delta_y = delta_y
		event.abs_x = x
		event.abs_y = y
		event.rel_x = info.mfc_rel_x
		event.rel_y = info.mfc_rel_y
		event.finger_key = info.key
		event.is_sfc = info.is_sfc
		info.mfc:DispatchEvent(___all_struct[1598008698], event)
		return true
	end
	return false
end

_G.A_UISystem = ALittle.UISystem()
end