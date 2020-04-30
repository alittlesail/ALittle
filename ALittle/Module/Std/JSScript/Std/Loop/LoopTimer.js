{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.LoopObject === undefined) throw new Error(" extends class:ALittle.LoopObject is undefined");
ALittle.LoopTimer = JavaScript.Class(ALittle.LoopObject, {
	Ctor : function(func, delay_time) {
		this._func = func;
		if (delay_time === undefined || delay_time < 0) {
			delay_time = 0;
		}
		this._total_delay_time = delay_time;
		this._accumulate_count = 0;
		this._accumulate_delay_time = 0;
		if (this._func === undefined) {
			this._accumulate_count = 1;
			this._accumulate_delay_time = this._total_delay_time;
			ALittle.Log("LoopTimer create failed:function is nil or not a function");
			return;
		}
		this._complete_callback = undefined;
	},
	get complete_callback() {
		return this._complete_callback;
	},
	set complete_callback(value) {
		this._complete_callback = value;
	},
	Reset : function() {
		this._accumulate_count = 0;
		this._accumulate_delay_time = 0;
	},
	Completed : function() {
		if (this._complete_callback !== undefined) {
			this._complete_callback();
		}
	},
	IsCompleted : function() {
		return this._accumulate_count >= 1;
	},
	SetCompleted : function() {
		if (this._accumulate_count >= 1) {
			return;
		}
		this._accumulate_count = 1;
		this._accumulate_delay_time = this._total_delay_time;
		this._func();
	},
	SetTime : function(time) {
		this._accumulate_count = 0;
		this._accumulate_delay_time = 0;
		if (time <= 0) {
			return [0, false];
		}
		if (time <= this._total_delay_time) {
			this._accumulate_delay_time = time;
			return [0, false];
		}
		this._accumulate_delay_time = this._total_delay_time;
		this._accumulate_count = 1;
		this._func();
		return [time - this._total_delay_time, true];
	},
	Update : function(frame_time) {
		if (this._accumulate_delay_time < this._total_delay_time) {
			this._accumulate_delay_time = this._accumulate_delay_time + (frame_time);
			if (this._accumulate_delay_time < this._total_delay_time) {
				return;
			}
			this._accumulate_delay_time = this._total_delay_time;
		}
		if (this._accumulate_count >= 1) {
			return;
		}
		this._accumulate_count = 1;
		this._func();
	},
}, "ALittle.LoopTimer");

}