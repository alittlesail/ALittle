{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Lua.ISocket === undefined) throw new Error(" extends class:Lua.ISocket is undefined");
Emulator.LWSocket = JavaScript.Class(Lua.ISocket, {
	ReadMessage : async function() {
		let msg_type = 0;
		let msg_size = 0;
		let server_id = 0;
		let server_type = 0;
		let protobuf_msg = undefined;
		let error = undefined;
		while (this.IsConnected()) {
			[error, msg_type] = await this.ReadUint16();
			if (error !== undefined) {
				break;
			}
			[error, msg_size] = await this.ReadUint16();
			if (error !== undefined) {
				break;
			}
			[error, server_id] = await this.ReadUint16();
			if (error !== undefined) {
				break;
			}
			[error, server_type] = await this.ReadUint16();
			if (error !== undefined) {
				break;
			}
			let name = this.MsgId2ProtobufName(msg_type);
			if (name === undefined) {
				name = "";
			}
			if (msg_size > 0) {
				let binary_value = undefined;
				[error, binary_value] = await this.ReadProtobuf(name, msg_size);
				if (error !== undefined) {
					break;
				}
			} else {
				protobuf_msg = {};
			}
			this.HandleMessage(msg_type, name, protobuf_msg);
		}
	},
	WriteMessage : function(name, msg) {
		let msg_type = this.ProtobufName2MsgId(name);
		if (msg_type === undefined) {
			return;
		}
		let size = 0;
		let buffer = undefined;
		this.WriteUint16(msg_type);
		this.WriteUint16(size);
		this.WriteUint16(1);
		this.WriteUint16(1);
		this.WriteBinary(buffer, size);
	},
	MsgId2ProtobufName : function(id) {
		return undefined;
	},
	ProtobufName2MsgId : function(name) {
		return undefined;
	},
	HandleMessage : function(id, name, msg) {
	},
}, "Emulator.LWSocket");

}