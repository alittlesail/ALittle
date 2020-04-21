
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-644464135, "ALittle.UIFocusInEvent", {
name = "ALittle.UIFocusInEvent", ns_name = "ALittle", rl_name = "UIFocusInEvent", hash_code = -644464135,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ABrowser.OPSCOMPBase, " extends class:ABrowser.OPSCOMPBase is nil")
OPSCOMPTimeSelect = Lua.Class(ABrowser.OPSCOMPBase, "ABrowser.OPSCOMPTimeSelect")

function OPSCOMPTimeSelect:Ctor(ctrl_sys, center, field_config, data)
	___rawset(self, "_center", center)
	___rawset(self, "_field_config", field_config)
	___rawset(self, "_data", data)
	___rawset(self, "_text_ctrl", g_Control:CreateControl("ops_common_text"))
	self._text_ctrl.y_type = 3
	___rawset(self, "_input_ctrl", g_Control:CreateControl("ops_common_input"))
	self._input_ctrl.y_type = 3
	self._input_ctrl:AddEventListener(___all_struct[-644464135], self, self.HandleTimeInput)
	self:UpdateConfig()
end

function OPSCOMPTimeSelect:GetData()
	return self._field_config.invoke_param, OPSDate.StringToTime(self._input_ctrl.text)
end

function OPSCOMPTimeSelect:GetCopyString()
	return self._input_ctrl.text
end

function OPSCOMPTimeSelect:HandleTimeInput(event)
	self._center.tool_logic:ShowDateSelect(event.target, self._field_config.select_type, self._field_config.default_hour, self._field_config.default_min, self._field_config.default_sec)
end

function OPSCOMPTimeSelect:UpdateConfig()
	self:RefreshConfig()
	self:RefreshDataInfo()
end

function OPSCOMPTimeSelect:RefreshConfig()
	local config = self._field_config
	self._text_ctrl.text = config.name
	self._input_ctrl.x = self._text_ctrl.width
	if config.width == nil then
		self._input_ctrl.width = 50
	else
		self._input_ctrl.width = config.width
	end
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
	self:AddChild(self._text_ctrl)
	self:AddChild(self._input_ctrl)
end

function OPSCOMPTimeSelect:RefreshDataInfo()
	local txt_time = self._data[self._field_config.input_param]
	self._input_ctrl.text = os.date("%Y-%m-%d %H:%M:%S", txt_time)
end

