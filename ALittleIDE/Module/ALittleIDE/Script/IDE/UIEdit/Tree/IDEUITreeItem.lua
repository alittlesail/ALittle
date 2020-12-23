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
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name = "ALittle.UIButtonDragEndEvent", ns_name = "ALittle", rl_name = "UIButtonDragEndEvent", hash_code = 150587926,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})

assert(ALittleIDE.IDEUITreeLogic, " extends class:ALittleIDE.IDEUITreeLogic is nil")
ALittleIDE.IDEUITreeItem = Lua.Class(ALittleIDE.IDEUITreeLogic, "ALittleIDE.IDEUITreeItem")

function ALittleIDE.IDEUITreeItem:Ctor(ctrl_sys, user_info, tab_child)
	if self._user_info.extends then
		___rawset(self, "_item", ctrl_sys:CreateControl("tree_item_disabled", self))
	else
		___rawset(self, "_item", ctrl_sys:CreateControl("tree_item", self))
	end
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._text_icon.visible = false
	self._image_icon.visible = false
	self._check_icon.visible = false
	self._button_icon.visible = false
	self._radio_icon.visible = false
	self._quad_icon.visible = false
	self._dropdown_icon.visible = false
	self._input_icon.visible = false
	local name_map = {}
	name_map["Text"] = self._text_icon
	name_map["TextArea"] = self._text_icon
	name_map["RichArea"] = self._text_icon
	name_map["TextInput"] = self._input_icon
	name_map["TextEdit"] = self._input_icon
	name_map["ImageInput"] = self._input_icon
	name_map["ImageEdit"] = self._input_icon
	name_map["RichEdit"] = self._input_icon
	name_map["RichInput"] = self._input_icon
	name_map["Quad"] = self._quad_icon
	name_map["Image"] = self._image_icon
	name_map["Grid9Image"] = self._image_icon
	name_map["Sprite"] = self._image_icon
	name_map["ImagePlay"] = self._image_icon
	name_map["SpritePlay"] = self._image_icon
	name_map["FramePlay"] = self._image_icon
	name_map["Piechart"] = self._image_icon
	name_map["Triangle"] = self._image_icon
	name_map["TextButton"] = self._button_icon
	name_map["ScrollButton"] = self._button_icon
	name_map["SpringTextButton"] = self._button_icon
	name_map["Slider"] = self._button_icon
	name_map["TextCheckButton"] = self._check_icon
	name_map["TextRadioButton"] = self._radio_icon
	name_map["DropDown"] = self._dropdown_icon
	local icon = name_map[self._user_info.default.__class]
	if icon ~= nil then
		icon.visible = true
	end
	self._extends_icon.visible = self._user_info.extends_root
	self._item_button.selected = false
	self._item_button.group = self._tab_child.group
	self._item_button:AddEventListener(___all_struct[-449066808], self, self.HandleClick)
	self._item_button:AddEventListener(___all_struct[1301789264], self, self.HandleDragBegin)
	self._item_button:AddEventListener(___all_struct[1337289812], self, self.HandleDrag)
	self._item_button:AddEventListener(___all_struct[150587926], self, self.HandleDragEnd)
	self._item_button:AddEventListener(___all_struct[-641444818], ALittleIDE.g_IDECenter.center.control_tree, ALittleIDE.g_IDECenter.center.control_tree.HandleControlTreeItemRightClick)
	self._item_button._user_data = self
end

function ALittleIDE.IDEUITreeItem:UpdateDesc()
	local title = ""
	if self._user_info.child_type ~= nil and self._user_info.child_type ~= "child" then
		title = title .. "[" .. self._user_info.child_type .. "]"
	end
	local link = self._user_info.base.__link
	if link == nil then
		link = self._user_info.default.__link
	end
	if link ~= nil then
		title = title .. link
	elseif self._user_info.base.description ~= nil then
		title = title .. self._user_info.base.description
	elseif self._user_info.default.description ~= nil then
		title = title .. self._user_info.default.description
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

function ALittleIDE.IDEUITreeItem.__getter:is_tree()
	return false
end

function ALittleIDE.IDEUITreeItem.__getter:fold()
	return false
end

function ALittleIDE.IDEUITreeItem.__setter:fold(value)
end

function ALittleIDE.IDEUITreeItem:GetDataListForAdd()
	return {}
end

function ALittleIDE.IDEUITreeItem:CalcInfo()
	return ALittle.String_CopyTable(self._user_info.base)
end

function ALittleIDE.IDEUITreeItem:SearchLink(name, list)
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
			return list
		end
	end
	return list
end

function ALittleIDE.IDEUITreeItem:SearchEvent(name, list)
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
				return list
			end
		end
	end
	return list
end

function ALittleIDE.IDEUITreeItem:SearchDescription(name, list)
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
			return list
		end
	end
	return list
end

function ALittleIDE.IDEUITreeItem:SearchTargetClass(name, list)
	if list == nil then
		list = {}
	end
	local target_class = self._user_info.base.__target_class
	if target_class == nil then
		target_class = self._user_info.default.__target_class
	end
	if target_class ~= nil then
		local target_class_str = ALittle.String_Join(target_class, ".")
		if ALittle.String_Find(target_class_str, name) ~= nil then
			ALittle.List_Push(list, self)
			return list
		end
	end
	return list
end

function ALittleIDE.IDEUITreeItem:SearchTextureName(name, list)
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
			return list
		end
	end
	return list
end

function ALittleIDE.IDEUITreeItem:EditPickUp(x, y)
	if self._user_info.extends then
		return nil
	end
	local object = self._user_info.object
	local pick_this, rel_x, rel_y = object:PickUpSelf(x, y)
	if pick_this ~= nil then
		return self
	end
	return nil
end

function ALittleIDE.IDEUITreeItem:QuickPickUp(x, y, list)
end

function ALittleIDE.IDEUITreeItem:SelectPickUp(x, y)
	if self._user_info.extends then
		return nil, nil
	end
	local pick_this, rel_x, rel_y = self._item_button:PickUpSelf(x, y)
	if pick_this ~= nil then
		return nil, self
	end
	return nil, nil
end

function ALittleIDE.IDEUITreeItem:GenerateClassMember(list)
	local link = self._user_info.base.__link
	if link == nil then
		link = self._user_info.default.__link
	end
	if link == nil then
		return
	end
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

end