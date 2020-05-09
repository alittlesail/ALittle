-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

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
ALittle.RegStruct(1883782801, "ALittle.UILButtonDownEvent", {
name = "ALittle.UILButtonDownEvent", ns_name = "ALittle", rl_name = "UILButtonDownEvent", hash_code = 1883782801,
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
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name = "ALittle.UIMoveInEvent", ns_name = "ALittle", rl_name = "UIMoveInEvent", hash_code = 544684311,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1001723540, "ALittle.UIMouseMoveEvent", {
name = "ALittle.UIMouseMoveEvent", ns_name = "ALittle", rl_name = "UIMouseMoveEvent", hash_code = -1001723540,
name_list = {"target","abs_x","abs_y","rel_x","rel_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name = "ALittle.UIMoveOutEvent", ns_name = "ALittle", rl_name = "UIMoveOutEvent", hash_code = -1202439334,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name = "ALittle.UIResizeEvent", ns_name = "ALittle", rl_name = "UIResizeEvent", hash_code = -431205740,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(Emulator.IDETreeLogic, " extends class:Emulator.IDETreeLogic is nil")
IDETree = Lua.Class(Emulator.IDETreeLogic, "Emulator.IDETree")

function IDETree:Ctor(ctrl_sys, field_name)
	___rawset(self, "_field_name", field_name)
end

function IDETree:Init()
	self._item_button.selected = false
	self._item_button:AddEventListener(___all_struct[1883782801], self, self.HandleLButtonDown)
	self._item_button:AddEventListener(___all_struct[-449066808], self, self.HandleClick)
	self._item_button:AddEventListener(___all_struct[544684311], self, self.HandleMoveIn)
	self._item_button:AddEventListener(___all_struct[-1001723540], self, self.HandleMouseMove)
	self._item_button:AddEventListener(___all_struct[-1202439334], self, self.HandleMoveOut)
	self._item_button._user_data = self
	self._body = ALittle.Linear(self._ctrl_sys)
	self._body.type = 2
	self._body.x = 8
	self._body.y = self._head.height
	self._body.width = self._head.width
	self._item_checkbutton.selected = true
	ALittle.DisplayGroup.AddChild(self, self._body)
	self._body:AddEventListener(___all_struct[-431205740], self, self.HandleChildResize)
	self._pickup_rect = false
	self._pickup_child = true
	self.fold = false
end

function IDETree:HandleLButtonDown(event)
	if event.count == 1 then
		return
	end
	self.fold = not self.fold
end

function IDETree:IsTree()
	return true
end

function IDETree:GetDescription()
	return self._item_title.text
end

function IDETree:SearchDescription(name, list)
	if list == nil then
		list = {}
	end
	local description = self:GetDescription()
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

function IDETree:HandleChildResize(event)
	self:DispatchEvent(___all_struct[-431205740], {})
end

function IDETree:HandleHeadChanged(event)
	self._body.visible = event.target.selected
	self:DispatchEvent(___all_struct[-431205740], {})
end

function IDETree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function IDETree:SetChildIndex(child, index)
	return self._body:SetChildIndex(child, index)
end

function IDETree:GetChildByIndex(index)
	return self._body:GetChildByIndex(index)
end

function IDETree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function IDETree.__getter:childs()
	return self._body.childs
end

function IDETree.__getter:child_count()
	return self._body.child_count
end

function IDETree:HasChild(child)
	return self._body:HasChild(child)
end

function IDETree:AddChild(child, index)
	if self._body:AddChild(child, index) == false then
		return false
	end
	child._logic_parent = self
	self:DispatchEvent(___all_struct[-431205740], {})
	return true
end

function IDETree:RemoveChild(child)
	if self._body:RemoveChild(child) == false then
		return false
	end
	self:DispatchEvent(___all_struct[-431205740], {})
	return true
end

function IDETree:RemoveAllChild()
	self._body:RemoveAllChild()
	self:DispatchEvent(___all_struct[-431205740], {})
end

function IDETree.__getter:width()
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

function IDETree.__getter:height()
	local head_height = 0.0
	if self._head ~= nil then
		head_height = self._head.height
	end
	if self._body.visible then
		return head_height + self._body.height
	end
	return head_height
end

function IDETree.__getter:fold()
	return self._body.visible
end

function IDETree.__setter:fold(value)
	if value == self._body.visible then
		return
	end
	self._body.visible = value
	self._item_checkbutton.selected = value
	self:DispatchEvent(___all_struct[-431205740], {})
end

function IDETree.__getter:max_right()
	return self.width
end

function IDETree.__getter:max_bottom()
	return self.height
end

