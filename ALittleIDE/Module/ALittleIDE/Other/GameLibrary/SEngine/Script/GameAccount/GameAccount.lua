-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1821069430, "ALittle.ProtocolAnyStruct", {
name = "ALittle.ProtocolAnyStruct", ns_name = "ALittle", rl_name = "ProtocolAnyStruct", hash_code = 1821069430,
name_list = {"hash_code","value"},
type_list = {"int","any"},
option_map = {}
})
ALittle.RegStruct(1463647694, "DataServer.GS2DATA_NBackupStruct", {
name = "DataServer.GS2DATA_NBackupStruct", ns_name = "DataServer", rl_name = "GS2DATA_NBackupStruct", hash_code = 1463647694,
name_list = {"account_id","data"},
type_list = {"int","ALittle.ProtocolAnyStruct"},
option_map = {}
})
ALittle.RegStruct(-1121683527, "DataServer.GS2DATA_QLoadStruct", {
name = "DataServer.GS2DATA_QLoadStruct", ns_name = "DataServer", rl_name = "GS2DATA_QLoadStruct", hash_code = -1121683527,
name_list = {"account_id","hash_code"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(-197564509, "ALittle.GS2C_NAccountInfo", {
name = "ALittle.GS2C_NAccountInfo", ns_name = "ALittle", rl_name = "GS2C_NAccountInfo", hash_code = -197564509,
name_list = {"session_code","account_id","gs_route_id"},
type_list = {"string","int","int"},
option_map = {}
})

ALittle.GameAccountStatus = {
	CREATE = 1,
	LOADING = 2,
	CACHE = 3,
	ONLINE = 4,
}

ALittle.GameModule = Lua.Class(nil, "ALittle.GameModule")

function ALittle.GameModule:Ctor(account)
	___rawset(self, "_account", account)
	self._account:RegisterModule(self)
end

function ALittle.GameModule:GetDataReflect()
	return nil
end

function ALittle.GameModule:Release()
end

function ALittle.GameModule:HasData()
	return false
end

function ALittle.GameModule:LoadData(session)
end
ALittle.GameModule.LoadData = Lua.CoWrap(ALittle.GameModule.LoadData)

function ALittle.GameModule:BackupData(session)
end

function ALittle.GameModule:OnDataReady()
end

function ALittle.GameModule:OnSendData()
end

function ALittle.GameModule:OnLogout()
end

assert(ALittle.GameModule, " extends class:ALittle.GameModule is nil")
ALittle.GameModuleTemplate = Lua.Class(ALittle.GameModule, "ALittle.GameModuleTemplate")

function ALittle.GameModuleTemplate:GetDataReflect()
	return self.__class.__element[1]
end

function ALittle.GameModuleTemplate:OnSendData()
	self._account:SendMsg(self.__class.__element[1], self._data)
end

function ALittle.GameModuleTemplate:HasData()
	return true
end

function ALittle.GameModuleTemplate:LoadData(session)
	if session == nil then
		ALittle.Error(tostring(self) .. " session == null")
		self._account:LoadOneCompleted(false)
		return
	end
	local rflt = self:GetDataReflect()
	if rflt == nil then
		ALittle.Error(tostring(self) .. ":GetDataReflect() == null")
		self._account:LoadOneCompleted(false)
		return
	end
	local param = {}
	param.account_id = self._account:GetId()
	param.hash_code = rflt.hash_code
	local error, result = ALittle.IMsgCommon.InvokeRPC(-1121683527, session, param)
	if error ~= nil then
		ALittle.Error(tostring(self) .. " DataServer.HandleQLoadStruct() failed:" .. error)
		self._account:LoadOneCompleted(false)
		return
	end
	self._data = result.value
	self._account:LoadOneCompleted(true)
end
ALittle.GameModuleTemplate.LoadData = Lua.CoWrap(ALittle.GameModuleTemplate.LoadData)

function ALittle.GameModuleTemplate:BackupData(session)
	if session == nil then
		return
	end
	local rflt = self:GetDataReflect()
	if rflt == nil then
		ALittle.Error(tostring(self) .. ":GetDataReflect() == null")
		self._account:LoadOneCompleted(false)
		return
	end
	local param = {}
	param.account_id = self._account:GetId()
	param.data = {}
	param.data.hash_code = rflt.hash_code
	param.data.value = self._data
	session:SendMsg(___all_struct[1463647694], param)
end

ALittle.GameAccount = Lua.Class(nil, "ALittle.GameAccount")

function ALittle.GameAccount:Ctor(id)
	___rawset(self, "_id", id)
	___rawset(self, "_loading_count", 0)
	___rawset(self, "_loading_failed", false)
	___rawset(self, "_status", 1)
	___rawset(self, "_module_map", {})
	___rawset(self, "_BACKUP_INTERVAL", 10 * 1000)
	___rawset(self, "_CACHE_INTERVAL", 30 * 1000)
	___rawset(self, "_session", tostring(math.random(10000, 99999)))
end

function ALittle.GameAccount:Release()
	for name, module in ___pairs(self._module_map) do
		module:Release()
	end
	self:StopBackupTimer()
	self:StopCacheTimer()
end

function ALittle.GameAccount:GetId()
	return self._id
end

function ALittle.GameAccount:SetClient(client)
	self._client = client
end

function ALittle.GameAccount:GetClient()
	return self._client
end

function ALittle.GameAccount:GetStatus()
	return self._status
end

function ALittle.GameAccount:SetStatus(status)
	self._status = status
end

function ALittle.GameAccount:GetSession()
	return self._session
end

function ALittle.GameAccount:RegisterModule(module)
	local rflt = (module).__class
	self._module_map[rflt.__name] = module
end

function ALittle.GameAccount:GetAllDataReflect()
	local map = {}
	local table_map = {}
	for name, module in ___pairs(self._module_map) do
		local rflt = module:GetDataReflect()
		if rflt ~= nil then
			table_map[rflt.hash_code] = true
			local error = ALittle.CollectStructReflect(rflt, map)
			if error ~= nil then
				ALittle.Error(error)
			end
		end
	end
	local rflt_list = {}
	local count = 0
	for hash_code, info in ___pairs(map) do
		count = count + 1
		rflt_list[count] = info
	end
	return rflt_list, table_map
end

function ALittle.GameAccount:StartLoading(session)
	if not A_GameAccountManager:IsSendModuleReflect(session) then
		local rflt_list, table_map = self:GetAllDataReflect()
		A_GameAccountManager:SendModuleReflect(session, rflt_list, table_map)
	end
	self._loading_count = 0
	for name, module in ___pairs(self._module_map) do
		if module:HasData() then
			self._loading_count = self._loading_count + 1
		end
	end
	if self._loading_count == 0 then
		self:LoadOneCompletedImpl()
		return
	end
	for name, module in ___pairs(self._module_map) do
		module:LoadData(session)
	end
end

function ALittle.GameAccount:LoadOneCompleted(result)
	self._loading_count = self._loading_count - 1
	if not result then
		self._loading_failed = true
	end
	if self._loading_count > 0 then
		return
	end
	self:LoadOneCompletedImpl()
end

function ALittle.GameAccount:LoadOneCompletedImpl()
	local account = A_GameAccountManager:GetAccountById(self._id)
	if account ~= self then
		return
	end
	self:OnDataReady()
	if self._client ~= nil then
		self:SetStatus(4)
		self:LoginAction()
	else
		self:SetStatus(3)
		self:StartCacheTimer()
	end
	self:StartBackupTimer()
end

function ALittle.GameAccount:StartBackupTimer()
	ALittle.Log("StartBackupTimer, account_id:" .. self._id)
	if self._backup_timer ~= nil then
		A_LoopSystem:RemoveTimer(self._backup_timer)
	end
	self._backup_timer = A_LoopSystem:AddTimer(self._BACKUP_INTERVAL, Lua.Bind(self.Backup, self), 0, self._BACKUP_INTERVAL)
end

function ALittle.GameAccount:StopBackupTimer()
	if self._backup_timer == nil then
		return
	end
	ALittle.Log("StopBackupTimer, account_id:" .. self._id)
	A_LoopSystem:RemoveTimer(self._backup_timer)
	self._backup_timer = nil
end

function ALittle.GameAccount:StartCacheTimer()
	ALittle.Log("StartCacheTimer, account_id:" .. self._id)
	if self._cache_timer ~= nil then
		A_LoopSystem:RemoveTimer(self._cache_timer)
	end
	self._cache_timer = A_LoopSystem:AddTimer(self._CACHE_INTERVAL, Lua.Bind(self.CacheTimeout, self))
end

function ALittle.GameAccount:StopCacheTimer()
	if self._cache_timer == nil then
		return
	end
	ALittle.Log("StopCacheTimer, account_id:" .. self._id)
	A_LoopSystem:RemoveTimer(self._cache_timer)
	self._cache_timer = nil
end

function ALittle.GameAccount:CacheTimeout()
	ALittle.Log("CacheTimeout, account_id:" .. self._id)
	self._cache_timer = nil
	self:Backup()
	ALittle.g_GameLeaseManager:ReleaseLease(self._id)
	A_GameAccountManager:DeleteAccount(self)
end

function ALittle.GameAccount:Backup()
	ALittle.Log("Backup, account_id:" .. self._id)
	local lease_info = ALittle.g_GameLeaseManager:GetLease(self._id)
	if lease_info == nil or lease_info.session == nil then
		return
	end
	for name, module in ___pairs(self._module_map) do
		module:BackupData(lease_info.session)
	end
end

function ALittle.GameAccount:LogoutAction()
	for name, module in ___pairs(self._module_map) do
		module:OnLogout()
	end
	self:Backup()
end

function ALittle.GameAccount:OnDataReady()
	for name, module in ___pairs(self._module_map) do
		module:OnDataReady()
	end
end

function ALittle.GameAccount:LoginAction()
	local param = {}
	param.account_id = self._id
	param.gs_route_id = __CPPAPI_ServerSchedule:GetRouteId()
	param.session_code = self._session
	self:SendMsg(___all_struct[-197564509], param)
	for name, module in ___pairs(self._module_map) do
		module:OnSendData()
	end
	self:SendMsg(___all_struct[-1836835016], {})
end

function ALittle.GameAccount:SendMsg(T, msg)
	if self._client == nil then
		return
	end
	self._client:SendMsg(T, msg)
end

end