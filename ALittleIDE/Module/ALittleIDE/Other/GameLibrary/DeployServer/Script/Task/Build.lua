-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployServer == nil then _G.DeployServer = {} end
local DeployServer = DeployServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1612084089, "DeployServer.QDownloadBuild", {
name = "DeployServer.QDownloadBuild", ns_name = "DeployServer", rl_name = "QDownloadBuild", hash_code = -1612084089,
name_list = {"task_id","build_index"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(361832837, "DeployServer.BuildInfo", {
name = "DeployServer.BuildInfo", ns_name = "DeployServer", rl_name = "BuildInfo", hash_code = 361832837,
name_list = {"log_list","create_time"},
type_list = {"List<string>","int"},
option_map = {}
})

function DeployServer.HandleDownloadBuild(sender, msg)
	local ___COROUTINE = coroutine.running()
	local task = g_TaskManager:GetTask(msg.task_id)
	Lua.Assert(task ~= nil, "任务不存在")
	local build_info = task.info.build_list[msg.build_index]
	Lua.Assert(build_info ~= nil, "构建信息不存在")
	return task:GetBuildPath(build_info.create_time), 0
end

ALittle.RegHttpDownloadCallback("DeployServer.QDownloadBuild", DeployServer.HandleDownloadBuild)
end