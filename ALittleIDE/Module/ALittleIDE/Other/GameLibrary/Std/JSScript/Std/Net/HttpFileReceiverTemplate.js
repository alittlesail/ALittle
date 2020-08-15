{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IHttpFileReceiverNative = JavaScript.Class(undefined, {
	Close : function(http_id) {
	},
	SendString : function(http_id, content) {
	},
	StartReceiveFile : function(http_id, file_path, start_size) {
	},
}, "ALittle.IHttpFileReceiverNative");

if (ALittle.IHttpFileReceiver === undefined) throw new Error(" extends class:ALittle.IHttpFileReceiver is undefined");
ALittle.HttpFileReceiverTemplate = JavaScript.Class(ALittle.IHttpFileReceiver, {
	Ctor : function(http_id, thread) {
		this._http_id = http_id;
		this._thread = thread;
		this._received = false;
		this._interface = ALittle.NewObject(this.__class.__element[0]);
	},
	StartReceiveFile : function(file_path, start_size) {
		return new Promise((function(___COROUTINE, ___) {
			if (this._received) {
				___COROUTINE("StartReceiveFile已经被调用过"); return;
			}
			this._received = true;
			this._interface.StartReceiveFile(this._http_id, file_path, start_size);
			return;
		}).bind(this));
	},
	HandleReceiveResult : function(reason) {
		let [result, error] = ALittle.Coroutine.Resume(this._thread, reason);
		if (!result) {
			ALittle.Error(error);
		}
	},
	get received() {
		return this._received;
	},
	SendString : function(content) {
		this._interface.SendString(this._http_id, content);
	},
	Clsoe : function() {
		this._interface.Close(this._http_id);
	},
}, "ALittle.HttpFileReceiverTemplate");

}