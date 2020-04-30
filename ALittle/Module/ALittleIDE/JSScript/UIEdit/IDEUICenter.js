{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.IDEUICenter = JavaScript.Class(undefined, {
	Ctor : function() {
	},
	get image_scroll_screen() {
		return this._image_scroll_screen;
	},
	Setup : function(edit_container) {
		return new Promise((async function(___COROUTINE, ___) {
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEUtility");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEDataCore/IDEEnum");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEDataCore/IDEExport");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDETabChild");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDETabManager");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDETreeLogic");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDETree");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDETreeItem");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDERevocation");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDEAttrTextDialog");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDEAttrEventDialog");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDEAttrImageDialog");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDEEditImageDialog");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDEImageCutPlugin");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/DisplayObjectS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/DisplayLayoutS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/DisplayViewS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/TextCheckButtonS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/DialogS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/DropDownS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/Grid3S");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/Grid9S");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/Grid9ImageS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/TextS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/TextEditS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/ImageEditS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/TextInputS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/ImageInputS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/ImageS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/TriangleS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/ImagePlayS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/FramePlayS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/SpriteS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/SpritePlayS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/LinearS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/QuadS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/RichAreaS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/RichInputS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/RichEditS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/SliderS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/ScrollBarS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/ScrollButtonS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/ScrollListS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/ScrollScreenS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/TabS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/TextAreaS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/TextButtonS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/SpringTextButtonS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/TextRadioButtonS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/TileTableS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditCore/IDESetting/PiechartS");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditLogic/IDETool");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditLogic/IDEMainMenu");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditLogic/IDEAttributeManager");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditLogic/IDEControlManager");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditLogic/IDEQuickManager");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditLogic/IDEAntiManager");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditLogic/IDEControlTree");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditLogic/IDEImageManager");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditLogic/IDEProjectManager");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditLogic/IDEVersionList");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditLogic/IDEVersionManager");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditLogic/IDELoginManager");
			await Require(ALittleIDE.g_ScriptBasePath, "UIEdit/IDEEditLogic/IDEIMEManager");
			this._ui_edit_container = ALittleIDE.g_Control.CreateControl("ide_ui_edit_container", this, edit_container);
			let tree_displaylayout = ALittleIDE.g_Control.CreateControl("ide_main_tab_tree_displaylayout", ALittleIDE.g_IDEControlTree, this._control_tree_tab);
			ALittleIDE.g_Control.CreateControl("ide_main_tab_control_scroll_screen", ALittleIDE.g_IDEControlManager, this._project_edit_tab);
			ALittleIDE.g_Control.CreateControl("ide_main_tab_image_scroll_screen", ALittleIDE.g_IDEImageManager, this._project_edit_tab);
			ALittleIDE.g_Control.CreateControl("ide_main_tab_project_scroll_screen", ALittleIDE.g_IDEProjectManager, this._project_edit_tab);
			this._project_edit_tab.DisableAllCloseButton();
			this._project_edit_tab.tab_index = 1;
			this._control_tree_tab.DisableAllCloseButton();
			this._control_tree_tab.tab_index = 1;
			let attr_displaylayout = ALittleIDE.g_Control.CreateControl("ide_main_tab_attr_displaylayout", ALittleIDE.g_IDEAttributeManager, this._control_edit_tab);
			this._control_edit_tab.DisableAllCloseButton();
			this._control_edit_tab.tab_index = 1;
			let anti_displaylayout = ALittleIDE.g_Control.CreateControl("ide_main_project_quick_anti", ALittleIDE.g_IDEAntiManager, this._project_quick_tab);
			ALittleIDE.g_IDEAntiManager.Setup(this._project_quick_tab, anti_displaylayout);
			ALittleIDE.g_IDEQuickManager.Setup(this._project_quick_tab);
			this._project_quick_tab.DisableAllCloseButton();
			this._project_quick_tab.tab_index = 1;
			ALittleIDE.g_IDEAttributeManager.Setup(this._control_edit_tab, attr_displaylayout);
			ALittleIDE.g_IDETabManager.Setup(this._main_edit_tab, tree_displaylayout, attr_displaylayout, anti_displaylayout);
			ALittleIDE.g_IDEAttrImageDialog.Setup();
			ALittle.TextRadioButton.SetGroup([this._tool_singleselect, this._tool_handdrag, this._tool_scale, this._tool_presee]);
			___COROUTINE();
		}).bind(this));
	},
	Shutdown : function() {
		ALittleIDE.g_IDETabManager.Shutdown();
	},
	Show : function() {
		this._ui_edit_container.visible = true;
	},
	Hide : function() {
		this._ui_edit_container.visible = false;
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
			ALittleIDE.g_IDEControlManager.ShowNewControl();
			return;
		}
	},
	HandleUndoRevoke : function(event) {
		let tab_child = ALittleIDE.g_IDETabManager.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		tab_child.revoke_list.UndoRevoke();
	},
	HandleDoRevoke : function(event) {
		let tab_child = ALittleIDE.g_IDETabManager.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		tab_child.revoke_list.DoRevoke();
	},
	HandleSaveCurrent : function(event) {
		let tab_child = ALittleIDE.g_IDETabManager.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		tab_child.Save(true);
	},
	HandleUndoRevoke : function(event) {
		if (ALittleIDE.g_IDEAttrEventDialog.IsShow()) {
			return;
		}
		let tab_child = ALittleIDE.g_IDETabManager.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		tab_child.revoke_list.UndoRevoke();
	},
	HandleDoRevoke : function(event) {
		let tab_child = ALittleIDE.g_IDETabManager.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		tab_child.revoke_list.DoRevoke();
	},
	HandleSaveCurrent : function(event) {
		let tab_child = ALittleIDE.g_IDETabManager.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		tab_child.Save(true);
	},
	HandleToolSingleSelect : function(event) {
		let object = event.target;
		ALittleIDE.g_IDETabManager.ShowTabChildSelectLayer(object.selected);
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
		ALittleIDE.g_IDETabManager.ShowTabChildHandDragLayer(event.target.selected);
	},
	HandleToolPreSee : function(event) {
	},
	HandleToolScale : function(event) {
		ALittleIDE.g_IDETabManager.ShowTabChildScaleLayer(event.target.selected);
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
		let tab_child = ALittleIDE.g_IDETabManager.cur_tab_child;
		if (tab_child === undefined) {
			return;
		}
		let scale = ALittle.Math_ToDouble(this._tool_scale_input.text);
		if (scale === undefined) {
			scale = 1;
		}
		scale = scale + event.delta_x * 0.05;
		if (scale < 0) {
			scale = 0;
		}
		this._tool_scale_input.text = scale;
		tab_child.SetScale(scale);
	},
	HandleToolScaleMoveIn : function(event) {
		ALittle.System_SetHDragCursor();
	},
	HandleToolScaleMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleToolScaleInputFOCUSOUT : function(event) {
		let tab_child = ALittleIDE.g_IDETabManager.cur_tab_child;
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
		tab_child.SetScale(scale);
	},
	HandleToolHLAlign : function(event) {
		let cur_tab = ALittleIDE.g_IDETabManager.cur_tab;
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
		ALittleIDE.g_IDEAttrImageDialog.ShowDialog(undefined, undefined);
	},
	HandleTabRightExMenu : function(event) {
		let [x, y] = event.target.LocalToGlobal();
		ALittleIDE.g_IDETabManager.ShowTabRightExMenu(x, y + event.target.height);
	},
}, "ALittleIDE.IDEUICenter");

ALittleIDE.g_IDEUICenter = ALittle.NewObject(ALittleIDE.IDEUICenter);
}