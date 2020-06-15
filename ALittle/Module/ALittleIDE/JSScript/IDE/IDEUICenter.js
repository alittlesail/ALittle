{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1408180774, "ALittleIDE.IDEUICenterScaleChangedEvent", {
name : "ALittleIDE.IDEUICenterScaleChangedEvent", ns_name : "ALittleIDE", rl_name : "IDEUICenterScaleChangedEvent", hash_code : 1408180774,
name_list : ["target","scale"],
type_list : ["ALittle.DisplayObject","double"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-506107723, "ALittleIDE.IDEUICenterSelectOpChangedEvent", {
name : "ALittleIDE.IDEUICenterSelectOpChangedEvent", ns_name : "ALittleIDE", rl_name : "IDEUICenterSelectOpChangedEvent", hash_code : -506107723,
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
ALittle.RegStruct(1299500288, "ALittleIDE.IDEUICenterHandDragOpChangedEvent", {
name : "ALittleIDE.IDEUICenterHandDragOpChangedEvent", ns_name : "ALittleIDE", rl_name : "IDEUICenterHandDragOpChangedEvent", hash_code : 1299500288,
name_list : ["target","value"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})
ALittle.RegStruct(2103672497, "ALittleIDE.IDEUICenterScaleOpChangedEvent", {
name : "ALittleIDE.IDEUICenterScaleOpChangedEvent", ns_name : "ALittleIDE", rl_name : "IDEUICenterScaleOpChangedEvent", hash_code : 2103672497,
name_list : ["target","value"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEUICenter = JavaScript.Class(ALittle.DisplayLayout, {
	TCtor : function() {
		this._project_edit_tab.DisableAllCloseButton();
		this._project_edit_tab.tab_index = 1;
		this._control_tree_tab.DisableAllCloseButton();
		this._control_tree_tab.tab_index = 1;
		this._control_edit_tab.DisableAllCloseButton();
		this._control_edit_tab.tab_index = 1;
		this._project_quick_tab.DisableAllCloseButton();
		this._project_quick_tab.tab_index = 1;
		ALittle.TextRadioButton.SetGroup([this._tool_singleselect, this._tool_handdrag, this._tool_scale, this._tool_presee]);
	},
	get control_tree() {
		return this._control_tree;
	},
	get control_list() {
		return this._control_list;
	},
	get project_list() {
		return this._project_list;
	},
	get control_attr() {
		return this._control_attr;
	},
	get control_anti() {
		return this._control_anti;
	},
	get content_edit() {
		return this._content_edit;
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
	HandleRightEditResizeDrag : function(event) {
		let down_size = this._right_edit_grid3.down_size;
		down_size = down_size - event.delta_x;
		let max_size = this._right_edit_grid3.width - this._right_edit_grid3.up_size - 50;
		if (down_size > max_size) {
			down_size = max_size;
		}
		if (down_size < 100) {
			down_size = 100;
		}
		this._right_edit_grid3.down_size = down_size;
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
	HandleShortcutKey : function() {
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
			ALittleIDE.g_IDECenter.center.control_list.ShowNewControl();
			return;
		}
	},
	HandleUndoRevoke : function(event) {
		let tab_child = ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		tab_child.revoke_list.UndoRevoke();
	},
	HandleDoRevoke : function(event) {
		let tab_child = ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		tab_child.revoke_list.DoRevoke();
	},
	HandleSaveCurrent : function(event) {
		let tab_child = ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		tab_child.save = true;
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
	},
	HandleDoRevoke : function(event) {
		let tab_child = ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		tab_child.revoke_list.DoRevoke();
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
		ALittleIDE.g_IDEImageManagerDialog.SetBasePath(ALittleIDE.g_IDEProject.project.texture_path);
		ALittleIDE.g_IDEImageManagerDialog.ShowDialog();
	},
}, "ALittleIDE.IDEUICenter");

}