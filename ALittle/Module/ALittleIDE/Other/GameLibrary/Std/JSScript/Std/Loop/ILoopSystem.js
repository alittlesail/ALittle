{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.ILoopSystem = JavaScript.Class(undefined, {
	Update : function(frame_time) {
	},
	AddTimer : function(delay_ms, callback, loop, interval_ms) {
		return 0;
	},
	RemoveTimer : function(id) {
		return false;
	},
	AddUpdater : function(object) {
	},
	RemoveUpdater : function(object) {
	},
	HasUpdater : function(object) {
		return false;
	},
}, "ALittle.ILoopSystem");

}