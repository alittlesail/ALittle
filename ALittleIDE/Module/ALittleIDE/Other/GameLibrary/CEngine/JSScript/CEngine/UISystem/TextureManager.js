{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(-1815508639, "ALittle.TextureCutInfo", {
name : "ALittle.TextureCutInfo", ns_name : "ALittle", rl_name : "TextureCutInfo", hash_code : -1815508639,
name_list : ["texture_name","max_width","max_height","cache"],
type_list : ["string","int","int","bool"],
option_map : {}
})
ALittle.RegStruct(1812223610, "ALittle.LoadAtlasInfo", {
name : "ALittle.LoadAtlasInfo", ns_name : "ALittle", rl_name : "LoadAtlasInfo", hash_code : 1812223610,
name_list : ["big_path","atlas","big_width","big_height"],
type_list : ["string","List<string>","int","int"],
option_map : {}
})
ALittle.RegStruct(1754262532, "ALittle.LoadingTextureInfo", {
name : "ALittle.LoadingTextureInfo", ns_name : "ALittle", rl_name : "LoadingTextureInfo", hash_code : 1754262532,
name_list : ["cache","object_map"],
type_list : ["bool","Map<ALittle.DisplayObject,ALittle.LoadingTextureObjectInfo>"],
option_map : {}
})
ALittle.RegStruct(1390702448, "ALittle.AltasCollectInfo", {
name : "ALittle.AltasCollectInfo", ns_name : "ALittle", rl_name : "AltasCollectInfo", hash_code : 1390702448,
name_list : ["count","list"],
type_list : ["int","List<List<any>>"],
option_map : {}
})
ALittle.RegStruct(1305876767, "ALittle.PrepareInfo", {
name : "ALittle.PrepareInfo", ns_name : "ALittle", rl_name : "PrepareInfo", hash_code : 1305876767,
name_list : ["total","succeed","failed","map","callback"],
type_list : ["int","int","int","Map<string,bool>","Functor<(int,int,int)>"],
option_map : {}
})
ALittle.RegStruct(1266404893, "ALittle.LoadTextureInfo", {
name : "ALittle.LoadTextureInfo", ns_name : "ALittle", rl_name : "LoadTextureInfo", hash_code : 1266404893,
name_list : ["loader","cut_loader","texture_mgr"],
type_list : ["ALittle.ITextureLoader","ALittle.ITextureCutLoader","ALittle.TextureManager"],
option_map : {}
})
ALittle.RegStruct(1002517605, "ALittle.LoadingTextureObjectInfo", {
name : "ALittle.LoadingTextureObjectInfo", ns_name : "ALittle", rl_name : "LoadingTextureObjectInfo", hash_code : 1002517605,
name_list : ["callback"],
type_list : ["Functor<(ALittle.DisplayObject,bool)>"],
option_map : {}
})
ALittle.RegStruct(-451991995, "ALittle.AltasTextureInfo", {
name : "ALittle.AltasTextureInfo", ns_name : "ALittle", rl_name : "AltasTextureInfo", hash_code : -451991995,
name_list : ["width","height","path"],
type_list : ["int","int","string"],
option_map : {}
})
ALittle.RegStruct(-60039899, "ALittle.AltasInfo", {
name : "ALittle.AltasInfo", ns_name : "ALittle", rl_name : "AltasInfo", hash_code : -60039899,
name_list : ["big_path","atlas","big_width","big_height","t","b","l","r"],
type_list : ["string","List<string>","int","int","double","double","double","double"],
option_map : {}
})

ALittle.LoadTextureManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._id_map_info = new Map();
		this._path_map_texture_cut = ALittle.CreateValueWeakMap();
		this._path_map_objects_cut = {};
		this._redraw_map_redraw = ALittle.CreateKeyWeakMap();
		this._texmgr_map_texmgr = ALittle.CreateKeyWeakMap();
	},
	CreateTexture : function(texture_mgr, atlas) {
		let loader = undefined;
		loader = ALittle.NewObject(JavaScript.JTextureLoader);
		loader.SetPath(atlas.big_path, ALittle.String_Join(atlas.atlas, ";"), atlas.big_width, atlas.big_height, texture_mgr.crypt_mode);
		let info = {};
		this._id_map_info.set(loader.GetID(), info);
		info.texture_mgr = texture_mgr;
		info.loader = loader;
		loader.Start();
	},
	HandleTextureLoadSucceed : function(loader, texture) {
		let loader_id = loader.GetID();
		let info = this._id_map_info.get(loader_id);
		if (info === undefined) {
			return;
		}
		this._id_map_info.delete(loader_id);
		info.texture_mgr.HandleTextureLoadSucceed(loader, texture);
	},
	HandleTextureLoadFailed : function(loader) {
		let loader_id = loader.GetID();
		let info = this._id_map_info.get(loader_id);
		if (info === undefined) {
			return;
		}
		this._id_map_info.delete(loader_id);
		info.texture_mgr.HandleTextureLoadFailed(loader);
	},
	GetTextureCut : function(path, max_width, max_height) {
		let texture_id = path + "_" + max_width + "_" + max_height;
		return this._path_map_texture_cut[texture_id];
	},
	ClearTextureCut : function(path, max_width, max_height) {
		let texture_id = path + "_" + max_width + "_" + max_height;
		delete this._path_map_texture_cut[texture_id];
	},
	IsLoadingTextureCut : function(path, max_width, max_height) {
		let texture_id = path + "_" + max_width + "_" + max_height;
		return this._path_map_objects_cut[texture_id] !== undefined;
	},
	SetTextureCut : function(object, path, max_width, max_height, cache, callback) {
		object.SetTextureCoord(0, 1, 0, 1);
		if (max_width === undefined) {
			max_width = 0;
		}
		max_width = ALittle.Math_Floor(max_width);
		if (max_height === undefined) {
			max_height = 0;
		}
		max_height = ALittle.Math_Floor(max_height);
		if (cache === undefined) {
			cache = false;
		}
		let texture_id = path + "_" + max_width + "_" + max_height;
		let texture = this._path_map_texture_cut[texture_id];
		if (texture !== undefined) {
			object.texture = texture;
			if (callback !== undefined) {
				callback(object, true);
			}
			return;
		}
		let loading_info = this._path_map_objects_cut[texture_id];
		if (loading_info !== undefined) {
			let object_info = {};
			object_info.callback = callback;
			loading_info.object_map.set(object, object_info);
			return;
		}
		loading_info = {};
		loading_info.cache = cache;
		this._path_map_objects_cut[texture_id] = loading_info;
		loading_info.object_map = ALittle.CreateKeyWeakMap();
		let object_info = {};
		object_info.callback = callback;
		loading_info.object_map.set(object, object_info);
		let loader = undefined;
		loader = ALittle.NewObject(JavaScript.JTextureCutLoader);
		loader.SetPath(path, max_width, max_height);
		let info = {};
		this._id_map_info.set(loader.GetID(), info);
		info.cut_loader = loader;
		loader.Start();
	},
	HandleTextureCutLoadSucceed : function(loader, texture) {
		let loader_id = loader.GetID();
		let info = this._id_map_info.get(loader_id);
		if (info === undefined) {
			return;
		}
		this._id_map_info.delete(loader_id);
		let path = loader.GetPath();
		let max_width = loader.GetMaxWidth();
		let max_height = loader.GetMaxHeight();
		let texture_id = path + "_" + max_width + "_" + max_height;
		let loading_info = this._path_map_objects_cut[texture_id];
		if (loading_info === undefined) {
			return;
		}
		if (loading_info.cache) {
			this._path_map_texture_cut[texture_id] = texture;
		}
		for (let [object, value] of loading_info.object_map) {
			if (value === undefined) continue;
			if (object.texture_name === path) {
				object.texture = texture;
				if (value.callback !== undefined) {
					value.callback(object, true);
				}
			}
		}
		delete this._path_map_objects_cut[texture_id];
	},
	HandleTextureCutLoadFailed : function(loader) {
		let loader_id = loader.GetID();
		let info = this._id_map_info.get(loader_id);
		if (info === undefined) {
			return;
		}
		this._id_map_info.delete(loader_id);
		let path = loader.GetPath();
		let max_width = loader.GetMaxWidth();
		let max_height = loader.GetMaxHeight();
		let texture_id = path + "_" + max_width + "_" + max_height;
		let loading_info = this._path_map_objects_cut[texture_id];
		if (loading_info === undefined) {
			return;
		}
		for (let [object, value] of loading_info.object_map) {
			if (value === undefined) continue;
			if (value.callback !== undefined) {
				value.callback(object, false);
			}
		}
		delete this._path_map_objects_cut[texture_id];
	},
	RegisterRedrawControl : function(control) {
		this._redraw_map_redraw.set(control, true);
	},
	RegisterTexmgrControl : function(control) {
		this._texmgr_map_texmgr.delete(control);
	},
	HandleRenderDeviceReset : function() {
		this._path_map_texture_cut = ALittle.CreateValueWeakMap();
		for (let [texmgr, _] of this._texmgr_map_texmgr) {
			if (_ === undefined) continue;
			texmgr.ClearCache();
		}
		for (let [control, _] of this._redraw_map_redraw) {
			if (_ === undefined) continue;
			control.Redraw();
		}
	},
}, "ALittle.LoadTextureManager");

