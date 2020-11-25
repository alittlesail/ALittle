{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(2117383637, "AUIPlugin.AUIFileSelectFileEvent", {
name : "AUIPlugin.AUIFileSelectFileEvent", ns_name : "AUIPlugin", rl_name : "AUIFileSelectFileEvent", hash_code : 2117383637,
name_list : ["target","info"],
type_list : ["ALittle.DisplayObject","AUIPlugin.AUIFileTreeUserInfo"],
option_map : {}
})
ALittle.RegStruct(-2082217254, "AUIPlugin.AUIFileCreateFileEvent", {
name : "AUIPlugin.AUIFileCreateFileEvent", ns_name : "AUIPlugin", rl_name : "AUIFileCreateFileEvent", hash_code : -2082217254,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
option_map : {}
})
ALittle.RegStruct(1826926916, "ALittleIDE.IDETileTreeUserInfo", {
name : "ALittleIDE.IDETileTreeUserInfo", ns_name : "ALittleIDE", rl_name : "IDETileTreeUserInfo", hash_code : 1826926916,
name_list : ["info","module_name"],
type_list : ["AUIPlugin.AUIFileTreeUserInfo","string"],
option_map : {}
})
ALittle.RegStruct(-1718818319, "AUIPlugin.AUIFileDeleteDirEvent", {
name : "AUIPlugin.AUIFileDeleteDirEvent", ns_name : "AUIPlugin", rl_name : "AUIFileDeleteDirEvent", hash_code : -1718818319,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
option_map : {}
})
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
ALittle.RegStruct(-686652419, "AUIPlugin.AUIFileTreeUserInfo", {
name : "AUIPlugin.AUIFileTreeUserInfo", ns_name : "AUIPlugin", rl_name : "AUIFileTreeUserInfo", hash_code : -686652419,
name_list : ["path","name","root","group","on_right_menu","on_select_file","on_delete_file","on_create_file","on_delete_dir"],
type_list : ["string","string","bool","Map<ALittle.TextRadioButton,bool>","Functor<(AUIPlugin.AUIFileTreeUserInfo,AUIPlugin.AUIRightMenu)>","Functor<(AUIPlugin.AUIFileTreeUserInfo)>","Functor<(string)>","Functor<(string)>","Functor<(string)>"],
option_map : {}
})
ALittle.RegStruct(-545221029, "AUIPlugin.AUIFileDeleteFileEvent", {
name : "AUIPlugin.AUIFileDeleteFileEvent", ns_name : "AUIPlugin", rl_name : "AUIFileDeleteFileEvent", hash_code : -545221029,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
option_map : {}
})

if (AUIPlugin.AUIFileTreeLayout === undefined) throw new Error(" extends class:AUIPlugin.AUIFileTreeLayout is undefined");
ALittleIDE.IDEUITileList = JavaScript.Class(AUIPlugin.AUIFileTreeLayout, {
	TCtor : function() {
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-975432877), this, this.HandleProjectOpen);
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-332308624), this, this.HandleProjectClose);
		this.AddEventListener(___all_struct.get(2117383637), this, this.HandleSelectFileEvent);
		this.AddEventListener(___all_struct.get(-545221029), this, this.HandleDeleteFileEvent);
		this.AddEventListener(___all_struct.get(-2082217254), this, this.HandleCreateFileEvent);
		this.AddEventListener(___all_struct.get(-1718818319), this, this.HandleDeleteDirEvent);
	},
	HandleSelectFileEvent : function(event) {
		let info = {};
		info.info = event.info;
		info.module_name = ALittleIDE.g_IDEProject.project.name;
		ALittleIDE.g_IDECenter.center.content_edit.StartEditTileBySelect(info.info.name, info);
	},
	HandleDeleteFileEvent : function(event) {
	},
	HandleCreateFileEvent : function(event) {
	},
	HandleDeleteDirEvent : function(event) {
	},
	OnRightMenu : function(user_info, menu) {
	},
	HandleProjectClose : function(event) {
		this._file_scroll_screen.RemoveAllChild();
	},
	HandleProjectOpen : async function(event) {
		let module_path = ALittle.File_BaseFilePath() + "Module/" + event.name + "/Tile";
		this.SetRoot(module_path, this.OnRightMenu.bind(this));
	},
}, "ALittleIDE.IDEUITileList");

}