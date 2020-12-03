{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesMapper = JavaScript.Class(undefined, {
	Reset : function() {
	},
	Load : function(address) {
		return 0;
	},
	Write : function(address, value) {
	},
}, "NESEmulator.NesMapper");

NESEmulator.CreateNesMapper = function(type) {
	return undefined;
}

}