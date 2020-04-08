require("base64");
require("csv");
require("dump");
require("json");
require("lfs");
require("md5");
require("net");
require("timer");
require("utf8");
dump.setup("HelloWorld");

require("ALittle/Module/ALittleIDE/Other/GameLibrary/Core/Script/ALittle")
__ALITTLEAPI_Core_Init("ALittle/Module/ALittleIDE/Other/GameLibrary/Core/Script/")
require("ALittle/Module/ALittleIDE/Other/GameLibrary/Std/Script/ALittle")
__ALITTLEAPI_Std_Init("ALittle/Module/ALittleIDE/Other/GameLibrary/Std/Script/")
Require("ALittle/Module/ALittleIDE/Other/GameLibrary/HelloWorld/Script/Main");
HelloWorld.Main();
