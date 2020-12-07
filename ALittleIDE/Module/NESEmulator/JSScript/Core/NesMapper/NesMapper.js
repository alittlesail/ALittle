{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesMapper = JavaScript.Class(undefined, {
	Ctor : function(nes) {
		this._nes = nes;
	},
	Reset : function() {
		this._zapper_fired = false;
		this._zapper_x = undefined;
		this._zapper_y = undefined;
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
	if (type === 1) {
		return ALittle.NewObject(NESEmulator.NesMapper1, nes);
	}
	if (type === 2) {
		return ALittle.NewObject(NESEmulator.NesMapper2, nes);
	}
	if (type === 3) {
		return ALittle.NewObject(NESEmulator.NesMapper3, nes);
	}
	if (type === 4) {
		return ALittle.NewObject(NESEmulator.NesMapper4, nes);
	}
	if (type === 5) {
		return ALittle.NewObject(NESEmulator.NesMapper5, nes);
	}
	if (type === 7) {
		return ALittle.NewObject(NESEmulator.NesMapper7, nes);
	}
	if (type === 11) {
		return ALittle.NewObject(NESEmulator.NesMapper11, nes);
	}
	if (type === 34) {
		return ALittle.NewObject(NESEmulator.NesMapper34, nes);
	}
	if (type === 38) {
		return ALittle.NewObject(NESEmulator.NesMapper38, nes);
	}
	if (type === 66) {
		return ALittle.NewObject(NESEmulator.NesMapper66, nes);
	}
	if (type === 74) {
		return ALittle.NewObject(NESEmulator.NesMapper4, nes);
	}
	if (type === 94) {
		return ALittle.NewObject(NESEmulator.NesMapper94, nes);
	}
	if (type === 140) {
		return ALittle.NewObject(NESEmulator.NesMapper140, nes);
	}
	if (type === 180) {
		return ALittle.NewObject(NESEmulator.NesMapper180, nes);
	}
	return undefined;
}

}