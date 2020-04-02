{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.IHttpFileSender = JavaScript.Class(undefined, {
	GetContent : function() {
		return undefined;
	},
	HandleSucceed : function() {
	},
	HandleProcess : function() {
	},
	HandleFailed : function(reason) {
	},
	SendDownloadRPC : function(thread, method, content) {
		throw new Error("not impl");
	},
	SendUploadRPC : function(thread, method, content) {
		throw new Error("not impl");
	},
	InvokeDownload : function(method, client, content) {
		return new Promise(function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE("当前不是协程"); return;
			}
			client.SendDownloadRPC(___COROUTINE, method, content);
			return;
			___COROUTINE();
		});
	},
	InvokeUpload : function(method, client, content) {
		return new Promise(function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE(["当前不是协程", undefined]); return;
			}
			client.SendUploadRPC(___COROUTINE, method, content);
			return;
			___COROUTINE();
		});
	},
}, "ALittle.IHttpFileSender");

}