{


__ALITTLEAPI_Std_Init = function(base_path) {
	return new Promise(async function(___COROUTINE, ___) {
		await Require(base_path + "Std/Reflect/ReflectCmd");
		await Require(base_path + "Std/Reflect/ReflectCsv");
		await Require(base_path + "Std/Reflect/ReflectMessage");
		await Require(base_path + "Std/Loop/LoopObject");
		await Require(base_path + "Std/Loop/ILoopSystem");
		await Require(base_path + "Std/Loop/LoopFunction");
		await Require(base_path + "Std/Loop/LoopGroup");
		await Require(base_path + "Std/Loop/LoopList");
		await Require(base_path + "Std/Loop/LoopTimer");
		await Require(base_path + "Std/Utility/Bit");
		await Require(base_path + "Std/Utility/WeakRef");
		await Require(base_path + "Std/Utility/IHeapTimer");
		await Require(base_path + "Std/Utility/ISchedule");
		await Require(base_path + "Std/Utility/CsvConfig");
		await Require(base_path + "Std/Utility/EventDispatcher");
		await Require(base_path + "Std/Utility/SafeIDCreator");
		await Require(base_path + "Std/Utility/String");
		await Require(base_path + "Std/Utility/File");
		await Require(base_path + "Std/Utility/JsonConfig");
		await Require(base_path + "Std/Net/HttpFileReceiverTemplate");
		await Require(base_path + "Std/Net/HttpFileSenderTemplate");
		await Require(base_path + "Std/Net/HttpReceiverTemplate");
		await Require(base_path + "Std/Net/HttpSenderTemplate");
		await Require(base_path + "Std/Net/MsgCommonTemplate");
		await Require(base_path + "Std/Net/MsgReceiverTemplate");
		await Require(base_path + "Std/Net/MsgSenderTemplate");
		await Require(base_path + "Std/Net/MsgSessionTemplate");
		{
			await Require(base_path + "Adapter/JavaScript/Timer");
			await Require(base_path + "Adapter/JavaScript/FileSystem");
			await Require(base_path + "Adapter/JavaScript/JHttpFileInterface");
			await Require(base_path + "Adapter/JavaScript/JHttpInterface");
			await Require(base_path + "Adapter/JavaScript/JMessageFactory");
			await Require(base_path + "Adapter/JavaScript/JMsgInterface");
			await Require(base_path + "Adapter/JavaScript/JSchedule");
			await Require(base_path + "Adapter/JavaScript/JCsvFile");
			await Require(base_path + "../../JSNative/md5.min");
			await Require(base_path + "../../JSNative/jweakmap");
			await Require(base_path + "../../JSNative/bit");
		}
		await Require(base_path + "Std/Loop/LoopSystem");
		await Require(base_path + "Std/Utility/Schedule");
		___COROUTINE();
	});
}

}