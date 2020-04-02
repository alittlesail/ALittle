{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.IHttpSender = JavaScript.Class(undefined, {
	HandleSucceed : function() {
	},
	HandleFailed : function(reason) {
	},
	SendRPC : function(thread, method, content) {
		throw new Error("not impl");
	},
	Invoke : function(method, client, content) {
		return new Promise(function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE(["当前不是协程", undefined]); return;
			}
			client.SendRPC(___COROUTINE, method, content);
			return;
			___COROUTINE();
		});
	},
}, "ALittle.IHttpSender");

}