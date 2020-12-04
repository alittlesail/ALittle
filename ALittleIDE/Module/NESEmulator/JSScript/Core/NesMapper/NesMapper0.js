{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


if (NESEmulator.NesMapper === undefined) throw new Error(" extends class:NESEmulator.NesMapper is undefined");
NESEmulator.NesMapper0 = JavaScript.Class(NESEmulator.NesMapper, {
	Reset : function() {
		this._joy1_strobe_state = 0;
		this._joy2_strobe_state = 0;
		this._joypad_strobe_state = 0;
		this._zapper_fired = false;
		this._zapper_x = undefined;
		this._zapper_y = undefined;
	},
	Write : function(address, value) {
		if (address < 0x2000) {
			this._nes._cpu._mem.set(address & 0x7ff, value);
		} else {
			if (address > 0x4017) {
				this._nes._cpu._mem.set(address, value);
				if (address >= 0x6000 && address < 0x8000) {
					this._nes.OnBatteryRamWrite(address, value);
				}
			} else {
				if (address > 0x2007 && address < 0x4000) {
					this.RegWrite(0x2000 + (address & 0x7), value);
				} else {
					this.RegWrite(address, value);
				}
			}
		}
	},
	Writelow : function(address, value) {
		if (address < 0x2000) {
			this._nes._cpu._mem.set(address & 0x7ff, value);
		} else {
			if (address > 0x4017) {
				this._nes._cpu._mem.set(address, value);
			} else {
				if (address > 0x2007 && address < 0x4000) {
					this.RegWrite(0x2000 + (address & 0x7), value);
				} else {
					this.RegWrite(address, value);
				}
			}
		}
	},
	Load : function(address) {
		address = address & 0xffff;
		if (address > 0x4017) {
			return this._nes._cpu._mem.get(address);
		} else {
			if (address >= 0x2000) {
				return this.RegLoad(address);
			} else {
				return this._nes._cpu._mem.get(address & 0x7ff);
			}
		}
	},
	RegLoad : function(address) {
		let type = address >> 12;
		if (type === 0 || type === 1) {
		} else if (type === 2 || type === 3) {
			let reg = address & 0x7;
			if (reg === 0x0) {
				return this._nes._cpu._mem.get(0x2000);
			} else if (reg === 0x1) {
				return this._nes._cpu._mem.get(0x2001);
			} else if (reg === 0x2) {
				return this._nes._ppu.ReadStatusRegister();
			} else if (reg === 0x3) {
				return 0;
			} else if (reg === 0x4) {
				return this._nes._ppu.SramLoad();
			} else if (reg === 0x5) {
				return 0;
			} else if (reg === 0x6) {
				return 0;
			} else if (reg === 0x7) {
				return this._nes._ppu.VramLoad();
			}
		} else if (type === 4) {
			let reg = address - 0x4015;
			if (reg === 0) {
				return this._nes._papu.ReadReg(address);
			} else if (reg === 1) {
				return this.Joy1Read();
			} else if (reg === 2) {
				let w = 0;
				if (this._zapper_x !== undefined && this._zapper_y !== undefined && this._nes._ppu.IsPixelWhite(this._zapper_x, this._zapper_y)) {
					w = 0;
				} else {
					w = 0x1 << 3;
				}
				if (this._zapper_fired) {
					w = w | 0x1 << 4;
				}
				return (this.Joy2Read() | w) & 0xffff;
			}
		}
		return 0;
	},
	RegWrite : function(address, value) {
		if (address === 0x2000) {
			this._nes._cpu._mem.set(address, value);
			this._nes._ppu.UpdateControlReg1(value);
		} else if (address === 0x2001) {
			this._nes._cpu._mem.set(address, value);
			this._nes._ppu.UpdateControlReg2(value);
		} else if (address === 0x2003) {
			this._nes._ppu.WriteSRAMAddress(value);
		} else if (address === 0x2004) {
			this._nes._ppu.SramWrite(value);
		} else if (address === 0x2005) {
			this._nes._ppu.ScrollWrite(value);
		} else if (address === 0x2006) {
			this._nes._ppu.WriteVRAMAddress(value);
		} else if (address === 0x2007) {
			this._nes._ppu.VramWrite(value);
		} else if (address === 0x4014) {
			this._nes._ppu.SramDMA(value);
		} else if (address === 0x4015) {
			this._nes._papu.WriteReg(address, value);
		} else if (address === 0x4016) {
			if ((value & 1) === 0 && (this._joypad_strobe_state & 1) === 1) {
				this._joy1_strobe_state = 0;
				this._joy2_strobe_state = 0;
			}
			this._joypad_strobe_state = value;
		} else if (address === 0x4017) {
			this._nes._papu.WriteReg(address, value);
		} else {
			if (address >= 0x4000 && address <= 0x4017) {
				this._nes._papu.WriteReg(address, value);
			}
		}
	},
	Joy1Read : function() {
		let ret = 0;
		if (this._joy1_strobe_state >= 0 && this._joy1_strobe_state <= 7) {
			ret = this._nes._controllers.get(1)._state.get(this._joy1_strobe_state);
		} else if (this._joy1_strobe_state >= 8 && this._joy1_strobe_state <= 18) {
			ret = 0;
		} else if (this._joy1_strobe_state === 19) {
			ret = 1;
		} else {
			ret = 0;
		}
		++ this._joy1_strobe_state;
		if (this._joy1_strobe_state === 24) {
			this._joy1_strobe_state = 0;
		}
		return ret;
	},
	Joy2Read : function() {
		let ret = 0;
		if (this._joy2_strobe_state >= 0 && this._joy2_strobe_state <= 7) {
			ret = this._nes._controllers.get(2)._state.get(this._joy2_strobe_state);
		} else if (this._joy2_strobe_state >= 8 && this._joy2_strobe_state <= 18) {
			ret = 0;
		} else if (this._joy2_strobe_state === 19) {
			ret = 1;
		} else {
			ret = 0;
		}
		++ this._joy2_strobe_state;
		if (this._joy2_strobe_state === 24) {
			this._joy2_strobe_state = 0;
		}
		return ret;
	},
	LoadROM : function() {
		if (!this._nes._rom._valid || this._nes._rom._rom_count < 1) {
			return "NoMapper: Invalid ROM! Unable to load.";
		}
		this.LoadPRGROM();
		this.LoadCHRROM();
		this.LoadBatteryRam();
		this._nes._cpu.RequestIrq(NESEmulator.NesCPUIRQ.IRQ_RESET);
		return undefined;
	},
	LoadPRGROM : function() {
		if (this._nes._rom._rom_count > 1) {
			this.LoadRomBank(0, 0x8000);
			this.LoadRomBank(1, 0xc000);
		} else {
			this.LoadRomBank(0, 0x8000);
			this.LoadRomBank(0, 0xc000);
		}
	},
	LoadCHRROM : function() {
		if (this._nes._rom._vrom_count > 0) {
			if (this._nes._rom._vrom_count === 1) {
				this.LoadVromBank(0, 0x0000);
				this.LoadVromBank(0, 0x1000);
			} else {
				this.LoadVromBank(0, 0x0000);
				this.LoadVromBank(1, 0x1000);
			}
		} else {
		}
	},
	LoadBatteryRam : function() {
		if (this._nes._rom._battery_ram !== undefined) {
			let ram = this._nes._rom._battery_ram;
			if (ram !== undefined && this._nes._rom._battery_ram_len === 0x2000) {
				NESEmulator.CopyArrayElements(ram, 0, this._nes._cpu._mem, 0x6000, 0x2000);
			}
		}
	},
	LoadRomBank : function(bank, address) {
		bank = bank % (this._nes._rom._rom_count);
		NESEmulator.CopyArrayElements(this._nes._rom._rom.get(bank), 0, this._nes._cpu._mem, address, 16384);
	},
	LoadVromBank : function(bank, address) {
		if (this._nes._rom._vrom_count === 0) {
			return;
		}
		this._nes._ppu.TriggerRendering();
		NESEmulator.CopyArrayElements(this._nes._rom._vrom.get(bank % this._nes._rom._vrom_count), 0, this._nes._ppu._vram_mem, address, 4096);
		let vrom_tile = this._nes._rom._vrom_tile.get(bank % this._nes._rom._vrom_count);
		NESEmulator.CopyArrayElements(vrom_tile, 0, this._nes._ppu._pt_tile, address >> 4, 256);
	},
	Load32kRomBank : function(bank, address) {
		this.LoadRomBank((bank * 2) % this._nes._rom._rom_count, address);
		this.LoadRomBank((bank * 2 + 1) % this._nes._rom._rom_count, address + 16384);
	},
	Load8kVromBank : function(bank4kStart, address) {
		if (this._nes._rom._vrom_count === 0) {
			return;
		}
		this._nes._ppu.TriggerRendering();
		this.LoadVromBank(bank4kStart % this._nes._rom._vrom_count, address);
		this.LoadVromBank((bank4kStart + 1) % this._nes._rom._vrom_count, address + 4096);
	},
	Load1kVromBank : function(bank1k, address) {
		if (this._nes._rom._vrom_count === 0) {
			return;
		}
		this._nes._ppu.TriggerRendering();
		let bank4k = ALittle.Math_Floor(bank1k / 4) % this._nes._rom._vrom_count;
		let bankoffset = (bank1k % 4) * 1024;
		NESEmulator.CopyArrayElements(this._nes._rom._vrom.get(bank4k), bankoffset, this._nes._ppu._vram_mem, address, 1024);
		let vromTile = this._nes._rom._vrom_tile.get(bank4k);
		let baseIndex = address >> 4;
		for (let i = 0; i < 64; i += 1) {
			this._nes._ppu._pt_tile.set(baseIndex + i, vromTile.get((bank1k % 4 << 6) + i));
		}
	},
	Load2kVromBank : function(bank2k, address) {
		if (this._nes._rom._vrom_count === 0) {
			return;
		}
		this._nes._ppu.TriggerRendering();
		let bank4k = ALittle.Math_Floor(bank2k / 2) % this._nes._rom._vrom_count;
		let bankoffset = (bank2k % 2) * 2048;
		NESEmulator.CopyArrayElements(this._nes._rom._vrom.get(bank4k), bankoffset, this._nes._ppu._vram_mem, address, 2048);
		let vromTile = this._nes._rom._vrom_tile.get(bank4k);
		let baseIndex = address >> 4;
		for (let i = 0; i < 128; i += 1) {
			this._nes._ppu._pt_tile.set(baseIndex + i, vromTile.get((bank2k % 2 << 7) + i));
		}
	},
	Load8kRomBank : function(bank8k, address) {
		let bank16k = ALittle.Math_Floor(bank8k / 2) % this._nes._rom._rom_count;
		let offset = (bank8k % 2) * 8192;
		NESEmulator.CopyArrayElements(this._nes._rom._rom.get(bank16k), offset, this._nes._cpu._mem, address, 8192);
	},
}, "NESEmulator.NesMapper0");

}