{
let ___lastscript = document.scripts[document.scripts.length - 1]
let ___thispath = "";
if (___lastscript !== undefined) ___thispath = ___lastscript.src.substring(0, ___lastscript.src.lastIndexOf("/") + 1);


window.Require = function(this_path, url) {
	if (typeof(require) !== "undefined") {
		require(url);
		return;
	}
	let script = document.createElement("script");
	script.type = "text/javascript";
	script.src = this_path + url + ".js";
	document.body.appendChild(script);
}

Require(___thispath, "Core/JavaScript/JavaScriptClass");
Require(___thispath, "Core/JavaScript/JavaScriptException");
Require(___thispath, "Core/Reflect/ReflectRegister");
Require(___thispath, "Core/Reflect/ReflectDefine");
Require(___thispath, "Core/Utility/Log");
Require(___thispath, "Core/Utility/List");
Require(___thispath, "Core/Utility/Map");
Require(___thispath, "Core/Utility/Math");
Require(___thispath, "Core/Utility/String");
Require(___thispath, "Core/Utility/Time");
Require(___thispath, "Core/Utility/Coroutine");
Require(___thispath, "Core/Net/HttpFileReceiver");
Require(___thispath, "Core/Net/HttpFileSender");
Require(___thispath, "Core/Net/HttpReceiver");
Require(___thispath, "Core/Net/HttpSender");
Require(___thispath, "Core/Net/MsgCommon");
}