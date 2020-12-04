-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.NESMirroringType = {
	VERTICAL_MIRRORING = 0,
	HORIZONTAL_MIRRORING = 1,
	FOURSCREEN_MIRRORING = 2,
	SINGLESCREEN_MIRRORING = 3,
	SINGLESCREEN_MIRRORING2 = 4,
	SINGLESCREEN_MIRRORING3 = 5,
	SINGLESCREEN_MIRRORING4 = 6,
	CHRROM_MIRRORING = 7,
}

NESEmulator.NesRom = Lua.Class(nil, "NESEmulator.NesRom")

function NESEmulator.NesRom:Ctor(nes)
	___rawset(self, "_mapper_name", {})
	___rawset(self, "_rom_count", 0)
	___rawset(self, "_vrom_count", 0)
	___rawset(self, "_mirroring", 0)
	___rawset(self, "_battery_ram_len", 0)
	___rawset(self, "_trainer", false)
	___rawset(self, "_four_screen", false)
	___rawset(self, "_mapper_type", 0)
	___rawset(self, "_valid", false)
	___rawset(self, "_nes", nes)
	local i = 0
	while true do
		if not(i < 92) then break end
		self._mapper_name[i] = "Unknown Mapper"
		i = i+(1)
	end
	self._mapper_name[0] = "Direct Access"
	self._mapper_name[1] = "Nintendo MMC1"
	self._mapper_name[2] = "UNROM"
	self._mapper_name[3] = "CNROM"
	self._mapper_name[4] = "Nintendo MMC3"
	self._mapper_name[5] = "Nintendo MMC5"
	self._mapper_name[6] = "FFE F4xxx"
	self._mapper_name[7] = "AOROM"
	self._mapper_name[8] = "FFE F3xxx"
	self._mapper_name[9] = "Nintendo MMC2"
	self._mapper_name[10] = "Nintendo MMC4"
	self._mapper_name[11] = "Color Dreams Chip"
	self._mapper_name[12] = "FFE F6xxx"
	self._mapper_name[15] = "100-in-1 switch"
	self._mapper_name[16] = "Bandai chip"
	self._mapper_name[17] = "FFE F8xxx"
	self._mapper_name[18] = "Jaleco SS8806 chip"
	self._mapper_name[19] = "Namcot 106 chip"
	self._mapper_name[20] = "Famicom Disk System"
	self._mapper_name[21] = "Konami VRC4a"
	self._mapper_name[22] = "Konami VRC2a"
	self._mapper_name[23] = "Konami VRC2a"
	self._mapper_name[24] = "Konami VRC6"
	self._mapper_name[25] = "Konami VRC4b"
	self._mapper_name[32] = "Irem G-101 chip"
	self._mapper_name[33] = "Taito TC0190/TC0350"
	self._mapper_name[34] = "32kB ROM switch"
	self._mapper_name[64] = "Tengen RAMBO-1 chip"
	self._mapper_name[65] = "Irem H-3001 chip"
	self._mapper_name[66] = "GNROM switch"
	self._mapper_name[67] = "SunSoft3 chip"
	self._mapper_name[68] = "SunSoft4 chip"
	self._mapper_name[69] = "SunSoft5 FME-7 chip"
	self._mapper_name[71] = "Camerica chip"
	self._mapper_name[78] = "Irem 74HC161/32-based"
	self._mapper_name[91] = "Pirate HK-SF3 chip"
end

