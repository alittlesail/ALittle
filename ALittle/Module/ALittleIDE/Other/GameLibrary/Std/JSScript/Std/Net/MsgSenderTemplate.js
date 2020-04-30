{
if (typeof ALittle === "undefined") window.ALittle = {};


let __MsgSenderMap = new Map();
if (ALittle.IMsgCommonTemplate === undefined) throw new Error(" extends class:ALittle.IMsgCommonTemplate is undefined");
ALittle.MsgSenderTemplate = JavaScript.Class(ALittle.IMsgCommonTemplate, {
	Ctor : function(heartbeat, check_heartbeat, loop_system, callback) {
		this._interface = ALittle.NewObject(this.__class.__element[0]);
		this._write_factory = ALittle.NewObject(this.__class.__element[1]);
		this._loop_system = loop_system;
		this._heartbeat = heartbeat;
		this._heartbeat_loop = undefined;
		this._check_heartbeat = undefined;
		if (this._heartbeat !== undefined) {
			this._check_heartbeat = check_heartbeat;
		}
		this._last_recv_time = 0;
		this._callback = callback;
	},
	Connect : function(ip, port) {
		return new Promise((function(___COROUTINE, ___) {
			if (ip === undefined) {
				ip = "";
			}
			if (port === undefined) {
				port = 0;
			}
			if (___COROUTINE === undefined) {
				___COROUTINE("当前不是协程"); return;
			}
			this._co = ___COROUTINE;
			__MsgSenderMap.set(this._interface.GetID(), this);
			this._ip = ip;
			this._port = port;
			this._interface.Connect(ip, port);
			return;
		}).bind(this));
	},
	HandleConnectSucceed : function() {
		this._last_recv_time = 0;
		this.SendHeartbeat();
		this.StartHeartbeat();
		let [result, reason] = ALittle.Coroutine.Resume(this._co, undefined);
		if (result !== true) {
			ALittle.Error(reason);
		}
	},
	HandleDisconnect : function() {
		this.StopHeartbeat();
		__MsgSenderMap.delete(this._interface.GetID());
		this.ClearRPC("连接断开了");
		if (this._callback !== undefined) {
			this._callback();
		}
	},
	HandleConnectFailed : function(error) {
		__MsgSenderMap.delete(this._interface.GetID());
		if (error === undefined) {
			error = this._ip + ":" + this._port + "连接失败";
		}
		let [result, reason] = ALittle.Coroutine.Resume(this._co, error);
		if (result !== true) {
			ALittle.Error(reason);
		}
	},
	Close : function(reason) {
		this.StopHeartbeat();
		this._interface.Close();
		if (reason === undefined) {
			reason = "主动关闭连接";
		}
		this.ClearRPC(reason);
		__MsgSenderMap.delete(this._interface.GetID());
	},
	SendHeartbeat : function(max_ms) {
		if (this._interface.IsConnected() === false) {
			return;
		}
		this._write_factory.ResetOffset();
		this._write_factory.SetID(0);
		this._write_factory.SetRpcID(0);
		this._interface.SendFactory(this._write_factory);
		if (this._check_heartbeat) {
			let send_time = ALittle.Time_GetCurTime();
			let default_delta = this._heartbeat / 2;
			let delta_time = max_ms;
			if (delta_time === undefined) {
				delta_time = default_delta;
			}
			if (delta_time > default_delta) {
				delta_time = default_delta;
			}
			this._loop_system.AddTimer(ALittle.Math_Floor(delta_time) * 1000, this.CheckHeartbeat.bind(this, send_time, ALittle.Math_Floor(delta_time)));
		}
	},
	CheckHeartbeat : function(send_time, delta_time) {
		let invoke_time = ALittle.Time_GetCurTime();
		let interval_time = invoke_time - send_time;
		if (interval_time > delta_time + 2) {
			return;
		}
		if (this._last_recv_time > 0 && send_time - this._last_recv_time > delta_time) {
			if (this._interface.IsConnected() === false) {
				return;
			}
			this.Close("心跳检测失败，主动断开连接");
			if (this._callback !== undefined) {
				this._callback();
			}
		}
	},
	StartHeartbeat : function() {
		if (this._heartbeat === undefined) {
			return;
		}
		if (this._heartbeat <= 0) {
			return;
		}
		if (this._heartbeat_loop !== undefined) {
			return;
		}
		this._heartbeat_loop = this._loop_system.AddTimer(1, this.SendHeartbeat.bind(this, undefined), -1, this._heartbeat * 1000);
	},
	StopHeartbeat : function() {
		if (this._heartbeat_loop === undefined) {
			return;
		}
		this._last_recv_time = 0;
		this._loop_system.RemoveTimer(this._heartbeat_loop);
		this._heartbeat_loop = undefined;
	},
}, "ALittle.MsgSenderTemplate");

ALittle.__ALITTLEAPI_ConnectSucceed = function(id) {
	let client = __MsgSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleConnectSucceed();
}

ALittle.__ALITTLEAPI_Disconnect = function(id) {
	let client = __MsgSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleDisconnect();
}

ALittle.__ALITTLEAPI_ConnectFailed = function(id) {
	let client = __MsgSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleConnectFailed(undefined);
}

ALittle.__ALITTLEAPI_Message = function(id, msg_id, rpc_id, factory) {
	let client = __MsgSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleMessage(msg_id, rpc_id, factory);
}

}