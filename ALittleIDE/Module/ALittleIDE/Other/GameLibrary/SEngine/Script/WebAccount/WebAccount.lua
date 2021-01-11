-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1809602374, "ALittle.S2CWebSession", {
name = "ALittle.S2CWebSession", ns_name = "ALittle", rl_name = "S2CWebSession", hash_code = 1809602374,
name_list = {"session_id"},
type_list = {"string"},
option_map = {}
})
ALittle.RegStruct(1391512615, "ALittle.S2CWebForceLogout", {
name = "ALittle.S2CWebForceLogout", ns_name = "ALittle", rl_name = "S2CWebForceLogout", hash_code = 1391512615,
name_list = {"reason"},
type_list = {"string"},
option_map = {}
})
ALittle.RegStruct(799192036, "ALittle.SessionInfo", {
name = "ALittle.SessionInfo", ns_name = "ALittle", rl_name = "SessionInfo", hash_code = 799192036,
name_list = {"new_client","old_client","time"},
type_list = {"string","string","int"},
option_map = {}
})
ALittle.RegStruct(-417093574, "ALittle.S2CWebAccountInfo", {
name = "ALittle.S2CWebAccountInfo", ns_name = "ALittle", rl_name = "S2CWebAccountInfo", hash_code = -417093574,
name_list = {"account_id","account_name","role_id","role_name","permission_map"},
type_list = {"string","string","string","string","Map<string,bool>"},
option_map = {}
})
ALittle.RegStruct(-300988017, "ALittle.S2CWebServerInfo", {
name = "ALittle.S2CWebServerInfo", ns_name = "ALittle", rl_name = "S2CWebServerInfo", hash_code = -300988017,
name_list = {"http_ip","http_port"},
type_list = {"string","int"},
option_map = {}
})

ALittle.WebAccount = Lua.Class(nil, "ALittle.WebAccount")

function ALittle.WebAccount:Ctor(client, base_info, role_info)
	___rawset(self, "_session_info", {})
	self._session_info.old_client = "s" .. tostring(math.random(100000, 999999))
	self._session_info.new_client = self._session_info.old_client
	self._session_info.time = os.time(nil)
	___rawset(self, "_client", client)
	___rawset(self, "_base_info", base_info)
	___rawset(self, "_role_info", role_info)
	___rawset(self, "_permission_map", {})
	for i, permission in ___ipairs(self._role_info.permission) do
		self._permission_map[permission] = true
	end
end

function ALittle.WebAccount:IsLogin()
	return self._is_login
end

function ALittle.WebAccount:IsDataReady()
	return self._is_login
end

function ALittle.WebAccount:GetID()
	return self._base_info.account_id
end

function ALittle.WebAccount:GetRoleID()
	return self._role_info.role_id
end

function ALittle.WebAccount:GetAccountName()
	return self._base_info.account_name
end

function ALittle.WebAccount:GetClient()
	return self._client
end

function ALittle.WebAccount:SendMsg(T, msg)
	if self._client == nil then
		return
	end
	self._client:SendMsg(T, msg)
end

function ALittle.WebAccount:UpdateRoleInfo()
	local ___COROUTINE = coroutine.running()
	do
		local error, base_info = A_MysqlSystem:SelectOneFromByKey(___all_struct[-192825113], "account_id", self._base_info.account_id)
		if error ~= nil then
			ALittle.Error(error)
		end
		if base_info == nil then
			return
		end
		self._base_info = base_info
	end
	do
		self._role_info = {}
		self._permission_map = {}
		local error, role_info = A_MysqlSystem:SelectOneFromByKey(___all_struct[-699725823], "role_id", self._base_info.role_id)
		if error ~= nil then
			ALittle.Error(error)
		end
		if role_info == nil then
			return
		end
		self._role_info = role_info
	end
	for i, permission in ___ipairs(self._role_info.permission) do
		self._permission_map[permission] = true
	end
end

function ALittle.WebAccount:CheckPermission(permission)
	if self._role_info.role_id == "alittle" then
		return true
	end
	return self._permission_map[permission] ~= nil
end

function ALittle.WebAccount:ForceLogout(reason)
	local param = {}
	param.reason = reason
	self._client:SendMsg(___all_struct[1391512615], param)
end

function ALittle.WebAccount:LogoutActionSystem()
	self._is_login = false
end

function ALittle.WebAccount:LoginActionSystem()
	self._is_login = true
	self:GenSessionCodeAndSync()
	do
		local param = {}
		param.account_id = self._base_info.account_id
		param.account_name = self._base_info.account_name
		param.role_id = self._role_info.role_id
		param.role_name = self._role_info.role_name
		param.permission_map = self._permission_map
		self._client:SendMsg(___all_struct[-417093574], param)
	end
	do
		local param = {}
		param.http_ip = __CPPAPI_ServerSchedule:GetHttpServerYunIp()
		if param.http_ip == nil or param.http_ip == "" then
			param.http_ip = __CPPAPI_ServerSchedule:GetHttpServerIp()
		end
		param.http_port = __CPPAPI_ServerSchedule:GetHttpServerPort()
		self._client:SendMsg(___all_struct[-300988017], param)
	end
end

function ALittle.WebAccount:GenSessionCodeAndSync()
	self._session_info.old_client = self._session_info.new_client
	self._session_info.new_client = "s" .. tostring(math.random(100000, 999999))
	self._session_info.time = os.time(nil)
	local param = {}
	param.session_id = self._session_info.new_client
	self._client:SendMsg(___all_struct[1809602374], param)
end

function ALittle.WebAccount:CheckSessionCodeAndSync(session_code)
	if session_code == nil or session_code == "" then
		return false
	end
	session_code = tostring(session_code)
	local result = self._session_info.old_client == session_code or self._session_info.new_client == session_code
	if os.time(nil) - self._session_info.time > 300 then
		self:GenSessionCodeAndSync()
	end
	return result
end

end