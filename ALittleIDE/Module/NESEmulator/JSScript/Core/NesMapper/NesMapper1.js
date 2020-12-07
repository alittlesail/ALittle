{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


if (NESEmulator.NesMapper0 === undefined) throw new Error(" extends class:NESEmulator.NesMapper0 is undefined");
NESEmulator.NesMapper1 = JavaScript.Class(NESEmulator.NesMapper0, {
	Reset : function() {
		NESEmulator.NesMapper0.Reset.call(this);
		this._reg_buffer = 0;
		this._reg_buffer_counter = 0;
		this._mirroring = 0;
		this._one_screen_mirroring = 0;
		this._prg_switching_area = 1;
		this._prg_switching_size = 1;
		this._vrom_switching_size = 0;
		this._rom_selection_reg_0 = 0;
		this._rom_selection_reg_1 = 0;
		this._rom_bank_select = 0;
	},
	Write : function(address, value) {
		if (address < 0x8000) {
			NESEmulator.NesMapper0.Write.call(this, address, value);
			return;
		}
		if ((value & 128) !== 0) {
			this._reg_buffer_counter = 0;
			this._reg_buffer = 0;
			if (this.GetRegNumber(address) === 0) {
				this._prg_switching_area = 1;
				this._prg_switching_size = 1;
			}
		} else {
			this._reg_buffer = (this._reg_buffer & (0xff - (1 << this._reg_buffer_counter))) | ((value & 1) << this._reg_buffer_counter);
			++ this._reg_buffer_counter;
			if (this._reg_buffer_counter === 5) {
				this.SetReg(this.GetRegNumber(address), this._reg_buffer);
				this._reg_buffer = 0;
				this._reg_buffer_counter = 0;
			}
		}
	},
	SetReg : function(reg, value) {
		let tmp = 0;
		if (reg === 0) {
			tmp = value & 3;
			if (tmp !== this._mirroring) {
				this._mirroring = tmp;
				if ((this._mirroring & 2) === 0) {
					this._nes._ppu.SetMirroring(NESEmulator.NESMirroringType.SINGLESCREEN_MIRRORING);
				} else if ((this._mirroring & 1) !== 0) {
					this._nes._ppu.SetMirroring(NESEmulator.NESMirroringType.HORIZONTAL_MIRRORING);
				} else {
					this._nes._ppu.SetMirroring(NESEmulator.NESMirroringType.VERTICAL_MIRRORING);
				}
			}
			this._prg_switching_area = (value >> 2) & 1;
			this._prg_switching_size = (value >> 3) & 1;
			this._vrom_switching_size = (value >> 4) & 1;
		} else if (reg === 1) {
			this._rom_selection_reg_0 = (value >> 4) & 1;
			if (this._nes._rom._vrom_count > 0) {
				if (this._vrom_switching_size === 0) {
					if (this._rom_selection_reg_0 === 0) {
						this.Load8kVromBank(value & 0xf, 0x0000);
					} else {
						this.Load8kVromBank(ALittle.Math_Floor(this._nes._rom._vrom_count / 2) + (value & 0xf), 0x0000);
					}
				} else {
					if (this._rom_selection_reg_0 === 0) {
						this.LoadVromBank(value & 0xf, 0x0000);
					} else {
						this.LoadVromBank(ALittle.Math_Floor(this._nes._rom._vrom_count / 2) + (value & 0xf), 0x0000);
					}
				}
			}
		} else if (reg === 2) {
			this._rom_selection_reg_1 = (value >> 4) & 1;
			if (this._nes._rom._vrom_count > 0) {
				if (this._vrom_switching_size === 1) {
					if (this._rom_selection_reg_1 === 0) {
						this.LoadVromBank(value & 0xf, 0x1000);
					} else {
						this.LoadVromBank(ALittle.Math_Floor(this._nes._rom._vrom_count / 2) + (value & 0xf), 0x1000);
					}
				}
			}
		} else {
			tmp = value & 0xf;
			let bank = 0;
			let baseBank = 0;
			if (this._nes._rom._rom_count >= 32) {
				if (this._vrom_switching_size === 0) {
					if (this._rom_selection_reg_0 === 1) {
						baseBank = 16;
					}
				} else {
					baseBank = (this._rom_selection_reg_0 | (this._rom_selection_reg_1 << 1)) << 3;
				}
			} else {
				if (this._nes._rom._rom_count >= 16) {
					if (this._rom_selection_reg_0 === 1) {
						baseBank = 8;
					}
				}
			}
			if (this._prg_switching_size === 0) {
				bank = baseBank + (value & 0xf);
				this.Load32kRomBank(bank, 0x8000);
			} else {
				bank = baseBank * 2 + (value & 0xf);
				if (this._prg_switching_area === 0) {
					this.LoadRomBank(bank, 0xc000);
				} else {
					this.LoadRomBank(bank, 0x8000);
				}
			}
		}
	},
	GetRegNumber : function(address) {
		if (address >= 0x8000 && address <= 0x9fff) {
			return 0;
		} else {
			if (address >= 0xa000 && address <= 0xbfff) {
				return 1;
			} else {
				if (address >= 0xc000 && address <= 0xdfff) {
					return 2;
				} else {
					return 3;
				}
			}
		}
	},
	LoadROM : function() {
		if (!this._nes._rom._valid) {
			return "MMC1: Invalid ROM! Unable to load.";
		}
		this.LoadRomBank(0, 0x8000);
		this.LoadRomBank(this._nes._rom._rom_count - 1, 0xc000);
		this.LoadCHRROM();
		this.LoadBatteryRam();
		this._nes._cpu.RequestIrq(NESEmulator.NesCPUIRQ.IRQ_RESET);
		return undefined;
	},
	switchLowHighPrgRom : function(old_setting) {
	},
	Switch16to32 : function() {
	},
	Switch32to16 : function() {
	},
}, "NESEmulator.NesMapper1");

}