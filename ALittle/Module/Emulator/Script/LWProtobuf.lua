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
			self._id_map_name[field_number] = field_name
			self._name_map_id[field_name] = field_number
		end
		i = i+(1)
	end
end

function LWProtobuf:MsgId2MsgFullName(id)
	return self._id_map_name[id]
end

function LWProtobuf:MsgFullName2MsgId(full_name)
	local list = ALittle.String_Split(full_name, ".")
	if list[2] == nil then
		return nil
	end
	return self._name_map_id["_" .. list[2]]
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
	self._login_status = LWLoginStatus.CONNECT_LS
	self._ls_socket = LWSocket(Lua.Bind(self.HandleDisconnected, self, LWLoginStatus.CONNECT_LS))
	local error = self._ls_socket:Connect(ip, port)
	if error ~= nil then
		return error
	end
	local register_req = {}
	register_req.info = {}
	register_req.info.server_type = 1
	error = self._ls_socket:SendStruct(___all_struct[-1424844312], "ProtoMsg.MSG_SERVER_REGIST_REQ", register_req)
	if error ~= nil then
		return error
	end
	self._ls_socket:SendMessage(msg)
	local json = protobuf.message_jsonencode(msg)
	ALittle.Log(json)
	error, msg = self._ls_socket:ReadMessage()
	if error ~= nil then
		return error
	end
	json = protobuf.message_jsonencode(msg)
	ALittle.Log(json)
	self._login_status = LWLoginStatus.CONNECT_GS
	return nil
end

g_LWProtobuf = LWProtobuf()
