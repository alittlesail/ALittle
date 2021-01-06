{
if (typeof ALittle === "undefined") window.ALittle = {};


let __byte = ALittle.String_Byte;
let __type = ALittle.String_Type;
ALittle.ControlSystem = JavaScript.Class(undefined, {
	Ctor : function(module_name, crypt_mode) {
		this._log_error = true;
		this._use_plugin_class = true;
		this._font_map = {};
		this._child_plugin_map = {};
		this._parent_plugin_map = {};
		this._name_map_info = {};
		this._name_map_info_cache = {};
		this._module_name = module_name;
		this._crypt_mode = crypt_mode || false;
		if (window["alittle_hostname"] !== undefined) {
			this._host = window["alittle_hostname"];
		} else {
			this._host = location.hostname;
		}
		if (window["alittle_port"] !== undefined) {
			this._port = window["alittle_port"];
		} else {
			this._port = ALittle.Math_ToInt(location.port);
		}
		if (window["alittle_base_url"] !== undefined) {
			this._base_url = window["alittle_base_url"];
		} else {
			this._base_url = ALittle.File_GetFilePathByPath(location.pathname) + "/";
		}
		if (this._port === undefined) {
			if (location.protocol === "https:") {
				this._port = 443;
			} else {
				this._port = 80;
			}
		}
		this._base_path = "Module/" + module_name + "/";
		this._base_path = this._base_url + this._base_path;
		this._ui_path = this._base_path + "UI/";
		this._font_path = this._base_path + "Font/";
		this._sound_path = this._base_path + "Sound/";
		this._other_path = this._base_path + "Other/";
		this._texture_mgr = ALittle.NewObject(ALittle.TextureManager, module_name, this._crypt_mode);
		A_LoadTextureManager.RegisterTexmgrControl(this._texture_mgr);
	},
	get crypt_mode() {
		return this._crypt_mode;
	},
	get log_error() {
		return this._log_error;
	},
	set log_error(value) {
		this._log_error = value;
	},
	get info_map() {
		return this._name_map_info;
	},
	RegisterFont : function(src, dst) {
		this._font_map[src] = dst;
	},
	RegisterPlugin : function(module_name, plugin) {
		this._child_plugin_map[module_name] = plugin;
		plugin._parent_plugin_map[this._module_name] = this;
	},
	UnRegisterPlugin : function(module_name) {
		let plugin = this._child_plugin_map[module_name];
		if (plugin === undefined) {
			return;
		}
		delete this._child_plugin_map[module_name];
		delete plugin._parent_plugin_map[this._module_name];
	},
	RegisterInfoByHttp : function() {
		return new Promise((async function(___COROUTINE, ___) {
			let path = this._ui_path + "../JSUI/ui_all_in_one.json";
			ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(path));
			let error = await ALittle.HttpDownloadRequest(this._host, this._port, path, path, undefined, true);
			if (error !== undefined) {
				ALittle.Error("ui load failed:" + error);
				___COROUTINE(); return;
			}
			let [content, buffer] = JavaScript.File_LoadFile(path);
			if (buffer === undefined) {
				ALittle.Error("ui load failed:" + error);
				___COROUTINE(); return;
			}
			content = UTF8ArrayToString(new Uint8Array(buffer));
			JavaScript.File_DeleteFile(path);
			let [jerror, json] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (jerror !== undefined) {
				ALittle.Error("ui json decode failed:" + jerror);
				___COROUTINE(); return;
			}
			let ___OBJECT_1 = json;
			for (let name in ___OBJECT_1) {
				let value = ___OBJECT_1[name];
				if (value === undefined) continue;
				this.RegisterInfo(name, value);
			}
			___COROUTINE();
		}).bind(this));
	},
	HttpDownload : function(path) {
		return new Promise((async function(___COROUTINE, ___) {
			let [content, buffer] = JavaScript.File_LoadFile(path);
			if (buffer !== undefined || content !== undefined) {
				___COROUTINE(undefined); return;
			}
			ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(path));
			let error = await ALittle.HttpDownloadRequest(this._host, this._port, path, this._base_url + path, undefined, true);
			if (error !== undefined) {
				___COROUTINE(error); return;
			}
			___COROUTINE(undefined); return;
		}).bind(this));
	},
	LoadMessageFromFile : function(T, path) {
		return new Promise((async function(___COROUTINE, ___) {
			let path_prefix = "Module/" + this._module_name + "/";
			let module_path = path;
			if (ALittle.String_Find(module_path, path_prefix) === 1) {
				path = ALittle.String_Sub(path, ALittle.String_Len(path_prefix) + 1);
			} else {
				module_path = path_prefix + path;
			}
			let factory = undefined;
			{
				let [content, buffer] = JavaScript.File_LoadFile(module_path);
				if (buffer === undefined) {
					ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(module_path));
					let error = await ALittle.HttpDownloadRequest(this._host, this._port, module_path, this._base_path + path, undefined, true);
					if (error !== undefined) {
						ALittle.Error(this._host, this._port, module_path, error);
						___COROUTINE(undefined); return;
					}
					[content, buffer] = JavaScript.File_LoadFile(module_path);
				}
				if (buffer === undefined) {
					ALittle.Error("FileLoad fialed:", module_path);
					___COROUTINE(undefined); return;
				}
				factory = ALittle.NewObject(JavaScript.JMessageReadFactory, new DataView(buffer), 0, false);
			}
			let rflct = T;
			let invoke_info = ALittle.CreateMessageInfo(rflct.name);
			if (invoke_info === undefined) {
				ALittle.Error("CreateMessageInfo fialed:", module_path);
				___COROUTINE(undefined); return;
			}
			let [data] = ALittle.PS_ReadMessage(factory, invoke_info, undefined, factory.GetDataSize());
			if (data === undefined) {
				ALittle.Error("PS_ReadMessage fialed:", module_path);
				___COROUTINE(undefined); return;
			}
			___COROUTINE(data); return;
		}).bind(this));
	},
	WriteMessageToFile : function(T, msg, path) {
		let path_prefix = "Module/" + this._module_name + "/";
		let module_path = path;
		if (ALittle.String_Find(module_path, path_prefix) === 1) {
			path = ALittle.String_Sub(path, ALittle.String_Len(path_prefix) + 1);
		} else {
			module_path = path_prefix + path;
		}
		let factory = undefined;
		factory = ALittle.NewObject(JavaScript.JMessageWriteFactory, 1024);
		if (factory === undefined) {
			return "factory create failed";
		}
		let rflct = T;
		let invoke_info = ALittle.CreateMessageInfo(rflct.name);
		if (invoke_info === undefined) {
			return "create message info failed:" + rflct.name;
		}
		ALittle.PS_WriteMessage(factory, invoke_info, undefined, msg);
		let result = factory.WriteToStdFile(ALittle.File_BaseFilePath() + module_path);
		if (!result) {
			return "WriteToStdFile failed";
		}
		return undefined;
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
		if (info.__module !== undefined && info.__module !== this._module_name) {
			let plugin = this._child_plugin_map[info.__module];
			if (plugin === undefined) {
				plugin = this._parent_plugin_map[info.__module];
			}
			if (plugin === undefined) {
				ALittle.Log("unknow module " + info.__module + " cur_module:" + this._module_name);
				return undefined;
			}
			return plugin.CreateControlObject(info);
		}
		let target_class = info.__target_class;
		if (this._use_plugin_class && target_class !== undefined) {
			let class_func = info.__class_func;
			if (class_func === undefined) {
				class_func = window;
				let ___OBJECT_2 = target_class;
				for (let index = 1; index <= ___OBJECT_2.length; ++index) {
					let value = ___OBJECT_2[index - 1];
					if (value === undefined) break;
					class_func = class_func[value];
					if (class_func === undefined) {
						break;
					}
				}
				info.__class_func = class_func;
			}
			if (class_func !== undefined) {
				return ALittle.NewObject(class_func, this);
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
	SetTexture : function(object, name) {
		this._texture_mgr.SetTexture(object, name);
	},
	PrepareTexture : function(ui_list, callback) {
		let name_map = {};
		if (ui_list !== undefined) {
			let ___OBJECT_3 = ui_list;
			for (let index = 1; index <= ___OBJECT_3.length; ++index) {
				let ui = ___OBJECT_3[index - 1];
				if (ui === undefined) break;
				this.CollectTextureName(ui, name_map);
			}
		}
		this._texture_mgr.PrepareTexture(name_map, callback);
	},
	PrepareCsv : function(csv_map, callback) {
		let new_csv_map = {};
		let ___OBJECT_4 = csv_map;
		for (let file_path in ___OBJECT_4) {
			let config = ___OBJECT_4[file_path];
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
	set use_plugin_class(use) {
		this._use_plugin_class = use;
	},
	get use_plugin_class() {
		return this._use_plugin_class;
	},
	SetFont : function(object, font_path, font_size) {
		let dst = this._font_map[font_path];
		if (dst === undefined) {
			dst = "Arial";
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
	CreateControlImpl : function(name, target_logic, parent) {
		let info = this.LoadInfo(name);
		if (info === undefined) {
			return undefined;
		}
		let object = this.CreateControlObject(info);
		if (object === undefined) {
			return undefined;
		}
		object.Deserialize(info, target_logic, parent);
		return object;
	},
	CreateControl : function(name, target_logic, parent) {
		let object = this.CreateControlImpl(name, target_logic, parent);
		if (object !== undefined) {
			return object;
		}
		let ___OBJECT_5 = this._child_plugin_map;
		for (let module_name in ___OBJECT_5) {
			let plugin = ___OBJECT_5[module_name];
			if (plugin === undefined) continue;
			object = plugin.CreateControlImpl(name, target_logic, parent);
			if (object !== undefined) {
				return object;
			}
		}
		ALittle.Log("can't find control name:" + name);
		return undefined;
	},
	CollectTextureName : function(name, map) {
		let info = this.LoadInfo(name);
		if (info === undefined) {
			let ___OBJECT_6 = this._child_plugin_map;
			for (let module_name in ___OBJECT_6) {
				let plugin = ___OBJECT_6[module_name];
				if (plugin === undefined) continue;
				info = plugin.LoadInfo(name);
				if (info !== undefined) {
					break;
				}
			}
			let ___OBJECT_7 = this._parent_plugin_map;
			for (let module_name in ___OBJECT_7) {
				let plugin = ___OBJECT_7[module_name];
				if (plugin === undefined) continue;
				info = plugin.LoadInfo(name);
				if (info !== undefined) {
					break;
				}
			}
		}
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
			let ___OBJECT_8 = json;
			for (let key in ___OBJECT_8) {
				let value = ___OBJECT_8[key];
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
			if (info.__module === undefined || info.__module === this._module_name) {
				return this.LoadInfo(info.__include);
			}
			let plugin = this._child_plugin_map[info.__module];
			if (plugin === undefined) {
				plugin = this._parent_plugin_map[info.__module];
			}
			if (plugin !== undefined) {
				return plugin.LoadInfo(info.__include);
			}
			return undefined;
		}
		let extendsv = info.__extends;
		if (extendsv !== undefined) {
			if (info.__extends_included !== true) {
				let control = undefined;
				if (info.__module === undefined || info.__module === this._module_name) {
					control = this.LoadInfo(extendsv);
					if (control === undefined) {
						ALittle.Log("ControlSystem CreateInfo extends Failed, can't find control. extends:" + extendsv + " module:" + this._module_name);
						return undefined;
					}
				} else {
					let plugin = this._child_plugin_map[info.__module];
					if (plugin === undefined) {
						plugin = this._parent_plugin_map[info.__module];
					}
					if (plugin === undefined) {
						ALittle.Log("ControlSystem CreateInfo extends Failed, can't find plugin. extends:" + extendsv + " module:" + info.__module);
						return undefined;
					}
					control = plugin.LoadInfo(extendsv);
					if (control === undefined) {
						ALittle.Log("ControlSystem CreateInfo extends Failed, can't find control. extends:" + extendsv + " module:" + info.__module);
						return undefined;
					}
				}
				let copy = {};
				let ___OBJECT_9 = control;
				for (let key in ___OBJECT_9) {
					let value = ___OBJECT_9[key];
					if (value === undefined) continue;
					copy[key] = value;
				}
				let ___OBJECT_10 = info;
				for (let key in ___OBJECT_10) {
					let value = ___OBJECT_10[key];
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
			let ___OBJECT_11 = info;
			for (let key in ___OBJECT_11) {
				let value = ___OBJECT_11[key];
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
				let ___OBJECT_12 = childs;
				for (let index = 1; index <= ___OBJECT_12.length; ++index) {
					let child = ___OBJECT_12[index - 1];
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
		let texture_name = info.texture_name;
		if (texture_name !== undefined && texture_name !== "") {
			map[texture_name] = true;
		}
		let info_t = info;
		let ___OBJECT_13 = info_t;
		for (let key in ___OBJECT_13) {
			let value = ___OBJECT_13[key];
			if (value === undefined) continue;
			if (__type(value) === "table" && value.__class !== undefined) {
				this.CollectTextureNameImpl(value, map);
			}
		}
		let childs = info.__childs;
		if (childs !== undefined) {
			let ___OBJECT_14 = childs;
			for (let index = 1; index <= ___OBJECT_14.length; ++index) {
				let value = ___OBJECT_14[index - 1];
				if (value === undefined) break;
				this.CollectTextureNameImpl(value, map);
			}
		}
		return map;
	},
}, "ALittle.ControlSystem");

}