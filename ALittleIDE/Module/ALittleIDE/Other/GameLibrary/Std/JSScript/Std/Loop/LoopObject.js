{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.LoopObject = JavaScript.Class(undefined, {
	IsCompleted : function() {
		return true;
	},
	Completed : function() {
	},
	Update : function(frame_time) {
	},
	Reset : function() {
	},
	SetTime : function(time) {
		return [time, true];
	},
	SetCompleted : function() {
	},
	Dispose : function(deep) {
		this.Stop();
	},
	Start : function() {
		A_JLoopSystem.AddUpdater(this);
	},
	Stop : function() {
		A_JLoopSystem.RemoveUpdater(this);
	},
}, "ALittle.LoopObject");

}