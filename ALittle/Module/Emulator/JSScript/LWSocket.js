{
if (typeof Emulator === "undefined") window.Emulator = {};
let ___all_struct = ALittle.GetAllStruct();


if (Lua.ISocket === undefined) throw new Error(" extends class:Lua.ISocket is undefined");
Emulator.LWSocket = JavaScript.Class(Lua.ISocket, {
	ReadMessage : function() {
		return new Promise((async function(___COROUTINE, ___) {
			let msg_type = 0;
			let msg_size = 0;
			let server_id = 0;
			let server_type = 0;
			let protobuf_msg = undefined;
			let error = undefined;
			[error, msg_size] = await this.ReadUint16();
			if (error !== undefined) {
				___COROUTINE([error, undefined]); return;
			}
			msg_size = msg_size - (8);
			[error, msg_type] = await this.ReadUint16();
			if (error !== undefined) {
				___COROUTINE([error, undefined]); return;
			}
			[error, server_id] = await this.ReadUint16();
			if (error !== undefined) {
				___COROUTINE([error, undefined]); return;
			}
			[error, server_type] = await this.ReadUint16();
			if (error !== undefined) {
				___COROUTINE([error, undefined]); return;
			}
			if (msg_size <= 0) {
				let full_name = Emulator.g_LWProtobuf.MsgId2MsgFullName(msg_type);
				if (full_name === undefined) {
					___COROUTINE(["unknow msg type:" + msg_type, undefined]); return;
				}
				___COROUTINE([undefined, A_LuaSocketSchedule.CreateMessage(full_name)]); return;
			} else {
				let full_name = Emulator.g_LWProtobuf.MsgId2MsgFullName(msg_type);
				if (full_name === undefined) {
					full_name = "";
				}
				[error, protobuf_msg] = await this.ReadProtobuf(full_name, msg_size);
				if (error !== undefined) {
					___COROUTINE([error, undefined]); return;
				}
				if (protobuf_msg === undefined) {
					___COROUTINE(["unknow msg type:" + msg_type, undefined]); return;
				}
				___COROUTINE([undefined, protobuf_msg]); return;
			}
		}).bind(this));
	},
	WriteMessage : function(full_name, protobuf_msg, protobuf_binary, protobuf_size) {
		let msg_type = Emulator.g_LWProtobuf.MsgFullName2MsgId(full_name);
		if (msg_type === undefined) {
			return "MsgFullName2MsgId failed, full_name:" + full_name;
		}
		this.WriteUint16(protobuf_size + 8);
		this.WriteUint16(msg_type);
		this.WriteUint16(1);
		this.WriteUint16(1);
		this.WriteBinary(protobuf_binary, protobuf_size);
		if (full_name !== "ProtoMsg.MSG_CLIENT_KEEP_LIVE_RSP") {
			Emulator.g_GCenter.AddLogMessage(protobuf_msg);
		}
		return undefined;
	},
	HandleMessage : function(msg) {
		let descriptor = lua.protobuf.message_getdescriptor(msg);
		let name = lua.protobuf.messagedescriptor_name(descriptor);
		if (name === "MSG_CLIENT_KEEP_LIVE_REQ") {
			this.SendStruct(___all_struct.get(754290029), "ProtoMsg.MSG_CLIENT_KEEP_LIVE_RSP", {});
			return;
		}
		Emulator.g_GCenter.AddLogMessage(msg);
	},
}, "Emulator.LWSocket");

}