require("json")
require("net")

local n = net.create();
net.download(n, 1, "https://marketplace.visualstudio.com/items?itemName=AProtobuf.ALittleAProtobuf", "test.txt")
while true do
local e = net.poll(n)
if e == nil then break end
	print(e.cur_size)
	print(e.total_size)
end

require("ALittle/Module/ALittleIDE/Other/GameLibrary/Core/Script/ALittle")

__ALITTLEAPI_Core_Init("ALittle/Module/ALittleIDE/Other/GameLibrary/Core/Script/")
Require("ALittle/Module/ALittleIDE/Other/GameLibrary/HelloWorld/Script/Main");
HelloWorld.Main();
