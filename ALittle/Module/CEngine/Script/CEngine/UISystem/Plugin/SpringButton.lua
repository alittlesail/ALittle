-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = GetAllStruct()


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
SpringButton = Lua.Class(ALittle.DisplayLayout, "ALittle.SpringButton")

function SpringButton:Ctor(ctrl_sys)
	___rawset(self, "_big_or_small", false)
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

function SpringButton.__getter:text()
	if self._show_text == nil then
		return ""
	end
	return self._show_text.text
end

function SpringButton.__setter:text(text)
	if self._show_text == nil then
		return
	end
	self._show_text.text = text
end

function SpringButton.__setter:disabled(value)
	DisplayObject.__setter.disabled(self, value)
	if value then
		self:ShowDisabled()
	else
		self:ShowUp(nil)
	end
end

function SpringButton:HandleMoveIn(event)
	self:ShowOver()
end

function SpringButton:HandleMoveOut(event)
	self:ShowUp(nil)
end

function SpringButton:HandleLButtonDown(event)
	self:ShowDown()
end

function SpringButton:HandleLButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local e = {}
		e.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[-449066808], e)
		if System_IsPhone == false then
			self:ShowOver()
		else
			self:ShowUp(nil)
		end
	else
		self:ShowUp(nil)
	end
end

function SpringButton:HandleMButtonDown(event)
	self:ShowDown()
end

function SpringButton:HandleMButtonUp(event)
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

function SpringButton:HandleFButtonDown(event)
	if event.is_sfc == false then
		self:ShowDown()
	end
end

function SpringButton:HandleFButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local e = {}
		e.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[286797479], e)
	end
	if event.is_sfc == false then
		self:ShowUp(nil)
	end
end

function SpringButton:ScaleTo(big_or_small, time_in_ms)
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

function SpringButton:ShowUp(event)
	if self._abs_disabled or self._disabled then
		return
	end
	if self._show_up ~= nil then
		self._show_up.visible = true
	end
	if self._show_disabled ~= nil then
		self._show_disabled.visible = false
	end
	self:ScaleTo(false, 200)
end

function SpringButton:ShowDown()
	if self._abs_disabled or self._disabled then
		return
	end
	if self._show_up ~= nil then
		self._show_up.visible = true
	end
	if self._show_disabled ~= nil then
		self._show_disabled.visible = false
	end
	self:ScaleTo(true, 200)
end

function SpringButton:ShowOver()
	if self._abs_disabled or self._disabled then
		return
	end
	if self._show_up ~= nil then
		self._show_up.visible = true
	end
	if self._show_disabled ~= nil then
		self._show_disabled.visible = false
	end
	self:ScaleTo(false, 200)
end

function SpringButton:ShowDisabled()
	self:ScaleTo(false, 200)
	if self._show_up ~= nil then
		self._show_up.visible = false
	end
	if self._show_disabled ~= nil then
		self._show_disabled.visible = true
	else
		self._show_up.visible = true
	end
end

