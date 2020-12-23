-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittle.DisplayView = Lua.Class(ALittle.DisplayLayout, "ALittle.DisplayView")

function ALittle.DisplayView:Ctor(ctrl_sys)
	___rawset(self, "_show", __CPPAPIDisplayView())
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", true)
end

end