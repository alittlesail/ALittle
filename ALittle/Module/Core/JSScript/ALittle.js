{


window.Require = function(url) {
	if (typeof(require) !== "undefined") {
		require(url);
		return;
	}
	let this_path = "";
	let last_script = document.scripts[document.scripts.length - 1];
	if (last_script !== undefined) {
		this_path = last_script.src.substring(0, last_script.src.lastIndexOf("/") + 1);
	}
	console.log(this_path, url);
	let script = document.createElement("script");
	script.type = "text/javascript";
	script.src = this_path + url + ".js";
	document.body.appendChild(script);
}

Require("Core/JavaScript/JavaScriptClass");
Require("Core/JavaScript/JavaScriptException");
Require("Core/Reflect/ReflectRegister");
Require("Core/Reflect/ReflectDefine");
Require("Core/Utility/Log");
Require("Core/Utility/List");
Require("Core/Utility/Map");
Require("Core/Utility/Math");
Require("Core/Utility/String");
Require("Core/Utility/Time");
Require("Core/Utility/Coroutine");
Require("Core/Net/HttpFileReceiver");
Require("Core/Net/HttpFileSender");
Require("Core/Net/HttpReceiver");
Require("Core/Net/HttpSender");
Require("Core/Net/MsgCommon");
}