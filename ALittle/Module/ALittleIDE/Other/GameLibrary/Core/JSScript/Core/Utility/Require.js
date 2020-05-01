{
if (typeof ALittle === "undefined") window.ALittle = {};


let JSRequire = function(base_path, url, thread) {
	if (typeof(require) !== "undefined") {
		require(url);
		thread(undefined);
		return;
	}
	let script = document.createElement("script");
	script.type = "text/javascript";
	script.async = "async";
	let error = thread.bind("load failed:" + url);
	script.onabort = error;
	script.onerror = error;
	script.ontimeout = error;
	script.onload = thread.bind(undefined);
	script.src = url + ".js";
	document.body.appendChild(script);
}

ALittle.Require = function(base_path, url) {
	return new Promise(function(___COROUTINE, ___) {
		JSRequire(base_path, url, ___COROUTINE);
		return;
	});
}

}