
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine
local ___all_struct = GetAllStruct()

RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
RegStruct(-1010453448, "DataServer.GS2DATA_NRegStruct", {
name = "DataServer.GS2DATA_NRegStruct", ns_name = "DataServer", rl_name = "GS2DATA_NRegStruct", hash_code = -1010453448,
name_list = {"rflt_list","table_map"},
type_list = {"List<ALittle.StructInfo>","Map<int,bool>"},
option_map = {}
})
RegStruct(1847150134, "ALittle.StructInfo", {
name = "ALittle.StructInfo", ns_name = "ALittle", rl_name = "StructInfo", hash_code = 1847150134,
name_list = {"name","ns_name","rl_name","hash_code","name_list","type_list","option_map"},
type_list = {"string","string","string","int","List<string>","List<string>","Map<string,string>"},
option_map = {}
})
RegStruct(-660832923, "ALittle.GS2C_NForceLogout", {
name = "ALittle.GS2C_NForceLogout", ns_name = "ALittle", rl_name = "GS2C_NForceLogout", hash_code = -660832923,
name_list = {"reason"},
type_list = {"string"},
option_map = {}
})
RegStruct(-1162432155, "ALittle.C2GS_QLogin", {
name = "ALittle.C2GS_QLogin", ns_name = "ALittle", rl_name = "C2GS_QLogin", hash_code = -1162432155,
name_list = {"account_id","session","device"},
type_list = {"int","string","string"},
option_map = {}
})
RegStruct(1569725693, "ALittle.GS2C_ALogin", {
name = "ALittle.GS2C_ALogin", ns_name = "ALittle", rl_name = "GS2C_ALogin", hash_code = 1569725693,
name_list = {},
type_list = {},
option_map = {}
})
RegStruct(-1836835016, "ALittle.GS2C_NDataReady", {
name = "ALittle.GS2C_NDataReady", ns_name = "ALittle", rl_name = "GS2C_NDataReady", hash_code = -1836835016,
name_list = {},
type_list = {},
option_map = {}
})
RegStruct(-2092316375, "ALittle.SS2GS_QCheckSessionCode", {
name = "ALittle.SS2GS_QCheckSessionCode", ns_name = "ALittle", rl_name = "SS2GS_QCheckSessionCode", hash_code = -2092316375,
name_list = {"account_id","session_code"},
type_list = {"int","string"},
option_map = {}
})
RegStruct(-1766835499, "ALittle.GS2SS_ACheckSessionCode", {
name = "ALittle.GS2SS_ACheckSessionCode", ns_name = "ALittle", rl_name = "GS2SS_ACheckSessionCode", hash_code = -1766835499,
name_list = {},
type_list = {},
option_map = {}
})

GameAccountManager = Class(nil, "ALittle.GameAccountManager")

function GameAccountManager:Ctor()
	___rawset(self, "_account_map", {})
	___rawset(self, "_account_count", 0)
	___rawset(self, "_client_map", {})
	___rawset(self, "_reg_struct_map", {})
end

function GameAccountManager:Setup(create_callback)
	g_GameLeaseManager:Setup()
	g_GameLoginManager:Setup()
	self._create_callback = create_callback
	A_ClientSystem:AddEventListener(___all_struct[-245025090], self, self.HandleClientDisconnected)
	A_SessionSystem:AddEventListener(___all_struct[-36908822], self, self.HandleAnySessionDisconnected)
	self._update_route = GatewayUpdateRoute(__CPPAPI_ServerSchedule:GetClientServerYunIp(), __CPPAPI_ServerSchedule:GetClientServerIp(), __CPPAPI_ServerSchedule:GetClientServerPort(), __CPPAPI_ServerSchedule:GetHttpServerYunIp(), __CPPAPI_ServerSchedule:GetHttpServerIp(), __CPPAPI_ServerSchedule:GetHttpServerPort(), self._account_count)
end

function GameAccountManager:Shutdown()
	g_GameLoginManager:Shutdown()
	g_GameLeaseManager:Shutdown()
end

function GameAccountManager:GetAccountByClient(client)
	return self._client_map[client]
end

function GameAccountManager:GetAccountById(account_id)
	return self._account_map[account_id]
end

function GameAccountManager:CreateAccount(account_id)
	local account = self._account_map[account_id]
	if account == nil then
		if self._create_callback ~= nil then
			account = self._create_callback(account_id)
		end
		if account == nil then
			account = GameAccount(account_id)
		end
		self._account_map[account_id] = account
		self._account_count = self._account_count + 1
		self._update_route:UpdateRouteWeight(self._account_count)
	end
	return account
end

function GameAccountManager:DeleteAccount(account)
	local cur_account = self._account_map[account:GetId()]
	if cur_account == account then
		account:Release()
		self._account_count = self._account_count - 1
		self._account_map[account:GetId()] = nil
		self._update_route:UpdateRouteWeight(self._account_count)
	end
