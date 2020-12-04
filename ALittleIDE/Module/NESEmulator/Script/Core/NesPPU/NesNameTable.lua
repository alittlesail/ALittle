-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.NesNameTable = Lua.Class(nil, "NESEmulator.NesNameTable")

function NESEmulator.NesNameTable:Ctor(width, height, name)
	___rawset(self, "_width", width)
	___rawset(self, "_height", height)
	___rawset(self, "_name", name)
	___rawset(self, "_tile", {})
	___rawset(self, "_attrib", {})
	local size = self._width * self._height
	local i = 0
	while true do
		if not(i < size) then break end
		self._tile[i] = 0
		self._attrib[i] = 0
		i = i+(1)
	end
end

function NESEmulator.NesNameTable:GetTileIndex(x, y)
	return self._tile[y * self._width + x]
end

function NESEmulator.NesNameTable:GetAttrib(x, y)
	return self._attrib[y * self._width + x]
end

function NESEmulator.NesNameTable:WriteAttrib(index, value)
	local basex = (index % 8) * 4
	local basey = ALittle.Math_Floor(index / 8) * 4
	local add = 0
	local tx = 0
	local ty = 0
	local attindex = 0
	local sqy = 0
	while true do
		if not(sqy < 2) then break end
		local sqx = 0
		while true do
			if not(sqx < 2) then break end
			add = (value >> (2 * (sqy * 2 + sqx))) & 3
			local y = 0
			while true do
				if not(y < 2) then break end
				local x = 0
				while true do
					if not(x < 2) then break end
					tx = basex + sqx * 2 + x
					ty = basey + sqy * 2 + y
					attindex = ty * self._width + tx
					self._attrib[attindex] = (add << 2) & 12
					x = x+(1)
				end
				y = y+(1)
			end
			sqx = sqx+(1)
		end
		sqy = sqy+(1)
	end
end

end