{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


if (NESEmulator.NesMapper === undefined) throw new Error(" extends class:NESEmulator.NesMapper is undefined");
NESEmulator.NesMapper0 = JavaScript.Class(NESEmulator.NesMapper, {
	Reset : function() {
		this._joy1_strobe_state = 0;
		this._joy2_strobe_state = 0;
		this._joypad_strobe_state = 0;
		this._zapper_fired = false;
		this._zapper_x = undefined;
		this._zapper_y = undefined;
	},
	Write : function(address, value) {
}