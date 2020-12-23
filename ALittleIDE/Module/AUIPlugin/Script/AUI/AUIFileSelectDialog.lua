-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1821709712, "AUIPlugin.AUIFileSelectRightButtonDownEvent", {
name = "AUIPlugin.AUIFileSelectRightButtonDownEvent", ns_name = "AUIPlugin", rl_name = "AUIFileSelectRightButtonDownEvent", hash_code = 1821709712,
name_list = {"target","path","directory"},
type_list = {"ALittle.EventDispatcher","string","bool"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.EventDispatcher, " extends class:ALittle.EventDispatcher is nil")
AUIPlugin.AUIFileSelectDialog = Lua.Class(ALittle.EventDispatcher, "AUIPlugin.AUIFileSelectDialog")

function AUIPlugin.AUIFileSelectDialog:Ctor(title, layer, ext_list)
	___rawset(self, "_title", title)
	___rawset(self, "_layer", layer)
	___rawset(self, "_ext_list", ext_list)
end

function AUIPlugin.AUIFileSelectDialog:Shutdown()
	if self._layout ~= nil then
		self._layout:Release()
	end
	if self._dialog ~= nil then
		if self._layer ~= nil then
			self._layer:RemoveChild(self._dialog)
		else
			A_LayerManager:RemoveFromModal(self._dialog)
		end
		self._dialog = nil
	end
end

function AUIPlugin.AUIFileSelectDialog:HideDialog()
	if self._layout ~= nil then
		self._layout:Release()
	end
	if self._dialog ~= nil then
		self._dialog.visible = false
	end
end

function AUIPlugin.AUIFileSelectDialog:ShowDialog()
	if self._layout ~= nil then
		self._layout:Release()
	end
	self:CreateDialog()
	self._dialog.visible = true
end

function AUIPlugin.AUIFileSelectDialog:CreateDialog()
	if self._dialog == nil then
		self._dialog = AUIPlugin.g_Control:CreateControl("file_select_dialog", self)
		self._dialog.title = self._title
		if self._layer ~= nil then
			self._layer:AddChild(self._dialog)
		else
			A_LayerManager:AddToModal(self._dialog)
		end
		self._dialog.close_callback = Lua.Bind(self.HandleDialogClose, self)
		self._layout:Init(self._ext_list)
		self._layout:AddEventListener(___all_struct[-1265378424], self, self.HandleItemRButtonDown)
	end
end

function AUIPlugin.AUIFileSelectDialog:HandleItemRButtonDown(event)
	local e = {}
	e.path = event.path
	e.directory = event.directory
	self:DispatchEvent(___all_struct[1821709712], e)
end

function AUIPlugin.AUIFileSelectDialog.__getter:base_path()
	if self._layout == nil then
		return nil
	end
	return self._layout.base_path
end

function AUIPlugin.AUIFileSelectDialog:ShowSelect()
	local ___COROUTINE = coroutine.running()
	self:ShowDialog()
	local result = self._layout:ShowSelect()
	self._dialog.visible = false
	return result
end

function AUIPlugin.AUIFileSelectDialog:HandleDialogClose()
	if self._layout ~= nil then
		self._layout:Release()
	end
	return true
end

function AUIPlugin.AUIFileSelectDialog:System_SetVDragCursor(event)
	ALittle.System_SetVDragCursor()
end

function AUIPlugin.AUIFileSelectDialog:System_SetNormalCursor(event)
	ALittle.System_SetNormalCursor()
end

function AUIPlugin.AUIFileSelectDialog:System_SetHDragCursor(event)
	ALittle.System_SetHDragCursor()
end

function AUIPlugin.AUIFileSelectDialog:System_SetHVDragCursor(event)
	ALittle.System_SetHVDragCursor()
end

function AUIPlugin.AUIFileSelectDialog:SetPath(base_path, rel_path)
	self:CreateDialog()
	return self._layout:SetPath(base_path, rel_path)
end

function AUIPlugin.AUIFileSelectDialog:SetBasePath(base_path)
	if self.base_path == base_path then
		return true
	end
	return self:SetPath(base_path, "")
end

function AUIPlugin.AUIFileSelectDialog:Refresh()
	if self._layout ~= nil then
		self._layout:Refresh()
	end
end

function AUIPlugin.AUIFileSelectDialog:HandleDialogDrag(event)
	local delta_x = event.delta_x
	local delta_y = event.delta_y
	if event.target == self._drag_lr_quad then
		delta_y = 0
	elseif event.target == self._drag_ud_quad then
		delta_x = 0
	end
	if self._dialog.width + delta_x < 506 then
		delta_x = 506 - self._dialog.width
	end
	if self._dialog.height + delta_y < 200 then
		delta_y = 200 - self._dialog.height
	end
	self._dialog.width = self._dialog.width + delta_x
	self._dialog.height = self._dialog.height + delta_y
end

function AUIPlugin.AUIFileSelectDialog:HandleDialogDragEnd(event)
	self._layout:Refresh()
end

function AUIPlugin.AUIFileSelectDialog:CheckResourceName(name)
	local len = ALittle.String_Len(name)
	if len == 0 then
		return false, "命名只能支持字母数字下划线"
	end
	local i = 1
	while true do
		if not(i <= len) then break end
		local byte = ALittle.String_Byte(name, i)
		local check_all = byte >= 65 and byte <= 90 or byte >= 97 and byte <= 122 or byte >= 48 and byte <= 57 or byte == 95
		if check_all == false then
			return false, "命名只能支持字母数字下划线"
		end
		i = i+(1)
	end
	return true, nil
end

end