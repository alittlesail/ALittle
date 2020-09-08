{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.RichAreaS = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_richarea";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		this.LoadValueData("line_spacing");
		this.LoadValueData("max_line_count");
		this.LoadTypeSelectData("halign", ALittleIDE.g_IDEEnum.HALIGN_type);
		this.LoadTypeSelectData("valign", ALittleIDE.g_IDEEnum.VALIGN_type);
		this.LoadShowTypeData("display_list");
	},
	HandleLineSpacingFOCUSOUT : function(event) {
		this.ValueNumInputChange("line_spacing", true);
	},
	HandleMaxLineCountFOCUSOUT : function(event) {
		this.ValueNumInputChange("max_line_count", true);
	},
	HandleHalignSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.HALIGN_rtype;
		this.TypeSelectChange("halign", list, false);
	},
	HandleValignSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.VALIGN_rtype;
		this.TypeSelectChange("valign", list, false);
	},
	HandleDisplayListFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.TableDataSet("display_list", true);
	},
}, "ALittleIDE.RichAreaS");

}