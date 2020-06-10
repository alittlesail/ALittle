
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
OPSTableData = ALittle.Class(ALittle.DisplayLayout, "ABrowser.OPSTableData")

function OPSTableData:Ctor(ctrl_sys, center, table_data_config, select_mode)
	self.width_type = ALittle.UIEnumTypes.SIZE_MARGIN
	self.height_type = ALittle.UIEnumTypes.SIZE_MARGIN
	___rawset(self, "_center", center)
	___rawset(self, "_table_data_config", table_data_config)
	___rawset(self, "_select_mode", select_mode)
	___rawset(self, "_screen_x", 0)
	___rawset(self, "_query", OPSTableDataQuery(self._center, self._table_data_config, self))
	___rawset(self, "_grid3", ALittle.Grid3(g_Control))
	self:AddChild(self._grid3)
	self._grid3.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
	self._grid3.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
	self._grid3.width_type = ALittle.UIEnumTypes.SIZE_MARGIN
	self._grid3.width_value = 5
	self._grid3.height_type = ALittle.UIEnumTypes.SIZE_MARGIN
	self._grid3.height_value = 5
	self._grid3.type = ALittle.UIEnumTypes.TYPE_V
	___rawset(self, "_search", OPSTableDataSearch(self._center, self._table_data_config, self))
	self._search.valign = ALittle.UIEnumTypes.VALIGN_CENTER
	self._search.line_spacing = 2
	self._search.column_spacing = 5
	self._search:AddEventListener(ALittle.UIEventTypes.RESIZE, self, self.HandleSearchGroupResize)
	self._grid3.show_up = self._search
	___rawset(self, "_screen", g_Control:CreateControl("abrowser_hv_scroll_screen", self))
	self._grid3.show_center = self._screen
	___rawset(self, "_static_object", OPSTableDataHead(self._center, self._table_data_config, self))
	self._screen.static_object_h = self._static_object
	___rawset(self, "_page_tail", OPSTableDataTail(self._center, self._table_data_config, self))
	self._grid3.down_size = self._page_tail.height
	self._grid3.show_down = self._page_tail
	self:SendQuery()
end

function OPSTableData.__getter:search_param()
	return self._search:SetQueryInfo()
end

function OPSTableData.__getter:page_index()
	return self._page_tail.page_index
end

function OPSTableData.__getter:count_per_page_text()
	return self._page_tail.count_per_page_text
end

function OPSTableData.__getter:query_info()
	return self._query.query_info
end

function OPSTableData.__getter:select_mode()
	return self._select_mode
end

function OPSTableData.__setter:select_all(value)
	self._static_object.all_select = value
end

function OPSTableData.__setter:choose_text(text)
	self._page_tail.choose_text = text
end

function OPSTableData.__setter:count_text(text)
	self._page_tail.count_text = text
end

function OPSTableData.__setter:page_count(text)
	self._page_tail.page_count = text
end

function OPSTableData:SendQuery()
	self._screen_x = self._screen.container.x
	self._query:SendQuery()
end

function OPSTableData:RefreshQuery()
	self._screen_x = self._screen.container.x
	self._query:RefreshQuery()
end

function OPSTableData:QueryOrder(order)
	self._query.order = order
	self:RefreshQuery()
end

function OPSTableData:SelectAll()
	self._data_object:SelectAll()
	self._page_tail.choose_text = tostring(self._data_object:GetChooseResult().count)
end

function OPSTableData:CancelSelectAll()
	self._data_object:CancelSelectAll()
	self._page_tail.choose_text = tostring(self._data_object:GetChooseResult().count)
end

function OPSTableData:SetDataList(list)
	local tr_height = 22
	local table_config = self._center.config.table[self._table_data_config.table]
	if table_config == nil then
		return
	end
	if table_config.tr_height ~= nil then
		tr_height = table_config.tr_height
	end
	local field_offset = self._static_object.field_offset
	local tr_width = self._screen.static_object_h.width - field_offset
	local offset_y = self._screen.static_object_h.height
	local handle_width = self._static_object.handle_width
	local set_param = {}
	set_param.tr_height = tr_height
	set_param.tr_width = tr_width
	set_param.field_offset = field_offset
	set_param.offset_y = offset_y
	set_param.handle_width = handle_width
	self._data_object = OPSTableDataSetData(self._center, self._table_data_config, self, set_param)
	self._data_object:AddEventListener(OPSTableDataSetDataEventTypes.DATA_CLICK, self, self.HandleDataClick)
	local static_object_v = self._data_object.static_object_v
	self._screen.static_object_v = static_object_v
	static_object_v.width = field_offset
	self._data_object:SetStaticObjectList(list)
	self._data_object:SetConcreteList(list, self._screen)
	self._screen.container_x = self._screen_x
end

function OPSTableData:HandleDataClick(event)
	self:DispatchEvent(event)
end

function OPSTableData:ClearData()
	if self._screen.static_object_v == nil then
		return
	end
	local object = self._screen.static_object_v
	object:RemoveAllChild()
	self._screen:RemoveAllChild()
end

function OPSTableData:GetChooseResult()
	return self._data_object:GetChooseResult().list
end

function OPSTableData:GetChoseTDIndex()
	return self._data_object:GetChooseTDIndex()
end

function OPSTableData:ShowOperateMenu(target)
	if self._tab_menu == nil then
		self._tab_menu = OPSTableDataMenu(self._center)
	end
	self._tab_menu:Show(target)
end

function OPSTableData:ShowCopyCutPasteMenu(text, target)
	self._center.tool_logic:ShowCopyCutPasteMenu(text, target)
end

function OPSTableData:ShowTimeSelect(target, select_type, default_hour, default_min, default_sec)
	self._center.tool_logic:ShowDateSelect(target, select_type, default_hour, default_min, default_sec)
end

function OPSTableData:HandleSearchGroupResize(event)
	self._grid3.up_size = self._grid3.show_up.height + 2
end

function OPSTableData:HandleEnterButtonClick(event)
	self._query:SendQuery()
end

