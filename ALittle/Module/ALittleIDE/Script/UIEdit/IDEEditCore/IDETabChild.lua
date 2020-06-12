-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

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
ALittle.RegStruct(-1328054622, "ALittleIDE.IDETabChildSearchInfo", {
name = "ALittleIDE.IDETabChildSearchInfo", ns_name = "ALittleIDE", rl_name = "IDETabChildSearchInfo", hash_code = -1328054622,
name_list = {"name","index"},
type_list = {"string","int"},
option_map = {}
})
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name = "ALittle.UIMoveOutEvent", ns_name = "ALittle", rl_name = "UIMoveOutEvent", hash_code = -1202439334,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1068858139, "ALittleIDE.IDETabChildQuickDragAddUserData", {
name = "ALittleIDE.IDETabChildQuickDragAddUserData", ns_name = "ALittleIDE", rl_name = "IDETabChildQuickDragAddUserData", hash_code = -1068858139,
name_list = {"abs_x","abs_y","control_name"},
type_list = {"double","double","string"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name = "ALittle.UIResizeEvent", ns_name = "ALittle", rl_name = "UIResizeEvent", hash_code = -431205740,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(40651933, "ALittle.UILButtonUpEvent", {
name = "ALittle.UILButtonUpEvent", ns_name = "ALittle", rl_name = "UILButtonUpEvent", hash_code = 40651933,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name = "ALittle.UIButtonDragEndEvent", ns_name = "ALittle", rl_name = "UIButtonDragEndEvent", hash_code = 150587926,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(322885752, "ALittleIDE.IDETabChildControlLine", {
name = "ALittleIDE.IDETabChildControlLine", ns_name = "ALittleIDE", rl_name = "IDETabChildControlLine", hash_code = 322885752,
name_list = {"quad","size_quad","size_quad_container"},
type_list = {"ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name = "ALittle.UIMoveInEvent", ns_name = "ALittle", rl_name = "UIMoveInEvent", hash_code = 544684311,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(882286932, "ALittle.UIKeyEvent", {
name = "ALittle.UIKeyEvent", ns_name = "ALittle", rl_name = "UIKeyEvent", hash_code = 882286932,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})
ALittle.RegStruct(1290936016, "ALittleIDE.IDETabChildHandleInfo", {
name = "ALittleIDE.IDETabChildHandleInfo", ns_name = "ALittleIDE", rl_name = "IDETabChildHandleInfo", hash_code = 1290936016,
name_list = {"display_group","handle_quad","focus_quad","size_quad_container","target","buttondown_lock","delta_x","delta_y","lock_x_or_y","delta_width","delta_height","lock_width_or_height"},
type_list = {"ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject","ALittleIDE.IDETreeLogic","bool","double","double","bool","double","double","bool"},
option_map = {}
})
ALittle.RegStruct(1301789264, "ALittle.UIButtonDragBeginEvent", {
name = "ALittle.UIButtonDragBeginEvent", ns_name = "ALittle", rl_name = "UIButtonDragBeginEvent", hash_code = 1301789264,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1337289812, "ALittle.UIButtonDragEvent", {
name = "ALittle.UIButtonDragEvent", ns_name = "ALittle", rl_name = "UIButtonDragEvent", hash_code = 1337289812,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1883782801, "ALittle.UILButtonDownEvent", {
name = "ALittle.UILButtonDownEvent", ns_name = "ALittle", rl_name = "UILButtonDownEvent", hash_code = 1883782801,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})

assert(ALittle.UIEventDispatcher, " extends class:ALittle.UIEventDispatcher is nil")
IDETabChild = Lua.Class(ALittle.UIEventDispatcher, "ALittleIDE.IDETabChild")

function IDETabChild:Ctor(name, save)
	___rawset(self, "_name", name)
	___rawset(self, "_save", save)
	___rawset(self, "_group", ALittle.CreateKeyWeakMap())
	___rawset(self, "_tab_body", g_Control:CreateControl("ide_edit_tab_screen", self))
	___rawset(self, "_tree_screen", g_Control:CreateControl("ide_edit_tree_screen", self))
	___rawset(self, "_control_screen", g_Control:CreateControl("ide_edit_control_screen", self))
	___rawset(self, "_anti_panel", g_Control:CreateControl("ide_edit_anti_panel", self))
	___rawset(self, "_tree_object", nil)
	self._tab_screen.container = ALittle.DisplayGroup(g_Control)
	self._tab_screen.container.scale_x = 1
	self._tab_screen.container.scale_y = 1
	self._tab_container.width = g_IDEProject.project.config:GetConfig("default_show_width", 800)
	self._tab_container.height = g_IDEProject.project.config:GetConfig("default_show_height", 600)
	self._tab_screen:RejustScrollBar()
	self._tab_select_container.visible = g_IDEUICenter.singleselect
	self._tab_handle_quad:AddEventListener(___all_struct[1883782801], self, self.HandleHandleContainerLButtonDown)
	self._tab_quad_container:RemoveAllChild()
	___rawset(self, "_tab_quad_map", {})
	self._tab_handdrag_container.visible = g_IDEUICenter.handdrag
	self._tab_handdrag_quad.drag_trans_target = self._tab_screen
	self._tab_dragadd_container.visible = false
	self._tab_scale_container.visible = g_IDEUICenter.scale
	self._tab_scale_quad:AddEventListener(___all_struct[1883782801], self, self.HandleScaleContainerLButtonDown)
	___rawset(self, "_tree_search_info", {})
	self._tree_search_info.name = ""
	self._tree_search_info.index = 0
	self._tab_body._user_data = self
	self._tree_screen._user_data = self
	___rawset(self, "_revoke_list", IDERevokeList())
	___rawset(self, "_tree_loop_x", nil)
	___rawset(self, "_tree_loop_y", nil)
	self:AddEventListener(___all_struct[-1676610185], self, self.HandleSavePng)
end

function IDETabChild:HandleTreeSizeChanged(event)
	self._tree_screen:RejustScrollBar()
end

function IDETabChild:HandleSavePng(event)
	ALittle.Log(event.path)
	g_Control:SaveControlToFile(self._tree_object.user_info.object, event.path)
end

function IDETabChild.__getter:name()
	return self._name
end

function IDETabChild.__getter:tab_screen()
	return self._tab_screen
end

function IDETabChild.__getter:tab_body()
	return self._tab_body
end

function IDETabChild.__getter:tree_screen()
	return self._tree_screen
end

function IDETabChild.__getter:control_screen()
	return self._control_screen
end

function IDETabChild.__getter:anti_panel()
	return self._anti_panel
end

function IDETabChild.__getter:group()
	return self._group
end

function IDETabChild.__getter:revoke_list()
	return self._revoke_list
end

function IDETabChild.__getter:tree_object()
	return self._tree_object
end

function IDETabChild.__getter:save()
	return self._save
end

function IDETabChild:Save(value)
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
	local info = self._tree_object:CalcInfo()
	local error = g_IDEProject.project.ui:SaveControl(self._name, info)
	if error ~= nil then
		return
	end
	self._save = value
	self:UpdateTitle()
end

function IDETabChild:Rename(name)
	self._name = name
	self:UpdateTitle()
end

function IDETabChild:UpdateTitle()
	if self._tree_object == nil then
		return
	end
	local text = self._tree_object:GetDesc()
	if text == "" then
		text = self._name
		if ALittle.String_Len(self._name) > 15 then
			text = "..." .. ALittle.String_Sub(self._name, -15, -1)
		end
	end
	if self._save == false then
		text = text .. " *"
	end
	g_IDETabManager.main_tab:SetChildText(self._tab_body, text)
end

function IDETabChild.__getter:total_title()
	local text = self._tree_object:GetDesc()
	if text == "" then
		return self._name
	end
	return self._name .. "(" .. text .. ")"
end

function IDETabChild:SetEditWH(width, height)
	self._tab_container.width = width
	self._tab_container.height = height
	self._tab_screen:RejustScrollBar()
	for target, handle_info in ___pairs(self._tab_quad_map) do
		self:UpdateHandleQuadLayout(target)
	end
end

function IDETabChild:CanDeleteControl(name)
	if self._tree_object == nil then
		return nil
	end
	local info = self._tree_object:CalcInfo()
	local map = IDEUIUtility_GetExtends(info)
	if map[name] then
		return "被其他控件引用:" .. name
	end
	return nil
end

function IDETabChild:SelectAlign(align_type)
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
		local parent = first_target.logic_parent
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
		local revoke = IDEDragXYRevoke(first_target, drag_x, drag_y)
		self._revoke_list:PushRevoke(revoke)
	else
		local revoke_bind = IDERevokeBind()
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
				local revoke = IDEDragXYRevoke(target, drag_x, 0)
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
				local revoke = IDEDragXYRevoke(target, drag_x, 0)
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
				local revoke = IDEDragXYRevoke(target, drag_x, 0)
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
				local revoke = IDEDragXYRevoke(target, 0, drag_y)
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
				local revoke = IDEDragXYRevoke(target, 0, drag_y)
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
				local revoke = IDEDragXYRevoke(target, 0, drag_y)
				revoke_bind:PushRevoke(revoke)
			end
		end
		self._revoke_list:PushRevoke(revoke_bind)
	end
	self:Save(false)
end

function IDETabChild:ShowSelectLayer(value)
	self._tab_select_container.visible = value
end

function IDETabChild:ShowHandDragLayer(value)
	self._tab_handdrag_container.visible = value
end

function IDETabChild:ShowScaleLayer(value)
	self._tab_scale_container.visible = value
end

function IDETabChild:CreateByNew(type)
	local info = {}
	info.__class = type
	local object = ALittle.NewObject(ALittle[type], g_IDEProject.project.control)
	IDEUIUtility_NewGiveBaseCase(info, object)
	self._tab_object_container:AddChild(object)
	self._tree_object = IDEUIUtility_CreateTree(info, false, object, nil, self, true)
	self._tree_object:AddEventListener(___all_struct[-431205740], self, self.HandleTreeSizeChanged)
	self._tree_object.fold = true
	self._tree_screen:AddChild(self._tree_object)
	self._anti_panel:Init(self)
end

function IDETabChild:CreateByExtends(extends_v)
	local info = {}
	info.__extends = extends_v
	local object = g_IDEProject.project.control:CreateControl(extends_v)
	self._tab_object_container:AddChild(object)
	self._tree_object = IDEUIUtility_CreateTree(info, false, object, nil, self, true)
	self._tree_object:AddEventListener(___all_struct[-431205740], self, self.HandleTreeSizeChanged)
	self._tree_object.fold = true
	self._tree_screen:AddChild(self._tree_object)
	self._anti_panel:Init(self)
end

function IDETabChild:CreateBySelect(info)
	local object = g_IDEProject.project.control:CreateControl(self._name)
	self._tab_object_container:AddChild(object)
	self._tree_object = IDEUIUtility_CreateTree(info, false, object, nil, self, true)
	self._tree_object:AddEventListener(___all_struct[-431205740], self, self.HandleTreeSizeChanged)
	self._tree_object.fold = true
	self._tree_screen:AddChild(self._tree_object)
	self._anti_panel:Init(self)
end

function IDETabChild:IsShowHandleQuad(target)
	return self._tab_quad_map[target] ~= nil
end

function IDETabChild:FocusInHandleQuad(target)
	local handle_info = self._tab_quad_map[target]
	if handle_info == nil then
		return
	end
	A_UISystem.focus = handle_info.focus_quad
end

function IDETabChild:ShowHandleQuad(target, force_shift)
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
		common_parent = tree_target.logic_parent
		has_target = true
		break
	end
	if has_target and common_parent ~= target.logic_parent then
		local parent = target.logic_parent
		while parent ~= nil and common_parent ~= parent do
			target = parent
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
		for target, info in ___pairs(self._tab_quad_map) do
			local index = common_parent:GetChildIndex(target)
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
		local handle_quad = g_Control:CreateControl("ide_common_handle_quad", control_line)
		control_line.quad:AddEventListener(___all_struct[40651933], self, self.HandleHandleQuadLButtonUp)
		control_line.quad:AddEventListener(___all_struct[1883782801], self, self.HandleHandleQuadLButtonDown)
		control_line.quad:AddEventListener(___all_struct[1301789264], self, self.HandleHandleQuadDragBegin)
		control_line.quad:AddEventListener(___all_struct[1337289812], self, self.HandleHandleQuadDrag)
		control_line.quad:AddEventListener(___all_struct[150587926], self, self.HandleHandleQuadDragEnd)
		control_line.quad:AddEventListener(___all_struct[-641444818], self, self.HandleHandleQuadRButtonDown)
		control_line.quad:AddEventListener(___all_struct[-1604617962], self, self.HandleHandleQuadKeyDown)
		control_line.size_quad:AddEventListener(___all_struct[-1604617962], self, self.HandleHandleSizeQuadKeyDown)
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
			local display_group = ALittle.DisplayGroup(g_Control)
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

function IDETabChild:HideHandleQuad(target, shift)
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

function IDETabChild:UpdateHandleQuadLayout(target)
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

function IDETabChild:UpdateHandleQuadRemove(target)
	local handle_info = self._tab_quad_map[target]
	if handle_info == nil then
		return
	end
	self._tab_quad_container:RemoveChild(handle_info.handle_quad)
	self._tab_quad_map[target] = nil
end

function IDETabChild:HandleHandleContainerLButtonDown(event)
	if self._tree_object == nil then
		return
	end
	local target = self._tree_object:EditPickUp(event.rel_x, event.rel_y)
	if target == nil then
		return
	end
	self:ShowHandleQuad(target)
end

function IDETabChild:HandleSelectRightExItemClick(event)
	A_LayerManager:HideFromRight(self._select_right_exmenu)
	self._tab_right_exlinear:RemoveAllChild()
	local tree = event.target._user_data
	if tree == nil then
		return
	end
	self:ShowHandleQuad(tree)
end

function IDETabChild:HandleScaleContainerLButtonDown(event)
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
	self._tab_screen:RejustScrollBar()
	g_IDEUICenter:UpdateToolScale(scale)
end

function IDETabChild:SetScale(scale)
	self._tab_screen.container.scale_x = scale
	self._tab_screen.container.scale_y = scale
	self._tab_screen:RejustScrollBar()
end

function IDETabChild:GetScale()
	return self._tab_screen.container.scale_x
end

function IDETabChild:HandleHandleQuadLButtonDown(event)
	local handle_info = event.target._user_data
	handle_info.buttondown_lock = true
end

function IDETabChild:HandleHandleQuadLButtonUp(event)
	local handle_info = event.target._user_data
	if handle_info.buttondown_lock ~= true then
		return
	end
	self:HideHandleQuad(handle_info.target)
end

function IDETabChild.ControlCopyInfoCmp(a, b)
	return a.index < b.index
end

function IDETabChild:HandleHandleQuadKeyDown(event)
	if event.sym == 99 and ALittle.BitAnd(event.mod, 0x00c0) ~= 0 then
		local copy_list = {}
		local copy_list_count = 0
		for target, handle_info in ___pairs(self._tab_quad_map) do
			if handle_info.target.logic_parent ~= nil then
				local info = {}
				info.index = handle_info.target.logic_parent:GetChildIndex(handle_info.target)
				info.info = handle_info.target:CalcInfo()
				copy_list_count = copy_list_count + 1
				copy_list[copy_list_count] = info
			end
		end
		if copy_list_count > 0 then
			ALittle.List_Sort(copy_list, IDETabChild.ControlCopyInfoCmp)
			ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
		end
		return
	end
	if event.sym == 120 and ALittle.BitAnd(event.mod, 0x00c0) ~= 0 then
		local copy_list = {}
		local copy_list_count = 0
		for target, handle_info in ___pairs(self._tab_quad_map) do
			local info = {}
			info.index = handle_info.target.logic_parent:GetChildIndex(handle_info.target)
			info.info = handle_info.target:CalcInfo()
			copy_list_count = copy_list_count + 1
			copy_list[copy_list_count] = info
		end
		if copy_list_count > 0 then
			ALittle.List_Sort(copy_list, IDETabChild.ControlCopyInfoCmp)
			ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
			local revoke_bind = IDERevokeBind()
			for target, handle_info in ___pairs(self._tab_quad_map) do
				handle_info.target:TreeCut(revoke_bind)
			end
			self._revoke_list:PushRevoke(revoke_bind)
		end
		return
	end
	if event.sym == 127 then
		local revoke_bind = IDERevokeBind()
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
	if event.sym == 118 and ALittle.BitAnd(event.mod, 0x00c0) ~= 0 then
		local handle_info = event.target._user_data
		local common_parent = handle_info.target.logic_parent
		local child_index = 1
		if common_parent == nil then
			common_parent = handle_info.target
		else
			child_index = common_parent:GetChildIndex(handle_info.target)
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
	if g_IDEEnum.can_move_child_map[common_parent.user_info.default.__class] == nil then
		return
	end
	local revoke_bind = IDERevokeBind()
	local has_target = false
	for target, handle_info in ___pairs(self._tab_quad_map) do
		target:DragXY(delta_x, delta_y)
		self:UpdateHandleQuadLayout(target)
		has_target = true
		local revoke = IDEDragXYRevoke(target, delta_x, delta_y)
		revoke_bind:PushRevoke(revoke)
	end
	if has_target == false then
		return
	end
	self._revoke_list:PushRevoke(revoke_bind)
	self:Save(false)
end

function IDETabChild:HandleHandleQuadDragBegin(event)
	local common_parent = nil
	for tree_target, handle_info in ___pairs(self._tab_quad_map) do
		common_parent = tree_target.logic_parent
		break
	end
	if common_parent == nil then
		return
	end
	if g_IDEEnum.can_move_child_map[common_parent.user_info.default.__class] == nil then
		return
	end
	for target, handle_info in ___pairs(self._tab_quad_map) do
		handle_info.delta_x = 0
		handle_info.delta_y = 0
		handle_info.lock_x_or_y = ALittle.Math_Abs(event.delta_x) > ALittle.Math_Abs(event.delta_y)
		handle_info.buttondown_lock = false
	end
	self:Save(false)
end

function IDETabChild:HandleHandleQuadDrag(event)
	local common_parent = nil
	for tree_target, handle_info in ___pairs(self._tab_quad_map) do
		common_parent = tree_target.logic_parent
		break
	end
	if common_parent == nil then
		return
	end
	if g_IDEEnum.can_move_child_map[common_parent.user_info.default.__class] == nil then
		return
	end
	local shift = (A_UISystem.sym_map[1073742049] ~= nil or A_UISystem.sym_map[1073742053] ~= nil)
	for target, handle_info in ___pairs(self._tab_quad_map) do
		local delta_x = event.delta_x
		local delta_y = event.delta_y
		if shift then
			if handle_info.lock_x_or_y then
				delta_y = 0
			else
				delta_x = 0
			end
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

function IDETabChild:HandleHandleQuadDragEnd(event)
	local revoke_bind = IDERevokeBind()
	local has_target = false
	for target, handle_info in ___pairs(self._tab_quad_map) do
		has_target = true
		local revoke = IDEDragXYRevoke(target, handle_info.delta_x, handle_info.delta_y)
		revoke_bind:PushRevoke(revoke)
	end
	if has_target == false then
		return
	end
	self._revoke_list:PushRevoke(revoke_bind)
end

function IDETabChild:HandleHandleQuadRButtonDown(event)
	local handle_info = event.target._user_data
	local target = handle_info.target
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("获取焦点", Lua.Bind(self.ShowTreeItemFocus, self, target))
	menu:AddItem("拾取父节点", Lua.Bind(self.PickParent, self, target), target.user_info.root)
	menu:AddItem("文本编辑", Lua.Bind(self.TextEdit, self, target), g_IDEEnum.text_edit_display_map[target.user_info.default.__class] == nil)
	menu:AddItem("上移", Lua.Bind(target.TransferUp, target), target.user_info.root or target.user_info.child_type ~= "child")
	menu:AddItem("下移", Lua.Bind(target.TransferDown, target), target.user_info.root or target.user_info.child_type ~= "child")
	menu:AddItem("添加", Lua.Bind(g_IDEControlTree.ShowAddDialog, g_IDEControlTree, target), not target:IsTree())
	menu:AddItem("添加Image", Lua.Bind(g_IDEControlTree.ShowAddImageDialog, g_IDEControlTree, target), not target:IsTree())
	menu:AddItem("添加Text", Lua.Bind(g_IDEControlTree.ShowAddTextDialog, g_IDEControlTree, target), not target:IsTree())
	menu:AddItem("复制", Lua.Bind(self.Copy, self, target))
	menu:AddItem("粘贴", Lua.Bind(self.Paste, self, target))
	menu:AddItem("剪切", Lua.Bind(self.Cut, self, target), target.user_info.root)
	menu:AddItem("删除", Lua.Bind(self.Delete, self, target), target.user_info.root)
	menu:AddItem("替换", Lua.Bind(g_IDEControlTree.ShowReplaceDialog, g_IDEControlTree, target), target.user_info.root)
	menu:AddItem("跳转", Lua.Bind(self.Jump, self, target), not target.user_info.extends_root)
	menu:Show()
end

function IDETabChild:HandleHandleSizeQuadKeyDown(event)
end

function IDETabChild:HandleHandleSizeQuadDragBegin(event)
	local target_handle_info = event.target._user_data
	local target = target_handle_info.target
	local parent = target.logic_parent
	if parent ~= nil and g_IDEEnum.can_move_child_map[parent.user_info.default.__class] == nil then
		return
	end
	for target, handle_info in ___pairs(self._tab_quad_map) do
		handle_info.delta_width = 0
		handle_info.delta_height = 0
		handle_info.lock_width_or_height = ALittle.Math_Abs(event.delta_x) > ALittle.Math_Abs(event.delta_y)
	end
	self:Save(false)
end

function IDETabChild:HandleHandleSizeQuadDrag(event)
	local handle_info = event.target._user_data
	local target = handle_info.target
	local parent = target.logic_parent
	if parent ~= nil and g_IDEEnum.can_move_child_map[parent.user_info.default.__class] == nil then
		return
	end
	local shift = (A_UISystem.sym_map[1073742049] ~= nil or A_UISystem.sym_map[1073742053] ~= nil)
	local delta_x = event.delta_x
	local delta_y = event.delta_y
	if shift then
		if handle_info.lock_width_or_height then
			delta_y = 0
		else
			delta_x = 0
		end
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

function IDETabChild:HandleHandleSizeQuadDragEnd(event)
	local handle_info = event.target._user_data
	local target = handle_info.target
	local revoke = IDEDragWHRevoke(target, handle_info.delta_width, handle_info.delta_height)
	self._revoke_list:PushRevoke(revoke)
end

function IDETabChild:HandleHandleSizeQuadMoveIn(event)
	ALittle.System_SetHVDragCursor()
end

function IDETabChild:HandleHandleSizeQuadMoveOut(event)
	ALittle.System_SetNormalCursor()
end

function IDETabChild:Copy(target)
	local copy_list = {}
	local copy_list_count = 0
	for target, handle_info in ___pairs(self._tab_quad_map) do
		local info = {}
		info.index = handle_info.target.logic_parent:GetChildIndex(handle_info.target)
		info.info = handle_info.target:CalcInfo()
		copy_list_count = copy_list_count + 1
		copy_list[copy_list_count] = info
	end
	if copy_list_count > 0 then
		ALittle.List_Sort(copy_list, IDETabChild.ControlCopyInfoCmp)
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
	end
end

function IDETabChild:RightControlTreePasteImpl(target, copy_list, child_index, revoke_bind, callback)
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
		if error ~= nil or ALittle.List_MaxN(copy_list_tmp) == 0 then
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
	end
	local clazz = target.user_info.default.__class
	if g_IDEEnum.can_add_child_map[clazz] and g_IDEEnum.child_show_map[clazz] == nil then
		local add_list = {}
		local add_list_count = 0
		local inner_revoke_bind = IDERevokeBind()
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
		g_IDEControlTree:ShowPasteDialog(target, copy_list[1].info, child_index, revoke_bind, callback)
	end
end

function IDETabChild:Paste(target)
	if target:IsTree() then
		self:RightControlTreePasteImpl(target)
	else
		local common_parent = target.logic_parent
		local child_index = 1
		if common_parent == nil then
			common_parent = target
		else
			child_index = common_parent:GetChildIndex(target)
		end
		self:RightControlTreePasteImpl(common_parent, nil, child_index)
	end
end

function IDETabChild:Delete(target)
	local revoke_bind = IDERevokeBind()
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
end

function IDETabChild:Cut(target)
	local copy_list = {}
	local copy_list_count = 0
	for target, handle_info in ___pairs(self._tab_quad_map) do
		local info = {}
		info.index = handle_info.target.logic_parent:GetChildIndex(handle_info.target)
		info.info = handle_info.target:CalcInfo()
		copy_list_count = copy_list_count + 1
		copy_list[copy_list_count] = info
	end
	if copy_list_count > 0 then
		ALittle.List_Sort(copy_list, IDETabChild.ControlCopyInfoCmp)
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
		local revoke_bind = IDERevokeBind()
		for target, handle_info in ___pairs(self._tab_quad_map) do
			handle_info.target:TreeCut(revoke_bind)
		end
		self._revoke_list:PushRevoke(revoke_bind)
	end
end

function IDETabChild:Jump(target)
	local extends_name = target.user_info.base.__extends
	local control_info = g_IDEProject.project.ui.control_map[extends_name]
	if control_info == nil then
		g_AUITool:ShowNotice("错误", "控件不存在:" .. extends_name)
		return
	end
	g_IDETabManager:StartEditControlBySelect(control_info.name, control_info.info)
end

function IDETabChild:TextEdit(target)
	local object = target.user_info.object
	if self._control_tabchild_textinput == nil then
		self._control_tabchild_textinput = g_Control:CreateControl("ide_rename_image_input", self)
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

function IDETabChild:PickParent(target)
	local parent = target.logic_parent
	if parent == nil then
		return
	end
	self:ShowHandleQuad(parent)
end

function IDETabChild:HandleRenameConfirm(event)
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

function IDETabChild:ShowTreeItemFocus(target)
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
	self._tree_screen:RejustScrollBar()
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

function IDETabChild:SearchLink(name)
	if self._tree_object == nil then
		return
	end
	if self._tree_search_info.name ~= name then
		self._tree_search_info.name = name
		self._tree_search_info.index = 0
	end
	local list = self._tree_object:SearchLink(name)
	local count = ALittle.List_MaxN(list)
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

function IDETabChild:SearchEvent(name)
	if self._tree_object == nil then
		return
	end
	if self._tree_search_info.name ~= name then
		self._tree_search_info.name = name
		self._tree_search_info.index = 0
	end
	local list = self._tree_object:SearchEvent(name)
	local count = ALittle.List_MaxN(list)
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

function IDETabChild:SearchDescription(name)
	if self._tree_object == nil then
		return
	end
	if self._tree_search_info.name ~= name then
		self._tree_search_info.name = name
		self._tree_search_info.index = 0
	end
	local list = self._tree_object:SearchDescription(name)
	local count = ALittle.List_MaxN(list)
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

function IDETabChild:SearchTargetClass(name)
	if self._tree_object == nil then
		return
	end
	if self._tree_search_info.name ~= name then
		self._tree_search_info.name = name
		self._tree_search_info.index = 0
	end
	local list = self._tree_object:SearchTargetClass(name)
	local count = ALittle.List_MaxN(list)
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

function IDETabChild:SearchTextureName(name)
	if self._tree_object == nil then
		return
	end
	if self._tree_search_info.name ~= name then
		self._tree_search_info.name = name
		self._tree_search_info.index = 0
	end
	local list = self._tree_object:SearchTextureName(name)
	local count = ALittle.List_MaxN(list)
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

function IDETabChild:QuickDragAddControl(abs_x, abs_y, control_name)
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
	local count = ALittle.List_MaxN(list)
	if count == 0 then
		return
	end
	local user_data = {}
	user_data.abs_x = abs_x
	user_data.abs_y = abs_y
	user_data.control_name = control_name
	if count == 1 then
		self:QuickDragAddStart(list[1], user_data)
		return
	end
	if self._quick_right_exmenu == nil then
		self._quick_right_exmenu = g_Control:CreateControl("ide_quick_drag_menu", self)
	end
	self._quick_right_exlinear:RemoveAllChild()
	for index, tree in ___ipairs(list) do
		local item = g_Control:CreateControl("ide_common_item_button")
		item:AddEventListener(___all_struct[-449066808], self, self.HandleQuickRightExItemClick)
		item._user_data = tree
		item.text = tree.title
		self._quick_right_exlinear:AddChild(item)
	end
	local item = g_Control:CreateControl("ide_common_item_button")
	item:AddEventListener(___all_struct[-449066808], self, self.HandleQuickRightExItemClick)
	item._user_data = nil
	item.text = "取消"
	self._quick_right_exlinear:AddChild(item)
	self._quick_right_exmenu.height = self._quick_right_exlinear.height + 5
	if abs_x + self._quick_right_exmenu.width > A_UISystem.view_width then
		abs_x = A_UISystem.view_width - self._quick_right_exmenu.width
	end
	self._quick_right_exmenu.x = abs_x
	self._quick_right_exmenu.y = abs_y
	self._quick_right_exmenu._user_data = user_data
	A_LayerManager:ShowFromRight(self._quick_right_exmenu)
end

function IDETabChild:HandleQuickRightExItemClick(event)
	A_LayerManager:HideFromRight(self._quick_right_exmenu)
	self._quick_right_exlinear:RemoveAllChild()
	local user_data = self._quick_right_exmenu._user_data
	local tree = event.target._user_data
	if tree == nil then
		return
	end
	self:QuickDragAddStart(tree, user_data)
end

function IDETabChild:QuickDragAddStart(tree, user_data)
	local revoke_bind = IDERevokeBind()
	local display_info = {}
	display_info.__extends = user_data.control_name
	local info = {}
	info.index = 1
	info.info = display_info
	local copy_list = {}
	copy_list[1] = info
	self:RightControlTreePasteImpl(tree, copy_list, tree.child_count + 1, revoke_bind, Lua.Bind(self.QuickDragAddEnd, self, tree, user_data, revoke_bind))
end

function IDETabChild:QuickDragAddEnd(tree, user_data, revoke_bind, result, add_list)
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

