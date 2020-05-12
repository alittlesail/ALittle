-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1048801311, "Emulator.NetAddress", {
name = "Emulator.NetAddress", ns_name = "Emulator", rl_name = "NetAddress", hash_code = -1048801311,
name_list = {"domain_name","ip","port"},
type_list = {"string","string","int"},
option_map = {}
})
ALittle.RegStruct(1391097920, "Emulator.MsgRegServerInfo", {
name = "Emulator.MsgRegServerInfo", ns_name = "Emulator", rl_name = "MsgRegServerInfo", hash_code = 1391097920,
name_list = {"server_type","server_id","kingdom_id","net_address"},
type_list = {"int","int","int","Emulator.NetAddress"},
option_map = {}
})
ALittle.RegStruct(-1424844312, "Emulator.MSG_SERVER_REGIST_REQ", {
name = "Emulator.MSG_SERVER_REGIST_REQ", ns_name = "Emulator", rl_name = "MSG_SERVER_REGIST_REQ", hash_code = -1424844312,
name_list = {"info"},
type_list = {"Emulator.MsgRegServerInfo"},
option_map = {}
})
ALittle.RegStruct(991647813, "Emulator.MSG_LS2CL_LOGIN_RSP", {
name = "Emulator.MSG_LS2CL_LOGIN_RSP", ns_name = "Emulator", rl_name = "MSG_LS2CL_LOGIN_RSP", hash_code = 991647813,
name_list = {"player_id","login_session","net_addr","ret_code"},
type_list = {"long","string","Emulator.NetAddress","int"},
option_map = {}
})
ALittle.RegStruct(1556610326, "Emulator.ClientVersion", {
name = "Emulator.ClientVersion", ns_name = "Emulator", rl_name = "ClientVersion", hash_code = 1556610326,
name_list = {"major","minor","patch"},
type_list = {"int","int","int"},
option_map = {}
})
ALittle.RegStruct(859426888, "Emulator.MSG_CL2GS_LOGIN_REQ", {
name = "Emulator.MSG_CL2GS_LOGIN_REQ", ns_name = "Emulator", rl_name = "MSG_CL2GS_LOGIN_REQ", hash_code = 859426888,
name_list = {"player_id","login_session","account","client_version","protocol_version"},
type_list = {"long","string","string","Emulator.ClientVersion","int"},
option_map = {}
})
ALittle.RegStruct(1703000291, "Emulator.MSG_GS2CL_LOGIN_RSP", {
name = "Emulator.MSG_GS2CL_LOGIN_RSP", ns_name = "Emulator", rl_name = "MSG_GS2CL_LOGIN_RSP", hash_code = 1703000291,
name_list = {"ret_code","flag","player_id","kingdom_id"},
type_list = {"int","int","long","int"},
option_map = {}
})
ALittle.RegStruct(1133484203, "Emulator.MSG_CLIENT_KEEP_LIVE_REQ", {
name = "Emulator.MSG_CLIENT_KEEP_LIVE_REQ", ns_name = "Emulator", rl_name = "MSG_CLIENT_KEEP_LIVE_REQ", hash_code = 1133484203,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(754290029, "Emulator.MSG_CLIENT_KEEP_LIVE_RSP", {
name = "Emulator.MSG_CLIENT_KEEP_LIVE_RSP", ns_name = "Emulator", rl_name = "MSG_CLIENT_KEEP_LIVE_RSP", hash_code = 754290029,
name_list = {},
type_list = {},
option_map = {}
})

LWLoginStatus = {
	CONNECT_IDLE = 0,
	CONNECT_LS = 1,
	CONNECT_GS = 2,
}

LWProtobuf = Lua.Class(nil, "Emulator.LWProtobuf")

function LWProtobuf:Ctor()
	___rawset(self, "_id_map_name", {})
	___rawset(self, "_name_map_id", {})
	___rawset(self, "_login_status", LWLoginStatus.CONNECT_IDLE)
end

function LWProtobuf:Clear()
	self._id_map_name = {}
	self._name_map_id = {}
end

function LWProtobuf:Refresh()
	self:Clear()
	local enum_descriptor = A_LuaSocketSchedule:GetEnumDescriptor("EMsgTypes")
	if enum_descriptor ~= nil then
		self:AddEnumKeyValue(enum_descriptor)
	end
end

function LWProtobuf:AddEnumKeyValue(descriptor)
	local count = protobuf.enumdescriptor_valuecount(descriptor)
	local i = 0
	while true do
		if not(i < count) then break end
		local enumvalue_descriptor = protobuf.enumdescriptor_value(descriptor, i)
		if enumvalue_descriptor ~= nil then
			local field_name = protobuf.enumvaluedescriptor_name(enumvalue_descriptor)
			local field_number = protobuf.enumvaluedescriptor_number(enumvalue_descriptor)
			local msg_name = ALittle.String_Sub(field_name, 2)
			local full_name = "ProtoMsg." .. msg_name
			self._id_map_name[field_number] = full_name
			self._name_map_id[full_name] = field_number
		end
		i = i+(1)
	end
end

function LWProtobuf:MsgId2MsgFullName(id)
	return self._id_map_name[id]
end

function LWProtobuf:MsgFullName2MsgId(full_name)
	return self._name_map_id[full_name]
end

function LWProtobuf:CloseConnect()
	if self._ls_socket ~= nil then
		self._ls_socket:Close()
		self._ls_socket = nil
	end
	if self._gs_socket ~= nil then
		self._gs_socket:Close()
		self._gs_socket = nil
	end
	self._login_status = LWLoginStatus.CONNECT_IDLE
end

function LWProtobuf:HandleDisconnected(status)
	if self._login_status == status then
		if self._ls_socket ~= nil then
			self._ls_socket:Close()
			self._ls_socket = nil
		end
		if self._gs_socket ~= nil then
			self._gs_socket:Close()
			self._gs_socket = nil
		end
		g_GCenter:HandleSocketDisconnected()
	end
end

function LWProtobuf:StartLogin(ip, port, msg)
local ___COROUTINE = coroutine.running()
	self:CloseConnect()
	local error = nil
	self._login_status = LWLoginStatus.CONNECT_LS
	self._ls_socket = LWSocket(Lua.Bind(self.HandleDisconnected, self, LWLoginStatus.CONNECT_LS))
	do
		error = self._ls_socket:Connect(ip, port)
		if error ~= nil then
			return error
		end
	end
	do
		local register_req = {}
		register_req.info = {}
		register_req.info.server_type = 1
		error = self._ls_socket:SendStruct(___all_struct[-1424844312], "ProtoMsg.MSG_SERVER_REGIST_REQ", register_req)
		if error ~= nil then
			return error
		end
	end
	do
		self._ls_socket:SendMessage(msg)
	end
	local ls_rsp = nil
	do
		error, ls_rsp = self._ls_socket:ReadStruct(___all_struct[991647813])
		if error ~= nil then
			return error
		end
		if ls_rsp.ret_code ~= nil and ls_rsp.ret_code ~= 0 then
			return "login server login failed, ret code:" .. ls_rsp.ret_code
		end
		self._login_status = LWLoginStatus.CONNECT_GS
		self._gs_socket = LWSocket(Lua.Bind(self.HandleDisconnected, self, LWLoginStatus.CONNECT_GS))
		error = self._gs_socket:Connect(ls_rsp.net_addr.ip, ls_rsp.net_addr.port)
		if error ~= nil then
			return error
		end
	end
	self._ls_socket:Close()
	self._ls_socket = nil
	do
		local register_req = {}
		register_req.info = {}
		register_req.info.server_type = 1
		error = self._gs_socket:SendStruct(___all_struct[-1424844312], "ProtoMsg.MSG_SERVER_REGIST_REQ", register_req)
		if error ~= nil then
			return error
		end
	end
	do
		local login_req = {}
		login_req.player_id = ls_rsp.player_id
		login_req.account = ALittle.String_ToString(ls_rsp.player_id)
		login_req.login_session = ls_rsp.login_session
		error = self._gs_socket:SendStruct(___all_struct[859426888], "ProtoMsg.MSG_CL2GS_LOGIN_REQ", login_req)
		if error ~= nil then
			return error
		end
	end
	local gs_rsp = nil
	do
		error, gs_rsp = self._gs_socket:ReadStruct(___all_struct[1703000291])
		if error ~= nil then
			return error
		end
		if gs_rsp.ret_code ~= nil and gs_rsp.ret_code ~= 0 then
			return "game server login failed, ret code:" .. gs_rsp.ret_code
		end
	end
	self._gs_socket:ReceiveMessage()
	return nil
end

function LWProtobuf:SendMessage(msg)
	if self._gs_socket == nil then
		return
	end
	self._gs_socket:SendMessage(msg)
end

g_LWProtobuf = LWProtobuf()
