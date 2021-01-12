-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployServer == nil then _G.DeployServer = {} end
local DeployServer = DeployServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1870092216, "DeployServer.ABatchExecute", {
name = "DeployServer.ABatchExecute", ns_name = "DeployServer", rl_name = "ABatchExecute", hash_code = 1870092216,
name_list = {"content"},
type_list = {"string"},
option_map = {}
})
ALittle.RegStruct(-1431809884, "DeployServer.QBatchExecute", {
name = "DeployServer.QBatchExecute", ns_name = "DeployServer", rl_name = "QBatchExecute", hash_code = -1431809884,
name_list = {"dir","cmd","param"},
type_list = {"string","string","string"},
option_map = {}
})

function DeployServer.HandleBatchWorker(sender, msg)
	local ___COROUTINE = coroutine.running()
	local rsp = {}
	local cmd = ""
	if msg.dir ~= nil and msg.dir ~= "" then
		local index = ALittle.String_Find(msg.dir, ":")
		if index ~= nil then
			cmd = cmd .. ALittle.String_Sub(msg.dir, 1, index) .. " && "
		end
		cmd = cmd .. "cd \"" .. msg.dir .. "\" && "
	end
	cmd = cmd .. msg.cmd .. " " .. msg.param
	local file = io.popen(cmd, "r")
	Lua.Assert(file ~= nil, "命令执行失败:" .. cmd)
	rsp.content = file:read("*a")
	file:close()
	return rsp
end

ALittle.RegWorkerRpcCallback(-1431809884, DeployServer.HandleBatchWorker, 1870092216)
end