-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.VersionServer == nil then _G.VersionServer = {} end
local VersionServer = VersionServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1929027535, "VersionServer.QDeleteVersionInfo", {
name = "VersionServer.QDeleteVersionInfo", ns_name = "VersionServer", rl_name = "QDeleteVersionInfo", hash_code = 1929027535,
name_list = {"__account_id","__session_id","platform","module_name","version_id"},
type_list = {"string","string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(1929027487, "VersionServer.ADeleteVersionInfo", {
name = "VersionServer.ADeleteVersionInfo", ns_name = "VersionServer", rl_name = "ADeleteVersionInfo", hash_code = 1929027487,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1889282870, "VersionServer.ANewVersionInfo", {
name = "VersionServer.ANewVersionInfo", ns_name = "VersionServer", rl_name = "ANewVersionInfo", hash_code = -1889282870,
name_list = {"version_id","update_time","update_index"},
type_list = {"string","int","int"},
option_map = {}
})
ALittle.RegStruct(-1754421001, "VersionServer.VersionClose", {
name = "VersionServer.VersionClose", ns_name = "VersionServer", rl_name = "VersionClose", hash_code = -1754421001,
name_list = {"account_id","module_name","platform","close_version","submit_platform","create_time","create_index","update_time","update_index"},
type_list = {"string","string","string","string","string","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(1657250345, "VersionServer.D_VersionInfo", {
name = "VersionServer.D_VersionInfo", ns_name = "VersionServer", rl_name = "D_VersionInfo", hash_code = 1657250345,
name_list = {"version_id","account_id","module_name","platform","big_version","version_number","install_version","plugin_list","install_size","status","small_version_time","small_version_index","create_time","create_index","update_time","update_index"},
type_list = {"string","string","string","string","string","string","string","string","int","int","int","int","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(-1549559517, "VersionServer.QAddVersionClose", {
name = "VersionServer.QAddVersionClose", ns_name = "VersionServer", rl_name = "QAddVersionClose", hash_code = -1549559517,
name_list = {"__account_id","__session_id","platform","module_name","close_version","submit_platform"},
type_list = {"string","string","string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(1318347807, "VersionServer.QNewUpdateTimeIndex", {
name = "VersionServer.QNewUpdateTimeIndex", ns_name = "VersionServer", rl_name = "QNewUpdateTimeIndex", hash_code = 1318347807,
name_list = {"__account_id","__session_id"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(-1265122365, "VersionServer.ANewUpdateTimeIndex", {
name = "VersionServer.ANewUpdateTimeIndex", ns_name = "VersionServer", rl_name = "ANewUpdateTimeIndex", hash_code = -1265122365,
name_list = {"update_time","update_index"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(-1118556144, "VersionServer.ANewCurVersion", {
name = "VersionServer.ANewCurVersion", ns_name = "VersionServer", rl_name = "ANewCurVersion", hash_code = -1118556144,
name_list = {"version_info","http_ip","http_port"},
type_list = {"VersionServer.D_VersionInfo","string","int"},
option_map = {}
})
ALittle.RegStruct(1083241076, "VersionServer.QNewCurVersion", {
name = "VersionServer.QNewCurVersion", ns_name = "VersionServer", rl_name = "QNewCurVersion", hash_code = 1083241076,
name_list = {"__account_id","__session_id","platform","module_name"},
type_list = {"string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(929252339, "VersionServer.D_VersionClose", {
name = "VersionServer.D_VersionClose", ns_name = "VersionServer", rl_name = "D_VersionClose", hash_code = 929252339,
name_list = {"account_id","module_name","platform","close_version","submit_platform","create_time","create_index","update_time","update_index"},
type_list = {"string","string","string","string","string","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(763533061, "VersionServer.QNewVersionInfo", {
name = "VersionServer.QNewVersionInfo", ns_name = "VersionServer", rl_name = "QNewVersionInfo", hash_code = 763533061,
name_list = {"__account_id","__session_id","module_name","platform","big_version","version_number","install_version","plugin_list","install_size","log_list","small_version_time","small_version_index","update_time","update_index"},
type_list = {"string","string","string","string","string","string","string","string","int","List<string>","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(660825889, "VersionServer.QDeleteVersionClose", {
name = "VersionServer.QDeleteVersionClose", ns_name = "VersionServer", rl_name = "QDeleteVersionClose", hash_code = 660825889,
name_list = {"__account_id","__session_id","platform","module_name","close_version"},
type_list = {"string","string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(-637772875, "VersionServer.D_VersionLog", {
name = "VersionServer.D_VersionLog", ns_name = "VersionServer", rl_name = "D_VersionLog", hash_code = -637772875,
name_list = {"version_id","account_id","module_name","platform","content","create_time","create_index","update_time","update_index"},
type_list = {"string","string","string","string","string","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(535646734, "VersionServer.VersionInfo", {
name = "VersionServer.VersionInfo", ns_name = "VersionServer", rl_name = "VersionInfo", hash_code = 535646734,
name_list = {"version_id","account_id","module_name","platform","big_version","version_number","install_version","plugin_list","install_size","status","small_version_time","small_version_index","create_time","create_index","update_time","update_index"},
type_list = {"string","string","string","string","string","string","string","string","int","int","int","int","int","int","int","int"},
option_map = {primary="version_id"}
})
ALittle.RegStruct(520612441, "VersionServer.AAddVersionClose", {
name = "VersionServer.AAddVersionClose", ns_name = "VersionServer", rl_name = "AAddVersionClose", hash_code = 520612441,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(403574870, "VersionServer.QVersionInfo", {
name = "VersionServer.QVersionInfo", ns_name = "VersionServer", rl_name = "QVersionInfo", hash_code = 403574870,
name_list = {"__account_id","__session_id","module_name","platform"},
type_list = {"string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(285640750, "VersionServer.AUploadVersionFile", {
name = "VersionServer.AUploadVersionFile", ns_name = "VersionServer", rl_name = "AUploadVersionFile", hash_code = 285640750,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(285640734, "VersionServer.QUploadVersionFile", {
name = "VersionServer.QUploadVersionFile", ns_name = "VersionServer", rl_name = "QUploadVersionFile", hash_code = 285640734,
name_list = {"__account_id","__session_id","platform","module_name","version_id","file_path"},
type_list = {"string","string","string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(242024252, "VersionServer.ADeleteVersionClose", {
name = "VersionServer.ADeleteVersionClose", ns_name = "VersionServer", rl_name = "ADeleteVersionClose", hash_code = 242024252,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-219924640, "VersionServer.VersionLog", {
name = "VersionServer.VersionLog", ns_name = "VersionServer", rl_name = "VersionLog", hash_code = -219924640,
name_list = {"version_id","account_id","module_name","platform","content","create_time","create_index","update_time","update_index"},
type_list = {"string","string","string","string","string","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(-192825113, "ALittle.WebBaseInfo", {
name = "ALittle.WebBaseInfo", ns_name = "ALittle", rl_name = "WebBaseInfo", hash_code = -192825113,
name_list = {"account_id","account_name","account_pwd","role_id","creator_id","create_time","create_index","update_time","update_index"},
type_list = {"string","string","string","string","string","int","int","int","int"},
option_map = {primary="account_id",unique="account_name"}
})
ALittle.RegStruct(129933683, "VersionServer.AVersionInfo", {
name = "VersionServer.AVersionInfo", ns_name = "VersionServer", rl_name = "AVersionInfo", hash_code = 129933683,
name_list = {"version_list","close_list","log_list"},
type_list = {"List<VersionServer.D_VersionInfo>","List<VersionServer.D_VersionClose>","List<VersionServer.D_VersionLog>"},
option_map = {}
})

VersionServer.VersionManager = Lua.Class(nil, "VersionServer.VersionManager")

function VersionServer.VersionManager:Ctor()
end

function VersionServer.VersionManager:Setup()
	local ___COROUTINE = coroutine.running()
	local error = A_MysqlSystem:CreateIfNotExit(___all_struct[535646734])
	Lua.Assert(error == nil, error)
	error = A_MysqlSystem:CreateIfNotExit(___all_struct[-1754421001])
	Lua.Assert(error == nil, error)
	error = A_MysqlSystem:CreateIfNotExit(___all_struct[-219924640])
	Lua.Assert(error == nil, error)
	self._version_path = VersionServer.g_ConfigSystem:GetString("version_path", "")
end

function VersionServer.VersionManager:Shutdown()
end

function VersionServer.VersionManager.__getter:version_path()
	return self._version_path
end

VersionServer.g_VersionManager = VersionServer.VersionManager()
function VersionServer.HandleHttpQVersionInfo(client, msg)
	local ___COROUTINE = coroutine.running()
	local param = {}
	param.version_list = {}
	param.close_list = {}
	param.log_list = {}
	local web_account = A_WebAccountManager:CheckLoginById(msg.__account_id, msg.__session_id)
	do
		local sql = "SELECT `version_id`,`account_id`,`module_name`,`platform`,`big_version`,`version_number`,`install_version`,`plugin_list`,`install_size`,`status`,`small_version_time`,`small_version_index`,`create_time`,`create_index`,`update_time`,`update_index` FROM `VersionInfo` WHERE `account_id`=? AND `module_name`=? AND `platform`=?"
		local query = ALittle.MysqlStatementQuery()
		query.sql = sql
		query.value = msg.__account_id
		query.value = msg.module_name
		query.value = msg.platform
		local error = query:Execute()
		if error ~= nil then
			Lua.Throw("数据库操作失败:" .. error)
		end
		local i = 1
		while true do
			if not(i <= query.count) then break end
			local data = {}
			ALittle.List_Push(param.version_list, data)
			data.version_id = query.value
			data.account_id = query.value
			data.module_name = query.value
			data.platform = query.value
			data.big_version = query.value
			data.version_number = query.value
			data.install_version = query.value
			data.plugin_list = query.value
			data.install_size = query.value
			data.status = query.value
			data.small_version_time = query.value
			data.small_version_index = query.value
			data.create_time = query.value
			data.create_index = query.value
			data.update_time = query.value
			data.update_index = query.value
			i = i+(1)
		end
	end
	do
		local sql = "SELECT `account_id`,`module_name`,`platform`,`close_version`,`submit_platform`,`create_time`,`create_index`,`update_time`,`update_index` FROM `VersionClose` WHERE `account_id`=? AND `module_name`=? AND `platform`=?"
		local query = ALittle.MysqlStatementQuery()
		query.sql = sql
		query.value = msg.__account_id
		query.value = msg.module_name
		query.value = msg.platform
		local error = query:Execute()
		if error ~= nil then
			Lua.Throw("数据库操作失败:" .. error)
		end
		local i = 1
		while true do
			if not(i <= query.count) then break end
			local data = {}
			ALittle.List_Push(param.close_list, data)
			data.account_id = query.value
			data.module_name = query.value
			data.platform = query.value
			data.close_version = query.value
			data.submit_platform = query.value
			data.create_time = query.value
			data.create_index = query.value
			data.update_time = query.value
			data.update_index = query.value
			i = i+(1)
		end
	end
	do
		local sql = "SELECT `version_id`,`account_id`,`module_name`,`platform`,`content`,`create_time`,`create_index`,`update_time`,`update_index` FROM `VersionLog` WHERE `account_id`=? AND `module_name`=? AND `platform`=?"
		local query = ALittle.MysqlStatementQuery()
		query.sql = sql
		query.value = msg.__account_id
		query.value = msg.module_name
		query.value = msg.platform
		local error = query:Execute()
		if error ~= nil then
			Lua.Throw("数据库操作失败:" .. error)
		end
		local i = 1
		while true do
			if not(i <= query.count) then break end
			local data = {}
			ALittle.List_Push(param.log_list, data)
			data.version_id = query.value
			data.account_id = query.value
			data.module_name = query.value
			data.platform = query.value
			data.content = query.value
			data.create_time = query.value
			data.create_index = query.value
			data.update_time = query.value
			data.update_index = query.value
			i = i+(1)
		end
	end
	return param
end

ALittle.RegHttpCallback("VersionServer.QVersionInfo", VersionServer.HandleHttpQVersionInfo)
function VersionServer.HandleHttpQAddVersionClose(client, msg)
	local ___COROUTINE = coroutine.running()
	local web_account = A_WebAccountManager:CheckLoginById(msg.__account_id, msg.__session_id)
	local sql = "INSERT INTO `VersionClose` (`account_id`,`module_name`,`platform`,`close_version`,`submit_platform`,`create_time`,`create_index`,`update_time`,`update_index`) VALUES (?,?,?,?,?,?,?,?,?)"
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	query.value = msg.__account_id
	query.value = msg.module_name
	query.value = msg.platform
	query.value = msg.close_version
	query.value = msg.submit_platform
	local time, index = ALittle.NewTimeAndIndex()
	query.value = time
	query.value = index
	query.value = time
	query.value = index
	local error = query:Execute()
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	return {}
end

ALittle.RegHttpCallback("VersionServer.QAddVersionClose", VersionServer.HandleHttpQAddVersionClose)
function VersionServer.HandleHttpQDeleteVersionClose(client, msg)
	local ___COROUTINE = coroutine.running()
	local web_account = A_WebAccountManager:CheckLoginById(msg.__account_id, msg.__session_id)
	local sql = "DELETE FROM `VersionClose` WHERE `account_id`=? AND `module_name`=? AND `platform`=? AND `close_version`=?"
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	query.value = msg.__account_id
	query.value = msg.module_name
	query.value = msg.platform
	query.value = msg.close_version
	local error = query:Execute()
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	return {}
end

ALittle.RegHttpCallback("VersionServer.QDeleteVersionClose", VersionServer.HandleHttpQDeleteVersionClose)
function VersionServer.HandleHttpQNewUpdateTimeIndex(client, msg)
	local ___COROUTINE = coroutine.running()
	local web_account = A_WebAccountManager:CheckLoginById(msg.__account_id, msg.__session_id)
	local param = {}
	param.update_time, param.update_index = ALittle.NewTimeAndIndex()
	return param
end

ALittle.RegHttpCallback("VersionServer.QNewUpdateTimeIndex", VersionServer.HandleHttpQNewUpdateTimeIndex)
function VersionServer.HandleHttpQNewCurVersion(client, msg)
	local ___COROUTINE = coroutine.running()
	local param = {}
	local web_account = A_WebAccountManager:CheckLoginById(msg.__account_id, msg.__session_id)
	local sql = "SELECT `version_id`,`account_id`,`module_name`,`platform`,`big_version`,`version_number`,`install_version`,`plugin_list`,`install_size`,`status`,`small_version_time`,`small_version_index`,`create_time`,`create_index`,`update_time`,`update_index` FROM `VersionInfo` WHERE `account_id`=? AND `module_name`=? AND `platform`=? AND `status`=1"
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	query.value = msg.__account_id
	query.value = msg.module_name
	query.value = msg.platform
	local error = query:Execute()
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	local i = 1
	while true do
		if not(i <= query.count) then break end
		local data = {}
		param.version_info = data
		data.version_id = query.value
		data.account_id = query.value
		data.module_name = query.value
		data.platform = query.value
		data.big_version = query.value
		data.version_number = query.value
		data.install_version = query.value
		data.plugin_list = query.value
		data.install_size = query.value
		data.status = query.value
		data.small_version_time = query.value
		data.small_version_index = query.value
		data.create_time = query.value
		data.create_index = query.value
		data.update_time = query.value
		data.update_index = query.value
		i = i+(1)
	end
	param.http_ip = __CPPAPI_ServerSchedule:GetHttpServerYunIp()
	if param.http_ip == nil or param.http_ip == "" then
		param.http_ip = __CPPAPI_ServerSchedule:GetHttpServerIp()
	end
	param.http_port = __CPPAPI_ServerSchedule:GetHttpServerPort()
	return param
end

ALittle.RegHttpCallback("VersionServer.QNewCurVersion", VersionServer.HandleHttpQNewCurVersion)
function VersionServer.HandleHttpQNewVersionInfo(client, msg)
	local ___COROUTINE = coroutine.running()
	local web_account = A_WebAccountManager:CheckLoginById(msg.__account_id, msg.__session_id)
	local version_id = ALittle.String_GenerateID("VERSION")
	local sql = "INSERT INTO `VersionInfo` (`version_id`,`account_id`,`module_name`,`platform`,`big_version`,`version_number`,`install_version`,`plugin_list`,`install_size`,`status`,`small_version_time`,`small_version_index`,`create_time`,`create_index`,`update_time`,`update_index`) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	query.value = version_id
	query.value = msg.__account_id
	query.value = msg.module_name
	query.value = msg.platform
	query.value = msg.big_version
	query.value = msg.version_number
	query.value = msg.install_version
	query.value = msg.plugin_list
	query.value = msg.install_size
	query.value = 0
	query.value = msg.small_version_time
	query.value = msg.small_version_index
	query.value = msg.update_time
	query.value = msg.update_index
	query.value = msg.update_time
	query.value = msg.update_index
	local error = query:Execute()
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	if msg.log_list ~= nil then
		for _, log in ___ipairs(msg.log_list) do
			sql = "INSERT INTO `VersionLog` (`version_id`,`account_id`,`module_name`,`platform`,`content`,`create_time`,`create_index`,`update_time`,`update_index`) VALUES (?,?,?,?,?,?,?,?,?)"
			query = ALittle.MysqlStatementQuery()
			query.sql = sql
			query.value = version_id
			query.value = msg.__account_id
			query.value = msg.module_name
			query.value = msg.platform
			query.value = log
			local time, index = ALittle.NewTimeAndIndex()
			query.value = time
			query.value = index
			query.value = time
			query.value = index
			error = query:Execute()
			if error ~= nil then
				Lua.Throw("数据库操作失败:" .. error)
			end
		end
	end
	local param = {}
	param.version_id = version_id
	param.update_time = msg.update_time
	param.update_index = msg.update_index
	return param
end

ALittle.RegHttpCallback("VersionServer.QNewVersionInfo", VersionServer.HandleHttpQNewVersionInfo)
function VersionServer.HandleHttpQUpdateVersion(client, msg)
	local ___COROUTINE = coroutine.running()
	local error, base_info = A_MysqlSystem:SelectOneFromByKey(___all_struct[-192825113], "account_name", msg.account_name)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(base_info ~= nil, "账号不存在")
	local param = {}
	param.version_info = {}
	param.log_list = {}
	param.result = false
	if msg.big_version ~= nil and msg.big_version ~= "" then
		local sql = "SELECT `close_version` FROM `VersionClose` WHERE `account_id`=? AND `module_name`=? AND `platform`=? AND `close_version`=?"
		local query = ALittle.MysqlStatementQuery()
		query.sql = sql
		query.value = base_info.account_id
		query.value = msg.module_name
		query.value = msg.platform
		query.value = msg.big_version
		error = query:Execute()
		if error ~= nil then
			Lua.Throw("数据库操作失败:" .. error)
		end
		if query.count > 0 then
			return param
		end
	end
	do
		local sql = "SELECT `version_id`,`account_id`,`module_name`,`platform`,`big_version`,`version_number`,`install_version`,`plugin_list`,`install_size`,`status`,`small_version_time`,`small_version_index`,`create_time`,`create_index`,`update_time`,`update_index` FROM `VersionInfo` WHERE `account_id`=? AND `module_name`=? AND `platform`=? ORDER BY `update_time` DESC,`update_index` DESC LIMIT 1"
		local query = ALittle.MysqlStatementQuery()
		query.sql = sql
		query.value = base_info.account_id
		query.value = msg.module_name
		query.value = msg.platform
		error = query:Execute()
		if error ~= nil then
			Lua.Throw("数据库操作失败:" .. error)
		end
		if query.count == 0 then
			return param
		end
		local data = {}
		param.version_info = data
		data.version_id = query.value
		data.account_id = query.value
		data.module_name = query.value
		data.platform = query.value
		data.big_version = query.value
		data.version_number = query.value
		data.install_version = query.value
		data.plugin_list = query.value
		data.install_size = query.value
		data.status = query.value
		data.small_version_time = query.value
		data.small_version_index = query.value
		data.create_time = query.value
		data.create_index = query.value
		data.update_time = query.value
		data.update_index = query.value
	end
	do
		local sql = "SELECT `content` FROM `VersionLog` WHERE `account_id`=? AND `module_name`=? AND `platform`=? AND `version_id`=? ORDER BY `update_time` DESC, `update_index` DESC"
		local query = ALittle.MysqlStatementQuery()
		query.sql = sql
		query.value = base_info.account_id
		query.value = msg.module_name
		query.value = msg.platform
		query.value = param.version_info.version_id
		error = query:Execute()
		if error ~= nil then
			Lua.Throw("数据库操作失败:" .. error)
		end
		local i = 1
		while true do
			if not(i <= query.count) then break end
			ALittle.List_Push(param.log_list, query.value)
			i = i+(1)
		end
	end
	param.result = true
	if msg.small_version_time == 0 or msg.big_version == "" or msg.big_version == nil then
		return param
	end
	if msg.small_version_time < param.version_info.small_version_time then
		return param
	end
	if msg.small_version_time == param.version_info.small_version_time and msg.small_version_index < param.version_info.small_version_index then
		return param
	end
	if msg.install_version < param.version_info.install_version then
		return param
	end
	param.result = false
	return param
end

ALittle.RegHttpCallback("VersionServer.QUpdateVersion", VersionServer.HandleHttpQUpdateVersion)
function VersionServer.HandleHttpQDownloadVersionFile(client, msg)
	local ___COROUTINE = coroutine.running()
	Lua.Assert(ALittle.String_Find(msg.platform, "..") == nil, "platform不能带两个点")
	Lua.Assert(ALittle.String_Find(msg.version_id, "..") == nil, "version_id不能带两个点")
	Lua.Assert(ALittle.String_Find(msg.file_path, "..") == nil, "file_path不能带两个点")
	local file_path = VersionServer.g_VersionManager.version_path .. "Version/" .. msg.platform .. "/" .. msg.version_id .. "/" .. msg.file_path
	local start_size = msg.start_size
	if start_size == nil then
		start_size = 0
	end
	return file_path, start_size
end

ALittle.RegHttpDownloadCallback("VersionServer.QDownloadVersionFile", VersionServer.HandleHttpQDownloadVersionFile)
function VersionServer.HandleHttpQDeleteVersionInfo(client, msg)
	local ___COROUTINE = coroutine.running()
	local web_account = A_WebAccountManager:CheckLoginById(msg.__account_id, msg.__session_id)
	local sql = "SELECT `version_id` FROM `VersionInfo` WHERE `status`=1 AND `account_id`=? AND `module_name`=? AND `platform`=? ORDER BY `update_time` DESC,`update_index` DESC LIMIT 1"
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	query.value = msg.__account_id
	query.value = msg.module_name
	query.value = msg.platform
	local error = query:Execute()
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	if query.count > 0 then
		local version_id = query.String
		Lua.Assert(version_id ~= msg.version_id, "不允许删除最新版本")
	end
	do
		sql = "DELETE FROM `VersionInfo` WHERE `version_id`=? AND `account_id`=?"
		query = ALittle.MysqlStatementQuery()
		query.sql = sql
		query.value = msg.version_id
		query.value = msg.__account_id
		error = query:Execute()
		if error ~= nil then
			Lua.Throw("数据库操作失败:" .. error)
		end
	end
	do
		sql = "DELETE FROM `VersionLog` WHERE `version_id`=? AND `account_id`=?"
		query = ALittle.MysqlStatementQuery()
		query.sql = sql
		query.value = msg.version_id
		query.value = msg.__account_id
		error = query:Execute()
		if error ~= nil then
			Lua.Throw("数据库操作失败:" .. error)
		end
	end
	local file_path = VersionServer.g_VersionManager.version_path .. "Version/" .. msg.platform .. "/" .. msg.version_id
	ALittle.File_DeleteDeepDir(file_path, false)
	return {}
end

ALittle.RegHttpCallback("VersionServer.QDeleteVersionInfo", VersionServer.HandleHttpQDeleteVersionInfo)
function VersionServer.HandleHttpQUploadVersionFile(client, msg)
	local ___COROUTINE = coroutine.running()
	local web_account = A_WebAccountManager:CheckLoginById(msg.__account_id, msg.__session_id)
	Lua.Assert(ALittle.String_Find(msg.platform, "..") == nil, "platform不能带两个点")
	Lua.Assert(ALittle.String_Find(msg.version_id, "..") == nil, "version_id不能带两个点")
	Lua.Assert(ALittle.String_Find(msg.file_path, "..") == nil, "file_path不能带两个点")
	local sql = "SELECT `module_name` FROM `VersionInfo` WHERE `version_id`=? AND `account_id`=? AND `platform`=?"
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	query.value = msg.version_id
	query.value = msg.__account_id
	query.value = msg.platform
	local error = query:Execute()
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(query.count ~= 0, "模块不存在")
	local file_path = VersionServer.g_VersionManager.version_path .. "Version/" .. msg.platform .. "/" .. msg.version_id .. "/" .. msg.file_path
	ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(file_path))
	error = client:StartReceiveFile(file_path, 0)
	if error ~= nil then
		ALittle.File_DeleteFile(file_path)
	end
	Lua.Assert(error == nil, error)
	if msg.file_path == "CurVersion.db" then
		sql = "UPDATE `VersionInfo` SET `status`=1 WHERE `version_id`=? AND `account_id`=?"
		query = ALittle.MysqlStatementQuery()
		query.sql = sql
		query.value = msg.version_id
		query.value = msg.__account_id
		error = query:Execute()
		if error ~= nil then
			Lua.Throw("数据库操作失败:" .. error)
		end
	end
end

ALittle.RegHttpFileCallback("VersionServer.QUploadVersionFile", VersionServer.HandleHttpQUploadVersionFile)
end