-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1970485469, "DataServer.GS2DATA_NReleaseLease", {
name = "DataServer.GS2DATA_NReleaseLease", ns_name = "DataServer", rl_name = "GS2DATA_NReleaseLease", hash_code = -1970485469,
name_list = {"account_id"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(1860871079, "ALittle.GameLeaseInfo", {
name = "ALittle.GameLeaseInfo", ns_name = "ALittle", rl_name = "GameLeaseInfo", hash_code = 1860871079,
name_list = {"account_id","session","timer"},
type_list = {"int","ALittle.MsgSessionTemplate<ALittle.MsgSessionNative,carp.CarpMessageWriteFactory>","int"},
option_map = {}
})
ALittle.RegStruct(-1627449907, "ALittle.DATA2GS_QEmpty", {
name = "ALittle.DATA2GS_QEmpty", ns_name = "ALittle", rl_name = "DATA2GS_QEmpty", hash_code = -1627449907,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1057357327, "DataServer.GS2DATA_QRenewLease", {
name = "DataServer.GS2DATA_QRenewLease", ns_name = "DataServer", rl_name = "GS2DATA_QRenewLease", hash_code = -1057357327,
name_list = {"account_id"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(726375194, "ALittle.GS2DATA_AEmpty", {
name = "ALittle.GS2DATA_AEmpty", ns_name = "ALittle", rl_name = "GS2DATA_AEmpty", hash_code = 726375194,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(370639724, "ALittle.DATA2GS_NNewLease", {
name = "ALittle.DATA2GS_NNewLease", ns_name = "ALittle", rl_name = "DATA2GS_NNewLease", hash_code = 370639724,
name_list = {"account_id"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(-276606114, "DataServer.DATA2GS_ARenewLease", {
name = "DataServer.DATA2GS_ARenewLease", ns_name = "DataServer", rl_name = "DATA2GS_ARenewLease", hash_code = -276606114,
name_list = {},
type_list = {},
option_map = {}
})

ALittle.GS_LEASE_INTERVAL = 20 * 1000
ALittle.GameLeaseManager = Lua.Class(nil, "ALittle.GameLeaseManager")

function ALittle.GameLeaseManager:Ctor()
	___rawset(self, "_lease_map", {})
end

function ALittle.GameLeaseManager:Setup()
end

function ALittle.GameLeaseManager:Shutdown()
	for account_id, info in ___pairs(self._lease_map) do
		if info.timer ~= nil then
			A_LoopSystem:RemoveTimer(info.timer)
		end
	end
	self._lease_map = {}
end

function ALittle.GameLeaseManager:GetLease(account_id)
	return self._lease_map[account_id]
end

function ALittle.GameLeaseManager:NewLease(session, msg)
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
	info.timer = A_LoopSystem:AddTimer(ALittle.GS_LEASE_INTERVAL, Lua.Bind(self.HandleRenewLease, self, msg.account_id))
end

function ALittle.GameLeaseManager:ReleaseLease(account_id)
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

function ALittle.GameLeaseManager:HandleRenewLease(account_id)
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
	info.timer = A_LoopSystem:AddTimer(ALittle.GS_LEASE_INTERVAL, Lua.Bind(self.HandleRenewLease, self, account_id))
end
ALittle.GameLeaseManager.HandleRenewLease = Lua.CoWrap(ALittle.GameLeaseManager.HandleRenewLease)

ALittle.g_GameLeaseManager = ALittle.GameLeaseManager()
function ALittle.HandleNNewLease(client, msg)
	ALittle.g_GameLeaseManager:NewLease(client, msg)
end

ALittle.RegMsgCallback(370639724, ALittle.HandleNNewLease)
function ALittle.HandleQEmpty(client, msg)
	local ___COROUTINE = coroutine.running()
	return {}
end

ALittle.RegMsgRpcCallback(-1627449907, ALittle.HandleQEmpty, 726375194)
end