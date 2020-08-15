
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(OPSCOMPBase, " extends class:OPSCOMPBase is nil")
OPSCOMPStringInput = ALittle.Class(OPSCOMPBase, "ABrowser.OPSCOMPStringInput")

function OPSCOMPStringInput:Ctor(ctrl_sys, center, field_config, data)
	___rawset(self, "_center", center)
	___rawset(self, "_field_config", field_config)
	___rawset(self, "_data", data)
	___rawset(self, "_text_ctrl", g_Control:CreateControl("ops_common_text"))
	self._text_ctrl.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
	___rawset(self, "_input_ctrl", g_Control:CreateControl("ops_common_input"))
	self._input_ctrl.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
	___rawset(self, "_unit_text", nil)
	self:UpdateConfig()
end

function OPSCOMPStringInput:GetData()
	return self._field_config.invoke_param, self._input_ctrl.text
end

function OPSCOMPStringInput:GetCopyString()
	return self._input_ctrl.text
end

function OPSCOMPStringInput:UpdateConfig()
	self:RefreshConfig()
	self:RefreshDataInfo()
end

function OPSCOMPStringInput:RefreshConfig()
	local config = self._field_config
	self._text_ctrl.text = config.name
	self._input_ctrl.x = self._text_ctrl.width
	if config.width == nil then
		self._input_ctrl.width = 150
	else
		self._input_ctrl.width = config.width
	end
	local width = self._input_ctrl.x + self._input_ctrl.width
	local height = self._input_ctrl.height
	if config.unit ~= nil then
		self._unit_text = g_Control:CreateControl("ops_common_text")
		self._unit_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
		self._unit_text.text = config.unit
		self._unit_text.x = self._input_ctrl.x + self._input_ctrl.width
		width = self._unit_text.x + self._unit_text.width
	end
	self._input_ctrl.text = config.default_value
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
	self.width = width
	self.height = height
	self:AddChild(self._text_ctrl)
	self:AddChild(self._input_ctrl)
	self:AddChild(self._unit_text)
end

function OPSCOMPStringInput:RefreshDataInfo()
	if self._data == nil then
		return
	end
	local text = self._data[self._field_config.input_param]
	self._input_ctrl.text = text
end

