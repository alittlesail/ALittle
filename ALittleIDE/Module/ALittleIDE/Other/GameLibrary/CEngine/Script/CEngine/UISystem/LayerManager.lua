-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


ALittle.LayerManager = Lua.Class(nil, "ALittle.LayerManager")

function ALittle.LayerManager:Ctor()
	___rawset(self, "_normal_groups", {})
	___rawset(self, "_normal_group_count", 0)
	___rawset(self, "_modal_layer", ALittle.DisplayLayout(nil))
	__CPPAPI_DisplaySystem:AddSpecialChild(self._modal_layer.native_show)
	___rawset(self, "_right_layer", ALittle.DisplayLayout(nil))
	___rawset(self, "_right_show", nil)
	__CPPAPI_DisplaySystem:AddSpecialChild(self._right_layer.native_show)
	___rawset(self, "_tip_layer", ALittle.DisplayLayout(nil))
	self._tip_layer.disabled = true
	__CPPAPI_DisplaySystem:AddSpecialChild(self._tip_layer.native_show)
end

function ALittle.LayerManager:Shutdown()
	__CPPAPI_DisplaySystem:RemoveAllChild()
end

function ALittle.LayerManager.__getter:group_count()
	return self._normal_group_count
end

function ALittle.LayerManager:AddChild(child, index)
	if child == nil then
		return
	end
	if index == nil or index > self._normal_group_count or self._normal_group_count < 1 then
		self._normal_group_count = self._normal_group_count + 1
		self._normal_groups[self._normal_group_count] = child
		__CPPAPI_DisplaySystem:AddChild(child.native_show)
	else
		if index < 1 then
			index = 1
		end
		local back_child = self._normal_groups[index]
		__CPPAPI_DisplaySystem:AddChildBefore(back_child.native_show, child.native_show)
		ALittle.List_Insert(self._normal_groups, index, child)
		self._normal_group_count = self._normal_group_count + 1
	end
	child.width = A_UISystem.view_width
	child.height = A_UISystem.view_height
end

function ALittle.LayerManager:RemoveChild(child)
	if child == nil then
		return
	end
	local has_layer = false
	for index, value in ___ipairs(self._normal_groups) do
		if value == child then
			ALittle.List_Remove(self._normal_groups, index)
			has_layer = true
			break
		end
	end
	if has_layer == false then
		return
	end
	__CPPAPI_DisplaySystem:RemoveChild(child.native_show)
	self._normal_group_count = self._normal_group_count - 1
end

function ALittle.LayerManager:HandleViewResized(width, height)
	for group_index, group in ___ipairs(self._normal_groups) do
		group.width = width
		group.height = height
	end
	self._modal_layer.width = width
	self._modal_layer.height = height
	self._right_layer.width = width
	self._right_layer.height = height
	self._tip_layer.width = width
	self._tip_layer.height = height
	self:HideCurrentFromRight()
end

function ALittle.LayerManager:AddToModal(dialog, index)
	if dialog == nil then
		return
	end
	dialog.x_type = 3
	dialog.x_value = 0
	dialog.y_type = 3
	dialog.y_value = 0
	dialog.modal = true
	dialog.visible = false
	self._modal_layer:AddChild(dialog, index)
end

function ALittle.LayerManager:RemoveFromModal(dialog)
	if dialog == nil then
		return
	end
	dialog.modal = false
	dialog.visible = true
	self._modal_layer:RemoveChild(dialog)
end

function ALittle.LayerManager:ShowFromRight(dialog, focus)
	if focus == nil then
		focus = true
	end
	if self._right_show == dialog then
		return
	end
	if self._right_show ~= nil then
		self._right_show:DispatchEvent(___all_struct[348388800], {})
		self._right_layer:RemoveChild(self._right_show)
		self._right_show = nil
	end
	self._right_show = dialog
	if self._right_show ~= nil then
		self._right_layer:AddChild(self._right_show)
		if focus then
			self._right_show.focus = true
		end
		dialog:DispatchEvent(___all_struct[1862557463], {})
		dialog.visible = true
	end
