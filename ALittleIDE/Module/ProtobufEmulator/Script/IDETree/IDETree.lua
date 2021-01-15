-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ProtobufEmulator == nil then _G.ProtobufEmulator = {} end
local ProtobufEmulator = ProtobufEmulator
local Lua = Lua
local ALittle = ALittle
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
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name = "ALittle.UIResizeEvent", ns_name = "ALittle", rl_name = "UIResizeEvent", hash_code = -431205740,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ProtobufEmulator.IDETreeLogic, " extends class:ProtobufEmulator.IDETreeLogic is nil")
ProtobufEmulator.IDETree = Lua.Class(ProtobufEmulator.IDETreeLogic, "ProtobufEmulator.IDETree")

function ProtobufEmulator.IDETree:Ctor(ctrl_sys, root)
	___rawset(self, "_body", ALittle.Linear(self._ctrl_sys))
	self._body.type = 2
	self._body.x = 8
	ALittle.DisplayGroup.AddChild(self, self._body)
	self._body:AddEventListener(___all_struct[-431205740], self, self.HandleChildResize)
end

function ProtobufEmulator.IDETree:Init()
	self._body.y = self._head.height
	self._body.width = self._head.width
	self._item_checkbutton.selected = true
	self._pickup_rect = false
	self._pickup_child = true
	self.fold = false
	self._upper_description = ALittle.String_Upper(self._item_title.text)
end

function ProtobufEmulator.IDETree:HandleLButtonDown(event)
	if event.count == 1 then
		return
	end
	self.fold = not self.fold
end

function ProtobufEmulator.IDETree:IsTree()
	return true
end

function ProtobufEmulator.IDETree:SearchBegin()
	self.fold = false
	self.light = false
	for k, child in ___ipairs(self._body.childs) do
		child:SearchBegin()
	end
end

function ProtobufEmulator.IDETree:SearchDescription(name, list)
	if list == nil then
		list = {}
	end
	if ALittle.String_Find(self._upper_description, name) ~= nil then
		ALittle.List_Push(list, self)
	end
	for k, child in ___ipairs(self._body.childs) do
		child:SearchDescription(name, list)
	end
	return list
end

function ProtobufEmulator.IDETree:HandleChildResize(event)
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ProtobufEmulator.IDETree:HandleHeadChanged(event)
	self._body.visible = event.target.selected
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ProtobufEmulator.IDETree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function ProtobufEmulator.IDETree:SetChildIndex(child, index)
	return self._body:SetChildIndex(child, index)
end

function ProtobufEmulator.IDETree:GetChildByIndex(index)
	return self._body:GetChildByIndex(index)
end

function ProtobufEmulator.IDETree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function ProtobufEmulator.IDETree.__getter:childs()
	return self._body.childs
end

function ProtobufEmulator.IDETree.__getter:child_count()
	return self._body.child_count
end

function ProtobufEmulator.IDETree:HasChild(child)
	return self._body:HasChild(child)
end

function ProtobufEmulator.IDETree:AddChild(child, index)
	if self._body.width < child.width then
		self._body.width = child.width
	end
	if self._body:AddChild(child, index) == false then
		return false
	end
	child._logic_parent = self
	self:DispatchEvent(___all_struct[-431205740], {})
	return true
end

function ProtobufEmulator.IDETree:RemoveChild(child)
	if self._body:RemoveChild(child) == false then
		return false
	end
	self:DispatchEvent(___all_struct[-431205740], {})
	return true
end

function ProtobufEmulator.IDETree:RemoveAllChild()
	self._body:RemoveAllChild()
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ProtobufEmulator.IDETree.__getter:width()
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

function ProtobufEmulator.IDETree.__getter:height()
	local head_height = 0.0
	if self._head ~= nil then
		head_height = self._head.height
	end
	if self._body.visible then
		return head_height + self._body.height
	end
	return head_height
end

function ProtobufEmulator.IDETree.__getter:fold()
	return self._body.visible
end

function ProtobufEmulator.IDETree.__setter:fold(value)
	if value == self._body.visible then
		return
	end
	self._body.visible = value
	self._item_checkbutton.selected = value
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ProtobufEmulator.IDETree.__getter:max_right()
	return self.width
end

function ProtobufEmulator.IDETree.__getter:max_bottom()
	return self.height
end

end