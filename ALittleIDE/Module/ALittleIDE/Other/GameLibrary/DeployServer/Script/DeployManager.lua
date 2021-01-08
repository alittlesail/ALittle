-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployServer == nil then _G.DeployServer = {} end
local DeployServer = DeployServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1544249038, "DeployServer.JobInfo", {
name = "DeployServer.JobInfo", ns_name = "DeployServer", rl_name = "JobInfo", hash_code = 1544249038,
name_list = {"job_id","task_id","job_type","parent_id"},
type_list = {"int","int","int","int"},
option_map = {primary="job_id",index="task_id"}
})
ALittle.RegStruct(276033112, "DeployServer.TaskInfo", {
name = "DeployServer.TaskInfo", ns_name = "DeployServer", rl_name = "TaskInfo", hash_code = 276033112,
name_list = {"task_id","create_time"},
type_list = {"int","int"},
option_map = {primary="task_id"}
})

DeployServer.DeployManager = Lua.Class(nil, "DeployServer.DeployManager")

function DeployServer.DeployManager:Ctor()
end

function DeployServer.DeployManager:Setup()
	local ___COROUTINE = coroutine.running()
	local error = A_MysqlSystem:CreateIfNotExit(___all_struct[276033112])
	Lua.Assert(error == nil, error)
	error = A_MysqlSystem:CreateIfNotExit(___all_struct[1544249038])
	Lua.Assert(error == nil, error)
end

function DeployServer.DeployManager:Shutdown()
end

DeployServer.g_DeployManager = DeployServer.DeployManager()
end