-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function ALittle.StartDebugServer(port)
	carp_CarpLuaDebugServer:Start("", "127.0.0.1", port)
end

ALittle.RegCmdCallback("StartDebugServer", ALittle.StartDebugServer, {"int"}, {"port"}, "")
function ALittle.StopDebugServer()
	carp_CarpLuaDebugServer:Stop()
end

ALittle.RegCmdCallback("StopDebugServer", ALittle.StopDebugServer, {}, {}, "")
end