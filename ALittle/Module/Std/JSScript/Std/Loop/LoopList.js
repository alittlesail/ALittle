{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.LoopObject === undefined) throw new Error(" extends class:ALittle.LoopObject is undefined");
ALittle.LoopList = JavaScript.Class(ALittle.LoopObject, {
	Ctor : function() {
		this._count = 0;
		this._cur_index = 1;
		this._update_list = [];
		this._complete_callback = undefined;
	},
	get complete_callback() {
		return this._complete_callback;
	},
	set complete_callback(value) {
		this._complete_callback = value;
	},
	get total_count() {
		return this._count;
	},
	AddUpdater : function(value) {
		if (value === undefined) {
			return;
		}
		++ this._count;
		this._update_list[this._count - 1] = value;
	},
	RemoveUpdater : function(value) {
		if (value === undefined || this._count === 0) {
			return;
		}
		let ___OBJECT_1 = this._update_list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let updater = ___OBJECT_1[index - 1];
			if (updater === undefined) break;
			if (value === updater) {
				if (this._cur_index > index) {
					-- this._cur_index;
				}
				ALittle.List_Remove(this._update_list, index);
				-- this._count;
				break;
			}
		}
	},
	Reset : function() {
		this._cur_index = 1;
		let ___OBJECT_2 = this._update_list;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let updater = ___OBJECT_2[index - 1];
			if (updater === undefined) break;
			updater.Reset();
		}
	},
	SetTime : function(time) {
		let ___OBJECT_3 = this._update_list;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let updater = ___OBJECT_3[index - 1];
			if (updater === undefined) break;
			updater.SetTime(0);
		}
		this._cur_index = 1;
		if (time <= 0) {
			return [0, false];
		}
		let ___OBJECT_4 = this._update_list;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let updater = ___OBJECT_4[index - 1];
			if (updater === undefined) break;
			let completed = undefined;
			[time, completed] = updater.SetTime(time);
			if (!completed) {
				this._cur_index = index;
				return [0, false];
			}
		}
		this._cur_index = this._count + 1;
		return [time, true];
	},
	IsCompleted : function() {
		return this._cur_index > this._count;
	},
	Completed : function() {
		if (this._complete_callback !== undefined) {
			this._complete_callback();
		}
	},
	SetCompleted : function() {
		for (let index = this._cur_index; index <= this._count; index += 1) {
			this._update_list[index - 1].SetCompleted();
		}
		this._cur_index = this._count + 1;
	},
	Update : function(frame_time) {
		if (this._cur_index > this._count) {
			return;
		}
		let updater = this._update_list[this._cur_index - 1];
		updater.Update(frame_time);
		if (updater.IsCompleted()) {
			++ this._cur_index;
			updater.Completed();
		}
	},
}, "ALittle.LoopList");

}