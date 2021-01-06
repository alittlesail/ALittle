-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-2090346221, "ALittle.QVersionSetAccountRole", {
name = "ALittle.QVersionSetAccountRole", ns_name = "ALittle", rl_name = "QVersionSetAccountRole", hash_code = -2090346221,
name_list = {"__account_id","__session_id","account_id","role_id"},
type_list = {"string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(1908089542, "ALittle.AVersionSetAccountPwd", {
name = "ALittle.AVersionSetAccountPwd", ns_name = "ALittle", rl_name = "AVersionSetAccountPwd", hash_code = 1908089542,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1670031053, "ALittle.QVersionSetAccountPwd", {
name = "ALittle.QVersionSetAccountPwd", ns_name = "ALittle", rl_name = "QVersionSetAccountPwd", hash_code = -1670031053,
name_list = {"__account_id","__session_id","account_id","account_pwd"},
type_list = {"string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(-1565382514, "ALittle.AVersionSetAccountRole", {
name = "ALittle.AVersionSetAccountRole", ns_name = "ALittle", rl_name = "AVersionSetAccountRole", hash_code = -1565382514,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1341503137, "ALittle.AVersionUpdateRole", {
name = "ALittle.AVersionUpdateRole", ns_name = "ALittle", rl_name = "AVersionUpdateRole", hash_code = -1341503137,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1334237987, "ALittle.QVersionCreateAccount", {
name = "ALittle.QVersionCreateAccount", ns_name = "ALittle", rl_name = "QVersionCreateAccount", hash_code = -1334237987,
name_list = {"__account_id","__session_id","account_name","account_pwd"},
type_list = {"string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(1314376608, "ALittle.QVersionDeleteRole", {
name = "ALittle.QVersionDeleteRole", ns_name = "ALittle", rl_name = "QVersionDeleteRole", hash_code = 1314376608,
name_list = {"__account_id","__session_id","role_id"},
type_list = {"string","string","string"},
option_map = {}
})
ALittle.RegStruct(-1217701648, "ALittle.AVersionDeleteAccount", {
name = "ALittle.AVersionDeleteAccount", ns_name = "ALittle", rl_name = "AVersionDeleteAccount", hash_code = -1217701648,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1169802891, "ALittle.AVersionDeleteRole", {
name = "ALittle.AVersionDeleteRole", ns_name = "ALittle", rl_name = "AVersionDeleteRole", hash_code = 1169802891,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1102339341, "ALittle.QVersionUpdateRole", {
name = "ALittle.QVersionUpdateRole", ns_name = "ALittle", rl_name = "QVersionUpdateRole", hash_code = 1102339341,
name_list = {"__account_id","__session_id","role_id","role_name","role_permission"},
type_list = {"string","string","string","string","Map<string,bool>"},
option_map = {}
})
ALittle.RegStruct(-813534860, "ALittle.QVersionCreateRole", {
name = "ALittle.QVersionCreateRole", ns_name = "ALittle", rl_name = "QVersionCreateRole", hash_code = -813534860,
name_list = {"__account_id","__session_id","role_name","role_permission"},
type_list = {"string","string","string","Map<string,bool>"},
option_map = {}
})
ALittle.RegStruct(662928143, "ALittle.AVersionCreateRole", {
name = "ALittle.AVersionCreateRole", ns_name = "ALittle", rl_name = "AVersionCreateRole", hash_code = 662928143,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-216744240, "ALittle.QVersionDeleteAccount", {
name = "ALittle.QVersionDeleteAccount", ns_name = "ALittle", rl_name = "QVersionDeleteAccount", hash_code = -216744240,
name_list = {"__account_id","__session_id","account_id"},
type_list = {"string","string","string"},
option_map = {}
})
ALittle.RegStruct(-52328307, "ALittle.AVersionCreateAccount", {
name = "ALittle.AVersionCreateAccount", ns_name = "ALittle", rl_name = "AVersionCreateAccount", hash_code = -52328307,
name_list = {},
type_list = {},
option_map = {}
})

function ALittle.HandleQVersionCreateAccount(client, msg)
	local ___COROUTINE = coroutine.running()
	local web_account = A_WebAccountManager:CheckLoginByClient(client)
	Lua.Assert(msg.account_name ~= nil and msg.account_name ~= "", "账号名不能为空")
	Lua.Assert(msg.account_pwd ~= nil and msg.account_pwd ~= "", "密码不能为空")
	local error, count = A_MysqlSystem:SelectCount(___all_struct[-192825113], "account_name", msg.account_name)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(count == 0, "账号名已存在")
	local base_info = {}
	base_info.account_id = ALittle.String_GenerateID("account_id")
	base_info.account_name = msg.account_name
	base_info.account_pwd = ALittle.String_Md5("ALittle" .. ALittle.String_Md5(msg.account_pwd) .. "ALittle")
	local time, index = ALittle.NewTimeAndIndex()
	base_info.create_time = time
	base_info.create_index = index
	base_info.update_time = time
	base_info.update_index = index
	error = A_MysqlSystem:InsertInto(___all_struct[-192825113], base_info)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	return {}
end

ALittle.RegMsgRpcCallback(-1334237987, ALittle.HandleQVersionCreateAccount, -52328307)
function ALittle.HandleQVersionDeleteAccount(client, msg)
	local ___COROUTINE = coroutine.running()
	local web_account = A_WebAccountManager:CheckLoginByClient(client)
	local error, base_info = A_MysqlSystem:SelectOneFromByKey(___all_struct[-192825113], "account_id", msg.account_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(base_info ~= nil, "账号不存在")
	Lua.Assert(base_info.account_name ~= "alittle", "超级管理员不能删除")
	error = A_MysqlSystem:DeleteFromByKey(___all_struct[-192825113], "account_id", msg.account_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	return {}
end

ALittle.RegMsgRpcCallback(-216744240, ALittle.HandleQVersionDeleteAccount, -1217701648)
function ALittle.HandleQVersionSetAccountPwd(client, msg)
	local ___COROUTINE = coroutine.running()
	local web_account = A_WebAccountManager:CheckLoginByClient(client)
	local error, base_info = A_MysqlSystem:SelectOneFromByKey(___all_struct[-192825113], "account_id", msg.account_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(base_info ~= nil, "账号不存在")
	local password = ALittle.String_Md5("ALittle" .. ALittle.String_Md5(msg.account_pwd) .. "ALittle")
	error = A_MysqlSystem:UpdateSet(___all_struct[-192825113], "account_pwd", password, "account_id", msg.account_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	return {}
end

ALittle.RegMsgRpcCallback(-1670031053, ALittle.HandleQVersionSetAccountPwd, 1908089542)
function ALittle.HandleQVersionSetAccountRole(client, msg)
	local ___COROUTINE = coroutine.running()
	local web_account = A_WebAccountManager:CheckLoginByClient(client)
	local error = nil
	local base_info = nil
	error, base_info = A_MysqlSystem:SelectOneFromByKey(___all_struct[-192825113], "account_id", msg.account_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(base_info ~= nil, "账号不存在")
	Lua.Assert(base_info.account_name ~= "alittle", "超级管理员不能修改角色")
	local role_info = nil
	error, role_info = A_MysqlSystem:SelectOneFromByKey(___all_struct[-699725823], "role_id", msg.role_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(role_info ~= nil, "角色不存在")
	error = A_MysqlSystem:UpdateSet(___all_struct[-192825113], "role_id", msg.role_id, "account_id", msg.account_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	web_account:UpdateRoleInfo()
	return {}
end

ALittle.RegMsgRpcCallback(-2090346221, ALittle.HandleQVersionSetAccountRole, -1565382514)
function ALittle.HandleQVersionCreateRole(client, msg)
	local ___COROUTINE = coroutine.running()
	local web_account = A_WebAccountManager:CheckLoginByClient(client)
	local permission_list = {}
	for permission, _ in ___pairs(msg.role_permission) do
		ALittle.List_Push(permission_list, permission)
	end
	local role_info = {}
	role_info.role_id = ALittle.String_GenerateID("role_id")
	role_info.permission = permission_list
	role_info.role_name = msg.role_name
	local time, index = ALittle.NewTimeAndIndex()
	role_info.create_time = time
	role_info.create_index = index
	role_info.update_time = time
	role_info.update_index = index
	local error = A_MysqlSystem:InsertInto(___all_struct[-699725823], role_info)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	return {}
end

ALittle.RegMsgRpcCallback(-813534860, ALittle.HandleQVersionCreateRole, 662928143)
function ALittle.HandleQVersionUpdateRole(client, msg)
	local ___COROUTINE = coroutine.running()
	local web_account = A_WebAccountManager:CheckLoginByClient(client)
	local error, role_info = A_MysqlSystem:SelectOneFromByKey(___all_struct[-699725823], "role_id", msg.role_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(role_info ~= nil, "角色不存在")
	local permission_list = {}
	for permission, _ in ___pairs(msg.role_permission) do
		ALittle.List_Push(permission_list, permission)
	end
	error = A_MysqlSystem:UpdateSet(___all_struct[-699725823], "role_name", msg.role_name, "role_id", msg.role_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	error = A_MysqlSystem:UpdateSet(___all_struct[-699725823], "permission", permission_list, "role_id", msg.role_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	local sql = "SELECT `account_id` FROM `WebBaseInfo` WHERE `role_id`=?"
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	query.value = msg.role_id
	error = query:Execute()
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	local i = 1
	while true do
		if not(i <= query.count) then break end
		local account_id = query.String
		local account = A_WebAccountManager:GetAccountById(account_id)
		if account ~= nil then
			account:UpdateRoleInfo()
		end
		i = i+(1)
	end
	return {}
end

ALittle.RegMsgRpcCallback(1102339341, ALittle.HandleQVersionUpdateRole, -1341503137)
function ALittle.HandleQVersionDeleteRole(client, msg)
	local ___COROUTINE = coroutine.running()
	local web_account = A_WebAccountManager:CheckLoginByClient(client)
	local error, count = A_MysqlSystem:SelectCount(___all_struct[-192825113], "role_id", msg.role_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(count == 0, "角色正在使用不能删除")
	error = A_MysqlSystem:DeleteFromByKey(___all_struct[-699725823], "role_id", msg.role_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	return {}
end

ALittle.RegMsgRpcCallback(1314376608, ALittle.HandleQVersionDeleteRole, 1169802891)
end