{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})

ALittle.EventDispatcher = JavaScript.Class(undefined, {
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
			callback_table = ALittle.CreateKeyWeakMap();
			this._listeners.set(rflt.hash_code, callback_table);
		}
		let callback_value = callback_table.get(object);
		if (callback_value === undefined) {
			callback_value = new Map();
			callback_table.set(object, callback_value);
		}
		callback_value.set(callback, true);
		return true;
	},
	RemoveEventListener : function(T, object, callback) {
		let rflt = T;
		let callback_table = this._listeners.get(rflt.hash_code);
		if (callback_table === undefined) {
			return;
		}
		if (callback === undefined) {
			callback_table.delete(object);
		} else {
			let callback_value = callback_table.get(object);
			if (callback_value === undefined) {
				return;
			}
			callback_value.delete(callback);
		}
	},
	ClearEventListener : function() {
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