
module("HelloWorld", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function DownloadTest()
	local error = ALittle.DownloadFile("marketplace.visualstudio.com", 443, "items?itemName=AProtobuf.ALittleAProtobuf", "text.txt")
	if error ~= nil then
		ALittle.Log(error)
	else
		ALittle.Log("download succeed")
	end
end
DownloadTest = Lua.CoWrap(DownloadTest)

function Main()
	ALittle.Log("HelloWorld")
	DownloadTest()
	A_Schedule:Run()
end

