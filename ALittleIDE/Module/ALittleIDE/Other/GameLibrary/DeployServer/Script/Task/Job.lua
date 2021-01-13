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

ALittle.RegStruct(-2035971543, "DeployServer.D_JobInfo", {
name = "DeployServer.D_JobInfo", ns_name = "DeployServer", rl_name = "D_JobInfo", hash_code = -2035971543,
name_list = {"job_type","job_name","status","progress","detail"},
type_list = {"int","string","int","double","DeployServer.JobInfoDetail"},
option_map = {}
})
ALittle.RegStruct(1811432266, "DeployServer.D_BuildInfo", {
name = "DeployServer.D_BuildInfo", ns_name = "DeployServer", rl_name = "D_BuildInfo", hash_code = 1811432266,
name_list = {"create_time"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(1544249038, "DeployServer.JobInfo", {
name = "DeployServer.JobInfo", ns_name = "DeployServer", rl_name = "JobInfo", hash_code = 1544249038,
name_list = {"job_type","job_name","detail"},
type_list = {"int","string","DeployServer.JobInfoDetail"},
option_map = {}
})
ALittle.RegStruct(1462309182, "DeployServer.NJobStatus", {
name = "DeployServer.NJobStatus", ns_name = "DeployServer", rl_name = "NJobStatus", hash_code = 1462309182,
name_list = {"task_id","index","status","progress"},
type_list = {"int","int","int","double"},
option_map = {}
})
ALittle.RegStruct(1232578034, "DeployServer.JobInfoDetail", {
name = "DeployServer.JobInfoDetail", ns_name = "DeployServer", rl_name = "JobInfoDetail", hash_code = 1232578034,
name_list = {"batch_dir","batch_cmd","batch_param","deepcopy_src","deepcopy_dst","deepcopy_ext"},
type_list = {"string","string","string","string","string","string"},
option_map = {}
})

DeployServer.JobType = {
	NONE = 0,
	BATCH = 1,
	DEEPCOPY = 2,
}

DeployServer.JobStatus = {
	WAITING = 0,
	DOING = 1,
	COMPLETED = 2,
}

DeployServer.Job = Lua.Class(nil, "DeployServer.Job")

function DeployServer.Job:Ctor(task, info)
	___rawset(self, "_status", 0)
	___rawset(self, "_progress", 0)
	___rawset(self, "_task", task)
	___rawset(self, "_info", info)
end

function DeployServer.Job.__getter:info()
	return self._info
end

function DeployServer.Job.__getter:data_info()
	local data = {}
	data.job_type = self._info.job_type
	data.job_name = self._info.job_name
	data.status = self._status
	data.progress = self._progress
	data.detail = self._info.detail
	return data
end

function DeployServer.Job:Modify(msg)
	self._info.job_name = msg.job_name
	self._info.detail = msg.detail
end

function DeployServer.Job:Waiting()
	self._status = 0
	self._progress = 0
	self:SendStatus()
end

function DeployServer.Job:Doing(build_info)
	local ___COROUTINE = coroutine.running()
	self._status = 1
	self._progress = 0
	self:SendStatus()
	ALittle.List_Push(build_info.log_list, "===>[" .. ALittle.Time_GetCurDate() .. "]Job Begin:" .. self._info.job_name)
	local error, log = self:Execute(build_info)
	if log ~= nil then
		local log_list = ALittle.String_SplitSepList(log, {"\r", "\n"})
		for index, log_content in ___ipairs(log_list) do
			ALittle.List_Push(build_info.log_list, log_content)
		end
	end
	ALittle.List_Push(build_info.log_list, "===>[" .. ALittle.Time_GetCurDate() .. "]Job End")
	self._status = 2
	self._progress = 1
	self:SendStatus()
	return error
end

function DeployServer.Job:Execute(build_info)
	local ___COROUTINE = coroutine.running()
	return nil, nil
end

function DeployServer.Job:SendStatus()
	local status_msg = {}
	status_msg.task_id = self._task.info.task_id
	status_msg.status = self._status
	status_msg.progress = self._progress
	A_WebAccountManager:SendMsgToAll(___all_struct[1462309182], status_msg)
end

function DeployServer.CreateJob(task, info)
	if info.job_type == 1 then
		return DeployServer.BatchJob(task, info)
	elseif info.job_type == 2 then
		return DeployServer.DeepCopyJob(task, info)
	end
	return nil
end

end