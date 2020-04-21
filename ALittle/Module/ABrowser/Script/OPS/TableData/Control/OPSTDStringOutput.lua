
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
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name = "ALittle.UIMoveInEvent", ns_name = "ALittle", rl_name = "UIMoveInEvent", hash_code = 544684311,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name = "ALittle.UIMoveOutEvent", ns_name = "ALittle", rl_name = "UIMoveOutEvent", hash_code = -1202439334,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
OPSTDStringOutput = Lua.Class(ALittle.DisplayLayout, "ABrowser.OPSTDStringOutput")

function OPSTDStringOutput:Ctor(ctrl_sys, center, field_config, data)
	___rawset(self, "_center", center)
	___rawset(self, "_field_config", field_config)
	___rawset(self, "_data", data)
	___rawset(self, "_original_text", "")
	___rawset(self, "_export_text", "")
	___rawset(self, "_text_ctrl", g_Control:CreateControl("ops_table_textarea"))
	self._text_ctrl:AddEventListener(___all_struct[-641444818], self, self.HandleFieldRightClick)
	self._text_ctrl:AddEventListener(___all_struct[544684311], self, self.HandleMouseMoveIn)
	self._text_ctrl:AddEventListener(___all_struct[-1202439334], self, self.HandleMouseMoveOut)
	self:AddChild(self._text_ctrl)
	self:RefreshConfig()
end

function OPSTDStringOutput.__setter:data(text)
	self._text_ctrl.text = text
end

function OPSTDStringOutput:GetCopyString()
	return self._export_text
end

function OPSTDStringOutput.__setter:drag_trans_target(scroll_list)
	self._text_ctrl.drag_trans_target = scroll_list
end

function OPSTDStringOutput:HandleFieldRightClick(event)
	event.target = self
	self:DispatchEvent(___all_struct[-641444818], event)
end

function OPSTDStringOutput:HandleMouseMoveIn(event)
	event.target = self
	self:DispatchEvent(___all_struct[544684311], event)
end

function OPSTDStringOutput:HandleMouseMoveOut(event)
	event.target = self
	self:DispatchEvent(___all_struct[-1202439334], event)
end

function OPSTDStringOutput:RefreshConfig()
	local height = 22.0
	local width = self._field_config.width
	local text = self._data[self._field_config.field]
	self._original_text = text
	self._export_text = text
	local cut_string = false
	if self._field_config.data_style ~= nil then
		local data_style = self._field_config.data_style
		if data_style.time_format ~= nil then
			if text ~= 0 then
				text = ALittle.Time_GetCurDate(ALittle.Math_ToInt(text))
			end
		end
		if data_style.enum_map ~= nil then
			for k, v in ___pairs(data_style.enum_map) do
				if text == v then
					text = k
					break
				end
			end
		end
		if data_style.expand ~= nil then
			text = tonumber(text) * data_style.expand
		end
		self._export_text = text
	end
	self._text_ctrl.text = text
	self._text_ctrl.height = height
	self._text_ctrl._user_data = self._export_text
	self.width = width
	self.height = height
end

