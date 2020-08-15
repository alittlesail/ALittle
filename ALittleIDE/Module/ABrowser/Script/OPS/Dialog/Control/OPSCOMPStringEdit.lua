
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(OPSCOMPBase, " extends class:OPSCOMPBase is nil")
OPSCOMPStringEdit = ALittle.Class(OPSCOMPBase, "ABrowser.OPSCOMPStringEdit")

function OPSCOMPStringEdit:Ctor(ctrl_sys, center, field_config, data)
	___rawset(self, "_center", center)
	___rawset(self, "_field_config", field_config)
	___rawset(self, "_data", data)
	___rawset(self, "_text_ctrl", g_Control:CreateControl("ops_common_text"))
	___rawset(self, "_input_link", {})
	___rawset(self, "_input_ctrl", g_Control:CreateControl("ops_common_edit", self._input_link))
	self._input_ctrl.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
	self._input_link._text_edit:AddEventListener(ALittle.UIEventTypes.FOCUSIN, self, self.HandleTextEditFocusin)
	self._input_link._text_edit:AddEventListener(ALittle.UIEventTypes.FOCUSOUT, self, self.HandleTextEditFocusout)
	self:UpdateConfig()
end

function OPSCOMPStringEdit:GetData()
	return self._field_config.invoke_param, self._input_link._text_edit.text
end

function OPSCOMPStringEdit:GetCopyString()
	return self._input_ctrl.text
end

function OPSCOMPStringEdit:UpdateConfig()
	self:RefreshConfig()
	self:RefreshDataInfo()
end

function OPSCOMPStringEdit:RefreshConfig()
	local config = self._field_config
	local width = nil
	local height = nil
	if config.name == nil then
		self._text_ctrl.text = ""
	else
		self._text_ctrl.text = config.name
	end
	self._input_ctrl.x = self._text_ctrl.width
	if config.width == nil then
		self._input_ctrl.width = 150
	else
		self._input_ctrl.width = config.width
	end
	if config.height == nil then
		self._input_ctrl.height = 70
	end
	self._input_link._text_edit.text = config.default_value
	if config.x == nil then
		self.x = 0
	else
		self.x = config.x
	end
	if config.y == nil then
		self.y = 0
	else
		self.y = config.y
	end
	self.width = self._input_ctrl.x + self._input_ctrl.width
	self.height = self._input_ctrl.height
	if config.name ~= nil then
		self:AddChild(self._text_ctrl)
	end
	self:AddChild(self._input_ctrl)
end

function OPSCOMPStringEdit:RefreshDataInfo()
	if self._data == nil then
		return
	end
	self._input_link._text_edit.text = self._data[self._field_config.input_param]
end

function OPSCOMPStringEdit:HandleTextEditFocusin(event)
	A_LoopSystem:AddUpdater(ALittle.LoopLinear(self._input_link._background, "alpha", 1, 200, 0))
end

function OPSCOMPStringEdit:HandleTextEditFocusout(event)
	A_LoopSystem:AddUpdater(ALittle.LoopLinear(self._input_link._background, "alpha", 0, 200, 0))
end

