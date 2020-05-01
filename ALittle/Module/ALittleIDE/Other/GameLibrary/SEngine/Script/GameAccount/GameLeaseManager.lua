-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = GetAllStruct()

RegStruct(1860871079, "ALittle.GameLeaseInfo", {
name = "ALittle.GameLeaseInfo", ns_name = "ALittle", rl_name = "GameLeaseInfo", hash_code = 1860871079,
name_list = {"account_id","session","timer"},
type_list = {"int","ALittle.MsgSessionTemplate<ALittle.MsgSessionNative,lua.__CPPAPIMessageWriteFactory>","int"},
option_map = {}
})
RegStruct(-1970485469, "DataServer.GS2DATA_NReleaseLease", {
name = "DataServer.GS2DATA_NReleaseLease", ns_name = "DataServer", rl_name = "GS2DATA_NReleaseLease", hash_code = -1970485469,
name_list = {"account_id"},
type_list = {"int"},
option_map = {}
})
RegStruct(-1057357327, "DataServer.GS2DATA_QRenewLease", {
name = "DataServer.GS2DATA_QRenewLease", ns_name = "DataServer", rl_name = "GS2DATA_QRenewLease", hash_code = -1057357327,
name_list = {"account_id"},
type_list = {"int"},
option_map = {}
})
RegStruct(-276606114, "DataServer.DATA2GS_ARenewLease", {
name = "DataServer.DATA2GS_ARenewLease", ns_name = "DataServer", rl_name = "DATA2GS_ARenewLease", hash_code = -276606114,
name_list = {},
type_list = {},
option_map = {}
})
RegStruct(370639724, "ALittle.DATA2GS_NNewLease", {
name = "ALittle.DATA2GS_NNewLease", ns_name = "ALittle", rl_name = "DATA2GS_NNewLease", hash_code = 370639724,
name_list = {"account_id"},
type_list = {"int"},
option_map = {}
})
RegStruct(-1627449907, "ALittle.DATA2GS_QEmpty", {
name = "ALittle.DATA2GS_QEmpty", ns_name = "ALittle", rl_name = "DATA2GS_QEmpty", hash_code = -1627449907,
name_list = {},
type_list = {},
option_map = {}
})
RegStruct(726375194, "ALittle.GS2DATA_AEmpty", {
name = "ALittle.GS2DATA_AEmpty", ns_name = "ALittle", rl_name = "GS2DATA_AEmpty", hash_code = 726375194,
name_list = {},
type_list = {},
option_map = {}
})

GS_LEASE_INTERVAL = 20 * 1000
GameLeaseManager = Lua.Class(nil, "ALittle.GameLeaseManager")

function GameLeaseManager:Ctor()
	___rawset(self, "_lease_map", {})
end

function GameLeaseManager:Setup()
end

function GameLeaseManager:Shutdown()
	for account_id, info in ___pairs(self._lease_map) do
		if info.timer ~= nil then
			A_LoopSystem:RemoveTimer(info.timer)
		end
	end
	self._lease_map = {}
end

function GameLeaseManager:GetLease(account_id)
	return self._lease_map[account_id]
end

function GameLeaseManager:NewLease(session, msg)
	local info = self._lease_map[msg.account_id]
	if info == nil then
		info = {}
		self._lease_map[msg.account_id] = info
	end
	info.session = session
	info.account_id = msg.account_id
	if info.timer ~= nil then
		A_LoopSystem:RemoveTimer(info.timer)
	end
	info.timer = A_LoopSystem:AddTimer(GS_LEASE_INTERVAL, Lua.Bind(self.HandleRenewLease, self, msg.account_id))
end

function GameLeaseManager:ReleaseLease(account_id)
	local info = self._lease_map[account_id]
	if info == nil then
		return
	end
	if info.session ~= nil then
		local param = {}
		param.account_id = account_id
		info.session:SendMsg(___all_struct[-1970485469], param)
	end
	self._lease_map[account_id] = nil
end

function GameLeaseManager:HandleRenewLease(account_id)
	local info = self._lease_map[account_id]
	if info == nil then
		return
	end
	if info.session == nil then
		A_GameAccountManager:HandleLeaseTimeout(account_id)
		self._lease_map[account_id] = nil
		return
	end
	info.timer = nil
	local begin_time = os.time()
	local param = {}
	param.account_id = account_id
	local error, result = ALittle.IMsgCommon.InvokeRPC(-1057357327, info.session, param)
	info = self._lease_map[account_id]
	if info == nil then
		return
	end
	if info.timer ~= nil then
		return
	end
	if error ~= nil or os.time() - begin_time >= 5 then
		A_GameAccountManager:HandleLeaseTimeout(account_id)
		self._lease_map[account_id] = nil
		return
	end
	info.timer = A_LoopSystem:AddTimer(GS_LEASE_INTERVAL, Lua.Bind(self.HandleRenewLease, self, account_id))
end
GameLeaseManager.HandleRenewLease = Lua.CoWrap(GameLeaseManager.HandleRenewLease)

g_GameLeaseManager = GameLeaseManager()
function HandleNNewLease(client, msg)
	g_GameLeaseManager:NewLease(client, msg)
end

RegMsgCallback(370639724, HandleNNewLease)
function HandleQEmpty(client, msg)
local ___COROUTINE = coroutine.running()
	return {}
end

RegMsgRpcCallback(-1627449907, HandleQEmpty, 726375194)
