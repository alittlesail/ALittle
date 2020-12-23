-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-2129379001, "ALittle.ScrollButtonDragBeginEvent", {
name = "ALittle.ScrollButtonDragBeginEvent", ns_name = "ALittle", rl_name = "ScrollButtonDragBeginEvent", hash_code = -2129379001,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(2101017097, "ALittle.ScrollButtonDragEndEvent", {
name = "ALittle.ScrollButtonDragEndEvent", ns_name = "ALittle", rl_name = "ScrollButtonDragEndEvent", hash_code = 2101017097,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(-646882501, "ALittle.ScrollButtonDragEvent", {
name = "ALittle.ScrollButtonDragEvent", ns_name = "ALittle", rl_name = "ScrollButtonDragEvent", hash_code = -646882501,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})

local __abs = ALittle.Math_Abs
assert(ALittle.TextButton, " extends class:ALittle.TextButton is nil")
ALittle.ScrollButton = Lua.Class(ALittle.TextButton, "ALittle.ScrollButton")

function ALittle.ScrollButton:Ctor(ctrl_sys)
	self:AddEventListener(___all_struct[1301789264], self, self.HandleDragBegin)
	self:AddEventListener(___all_struct[1337289812], self, self.HandleDrag)
	self:AddEventListener(___all_struct[150587926], self, self.HandleDragEnd)
	___rawset(self, "_button_down", false)
	___rawset(self, "_drag_begin_x", 0)
	___rawset(self, "_drag_begin_y", 0)
	___rawset(self, "_btn_drag", false)
	___rawset(self, "_can_drag_trans", true)
	___rawset(self, "_can_set_drag_trans", true)
end

function ALittle.ScrollButton.__setter:can_drag_trans(value)
	if self._can_set_drag_trans == false then
		return
	end
	self._can_drag_trans = value
end

function ALittle.ScrollButton.__getter:can_drag_trans()
	return self._can_drag_trans
end

function ALittle.ScrollButton:HandleDragBegin(event)
	self._drag_begin_x = event.abs_x
	self._drag_begin_y = event.abs_y
end

function ALittle.ScrollButton:HandleDrag(event)
	if self._btn_drag == false then
		if __abs(event.abs_x - self._drag_begin_x) > 2 or __abs(event.abs_y - self._drag_begin_y) > 2 then
			self._button_down = false
			self:ShowUp(nil)
			local e = {}
			e.target = self
			e.delta_x = event.delta_x
			e.delta_y = event.delta_y
			e.abs_x = event.abs_x
			e.abs_y = event.abs_y
			self:DispatchEvent(___all_struct[-2129379001], e)
			self._can_set_drag_trans = false
			if self._can_drag_trans and self._trans_target["drag"] ~= nil then
				local ue = {}
				ue.target = self._trans_target["drag"]
				ue.delta_x = event.delta_x
				ue.delta_y = event.delta_y
				ue.abs_x = event.abs_x
				ue.abs_y = event.abs_y
				self._trans_target["drag"]:DispatchEvent(___all_struct[-2129379001], e)
			end
			self._btn_drag = true
		end
	elseif self._btn_drag == true then
		local e = {}
		e.target = self
		e.delta_x = event.delta_x
		e.delta_y = event.delta_y
		e.abs_x = event.abs_x
		e.abs_y = event.abs_y
		self:DispatchEvent(___all_struct[-646882501], e)
		if self._can_drag_trans and self._trans_target["drag"] ~= nil then
			local ue = {}
			ue.target = self._trans_target["drag"]
			ue.delta_x = event.delta_x
			ue.delta_y = event.delta_y
			ue.abs_x = event.abs_x
			ue.abs_y = event.abs_y
			self:DispatchEvent(___all_struct[-646882501], e)
		end
	end
end

function ALittle.ScrollButton:HandleDragEnd(event)
	if self._btn_drag then
		if self._can_drag_trans and self._trans_target["drag"] ~= nil then
			local e = {}
			e.target = self._trans_target["drag"]
			e.delta_x = event.delta_x
			e.delta_y = event.delta_y
			e.abs_x = event.abs_x
			e.abs_y = event.abs_y
			self._trans_target["drag"]:DispatchEvent(___all_struct[150587926], e)
		end
		self._can_set_drag_trans = true
		local e = {}
		e.target = self
		e.delta_x = event.delta_x
		e.delta_y = event.delta_y
		e.abs_x = event.abs_x
		e.abs_y = event.abs_y
		self:DispatchEvent(___all_struct[2101017097], e)
	end
end

function ALittle.ScrollButton:HandleLButtonDown(event)
	self._drag_begin_x = 0
	self._drag_begin_y = 0
	self._btn_drag = false
	self._button_down = true
	self._button_down_loop = ALittle.LoopFunction(Lua.Bind(self.HandleLButtonDownFunc, self, nil), 1, 0, 100)
	A_LoopSystem:AddUpdater(self._button_down_loop)
end

function ALittle.ScrollButton:HandleLButtonUp(event)
	if self._btn_drag then
		return
	end
	if self._button_down == false then
		self:HandleLButtonUpFunc(event)
	else
		self:ShowDown()
		self._button_up_loop = ALittle.LoopFunction(Lua.Bind(self.HandleLButtonUpFunc, self, event), 1, 0, 60)
		self._button_up_loop:Start()
	end
end

function ALittle.ScrollButton:DispatchEvent(T, event)
	local rflt = T
	local event_target = self
	if self._trans_target["event"] ~= nil then
		event_target = self._trans_target["event"]
	end
	if event_target._abs_disabled then
		return
	end
	if event_target._abs_disabled then
		return
	end
	local callback_table = event_target._listeners[rflt.name]
	if callback_table == nil then
		return
	end
	for object, callback_value in ___pairs(callback_table) do
		for func, _ in ___pairs(callback_value) do
			func(object, event)
		end
	end
end

function ALittle.ScrollButton:HandleLButtonDownFunc(event)
	if self._button_down == true then
		self:ShowDown()
		self._button_down = false
	end
	A_LoopSystem:RemoveUpdater(self._button_down_loop)
end

function ALittle.ScrollButton:HandleLButtonUpFunc(event)
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
	A_LoopSystem:RemoveUpdater(self._button_up_loop)
end

end