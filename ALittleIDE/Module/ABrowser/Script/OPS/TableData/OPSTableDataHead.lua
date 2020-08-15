
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

OPSTableDataHeadEventTypes = {
	ALL_SELECT_CHANGE = "ABrowser_OPS_OPSTableDataHead_ALL_SELECT_CHANGE",
	ORDER_CHANGE = "ABrowser_OPS_OPSTableDataHead_ORDER_CHANGE",
}

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
OPSTableDataHead = ALittle.Class(ALittle.DisplayLayout, "ABrowser.OPSTableDataHead")

function OPSTableDataHead:Ctor(ctrl_sys, center, table_data_config, parent)
	___rawset(self, "_center", center)
	___rawset(self, "_table_data_config", table_data_config)
	___rawset(self, "_parent", parent)
	___rawset(self, "_handle_width", 100)
	___rawset(self, "_field_offset", 0)
	___rawset(self, "_field_list", {})
	___rawset(self, "_order_btn", {})
	local static_bg = ALittle.Quad(g_Control)
	static_bg.width_type = ALittle.UIEnumTypes.SIZE_MARGIN
	static_bg.height_type = ALittle.UIEnumTypes.SIZE_MARGIN
	self:AddChild(static_bg)
	local offset_x = 0
	local check_button = g_Control:CreateControl("ops_common_check")
	___rawset(self, "_all_check_button", check_button)
	check_button.y = 2
	check_button.x = 2
	check_button:AddEventListener(ALittle.UIEventTypes.CHANGE, self, self.HandleSelectAllChange)
	self:AddChild(check_button)
	self.height = check_button.y * 2 + check_button.height
	offset_x = check_button.x * 2 + check_button.width
	if self._table_data_config.single_handle ~= nil or self._parent.select_mode then
		local text = g_Control:CreateControl("ops_tab_text")
		text.text = "操作"
		text.x = (self._handle_width - text.width) / 2 + offset_x
		text.y = (self.height - text.height) / 2
		self:AddChild(text)
		offset_x = offset_x + (self._handle_width)
	end
	___rawset(self, "_field_offset", offset_x)
	local order_btn_count = table.maxn(self._order_btn)
	local field_list_count = table.maxn(self._field_list)
	local table_config = self._center.config.table[self._table_data_config.table]
	for k, field_config in ___ipairs(table_config.table_td) do
		if field_config.hidden ~= true then
			local has_order = false
			if field_config.order then
				has_order = true
				local button = OPSTableDataOrderButton(g_Control, field_config.field)
				button:AddEventListener(ALittle.UIEventTypes.CHANGE, self, self.HandleOrderChange)
				button.width = field_config.width
				button.height_type = ALittle.UIEnumTypes.SIZE_MARGIN
				button.x = offset_x
				self:AddChild(button)
				order_btn_count = order_btn_count + 1
				self._order_btn[order_btn_count] = button
			end
			local text = g_Control:CreateControl("ops_tab_text")
			if has_order then
				text.underline = true
			end
			text.text = field_config.name
			text.disabled = true
			text.x = (field_config.width - text.width) / 2 + offset_x
			text.y = (self.height - text.height) / 2
			self:AddChild(text)
			offset_x = offset_x + field_config.width
			local field_info = {}
			field_info.field = field_config.field
			field_info.name = field_config.name
			field_list_count = field_list_count + 1
			self._field_list[field_list_count] = field_info
		end
	end
	self.width = offset_x
end

function OPSTableDataHead.__getter:field_offset()
	return self._field_offset
end

function OPSTableDataHead.__getter:field_list()
	return self._field_list
end

function OPSTableDataHead.__getter:handle_width()
	return self._handle_width
end

function OPSTableDataHead.__setter:all_select(value)
	self._all_check_button.selected = value
end

function OPSTableDataHead:HandleSelectAllChange(event)
	local object = event.target
	local selected = object.selected
	if selected then
		self._parent:SelectAll()
	else
		self._parent:CancelSelectAll()
	end
end

function OPSTableDataHead:HandleOrderChange(event)
	local object = event.target
	local order = {}
	order.order_param = object.order_param
	order.order_type = object.order_type
	self:OtherOrderButtonChange(object)
	self._parent:QueryOrder(order)
end

function OPSTableDataHead:OtherOrderButtonChange(target)
	for k, button in ___ipairs(self._order_btn) do
		if button ~= target then
			button:DefaultType()
		end
	end
end

