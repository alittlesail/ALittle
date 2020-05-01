{


window.RequireStd = function(base_path) {
	return new Promise(async function(___COROUTINE, ___) {
		await ALittle.Require(base_path, "Std/Reflect/ReflectCmd");
		await ALittle.Require(base_path, "Std/Reflect/ReflectCsv");
		await ALittle.Require(base_path, "Std/Reflect/ReflectMessage");
		await ALittle.Require(base_path, "Std/Loop/LoopObject");
		await ALittle.Require(base_path, "Std/Loop/ILoopSystem");
		await ALittle.Require(base_path, "Std/Loop/LoopFrame");
		await ALittle.Require(base_path, "Std/Loop/LoopFunction");
		await ALittle.Require(base_path, "Std/Loop/LoopGroup");
		await ALittle.Require(base_path, "Std/Loop/LoopList");
		await ALittle.Require(base_path, "Std/Loop/LoopTimer");
		await ALittle.Require(base_path, "Std/Utility/Bit");
		await ALittle.Require(base_path, "Std/Utility/WeakRef");
		await ALittle.Require(base_path, "Std/Utility/IHeapTimer");
		await ALittle.Require(base_path, "Std/Utility/ISchedule");
		await ALittle.Require(base_path, "Std/Utility/CsvConfig");
		await ALittle.Require(base_path, "Std/Utility/EventDispatcher");
		await ALittle.Require(base_path, "Std/Utility/SafeIDCreator");
		await ALittle.Require(base_path, "Std/Utility/String");
		await ALittle.Require(base_path, "Std/Utility/File");
		await ALittle.Require(base_path, "Std/Utility/JsonConfig");
		await ALittle.Require(base_path, "Std/Net/HttpFileReceiverTemplate");
		await ALittle.Require(base_path, "Std/Net/HttpFileSenderTemplate");
		await ALittle.Require(base_path, "Std/Net/HttpReceiverTemplate");
		await ALittle.Require(base_path, "Std/Net/HttpSenderTemplate");
		await ALittle.Require(base_path, "Std/Net/MsgCommonTemplate");
		await ALittle.Require(base_path, "Std/Net/MsgReceiverTemplate");
		await ALittle.Require(base_path, "Std/Net/MsgSenderTemplate");
		await ALittle.Require(base_path, "Std/Net/MsgSessionTemplate");
		await ALittle.Require(base_path, "Adapter/JavaScript/Timer");
		await ALittle.Require(base_path, "Adapter/JavaScript/FileSystem");
		await ALittle.Require(base_path, "Adapter/JavaScript/JHttpFileInterface");
		await ALittle.Require(base_path, "Adapter/JavaScript/JHttpInterface");
		await ALittle.Require(base_path, "Adapter/JavaScript/JMessageFactory");
		await ALittle.Require(base_path, "Adapter/JavaScript/JMsgInterface");
		await ALittle.Require(base_path, "Adapter/JavaScript/JSchedule");
		await ALittle.Require(base_path, "Adapter/JavaScript/JCsvFile");
		await ALittle.Require(base_path, "../JSNative/md5.min");
		await ALittle.Require(base_path, "../JSNative/jweakmap");
		await ALittle.Require(base_path, "../JSNative/bit");
		await ALittle.Require(base_path, "Std/Loop/LoopSystem");
		await ALittle.Require(base_path, "Std/Utility/Schedule");
		___COROUTINE();
	});
}

}