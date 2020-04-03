{
if (typeof ALittle === "undefined") ALittle = {};


let __byte = ALittle.String_Byte;
let __type = ALittle.String_Type;
ALittle.ControlSystem = JavaScript.Class(undefined, {
	Ctor : function(module_name, crypt_mode) {
		this._font_map = {};
		this._name_map_info = {};
		this._name_map_info_cache = {};
		this._module_name = module_name;
		this._crypt_mode = crypt_mode || false;
		this._base_path = "Module/" + module_name + "/";
		this._ui_path = this._base_path + "UI/";
		this._font_path = this._base_path + "Font/";
		this._sound_path = this._base_path + "Sound/";
		this._other_path = this._base_path + "Other/";
		this._texture_mgr = ALittle.NewObject(ALittle.TextureManager, module_name, this._crypt_mode);
		A_LoadTextureManager.RegisterTexmgrControl(this._texture_mgr);
	},
	RegisterFont : function(src, dst) {
		this._font_map[src] = dst;
	},
	RegisterInfoByHttp : function(host, port, name_list) {
		return new Promise((async function(___COROUTINE, ___) {
			let ___OBJECT_1 = name_list;
			for (let index = 1; index <= ___OBJECT_1.length; ++index) {
				let name = ___OBJECT_1[index - 1];
				if (name === undefined) break;
				let [error, content] = await ALittle.HttpDownloadRequest(host, port, this._ui_path + name + ".json");
				if (error !== undefined) {
					ALittle.Error("ui load failed:" + error);
					continue;
				}
				let [jerror, json] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content.GetContent()); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
				if (jerror !== undefined) {
					ALittle.Error("ui json decode failed:" + jerror);
					continue;
				}
				let ___OBJECT_2 = json;
				for (let key in ___OBJECT_2) {
					let value = ___OBJECT_2[key];
					if (value === undefined) continue;
					this.RegisterInfo(key, value);
				}
				let info = this.CreateInfo(this._name_map_info[name]);
				this._name_map_info[name] = info;
				this._name_map_info_cache[name] = true;
			}
			___COROUTINE();
		}).bind(this));
	},
	RegisterInfo : function(name, info) {
		this._name_map_info[name] = info;
		delete this._name_map_info_cache[name];
	},
	UnRegisterInfo : function(name) {
		delete this._name_map_info[name];
		delete this._name_map_info_cache[name];
	},
	ClearAllInfo : function() {
		this._name_map_info = {};
		this._name_map_info_cache = {};
	},
	CreateControlObject : function(info) {
		let target_class = info.__target_class;
		if (target_class !== undefined) {
			let class_func = info.__class_func;
			if (class_func === undefined) {
				class_func = window;
				let ___OBJECT_3 = target_class;
				for (let index = 1; index <= ___OBJECT_3.length; ++index) {
					let value = ___OBJECT_3[index - 1];
					if (value === undefined) break;
					class_func = class_func[value];
					if (class_func === undefined) {
						break;
					}
				}
				info.__class_func = class_func;
			}
			if (class_func !== undefined) {
				return class_func(this);
			} else {
				ALittle.Log("unknow target class." + ALittle.String_Join(target_class, "."));
			}
		}
		let clazz = info.__class;
		if (clazz === undefined) {
			ALittle.Log("__class is null");
			return undefined;
		}
		let class_func = info.__class_func;
		if (class_func === undefined) {
			class_func = ALittle[clazz];
			info.__class_func = class_func;
		}
		if (class_func === undefined) {
			ALittle.Log("unknow class." + clazz);
			return undefined;
		}
		return ALittle.NewObject(class_func, this);
	},
	StartChunk : function(file_path, loop, callback) {
		return A_AudioSystem.StartChunk(this._sound_path + file_path, loop, callback);
	},
	StopChunk : function(channel) {
		A_AudioSystem.StopChunk(channel);
	},
	StartMusic : function(file_path, loop) {
		return A_AudioSystem.StartMusic(this._sound_path + file_path, loop);
	},
	StopMusic : function() {
		A_AudioSystem.StopMusic();
	},
	SetTexture : function(object, name) {
		this._texture_mgr.SetTexture(object, name);
	},
	PrepareTexture : function(ui_list, callback) {
		let name_map = {};
		if (ui_list !== undefined) {
			let ___OBJECT_4 = ui_list;
			for (let index = 1; index <= ___OBJECT_4.length; ++index) {
				let ui = ___OBJECT_4[index - 1];
				if (ui === undefined) break;
				this.CollectTextureName(ui, name_map);
			}
		}
		this._texture_mgr.PrepareTexture(name_map, callback);
	},
	PrepareCsv : function(csv_map, callback) {
		let new_csv_map = {};
		let ___OBJECT_5 = csv_map;
		for (let file_path in ___OBJECT_5) {
			let config = ___OBJECT_5[file_path];
			if (config === undefined) continue;
			new_csv_map[this._other_path + file_path] = config;
		}
		A_CsvConfigManager.PrepareCsv(new_csv_map, callback);
	},
	set cache_texture(cache) {
		this._texture_mgr.cache_texture = cache;
	},
	get cache_texture() {
		return this._texture_mgr.cache_texture;
	},
	SetFont : function(object, font_path, font_size) {
		let dst = this._font_map[font_path];
		if (dst === undefined) {
			dst = font_path;
		}
		object.native_show.SetFont(dst, font_size);
	},
	SaveControlToFile : function(control, file_path, scale) {
		if (control === undefined) {
			return false;
		}
		if (scale === undefined) {
			scale = 1;
		}
		let texture = ALittle.NewObject(lua.__CPPAPIRenderTexture);
		let x = control.x;
		let y = control.y;
		let width = control.width;
		let height = control.height;
		let visible = control.visible;
		let clip = control.clip;
		control.native_show.SetX(0);
		control.native_show.SetY(0);
		control.visible = true;
		control.clip = false;
		let result = texture.Save(file_path, control.native_show, ALittle.Math_Floor(width), ALittle.Math_Floor(height), scale);
		control.native_show.SetX(x);
		control.native_show.SetY(y);
		control.visible = visible;
		control.clip = clip;
		texture.Clear();
		return result;
	},
	CreateControl : function(name, target_logic, parent) {
		let info = this.LoadInfo(name);
		if (info === undefined) {
			ALittle.Log("can't find control name:" + name);
			return undefined;
		}
		let object = this.CreateControlObject(info);
		if (object === undefined) {
			return undefined;
		}
		object.Deserialize(info, target_logic, parent);
		return object;
	},
	CollectTextureName : function(name, map) {
		let info = this.LoadInfo(name);
		if (info === undefined) {
			ALittle.Log("can't find control name:" + name);
			return undefined;
		}
		return this.CollectTextureNameImpl(info, map);
	},
	LoadInfo : function(name) {
		if (this._name_map_info_cache[name]) {
			return this._name_map_info[name];
		}
		let info = this._name_map_info[name];
		if (info === undefined) {
			let [json] = ALittle.File_ReadJsonFromFile(this._ui_path + name + ".json", this._crypt_mode);
			if (json === undefined) {
				return undefined;
			}
			let ___OBJECT_6 = json;
			for (let key in ___OBJECT_6) {
				let value = ___OBJECT_6[key];
				if (value === undefined) continue;
				this.RegisterInfo(key, value);
			}
		}
		info = this.CreateInfo(this._name_map_info[name]);
		this._name_map_info[name] = info;
		this._name_map_info_cache[name] = true;
		return this._name_map_info[name];
	},
	CreateInfo : function(info) {
		if (info === undefined) {
			return undefined;
		}
		if (info.__include !== undefined) {
			return this.LoadInfo(info.__include);
		}
		let extendsv = info.__extends;
		if (extendsv !== undefined) {
			if (info.__extends_included !== true) {
				let control = this.LoadInfo(extendsv);
				if (control === undefined) {
					ALittle.Log("ControlSystem CreateInfo extends Failed:" + extendsv);
					return undefined;
				}
				let copy = {};
				let ___OBJECT_7 = control;
				for (let key in ___OBJECT_7) {
					let value = ___OBJECT_7[key];
					if (value === undefined) continue;
					copy[key] = value;
				}
				let ___OBJECT_8 = info;
				for (let key in ___OBJECT_8) {
					let value = ___OBJECT_8[key];
					if (value === undefined) continue;
					copy[key] = value;
				}
				info = copy;
				info.__extends_included = true;
				info.__shows_included = undefined;
				info.__childs_included = undefined;
				info.__base_attr = undefined;
				info.__show_attr = undefined;
			}
		}
		if (info.__shows_included !== true) {
			let ___OBJECT_9 = info;
			for (let key in ___OBJECT_9) {
				let value = ___OBJECT_9[key];
				if (value === undefined) continue;
				if (__byte(key, 1) !== 95 && __type(value) === "table" && (value.__include !== undefined || value.__extends !== undefined || value.__class !== undefined)) {
					info[key] = this.CreateInfo(value);
				}
			}
			info.__shows_included = true;
		}
		let childs = info.__childs;
		if (childs !== undefined) {
			if (info.__childs_included !== true) {
				let ___OBJECT_10 = childs;
				for (let index = 1; index <= ___OBJECT_10.length; ++index) {
					let child = ___OBJECT_10[index - 1];
					if (child === undefined) break;
					childs[index - 1] = this.CreateInfo(childs[index - 1]);
				}
				info.__childs_included = true;
			}
		}
		return info;
	},
	CollectTextureNameImpl : function(info, map) {
		if (map === undefined) {
			map = {};
		}
		let class_func = undefined;
		let target_class = info.__target_class;
		if (target_class !== undefined) {
			class_func = _G;
			let ___OBJECT_11 = target_class;
			for (let index = 1; index <= ___OBJECT_11.length; ++index) {
				let value = ___OBJECT_11[index - 1];
				if (value === undefined) break;
				class_func = class_func[value];
				if (class_func === undefined) {
					break;
				}
			}
			if (class_func === undefined) {
				ALittle.Log("unknow target class." + ALittle.String_Join(target_class, "."));
			}
		}
		if (class_func === undefined) {
			class_func = ALittle[info.__class];
		}
		if (class_func === undefined) {
			ALittle.Log("unknow class." + info.__class);
			return map;
		}
		let texture_name = info.texture_name;
		if (texture_name !== undefined && texture_name !== "") {
			map[texture_name] = true;
		}
		let info_t = info;
		let ___OBJECT_12 = info_t;
		for (let key in ___OBJECT_12) {
			let value = ___OBJECT_12[key];
			if (value === undefined) continue;
			if (__type(value) === "table" && value.__class !== undefined) {
				this.CollectTextureNameImpl(value, map);
			}
		}
		let childs = info.__childs;
		if (childs !== undefined) {
			let ___OBJECT_13 = childs;
			for (let index = 1; index <= ___OBJECT_13.length; ++index) {
				let value = ___OBJECT_13[index - 1];
				if (value === undefined) break;
				this.CollectTextureNameImpl(value, map);
			}
		}
		return map;
	},
}, "ALittle.ControlSystem");

}