-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ALittleIDE = ALittleIDE
local ALittle = ALittle


assert(ALittleIDE.DisplayObjectS, " extends class:ALittleIDE.DisplayObjectS is nil")
ALittleIDE.DisplayViewS = Lua.Class(ALittleIDE.DisplayObjectS, "ALittleIDE.DisplayViewS")

function ALittleIDE.DisplayViewS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_displayview")
end

end