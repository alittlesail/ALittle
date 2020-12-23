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
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag","count"},
type_list = {"ALittle.DisplayObject","bool","int"},
option_map = {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name = "ALittle.UIResizeEvent", ns_name = "ALittle", rl_name = "UIResizeEvent", hash_code = -431205740,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name = "ALittle.UIButtonDragEndEvent", ns_name = "ALittle", rl_name = "UIButtonDragEndEvent", hash_code = 150587926,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})

assert(ALittleIDE.IDEUITreeLogic, " extends class:ALittleIDE.IDEUITreeLogic is nil")
ALittleIDE.IDEUITree = Lua.Class(ALittleIDE.IDEUITreeLogic, "ALittleIDE.IDEUITree")

function ALittleIDE.IDEUITree:Ctor(ctrl_sys, user_info, tab_child)
	if self._user_info.extends then
		___rawset(self, "_head", ctrl_sys:CreateControl("tree_head_disabled", self))
	else
		___rawset(self, "_head", ctrl_sys:CreateControl("tree_head", self))
	end
	ALittle.DisplayGroup.AddChild(self, self._head)
	self._extends_icon.visible = self._user_info.extends_root
	self._item_button.selected = false
	self._item_button.group = self._tab_child.group
	self._item_button:AddEventListener(___all_struct[1883782801], self, self.HandleLButtonDown)
	self._item_button:AddEventListener(___all_struct[-449066808], self, self.HandleClick)
	self._item_button:AddEventListener(___all_struct[1301789264], self, self.HandleDragBegin)
	self._item_button:AddEventListener(___all_struct[1337289812], self, self.HandleDrag)
	self._item_button:AddEventListener(___all_struct[150587926], self, self.HandleDragEnd)
	self._item_button:AddEventListener(___all_struct[-641444818], ALittleIDE.g_IDECenter.center.control_tree, ALittleIDE.g_IDECenter.center.control_tree.HandleControlTreeItemRightClick)
	self._item_button._user_data = self
	___rawset(self, "_body", ALittle.Linear(ctrl_sys))
	self._body.type = 2
	self._body.x = 8
	self._body.y = self._head.height
	self._body.width = self._head.width
	self._item_checkbutton.selected = true
	ALittle.DisplayGroup.AddChild(self, self._body)
	self._body:AddEventListener(___all_struct[-431205740], self, self.HandleChildResize)
	___rawset(self, "_pickup_rect", false)
	___rawset(self, "_pickup_child", true)
	self.fold = false
end

function ALittleIDE.IDEUITree:UpdateDesc()
	local title = ""
	if self._user_info.child_type ~= nil and self._user_info.child_type ~= "child" then
		title = title .. "[" .. self._user_info.child_type .. "]"
	end
	title = title .. "[" .. self._user_info.default.__class .. "]"
	local link = self._user_info.base.__link
	if link == nil then
		link = self._user_info.default.__link
	end
	if self._user_info.base.description ~= nil then
		title = title .. self._user_info.base.description
	elseif self._user_info.default.description ~= nil then
		title = title .. self._user_info.default.description
	elseif link ~= nil then
		title = title .. link
	elseif self._user_info.base.text ~= nil then
		title = title .. self._user_info.base.text
	elseif self._user_info.default.text ~= nil then
		title = title .. self._user_info.default.text
	end
	self._item_button.text = title
	if self._user_info.child_type == nil then
		self._tab_child:UpdateTitle()
	end
end

function ALittleIDE.IDEUITree:HandleLButtonDown(event)
	if event.count == 1 then
		return
	end
	self.fold = not self.fold
end

function ALittleIDE.IDEUITree.__getter:is_tree()
	return true
end

function ALittleIDE.IDEUITree:GetDataListForAdd()
	local data_list = {}
	local data_list_count = 0
	local clazz = self._user_info.default.__class
	if ALittleIDE.g_IDEEnum.can_add_child_map[clazz] then
		local can_add = true
		for index, child in ___ipairs(self._body.childs) do
			if child.user_info.child_type == "child" and child.user_info.extends then
				can_add = false
				break
			end
		end
		if can_add then
			data_list_count = data_list_count + 1
			data_list[data_list_count] = "child"
		end
	end
	local show_list = ALittleIDE.g_IDEEnum.child_show_map[clazz]
	local show_list_count = 0
	if show_list ~= nil then
		for k, v in ___ipairs(show_list) do
			local can_add = true
			for index, child in ___ipairs(self._body.childs) do
				if child.user_info.child_type == v and child.user_info.extends then
					can_add = false
					break
				end
			end
			if can_add then
				data_list_count = data_list_count + 1
				data_list[data_list_count] = v
			end
		end
	end
	return data_list
end

