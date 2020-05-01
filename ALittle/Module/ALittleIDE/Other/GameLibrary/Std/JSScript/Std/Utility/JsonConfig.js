{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IJsonConfig = JavaScript.Class(undefined, {
	GetConfig : function(key, defaultv) {
		return defaultv;
	},
	GetBool : function(key, defaultv) {
		return defaultv;
	},
	GetInt : function(key, defaultv) {
		return defaultv;
	},
	GetDouble : function(key, defaultv) {
		return defaultv;
	},
	GetString : function(key, defaultv) {
		return defaultv;
	},
	SetConfig : function(key, value, not_save) {
	},
	CoverConfig : function(msg, save) {
	},
	SaveConfig : function() {
	},
}, "ALittle.IJsonConfig");

if (ALittle.IJsonConfig === undefined) throw new Error(" extends class:ALittle.IJsonConfig is undefined");
ALittle.JsonConfig = JavaScript.Class(ALittle.IJsonConfig, {
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
		let [error, json_content] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
		if (error !== undefined) {
			ALittle.Log("Json Decode failed." + file_path + ", " + error);
			return;
		}
		this._config_map = json_content;
	},
	GetConfig : function(key, defaultv) {
		let value = this._config_map[key];
		if (value === undefined) {
			return defaultv;
		}
		return value;
	},
	GetBool : function(key, defaultv) {
		let value = this.GetConfig(key, defaultv);
		return value !== undefined && value !== false;
	},
	GetInt : function(key, defaultv) {
		let value = this.GetConfig(key, defaultv);
		if (value === undefined) {
			value = 0;
		}
		return value;
	},
	GetDouble : function(key, defaultv) {
		let value = this.GetConfig(key, defaultv);
		if (value === undefined) {
			value = 0;
		}
		return value;
	},
	GetString : function(key, defaultv) {
		let value = this.GetConfig(key, defaultv);
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
}, "ALittle.JsonConfig");

ALittle.CreateJsonConfig = function(file_path, print_error) {
	return ALittle.NewObject(JavaScript.Template(ALittle.JsonConfig, "ALittle.JsonConfig<ALittle.JFileLoader, ALittle.JFileSaver>", ALittle.JFileLoader, ALittle.JFileSaver), file_path, print_error);
}

}