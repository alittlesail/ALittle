
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

OPSRequestDialog = ALittle.Class(OPSBaseDialog, "OPSRequestDialog")

function OPSRequestDialog:Ctor()
end

function OPSRequestDialog:Show()
	local param = {}
	local method = self._method
	if self._dialog_config.module_invoke then
		param["__method"] = self._method
		method = "QOPSInvoke"
	end
	self._center.login_logic:HttpPostRequest(method, param, ALittle.Bind(self.QueryResult, self))
end

function OPSRequestDialog:QueryResult(result, client)
	if result == false then
		self._center.tool_logic:ShowCenterWeakNotice("调用失败，请检查网络或关闭360等管理软件", false)
		return
	end
	local result, msg = pcall(Json.decode, client:GetResponse())
	if result == false then
		self._center.tool_logic:ShowCenterWeakNotice("返回数据错误，请联系管理员", false)
		ALittle.Log(client:GetResponse())
		return
	end
	if msg["error"] then
		self._center.tool_logic:ShowCenterWeakNotice(msg["error"], false)
		return
	end
	self._center.tool_logic:ShowWeakNotice("操作成功", true)
	local ctrl_list = {}
	local ctrl_list_count = 0
	for k, field_config in ___ipairs(self._dialog_config.field) do
		local clazz = _G["ABrowser"][field_config.input_type]
		if clazz then
			ctrl_list_count = ctrl_list_count + 1
			ctrl_list[ctrl_list_count] = clazz(self._center, field_config, msg[field_config.input_param])
		end
	end
	self._container:RemoveAllChild()
	local max_width = self._container.width
	for k, control in ___ipairs(ctrl_list) do
		if control.width > max_width then
			max_width = control.width
		end
		self._container:AddChild(control)
	end
	local dialog_width = 0
	dialog_width = dialog_width + max_width
	dialog_width = dialog_width + self._container.width_value
	dialog_width = dialog_width + self._layer.width_value
	self.height = dialog_width
	local dialog_height = 0
	dialog_height = dialog_height + self._g3.up_size
	dialog_height = dialog_height + self._g3.down_size
	dialog_height = dialog_height + self._container.real_height
	dialog_height = dialog_height + self._container.height_value
	dialog_height = dialog_height + self._layer.height_value
	if dialog_height > A_UISystem.view_height then
		dialog_height = A_UISystem.view_height
	end
	self.height = dialog_height
	self:ShowFromModal()
end

