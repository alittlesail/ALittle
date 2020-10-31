-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUIPlugin.AUIStatLayout = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUIStatLayout")

function AUIPlugin.AUIStatLayout:Ctor()
	___rawset(self, "_point_size", 5)
	___rawset(self, "_draw_width", 0)
	___rawset(self, "_draw_height", 0)
	___rawset(self, "_min_index", 0)
	___rawset(self, "_max_index", 0)
	___rawset(self, "_max_value", 0)
	___rawset(self, "_loss_map", {})
	___rawset(self, "_right_map", {})
end

function AUIPlugin.AUIStatLayout:TCtor()
	self._image = ALittle.DynamicImage(self._ctrl_sys)
	self._image.width_type = 4
	self._image.height_type = 4
	self._image:SetRenderMode(1)
	self:AddChild(self._image)
end

function AUIPlugin.AUIStatLayout:Init(point_size, draw_width, draw_height, max_value)
	self._point_size = point_size
	if self._point_size < 1 then
		self._point_size = 1
	end
	self._draw_width = draw_width
	if self._draw_width < 0 then
		self._draw_width = 0
	end
	self._draw_height = draw_height
	if self._draw_height < 0 then
		self._draw_height = 0
	end
	self._min_index = 0
	self._max_index = 0
	self._max_value = max_value
	if self._max_value < 0 then
		self._max_value = 0
	end
	self._loss_map = {}
	self._right_map = {}
	self._image:SetSurfaceSize(self._draw_width, self._draw_height, 0xFF000000)
end

function AUIPlugin.AUIStatLayout:AddValue(loss, right)
	if self._max_index - self._min_index < ALittle.Math_Floor(self._draw_width / self._point_size) then
		self._max_index = self._max_index + (1)
	else
		self._loss_map[self._min_index] = nil
		self._right_map[self._min_index] = nil
		self._min_index = self._min_index + (1)
		self._max_index = self._max_index + (1)
		local surface = self._image:GetSurface(true)
		carp.TransferCarpSurface(surface, "left", self._point_size)
	end
	self._loss_map[self._max_index] = loss
	self._right_map[self._max_index] = right
	local color = 0xFFFFFFFF
	local x = (self._max_index - self._min_index) * self._point_size
	if x > self._draw_width - self._point_size then
		x = self._draw_width - self._point_size
	end
	local y = 0
	if self._max_value ~= 0 then
		local rate = loss / self._max_value
		if rate > 1 then
			color = 0xFF0000FF
		elseif rate < 0.00001 then
			color = 0xFF00FFFF
		end
		if right then
			color = 0xFF00FF00
		end
		y = ALittle.Math_Floor(rate * self._draw_height)
		if y > self._draw_height - self._point_size then
			y = self._draw_height - self._point_size
		end
	end
	y = self._draw_height - self._point_size - y
	local surface = self._image:GetSurface(true)
	local col = x
	while true do
		if not(col < x + self._point_size) then break end
		local row = y
		while true do
			if not(row < y + self._point_size) then break end
			carp.SetCarpSurfacePixel(surface, col, row, color)
			row = row+(1)
		end
		col = col+(1)
	end
end

function AUIPlugin.AUIStatLayout:ClearContent()
	self._min_index = 0
	self._max_index = 0
	self._max_value = self._max_value
	if self._max_value < 0 then
		self._max_value = 0
	end
	self._loss_map = {}
	self._right_map = {}
	self._image:SetSurfaceSize(self._draw_width, self._draw_height, 0xFF000000)
end

function AUIPlugin.AUIStatLayout.__getter:surface()
	return self._image:GetSurface(false)
end

end