end

function GameAccountManager:IsSendModuleReflect(session)
	return self._reg_struct_map[session] == true
end

function GameAccountManager:SendModuleReflect(session, rflt_list, table_map)
	if self._reg_struct_map[session] then
		return
	end
	self._reg_struct_map[session] = true
	local param = {}
	param.rflt_list = rflt_list
	param.table_map = table_map
	session:SendMsg(___all_struct[-1010453448], param)
end
GameAccountManager.SendModuleReflect = CoWrap(GameAccountManager.SendModuleReflect)

function GameAccountManager:SetAccountClient(account, client)
	local old_client = account:GetClient()
	if old_client ~= nil then
		self._client_map[old_client] = nil
	end
	account:SetClient(client)
	if client ~= nil then
		self._client_map[client] = account
	end
end

function GameAccountManager:HandleClientDisconnected(event)
	local account = self._client_map[event.msg_receiver]
	if account == nil then
		return
	end
	local status = account:GetStatus()
	if status == GameAccountStatus.CREATE then
		self:SetAccountClient(account, nil)
		return
	end
	if status == GameAccountStatus.LOADING then
		self:SetAccountClient(account, nil)
		return
	end
	if status == GameAccountStatus.CACHE then
		account:Backup()
		self:SetAccountClient(account, nil)
		return
	end
	if status == GameAccountStatus.ONLINE then
		account:LogoutAction()
		account:SetStatus(GameAccountStatus.CACHE)
		account:StartCacheTimer()
		self:SetAccountClient(account, nil)
		return
	end
	self:SetAccountClient(account, nil)
end

function GameAccountManager:HandleAnySessionDisconnected(event)
	if event.route_type ~= RouteType.RT_DATA then
		return
	end
	self._reg_struct_map[event.session] = nil
end

function GameAccountManager:HandleLeaseTimeout(account_id)
	local account = self._account_map[account_id]
	if account == nil then
		return
	end
	local status = account:GetStatus()
	if status == GameAccountStatus.CREATE then
		self:SetAccountClient(account, nil)
		self:DeleteAccount(account)
		return
	end
	if status == GameAccountStatus.LOADING then
		self:SetAccountClient(account, nil)
		self:DeleteAccount(account)
		return
	end
	if status == GameAccountStatus.CACHE then
		account:Backup()
		self:SetAccountClient(account, nil)
		self:DeleteAccount(account)
		return
	end
	if status == GameAccountStatus.ONLINE then
		account:LogoutAction()
		local param = {}
		param.reason = "租约超时"
		account:SendMsg(___all_struct[-660832923], param)
		self:SetAccountClient(account, nil)
		self:DeleteAccount(account)
		return
	end
	self:DeleteAccount(account)
end

_G.A_GameAccountManager = GameAccountManager()
function HandleQLogin(client, msg)
	local lease_info = g_GameLeaseManager:GetLease(msg.account_id)
	Assert(lease_info, "没有租约信息:" .. msg.account_id)
	Assert(g_GameLoginManager:ChcekSession(msg.account_id, msg.session), "会话ID错误")
	g_GameLoginManager:RemoveSession(msg.account_id)
	local account = A_GameAccountManager:CreateAccount(msg.account_id)
	local status = account:GetStatus()
	if status == GameAccountStatus.CREATE then
		account:SetStatus(GameAccountStatus.LOADING)
		A_GameAccountManager:SetAccountClient(account, client)
		account:StartLoading(lease_info.session)
		return {}
	end
	if status == GameAccountStatus.LOADING then
		local param = {}
		param.reason = "您的账号在另一个地方登录"
		account:SendMsg(___all_struct[-660832923], param)
		A_GameAccountManager:SetAccountClient(account, client)
		return {}
	end
	if status == GameAccountStatus.CACHE then
		local param = {}
		param.reason = "您的账号在另一个地方登录"
		account:SendMsg(___all_struct[-660832923], param)
		A_GameAccountManager:SetAccountClient(account, client)
		account:SetStatus(GameAccountStatus.ONLINE)
		account:StopCacheTimer()
		account:LoginAction()
		return {}
	end
	if status == GameAccountStatus.ONLINE then
		account:LogoutAction()
		local param = {}
		param.reason = "您的账号在另一个地方登录"
		account:SendMsg(___all_struct[-660832923], param)
		A_GameAccountManager:SetAccountClient(account, client)
		account:LoginAction()
		return {}
	end
	Throw("未知的账号状态")
end

RegMsgRpcCallback(-1162432155, HandleQLogin, 1569725693)
function HandleQCheckSessionCode(client, msg)
	local account = A_GameAccountManager:GetAccountById(msg.account_id)
	Assert(account, "账号不存在")
	Assert(account:GetSession() == msg.session_code, "验证码错误")
	return {}
end

RegMsgRpcCallback(-2092316375, HandleQCheckSessionCode, -1766835499)
