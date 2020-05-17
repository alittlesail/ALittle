-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


IDEAttributeManager = Lua.Class(nil, "ALittleIDE.IDEAttributeManager")

function IDEAttributeManager:Setup(tab, control)
	self._main_tab = tab
	self._main_control = control
end

function IDEAttributeManager:SetTitle(title)
	local text = "控件属性"
	if title ~= "" then
		text = "控件属性(" .. title .. ")"
	end
	self._main_tab:SetChildText(self._main_control, text)
end

g_IDEAttributeManager = IDEAttributeManager()
