{


window.RequireStd = function(base_path) {
	return new Promise(async function(___COROUTINE, ___) {
		await Require(base_path, "Cmd/ReflectCmd");
		await Require(base_path, "Config/ReflectCsv");
		await Require(base_path, "Net/ReflectMessage");
		await Require(base_path, "Loop/LoopObject");
		await Require(base_path, "Loop/ILoopSystem");
		await Require(base_path, "Loop/LoopFrame");
		await Require(base_path, "Loop/LoopFunction");
		await Require(base_path, "Loop/LoopGroup");
		await Require(base_path, "Loop/LoopList");
		await Require(base_path, "Loop/LoopTimer");
		await Require(base_path, "Config/CsvConfig");
		await Require(base_path, "Config/JsonConfig");
		await Require(base_path, "Bit/Bit");
		await Require(base_path, "WeakRef/WeakRef");
		await Require(base_path, "Loop/IHeapTimer");
		await Require(base_path, "Schedule/ISchedule");
		await Require(base_path, "Utility/EventDispatcher");
		await Require(base_path, "Utility/SafeIDCreator");
		await Require(base_path, "String/String");
		await Require(base_path, "File/File");
		await Require(base_path, "Net/HttpFileReceiverTemplate");
		await Require(base_path, "Net/HttpFileSenderTemplate");
		await Require(base_path, "Net/HttpReceiverTemplate");
		await Require(base_path, "Net/HttpSenderTemplate");
		await Require(base_path, "Net/MsgCommonTemplate");
		await Require(base_path, "Net/MsgReceiverTemplate");
		await Require(base_path, "Net/MsgSenderTemplate");
		await Require(base_path, "Net/MsgSessionTemplate");
		await Require(base_path, "Loop/JavaScript/JHeapTimer");
		await Require(base_path, "File/JavaScript/JFileSystem");
		await Require(base_path, "Net/JavaScript/JHttpFileInterface");
		await Require(base_path, "Net/JavaScript/JHttpFileWxInterface");
		await Require(base_path, "Net/JavaScript/JHttpInterface");
		await Require(base_path, "Net/JavaScript/JHttpWxInterface");
		await Require(base_path, "Net/JavaScript/JMessageFactory");
		await Require(base_path, "Net/JavaScript/JMsgInterface");
		await Require(base_path, "Schedule/JavaScript/JSchedule");
		await Require(base_path, "Config/JavaScript/JCsvFile");
		await Require(base_path, "../JSNative/md5.min");
		await Require(base_path, "../JSNative/native");
		await Require(base_path, "Loop/LoopSystem");
		await Require(base_path, "Schedule/Schedule");
		___COROUTINE();
	});
}

}