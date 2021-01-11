-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1883782801, "ALittle.UILButtonDownEvent", {
name = "ALittle.UILButtonDownEvent", ns_name = "ALittle", rl_name = "UILButtonDownEvent", hash_code = 1883782801,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(-1676610185, "ALittle.UISystemSaveFileEvent", {
name = "ALittle.UISystemSaveFileEvent", ns_name = "ALittle", rl_name = "UISystemSaveFileEvent", hash_code = -1676610185,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})
ALittle.RegStruct(-1604617962, "ALittle.UIKeyDownEvent", {
name = "ALittle.UIKeyDownEvent", ns_name = "ALittle", rl_name = "UIKeyDownEvent", hash_code = -1604617962,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(1337289812, "ALittle.UIButtonDragEvent", {
name = "ALittle.UIButtonDragEvent", ns_name = "ALittle", rl_name = "UIButtonDragEvent", hash_code = 1337289812,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1301789264, "ALittle.UIButtonDragBeginEvent", {
name = "ALittle.UIButtonDragBeginEvent", ns_name = "ALittle", rl_name = "UIButtonDragBeginEvent", hash_code = 1301789264,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name = "ALittle.UIMoveOutEvent", ns_name = "ALittle", rl_name = "UIMoveOutEvent", hash_code = -1202439334,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1043339049, "ALittleIDE.IDEUITabChildSearchInfo", {
name = "ALittleIDE.IDEUITabChildSearchInfo", ns_name = "ALittleIDE", rl_name = "IDEUITabChildSearchInfo", hash_code = 1043339049,
name_list = {"name","index"},
type_list = {"string","int"},
option_map = {}
})
ALittle.RegStruct(-959526497, "ALittleIDE.IDEUITabChildHandleInfo", {
name = "ALittleIDE.IDEUITabChildHandleInfo", ns_name = "ALittleIDE", rl_name = "IDEUITabChildHandleInfo", hash_code = -959526497,
name_list = {"display_group","handle_quad","focus_quad","size_quad_container","target","buttondown_lock","buttondown_count","delta_x","delta_y","lock_x_or_y","delta_width","delta_height","lock_width_or_height"},
type_list = {"ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject","ALittleIDE.IDEUITreeLogic","bool","int","double","double","bool","double","double","bool"},
option_map = {}
})
ALittle.RegStruct(882286932, "ALittle.UIKeyEvent", {
name = "ALittle.UIKeyEvent", ns_name = "ALittle", rl_name = "UIKeyEvent", hash_code = 882286932,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name = "ALittle.UIMoveInEvent", ns_name = "ALittle", rl_name = "UIMoveInEvent", hash_code = 544684311,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(456283290, "ALittleIDE.IDEUITabChildControlLine", {
name = "ALittleIDE.IDEUITabChildControlLine", ns_name = "ALittleIDE", rl_name = "IDEUITabChildControlLine", hash_code = 456283290,
name_list = {"quad","size_quad","size_quad_container"},
type_list = {"ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name = "ALittle.UIResizeEvent", ns_name = "ALittle", rl_name = "UIResizeEvent", hash_code = -431205740,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-370908646, "ALittleIDE.IDEUITabChildQuickDragAddUserData", {
name = "ALittleIDE.IDEUITabChildQuickDragAddUserData", ns_name = "ALittleIDE", rl_name = "IDEUITabChildQuickDragAddUserData", hash_code = -370908646,
name_list = {"abs_x","abs_y","module_name","control_name"},
type_list = {"double","double","string","string"},
option_map = {}
})
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name = "ALittle.UIButtonDragEndEvent", ns_name = "ALittle", rl_name = "UIButtonDragEndEvent", hash_code = 150587926,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(40651933, "ALittle.UILButtonUpEvent", {
name = "ALittle.UILButtonUpEvent", ns_name = "ALittle", rl_name = "UILButtonUpEvent", hash_code = 40651933,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})

assert(ALittleIDE.IDETabChild, " extends class:ALittleIDE.IDETabChild is nil")
ALittleIDE.IDEUITabChild = Lua.Class(ALittleIDE.IDETabChild, "ALittleIDE.IDEUITabChild")

function ALittleIDE.IDEUITabChild:Ctor(ctrl_sys, module, name, save)
	ALittleIDE.g_IDECenter.center:AddEventListener(___all_struct[-506107723], self, self.HandleShowSelectLayer)
	ALittleIDE.g_IDECenter.center:AddEventListener(___all_struct[1299500288], self, self.HandleShowHandDragLayer)
	ALittleIDE.g_IDECenter.center:AddEventListener(___all_struct[2103672497], self, self.HandleShowScaleLayer)
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[1787992834], self, self.HandleProjectSettingChanged)
	___rawset(self, "_group", ALittle.CreateKeyWeakMap())
	___rawset(self, "_tab_screen", ALittleIDE.g_Control:CreateControl("ide_edit_tab_screen", self))
	___rawset(self, "_tree_screen", ALittleIDE.g_Control:CreateControl("ide_edit_tree_screen", self))
	___rawset(self, "_attr_screen", ALittleIDE.g_Control:CreateControl("ide_edit_attr_screen", self))
	___rawset(self, "_anti_panel", ALittleIDE.g_Control:CreateControl("ide_edit_anti_panel", self))
	___rawset(self, "_tree_object", nil)
	self._tab_screen.container.scale_x = 1
	self._tab_screen.container.scale_y = 1
	self._tab_container.width = ALittleIDE.g_IDEProject.project.config:GetConfig("default_show_width", 800)
	self._tab_container.height = ALittleIDE.g_IDEProject.project.config:GetConfig("default_show_height", 600)
	self._tab_container.x = 100
	self._tab_container.y = 100
	self._tab_rb_quad.x = self._tab_container.x + self._tab_container.width + 100
	self._tab_rb_quad.y = self._tab_container.y + self._tab_container.height + 100
	self._tab_screen:AdjustScrollBar()
	self._tab_select_container.visible = ALittleIDE.g_IDECenter.center.singleselect
	self._tab_handle_quad:AddEventListener(___all_struct[1883782801], self, self.HandleHandleContainerLButtonDown)
	self._tab_handle_quad:AddEventListener(___all_struct[40651933], self, self.HandleHandleContainerLButtonUp)
	self._tab_handle_quad:AddEventListener(___all_struct[1301789264], self, self.HandleHandleContainerDragBegin)
	self._tab_handle_quad:AddEventListener(___all_struct[1337289812], self, self.HandleHandleContainerDrag)
	self._tab_handle_quad:AddEventListener(___all_struct[150587926], self, self.HandleHandleContainerDragEnd)
	self._tab_select_rect.visible = false
	self._tab_quad_container:RemoveAllChild()
	___rawset(self, "_tab_quad_map", {})
	self._tab_handdrag_container.visible = ALittleIDE.g_IDECenter.center.handdrag
	self._tab_handdrag_quad.drag_trans_target = self._tab_screen
	self._tab_scale_container.visible = ALittleIDE.g_IDECenter.center.scale
	self._tab_scale_quad:AddEventListener(___all_struct[1883782801], self, self.HandleScaleContainerLButtonDown)
	___rawset(self, "_tree_search_info", {})
	self._tree_search_info.name = ""
	self._tree_search_info.index = 0
	self._tab_screen._user_data = self
	self._tree_screen._user_data = self
	___rawset(self, "_tree_loop_x", nil)
	___rawset(self, "_tree_loop_y", nil)
	self:AddEventListener(___all_struct[-1676610185], self, self.HandleSavePng)
end

function ALittleIDE.IDEUITabChild:OnHide()
	self._tree_screen.visible = false
	self._attr_screen.visible = false
	self._anti_panel.visible = false
	ALittleIDE.g_IDECenter.center.tool_ui.visible = false
	ALittleIDE.g_IDEAttrControlDialog:SetTitle("")
	ALittleIDE.g_IDEAttrControlDialog:HideDialog()
	ALittleIDE.g_IDECenter.center:RemoveEventListener(___all_struct[1408180774], self, self.HandleEditScaleChanged)
end

function ALittleIDE.IDEUITabChild:OnShow()
	self._tree_screen.visible = true
	self._attr_screen.visible = true
	self._anti_panel.visible = true
	ALittleIDE.g_IDECenter.center.tool_ui.visible = true
	ALittleIDE.g_IDECenter.center.detail_tree_tab.tab = ALittleIDE.g_IDECenter.center.control_tree
	local panel_childs = self._attr_screen.childs
	if panel_childs[1] ~= nil then
		ALittleIDE.g_IDEAttrControlDialog:SetTitle(panel_childs[1]._user_data.title)
	end
	ALittleIDE.g_IDECenter.center:UpdateToolScale(self:GetScale())
	ALittleIDE.g_IDECenter.center:AddEventListener(___all_struct[1408180774], self, self.HandleEditScaleChanged)
end

function ALittleIDE.IDEUITabChild:OnClose()
	ALittleIDE.g_IDECenter.center.control_tree:RemoveChild(self._tree_screen)
	ALittleIDE.g_IDEAttrControlDialog.attr_container:RemoveChild(self._attr_screen)
	ALittleIDE.g_IDECenter.center.control_anti:RemoveChild(self._anti_panel)
	ALittleIDE.g_IDEProject:RemoveEventListener(___all_struct[1787992834], self, self.HandleProjectSettingChanged)
	ALittleIDE.g_IDECenter.center:RemoveEventListener(___all_struct[1408180774], self, self.HandleEditScaleChanged)
	ALittleIDE.g_IDECenter.center:RemoveEventListener(___all_struct[-506107723], self, self.HandleShowSelectLayer)
	ALittleIDE.g_IDECenter.center:RemoveEventListener(___all_struct[1299500288], self, self.HandleShowHandDragLayer)
	ALittleIDE.g_IDECenter.center:RemoveEventListener(___all_struct[2103672497], self, self.HandleShowScaleLayer)
end

function ALittleIDE.IDEUITabChild:OnOpen()
	ALittleIDE.g_IDECenter.center.control_tree:AddChild(self._tree_screen)
	ALittleIDE.g_IDEAttrControlDialog.attr_container:AddChild(self._attr_screen)
	ALittleIDE.g_IDECenter.center.control_anti:AddChild(self._anti_panel)
end

function ALittleIDE.IDEUITabChild:ShowInCenter()
	local object = self._tree_object.user_info.object
	local x, y = object:LocalToGlobal(self._tab_object_container)
	if x > 0 and y > 0 then
		local real_width = self._tab_object_container.width - self._tab_screen.view_width
		if object.width < self._tab_object_container.width and real_width > 0 then
			local view_x = self._tab_screen.view_width / 2
			local center_x = x + object.width / 2
			self._tab_screen.bottom_scrollbar.offset_rate = (center_x - view_x) / real_width
		end
		local real_height = self._tab_object_container.height - self._tab_screen.view_height
		if object.height < self._tab_object_container.height and real_height > 0 then
			local view_y = self._tab_screen.view_height / 2
			local center_y = y + object.height / 2
			self._tab_screen.right_scrollbar.offset_rate = (center_y - view_y) / real_height
		end
		self._tab_screen:AdjustScrollBar()
	end
end

function ALittleIDE.IDEUITabChild:OnTabRightMenu(menu)
	menu:AddItem("截图导出", Lua.Bind(A_OtherSystem.SystemSaveFile, A_OtherSystem, self, self._name .. ".png", nil))
	menu:AddItem("复制控件名", Lua.Bind(ALittle.System_SetClipboardText, self._name))
	menu:AddItem("复制继承代码", Lua.Bind(self.CopyExtends, self))
	menu:AddItem("刷新", Lua.Bind(self.Refresh, self))
	menu:AddItem("获取焦点", Lua.Bind(self.ShowControlFocus, self))
end

function ALittleIDE.IDEUITabChild:CopyExtends()
	local display_info = {}
	display_info.__module = self._module
	display_info.__extends = self._name
	local copy_list = {}
	local info = {}
	info.index = 1
	info.info = display_info
	copy_list[1] = info
	ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
end

function ALittleIDE.IDEUITabChild:HandleProjectSettingChanged(event)
	self._tab_container.width = event.default_show_width
	self._tab_container.height = event.default_show_height
	self._tab_screen:AdjustScrollBar()
	for target, handle_info in ___pairs(self._tab_quad_map) do
		self:UpdateHandleQuadLayout(target)
	end
end

function ALittleIDE.IDEUITabChild:HandleTreeSizeChanged(event)
	self._tree_screen:AdjustScrollBar()
end

function ALittleIDE.IDEUITabChild:HandleSavePng(event)
	ALittleIDE.g_Control:SaveControlToFile(self._tree_object.user_info.object, event.path)
end

function ALittleIDE.IDEUITabChild.__getter:tab_body()
	return self._tab_screen
end

function ALittleIDE.IDEUITabChild.__getter:edit_screen()
	return self._edit_screen
end

function ALittleIDE.IDEUITabChild.__getter:tree_screen()
	return self._tree_screen
end

function ALittleIDE.IDEUITabChild.__getter:attr_screen()
	return self._attr_screen
end

function ALittleIDE.IDEUITabChild.__getter:anti_panel()
	return self._anti_panel
end

function ALittleIDE.IDEUITabChild.__getter:group()
	return self._group
end

function ALittleIDE.IDEUITabChild.__getter:tree_object()
	return self._tree_object
end

function ALittleIDE.IDEUITabChild.__setter:save(value)
	if self._save == value then
		return
	end
	if value == false then
		self._save = false
		self:UpdateTitle()
		return
	end
	if self._tree_object == nil then
		return
	end
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(self._module)
	if ui_manager == nil then
		g_AUITool:ShowNotice("错误", "模块不存在:" .. self._module)
		return
	end
	local info = self._tree_object:CalcInfo()
	local create = ui_manager.control_map[self._name] == nil
	local error = ui_manager:SaveControl(self._name, info)
	if error ~= nil then
		return
	end
	if create then
		local tree = ALittleIDE.g_IDECenter.center.control_list:GetControlTree(self._module)
		if tree ~= nil then
			tree:Refresh()
		end
	end
	self._save = value
	self:UpdateTitle()
end

function ALittleIDE.IDEUITabChild:Rename(name)
	self._name = name
	self:UpdateTitle()
end

function ALittleIDE.IDEUITabChild:UpdateTitle()
	if self._tree_object == nil then
		return
	end
	local text = self._tree_object:GetDesc()
	if text == "" then
		text = self._name
		if ALittle.String_Len(self._name) > 30 then
			text = "..." .. ALittle.String_Sub(self._name, -30, -1)
		end
	end
	if self._save == false then
		text = text .. " *"
	end
	ALittleIDE.g_IDECenter.center.content_edit.main_tab:SetChildText(self._tab_screen, text)
end

function ALittleIDE.IDEUITabChild.__getter:title()
	local text = self._tree_object:GetDesc()
	if text == "" then
		return self._name
	end
	return self._name .. "(" .. text .. ")"
end

function ALittleIDE.IDEUITabChild:SelectAlign(align_type)
	local count = 0
	local first_target = nil
	for target, handle_info in ___pairs(self._tab_quad_map) do
		count = count + 1
		first_target = target
	end
	if count == 0 then
		return
	end
	if first_target == self._tree_object then
		return
	end
	if count == 1 then
		local parent = ALittle.Cast(ALittleIDE.IDEUITreeLogic, ALittle.DisplayGroup, first_target.logic_parent)
		if parent == nil then
			return
		end
		local parent_object = parent.user_info.object
		local drag_x = 0.0
		local drag_y = 0.0
		local target_object = first_target.user_info.object
		if align_type == "h_align_left" then
			drag_x = -target_object.x
		elseif align_type == "h_align_center" then
			drag_x = (parent_object.width - target_object.width) / 2 - target_object.x
		elseif align_type == "h_align_right" then
			drag_x = (parent_object.width - target_object.width) - target_object.x
		elseif align_type == "v_align_top" then
			drag_y = -target_object.y
		elseif align_type == "v_align_center" then
			drag_y = (parent_object.height - target_object.height) / 2 - target_object.y
		elseif align_type == "v_align_bottom" then
			drag_y = (parent_object.height - target_object.height) - target_object.y
		end
		first_target:DragXY(drag_x, drag_y)
		self:UpdateHandleQuadLayout(first_target)
		local revoke = ALittleIDE.IDEDragXYRevoke(first_target, drag_x, drag_y)
		self._revoke_list:PushRevoke(revoke)
	else
		local revoke_bind = ALittle.RevokeBind()
		if align_type == "h_align_left" then
			local common = first_target.user_info.object.x
			for target, v in ___pairs(self._tab_quad_map) do
				if target.user_info.object.x < common then
					common = target.user_info.object.x
				end
			end
			for target, v in ___pairs(self._tab_quad_map) do
				local drag_x = common - target.user_info.object.x
				target:DragXY(drag_x, 0)
				self:UpdateHandleQuadLayout(target)
				local revoke = ALittleIDE.IDEDragXYRevoke(target, drag_x, 0)
				revoke_bind:PushRevoke(revoke)
			end
		elseif align_type == "h_align_center" then
			local common = 0.0
			for target, v in ___pairs(self._tab_quad_map) do
				common = common + target.user_info.object.x + target.user_info.object.width / 2
			end
			common = common / count
			for target, v in ___pairs(self._tab_quad_map) do
				local drag_x = common - (target.user_info.object.x + target.user_info.object.width / 2)
				target:DragXY(drag_x, 0)
				self:UpdateHandleQuadLayout(target)
				local revoke = ALittleIDE.IDEDragXYRevoke(target, drag_x, 0)
				revoke_bind:PushRevoke(revoke)
			end
		elseif align_type == "h_align_right" then
			local common = first_target.user_info.object.x + first_target.user_info.object.width
			for target, v in ___pairs(self._tab_quad_map) do
				if target.user_info.object.x + target.user_info.object.width > common then
					common = target.user_info.object.x + target.user_info.object.width
				end
			end
			for target, v in ___pairs(self._tab_quad_map) do
				local drag_x = common - (target.user_info.object.x + target.user_info.object.width)
				target:DragXY(drag_x, 0)
				self:UpdateHandleQuadLayout(target)
				local revoke = ALittleIDE.IDEDragXYRevoke(target, drag_x, 0)
				revoke_bind:PushRevoke(revoke)
			end
		elseif align_type == "v_align_top" then
			local common = first_target.user_info.object.y
			for target, v in ___pairs(self._tab_quad_map) do
				if target.user_info.object.y < common then
					common = target.user_info.object.y
				end
			end
			for target, v in ___pairs(self._tab_quad_map) do
				local drag_y = common - target.user_info.object.y
				target:DragXY(0, drag_y)
				self:UpdateHandleQuadLayout(target)
				local revoke = ALittleIDE.IDEDragXYRevoke(target, 0, drag_y)
				revoke_bind:PushRevoke(revoke)
			end
		elseif align_type == "v_align_center" then
			local common = 0.0
			for target, v in ___pairs(self._tab_quad_map) do
				common = common + target.user_info.object.y + target.user_info.object.height / 2
			end
			common = common / count
			for target, v in ___pairs(self._tab_quad_map) do
				local drag_y = common - (target.user_info.object.y + target.user_info.object.height / 2)
				target:DragXY(0, drag_y)
				self:UpdateHandleQuadLayout(target)
				local revoke = ALittleIDE.IDEDragXYRevoke(target, 0, drag_y)
				revoke_bind:PushRevoke(revoke)
			end
		elseif align_type == "v_align_bottom" then
			local common = first_target.user_info.object.y + first_target.user_info.object.height
			for target, v in ___pairs(self._tab_quad_map) do
				if target.user_info.object.y + target.user_info.object.height > common then
					common = target.user_info.object.y + target.user_info.object.height
				end
			end
			for target, v in ___pairs(self._tab_quad_map) do
				local drag_y = common - (target.user_info.object.y + target.user_info.object.height)
				target:DragXY(0, drag_y)
				self:UpdateHandleQuadLayout(target)
				local revoke = ALittleIDE.IDEDragXYRevoke(target, 0, drag_y)
				revoke_bind:PushRevoke(revoke)
			end
		end
		self._revoke_list:PushRevoke(revoke_bind)
	end
	self.save = false
end

function ALittleIDE.IDEUITabChild:HandleShowSelectLayer(event)
	self._tab_select_container.visible = event.value
end

function ALittleIDE.IDEUITabChild:HandleShowHandDragLayer(event)
	self._tab_handdrag_container.visible = event.value
end

function ALittleIDE.IDEUITabChild:HandleShowScaleLayer(event)
	self._tab_scale_container.visible = event.value
end

function ALittleIDE.IDEUITabChild:Refresh()
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(self._module)
	if ui_manager == nil then
		return
	end
	local control_info = ui_manager.control_map[self._name]
	if control_info == nil then
		return
	end
	local object = ui_manager.control:CreateControl(self._name)
	self._tab_object_container:RemoveAllChild()
	self._tab_object_container:AddChild(object)
	self._tree_object = ALittleIDE.IDEUIUtility_CreateTree(control_info.info, self._module, false, object, nil, self, true)
	self._tree_object:AddEventListener(___all_struct[-431205740], self, self.HandleTreeSizeChanged)
	self._tree_object.fold = true
	self._tree_screen:RemoveAllChild()
	self._tree_screen:AddChild(self._tree_object)
	self._anti_panel:Init(self)
	self._group = ALittle.CreateKeyWeakMap()
	self._tab_quad_container:RemoveAllChild()
	self._tab_quad_map = {}
	self._tree_search_info = {}
	self._tree_search_info.name = ""
	self._tree_search_info.index = 0
	self._save = true
	self:UpdateTitle()
	self._revoke_list = ALittle.RevokeList(10000)
end

function ALittleIDE.IDEUITabChild:ShowControlFocus()
	local tree = ALittleIDE.g_IDECenter.center.control_list:GetControlTree(self._module)
	if tree == nil then
		return
	end
	for index, child in ___ipairs(tree.childs) do
		if child.user_info.name == self._name then
			ALittleIDE.g_IDECenter.center.project_edit_tab.tab = ALittleIDE.g_IDECenter.center.control_list
			ALittleIDE.g_IDECenter.center.control_list:ShowTreeItemFocus(child)
			return
		end
	end
end

function ALittleIDE.IDEUITabChild:CreateByNew(type)
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(self._module)
	if ui_manager == nil then
		return
	end
	local info = {}
	info.__class = type
	local object = ALittle.NewObject(ALittle[type], ui_manager.control)
	ALittleIDE.IDEUIUtility_NewGiveBaseCase(info, object)
	self._tab_object_container:AddChild(object)
	self._tree_object = ALittleIDE.IDEUIUtility_CreateTree(info, self._module, false, object, nil, self, true)
	self._tree_object:AddEventListener(___all_struct[-431205740], self, self.HandleTreeSizeChanged)
	self._tree_object.fold = true
	self._tree_screen:AddChild(self._tree_object)
	self._anti_panel:Init(self)
end

function ALittleIDE.IDEUITabChild:CreateByExtends(extends_module, extends_name)
	local extends_ui = ALittleIDE.g_IDEProject:GetUIManager(extends_module)
	if extends_ui == nil then
		return false
	end
	if extends_ui.control_map[extends_name] == nil then
		return false
	end
	local info = {}
	info.__module = extends_module
	info.__extends = extends_name
	local object = extends_ui.control:CreateControl(extends_name)
	self._tab_object_container:AddChild(object)
	self._tree_object = ALittleIDE.IDEUIUtility_CreateTree(info, self._module, false, object, nil, self, true)
	self._tree_object:AddEventListener(___all_struct[-431205740], self, self.HandleTreeSizeChanged)
	self._tree_object.fold = true
	self._tree_screen:AddChild(self._tree_object)
	self._anti_panel:Init(self)
	return true
end

function ALittleIDE.IDEUITabChild:CreateBySelect(info)
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(self._module)
	if ui_manager == nil then
		return
	end
	local object = ui_manager.control:CreateControl(ALittle.File_GetJustFileNameByPath(self._name))
	self._tab_object_container:AddChild(object)
	self._tree_object = ALittleIDE.IDEUIUtility_CreateTree(info, self._module, false, object, nil, self, true)
	self._tree_object:AddEventListener(___all_struct[-431205740], self, self.HandleTreeSizeChanged)
	self._tree_object.fold = true
	self._tree_screen:AddChild(self._tree_object)
	self._anti_panel:Init(self)
end

function ALittleIDE.IDEUITabChild:IsShowHandleQuad(target)
	return self._tab_quad_map[target] ~= nil
end

function ALittleIDE.IDEUITabChild:FocusInHandleQuad(target)
	local handle_info = self._tab_quad_map[target]
	if handle_info == nil then
		return
	end
	A_UISystem.focus = handle_info.focus_quad
end

function ALittleIDE.IDEUITabChild:ClearHandQuad()
	self._tab_quad_map = {}
	self._tab_quad_container:RemoveAllChild()
end

function ALittleIDE.IDEUITabChild:ShowHandleQuad(target, force_shift)
	local shift = (A_UISystem.sym_map[1073742049] ~= nil or A_UISystem.sym_map[1073742053] ~= nil)
	if force_shift then
		shift = true
	end
	local ctrl = (A_UISystem.sym_map[1073742048] ~= nil or A_UISystem.sym_map[1073742052] ~= nil)
	if shift then
		ctrl = false
	end
	if shift == false and ctrl == false then
		self._tab_quad_map = {}
		self._tab_quad_container:RemoveAllChild()
	end
	local common_parent = nil
	local has_target = false
	for tree_target, handle_info in ___pairs(self._tab_quad_map) do
		common_parent = ALittle.Cast(ALittleIDE.IDEUITreeLogic, ALittle.DisplayGroup, tree_target.logic_parent)
		has_target = true
		break
	end
	if has_target and common_parent ~= target.logic_parent then
		local parent = target.logic_parent
		while parent ~= nil and common_parent ~= parent do
			target = ALittle.Cast(ALittleIDE.IDEUITreeLogic, ALittle.DisplayGroup, parent)
			if target == nil then
				parent = nil
				break
			end
			parent = parent.logic_parent
		end
		if parent == nil then
			return
		end
	end
	local list = {}
	if not has_target or common_parent == nil or ctrl then
		list[1] = target
	else
		local max_index = common_parent:GetChildIndex(target)
		local min_index = max_index
		for child, info in ___pairs(self._tab_quad_map) do
			local index = common_parent:GetChildIndex(child)
			if index < min_index then
				min_index = index
			elseif index > max_index then
				max_index = index
			end
		end
		local index = min_index
		while true do
			if not(index <= max_index) then break end
			local child = common_parent:GetChildByIndex(index)
			if self._tab_quad_map[child] == nil then
				ALittle.List_Push(list, child)
			end
			index = index+(1)
		end
	end
	for index, child in ___ipairs(list) do
		local control_line = {}
		local handle_quad = ALittleIDE.g_Control:CreateControl("aui_handle_quad", control_line)
		control_line.quad:AddEventListener(___all_struct[40651933], self, self.HandleHandleQuadLButtonUp)
		control_line.quad:AddEventListener(___all_struct[1883782801], self, self.HandleHandleQuadLButtonDown)
		control_line.quad:AddEventListener(___all_struct[1301789264], self, self.HandleHandleQuadDragBegin)
		control_line.quad:AddEventListener(___all_struct[1337289812], self, self.HandleHandleQuadDrag)
		control_line.quad:AddEventListener(___all_struct[150587926], self, self.HandleHandleQuadDragEnd)
		control_line.quad:AddEventListener(___all_struct[-641444818], self, self.HandleHandleQuadRButtonDown)
		control_line.quad:AddEventListener(___all_struct[-1604617962], self, self.HandleHandleQuadKeyDown)
		control_line.size_quad:AddEventListener(___all_struct[-1604617962], self, self.HandleHandleQuadKeyDown)
		control_line.size_quad:AddEventListener(___all_struct[1301789264], self, self.HandleHandleSizeQuadDragBegin)
		control_line.size_quad:AddEventListener(___all_struct[1337289812], self, self.HandleHandleSizeQuadDrag)
		control_line.size_quad:AddEventListener(___all_struct[150587926], self, self.HandleHandleSizeQuadDragEnd)
		control_line.size_quad:AddEventListener(___all_struct[544684311], self, self.HandleHandleSizeQuadMoveIn)
		control_line.size_quad:AddEventListener(___all_struct[-1202439334], self, self.HandleHandleSizeQuadMoveOut)
		local handle_info = {}
		local target_parent = child.user_info.object
		local quad_parent = handle_quad
		while target_parent ~= nil do
			quad_parent.x = target_parent.x
			quad_parent.y = target_parent.y
			quad_parent.width = target_parent.width
			quad_parent.height = target_parent.height
			quad_parent.scale_x = target_parent.scale_x
			quad_parent.scale_y = target_parent.scale_y
			quad_parent.center_x = target_parent.center_x
			quad_parent.center_y = target_parent.center_y
			quad_parent.angle = target_parent.angle
			local display_group = ALittle.DisplayGroup(ALittleIDE.g_Control)
			display_group:AddChild(quad_parent)
			if target_parent.show_parent == self._tab_object_container then
				handle_info.display_group = display_group
				self._tab_quad_container:AddChild(display_group)
				break
			end
			quad_parent = display_group
			target_parent = target_parent.show_parent
		end
		handle_info.handle_quad = handle_quad
		handle_info.focus_quad = control_line.quad
		handle_info.size_quad_container = control_line.size_quad_container
		control_line.quad._user_data = handle_info
		control_line.size_quad._user_data = handle_info
		child:ShowAttributePanel()
		handle_info.target = child
		self._tab_quad_map[child] = handle_info
	end
	local loop = ALittle.LoopFunction(Lua.Bind(self.FocusInHandleQuad, self, target), 1, 0, 1)
	loop:Start()
end

function ALittleIDE.IDEUITabChild:ShowHandleQuadList(list)
	self._tab_quad_map = {}
	self._tab_quad_container:RemoveAllChild()
	local target = nil
	for index, child in ___ipairs(list) do
		target = child
		local control_line = {}
		local handle_quad = ALittleIDE.g_Control:CreateControl("ide_common_handle_quad", control_line)
		control_line.quad:AddEventListener(___all_struct[40651933], self, self.HandleHandleQuadLButtonUp)
		control_line.quad:AddEventListener(___all_struct[1883782801], self, self.HandleHandleQuadLButtonDown)
		control_line.quad:AddEventListener(___all_struct[1301789264], self, self.HandleHandleQuadDragBegin)
		control_line.quad:AddEventListener(___all_struct[1337289812], self, self.HandleHandleQuadDrag)
		control_line.quad:AddEventListener(___all_struct[150587926], self, self.HandleHandleQuadDragEnd)
		control_line.quad:AddEventListener(___all_struct[-641444818], self, self.HandleHandleQuadRButtonDown)
		control_line.quad:AddEventListener(___all_struct[-1604617962], self, self.HandleHandleQuadKeyDown)
		control_line.size_quad:AddEventListener(___all_struct[-1604617962], self, self.HandleHandleQuadKeyDown)
		control_line.size_quad:AddEventListener(___all_struct[1301789264], self, self.HandleHandleSizeQuadDragBegin)
		control_line.size_quad:AddEventListener(___all_struct[1337289812], self, self.HandleHandleSizeQuadDrag)
		control_line.size_quad:AddEventListener(___all_struct[150587926], self, self.HandleHandleSizeQuadDragEnd)
		control_line.size_quad:AddEventListener(___all_struct[544684311], self, self.HandleHandleSizeQuadMoveIn)
		control_line.size_quad:AddEventListener(___all_struct[-1202439334], self, self.HandleHandleSizeQuadMoveOut)
		local handle_info = {}
		local target_parent = child.user_info.object
		local quad_parent = handle_quad
		while target_parent ~= nil do
			quad_parent.x = target_parent.x
			quad_parent.y = target_parent.y
			quad_parent.width = target_parent.width
			quad_parent.height = target_parent.height
			quad_parent.scale_x = target_parent.scale_x
			quad_parent.scale_y = target_parent.scale_y
			quad_parent.center_x = target_parent.center_x
			quad_parent.center_y = target_parent.center_y
			quad_parent.angle = target_parent.angle
			local display_group = ALittle.DisplayGroup(ALittleIDE.g_Control)
			display_group:AddChild(quad_parent)
			if target_parent.show_parent == self._tab_object_container then
				handle_info.display_group = display_group
				self._tab_quad_container:AddChild(display_group)
				break
			end
			quad_parent = display_group
			target_parent = target_parent.show_parent
		end
		handle_info.handle_quad = handle_quad
		handle_info.focus_quad = control_line.quad
		handle_info.size_quad_container = control_line.size_quad_container
		control_line.quad._user_data = handle_info
		control_line.size_quad._user_data = handle_info
		child:ShowAttributePanel()
		handle_info.target = child
		self._tab_quad_map[child] = handle_info
	end
	if target == nil then
		return
	end
	local loop = ALittle.LoopFunction(Lua.Bind(self.FocusInHandleQuad, self, target), 1, 0, 1)
	loop:Start()
end

function ALittleIDE.IDEUITabChild:HideHandleQuad(target, shift)
	local handle_info = self._tab_quad_map[target]
	if handle_info == nil then
		return
	end
	if shift == nil then
		shift = (A_UISystem.sym_map[1073742049] ~= nil or A_UISystem.sym_map[1073742053] ~= nil)
	end
	local ctrl = (A_UISystem.sym_map[1073742048] ~= nil or A_UISystem.sym_map[1073742052] ~= nil)
	if shift then
		ctrl = false
	end
	if shift == false and ctrl == false then
		self._tab_quad_map = {}
		self._tab_quad_container:RemoveAllChild()
		target:ShowAttributePanel()
		self._tab_quad_map[handle_info.target] = handle_info
		self._tab_quad_container:AddChild(handle_info.display_group)
		return
	end
	self._tab_quad_container:RemoveChild(handle_info.display_group)
	self._tab_quad_map[handle_info.target] = nil
end

function ALittleIDE.IDEUITabChild:UpdateHandleQuadLayout(target)
	local handle_info = self._tab_quad_map[target]
	if handle_info == nil then
		return
	end
	handle_info.handle_quad.x = target.user_info.object.x
	handle_info.handle_quad.y = target.user_info.object.y
	handle_info.handle_quad.width = target.user_info.object.width
	handle_info.handle_quad.height = target.user_info.object.height
	handle_info.handle_quad.scale_x = target.user_info.object.scale_x
	handle_info.handle_quad.scale_y = target.user_info.object.scale_y
	handle_info.handle_quad.center_x = target.user_info.object.center_x
	handle_info.handle_quad.center_y = target.user_info.object.center_y
	handle_info.handle_quad.angle = target.user_info.object.angle
end

function ALittleIDE.IDEUITabChild:UpdateHandleQuadRemove(target)
	local handle_info = self._tab_quad_map[target]
	if handle_info == nil then
		return
	end
	self._tab_quad_container:RemoveChild(handle_info.handle_quad)
	self._tab_quad_map[target] = nil
end

function ALittleIDE.IDEUITabChild:HandleHandleContainerLButtonDown(event)
	self._container_drag = false
end

function ALittleIDE.IDEUITabChild:HandleHandleContainerLButtonUp(event)
	if self._container_drag then
		return
	end
	if self._tree_object == nil then
		return
	end
	local target = self._tree_object:EditPickUp(event.rel_x, event.rel_y)
	if target == nil then
		return
	end
	self:ShowHandleQuad(target)
end

function ALittleIDE.IDEUITabChild:HandleHandleContainerDragBegin(event)
	self:ClearHandQuad()
	local target = self._tree_object:EditPickUp(event.rel_x, event.rel_y)
	if target == nil then
		return
	end
	self._container_drag_x = event.rel_x
	self._container_drag_y = event.rel_y
	self._container_drag_parent = target.logic_parent
	self._tab_select_rect.visible = true
	self._tab_select_rect.x = self._container_drag_x
	self._tab_select_rect.y = self._container_drag_y
	self._tab_select_rect.width = 0
	self._tab_select_rect.height = 0
end

function ALittleIDE.IDEUITabChild:HandleHandleContainerDrag(event)
	if self._container_drag_x == nil then
		return
	end
	local min_x = self._container_drag_x
	local max_x = event.rel_x
	if self._container_drag_x > event.rel_x then
		min_x = event.rel_x
		max_x = self._container_drag_x
	end
	local min_y = self._container_drag_y
	local max_y = event.rel_y
	if self._container_drag_y > event.rel_y then
		min_y = event.rel_y
		max_y = self._container_drag_y
	end
	self._tab_select_rect.x = min_x
	self._tab_select_rect.y = min_y
	self._tab_select_rect.width = max_x - min_x
	self._tab_select_rect.height = max_y - min_y
end

function ALittleIDE.IDEUITabChild:HandleHandleContainerDragEnd(event)
	self._tab_select_rect.visible = false
	if self._container_drag_parent == nil then
		return
	end
	local rel_x, rel_y = self._container_drag_parent.user_info.object:LocalToGlobal(self._edit_screen)
	local offset_x, offset_y = self._container_drag_parent.user_info.object:GetChildOffset()
	rel_x = rel_x + (offset_x)
	rel_y = rel_y + (offset_y)
	local min_x = self._container_drag_x
	local max_x = event.rel_x
	if self._container_drag_x > event.rel_x then
		min_x = event.rel_x
		max_x = self._container_drag_x
	end
	min_x = min_x - (rel_x)
	max_x = max_x - (rel_x)
	local min_y = self._container_drag_y
	local max_y = event.rel_y
	if self._container_drag_y > event.rel_y then
		min_y = event.rel_y
		max_y = self._container_drag_y
	end
	min_y = min_y - (rel_y)
	max_y = max_y - (rel_y)
	local list = {}
	for index, tree_logic in ___ipairs(self._container_drag_parent.childs) do
		if tree_logic:SelectPickRange(min_x, min_y, max_x, max_y) then
			ALittle.List_Push(list, tree_logic)
		end
	end
	self:ShowHandleQuadList(list)
	self._container_drag_x = nil
	self._container_drag_y = nil
	self._container_drag_parent = nil
	self._container_drag = true
end

function ALittleIDE.IDEUITabChild:HandleSelectRightExItemClick(event)
	local tree = event.target._user_data
	if tree == nil then
		return
	end
	self:ShowHandleQuad(tree)
end

function ALittleIDE.IDEUITabChild:HandleScaleContainerLButtonDown(event)
	local shift = (A_UISystem.sym_map[1073742049] ~= nil or A_UISystem.sym_map[1073742053] ~= nil)
	local scale = self._tab_screen.container.scale_x
	if shift then
		scale = scale - 0.1
		if scale < 0 then
			scale = 0
		end
	else
		scale = scale + 0.1
	end
	self._tab_screen.container.scale_x = scale
	self._tab_screen.container.scale_y = scale
	self._tab_screen:AdjustScrollBar()
	ALittleIDE.g_IDECenter.center:UpdateToolScale(scale)
end

function ALittleIDE.IDEUITabChild:HandleEditScaleChanged(event)
	self._tab_screen.container.scale_x = event.scale
	self._tab_screen.container.scale_y = event.scale
	self._tab_screen:AdjustScrollBar()
end

function ALittleIDE.IDEUITabChild:GetScale()
	return self._tab_screen.container.scale_x
end

function ALittleIDE.IDEUITabChild:HandleHandleQuadLButtonDown(event)
	local handle_info = event.target._user_data
	handle_info.buttondown_lock = true
	handle_info.buttondown_count = event.count
end

function ALittleIDE.IDEUITabChild:HandleHandleQuadLButtonUp(event)
	local handle_info = event.target._user_data
	if handle_info.buttondown_lock ~= true then
		return
	end
	self:HideHandleQuad(handle_info.target)
	if handle_info.buttondown_count >= 2 then
		ALittleIDE.g_IDEAttrControlDialog:ShowDialog(handle_info.target.user_info.object)
	else
		ALittleIDE.g_IDEAttrControlDialog:HideDialog()
	end
end

function ALittleIDE.IDEUITabChild.ControlCopyInfoCmp(a, b)
	return a.index < b.index
end

function ALittleIDE.IDEUITabChild:HandleHandleQuadKeyDown(event)
	if event.sym == 99 and event.mod & 0x00c0 ~= 0 then
		local copy_list = {}
		local copy_list_count = 0
		for target, handle_info in ___pairs(self._tab_quad_map) do
			if handle_info.target.logic_parent ~= nil then
				local info = {}
				info.module = self._module
				info.index = handle_info.target.logic_parent:GetChildIndex(handle_info.target)
				info.info = handle_info.target:CalcInfo()
				copy_list_count = copy_list_count + 1
				copy_list[copy_list_count] = info
			end
		end
		if copy_list_count > 0 then
			ALittle.List_Sort(copy_list, ALittleIDE.IDEUITabChild.ControlCopyInfoCmp)
			ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
		end
		return
	end
	if event.sym == 120 and event.mod & 0x00c0 ~= 0 then
		local copy_list = {}
		local copy_list_count = 0
		for target, handle_info in ___pairs(self._tab_quad_map) do
			local info = {}
			info.module = self._module
			info.index = handle_info.target.logic_parent:GetChildIndex(handle_info.target)
			info.info = handle_info.target:CalcInfo()
			copy_list_count = copy_list_count + 1
			copy_list[copy_list_count] = info
		end
		if copy_list_count > 0 then
			ALittle.List_Sort(copy_list, ALittleIDE.IDEUITabChild.ControlCopyInfoCmp)
			ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
			local revoke_bind = ALittle.RevokeBind()
			for target, handle_info in ___pairs(self._tab_quad_map) do
				handle_info.target:TreeCut(revoke_bind)
			end
			self._revoke_list:PushRevoke(revoke_bind)
		end
		return
	end
	if event.sym == 127 then
		local revoke_bind = ALittle.RevokeBind()
		local has_target = false
		for target, handle_info in ___pairs(self._tab_quad_map) do
			handle_info.target:TreeDelete(revoke_bind)
			has_target = true
		end
		if has_target then
			self._tab_quad_map = {}
			self._tab_quad_container:RemoveAllChild()
			self._revoke_list:PushRevoke(revoke_bind)
		end
		return
	end
	if event.sym == 118 and event.mod & 0x00c0 ~= 0 then
		local handle_info = event.target._user_data
		local common_parent = handle_info.target.logic_parent
		local child_index = 1
		if common_parent == nil then
			common_parent = handle_info.target
		else
			child_index = common_parent:GetChildIndex(handle_info.target) + 1
		end
		self:RightControlTreePasteImpl(common_parent, nil, child_index)
		return
	end
	local delta_x = 0
	local delta_y = 0
	if event.sym == 1073741904 then
		delta_x = -1
	elseif event.sym == 1073741903 then
		delta_x = 1
	elseif event.sym == 1073741906 then
		delta_y = -1
	elseif event.sym == 1073741905 then
		delta_y = 1
	else
		return
	end
	local common_parent = nil
	for tree_target, handle_info in ___pairs(self._tab_quad_map) do
		common_parent = tree_target.logic_parent
		break
	end
	if common_parent == nil then
		return
	end
	if ALittleIDE.g_IDEEnum.can_move_child_map[common_parent.user_info.default.__class] == nil then
		return
	end
	local revoke_bind = ALittle.RevokeBind()
	local has_target = false
	for target, handle_info in ___pairs(self._tab_quad_map) do
		target:DragXY(delta_x, delta_y)
		self:UpdateHandleQuadLayout(target)
		has_target = true
		local revoke = ALittleIDE.IDEDragXYRevoke(target, delta_x, delta_y)
		revoke_bind:PushRevoke(revoke)
	end
	if has_target == false then
		return
	end
	self._revoke_list:PushRevoke(revoke_bind)
	self.save = false
end

function ALittleIDE.IDEUITabChild:HandleHandleQuadDragBegin(event)
	local common_parent = nil
	for tree_target, handle_info in ___pairs(self._tab_quad_map) do
		common_parent = tree_target.logic_parent
		break
	end
	if common_parent == nil then
		return
	end
	if ALittleIDE.g_IDEEnum.can_move_child_map[common_parent.user_info.default.__class] == nil then
		return
	end
	for target, handle_info in ___pairs(self._tab_quad_map) do
		handle_info.delta_x = 0
		handle_info.delta_y = 0
		handle_info.lock_x_or_y = nil
		handle_info.buttondown_lock = false
	end
	self.save = false
end

function ALittleIDE.IDEUITabChild:HandleHandleQuadDrag(event)
	local common_parent = nil
	for tree_target, handle_info in ___pairs(self._tab_quad_map) do
		common_parent = tree_target.logic_parent
		break
	end
	if common_parent == nil then
		return
	end
	if ALittleIDE.g_IDEEnum.can_move_child_map[common_parent.user_info.default.__class] == nil then
		return
	end
	local shift = (A_UISystem.sym_map[1073742049] ~= nil or A_UISystem.sym_map[1073742053] ~= nil)
	for target, handle_info in ___pairs(self._tab_quad_map) do
		local delta_x = event.delta_x
		local delta_y = event.delta_y
		if shift then
			if handle_info.lock_x_or_y == nil then
				handle_info.lock_x_or_y = ALittle.Math_Abs(delta_x) > ALittle.Math_Abs(delta_y)
			end
			if handle_info.lock_x_or_y then
				delta_y = 0
			else
				delta_x = 0
			end
		else
			handle_info.lock_x_or_y = nil
		end
		local old_abs_x = event.abs_x - delta_x
		local old_abs_y = event.abs_y - delta_y
		local old_rel_x, old_rel_y = target.user_info.object.show_parent:GlobalToLocalMatrix2D(old_abs_x, old_abs_y)
		local new_rel_x, new_rel_y = target.user_info.object.show_parent:GlobalToLocalMatrix2D(event.abs_x, event.abs_y)
		delta_x = new_rel_x - old_rel_x
		delta_y = new_rel_y - old_rel_y
		target:DragXY(delta_x, delta_y)
		self:UpdateHandleQuadLayout(target)
		handle_info.delta_x = handle_info.delta_x + delta_x
		handle_info.delta_y = handle_info.delta_y + delta_y
	end
end

function ALittleIDE.IDEUITabChild:HandleHandleQuadDragEnd(event)
	local revoke_bind = ALittle.RevokeBind()
	local has_target = false
	for target, handle_info in ___pairs(self._tab_quad_map) do
		has_target = true
		local revoke = ALittleIDE.IDEDragXYRevoke(target, handle_info.delta_x, handle_info.delta_y)
		revoke_bind:PushRevoke(revoke)
	end
	if has_target == false then
		return
	end
	self._revoke_list:PushRevoke(revoke_bind)
end

function ALittleIDE.IDEUITabChild:HandleHandleQuadRButtonDown(event)
	local handle_info = event.target._user_data
	local target = handle_info.target
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("获取焦点", Lua.Bind(self.ShowTreeItemFocus, self, target))
	menu:AddItem("拾取父节点", Lua.Bind(self.PickParent, self, target), target.user_info.root)
	menu:AddItem("设置", Lua.Bind(ALittleIDE.g_IDEAttrControlDialog.ShowDialog, ALittleIDE.g_IDEAttrControlDialog, target.user_info.object))
	menu:AddItem("文本编辑", Lua.Bind(self.TextEdit, self, target), ALittleIDE.g_IDEEnum.text_edit_display_map[target.user_info.default.__class] == nil)
	menu:AddItem("上移", Lua.Bind(target.TransferUp, target), target.user_info.root or target.user_info.child_type ~= "child")
	menu:AddItem("下移", Lua.Bind(target.TransferDown, target), target.user_info.root or target.user_info.child_type ~= "child")
	menu:AddItem("添加", Lua.Bind(ALittleIDE.g_IDECenter.center.control_tree.ShowAddDialog, ALittleIDE.g_IDECenter.center.control_tree, target), not target.is_tree)
	menu:AddItem("添加Image", Lua.Bind(ALittleIDE.g_IDECenter.center.control_tree.ShowAddImageDialog, ALittleIDE.g_IDECenter.center.control_tree, target), not target.is_tree)
	menu:AddItem("添加Text", Lua.Bind(ALittleIDE.g_IDECenter.center.control_tree.ShowAddTextDialog, ALittleIDE.g_IDECenter.center.control_tree, target), not target.is_tree)
	menu:AddItem("复制", Lua.Bind(self.Copy, self, target))
	menu:AddItem("粘贴", Lua.Bind(self.Paste, self, target))
	menu:AddItem("剪切", Lua.Bind(self.Cut, self, target), target.user_info.root)
	menu:AddItem("删除", Lua.Bind(self.Delete, self, target), target.user_info.root)
	menu:AddItem("跳转", Lua.Bind(self.Jump, self, target), not target.user_info.extends_root)
	menu:AddItem("生成成员变量代码", Lua.Bind(self.GenerateClassMember, self, target), target.is_tree and target.user_info.base.__target_class == nil and target.user_info.default.__target_class == nil)
	menu:Show()
end

function ALittleIDE.IDEUITabChild:HandleHandleSizeQuadDragBegin(event)
	local target_handle_info = event.target._user_data
	local target = target_handle_info.target
	local parent = ALittle.Cast(ALittleIDE.IDEUITreeLogic, ALittle.DisplayGroup, target.logic_parent)
	if parent ~= nil and ALittleIDE.g_IDEEnum.can_move_child_map[parent.user_info.default.__class] == nil then
		return
	end
	for child, handle_info in ___pairs(self._tab_quad_map) do
		handle_info.delta_width = 0
		handle_info.delta_height = 0
		handle_info.lock_width_or_height = nil
	end
	self.save = false
end

function ALittleIDE.IDEUITabChild:HandleHandleSizeQuadDrag(event)
	local handle_info = event.target._user_data
	local target = handle_info.target
	local parent = ALittle.Cast(ALittleIDE.IDEUITreeLogic, ALittle.DisplayGroup, target.logic_parent)
	if parent ~= nil and ALittleIDE.g_IDEEnum.can_move_child_map[parent.user_info.default.__class] == nil then
		return
	end
	local shift = (A_UISystem.sym_map[1073742049] ~= nil or A_UISystem.sym_map[1073742053] ~= nil)
	local delta_x = event.delta_x
	local delta_y = event.delta_y
	if shift then
		if handle_info.lock_width_or_height == nil then
			handle_info.lock_width_or_height = ALittle.Math_Abs(delta_x) > ALittle.Math_Abs(delta_y)
		end
		if handle_info.lock_width_or_height then
			delta_y = 0
		else
			delta_x = 0
		end
	else
		handle_info.lock_width_or_height = nil
	end
	local old_abs_x = event.abs_x - delta_x
	local old_abs_y = event.abs_y - delta_y
	local old_rel_x, old_rel_y = target.user_info.object:GlobalToLocalMatrix2D(old_abs_x, old_abs_y)
	local new_rel_x, new_rel_y = target.user_info.object:GlobalToLocalMatrix2D(event.abs_x, event.abs_y)
	delta_x = new_rel_x - old_rel_x
	delta_y = new_rel_y - old_rel_y
	local quad_width = handle_info.handle_quad.width + delta_x
	if quad_width < 0 then
		delta_x = -handle_info.handle_quad.width
	end
	local quad_height = handle_info.handle_quad.height + delta_y
	if quad_height < 0 then
		delta_y = -handle_info.handle_quad.height
	end
	target:DragWH(delta_x, delta_y)
	handle_info.handle_quad.width = handle_info.handle_quad.width + delta_x
	handle_info.handle_quad.height = handle_info.handle_quad.height + delta_y
	handle_info.delta_width = handle_info.delta_width + delta_x
	handle_info.delta_height = handle_info.delta_height + delta_y
	self:UpdateHandleQuadLayout(target)
end

function ALittleIDE.IDEUITabChild:HandleHandleSizeQuadDragEnd(event)
	local handle_info = event.target._user_data
	local target = handle_info.target
	local revoke = ALittleIDE.IDEDragWHRevoke(target, handle_info.delta_width, handle_info.delta_height)
	self._revoke_list:PushRevoke(revoke)
end

function ALittleIDE.IDEUITabChild:HandleHandleSizeQuadMoveIn(event)
	ALittle.System_SetHVDragCursor()
end

function ALittleIDE.IDEUITabChild:HandleHandleSizeQuadMoveOut(event)
	ALittle.System_SetNormalCursor()
end

function ALittleIDE.IDEUITabChild:Copy(target)
	local copy_list = {}
	local copy_list_count = 0
	for child, handle_info in ___pairs(self._tab_quad_map) do
		local info = {}
		info.index = handle_info.target.logic_parent:GetChildIndex(handle_info.target)
		info.info = handle_info.target:CalcInfo()
		copy_list_count = copy_list_count + 1
		copy_list[copy_list_count] = info
	end
	if copy_list_count > 0 then
		ALittle.List_Sort(copy_list, ALittleIDE.IDEUITabChild.ControlCopyInfoCmp)
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
	end
end

function ALittleIDE.IDEUITabChild:RightControlTreePasteImpl(target, copy_list, child_index, revoke_bind, callback)
	if copy_list == nil then
		local text_info = ALittle.System_GetClipboardText()
		if text_info == nil then
			g_AUITool:ShowNotice("错误", "剪切板的内容不能粘帖")
			if callback ~= nil then
				callback(false, nil)
			end
			return
		end
		local error, copy_list_tmp = Lua.TCall(ALittle.String_JsonDecode, text_info)
		if error ~= nil or ALittle.List_Len(copy_list_tmp) == 0 then
			g_AUITool:ShowNotice("错误", "剪切板的内容不能粘帖")
			if callback ~= nil then
				callback(false, nil)
			end
			return
		end
		copy_list = copy_list_tmp
	end
	for k, info in ___ipairs(copy_list) do
		if info.info.__class == nil and info.info.__extends == nil then
			g_AUITool:ShowNotice("错误", "剪切板的内容不能粘帖")
			if callback ~= nil then
				callback(false, nil)
			end
			return
		end
		if info.module ~= nil and info.module ~= self._module then
			g_AUITool:ShowNotice("错误", "剪切板的内容属于其他模块不能粘帖")
			if callback ~= nil then
				callback(false, nil)
			end
			return
		end
	end
	self:ClearHandQuad()
	local clazz = target.user_info.default.__class
	if ALittleIDE.g_IDEEnum.can_add_child_map[clazz] and ALittleIDE.g_IDEEnum.child_show_map[clazz] == nil then
		local add_list = {}
		local add_list_count = 0
		local inner_revoke_bind = ALittle.RevokeBind()
		for k, info in ___ipairs(copy_list) do
			if k == 1 then
				local tree_object = target:TreePaste(info.info, "child", child_index, false, inner_revoke_bind)
				add_list_count = add_list_count + 1
				add_list[add_list_count] = tree_object
			else
				local tree_object = target:TreePaste(info.info, "child", child_index, true, inner_revoke_bind)
				add_list_count = add_list_count + 1
				add_list[add_list_count] = tree_object
			end
		end
		if revoke_bind ~= nil then
			revoke_bind:PushRevoke(inner_revoke_bind)
		else
			self._revoke_list:PushRevoke(inner_revoke_bind)
		end
		if callback ~= nil then
			callback(true, add_list)
		end
	else
		ALittleIDE.g_IDECenter.center.control_tree:ShowPasteDialog(target, copy_list[1].info, child_index, revoke_bind, callback)
	end
end

function ALittleIDE.IDEUITabChild:Paste(target)
	if target.is_tree then
		self:RightControlTreePasteImpl(target)
	else
		local common_parent = target.logic_parent
		local child_index = 1
		if common_parent == nil then
			common_parent = target
		else
			child_index = common_parent:GetChildIndex(target) + 1
		end
		self:RightControlTreePasteImpl(common_parent, nil, child_index)
	end
end

function ALittleIDE.IDEUITabChild:Delete(target)
	local revoke_bind = ALittle.RevokeBind()
	local has_target = false
	for child, handle_info in ___pairs(self._tab_quad_map) do
		handle_info.target:TreeDelete(revoke_bind)
		has_target = true
	end
	if has_target then
		self._tab_quad_map = {}
		self._tab_quad_container:RemoveAllChild()
		self._revoke_list:PushRevoke(revoke_bind)
	end
end

function ALittleIDE.IDEUITabChild:Cut(target)
	local copy_list = {}
	local copy_list_count = 0
	for child, handle_info in ___pairs(self._tab_quad_map) do
		local info = {}
		info.index = handle_info.target.logic_parent:GetChildIndex(handle_info.target)
		info.info = handle_info.target:CalcInfo()
		copy_list_count = copy_list_count + 1
		copy_list[copy_list_count] = info
	end
	if copy_list_count > 0 then
		ALittle.List_Sort(copy_list, ALittleIDE.IDEUITabChild.ControlCopyInfoCmp)
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
		local revoke_bind = ALittle.RevokeBind()
		for child, handle_info in ___pairs(self._tab_quad_map) do
			handle_info.target:TreeCut(revoke_bind)
		end
		self._revoke_list:PushRevoke(revoke_bind)
	end
end

function ALittleIDE.IDEUITabChild:Jump(target)
	local extends_module = target.user_info.base.__module
	if extends_module == nil then
		extends_module = target.user_info.module
	end
	local extends_name = target.user_info.base.__extends
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(extends_module)
	if ui_manager == nil then
		return
	end
	local control_info = ui_manager.control_map[extends_name]
	if control_info == nil then
		g_AUITool:ShowNotice("错误", "控件不存在:" .. extends_name)
		return
	end
	ALittleIDE.g_IDECenter.center.content_edit:StartEditControlBySelect(extends_module, extends_name)
end

function ALittleIDE.IDEUITabChild:GenerateClassMember(target)
	if not target.is_tree then
		g_AUITool:ShowNotice("错误", "容器才能生成成员变量代码")
		return
	end
	local target_class = target.user_info.base.__target_class
	if target_class == nil then
		target_class = target.user_info.default.__target_class
	end
	if target_class == nil then
		g_AUITool:ShowNotice("错误", "没有设置插件类")
		return
	end
	if ALittleIDE.g_IDEProject.project.code == nil then
		return
	end
	local find_text = ALittle.String_Join(target_class, ".")
	local info = ALittleIDE.g_IDEProject.project.code:FindGoto(find_text)
	if info == nil then
		g_AUITool:ShowNotice("错误", "找不到插件类:" .. find_text)
		return
	end
	local tab_child = ALittleIDE.g_IDECenter.center.code_list:OpenByFullPath(info.file_path, info.line_start, info.char_start, info.line_end, info.char_end)
	if tab_child == nil then
		g_AUITool:ShowNotice("错误", "找不到插件类:" .. find_text)
		return
	end
	local member_list = {}
	for index, child in ___ipairs(target.childs) do
		child:GenerateClassMember(member_list)
	end
	if ALittle.List_Len(member_list) == 0 then
		return
	end
	local text = ALittle.String_Join(member_list, "")
	tab_child.edit:EditFocus(info.line_end + 2, 0, nil, nil, true)
	tab_child.edit:InsertText(text, true)
end
ALittleIDE.IDEUITabChild.GenerateClassMember = Lua.CoWrap(ALittleIDE.IDEUITabChild.GenerateClassMember)

function ALittleIDE.IDEUITabChild:TextEdit(target)
	local object = target.user_info.object
	if self._control_tabchild_textinput == nil then
		self._control_tabchild_textinput = ALittleIDE.g_Control:CreateControl("aui_rename_image_input", self)
		self._control_tabchild_textinput.width = 200
		A_LayerManager:AddToModal(self._control_tabchild_textinput)
	end
	self._control_tabchild_textinput.visible = true
	local x, y = object:LocalToGlobal()
	self._control_tabchild_textinput.text = object.text
	self._control_tabchild_textinput.x = x
	self._control_tabchild_textinput.y = y
	self._control_tabchild_textinput._user_data = target
	self._control_tabchild_textinput:SelectAll()
	A_UISystem.focus = self._control_tabchild_textinput.show_input
end

function ALittleIDE.IDEUITabChild:PickParent(target)
	local parent = target.logic_parent
	if parent == nil then
		return
	end
	self:ShowHandleQuad(parent)
end

function ALittleIDE.IDEUITabChild:HandleRenameConfirm(event)
	local target = self._control_tabchild_textinput._user_data
	if target == nil then
		return
	end
	self._control_tabchild_textinput._user_data = nil
	self._control_tabchild_textinput.visible = false
	local text = self._control_tabchild_textinput.text
	if text == "" then
		return
	end
	target:ChangeText(text)
end

function ALittleIDE.IDEUITabChild:ShowTreeItemFocus(target)
	if self._tree_object == nil then
		return
	end
	if target ~= self._tree_object then
		local parent = target.logic_parent
		while parent ~= nil and parent ~= self._tree_object do
			parent.fold = true
			parent = parent.logic_parent
		end
	end
	self._tree_object.fold = true
	self._tree_screen:AdjustScrollBar()
	local x, y = target:LocalToGlobal(self._tree_screen.container)
	local target_x = (self._tree_screen.view_width - target.width / 2) / 2 - x
	local target_y = (self._tree_screen.view_height - target.height) / 2 - y
	if self._tree_loop_x ~= nil then
		self._tree_loop_x:Stop()
		self._tree_loop_x = nil
	end
	if self._tree_loop_y ~= nil then
		self._tree_loop_y:Stop()
		self._tree_loop_y = nil
	end
	self._tree_loop_x = ALittle.LoopLinear(self._tree_screen, "container_x", target_x, 300, 0)
	self._tree_loop_x:Start()
	self._tree_loop_y = ALittle.LoopLinear(self._tree_screen, "container_y", target_y, 300, 0)
	self._tree_loop_y:Start()
end

function ALittleIDE.IDEUITabChild:SearchLink(name)
	if self._tree_object == nil then
		return
	end
	if self._tree_search_info.name ~= name then
		self._tree_search_info.name = name
		self._tree_search_info.index = 0
	end
	local list = self._tree_object:SearchLink(name)
	local count = ALittle.List_Len(list)
	if count == 0 then
		return
	end
	self._tree_search_info.index = self._tree_search_info.index + 1
	self._tree_search_info.index = self._tree_search_info.index % (count + 1)
	local target = list[self._tree_search_info.index]
	self:ShowTreeItemFocus(target)
	target:ShowAttributePanel()
	self:ShowHandleQuad(target)
end

function ALittleIDE.IDEUITabChild:SearchEvent(name)
	if self._tree_object == nil then
		return
	end
	if self._tree_search_info.name ~= name then
		self._tree_search_info.name = name
		self._tree_search_info.index = 0
	end
	local list = self._tree_object:SearchEvent(name)
	local count = ALittle.List_Len(list)
	if count == 0 then
		return
	end
	self._tree_search_info.index = self._tree_search_info.index + 1
	self._tree_search_info.index = self._tree_search_info.index % (count + 1)
	local target = list[self._tree_search_info.index]
	self:ShowTreeItemFocus(target)
	target:ShowAttributePanel()
	self:ShowHandleQuad(target)
end

function ALittleIDE.IDEUITabChild:SearchDescription(name)
	if self._tree_object == nil then
		return
	end
	if self._tree_search_info.name ~= name then
		self._tree_search_info.name = name
		self._tree_search_info.index = 0
	end
	local list = self._tree_object:SearchDescription(name)
	local count = ALittle.List_Len(list)
	if count == 0 then
		return
	end
	self._tree_search_info.index = self._tree_search_info.index + 1
	self._tree_search_info.index = self._tree_search_info.index % (count + 1)
	local target = list[self._tree_search_info.index]
	self:ShowTreeItemFocus(target)
	target:ShowAttributePanel()
	self:ShowHandleQuad(target)
end

function ALittleIDE.IDEUITabChild:SearchTargetClass(name)
	if self._tree_object == nil then
		return
	end
	if self._tree_search_info.name ~= name then
		self._tree_search_info.name = name
		self._tree_search_info.index = 0
	end
	local list = self._tree_object:SearchTargetClass(name)
	local count = ALittle.List_Len(list)
	if count == 0 then
		return
	end
	self._tree_search_info.index = self._tree_search_info.index + 1
	self._tree_search_info.index = self._tree_search_info.index % (count + 1)
	local target = list[self._tree_search_info.index]
	self:ShowTreeItemFocus(target)
	target:ShowAttributePanel()
	self:ShowHandleQuad(target)
end

function ALittleIDE.IDEUITabChild:SearchTextureName(name)
	if self._tree_object == nil then
		return
	end
	if self._tree_search_info.name ~= name then
		self._tree_search_info.name = name
		self._tree_search_info.index = 0
	end
	local list = self._tree_object:SearchTextureName(name)
	local count = ALittle.List_Len(list)
	if count == 0 then
		return
	end
	self._tree_search_info.index = self._tree_search_info.index + 1
	self._tree_search_info.index = self._tree_search_info.index % (count + 1)
	local target = list[self._tree_search_info.index]
	self:ShowTreeItemFocus(target)
	target:ShowAttributePanel()
	self:ShowHandleQuad(target)
end

function ALittleIDE.IDEUITabChild:QuickDragAddControl(abs_x, abs_y, module_name, control_name)
	if self._tree_object == nil then
		return
	end
	local screen_x, screen_y = self._tab_screen:LocalToGlobal()
	if abs_x < screen_x or abs_y < screen_y or abs_x > screen_x + self._tab_screen.width or abs_y > screen_y + self._tab_screen.height then
		return
	end
	local global_x, global_y = self._tab_handle_quad:LocalToGlobal()
	local list = {}
	self._tree_object:QuickPickUp(abs_x - global_x, abs_y - global_y, list)
	local count = ALittle.List_Len(list)
	if count == 0 then
		return
	end
	local user_data = {}
	user_data.abs_x = abs_x
	user_data.abs_y = abs_y
	user_data.module_name = module_name
	user_data.control_name = control_name
	if count == 1 then
		self:QuickDragAddStart(list[1], user_data)
		return
	end
	local menu = AUIPlugin.AUIRightMenu()
	for index, tree in ___ipairs(list) do
		menu:AddItem(tree.title, Lua.Bind(self.QuickDragAddStart, self, tree, user_data))
	end
	menu:AddItem("取消", nil)
end

function ALittleIDE.IDEUITabChild:QuickDragAddStart(tree, user_data)
	local revoke_bind = ALittle.RevokeBind()
	local display_info = {}
	display_info.__module = user_data.module_name
	display_info.__extends = user_data.control_name
	local info = {}
	info.index = 1
	info.info = display_info
	local copy_list = {}
	copy_list[1] = info
	self:RightControlTreePasteImpl(tree, copy_list, tree.child_count + 1, revoke_bind, Lua.Bind(self.QuickDragAddEnd, self, tree, user_data, revoke_bind))
end

function ALittleIDE.IDEUITabChild:QuickDragAddEnd(tree, user_data, revoke_bind, result, add_list)
	if result == false then
		return
	end
	local global_x, global_y = tree.user_info.object:LocalToGlobal()
	for k, tree_object in ___ipairs(add_list) do
		tree_object.attr_panel:SetXType(1, revoke_bind)
		tree_object.attr_panel:SetYType(1, revoke_bind)
		tree_object.attr_panel:SetXValue(user_data.abs_x - global_x, revoke_bind)
		tree_object.attr_panel:SetYValue(user_data.abs_y - global_y, revoke_bind)
	end
	self._revoke_list:PushRevoke(revoke_bind)
end

end