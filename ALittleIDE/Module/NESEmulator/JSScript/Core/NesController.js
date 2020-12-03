{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesControlType = {
	BUTTON_A : 0,
	BUTTON_B : 1,
	BUTTON_SELECT : 2,
	BUTTON_START : 3,
	BUTTON_UP : 4,
	BUTTON_DOWN : 5,
	BUTTON_LEFT : 6,
	BUTTON_RIGHT : 7,
}

NESEmulator.NesController = JavaScript.Class(undefined, {
	Ctor : function() {
		this._state = new Map();
	},
	ButtonDown : function(key) {
		this._state.set(key, 0x41);
	},
	ButtonUp : function(key) {
		this._state.set(key, 0x40);
	},
}, "NESEmulator.NesController");

}