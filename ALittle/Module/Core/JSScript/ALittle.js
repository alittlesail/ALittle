{


window.RequireCore = function(base_path) {
	return new Promise(async function(___COROUTINE, ___) {
		await ALittle.Require(base_path, "Core/JavaScript/JavaScriptClass");
		await ALittle.Require(base_path, "Core/JavaScript/JavaScriptException");
		await ALittle.Require(base_path, "Core/Reflect/ReflectRegister");
		await ALittle.Require(base_path, "Core/Reflect/ReflectDefine");
		await ALittle.Require(base_path, "Core/Utility/Log");
		await ALittle.Require(base_path, "Core/Utility/List");
		await ALittle.Require(base_path, "Core/Utility/Map");
		await ALittle.Require(base_path, "Core/Utility/Math");
		await ALittle.Require(base_path, "Core/Utility/String");
		await ALittle.Require(base_path, "Core/Utility/Time");
		await ALittle.Require(base_path, "Core/Utility/Coroutine");
		await ALittle.Require(base_path, "Core/Net/HttpFileReceiver");
		await ALittle.Require(base_path, "Core/Net/HttpFileSender");
		await ALittle.Require(base_path, "Core/Net/HttpReceiver");
		await ALittle.Require(base_path, "Core/Net/HttpSender");
		await ALittle.Require(base_path, "Core/Net/MsgCommon");
		___COROUTINE();
	});
}

}