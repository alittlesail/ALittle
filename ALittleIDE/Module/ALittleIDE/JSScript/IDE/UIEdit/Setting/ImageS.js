{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayObjectS === undefined) throw new Error(" extends class:ALittleIDE.DisplayObjectS is undefined");
ALittleIDE.ImageS = JavaScript.Class(ALittleIDE.DisplayObjectS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_image";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayObjectS.LoadNatureBase.call(this);
		this.LoadDefaultNilString("texture_name");
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
	SetTextureName : function(texture_name, revoke_bind) {
		if (texture_name === undefined) {
			return;
		}
		this.ImagePathSelectCallback("texture_name", this.HandleImageTextureNameFOCUSOUT, revoke_bind, texture_name, true);
	},
	HandleFlipSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.flip_rtype;
		this.TypeSelectChange("flip", list, false);
	},
}, "ALittleIDE.ImageS");

}