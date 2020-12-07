{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


if (NESEmulator.NesMapper0 === undefined) throw new Error(" extends class:NESEmulator.NesMapper0 is undefined");
NESEmulator.NesMapper7 = JavaScript.Class(NESEmulator.NesMapper0, {
	Write : function(address, value) {
		if (address < 0x8000) {
			NESEmulator.NesMapper0.Write.call(this, address, value);
		} else {
			this.Load32kRomBank(value & 0x7, 0x8000);
			if (value & 0x10 !== 0) {
				this._nes._ppu.SetMirroring(NESEmulator.NESMirroringType.SINGLESCREEN_MIRRORING2);
			} else {
				this._nes._ppu.SetMirroring(NESEmulator.NESMirroringType.SINGLESCREEN_MIRRORING);
			}
		}
	},
	LoadROM : function() {
		if (!this._nes._rom._valid) {
			return "AOROM: Invalid ROM! Unable to load.";
		}
		this.LoadPRGROM();
		this.LoadCHRROM();
		this._nes._cpu.RequestIrq(NESEmulator.NesCPUIRQ.IRQ_RESET);
		return undefined;
	},
}, "NESEmulator.NesMapper7");

}