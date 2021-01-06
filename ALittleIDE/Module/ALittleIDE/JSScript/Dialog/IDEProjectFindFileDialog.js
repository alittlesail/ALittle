{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name : "ALittle.UIClickEvent", ns_name : "ALittle", rl_name : "UIClickEvent", hash_code : -449066808,
name_list : ["target","is_drag","count"],
type_list : ["ALittle.DisplayObject","bool","int"],
option_map : {}
})

ALittleIDE.IDEProjectFindFileDialog = JavaScript.Class(undefined, {
	ShowFindFile : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("错误", "当前没有打开的项目");
			return;
		}
		if (this._project_find_file_dialog === undefined) {
			this._project_find_file_dialog = ALittleIDE.g_Control.CreateControl("ide_find_file_dialog", this);
			this._project_find_file_dialog.x = (A_UISystem.view_width - this._project_find_file_dialog.width) / 2;
			this._project_find_file_dialog.y = (A_UISystem.view_height - this._project_find_file_dialog.height) / 2;
			ALittleIDE.g_DialogLayer.AddChild(this._project_find_file_dialog);
		}
		this._project_find_file_dialog.visible = true;
		this._project_find_file_dialog.MoveToTop();
		this._find_input.DelayFocus();
	},
	HideDialog : function() {
		if (this._project_find_file_dialog === undefined) {
			return;
		}
		this._project_find_file_dialog.visible = false;
	},
	IsShow : function() {
		if (this._project_find_file_dialog === undefined) {
			return false;
		}
		return this._project_find_file_dialog.visible;
	},
	HandleEnterKeyClick : function(event) {
		this.HandleSearchClick(undefined);
	},
	HandleSearchClick : async function(event) {
		this._file_scroll_screen.RemoveAllChild();
		let text = ALittle.String_Trim(this._find_input.text);
		if (text === undefined) {
			return;
		}
		if (ALittleIDE.g_IDEProject.project === undefined) {
			return;
		}
		if (ALittleIDE.g_IDEProject.project.code === undefined) {
			return;
		}
		let file_list = await ALittleIDE.g_IDEProject.project.code.FindFile(text);
		let ___OBJECT_1 = file_list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let file_path = ___OBJECT_1[index - 1];
			if (file_path === undefined) break;
			let item = ALittleIDE.g_Control.CreateControl("scroll_screen_item_checkbutton");
			item.AddEventListener(___all_struct.get(-449066808), this, this.HandleItemClick);
			item.text = file_path;
			item._user_data = file_path;
			this._file_scroll_screen.AddChild(item);
		}
	},
	HandleItemClick : function(event) {
		let code_child = ALittleIDE.g_IDECenter.center.code_list.OpenByFullPath(event.target._user_data, 1, 1, 1, 1);
		if (code_child === undefined) {
			return;
		}
		code_child.FindText(this._find_input.text);
	},
}, "ALittleIDE.IDEProjectFindFileDialog");

ALittleIDE.g_IDEProjectFindFileDialog = ALittle.NewObject(ALittleIDE.IDEProjectFindFileDialog);
}