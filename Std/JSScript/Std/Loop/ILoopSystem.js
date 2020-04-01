{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.ILoopSystem = JavaScript.Class(undefined, {
	AddTimer : function(delay_ms, callback, loop, interval_ms) {
		return 0;
	},
	RemoveTimer : function(id) {
		return false;
	},
}, "ALittle.ILoopSystem");

}