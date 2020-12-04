-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.NesPaletteTable = Lua.Class(nil, "NESEmulator.NesPaletteTable")

function NESEmulator.NesPaletteTable:Ctor()
	___rawset(self, "_cur_table", {})
	___rawset(self, "_emph_table", {})
	___rawset(self, "_current_emph", -1)
end

function NESEmulator.NesPaletteTable:Reset()
	self:SetEmphasis(0)
end

function NESEmulator.NesPaletteTable:LoadNTSCPalette()
	local values = {0x525252, 0xB40000, 0xA00000, 0xB1003D, 0x740069, 0x00005B, 0x00005F, 0x001840, 0x002F10, 0x084A08, 0x006700, 0x124200, 0x6D2800, 0x000000, 0x000000, 0x000000, 0xC4D5E7, 0xFF4000, 0xDC0E22, 0xFF476B, 0xD7009F, 0x680AD7, 0x0019BC, 0x0054B1, 0x006A5B, 0x008C03, 0x00AB00, 0x2C8800, 0xA47200, 0x000000, 0x000000, 0x000000, 0xF8F8F8, 0xFFAB3C, 0xFF7981, 0xFF5BC5, 0xFF48F2, 0xDF49FF, 0x476DFF, 0x00B4F7, 0x00E0FF, 0x00E375, 0x03F42B, 0x78B82E, 0xE5E218, 0x787878, 0x000000, 0x000000, 0xFFFFFF, 0xFFF2BE, 0xF8B8B8, 0xF8B8D8, 0xFFB6FF, 0xFFC3FF, 0xC7D1FF, 0x9ADAFF, 0x88EDF8, 0x83FFDD, 0xB8F8B8, 0xF5F8AC, 0xFFFFB0, 0xF8D8F8, 0x000000, 0x000000}
	for index, value in ___ipairs(values) do
		self._cur_table[index - 1] = value
	end
	self:MakeTables()
	self:SetEmphasis(0)
end

function NESEmulator.NesPaletteTable:LoadPALPalette()
	local values = {0x525252, 0xB40000, 0xA00000, 0xB1003D, 0x740069, 0x00005B, 0x00005F, 0x001840, 0x002F10, 0x084A08, 0x006700, 0x124200, 0x6D2800, 0x000000, 0x000000, 0x000000, 0xC4D5E7, 0xFF4000, 0xDC0E22, 0xFF476B, 0xD7009F, 0x680AD7, 0x0019BC, 0x0054B1, 0x006A5B, 0x008C03, 0x00AB00, 0x2C8800, 0xA47200, 0x000000, 0x000000, 0x000000, 0xF8F8F8, 0xFFAB3C, 0xFF7981, 0xFF5BC5, 0xFF48F2, 0xDF49FF, 0x476DFF, 0x00B4F7, 0x00E0FF, 0x00E375, 0x03F42B, 0x78B82E, 0xE5E218, 0x787878, 0x000000, 0x000000, 0xFFFFFF, 0xFFF2BE, 0xF8B8B8, 0xF8B8D8, 0xFFB6FF, 0xFFC3FF, 0xC7D1FF, 0x9ADAFF, 0x88EDF8, 0x83FFDD, 0xB8F8B8, 0xF5F8AC, 0xFFFFB0, 0xF8D8F8, 0x000000, 0x000000}
	for index, value in ___ipairs(values) do
		self._cur_table[index - 1] = value
	end
	self:MakeTables()
	self:SetEmphasis(0)
end

function NESEmulator.NesPaletteTable:MakeTables()
	local r = 0
	local g = 0
	local b = 0
	local col = 0
	local rFactor = 0.0
	local gFactor = 0.0
	local bFactor = 0.0
	local emph = 0
	while true do
		if not(emph < 8) then break end
		rFactor = 1.0
		gFactor = 1.0
		bFactor = 1.0
		if (emph & 1) ~= 0 then
			rFactor = 0.75
			bFactor = 0.75
		end
		if (emph & 2) ~= 0 then
			rFactor = 0.75
			gFactor = 0.75
		end
		if (emph & 4) ~= 0 then
			gFactor = 0.75
			bFactor = 0.75
		end
		self._emph_table[emph] = {}
		local i = 0
		while true do
			if not(i < 64) then break end
			col = self._cur_table[i]
			r = ALittle.Math_Floor(self:GetRed(col) * rFactor)
			g = ALittle.Math_Floor(self:GetGreen(col) * gFactor)
			b = ALittle.Math_Floor(self:GetBlue(col) * bFactor)
			self._emph_table[emph][i] = self:GetRgb(r, g, b)
			i = i+(1)
		end
		emph = emph+(1)
	end
end

function NESEmulator.NesPaletteTable:SetEmphasis(emph)
	if emph ~= self._current_emph then
		self._current_emph = emph
		local i = 0
		while true do
			if not(i < 64) then break end
			self._cur_table[i] = self._emph_table[emph][i]
			i = i+(1)
		end
	end
end

function NESEmulator.NesPaletteTable:GetEntry(yiq)
	return self._cur_table[yiq]
end

