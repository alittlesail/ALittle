{
let ___lastscript = document.scripts[document.scripts.length - 1]
let ___thispath = "";
if (___lastscript !== undefined) ___thispath = ___lastscript.src.substring(0, ___lastscript.src.lastIndexOf("/") + 1);


Require(___thispath, "Std/Reflect/ReflectCmd");
Require(___thispath, "Std/Reflect/ReflectCsv");
Require(___thispath, "Std/Reflect/ReflectMessage");
Require(___thispath, "Std/Loop/LoopObject");
Require(___thispath, "Std/Loop/ILoopSystem");
Require(___thispath, "Std/Loop/LoopFrame");
Require(___thispath, "Std/Loop/LoopFunction");
Require(___thispath, "Std/Loop/LoopGroup");
Require(___thispath, "Std/Loop/LoopList");
Require(___thispath, "Std/Loop/LoopTimer");
Require(___thispath, "Std/Utility/Bit");
Require(___thispath, "Std/Utility/WeakRef");
Require(___thispath, "Std/Utility/IHeapTimer");
Require(___thispath, "Std/Utility/ISchedule");
Require(___thispath, "Std/Utility/CsvConfig");
Require(___thispath, "Std/Utility/EventDispatcher");
Require(___thispath, "Std/Utility/SafeIDCreator");
Require(___thispath, "Std/Utility/String");
Require(___thispath, "Std/Utility/File");
Require(___thispath, "Std/Utility/JsonConfig");
Require(___thispath, "Std/Net/HttpFileReceiverTemplate");
Require(___thispath, "Std/Net/HttpFileSenderTemplate");
Require(___thispath, "Std/Net/HttpReceiverTemplate");
Require(___thispath, "Std/Net/HttpSenderTemplate");
Require(___thispath, "Std/Net/MsgCommonTemplate");
Require(___thispath, "Std/Net/MsgReceiverTemplate");
Require(___thispath, "Std/Net/MsgSenderTemplate");
Require(___thispath, "Std/Net/MsgSessionTemplate");
Require(___thispath, "Adapter/JavaScript/Timer");
Require(___thispath, "Adapter/JavaScript/FileSystem");
Require(___thispath, "Adapter/JavaScript/JHttpFileInterface");
Require(___thispath, "Adapter/JavaScript/JHttpInterface");
Require(___thispath, "Adapter/JavaScript/JMessageFactory");
Require(___thispath, "Adapter/JavaScript/JMsgInterface");
Require(___thispath, "Adapter/JavaScript/JSchedule");
Require(___thispath, "Adapter/JavaScript/JCsvFile");
Require(___thispath, "../JSNative/md5.min");
Require(___thispath, "../JSNative/jweakmap");
Require(___thispath, "../JSNative/bit");
Require(___thispath, "Std/Loop/LoopSystem");
Require(___thispath, "Std/Utility/Schedule");
}