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
ALittleIDE.IDEUIProjectDropdown = JavaScript.Class(ALittle.DisplayLayout, {
	TCtor : function() {
		this.UpdateProjectList();
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-975432877), this, this.HandleProjectOpen);
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-332308624), this, this.HandleProjectClose);
	},
	HandleProjectOpen : function(event) {
		this.UpdateProjectList();
	},
	HandleProjectClose : function(event) {
		this.UpdateProjectList();
	},
	UpdateProjectList : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			this._current_project_name.text = "当前没有打开的项目";
		} else {
			this._current_project_name.text = ALittleIDE.g_IDEProject.project.name;
		}
		let data_list = [];
		let data_list_count = 0;
		let project_map = ALittleIDE.g_IDEConfig.GetConfig("project_map", {});
		let ___OBJECT_1 = project_map;
		for (let k in ___OBJECT_1) {
			let v = ___OBJECT_1[k];
			if (v === undefined) continue;
			++ data_list_count;
			data_list[data_list_count - 1] = v;
		}
		ALittle.List_Sort(data_list);
		let text = this._current_project_name.text;
		this._current_project_name.data_list = data_list;
		this._current_project_name.text = text;
	},
	HandlePeojectSelectChange : async function(event) {
		let name = "";
		if (ALittleIDE.g_IDEProject.project !== undefined) {
			name = ALittleIDE.g_IDEProject.project.name;
		}
		let new_name = event.target.text;
		if (new_name === name) {
			return;
		}
		if (ALittleIDE.g_IDECenter.center.content_edit.IsSaveAll()) {
			let error = ALittleIDE.g_IDEProject.OpenProject(new_name);
			if (error !== undefined) {
				g_AUITool.ShowNotice("错误", error);
			}
			return;
		}
		event.target.text = name;
		let result = await g_AUITool.SaveNotice("提示", "是否保存当前项目?");
		if (result === "YES") {
			ALittleIDE.g_IDECenter.center.content_edit.SaveAllTab();
		}
		let error = ALittleIDE.g_IDEProject.OpenProject(new_name);
		if (error !== undefined) {
			g_AUITool.ShowNotice("错误", error);
		}
	},
}, "ALittleIDE.IDEUIProjectDropdown");

}