{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


if (NESEmulator.NesMapper0 === undefined) throw new Error(" extends class:NESEmulator.NesMapper0 is undefined");
NESEmulator.NesMapper2 = JavaScript.Class(NESEmulator.NesMapper0, {
	Write : function(address, value) {
		if (address < 0x8000) {
			NESEmulator.NesMapper0.Write.call(this, address, value);
			return;
		} else {
			this.LoadRomBank(value, 0x8000);
		}
	},
	LoadROM : function() {
		if (!this._nes._rom._valid) {
			return "UNROM: Invalid ROM! Unable to load.";
		}
		this.LoadRomBank(0, 0x8000);
		this.LoadRomBank(this._nes._rom._rom_count - 1, 0xc000);
		this.LoadCHRROM();
		this._nes._cpu.RequestIrq(NESEmulator.NesCPUIRQ.IRQ_RESET);
		return undefined;
	},
}, "NESEmulator.NesMapper2");

}