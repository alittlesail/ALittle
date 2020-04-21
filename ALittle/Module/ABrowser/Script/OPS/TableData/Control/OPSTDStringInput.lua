
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
ALittle.RegStruct(776398171, "ALittle.UIEnterKeyEvent", {
name = "ALittle.UIEnterKeyEvent", ns_name = "ALittle", rl_name = "UIEnterKeyEvent", hash_code = 776398171,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})

assert(ABrowser.OPSTDBase, " extends class:ABrowser.OPSTDBase is nil")
OPSTDStringInput = Lua.Class(ABrowser.OPSTDBase, "ABrowser.OPSTDStringInput")

function OPSTDStringInput:Ctor(ctrl_sys, center, field_config)
	___rawset(self, "_center", center)
	___rawset(self, "_field_config", field_config)
	local text = g_Control:CreateControl("ops_common_text")
	text.text = self._field_config.name
	text.y_type = 3
	local input = g_Control:CreateControl("ops_common_input")
	input.x = text.width
	if self._field_config.width == nil then
		input.width = 150
	else
		input.width = self._field_config.width
	end
	input.y_type = 3
	if self._field_config.default_value ~= nil then
		input.text = self._field_config.default_value
	end
	input:AddEventListener(___all_struct[776398171], self, self.HandleEnterButtonClick)
	input:AddEventListener(___all_struct[-641444818], self, self.HandleFieldRightClick)
	___rawset(self, "_input", input)
	self.width = text.width + input.width
	self.height = input.height
	self:AddChild(text)
	self:AddChild(input)
end

function OPSTDStringInput:HandleEnterButtonClick(event)
	self:DispatchEvent(___all_struct[776398171], {})
end

function OPSTDStringInput:HandleFieldRightClick(event)
	self:DispatchEvent(___all_struct[-641444818], {})
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