window.A_LoadTextureManager = ALittle.NewObject(ALittle.LoadTextureManager);
ALittle.AltasBinary = JavaScript.Class(undefined, {
	Ctor : function(x, y, width, height) {
		this._width = width;
		this._height = height;
		this._x = x;
		this._y = y;
		this._texture_x = undefined;
		this._texture_y = undefined;
		this._texture_w = undefined;
		this._texture_h = undefined;
		this._texture_path = undefined;
		this._left = undefined;
		this._right = undefined;
	},
	Fill : function(texture_info, padding) {
		if (this._left !== undefined) {
			if (this._left.Fill(texture_info, padding)) {
				return true;
			}
		}
		if (this._right !== undefined) {
			if (this._right.Fill(texture_info, padding)) {
				return true;
			}
		}
		if (this._texture_path === undefined) {
			let real_width = texture_info.width + padding * 2;
			let real_height = texture_info.height + padding * 2;
			if (real_width > this._width) {
				return false;
			}
			if (real_height > this._height) {
				return false;
			}
			this._texture_w = texture_info.width;
			this._texture_h = texture_info.height;
			this._texture_x = this._x + padding;
			this._texture_y = this._y + padding;
			this._texture_path = texture_info.path;
			this._left = ALittle.NewObject(ALittle.AltasBinary, this._x + real_width, this._y, this._width - real_width, real_height);
			this._right = ALittle.NewObject(ALittle.AltasBinary, this._x, this._y + real_height, this._width, this._height - real_height);
			return true;
		}
		return false;
	},
	GetInfo : function(list_info) {
		if (list_info === undefined) {
			list_info = {};
			list_info.count = 0;
			list_info.list = [];
		}
		if (this._texture_path !== undefined) {
			let info = [];
			info[1 - 1] = this._texture_path;
			info[2 - 1] = this._texture_x;
			info[3 - 1] = this._texture_y;
			info[4 - 1] = this._texture_w;
			info[5 - 1] = this._texture_h;
			++ list_info.count;
			list_info.list[list_info.count - 1] = info;
		}
		if (this._left !== undefined) {
			this._left.GetInfo(list_info);
		}
		if (this._right !== undefined) {
			this._right.GetInfo(list_info);
		}
		return list_info.list;
	},
	TextureListComp : function(a, b) {
		if (a.height > b.height) {
			return true;
		} else if (a.height === b.height) {
			if (a.width > b.width) {
				return true;
			} else if (a.width === b.width) {
				if (a.path > b.path) {
					return true;
				}
			}
		}
		return false;
	},
	GenerateAltas : function(texture_list, max_width, max_height, padding) {
		ALittle.List_Sort(texture_list, ALittle.AltasBinary.TextureListComp);
		let big_list = [];
		let big_list_count = 0;
		++ big_list_count;
		big_list[big_list_count - 1] = max_width;
		++ big_list_count;
		big_list[big_list_count - 1] = max_height;
		while (true) {
			let altas = ALittle.NewObject(ALittle.AltasBinary, 0, 0, max_width, max_height);
			let left_list = [];
			let left_list_count = 0;
			let ___OBJECT_1 = texture_list;
			for (let index = 1; index <= ___OBJECT_1.length; ++index) {
				let texture_info = ___OBJECT_1[index - 1];
				if (texture_info === undefined) break;
				let real_width = texture_info.width + padding * 2;
				let real_height = texture_info.height + padding * 2;
				if (real_width <= max_width && real_height <= max_height) {
					if (altas.Fill(texture_info, padding) !== true) {
						++ left_list_count;
						left_list[left_list_count - 1] = texture_info;
					}
				}
			}
			let list = altas.GetInfo();
			if (list[2 - 1] !== undefined) {
				++ big_list_count;
				big_list[big_list_count - 1] = list;
			}
			texture_list = left_list;
			if (texture_list[1 - 1] === undefined) {
				break;
			}
		}
		return big_list;
	},
}, "ALittle.AltasBinary");

