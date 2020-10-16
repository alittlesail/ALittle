{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1755750412, "ALittle.ALittleJsonRPCInfo", {
name : "ALittle.ALittleJsonRPCInfo", ns_name : "ALittle", rl_name : "ALittleJsonRPCInfo", hash_code : 1755750412,
name_list : ["method","param"],
type_list : ["string","any"],
option_map : {}
})
ALittle.RegStruct(1720966934, "ALittle.NewIntentEvent", {
name : "ALittle.NewIntentEvent", ns_name : "ALittle", rl_name : "NewIntentEvent", hash_code : 1720966934,
name_list : ["target","url"],
type_list : ["ALittle.EventDispatcher","string"],
option_map : {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(1452333751, "ALittle.AppLowMemory", {
name : "ALittle.AppLowMemory", ns_name : "ALittle", rl_name : "AppLowMemory", hash_code : 1452333751,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(-1440165311, "ALittle.AppWillEnterBackground", {
name : "ALittle.AppWillEnterBackground", ns_name : "ALittle", rl_name : "AppWillEnterBackground", hash_code : -1440165311,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(-840570937, "ALittle.NotifyJsonRPCEvent", {
name : "ALittle.NotifyJsonRPCEvent", ns_name : "ALittle", rl_name : "NotifyJsonRPCEvent", hash_code : -840570937,
name_list : ["target","method","param"],
type_list : ["ALittle.EventDispatcher","string","any"],
option_map : {}
})
ALittle.RegStruct(812594882, "ALittle.AppWillEnterForeground", {
name : "ALittle.AppWillEnterForeground", ns_name : "ALittle", rl_name : "AppWillEnterForeground", hash_code : 812594882,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(760325696, "ALittle.AppDidEnterForeground", {
name : "ALittle.AppDidEnterForeground", ns_name : "ALittle", rl_name : "AppDidEnterForeground", hash_code : 760325696,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(708183011, "ALittle.NetChangeEvent", {
name : "ALittle.NetChangeEvent", ns_name : "ALittle", rl_name : "NetChangeEvent", hash_code : 708183011,
name_list : ["target","net_type"],
type_list : ["ALittle.EventDispatcher","int"],
option_map : {}
})
ALittle.RegStruct(521107426, "ALittle.AppDidEnterBackground", {
name : "ALittle.AppDidEnterBackground", ns_name : "ALittle", rl_name : "AppDidEnterBackground", hash_code : 521107426,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})

if (ALittle.EventDispatcher === undefined) throw new Error(" extends class:ALittle.EventDispatcher is undefined");
ALittle.OtherSystem = JavaScript.Class(ALittle.EventDispatcher, {
	Ctor : function() {
		this._network_started = false;
		this._system_select_directory = undefined;
		this._system_select_file = undefined;
		this._system_save_file = undefined;
		this._third_share_callback = undefined;
		this._third_login_callback = undefined;
		this._third_login_ing = false;
	},
	HandleWillEnterBackground : function() {
		this.DispatchEvent(___all_struct.get(-1440165311), {});
	},
	HandleDidEnterBackground : function() {
		this.DispatchEvent(___all_struct.get(521107426), {});
	},
	HandleWillEnterForeground : function() {
		this.DispatchEvent(___all_struct.get(812594882), {});
	},
	HandleDidEnterForeground : function() {
		this.DispatchEvent(___all_struct.get(760325696), {});
	},
	HandleLowMemory : function() {
		this.DispatchEvent(___all_struct.get(1452333751), {});
	},
	HandleNewIntent : function(url) {
		let event = {};
		event.url = url;
		this.DispatchEvent(___all_struct.get(1720966934), event);
	},
	HandleALittleJsonRPC : function(json) {
		let [error, content] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, json); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
		if (error !== undefined) {
			ALittle.Log("OtherSystem:HandleALittleJsonRPC:", error, json);
			return;
		}
		if (content.method === undefined) {
			return;
		}
		if (content.param === undefined) {
			return;
		}
		let event = {};
		event.target = this;
		event.method = content.method;
		event.param = content.param;
		this.DispatchEvent(___all_struct.get(-840570937), event);
	},
	SystemSelectDirectory : function(target, init_dir) {
		ALittle.Error("not support SystemSelectDirectory");
	},
	HandleSystemSelectDirectory : function(path) {
		if (this._system_select_directory === undefined) {
			return;
		}
		let tmp = this._system_select_directory;
		this._system_select_directory = undefined;
		let event = {};
		event.target = tmp;
		event.path = path;
		tmp.DispatchEvent(___all_struct.get(1800966813), event);
	},
	SystemSelectFile : function(target, init_dir) {
		ALittle.Error("not support SystemSelectFile");
	},
	HandleSystemSelectFile : function(path) {
		if (this._system_select_file === undefined) {
			return;
		}
		let tmp = this._system_select_file;
		this._system_select_file = undefined;
		let event = {};
		event.target = tmp;
		event.path = path;
		tmp.DispatchEvent(___all_struct.get(124598654), event);
	},
	SystemSaveFile : function(target, file_name, path) {
		ALittle.Error("not support SystemSelectFile");
	},
	HandleSystemSaveFile : function(path) {
		if (this._system_save_file === undefined) {
			return;
		}
		let tmp = this._system_save_file;
		this._system_save_file = undefined;
		let event = {};
		event.target = tmp;
		event.path = path;
		tmp.DispatchEvent(___all_struct.get(-1676610185), event);
	},
}, "ALittle.OtherSystem");

window.A_OtherSystem = ALittle.NewObject(ALittle.OtherSystem);
}