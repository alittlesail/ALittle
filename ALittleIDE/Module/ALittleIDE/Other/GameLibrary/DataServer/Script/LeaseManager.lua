-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DataServer == nil then _G.DataServer = {} end
local DataServer = DataServer
local Lua = Lua
local ALittle = ALittle
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
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(-1307158553, "DataServer.GS2DATA_NGameServerInfo", {
name = "DataServer.GS2DATA_NGameServerInfo", ns_name = "DataServer", rl_name = "GS2DATA_NGameServerInfo", hash_code = -1307158553,
name_list = {"client_ip","client_port"},
type_list = {"string","int"},
option_map = {}
})
ALittle.RegStruct(-1076468151, "DataServer.LeaseGameServerInfo", {
name = "DataServer.LeaseGameServerInfo", ns_name = "DataServer", rl_name = "LeaseGameServerInfo", hash_code = -1076468151,
name_list = {"client_ip","client_port","count","session"},
type_list = {"string","int","int","ALittle.MsgSessionTemplate<ALittle.MsgSessionNative,carp.CarpMessageWriteFactory>"},
option_map = {}
})
ALittle.RegStruct(-1057357327, "DataServer.GS2DATA_QRenewLease", {
name = "DataServer.GS2DATA_QRenewLease", ns_name = "DataServer", rl_name = "GS2DATA_QRenewLease", hash_code = -1057357327,
name_list = {"account_id"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(-714377901, "DataServer.LeaseInfo", {
name = "DataServer.LeaseInfo", ns_name = "DataServer", rl_name = "LeaseInfo", hash_code = -714377901,
name_list = {"account_id","confirm","timer","gs_route_num"},
type_list = {"int","bool","int","int"},
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
ALittle.RegStruct(-36908822, "ALittle.SessionDisconnectEvent", {
name = "ALittle.SessionDisconnectEvent", ns_name = "ALittle", rl_name = "SessionDisconnectEvent", hash_code = -36908822,
name_list = {"target","connect_key","route_type","route_num","session"},
type_list = {"ALittle.EventDispatcher","int","int","int","ALittle.MsgSessionTemplate<ALittle.MsgSessionNative,carp.CarpMessageWriteFactory>"},
option_map = {}
})

DataServer.DATA_LEASE_INTERVAL = 30 * 1000
DataServer.LeaseManager = Lua.Class(nil, "DataServer.LeaseManager")

function DataServer.LeaseManager:Ctor()
	___rawset(self, "_lease_map", {})
	___rawset(self, "_lease_count", 0)
	___rawset(self, "_info_map", {})
	___rawset(self, "_lease_start", true)
end

function DataServer.LeaseManager:Setup()
	A_SessionSystem:AddEventListener(___all_struct[-36908822], self, self.HandleAnySessionDisconnected)
	self._update_route = ALittle.GatewayUpdateRoute(DataServer.g_ConnectServerYunIp, DataServer.g_ConnectServerWanIp, DataServer.g_ConnectServerPort, "", "", 0, self._lease_count)
	A_LoopSystem:AddTimer(DataServer.DATA_LEASE_INTERVAL, Lua.Bind(self.LeaseStart, self))
end

function DataServer.LeaseManager:LeaseStart()
	self._lease_start = true
end

function DataServer.LeaseManager:Shutdown()
	for account_id, info in ___pairs(self._lease_map) do
		if info.timer ~= nil then
			A_LoopSystem:RemoveTimer(info.timer)
		end
	end
	self._lease_map = {}
	self._info_map = {}
end

function DataServer.LeaseManager:HandleAnySessionDisconnected(event)
	if event.route_type ~= 7 then
		return
	end
	self._info_map[event.route_num] = nil
end

function DataServer.LeaseManager:HandleGameServerInfo(session, msg)
	if session.route_type ~= 7 then
		return
	end
	local info = {}
	info.session = session
	info.client_ip = msg.client_ip
	info.client_port = msg.client_port
	info.count = 0
	for account_id, lease_info in ___pairs(self._lease_map) do
		if lease_info.gs_route_num == session.route_num then
			info.count = info.count + 1
		end
	end
	self._info_map[session.route_num] = info
end

function DataServer.LeaseManager:GetGameServerInfo(gs_route_num)
	return self._info_map[gs_route_num]
end

function DataServer.LeaseManager:SelectGameServer()
	local target_info = nil
	for route_num, info in ___pairs(self._info_map) do
		if target_info == nil or target_info.count > info.count then
			target_info = info
		end
	end
	return target_info
end

function DataServer.LeaseManager:CheckLease(account_id, gs_route_num)
	local info = self._lease_map[account_id]
	if info == nil then
		return false
	end
	return info.gs_route_num == gs_route_num
end

function DataServer.LeaseManager:GetLease(account_id)
	if not self._lease_start then
		return nil
	end
	local info = self._lease_map[account_id]
	if info ~= nil then
		return info
	end
	local target = self:SelectGameServer()
	if target == nil then
		return nil
	end
	target.count = target.count + 1
	info = {}
	info.account_id = account_id
	info.gs_route_num = target.session.route_num
	info.timer = A_LoopSystem:AddTimer(DataServer.DATA_LEASE_INTERVAL, Lua.Bind(self.HandleLeaseTimeout, self, info.gs_route_num, account_id))
	self._lease_map[account_id] = info
	self._lease_count = self._lease_count + 1
	local param = {}
	param.account_id = account_id
	target.session:SendMsg(___all_struct[370639724], param)
	self._update_route:UpdateRouteWeight(self._lease_count)
	return info
end

function DataServer.LeaseManager:HandleLeaseRenew(session, msg)
	local info = self._lease_map[msg.account_id]
	if info == nil then
		info = {}
		info.account_id = msg.account_id
		info.gs_route_num = session.route_num
		info.confirm = true
		self._lease_map[msg.account_id] = info
		info.timer = A_LoopSystem:AddTimer(DataServer.DATA_LEASE_INTERVAL, Lua.Bind(self.HandleLeaseTimeout, self, info.gs_route_num, info.account_id))
		return nil
	end
	if info.gs_route_num ~= session.route_num then
		return "续约失败"
	end
	info.confirm = true
	if info.timer ~= nil then
		A_LoopSystem:RemoveTimer(info.timer)
	end
	info.timer = A_LoopSystem:AddTimer(DataServer.DATA_LEASE_INTERVAL, Lua.Bind(self.HandleLeaseTimeout, self, info.gs_route_num, info.account_id))
	return nil
end

function DataServer.LeaseManager:HandleReleaseLease(session, msg)
	local info = self._lease_map[msg.account_id]
	if info == nil then
		return
	end
	if info.gs_route_num ~= session.route_num then
		return
	end
	if info.timer ~= nil then
		A_LoopSystem:RemoveTimer(info.timer)
	end
	local gs_info = self._info_map[session.route_num]
	if gs_info ~= nil then
		gs_info.count = gs_info.count - 1
	end
	self._lease_map[msg.account_id] = nil
end

function DataServer.LeaseManager:HandleLeaseTimeout(route_num, account_id)
	local info = self._info_map[route_num]
	if info ~= nil then
		info.count = info.count - 1
	end
	self._lease_map[account_id] = nil
end

DataServer.g_LeaseManager = DataServer.LeaseManager()
function DataServer.HandleNGameServerInfo(client, msg)
	DataServer.g_LeaseManager:HandleGameServerInfo(client, msg)
end

ALittle.RegMsgCallback(-1307158553, DataServer.HandleNGameServerInfo)
function DataServer.HandleQLeaseRenew(client, msg)
	local ___COROUTINE = coroutine.running()
	local error = DataServer.g_LeaseManager:HandleLeaseRenew(client, msg)
	Lua.Assert(error == nil, error)
	return {}
end

ALittle.RegMsgRpcCallback(-1057357327, DataServer.HandleQLeaseRenew, -276606114)
function DataServer.HandleNLeaseRelease(client, msg)
	DataServer.g_LeaseManager:HandleReleaseLease(client, msg)
end

ALittle.RegMsgCallback(-1970485469, DataServer.HandleNLeaseRelease)
end