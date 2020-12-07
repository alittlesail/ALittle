{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


if (NESEmulator.NesMapper0 === undefined) throw new Error(" extends class:NESEmulator.NesMapper0 is undefined");
NESEmulator.NesMapper3 = JavaScript.Class(NESEmulator.NesMapper0, {
	Write : function(address, value) {
		if (address < 0x8000) {
			NESEmulator.NesMapper0.Write.call(this, address, value);
			return;
		} else {
			let bank = ALittle.Math_Floor((value % (this._nes._rom._vrom_count / 2)) * 2);
			this.LoadVromBank(bank, 0x0000);
			this.LoadVromBank(bank + 1, 0x1000);
			this.Load8kVromBank(value * 2, 0x0000);
		}
	},
}, "NESEmulator.NesMapper3");

}