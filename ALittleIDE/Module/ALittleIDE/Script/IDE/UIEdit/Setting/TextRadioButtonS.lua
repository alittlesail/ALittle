-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.TextCheckButtonS, " extends class:ALittleIDE.TextCheckButtonS is nil")
ALittleIDE.TextRadioButtonS = Lua.Class(ALittleIDE.TextCheckButtonS, "ALittleIDE.TextRadioButtonS")

function ALittleIDE.TextRadioButtonS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_textradiobutton")
end

function ALittleIDE.TextRadioButtonS:LoadNatureBase()
	ALittleIDE.TextCheckButtonS.LoadNatureBase(self)
end

end