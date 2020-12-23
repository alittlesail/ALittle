-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayObjectS, " extends class:ALittleIDE.DisplayObjectS is nil")
ALittleIDE.ImagePlayS = Lua.Class(ALittleIDE.DisplayObjectS, "ALittleIDE.ImagePlayS")

function ALittleIDE.ImagePlayS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_imageplay")
end

function ALittleIDE.ImagePlayS:LoadNatureBase()
	ALittleIDE.DisplayObjectS.LoadNatureBase(self)
	self:LoadValueData("interval")
	self:LoadShowTypeData("path_list")
end

function ALittleIDE.ImagePlayS:HandleIntervalFOCUSOUT(event)
	self:ValueNumZInputChange("interval", false)
end

function ALittleIDE.ImagePlayS:HandlePathListFOCUSOUT(event)
	self:TableDataSet("path_list", false)
end

end