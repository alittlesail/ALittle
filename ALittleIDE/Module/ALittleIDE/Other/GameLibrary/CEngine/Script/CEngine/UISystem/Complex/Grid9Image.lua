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
ALittle.Grid9Image = Lua.Class(ALittle.DisplayObject, "ALittle.Grid9Image")

function ALittle.Grid9Image:Ctor(ctrl_sys)
	___rawset(self, "_show", __CPPAPIGrid9Image())
	___rawset(self, "_texture_width", 0)
	___rawset(self, "_texture_height", 0)
	___rawset(self, "_flip", 0)
	___rawset(self, "_tex_coord_t", 0)
	___rawset(self, "_tex_coord_b", 1)
	___rawset(self, "_tex_coord_l", 0)
	___rawset(self, "_tex_coord_r", 1)
	___rawset(self, "_left_size", 0)
	___rawset(self, "_right_size", 0)
	___rawset(self, "_top_size", 0)
	___rawset(self, "_bottom_size", 0)
	A_LoadTextureManager:RegisterRedrawControl(self)
	self:AddEventListener(___all_struct[40651933], self, self.HandleLButtonUp)
	self:AddEventListener(___all_struct[683647260], self, self.HandleMButtonUp)
	self:AddEventListener(___all_struct[734860930], self, self.HandleFLButtonUp)
end

function ALittle.Grid9Image:HandleLButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local c_event = {}
		c_event.is_drag = event.is_drag
		c_event.count = event.count
		self:DispatchEvent(___all_struct[-449066808], c_event)
	end
end

function ALittle.Grid9Image:HandleMButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local c_event = {}
		c_event.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[-1330840], c_event)
	end
end

function ALittle.Grid9Image:HandleFLButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local c_event = {}
		c_event.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[286797479], c_event)
	end
end

function ALittle.Grid9Image:Redraw()
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

function ALittle.Grid9Image:CopyTextureRef(image)
	if image == nil or image._texture == nil then
		return
	end
	self._texture_name = image._texture_name
	self._texture_cut = nil
	if image._texture_cut ~= nil then
		self._texture_cut = {}
		self._texture_cut.max_width = image._texture_cut.max_width
		self._texture_cut.max_height = image._texture_cut.max_height
		self._texture_cut.cache = image._texture_cut.cache
	end
	self._texture = image._texture
	self._show:SetTexture(image._texture:GetTexture())
	self:SetTextureCoord(image._tex_coord_t, image._tex_coord_b, image._tex_coord_l, image._tex_coord_r)
	self._texture_width = image._texture_width
	self._texture_height = image._texture_height
	self.left_size = image.left_size
	self.right_size = image.right_size
	self.top_size = image.top_size
	self.bottom_size = image.bottom_size
end

function ALittle.Grid9Image.__setter:texture_name(value)
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

function ALittle.Grid9Image:SetTextureCut(texture_name, max_width, max_height, cache, index, callback)
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
		A_LoadTextureManager:SetTextureCut(self, texture_name, max_width, max_height, cache, callback)
	end
end

function ALittle.Grid9Image.__setter:texture_cut(param)
	self:SetTextureCut(param.texture_name, param.max_width, param.max_height, param.cache, nil)
end

function ALittle.Grid9Image.__getter:texture_cut()
	if self._texture_cut == nil then
		return nil
	end
	local texture_cut = {}
	texture_cut.max_width = self._texture_cut.max_width
	texture_cut.max_height = self._texture_cut.max_height
	texture_cut.texture_name = self._texture_name
	return texture_cut
end

function ALittle.Grid9Image.__getter:texture_name()
	return self._texture_name
end

function ALittle.Grid9Image.__setter:texture(value)
	self._show:SetTexture(value:GetTexture())
	self._texture_width = value:GetWidth()
	self._texture_height = value:GetHeight()
	self._texture = value
end

function ALittle.Grid9Image.__getter:texture()
	return self._texture
end

function ALittle.Grid9Image:SetTextureCoord(t, b, l, r)
	self._tex_coord_t = t
	self._tex_coord_b = b
	self._tex_coord_l = l
	self._tex_coord_r = r
	self._show:SetTextureCoord(t, b, l, r)
end

function ALittle.Grid9Image.__setter:left_size(value)
	self._left_size = value
	self._show:SetLeftSize(value)
end

function ALittle.Grid9Image.__getter:left_size()
	return self._left_size
end

function ALittle.Grid9Image.__setter:right_size(value)
	self._right_size = value
	self._show:SetRightSize(value)
end

function ALittle.Grid9Image.__getter:right_size()
	return self._right_size
end

function ALittle.Grid9Image.__setter:top_size(value)
	self._top_size = value
	self._show:SetTopSize(value)
end

function ALittle.Grid9Image.__getter:top_size()
	return self._top_size
end

function ALittle.Grid9Image.__setter:bottom_size(value)
	self._bottom_size = value
	self._show:SetBottomSize(value)
end

function ALittle.Grid9Image.__getter:bottom_size()
	return self._bottom_size
end

function ALittle.Grid9Image.__getter:texture_width()
	return self._texture_width
end

function ALittle.Grid9Image.__getter:texture_height()
	return self._texture_height
end

function ALittle.Grid9Image.__getter:flip()
	return self._flip
end

function ALittle.Grid9Image.__setter:flip(value)
	self._flip = value
	self._show:SetFlip(value)
end

end