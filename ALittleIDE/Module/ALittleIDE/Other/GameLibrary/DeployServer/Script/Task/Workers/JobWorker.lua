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
name_list = {"exit_code","content"},
type_list = {"int","string"},
option_map = {}
})
ALittle.RegStruct(1447368920, "DeployServer.ACopyFileExecute", {
name = "DeployServer.ACopyFileExecute", ns_name = "DeployServer", rl_name = "ACopyFileExecute", hash_code = 1447368920,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1431809884, "DeployServer.QBatchExecute", {
name = "DeployServer.QBatchExecute", ns_name = "DeployServer", rl_name = "QBatchExecute", hash_code = -1431809884,
name_list = {"detail"},
type_list = {"DeployServer.JobInfoDetail"},
option_map = {}
})
ALittle.RegStruct(-1351236611, "DeployServer.QDeepCopyExecute", {
name = "DeployServer.QDeepCopyExecute", ns_name = "DeployServer", rl_name = "QDeepCopyExecute", hash_code = -1351236611,
name_list = {"detail"},
type_list = {"DeployServer.JobInfoDetail"},
option_map = {}
})
ALittle.RegStruct(-876622592, "DeployServer.ADeepCopyExecute", {
name = "DeployServer.ADeepCopyExecute", ns_name = "DeployServer", rl_name = "ADeepCopyExecute", hash_code = -876622592,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-467409153, "DeployServer.QCopyFileExecute", {
name = "DeployServer.QCopyFileExecute", ns_name = "DeployServer", rl_name = "QCopyFileExecute", hash_code = -467409153,
name_list = {"detail"},
type_list = {"DeployServer.JobInfoDetail"},
option_map = {}
})

function DeployServer.HandleBatchWorker(sender, msg)
	local ___COROUTINE = coroutine.running()
	local detail = msg.detail
	local rsp = {}
	local cmd = ""
	if detail.batch_dir ~= nil and detail.batch_dir ~= "" then
		local index = ALittle.String_Find(detail.batch_dir, ":")
		if index ~= nil then
			cmd = cmd .. ALittle.String_Sub(detail.batch_dir, 1, index) .. " && "
		end
		if index ~= ALittle.String_Len(detail.batch_dir) then
			cmd = cmd .. "cd \"" .. detail.batch_dir .. "\" && "
		end
	end
	cmd = cmd .. detail.batch_cmd .. " " .. detail.batch_param
	local file = io.popen(cmd, "rb")
	Lua.Assert(file ~= nil, "命令执行失败:" .. cmd)
	rsp.content = file:read("*a")
	rsp.exit_code = file:close()
	return rsp
end

ALittle.RegWorkerRpcCallback(-1431809884, DeployServer.HandleBatchWorker, 1870092216)
function DeployServer.HandleDeepCopyWorker(sender, msg)
	local ___COROUTINE = coroutine.running()
	local detail = msg.detail
	local rsp = {}
	if detail.deepcopy_ext == "" then
		detail.deepcopy_ext = nil
	end
	local attr = ALittle.File_GetFileAttr(detail.deepcopy_src)
	Lua.Assert(attr ~= nil and attr.directory, "源目录不存在")
	ALittle.File_MakeDeepDir(detail.deepcopy_dst)
	attr = ALittle.File_GetFileAttr(detail.deepcopy_dst)
	Lua.Assert(attr ~= nil and attr.directory, "目标目录创建失败")
	ALittle.File_CopyDeepDir(detail.deepcopy_src, detail.deepcopy_dst, detail.deepcopy_ext)
	return rsp
end

ALittle.RegWorkerRpcCallback(-1351236611, DeployServer.HandleDeepCopyWorker, -876622592)
function DeployServer.HandleCopyFileWorker(sender, msg)
	local ___COROUTINE = coroutine.running()
	local detail = msg.detail
	local rsp = {}
	local attr = ALittle.File_GetFileAttr(detail.copyfile_src)
	Lua.Assert(attr ~= nil and attr.directory, "源目录不存在")
	ALittle.File_MakeDeepDir(detail.copyfile_dst)
	attr = ALittle.File_GetFileAttr(detail.copyfile_dst)
	Lua.Assert(attr ~= nil and attr.directory, "目标目录创建失败")
	local src = ALittle.File_PathEndWithSplit(detail.copyfile_src)
	local dst = ALittle.File_PathEndWithSplit(detail.copyfile_dst)
	for index, file_name in ___ipairs(detail.copyfile_file) do
		local result = ALittle.File_CopyFile(src .. file_name, dst .. file_name)
		Lua.Assert(result, "文件复制失败:" .. src .. file_name)
	end
	return rsp
end

ALittle.RegWorkerRpcCallback(-467409153, DeployServer.HandleCopyFileWorker, 1447368920)
end