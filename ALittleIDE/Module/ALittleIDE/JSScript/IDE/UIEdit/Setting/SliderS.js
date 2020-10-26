{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.SliderS = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_slider";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		this.LoadTypeSelectData("type", ALittleIDE.g_IDEEnum.hv_type);
		this.LoadTypeSelectData("fixed", ALittleIDE.g_IDEEnum.fix_type);
		this.LoadValueData("grade");
		this.LoadValueData("offset_rate");
		this.LoadShowTypeDataForExtends("bar_button");
		this.LoadShowTypeDataForImage("bar_background");
	},
	HandleSliderTypeSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.hv_rtype;
		this.TypeSelectChange("type", list, false);
	},
	HandleOffsetRateFOCUSOUT : function(event) {
		this.Z2OValueInputChange("offset_rate", false);
	},
	HandleGradeFOCUSOUT : function(event) {
		this.ValueNumInputChange("grade", false);
	},
	HandleFixedSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.fix_rtype;
		this.TypeSelectChange("fixed", list, false);
	},
	HandleBarButtonFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForExtends("bar_button", this._bar_button.text, false);
	},
	HandleBarBackFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("bar_background", this._bar_background.text, this._bar_background_grid9.selected, false);
	},
	HandleBarBackSelect : async function(event) {
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
		this.ImagePathSelectCallback("bar_background", this.HandleBarBackFOCUSOUT, undefined, path, false);
	},
}, "ALittleIDE.SliderS");

}