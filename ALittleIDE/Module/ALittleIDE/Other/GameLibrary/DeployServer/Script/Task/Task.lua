-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployServer == nil then _G.DeployServer = {} end
local DeployServer = DeployServer
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
ALittle.RegStruct(-1662612614, "DeployServer.NUpdateTaskInfo", {
name = "DeployServer.NUpdateTaskInfo", ns_name = "DeployServer", rl_name = "NUpdateTaskInfo", hash_code = -1662612614,
name_list = {"task_id","task_name","task_desc","web_hook"},
type_list = {"int","string","string","List<string>"},
option_map = {}
})
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
ALittle.RegStruct(816033453, "DeployServer.NTaskStatus", {
name = "DeployServer.NTaskStatus", ns_name = "DeployServer", rl_name = "NTaskStatus", hash_code = 816033453,
name_list = {"task_id","status","progress"},
type_list = {"int","int","double"},
option_map = {}
})
ALittle.RegStruct(625732643, "DeployServer.S2CStartTask", {
name = "DeployServer.S2CStartTask", ns_name = "DeployServer", rl_name = "S2CStartTask", hash_code = 625732643,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(390627548, "DeployServer.D_TaskInfo", {
name = "DeployServer.D_TaskInfo", ns_name = "DeployServer", rl_name = "D_TaskInfo", hash_code = 390627548,
name_list = {"task_id","task_name","task_desc","web_hook","create_time","status","progress","job_list"},
type_list = {"int","string","string","List<string>","int","int","double","List<DeployServer.D_JobInfo>"},
option_map = {}
})
ALittle.RegStruct(276033112, "DeployServer.TaskInfo", {
name = "DeployServer.TaskInfo", ns_name = "DeployServer", rl_name = "TaskInfo", hash_code = 276033112,
name_list = {"task_id","task_name","task_desc","web_hook","job_list","create_time"},
type_list = {"int","string","string","Map<string,bool>","List<DeployServer.JobInfo>","int"},
option_map = {primary="task_id"}
})

DeployServer.TaskStatus = {
	IDLE = 0,
	DOING = 1,
}

DeployServer.Task = Lua.Class(nil, "DeployServer.Task")

function DeployServer.Task:Ctor(info)
	___rawset(self, "_job_list", {})
	___rawset(self, "_status", 0)
	___rawset(self, "_progress", 0)
	___rawset(self, "_info", info)
	___rawset(self, "_upper_name", ALittle.String_Upper(info.task_name))
	if info.job_list ~= nil then
		for index, job_info in ___ipairs(info.job_list) do
			local job = DeployServer.CreateJob(self, job_info)
			self._job_list[index] = job
		end
	end
end

function DeployServer.Task:Start()
	if self._status ~= 0 then
		return "当前任务不是空闲状态"
	end
	self:StartImpl()
	return nil
end

function DeployServer.Task:StartImpl()
	self._status = 1
	self._progress = 0
	self:SendStatus()
	for index, job in ___ipairs(self._job_list) do
		local error = job:Doing()
		if error ~= nil then
			ALittle.Log("task" .. self._info.task_id .. ":" .. self._info.task_name .. " doing failed:" .. error)
			break
		end
		self._progress = (index - 1) / ALittle.List_Len(self._job_list)
		self:SendStatus()
	end
	self._status = 0
	self._progress = 1
	self:SendStatus()
end
DeployServer.Task.StartImpl = Lua.CoWrap(DeployServer.Task.StartImpl)

function DeployServer.Task:SendStatus()
	local msg = {}
	msg.task_id = self._info.task_id
	msg.status = self._status
	msg.progress = self._progress
	A_WebAccountManager:SendMsgToAll(___all_struct[816033453], msg)
end

function DeployServer.Task.__getter:status()
	return self._status
end

function DeployServer.Task:StartByWebHook(url)
	if self._info.web_hook == nil then
		return
	end
	for key, open in ___pairs(self._info.web_hook) do
		if key == url and open then
			self:Start()
			break
		end
	end
end

function DeployServer.Task.__getter:info()
	return self._info
end

function DeployServer.Task.__getter:upper_name()
	return self._upper_name
end

function DeployServer.Task:UpdateInfo(msg)
	self._info.task_name = msg.task_name
	self._info.task_desc = msg.task_desc
	self._info.web_hook = {}
	for index, value in ___ipairs(msg.web_hook) do
		self._info.web_hook[value] = true
	end
	self._upper_name = ALittle.String_Upper(msg.task_name)
	local ntf = {}
	ntf.task_id = msg.task_id
	ntf.task_name = msg.task_name
	ntf.task_desc = msg.task_desc
	ntf.web_hook = msg.web_hook
	A_WebAccountManager:SendMsgToAll(___all_struct[-1662612614], ntf)
end

function DeployServer.Task.__getter:data_info()
	local data = {}
	data.task_id = self._info.task_id
	data.task_name = self._info.task_name
	data.task_desc = self._info.task_desc
	data.create_time = self._info.create_time
	data.status = self._status
	data.progress = self._progress
	data.web_hook = {}
	if self._info.web_hook ~= nil then
		for web_hook, _ in ___pairs(self._info.web_hook) do
			ALittle.List_Push(data.web_hook, web_hook)
		end
	end
	data.job_list = {}
	for index, job in ___ipairs(self._job_list) do
		ALittle.List_Push(data.job_list, job.data_info)
	end
	return data
end

function DeployServer.HandleC2SStartTask(sender, msg)
	local ___COROUTINE = coroutine.running()
	A_WebAccountManager:CheckLoginByClient(sender)
	local task = g_TaskManager:GetTask(msg.task_id)
	Lua.Assert(task ~= nil, "任务不存在")
	local error = task:Start()
	Lua.Assert(error == nil, error)
	return {}
end

ALittle.RegMsgRpcCallback(2082241964, DeployServer.HandleC2SStartTask, 625732643)
function DeployServer.HandleC2SUpdateTaskInfo(sender, msg)
	local ___COROUTINE = coroutine.running()
	A_WebAccountManager:CheckLoginByClient(sender)
	local task = g_TaskManager:GetTask(msg.task_id)
	Lua.Assert(task ~= nil, "任务不存在")
	task:UpdateInfo(msg)
	return {}
end

ALittle.RegMsgRpcCallback(1149037254, DeployServer.HandleC2SUpdateTaskInfo, 1566214727)
end