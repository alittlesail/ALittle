{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(-1652314301, "ALittle.ModuleShortInfo", {
name : "ALittle.ModuleShortInfo", ns_name : "ALittle", rl_name : "ModuleShortInfo", hash_code : -1652314301,
name_list : ["title","icon","width_type","width_value","height_type","height_value"],
type_list : ["string","string","int","int","int","int"],
option_map : {}
})
ALittle.RegStruct(1376035901, "ALittle.ModuleInfo", {
name : "ALittle.ModuleInfo", ns_name : "ALittle", rl_name : "ModuleInfo", hash_code : 1376035901,
name_list : ["name","crypt_mode","control","module","plugin_loaded","module_loaded","browser_loaded","layer_group","browser_setup","browser_addmodule","browser_shutdown","module_setup","module_shutdown","module_getinfo","plugin_setup","plugin_shutdown"],
type_list : ["string","bool","ALittle.ControlSystem","any","bool","bool","bool","ALittle.DisplayLayout","Functor<(ALittle.DisplayLayout,ALittle.ControlSystem,string,string)>","Functor<(string,ALittle.DisplayLayout,ALittle.ModuleShortInfo):bool>","Functor<()>","Functor<(ALittle.DisplayLayout,ALittle.ControlSystem,string,string)>","Functor<()>","Functor<(ALittle.ControlSystem,string):ALittle.ModuleShortInfo>","Functor<await(ALittle.ControlSystem,string,string)>","Functor<()>"],
option_map : {}
})

ALittle.ModuleSystem = JavaScript.Class(undefined, {
	Ctor : function() {
		this._name_module_map = {};
		this._main_module = undefined;
	},
	GetMainModuleName : function() {
		if (this._main_module === undefined) {
			return undefined;
		}
		return this._main_module.name;
	},
	GetDebugInfo : function() {
		return this._debug_info;
	},
	LoadModuleImpl : function(module_base_path, name) {
		return new Promise((async function(___COROUTINE, ___) {
			let info = {};
			info.name = name;
			if (window[name] === undefined) {
				await Require(module_base_path, "JSScript/Main");
			}
			info.module = window[name];
			if (info.module === undefined) {
				___COROUTINE(undefined); return;
			}
			info.crypt_mode = false;
			info.control = ALittle.NewObject(ALittle.ControlSystem, name, info.crypt_mode);
			await info.control.RegisterInfoByHttp();
			this._name_module_map[name] = info;
			info.browser_setup = info.module["__Browser_Setup"];
			info.browser_addmodule = info.module["__Browser_AddModule"];
			info.browser_shutdown = info.module["__Browser_Shutdown"];
			info.module_setup = info.module["__Module_Setup"];
			info.module_shutdown = info.module["__Module_Shutdown"];
			info.module_getinfo = info.module["__Module_GetInfo"];
			info.plugin_setup = info.module["__Plugin_Setup"];
			info.plugin_shutdown = info.module["__Plugin_Shutdown"];
			let control = info.control;
			if (this._main_module !== undefined) {
				control = this._main_module.control;
			}
			info.layer_group = ALittle.NewObject(ALittle.DisplayLayout, control);
			___COROUTINE(info); return;
		}).bind(this));
	},
	RemoveModule : function(name) {
		if (this._main_module !== undefined && this._main_module.name === name) {
			return false;
		}
		let info = this._name_module_map[name];
		if (info === undefined) {
			return false;
		}
		let module_shutdown = info.module_shutdown;
		if (module_shutdown !== undefined) {
			module_shutdown();
		}
		delete this._name_module_map[name];
		A_LayerManager.RemoveChild(info.layer_group);
		delete window[name];
		return true;
	},
	LoadPlugin : function(module_name) {
		return new Promise((async function(___COROUTINE, ___) {
			let module_base_path = "Module/" + module_name + "/";
			if (module_name === undefined) {
				ALittle.Log("module_name is null!");
				___COROUTINE(undefined); return;
			}
			let info = this._name_module_map[module_name];
			if (info === undefined) {
				info = await this.LoadModuleImpl(module_base_path, module_name);
				if (info === undefined) {
					ALittle.Log("Module:" + module_name + " load failed!");
					___COROUTINE(undefined); return;
				}
			}
			if (info.plugin_loaded) {
				___COROUTINE(info.control); return;
			}
			this._main_module.control.RegisterPlugin(module_name, info.control);
			let setup_func = info.plugin_setup;
			if (setup_func === undefined) {
				ALittle.Log("can't find Plugin_Setup funciton in Module:" + module_name);
				___COROUTINE(undefined); return;
			}
			info.plugin_loaded = true;
			await setup_func(info.control, module_base_path, module_base_path + "JSScript/");
			___COROUTINE(info.control); return;
		}).bind(this));
	},
	LoadModule : function(module_base_path, module_name) {
		return new Promise((async function(___COROUTINE, ___) {
			if (module_name === undefined) {
				ALittle.Log("module_name is null!");
				___COROUTINE(false); return;
			}
			let info = this._name_module_map[module_name];
			if (info === undefined) {
				info = await this.LoadModuleImpl(module_base_path, module_name);
				if (info === undefined) {
					ALittle.Log("Module:" + module_name + " load failed!");
					___COROUTINE(false); return;
				}
			}
			if (info.module_loaded) {
				ALittle.Log(module_name + ":__Module_Setup already invoked!");
				___COROUTINE(false); return;
			}
			let setup_func = info.module_setup;
			if (setup_func === undefined) {
				ALittle.Log("can't find Module_Setup funciton in Module:" + module_name);
				___COROUTINE(false); return;
			}
			info.module_loaded = true;
			if (this._main_module.name !== module_name) {
				let result = false;
				if (this._main_module !== undefined && this._main_module.browser_addmodule !== undefined) {
					let module_info = undefined;
					if (info.module_getinfo !== undefined) {
						module_info = info.module_getinfo(info.control, module_base_path);
					}
					result = this._main_module.browser_addmodule(module_name, info.layer_group, module_info);
				}
				if (!result) {
					A_LayerManager.AddChild(info.layer_group, A_LayerManager.group_count - 1);
				}
			}
			setup_func(info.layer_group, info.control, module_base_path, module_base_path + "JSScript/");
			___COROUTINE(true); return;
		}).bind(this));
	},
	MainSetup : async function(base_path, module_name, debug_info) {
		if (this._main_module !== undefined) {
			return;
		}
		if (module_name === undefined) {
			module_name = ALittle.File_ReadTextFromFile("Module/Enter.ali", false);
		}
		if (module_name === undefined) {
			ALittle.Log("Load Enter.ali failed!");
			return;
		}
		let info = await this.LoadModuleImpl(base_path, module_name);
		if (info === undefined) {
			ALittle.Log("Module:" + module_name + " load failed!");
			return;
		}
		A_LayerManager.AddChild(info.layer_group, A_LayerManager.group_count - 1);
		this._main_module = info;
		this._debug_info = debug_info;
		let module_base_path = "Module/" + module_name + "/";
		this._main_module.browser_loaded = true;
		let setup_func = this._main_module.browser_setup;
		if (setup_func === undefined) {
			await this.LoadModule(module_base_path, this._main_module.name);
			return;
		}
		setup_func(this._main_module.layer_group, this._main_module.control, module_base_path, module_base_path + "JSScript/");
	},
	MainShutdown : function() {
		if (this._main_module === undefined) {
			return;
		}
		let ___OBJECT_1 = this._name_module_map;
		for (let name in ___OBJECT_1) {
			let info = ___OBJECT_1[name];
			if (info === undefined) continue;
			let shutdown_func = info.module_shutdown;
			if (shutdown_func !== undefined && info.module_loaded) {
				let error = (function() { try { shutdown_func.call(); return undefined; } catch (___ERROR) { return ___ERROR.message; } }).call(this);
				if (error !== undefined) {
					ALittle.Log("ModuleSystem:MainShutdown invoke __Module_Shutdown error:", error);
				}
			}
			shutdown_func = info.plugin_shutdown;
			if (shutdown_func !== undefined && info.plugin_loaded) {
				let error = (function() { try { shutdown_func.call(); return undefined; } catch (___ERROR) { return ___ERROR.message; } }).call(this);
				if (error !== undefined) {
					ALittle.Log("ModuleSystem:MainShutdown invoke __Plugin_Shutdown error:", error);
				}
			}
		}
		let shutdown_func = this._main_module.browser_shutdown;
		if (shutdown_func === undefined) {
			return;
		}
		shutdown_func();
	},
}, "ALittle.ModuleSystem");

window.A_ModuleSystem = ALittle.NewObject(ALittle.ModuleSystem);
}