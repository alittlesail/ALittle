
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(OPSCOMPBase, " extends class:OPSCOMPBase is nil")
OPSCOMPDropDownSelect = ALittle.Class(OPSCOMPBase, "ABrowser.OPSCOMPDropDownSelect")

function OPSCOMPDropDownSelect:Ctor(ctrl_sys, center, field_config, data)
	___rawset(self, "_center", center)
	___rawset(self, "_field_config", field_config)
	___rawset(self, "_data", data)
	___rawset(self, "_data_map", {})
	___rawset(self, "_text_ctrl", g_Control:CreateControl("ops_common_text"))
	self._text_ctrl.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
	___rawset(self, "_dropdown_ctrl", g_Control:CreateControl("ops_common_dropdown"))
	self._dropdown_ctrl.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
	self:UpdateConfig()
end

function OPSCOMPDropDownSelect:GetData()
	ALittle.Log(self._field_config.invoke_param, self._data_map[self._dropdown_ctrl.text])
	return self._field_config.invoke_param, self._data_map[self._dropdown_ctrl.text]
end

function OPSCOMPDropDownSelect:UpdateConfig()
	self:RefreshConfig()
	self:RefreshDataInfo()
end

function OPSCOMPDropDownSelect:RefreshConfig()
	local config = self._field_config
	self._text_ctrl.text = config.name
	self._dropdown_ctrl.x = self._text_ctrl.width
	if config.width == nil then
		self._dropdown_ctrl.width = 150
	else
		self._dropdown_ctrl.width = config.width
	end
	if config.data_list ~= nil then
		self._dropdown_ctrl.data_list = config.data_list
	end
	self._data_map = config.data_map
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
	self.width = self._dropdown_ctrl.x + self._dropdown_ctrl.width
	self.height = self._dropdown_ctrl.height
	self:AddChild(self._text_ctrl)
	self:AddChild(self._dropdown_ctrl)
end

function OPSCOMPDropDownSelect:RefreshDataInfo()
	if self._data == nil then
		return
	end
	if self._field_config.input_param == nil then
		return
	end
	local text = self._data[self._field_config.input_param]
	for k, v in ___pairs(self._data_map) do
		if text == v then
			self._dropdown_ctrl.text = k
			break
		end
	end
end

