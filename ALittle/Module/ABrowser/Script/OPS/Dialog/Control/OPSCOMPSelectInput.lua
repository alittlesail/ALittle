
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(OPSCOMPBase, " extends class:OPSCOMPBase is nil")
OPSCOMPSelectInput = ALittle.Class(OPSCOMPBase, "ABrowser.OPSCOMPSelectInput")

function OPSCOMPSelectInput:Ctor(ctrl_sys, center, field_config, data)
	___rawset(self, "_center", center)
	___rawset(self, "_field_config", field_config)
	___rawset(self, "_data", data)
	___rawset(self, "_text_ctrl", g_Control:CreateControl("ops_common_text"))
	self._text_ctrl.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
	___rawset(self, "_input_ctrl", g_Control:CreateControl("ops_common_input"))
	self._input_ctrl.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
	self._input_ctrl.disabled = true
	___rawset(self, "_choose_btn", g_Control:CreateControl("ops_common_button"))
	self._choose_btn.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
	self._choose_btn:AddEventListener(ALittle.UIEventTypes.CLICK, self, self.HandleChooseButtonClick)
	self:UpdateConfig()
end

function OPSCOMPSelectInput:GetData()
	local user_data = self._input_ctrl._user_data
	if user_data == nil then
		return "", ""
	end
	return self._field_config.invoke_param, user_data
end

function OPSCOMPSelectInput:GetCopyString()
	return self._input_ctrl.text
end

function OPSCOMPSelectInput:UpdateConfig()
	self:RefreshConfig()
	self:RefreshDataInfo()
end

function OPSCOMPSelectInput:RefreshConfig()
	local config = self._field_config
	local width = nil
	local height = nil
	self._text_ctrl.text = config.name
	self._input_ctrl.x = self._text_ctrl.width
	if config.width == nil then
		self._input_ctrl.width = 150
	else
		self._input_ctrl.width = config.width
	end
	self._choose_btn.text = "选择"
	self._choose_btn.width = 70
	self._choose_btn.x = self._input_ctrl.x + self._input_ctrl.width + 10
	local user_data = {}
	user_data.dialog_config = {}
	user_data.dialog_config.dialog = config.__select_dialog
	user_data.data = self._data
	self._choose_btn._user_data = user_data
	width = self._choose_btn.x + self._choose_btn.width
	height = self._choose_btn.height
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
	self:AddChild(self._choose_btn)
end

function OPSCOMPSelectInput:RefreshDataInfo()
	if self._data == nil then
		return
	end
	self._input_ctrl.text = self._data[self._field_config.show_param]
	self._input_ctrl._user_data = self._data[self._field_config.input_param]
end

function OPSCOMPSelectInput:HandleChooseButtonClick(event)
	local object = event.target
	local dialog = self._center.dialog_logic:Show(object)
	if dialog ~= nil then
		dialog:RemoveEventListener(OPSTableDataSetDataEventTypes.DATA_CLICK)
		dialog:AddEventListener(OPSTableDataSetDataEventTypes.DATA_CLICK, self, self.HandleSelectCallback)
	end
end

function OPSCOMPSelectInput:HandleSelectCallback(event)
	local user_data = event.target._user_data
	self._input_ctrl.text = user_data[self._field_config.show_field]
	self._input_ctrl._user_data = user_data[self._field_config.select_field]
end

