
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(OPSBaseDialog, " extends class:OPSBaseDialog is nil")
OPSDeleteDialog = ALittle.Class(OPSBaseDialog, "ABrowser.OPSDeleteDialog")

function OPSDeleteDialog:Ctor(ctrl_sys)
end

function OPSDeleteDialog:Show()
	if self._dialog_config.title == nil then
		self._title.text = "删除记录"
	else
		self._title.text = self._dialog_config.title
	end
	if self._dialog_config.content == nil then
		self._content.text = "确定要删除这条记录吗?"
	else
		self._content.text = self._dialog_config.content
	end
	self:ShowFromModal()
end

