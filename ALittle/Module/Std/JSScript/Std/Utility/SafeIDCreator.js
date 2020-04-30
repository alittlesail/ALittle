{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.SafeIDCreator = JavaScript.Class(undefined, {
	Ctor : function() {
		this._max_id = 0;
		this._map = new Map();
	},
	CreateID : function() {
		let id = undefined;
		for (let [k, v] of this._map) {
			if (v === undefined) continue;
			id = k;
			break;
		}
		if (id !== undefined) {
			this._map.delete(id);
			return id;
		}
		this._max_id = this._max_id + 1;
		return this._max_id;
	},
	ReleaseID : function(id) {
		this._map.set(id, true);
	},
	PrintStatus : function() {
		let count = 0;
		for (let [k, v] of this._map) {
			if (v === undefined) continue;
			++ count;
		}
		ALittle.Log("SafeIDCreator:PrintStatus count:" + count + " max_id:" + this._max_id);
	},
}, "ALittle.SafeIDCreator");

}