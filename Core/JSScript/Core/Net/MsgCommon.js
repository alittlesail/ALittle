{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.IMsgCommon = JavaScript.Class(undefined, {
	IsConnected : function() {
		return false;
	},
	HandleConnectSucceed : function() {
	},
	HandleDisconnect : function() {
	},
	HandleConnectFailed : function(reason) {
	},
	HandleMessage : function(id, rpc_id, factory) {
	},
	Send : function(msg_id, msg_body, rpc_id) {
		throw new Error("not impl");
	},
	SendRPC : function(thread, msg_id, msg_body) {
	},
	Invoke : function(msg_id, client, msg_body) {
		client.Send(msg_id, msg_body, 0);
	},
	InvokeRPC : function(msg_id, client, msg_body) {
		return new Promise(async function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE(["当前不是协程", undefined]); return;
			}
			if (!client.IsConnected()) {
				___COROUTINE(["连接还没成功", undefined]); return;
			}
			client.SendRPC(___COROUTINE, msg_id, msg_body);
			return;
			___COROUTINE();
		});
	},
}, "ALittle.IMsgCommon");

let __all_callback = new Map();
ALittle.RegMsgCallback = function(msg_id, callback) {
	if (__all_callback.get(msg_id) !== undefined) {
		ALittle.Error("RegMsgCallback消息回调函数注册失败，名字为" + msg_id + "已存在");
		return;
	}
	__all_callback.set(msg_id, callback);
}

ALittle.FindMsgCallback = function(msg_id) {
	return __all_callback.get(msg_id);
}

let __all_rpc_callback = new Map();
let __all_rpc_return_id = new Map();
ALittle.RegMsgRpcCallback = function(msg_id, callback, return_id) {
	if (__all_rpc_callback.get(msg_id) !== undefined) {
		ALittle.Error("RegMsgRpcCallback消息回调函数注册失败，名字为" + msg_id + "已存在");
		return;
	}
	__all_rpc_callback.set(msg_id, callback);
	__all_rpc_return_id.set(msg_id, return_id);
}

ALittle.FindMsgRpcCallback = function(msg_id) {
	return [__all_rpc_callback.get(msg_id), __all_rpc_return_id.get(msg_id)];
}

}