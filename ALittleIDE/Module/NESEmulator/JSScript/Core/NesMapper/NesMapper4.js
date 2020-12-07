{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


if (NESEmulator.NesMapper0 === undefined) throw new Error(" extends class:NESEmulator.NesMapper0 is undefined");
NESEmulator.NesMapper4 = JavaScript.Class(NESEmulator.NesMapper0, {
	Ctor : function(nes) {
		this.CMD_SEL_2_1K_VROM_0000 = 0;
		this.CMD_SEL_2_1K_VROM_0800 = 1;
		this.CMD_SEL_1K_VROM_1000 = 2;
		this.CMD_SEL_1K_VROM_1400 = 3;
		this.CMD_SEL_1K_VROM_1800 = 4;
		this.CMD_SEL_1K_VROM_1C00 = 5;
		this.CMD_SEL_ROM_PAGE1 = 6;
		this.CMD_SEL_ROM_PAGE2 = 7;
		this._command = undefined;
		this._prg_address_select = undefined;
		this._chr_address_select = undefined;
		this._page_number = undefined;
		this._irq_counter = undefined;
		this._irq_latch_value = undefined;
		this._irq_enable = undefined;
		this._prg_address_changed = false;
	},
	Write : function(address, value) {
		if (address < 0x8000) {
			NESEmulator.NesMapper0.Write.call(this, address, value);
			return;
		}
		if (address === 0x8000) {
			this._command = value & 7;
			let tmp = (value >> 6) & 1;
			if (tmp !== this._prg_address_select) {
				this._prg_address_changed = true;
			}
			this._prg_address_select = tmp;
			this._chr_address_select = (value >> 7) & 1;
		} else if (address === 0x8001) {
			this.ExecuteCommand(this._command, value);
		} else if (address === 0xa000) {
			if ((value & 1) !== 0) {
				this._nes._ppu.SetMirroring(NESEmulator.NESMirroringType.HORIZONTAL_MIRRORING);
			} else {
				this._nes._ppu.SetMirroring(NESEmulator.NESMirroringType.VERTICAL_MIRRORING);
			}
		} else if (address === 0xa001) {
		} else if (address === 0xc000) {
			this._irq_counter = value;
		} else if (address === 0xc001) {
			this._irq_latch_value = value;
		} else if (address === 0xe000) {
			this._irq_enable = 0;
		} else if (address === 0xe001) {
			this._irq_enable = 1;
		} else {
		}
	},
	ExecuteCommand : function(cmd, arg) {
		if (cmd === this.CMD_SEL_2_1K_VROM_0000) {
			if (this._chr_address_select === 0) {
				this.Load1kVromBank(arg, 0x0000);
				this.Load1kVromBank(arg + 1, 0x0400);
			} else {
				this.Load1kVromBank(arg, 0x1000);
				this.Load1kVromBank(arg + 1, 0x1400);
			}
		} else if (cmd === this.CMD_SEL_2_1K_VROM_0800) {
			if (this._chr_address_select === 0) {
				this.Load1kVromBank(arg, 0x0800);
				this.Load1kVromBank(arg + 1, 0x0c00);
			} else {
				this.Load1kVromBank(arg, 0x1800);
				this.Load1kVromBank(arg + 1, 0x1c00);
			}
		} else if (cmd === this.CMD_SEL_1K_VROM_1000) {
			if (this._chr_address_select === 0) {
				this.Load1kVromBank(arg, 0x1000);
			} else {
				this.Load1kVromBank(arg, 0x0000);
			}
		} else if (cmd === this.CMD_SEL_1K_VROM_1400) {
			if (this._chr_address_select === 0) {
				this.Load1kVromBank(arg, 0x1400);
			} else {
				this.Load1kVromBank(arg, 0x0400);
			}
		} else if (cmd === this.CMD_SEL_1K_VROM_1800) {
			if (this._chr_address_select === 0) {
				this.Load1kVromBank(arg, 0x1800);
			} else {
				this.Load1kVromBank(arg, 0x0800);
			}
		} else if (cmd === this.CMD_SEL_1K_VROM_1C00) {
			if (this._chr_address_select === 0) {
				this.Load1kVromBank(arg, 0x1c00);
			} else {
				this.Load1kVromBank(arg, 0x0c00);
			}
		} else if (cmd === this.CMD_SEL_ROM_PAGE1) {
			if (this._prg_address_changed) {
				if (this._prg_address_select === 0) {
					this.Load8kRomBank((this._nes._rom._rom_count - 1) * 2, 0xc000);
				} else {
					this.Load8kRomBank((this._nes._rom._rom_count - 1) * 2, 0x8000);
				}
				this._prg_address_changed = false;
			}
			if (this._prg_address_select === 0) {
				this.Load8kRomBank(arg, 0x8000);
			} else {
				this.Load8kRomBank(arg, 0xc000);
			}
		} else if (cmd === this.CMD_SEL_ROM_PAGE2) {
			this.Load8kRomBank(arg, 0xa000);
			if (this._prg_address_changed) {
				if (this._prg_address_select === 0) {
					this.Load8kRomBank((this._nes._rom._rom_count - 1) * 2, 0xc000);
				} else {
					this.Load8kRomBank((this._nes._rom._rom_count - 1) * 2, 0x8000);
				}
				this._prg_address_changed = false;
			}
		}
	},
	LoadROM : function() {
		if (!this._nes._rom._valid) {
			return "MMC3: Invalid ROM! Unable to load.";
		}
		this.Load8kRomBank((this._nes._rom._rom_count - 1) * 2, 0xc000);
		this.Load8kRomBank((this._nes._rom._rom_count - 1) * 2 + 1, 0xe000);
		this.Load8kRomBank(0, 0x8000);
		this.Load8kRomBank(1, 0xa000);
		this.LoadCHRROM();
		this.LoadBatteryRam();
		this._nes._cpu.RequestIrq(NESEmulator.NesCPUIRQ.IRQ_RESET);
		return undefined;
	},
	ClockIrqCounter : function() {
		if (this._irq_enable === 1) {
			-- this._irq_counter;
			if (this._irq_counter < 0) {
				this._nes._cpu.RequestIrq(NESEmulator.NesCPUIRQ.IRQ_NORMAL);
				this._irq_counter = this._irq_latch_value;
			}
		}
	},
}, "NESEmulator.NesMapper4");

}