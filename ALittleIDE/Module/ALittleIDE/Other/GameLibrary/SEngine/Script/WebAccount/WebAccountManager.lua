-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(1652964636, "ALittle.AWebChangePassword", {
name = "ALittle.AWebChangePassword", ns_name = "ALittle", rl_name = "AWebChangePassword", hash_code = 1652964636,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1598450085, "ALittle.QWebLogout", {
name = "ALittle.QWebLogout", ns_name = "ALittle", rl_name = "QWebLogout", hash_code = 1598450085,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1393745450, "ALittle.WebAccountLogoutEvent", {
name = "ALittle.WebAccountLogoutEvent", ns_name = "ALittle", rl_name = "WebAccountLogoutEvent", hash_code = -1393745450,
name_list = {"target","account"},
type_list = {"ALittle.EventDispatcher","ALittle.WebAccount"},
option_map = {}
})
ALittle.RegStruct(-1373673802, "ALittle.QWebChangePassword", {
name = "ALittle.QWebChangePassword", ns_name = "ALittle", rl_name = "QWebChangePassword", hash_code = -1373673802,
name_list = {"old_password","new_password"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(-1353883986, "ALittle.WebAccountLoginEvent", {
name = "ALittle.WebAccountLoginEvent", ns_name = "ALittle", rl_name = "WebAccountLoginEvent", hash_code = -1353883986,
name_list = {"target","account"},
type_list = {"ALittle.EventDispatcher","ALittle.WebAccount"},
option_map = {}
})
ALittle.RegStruct(898014419, "ALittle.QWebLogin", {
name = "ALittle.QWebLogin", ns_name = "ALittle", rl_name = "QWebLogin", hash_code = 898014419,
name_list = {"device_id","client_platform","third_platform","account_name","account_pwd"},
type_list = {"string","string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(-699725823, "ALittle.WebRoleInfo", {
name = "ALittle.WebRoleInfo", ns_name = "ALittle", rl_name = "WebRoleInfo", hash_code = -699725823,
name_list = {"role_id","role_name","permission","creator_id","create_time","create_index","update_time","update_index"},
type_list = {"string","string","List<string>","string","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(-344058063, "ALittle.AWebLogout", {
name = "ALittle.AWebLogout", ns_name = "ALittle", rl_name = "AWebLogout", hash_code = -344058063,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-303211063, "ALittle.AWebLogin", {
name = "ALittle.AWebLogin", ns_name = "ALittle", rl_name = "AWebLogin", hash_code = -303211063,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-192825113, "ALittle.WebBaseInfo", {
name = "ALittle.WebBaseInfo", ns_name = "ALittle", rl_name = "WebBaseInfo", hash_code = -192825113,
name_list = {"account_id","account_name","account_pwd","role_id","creator_id","create_time","create_index","update_time","update_index"},
type_list = {"string","string","string","string","string","int","int","int","int"},
option_map = {primary="account_id",unique="account_name"}
})

assert(ALittle.EventDispatcher, " extends class:ALittle.EventDispatcher is nil")
ALittle.WebAccountManager = Lua.Class(ALittle.EventDispatcher, "ALittle.WebAccountManager")

function ALittle.WebAccountManager:Ctor()
	___rawset(self, "_id_map_account", {})
	___rawset(self, "_client_map_account", {})
	___rawset(self, "_account_count", 0)
end

function ALittle.WebAccountManager:Setup()
	local ___COROUTINE = coroutine.running()
	local error = A_MysqlSystem:CreateIfNotExit(___all_struct[-192825113])
	Lua.Assert(error == nil, error)
	error = A_MysqlSystem:CreateIfNotExit(___all_struct[-699725823])
	Lua.Assert(error == nil, error)
	local count = 0
	error, count = A_MysqlSystem:SelectCount(___all_struct[-699725823], "role_id", "alittle")
	if error ~= nil then
		ALittle.Error(error)
	end
	if count == 0 then
		local role_info = {}
		role_info.role_id = "alittle"
		role_info.role_name = "alittle"
		role_info.permission = {}
		role_info.creator_id = "alittle"
		local time, index = ALittle.NewTimeAndIndex()
		role_info.create_time = time
		role_info.create_index = index
		role_info.update_time = time
		role_info.update_index = index
		error = A_MysqlSystem:InsertInto(___all_struct[-699725823], role_info)
		if error ~= nil then
			ALittle.Error(error)
		end
	end
	error, count = A_MysqlSystem:SelectCount(___all_struct[-192825113], "account_name", "alittle")
	if error ~= nil then
		ALittle.Error(error)
	end
	if count == 0 then
		local base_info = {}
		base_info.account_id = ALittle.String_Md5("alittle")
		base_info.account_name = "alittle"
		base_info.account_pwd = ALittle.String_Md5("ALittle" .. ALittle.String_Md5("alittle") .. "ALittle")
		base_info.role_id = "alittle"
		local time, index = ALittle.NewTimeAndIndex()
		base_info.create_time = time
		base_info.create_index = index
		base_info.update_time = time
		base_info.update_index = index
		error = A_MysqlSystem:InsertInto(___all_struct[-192825113], base_info)
		if error ~= nil then
			ALittle.Error(error)
		end
	end
	self._update_route = ALittle.GatewayUpdateRoute(__CPPAPI_ServerSchedule:GetClientServerYunIp(), __CPPAPI_ServerSchedule:GetClientServerIp(), __CPPAPI_ServerSchedule:GetClientServerPort(), __CPPAPI_ServerSchedule:GetHttpServerYunIp(), __CPPAPI_ServerSchedule:GetHttpServerIp(), __CPPAPI_ServerSchedule:GetHttpServerPort(), self._account_count)
	A_ClientSystem:AddEventListener(___all_struct[-245025090], self, self.HandleClientDisconnect)
	A_ClientSystem:AddEventListener(___all_struct[-1221484301], self, self.HandleClientConnect)
end

function ALittle.WebAccountManager:GetAccountById(account_id)
	return self._id_map_account[account_id]
end

function ALittle.WebAccountManager:SendMsgToAll(T, msg)
	for id, account in ___pairs(self._id_map_account) do
		account:SendMsg(T, msg)
	end
end

function ALittle.WebAccountManager:GetAccountByClient(client)
	return self._client_map_account[client]
end

function ALittle.WebAccountManager:AddAccount(account)
	self._client_map_account[account:GetClient()] = account
	self._id_map_account[account:GetID()] = account
	self._account_count = self._account_count + 1
end

function ALittle.WebAccountManager:RemoveAccount(account_id)
	local account = self._id_map_account[account_id]
	if account == nil then
		return
	end
	self._id_map_account[account_id] = nil
	self._client_map_account[account:GetClient()] = nil
	self._account_count = self._account_count - 1
	self._update_route:UpdateRouteWeight(self._account_count)
end

function ALittle.WebAccountManager:ForceLogout(account_id, reason)
	local account = self._id_map_account[account_id]
	if account == nil then
		return false
	end
	local logout_event = {}
	logout_event.account = account
	self:DispatchEvent(___all_struct[-1393745450], logout_event)
	account:ForceLogout(reason)
	account:LogoutActionSystem()
	self:RemoveAccount(account_id)
	return true
end

function ALittle.WebAccountManager:CheckLoginById(account_id, session_id)
	local account = self:GetAccountById(account_id)
	Lua.Assert(account ~= nil, "请先登录")
	Lua.Assert(account:CheckSessionCodeAndSync(session_id), "请先登录")
	return account
end

function ALittle.WebAccountManager:CheckLoginByClient(client)
	local account = self:GetAccountByClient(client)
	Lua.Assert(account ~= nil, "请先登录")
	return account
end

function ALittle.WebAccountManager:Shutdown()
end

function ALittle.WebAccountManager:HandleClientDisconnect(event)
	event.msg_receiver._web_is_logining = false
	local account = self:GetAccountById(event.msg_receiver._web_account_id)
	if account == nil then
		return
	end
	local logout_event = {}
	logout_event.account = account
	self:DispatchEvent(___all_struct[-245025090], event)
	event.msg_receiver._web_account_id = ""
	account:LogoutActionSystem()
	self:RemoveAccount(account:GetID())
end

function ALittle.WebAccountManager:HandleClientConnect(event)
end

_G.A_WebAccountManager = ALittle.WebAccountManager()
function ALittle.HandleQWebLogin(client, msg)
	local ___COROUTINE = coroutine.running()
	local receiver = client
	Lua.Assert(receiver._web_account_id == "" or receiver._web_account_id == nil, "当前连接已经登录")
	local error = nil
	local base_info = nil
	error, base_info = A_MysqlSystem:SelectOneFromByKey(___all_struct[-192825113], "account_name", msg.account_name)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(base_info ~= nil, "账号或密码错误")
	Lua.Assert(base_info.account_pwd == ALittle.String_Md5("ALittle" .. msg.account_pwd .. "ALittle"), "账号或密码错误")
	local role_info = nil
	error, role_info = A_MysqlSystem:SelectOneFromByKey(___all_struct[-699725823], "role_id", base_info.role_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(role_info ~= nil, "您没有登录权限")
	local permission_map = {}
	for i, permission in ___ipairs(role_info.permission) do
		permission_map[permission] = true
	end
	Lua.Assert(msg.account_name == "alittle" or permission_map["105"] ~= nil, "您没有登录权限")
	local other_account = A_WebAccountManager:GetAccountById(base_info.account_id)
	if other_account ~= nil then
		local other_client = other_account:GetClient()
		other_account:ForceLogout("您的账号再另一个地方登录了")
		other_account:LogoutActionSystem()
		A_WebAccountManager:RemoveAccount(base_info.account_id)
		if other_client ~= nil then
			other_client._web_account_id = ""
		end
	end
	local web_account = ALittle.WebAccount(receiver, base_info, role_info)
	A_WebAccountManager:AddAccount(web_account)
	receiver._web_account_id = base_info.account_id
	web_account:LoginActionSystem()
	local login_event = {}
	login_event.account = web_account
	A_WebAccountManager:DispatchEvent(___all_struct[-1353883986], login_event)
	A_WebAccountManager._update_route:UpdateRouteWeight(A_WebAccountManager._account_count)
	return {}
end

ALittle.RegMsgRpcCallback(898014419, ALittle.HandleQWebLogin, -303211063)
function ALittle.HandleQWebLogout(client, msg)
	local ___COROUTINE = coroutine.running()
	local receiver = client
	Lua.Assert(receiver._web_account_id ~= nil and receiver._web_account_id ~= "", "当前连接还未登录")
	local web_account = A_WebAccountManager:GetAccountByClient(receiver)
	Lua.Assert(web_account ~= nil, "账号还未登录")
	local logout_event = {}
	logout_event.account = web_account
	A_WebAccountManager:DispatchEvent(___all_struct[-1393745450], logout_event)
	receiver._web_account_id = ""
	web_account:LogoutActionSystem()
	A_WebAccountManager:RemoveAccount(web_account:GetID())
	return {}
end

ALittle.RegMsgRpcCallback(1598450085, ALittle.HandleQWebLogout, -344058063)
function ALittle.HandleQWebChangePassword(client, msg)
	local ___COROUTINE = coroutine.running()
	local web_account = A_WebAccountManager:CheckLoginByClient(client)
	local error = nil
	local base_info = nil
	error, base_info = A_MysqlSystem:SelectOneFromByKey(___all_struct[-192825113], "account_id", web_account:GetID())
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(base_info ~= nil, "账号不存在")
	Lua.Assert(ALittle.String_Md5("ALittle" .. msg.old_password .. "ALittle") == base_info.account_pwd, "原密码错误")
	local new_password = ALittle.String_Md5("ALittle" .. msg.new_password .. "ALittle")
	error = A_MysqlSystem:UpdateSet(___all_struct[-192825113], "account_pwd", new_password, "account_id", base_info.account_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	return {}
end

ALittle.RegMsgRpcCallback(-1373673802, ALittle.HandleQWebChangePassword, 1652964636)
end