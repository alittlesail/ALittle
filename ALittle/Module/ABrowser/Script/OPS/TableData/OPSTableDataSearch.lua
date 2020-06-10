
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(OPSTableDataRichGroup, " extends class:OPSTableDataRichGroup is nil")
OPSTableDataSearch = ALittle.Class(OPSTableDataRichGroup, "ABrowser.OPSTableDataSearch")

function OPSTableDataSearch:Ctor(ctrl_sys, center, table_data_config, parent)
	___rawset(self, "_center", center)
	___rawset(self, "_table_data_config", table_data_config)
	___rawset(self, "_parent", parent)
	local child_list = {}
	local child_list_count = 0
	___rawset(self, "_ctrl_list", {})
	local ctrl_list_count = 0
	local query_info = self._center.config.table[self._table_data_config.table].query_info
	for k, field_config in ___ipairs(query_info) do
		local clazz = _G["ABrowser"][field_config.input_type]
		if clazz ~= nil then
			local control = ALittle.NewObject(clazz, g_Control, self._center, field_config)
			control:AddEventListener(ALittle.UIEventTypes.ENTER_KEY, self, self.HandleEnterButtonClick)
			control:AddEventListener(ALittle.UIEventTypes.RBUTTONDOWN, self, self.HandleFieldRightClick)
			child_list_count = child_list_count + 1
			child_list[child_list_count] = control
			ctrl_list_count = ctrl_list_count + 1
			self._ctrl_list[ctrl_list_count] = control
		end
	end
	local container = ALittle.DisplayLayout(g_Control)
	local query_button = g_Control:CreateControl("ops_common_button")
	query_button.text = "查询"
	query_button:AddEventListener(ALittle.UIEventTypes.CLICK, self, self.HandleQueryButtonClick)
	container:AddChild(query_button)
	local refresh_button = g_Control:CreateControl("ops_common_button")
	refresh_button.text = "刷新"
	refresh_button:AddEventListener(ALittle.UIEventTypes.CLICK, self, self.HandleRefreshButtonClick)
	refresh_button.x = query_button.width + 5
	container.width = refresh_button.x + refresh_button.width
	container.height = refresh_button.height
	container:AddChild(refresh_button)
	child_list_count = child_list_count + 1
	child_list[child_list_count] = container
	self:CreateBatchButton(child_list)
	self:CreateEasyButton(child_list)
	self:SetChildList(child_list)
end

function OPSTableDataSearch:SetQueryInfo()
	local param_object = {}
	for index, control in ___ipairs(self._ctrl_list) do
		local result, data, reason = control:GetData()
		if result ~= true and control:CanOption() == false then
			self._center.tool_logic:ShowCenterWeakNotice(reason, false)
			return nil
		end
		if data ~= nil then
			for k, v in ___pairs(data) do
				param_object[k] = tostring(v)
			end
		end
	end
	return param_object
end

function OPSTableDataSearch:CreateBatchButton(child_list)
	local batch_menu = self._table_data_config.single_handle
	if batch_menu == nil or table.maxn(batch_menu) <= 0 then
		return
	end
	local handle_menu = {}
	local handle_menu_count = 0
	for k, v in ___ipairs(batch_menu) do
		local dialog_config = self._center.config.dialog[v.dialog]
		if dialog_config ~= nil then
			local result = self._center.login_logic:CheckPermission(dialog_config.permission)
			if result then
				handle_menu_count = handle_menu_count + 1
				handle_menu[handle_menu_count] = v
			end
		end
	end
	local container = ALittle.DisplayLayout(g_Control)
	local button = g_Control:CreateControl("ops_common_button")
	button.text = "批量操作"
	button.hand_cursor = true
	button:AddEventListener(ALittle.UIEventTypes.CLICK, self, self.HandleBatchButtonClick)
	button.width = 70
	container.width = button.width
	container.height = button.height
	container:AddChild(button)
	local child_list_count = table.maxn(child_list)
	child_list_count = child_list_count + 1
	child_list[child_list_count] = container
	local user_data = {}
	user_data.single_handle_config_list = handle_menu
	user_data.table_data = self._parent
	user_data.batch = true
	user_data.position = OPSTableDataMenuType.SHOW_BOTTOM
	button._user_data = user_data
end

function OPSTableDataSearch:HandleBatchButtonClick(event)
	self._parent:ShowOperateMenu(event.target)
end

function OPSTableDataSearch:CreateEasyButton(child_list)
	local handle_list = self._table_data_config.multi_handle
	if handle_list == nil or table.maxn(handle_list) <= 0 then
		return
	end
	local container = ALittle.DisplayLayout(g_Control)
	local offset_x = -5
	for _, list_v in ___ipairs(handle_list) do
		local handle_menu = {}
		local handle_menu_count = 0
		for k, v in ___ipairs(list_v.childs) do
			local dialog_config = self._center.config.dialog[v.dialog]
			if dialog_config ~= nil then
				local result = self._center.login_logic:CheckPermission(dialog_config.permission)
				if result then
					handle_menu_count = handle_menu_count + 1
					handle_menu[handle_menu_count] = v
				end
			end
		end
		if handle_menu_count > 0 then
			local button = g_Control:CreateControl("ops_common_button")
			button.text = list_v.name
			button.hand_cursor = true
			button:AddEventListener(ALittle.UIEventTypes.CLICK, self, self.HandleOtherButtonClick)
			button.width = 70
			button.x = offset_x + 5
			offset_x = button.x + button.width
			container:AddChild(button)
			local user_data = {}
			user_data.multy_handle_config_list = handle_menu
			user_data.table_data = self._parent
			user_data.position = OPSTableDataMenuType.SHOW_BOTTOM
			button._user_data = user_data
		end
	end
	local count = container.child_count
	if count > 0 then
		local last_obj = container:GetChildByIndex(count)
		container.height = last_obj.height
		container.width = last_obj.x + last_obj.width
	end
	local child_list_count = table.maxn(child_list)
	child_list_count = child_list_count + 1
	child_list[child_list_count] = container
end

function OPSTableDataSearch:HandleOtherButtonClick(event)
	self._parent:ShowOperateMenu(event.target)
end

function OPSTableDataSearch:HandleTimeInput(event)
	self._parent:ShowTimeSelect(event.target)
end

function OPSTableDataSearch:HandleQueryButtonClick(event)
	self._parent:SendQuery()
end

function OPSTableDataSearch:HandleRefreshButtonClick(event)
	self._parent:RefreshQuery()
end

function OPSTableDataSearch:HandleEnterButtonClick(event)
	self._parent:SendQuery()
end

function OPSTableDataSearch:HandleFieldRightClick(event)
	local object = event.target
	self._parent:ShowCopyCutPasteMenu(object:GetCopyString(), object)
end

