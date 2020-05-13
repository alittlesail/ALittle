-- ALittle Generate Lua And Do Not Edit This Line!
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1468681065, "alittle.NetAddress", {
name = "alittle.NetAddress", ns_name = "alittle", rl_name = "NetAddress", hash_code = 1468681065,
name_list = {"domain_name","ip","port"},
type_list = {"string","string","int"},
option_map = {}
})
ALittle.RegStruct(-737748066, "alittle.MsgRegServerInfo", {
name = "alittle.MsgRegServerInfo", ns_name = "alittle", rl_name = "MsgRegServerInfo", hash_code = -737748066,
name_list = {"server_type","server_id","kingdom_id","net_address"},
type_list = {"int","int","int","alittle.NetAddress"},
option_map = {}
})
ALittle.RegStruct(-2134502702, "alittle.MSG_SERVER_REGIST_REQ", {
name = "alittle.MSG_SERVER_REGIST_REQ", ns_name = "alittle", rl_name = "MSG_SERVER_REGIST_REQ", hash_code = -2134502702,
name_list = {"info"},
type_list = {"alittle.MsgRegServerInfo"},
option_map = {}
})
ALittle.RegStruct(1647167193, "alittle.MSG_LS2CL_LOGIN_RSP", {
name = "alittle.MSG_LS2CL_LOGIN_RSP", ns_name = "alittle", rl_name = "MSG_LS2CL_LOGIN_RSP", hash_code = 1647167193,
name_list = {"player_id","login_session","net_addr","ret_code"},
type_list = {"long","string","alittle.NetAddress","int"},
option_map = {}
})
ALittle.RegStruct(1475448950, "alittle.ClientVersion", {
name = "alittle.ClientVersion", ns_name = "alittle", rl_name = "ClientVersion", hash_code = 1475448950,
name_list = {"major","minor","patch"},
type_list = {"int","int","int"},
option_map = {}
})
ALittle.RegStruct(1677596493, "alittle.MSG_CL2GS_LOGIN_REQ", {
name = "alittle.MSG_CL2GS_LOGIN_REQ", ns_name = "alittle", rl_name = "MSG_CL2GS_LOGIN_REQ", hash_code = 1677596493,
name_list = {"player_id","login_session","account","client_version","protocol_version"},
type_list = {"long","string","string","alittle.ClientVersion","int"},
option_map = {}
})
ALittle.RegStruct(1100514745, "alittle.MSG_GS2CL_LOGIN_RSP", {
name = "alittle.MSG_GS2CL_LOGIN_RSP", ns_name = "alittle", rl_name = "MSG_GS2CL_LOGIN_RSP", hash_code = 1100514745,
name_list = {"ret_code","flag","player_id","kingdom_id"},
type_list = {"int","int","long","int"},
option_map = {}
})
ALittle.RegStruct(-2095874882, "alittle.MSG_CLIENT_KEEP_LIVE_REQ", {
name = "alittle.MSG_CLIENT_KEEP_LIVE_REQ", ns_name = "alittle", rl_name = "MSG_CLIENT_KEEP_LIVE_REQ", hash_code = -2095874882,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1578310667, "alittle.MSG_CLIENT_KEEP_LIVE_RSP", {
name = "alittle.MSG_CLIENT_KEEP_LIVE_RSP", ns_name = "alittle", rl_name = "MSG_CLIENT_KEEP_LIVE_RSP", hash_code = -1578310667,
name_list = {},
type_list = {},
option_map = {}
})

local g_id_map_name = {}
local g_name_map_id = {}
function __PLUGIN_ProtoRefresh()
	local descriptor = A_LuaSocketSchedule:GetEnumDescriptor("EMsgTypes")
	if descriptor == nil then
		return
	end
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
			g_id_map_name[field_number] = full_name
			g_name_map_id[full_name] = field_number
		end
		i = i+(1)
	end
end

function __PLUGIN_StartLogin(ip, port, login_msg)
local ___COROUTINE = coroutine.running()
	local error = nil
	local ls_socket = Emulator.PluginSocket()
	do
		error = ls_socket:Connect(ip, port)
		if error ~= nil then
			return error, nil
		end
	end
	do
		local register_req = {}
		register_req.info = {}
		register_req.info.server_type = 1
		error = ls_socket:SendStruct(___all_struct[-2134502702], "ProtoMsg.MSG_SERVER_REGIST_REQ", register_req)
		if error ~= nil then
			return error, nil
		end
	end
	do
		ls_socket:SendMessage(login_msg)
	end
	local gs_socket = nil
	local ls_rsp = nil
	do
		error, ls_rsp = ls_socket:ReadStruct(___all_struct[1647167193])
		if error ~= nil then
			return error, nil
		end
		if ls_rsp.ret_code ~= nil and ls_rsp.ret_code ~= 0 then
			return "login server login failed, ret code:" .. ls_rsp.ret_code, nil
		end
		gs_socket = Emulator.PluginSocket()
		error = gs_socket:Connect(ls_rsp.net_addr.ip, ls_rsp.net_addr.port)
		if error ~= nil then
			return error, nil
		end
	end
	ls_socket:Close()
	do
		local register_req = {}
		register_req.info = {}
		register_req.info.server_type = 1
		error = gs_socket:SendStruct(___all_struct[-2134502702], "ProtoMsg.MSG_SERVER_REGIST_REQ", register_req)
		if error ~= nil then
			return error, nil
		end
	end
	do
		local login_req = {}
		login_req.player_id = ls_rsp.player_id
		login_req.account = ALittle.String_ToString(ls_rsp.player_id)
		login_req.login_session = ls_rsp.login_session
		error = gs_socket:SendStruct(___all_struct[1677596493], "ProtoMsg.MSG_CL2GS_LOGIN_REQ", login_req)
		if error ~= nil then
			return error, nil
		end
	end
	local gs_rsp = nil
	do
		error, gs_rsp = gs_socket:ReadStruct(___all_struct[1100514745])
		if error ~= nil then
			return error, nil
		end
		if gs_rsp.ret_code ~= nil and gs_rsp.ret_code ~= 0 then
			return "game server login failed, ret code:" .. gs_rsp.ret_code, nil
		end
	end
	return nil, gs_socket
end

function __SOCKET_ReadMessage(socket)
local ___COROUTINE = coroutine.running()
	local msg_type = 0
	local msg_size = 0
	local server_id = 0
	local server_type = 0
	local protobuf_msg = nil
	local error = nil
	error, msg_size = socket:ReadUint16()
	if error ~= nil then
		return error, nil
	end
	msg_size = msg_size - (8)
	error, msg_type = socket:ReadUint16()
	if error ~= nil then
		return error, nil
	end
	error, server_id = socket:ReadUint16()
	if error ~= nil then
		return error, nil
	end
	error, server_type = socket:ReadUint16()
	if error ~= nil then
		return error, nil
	end
	local full_name = g_id_map_name[msg_type]
	if msg_size <= 0 then
		if full_name == nil then
			return "unknow msg type:" .. msg_type, nil
		end
		return nil, A_LuaSocketSchedule:CreateMessage(full_name)
	else
		return socket:ReadProtobuf(full_name, msg_size)
	end
end

function __SOCKET_WriteMessage(socket, full_name, protobuf_msg, protobuf_binary, protobuf_size)
	local msg_type = g_name_map_id[full_name]
	if msg_type == nil then
		return "MsgFullName2MsgId failed, full_name:" .. full_name
	end
	socket:WriteUint16(protobuf_size + 8)
	socket:WriteUint16(msg_type)
	socket:WriteUint16(1)
	socket:WriteUint16(1)
	socket:WriteBinary(protobuf_binary, protobuf_size)
	return nil
end

function __SOCKET_HandleMessage(socket, msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	local name = protobuf.messagedescriptor_name(descriptor)
	if name == "MSG_CLIENT_KEEP_LIVE_REQ" then
		socket:SendStruct(___all_struct[-1578310667], "ProtoMsg.MSG_CLIENT_KEEP_LIVE_RSP", {})
		return
	end
end

