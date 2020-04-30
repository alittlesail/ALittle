{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IHttpFileReceiver = JavaScript.Class(undefined, {
	StartReceiveFile : function(file_path, start_size) {
		return new Promise((function(___COROUTINE, ___) {
			___COROUTINE("not impl"); return;
		}).bind(this));
	},
}, "ALittle.IHttpFileReceiver");

let __all_callback = {};
ALittle.RegHttpFileCallback = function(method, callback) {
	if (__all_callback[method] !== undefined) {
		ALittle.Error("RegHttpFileCallback消息回调函数注册失败，名字为" + method + "已存在");
		return;
	}
	__all_callback[method] = callback;
}

ALittle.FindHttpFileReceiverCallback = function(method) {
	return __all_callback[method];
}

}