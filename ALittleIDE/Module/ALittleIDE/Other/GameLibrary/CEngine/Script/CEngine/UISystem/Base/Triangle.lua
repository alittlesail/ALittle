-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayObject, " extends class:ALittle.DisplayObject is nil")
ALittle.Triangle = Lua.Class(ALittle.DisplayObject, "ALittle.Triangle")

function ALittle.Triangle:Ctor(ctrl_sys)
	___rawset(self, "_show", __CPPAPITriangle())
	___rawset(self, "_u1", 0)
	___rawset(self, "_v1", 0)
	___rawset(self, "_u2", 0)
	___rawset(self, "_v2", 0)
	___rawset(self, "_u3", 0)
	___rawset(self, "_v3", 0)
	___rawset(self, "_x1", 0)
	___rawset(self, "_y1", 0)
	___rawset(self, "_x2", 0)
	___rawset(self, "_y2", 0)
	___rawset(self, "_x3", 0)
	___rawset(self, "_y3", 0)
	___rawset(self, "_texture_width", 0)
	___rawset(self, "_texture_height", 0)
	___rawset(self, "_auto_rejust", false)
	A_LoadTextureManager:RegisterRedrawControl(self)
end

function ALittle.Triangle:Redraw()
	self._show:ClearTexture()
	if self._texture ~= nil then
		self._texture:Clear()
		self._texture = nil
	end
	if self._texture_name == nil then
		return
	end
	if self._texture_cut ~= nil then
		A_LoadTextureManager:SetTextureCut(self, self._texture_name, self._texture_cut.max_width, self._texture_cut.max_height, self._texture_cut.cache)
	else
		self._ctrl_sys:SetTexture(self, self._texture_name)
	end
end

function ALittle.Triangle.__setter:texture_name(value)
	if self._texture_name == value then
		return
	end
	if self._texture_name ~= nil then
		self._show:ClearTexture()
		self._texture = nil
	end
	self._texture_name = value
	if self._texture_name ~= nil then
		self._texture_cut = nil
		self._ctrl_sys:SetTexture(self, value)
	end
end

function ALittle.Triangle:SetTextureCut(texture_name, auto_rejust, max_width, max_height, cache, index)
	if self._texture_name ~= nil then
		self._show:ClearTexture()
		self._texture = nil
	end
	self._texture_name = texture_name
	if self._texture_name ~= nil then
		self._texture_cut = {}
		self._texture_cut.max_width = max_width
		self._texture_cut.max_height = max_height
		self._texture_cut.cache = cache
		self._auto_rejust = auto_rejust or false
		A_LoadTextureManager:SetTextureCut(self, texture_name, max_width, max_height, cache)
	end
end

function ALittle.Triangle.__setter:texture_cut(param)
	self:SetTextureCut(param.texture_name, true, param.max_width, param.max_height, param.cache, nil)
end

function ALittle.Triangle.__getter:texture_cut()
	if self._texture_cut == nil then
		return nil
	end
	local texture_cut = {}
	texture_cut.max_width = self._texture_cut.max_width
	texture_cut.max_height = self._texture_cut.max_height
	texture_cut.texture_name = self._texture_name
	return texture_cut
end

function ALittle.Triangle.__getter:texture_name()
	return self._texture_name
end

function ALittle.Triangle.__setter:texture(value)
	self._show:SetTexture(value:GetTexture())
	self._texture_width = value:GetWidth()
	self._texture_height = value:GetHeight()
	self._texture = value
	if self._auto_rejust then
		self.width = self._texture_width
		self.height = self._texture_height
	end
end

function ALittle.Triangle.__getter:texture()
	return self._texture
end

function ALittle.Triangle:SetTextureCoord(t, b, l, r)
	self._show:SetTextureCoord(t, b, l, r)
end

function ALittle.Triangle.__getter:texture_width()
	return self._texture_width
end

function ALittle.Triangle.__getter:texture_height()
	return self._texture_height
end

function ALittle.Triangle.__getter:u1()
	return self._u1
end

function ALittle.Triangle.__getter:v1()
	return self._v1
end

function ALittle.Triangle.__getter:u2()
	return self._u2
end

function ALittle.Triangle.__getter:v2()
	return self._v2
end

function ALittle.Triangle.__getter:u3()
	return self._u3
end

function ALittle.Triangle.__getter:v3()
	return self._v3
end

function ALittle.Triangle.__setter:u1(v)
	self._u1 = v
	self._show:SetTexUV(0, self._u1, self._v1)
end

function ALittle.Triangle.__setter:v1(v)
	self._v1 = v
	self._show:SetTexUV(0, self._u1, self._v1)
end

function ALittle.Triangle.__setter:u2(v)
	self._u2 = v
	self._show:SetTexUV(1, self._u2, self._v2)
end

function ALittle.Triangle.__setter:v2(v)
	self._v2 = v
	self._show:SetTexUV(1, self._u2, self._v2)
end

function ALittle.Triangle.__setter:u3(v)
	self._u3 = v
	self._show:SetTexUV(2, self._u3, self._v3)
end

function ALittle.Triangle.__setter:v3(v)
	self._v3 = v
	self._show:SetTexUV(2, self._u3, self._v3)
end

function ALittle.Triangle.__getter:x1()
	return self._x1
end

function ALittle.Triangle.__getter:y1()
	return self._y1
end

function ALittle.Triangle.__getter:x2()
	return self._x2
end

function ALittle.Triangle.__getter:y2()
	return self._y2
end

function ALittle.Triangle.__getter:x3()
	return self._x3
end

function ALittle.Triangle.__getter:y3()
	return self._y3
end

function ALittle.Triangle.__setter:x1(v)
	self._x1 = v
	self._show:SetPosXY(0, self._x1, self._y1)
end

function ALittle.Triangle.__setter:y1(v)
	self._y1 = v
	self._show:SetPosXY(0, self._x1, self._y1)
end

function ALittle.Triangle.__setter:x2(v)
	self._x2 = v
	self._show:SetPosXY(1, self._x2, self._y2)
end

function ALittle.Triangle.__setter:y2(v)
	self._y2 = v
	self._show:SetPosXY(1, self._x2, self._y2)
end

function ALittle.Triangle.__setter:x3(v)
	self._x3 = v
	self._show:SetPosXY(2, self._x3, self._y3)
end

function ALittle.Triangle.__setter:y3(v)
	self._y3 = v
	self._show:SetPosXY(2, self._x3, self._y3)
end

function ALittle.Triangle:RejuseSize()
	local max = self._x1
	if max < self._x2 then
		max = self._x2
	end
	if max < self._x3 then
		max = self._x3
	end
	self.width = max
	max = self._y1
	if max < self._y2 then
		max = self._y2
	end
	if max < self._y3 then
		max = self._y3
	end
	self.height = max
	self:UpdateLayout()
end

end