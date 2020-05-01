{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.LoopObject === undefined) throw new Error(" extends class:ALittle.LoopObject is undefined");
ALittle.LoopFrame = JavaScript.Class(ALittle.LoopObject, {
	Ctor : function(func) {
		this._func = func;
		this._force_completed = false;
		if (this._func === undefined) {
			this._force_completed = true;
			ALittle.Log("LoopFrame create failed:function is nil or not a function");
			return;
		}
	},
	Reset : function() {
	},
	Completed : function() {
	},
	IsCompleted : function() {
		return this._force_completed;
	},
	SetCompleted : function() {
		this._force_completed = true;
	},
	SetTime : function(time) {
		return [time, true];
	},
	Update : function(frame_time) {
		this._func(frame_time);
	},
}, "ALittle.LoopFrame");

}