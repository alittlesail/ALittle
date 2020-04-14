{
if (typeof ALittleIDE === "undefined") ALittleIDE = {};


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
	HandleImageTextureNameSelect : function(event) {
		let func = this.ImagePathSelectCallback.bind(this, "texture_name", this.HandleImageTextureNameFOCUSOUT, undefined);
		ALittleIDE.g_IDEAttrImageDialog.ShowDialog(undefined, func);
	},
	HandleImageStartDegreeFOCUSOUT : function(event) {
		this.ValueNumZInputChange("start_degree", false);
	},
	HandleImageEndDegreeFOCUSOUT : function(event) {
		this.ValueNumZInputChange("end_degree", false);
	},
}, "ALittleIDE.PiechartS");

}