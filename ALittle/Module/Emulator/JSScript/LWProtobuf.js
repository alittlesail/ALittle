{
if (typeof Emulator === "undefined") window.Emulator = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1048801311, "Emulator.NetAddress", {
name : "Emulator.NetAddress", ns_name : "Emulator", rl_name : "NetAddress", hash_code : -1048801311,
name_list : ["domain_name","ip","port"],
type_list : ["string","string","int"],
option_map : {}
})
ALittle.RegStruct(1391097920, "Emulator.MsgRegServerInfo", {
name : "Emulator.MsgRegServerInfo", ns_name : "Emulator", rl_name : "MsgRegServerInfo", hash_code : 1391097920,
name_list : ["server_type","server_id","kingdom_id","net_address"],
type_list : ["int","int","int","Emulator.NetAddress"],
option_map : {}
})
ALittle.RegStruct(-1424844312, "Emulator.MSG_SERVER_REGIST_REQ", {
name : "Emulator.MSG_SERVER_REGIST_REQ", ns_name : "Emulator", rl_name : "MSG_SERVER_REGIST_REQ", hash_code : -1424844312,
name_list : ["info"],
type_list : ["Emulator.MsgRegServerInfo"],
option_map : {}
})
ALittle.RegStruct(991647813, "Emulator.MSG_LS2CL_LOGIN_RSP", {
name : "Emulator.MSG_LS2CL_LOGIN_RSP", ns_name : "Emulator", rl_name : "MSG_LS2CL_LOGIN_RSP", hash_code : 991647813,
name_list : ["player_id","login_session","net_addr","ret_code"],
type_list : ["long","string","Emulator.NetAddress","int"],
option_map : {}
})
ALittle.RegStruct(1556610326, "Emulator.ClientVersion", {
name : "Emulator.ClientVersion", ns_name : "Emulator", rl_name : "ClientVersion", hash_code : 1556610326,
name_list : ["major","minor","patch"],
type_list : ["int","int","int"],
option_map : {}
})
ALittle.RegStruct(859426888, "Emulator.MSG_CL2GS_LOGIN_REQ", {
name : "Emulator.MSG_CL2GS_LOGIN_REQ", ns_name : "Emulator", rl_name : "MSG_CL2GS_LOGIN_REQ", hash_code : 859426888,
name_list : ["player_id","login_session","account","client_version","protocol_version"],
type_list : ["long","string","string","Emulator.ClientVersion","int"],
option_map : {}
})
ALittle.RegStruct(1703000291, "Emulator.MSG_GS2CL_LOGIN_RSP", {
name : "Emulator.MSG_GS2CL_LOGIN_RSP", ns_name : "Emulator", rl_name : "MSG_GS2CL_LOGIN_RSP", hash_code : 1703000291,
name_list : ["ret_code","flag","player_id","kingdom_id"],
type_list : ["int","int","long","int"],
option_map : {}
})
ALittle.RegStruct(1133484203, "Emulator.MSG_CLIENT_KEEP_LIVE_REQ", {
name : "Emulator.MSG_CLIENT_KEEP_LIVE_REQ", ns_name : "Emulator", rl_name : "MSG_CLIENT_KEEP_LIVE_REQ", hash_code : 1133484203,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(754290029, "Emulator.MSG_CLIENT_KEEP_LIVE_RSP", {
name : "Emulator.MSG_CLIENT_KEEP_LIVE_RSP", ns_name : "Emulator", rl_name : "MSG_CLIENT_KEEP_LIVE_RSP", hash_code : 754290029,
name_list : [],
type_list : [],
option_map : {}
})

Emulator.LWLoginStatus = {
	CONNECT_IDLE : 0,
	CONNECT_LS : 1,
	CONNECT_GS : 2,
}

Emulator.LWProtobuf = JavaScript.Class(undefined, {
	Ctor : function() {
		this._id_map_name = new Map();
		this._name_map_id = {};
		this._login_status = Emulator.LWLoginStatus.CONNECT_IDLE;
	},
	Clear : function() {
		this._id_map_name = new Map();
		this._name_map_id = {};
	},
	Refresh : function() {
		this.Clear();
		let enum_descriptor = A_LuaSocketSchedule.GetEnumDescriptor("EMsgTypes");
		if (enum_descriptor !== undefined) {
			this.AddEnumKeyValue(enum_descriptor);
		}
	},
	AddEnumKeyValue : function(descriptor) {
		let count = lua.protobuf.enumdescriptor_valuecount(descriptor);
		for (let i = 0; i < count; i += 1) {
			let enumvalue_descriptor = lua.protobuf.enumdescriptor_value(descriptor, i);
			if (enumvalue_descriptor !== undefined) {
				let field_name = lua.protobuf.enumvaluedescriptor_name(enumvalue_descriptor);
				let field_number = lua.protobuf.enumvaluedescriptor_number(enumvalue_descriptor);
				let msg_name = ALittle.String_Sub(field_name, 2);
				let full_name = "ProtoMsg." + msg_name;
				this._id_map_name.set(field_number, full_name);
				this._name_map_id[full_name] = field_number;
			}
		}
	},
	MsgId2MsgFullName : function(id) {
		return this._id_map_name.get(id);
	},
	MsgFullName2MsgId : function(full_name) {
		return this._name_map_id[full_name];
	},
	CloseConnect : function() {
		if (this._ls_socket !== undefined) {
			this._ls_socket.Close();
			this._ls_socket = undefined;
		}
		if (this._gs_socket !== undefined) {
			this._gs_socket.Close();
			this._gs_socket = undefined;
		}
		this._login_status = Emulator.LWLoginStatus.CONNECT_IDLE;
	},
	HandleDisconnected : function(status) {
		if (this._login_status === status) {
			if (this._ls_socket !== undefined) {
				this._ls_socket.Close();
				this._ls_socket = undefined;
			}
			if (this._gs_socket !== undefined) {
				this._gs_socket.Close();
				this._gs_socket = undefined;
			}
			Emulator.g_GCenter.HandleSocketDisconnected();
		}
	},
	StartLogin : function(ip, port, msg) {
		return new Promise((async function(___COROUTINE, ___) {
			this.CloseConnect();
			let error = undefined;
			this._login_status = Emulator.LWLoginStatus.CONNECT_LS;
			this._ls_socket = ALittle.NewObject(Emulator.LWSocket, this.HandleDisconnected.bind(this, Emulator.LWLoginStatus.CONNECT_LS));
			{
				error = await this._ls_socket.Connect(ip, port);
				if (error !== undefined) {
					___COROUTINE(error); return;
				}
			}
			{
				let register_req = {};
				register_req.info = {};
				register_req.info.server_type = 1;
				error = this._ls_socket.SendStruct(___all_struct.get(-1424844312), "ProtoMsg.MSG_SERVER_REGIST_REQ", register_req);
				if (error !== undefined) {
					___COROUTINE(error); return;
				}
			}
			{
				this._ls_socket.SendMessage(msg);
			}
			let ls_rsp = undefined;
			{
				[error, ls_rsp] = await this._ls_socket.ReadStruct(___all_struct.get(991647813));
				if (error !== undefined) {
					___COROUTINE(error); return;
				}
				if (ls_rsp.ret_code !== undefined && ls_rsp.ret_code !== 0) {
					___COROUTINE("login server login failed, ret code:" + ls_rsp.ret_code); return;
				}
				this._login_status = Emulator.LWLoginStatus.CONNECT_GS;
				this._gs_socket = ALittle.NewObject(Emulator.LWSocket, this.HandleDisconnected.bind(this, Emulator.LWLoginStatus.CONNECT_GS));
				error = await this._gs_socket.Connect(ls_rsp.net_addr.ip, ls_rsp.net_addr.port);
				if (error !== undefined) {
					___COROUTINE(error); return;
				}
			}
			this._ls_socket.Close();
			this._ls_socket = undefined;
			{
				let register_req = {};
				register_req.info = {};
				register_req.info.server_type = 1;
				error = this._gs_socket.SendStruct(___all_struct.get(-1424844312), "ProtoMsg.MSG_SERVER_REGIST_REQ", register_req);
				if (error !== undefined) {
					___COROUTINE(error); return;
				}
			}
			{
				let login_req = {};
				login_req.player_id = ls_rsp.player_id;
				login_req.account = ALittle.String_ToString(ls_rsp.player_id);
				login_req.login_session = ls_rsp.login_session;
				error = this._gs_socket.SendStruct(___all_struct.get(859426888), "ProtoMsg.MSG_CL2GS_LOGIN_REQ", login_req);
				if (error !== undefined) {
					___COROUTINE(error); return;
				}
			}
			let gs_rsp = undefined;
			{
				[error, gs_rsp] = await this._gs_socket.ReadStruct(___all_struct.get(1703000291));
				if (error !== undefined) {
					___COROUTINE(error); return;
				}
				if (gs_rsp.ret_code !== undefined && gs_rsp.ret_code !== 0) {
					___COROUTINE("game server login failed, ret code:" + gs_rsp.ret_code); return;
				}
			}
			this._gs_socket.ReceiveMessage();
			___COROUTINE(undefined); return;
		}).bind(this));
	},
	SendMessage : function(msg) {
		if (this._gs_socket === undefined) {
			return;
		}
		this._gs_socket.SendMessage(msg);
	},
}, "Emulator.LWProtobuf");

Emulator.g_LWProtobuf = ALittle.NewObject(Emulator.LWProtobuf);
}