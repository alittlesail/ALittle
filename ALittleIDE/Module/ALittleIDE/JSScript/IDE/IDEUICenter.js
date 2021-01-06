{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(2103672497, "ALittleIDE.IDEUICenterScaleOpChangedEvent", {
name : "ALittleIDE.IDEUICenterScaleOpChangedEvent", ns_name : "ALittleIDE", rl_name : "IDEUICenterScaleOpChangedEvent", hash_code : 2103672497,
name_list : ["target","value"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(-1614198151, "ALittleIDE.IDEUICenterTileEraseOpChangedEvent", {
name : "ALittleIDE.IDEUICenterTileEraseOpChangedEvent", ns_name : "ALittleIDE", rl_name : "IDEUICenterTileEraseOpChangedEvent", hash_code : -1614198151,
name_list : ["target","value"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1408180774, "ALittleIDE.IDEUICenterScaleChangedEvent", {
name : "ALittleIDE.IDEUICenterScaleChangedEvent", ns_name : "ALittleIDE", rl_name : "IDEUICenterScaleChangedEvent", hash_code : 1408180774,
name_list : ["target","scale"],
type_list : ["ALittle.DisplayObject","double"],
option_map : {}
})
ALittle.RegStruct(1299500288, "ALittleIDE.IDEUICenterHandDragOpChangedEvent", {
name : "ALittleIDE.IDEUICenterHandDragOpChangedEvent", ns_name : "ALittleIDE", rl_name : "IDEUICenterHandDragOpChangedEvent", hash_code : 1299500288,
name_list : ["target","value"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})
ALittle.RegStruct(-1173423947, "ALittleIDE.IDEUICenterTileBrushOpChangedEvent", {
name : "ALittleIDE.IDEUICenterTileBrushOpChangedEvent", ns_name : "ALittleIDE", rl_name : "IDEUICenterTileBrushOpChangedEvent", hash_code : -1173423947,
name_list : ["target","value"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})
ALittle.RegStruct(-751714957, "ALittleIDE.IDEUICenterTileHandDragOpChangedEvent", {
name : "ALittleIDE.IDEUICenterTileHandDragOpChangedEvent", ns_name : "ALittleIDE", rl_name : "IDEUICenterTileHandDragOpChangedEvent", hash_code : -751714957,
name_list : ["target","value"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})
ALittle.RegStruct(516695166, "ALittleIDE.IDEUICenterPreSeeOpChangedEvent", {
name : "ALittleIDE.IDEUICenterPreSeeOpChangedEvent", ns_name : "ALittleIDE", rl_name : "IDEUICenterPreSeeOpChangedEvent", hash_code : 516695166,
name_list : ["target","value"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})
ALittle.RegStruct(-506107723, "ALittleIDE.IDEUICenterSelectOpChangedEvent", {
name : "ALittleIDE.IDEUICenterSelectOpChangedEvent", ns_name : "ALittleIDE", rl_name : "IDEUICenterSelectOpChangedEvent", hash_code : -506107723,
name_list : ["target","value"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEUICenter = JavaScript.Class(ALittle.DisplayLayout, {
	TCtor : function() {
		this._project_edit_tab.DisableAllCloseButton();
		this._project_edit_tab.tab_index = 1;
		this._detail_tree_tab.DisableAllCloseButton();
		this._detail_tree_tab.tab_index = 1;
		this._project_quick_tab.DisableAllCloseButton();
		this._project_quick_tab.tab_index = 1;
		this._tool_ui_container.visible = false;
		this._tool_code_container.visible = false;
		this._tool_tile_container.visible = false;
		this._quick_edit_grid3_down_size = this._quick_edit_grid3.down_size;
		this._quick_edit_grid3.down_size = this._project_quick_tab.up_size;
		this._quick_fold_updown.selected = false;
		ALittle.TextRadioButton.SetGroup([this._tool_singleselect, this._tool_handdrag, this._tool_scale, this._tool_presee]);
		ALittle.TextRadioButton.SetGroup([this._tool_tile_brush, this._tool_tile_handdrag, this._tool_tile_erase]);
		ALittleIDE.g_IDEProject.AddEventListener(___all_struct.get(-975432877), this, this.HandleProjectOpen);
	},
	get project_edit_tab() {
		return this._project_edit_tab;
	},
	get detail_tree_tab() {
		return this._detail_tree_tab;
	},
	get control_tree() {
		return this._control_tree;
	},
	get tile_brush_edit() {
		return this._tile_brush_edit;
	},
	get tile_brush_list() {
		return this._tile_brush_list;
	},
	get control_list() {
		return this._control_list;
	},
	get code_list() {
		return this._code_list;
	},
	get tile_list() {
		return this._tile_list;
	},
	get project_list() {
		return this._project_list;
	},
	get control_anti() {
		return this._control_anti;
	},
	get content_edit() {
		return this._content_edit;
	},
	get tool_ui() {
		return this._tool_ui_container;
	},
	get tool_code() {
		return this._tool_code_container;
	},
	get tool_tile() {
		return this._tool_tile_container;
	},
	System_SetVDragCursor : function(event) {
		ALittle.System_SetVDragCursor();
	},
	System_SetNormalCursor : function(event) {
		ALittle.System_SetNormalCursor();
	},
	System_SetHDragCursor : function(event) {
		ALittle.System_SetHDragCursor();
	},
	System_SetHVDragCursor : function(event) {
		ALittle.System_SetHVDragCursor();
	},
	HandleLeftEditResizeDrag : function(event) {
		let up_size = this._right_edit_grid3.up_size;
		up_size = up_size + event.delta_x;
		let max_size = this._right_edit_grid3.width - this._right_edit_grid3.down_size - 50;
		if (up_size > max_size) {
			up_size = max_size;
		}
		if (up_size < 100) {
			up_size = 100;
		}
		this._right_edit_grid3.up_size = up_size;
	},
	HandleControlEditResizeDrag : function(event) {
		let up_size = this._control_edit_grid3.up_size;
		up_size = up_size + event.delta_y;
		let max_size = this._control_edit_grid3.height - this._control_edit_grid3.down_size - 50;
		if (up_size < 50) {
			up_size = 50;
		}
		if (up_size > max_size) {
			up_size = max_size;
		}
		this._control_edit_grid3.up_size = up_size;
	},
	HandleQuickEditResizeDrag : function(event) {
		let down_size = this._quick_edit_grid3.down_size;
		down_size = down_size - event.delta_y;
		let max_size = this._quick_edit_grid3.height - this._quick_edit_grid3.up_size - 50;
		if (down_size < 50) {
			down_size = 50;
		}
		if (down_size > max_size) {
			down_size = max_size;
		}
		this._quick_edit_grid3.down_size = down_size;
	},
	HandleQuickFoldChanged : function(event) {
		if (event.target.selected) {
			this._quick_edit_grid3.down_size = this._quick_edit_grid3_down_size;
		} else {
			this._quick_edit_grid3_down_size = this._quick_edit_grid3.down_size;
			this._quick_edit_grid3.down_size = this._project_quick_tab.up_size;
		}
	},
	HandleShortcutKey : function() {
		if (A_UISystem.sym_map.get(27)) {
			if (ALittleIDE.g_IDEAttrEventDialog.IsShow()) {
				ALittleIDE.g_IDEAttrEventDialog.HideDialog();
				return;
			}
			if (ALittleIDE.g_IDEAttrControlDialog.IsShow()) {
				ALittleIDE.g_IDEAttrControlDialog.HideDialog();
				return;
			}
			if (ALittleIDE.g_IDEProjectFindFileDialog.IsShow()) {
				ALittleIDE.g_IDEProjectFindFileDialog.HideDialog();
				return;
			}
		}
		let ctrl = A_UISystem.sym_map.get(1073742048);
		if (ctrl === undefined) {
			return;
		}
		let z = A_UISystem.sym_map.get(122);
		if (z) {
			this.HandleUndoRevoke(undefined);
			return;
		}
		let s = A_UISystem.sym_map.get(115);
		if (s) {
			this.HandleSaveCurrent(undefined);
			return;
		}
		let n = A_UISystem.sym_map.get(110);
		if (n) {
			this._control_list.ShowNewControl(undefined);
			return;
		}
	},
	HandleUndoRevoke : function(event) {
		if (ALittleIDE.g_IDEAttrEventDialog.IsShow()) {
			return;
		}
		let tab_child = ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		tab_child.revoke_list.UndoRevoke();
		tab_child.OnUndo();
	},
	HandleDoRevoke : function(event) {
		let tab_child = ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		tab_child.revoke_list.DoRevoke();
		tab_child.OnRedo();
	},
	HandleSaveCurrent : function(event) {
		let tab_child = ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		tab_child.save = true;
	},
	HandleToolSingleSelect : function(event) {
		let object = event.target;
		let op_event = {};
		op_event.value = object.selected;
		ALittleIDE.g_IDECenter.center.DispatchEvent(___all_struct.get(-506107723), op_event);
		this._tool_h_align_left.visible = object.selected;
		this._tool_h_align_center.visible = object.selected;
		this._tool_h_align_right.visible = object.selected;
		this._tool_v_align_top.visible = object.selected;
		this._tool_v_align_center.visible = object.selected;
		this._tool_v_align_bottom.visible = object.selected;
		this._tool_h_align_left_icon.visible = object.selected;
		this._tool_h_align_center_icon.visible = object.selected;
		this._tool_h_align_right_icon.visible = object.selected;
		this._tool_v_align_top_icon.visible = object.selected;
		this._tool_v_align_center_icon.visible = object.selected;
		this._tool_v_align_bottom_icon.visible = object.selected;
	},
	HandleToolHandDrag : function(event) {
		let op_event = {};
		op_event.value = event.target.selected;
		ALittleIDE.g_IDECenter.center.DispatchEvent(___all_struct.get(1299500288), op_event);
	},
	HandleToolPreSee : function(event) {
		let op_event = {};
		op_event.value = event.target.selected;
		ALittleIDE.g_IDECenter.center.DispatchEvent(___all_struct.get(516695166), op_event);
	},
	HandleToolScale : function(event) {
		let op_event = {};
		op_event.value = event.target.selected;
		ALittleIDE.g_IDECenter.center.DispatchEvent(___all_struct.get(2103672497), op_event);
		this._tool_scale_text.visible = event.target.selected;
		this._tool_scale_input.visible = event.target.selected;
	},
	get singleselect() {
		return this._tool_singleselect.selected;
	},
	get handdrag() {
		return this._tool_handdrag.selected;
	},
	get scale() {
		return this._tool_scale.selected;
	},
	UpdateToolScale : function(scale) {
		this._tool_scale_input.text = scale;
	},
	HandleToolScaleDrag : function(event) {
		let scale = ALittle.Math_ToDouble(this._tool_scale_input.text);
		if (scale === undefined) {
			scale = 1;
		}
		scale = scale + event.delta_x * 0.05;
		if (scale < 0) {
			scale = 0;
		}
		this._tool_scale_input.text = scale;
		let scale_event = {};
		scale_event.scale = scale;
		this.DispatchEvent(___all_struct.get(1408180774), scale_event);
	},
	HandleToolScaleMoveIn : function(event) {
		ALittle.System_SetHDragCursor();
	},
	HandleToolScaleMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleToolScaleInputFOCUSOUT : function(event) {
		let tab_child = ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		let scale = ALittle.Math_ToDouble(this._tool_scale_input.text);
		if (scale === undefined) {
			scale = 1;
		}
		if (scale < 0) {
			scale = 0;
			this._tool_scale_input.text = "0";
		}
		let scale_event = {};
		scale_event.scale = scale;
		this.DispatchEvent(___all_struct.get(1408180774), scale_event);
	},
	HandleToolHLAlign : function(event) {
		let cur_tab = ALittleIDE.g_IDECenter.center.content_edit.cur_tab;
		if (cur_tab === undefined) {
			return;
		}
		let tab_child = cur_tab._user_data;
		if (event.target === this._tool_h_align_left) {
			tab_child.SelectAlign("h_align_left");
		} else if (event.target === this._tool_h_align_center) {
			tab_child.SelectAlign("h_align_center");
		} else if (event.target === this._tool_h_align_right) {
			tab_child.SelectAlign("h_align_right");
		} else if (event.target === this._tool_v_align_top) {
			tab_child.SelectAlign("v_align_top");
		} else if (event.target === this._tool_v_align_center) {
			tab_child.SelectAlign("v_align_center");
		} else if (event.target === this._tool_v_align_bottom) {
			tab_child.SelectAlign("v_align_bottom");
		}
	},
	HandleImageSelectClick : function(event) {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			g_AUITool.ShowNotice("提示", "请先打开项目");
			return;
		}
		let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(undefined);
		if (ui_manager === undefined) {
			return;
		}
		ALittleIDE.g_IDEImageManagerDialog.SetBasePath(ui_manager.texture_path);
		ALittleIDE.g_IDEImageManagerDialog.ShowDialog();
	},
	HandleTargetLanguageSelectChange : function(event) {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			return;
		}
		if (ALittleIDE.g_IDEProject.project.code === undefined) {
			return;
		}
		lua.alittlescript.alittlescriptproject_settargetlanguage(ALittleIDE.g_IDEProject.project.code.project, event.target.text);
		ALittleIDE.g_IDEProject.project.config.SetConfig("target_language", event.target.text);
	},
	HandleJumpNextCodeClick : function(event) {
		let info = this._code_list.JumpNextCode();
		if (info === undefined) {
			return;
		}
		ALittleIDE.g_IDECenter.center.code_list.OpenByFullPath(info.file_path, info.it_line, info.it_char, undefined, undefined);
	},
	HandleJumpPreCodeClick : function(event) {
		let info = this._code_list.JumpPreCode();
		if (info === undefined) {
			return;
		}
		ALittleIDE.g_IDECenter.center.code_list.OpenByFullPath(info.file_path, info.it_line, info.it_char, undefined, undefined);
	},
	HandleToolTileBrushSelect : function(event) {
		let object = event.target;
		let op_event = {};
		op_event.value = object.selected;
		ALittleIDE.g_IDECenter.center.DispatchEvent(___all_struct.get(-1173423947), op_event);
	},
	HandleToolTileHandDrag : function(event) {
		let op_event = {};
		op_event.value = event.target.selected;
		ALittleIDE.g_IDECenter.center.DispatchEvent(___all_struct.get(-751714957), op_event);
	},
	HandleToolTileErase : function(event) {
		let op_event = {};
		op_event.value = event.target.selected;
		ALittleIDE.g_IDECenter.center.DispatchEvent(___all_struct.get(-1614198151), op_event);
	},
	get tile_brush() {
		return this._tool_tile_brush.selected;
	},
	get tile_handdrag() {
		return this._tool_tile_handdrag.selected;
	},
	get tile_erase() {
		return this._tool_tile_erase.selected;
	},
	HandleFindFileClick : function(event) {
		ALittleIDE.g_IDEProjectFindFileDialog.ShowFindFile();
	},
	HandleProjectOpen : function(event) {
		this._tool_ui_container.visible = false;
		this._tool_code_container.visible = false;
		this._tool_tile_container.visible = false;
		this._tool_language.text = ALittleIDE.g_IDEProject.project.config.GetConfig("target_language", "Lua");
	},
}, "ALittleIDE.IDEUICenter");

}