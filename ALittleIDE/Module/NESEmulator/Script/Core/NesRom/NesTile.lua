-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.NesTile = Lua.Class(nil, "NESEmulator.NesTile")

function NESEmulator.NesTile:Ctor()
	___rawset(self, "_pix", {})
	___rawset(self, "_init", false)
end

function NESEmulator.NesTile:SetBuffer(scanline)
	local y = 0
	while true do
		if not(y < 8) then break end
		self:SetScanline(y, scanline[y], scanline[y + 8])
		y = y+(1)
	end
end

function NESEmulator.NesTile:SetScanline(sline, b1, b2)
	self._init = true
	local t_index = sline << 3
	local x = 0
	while true do
		if not(x < 8) then break end
		self._pix[t_index + x] = ((b1 >> (7 - x)) & 1) + (((b2 >> (7 - x)) & 1) << 1)
		if self._pix[t_index + x] == 0 then
			self._opaque[sline] = false
		end
		x = x+(1)
	end
end

function NESEmulator.NesTile:Render(buffer, src_x1, src_y1, src_x2, src_y2, dx, dy, pal_add, palette, flip_horizontal, flip_vertical, pri, pri_table)
	if dx < -7 or dx >= 256 or dy < -7 or dy >= 240 then
		return
	end
	local w = src_x2 - src_x1
	local h = src_y2 - src_y1
	if dx < 0 then
		src_x1 = src_x1 - (dx)
	end
	if dx + src_x2 >= 256 then
		src_x2 = 256 - dx
	end
	if dy < 0 then
		src_y1 = src_y1 - (dy)
	end
	if dy + src_y2 >= 240 then
		src_y2 = 240 - dy
	end
	if not flip_horizontal and not flip_vertical then
		local fb_index = (dy << 8) + dx
		local t_index = 0
		local y = 0
		while true do
			if not(y < 8) then break end
			local x = 0
			while true do
				if not(x < 8) then break end
				if x >= src_x1 and x < src_x2 and y >= src_y1 and y < src_y2 then
					local pal_index = self._pix[t_index]
					local tpri = pri_table[fb_index]
					if pal_index ~= 0 and pri <= (tpri & 0xff) then
						buffer[fb_index] = palette[pal_index + pal_add]
						tpri = (tpri & 0xf00) | pri
						pri_table[fb_index] = tpri
					end
				end
				fb_index = fb_index + 1
				t_index = t_index + 1
				x = x+(1)
			end
			fb_index = fb_index - (8)
			fb_index = fb_index + (256)
			y = y+(1)
		end
	elseif flip_horizontal and not flip_vertical then
		local fb_index = (dy << 8) + dx
		local t_index = 7
		local y = 0
		while true do
			if not(y < 8) then break end
			local x = 0
			while true do
				if not(x < 8) then break end
				if x >= src_x1 and x < src_x2 and y >= src_y1 and y < src_y2 then
					local pal_index = self._pix[t_index]
					local tpri = pri_table[fb_index]
					if pal_index ~= 0 and pri <= (tpri & 0xff) then
						buffer[fb_index] = palette[pal_index + pal_add]
						tpri = (tpri & 0xf00) | pri
						pri_table[fb_index] = tpri
					end
				end
				fb_index = fb_index + 1
				t_index = t_index - 1
				x = x+(1)
			end
			fb_index = fb_index - (8)
			fb_index = fb_index + (256)
			t_index = t_index + (16)
			y = y+(1)
		end
	elseif not flip_horizontal and flip_vertical then
		local fb_index = (dy << 8) + dx
		local t_index = 56
		local y = 0
		while true do
			if not(y < 8) then break end
			local x = 0
			while true do
				if not(x < 8) then break end
				if x >= src_x1 and x < src_x2 and y >= src_y1 and y < src_y2 then
					local pal_index = self._pix[t_index]
					local tpri = pri_table[fb_index]
					if pal_index ~= 0 and pri <= (tpri & 0xff) then
						buffer[fb_index] = palette[pal_index + pal_add]
						tpri = (tpri & 0xf00) | pri
						pri_table[fb_index] = tpri
					end
				end
				fb_index = fb_index + 1
				t_index = t_index + 1
				x = x+(1)
			end
			fb_index = fb_index - (8)
			fb_index = fb_index + (256)
			t_index = t_index - (16)
			y = y+(1)
		end
	else
		local fb_index = (dy << 8) + dx
		local t_index = 63
		local y = 0
		while true do
			if not(y < 8) then break end
			local x = 0
			while true do
				if not(x < 8) then break end
				if x >= src_x1 and x < src_x2 and y >= src_y1 and y < src_y2 then
					local pal_index = self._pix[t_index]
					local tpri = pri_table[fb_index]
					if pal_index ~= 0 and pri <= (tpri & 0xff) then
						buffer[fb_index] = palette[pal_index + pal_add]
						tpri = (tpri & 0xf00) | pri
						pri_table[fb_index] = tpri
					end
				end
				fb_index = fb_index + 1
				t_index = t_index - 1
				x = x+(1)
			end
			fb_index = fb_index - (8)
			fb_index = fb_index + (256)
			y = y+(1)
		end
	end
end

function NESEmulator.NesTile:IsTransparent(x, y)
	return self._pix[(y << 3) + x] == 0
end

end