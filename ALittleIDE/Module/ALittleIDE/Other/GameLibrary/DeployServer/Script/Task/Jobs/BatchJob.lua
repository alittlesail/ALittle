-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployServer == nil then _G.DeployServer = {} end
local DeployServer = DeployServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(DeployServer.Job, " extends class:DeployServer.Job is nil")
DeployServer.BatchJob = Lua.Class(DeployServer.Job, "DeployServer.BatchJob")

function DeployServer.BatchJob.__getter:data_info()
	local data = DeployServer.Job.__getter.data_info(self)
	data.batch_cmd = self._info.batch_cmd
	data.batch_param = self._info.batch_param
	return data
end

function DeployServer.BatchJob:Execute()
	local ___COROUTINE = coroutine.running()
	local msg = {}
	msg.cmd = self._info.batch_cmd
	msg.param = self._info.batch_param
	local error, rsp = ALittle.IWorkerCommon.InvokeRPC(-1431809884, DeployServer.g_JobWorker, msg)
	ALittle.Log(ALittle.String_JsonEncode(rsp))
	return nil
end

function DeployServer.BatchJob:Modify(msg)
	DeployServer.Job.Modify(self, msg)
	self._info.batch_cmd = msg.batch_cmd
	self._info.batch_param = msg.batch_param
end

end