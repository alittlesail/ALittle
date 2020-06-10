
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(OPSTDBase, " extends class:OPSTDBase is nil")
OPSTDStringInput = ALittle.Class(OPSTDBase, "ABrowser.OPSTDStringInput")

function OPSTDStringInput:Ctor(ctrl_sys, center, field_config)
	___rawset(self, "_center", center)
	___rawset(self, "_field_config", field_config)
	local text = g_Control:CreateControl("ops_common_text")
	text.text = self._field_config.name
	text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
	local input = g_Control:CreateControl("ops_common_input")
	input.x = text.width
	if self._field_config.width == nil then
		input.width = 150
	else
		input.width = self._field_config.width
	end
	input.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
	if self._field_config.default_value ~= nil then
		input.text = self._field_config.default_value
	end
	input:AddEventListener(ALittle.UIEventTypes.ENTER_KEY, self, self.HandleEnterButtonClick)
	input:AddEventListener(ALittle.UIEventTypes.RBUTTONDOWN, self, self.HandleFieldRightClick)
	___rawset(self, "_input", input)
	self.width = text.width + input.width
	self.height = input.height
	self:AddChild(text)
	self:AddChild(input)
end

function OPSTDStringInput:HandleEnterButtonClick(event)
	self:DispatchEventType(ALittle.UIEventTypes.ENTER_KEY)
end

function OPSTDStringInput:HandleFieldRightClick(event)
	self:DispatchEventType(ALittle.UIEventTypes.RBUTTONDOWN)
end

function OPSTDStringInput:GetData()
	local map = {}
	if self:CanOption() then
		return true, map, nil
	end
	map[self._field_config.query_param] = self._input.text
	return true, map, nil
end

function OPSTDStringInput:CanOption()
	return self._field_config.option == true and self._input.text == ""
end

function OPSTDStringInput:GetCopyString()
	return self._input.text
end

function OPSTDStringInput:CutText()
	self._input:CutText()
end

function OPSTDStringInput:PasteText()
	self._input:PasteText()
end

