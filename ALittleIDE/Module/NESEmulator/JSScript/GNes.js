{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


if (NESEmulator.NesCore === undefined) throw new Error(" extends class:NESEmulator.NesCore is undefined");
NESEmulator.GNes = JavaScript.Class(NESEmulator.NesCore, {
	Ctor : function() {
		this._frame_buffer = new Map();
	},
	Setup : function(image) {
		this._image = image;
		A_UISystem.keydown_callback = this.HandleKey.bind(this, true);
		A_UISystem.keyup_callback = this.HandleKey.bind(this, false);
		ALittle.System_SetFPS(1000);
	},
	LoadROMFromOther : function(file_name) {
		return new Promise((async function(___COROUTINE, ___) {
			this.Reset();
			if (this._loop_frame !== undefined) {
				this._loop_frame.Stop();
				this._loop_frame = undefined;
			}
			if (this._loop_func !== undefined) {
				this._loop_func.Stop();
				this._loop_func = undefined;
			}
			let path = NESEmulator.g_ModuleBasePath + "Other/" + file_name;
			await NESEmulator.g_Control.HttpDownload(path);
			let nes_rom = ALittle.NewObject(ALittle.LocalFile);
			if (!nes_rom.Load(path)) {
				___COROUTINE("can't find rom:" + file_name); return;
			}
			let error = this.ReloadROM(nes_rom);
			if (error !== undefined) {
				___COROUTINE(error); return;
			}
			this._loop_frame = ALittle.NewObject(ALittle.LoopFrame, this.UpdateFrame.bind(this));
			this._loop_frame.Start();
			this._loop_func = ALittle.NewObject(ALittle.LoopFunction, this.ShowInfo.bind(this), -1, 1000, 1000);
			this._loop_func.Start();
			___COROUTINE(undefined); return;
		}).bind(this));
	},
	LoadROMFromPath : function(path) {
		return new Promise((function(___COROUTINE, ___) {
			this.Reset();
			if (this._loop_frame !== undefined) {
				this._loop_frame.Stop();
				this._loop_frame = undefined;
			}
			if (this._loop_func !== undefined) {
				this._loop_func.Stop();
				this._loop_func = undefined;
			}
			let nes_rom = ALittle.NewObject(ALittle.LocalFile);
			if (!nes_rom.Load(path)) {
				___COROUTINE("can't find rom:" + path); return;
			}
			let error = this.ReloadROM(nes_rom);
			if (error !== undefined) {
				___COROUTINE(error); return;
			}
			this._loop_frame = ALittle.NewObject(ALittle.LoopFrame, this.UpdateFrame.bind(this));
			this._loop_frame.Start();
			this._loop_func = ALittle.NewObject(ALittle.LoopFunction, this.ShowInfo.bind(this), -1, 1000, 1000);
			this._loop_func.Start();
			___COROUTINE(undefined); return;
		}).bind(this));
	},
	HandleKey : function(down, mod, sym, scancode) {
		if (sym === 97) {
			if (down) {
				this.ButtonDown(1, NESEmulator.NesControlType.BUTTON_LEFT);
			} else {
				this.ButtonUp(1, NESEmulator.NesControlType.BUTTON_LEFT);
			}
		} else if (sym === 115) {
			if (down) {
				this.ButtonDown(1, NESEmulator.NesControlType.BUTTON_DOWN);
			} else {
				this.ButtonUp(1, NESEmulator.NesControlType.BUTTON_DOWN);
			}
		} else if (sym === 100) {
			if (down) {
				this.ButtonDown(1, NESEmulator.NesControlType.BUTTON_RIGHT);
			} else {
				this.ButtonUp(1, NESEmulator.NesControlType.BUTTON_RIGHT);
			}
		} else if (sym === 119) {
			if (down) {
				this.ButtonDown(1, NESEmulator.NesControlType.BUTTON_UP);
			} else {
				this.ButtonUp(1, NESEmulator.NesControlType.BUTTON_UP);
			}
		} else if (sym === 103) {
			if (down) {
				this.ButtonDown(1, NESEmulator.NesControlType.BUTTON_SELECT);
			} else {
				this.ButtonUp(1, NESEmulator.NesControlType.BUTTON_SELECT);
			}
		} else if (sym === 104) {
			if (down) {
				this.ButtonDown(1, NESEmulator.NesControlType.BUTTON_START);
			} else {
				this.ButtonUp(1, NESEmulator.NesControlType.BUTTON_START);
			}
		} else if (sym === 107) {
			if (down) {
				this.ButtonDown(1, NESEmulator.NesControlType.BUTTON_A);
			} else {
				this.ButtonUp(1, NESEmulator.NesControlType.BUTTON_A);
			}
		} else if (sym === 106) {
			if (down) {
				this.ButtonDown(1, NESEmulator.NesControlType.BUTTON_B);
			} else {
				this.ButtonUp(1, NESEmulator.NesControlType.BUTTON_B);
			}
		}
	},
	OnFrame : function(frame_buffer) {
		let len = NESEmulator.SCREEN_WIDTH * NESEmulator.SCREEN_HEIGHT;
		for (let i = 0; i < len; i += 1) {
			this._frame_buffer.set(i, frame_buffer.get(i) | 0xFF000000);
		}
		this._image.SetRangeColor(this._frame_buffer);
	},
	ShowInfo : function() {
	},
	UpdateFrame : function(frame_time) {
		let error = this.Frame();
		if (error !== undefined) {
			ALittle.Log(error);
			if (this._loop_frame !== undefined) {
				this._loop_frame.Stop();
			}
			if (this._loop_func !== undefined) {
				this._loop_func.Stop();
			}
		}
	},
	Shutdown : function() {
		if (this._loop_frame !== undefined) {
			this._loop_frame.Stop();
		}
		this._loop_frame = undefined;
		if (this._loop_func !== undefined) {
			this._loop_func.Stop();
		}
		this._loop_func = undefined;
	},
}, "NESEmulator.GNes");

window.g_GNes = ALittle.NewObject(NESEmulator.GNes);
}