function ALittleIDE.IDEUITree:CanAddChild()
	local clazz = self._user_info.default.__class
	if ALittleIDE.g_IDEEnum.can_add_child_map[clazz] then
		local can_add = true
		for index, child in ___ipairs(self._body.childs) do
			if child.user_info.child_type == "child" and child.user_info.extends then
				can_add = false
				break
			end
		end
		if can_add then
			return true
		end
	end
	return false
end

function ALittleIDE.IDEUITree:CalcInfo()
	local info = ALittle.String_CopyTable(self._user_info.base)
	info.__childs = nil
	local child_count = 0
	for k, v in ___ipairs(self._body.childs) do
		local child_type = nil
		if v._user_info.extends == false then
			child_type = v._user_info.child_type
		end
		if child_type == "child" then
			if info.__childs == nil then
				info.__childs = {}
			end
			child_count = child_count + 1
			info.__childs[child_count] = v:CalcInfo()
		elseif child_type ~= nil then
			info[child_type] = v:CalcInfo()
		end
	end
	return info
end

function ALittleIDE.IDEUITree:GenerateClassMember(list)
	local link = self._user_info.base.__link
	if link == nil then
		link = self._user_info.default.__link
	end
	if link ~= nil then
		local member = "\tprivate "
		if self._user_info.base.__target_class ~= nil then
			member = member .. ALittle.String_Join(self._user_info.base.__target_class, ".")
		elseif self._user_info.default.__target_class ~= nil then
			member = member .. ALittle.String_Join(self._user_info.default.__target_class, ".")
		elseif self._user_info.base.__class ~= nil then
			member = member .. "ALittle." .. self._user_info.base.__class
		else
			member = member .. "ALittle." .. self._user_info.default.__class
		end
		member = member .. " " .. link .. ";"
		local desc = self._user_info.base.description
		if desc == nil or desc == "" then
			desc = self._user_info.default.description
		end
		if desc ~= nil and desc ~= "" then
			member = member .. " // " .. desc
		end
		member = member .. "\n"
		ALittle.List_Push(list, member)
	end
	if self._user_info.base.__target_class ~= nil or self._user_info.default.__target_class ~= nil then
		return
	end
	for k, child in ___ipairs(self._body.childs) do
		child:GenerateClassMember(list)
	end
end

function ALittleIDE.IDEUITree:SearchLink(name, list)
	if list == nil then
		list = {}
	end
	local link = self._user_info.base.__link
	if link == nil then
		link = self._user_info.default.__link
	end
	if link ~= nil then
		if ALittle.String_Find(link, name) ~= nil then
			ALittle.List_Push(list, self)
		end
	end
	for k, child in ___ipairs(self._body.childs) do
		child:SearchLink(name, list)
	end
	return list
end

function ALittleIDE.IDEUITree:SearchEvent(name, list)
	if list == nil then
		list = {}
	end
	local event = self._user_info.base.__event
	if event == nil then
		event = self._user_info.default.__event
	end
	if event ~= nil then
		for k, v in ___ipairs(event) do
			if ALittle.String_Find(v.func, name) ~= nil then
				ALittle.List_Push(list, self)
				break
			end
		end
	end
	for k, child in ___ipairs(self._body.childs) do
		child:SearchEvent(name, list)
	end
	return list
end

function ALittleIDE.IDEUITree:SearchDescription(name, list)
	if list == nil then
		list = {}
	end
	local description = self._user_info.base.description
	if description == nil then
		description = self._user_info.default.description
	end
	if description ~= nil then
		if ALittle.String_Find(description, name) ~= nil then
			ALittle.List_Push(list, self)
		end
	end
	for k, child in ___ipairs(self._body.childs) do
		child:SearchDescription(name, list)
	end
	return list
end

function ALittleIDE.IDEUITree:SearchTargetClass(name, list)
	if list == nil then
		list = {}
	end
	local target_class = self._user_info.base.__target_class
	if target_class == nil then
		target_class = self._user_info.default.__target_class
	end
	if target_class ~= nil then
		local target_class_str = ALittle.String_Join(target_class, "")
		if ALittle.String_Find(target_class_str, name) ~= nil then
			ALittle.List_Push(list, self)
		end
	end
	for k, child in ___ipairs(self._body.childs) do
		child:SearchTargetClass(name, list)
	end
	return list
end

function ALittleIDE.IDEUITree:SearchTextureName(name, list)
	if list == nil then
		list = {}
	end
	local texture_name = self._user_info.base.texture_name
	if texture_name == nil then
		texture_name = self._user_info.default.texture_name
	end
	if texture_name ~= nil then
		if ALittle.String_Find(texture_name, name) ~= nil then
			ALittle.List_Push(list, self)
		end
	end
	for k, child in ___ipairs(self._body.childs) do
		child:SearchTextureName(name, list)
	end
	return list
