
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ABrowser.OPSTDBase, " extends class:ABrowser.OPSTDBase is nil")
OPSTDDropDownSelect = Lua.Class(ABrowser.OPSTDBase, "ABrowser.OPSTDDropDownSelect")

function OPSTDDropDownSelect:Ctor(ctrl_sys, center, field_config)
	___rawset(self, "_center", center)
	___rawset(self, "_field_config", field_config)
	local width = 0.0
	local height = 0.0
	local text = g_Control:CreateControl("ops_common_text")
	text.text = self._field_config.name
	text.y_type = 3
	local dropdown = g_Control:CreateControl("ops_common_dropdown")
	dropdown.x = text.width
	if self._field_config.width == nil then
		dropdown.width = 150
	else
		dropdown.width = self._field_config.width
	end
	dropdown.y_type = 3
	___rawset(self, "_dropdown", dropdown)
	dropdown.data_list = self._field_config.data_list
	width = text.width + dropdown.width
	height = dropdown.height
	self.width = width
	self.height = height
	self:AddChild(text)
	self:AddChild(dropdown)
end

function OPSTDDropDownSelect:GetData()
	local value = self._field_config.data_map[self._dropdown.text]
	if value == nil then
		return true, nil, nil
	end
	local map = {}
	map[self._field_config.query_param] = value
	return true, map, nil
end

function OPSTDDropDownSelect:CanOption()
	return false
end

