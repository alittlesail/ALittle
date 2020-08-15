{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IHttpReceiverNative = JavaScript.Class(undefined, {
	Close : function(http_id) {
	},
	SendString : function(http_id, content) {
	},
	SendFile : function(http_id, file_path, start_size) {
	},
}, "ALittle.IHttpReceiverNative");

if (ALittle.IHttpReceiver === undefined) throw new Error(" extends class:ALittle.IHttpReceiver is undefined");
ALittle.HttpReceiverTemplate = JavaScript.Class(ALittle.IHttpReceiver, {
	Ctor : function(http_id) {
		this._http_id = http_id;
		this._interface = ALittle.NewObject(this.__class.__element[0]);
	},
	Close : function() {
		this._interface.Close(this._http_id);
	},
	SendString : function(content) {
		this._interface.SendString(this._http_id, content);
	},
	SendFile : function(file_path, start_size) {
		this._interface.SendFile(this._http_id, file_path, start_size);
	},
}, "ALittle.HttpReceiverTemplate");

}