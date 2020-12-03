{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesCore = JavaScript.Class(undefined, {
	OnFrame : function(frame_buffer) {
	},
	OnAudioSample : function(left, right) {
	},
	OnStatusUpdate : function(content) {
	},
	OnBatteryRamWrite : function(address, value) {
	},
	Ctor : function() {
		this._sample_rate = 48000;
		this._frame_rate = 60;
		this._frame_count = 0;
		this._sample_rate = 8000;
		this._preferred_frame_rate = 0;
		this._controllers = new Map();
		this._frame_time = 1000 / this._frame_rate;
		this._controllers.set(1, ALittle.NewObject(NESEmulator.NesController));
		this._controllers.set(2, ALittle.NewObject(NESEmulator.NesController));
	},
	Reset : function() {
		if (this._mmap !== undefined) {
			this._mmap.Reset();
		}
	},
	Stop : function() {
	},
}, "NESEmulator.NesCore");

}