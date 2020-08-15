
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
OPSTableDataTail = ALittle.Class(ALittle.DisplayLayout, "ABrowser.OPSTableDataTail")

function OPSTableDataTail:Ctor(ctrl_sys, center, table_data_config, parent)
	___rawset(self, "_center", center)
	___rawset(self, "_table_data_config", table_data_config)
	___rawset(self, "_parent", parent)
	___rawset(self, "_query_info", parent.query_info)
	local control = g_Control:CreateControl("ops_scroll_down", self)
	self:AddChild(control)
	self.width = control.width
	self.height = control.height
end

function OPSTableDataTail.__getter:count_per_page_text()
	return self._count_per_page_text.text
end

function OPSTableDataTail.__getter:page_index()
	return self._page_index
end

function OPSTableDataTail.__setter:count_text(text)
	self._count_text.text = text
end

function OPSTableDataTail.__setter:page_count(text)
	self._page_text.text = text
end

function OPSTableDataTail.__setter:choose_text(count)
	self._choose_text.text = "已选中" .. count .. "条"
end

function OPSTableDataTail:HandlePrePage(event)
	if self._query_info.query_id ~= nil then
		return
	end
	self._query_info.page_index = self._query_info.page_index - 1
	if self._query_info.page_index < 1 then
		self._query_info.page_index = 1
		return
	end
	self:RefreshQuery()
end

function OPSTableDataTail:HandleNextPage(event)
	if self._query_info.query_id ~= nil then
		return
	end
	self._query_info.page_index = self._query_info.page_index + 1
	if self._query_info.page_index > self._query_info.total_page then
		self._query_info.page_index = self._query_info.total_page
		return
	end
	self:RefreshQuery()
end

function OPSTableDataTail:HandleJumpPage(event)
	if self._query_info.query_id ~= nil then
		return
	end
	local page_index = math.floor(tonumber(self._page_index.text))
	if page_index == nil or page_index <= 0 then
		self._center.tool_logic:ShowCenterWeakNotice("页数不正确", false)
		return
	end
	self._query_info.page_index = page_index
	self:RefreshQuery()
end

function OPSTableDataTail:RefreshQuery()
	self._parent:RefreshQuery()
end

