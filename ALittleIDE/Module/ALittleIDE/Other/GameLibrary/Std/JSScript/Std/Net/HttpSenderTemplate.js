{
if (typeof ALittle === "undefined") window.ALittle = {};


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
if (ALittle.IHttpSender === undefined) throw new Error(" extends class:ALittle.IHttpSender is undefined");
ALittle.HttpSenderTemplate = JavaScript.Class(ALittle.IHttpSender, {
	Ctor : function(ip, port) {
		this._interface = ALittle.NewObject(this.__class.__element[0]);
		this._ip = ip;
		this._port = port;
		if (this._port === undefined) {
			if (location.protocol === "https:") {
				this._port = 443;
			} else {
				this._port = 80;
			}
		}
	},
	SendRPC : function(thread, method, content) {
		this._thread = thread;
		__HttpSenderMap.set(this._interface.GetID(), this);
		let url = this._ip + ":" + this._port + "/" + method;
		if (ALittle.String_Find(this._ip, "http://") !== 1 && ALittle.String_Find(this._ip, "https://") !== 1) {
			if (location.hostname === this._ip) {
				url = location.protocol + "//" + url;
			} else {
				if (this._port === 443) {
					url = "https://" + url;
				} else {
					url = "http://" + url;
				}
			}
		}
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

ALittle.__ALITTLEAPI_HttpClientSucceed = function(id) {
	let client = __HttpSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleSucceed();
}

ALittle.__ALITTLEAPI_HttpClientFailed = function(id, reason) {
	let client = __HttpSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleFailed(reason);
}

}