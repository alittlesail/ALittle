{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesCore = JavaScript.Class(undefined, {
	OnFrame : function(frame_buffer) {
	},
	OnAudioSample : function(left, right) {
	},
	OnStatusUpdate : function(content) {
	},
	Ctor : function() {
		this._sample_rate = 48000;
		this._frame_rate = 60;
		this._frame_count = 0;
		this._frame_time = 1000 / this._frame_rate;
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