{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.ILoopSystem === undefined) throw new Error(" extends class:ALittle.ILoopSystem is undefined");
ALittle.LoopSystem = JavaScript.Class(ALittle.ILoopSystem, {
	Ctor : function(weak) {
		if (weak) {
			this._loop_updaters = ALittle.CreateKeyWeakMap();
		} else {
			this._loop_updaters = new Map();
		}
		this._in_update = false;
		this._loop_cache = new Map();
		this._cache_empty = true;
		this._timer = ALittle.NewObject(this.__class.__element[0]);
		this._handler_map = new Map();
	},
	AddUpdater : function(updater) {
		if (updater === undefined) {
			return;
		}
		if (this._in_update) {
			this._cache_empty = false;
			this._loop_cache.set(updater, true);
		} else {
			this._loop_updaters.set(updater, true);
		}
	},
	RemoveUpdater : function(updater) {
		if (updater === undefined) {
			return;
		}
		if (this._in_update) {
			this._cache_empty = false;
			this._loop_cache.set(updater, false);
		} else {
			this._loop_updaters.delete(updater);
		}
	},
	HasUpdater : function(updater) {
		return this._loop_updaters.get(updater) !== undefined || this._loop_cache.get(updater) === true;
	},
	AddTimer : function(delay_ms, callback, loop, interval_ms) {
		if (callback === undefined) {
			return 0;
		}
		if (loop === undefined) {
			loop = 1;
		}
		if (interval_ms === undefined) {
			interval_ms = 1;
		}
		let id = this._timer.Add(delay_ms, loop, interval_ms);
		this._handler_map.set(id, callback);
		return id;
	},
	RemoveTimer : function(id) {
		if (id === undefined) {
			return false;
		}
		this._handler_map.delete(id);
		return this._timer.Remove(id);
	},
	Update : function(frame_time) {
		this._in_update = true;
		let remove_map = undefined;
		for (let [updater, v] of this._loop_updaters) {
			if (v === undefined) continue;
			if (updater.IsCompleted()) {
				if (remove_map === undefined) {
					remove_map = new Map();
				}
				remove_map.set(updater, true);
			} else {
				updater.Update(frame_time);
			}
		}
		if (remove_map !== undefined) {
			for (let [updater, v] of remove_map) {
				if (v === undefined) continue;
				this._loop_updaters.delete(updater);
				updater.Completed();
			}
		}
		if (!this._cache_empty) {
			for (let [updater, v] of this._loop_cache) {
				if (v === undefined) continue;
				if (v) {
					this._loop_updaters.set(updater, true);
				} else {
					this._loop_updaters.delete(updater);
				}
			}
			this._loop_cache = new Map();
			this._cache_empty = true;
		}
		this._in_update = false;
		this._timer.Update(frame_time);
		while (true) {
			let id = this._timer.Poll();
			if (id === 0) {
				break;
			}
			if (id < 0) {
				let handle = this._handler_map.get(-id);
				if (handle !== undefined) {
					handle();
					this._handler_map.delete(-id);
				}
			} else {
				let handle = this._handler_map.get(id);
				if (handle !== undefined) {
					handle();
				}
			}
		}
	},
}, "ALittle.LoopSystem");

window.A_JLoopSystem = ALittle.NewObject(JavaScript.Template(ALittle.LoopSystem, "ALittle.LoopSystem<JavaScript.JHeapTimer>", JavaScript.JHeapTimer));
window.A_JWeakLoopSystem = ALittle.NewObject(JavaScript.Template(ALittle.LoopSystem, "ALittle.LoopSystem<JavaScript.JHeapTimer>", JavaScript.JHeapTimer), true);
let GetLoopSystem = function() {
	return A_JLoopSystem;
}

let GetWeakLoopSystem = function() {
	return A_JWeakLoopSystem;
}

window.A_LoopSystem = GetLoopSystem();
window.A_WeakLoopSystem = GetWeakLoopSystem();
}