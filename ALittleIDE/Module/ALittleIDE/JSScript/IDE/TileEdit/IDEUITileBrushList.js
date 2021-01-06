{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1206110359, "AUIPlugin.AUIFileSelectFileClickUIEvent", {
name : "AUIPlugin.AUIFileSelectFileClickUIEvent", ns_name : "AUIPlugin", rl_name : "AUIFileSelectFileClickUIEvent", hash_code : 1206110359,
name_list : ["target","path","ctrl"],
type_list : ["ALittle.DisplayObject","string","bool"],
option_map : {}
})
ALittle.RegStruct(-989784577, "AUIPlugin.AUIFileSelectDirClickUIEvent", {
name : "AUIPlugin.AUIFileSelectDirClickUIEvent", ns_name : "AUIPlugin", rl_name : "AUIFileSelectDirClickUIEvent", hash_code : -989784577,
name_list : ["target","path","ctrl"],
type_list : ["ALittle.DisplayObject","string","bool"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEUITileBrushList = JavaScript.Class(ALittle.DisplayLayout, {
	TCtor : function() {
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-975432877), this, this.HandleProjectOpen);
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-332308624), this, this.HandleProjectClose);
		this._file_select.Init(["png", "jpg"]);
		this._file_select.AddEventListener(___all_struct.get(1206110359), this, this.HandleImageSelect);
		this._file_select.AddEventListener(___all_struct.get(-989784577), this, this.HandleImageListSelect);
	},
	HandleProjectClose : function(event) {
		this._file_select.SetBasePath(undefined);
	},
	HandleProjectOpen : async function(event) {
		let module_path = ALittle.File_BaseFilePath() + "Module/" + event.name + "/Texture";
		this._file_select.SetBasePath(module_path);
	},
	HandleImageSelect : function(event) {
		let module_path_list = [];
		let tex_path_list = [];
		module_path_list[1 - 1] = this._file_select.base_path + "/" + event.path;
		tex_path_list[1 - 1] = event.path;
		ALittleIDE.g_IDECenter.center.tile_brush_edit.AddBrushList(module_path_list, tex_path_list, event.ctrl);
	},
	HandleImageListSelect : function(event) {
		let module_path_list = [];
		let tex_path_list = [];
		let path_prefix = this._file_select.base_path + "/";
		let name_map = ALittle.File_GetNameListByDir(path_prefix + event.path);
		let ___OBJECT_1 = name_map;
		for (let name in ___OBJECT_1) {
			let attr = ___OBJECT_1[name];
			if (attr === undefined) continue;
			if (!attr.directory) {
				ALittle.List_Push(module_path_list, path_prefix + event.path + "/" + name);
				ALittle.List_Push(tex_path_list, event.path + "/" + name);
			}
		}
		ALittleIDE.g_IDECenter.center.tile_brush_edit.AddBrushList(module_path_list, tex_path_list, event.ctrl);
	},
}, "ALittleIDE.IDEUITileBrushList");

}