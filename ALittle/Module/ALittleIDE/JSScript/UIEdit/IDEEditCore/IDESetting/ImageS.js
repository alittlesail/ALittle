{
if (typeof ALittleIDE === "undefined") ALittleIDE = {};


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
	HandleImageTextureNameSelect : function(event) {
		let func = this.ImagePathSelectCallback.bind(this, "texture_name", this.HandleImageTextureNameFOCUSOUT, undefined);
		ALittleIDE.g_IDEAttrImageDialog.ShowDialog(undefined, func);
	},
	SetTextureName : function(texture_name, revoke_bind) {
		if (texture_name === undefined) {
			return;
		}
		this.ImagePathSelectCallback("texture_name", this.HandleImageTextureNameFOCUSOUT, revoke_bind, texture_name);
	},
	HandleFlipSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.flip_rtype;
		this.TypeSelectChange("flip", list, false);
	},
}, "ALittleIDE.ImageS");

}