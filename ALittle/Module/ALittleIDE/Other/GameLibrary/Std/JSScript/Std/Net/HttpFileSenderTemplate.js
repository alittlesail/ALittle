{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.IHttpFileSenderNative = JavaScript.Class(undefined, {
	GetID : function() {
		return 0;
	},
	SetURL : function(url, file_path, download, start_size) {
	},
	Start : function() {
	},
	Stop : function() {
	},
	GetPath : function() {
		return "";
	},
}, "ALittle.IHttpFileSenderNative");

let __HttpFileSenderMap = new Map();
if (ALittle.IHttpFileSender === undefined) throw new Error(" extends class:ALittle.IHttpFileSender is undefined");
ALittle.HttpFileSenderTemplate = JavaScript.Class(ALittle.IHttpFileSender, {
	Ctor : function(ip, port, file_path, start_size, callback) {
		this._interface = ALittle.NewObject(this.__class.__element[0]);
		this._ip = ip;
		this._port = port;
		if (this._port === undefined) {
			this._port = 80;
		}
		this._file_path = file_path;
		this._start_size = start_size;
		this._callback = callback;
		this._cur_size = 0;
		this._total_size = 0;
	},
	SendDownloadRPC : function(thread, method, content) {
		this._thread = thread;
		__HttpFileSenderMap.set(this._interface.GetID(), this);
		if (this._start_size === undefined) {
			this._start_size = 0;
		}
		let url = "http://" + this._ip + ":" + this._port + "/" + method;
		this._interface.SetURL(this.HttpUrlAppendParamMap(url, content), this._file_path, true, this._start_size);
		this._interface.Start();
	},
	SendUploadRPC : function(thread, method, content) {
		this._thread = thread;
		__HttpFileSenderMap.set(this._interface.GetID(), this);
		if (this._start_size === undefined) {
			this._start_size = 0;
		}
		let url = "http://" + this._ip + ":" + this._port + "/" + method;
		this._interface.SetURL(this.HttpUrlAppendParamMap(url, content), this._file_path, false, this._start_size);
		this._interface.Start();
	},
	Stop : function() {
		this._interface.Stop();
	},
	GetTotalSize : function() {
		return this._total_size;
	},
	GetCurSize : function() {
		return this._cur_size;
	},
	HandleSucceed : function() {
		__HttpFileSenderMap.delete(this._interface.GetID());
		let [result, reason] = ALittle.Coroutine.Resume(this._thread, undefined, this);
		if (result !== true) {
			ALittle.Error(reason);
		}
	},
	HandleFailed : function(reason) {
		__HttpFileSenderMap.delete(this._interface.GetID());
		let [result, error] = ALittle.Coroutine.Resume(this._thread, reason, this);
		if (result !== true) {
			ALittle.Error(error);
		}
	},
	HandleProcess : function(cur_size, total_size) {
		this._cur_size = cur_size;
		this._total_size = total_size;
		if (this._callback !== undefined) {
			this._callback(this._interface);
		}
	},
	HttpUrlAppendParamMap : function(url, param) {
		let list = [];
		let count = 0;
		let ___OBJECT_1 = param;
		for (let key in ___OBJECT_1) {
			let value = ___OBJECT_1[key];
			if (value === undefined) continue;
			++ count;
			list[count - 1] = key + "=" + ALittle.String_ToString(value);
		}
		if (ALittle.String_Find(url, "?") === undefined) {
			url = url + "?";
		} else {
			url = url + "&";
		}
		return url + ALittle.String_Join(list, "&");
	},
}, "ALittle.HttpFileSenderTemplate");

ALittle.__ALITTLEAPI_HttpFileSucceed = function(id) {
	let client = __HttpFileSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleSucceed();
}

ALittle.__ALITTLEAPI_HttpFileFailed = function(id, reason) {
	let client = __HttpFileSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleFailed(reason);
}

ALittle.__ALITTLEAPI_HttpFileProcess = function(id, cur_size, total_size) {
	let client = __HttpFileSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleProcess(cur_size, total_size);
}

}