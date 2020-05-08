-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = GetAllStruct()


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
SpringCheckButton = Lua.Class(ALittle.DisplayLayout, "ALittle.SpringCheckButton")

function SpringCheckButton:Ctor(ctrl_sys)
	___rawset(self, "_big_or_small", false)
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

function SpringCheckButton.__setter:disabled(value)
	DisplayObject.__setter.disabled(self, value)
	if self._abs_disabled then
		self:ShowDisabled()
	else
		self:ShowUp()
	end
end

function SpringCheckButton:HandleMoveIn(event)
	self:ShowOver()
end

function SpringCheckButton:HandleMoveOut(event)
	self:ShowUp()
end

function SpringCheckButton:HandleLButtonDown(event)
	self:ShowDown()
end

function SpringCheckButton:HandleLButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		self._selected = (self._selected == false)
		local e = {}
		e.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[-449066808], e)
		self:DispatchEvent(___all_struct[958494922], {})
		if System_IsPhone == false then
			self:ShowOver()
		else
			self:ShowUp()
		end
	else
		self:ShowUp()
	end
end

function SpringCheckButton:HandleMButtonDown(event)
	self:ShowDown()
end

function SpringCheckButton:HandleMButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local e = {}
		e.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[-1330840], e)
		if System_IsPhone == false then
			self:ShowOver()
		else
			self:ShowUp()
		end
	else
		self:ShowUp()
	end
end

function SpringCheckButton.__setter:selected(value)
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

function SpringCheckButton.__getter:selected()
	return self._selected
end

function SpringCheckButton:ScaleTo(big_or_small, time_in_ms)
	if self._big_or_small == big_or_small then
		return
	end
	self._big_or_small = big_or_small
	local scale = 1.0
	if self._big_or_small then
		scale = 1.2
	end
	if self._anti_loop ~= nil then
		self._anti_loop:Stop()
		self._anti_loop = nil
	end
	self._anti_loop = LoopGroup()
	self._anti_loop:AddUpdater(LoopLinear(self, "scale_x", scale, time_in_ms, 1))
	self._anti_loop:AddUpdater(LoopLinear(self, "scale_y", scale, time_in_ms, 1))
	self._anti_loop:Start()
end

function SpringCheckButton:ShowUp()
	if self._abs_disabled or self._disabled then
		return
	end
	if self._selected then
		if self._show_selected_up ~= nil then
			self._show_selected_up.visible = true
		end
		if self._show_up ~= nil then
			self._show_up.visible = false
		end
	else
		if self._show_selected_up ~= nil then
			self._show_selected_up.visible = false
		end
		if self._show_up ~= nil then
			self._show_up.visible = true
		end
	end
	if self._show_disabled ~= nil then
		self._show_disabled.visible = false
	end
	self:ScaleTo(false, 200)
end

function SpringCheckButton:ShowDown()
	if self._abs_disabled or self._disabled then
		return
	end
	if self._selected then
		if self._show_selected_up ~= nil then
			self._show_selected_up.visible = true
		end
		if self._show_up ~= nil then
			self._show_up.visible = false
		end
	else
		if self._show_selected_up ~= nil then
			self._show_selected_up.visible = false
		end
		if self._show_up ~= nil then
			self._show_up.visible = true
		end
	end
	if self._show_disabled ~= nil then
		self._show_disabled.visible = false
	end
	self:ScaleTo(true, 200)
end

function SpringCheckButton:ShowOver()
	if self._abs_disabled or self._disabled then
		return
	end
	if self._selected then
		if self._show_selected_up ~= nil then
			self._show_selected_up.visible = true
		end
		if self._show_up ~= nil then
			self._show_up.visible = false
		end
	else
		if self._show_selected_up ~= nil then
			self._show_selected_up.visible = false
		end
		if self._show_up ~= nil then
			self._show_up.visible = true
		end
	end
	if self._show_disabled ~= nil then
		self._show_disabled.alpha = 0
	end
	self:ScaleTo(false, 200)
end

function SpringCheckButton:ShowDisabled()
	self:ScaleTo(false, 200)
	if self._show_up ~= nil then
		self._show_up.visible = false
	end
	if self._show_selected_up ~= nil then
		self._show_selected_up.visible = false
	end
	if self._show_disabled ~= nil then
		self._show_disabled.visible = true
	else
		if self._selected then
			self._show_selected_up.visible = true
		else
			self._show_up.visible = true
		end
	end
end

