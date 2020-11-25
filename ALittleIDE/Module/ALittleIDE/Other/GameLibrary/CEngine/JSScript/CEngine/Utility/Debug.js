{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.StartDebugServer = function(port) {
	carp_CarpLuaDebugServer.Start(carp_CarpScript, "", "0.0.0.0", port);
}

ALittle.RegCmdCallback("StartDebugServer", ALittle.StartDebugServer, ["int"], ["port"], "")
ALittle.StopDebugServer = function() {
	carp_CarpLuaDebugServer.Stop();
}

ALittle.RegCmdCallback("StopDebugServer", ALittle.StopDebugServer, [], [], "")
}