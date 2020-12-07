{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


if (NESEmulator.NesMapper0 === undefined) throw new Error(" extends class:NESEmulator.NesMapper0 is undefined");
NESEmulator.NesMapper5 = JavaScript.Class(NESEmulator.NesMapper0, {
	Ctor : function() {
		this._nametable_type = new Map();
	},
	Write : function(address, value) {
		if (address < 0x5000) {
			NESEmulator.NesMapper0.Write.call(this, address, value);
			return;
		}
		if (address === 0x5100) {
			this._prg_size = value & 3;
		} else if (address === 0x5101) {
			this._chr_size = value & 3;
		} else if (address === 0x5102) {
			this._sram_we_a = value & 3;
		} else if (address === 0x5103) {
			this._sram_we_b = value & 3;
		} else if (address === 0x5104) {
			this._graphic_mode = value & 3;
		} else if (address === 0x5105) {
			this._nametable_mode = value;
			this._nametable_type.set(0, value & 3);
			this.Load1kVromBank(value & 3, 0x2000);
			value = value >> 2;
			this._nametable_type.set(1, value & 3);
			this.Load1kVromBank(value & 3, 0x2400);
			value = value >> 2;
			this._nametable_type.set(2, value & 3);
			this.Load1kVromBank(value & 3, 0x2800);
			value = value >> 2;
			this._nametable_type.set(3, value & 3);
			this.Load1kVromBank(value & 3, 0x2c00);
		} else if (address === 0x5106) {
			this._fill_chr = value;
		} else if (address === 0x5107) {
			this._fill_pal = value & 3;
		} else if (address === 0x5113) {
		} else if (address === 0x5114 || address === 0x5115 || address === 0x5116 || address === 0x5117) {
		} else if (address === 0x5120 || address === 0x5121 || address === 0x5122 || address === 0x5123 || address === 0x5124 || address === 0x5125 || address === 0x5126 || address === 0x5127) {
			this._chr_mode = 0;
			this._chr_page.get(0).set(address & 7, value);
		} else if (address === 0x5128 || address === 0x5129 || address === 0x512a || address === 0x512b) {
			this._chr_mode = 1;
			this._chr_page.get(1).set((address & 3) + 0, value);
			this._chr_page.get(1).set((address & 3) + 4, value);
		} else if (address === 0x5200) {
			this._split_control = value;
		} else if (address === 0x5201) {
			this._split_scroll = value;
		} else if (address === 0x5202) {
			this._split_page = value & 0x3f;
		} else if (address === 0x5203) {
			this._irq_line = value;
			this._nes._cpu.ClearIrq();
		} else if (address === 0x5204) {
			this._irq_enable = value;
			this._nes._cpu.ClearIrq();
		} else if (address === 0x5205) {
			this._mult_a = value;
		} else if (address === 0x5206) {
			this._mult_b = value;
		} else {
			if (address >= 0x5000 && address <= 0x5015) {
			} else {
				if (address >= 0x5c00 && address <= 0x5fff) {
					if (this._graphic_mode === 2) {
					} else {
						if (this._graphic_mode !== 3) {
							if (this._irq_status & 0x40 !== 0) {
							} else {
							}
						}
					}
				} else {
					if (address >= 0x6000 && address <= 0x7fff) {
						if (this._sram_we_a === 2 && this._sram_we_b === 1) {
						}
					}
				}
			}
		}
	},
	LoadROM : function() {
		if (!this._nes._rom._valid) {
			return "UNROM: Invalid ROM! Unable to load.";
		}
		this.Load8kRomBank(this._nes._rom._rom_count * 2 - 1, 0x8000);
		this.Load8kRomBank(this._nes._rom._rom_count * 2 - 1, 0xa000);
		this.Load8kRomBank(this._nes._rom._rom_count * 2 - 1, 0xc000);
		this.Load8kRomBank(this._nes._rom._rom_count * 2 - 1, 0xe000);
		this.LoadCHRROM();
		this._nes._cpu.RequestIrq(NESEmulator.NesCPUIRQ.IRQ_RESET);
		return undefined;
	},
}, "NESEmulator.NesMapper5");

}