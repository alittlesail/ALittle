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
ALittle.SpringButton = Lua.Class(ALittle.DisplayLayout, "ALittle.SpringButton")

function ALittle.SpringButton:Ctor(ctrl_sys)
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

function ALittle.SpringButton.__getter:text()
	if self._show_text == nil then
		return ""
	end
	return self._show_text.text
end

function ALittle.SpringButton.__setter:text(text)
	if self._show_text == nil then
		return
	end
	self._show_text.text = text
end

function ALittle.SpringButton.__setter:disabled(value)
	ALittle.DisplayObject.__setter.disabled(self, value)
	if value then
		self:ShowDisabled()
	else
		self:ShowUp(nil)
	end
end

function ALittle.SpringButton:HandleMoveIn(event)
	self:ShowOver()
end

function ALittle.SpringButton:HandleMoveOut(event)
	self:ShowUp(nil)
end

function ALittle.SpringButton:HandleLButtonDown(event)
	self:ShowDown()
end

function ALittle.SpringButton:HandleLButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local e = {}
		e.is_drag = event.is_drag
		e.count = event.count
		self:DispatchEvent(___all_struct[-449066808], e)
		if ALittle.System_IsPhone() == false then
			self:ShowOver()
		else
			self:ShowUp(nil)
		end
	else
		self:ShowUp(nil)
	end
end

function ALittle.SpringButton:HandleMButtonDown(event)
	self:ShowDown()
end

function ALittle.SpringButton:HandleMButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local e = {}
		e.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[-1330840], e)
		if ALittle.System_IsPhone() == false then
			self:ShowOver()
		else
			self:ShowUp(nil)
		end
	else
		self:ShowUp(nil)
	end
end

function ALittle.SpringButton:HandleFButtonDown(event)
	if event.is_sfc == false then
		self:ShowDown()
	end
end

function ALittle.SpringButton:HandleFButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local e = {}
		e.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[286797479], e)
	end
	if event.is_sfc == false then
		self:ShowUp(nil)
	end
end

function ALittle.SpringButton:ScaleTo(big_or_small, time_in_ms)
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
	self._anti_loop = ALittle.LoopGroup()
	self._anti_loop:AddUpdater(ALittle.LoopLinear(self, "scale_x", scale, time_in_ms, 1))
	self._anti_loop:AddUpdater(ALittle.LoopLinear(self, "scale_y", scale, time_in_ms, 1))
	self._anti_loop:Start()
end

function ALittle.SpringButton:ShowUp(event)
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

function ALittle.SpringButton:ShowDown()
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

function ALittle.SpringButton:ShowOver()
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

function ALittle.SpringButton:ShowDisabled()
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

end