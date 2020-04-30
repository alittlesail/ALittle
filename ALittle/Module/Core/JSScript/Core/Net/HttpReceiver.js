{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IHttpReceiver = JavaScript.Class(undefined, {
}, "ALittle.IHttpReceiver");

let __all_callback = {};
ALittle.RegHttpCallback = function(method, callback) {
	if (__all_callback[method] !== undefined) {
		ALittle.Error("RegHttpCallback消息回调函数注册失败，名字为" + method + "已存在");
		return;
	}
	__all_callback[method] = callback;
}

ALittle.FindHttpCallback = function(method) {
	return __all_callback[method];
}

let __all_download_callback = {};
ALittle.RegHttpDownloadCallback = function(method, callback) {
	if (__all_download_callback[method] !== undefined) {
		ALittle.Error("RegHttpDownloadCallback消息回调函数注册失败，名字为" + method + "已存在");
		return;
	}
	__all_download_callback[method] = callback;
}

ALittle.FindHttpDownloadCallback = function(method) {
	return __all_download_callback[method];
}

}