
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

OPSBaseDialog = ALittle.Class(ALittle.DisplayLayout, "OPSBaseDialog")

function OPSBaseDialog:Ctor()
	___rawset(self, "_ctrl_list", {})
end

function OPSBaseDialog:SetData(center, method, data, table_data, batch)
	self._center = center
	self._method = method
	self._dialog_config = center.config.dialog[method]
	self._data = data
	self._table_data = table_data
	self._batch = batch
	self._execute_count = 0
	self._total_count = 0
	self._failed_count = 0
end

function OPSBaseDialog:HandleDrag(event)
	self.x = self.x + event.delta_x
	self.y = self.y + event.delta_y
end

function OPSBaseDialog:Clear()
end

function OPSBaseDialog:Show()
end

function OPSBaseDialog:OtherParam(param)
end

function OPSBaseDialog:HandleCancelButtonClick(event)
	self:HideFromModal()
end

function OPSBaseDialog:HandleCloseButtonClick(event)
	self:HideFromModal()
end

function OPSBaseDialog:ShowFromModal()
	self._center.dialog_layer:AddChild(self)
	self.visible = true
end

function OPSBaseDialog:HideFromModal()
	self._center.dialog_layer:RemoveChild(self)
	self:Clear()
	self._ctrl_list = {}
	self._data = nil
end

function OPSBaseDialog:HandleConfirmButtonClick(event)
	if self._batch then
		local choose_list = self._table_data:GetChooseResult()
		self._total_count = self._total_count + (table.maxn(choose_list))
		for k, choose in ___ipairs(choose_list) do
			local param = {}
			if self._dialog_config.send_param then
				for k1, v1 in ___pairs(self._dialog_config.send_param) do
					if choose[v1.key] == nil then
						param[k1] = v1
					else
						param[k1] = choose[v1.key]
					end
					if v1.type == "string" then
						param[k1] = tostring(param[k1])
					elseif v1.type == "bool" then
						param[k1] = param[k1] == "true"
					else
						param[k1] = tonumber(param[k1])
					end
				end
			end
			for k, control in ___ipairs(self._ctrl_list) do
				local key, data = control:GetData()
				if key ~= nil and data ~= nil then
					param[key] = data
				end
			end
			self:OtherParam(param)
			local method = self._method
			if self._dialog_config.module_invoke then
				param["__method"] = self._method
				method = "QOPSInvoke"
			end
			self._center.login_logic:HttpPostRequest(method, param, ALittle.Bind(self.HandleRefrshResult, self))
		end
	else
		self._total_count = self._total_count + 1
		local param = {}
		if self._dialog_config.send_param then
			for k, v in ___pairs(self._dialog_config.send_param) do
				if self._data[v.key] == nil then
					param[k] = v.key
				else
					param[k] = self._data[v.key]
				end
				if v.type == "string" then
					param[k] = tostring(param[k])
				elseif v.type == "bool" then
					param[k] = param[k] == "true"
				else
					param[k] = tonumber(param[k])
				end
			end
		end
		for k, control in ___ipairs(self._ctrl_list) do
			local key, data = control:GetData()
			if key ~= nil and data ~= nil then
				param[key] = data
			end
		end
		self:OtherParam(param)
		local method = self._method
		if self._dialog_config.module_invoke then
			param["__method"] = self._method
			method = "QOPSInvoke"
		end
		self._center.login_logic:HttpPostRequest(method, param, ALittle.Bind(self.HandleRefrshResult, self))
	end
end

function OPSBaseDialog:HandleRefrshResult(result, client)
	self._execute_count = self._execute_count + 1
	local succeed = true
	local error_msg = "接口调用失败, 请检查网络或关闭360等管理软件"
	if result == false then
		succeed = false
	else
		local result, msg = pcall(Json.decode, client:GetResponse())
		if result == false then
			succeed = false
		end
		if msg["result"] == false then
			error_msg = msg["reason"]
			succeed = false
		end
	end
	if succeed == false then
		self._failed_count = self._failed_count + 1
	end
	local process_msg = "进度:" .. self._execute_count .. "/" .. self._total_count .. ", 失败数:" .. self._failed_count
	if succeed == false and error_msg ~= nil then
		self._center.tool_logic:ShowCenterWeakNotice(process_msg .. ", " .. error_msg, false)
	else
		if self._total_count == 1 then
			self._center.tool_logic:ShowWeakNotice("操作成功", true)
		else
			self._center.tool_logic:ShowWeakNotice("操作结果:" .. process_msg, true)
		end
	end
	if self._total_count <= self._execute_count then
		self._failed_count = 0
		self._total_count = 0
		self._execute_count = 0
		if self._table_data then
			self._table_data:RefreshQuery()
		end
		self:HideFromModal()
	end
end

OPSBaseDialogManager = ALittle.Class(nil, "OPSBaseDialogManager")

function OPSBaseDialogManager:Ctor(center)
	___rawset(self, "_center", center)
	___rawset(self, "_dialog_map", {})
	___rawset(self, "_ui_map", {})
	self._ui_map["OPSChoiceDialog"] = "ops_choice_dialog"
	self._ui_map["OPSCustomDialog"] = "ops_custom_dialog"
	self._ui_map["OPSDeleteDialog"] = "ops_delete_dialog"
	self._ui_map["OPSRequestDialog"] = "ops_request_dialog"
	self._ui_map["OPSRoleDialog"] = "ops_role_dialog"
end

function OPSBaseDialogManager:Show(target)
	local user_data = target._user_data
	local dialog = self._dialog_map[user_data.dialog_config.dialog]
	if dialog == nil then
		local dialog_config = self._center.config.dialog[user_data.dialog_config.dialog]
		if dialog_config == nil then
			return nil
		end
		local clazz = _G["ABrowser"][dialog_config.__class]
		if clazz == nil then
			self._center.tool_logic:ShowCenterWeakNotice("没有找到对应的对话框类型:" .. dialog_config.__class, false)
			return nil
		end
		dialog = g_Control:CreateControl(self._ui_map[dialog_config.__class])
		self._dialog_map[user_data.dialog_config.dialog] = dialog
	end
	dialog:SetData(self._center, user_data.dialog_config.dialog, user_data.data, user_data.table_data, user_data.batch)
	dialog:Show()
	return dialog
end

function OPSBaseDialogManager:Close()
	for k, v in ___pairs(self._dialog_map) do
		v:HideFromModal()
	end
	self._dialog_map = {}
end

