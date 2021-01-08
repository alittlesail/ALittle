-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleDeploy.DPLUICenter = Lua.Class(ALittle.DisplayLayout, "ALittleDeploy.DPLUICenter")

function ALittleDeploy.DPLUICenter:TCtor()
end

function ALittleDeploy.DPLUICenter.__getter:content_edit()
	return self._content_edit
end

function ALittleDeploy.DPLUICenter:System_SetVDragCursor(event)
	ALittle.System_SetVDragCursor()
end

function ALittleDeploy.DPLUICenter:System_SetNormalCursor(event)
	ALittle.System_SetNormalCursor()
end

function ALittleDeploy.DPLUICenter:System_SetHDragCursor(event)
	ALittle.System_SetHDragCursor()
end

function ALittleDeploy.DPLUICenter:System_SetHVDragCursor(event)
	ALittle.System_SetHVDragCursor()
end

function ALittleDeploy.DPLUICenter:HandleLeftEditResizeDrag(event)
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

function ALittleDeploy.DPLUICenter:HandleShortcutKey()
	if A_UISystem.sym_map[27] then
	end
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
		return
	end
end

function ALittleDeploy.DPLUICenter:HandleUndoRevoke(event)
	local tab_child = self._content_edit.cur_tab_child
	if tab_child == nil then
		return
	end
	tab_child.revoke_list:UndoRevoke()
	tab_child:OnUndo()
end

function ALittleDeploy.DPLUICenter:HandleDoRevoke(event)
	local tab_child = self._content_edit.cur_tab_child
	if tab_child == nil then
		return
	end
	tab_child.revoke_list:DoRevoke()
	tab_child:OnRedo()
end

function ALittleDeploy.DPLUICenter:HandleSaveCurrent(event)
	local tab_child = self._content_edit.cur_tab_child
	if tab_child == nil then
		return
	end
	tab_child.save = true
end

end