{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayObjectS === undefined) throw new Error(" extends class:ALittleIDE.DisplayObjectS is undefined");
ALittleIDE.VertexImageS = JavaScript.Class(ALittleIDE.DisplayObjectS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_verteximage";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayObjectS.LoadNatureBase.call(this);
		this.LoadDefaultNilString("texture_name");
		this.LoadValueData("u1");
		this.LoadValueData("v1");
		this.LoadValueData("u2");
		this.LoadValueData("v2");
		this.LoadValueData("u3");
		this.LoadValueData("v3");
		this.LoadValueData("u4");
		this.LoadValueData("v4");
		this.LoadValueData("x1");
		this.LoadValueData("y1");
		this.LoadValueData("x2");
		this.LoadValueData("y2");
		this.LoadValueData("x3");
		this.LoadValueData("y3");
		this.LoadValueData("x4");
		this.LoadValueData("y4");
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
	HandleU1FOCUSOUT : function(event) {
		this.ValueNumInputChange("u1", true);
	},
	HandleV1FOCUSOUT : function(event) {
		this.ValueNumInputChange("v1", true);
	},
	HandleU2FOCUSOUT : function(event) {
		this.ValueNumInputChange("u2", true);
	},
	HandleV2FOCUSOUT : function(event) {
		this.ValueNumInputChange("v2", true);
	},
	HandleU3FOCUSOUT : function(event) {
		this.ValueNumInputChange("u3", true);
	},
	HandleV3FOCUSOUT : function(event) {
		this.ValueNumInputChange("v3", true);
	},
	HandleU4FOCUSOUT : function(event) {
		this.ValueNumInputChange("u4", true);
	},
	HandleV4FOCUSOUT : function(event) {
		this.ValueNumInputChange("v4", true);
	},
	HandleX1FOCUSOUT : function(event) {
		this.ValueNumInputChange("x1", true);
	},
	HandleY1FOCUSOUT : function(event) {
		this.ValueNumInputChange("y1", true);
	},
	HandleX2FOCUSOUT : function(event) {
		this.ValueNumInputChange("x2", true);
	},
	HandleY2FOCUSOUT : function(event) {
		this.ValueNumInputChange("y2", true);
	},
	HandleX3FOCUSOUT : function(event) {
		this.ValueNumInputChange("x3", true);
	},
	HandleY3FOCUSOUT : function(event) {
		this.ValueNumInputChange("y3", true);
	},
	HandleX4FOCUSOUT : function(event) {
		this.ValueNumInputChange("x4", true);
	},
	HandleY4FOCUSOUT : function(event) {
		this.ValueNumInputChange("y4", true);
	},
}, "ALittleIDE.VertexImageS");

}