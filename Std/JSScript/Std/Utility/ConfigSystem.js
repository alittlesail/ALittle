{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.IConfigSystem = JavaScript.Class(undefined, {
	GetConfig : function(key, default) {
		return default;
	},
	GetBool : function(key, default) {
		return default;
	},
	GetInt : function(key, default) {
		return default;
	},
	GetDouble : function(key, default) {
		return default;
	},
	GetString : function(key, default) {
		return default;
	},
	SetConfig : function(key, value, not_save) {
	},
	CoverConfig : function(msg, save) {
	},
	SaveConfig : function() {
	},
}, "ALittle.IConfigSystem");

if (ALittle.IConfigSystem === undefined) throw new Error(" extends class:ALittle.IConfigSystem is undefined");
ALittle.ConfigSystem = JavaScript.Class(ALittle.IConfigSystem, {
	Ctor : function(file_path, print_error) {
		this._file_path = file_path;
		this._config_map = {};
		let file = ALittle.NewObject(this.__class.__element[0]);
		let content = file.Load(this._file_path);
		if (content === undefined) {
			if (print_error) {
				ALittle.Error("config load failed." + file_path);
			}
			return;
		}
		let [error, json_content] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } })();
		if (error !== undefined) {
			ALittle.Log("Json Decode failed." + file_path + ", " + error);
			return;
		}
		this._config_map = json_content;
	},
	GetConfig : function(key, default) {
		let value = this._config_map[key];
		if (value === undefined) {
			return default;
		}
		return value;
	},
	GetBool : function(key, default) {
		let value = this.GetConfig(key, default);
		return value !== undefined && value !== false;
	},
	GetInt : function(key, default) {
		let value = this.GetConfig(key, default);
		if (value === undefined) {
			value = 0;
		}
		return value;
	},
	GetDouble : function(key, default) {
		let value = this.GetConfig(key, default);
		if (value === undefined) {
			value = 0;
		}
		return value;
	},
	GetString : function(key, default) {
		let value = this.GetConfig(key, default);
		if (value === undefined) {
			value = "";
		}
		return value;
	},
	SetConfig : function(key, value, not_save) {
		this._config_map[key] = value;
		if (!not_save) {
			this.SaveConfig();
		}
	},
	CoverConfig : function(msg, save) {
		let ___OBJECT_1 = msg;
		for (let k in ___OBJECT_1) {
			let v = ___OBJECT_1[k];
			if (v === undefined) continue;
			this._config_map[k] = v;
		}
		if (!save) {
			this.SaveConfig();
		}
	},
	SaveConfig : function() {
		let file = ALittle.NewObject(this.__class.__element[1]);
		if (!file.Save(this._file_path, ALittle.String_JsonEncode(this._config_map))) {
			ALittle.Log("Save Congig Failed.", this._file_path);
		}
	},
}, "ALittle.ConfigSystem");

NormalConfigSystem = JavaScript.Template(ALittle.ConfigSystem, "ALittle.ConfigSystem<ALittle.NormalFileLoader, ALittle.NormalFileSaver>", ALittle.NormalFileLoader, ALittle.NormalFileSaver);
}