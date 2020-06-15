-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


AUIEditImageDialog = Lua.Class(nil, "AUIPlugin.AUIEditImageDialog")

function AUIEditImageDialog:HideDialog()
	if self._dialog ~= nil then
		self._dialog.visible = false
		self._cut_plugin:Clear()
	end
end

function AUIEditImageDialog:ShowDialog(path, save_dir)
	if self._dialog == nil then
		self._dialog = g_Control:CreateControl("ide_image_edit_dialog", self)
		A_LayerManager:AddToModal(self._dialog)
	end
	self._save_dir = save_dir
	self._cut_plugin:EditTexture(path)
	self._dialog.visible = true
end

function AUIEditImageDialog:Shutdown()
	if self._dialog ~= nil then
		A_LayerManager:RemoveFromModal(self._dialog)
		self._dialog = nil
	end
end

function AUIEditImageDialog:HandleCancelClick(event)
	self:HideDialog()
end

function AUIEditImageDialog:HandleSaveClick(event)
	self._cut_plugin:Cut()
end

function AUIEditImageDialog:HandleSaveToClick(event)
	A_OtherSystem:SystemSaveFile(event.target, "input_file_name.png", self._save_dir)
end

function AUIEditImageDialog:HandleSystemSaveFile(event)
	self._cut_plugin:Cut(event.path)
end