end

function ALittleIDE.IDEUITree:EditPickUp(x, y)
	if self._user_info.extends then
		return nil
	end
	local object = self._user_info.object
	local pick_this, rel_x, rel_y = object:PickUpSelf(x, y)
	local offset_x, offset_y = object:GetChildOffset()
	rel_x = rel_x - offset_x
	rel_y = rel_y - offset_y
	local child_count = self._body.child_count
	local child_list = self._body.childs
	local i = child_count
	while true do
		if not(i >= 1) then break end
		local child = child_list[i]
		local target = child:EditPickUp(rel_x, rel_y)
		if target ~= nil then
			return target
		end
		i = i+(-1)
	end
	if pick_this ~= nil then
		return self
	end
	return nil
end

function ALittleIDE.IDEUITree:QuickPickUp(x, y, list)
	if self._user_info.extends then
		return
	end
	local object = self._user_info.object
	local pick_this, rel_x, rel_y = object:PickUpSelf(x, y)
	if pick_this ~= nil then
		ALittle.List_Push(list, self)
	end
	local child_count = self._body.child_count
	local child_list = self._body.childs
	local i = child_count
	while true do
		if not(i >= 1) then break end
		local child = child_list[i]
		child:QuickPickUp(rel_x, rel_y, list)
		i = i+(-1)
	end
end

function ALittleIDE.IDEUITree:SelectPickUp(x, y)
	if self._user_info.extends then
		return nil, nil
	end
	local pick_this, rel_x, rel_y = self._item_button:PickUpSelf(x, y)
	if self._body.visible then
		local child_count = self._body.child_count
		local child_list = self._body.childs
		local i = child_count
		while true do
			if not(i >= 1) then break end
			local parent, child = child_list[i]:SelectPickUp(rel_x, rel_y)
			if parent ~= nil or child ~= nil then
				return parent, child
			end
			i = i+(-1)
		end
	end
	if pick_this ~= nil then
		return self, nil
	end
	return nil, nil
end

function ALittleIDE.IDEUITree:HandleChildResize(event)
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ALittleIDE.IDEUITree:HandleHeadChanged(event)
	self._body.visible = event.target.selected
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ALittleIDE.IDEUITree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function ALittleIDE.IDEUITree:SetChildIndex(child, index)
	return self._body:SetChildIndex(child, index)
end

function ALittleIDE.IDEUITree:GetChildByIndex(index)
	return self._body:GetChildByIndex(index)
end

function ALittleIDE.IDEUITree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function ALittleIDE.IDEUITree.__getter:childs()
	return self._body.childs
end

function ALittleIDE.IDEUITree.__getter:child_count()
	return self._body.child_count
end

function ALittleIDE.IDEUITree:HasChild(child)
	return self._body:HasChild(child)
end

function ALittleIDE.IDEUITree:AddChild(child, index)
	if self._body:AddChild(child, index) == false then
		return false
	end
	child._logic_parent = self
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
	return true
end

function ALittleIDE.IDEUITree:RemoveChild(child)
	if self._body:RemoveChild(child) == false then
		return false
	end
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
	return true
end

function ALittleIDE.IDEUITree:SpliceChild(index, count)
	local result = self._body:SpliceChild(index, count)
	if result == 0 then
		return 0
	end
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
	return result
end

function ALittleIDE.IDEUITree:RemoveAllChild()
	self._body:RemoveAllChild()
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
end

function ALittleIDE.IDEUITree.__getter:width()
	local head_width = 0.0
	if self._head ~= nil then
		head_width = self._head.width
	end
	local body_width = 0.0
	if self._body.visible then
		local start_x = self._body.x
		body_width = start_x + self._body.width
		local childs = self._body.childs
		for k, v in ___ipairs(childs) do
			local child_width = start_x + v.x + v.width
			if body_width < child_width then
				body_width = child_width
			end
		end
	end
	if head_width > body_width then
		return head_width
	end
	return body_width
end

function ALittleIDE.IDEUITree.__getter:height()
	local head_height = 0.0
	if self._head ~= nil then
		head_height = self._head.height
	end
	if self._body.visible then
		return head_height + self._body.height
	end
	return head_height
end

function ALittleIDE.IDEUITree.__getter:fold()
	return self._body.visible
end

function ALittleIDE.IDEUITree.__setter:fold(value)
	if value == self._body.visible then
		return
	end
	self._body.visible = value
	self._item_checkbutton.selected = value
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ALittleIDE.IDEUITree.__getter:max_right()
	return self.width
end

function ALittleIDE.IDEUITree.__getter:max_bottom()
	return self.height
end

end