{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesMapper = JavaScript.Class(undefined, {
	Ctor : function(nes) {
		this._nes = nes;
	},
	Reset : function() {
	},
	LoadROM : function() {
		return "not implement";
	},
	Load : function(address) {
		return 0;
	},
	Write : function(address, value) {
	},
	ClockIrqCounter : function() {
	},
	LatchAccess : function(address) {
	},
}, "NESEmulator.NesMapper");

NESEmulator.CreateNesMapper = function(nes, type) {
	if (type === 0) {
		return ALittle.NewObject(NESEmulator.NesMapper0, nes);
	}
	return undefined;
}

}