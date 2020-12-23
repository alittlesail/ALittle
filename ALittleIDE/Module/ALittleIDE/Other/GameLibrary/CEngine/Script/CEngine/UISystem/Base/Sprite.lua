-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


assert(ALittle.DisplayObject, " extends class:ALittle.DisplayObject is nil")
ALittle.Sprite = Lua.Class(ALittle.DisplayObject, "ALittle.Sprite")

function ALittle.Sprite:Ctor(ctrl_sys)
	___rawset(self, "_show", __CPPAPISprite())
	___rawset(self, "_texture_width", 0)
	___rawset(self, "_texture_height", 0)
	___rawset(self, "_tex_coord_t", 0)
	___rawset(self, "_tex_coord_b", 1)
	___rawset(self, "_tex_coord_l", 0)
	___rawset(self, "_tex_coord_r", 1)
	___rawset(self, "_row_count", 1)
	___rawset(self, "_col_count", 1)
	___rawset(self, "_row_index", 1)
	___rawset(self, "_col_index", 1)
	___rawset(self, "_flip", 0)
	A_LoadTextureManager:RegisterRedrawControl(self)
	self:AddEventListener(___all_struct[40651933], self, self.HandleLButtonUp)
	self:AddEventListener(___all_struct[683647260], self, self.HandleMButtonUp)
	self:AddEventListener(___all_struct[734860930], self, self.HandleFLButtonUp)
end

function ALittle.Sprite:HandleLButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local c_event = {}
		c_event.is_drag = event.is_drag
		c_event.count = event.count
		self:DispatchEvent(___all_struct[-449066808], c_event)
	end
end

function ALittle.Sprite:HandleMButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local c_event = {}
		c_event.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[-1330840], c_event)
	end
end

function ALittle.Sprite:HandleFLButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local c_event = {}
		c_event.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[286797479], c_event)
	end
end

function ALittle.Sprite:Redraw()
	self._show:ClearTexture()
	if self._texture ~= nil then
		self._texture:Clear()
		self._texture = nil
	end
	if self._texture_name == nil then
		return
	end
	if self._texture_cut ~= nil then
		A_LoadTextureManager:SetTextureCut(self, self._texture_name, 0, 0, self._texture_cut.cache)
	else
		self._ctrl_sys:SetTexture(self, self._texture_name)
	end
end

function ALittle.Sprite:CopyTextureRef(sprite)
	if sprite == nil or sprite._texture == nil then
		return
	end
	self._texture_name = sprite._texture_name
	self._texture_cut = nil
	if sprite._texture_cut ~= nil then
		self._texture_cut = {}
		self._texture_cut.max_width = sprite._texture_cut.max_width
		self._texture_cut.max_height = sprite._texture_cut.max_height
		self._texture_cut.cache = sprite._texture_cut.cache
	end
	self._texture = sprite._texture
	self._show:SetTexture(sprite._texture:GetTexture())
	self:SetTextureCoord(sprite._tex_coord_t, sprite._tex_coord_b, sprite._tex_coord_l, sprite._tex_coord_r)
	self._texture_width = sprite._texture_width
	self._texture_height = sprite._texture_height
	self.row_count = sprite.row_count
	self.col_count = sprite.col_count
	self.row_index = sprite.row_index
	self.col_index = sprite.col_index
end

function ALittle.Sprite.__setter:texture_name(value)
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

function ALittle.Sprite:SetTextureCut(texture_name, cache, index)
	if self._texture_name ~= nil then
		self._show:ClearTexture()
		self._texture = nil
	end
	self._texture_name = texture_name
	if self._texture_name ~= nil then
		self._texture_cut = {}
		self._texture_cut.cache = cache
		A_LoadTextureManager:SetTextureCut(self, texture_name, 0, 0, cache)
	end
end

function ALittle.Sprite.__getter:texture_name()
	return self._texture_name
end

function ALittle.Sprite.__setter:texture(value)
	self._show:SetTexture(value:GetTexture())
	self._texture_width = value:GetWidth()
	self._texture_height = value:GetHeight()
	self._texture = value
end

function ALittle.Sprite.__getter:texture()
	return self._texture
end

function ALittle.Sprite:SetTextureCoord(t, b, l, r)
	self._tex_coord_t = t
	self._tex_coord_b = b
	self._tex_coord_l = l
	self._tex_coord_r = r
	self._show:SetTextureCoord(t, b, l, r)
end

function ALittle.Sprite.__getter:texture_width()
	return self._texture_width
end

function ALittle.Sprite.__getter:texture_height()
	return self._texture_height
end

function ALittle.Sprite.__setter:row_count(value)
	self._row_count = value
	self._show:SetRowColCount(self._row_count, self._col_count)
end

function ALittle.Sprite.__getter:row_count()
	return self._row_count
end

function ALittle.Sprite.__setter:col_count(value)
	self._col_count = value
	self._show:SetRowColCount(self._row_count, self._col_count)
end

function ALittle.Sprite.__getter:col_count()
	return self._col_count
end

function ALittle.Sprite.__setter:row_index(value)
	self._row_index = value
	self._show:SetRowColIndex(self._row_index, self._col_index)
end

function ALittle.Sprite.__getter:row_index()
	return self._row_index
end

function ALittle.Sprite.__setter:col_index(value)
	self._col_index = value
	self._show:SetRowColIndex(self._row_index, self._col_index)
end

function ALittle.Sprite.__getter:col_index()
	return self._col_index
end

function ALittle.Sprite:SetRowCol(row, col)
	self._row_index = row
	self._col_index = col
	self._show:SetRowColIndex(self._row_index, self._col_index)
end

function ALittle.Sprite.__getter:flip()
	return self._flip
end

function ALittle.Sprite.__setter:flip(value)
	self._flip = value
	self._show:SetFlip(value)
end

end