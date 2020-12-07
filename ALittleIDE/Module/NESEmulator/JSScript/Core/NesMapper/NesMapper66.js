{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


if (NESEmulator.NesMapper0 === undefined) throw new Error(" extends class:NESEmulator.NesMapper0 is undefined");
NESEmulator.NesMapper66 = JavaScript.Class(NESEmulator.NesMapper0, {
	Write : function(address, value) {
		if (address < 0x8000) {
			NESEmulator.NesMapper0.Write.call(this, address, value);
			return;
		} else {
			this.Load32kRomBank((value >> 4) & 3, 0x8000);
			this.Load8kVromBank((value & 3) * 2, 0x0000);
		}
	},
}, "NESEmulator.NesMapper66");

}