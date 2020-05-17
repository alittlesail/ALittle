-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


IDEEditImageDialog = Lua.Class(nil, "ALittleIDE.IDEEditImageDialog")

function IDEEditImageDialog:HideDialog()
	if self._dialog ~= nil then
		self._dialog.visible = false
		self._cut_plugin:Clear()
	end
end

function IDEEditImageDialog:ShowDialog(path)
	if self._dialog == nil then
		self._dialog = g_Control:CreateControl("ide_image_edit_dialog", self)
		A_LayerManager:AddToModal(self._dialog)
	end
	self._cut_plugin:EditTexture(path)
	self._dialog.visible = true
end

function IDEEditImageDialog:HandleCancelClick(event)
	self:HideDialog()
end

function IDEEditImageDialog:HandleSaveClick(event)
	self._cut_plugin:Cut()
end

function IDEEditImageDialog:HandleSaveToClick(event)
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("提示", "当前没有打开项目")
		return
	end
	A_OtherSystem:SystemSaveFile(event.target, "input_file_name.png", g_IDEProject.project.base_path .. "Texture")
end

function IDEEditImageDialog:HandleSystemSaveFile(event)
	self._cut_plugin:Cut(event.path)
end

g_IDEEditImageDialog = IDEEditImageDialog()
