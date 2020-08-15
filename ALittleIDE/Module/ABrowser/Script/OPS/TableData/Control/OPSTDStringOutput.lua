
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
OPSTDStringOutput = ALittle.Class(ALittle.DisplayLayout, "ABrowser.OPSTDStringOutput")

function OPSTDStringOutput:Ctor(ctrl_sys, center, field_config, data)
	___rawset(self, "_center", center)
	___rawset(self, "_field_config", field_config)
	___rawset(self, "_data", data)
	___rawset(self, "_original_text", "")
	___rawset(self, "_export_text", "")
	___rawset(self, "_text_ctrl", g_Control:CreateControl("ops_table_textarea"))
	self._text_ctrl:AddEventListener(ALittle.UIEventTypes.RBUTTONDOWN, self, self.HandleFieldRightClick)
	self._text_ctrl:AddEventListener(ALittle.UIEventTypes.MOVEIN, self, self.HandleMouseMoveIn)
	self._text_ctrl:AddEventListener(ALittle.UIEventTypes.MOVEOUT, self, self.HandleMouseMoveOut)
	self:AddChild(self._text_ctrl)
	self:RefreshConfig()
end

function OPSTDStringOutput.__setter:data(text)
	self._text_ctrl.text = text
end

function OPSTDStringOutput.__setter:drag_trans_target(scroll_list)
	self._text_ctrl.drag_trans_target = scroll_list
end

function OPSTDStringOutput:GetCopyString()
	return self._export_text
end

function OPSTDStringOutput:HandleFieldRightClick(event)
	self:TransferEvent(event)
end

function OPSTDStringOutput:HandleMouseMoveIn(event)
	self:TransferEvent(event)
end

function OPSTDStringOutput:HandleMouseMoveOut(event)
	self:TransferEvent(event)
end

function OPSTDStringOutput:RefreshConfig()
	local height = 22
	local width = self._field_config.width
	local text = self._data[self._field_config.field]
	self._original_text = text
	self._export_text = text
	local cut_string = false
	if self._field_config.data_style ~= nil then
		local data_style = self._field_config.data_style
		if data_style.time_format ~= nil then
			if text ~= 0 then
				text = os.date(data_style.time_format, math.floor(tonumber(text)))
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

