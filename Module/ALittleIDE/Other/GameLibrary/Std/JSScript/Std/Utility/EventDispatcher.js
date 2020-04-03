{
if (typeof ALittle === "undefined") ALittle = {};

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})

ALittle.EventListener = JavaScript.Class(undefined, {
	Ctor : function() {
	},
	RemoveFromDispatcher : function() {
		if (this._ref_map === undefined) {
			return;
		}
		for (let [d, t] of this._ref_map) {
			if (t === undefined) continue;
			for (let [hash_code, vb] of t) {
				if (vb === undefined) continue;
				let callback_table = d._listeners.get(hash_code);
				if (callback_table !== undefined) {
					callback_table.delete(this);
				}
			}
		}
		this._ref_map = undefined;
	},
}, "ALittle.EventListener");

if (ALittle.EventListener === undefined) throw new Error(" extends class:ALittle.EventListener is undefined");
ALittle.EventDispatcher = JavaScript.Class(ALittle.EventListener, {
	Ctor : function() {
		this._listeners = new Map();
		this._abs_disabled = false;
	},
	AddEventListener : function(T, object, callback) {
		if (object === undefined) {
			return false;
		}
		if (callback === undefined) {
			return false;
		}
		let rflt = T;
		let callback_table = this._listeners.get(rflt.hash_code);
		if (callback_table === undefined) {
			callback_table = new Map();
			this._listeners.set(rflt.hash_code, callback_table);
		}
		let callback_value = callback_table.get(object);
		if (callback_value === undefined) {
			callback_value = new Map();
			callback_table.set(object, callback_value);
		}
		callback_value.set(callback, true);
		let ref_map = object._ref_map;
		if (ref_map === undefined) {
			ref_map = new Map();
			object._ref_map = ref_map;
		}
		let ref_value = ref_map.get(this);
		if (ref_value === undefined) {
			ref_value = new Map();
			ref_map.set(this, ref_value);
		}
		ref_value.set(rflt.hash_code, true);
		return true;
	},
	RemoveEventListener : function(T, object, callback) {
		let rflt = T;
		let callback_table = this._listeners.get(rflt.hash_code);
		if (callback_table === undefined) {
			return;
		}
		if (callback === undefined) {
			object._ref_map.delete(this);
			callback_table.delete(object);
		} else {
			let callback_value = callback_table.get(object);
			if (callback_value === undefined) {
				return;
			}
			callback_value.delete(callback);
			object._ref_map.get(this).delete(rflt.hash_code);
		}
	},
	ClearEventListener : function() {
		for (let [hash_code, callback_table] of this._listeners) {
			if (callback_table === undefined) continue;
			for (let [listener, callback_value] of callback_table) {
				if (callback_value === undefined) continue;
				listener._ref_map.delete(this);
			}
		}
		this._listeners = new Map();
	},
	DispatchEvent : function(T, event) {
		let rflt = T;
		if (event.target === undefined) {
			event.target = this;
		}
		let callback_table = this._listeners.get(rflt.hash_code);
		if (callback_table === undefined) {
			return;
		}
		for (let [object, callback_value] of callback_table) {
			if (callback_value === undefined) continue;
			for (let [func, _] of callback_value) {
				if (_ === undefined) continue;
				func.call(object, event);
			}
		}
	},
}, "ALittle.EventDispatcher");

}