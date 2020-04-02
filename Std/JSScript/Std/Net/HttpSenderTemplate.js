{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.IHttpSenderNative = JavaScript.Class(undefined, {
	GetID : function() {
		return 0;
	},
	SetURL : function(url, content) {
	},
	Start : function() {
	},
	Stop : function() {
	},
	GetResponse : function() {
		return undefined;
	},
}, "ALittle.IHttpSenderNative");

let __HttpSenderMap = new Map();
ALittle.FindHttpSender = function(id) {
	return __HttpSenderMap.get(id);
}

if (ALittle.IHttpSender === undefined) throw new Error(" extends class:ALittle.IHttpSender is undefined");
ALittle.HttpSenderTemplate = JavaScript.Class(ALittle.IHttpSender, {
	Ctor : function(ip, port) {
		this._interface = ALittle.NewObject(this.__class.__element[0]);
		this._ip = ip;
		this._port = port;
	},
	SendRPC : function(thread, method, content) {
		this._thread = thread;
		__HttpSenderMap.set(this._interface.GetID(), this);
		let url = "http://" + this._ip + ":" + this._port + "/" + method;
		if (content === undefined) {
			this._interface.SetURL(url, undefined);
		} else {
			this._interface.SetURL(url, ALittle.String_JsonEncode(content));
		}
		this._interface.Start();
	},
	Stop : function() {
		this._interface.Stop();
	},
	HandleSucceed : function() {
		__HttpSenderMap.delete(this._interface.GetID());
		let [error, param] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, this._interface.GetResponse()); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
		if (error !== undefined) {
			let [result, reason] = ALittle.Coroutine.Resume(this._thread, error, undefined);
			if (result !== true) {
				ALittle.Error(reason);
			}
			return;
		}
		if (param["error"] !== undefined) {
			let [result, reason] = ALittle.Coroutine.Resume(this._thread, param["error"], undefined);
			if (result !== true) {
				ALittle.Error(reason);
			}
			return;
		}
		let [result, reason] = ALittle.Coroutine.Resume(this._thread, undefined, param);
		if (result !== true) {
			ALittle.Error(reason);
		}
	},
	HandleFailed : function(reason) {
		__HttpSenderMap.delete(this._interface.GetID());
		let [result, error] = ALittle.Coroutine.Resume(this._thread, reason, undefined);
		if (result !== true) {
			ALittle.Error(error);
		}
	},
}, "ALittle.HttpSenderTemplate");

}