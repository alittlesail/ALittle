{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.LoopObject === undefined) throw new Error(" extends class:ALittle.LoopObject is undefined");
ALittle.LoopGroup = JavaScript.Class(ALittle.LoopObject, {
	Ctor : function() {
		this._total_count = 0;
		this._complete_count = 0;
		this._loop_updaters = new Map();
		this._complete_updaters = new Map();
		this._complete_callback = undefined;
	},
	get complete_callback() {
		return this._complete_callback;
	},
	set complete_callback(value) {
		this._complete_callback = value;
	},
	get total_count() {
		return this._total_count;
	},
	AddUpdater : function(value) {
		if (value === undefined) {
			return;
		}
		if (this._complete_updaters.get(value) || this._loop_updaters.get(value)) {
			return;
		}
		this._loop_updaters.set(value, true);
		++ this._total_count;
	},
	RemoveUpdater : function(value) {
		if (this._loop_updaters.get(value)) {
			this._loop_updaters.delete(value);
			-- this._total_count;
			return;
		}
		if (this._complete_updaters.get(value)) {
			this._complete_updaters.delete(value);
			-- this._total_count;
			-- this._complete_count;
		}
	},
	Reset : function() {
		this._complete_count = 0;
		for (let [updater, v] of this._loop_updaters) {
			if (v === undefined) continue;
			updater.Reset();
		}
		for (let [updater, v] of this._complete_updaters) {
			if (v === undefined) continue;
			this._loop_updaters.set(updater, true);
			updater.Reset();
		}
	},
	SetTime : function(time) {
		if (this._total_count === 0) {
			return [time, true];
		}
		let total_updater = new Map();
		for (let [updater, v] of this._loop_updaters) {
			if (v === undefined) continue;
			total_updater.set(updater, true);
		}
		for (let [updater, v] of this._complete_updaters) {
			if (v === undefined) continue;
			total_updater.set(updater, true);
		}
		this._loop_updaters = new Map();
		this._complete_updaters = new Map();
		this._complete_count = 0;
		let min_time = undefined;
		for (let [updater, v] of total_updater) {
			if (v === undefined) continue;
			let [remain_time, completed] = updater.SetTime(time);
			if (completed) {
				this._complete_updaters.set(updater, true);
				++ this._complete_count;
			} else {
				this._loop_updaters.set(updater, true);
			}
			if (min_time === undefined || min_time > remain_time) {
				min_time = remain_time;
			}
		}
		return [min_time, this._complete_count === this._total_count];
	},
	IsCompleted : function() {
		return this._complete_count >= this._total_count;
	},
	Completed : function() {
		if (this._complete_callback !== undefined) {
			this._complete_callback();
		}
	},
	SetCompleted : function() {
		this._complete_count = this._total_count;
		for (let [updater, v] of this._loop_updaters) {
			if (v === undefined) continue;
			updater.SetCompleted();
			this._complete_updaters.set(updater, true);
		}
		this._loop_updaters = new Map();
	},
	Update : function(frame_time) {
		if (this._complete_count >= this._total_count) {
			return;
		}
		let remove_map = new Map();
		for (let [updater, v] of this._loop_updaters) {
			if (v === undefined) continue;
			if (updater.IsCompleted()) {
				remove_map.set(updater, true);
			} else {
				updater.Update(frame_time);
			}
		}
		for (let [updater, v] of remove_map) {
			if (v === undefined) continue;
			this._loop_updaters.delete(updater);
			this._complete_updaters.set(updater, true);
			++ this._complete_count;
			updater.Completed();
		}
	},
}, "ALittle.LoopGroup");

}