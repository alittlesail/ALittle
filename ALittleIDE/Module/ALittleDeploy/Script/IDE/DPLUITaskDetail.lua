-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1566214727, "DeployServer.S2CUpdateTaskInfo", {
name = "DeployServer.S2CUpdateTaskInfo", ns_name = "DeployServer", rl_name = "S2CUpdateTaskInfo", hash_code = 1566214727,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1149037254, "DeployServer.C2SUpdateTaskInfo", {
name = "DeployServer.C2SUpdateTaskInfo", ns_name = "DeployServer", rl_name = "C2SUpdateTaskInfo", hash_code = 1149037254,
name_list = {"task_id","task_name","task_desc","web_hook"},
type_list = {"int","string","string","List<string>"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleDeploy.DPLUITaskDetail = Lua.Class(ALittle.DisplayLayout, "ALittleDeploy.DPLUITaskDetail")

function ALittleDeploy.DPLUITaskDetail:Init(item_info)
	self._item_info = item_info
	self:UpdateTaskInfo()
end

function ALittleDeploy.DPLUITaskDetail:Show()
	self.visible = true
	if not self._save_button.disabled then
		self:UpdateTaskInfo()
	end
end

function ALittleDeploy.DPLUITaskDetail:Hide()
	self.visible = false
end

function ALittleDeploy.DPLUITaskDetail:UpdateTaskInfo()
	self._save_button.disabled = true
	self._task_name_input.text = self._item_info.info.task_name
	self._task_desc_input.text = self._item_info.info.task_desc
	self._webhook_input.text = ALittle.String_Join(self._item_info.info.web_hook, "\n")
end

function ALittleDeploy.DPLUITaskDetail:HandleTaskBaseChanged(event)
	self._save_button.disabled = false
end

function ALittleDeploy.DPLUITaskDetail:HandleTaskSaveClick(event)
	local msg_client = ALittleDeploy.g_DPLWebLoginManager.msg_client
	if msg_client == nil or not msg_client:IsConnected() then
		g_AUITool:ShowNotice("提示", "当前还未连接成功!")
		return
	end
	if self._task_name_input.text == "" then
		g_AUITool:ShowNotice("提示", "任务名称不能为空!")
		return
	end
	local msg = {}
	msg.task_id = self._item_info.info.task_id
	msg.task_name = self._task_name_input.text
	msg.task_desc = self._task_desc_input.text
	msg.web_hook = ALittle.String_SplitSepList(self._webhook_input.text, {"\r", "\n"})
	local error = ALittle.IMsgCommon.InvokeRPC(1149037254, msg_client, msg)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
	end
end
ALittleDeploy.DPLUITaskDetail.HandleTaskSaveClick = Lua.CoWrap(ALittleDeploy.DPLUITaskDetail.HandleTaskSaveClick)

end