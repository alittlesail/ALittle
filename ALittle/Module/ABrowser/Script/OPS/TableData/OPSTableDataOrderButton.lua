
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(OPSTDBase, " extends class:OPSTDBase is nil")
OPSTableDataOrderButton = ALittle.Class(OPSTDBase, "ABrowser.OPSTableDataOrderButton")

function OPSTableDataOrderButton:Ctor(ctrl_sys, param)
	___rawset(self, "_param", param)
	___rawset(self, "_order_type", nil)
	___rawset(self, "_index", 1)
	___rawset(self, "_button", g_Control:CreateControl("ops_common_order_button", self))
	self._button.width_type = ALittle.UIEnumTypes.SIZE_MARGIN
	self._button.height_type = ALittle.UIEnumTypes.SIZE_MARGIN
	self._btn:AddEventListener(ALittle.UIEventTypes.CLICK, self, self.HandleButtonClick)
	self._btn.hand_cursor = true
	self:AddChild(self._button)
	self:DefaultType()
end

function OPSTableDataOrderButton.__getter:order_type()
	return self._order_type
end

function OPSTableDataOrderButton.__getter:order_param()
	return self._param
end

function OPSTableDataOrderButton:DefaultType()
	self._quad.visible = false
	self._up_icon.visible = false
	self._down_icon.visible = false
	self._order_type = nil
	self._index = 1
end

function OPSTableDataOrderButton:SwitchType()
	self._index = self._index + 1
	if self._index > 3 then
		self._index = 1
	end
	if self._index == 1 then
		self:DefaultType()
	elseif self._index == 2 then
		self._quad.visible = true
		self._up_icon.visible = false
		self._down_icon.visible = true
		self._order_type = false
	else
		self._quad.visible = true
		self._up_icon.visible = true
		self._down_icon.visible = false
		self._order_type = true
	end
end

function OPSTableDataOrderButton:HandleButtonClick(event)
	self:SwitchType()
	self:DispatchEventType(ALittle.UIEventTypes.CHANGE)
end

