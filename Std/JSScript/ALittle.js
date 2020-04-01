{


__ALITTLEAPI_Std_Init = async function(base_path, callback) {
	await Require(base_path + "Std/Reflect/ReflectCmd");
	await Require(base_path + "Std/Reflect/ReflectCsv");
	await Require(base_path + "Std/Reflect/ReflectMessage");
	await Require(base_path + "Std/Utility/IHeapTimer");
	{
		await Require(base_path + "Adapter/JavaScript/Timer");
	}
	await Require(base_path + "Std/Loop/LoopObject");
	await Require(base_path + "Std/Loop/ILoopSystem");
	await Require(base_path + "Std/Loop/LoopSystem");
	await Require(base_path + "Std/Loop/LoopFunction");
	await Require(base_path + "Std/Loop/LoopGroup");
	await Require(base_path + "Std/Loop/LoopList");
	await Require(base_path + "Std/Loop/LoopTimer");
	await Require(base_path + "Std/Utility/CsvConfig");
	await Require(base_path + "Std/Utility/EventDispatcher");
	await Require(base_path + "Std/Utility/SafeIDCreator");
	await Require(base_path + "Std/Utility/String");
	await Require(base_path + "Std/Utility/File");
	await Require(base_path + "Std/Utility/ConfigSystem");
	await Require(base_path + "Std/Net/HttpFileReceiverTemplate");
	await Require(base_path + "Std/Net/HttpFileSenderTemplate");
	await Require(base_path + "Std/Net/HttpReceiverTemplate");
	await Require(base_path + "Std/Net/HttpSenderTemplate");
	await Require(base_path + "Std/Net/MsgCommonTemplate");
	await Require(base_path + "Std/Net/MsgReceiverTemplate");
	await Require(base_path + "Std/Net/MsgSenderTemplate");
	await Require(base_path + "Std/Net/MsgSessionTemplate");
	if (callback !== undefined) {
		callback();
	}
}

}