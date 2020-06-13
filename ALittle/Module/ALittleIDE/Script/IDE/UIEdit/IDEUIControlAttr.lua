-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEUIControlAttr = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUIControlAttr")

function IDEUIControlAttr:SetTitle(title)
	local text = "控件属性"
	if title ~= "" then
		text = "控件属性(" .. title .. ")"
	end
	local main_tab = self.parent
	main_tab:SetChildText(self, text)
end

