{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayObjectS === undefined) throw new Error(" extends class:ALittleIDE.DisplayObjectS is undefined");
ALittleIDE.SpriteS = JavaScript.Class(ALittleIDE.DisplayObjectS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_sprite";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayObjectS.LoadNatureBase.call(this);
		this.LoadDefaultNilString("texture_name");
		this.LoadValueData("row_count");
		this.LoadValueData("col_count");
		this.LoadValueData("row_index");
		this.LoadValueData("col_index");
		this.LoadEnumData("flip", ALittleIDE.g_IDEEnum.flip_type);
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
	HandleRowCountFOCUSOUT : function(event) {
		this.ValueNumInputChange("row_count", false);
	},
	HandleColCountFOCUSOUT : function(event) {
		this.ValueNumInputChange("col_count", false);
	},
	HandleRowIndexFOCUSOUT : function(event) {
		this.ValueNumInputChange("row_index", false);
	},
	HandleColIndexFOCUSOUT : function(event) {
		this.ValueNumInputChange("col_index", false);
	},
	HandleFlipSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.flip_rtype;
		this.TypeSelectChange("flip", list, false);
	},
}, "ALittleIDE.SpriteS");

}