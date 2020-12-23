-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___pairs = pairs
local ___ipairs = ipairs


function ALittle.StartDebugServer(port)
	carp_CarpLuaDebugServer:Start(carp_CarpScript, "", "0.0.0.0", port)
end

ALittle.RegCmdCallback("StartDebugServer", ALittle.StartDebugServer, {"int"}, {"port"}, "")
function ALittle.StopDebugServer()
	carp_CarpLuaDebugServer:Stop()
end

ALittle.RegCmdCallback("StopDebugServer", ALittle.StopDebugServer, {}, {}, "")
end