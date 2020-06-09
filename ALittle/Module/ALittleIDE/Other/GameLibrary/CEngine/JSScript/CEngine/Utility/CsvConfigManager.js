{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(-1040774381, "ALittle.CsvPreloadInfo", {
name : "ALittle.CsvPreloadInfo", ns_name : "ALittle", rl_name : "CsvPreloadInfo", hash_code : -1040774381,
name_list : ["total","succeed","failed","loader_map","callback"],
type_list : ["int","int","int","Map<int,ALittle.CsvPreloadInfoDetail>","Functor<(int,int,int)>"],
option_map : {}
})
ALittle.RegStruct(332955965, "ALittle.CsvPreloadInfoDetail", {
name : "ALittle.CsvPreloadInfoDetail", ns_name : "ALittle", rl_name : "CsvPreloadInfoDetail", hash_code : 332955965,
name_list : ["loader","config"],
type_list : ["ALittle.ICsvFileLoader","ALittle.CsvConfig"],
option_map : {}
})

ALittle.CsvConfigManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._preload_map = new Map();
	},
	PrepareCsv : function(csv_map, callback) {
		let preload_info = {};
		preload_info.total = 0;
		preload_info.succeed = 0;
		preload_info.failed = 0;
		preload_info.loader_map = new Map();
		preload_info.callback = callback;
		let ___OBJECT_1 = csv_map;
		for (let file_path in ___OBJECT_1) {
			let config = ___OBJECT_1[file_path];
			if (config === undefined) continue;
			let loader = undefined;
			loader = ALittle.NewObject(JavaScript.JCsvFileLoader);
			loader.SetPath(file_path, false);
			let detail = {};
			detail.loader = loader;
			detail.config = config;
			preload_info.loader_map.set(loader.GetID(), detail);
			loader.Start();
			++ preload_info.total;
		}
		if (preload_info.total > preload_info.succeed + preload_info.failed) {
			this._preload_map.set(preload_info, true);
		}
		if (callback !== undefined) {
			callback(preload_info.total, preload_info.succeed, preload_info.failed);
		}
	},
	HandleCsvFileLoadSucceed : function(loader, file) {
		let id = loader.GetID();
		for (let [info, value] of this._preload_map) {
			if (value === undefined) continue;
			let detail = info.loader_map.get(id);
			if (detail !== undefined) {
				++ info.succeed;
				if (detail.config !== undefined) {
					detail.config.Init(file);
				}
				if (info.callback !== undefined) {
					info.callback(info.total, info.succeed, info.failed);
				}
				if (info.total === info.succeed + info.failed) {
					this._preload_map.delete(info);
				}
				return;
			}
		}
	},
	HandleCsvFileLoadFailed : function(loader) {
		ALittle.Error("csv load failed! path:" + loader.GetPath());
		let id = loader.GetID();
		for (let [info, value] of this._preload_map) {
			if (value === undefined) continue;
			let detail = info.loader_map.get(id);
			if (detail !== undefined) {
				++ info.failed;
				if (detail.config !== undefined) {
					detail.config.Init(undefined);
				}
				if (info.callback !== undefined) {
					info.callback(info.total, info.succeed, info.failed);
				}
				if (info.total === info.succeed + info.failed) {
					this._preload_map.delete(info);
				}
				return;
			}
		}
	},
}, "ALittle.CsvConfigManager");

window.A_CsvConfigManager = ALittle.NewObject(ALittle.CsvConfigManager);
}