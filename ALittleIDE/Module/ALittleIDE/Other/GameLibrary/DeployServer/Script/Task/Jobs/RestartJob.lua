-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployServer == nil then _G.DeployServer = {} end
local DeployServer = DeployServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(DeployServer.Job, " extends class:DeployServer.Job is nil")
DeployServer.RestartJob = Lua.Class(DeployServer.Job, "DeployServer.RestartJob")

function DeployServer.RestartJob:Execute(build_info)
	local ___COROUTINE = coroutine.running()
	__CPPAPI_ServerSchedule:RestartAll()
	return nil, nil
end

end