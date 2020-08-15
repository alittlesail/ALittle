
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

OPSTableDataQuery = ALittle.Class(nil, "OPSTableDataQuery")

function OPSTableDataQuery:Ctor(center, table_data_config, parent)
	___rawset(self, "_center", center)
	___rawset(self, "_table_data_config", table_data_config)
	___rawset(self, "_parent", parent)
	___rawset(self, "_query_info", {})
	self._query_info.page_index = 1
	self._query_info.total_page = 1
	self._query_info.query_id = nil
	___rawset(self, "_order", {})
	___rawset(self, "_query_modal", g_Control:CreateControl("ops_query_modal", self))
end

function OPSTableDataQuery.__getter:query_info()
	return self._query_info
end

function OPSTableDataQuery.__setter:order(order)
	self._order = order
end

function OPSTableDataQuery:SendQuery()
	if self._query_info.query_id then
		return
	end
	self._query_info.page_index = 1
	self:RefreshQuery()
end

function OPSTableDataQuery:StopQuery()
	if self._query_info.query_id == nil then
		return
	end
	A_NetSystem:StopHttpPostRequest(self._query_info.query_id)
	self._query_info.query_id = nil
	self:HideQueryModal()
	self._query_loading:Stop()
end

function OPSTableDataQuery:HandleQueryCancel(event)
	self:StopQuery()
end

function OPSTableDataQuery:RefreshQuery()
	if self._query_info.query_id then
		return
	end
	local value_map = self._parent.search_param
	if value_map == nil then
		return
	end
	local param = {}
	param["value_map"] = value_map
	param["__page_index"] = self._query_info.page_index
	param["__page_size"] = tonumber(self._parent.count_per_page_text)
	if param["__page_size"] == nil then
		param["__page_size"] = 20
	end
	param["method"] = self._table_data_config.table
	if self._table_data_config.order then
		local order = self._table_data_config.order
		param["__order_name"] = order.name
		param["__order_type"] = order.type
	end
	local order_param = self._order.order_param
	local order_type = self._order.order_type
	if order_param ~= nil and order_type ~= nil then
		param["__order_name"] = order_param
		param["__order_type"] = order_type
	end
	self._query_info.query_id = self._center.login_logic:HttpPostRequest("QOPSOuterQuery", param, ALittle.Bind(self.HandleGeneralQueryResult, self))
	self:ShowQueryModal()
	self._query_loading:Play()
end

function OPSTableDataQuery:HandleGeneralQueryResult(result, client)
	if self._query_info.query_id == nil or self._query_info.query_id ~= client:GetID() then
		return
	end
	self._query_info.query_id = nil
	self:HideQueryModal()
	self._query_loading:Stop()
	if result == false then
		self._center.tool_logic:ShowCenterWeakNotice("查询失败，请检查网络或关闭360等管理软件", false)
		return
	end
	local result, msg = pcall(Json.decode, client:GetResponse())
	if result == false then
		self._center.tool_logic:ShowCenterWeakNotice("返回数据错误，请联系管理员", false)
		ALittle.Log(client:GetResponse())
		return
	end
	if msg["result"] == false then
		self._center.tool_logic:ShowCenterWeakNotice(msg["reason"], false)
		return
	end
	self._center.tool_logic:ShowWeakNotice("操作成功", true)
	self._query_info.page_index = msg["page_index"]
	if self._query_info.page_index == nil then
		self._query_info.page_index = 1
	end
	self._parent.count_text = "共" .. msg["total_count"] .. "条"
	local page_total = msg["page_count"]
	if page_total == nil then
		page_total = msg["total_count"]
	end
	local page_index = msg["page_index"]
	self._query_info.total_page = page_total
	self._parent.page_count = "第" .. page_index .. "页/共" .. page_total .. "页"
	self._parent.choose_text = "0"
	self._parent:ClearData()
	self._parent:SetDataList(msg["list"])
end

function OPSTableDataQuery:ShowQueryModal()
	self._parent:AddChild(self._query_modal)
	self._query_modal.visible = true
end

function OPSTableDataQuery:HideQueryModal()
	self._parent:RemoveChild(self._query_modal)
	self._query_modal.visible = false
end

