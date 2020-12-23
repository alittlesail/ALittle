-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(2103672497, "ALittleIDE.IDEUICenterScaleOpChangedEvent", {
name = "ALittleIDE.IDEUICenterScaleOpChangedEvent", ns_name = "ALittleIDE", rl_name = "IDEUICenterScaleOpChangedEvent", hash_code = 2103672497,
name_list = {"target","value"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(-1614198151, "ALittleIDE.IDEUICenterTileEraseOpChangedEvent", {
name = "ALittleIDE.IDEUICenterTileEraseOpChangedEvent", ns_name = "ALittleIDE", rl_name = "IDEUICenterTileEraseOpChangedEvent", hash_code = -1614198151,
name_list = {"target","value"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1408180774, "ALittleIDE.IDEUICenterScaleChangedEvent", {
name = "ALittleIDE.IDEUICenterScaleChangedEvent", ns_name = "ALittleIDE", rl_name = "IDEUICenterScaleChangedEvent", hash_code = 1408180774,
name_list = {"target","scale"},
type_list = {"ALittle.DisplayObject","double"},
option_map = {}
})
ALittle.RegStruct(1299500288, "ALittleIDE.IDEUICenterHandDragOpChangedEvent", {
name = "ALittleIDE.IDEUICenterHandDragOpChangedEvent", ns_name = "ALittleIDE", rl_name = "IDEUICenterHandDragOpChangedEvent", hash_code = 1299500288,
name_list = {"target","value"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(-1173423947, "ALittleIDE.IDEUICenterTileBrushOpChangedEvent", {
name = "ALittleIDE.IDEUICenterTileBrushOpChangedEvent", ns_name = "ALittleIDE", rl_name = "IDEUICenterTileBrushOpChangedEvent", hash_code = -1173423947,
name_list = {"target","value"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(-751714957, "ALittleIDE.IDEUICenterTileHandDragOpChangedEvent", {
name = "ALittleIDE.IDEUICenterTileHandDragOpChangedEvent", ns_name = "ALittleIDE", rl_name = "IDEUICenterTileHandDragOpChangedEvent", hash_code = -751714957,
name_list = {"target","value"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(516695166, "ALittleIDE.IDEUICenterPreSeeOpChangedEvent", {
name = "ALittleIDE.IDEUICenterPreSeeOpChangedEvent", ns_name = "ALittleIDE", rl_name = "IDEUICenterPreSeeOpChangedEvent", hash_code = 516695166,
name_list = {"target","value"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(-506107723, "ALittleIDE.IDEUICenterSelectOpChangedEvent", {
name = "ALittleIDE.IDEUICenterSelectOpChangedEvent", ns_name = "ALittleIDE", rl_name = "IDEUICenterSelectOpChangedEvent", hash_code = -506107723,
name_list = {"target","value"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEUICenter = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUICenter")

function ALittleIDE.IDEUICenter:TCtor()
	self._project_edit_tab:DisableAllCloseButton()
	self._project_edit_tab.tab_index = 1
	self._detail_tree_tab:DisableAllCloseButton()
	self._detail_tree_tab.tab_index = 1
	self._project_quick_tab:DisableAllCloseButton()
	self._project_quick_tab.tab_index = 1
	self._tool_ui_container.visible = false
	self._tool_code_container.visible = false
	self._tool_tile_container.visible = false
	self._quick_edit_grid3_down_size = self._quick_edit_grid3.down_size
	self._quick_edit_grid3.down_size = self._project_quick_tab.up_size
	self._quick_fold_updown.selected = false
	ALittle.TextRadioButton.SetGroup({self._tool_singleselect, self._tool_handdrag, self._tool_scale, self._tool_presee})
	ALittle.TextRadioButton.SetGroup({self._tool_tile_brush, self._tool_tile_handdrag, self._tool_tile_erase})
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-975432877], self, self.HandleProjectOpen)
end

function ALittleIDE.IDEUICenter.__getter:project_edit_tab()
	return self._project_edit_tab
end

function ALittleIDE.IDEUICenter.__getter:detail_tree_tab()
	return self._detail_tree_tab
end

function ALittleIDE.IDEUICenter.__getter:control_tree()
	return self._control_tree
end

function ALittleIDE.IDEUICenter.__getter:tile_brush_edit()
	return self._tile_brush_edit
end

function ALittleIDE.IDEUICenter.__getter:tile_brush_list()
	return self._tile_brush_list
end

function ALittleIDE.IDEUICenter.__getter:control_list()
	return self._control_list
end

function ALittleIDE.IDEUICenter.__getter:code_list()
	return self._code_list
end

function ALittleIDE.IDEUICenter.__getter:tile_list()
	return self._tile_list
end

function ALittleIDE.IDEUICenter.__getter:project_list()
	return self._project_list
end

function ALittleIDE.IDEUICenter.__getter:control_anti()
	return self._control_anti
end

function ALittleIDE.IDEUICenter.__getter:content_edit()
	return self._content_edit
end

function ALittleIDE.IDEUICenter.__getter:tool_ui()
	return self._tool_ui_container
end

function ALittleIDE.IDEUICenter.__getter:tool_code()
	return self._tool_code_container
end

function ALittleIDE.IDEUICenter.__getter:tool_tile()
	return self._tool_tile_container
end

function ALittleIDE.IDEUICenter:System_SetVDragCursor(event)
	ALittle.System_SetVDragCursor()
end

function ALittleIDE.IDEUICenter:System_SetNormalCursor(event)
	ALittle.System_SetNormalCursor()
end

function ALittleIDE.IDEUICenter:System_SetHDragCursor(event)
	ALittle.System_SetHDragCursor()
end

function ALittleIDE.IDEUICenter:System_SetHVDragCursor(event)
	ALittle.System_SetHVDragCursor()
end

function ALittleIDE.IDEUICenter:HandleLeftEditResizeDrag(event)
	local up_size = self._right_edit_grid3.up_size
	up_size = up_size + event.delta_x
	local max_size = self._right_edit_grid3.width - self._right_edit_grid3.down_size - 50
	if up_size > max_size then
		up_size = max_size
	end
	if up_size < 100 then
		up_size = 100
	end
	self._right_edit_grid3.up_size = up_size
end

function ALittleIDE.IDEUICenter:HandleControlEditResizeDrag(event)
	local up_size = self._control_edit_grid3.up_size
	up_size = up_size + event.delta_y
	local max_size = self._control_edit_grid3.height - self._control_edit_grid3.down_size - 50
	if up_size < 50 then
		up_size = 50
	end
	if up_size > max_size then
		up_size = max_size
	end
	self._control_edit_grid3.up_size = up_size
end

function ALittleIDE.IDEUICenter:HandleQuickEditResizeDrag(event)
	local down_size = self._quick_edit_grid3.down_size
	down_size = down_size - event.delta_y
	local max_size = self._quick_edit_grid3.height - self._quick_edit_grid3.up_size - 50
	if down_size < 50 then
		down_size = 50
	end
	if down_size > max_size then
		down_size = max_size
	end
	self._quick_edit_grid3.down_size = down_size
end

function ALittleIDE.IDEUICenter:HandleQuickFoldChanged(event)
	if event.target.selected then
		self._quick_edit_grid3.down_size = self._quick_edit_grid3_down_size
	else
		self._quick_edit_grid3_down_size = self._quick_edit_grid3.down_size
		self._quick_edit_grid3.down_size = self._project_quick_tab.up_size
	end
end

function ALittleIDE.IDEUICenter:HandleShortcutKey()
	if A_UISystem.sym_map[27] then
		if ALittleIDE.g_IDEAttrEventDialog:IsShow() then
			ALittleIDE.g_IDEAttrEventDialog:HideDialog()
			return
		end
		if ALittleIDE.g_IDEAttrControlDialog:IsShow() then
			ALittleIDE.g_IDEAttrControlDialog:HideDialog()
			return
		end
		if ALittleIDE.g_IDEProjectFindFileDialog:IsShow() then
			ALittleIDE.g_IDEProjectFindFileDialog:HideDialog()
			return
		end
	end
	local ctrl = A_UISystem.sym_map[1073742048]
	if ctrl == nil then
		return
	end
	local z = A_UISystem.sym_map[122]
	if z then
		self:HandleUndoRevoke(nil)
		return
	end
	local s = A_UISystem.sym_map[115]
	if s then
		self:HandleSaveCurrent(nil)
		return
	end
	local n = A_UISystem.sym_map[110]
	if n then
		self._control_list:ShowNewControl(nil)
		return
	end
end

function ALittleIDE.IDEUICenter:HandleUndoRevoke(event)
	if ALittleIDE.g_IDEAttrEventDialog:IsShow() then
		return
	end
	local tab_child = ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child
	if tab_child == nil then
		return
	end
	tab_child.revoke_list:UndoRevoke()
	tab_child:OnUndo()
end

function ALittleIDE.IDEUICenter:HandleDoRevoke(event)
	local tab_child = ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child
	if tab_child == nil then
		return
	end
	tab_child.revoke_list:DoRevoke()
	tab_child:OnRedo()
end

function ALittleIDE.IDEUICenter:HandleSaveCurrent(event)
	local tab_child = ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child
	if tab_child == nil then
		return
	end
	tab_child.save = true
end

function ALittleIDE.IDEUICenter:HandleToolSingleSelect(event)
	local object = event.target
	local op_event = {}
	op_event.value = object.selected
	ALittleIDE.g_IDECenter.center:DispatchEvent(___all_struct[-506107723], op_event)
	self._tool_h_align_left.visible = object.selected
	self._tool_h_align_center.visible = object.selected
	self._tool_h_align_right.visible = object.selected
	self._tool_v_align_top.visible = object.selected
	self._tool_v_align_center.visible = object.selected
	self._tool_v_align_bottom.visible = object.selected
	self._tool_h_align_left_icon.visible = object.selected
	self._tool_h_align_center_icon.visible = object.selected
	self._tool_h_align_right_icon.visible = object.selected
	self._tool_v_align_top_icon.visible = object.selected
	self._tool_v_align_center_icon.visible = object.selected
	self._tool_v_align_bottom_icon.visible = object.selected
end

function ALittleIDE.IDEUICenter:HandleToolHandDrag(event)
	local op_event = {}
	op_event.value = event.target.selected
	ALittleIDE.g_IDECenter.center:DispatchEvent(___all_struct[1299500288], op_event)
end

function ALittleIDE.IDEUICenter:HandleToolPreSee(event)
	local op_event = {}
	op_event.value = event.target.selected
	ALittleIDE.g_IDECenter.center:DispatchEvent(___all_struct[516695166], op_event)
end

function ALittleIDE.IDEUICenter:HandleToolScale(event)
	local op_event = {}
	op_event.value = event.target.selected
	ALittleIDE.g_IDECenter.center:DispatchEvent(___all_struct[2103672497], op_event)
	self._tool_scale_text.visible = event.target.selected
	self._tool_scale_input.visible = event.target.selected
end

function ALittleIDE.IDEUICenter.__getter:singleselect()
	return self._tool_singleselect.selected
end

function ALittleIDE.IDEUICenter.__getter:handdrag()
	return self._tool_handdrag.selected
end

function ALittleIDE.IDEUICenter.__getter:scale()
	return self._tool_scale.selected
end

function ALittleIDE.IDEUICenter:UpdateToolScale(scale)
	self._tool_scale_input.text = scale
end

function ALittleIDE.IDEUICenter:HandleToolScaleDrag(event)
	local scale = ALittle.Math_ToDouble(self._tool_scale_input.text)
	if scale == nil then
		scale = 1
	end
	scale = scale + event.delta_x * 0.05
	if scale < 0 then
		scale = 0
	end
	self._tool_scale_input.text = scale
	local scale_event = {}
	scale_event.scale = scale
	self:DispatchEvent(___all_struct[1408180774], scale_event)
end

function ALittleIDE.IDEUICenter:HandleToolScaleMoveIn(event)
	ALittle.System_SetHDragCursor()
end

function ALittleIDE.IDEUICenter:HandleToolScaleMoveOut(event)
	ALittle.System_SetNormalCursor()
end

function ALittleIDE.IDEUICenter:HandleToolScaleInputFOCUSOUT(event)
	local tab_child = ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child
	if tab_child == nil then
		return
	end
	local scale = ALittle.Math_ToDouble(self._tool_scale_input.text)
	if scale == nil then
		scale = 1
	end
	if scale < 0 then
		scale = 0
		self._tool_scale_input.text = "0"
	end
	local scale_event = {}
	scale_event.scale = scale
	self:DispatchEvent(___all_struct[1408180774], scale_event)
end

function ALittleIDE.IDEUICenter:HandleToolHLAlign(event)
	local cur_tab = ALittleIDE.g_IDECenter.center.content_edit.cur_tab
	if cur_tab == nil then
		return
	end
	local tab_child = cur_tab._user_data
	if event.target == self._tool_h_align_left then
		tab_child:SelectAlign("h_align_left")
	elseif event.target == self._tool_h_align_center then
		tab_child:SelectAlign("h_align_center")
	elseif event.target == self._tool_h_align_right then
		tab_child:SelectAlign("h_align_right")
	elseif event.target == self._tool_v_align_top then
		tab_child:SelectAlign("v_align_top")
	elseif event.target == self._tool_v_align_center then
		tab_child:SelectAlign("v_align_center")
	elseif event.target == self._tool_v_align_bottom then
		tab_child:SelectAlign("v_align_bottom")
	end
end

function ALittleIDE.IDEUICenter:HandleImageSelectClick(event)
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("提示", "请先打开项目")
		return
	end
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(nil)
	if ui_manager == nil then
		return
	end
	ALittleIDE.g_IDEImageManagerDialog:SetBasePath(ui_manager.texture_path)
	ALittleIDE.g_IDEImageManagerDialog:ShowDialog()
end

function ALittleIDE.IDEUICenter:HandleTargetLanguageSelectChange(event)
	if ALittleIDE.g_IDEProject.project == nil then
		return
	end
	if ALittleIDE.g_IDEProject.project.code == nil then
		return
	end
	alittlescript.alittlescriptproject_settargetlanguage(ALittleIDE.g_IDEProject.project.code.project, event.target.text)
	ALittleIDE.g_IDEProject.project.config:SetConfig("target_language", event.target.text)
end

function ALittleIDE.IDEUICenter:HandleJumpNextCodeClick(event)
	local info = self._code_list:JumpNextCode()
	if info == nil then
		return
	end
	ALittleIDE.g_IDECenter.center.code_list:OpenByFullPath(info.file_path, info.it_line, info.it_char, nil, nil)
end

function ALittleIDE.IDEUICenter:HandleJumpPreCodeClick(event)
	local info = self._code_list:JumpPreCode()
	if info == nil then
		return
	end
	ALittleIDE.g_IDECenter.center.code_list:OpenByFullPath(info.file_path, info.it_line, info.it_char, nil, nil)
end

function ALittleIDE.IDEUICenter:HandleToolTileBrushSelect(event)
	local object = event.target
	local op_event = {}
	op_event.value = object.selected
	ALittleIDE.g_IDECenter.center:DispatchEvent(___all_struct[-1173423947], op_event)
end

function ALittleIDE.IDEUICenter:HandleToolTileHandDrag(event)
	local op_event = {}
	op_event.value = event.target.selected
	ALittleIDE.g_IDECenter.center:DispatchEvent(___all_struct[-751714957], op_event)
end

function ALittleIDE.IDEUICenter:HandleToolTileErase(event)
	local op_event = {}
	op_event.value = event.target.selected
	ALittleIDE.g_IDECenter.center:DispatchEvent(___all_struct[-1614198151], op_event)
end

function ALittleIDE.IDEUICenter.__getter:tile_brush()
	return self._tool_tile_brush.selected
end

function ALittleIDE.IDEUICenter.__getter:tile_handdrag()
	return self._tool_tile_handdrag.selected
end

function ALittleIDE.IDEUICenter.__getter:tile_erase()
	return self._tool_tile_erase.selected
end

function ALittleIDE.IDEUICenter:HandleFindFileClick(event)
	ALittleIDE.g_IDEProjectFindFileDialog:ShowFindFile()
end

function ALittleIDE.IDEUICenter:HandleProjectOpen(event)
	self._tool_ui_container.visible = false
	self._tool_code_container.visible = false
	self._tool_tile_container.visible = false
	self._tool_language.text = ALittleIDE.g_IDEProject.project.config:GetConfig("target_language", "Lua")
end

end