end

function ALittle.LayerManager:HideFromRight(dialog)
	if self._right_show ~= dialog then
		return
	end
	if self._right_show == nil then
		return
	end
	self._right_show:DispatchEvent(___all_struct[348388800], {})
	self._right_layer:RemoveChild(self._right_show)
	self._right_show.focus = false
	self._right_show = nil
end

function ALittle.LayerManager:HideCurrentFromRight()
	if self._right_show == nil then
		return false
	end
	self:HideFromRight(self._right_show)
	return true
end

function ALittle.LayerManager:IsCurrentRight(dialog)
	return self._right_show == dialog
end

function ALittle.LayerManager:AddToTip(dialog)
	self._tip_layer:AddChild(dialog)
end

function ALittle.LayerManager:RemoveFromTip(dialog)
	self._tip_layer:RemoveChild(dialog)
end

function ALittle.LayerManager:PickUp(x, y)
	local mfc_rel_x
	local mfc_rel_y
	local mfc
	local mfd
	mfc, mfc_rel_x, mfc_rel_y = self._right_layer:PickUp(x, y)
	if mfc ~= nil then
		return mfc, nil, mfc_rel_x, mfc_rel_y
	end
	mfc, mfc_rel_x, mfc_rel_y = self._modal_layer:PickUp(x, y)
	if mfc ~= nil then
		return mfc, nil, mfc_rel_x, mfc_rel_y
	end
	local normal_groups = self._normal_groups
	local group_index = self._normal_group_count
	while true do
		if not(group_index > 0) then break end
		local normal_layers = normal_groups[group_index]
		local layer_list = normal_layers.childs
		local layer_index = normal_layers.child_count
		while true do
			if not(layer_index > 0) then break end
			local layer = layer_list[layer_index]
			mfc, mfd, mfc_rel_x, mfc_rel_y = self:LayerPickup(layer, x, y)
			if mfc ~= nil then
				return mfc, mfd, mfc_rel_x, mfc_rel_y
			end
			layer_index = layer_index+(-1)
		end
		group_index = group_index+(-1)
	end
	return nil, nil, nil, nil
end

function ALittle.LayerManager:LayerPickup(layer, x, y)
	local mfc_rel_x
	local mfc_rel_y
	local mfc
	local mfd
	if layer.visible and layer.disabled == false and layer.childs ~= nil then
		local rel_x = x - layer.x
		local rel_y = y - layer.y
		local child_list = layer.childs
		local index = layer.child_count
		while true do
			if not(index > 0) then break end
			local dialog = child_list[index]
			mfc, mfc_rel_x, mfc_rel_y = dialog:PickUp(rel_x, rel_y)
			if mfc ~= nil then
				mfd = dialog
				break
			end
			index = index+(-1)
		end
	end
	return mfc, mfd, mfc_rel_x, mfc_rel_y
end

function ALittle.LayerManager:HandleLRButtonDown(x, y)
	if self._right_show == nil then
		return
	end
	local left, top = self._right_show:LocalToGlobal()
	local right = self._right_show.width * self._right_show.scale_x + left
	local bottom = self._right_show.height * self._right_show.scale_y + top
	if x >= left and x < right and y >= top and y < bottom then
		return
	end
	local link_control = self._right_show.__right_data
	if link_control ~= nil then
		local abs_x, abs_y = link_control:LocalToGlobal()
		if x >= abs_x and x < abs_x + link_control.width * link_control.scale_x and y >= abs_y and y < abs_y + link_control.height * link_control.scale_y then
			return
		end
	end
	self._right_show:DispatchEvent(___all_struct[348388800], {})
	self._right_show.visible = false
	self._right_show = nil
end

_G.A_LayerManager = ALittle.LayerManager()
end