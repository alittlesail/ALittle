{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.ScrollListS = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_scrolllist";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		let list = ALittleIDE.g_IDEEnum.hv_type;
		this.LoadTypeSelectData("type", list);
		this.LoadShowTypeDataForExtends("right_scrollbar");
		this.LoadValueData("gap");
		this.LoadBoolData("clip_atonce", false, ALittleIDE.g_IDEEnum.yn_type);
		this.LoadBoolData("open_extends_drag", true, ALittleIDE.g_IDEEnum.yn_type);
	},
	HandleRightSFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForExtends("right_scrollbar", this._right_scrollbar.text, false);
	},
	HandleScrollListTypeSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.hv_rtype;
		this.TypeSelectChange("type", list, true);
	},
	HandleGapFOCUSOUT : function(event) {
		this.ValueNumInputChange("gap", false);
	},
	HandleClipClick : function(event) {
		this._object.AdjustScrollBar();
		this._object.RefreshClipDisLine();
	},
	HandleClipAtonceSELECT_CHANGE : function(event) {
		this.BoolSelectChange("clip_atonce", false, ALittleIDE.g_IDEEnum.yn_type);
	},
	HandleHandOpenExtendsDragSELECT_CHANGE : function(event) {
		this.BoolSelectChange("open_extends_drag", false, ALittleIDE.g_IDEEnum.yn_type);
	},
}, "ALittleIDE.ScrollListS");

}