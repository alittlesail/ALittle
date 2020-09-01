{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IHttpFileSender = JavaScript.Class(undefined, {
	HandleSucceed : function() {
	},
	HandleProcess : function(cur_size, total_size) {
	},
	HandleFailed : function(reason) {
	},
	Stop : function() {
	},
	GetFilePath : function() {
		return undefined;
	},
	GetTotalSize : function() {
		return 0;
	},
	GetCurSize : function() {
		return 0;
	},
	SendDownloadRPC : function(thread, method, content, array_buffer) {
		throw new Error("not impl");
	},
	SendUploadRPC : function(thread, method, content, array_buffer) {
		throw new Error("not impl");
	},
	InvokeDownload : function(method, client, content, array_buffer) {
		return new Promise(function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE("当前不是协程"); return;
			}
			client.SendDownloadRPC(___COROUTINE, method, content, array_buffer);
			return;
		});
	},
	InvokeUpload : function(method, client, content, array_buffer) {
		return new Promise(function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE("当前不是协程"); return;
			}
			client.SendUploadRPC(___COROUTINE, method, content, array_buffer);
			return;
		});
	},
}, "ALittle.IHttpFileSender");

}