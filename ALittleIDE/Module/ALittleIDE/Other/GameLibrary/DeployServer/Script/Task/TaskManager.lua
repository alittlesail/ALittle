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

function ALittleDeploy.TaskManager:Shutdown()
end

_G.g_TaskManager = ALittleDeploy.TaskManager()
end