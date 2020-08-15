{


let JSRequire = function(base_path, url, thread) {
	if (typeof(require) !== "undefined") {
		require("../../../" + base_path + url);
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
	script.src = base_path + url + ".js";
	document.body.appendChild(script);
}

window.Require = function(base_path, url) {
	return new Promise(function(___COROUTINE, ___) {
		JSRequire(base_path, url, ___COROUTINE);
		return;
	});
}

window.RequireFromPaths = function(base_path, rel_path, file_list) {
	return new Promise(async function(___COROUTINE, ___) {
		let ___OBJECT_1 = file_list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let path = ___OBJECT_1[index - 1];
			if (path === undefined) break;
			path = path.substring(0, path.length - 8);
			await Require(base_path, rel_path + path);
		}
		___COROUTINE();
	});
}

window.RequireCore = function(base_path) {
	return new Promise(async function(___COROUTINE, ___) {
		await Require(base_path, "Core/JavaScript/JavaScriptClass");
		await Require(base_path, "Core/JavaScript/JavaScriptException");
		await Require(base_path, "Core/Reflect/ReflectRegister");
		await Require(base_path, "Core/Reflect/ReflectDefine");
		await Require(base_path, "Core/Utility/Log");
		await Require(base_path, "Core/Utility/List");
		await Require(base_path, "Core/Utility/Map");
		await Require(base_path, "Core/Utility/Math");
		await Require(base_path, "Core/Utility/String");
		await Require(base_path, "Core/Utility/Time");
		await Require(base_path, "Core/Utility/Coroutine");
		await Require(base_path, "Core/Net/HttpFileReceiver");
		await Require(base_path, "Core/Net/HttpFileSender");
		await Require(base_path, "Core/Net/HttpReceiver");
		await Require(base_path, "Core/Net/HttpSender");
		await Require(base_path, "Core/Net/MsgCommon");
		___COROUTINE();
	});
}

}