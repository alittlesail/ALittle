-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEUICenter = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUICenter")

function IDEUICenter:TCtor()
	self._project_edit_tab:DisableAllCloseButton()
	self._project_edit_tab.tab_index = 1
	self._control_tree_tab:DisableAllCloseButton()
	self._control_tree_tab.tab_index = 1
	self._control_edit_tab:DisableAllCloseButton()
	self._control_edit_tab.tab_index = 1
	self._project_quick_tab:DisableAllCloseButton()
	self._project_quick_tab.tab_index = 1
	g_IDETabManager:Setup(self._main_edit_tab, self._control_tree, self._control_attr, self._control_anti)
	ALittle.TextRadioButton.SetGroup({self._tool_singleselect, self._tool_handdrag, self._tool_scale, self._tool_presee})
	self._project_list:OpenLastProject()
end

function IDEUICenter:Shutdown()
	g_IDETabManager:Shutdown()
end

function IDEUICenter.__getter:control_tree()
	return self._control_tree
end

function IDEUICenter.__getter:control_list()
	return self._control_list
end

function IDEUICenter.__getter:project_list()
	return self._project_list
end

function IDEUICenter.__getter:control_attr()
	return self._control_attr
end

function IDEUICenter.__getter:control_anti()
	return self._control_anti
end

function IDEUICenter:System_SetVDragCursor(event)
	ALittle.System_SetVDragCursor()
end

function IDEUICenter:System_SetNormalCursor(event)
	ALittle.System_SetNormalCursor()
end

function IDEUICenter:System_SetHDragCursor(event)
	ALittle.System_SetHDragCursor()
end

function IDEUICenter:System_SetHVDragCursor(event)
	ALittle.System_SetHVDragCursor()
end

function IDEUICenter:HandleLeftEditResizeDrag(event)
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

function IDEUICenter:HandleRightEditResizeDrag(event)
	local down_size = self._right_edit_grid3.down_size
	down_size = down_size - event.delta_x
	local max_size = self._right_edit_grid3.width - self._right_edit_grid3.up_size - 50
	if down_size > max_size then
		down_size = max_size
	end
	if down_size < 100 then
		down_size = 100
	end
	self._right_edit_grid3.down_size = down_size
end

function IDEUICenter:HandleControlEditResizeDrag(event)
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

function IDEUICenter:HandleQuickEditResizeDrag(event)
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

function IDEUICenter:HandleShortcutKey()
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
		g_IDECenter.center.control_list:ShowNewControl()
		return
	end
end

function IDEUICenter:HandleUndoRevoke(event)
	local tab_child = g_IDETabManager.cur_tab_child
	if tab_child == nil then
		return
	end
	tab_child.revoke_list:UndoRevoke()
end

function IDEUICenter:HandleDoRevoke(event)
	local tab_child = g_IDETabManager.cur_tab_child
	if tab_child == nil then
		return
	end
	tab_child.revoke_list:DoRevoke()
end

function IDEUICenter:HandleSaveCurrent(event)
	local tab_child = g_IDETabManager.cur_tab_child
	if tab_child == nil then
		return
	end
	tab_child:Save(true)
end

function IDEUICenter:HandleUndoRevoke(event)
	if g_IDEAttrEventDialog:IsShow() then
		return
	end
	local tab_child = g_IDETabManager.cur_tab_child
	if tab_child == nil then
		return
	end
	tab_child.revoke_list:UndoRevoke()
end

function IDEUICenter:HandleDoRevoke(event)
	local tab_child = g_IDETabManager.cur_tab_child
	if tab_child == nil then
		return
	end
	tab_child.revoke_list:DoRevoke()
end

function IDEUICenter:HandleSaveCurrent(event)
	local tab_child = g_IDETabManager.cur_tab_child
	if tab_child == nil then
		return
	end
	tab_child:Save(true)
end

function IDEUICenter:HandleToolSingleSelect(event)
	local object = event.target
	g_IDETabManager:ShowTabChildSelectLayer(object.selected)
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

function IDEUICenter:HandleToolHandDrag(event)
	g_IDETabManager:ShowTabChildHandDragLayer(event.target.selected)
end

function IDEUICenter:HandleToolPreSee(event)
end

function IDEUICenter:HandleToolScale(event)
	g_IDETabManager:ShowTabChildScaleLayer(event.target.selected)
	self._tool_scale_text.visible = event.target.selected
	self._tool_scale_input.visible = event.target.selected
end

function IDEUICenter.__getter:singleselect()
	return self._tool_singleselect.selected
end

function IDEUICenter.__getter:handdrag()
	return self._tool_handdrag.selected
end

function IDEUICenter.__getter:scale()
	return self._tool_scale.selected
end

function IDEUICenter:UpdateToolScale(scale)
	self._tool_scale_input.text = scale
end

function IDEUICenter:HandleToolScaleDrag(event)
	local tab_child = g_IDETabManager.cur_tab_child
	if tab_child == nil then
		return
	end
	local scale = ALittle.Math_ToDouble(self._tool_scale_input.text)
	if scale == nil then
		scale = 1
	end
	scale = scale + event.delta_x * 0.05
	if scale < 0 then
		scale = 0
	end
	self._tool_scale_input.text = scale
	tab_child:SetScale(scale)
end

function IDEUICenter:HandleToolScaleMoveIn(event)
	ALittle.System_SetHDragCursor()
end

function IDEUICenter:HandleToolScaleMoveOut(event)
	ALittle.System_SetNormalCursor()
end

function IDEUICenter:HandleToolScaleInputFOCUSOUT(event)
	local tab_child = g_IDETabManager.cur_tab_child
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
	tab_child:SetScale(scale)
end

function IDEUICenter:HandleToolHLAlign(event)
	local cur_tab = g_IDETabManager.cur_tab
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

function IDEUICenter:HandleImageSelectClick(event)
	if g_IDEProject.project == nil then
		g_AUITool:ShowNotice("提示", "请先打开项目")
		return
	end
	g_IDEImageManagerDialog:SetBasePath(g_IDEProject.project.texture_path)
	g_IDEImageManagerDialog:ShowDialog()
end

function IDEUICenter:HandleTabRightExMenu(event)
	local x, y = event.target:LocalToGlobal()
	g_IDETabManager:ShowTabRightExMenu(x, y + event.target.height)
end

