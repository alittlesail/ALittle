-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayObject, " extends class:ALittle.DisplayObject is nil")
ALittle.DynamicImage = Lua.Class(ALittle.DisplayObject, "ALittle.DynamicImage")

function ALittle.DynamicImage:Ctor(ctrl_sys)
	___rawset(self, "_real_width", 0)
	___rawset(self, "_real_height", 0)
	___rawset(self, "_show", __CPPAPIImage())
	___rawset(self, "_texture", __CPPAPIDynamicTexture())
	self._texture:SetRenderMode(0)
	self._show:SetTexture(self._texture)
end

function ALittle.DynamicImage:GetSurface(redraw)
	return self._texture:GetSurface(redraw)
end

function ALittle.DynamicImage:SetRangeColor(buffer)
	do
		local surface = self:GetSurface(true)
		carp.SetCarpSurfacePixelRect(surface, buffer)
	end
end

function ALittle.DynamicImage:SetSurfaceSize(width, height, color)
	self._real_width = width
	self._real_height = height
	self._texture:SetSurfaceSize(width, height, color)
end

function ALittle.DynamicImage:SetRenderMode(mode)
	self._texture:SetRenderMode(mode)
end

function ALittle.DynamicImage:Clear()
	if self._texture == nil then
		return
	end
	self._texture:Clear()
end

end