function NESEmulator.NesRom:Load(data, battery_ram)
	local offset = 0
	if data:ReadUChar(offset) ~= 0x4E then
		return "Not a valid NES ROM."
	end
	offset = offset + 1
	if data:ReadUChar(offset) ~= 0x45 then
		return "Not a valid NES ROM."
	end
	offset = offset + 1
	if data:ReadUChar(offset) ~= 0x53 then
		return "Not a valid NES ROM."
	end
	offset = offset + 1
	if data:ReadUChar(offset) ~= 0x1A then
		return "Not a valid NES ROM."
	end
	offset = offset + 1
	self._rom_count = data:ReadUChar(offset)
	offset = offset + 1
	self._vrom_count = data:ReadUChar(offset) * 2
	offset = offset + 1
	local flag1 = data:ReadUChar(offset)
	offset = offset + 1
	local flag2 = data:ReadUChar(offset)
	offset = offset + 1
	self._mirroring = NESEmulator.ConditionExpr((flag1 & 1) ~= 0, 1, 0)
	local has_battery_ram = flag1 & 2 ~= 0
	if has_battery_ram then
		self._battery_ram = {}
		self._battery_ram_len = 0x2000
		local i = 0
		while true do
			if not(i < self._battery_ram_len) then break end
			self._battery_ram[i] = 0
			i = i+(1)
		end
		if battery_ram ~= nil then
			local len = battery_ram:GetSize()
			local i = 0
			while true do
				if not(i < len) then break end
				self._battery_ram[i] = battery_ram:ReadUChar(i)
				i = i+(1)
			end
		end
	else
		self._battery_ram = nil
		self._battery_ram_len = 0
	end
	self._trainer = flag1 & 4 ~= 0
	self._four_screen = flag1 & 8 ~= 0
	self._mapper_type = flag1 >> 4 | flag2 & 0xf0
	local found_error = false
	local i = 8
	while true do
		if not(i < 16) then break end
		if data:ReadUChar(i) ~= 0 then
			found_error = true
			break
		end
		i = i+(1)
	end
	if found_error then
		self._mapper_type = self._mapper_type & 0xf
	end
	offset = 16
	self._rom = {}
	local i = 0
	while true do
		if not(i < self._rom_count) then break end
		self._rom[i] = {}
		local j = 0
		while true do
			if not(j < 16384) then break end
			if offset + j >= data:GetSize() then
				break
			end
			self._rom[i][j] = data:ReadUChar(offset + j)
			j = j+(1)
		end
		offset = offset + (16384)
		i = i+(1)
	end
	self._vrom = {}
	local i = 0
	while true do
		if not(i < self._vrom_count) then break end
		self._vrom[i] = {}
		local j = 0
		while true do
			if not(j < 4096) then break end
			if offset + j >= data:GetSize() then
				break
			end
			self._vrom[i][j] = data:ReadUChar(offset + j)
			j = j+(1)
		end
		offset = offset + (4096)
		i = i+(1)
	end
	self._vrom_tile = {}
	local i = 0
	while true do
		if not(i < self._vrom_count) then break end
		self._vrom_tile[i] = {}
		local j = 0
		while true do
			if not(j < 256) then break end
			self._vrom_tile[i][j] = NESEmulator.NesTile()
			j = j+(1)
		end
		i = i+(1)
	end
	local v = 0
	while true do
		if not(v < self._vrom_count) then break end
		local i = 0
		while true do
			if not(i < 4096) then break end
			local tile_index = i >> 4
			local left_over = i % 16
			if left_over < 8 then
				self._vrom_tile[v][tile_index]:SetScanline(left_over, self._vrom[v][i], self._vrom[v][i + 8])
			else
				self._vrom_tile[v][tile_index]:SetScanline(left_over - 8, self._vrom[v][i - 8], self._vrom[v][i])
			end
			i = i+(1)
		end
		v = v+(1)
	end
	self._valid = true
	return nil
end

function NESEmulator.NesRom:GetMirroringType()
	if self._four_screen then
		return NESEmulator.NESMirroringType.FOURSCREEN_MIRRORING
	end
	if self._mirroring == 0 then
		return NESEmulator.NESMirroringType.HORIZONTAL_MIRRORING
	end
	return NESEmulator.NESMirroringType.VERTICAL_MIRRORING
end

function NESEmulator.NesRom:GetMapperName()
	local name = self._mapper_name[self._mapper_type]
	if name ~= nil then
		return name
	end
	return "Unknow Mapper, " .. self._mapper_type
end

function NESEmulator.NesRom:CreateMapper()
	return NESEmulator.CreateNesMapper(self._nes, self._mapper_type)
end

end