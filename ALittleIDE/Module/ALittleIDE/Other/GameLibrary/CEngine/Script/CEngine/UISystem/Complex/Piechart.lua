-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittle.Piechart = Lua.Class(ALittle.DisplayLayout, "ALittle.Piechart")

function ALittle.Piechart:Ctor(ctrl_sys)
	___rawset(self, "_start_degree", 0)
	___rawset(self, "_end_degree", 0)
	___rawset(self, "_tri_list", {})
	local i = 1
	while true do
		if not(i <= 5) then break end
		local triangle = ALittle.Triangle(self._ctrl_sys)
		triangle.u2 = 0.5
		triangle.v2 = 0.5
		triangle.width_type = 4
		triangle.width_value = 0
		triangle.height_type = 4
		triangle.height_value = 0
		self._tri_list[i] = triangle
		ALittle.DisplayLayout.AddChild(self, triangle)
		i = i+(1)
	end
	___rawset(self, "_start_degree", 0)
	___rawset(self, "_end_degree", 360)
	self:SetDegree(0, 360)
	___rawset(self, "_pie_texture_name", nil)
end

function ALittle.Piechart.__setter:start_degree(value)
	local tmp = value % 360
	if tmp < 0 then
		tmp = tmp + (360)
	end
	if tmp == 0 and value / 360 ~= 0 then
		tmp = 360
	end
	self._start_degree = tmp
	self:SetDegree(tmp, self._end_degree)
end

function ALittle.Piechart.__getter:start_degree()
	return self._start_degree
end

function ALittle.Piechart.__setter:end_degree(value)
	local tmp = value % 360
	if tmp < 0 then
		tmp = tmp + (360)
	end
	if tmp == 0 and value / 360 ~= 0 then
		tmp = 360
	end
	self._end_degree = tmp
	self:SetDegree(self._start_degree, tmp)
end

function ALittle.Piechart.__getter:end_degree()
	return self._end_degree
end

function ALittle.Piechart.__setter:red(value)
	if self.red == value then
		return
	end
	self.red = value
	local i = 1
	while true do
		if not(i <= 5) then break end
		self._tri_list[i].red = value
		i = i+(1)
	end
end

function ALittle.Piechart.__setter:green(value)
	if self.green == value then
		return
	end
	self.green = value
	local i = 1
	while true do
		if not(i <= 5) then break end
		self._tri_list[i].green = value
		i = i+(1)
	end
end

function ALittle.Piechart.__setter:blue(value)
	if self.blue == value then
		return
	end
	self.blue = value
	local i = 1
	while true do
		if not(i <= 5) then break end
		self._tri_list[i].blue = value
		i = i+(1)
	end
end

function ALittle.Piechart.__setter:width(value)
	if value == self._width then
		return
	end
	self._width = value
	if self._width_type == 1 then
		self._width_value = self._width
	end
	for k, v in ___ipairs(self._tri_list) do
		v.x1 = v.u1 * value
		v.x2 = v.u2 * value
		v.x3 = v.u3 * value
		self:UpdateWidthLayout(v)
		self:UpdateXLayout(v)
	end
	self._show:SetWidth(value)
end

function ALittle.Piechart.__setter:height(value)
	if value == self._height then
		return
	end
	self._height = value
	if self._height_type == 1 then
		self._height_value = self._height
	end
	for k, v in ___ipairs(self._tri_list) do
		v.y1 = v.v1 * value
		v.y2 = v.v2 * value
		v.y3 = v.v3 * value
		self:UpdateHeightLayout(v)
		self:UpdateYLayout(v)
	end
	self._show:SetHeight(value)
end

function ALittle.Piechart.__setter:texture_name(value)
	if self._pie_texture_name == value then
		return
	end
	self._pie_texture_name = value
	for k, v in ___ipairs(self._tri_list) do
		v.texture_name = value
	end
end

function ALittle.Piechart.__getter:texture_name()
	return self._pie_texture_name
end

