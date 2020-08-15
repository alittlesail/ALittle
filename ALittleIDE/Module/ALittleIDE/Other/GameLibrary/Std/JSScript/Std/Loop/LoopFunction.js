{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.LoopObject === undefined) throw new Error(" extends class:ALittle.LoopObject is undefined");
ALittle.LoopFunction = JavaScript.Class(ALittle.LoopObject, {
	Ctor : function(func, count, interval_time, delay_time) {
		this._func = func;
		this._total_count = count;
		this._force_completed = false;
		if (delay_time === undefined || delay_time < 0) {
			delay_time = 0;
		}
		if (interval_time < 0) {
			interval_time = 0;
		}
		this._total_interval_time = interval_time;
		this._total_delay_time = delay_time;
		this._accumulate_count = 0;
		this._accumulate_time = 0;
		this._accumulate_delay_time = 0;
		if (this._func === undefined) {
			this._accumulate_count = 0;
			this._total_count = 0;
			ALittle.Log("LoopFunction create failed:function is nil or not a function");
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
		this._accumulate_time = 0;
		this._accumulate_delay_time = 0;
	},
	Completed : function() {
		if (this._complete_callback !== undefined) {
			this._complete_callback();
		}
	},
	IsCompleted : function() {
		if (this._force_completed) {
			return true;
		}
		if (this._total_count < 0) {
			return false;
		}
		return this._total_count <= this._accumulate_count;
	},
	SetCompleted : function() {
		if (this._total_count < 0) {
			this._force_completed = true;
			return;
		}
		this._accumulate_count = this._total_count;
	},
	SetTime : function(time) {
		this._accumulate_count = 0;
		this._accumulate_delay_time = 0;
		this._accumulate_time = 0;
		if (time <= 0) {
			return [0, false];
		}
		if (this._total_count < 0) {
			return [0, false];
		}
		if (time <= this._total_delay_time) {
			this._accumulate_delay_time = time;
			return [0, false];
		}
		this._accumulate_delay_time = this._total_delay_time;
		time = time - (this._total_delay_time);
		let total_time = this._total_interval_time * this._total_count;
		if (time < total_time) {
			let float_count = total_time / this._total_interval_time;
			let count = ALittle.Math_Floor(float_count);
			this._accumulate_count = count;
			this._accumulate_time = ALittle.Math_Floor((float_count - count) * this._total_interval_time);
			return [0, false];
		}
		this._accumulate_count = this._total_count;
		return [time - total_time, true];
	},
	Update : function(frame_time) {
		if (this._accumulate_delay_time < this._total_delay_time) {
			this._accumulate_delay_time = this._accumulate_delay_time + (frame_time);
			if (this._accumulate_delay_time < this._total_delay_time) {
				return;
			}
			frame_time = this._accumulate_delay_time - this._total_delay_time;
			this._accumulate_delay_time = this._total_delay_time;
		}
		this._accumulate_time = this._accumulate_time + (frame_time);
		if (this._accumulate_time > this._total_interval_time) {
			this._accumulate_time = 0;
			++ this._accumulate_count;
			this._func();
		}
	},
}, "ALittle.LoopFunction");

}