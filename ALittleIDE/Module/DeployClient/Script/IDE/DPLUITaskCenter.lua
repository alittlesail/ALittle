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

ALittle.RegStruct(2082241964, "DeployServer.C2SStartTask", {
name = "DeployServer.C2SStartTask", ns_name = "DeployServer", rl_name = "C2SStartTask", hash_code = 2082241964,
name_list = {"task_id"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(-2035971543, "DeployServer.D_JobInfo", {
name = "DeployServer.D_JobInfo", ns_name = "DeployServer", rl_name = "D_JobInfo", hash_code = -2035971543,
name_list = {"job_type","job_name","status","progress","detail"},
type_list = {"int","string","int","double","DeployServer.JobInfoDetail"},
option_map = {}
})
ALittle.RegStruct(-2015558870, "DeployServer.NMoveJob", {
name = "DeployServer.NMoveJob", ns_name = "DeployServer", rl_name = "NMoveJob", hash_code = -2015558870,
name_list = {"task_id","job_index","target_index"},
type_list = {"int","int","int"},
option_map = {}
})
ALittle.RegStruct(1811432266, "DeployServer.D_BuildInfo", {
name = "DeployServer.D_BuildInfo", ns_name = "DeployServer", rl_name = "D_BuildInfo", hash_code = 1811432266,
name_list = {"create_time"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(-1662612614, "DeployServer.NUpdateTaskInfo", {
name = "DeployServer.NUpdateTaskInfo", ns_name = "DeployServer", rl_name = "NUpdateTaskInfo", hash_code = -1662612614,
name_list = {"task_id","task_name","task_desc","web_hook"},
type_list = {"int","string","string","List<string>"},
option_map = {}
})
ALittle.RegStruct(-1533563228, "DeployServer.S2CCreateTask", {
name = "DeployServer.S2CCreateTask", ns_name = "DeployServer", rl_name = "S2CCreateTask", hash_code = -1533563228,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1487624699, "DeployServer.NCreateBuild", {
name = "DeployServer.NCreateBuild", ns_name = "DeployServer", rl_name = "NCreateBuild", hash_code = 1487624699,
name_list = {"task_id","build_info"},
type_list = {"int","DeployServer.D_BuildInfo"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1462309182, "DeployServer.NJobStatus", {
name = "DeployServer.NJobStatus", ns_name = "DeployServer", rl_name = "NJobStatus", hash_code = 1462309182,
name_list = {"task_id","index","status","progress"},
type_list = {"int","int","int","double"},
option_map = {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-1294478047, "DeployServer.S2CDeleteTask", {
name = "DeployServer.S2CDeleteTask", ns_name = "DeployServer", rl_name = "S2CDeleteTask", hash_code = -1294478047,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1287526271, "DeployServer.C2SCreateTask", {
name = "DeployServer.C2SCreateTask", ns_name = "DeployServer", rl_name = "C2SCreateTask", hash_code = 1287526271,
name_list = {"task_name"},
type_list = {"string"},
option_map = {}
})
ALittle.RegStruct(-1243553967, "DeployServer.NCreateTask", {
name = "DeployServer.NCreateTask", ns_name = "DeployServer", rl_name = "NCreateTask", hash_code = -1243553967,
name_list = {"task_info"},
type_list = {"DeployServer.D_TaskInfo"},
option_map = {}
})
ALittle.RegStruct(1232578034, "DeployServer.JobInfoDetail", {
name = "DeployServer.JobInfoDetail", ns_name = "DeployServer", rl_name = "JobInfoDetail", hash_code = 1232578034,
name_list = {"batch_dir","batch_cmd","batch_param","deepcopy_src","deepcopy_dst","deepcopy_ext","copyfile_src","copyfile_file","copyfile_dst","virtualkey_exepath","virtualkey_cmd","wait_p_exit_exe_path","wait_p_exit_max_time","createprocess_dir","createprocess_cmd","createprocess_param","killprocess_exe_path"},
type_list = {"string","string","string","string","string","string","string","List<string>","string","string","List<string>","List<string>","int","string","string","string","List<string>"},
option_map = {}
})
ALittle.RegStruct(-1164681133, "DeployServer.NDeleteTask", {
name = "DeployServer.NDeleteTask", ns_name = "DeployServer", rl_name = "NDeleteTask", hash_code = -1164681133,
name_list = {"task_id"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(-1050312971, "DeployServer.NDeleteJob", {
name = "DeployServer.NDeleteJob", ns_name = "DeployServer", rl_name = "NDeleteJob", hash_code = -1050312971,
name_list = {"task_id","job_index"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(917908039, "DeployServer.NCreateJob", {
name = "DeployServer.NCreateJob", ns_name = "DeployServer", rl_name = "NCreateJob", hash_code = 917908039,
name_list = {"task_id","job_index","job_info"},
type_list = {"int","int","DeployServer.D_JobInfo"},
option_map = {}
})
ALittle.RegStruct(816033453, "DeployServer.NTaskStatus", {
name = "DeployServer.NTaskStatus", ns_name = "DeployServer", rl_name = "NTaskStatus", hash_code = 816033453,
name_list = {"task_id","status","progress"},
type_list = {"int","int","double"},
option_map = {}
})
ALittle.RegStruct(808269380, "DeployServer.C2SDeleteTask", {
name = "DeployServer.C2SDeleteTask", ns_name = "DeployServer", rl_name = "C2SDeleteTask", hash_code = 808269380,
name_list = {"task_id"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(625732643, "DeployServer.S2CStartTask", {
name = "DeployServer.S2CStartTask", ns_name = "DeployServer", rl_name = "S2CStartTask", hash_code = 625732643,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-601303991, "DeployServer.S2CCopyTask", {
name = "DeployServer.S2CCopyTask", ns_name = "DeployServer", rl_name = "S2CCopyTask", hash_code = -601303991,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-542744414, "DeployServer.S2CTaskList", {
name = "DeployServer.S2CTaskList", ns_name = "DeployServer", rl_name = "S2CTaskList", hash_code = -542744414,
name_list = {"task_list"},
type_list = {"List<DeployServer.D_TaskInfo>"},
option_map = {}
})
ALittle.RegStruct(-478034953, "DeployServer.C2SCopyTask", {
name = "DeployServer.C2SCopyTask", ns_name = "DeployServer", rl_name = "C2SCopyTask", hash_code = -478034953,
name_list = {"task_id"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(390627548, "DeployServer.D_TaskInfo", {
name = "DeployServer.D_TaskInfo", ns_name = "DeployServer", rl_name = "D_TaskInfo", hash_code = 390627548,
name_list = {"task_id","task_name","task_desc","web_hook","create_time","status","progress","job_list","build_list"},
type_list = {"int","string","string","List<string>","int","int","double","List<DeployServer.D_JobInfo>","List<DeployServer.D_BuildInfo>"},
option_map = {}
})
ALittle.RegStruct(-369409021, "DeployClient.TaskItemInfo", {
name = "DeployClient.TaskItemInfo", ns_name = "DeployClient", rl_name = "TaskItemInfo", hash_code = -369409021,
name_list = {"item","info","_button","_status","detail"},
type_list = {"ALittle.DisplayObject","DeployServer.D_TaskInfo","ALittle.DisplayObject","ALittle.DisplayObject","DeployClient.DPLUITaskDetail"},
option_map = {}
})
ALittle.RegStruct(-206375730, "DeployServer.NDeleteBuild", {
name = "DeployServer.NDeleteBuild", ns_name = "DeployServer", rl_name = "NDeleteBuild", hash_code = -206375730,
name_list = {"task_id","build_index"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(-173628832, "DeployServer.NModifyJob", {
name = "DeployServer.NModifyJob", ns_name = "DeployServer", rl_name = "NModifyJob", hash_code = -173628832,
name_list = {"task_id","job_index","job_info"},
type_list = {"int","int","DeployServer.D_JobInfo"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
DeployClient.DPLUITaskCenter = Lua.Class(ALittle.DisplayLayout, "DeployClient.DPLUITaskCenter")

function DeployClient.DPLUITaskCenter:Ctor()
	___rawset(self, "_group", {})
	___rawset(self, "_item_map", {})
end

function DeployClient.DPLUITaskCenter:System_SetVDragCursor(event)
	ALittle.System_SetVDragCursor()
end

function DeployClient.DPLUITaskCenter:System_SetNormalCursor(event)
	ALittle.System_SetNormalCursor()
end

function DeployClient.DPLUITaskCenter:System_SetHDragCursor(event)
	ALittle.System_SetHDragCursor()
end

function DeployClient.DPLUITaskCenter:System_SetHVDragCursor(event)
	ALittle.System_SetHVDragCursor()
end

function DeployClient.DPLUITaskCenter:HandleGrid3UpResizeDrag(event)
	local up_size = self._task_grid3.up_size
	up_size = up_size + event.delta_x
	local max_size = self._task_grid3.width - self._task_grid3.down_size - 50
	if up_size > max_size then
		up_size = max_size
	end
	if up_size < 100 then
		up_size = 100
	end
	self._task_grid3.up_size = up_size
end

function DeployClient.DPLUITaskCenter:HandleGrid3DownResizeDrag(event)
	local down_size = self._task_grid3.down_size
	down_size = down_size - event.delta_x
	local max_size = self._task_grid3.width - self._task_grid3.down_size - 50
	if down_size > max_size then
		down_size = max_size
	end
	if down_size < 100 then
		down_size = 100
	end
	self._task_grid3.down_size = down_size
end

function DeployClient.DPLUITaskCenter:AddTaskItem(info)
	local task_info = {}
	task_info.item = DeployClient.g_Control:CreateControl("dpl_task_item", task_info)
	task_info.info = info
	task_info._button.text = info.task_name
	task_info._button._user_data = task_info
	task_info._button:AddEventListener(___all_struct[-641444818], self, self.HandleItemRButtonDown)
	task_info._button:AddEventListener(___all_struct[958494922], self, self.HandleItemChanged)
	task_info._button.group = self._group
	self._scroll_list:AddChild(task_info.item)
	if info.status == 0 then
		task_info._status.text = ""
	else
		task_info._status.text = ALittle.Math_Floor(info.progress * 100) / 100 .. "%"
	end
	self._item_map[info.task_id] = task_info
end

function DeployClient.DPLUITaskCenter:AddJobItem(task_id, job_index, info)
	local task_info = self._item_map[task_id]
	if task_info == nil then
		return
	end
	if job_index == nil or job_index <= 0 or job_index > ALittle.List_Len(task_info.info.job_list) then
		ALittle.List_Push(task_info.info.job_list, info)
		job_index = ALittle.List_Len(task_info.info.job_list)
	else
		ALittle.List_Insert(task_info.info.job_list, job_index, info)
	end
	if task_info.detail ~= nil then
		task_info.detail:AddJobItem(job_index, info)
	end
end

function DeployClient.DPLUITaskCenter:AddBuildItem(task_id, info)
	local task_info = self._item_map[task_id]
	if task_info == nil then
		return
	end
	ALittle.List_Push(task_info.info.build_list, info)
	if task_info.detail ~= nil then
		task_info.detail:AddBuildItem(info)
	end
end

function DeployClient.DPLUITaskCenter:HandleItemRButtonDown(event)
	local task_info = event.target._user_data
	local menu = AUIPlugin.AUIRightMenu()
	if task_info.info.status == 0 then
		menu:AddItem("执行", Lua.Bind(self.HandleStartTask, self, task_info))
	end
	menu:AddItem("复制", Lua.Bind(self.HandleCopyTask, self, task_info))
	if task_info.info.status == 0 then
		menu:AddItem("删除", Lua.Bind(self.HandleDeleteTask, self, task_info))
	end
	menu:Show()
end

function DeployClient.DPLUITaskCenter:HandleItemChanged(event)
	local task_info = event.target._user_data
	if event.target.selected then
		if task_info.detail == nil then
			task_info.detail = DeployClient.g_Control:CreateControl("dpl_task_detail")
			self._task_detail_container:AddChild(task_info.detail)
			task_info.detail:Init(task_info)
		end
		task_info.detail:Show()
	else
		if task_info.detail ~= nil then
			task_info.detail:Hide()
		end
	end
end

function DeployClient.DPLUITaskCenter:HandleStartTask(task_info)
	local msg_client = DeployClient.g_DPLWebLoginManager.msg_client
	if msg_client == nil or not msg_client:IsConnected() then
		g_AUITool:ShowNotice("提示", "当前还未连接成功!")
		return
	end
	local msg = {}
	msg.task_id = task_info.info.task_id
	local error = ALittle.IMsgCommon.InvokeRPC(2082241964, msg_client, msg)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
	end
end
DeployClient.DPLUITaskCenter.HandleStartTask = Lua.CoWrap(DeployClient.DPLUITaskCenter.HandleStartTask)

function DeployClient.DPLUITaskCenter:HandleCopyTask(task_info)
	local msg_client = DeployClient.g_DPLWebLoginManager.msg_client
	if msg_client == nil or not msg_client:IsConnected() then
		g_AUITool:ShowNotice("提示", "当前还未连接成功!")
		return
	end
	local msg = {}
	msg.task_id = task_info.info.task_id
	local error = ALittle.IMsgCommon.InvokeRPC(-478034953, msg_client, msg)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
	end
end
DeployClient.DPLUITaskCenter.HandleCopyTask = Lua.CoWrap(DeployClient.DPLUITaskCenter.HandleCopyTask)

function DeployClient.DPLUITaskCenter:HandleDeleteTask(task_info)
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
	msg.task_id = task_info.info.task_id
	local error = ALittle.IMsgCommon.InvokeRPC(808269380, msg_client, msg)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
	end
end
DeployClient.DPLUITaskCenter.HandleDeleteTask = Lua.CoWrap(DeployClient.DPLUITaskCenter.HandleDeleteTask)

function DeployClient.DPLUITaskCenter:RemoveTaskItem(task_id)
	local task_info = self._item_map[task_id]
	if task_info == nil then
		return
	end
	task_info._button.group = nil
	self._item_map[task_id] = nil
	self._scroll_list:RemoveChild(task_info.item)
	if task_info.detail ~= nil then
		self._task_detail_container:RemoveChild(task_info.detail)
	end
end

function DeployClient.DPLUITaskCenter:UpdateTaskItem(info)
	local task_info = self._item_map[info.task_id]
	if task_info == nil then
		return
	end
	task_info.info.task_name = info.task_name
	task_info._button.text = info.task_name
	task_info.info.task_desc = info.task_desc
	task_info.info.web_hook = info.web_hook
	if task_info.detail ~= nil then
		task_info.detail:UpdateTaskInfo()
	end
end

function DeployClient.DPLUITaskCenter:UpdateJobItem(info)
	local task_info = self._item_map[info.task_id]
	if task_info == nil then
		return
	end
	local job_info = task_info.info.job_list[info.job_index]
	if job_info == nil then
		return
	end
	task_info.info.job_list[info.job_index] = info.job_info
	if task_info.detail ~= nil then
		task_info.detail:UpdateJobInfo(info.job_index)
	end
end

function DeployClient.DPLUITaskCenter:RemoveJobItem(task_id, job_index)
	local task_info = self._item_map[task_id]
	if task_info == nil then
		return
	end
	if task_info.detail ~= nil then
		task_info.detail:RemoveJobItem(job_index)
	end
	ALittle.List_Remove(task_info.info.job_list, job_index)
end

function DeployClient.DPLUITaskCenter:MoveJobItem(task_id, job_index, target_index)
	local task_info = self._item_map[task_id]
	if task_info == nil then
		return
	end
	if task_info.detail ~= nil then
		task_info.detail:MoveJobItem(job_index, target_index)
	end
	local job = task_info.info.job_list[job_index]
	ALittle.List_Remove(task_info.info.job_list, job_index)
	local job_len = ALittle.List_Len(task_info.info.job_list)
	if target_index <= 0 or target_index > job_len then
		ALittle.List_Push(task_info.info.job_list, job)
	else
		ALittle.List_Insert(task_info.info.job_list, target_index, job)
	end
end

function DeployClient.DPLUITaskCenter:RemoveBuildItem(task_id, build_index)
	local task_info = self._item_map[task_id]
	if task_info == nil then
		return
	end
	if task_info.detail ~= nil then
		task_info.detail:RemoveBuildItem(build_index)
	end
	ALittle.List_Remove(task_info.info.build_list, build_index)
end

function DeployClient.DPLUITaskCenter:RemoveAllTaskItem()
	self._item_map = {}
	self._scroll_list:RemoveAllChild()
	self._task_detail_container:RemoveAllChild()
end

function DeployClient.DPLUITaskCenter:UpdateTaskStatus(info)
	local task_info = self._item_map[info.task_id]
	if task_info == nil then
		return
	end
	task_info.info.status = info.status
	task_info.info.progress = info.progress
	if info.status == 0 then
		task_info._status.text = ""
	else
		task_info._status.text = ALittle.Math_Floor(info.progress * 100) / 100 .. "%"
	end
end

function DeployClient.DPLUITaskCenter:UpdateJobStatus(msg)
	local task_info = self._item_map[msg.task_id]
	if task_info == nil then
		return
	end
	local job_info = task_info.info.job_list[msg.index]
	if job_info == nil then
		return
	end
	job_info.status = msg.status
	job_info.progress = msg.progress
	if task_info.detail ~= nil then
		task_info.detail:UpdateJobInfo(msg.index)
	end
end

function DeployClient.DPLUITaskCenter:HandleNewTaskClick(event)
	local msg_client = DeployClient.g_DPLWebLoginManager.msg_client
	if msg_client == nil or not msg_client:IsConnected() then
		g_AUITool:ShowNotice("提示", "当前还未连接成功!")
		return
	end
	local x, y = event.target:LocalToGlobal()
	local result = g_AUITool:ShowRename("", x, y + event.target.height, 200)
	if result == nil or result == "" then
		return
	end
	local msg = {}
	msg.task_name = result
	local error = ALittle.IMsgCommon.InvokeRPC(1287526271, msg_client, msg)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
	end
end
DeployClient.DPLUITaskCenter.HandleNewTaskClick = Lua.CoWrap(DeployClient.DPLUITaskCenter.HandleNewTaskClick)

function DeployClient.HandleS2CTaskList(sender, msg)
	DeployClient.g_DPLCenter.center.task_center:RemoveAllTaskItem()
	for index, info in ___ipairs(msg.task_list) do
		DeployClient.g_DPLCenter.center.task_center:AddTaskItem(info)
	end
end

ALittle.RegMsgCallback(-542744414, DeployClient.HandleS2CTaskList)
function DeployClient.HandleS2CCreateTask(sender, msg)
	DeployClient.g_DPLCenter.center.task_center:AddTaskItem(msg.task_info)
end

ALittle.RegMsgCallback(-1243553967, DeployClient.HandleS2CCreateTask)
function DeployClient.HandleNTaskStatus(sender, msg)
	DeployClient.g_DPLCenter.center.task_center:UpdateTaskStatus(msg)
end

ALittle.RegMsgCallback(816033453, DeployClient.HandleNTaskStatus)
function DeployClient.HandleNDeleteTask(sender, msg)
	DeployClient.g_DPLCenter.center.task_center:RemoveTaskItem(msg.task_id)
end

ALittle.RegMsgCallback(-1164681133, DeployClient.HandleNDeleteTask)
function DeployClient.HandleNUpdateTaskInfo(sender, msg)
	DeployClient.g_DPLCenter.center.task_center:UpdateTaskItem(msg)
end

ALittle.RegMsgCallback(-1662612614, DeployClient.HandleNUpdateTaskInfo)
function DeployClient.HandleNCreateJob(sender, msg)
	DeployClient.g_DPLCenter.center.task_center:AddJobItem(msg.task_id, msg.job_index, msg.job_info)
end

ALittle.RegMsgCallback(917908039, DeployClient.HandleNCreateJob)
function DeployClient.HandleNJobStatus(sender, msg)
	DeployClient.g_DPLCenter.center.task_center:UpdateJobStatus(msg)
end

ALittle.RegMsgCallback(1462309182, DeployClient.HandleNJobStatus)
function DeployClient.HandleNModifyJob(sender, msg)
	DeployClient.g_DPLCenter.center.task_center:UpdateJobItem(msg)
end

ALittle.RegMsgCallback(-173628832, DeployClient.HandleNModifyJob)
function DeployClient.HandleNDeleteJob(sender, msg)
	DeployClient.g_DPLCenter.center.task_center:RemoveJobItem(msg.task_id, msg.job_index)
end

ALittle.RegMsgCallback(-1050312971, DeployClient.HandleNDeleteJob)
function DeployClient.HandleNMoveJob(sender, msg)
	DeployClient.g_DPLCenter.center.task_center:MoveJobItem(msg.task_id, msg.job_index, msg.target_index)
end

ALittle.RegMsgCallback(-2015558870, DeployClient.HandleNMoveJob)
function DeployClient.HandleNCreateBuild(sender, msg)
	DeployClient.g_DPLCenter.center.task_center:AddBuildItem(msg.task_id, msg.build_info)
end

ALittle.RegMsgCallback(1487624699, DeployClient.HandleNCreateBuild)
function DeployClient.HandleNDeleteBuild(sender, msg)
	DeployClient.g_DPLCenter.center.task_center:RemoveBuildItem(msg.task_id, msg.build_index)
end

ALittle.RegMsgCallback(-206375730, DeployClient.HandleNDeleteBuild)
end