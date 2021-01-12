-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1492768812, "DeployServer.C2SModifyJob", {
name = "DeployServer.C2SModifyJob", ns_name = "DeployServer", rl_name = "C2SModifyJob", hash_code = -1492768812,
name_list = {"task_id","job_index","job_name","batch_cmd","batch_param"},
type_list = {"int","int","string","string","string"},
option_map = {}
})
ALittle.RegStruct(-1402593517, "DeployServer.S2CCreateJob", {
name = "DeployServer.S2CCreateJob", ns_name = "DeployServer", rl_name = "S2CCreateJob", hash_code = -1402593517,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(812356121, "DeployServer.S2CModifyJob", {
name = "DeployServer.S2CModifyJob", ns_name = "DeployServer", rl_name = "S2CModifyJob", hash_code = 812356121,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-105312390, "DeployServer.C2SCreateJob", {
name = "DeployServer.C2SCreateJob", ns_name = "DeployServer", rl_name = "C2SCreateJob", hash_code = -105312390,
name_list = {"task_id","job_type","job_index","job_name","batch_cmd","batch_param"},
type_list = {"int","int","int","string","string","string"},
option_map = {}
})

assert(ALittle.Dialog, " extends class:ALittle.Dialog is nil")
ALittleDeploy.BatchJobDialog = Lua.Class(ALittle.Dialog, "ALittleDeploy.BatchJobDialog")

function ALittleDeploy.BatchJobDialog:Ctor()
	___rawset(self, "_is_create", false)
	___rawset(self, "_task_id", 0)
	___rawset(self, "_job_index", 0)
end

function ALittleDeploy.BatchJobDialog:Show(task_id, job_index, info)
	self._is_create = info == nil
	self._task_id = task_id
	self._job_index = job_index
	if info ~= nil then
		self._name.text = info.job_name
		self._cmd.text = info.batch_cmd
		self._param.text = info.batch_param
	else
		self._name.text = ""
		self._cmd.text = ""
		self._param.text = ""
	end
	ALittleDeploy.g_DialogLayer:AddChild(self)
	self:MoveToTop()
end

function ALittleDeploy.BatchJobDialog:Hide()
	ALittleDeploy.g_DialogLayer:RemoveChild(self)
end

function ALittleDeploy.BatchJobDialog:HandleComfirmClick(event)
	local msg_client = ALittleDeploy.g_DPLWebLoginManager.msg_client
	if msg_client == nil or not msg_client:IsConnected() then
		g_AUITool:ShowNotice("提示", "当前还未连接成功!")
		return
	end
	if self._is_create then
		local msg = {}
		msg.task_id = self._task_id
		msg.job_type = 1
		msg.job_index = self._job_index
		msg.job_name = self._name.text
		msg.batch_cmd = self._cmd.text
		msg.batch_param = self._param.text
		local error = ALittle.IMsgCommon.InvokeRPC(-105312390, msg_client, msg)
		if error ~= nil then
			g_AUITool:ShowNotice("提示", error)
		end
	else
		local msg = {}
		msg.task_id = self._task_id
		msg.job_index = self._job_index
		msg.job_name = self._name.text
		msg.batch_cmd = self._cmd.text
		msg.batch_param = self._param.text
		local error = ALittle.IMsgCommon.InvokeRPC(-1492768812, msg_client, msg)
		if error ~= nil then
			g_AUITool:ShowNotice("提示", error)
		end
	end
	self:Hide()
end
ALittleDeploy.BatchJobDialog.HandleComfirmClick = Lua.CoWrap(ALittleDeploy.BatchJobDialog.HandleComfirmClick)

function ALittleDeploy.BatchJobDialog:HandleCancelClick(event)
	self:Hide()
end

end