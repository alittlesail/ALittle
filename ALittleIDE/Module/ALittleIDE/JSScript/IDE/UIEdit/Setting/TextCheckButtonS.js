{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.DisplayLayoutS === undefined) throw new Error(" extends class:ALittleIDE.DisplayLayoutS is undefined");
ALittleIDE.TextCheckButtonS = JavaScript.Class(ALittleIDE.DisplayLayoutS, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_textcheckbutton";
	},
	LoadNatureBase : function() {
		ALittleIDE.DisplayLayoutS.LoadNatureBase.call(this);
		this.LoadValueData("text");
		this.LoadEnumData("text_x_type", ALittleIDE.g_IDEEnum.xy_type);
		this.LoadValueData("text_x_value");
		this.LoadBoolData("selected", false, ALittleIDE.g_IDEEnum.yn_type);
		this.LoadShowTypeDataForImage("show_up");
		this.LoadShowTypeDataForImage("show_over");
		this.LoadShowTypeDataForImage("show_down");
		this.LoadShowTypeDataForImage("show_disabled");
		this.LoadShowTypeDataForImage("show_selected_up");
		this.LoadShowTypeDataForImage("show_selected_over");
		this.LoadShowTypeDataForImage("show_selected_down");
		this.LoadShowTypeDataForImage("show_selected_disabled");
		this.LoadShowTypeNoNilData("show_text");
		this.LoadShowTypeNoNilData("show_over_text");
		this.LoadShowTypeNoNilData("show_down_text");
		this.LoadShowTypeNoNilData("show_disabled_text");
		this.LoadShowTypeNoNilData("show_selected_text");
		this.LoadShowTypeNoNilData("show_selected_over_text");
		this.LoadShowTypeNoNilData("show_selected_down_text");
		this.LoadShowTypeNoNilData("show_selected_disabled_text");
	},
	HandleMTextFOCUSOUT : function(event) {
		this.DefaultNoStringInputChange("text", false);
		this._tree_logic.UpdateDesc();
	},
	HandleTextXTypeSELECT_CHANGE : function(event) {
		let object = this._object;
		let target_x = object.text_x_type;
		let new_x = target_x;
		let list = ALittleIDE.g_IDEEnum.xy_rtype;
		let revoke_bind = ALittle.NewObject(ALittle.RevokeBind);
		this.TypeSelectChange("text_x_type", list, false, revoke_bind);
	},
	HandleTextXValueFOCUSOUT : function(event) {
		this._base.text_x_value = undefined;
		this.ValueNumInputChange("text_x_value", true);
	},
	HandleSelectedSELECT_CHANGE : function(event) {
		this.BoolSelectChange("selected", false, ALittleIDE.g_IDEEnum.yn_type);
	},
	HandleShowUpFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_up", this._show_up.text, this._show_up_grid9.selected, false);
	},
	HandleShowUpSelect : async function(event) {
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
		this.ImagePathSelectCallback("show_up", this.HandleShowUpFOCUSOUT, undefined, path, true);
	},
	HandleShowOverFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_over", this._show_over.text, this._show_over_grid9.selected, false);
	},
	HandleShowOverSelect : async function(event) {
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
		this.ImagePathSelectCallback("show_over", this.HandleShowOverFOCUSOUT, undefined, path, true);
	},
	HandleShowDownFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_down", this._show_down.text, this._show_down_grid9.selected, false);
	},
	HandleShowDownSelect : async function(event) {
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
		this.ImagePathSelectCallback("show_down", this.HandleShowDownFOCUSOUT, undefined, path, true);
	},
	HandleShowDisabledFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_disabled", this._show_disabled.text, this._show_disabled_grid9.selected, false);
	},
	HandleShowDisabledSelect : async function(event) {
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
		this.ImagePathSelectCallback("show_disabled", this.HandleShowDisabledFOCUSOUT, undefined, path, true);
	},
	HandleShowSUpFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_selected_up", this._show_selected_up.text, this._show_selected_up_grid9.selected, false);
	},
	HandleShowSUpSelect : async function(event) {
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
		this.ImagePathSelectCallback("show_selected_up", this.HandleShowSUpFOCUSOUT, undefined, path, true);
	},
	HandleShowSOverFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_selected_over", this._show_selected_over.text, this._show_selected_over_grid9.selected, false);
	},
	HandleShowSOverSelect : async function(event) {
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
		this.ImagePathSelectCallback("show_selected_over", this.HandleShowSOverFOCUSOUT, undefined, path, true);
	},
	HandleShowSDownFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_selected_down", this._show_selected_down.text, this._show_selected_down_grid9.selected, false);
	},
	HandleShowSDownSelect : async function(event) {
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
		this.ImagePathSelectCallback("show_selected_down", this.HandleShowSDownFOCUSOUT, undefined, path, true);
	},
	HandleShowSDisabledFOCUSOUT : function(event) {
		if (event.target._user_data !== undefined) {
			if (event.target._user_data === event.target.text) {
				return;
			}
			event.target._user_data = event.target.text;
		}
		this.RemoverToNilShowSetForImage("show_selected_disabled", this._show_selected_disabled.text, this._show_selected_disabled_grid9.selected, false);
	},
	HandleShowSDisabledSelect : async function(event) {
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
		this.ImagePathSelectCallback("show_selected_disabled", this.HandleShowSDisabledFOCUSOUT, undefined, path, true);
	},
	HandleShowTextFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_text", false);
	},
	HandleShowTextClear : function(event) {
		this.RemoverToNilShowSet("show_text", "", false);
	},
	HandleShowOverTextClear : function(event) {
		this.RemoverToNilShowSet("show_over_text", "", false);
	},
	HandleShowOverTextFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_over_text", false);
	},
	HandleShowOverTextClear : function(event) {
		this.RemoverToNilShowSet("show_over_text", "", false);
	},
	HandleShowDownTextFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_down_text", false);
	},
	HandleShowDownTextClear : function(event) {
		this.RemoverToNilShowSet("show_down_text", "", false);
	},
	HandleShowDisabledTextFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_disabled_text", false);
	},
	HandleShowDisabledTextClear : function(event) {
		this.RemoverToNilShowSet("show_disabled_text", "", false);
	},
	HandleShowSelectedTextFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_selected_text", false);
	},
	HandleShowSelectedTextClear : function(event) {
		this.RemoverToNilShowSet("show_selected_text", "", false);
	},
	HandleShowSelectedOverTextClear : function(event) {
		this.RemoverToNilShowSet("show_selected_over_text", "", false);
	},
	HandleShowSelectedOverTextFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_selected_over_text", false);
	},
	HandleShowSelectedOverTextClear : function(event) {
		this.RemoverToNilShowSet("show_selected_over_text", "", false);
	},
	HandleShowSelectedDownTextFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_selected_down_text", false);
	},
	HandleShowSelectedDownTextClear : function(event) {
		this.RemoverToNilShowSet("show_selected_down_text", "", false);
	},
	HandleShowSelectedDisabledTextFOCUSOUT : function(event) {
		ALittleIDE.g_IDEAttrTextDialog.ShowDialog(this, "show_selected_disabled_text", false);
	},
	HandleShowSelectedDisabledTextClear : function(event) {
		this.RemoverToNilShowSet("show_selected_disabled_text", "", false);
	},
}, "ALittleIDE.TextCheckButtonS");

}