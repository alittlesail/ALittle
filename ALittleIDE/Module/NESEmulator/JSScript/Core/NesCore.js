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
		this._emulate_sound = false;
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
		if (this._run_error !== undefined) {
			return this._run_error;
		}
		this._ppu.StartFrame();
		let cycles = 0;
		let emulate_sound = this._emulate_sound;
		let cpu = this._cpu;
		let ppu = this._ppu;
		let papu = this._papu;
		let run = true;
		while (run) {
			if (cpu._cycles_to_halt === 0) {
				cycles = cpu.Emulate();
				if (emulate_sound) {
					papu.ClockFrameCounter(cycles);
				}
				cycles = cycles * (3);
			} else {
				if (cpu._cycles_to_halt > 8) {
					cycles = 24;
					if (emulate_sound) {
						papu.ClockFrameCounter(8);
					}
					cpu._cycles_to_halt = cpu._cycles_to_halt - (8);
				} else {
					cycles = cpu._cycles_to_halt * 3;
					if (emulate_sound) {
						papu.ClockFrameCounter(cpu._cycles_to_halt);
					}
					cpu._cycles_to_halt = 0;
				}
			}
			while (cycles > 0) {
				if (ppu._cur_x === ppu._spr_0_hit_x && ppu._f_sp_visibility === 1 && ppu._scanline - 21 === ppu._spr_0_hit_y) {
					ppu.SetStatusFlag(NESEmulator.NesPPUStatus.STATUS_SPRITE0HIT, true);
				}
				if (ppu._request_end_frame) {
					-- ppu._nmi_counter;
					if (ppu._nmi_counter === 0) {
						ppu._request_end_frame = false;
						ppu.StartVBlank();
						run = false;
						break;
					}
				}
				++ ppu._cur_x;
				if (ppu._cur_x === 341) {
					ppu._cur_x = 0;
					ppu.EndScanline();
				}
				-- cycles;
			}
		}
		++ this._fps_frame_count;
		return this._run_error;
	},
	ButtonDown : function(controller, button) {
		this._controllers.get(controller).ButtonDown(button);
	},
	ButtonUp : function(controller, button) {
		this._controllers.get(controller).ButtonUp(button);
	},
	ZapperMove : function(x, y) {
		if (this._mmap === undefined) {
			return;
		}
		this._mmap._zapper_x = x;
		this._mmap._zapper_y = x;
	},
	ZapperFireUp : function() {
		if (this._mmap === undefined) {
			return;
		}
		this._mmap._zapper_fired = false;
	},
	ZapperFireDown : function() {
		if (this._mmap === undefined) {
			return;
		}
		this._mmap._zapper_fired = true;
	},
	GetFPS : function() {
		let now = ALittle.System_GetCurMSTime();
		let fps = 0.0;
		if (this._last_fps_time !== 0) {
			fps = this._fps_frame_count / ((now - this._last_fps_time) / 1000);
		}
		this._fps_frame_count = 0;
		this._last_fps_time = now;
		return fps;
	},
	ReloadROM : function(data) {
		let rom = ALittle.NewObject(NESEmulator.NesRom, this);
		let error = rom.Load(data, undefined);
		if (error !== undefined) {
			return error;
		}
		let mapper = rom.CreateMapper();
		if (mapper === undefined) {
			return "not support mapper type:" + rom._mapper_type;
		}
		this._rom = rom;
		this._rom_data = data;
		this.Reset();
		error = mapper.LoadROM();
		if (error !== undefined) {
			return error;
		}
		this._mmap = mapper;
		this._ppu.SetMirroring(this._rom.GetMirroringType());
		return undefined;
	},
	SetFramerate : function(rate) {
		this._preferred_frame_rate = rate;
		this._frame_time = 1000 / rate;
	},
	Stop : function(error) {
		this._run_error = error;
	},
}, "NESEmulator.NesCore");

}