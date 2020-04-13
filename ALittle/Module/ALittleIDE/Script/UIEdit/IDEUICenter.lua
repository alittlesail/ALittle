
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


IDEUICenter = ALittle.Class(nil, "ALittleIDE.IDEUICenter")

function IDEUICenter:Ctor()
end

function IDEUICenter.__getter:image_scroll_screen()
	return self._image_scroll_screen
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

function IDEUICenter:Setup(edit_container)
	g_Script:Require("UIEdit/IDEUtility")
	g_Script:Require("UIEdit/IDEDataCore/IDEEnum")
	g_Script:Require("UIEdit/IDEDataCore/IDEExport")
	g_Script:Require("UIEdit/IDEEditCore/IDETabChild")
	g_Script:Require("UIEdit/IDEEditCore/IDETabManager")
	g_Script:Require("UIEdit/IDEEditCore/IDETreeLogic")
	g_Script:Require("UIEdit/IDEEditCore/IDETree")
	g_Script:Require("UIEdit/IDEEditCore/IDETreeItem")
	g_Script:Require("UIEdit/IDEEditCore/IDERevocation")
	g_Script:Require("UIEdit/IDEEditCore/IDEAttrTextDialog")
	g_Script:Require("UIEdit/IDEEditCore/IDEAttrEventDialog")
	g_Script:Require("UIEdit/IDEEditCore/IDEAttrImageDialog")
	g_Script:Require("UIEdit/IDEEditCore/IDEEditImageDialog")
	g_Script:Require("UIEdit/IDEEditCore/IDEImageCutPlugin")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/DisplayObjectS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/DisplayLayoutS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/DisplayViewS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/TextCheckButtonS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/DialogS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/DropDownS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/Grid3S")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/Grid9S")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/Grid9ImageS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/TextS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/TextEditS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/ImageEditS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/TextInputS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/ImageInputS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/ImageS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/TriangleS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/ImagePlayS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/FramePlayS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/SpriteS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/SpritePlayS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/LinearS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/QuadS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/RichAreaS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/RichInputS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/RichEditS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/SliderS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/ScrollBarS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/ScrollButtonS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/ScrollListS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/ScrollScreenS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/TabS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/TextAreaS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/TextButtonS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/SpringTextButtonS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/TextRadioButtonS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/TileTableS")
	g_Script:Require("UIEdit/IDEEditCore/IDESetting/PiechartS")
	g_Script:Require("UIEdit/IDEEditLogic/IDETool")
	g_Script:Require("UIEdit/IDEEditLogic/IDEMainMenu")
	g_Script:Require("UIEdit/IDEEditLogic/IDEAttributeManager")
	g_Script:Require("UIEdit/IDEEditLogic/IDEControlManager")
	g_Script:Require("UIEdit/IDEEditLogic/IDEQuickManager")
	g_Script:Require("UIEdit/IDEEditLogic/IDEAntiManager")
	g_Script:Require("UIEdit/IDEEditLogic/IDEControlTree")
	g_Script:Require("UIEdit/IDEEditLogic/IDEImageManager")
	g_Script:Require("UIEdit/IDEEditLogic/IDEProjectManager")
	g_Script:Require("UIEdit/IDEEditLogic/IDEVersionList")
	g_Script:Require("UIEdit/IDEEditLogic/IDEVersionManager")
	g_Script:Require("UIEdit/IDEEditLogic/IDELoginManager")
	g_Script:Require("UIEdit/IDEEditLogic/IDEIMEManager")
	self._ui_edit_container = g_Control:CreateControl("ide_ui_edit_container", self, edit_container)
	local tree_displaylayout = g_Control:CreateControl("ide_main_tab_tree_displaylayout", g_IDEControlTree, self._control_tree_tab)
	g_Control:CreateControl("ide_main_tab_control_scroll_screen", g_IDEControlManager, self._project_edit_tab)
	g_Control:CreateControl("ide_main_tab_image_scroll_screen", g_IDEImageManager, self._project_edit_tab)
	g_Control:CreateControl("ide_main_tab_project_scroll_screen", g_IDEProjectManager, self._project_edit_tab)
	self._project_edit_tab:DisableAllCloseButton()
	self._project_edit_tab.tab_index = 1
	self._control_tree_tab:DisableAllCloseButton()
	self._control_tree_tab.tab_index = 1
	local attr_displaylayout = g_Control:CreateControl("ide_main_tab_attr_displaylayout", g_IDEAttributeManager, self._control_edit_tab)
	self._control_edit_tab:DisableAllCloseButton()
	self._control_edit_tab.tab_index = 1
	local anti_displaylayout = g_Control:CreateControl("ide_main_project_quick_anti", g_IDEAntiManager, self._project_quick_tab)
	g_IDEAntiManager:Setup(self._project_quick_tab, anti_displaylayout)
	g_IDEQuickManager:Setup(self._project_quick_tab)
	self._project_quick_tab:DisableAllCloseButton()
	self._project_quick_tab.tab_index = 1
	g_IDEAttributeManager:Setup(self._control_edit_tab, attr_displaylayout)
	g_IDETabManager:Setup(self._main_edit_tab, tree_displaylayout, attr_displaylayout, anti_displaylayout)
	g_IDEAttrImageDialog:Setup()
end

function IDEUICenter:Shutdown()
	g_IDETabManager:Shutdown()
end

function IDEUICenter:Show()
	self._ui_edit_container.visible = true
end

function IDEUICenter:Hide()
	self._ui_edit_container.visible = false
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
		g_IDEControlManager:ShowNewControl()
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

function IDEUICenter:UpdateToolScale(scale)
	self._tool_scale_input.text = scale
end

function IDEUICenter:HandleToolScaleDrag(event)
	local tab_child = g_IDETabManager.cur_tab_child
	if tab_child == nil then
		return
	end
	local scale = tonumber(self._tool_scale_input.text)
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
	local scale = tonumber(self._tool_scale_input.text)
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
	g_IDEAttrImageDialog:ShowDialog(nil, nil)
end

function IDEUICenter:HandleTabRightExMenu(event)
	local x, y = event.target:LocalToGlobal()
	g_IDETabManager:ShowTabRightExMenu(x, y + event.target.height)
end

g_IDEUICenter = IDEUICenter()
