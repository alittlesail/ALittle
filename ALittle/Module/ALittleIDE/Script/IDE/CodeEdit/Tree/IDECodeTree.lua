-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

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
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name = "ALittle.UIResizeEvent", ns_name = "ALittle", rl_name = "UIResizeEvent", hash_code = -431205740,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittleIDE.IDECodeTreeLogic, " extends class:ALittleIDE.IDECodeTreeLogic is nil")
IDECodeTree = Lua.Class(ALittleIDE.IDECodeTreeLogic, "ALittleIDE.IDECodeTree")

function IDECodeTree:Ctor(ctrl_sys, user_info)
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_code_tree_head", self))
	ALittle.DisplayGroup.AddChild(self, self._head)
	self._item_button.selected = false
	self._item_button.group = user_info.group
	self._item_button:AddEventListener(___all_struct[1883782801], self, self.HandleLButtonDown)
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
	if user_info.root then
		self._item_title.text = self._user_info.module_name
	else
		self._item_title.text = self._user_info.name
	end
	self:Refresh()
end

function IDECodeTree:HandleLButtonDown(event)
	if event.count == 1 then
		return
	end
	self.fold = not self.fold
end

function IDECodeTree.__getter:is_tree()
	return true
end

function IDECodeTree:Refresh()
	local map = ALittle.File_GetFileNameListByDir(self._user_info.path)
	local remove = nil
	for index, child in ___ipairs(self.childs) do
		local attr = map[child._user_info.name]
		if attr == nil then
			if remove == nil then
				remove = {}
			end
			ALittle.List_Push(remove, child)
		end
		map[child._user_info.name] = nil
		child:Refresh()
	end
	local add = nil
	for name, attr in ___pairs(map) do
		if add == nil then
			add = {}
		end
		ALittle.List_Push(add, name)
	end
	if add ~= nil then
		ALittle.List_Sort(add)
		for index, name in ___ipairs(add) do
			local attr = map[name]
			if attr.mode == "directory" then
				local info = {}
				info.module_name = self._user_info.module_name
				info.name = name
				info.path = self._user_info.path .. "/" .. name
				info.group = self._user_info.group
				info.root = false
				self:AddChild(IDECodeTree(self._ctrl_sys, info))
			elseif ALittle.File_GetFileExtByPathAndUpper(name) == "ALITTLE" then
				local info = {}
				info.module_name = self._user_info.module_name
				info.name = name
				info.path = self._user_info.path .. "/" .. name
				info.group = self._user_info.group
				info.root = false
				self:AddChild(IDECodeTreeItem(self._ctrl_sys, info))
			end
		end
	end
end

function IDECodeTree:SearchFile(name, list)
	if list == nil then
		list = {}
	end
	for k, child in ___ipairs(self._body.childs) do
		child:SearchFile(name, list)
	end
	return list
end

function IDECodeTree:SearchDefine(name, list)
	if list == nil then
		list = {}
	end
	for k, child in ___ipairs(self._body.childs) do
		child:SearchDefine(name, list)
	end
	return list
end

function IDECodeTree:HandleChildResize(event)
	self:DispatchEvent(___all_struct[-431205740], {})
end

function IDECodeTree:HandleHeadChanged(event)
	self._body.visible = event.target.selected
	self:DispatchEvent(___all_struct[-431205740], {})
end

function IDECodeTree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function IDECodeTree:SetChildIndex(child, index)
	return self._body:SetChildIndex(child, index)
end

function IDECodeTree:GetChildByIndex(index)
	return self._body:GetChildByIndex(index)
end

function IDECodeTree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function IDECodeTree.__getter:childs()
	return self._body.childs
end

function IDECodeTree.__getter:child_count()
	return self._body.child_count
end

function IDECodeTree:HasChild(child)
	return self._body:HasChild(child)
end

function IDECodeTree:AddChild(child, index)
	if self._body:AddChild(child, index) == false then
		return false
	end
	child._logic_parent = self
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
	return true
end

function IDECodeTree:RemoveChild(child)
	if self._body:RemoveChild(child) == false then
		return false
	end
	child.group = nil
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
	return true
end

function IDECodeTree:RemoveAllChild()
	for index, child in ___ipairs(self.childs) do
		child.group = nil
	end
	self._body:RemoveAllChild()
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
end

function IDECodeTree.__getter:width()
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

function IDECodeTree.__getter:height()
	local head_height = 0.0
	if self._head ~= nil then
		head_height = self._head.height
	end
	if self._body.visible then
		return head_height + self._body.height
	end
	return head_height
end

function IDECodeTree.__getter:fold()
	return self._body.visible
end

function IDECodeTree.__setter:fold(value)
	if value == self._body.visible then
		return
	end
	self._body.visible = value
	self._item_checkbutton.selected = value
	self:DispatchEvent(___all_struct[-431205740], {})
end

function IDECodeTree.__getter:max_right()
	return self.width
end

function IDECodeTree.__getter:max_bottom()
	return self.height
end

