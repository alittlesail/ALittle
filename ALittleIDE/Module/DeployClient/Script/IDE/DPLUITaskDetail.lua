-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployClient == nil then _G.DeployClient = {} end
local DeployClient = DeployClient
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-2127611090, "DeployClient.BuildItemInfo", {
name = "DeployClient.BuildItemInfo", ns_name = "DeployClient", rl_name = "BuildItemInfo", hash_code = -2127611090,
name_list = {"item","info","_button","_download_button"},
type_list = {"ALittle.DisplayObject","DeployServer.D_BuildInfo","ALittle.DisplayObject","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-2035971543, "DeployServer.D_JobInfo", {
name = "DeployServer.D_JobInfo", ns_name = "DeployServer", rl_name = "D_JobInfo", hash_code = -2035971543,
name_list = {"job_type","job_name","status","progress","detail"},
type_list = {"int","string","int","double","DeployServer.JobInfoDetail"},
option_map = {}
})
ALittle.RegStruct(-2031251578, "DeployServer.C2SCopyJob", {
name = "DeployServer.C2SCopyJob", ns_name = "DeployServer", rl_name = "C2SCopyJob", hash_code = -2031251578,
name_list = {"task_id","job_index"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(1984174335, "DeployServer.S2CDeleteBuild", {
name = "DeployServer.S2CDeleteBuild", ns_name = "DeployServer", rl_name = "S2CDeleteBuild", hash_code = 1984174335,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1811432266, "DeployServer.D_BuildInfo", {
name = "DeployServer.D_BuildInfo", ns_name = "DeployServer", rl_name = "D_BuildInfo", hash_code = 1811432266,
name_list = {"create_time"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(1809409109, "DeployServer.S2CDeleteJob", {
name = "DeployServer.S2CDeleteJob", ns_name = "DeployServer", rl_name = "S2CDeleteJob", hash_code = 1809409109,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1800966813, "ALittle.UISystemSelectDirectoryEvent", {
name = "ALittle.UISystemSelectDirectoryEvent", ns_name = "ALittle", rl_name = "UISystemSelectDirectoryEvent", hash_code = 1800966813,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})
ALittle.RegStruct(1624339767, "DeployServer.S2CMoveJob", {
name = "DeployServer.S2CMoveJob", ns_name = "DeployServer", rl_name = "S2CMoveJob", hash_code = 1624339767,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1566214727, "DeployServer.S2CUpdateTaskInfo", {
name = "DeployServer.S2CUpdateTaskInfo", ns_name = "DeployServer", rl_name = "S2CUpdateTaskInfo", hash_code = 1566214727,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-1320965296, "DeployServer.C2SDeleteJob", {
name = "DeployServer.C2SDeleteJob", ns_name = "DeployServer", rl_name = "C2SDeleteJob", hash_code = -1320965296,
name_list = {"task_id","job_index"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(1254025721, "DeployServer.C2SDeleteBuild", {
name = "DeployServer.C2SDeleteBuild", ns_name = "DeployServer", rl_name = "C2SDeleteBuild", hash_code = 1254025721,
name_list = {"task_id","build_index"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(1232578034, "DeployServer.JobInfoDetail", {
name = "DeployServer.JobInfoDetail", ns_name = "DeployServer", rl_name = "JobInfoDetail", hash_code = 1232578034,
name_list = {"batch_dir","batch_cmd","batch_param","deepcopy_src","deepcopy_dst","deepcopy_ext","copyfile_src","copyfile_file","copyfile_dst","virtualkey_exepath","virtualkey_cmd","wait_p_exit_exe_path","wait_p_exit_max_time","createprocess_dir","createprocess_cmd","createprocess_param","killprocess_exe_path"},
type_list = {"string","string","string","string","string","string","string","List<string>","string","string","List<string>","List<string>","int","string","string","string","List<string>"},
option_map = {}
})
ALittle.RegStruct(1149037254, "DeployServer.C2SUpdateTaskInfo", {
name = "DeployServer.C2SUpdateTaskInfo", ns_name = "DeployServer", rl_name = "C2SUpdateTaskInfo", hash_code = 1149037254,
name_list = {"task_id","task_name","task_desc","web_hook"},
type_list = {"int","string","string","List<string>"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(874244823, "DeployServer.S2CCopyJob", {
name = "DeployServer.S2CCopyJob", ns_name = "DeployServer", rl_name = "S2CCopyJob", hash_code = 874244823,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(629373421, "DeployClient.JobItemInfo", {
name = "DeployClient.JobItemInfo", ns_name = "DeployClient", rl_name = "JobItemInfo", hash_code = 629373421,
name_list = {"item","info","_button","_status"},
type_list = {"ALittle.DisplayObject","DeployServer.D_JobInfo","ALittle.DisplayObject","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-616678126, "DeployServer.C2SMoveJob", {
name = "DeployServer.C2SMoveJob", ns_name = "DeployServer", rl_name = "C2SMoveJob", hash_code = -616678126,
name_list = {"task_id","job_index","target_index"},
type_list = {"int","int","int"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
DeployClient.DPLUITaskDetail = Lua.Class(ALittle.DisplayLayout, "DeployClient.DPLUITaskDetail")

function DeployClient.DPLUITaskDetail:Ctor()
	___rawset(self, "_job_group", {})
	___rawset(self, "_build_group", {})
end

function DeployClient.DPLUITaskDetail:Init(task_item)
	self._task_item = task_item
	self:UpdateTaskInfo()
	self:RefreshJobInfo()
	self:RefreshBuildInfo()
end

function DeployClient.DPLUITaskDetail:Show()
	self.visible = true
	if not self._save_button.disabled then
		self:UpdateTaskInfo()
	end
end

function DeployClient.DPLUITaskDetail:Hide()
	self.visible = false
end

function DeployClient.DPLUITaskDetail:UpdateTaskInfo()
	self._save_button.disabled = true
	self._task_name_input.text = self._task_item.info.task_name
	self._task_desc_input.text = self._task_item.info.task_desc
	self._webhook_input.text = ALittle.String_Join(self._task_item.info.web_hook, "\n")
end

function DeployClient.DPLUITaskDetail:UpdateJobInfo(index)
	local job_info = self._task_item.info.job_list[index]
	if job_info == nil then
		return
	end
	local job_item = self._job_list.childs[index]._user_data
	job_item.info = job_info
	self:RefreshJobItem(job_item)
end

function DeployClient.DPLUITaskDetail:RemoveJobItem(index)
	local job_info = self._task_item.info.job_list[index]
	if job_info == nil then
		return
	end
	self._job_list:SpliceChild(index, 1)
end

function DeployClient.DPLUITaskDetail:MoveJobItem(index, target_index)
	local job_info = self._task_item.info.job_list[index]
	if job_info == nil then
		return
	end
	self._job_list:SetChildIndex(self._job_list:GetChildByIndex(index), target_index)
end

function DeployClient.DPLUITaskDetail:RemoveBuildItem(index)
	local build_info = self._task_item.info.build_list[index]
	if build_info == nil then
		return
	end
	self._build_list:SpliceChild(index, 1)
end

function DeployClient.DPLUITaskDetail:RefreshJobInfo()
	self._job_list:RemoveAllChild()
	for index, job_info in ___ipairs(self._task_item.info.job_list) do
		self:AddJobItem(nil, job_info)
	end
end

function DeployClient.DPLUITaskDetail:RefreshBuildInfo()
	self._build_list:RemoveAllChild()
	for index, build_info in ___ipairs(self._task_item.info.build_list) do
		self:AddBuildItem(build_info)
	end
end

function DeployClient.DPLUITaskDetail:HandleTaskBaseChanged(event)
	self._save_button.disabled = false
end

function DeployClient.DPLUITaskDetail:HandleTaskStart()
	for index, child in ___ipairs(self._job_list.childs) do
		local job_item = child._user_data
		job_item._status.text = "等待"
	end
end

function DeployClient.DPLUITaskDetail:HandleTaskSaveClick(event)
	local msg_client = DeployClient.g_DPLWebLoginManager.msg_client
	if msg_client == nil or not msg_client:IsConnected() then
		g_AUITool:ShowNotice("提示", "当前还未连接成功!")
		return
	end
	if self._task_name_input.text == "" then
		g_AUITool:ShowNotice("提示", "任务名称不能为空!")
		return
	end
	local msg = {}
	msg.task_id = self._task_item.info.task_id
	msg.task_name = self._task_name_input.text
	msg.task_desc = self._task_desc_input.text
	msg.web_hook = ALittle.String_SplitSepList(self._webhook_input.text, {"\r", "\n"})
	local error = ALittle.IMsgCommon.InvokeRPC(1149037254, msg_client, msg)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
	end
end
DeployClient.DPLUITaskDetail.HandleTaskSaveClick = Lua.CoWrap(DeployClient.DPLUITaskDetail.HandleTaskSaveClick)

function DeployClient.DPLUITaskDetail:HandleNewJobClick(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("批处理", Lua.Bind(self.HandleNewCommonJob, self, "batch_job_dialog"))
	menu:AddItem("复制目录", Lua.Bind(self.HandleNewCommonJob, self, "deepcopy_job_dialog"))
	menu:AddItem("复制文件", Lua.Bind(self.HandleNewCommonJob, self, "copyfile_job_dialog"))
	menu:AddItem("发送命令", Lua.Bind(self.HandleNewCommonJob, self, "sendvirtualkey_job_dialog"))
	menu:AddItem("等待进程退出", Lua.Bind(self.HandleNewCommonJob, self, "waitprocessexit_job_dialog"))
	menu:AddItem("创建进程", Lua.Bind(self.HandleNewCommonJob, self, "createprocess_job_dialog"))
	menu:AddItem("杀死进程", Lua.Bind(self.HandleNewCommonJob, self, "killprocess_job_dialog"))
	menu:Show()
end

function DeployClient.DPLUITaskDetail:HandleStartTaskClick(event)
	DeployClient.g_DPLCenter.center.task_center:HandleStartTask(self._task_item)
end

function DeployClient.DPLUITaskDetail:HandleNewCommonJob(ui)
	local dialog = DeployClient.g_Control:CreateControl(ui)
	dialog:Show(self._task_item.info.task_id, nil, nil)
end

function DeployClient.DPLUITaskDetail:AddJobItem(job_index, job_info)
	local job_item = {}
	job_item.info = job_info
	job_item.item = DeployClient.g_Control:CreateControl("dpl_job_item", job_item)
	job_item.item._user_data = job_item
	job_item._button._user_data = job_item
	job_item._button.group = self._job_group
	job_item._button:AddEventListener(___all_struct[-641444818], self, self.HandleJobRButtonDown)
	self._job_list:AddChild(job_item.item, job_index)
	self:RefreshJobItem(job_item)
end

function DeployClient.DPLUITaskDetail:AddBuildItem(build_info)
	local build_item = {}
	build_item.info = build_info
	build_item.item = DeployClient.g_Control:CreateControl("dpl_build_item", build_item)
	build_item.item._user_data = build_item
	build_item._button._user_data = build_item
	build_item._button.group = self._build_group
	build_item._button:AddEventListener(___all_struct[-641444818], self, self.HandleBuildRButtonDown)
	build_item._button:AddEventListener(___all_struct[958494922], self, self.HandlePreSeeBuild)
	build_item._download_button:AddEventListener(___all_struct[1800966813], self, self.HandleDownloadBuild)
	build_item._download_button._user_data = build_item
	self._build_list:AddChild(build_item.item)
	self._build_list:ScrollToBottom()
	build_item._button.text = ALittle.Time_GetCurDate(build_info.create_time)
end

function DeployClient.DPLUITaskDetail:RefreshJobItem(job_item)
	if job_item.info.job_type == 1 then
		job_item._button.text = "[批处理] " .. job_item.info.job_name .. ":" .. job_item.info.detail.batch_cmd
	elseif job_item.info.job_type == 2 then
		job_item._button.text = "[复制目录] " .. job_item.info.job_name .. ":" .. job_item.info.detail.deepcopy_src .. "->" .. job_item.info.detail.deepcopy_dst
	elseif job_item.info.job_type == 3 then
		job_item._button.text = "[复制文件] " .. job_item.info.job_name .. ":" .. job_item.info.detail.copyfile_src .. "->" .. job_item.info.detail.copyfile_dst
	elseif job_item.info.job_type == 4 then
		job_item._button.text = "[发送命令] " .. job_item.info.job_name .. ":" .. job_item.info.detail.virtualkey_exepath
	elseif job_item.info.job_type == 5 then
		job_item._button.text = "[等待进程退出] " .. job_item.info.job_name
	elseif job_item.info.job_type == 6 then
		job_item._button.text = "[创建进程] " .. job_item.info.job_name .. ":" .. job_item.info.detail.createprocess_cmd
	elseif job_item.info.job_type == 7 then
		job_item._button.text = "[杀死进程] " .. job_item.info.job_name
	end
	if self._task_item.info.status == 0 then
		job_item._status.text = ""
	else
		if job_item.info.status == 0 then
			job_item._status.text = "等待"
		elseif job_item.info.status == 1 then
			job_item._status.text = ALittle.Math_Floor(job_item.info.progress * 10000) / 100 .. "%"
		elseif job_item.info.status == 2 then
			job_item._status.text = "完成"
		elseif job_item.info.status == 3 then
			job_item._status.text = "失败"
		end
	end
end

function DeployClient.DPLUITaskDetail:HandleJobRButtonDown(event)
	local job_item = event.target._user_data
	local job_index = self._job_list:GetChildIndex(job_item.item)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("修改", Lua.Bind(self.HandleModifyJob, self, job_item, job_index))
	menu:AddItem("上移", Lua.Bind(self.HandleMoveJob, self, job_item, job_index, job_index - 1))
	menu:AddItem("下移", Lua.Bind(self.HandleMoveJob, self, job_item, job_index, job_index + 1))
	menu:AddItem("复制", Lua.Bind(self.HandleCopyJob, self, job_item, job_index))
	menu:AddItem("删除", Lua.Bind(self.HandleDeleteJob, self, job_item, job_index))
	menu:Show()
end

function DeployClient.DPLUITaskDetail:HandleBuildRButtonDown(event)
	local build_item = event.target._user_data
	local build_index = self._build_list:GetChildIndex(build_item.item)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("删除", Lua.Bind(self.HandleDeleteBuild, self, build_item, build_index))
	menu:Show()
end

function DeployClient.DPLUITaskDetail:HandlePreSeeBuild(event)
	local build_item = event.target._user_data
	local build_index = self._build_list:GetChildIndex(build_item.item)
	DeployClient.g_DPLCenter.center.task_center._build_edit.text = ""
	local msg = {}
	msg.task_id = self._task_item.info.task_id
	msg.build_index = build_index
	local sender = DeployClient.g_DPLCenter:CreateHttpSender()
	local error, rsp = ALittle.IHttpSender.Invoke("DeployServer.QPreSeeBuild", sender, msg)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
		return
	end
	DeployClient.g_DPLCenter.center.task_center._build_edit.text = ALittle.String_Join(rsp.log_list, "\r\n")
end
DeployClient.DPLUITaskDetail.HandlePreSeeBuild = Lua.CoWrap(DeployClient.DPLUITaskDetail.HandlePreSeeBuild)

function DeployClient.DPLUITaskDetail:HandleDownloadBuild(event)
	if event.path == nil or event.path == "" then
		return
	end
	local build_item = event.target._user_data
	local build_index = self._build_list:GetChildIndex(build_item.item)
	local msg = {}
	msg.task_id = self._task_item.info.task_id
	msg.build_index = build_index
	local sender = DeployClient.g_DPLCenter:CreateHttpFileSender(event.path .. "/" .. ALittle.Time_GetCurDate(build_item.info.create_time) .. ".log")
	local error = ALittle.IHttpFileSender.InvokeDownload("DeployServer.QDownloadBuild", sender, msg)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
	end
end
DeployClient.DPLUITaskDetail.HandleDownloadBuild = Lua.CoWrap(DeployClient.DPLUITaskDetail.HandleDownloadBuild)

function DeployClient.DPLUITaskDetail:HandleModifyJob(info, index)
	local ui = nil
	if info.info.job_type == 1 then
		ui = "batch_job_dialog"
	elseif info.info.job_type == 2 then
		ui = "deepcopy_job_dialog"
	elseif info.info.job_type == 3 then
		ui = "copyfile_job_dialog"
	elseif info.info.job_type == 4 then
		ui = "sendvirtualkey_job_dialog"
	elseif info.info.job_type == 5 then
		ui = "waitprocessexit_job_dialog"
	elseif info.info.job_type == 6 then
		ui = "createprocess_job_dialog"
	elseif info.info.job_type == 7 then
		ui = "killprocess_job_dialog"
	end
	if ui ~= nil then
		local dialog = DeployClient.g_Control:CreateControl(ui)
		dialog:Show(self._task_item.info.task_id, index, info.info)
	end
end

function DeployClient.DPLUITaskDetail:HandleMoveJob(info, index, new_index)
	local msg_client = DeployClient.g_DPLWebLoginManager.msg_client
	if msg_client == nil or not msg_client:IsConnected() then
		g_AUITool:ShowNotice("提示", "当前还未连接成功!")
		return
	end
	local msg = {}
	msg.task_id = self._task_item.info.task_id
	msg.job_index = index
	msg.target_index = new_index
	local error = ALittle.IMsgCommon.InvokeRPC(-616678126, msg_client, msg)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
	end
end
DeployClient.DPLUITaskDetail.HandleMoveJob = Lua.CoWrap(DeployClient.DPLUITaskDetail.HandleMoveJob)

function DeployClient.DPLUITaskDetail:HandleCopyJob(info, index)
	local msg_client = DeployClient.g_DPLWebLoginManager.msg_client
	if msg_client == nil or not msg_client:IsConnected() then
		g_AUITool:ShowNotice("提示", "当前还未连接成功!")
		return
	end
	local msg = {}
	msg.task_id = self._task_item.info.task_id
	msg.job_index = index
	local error = ALittle.IMsgCommon.InvokeRPC(-2031251578, msg_client, msg)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
	end
end
DeployClient.DPLUITaskDetail.HandleCopyJob = Lua.CoWrap(DeployClient.DPLUITaskDetail.HandleCopyJob)

function DeployClient.DPLUITaskDetail:HandleDeleteJob(info, index)
	local msg_client = DeployClient.g_DPLWebLoginManager.msg_client
	if msg_client == nil or not msg_client:IsConnected() then
		g_AUITool:ShowNotice("提示", "当前还未连接成功!")
		return
	end
	local result = g_AUITool:DeleteNotice("删除", "确定要删除该任务吗?")
	if result ~= "YES" then
		return
	end
	local msg = {}
	msg.task_id = self._task_item.info.task_id
	msg.job_index = index
	local error = ALittle.IMsgCommon.InvokeRPC(-1320965296, msg_client, msg)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
	end
end
DeployClient.DPLUITaskDetail.HandleDeleteJob = Lua.CoWrap(DeployClient.DPLUITaskDetail.HandleDeleteJob)

function DeployClient.DPLUITaskDetail:HandleDeleteBuild(info, index)
	local msg_client = DeployClient.g_DPLWebLoginManager.msg_client
	if msg_client == nil or not msg_client:IsConnected() then
		g_AUITool:ShowNotice("提示", "当前还未连接成功!")
		return
	end
	local result = g_AUITool:DeleteNotice("删除", "确定要删除该构建信息吗?")
	if result ~= "YES" then
		return
	end
	local msg = {}
	msg.task_id = self._task_item.info.task_id
	msg.build_index = index
	local error = ALittle.IMsgCommon.InvokeRPC(1254025721, msg_client, msg)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
	end
end
DeployClient.DPLUITaskDetail.HandleDeleteBuild = Lua.CoWrap(DeployClient.DPLUITaskDetail.HandleDeleteBuild)

end