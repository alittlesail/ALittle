{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name : "ALittle.UIButtonEvent", ns_name : "ALittle", rl_name : "UIButtonEvent", hash_code : -1347278145,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEUIProjectList = JavaScript.Class(ALittle.DisplayLayout, {
	HandleProjectSearchClick : function(event) {
		this._project_scroll_screen.RemoveAllChild();
		let key = this._project_search_key.text;
		let project_map = ALittleIDE.g_IDEConfig.GetConfig("project_map", {});
		let ___OBJECT_1 = project_map;
		for (let k in ___OBJECT_1) {
			let v = ___OBJECT_1[k];
			if (v === undefined) continue;
			if (key === "" || ALittle.String_Find(v, key) !== undefined) {
				let item = ALittleIDE.g_Control.CreateControl("aui_menu_item_button");
				item.text = v;
				item.drag_trans_target = this._project_scroll_screen;
				item.AddEventListener(___all_struct.get(-641444818), this, this.HandleProjectItemRightClick);
				this._project_scroll_screen.AddChild(item);
			}
		}
	},
	HandleProjectItemRightClick : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("打开", this.HandleRightProjectOpen.bind(this, event.target));
		menu.AddItem("关闭", this.HandleRightProjectClose.bind(this, event.target));
		menu.AddItem("移除", this.HandleRightProjectRemove.bind(this, event.target));
		menu.Show();
	},
	HandleRightProjectOpen : async function(target) {
		let project_name = target.text;
		if (!ALittleIDE.g_IDECenter.center.content_edit.IsSaveAll()) {
			let result = await g_AUITool.SaveNotice("提示", "是否保存当前项目?");
			if (result === "YES") {
				ALittleIDE.g_IDECenter.center.content_edit.SaveAllTab();
			}
		}
		let error = ALittleIDE.g_IDEProject.OpenProject(project_name);
		if (error !== undefined) {
			g_AUITool.ShowNotice("错误", error);
		}
	},
	HandleRightProjectRemove : function(target) {
		let project_name = target.text;
		if (ALittleIDE.g_IDEProject.project !== undefined && ALittleIDE.g_IDEProject.project.name === project_name) {
			g_AUITool.ShowNotice("提示", "当前项目正在编辑，请先关闭");
			return;
		}
		this._project_scroll_screen.RemoveChild(target);
		ALittleIDE.g_IDEProject.RemoveProject(project_name);
	},
	HandleRightProjectClose : async function(target) {
		let project_name = target.text;
		if (ALittleIDE.g_IDEProject.project === undefined || ALittleIDE.g_IDEProject.project.name !== project_name) {
			return;
		}
		if (!ALittleIDE.g_IDECenter.center.content_edit.IsSaveAll()) {
			let result = await g_AUITool.SaveNotice("提示", "是否保存当前项目?");
			if (result === "YES") {
				ALittleIDE.g_IDECenter.center.content_edit.SaveAllTab();
			}
		}
		ALittleIDE.g_IDEProject.CloseProject();
	},
}, "ALittleIDE.IDEUIProjectList");

}