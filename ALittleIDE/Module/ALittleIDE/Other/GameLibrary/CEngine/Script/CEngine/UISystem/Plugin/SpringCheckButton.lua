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
ALittle.SpringCheckButton = Lua.Class(ALittle.DisplayLayout, "ALittle.SpringCheckButton")

function ALittle.SpringCheckButton:Ctor(ctrl_sys)
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

function ALittle.SpringCheckButton.__setter:disabled(value)
	ALittle.DisplayObject.__setter.disabled(self, value)
	if self._abs_disabled then
		self:ShowDisabled()
	else
		self:ShowUp()
	end
end

function ALittle.SpringCheckButton:HandleMoveIn(event)
	self:ShowOver()
end

function ALittle.SpringCheckButton:HandleMoveOut(event)
	self:ShowUp()
end

function ALittle.SpringCheckButton:HandleLButtonDown(event)
	self:ShowDown()
end

function ALittle.SpringCheckButton:HandleLButtonUp(event)
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

function ALittle.SpringCheckButton:HandleMButtonDown(event)
	self:ShowDown()
end

function ALittle.SpringCheckButton:HandleMButtonUp(event)
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

function ALittle.SpringCheckButton.__setter:selected(value)
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

function ALittle.SpringCheckButton.__getter:selected()
	return self._selected
end

function ALittle.SpringCheckButton:ScaleTo(big_or_small, time_in_ms)
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

function ALittle.SpringCheckButton:ShowUp()
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

function ALittle.SpringCheckButton:ShowDown()
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

function ALittle.SpringCheckButton:ShowOver()
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

function ALittle.SpringCheckButton:ShowDisabled()
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

end