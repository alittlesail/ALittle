{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.Grid9S === undefined) throw new Error(" extends class:ALittleIDE.Grid9S is undefined");
ALittleIDE.Grid9ImageS = JavaScript.Class(ALittleIDE.Grid9S, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_grid9image";
	},
	LoadNatureBase : function() {
		ALittleIDE.Grid9S.LoadNatureBase.call(this);
		this.LoadDefaultNilString("texture_name");
		this.LoadEnumData("flip", ALittleIDE.g_IDEEnum.flip_type);
	},
	HandleImageTextureNameFOCUSOUT : function(event) {
		this.DefaultNilStringInputChange("texture_name", false);
		this.HandleAutoCut(event);
	},
	HandleImageTextureNameSelect : function(event) {
		let func = this.ImagePathSelectCallback.bind(this, "texture_name", this.HandleImageTextureNameFOCUSOUT, undefined);
		ALittleIDE.g_IDEAttrImageDialog.ShowDialog(undefined, func);
	},
	HandleFlipSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.flip_rtype;
		this.TypeSelectChange("flip", list, false);
	},
	HandleAutoCut : function(event) {
		let image_path = this._texture_name.text;
		let display_info = ALittleIDE.IDEUtility_GenerateGrid9ImageInfo(ALittleIDE.g_IDEProject.project.base_path + "Texture/", image_path);
		if (display_info === undefined) {
			return;
		}
		let revoke_bind = ALittle.NewObject(ALittleIDE.IDERevokeBind);
		this._left_size.text = display_info.left_size;
		this.ValueNumInputChange("left_size", false, revoke_bind);
		this._right_size.text = display_info.right_size;
		this.ValueNumInputChange("right_size", false, revoke_bind);
		this._top_size.text = display_info.top_size;
		this.ValueNumInputChange("top_size", false, revoke_bind);
		this._bottom_size.text = display_info.bottom_size;
		this.ValueNumInputChange("bottom_size", false, revoke_bind);
		this._tab_child.revoke_list.PushRevoke(revoke_bind);
	},
}, "ALittleIDE.Grid9ImageS");

}