function ALittle.Piechart:SetDegree(start_c, end_c)
	if end_c <= start_c then
		return
	end
	local width = self.width
	local height = self.height
	for k, v in ___ipairs(self._tri_list) do
		v.visible = false
	end
	local e_offset = 0.0
	local s_offset = 0.0
	if end_c >= 0 and end_c <= 45 then
		s_offset = (45 - start_c) / 90
		e_offset = (45 - end_c) / 90
		self:SetTriangleUV(self._tri_list[1], 1, e_offset, 1, s_offset)
		self:SetTriangleXY(self._tri_list[1], width, e_offset * height, width, s_offset * height)
	elseif end_c <= 135 then
		e_offset = (135 - end_c) / 90
		if start_c < 45 then
			s_offset = (45 - start_c) / 90
			self:SetTriangleUV(self._tri_list[1], 1, 0, 1, s_offset)
			self:SetTriangleXY(self._tri_list[1], width, 0, width, s_offset * height)
			self:SetTriangleUV(self._tri_list[2], e_offset, 0, self._tri_list[1].u1, self._tri_list[1].v1)
			self:SetTriangleXY(self._tri_list[2], e_offset * width, 0, self._tri_list[1].x1, self._tri_list[1].y1)
		else
			e_offset = (135 - end_c) / 90
			s_offset = (135 - start_c) / 90
			self:SetTriangleUV(self._tri_list[2], e_offset, 0, s_offset, 0)
			self:SetTriangleXY(self._tri_list[2], e_offset * width, 0, s_offset * width, 0)
		end
	elseif end_c <= 225 then
		e_offset = (end_c - 135) / 90
		if start_c < 45 then
			s_offset = (45 - start_c) / 90
			self:SetTriangleUV(self._tri_list[1], 1, 0, 1, s_offset)
			self:SetTriangleXY(self._tri_list[1], width, 0, width, s_offset * height)
			self:SetTriangleUV(self._tri_list[2], 0, 0, self._tri_list[1].u1, self._tri_list[1].v1)
			self:SetTriangleXY(self._tri_list[2], 0, 0, self._tri_list[1].x1, self._tri_list[1].y1)
			self:SetTriangleUV(self._tri_list[3], self._tri_list[2].u1, self._tri_list[2].v1, 0, e_offset)
			self:SetTriangleXY(self._tri_list[3], self._tri_list[2].x1, self._tri_list[2].y1, 0, e_offset * height)
		elseif start_c < 135 then
			s_offset = (135 - start_c) / 90
			self:SetTriangleUV(self._tri_list[2], 0, 0, s_offset, 0)
			self:SetTriangleXY(self._tri_list[2], 0, 0, s_offset * width, 0)
			self:SetTriangleUV(self._tri_list[3], self._tri_list[2].u1, self._tri_list[2].v1, 0, e_offset)
			self:SetTriangleXY(self._tri_list[3], self._tri_list[2].x1, self._tri_list[2].y1, 0, e_offset * height)
		else
			s_offset = (start_c - 135) / 90
			self:SetTriangleUV(self._tri_list[3], 0, s_offset, 0, e_offset)
			self:SetTriangleXY(self._tri_list[3], 0, s_offset * height, 0, e_offset * height)
		end
	elseif end_c <= 315 then
		e_offset = (end_c - 225) / 90
		if start_c < 45 then
			s_offset = (45 - start_c) / 90
			self:SetTriangleUV(self._tri_list[1], 1, 0, 1, s_offset)
			self:SetTriangleXY(self._tri_list[1], width, 0, width, s_offset * height)
			self:SetTriangleUV(self._tri_list[2], 0, 0, self._tri_list[1].u1, self._tri_list[1].v1)
			self:SetTriangleXY(self._tri_list[2], 0, 0, self._tri_list[1].x1, self._tri_list[1].y1)
			self:SetTriangleUV(self._tri_list[3], self._tri_list[2].u1, self._tri_list[2].v1, 0, 1)
			self:SetTriangleXY(self._tri_list[3], self._tri_list[2].x1, self._tri_list[2].y1, 0, height)
			self:SetTriangleUV(self._tri_list[4], self._tri_list[3].u3, self._tri_list[3].v3, e_offset, 1)
			self:SetTriangleXY(self._tri_list[4], self._tri_list[3].x3, self._tri_list[3].y3, e_offset * width, height)
		elseif start_c < 135 then
			s_offset = (135 - start_c) / 90
			self:SetTriangleUV(self._tri_list[2], 0, 0, s_offset, 0)
			self:SetTriangleXY(self._tri_list[2], 0, 0, s_offset * width, 0)
			self:SetTriangleUV(self._tri_list[3], self._tri_list[2].u1, self._tri_list[2].v1, 0, 1)
			self:SetTriangleXY(self._tri_list[3], self._tri_list[2].x1, self._tri_list[2].y1, 0, height)
			self:SetTriangleUV(self._tri_list[4], self._tri_list[3].u3, self._tri_list[3].v3, e_offset, 1)
			self:SetTriangleXY(self._tri_list[4], self._tri_list[3].x3, self._tri_list[3].y3, e_offset * width, height)
		elseif start_c < 225 then
			s_offset = (start_c - 135) / 90
			self:SetTriangleUV(self._tri_list[3], 0, s_offset, 0, 1)
			self:SetTriangleXY(self._tri_list[3], 0, s_offset * height, 0, height)
			self:SetTriangleUV(self._tri_list[4], self._tri_list[3].u3, self._tri_list[3].v3, e_offset, 1)
			self:SetTriangleXY(self._tri_list[4], self._tri_list[3].x3, self._tri_list[3].y3, e_offset * width, height)
		else
			s_offset = (start_c - 225) / 90
			self:SetTriangleUV(self._tri_list[4], s_offset, 1, e_offset, 1)
			self:SetTriangleXY(self._tri_list[4], s_offset * width, height, e_offset * width, height)
		end
	else
		e_offset = (405 - end_c) / 90
		if start_c < 45 then
			s_offset = (45 - start_c) / 90
			self:SetTriangleUV(self._tri_list[1], 1, 0, 1, s_offset)
			self:SetTriangleXY(self._tri_list[1], width, 0, width, s_offset * height)
			self:SetTriangleUV(self._tri_list[2], 0, 0, self._tri_list[1].u1, self._tri_list[1].v1)
			self:SetTriangleXY(self._tri_list[2], 0, 0, self._tri_list[1].x1, self._tri_list[1].y1)
			self:SetTriangleUV(self._tri_list[3], self._tri_list[2].u1, self._tri_list[2].v1, 0, 1)
			self:SetTriangleXY(self._tri_list[3], self._tri_list[2].x1, self._tri_list[2].y1, 0, height)
			self:SetTriangleUV(self._tri_list[4], self._tri_list[3].u3, self._tri_list[3].v3, 1, 1)
			self:SetTriangleXY(self._tri_list[4], self._tri_list[3].x3, self._tri_list[3].y3, width, height)
			self:SetTriangleUV(self._tri_list[5], 1, e_offset, self._tri_list[4].u3, self._tri_list[4].v3)
			self:SetTriangleXY(self._tri_list[5], width, e_offset * height, self._tri_list[4].x3, self._tri_list[4].y3)
		elseif start_c < 135 then
			s_offset = (135 - start_c) / 90
			self:SetTriangleUV(self._tri_list[2], 0, 0, s_offset, 0)
			self:SetTriangleXY(self._tri_list[2], 0, 0, s_offset * width, 0)
			self:SetTriangleUV(self._tri_list[3], self._tri_list[2].u1, self._tri_list[2].v1, 0, 1)
			self:SetTriangleXY(self._tri_list[3], self._tri_list[2].x1, self._tri_list[2].y1, 0, height)
			self:SetTriangleUV(self._tri_list[4], self._tri_list[3].u3, self._tri_list[3].v3, 1, 1)
			self:SetTriangleXY(self._tri_list[4], self._tri_list[3].x3, self._tri_list[3].y3, width, height)
			self:SetTriangleUV(self._tri_list[1], 1, e_offset, self._tri_list[4].u3, self._tri_list[4].v3)
			self:SetTriangleXY(self._tri_list[1], width, e_offset * height, self._tri_list[4].x3, self._tri_list[4].y3)
		elseif start_c < 225 then
			s_offset = (start_c - 135) / 90
			self:SetTriangleUV(self._tri_list[3], 0, s_offset, 0, 1)
			self:SetTriangleXY(self._tri_list[3], 0, s_offset * height, 0, height)
			self:SetTriangleUV(self._tri_list[4], self._tri_list[3].u3, self._tri_list[3].v3, 1, 1)
			self:SetTriangleXY(self._tri_list[4], self._tri_list[3].x3, self._tri_list[3].y3, width, height)
			self:SetTriangleUV(self._tri_list[1], 1, e_offset, self._tri_list[4].u3, self._tri_list[4].v3)
			self:SetTriangleXY(self._tri_list[1], width, e_offset * height, self._tri_list[4].x3, self._tri_list[4].y3)
		elseif start_c < 315 then
			s_offset = (start_c - 225) / 90
			self:SetTriangleUV(self._tri_list[4], s_offset, 1, 1, 1)
			self:SetTriangleXY(self._tri_list[4], s_offset * width, height, width, height)
			self:SetTriangleUV(self._tri_list[1], 1, e_offset, self._tri_list[4].u3, self._tri_list[4].v3)
			self:SetTriangleXY(self._tri_list[1], width, e_offset * height, self._tri_list[4].x3, self._tri_list[4].y3)
		else
			s_offset = (405 - start_c) / 90
			self:SetTriangleUV(self._tri_list[1], 1, e_offset, 1, s_offset)
			self:SetTriangleXY(self._tri_list[1], width, e_offset * height, width, s_offset * height)
		end
	end
end

function ALittle.Piechart:SetTriangleXY(tri, x1, y1, x3, y3)
	tri.x1 = x1
	tri.y1 = y1
	tri.x3 = x3
	tri.y3 = y3
	tri.visible = true
end

function ALittle.Piechart:SetTriangleUV(tri, u1, v1, u3, v3)
	tri.u1 = u1
	tri.v1 = v1
	tri.u3 = u3
	tri.v3 = v3
end

end