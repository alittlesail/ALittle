{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.LoopObject === undefined) throw new Error(" extends class:ALittle.LoopObject is undefined");
ALittle.LoopLinear = JavaScript.Class(ALittle.LoopObject, {
	Ctor : function(target, property, target_value, total_time, delay_time, func) {
		this._target = target;
		this._target_value = target_value;
		this._func = func;
		if (total_time === undefined || total_time < 0) {
			total_time = 0;
		}
		this._total_time = total_time;
		if (delay_time === undefined || delay_time < 0) {
			delay_time = 0;
		}
		this._total_delay_time = delay_time;
		this._accumulate_time = 0;
		this._accumulate_delay_time = 0;
		if (target === undefined || target[property] === undefined) {
			this._accumulate_time = this._total_time;
			ALittle.Log("LoopLinear create failed:loop_target is nil or property is nil");
			return;
		}
		this._property = property;
		this._complete_callback = undefined;
		this._speed = undefined;
		this._init_value = undefined;
	},
	get complete_callback() {
		return this._complete_callback;
	},
	set complete_callback(value) {
		this._complete_callback = value;
	},
	get speed() {
		if (this._speed !== undefined) {
			return this._speed;
		}
		if (this._init_value === undefined) {
			this._init_value = this._target[this._property];
		}
		this._speed = (this._target_value - this._init_value) / this._total_time;
		return this._speed;
	},
	Reset : function() {
		this._accumulate_time = 0;
		this._accumulate_delay_time = 0;
		this._init_value = undefined;
	},
	SetTime : function(time) {
		this._accumulate_delay_time = 0;
		this._accumulate_time = 0;
		if (time <= 0) {
			return [0, false];
		}
		if (time <= this._total_delay_time) {
			this._accumulate_delay_time = time;
			return [0, false];
		}
		this._accumulate_delay_time = this._total_delay_time;
		time = time - (this._total_delay_time);
		if (time < this._total_time) {
			this._accumulate_time = time;
			if (this._init_value === undefined) {
				this._init_value = this._target[this._property];
			}
			let current_value = (this._accumulate_time * this._target_value + (this._total_time - this._accumulate_time) * this._init_value) / this._total_time;
			this._target[this._property] = current_value;
			return [0, false];
		}
		this._target[this._property] = this._target_value;
		this._accumulate_time = this._total_time;
		if (this._func !== undefined) {
			this._func();
		}
		return [time - this._total_time, true];
	},
	IsCompleted : function() {
		return this._accumulate_time >= this._total_time;
	},
	Completed : function() {
		if (this._complete_callback !== undefined) {
			this._complete_callback();
		}
	},
	SetCompleted : function() {
		if (this._accumulate_time >= this._total_time) {
			return;
		}
		this.SetTime(this._total_time + this._total_delay_time);
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
		if (this._init_value === undefined) {
			this._init_value = this._target[this._property];
		}
		this._accumulate_time = this._accumulate_time + (frame_time);
		if (this._accumulate_time > this._total_time) {
			this._accumulate_time = this._total_time;
		}
		let current_value = (this._accumulate_time * this._target_value + (this._total_time - this._accumulate_time) * this._init_value) / this._total_time;
		this._target[this._property] = current_value;
		if (this._func !== undefined) {
			this._func();
		}
	},
}, "ALittle.LoopLinear");

}