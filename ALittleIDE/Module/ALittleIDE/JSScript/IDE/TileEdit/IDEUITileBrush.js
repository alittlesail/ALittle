{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEUITileBrush = JavaScript.Class(ALittle.DisplayLayout, {
	TCtor : function() {
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-975432877), this, this.HandleProjectOpen);
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-332308624), this, this.HandleProjectClose);
		this._file_select.Init(["png", "jpg"]);
	},
	HandleProjectClose : function(event) {
		this._file_select.SetBasePath(undefined);
	},
	HandleProjectOpen : async function(event) {
		let module_path = ALittle.File_BaseFilePath() + "Module/" + event.name + "/Texture";
		this._file_select.SetBasePath(module_path);
	},
}, "ALittleIDE.IDEUITileBrush");

}