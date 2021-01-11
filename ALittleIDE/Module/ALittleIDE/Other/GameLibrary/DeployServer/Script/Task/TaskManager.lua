-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1686717773, "ALittleDeploy.TaskInfo", {
name = "ALittleDeploy.TaskInfo", ns_name = "ALittleDeploy", rl_name = "TaskInfo", hash_code = -1686717773,
name_list = {"task_id","task_name","task_desc","web_hook","job_list","create_time"},
type_list = {"int","string","string","Map<string,bool>","List<ALittleDeploy.JobInfo>","int"},
option_map = {primary="task_id"}
})
ALittle.RegStruct(1037962987, "ALittleDeploy.JobInfo", {
name = "ALittleDeploy.JobInfo", ns_name = "ALittleDeploy", rl_name = "JobInfo", hash_code = 1037962987,
name_list = {"job_type"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(-940476300, "ALittleDeploy.AQueryTask", {
name = "ALittleDeploy.AQueryTask", ns_name = "ALittleDeploy", rl_name = "AQueryTask", hash_code = -940476300,
name_list = {"task_list"},
type_list = {"List<ALittleDeploy.D_TaskInfo>"},
option_map = {}
})
ALittle.RegStruct(-760006533, "ALittleDeploy.QQueryTask", {
name = "ALittleDeploy.QQueryTask", ns_name = "ALittleDeploy", rl_name = "QQueryTask", hash_code = -760006533,
name_list = {"key"},
type_list = {"string"},
option_map = {}
})
ALittle.RegStruct(109366875, "ALittleDeploy.D_TaskInfo", {
name = "ALittleDeploy.D_TaskInfo", ns_name = "ALittleDeploy", rl_name = "D_TaskInfo", hash_code = 109366875,
name_list = {"info"},
type_list = {"ALittleDeploy.TaskInfo"},
option_map = {}
})

ALittleDeploy.TaskManager = Lua.Class(nil, "ALittleDeploy.TaskManager")

function ALittleDeploy.TaskManager:Ctor()
	___rawset(self, "_max_task_id", 0)
	___rawset(self, "_max_job_id", 0)
	___rawset(self, "_task_map", {})
end

function ALittleDeploy.TaskManager:Setup()
	local ___COROUTINE = coroutine.running()
	local error = A_MysqlSystem:CreateIfNotExit(___all_struct[-1686717773])
	Lua.Assert(error == nil, error)
	error = A_MysqlSystem:CreateIfNotExit(___all_struct[1037962987])
	Lua.Assert(error == nil, error)
	local task_error, task_list = A_MysqlSystem:SelectListFromByMap(___all_struct[-1686717773], {})
	Lua.Assert(task_error == nil, task_error)
	for index, task_info in ___ipairs(task_list) do
		self._task_map[task_info.task_id] = ALittleDeploy.Task(task_info)
	end
end

function ALittleDeploy.TaskManager:GetTask(task_id)
	return self._task_map[task_id]
end

function ALittleDeploy.TaskManager:StartTaskByWebHook(url)
	for index, task in ___pairs(self._task_map) do
		task:StartByWebHook(url)
	end
end

function ALittleDeploy.TaskManager:FindTaskByUpperKey(key)
	local result = {}
	local count = 0
	for id, task in ___pairs(self._task_map) do
		if ALittle.String_Find(task.upper_name, key) ~= nil then
			count = count + 1
			result[count] = task
		end
	end
	return result
end

function ALittleDeploy.TaskManager:FindTaskByUpperKeyList(key_list)
	local result = {}
	local count = 0
	for id, task in ___pairs(self._task_map) do
		local find = true
		local init = 1
		for index, key in ___ipairs(key_list) do
			local pos = ALittle.String_Find(task.upper_name, key, init)
			if pos == nil then
				find = false
				break
			end
			init = pos + ALittle.String_Len(key)
		end
		if find then
			count = count + (1)
			result[count] = task
		end
	end
	return result
end

function ALittleDeploy.TaskManager:FindTask(key)
	key = ALittle.String_Upper(key)
	local key_list = ALittle.String_SplitSepList(key, {" ", "\t"})
	if key_list[1] == nil then
		return self:FindTaskByUpperKey(key)
	else
		return self:FindTaskByUpperKeyList(key_list)
	end
end

function ALittleDeploy.TaskManager:Shutdown()
end

_G.g_TaskManager = ALittleDeploy.TaskManager()
function ALittleDeploy.HandleQQueryTask(sender, msg)
	local ___COROUTINE = coroutine.running()
	local rsp = {}
	rsp.task_list = {}
	local task_list = g_TaskManager:FindTask(msg.key)
	for index, task in ___ipairs(task_list) do
		local info = {}
		info.info = task.info
		ALittle.List_Push(rsp.task_list, info)
	end
	return rsp
end

ALittle.RegHttpCallback("ALittleDeploy.QQueryTask", ALittleDeploy.HandleQQueryTask)
end