ALittle.TextureManager = JavaScript.Class(undefined, {
	Ctor : function(module_name, crypt_mode) {
		this._cache_texture = true;
		this._base_path = "Module/" + module_name + "/Texture/";
		this._crypt_mode = crypt_mode || false;
		this._path_map_texture = ALittle.CreateValueWeakMap();
		this._prepare_map = new Map();
		this._path_map_objects = {};
		this.LoadAtlas();
	},
	LoadAtlas : function() {
		this._name_map_atlas = {};
		if (!this._crypt_mode) {
			return;
		}
		let [big_list] = ALittle.File_ReadJsonFromFile(this._base_path + "Atlas.ali", this._crypt_mode);
		if (big_list === undefined) {
			return;
		}
		let big_list_count = ALittle.List_Len(big_list);
		if (big_list_count < 2) {
			return;
		}
		let texture_width = big_list[1 - 1];
		let texture_height = big_list[2 - 1];
		for (let index = 3; index <= big_list_count; index += 1) {
			let list = big_list[index - 1];
			let big_path = index + ".atlas";
			let info = [];
			let info_count = 0;
			let ___OBJECT_2 = list;
			for (let _ = 1; _ <= ___OBJECT_2.length; ++_) {
				let value = ___OBJECT_2[_ - 1];
				if (value === undefined) break;
				let path = value[1 - 1];
				let x = value[2 - 1];
				let y = value[3 - 1];
				let w = value[4 - 1];
				let h = value[5 - 1];
				let atlas = {};
				atlas.big_path = big_path;
				atlas.t = y / texture_height;
				atlas.b = (y + h) / texture_height;
				atlas.l = x / texture_width;
				atlas.r = (x + w) / texture_width;
				atlas.big_width = texture_width;
				atlas.big_height = texture_height;
				atlas.atlas = info;
				this._name_map_atlas[path] = atlas;
				++ info_count;
				info[info_count - 1] = this._base_path + path + "," + y + "," + ((y + h)) + "," + x + "," + ((x + w)) + "," + w + "," + h;
			}
		}
	},
	GetAtlas : function(name) {
		let atlas = this._name_map_atlas[name];
		if (atlas !== undefined) {
			return atlas;
		}
		atlas = {};
		this._name_map_atlas[name] = atlas;
		atlas.big_path = name;
		atlas.t = 0;
		atlas.b = 1;
		atlas.l = 0;
		atlas.r = 1;
		atlas.big_width = 0;
		atlas.big_height = 0;
		atlas.atlas = [];
		atlas.atlas[1 - 1] = this._base_path + name + ",0,0,0,0,0,0";
		return atlas;
	},
	set cache_texture(cache) {
		this._cache_texture = cache;
	},
	get cache_texture() {
		return this._cache_texture;
	},
	get crypt_mode() {
		return this._crypt_mode;
	},
	ClearCache : function() {
		this._path_map_texture = ALittle.CreateValueWeakMap();
		this._prepare_map = new Map();
	},
	PrepareTexture : function(name_map, callback) {
		let new_name_map = {};
		let ___OBJECT_3 = name_map;
		for (let name in ___OBJECT_3) {
			let value = ___OBJECT_3[name];
			if (value === undefined) continue;
			let atlas = this.GetAtlas(name);
			if (new_name_map[atlas.big_path] === undefined) {
				let texture = this._path_map_texture[atlas.big_path];
				if (texture === undefined) {
					let loading_map = this._path_map_objects[atlas.big_path];
					if (loading_map === undefined) {
						loading_map = ALittle.CreateKeyWeakMap();
						this._path_map_objects[atlas.big_path] = loading_map;
					}
					A_LoadTextureManager.CreateTexture(this, atlas);
					new_name_map[atlas.big_path] = false;
				} else {
					new_name_map[atlas.big_path] = true;
				}
			}
		}
		let prepare_info = {};
		prepare_info.total = 0;
		prepare_info.succeed = 0;
		prepare_info.failed = 0;
		prepare_info.map = new_name_map;
		prepare_info.callback = callback;
		let ___OBJECT_4 = new_name_map;
		for (let name in ___OBJECT_4) {
			let value = ___OBJECT_4[name];
			if (value === undefined) continue;
			++ prepare_info.total;
			if (value) {
				++ prepare_info.succeed;
			}
		}
		if (prepare_info.total > prepare_info.succeed + prepare_info.failed) {
			this._prepare_map.set(prepare_info, true);
		}
		if (callback !== undefined) {
			callback(prepare_info.total, prepare_info.succeed, prepare_info.failed);
		}
	},
	SetTexture : function(object, name) {
		let atlas = this.GetAtlas(name);
		object.SetTextureCoord(atlas.t, atlas.b, atlas.l, atlas.r);
		let texture = this._path_map_texture[atlas.big_path];
		if (texture !== undefined) {
			object.texture = texture;
			return;
		}
		let loading_map = this._path_map_objects[atlas.big_path];
		if (loading_map !== undefined) {
			loading_map.set(object, name);
			return;
		}
		loading_map = ALittle.CreateKeyWeakMap();
		this._path_map_objects[atlas.big_path] = loading_map;
		loading_map.set(object, name);
		A_LoadTextureManager.CreateTexture(this, atlas);
	},
	HandleTextureLoadSucceed : function(loader, texture) {
		let path = loader.GetPath();
		let loading_map = this._path_map_objects[path];
		if (loading_map !== undefined) {
			if (this._cache_texture) {
				this._path_map_texture[path] = texture;
			}
			for (let [k, v] of loading_map) {
				if (v === undefined) continue;
				if (k.texture_name === v) {
					k.texture = texture;
				}
			}
			delete this._path_map_objects[path];
		}
		let copy_map = new Map();
		for (let [k, v] of this._prepare_map) {
			if (v === undefined) continue;
			copy_map.set(k, v);
		}
		let erase_map = new Map();
		for (let [info, v] of copy_map) {
			if (v === undefined) continue;
			if (info.map[path] === false) {
				++ info.succeed;
				info.map[path] = true;
				if (info.callback !== undefined) {
					info.callback(info.total, info.succeed, info.failed);
				}
				if (info.total <= info.succeed + info.failed) {
					erase_map.set(info, true);
				}
			}
		}
		for (let [info, v] of erase_map) {
			if (v === undefined) continue;
			this._prepare_map.delete(info);
		}
	},
	HandleTextureLoadFailed : function(loader) {
		let path = loader.GetPath();
		delete this._path_map_objects[path];
		let erase_map = new Map();
		for (let [info, v] of this._prepare_map) {
			if (v === undefined) continue;
			if (info.map[path] === false) {
				++ info.failed;
				info.map[path] = true;
				if (info.callback !== undefined) {
					info.callback(info.total, info.succeed, info.failed);
				}
				if (info.total <= info.succeed + info.failed) {
					erase_map.set(info, true);
				}
			}
		}
		for (let [info, v] of erase_map) {
			if (v === undefined) continue;
			this._prepare_map.delete(info);
		}
	},
}, "ALittle.TextureManager");

}