function NESEmulator.NesPaletteTable:GetRed(rgb)
	return (rgb >> 16) & 0xff
end

function NESEmulator.NesPaletteTable:GetGreen(rgb)
	return (rgb >> 8) & 0xff
end

function NESEmulator.NesPaletteTable:GetBlue(rgb)
	return rgb & 0xff
end

function NESEmulator.NesPaletteTable:GetRgb(r, g, b)
	return (r << 16) | (g << 8) | b
end

function NESEmulator.NesPaletteTable:LoadDefaultPalette()
	self._cur_table[0] = self:GetRgb(117, 117, 117)
	self._cur_table[1] = self:GetRgb(39, 27, 143)
	self._cur_table[2] = self:GetRgb(0, 0, 171)
	self._cur_table[3] = self:GetRgb(71, 0, 159)
	self._cur_table[4] = self:GetRgb(143, 0, 119)
	self._cur_table[5] = self:GetRgb(171, 0, 19)
	self._cur_table[6] = self:GetRgb(167, 0, 0)
	self._cur_table[7] = self:GetRgb(127, 11, 0)
	self._cur_table[8] = self:GetRgb(67, 47, 0)
	self._cur_table[9] = self:GetRgb(0, 71, 0)
	self._cur_table[10] = self:GetRgb(0, 81, 0)
	self._cur_table[11] = self:GetRgb(0, 63, 23)
	self._cur_table[12] = self:GetRgb(27, 63, 95)
	self._cur_table[13] = self:GetRgb(0, 0, 0)
	self._cur_table[14] = self:GetRgb(0, 0, 0)
	self._cur_table[15] = self:GetRgb(0, 0, 0)
	self._cur_table[16] = self:GetRgb(188, 188, 188)
	self._cur_table[17] = self:GetRgb(0, 115, 239)
	self._cur_table[18] = self:GetRgb(35, 59, 239)
	self._cur_table[19] = self:GetRgb(131, 0, 243)
	self._cur_table[20] = self:GetRgb(191, 0, 191)
	self._cur_table[21] = self:GetRgb(231, 0, 91)
	self._cur_table[22] = self:GetRgb(219, 43, 0)
	self._cur_table[23] = self:GetRgb(203, 79, 15)
	self._cur_table[24] = self:GetRgb(139, 115, 0)
	self._cur_table[25] = self:GetRgb(0, 151, 0)
	self._cur_table[26] = self:GetRgb(0, 171, 0)
	self._cur_table[27] = self:GetRgb(0, 147, 59)
	self._cur_table[28] = self:GetRgb(0, 131, 139)
	self._cur_table[29] = self:GetRgb(0, 0, 0)
	self._cur_table[30] = self:GetRgb(0, 0, 0)
	self._cur_table[31] = self:GetRgb(0, 0, 0)
	self._cur_table[32] = self:GetRgb(255, 255, 255)
	self._cur_table[33] = self:GetRgb(63, 191, 255)
	self._cur_table[34] = self:GetRgb(95, 151, 255)
	self._cur_table[35] = self:GetRgb(167, 139, 253)
	self._cur_table[36] = self:GetRgb(247, 123, 255)
	self._cur_table[37] = self:GetRgb(255, 119, 183)
	self._cur_table[38] = self:GetRgb(255, 119, 99)
	self._cur_table[39] = self:GetRgb(255, 155, 59)
	self._cur_table[40] = self:GetRgb(243, 191, 63)
	self._cur_table[41] = self:GetRgb(131, 211, 19)
	self._cur_table[42] = self:GetRgb(79, 223, 75)
	self._cur_table[43] = self:GetRgb(88, 248, 152)
	self._cur_table[44] = self:GetRgb(0, 235, 219)
	self._cur_table[45] = self:GetRgb(0, 0, 0)
	self._cur_table[46] = self:GetRgb(0, 0, 0)
	self._cur_table[47] = self:GetRgb(0, 0, 0)
	self._cur_table[48] = self:GetRgb(255, 255, 255)
	self._cur_table[49] = self:GetRgb(171, 231, 255)
	self._cur_table[50] = self:GetRgb(199, 215, 255)
	self._cur_table[51] = self:GetRgb(215, 203, 255)
	self._cur_table[52] = self:GetRgb(255, 199, 255)
	self._cur_table[53] = self:GetRgb(255, 199, 219)
	self._cur_table[54] = self:GetRgb(255, 191, 179)
	self._cur_table[55] = self:GetRgb(255, 219, 171)
	self._cur_table[56] = self:GetRgb(255, 231, 163)
	self._cur_table[57] = self:GetRgb(227, 255, 163)
	self._cur_table[58] = self:GetRgb(171, 243, 191)
	self._cur_table[59] = self:GetRgb(179, 255, 207)
	self._cur_table[60] = self:GetRgb(159, 255, 243)
	self._cur_table[61] = self:GetRgb(0, 0, 0)
	self._cur_table[62] = self:GetRgb(0, 0, 0)
	self._cur_table[63] = self:GetRgb(0, 0, 0)
	self:MakeTables()
	self:SetEmphasis(0)
end

end