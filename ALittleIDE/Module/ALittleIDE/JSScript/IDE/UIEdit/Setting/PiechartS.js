{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.PiechartS = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_piechart";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		this.LoadDefaultNilString("texture_name");
		this.LoadValueData("start_degree");
		this.LoadValueData("end_degree");
	},
	HandleImageTextureNameFOCUSOUT : function(event) {
		this.DefaultNilStringInputChange("texture_name", false);
	},
	HandleImageTextureNameSelect : async function(event) {
		let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(this._tree_logic.user_info.module);
		if (ui_manager === undefined) {
			g_AUITool.ShowNotice("错误", "模块不存在:" + this._tree_logic.user_info.module);
			return;
		}
		ALittleIDE.g_IDEImageSelectDialog.SetBasePath(ui_manager.texture_path);
		let path = await ALittleIDE.g_IDEImageSelectDialog.ShowSelect();
		if (path === undefined) {
			return;
		}
		this.ImagePathSelectCallback("texture_name", this.HandleImageTextureNameFOCUSOUT, undefined, path, true);
	},
	HandleImageStartDegreeFOCUSOUT : function(event) {
		this.ValueNumZInputChange("start_degree", false);
	},
	HandleImageEndDegreeFOCUSOUT : function(event) {
		this.ValueNumZInputChange("end_degree", false);
	},
}, "ALittleIDE.PiechartS");

}