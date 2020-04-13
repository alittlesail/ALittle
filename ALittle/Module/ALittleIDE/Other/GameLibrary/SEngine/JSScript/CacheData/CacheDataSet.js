{
if (typeof ALittle === "undefined") ALittle = {};

ALittle.RegStruct(-1164907202, "ALittle.CacheData", {
name : "ALittle.CacheData", ns_name : "ALittle", rl_name : "CacheData", hash_code : -1164907202,
name_list : ["id"],
type_list : ["int"],
option_map : {primary : "id"}
})

ALittle.CacheDataSet = JavaScript.Class(undefined, {
	Ctor : function(submit_interval_ms, cache_interval_ms) {
		this._submit_interval_ms = submit_interval_ms;
		this._cache_interval_ms = cache_interval_ms;
		this._data_map = new Map();
		this._loading_map = new Map();
		this._timer_map = new Map();
		this._dirty_map = new Map();
	},
	Init : function() {
		return new Promise((async function(___COROUTINE, ___) {
			let rflt = this.__class.__element[0];
			this._primary = rflt.option_map["primary"];
			if (this._primary === undefined) {
				___COROUTINE(rflt.name + "没有定义主键"); return;
			}
			let error = await A_MysqlSystem.CreateIfNotExit(this.__class.__element[0]);
			if (error !== undefined) {
				___COROUTINE(error); return;
			}
			if (this._submit_timer !== undefined) {
				A_LoopSystem.RemoveTimer(this._submit_timer);
			}
			this._submit_timer = A_LoopSystem.AddTimer(this._submit_interval_ms, this.Submit.bind(this, true));
			___COROUTINE(undefined); return;
			___COROUTINE();
		}).bind(this));
	},
	Release : function() {
		if (this._submit_timer !== undefined) {
			A_LoopSystem.RemoveTimer(this._submit_timer);
			this._submit_timer = undefined;
		}
		this.Submit(false);
		this._data_map = new Map();
		this._loading_map = new Map();
		for (let [id, timer] of this._timer_map) {
			if (timer === undefined) continue;
			A_LoopSystem.RemoveTimer(timer);
		}
		this._timer_map = new Map();
		this._dirty_map = new Map();
		this._release = true;
		let rflt = this.__class.__element[0];
		ALittle.Log(rflt.name + "操作完毕");
	},
	Submit : async function(loop) {
		this._submit_timer = undefined;
		let data_map = this._data_map;
		let dirty_map = this._dirty_map;
		for (let [id, _] of dirty_map) {
			if (_ === undefined) continue;
			let data = data_map.get(id);
			if (data !== undefined) {
				let error = await A_MysqlSystem.UpdateOne(this.__class.__element[0], data, this._primary, data.id, data.id);
				if (error !== undefined) {
					ALittle.Error(error);
				}
			}
		}
		this._dirty_map = new Map();
		if (loop) {
			this._submit_timer = A_LoopSystem.AddTimer(this._submit_interval_ms, this.Submit.bind(this, true));
		}
	},
	GetDataAndDirty : function(id) {
		return new Promise((async function(___COROUTINE, ___) {
			let data = await this.GetData(id);
			if (data !== undefined) {
				this._dirty_map.set(id, true);
			}
			___COROUTINE(data); return;
			___COROUTINE();
		}).bind(this));
	},
	GetData : function(id) {
		return new Promise((async function(___COROUTINE, ___) {
			if (this._release) {
				___COROUTINE(undefined); return;
			}
			let data = this._data_map.get(id);
			if (data !== undefined) {
				___COROUTINE(data); return;
			}
			if (this._loading_map.get(id)) {
				await A_MysqlSystem.ExecuteEmpty(id);
				if (this._release) {
					___COROUTINE(undefined); return;
				}
				___COROUTINE(this._data_map.get(id)); return;
			}
			this._loading_map.set(id, true);
			let [error, new_data] = await A_MysqlSystem.SelectOneFromByKey(this.__class.__element[0], this._primary, id, id);
			if (error !== undefined) {
				ALittle.Error(error);
			}
			if (this._release) {
				___COROUTINE(undefined); return;
			}
			this._loading_map.delete(id);
			if (new_data === undefined) {
				___COROUTINE(undefined); return;
			}
			this._data_map.set(id, new_data);
			if (this._timer_map.get(id) !== undefined) {
				A_LoopSystem.RemoveTimer(this._timer_map.get(id));
			}
			this._timer_map.set(id, A_LoopSystem.AddTimer(this._cache_interval_ms, this.RemoveCache.bind(this, id)));
			___COROUTINE(new_data); return;
			___COROUTINE();
		}).bind(this));
	},
	RemoveCache : function(id) {
		if (this._release) {
			return;
		}
		this._timer_map.delete(id);
		let data = this._data_map.get(id);
		if (data === undefined) {
			return;
		}
		this._data_map.delete(id);
		if (this._dirty_map.get(id)) {
			this._dirty_map.delete(data.id);
			this.SubmitData(data);
		}
	},
	SubmitData : async function(data) {
		let error = await A_MysqlSystem.UpdateOne(this.__class.__element[0], data, this._primary, data.id, data.id);
		if (error !== undefined) {
			ALittle.Error(error);
		}
	},
	CreateData : function(data) {
		return new Promise((async function(___COROUTINE, ___) {
			if (this._release) {
				___COROUTINE("数据集已经被释放"); return;
			}
			if (this._loading_map.get(data.id)) {
				await A_MysqlSystem.ExecuteEmpty(data.id);
				if (this._release) {
					___COROUTINE("数据集已经被释放"); return;
				}
			}
			if (this._data_map.get(data.id) !== undefined) {
				___COROUTINE("数据已存在"); return;
			}
			this._data_map.set(data.id, data);
			if (this._timer_map.get(data.id) !== undefined) {
				A_LoopSystem.RemoveTimer(this._timer_map.get(data.id));
			}
			this._timer_map.set(data.id, A_LoopSystem.AddTimer(this._cache_interval_ms, this.RemoveCache.bind(this, data.id)));
			let error = await A_MysqlSystem.InsertInto(this.__class.__element[0], data, undefined, data.id);
			if (error !== undefined) {
				ALittle.Error(error);
			}
			___COROUTINE(undefined); return;
			___COROUTINE();
		}).bind(this));
	},
	DeleteData : function(id) {
		return new Promise((async function(___COROUTINE, ___) {
			if (this._release) {
				___COROUTINE("数据集已经被释放"); return;
			}
			if (this._loading_map.get(id)) {
				await A_MysqlSystem.ExecuteEmpty(id);
				if (this._release) {
					___COROUTINE("数据集已经被释放"); return;
				}
			}
			this._dirty_map.delete(id);
			let timer = this._timer_map.get(id);
			if (timer !== undefined) {
				A_LoopSystem.RemoveTimer(timer);
				this._timer_map.delete(id);
			}
			this._data_map.delete(id);
			let error = await A_MysqlSystem.DeleteFromByKey(this.__class.__element[0], this._primary, id, id);
			if (error !== undefined) {
				ALittle.Error(error);
			}
			___COROUTINE(undefined); return;
			___COROUTINE();
		}).bind(this));
	},
}, "ALittle.CacheDataSet");

}