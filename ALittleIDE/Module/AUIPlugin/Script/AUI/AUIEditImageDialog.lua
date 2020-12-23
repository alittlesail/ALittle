-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


AUIPlugin.AUIEditImageDialog = Lua.Class(nil, "AUIPlugin.AUIEditImageDialog")

function AUIPlugin.AUIEditImageDialog:HideDialog()
	if self._dialog ~= nil then
		self._dialog.visible = false
		self._cut_plugin:Clear()
	end
end

function AUIPlugin.AUIEditImageDialog:ShowDialog(path, save_dir)
	if self._dialog == nil then
		self._dialog = AUIPlugin.g_Control:CreateControl("aui_image_edit_dialog", self)
		A_LayerManager:AddToModal(self._dialog)
	end
	self._save_dir = save_dir
	self._cut_plugin:EditTexture(path)
	self._dialog.visible = true
end

function AUIPlugin.AUIEditImageDialog:Shutdown()
	if self._dialog ~= nil then
		A_LayerManager:RemoveFromModal(self._dialog)
		self._dialog = nil
	end
end

function AUIPlugin.AUIEditImageDialog:HandleCancelClick(event)
	self:HideDialog()
end

function AUIPlugin.AUIEditImageDialog:HandleSaveClick(event)
	self._cut_plugin:Cut()
end

function AUIPlugin.AUIEditImageDialog:HandleSaveToClick(event)
	A_OtherSystem:SystemSaveFile(event.target, "input_file_name.png", self._save_dir)
end

function AUIPlugin.AUIEditImageDialog:HandleSystemSaveFile(event)
	self._cut_plugin:Cut(event.path)
end

end