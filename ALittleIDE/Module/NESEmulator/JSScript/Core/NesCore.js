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
		this._preferred_frame_rate = 60;
		this._emulate_sound = true;
		this._fps_frame_count = 0;
		this._last_fps_time = 0;
		this._controllers = new Map();
		this._frame_time = 1000 / this._preferred_frame_rate;
		this._cpu = ALittle.NewObject(NESEmulator.NesCPU, this);
		this._ppu = ALittle.NewObject(NESEmulator.NesPPU, this);
		this._papu = ALittle.NewObject(NESEmulator.NesPAPU, this);
		this._mmap = undefined;
		this._controllers.set(1, ALittle.NewObject(NESEmulator.NesController));
		this._controllers.set(2, ALittle.NewObject(NESEmulator.NesController));
		this.OnStatusUpdate("Ready to load a ROM.");
	},
	Reset : function() {
		if (this._mmap !== undefined) {
			this._mmap.Reset();
		}
		this._cpu.Reset();
		this._ppu.Reset();
		this._papu.Reset();
		this._last_fps_time = 0;
		this._fps_frame_count = 0;
		this._run_error = undefined;
	},
	Frame : function() {
}