{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


if (NESEmulator.NesMapper0 === undefined) throw new Error(" extends class:NESEmulator.NesMapper0 is undefined");
NESEmulator.NesMapper11 = JavaScript.Class(NESEmulator.NesMapper0, {
	Write : function(address, value) {
		if (address < 0x8000) {
			NESEmulator.NesMapper0.Write.call(this, address, value);
			return;
		} else {
			let prgbank1 = ((value & 0xf) * 2) % this._nes._rom._rom_count;
			let prgbank2 = ((value & 0xf) * 2 + 1) % this._nes._rom._rom_count;
			this.LoadRomBank(prgbank1, 0x8000);
			this.LoadRomBank(prgbank2, 0xc000);
			if (this._nes._rom._vrom_count > 0) {
				let bank = ((value >> 4) * 2) % this._nes._rom._vrom_count;
				this.LoadVromBank(bank, 0x0000);
				this.LoadVromBank(bank + 1, 0x1000);
			}
		}
	},
}, "NESEmulator.NesMapper11");

}