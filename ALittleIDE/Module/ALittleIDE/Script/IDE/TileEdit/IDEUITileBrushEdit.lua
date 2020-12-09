-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEUITileBrushEdit = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUITileBrushEdit")

function ALittleIDE.IDEUITileBrushEdit.__getter:layer_container()
	return self._layer_container
end

function ALittleIDE.IDEUITileBrushEdit:HandleClearBrushClick(event)
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEUITileLayerEdit = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUITileLayerEdit")

function ALittleIDE.IDEUITileLayerEdit:HandleAddLayerClick(event)
end

end