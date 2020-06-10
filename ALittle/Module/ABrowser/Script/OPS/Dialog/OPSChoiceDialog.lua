
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(OPSBaseDialog, " extends class:OPSBaseDialog is nil")
OPSChoiceDialog = ALittle.Class(OPSBaseDialog, "ABrowser.OPSChoiceDialog")

function OPSChoiceDialog:Ctor(ctrl_sys)
end

function OPSChoiceDialog:Show()
	self._title.text = self._dialog_config.title
