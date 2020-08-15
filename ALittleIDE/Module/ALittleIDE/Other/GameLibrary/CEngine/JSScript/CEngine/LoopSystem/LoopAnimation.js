{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(-1741432339, "ALittle.LoopListInfo", {
name : "ALittle.LoopListInfo", ns_name : "ALittle", rl_name : "LoopListInfo", hash_code : -1741432339,
name_list : ["link","attribute","init","childs"],
type_list : ["string","string","any","List<ALittle.LoopChildInfo>"],
option_map : {}
})
ALittle.RegStruct(1653869333, "ALittle.LoopGroupInfo", {
name : "ALittle.LoopGroupInfo", ns_name : "ALittle", rl_name : "LoopGroupInfo", hash_code : 1653869333,
name_list : ["childs"],
type_list : ["List<ALittle.LoopListInfo>"],
option_map : {}
})
ALittle.RegStruct(-925381158, "ALittle.LoopChildInfo", {
name : "ALittle.LoopChildInfo", ns_name : "ALittle", rl_name : "LoopChildInfo", hash_code : -925381158,
name_list : ["clazz","target","total_time","delay_time"],
type_list : ["string","any","int","int"],
option_map : {}
})

ALittle.LoopAnimation = JavaScript.Class(undefined, {
	Ctor : function(from, info) {
		this._from = from;
		this._info = info;
	},
	Init : function(map) {
		this.Stop();
		this._group = ALittle.NewObject(ALittle.LoopGroup);
		this._group.complete_callback = this.Completed.bind(this);
		this._save_value_map = new Map();
		this._init_value_map = new Map();
		let ___OBJECT_1 = this._info.childs;
		for (let _ = 1; _ <= ___OBJECT_1.length; ++_) {
			let list = ___OBJECT_1[_ - 1];
			if (list === undefined) break;
			let target = undefined;
			if (map !== undefined) {
				target = map[list.link];
			}
			if (target === undefined && this._from !== undefined) {
				target = this._from[list.link];
			}
			if (target === undefined) {
				this._group = undefined;
				this._save_value_map = undefined;
				this._init_value_map = undefined;
				return "can't find link:" + list.link + " from map or object";
			}
			let value_map = this._save_value_map.get(target);
			if (value_map === undefined) {
				value_map = {};
				this._save_value_map.set(target, value_map);
			}
			value_map[list.attribute] = target[list.attribute];
			if (list.init !== undefined) {
				target[list.attribute] = list.init;
				value_map = this._init_value_map.get(target);
				if (value_map === undefined) {
					value_map = {};
					this._init_value_map.set(target, value_map);
				}
				value_map[list.attribute] = list.init;
			}
			let loop_list = ALittle.NewObject(ALittle.LoopList);
			let ___OBJECT_2 = list.childs;
			for (let index = 1; index <= ___OBJECT_2.length; ++index) {
				let info = ___OBJECT_2[index - 1];
				if (info === undefined) break;
				if (info.clazz === "LoopLinear") {
					loop_list.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, target, list.attribute, info.target, info.total_time, info.delay_time));
				} else if (info.clazz === "LoopAttribute") {
					loop_list.AddUpdater(ALittle.NewObject(ALittle.LoopAttribute, target, list.attribute, info.target, info.delay_time));
				} else if (info.clazz === "LoopRit") {
					loop_list.AddUpdater(ALittle.NewObject(ALittle.LoopRit, target, list.attribute, info.target, info.total_time, info.delay_time));
				}
			}
			this._group.AddUpdater(loop_list);
		}
		return undefined;
	},
	Completed : function() {
		if (this._loop === 0) {
			this.ReleaseCo(undefined);
			return;
		}
		if (this._loop > 0) {
			-- this._loop;
			if (this._loop <= 0) {
				this.ReleaseCo(undefined);
				return;
			}
		}
		this.SetTime(0);
		this._group.Start();
	},
	Play : function(loop) {
		this.ReleaseCo("Play被调用");
		if (this._group === undefined) {
			return;
		}
		if (loop === undefined) {
			this._loop = 1;
		} else if (loop === 0) {
			this._loop = -1;
		} else {
			this._loop = loop;
		}
		this._group.Start();
	},
	AsyncPlay : function(loop) {
		return new Promise((function(___COROUTINE, ___) {
			this.ReleaseCo("AsyncPlay被调用");
			if (this._group === undefined) {
				___COROUTINE("this._group == null"); return;
			}
			if (___COROUTINE === undefined) {
				___COROUTINE("当前不是协程"); return;
			}
			this._co = ___COROUTINE;
			if (loop === undefined) {
				this._loop = 1;
			} else if (loop === 0) {
				this._loop = -1;
			} else {
				this._loop = loop;
			}
			this._group.Start();
			return;
		}).bind(this));
	},
	ReleaseCo : function(reason) {
		if (this._co === undefined) {
			return;
		}
		let [result, error] = ALittle.Coroutine.Resume(this._co, reason);
		if (result !== true) {
			ALittle.Error(error);
		}
		this._co = undefined;
	},
	Pause : function() {
		if (this._group === undefined) {
			return;
		}
		this._group.Stop();
	},
	SetTime : function(time) {
		this.ReleaseCo("SetTime被调用");
		if (this._group === undefined) {
			return;
		}
		if (this._save_value_map !== undefined) {
			for (let [object, value_map] of this._save_value_map) {
				if (value_map === undefined) continue;
				let ___OBJECT_3 = value_map;
				for (let attr in ___OBJECT_3) {
					let param = ___OBJECT_3[attr];
					if (param === undefined) continue;
					object[attr] = param;
				}
			}
		}
		if (this._init_value_map !== undefined) {
			for (let [object, value_map] of this._init_value_map) {
				if (value_map === undefined) continue;
				let ___OBJECT_4 = value_map;
				for (let attr in ___OBJECT_4) {
					let param = ___OBJECT_4[attr];
					if (param === undefined) continue;
					object[attr] = param;
				}
			}
		}
		this._group.SetTime(time);
	},
	Stop : function() {
		this.ReleaseCo("Stop被调用");
		if (this._group !== undefined) {
			this._group.Stop();
			this._group = undefined;
		}
		if (this._save_value_map !== undefined) {
			for (let [object, value_map] of this._save_value_map) {
				if (value_map === undefined) continue;
				let ___OBJECT_5 = value_map;
				for (let attr in ___OBJECT_5) {
					let param = ___OBJECT_5[attr];
					if (param === undefined) continue;
					object[attr] = param;
				}
			}
			this._save_value_map = undefined;
		}
		this._init_value_map = undefined;
	},
}, "ALittle.LoopAnimation");

}