-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayObject, " extends class:ALittle.DisplayObject is nil")
ALittle.DynamicImage = Lua.Class(ALittle.DisplayObject, "ALittle.DynamicImage")

function ALittle.DynamicImage:Ctor(ctrl_sys)
	___rawset(self, "_show", __CPPAPIImage())
	___rawset(self, "_texture", __CPPAPIDynamicTexture())
	self._show:SetTexture(self._texture)
end

function ALittle.DynamicImage:GetSurface(redraw)
	return self._texture:GetSurface(redraw)
end

function ALittle.DynamicImage:SetRangeColor(buffer, width, height)
	do
		local surface = self:GetSurface(true)
		local x = 0
		while true do
			if not(x < width) then break end
			local y = 0
			while true do
				if not(y < height) then break end
				local index = y * width + x
				carp.SetCarpSurfacePixel(surface, x, y, buffer[index])
				y = y+(1)
			end
			x = x+(1)
		end
	end
end

function ALittle.DynamicImage:SetSurfaceSize(width, height, color)
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