{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NESMirroringType = {
	VERTICAL_MIRRORING : 0,
	HORIZONTAL_MIRRORING : 1,
	FOURSCREEN_MIRRORING : 2,
	SINGLESCREEN_MIRRORING : 3,
	SINGLESCREEN_MIRRORING2 : 4,
	SINGLESCREEN_MIRRORING3 : 5,
	SINGLESCREEN_MIRRORING4 : 6,
	CHRROM_MIRRORING : 7,
}

NESEmulator.NesRom = JavaScript.Class(undefined, {
	Ctor : function(nes) {
		this._mapper_name = new Map();
		this._rom_count = 0;
		this._vrom_count = 0;
		this._mirroring = 0;
		this._battery_ram_len = 0;
		this._trainer = false;
		this._four_screen = false;
		this._mapper_type = 0;
		this._valid = false;
		this._nes = nes;
		for (let i = 0; i < 92; i += 1) {
			this._mapper_name.set(i, "Unknown Mapper");
		}
		this._mapper_name.set(0, "Direct Access");
		this._mapper_name.set(1, "Nintendo MMC1");
		this._mapper_name.set(2, "UNROM");
		this._mapper_name.set(3, "CNROM");
		this._mapper_name.set(4, "Nintendo MMC3");
		this._mapper_name.set(5, "Nintendo MMC5");
		this._mapper_name.set(6, "FFE F4xxx");
		this._mapper_name.set(7, "AOROM");
		this._mapper_name.set(8, "FFE F3xxx");
		this._mapper_name.set(9, "Nintendo MMC2");
		this._mapper_name.set(10, "Nintendo MMC4");
		this._mapper_name.set(11, "Color Dreams Chip");
		this._mapper_name.set(12, "FFE F6xxx");
		this._mapper_name.set(15, "100-in-1 switch");
		this._mapper_name.set(16, "Bandai chip");
		this._mapper_name.set(17, "FFE F8xxx");
		this._mapper_name.set(18, "Jaleco SS8806 chip");
		this._mapper_name.set(19, "Namcot 106 chip");
		this._mapper_name.set(20, "Famicom Disk System");
		this._mapper_name.set(21, "Konami VRC4a");
		this._mapper_name.set(22, "Konami VRC2a");
		this._mapper_name.set(23, "Konami VRC2a");
		this._mapper_name.set(24, "Konami VRC6");
		this._mapper_name.set(25, "Konami VRC4b");
		this._mapper_name.set(32, "Irem G-101 chip");
		this._mapper_name.set(33, "Taito TC0190/TC0350");
		this._mapper_name.set(34, "32kB ROM switch");
		this._mapper_name.set(64, "Tengen RAMBO-1 chip");
		this._mapper_name.set(65, "Irem H-3001 chip");
		this._mapper_name.set(66, "GNROM switch");
		this._mapper_name.set(67, "SunSoft3 chip");
		this._mapper_name.set(68, "SunSoft4 chip");
		this._mapper_name.set(69, "SunSoft5 FME-7 chip");
		this._mapper_name.set(71, "Camerica chip");
		this._mapper_name.set(78, "Irem 74HC161/32-based");
		this._mapper_name.set(91, "Pirate HK-SF3 chip");
	},
	Load : function(data, battery_ram) {
		let offset = 0;
		if (data.ReadUChar(offset) !== 0x4E) {
			return "Not a valid NES ROM.";
		}
		++ offset;
		if (data.ReadUChar(offset) !== 0x45) {
			return "Not a valid NES ROM.";
		}
		++ offset;
		if (data.ReadUChar(offset) !== 0x53) {
			return "Not a valid NES ROM.";
		}
		++ offset;
		if (data.ReadUChar(offset) !== 0x1A) {
			return "Not a valid NES ROM.";
		}
		++ offset;
		this._rom_count = data.ReadUChar(offset);
		++ offset;
		this._vrom_count = data.ReadUChar(offset) * 2;
		++ offset;
		let flag = data.ReadUChar(offset);
		++ offset;
		this._mirroring = 0;
		if (flag & 1 !== 0) {
			this._mirroring = 1;
		}
		let has_battery_ram = flag & 2 !== 0;
		if (has_battery_ram) {
			this._battery_ram = new Map();
			this._battery_ram_len = 0x2000;
			for (let i = 0; i < this._battery_ram_len; i += 1) {
				this._battery_ram.set(i, 0);
			}
			if (battery_ram !== undefined) {
				let len = battery_ram.GetSize();
				for (let i = 0; i < len; i += 1) {
					this._battery_ram.set(i, battery_ram.ReadUChar(i));
				}
			}
		} else {
			this._battery_ram = undefined;
			this._battery_ram_len = 0;
		}
		this._trainer = flag & 4 !== 0;
		this._four_screen = flag & 8 !== 0;
		this._mapper_type = (flag & 6) >> 4 | (flag & 7) & 0xf0;
		let found_error = false;
		for (let i = 8; i < 16; i += 1) {
			if (data.ReadUChar(i) !== 0) {
				found_error = true;
				break;
			}
		}
		if (found_error) {
			this._mapper_type = this._mapper_type & 0xf;
		}
		offset = 16;
		this._rom = new Map();
		for (let i = 0; i < this._rom_count; i += 1) {
			this._rom.set(i, new Map());
			for (let j = 0; j < 16384; j += 1) {
				if (offset + j >= data.GetSize()) {
					break;
				}
				this._rom.get(i).set(j, data.ReadUChar(offset + j));
			}
			offset = offset + (16384);
		}
		this._vrom = new Map();
		for (let i = 0; i < this._vrom_count; i += 1) {
			this._vrom.set(i, new Map());
			for (let j = 0; j < 4096; j += 1) {
				if (offset + j >= data.GetSize()) {
					break;
				}
				this._vrom.get(i).set(j, data.ReadUChar(offset + j));
			}
			offset = offset + (4096);
		}
		this._vrom_tile = new Map();
		for (let i = 0; i < this._vrom_count; i += 1) {
			this._vrom_tile.set(i, new Map());
			for (let j = 0; j < 256; j += 1) {
				this._vrom_tile.get(i).set(j, ALittle.NewObject(NESEmulator.NesTile));
			}
		}
		for (let v = 0; v < this._vrom_count; v += 1) {
			for (let i = 0; i < 4096; i += 1) {
				let tile_index = i >> 4;
				let left_over = i % 16;
				if (left_over < 8) {
					this._vrom_tile.get(v).get(tile_index).SetScanline(left_over, this._vrom.get(v).get(i), this._vrom.get(v).get(i + 8));
				} else {
					this._vrom_tile.get(v).get(tile_index).SetScanline(left_over - 8, this._vrom.get(v).get(i - 8), this._vrom.get(v).get(i));
				}
			}
		}
		this._valid = true;
		return undefined;
	},
	GetMirroringType : function() {
		if (this._four_screen) {
			return NESEmulator.NESMirroringType.FOURSCREEN_MIRRORING;
		}
		if (this._mirroring === 0) {
			return NESEmulator.NESMirroringType.HORIZONTAL_MIRRORING;
		}
		return NESEmulator.NESMirroringType.VERTICAL_MIRRORING;
	},
	GetMapperName : function() {
		let name = this._mapper_name.get(this._mapper_type);
		if (name !== undefined) {
			return name;
		}
		return "Unknow Mapper, " + this._mapper_type;
	},
	CreateMapper : function() {
		return NESEmulator.CreateNesMapper(this._nes, this._mapper_type);
	},
}, "NESEmulator.NesRom");

}