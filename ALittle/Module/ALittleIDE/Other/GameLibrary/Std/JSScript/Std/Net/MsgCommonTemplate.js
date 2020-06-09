{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(-930447138, "ALittle.Thread", {
name : "ALittle.Thread", ns_name : "ALittle", rl_name : "Thread", hash_code : -930447138,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(361433949, "ALittle.MsgRPCInfo", {
name : "ALittle.MsgRPCInfo", ns_name : "ALittle", rl_name : "MsgRPCInfo", hash_code : 361433949,
name_list : ["rpc_id","thread"],
type_list : ["int","ALittle.Thread"],
option_map : {}
})

ALittle.IMsgCommonNative = JavaScript.Class(undefined, {
	SetID : function(id) {
	},
	GetID : function() {
		return 0;
	},
	Connect : function(ip, port) {
	},
	IsConnected : function() {
		return false;
	},
	SendFactory : function(factory) {
	},
	Close : function() {
	},
}, "ALittle.IMsgCommonNative");

if (ALittle.IMsgCommon === undefined) throw new Error(" extends class:ALittle.IMsgCommon is undefined");
ALittle.IMsgCommonTemplate = JavaScript.Class(ALittle.IMsgCommon, {
	Ctor : function() {
		this._last_recv_time = 0;
		this._id_creator = ALittle.NewObject(ALittle.SafeIDCreator);
		this._id_map_rpc = new Map();
	},
	GetID : function() {
		return this._interface.GetID();
	},
	Connect : function(ip, port) {
		return new Promise((function(___COROUTINE, ___) {
			___COROUTINE("not impl"); return;
		}).bind(this));
	},
	IsConnected : function() {
		return this._interface.IsConnected();
	},
	MessageRead : function(factory, msg_id) {
		let invoke = ALittle.CreateProtocolInvokeInfo(msg_id);
		let [object, size] = ALittle.PS_ReadMessageForReceive(factory, invoke, undefined, factory.GetDataSize());
		return object;
	},
	MessageWrite : function(msg_id, msg_body) {
		let invoke = ALittle.CreateProtocolInvokeInfo(msg_id);
		this._write_factory.ResetOffset();
		ALittle.PS_WriteMessageForSend(this._write_factory, invoke, undefined, msg_body);
		this._write_factory.SetID(msg_id);
	},
	HandleMessage : function(id, rpc_id, factory) {
		if (id === 0) {
			this._last_recv_time = ALittle.Time_GetCurTime();
			return;
		}
		if (rpc_id === 0) {
			let callback = ALittle.FindMsgCallback(id);
			if (callback === undefined) {
				let name = "unknow";
				let rflt = ALittle.FindStructById(id);
				if (rflt !== undefined) {
					name = rflt.name;
				}
				ALittle.Log("MsgSystem.HandleMessage can't find callback by id:" + id + ", name:" + name);
				return;
			}
			let msg = this.MessageRead(factory, id);
			if (msg === undefined) {
				let name = "unknow";
				let rflt = ALittle.FindStructById(id);
				if (rflt !== undefined) {
					name = rflt.name;
				}
				ALittle.Log("MsgSystem.HandleMessage MessageRead failed by id:" + id + ", name:" + name);
				return;
			}
			callback(this, msg);
			return;
		}
		if (rpc_id > 0) {
			this.HandleRPCRequest(id, rpc_id, factory);
			return;
		}
		rpc_id = -rpc_id;
		this._id_creator.ReleaseID(rpc_id);
		let info = this._id_map_rpc.get(rpc_id);
		if (info === undefined) {
			ALittle.Log("MsgSystem.HandleMessage can't find rpc info by id:" + id);
			return;
		}
		this._id_map_rpc.delete(rpc_id);
		if (id === 1) {
			let [result, reason] = ALittle.Coroutine.Resume(info.thread, factory.ReadString(), undefined);
			if (result !== true) {
				ALittle.Error(reason);
			}
			return;
		}
		let msg = this.MessageRead(factory, id);
		if (msg === undefined) {
			let [result, reason] = ALittle.Coroutine.Resume(info.thread, "MsgSystem.HandleMessage MessageRead failed by id:" + id, undefined);
			if (result !== true) {
				ALittle.Error(reason);
			}
			ALittle.Log("MsgSystem.HandleMessage MessageRead failed by id:" + id);
			return;
		}
		let [result, reason] = ALittle.Coroutine.Resume(info.thread, undefined, msg);
		if (result !== true) {
			ALittle.Error(reason);
		}
	},
	SendMsg : function(T, msg) {
		let info = T;
		this.Send(info.hash_code, msg, 0);
	},
	Send : function(msg_id, msg_body, rpc_id) {
		if (!this.IsConnected()) {
			return;
		}
		this._write_factory.SetRpcID(rpc_id);
		this.MessageWrite(msg_id, msg_body);
		this._interface.SendFactory(this._write_factory);
	},
	SendRpcError : function(rpc_id, reason) {
		if (!this.IsConnected()) {
			return;
		}
		this._write_factory.ResetOffset();
		this._write_factory.SetID(1);
		this._write_factory.SetRpcID(-rpc_id);
		this._write_factory.WriteString(reason);
		this._interface.SendFactory(this._write_factory);
	},
	SendRPC : function(thread, msg_id, msg_body) {
		let rpc_id = this._id_creator.CreateID();
		this._write_factory.SetRpcID(rpc_id);
		this.MessageWrite(msg_id, msg_body);
		this._interface.SendFactory(this._write_factory);
		let info = {};
		info.thread = thread;
		info.rpc_id = rpc_id;
		this._id_map_rpc.set(rpc_id, info);
	},
	HandleRPCRequest : async function(id, rpc_id, factory) {
		let [callback, return_id] = ALittle.FindMsgRpcCallback(id);
		if (callback === undefined) {
			this.SendRpcError(rpc_id, "没有注册消息RPC回调函数");
			ALittle.Log("MsgSystem.HandleMessage can't find callback by id:" + id);
			return;
		}
		let msg = this.MessageRead(factory, id);
		if (msg === undefined) {
			this.SendRpcError(rpc_id, "MsgSystem.HandleMessage MessageRead failed by id:" + id);
			ALittle.Log("MsgSystem.HandleMessage MessageRead failed by id:" + id);
			return;
		}
		let [error, return_body] = await (async function() { try { let ___VALUE = await callback.call(this, msg); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
		if (error !== undefined) {
			this.SendRpcError(rpc_id, error);
			ALittle.Log("MsgSystem.HandleMessage callback invoke failed! by id:" + id + ", reason:" + error);
			return;
		}
		if (return_body === undefined) {
			this.SendRpcError(rpc_id, "MsgSystem.HandleMessage callback have not return! by id:" + id);
			ALittle.Log("MsgSystem.HandleMessage callback have not return! by id:" + id);
			return;
		}
		this.Send(return_id, return_body, -rpc_id);
	},
	ClearRPC : function(reason) {
		let tmp = new Map();
		for (let [rpc_id, info] of this._id_map_rpc) {
			if (info === undefined) continue;
			this._id_creator.ReleaseID(rpc_id);
			tmp.set(rpc_id, info);
		}
		this._id_map_rpc = new Map();
		for (let [rpc_id, info] of tmp) {
			if (info === undefined) continue;
			let [result, error] = ALittle.Coroutine.Resume(info.thread, reason, undefined);
			if (result !== true) {
				ALittle.Error(error);
			}
		}
	},
	Close : function(reason) {
		if (reason === undefined) {
			reason = "主动关闭连接";
		}
		this.ClearRPC(reason);
		this._interface.Close();
	},
}, "ALittle.IMsgCommonTemplate");

}