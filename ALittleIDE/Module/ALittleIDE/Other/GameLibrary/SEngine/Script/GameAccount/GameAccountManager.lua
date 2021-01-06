-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-2092316375, "ALittle.SS2GS_QCheckSessionCode", {
name = "ALittle.SS2GS_QCheckSessionCode", ns_name = "ALittle", rl_name = "SS2GS_QCheckSessionCode", hash_code = -2092316375,
name_list = {"account_id","session_code"},
type_list = {"int","string"},
option_map = {}
})
ALittle.RegStruct(1847150134, "ALittle.StructInfo", {
name = "ALittle.StructInfo", ns_name = "ALittle", rl_name = "StructInfo", hash_code = 1847150134,
name_list = {"name","ns_name","rl_name","hash_code","name_list","type_list","option_map"},
type_list = {"string","string","string","int","List<string>","List<string>","Map<string,string>"},
option_map = {}
})
ALittle.RegStruct(-1836835016, "ALittle.GS2C_NDataReady", {
name = "ALittle.GS2C_NDataReady", ns_name = "ALittle", rl_name = "GS2C_NDataReady", hash_code = -1836835016,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1766835499, "ALittle.GS2SS_ACheckSessionCode", {
name = "ALittle.GS2SS_ACheckSessionCode", ns_name = "ALittle", rl_name = "GS2SS_ACheckSessionCode", hash_code = -1766835499,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(1569725693, "ALittle.GS2C_ALogin", {
name = "ALittle.GS2C_ALogin", ns_name = "ALittle", rl_name = "GS2C_ALogin", hash_code = 1569725693,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1162432155, "ALittle.C2GS_QLogin", {
name = "ALittle.C2GS_QLogin", ns_name = "ALittle", rl_name = "C2GS_QLogin", hash_code = -1162432155,
name_list = {"account_id","session","device"},
type_list = {"int","string","string"},
option_map = {}
})
ALittle.RegStruct(-1010453448, "DataServer.GS2DATA_NRegStruct", {
name = "DataServer.GS2DATA_NRegStruct", ns_name = "DataServer", rl_name = "GS2DATA_NRegStruct", hash_code = -1010453448,
name_list = {"rflt_list","table_map"},
type_list = {"List<ALittle.StructInfo>","Map<int,bool>"},
option_map = {}
})
ALittle.RegStruct(-660832923, "ALittle.GS2C_NForceLogout", {
name = "ALittle.GS2C_NForceLogout", ns_name = "ALittle", rl_name = "GS2C_NForceLogout", hash_code = -660832923,
name_list = {"reason"},
type_list = {"string"},
option_map = {}
})

ALittle.GameAccountManager = Lua.Class(nil, "ALittle.GameAccountManager")

function ALittle.GameAccountManager:Ctor()
	___rawset(self, "_account_map", {})
	___rawset(self, "_account_count", 0)
	___rawset(self, "_client_map", {})
	___rawset(self, "_reg_struct_map", {})
end

function ALittle.GameAccountManager:Setup(create_callback)
	ALittle.g_GameLeaseManager:Setup()
	ALittle.g_GameLoginManager:Setup()
	self._create_callback = create_callback
	A_ClientSystem:AddEventListener(___all_struct[-245025090], self, self.HandleClientDisconnected)
	A_SessionSystem:AddEventListener(___all_struct[-36908822], self, self.HandleAnySessionDisconnected)
	self._update_route = ALittle.GatewayUpdateRoute(__CPPAPI_ServerSchedule:GetClientServerYunIp(), __CPPAPI_ServerSchedule:GetClientServerIp(), __CPPAPI_ServerSchedule:GetClientServerPort(), __CPPAPI_ServerSchedule:GetHttpServerYunIp(), __CPPAPI_ServerSchedule:GetHttpServerIp(), __CPPAPI_ServerSchedule:GetHttpServerPort(), self._account_count)
end

function ALittle.GameAccountManager:Shutdown()
	ALittle.g_GameLoginManager:Shutdown()
	ALittle.g_GameLeaseManager:Shutdown()
end

function ALittle.GameAccountManager:GetAccountByClient(client)
	return self._client_map[client]
end

function ALittle.GameAccountManager:GetAccountById(account_id)
	return self._account_map[account_id]
end

function ALittle.GameAccountManager:CreateAccount(account_id)
	local account = self._account_map[account_id]
	if account == nil then
		if self._create_callback ~= nil then
			account = self._create_callback(account_id)
		end
		if account == nil then
			account = ALittle.GameAccount(account_id)
		end
		self._account_map[account_id] = account
		self._account_count = self._account_count + 1
		self._update_route:UpdateRouteWeight(self._account_count)
	end
	return account
end

function ALittle.GameAccountManager:DeleteAccount(account)
	local cur_account = self._account_map[account:GetId()]
	if cur_account == account then
		account:Release()
		self._account_count = self._account_count - 1
		self._account_map[account:GetId()] = nil
		self._update_route:UpdateRouteWeight(self._account_count)
	end
end

function ALittle.GameAccountManager:IsSendModuleReflect(session)
	return self._reg_struct_map[session] == true
end

function ALittle.GameAccountManager:SendModuleReflect(session, rflt_list, table_map)
	if self._reg_struct_map[session] then
		return
	end
	self._reg_struct_map[session] = true
	local param = {}
	param.rflt_list = rflt_list
	param.table_map = table_map
	session:SendMsg(___all_struct[-1010453448], param)
end
ALittle.GameAccountManager.SendModuleReflect = Lua.CoWrap(ALittle.GameAccountManager.SendModuleReflect)

function ALittle.GameAccountManager:SetAccountClient(account, client)
	local old_client = account:GetClient()
	if old_client ~= nil then
		self._client_map[old_client] = nil
	end
	account:SetClient(client)
	if client ~= nil then
		self._client_map[client] = account
	end
end

function ALittle.GameAccountManager:HandleClientDisconnected(event)
	local account = self._client_map[event.msg_receiver]
	if account == nil then
		return
	end
	local status = account:GetStatus()
	if status == 1 then
		self:SetAccountClient(account, nil)
		return
	end
	if status == 2 then
		self:SetAccountClient(account, nil)
		return
	end
	if status == 3 then
		account:Backup()
		self:SetAccountClient(account, nil)
		return
	end
	if status == 4 then
		account:LogoutAction()
		account:SetStatus(3)
		account:StartCacheTimer()
		self:SetAccountClient(account, nil)
		return
	end
	self:SetAccountClient(account, nil)
end

function ALittle.GameAccountManager:HandleAnySessionDisconnected(event)
	if event.route_type ~= 2 then
		return
	end
	self._reg_struct_map[event.session] = nil
end

function ALittle.GameAccountManager:HandleLeaseTimeout(account_id)
	local account = self._account_map[account_id]
	if account == nil then
		return
	end
	local status = account:GetStatus()
	if status == 1 then
		self:SetAccountClient(account, nil)
		self:DeleteAccount(account)
		return
	end
	if status == 2 then
		self:SetAccountClient(account, nil)
		self:DeleteAccount(account)
		return
	end
	if status == 3 then
		account:Backup()
		self:SetAccountClient(account, nil)
		self:DeleteAccount(account)
		return
	end
	if status == 4 then
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

_G.A_GameAccountManager = ALittle.GameAccountManager()
function ALittle.HandleQLogin(client, msg)
	local ___COROUTINE = coroutine.running()
	local lease_info = ALittle.g_GameLeaseManager:GetLease(msg.account_id)
	Lua.Assert(lease_info, "没有租约信息:" .. msg.account_id)
	Lua.Assert(ALittle.g_GameLoginManager:ChcekSession(msg.account_id, msg.session), "会话ID错误")
	ALittle.g_GameLoginManager:RemoveSession(msg.account_id)
	local account = A_GameAccountManager:CreateAccount(msg.account_id)
	local status = account:GetStatus()
	if status == 1 then
		account:SetStatus(2)
		A_GameAccountManager:SetAccountClient(account, client)
		account:StartLoading(lease_info.session)
		return {}
	end
	if status == 2 then
		local param = {}
		param.reason = "您的账号在另一个地方登录"
		account:SendMsg(___all_struct[-660832923], param)
		A_GameAccountManager:SetAccountClient(account, client)
		return {}
	end
	if status == 3 then
		local param = {}
		param.reason = "您的账号在另一个地方登录"
		account:SendMsg(___all_struct[-660832923], param)
		A_GameAccountManager:SetAccountClient(account, client)
		account:SetStatus(4)
		account:StopCacheTimer()
		account:LoginAction()
		return {}
	end
	if status == 4 then
		account:LogoutAction()
		local param = {}
		param.reason = "您的账号在另一个地方登录"
		account:SendMsg(___all_struct[-660832923], param)
		A_GameAccountManager:SetAccountClient(account, client)
		account:LoginAction()
		return {}
	end
	Lua.Throw("未知的账号状态")
end

ALittle.RegMsgRpcCallback(-1162432155, ALittle.HandleQLogin, 1569725693)
function ALittle.HandleQCheckSessionCode(client, msg)
	local ___COROUTINE = coroutine.running()
	local account = A_GameAccountManager:GetAccountById(msg.account_id)
	Lua.Assert(account, "账号不存在")
	Lua.Assert(account:GetSession() == msg.session_code, "验证码错误")
	return {}
end

ALittle.RegMsgRpcCallback(-2092316375, ALittle.HandleQCheckSessionCode, -1766835499)
end