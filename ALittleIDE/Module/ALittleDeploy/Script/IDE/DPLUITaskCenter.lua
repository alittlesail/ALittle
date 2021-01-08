-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleDeploy.DPLUITaskCenter = Lua.Class(ALittle.DisplayLayout, "ALittleDeploy.DPLUITaskCenter")

function ALittleDeploy.DPLUITaskCenter:System_SetVDragCursor(event)
	ALittle.System_SetVDragCursor()
end

function ALittleDeploy.DPLUITaskCenter:System_SetNormalCursor(event)
	ALittle.System_SetNormalCursor()
end

function ALittleDeploy.DPLUITaskCenter:System_SetHDragCursor(event)
	ALittle.System_SetHDragCursor()
end

function ALittleDeploy.DPLUITaskCenter:System_SetHVDragCursor(event)
	ALittle.System_SetHVDragCursor()
end

function ALittleDeploy.DPLUITaskCenter:HandleTaskGrid3ResizeDrag(event)
	local up_size = self._task_grid3.up_size
	up_size = up_size + event.delta_x
	local max_size = self._task_grid3.width - self._task_grid3.down_size - 50
	if up_size > max_size then
		up_size = max_size
	end
	if up_size < 100 then
		up_size = 100
	end
	self._task_grid3.up_size = up_size
end

end