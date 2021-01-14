-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployClient == nil then _G.DeployClient = {} end
local DeployClient = DeployClient
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1492768812, "DeployServer.C2SModifyJob", {
name = "DeployServer.C2SModifyJob", ns_name = "DeployServer", rl_name = "C2SModifyJob", hash_code = -1492768812,
name_list = {"task_id","job_index","job_name","detail"},
type_list = {"int","int","string","DeployServer.JobInfoDetail"},
option_map = {}
})
ALittle.RegStruct(-1402593517, "DeployServer.S2CCreateJob", {
name = "DeployServer.S2CCreateJob", ns_name = "DeployServer", rl_name = "S2CCreateJob", hash_code = -1402593517,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1232578034, "DeployServer.JobInfoDetail", {
name = "DeployServer.JobInfoDetail", ns_name = "DeployServer", rl_name = "JobInfoDetail", hash_code = 1232578034,
name_list = {"batch_dir","batch_cmd","batch_param","deepcopy_src","deepcopy_dst","deepcopy_ext","copyfile_src","copyfile_file","copyfile_dst","virtualkey_exepath","virtualkey_cmd","wait_p_exit_exe_path","wait_p_exit_max_time","createprocess_dir","createprocess_cmd","createprocess_param","killprocess_exe_path"},
type_list = {"string","string","string","string","string","string","string","List<string>","string","string","List<string>","List<string>","int","string","string","string","List<string>"},
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
name_list = {"task_id","job_type","job_index","job_name","detail"},
type_list = {"int","int","int","string","DeployServer.JobInfoDetail"},
option_map = {}
})

assert(ALittle.Dialog, " extends class:ALittle.Dialog is nil")
DeployClient.CommonJobDialog = Lua.Class(ALittle.Dialog, "DeployClient.CommonJobDialog")

function DeployClient.CommonJobDialog:Ctor()
	___rawset(self, "_is_create", false)
	___rawset(self, "_task_id", 0)
	___rawset(self, "_job_index", 0)
end

function DeployClient.CommonJobDialog:Show(task_id, job_index, info)
	self._is_create = info == nil
	self._task_id = task_id
	self._job_index = job_index
	if info ~= nil then
		self._name.text = info.job_name
		self:ShowDetail(info.detail)
	else
		self._name.text = ""
		self:ShowDetail(nil)
	end
	DeployClient.g_DialogLayer:AddChild(self)
	self:MoveToTop()
end

function DeployClient.CommonJobDialog:ShowDetail(detail)
end

function DeployClient.CommonJobDialog.__getter:type()
	return nil
end

function DeployClient.CommonJobDialog:Hide()
	DeployClient.g_DialogLayer:RemoveChild(self)
end

function DeployClient.CommonJobDialog:GetDetail()
	return nil
end

function DeployClient.CommonJobDialog:HandleComfirmClick(event)
	local msg_client = DeployClient.g_DPLWebLoginManager.msg_client
	if msg_client == nil or not msg_client:IsConnected() then
		g_AUITool:ShowNotice("提示", "当前还未连接成功!")
		return
	end
	local detail = self:GetDetail()
	if self._is_create then
		local msg = {}
		msg.task_id = self._task_id
		msg.job_type = self.type
		msg.job_index = self._job_index
		msg.job_name = self._name.text
		msg.detail = detail
		local error = ALittle.IMsgCommon.InvokeRPC(-105312390, msg_client, msg)
		if error ~= nil then
			g_AUITool:ShowNotice("提示", error)
		end
	else
		local msg = {}
		msg.task_id = self._task_id
		msg.job_index = self._job_index
		msg.job_name = self._name.text
		msg.detail = detail
		local error = ALittle.IMsgCommon.InvokeRPC(-1492768812, msg_client, msg)
		if error ~= nil then
			g_AUITool:ShowNotice("提示", error)
		end
	end
	self:Hide()
end
DeployClient.CommonJobDialog.HandleComfirmClick = Lua.CoWrap(DeployClient.CommonJobDialog.HandleComfirmClick)

function DeployClient.CommonJobDialog:HandleCancelClick(event)
	self:Hide()
end

end