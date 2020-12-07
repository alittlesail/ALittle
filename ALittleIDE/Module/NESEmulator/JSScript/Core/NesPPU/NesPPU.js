{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesPPUStatus = {
	STATUS_VRAMWRITE : 4,
	STATUS_SLSPRITECOUNT : 5,
	STATUS_SPRITE0HIT : 6,
	STATUS_VBLANK : 7,
}

NESEmulator.SCREEN_WIDTH = 256;
NESEmulator.SCREEN_HEIGHT = 240;
NESEmulator.PIXEL_COUNT = NESEmulator.SCREEN_WIDTH * NESEmulator.SCREEN_HEIGHT;
NESEmulator.NesPPU = JavaScript.Class(undefined, {
	Ctor : function(nes) {
		this._nes = nes;
	},
	Reset : function() {
		this._vram_mem = new Map();
		for (let i = 0; i < 0x8000; i += 1) {
			this._vram_mem.set(i, 0);
		}
		this._sprite_mem = new Map();
		for (let i = 0; i < 0x100; i += 1) {
			this._sprite_mem.set(i, 0);
		}
		this._vram_address = undefined;
		this._vram_tmp_address = undefined;
		this._vram_buffered_read_value = 0;
		this._first_write = true;
		this._sram_address = 0;
		this._current_mirroring = -1;
		this._request_end_frame = false;
		this._nmi_ok = false;
		this._dummy_cycle_toggle = false;
		this._valid_tile_data = false;
		this._nmi_counter = 0;
		this._scanline_already_rendered = undefined;
		this._f_nmi_on_vblank = 0;
		this._f_sprite_size = 0;
		this._f_bg_pattern_table = 0;
		this._f_sp_pattern_table = 0;
		this._f_addr_inc = 0;
		this._f_ntbl_address = 0;
		this._f_color = 0;
		this._f_sp_visibility = 0;
		this._f_bg_visibility = 0;
		this._f_sp_clipping = 0;
		this._f_bg_clipping = 0;
		this._f_disp_type = 0;
		this._cnt_fv = 0;
		this._cnt_v = 0;
		this._cnt_h = 0;
		this._cnt_vt = 0;
		this._cnt_ht = 0;
		this._reg_fv = 0;
		this._reg_v = 0;
		this._reg_h = 0;
		this._reg_vt = 0;
		this._reg_ht = 0;
		this._reg_fh = 0;
		this._reg_s = 0;
		this._cur_nt = undefined;
		this._attrib = new Map();
		this._buffer = new Map();
		this._bgbuffer = new Map();
		this._pixrendered = new Map();
		this._valid_tile_data = undefined;
		this._scantile = new Map();
		this._scanline = 0;
		this._last_rendered_scanline = -1;
		this._cur_x = 0;
		this._spr_x = new Map();
		for (let i = 0; i < 64; i += 1) {
			this._spr_x.set(i, 0);
		}
		this._spr_y = new Map();
		for (let i = 0; i < 64; i += 1) {
			this._spr_y.set(i, 0);
		}
		this._spr_tile = new Map();
		for (let i = 0; i < 64; i += 1) {
			this._spr_tile.set(i, 0);
		}
		this._spr_col = new Map();
		for (let i = 0; i < 64; i += 1) {
			this._spr_col.set(i, 0);
		}
		this._vert_flip = new Map();
		for (let i = 0; i < 64; i += 1) {
			this._vert_flip.set(i, false);
		}
		this._hori_flip = new Map();
		for (let i = 0; i < 64; i += 1) {
			this._hori_flip.set(i, false);
		}
		this._bg_priority = new Map();
		for (let i = 0; i < 64; i += 1) {
			this._bg_priority.set(i, false);
		}
		this._spr_0_hit_x = 0;
		this._spr_0_hit_y = 0;
		this._hit_spr_0 = false;
		this._spr_palette = new Map();
		this._img_palette = new Map();
		this._pt_tile = new Map();
		for (let i = 0; i < 512; i += 1) {
			this._pt_tile.set(i, ALittle.NewObject(NESEmulator.NesTile));
		}
		this._ntable_1 = new Map();
		this._current_mirroring = -1;
		this._name_table = new Map();
		for (let i = 0; i < 4; i += 1) {
			this._name_table.set(i, ALittle.NewObject(NESEmulator.NesNameTable, 32, 32, "Nt" + i));
		}
		this._vram_mirror_table = new Map();
		for (let i = 0; i < 0x8000; i += 1) {
			this._vram_mirror_table.set(i, i);
		}
		this._pal_table = ALittle.NewObject(NESEmulator.NesPaletteTable);
		this._pal_table.LoadNTSCPalette();
		this.UpdateControlReg1(0);
		this.UpdateControlReg2(0);
	},
	SetMirroring : function(mirroring) {
		if (mirroring === this._current_mirroring) {
			return;
		}
		this._current_mirroring = mirroring;
		this.TriggerRendering();
		if (this._vram_mirror_table === undefined) {
			this._vram_mirror_table = new Map();
		}
		for (let i = 0; i < 0x8000; i += 1) {
			this._vram_mirror_table.set(i, i);
		}
		this.DefineMirrorRegion(0x3f20, 0x3f00, 0x20);
		this.DefineMirrorRegion(0x3f40, 0x3f00, 0x20);
		this.DefineMirrorRegion(0x3f80, 0x3f00, 0x20);
		this.DefineMirrorRegion(0x3fc0, 0x3f00, 0x20);
		this.DefineMirrorRegion(0x3000, 0x2000, 0xf00);
		this.DefineMirrorRegion(0x4000, 0x0000, 0x4000);
		if (mirroring === NESEmulator.NESMirroringType.HORIZONTAL_MIRRORING) {
			this._ntable_1.set(0, 0);
			this._ntable_1.set(1, 0);
			this._ntable_1.set(2, 1);
			this._ntable_1.set(3, 1);
			this.DefineMirrorRegion(0x2400, 0x2000, 0x400);
			this.DefineMirrorRegion(0x2c00, 0x2800, 0x400);
		} else {
			if (mirroring === NESEmulator.NESMirroringType.VERTICAL_MIRRORING) {
				this._ntable_1.set(0, 0);
				this._ntable_1.set(1, 1);
				this._ntable_1.set(2, 0);
				this._ntable_1.set(3, 1);
				this.DefineMirrorRegion(0x2800, 0x2000, 0x400);
				this.DefineMirrorRegion(0x2c00, 0x2400, 0x400);
			} else {
				if (mirroring === NESEmulator.NESMirroringType.SINGLESCREEN_MIRRORING) {
					this._ntable_1.set(0, 0);
					this._ntable_1.set(1, 0);
					this._ntable_1.set(2, 0);
					this._ntable_1.set(3, 0);
					this.DefineMirrorRegion(0x2400, 0x2000, 0x400);
					this.DefineMirrorRegion(0x2800, 0x2000, 0x400);
					this.DefineMirrorRegion(0x2c00, 0x2000, 0x400);
				} else {
					if (mirroring === NESEmulator.NESMirroringType.SINGLESCREEN_MIRRORING2) {
						this._ntable_1.set(0, 1);
						this._ntable_1.set(1, 1);
						this._ntable_1.set(2, 1);
						this._ntable_1.set(3, 1);
						this.DefineMirrorRegion(0x2400, 0x2400, 0x400);
						this.DefineMirrorRegion(0x2800, 0x2400, 0x400);
						this.DefineMirrorRegion(0x2c00, 0x2400, 0x400);
					} else {
						this._ntable_1.set(0, 0);
						this._ntable_1.set(1, 1);
						this._ntable_1.set(2, 2);
						this._ntable_1.set(3, 3);
					}
				}
			}
		}
	},
	DefineMirrorRegion : function(fromStart, toStart, size) {
		for (let i = 0; i < size; i += 1) {
			this._vram_mirror_table.set(fromStart + i, toStart + i);
		}
	},
	StartVBlank : function() {
		this._nes._cpu.RequestIrq(NESEmulator.NesCPUIRQ.IRQ_NMI);
		if (this._last_rendered_scanline < 239) {
			this.RenderFramePartially(this._last_rendered_scanline + 1, 240 - this._last_rendered_scanline);
		}
		this.EndFrame();
		this._last_rendered_scanline = -1;
	},
	EndScanline : function() {
		if (this._scanline === 19) {
			if (this._dummy_cycle_toggle) {
				this._cur_x = 1;
				this._dummy_cycle_toggle = !this._dummy_cycle_toggle;
			}
		} else if (this._scanline === 20) {
			this.SetStatusFlag(NESEmulator.NesPPUStatus.STATUS_VBLANK, false);
			this.SetStatusFlag(NESEmulator.NesPPUStatus.STATUS_SPRITE0HIT, false);
			this._hit_spr_0 = false;
			this._spr_0_hit_x = -1;
			this._spr_0_hit_y = -1;
			if (this._f_bg_visibility === 1 || this._f_sp_visibility === 1) {
				this._cnt_fv = this._reg_fv;
				this._cnt_v = this._reg_v;
				this._cnt_h = this._reg_h;
				this._cnt_vt = this._reg_vt;
				this._cnt_ht = this._reg_ht;
				if (this._f_bg_visibility === 1) {
					this.RenderBgScanline(false, 0);
				}
			}
			if (this._f_bg_visibility === 1 && this._f_sp_visibility === 1) {
				this.CheckSprite0(0);
			}
			if (this._f_bg_visibility === 1 || this._f_sp_visibility === 1) {
				this._nes._mmap.ClockIrqCounter();
			}
		} else if (this._scanline === 261) {
			this.SetStatusFlag(NESEmulator.NesPPUStatus.STATUS_VBLANK, true);
			this._request_end_frame = true;
			this._nmi_counter = 9;
			this._scanline = -1;
		} else {
			if (this._scanline >= 21 && this._scanline <= 260) {
				if (this._f_bg_visibility === 1) {
					if (!this._scanline_already_rendered) {
						this._cnt_ht = this._reg_ht;
						this._cnt_h = this._reg_h;
						this.RenderBgScanline(true, this._scanline + 1 - 21);
					}
					this._scanline_already_rendered = false;
					if (!this._hit_spr_0 && this._f_sp_visibility === 1) {
						if (this._spr_x.get(0) >= -7 && this._spr_x.get(0) < 256 && this._spr_y.get(0) + 1 <= this._scanline - 20 && this._spr_y.get(0) + 1 + NESEmulator.ConditionExpr(this._f_sprite_size === 0, 8, 16) >= this._scanline - 20) {
							if (this.CheckSprite0(this._scanline - 20)) {
								this._hit_spr_0 = true;
							}
						}
					}
				}
				if (this._f_bg_visibility === 1 || this._f_sp_visibility === 1) {
					this._nes._mmap.ClockIrqCounter();
				}
			}
		}
		++ this._scanline;
		this.RegsToAddress();
		this.CntsToAddress();
	},
	StartFrame : function() {
		let bgColor = 0;
		if (this._f_disp_type === 0) {
			bgColor = this._img_palette.get(0);
		} else {
			if (this._f_color === 0) {
				bgColor = 0x00000;
			} else if (this._f_color === 1) {
				bgColor = 0x00ff00;
			} else if (this._f_color === 2) {
				bgColor = 0xff0000;
			} else if (this._f_color === 3) {
				bgColor = 0x000000;
			} else if (this._f_color === 4) {
				bgColor = 0x0000ff;
			} else {
				bgColor = 0x0;
			}
		}
		let buffer = this._buffer;
		let pixrendered = this._pixrendered;
		for (let i = 0; i < NESEmulator.PIXEL_COUNT; i += 1) {
			buffer.set(i, bgColor);
			pixrendered.set(i, 65);
		}
	},
	EndFrame : function() {
		let buffer = this._buffer;
		if (this._show_spr_0_hit) {
			if (this._spr_x.get(0) >= 0 && this._spr_x.get(0) < 256 && this._spr_y.get(0) >= 0 && this._spr_y.get(0) < 240) {
				for (let i = 0; i < 256; i += 1) {
					buffer.set((this._spr_y.get(0) << 8) + i, 0xff5555);
				}
				for (let i = 0; i < 240; i += 1) {
					buffer.set((i << 8) + this._spr_x.get(0), 0xff5555);
				}
			}
			if (this._spr_0_hit_x >= 0 && this._spr_0_hit_x < 256 && this._spr_0_hit_y >= 0 && this._spr_0_hit_y < 240) {
				for (let i = 0; i < 256; i += 1) {
					buffer.set((this._spr_0_hit_y << 8) + i, 0x55ff55);
				}
				for (let i = 0; i < 240; i += 1) {
					buffer.set((i << 8) + this._spr_0_hit_x, 0x55ff55);
				}
			}
		}
		if (this._clip_to_tv_size || this._f_bg_clipping === 0 || this._f_sp_clipping === 0) {
			for (let y = 0; y < 240; y += 1) {
				for (let x = 0; x < 8; x += 1) {
					buffer.set((y << 8) + x, 0);
				}
			}
		}
		if (this._clip_to_tv_size) {
			for (let y = 0; y < 240; y += 1) {
				for (let x = 0; x < 8; x += 1) {
					buffer.set((y << 8) + 255 - x, 0);
				}
			}
		}
		if (this._clip_to_tv_size) {
			for (let y = 0; y < 8; y += 1) {
				for (let x = 0; x < 256; x += 1) {
					buffer.set((y << 8) + x, 0);
					buffer.set(((239 - y) << 8) + x, 0);
				}
			}
		}
		this._nes.OnFrame(buffer);
	},
	UpdateControlReg1 : function(value) {
		this.TriggerRendering();
		this._f_nmi_on_vblank = (value >> 7) & 1;
		this._f_sprite_size = (value >> 5) & 1;
		this._f_bg_pattern_table = (value >> 4) & 1;
		this._f_sp_pattern_table = (value >> 3) & 1;
		this._f_addr_inc = (value >> 2) & 1;
		this._f_ntbl_address = value & 3;
		this._reg_v = (value >> 1) & 1;
		this._reg_h = value & 1;
		this._reg_s = (value >> 4) & 1;
	},
	UpdateControlReg2 : function(value) {
		this.TriggerRendering();
		this._f_color = (value >> 5) & 7;
		this._f_sp_visibility = (value >> 4) & 1;
		this._f_bg_visibility = (value >> 3) & 1;
		this._f_sp_clipping = (value >> 2) & 1;
		this._f_bg_clipping = (value >> 1) & 1;
		this._f_disp_type = value & 1;
		if (this._f_disp_type === 0) {
			this._pal_table.SetEmphasis(this._f_color);
		}
		this.UpdatePalettes();
	},
	SetStatusFlag : function(flag, value) {
		let n = 1 << flag;
		this._nes._cpu._mem.set(0x2002, (this._nes._cpu._mem.get(0x2002) & (255 - n)) | NESEmulator.ConditionExpr(value, n, 0));
	},
	ReadStatusRegister : function() {
		let tmp = this._nes._cpu._mem.get(0x2002);
		this._first_write = true;
		this.SetStatusFlag(NESEmulator.NesPPUStatus.STATUS_VBLANK, false);
		return tmp;
	},
	WriteSRAMAddress : function(address) {
		this._sram_address = address;
	},
	SramLoad : function() {
		return this._sprite_mem.get(this._sram_address);
	},
	SramWrite : function(value) {
		this._sprite_mem.set(this._sram_address, value);
		this.SpriteRamWriteUpdate(this._sram_address, value);
		++ this._sram_address;
		this._sram_address = this._sram_address % (0x100);
	},
	ScrollWrite : function(value) {
		this.TriggerRendering();
		if (this._first_write) {
			this._reg_ht = (value >> 3) & 31;
			this._reg_fh = value & 7;
		} else {
			this._reg_fv = value & 7;
			this._reg_vt = (value >> 3) & 31;
		}
		this._first_write = !this._first_write;
	},
	WriteVRAMAddress : function(address) {
		if (this._first_write) {
			this._reg_fv = (address >> 4) & 3;
			this._reg_v = (address >> 3) & 1;
			this._reg_h = (address >> 2) & 1;
			this._reg_vt = (this._reg_vt & 7) | ((address & 3) << 3);
		} else {
			this.TriggerRendering();
			this._reg_vt = (this._reg_vt & 24) | ((address >> 5) & 7);
			this._reg_ht = address & 31;
			this._cnt_fv = this._reg_fv;
			this._cnt_v = this._reg_v;
			this._cnt_h = this._reg_h;
			this._cnt_vt = this._reg_vt;
			this._cnt_ht = this._reg_ht;
			this.CheckSprite0(this._scanline - 20);
		}
		this._first_write = !this._first_write;
		this.CntsToAddress();
		if (this._vram_address < 0x2000) {
			this._nes._mmap.LatchAccess(this._vram_address);
		}
	},
	VramLoad : function() {
		let tmp = 0;
		this.CntsToAddress();
		this.RegsToAddress();
		if (this._vram_address <= 0x3eff) {
			tmp = this._vram_buffered_read_value;
			if (this._vram_address < 0x2000) {
				this._vram_buffered_read_value = this._vram_mem.get(this._vram_address);
			} else {
				this._vram_buffered_read_value = this.MirroredLoad(this._vram_address);
			}
			if (this._vram_address < 0x2000) {
				this._nes._mmap.LatchAccess(this._vram_address);
			}
			this._vram_address = this._vram_address + (NESEmulator.ConditionExpr(this._f_addr_inc === 1, 32, 1));
			this.CntsFromAddress();
			this.RegsFromAddress();
			return tmp;
		}
		tmp = this.MirroredLoad(this._vram_address);
		this._vram_address = this._vram_address + (NESEmulator.ConditionExpr(this._f_addr_inc === 1, 32, 1));
		this.CntsFromAddress();
		this.RegsFromAddress();
		return tmp;
	},
	VramWrite : function(value) {
		this.TriggerRendering();
		this.CntsToAddress();
		this.RegsToAddress();
		if (this._vram_address >= 0x2000) {
			this.MirroredWrite(this._vram_address, value);
		} else {
			this.WriteMem(this._vram_address, value);
			this._nes._mmap.LatchAccess(this._vram_address);
		}
		if (this._f_addr_inc === 1) {
			this._vram_address = this._vram_address + (32);
		} else {
			this._vram_address = this._vram_address + (1);
		}
		this.RegsFromAddress();
		this.CntsFromAddress();
	},
	SramDMA : function(value) {
		let baseAddress = value * 0x100;
		let data = 0;
		for (let i = this._sram_address; i < 256; i += 1) {
			data = this._nes._cpu._mem.get(baseAddress + i);
			this._sprite_mem.set(i, data);
			this.SpriteRamWriteUpdate(i, data);
		}
		this._nes._cpu.HaltCycles(513);
	},
	RegsFromAddress : function() {
		let address = (this._vram_tmp_address >> 8) & 0xff;
		this._reg_fv = (address >> 4) & 7;
		this._reg_v = (address >> 3) & 1;
		this._reg_h = (address >> 2) & 1;
		this._reg_vt = (this._reg_vt & 7) | ((address & 3) << 3);
		address = this._vram_tmp_address & 0xff;
		this._reg_vt = (this._reg_vt & 24) | ((address >> 5) & 7);
		this._reg_ht = address & 31;
	},
	CntsFromAddress : function() {
		let address = (this._vram_address >> 8) & 0xff;
		this._cnt_fv = (address >> 4) & 3;
		this._cnt_v = (address >> 3) & 1;
		this._cnt_h = (address >> 2) & 1;
		this._cnt_vt = (this._cnt_vt & 7) | ((address & 3) << 3);
		address = this._vram_address & 0xff;
		this._cnt_vt = (this._cnt_vt & 24) | ((address >> 5) & 7);
		this._cnt_ht = address & 31;
	},
	RegsToAddress : function() {
		let b1 = (this._reg_fv & 7) << 4;
		b1 = b1 | (this._reg_v & 1) << 3;
		b1 = b1 | (this._reg_h & 1) << 2;
		b1 = b1 | (this._reg_vt >> 3) & 3;
		let b2 = (this._reg_vt & 7) << 5;
		b2 = b2 | this._reg_ht & 31;
		this._vram_tmp_address = ((b1 << 8) | b2) & 0x7fff;
	},
	CntsToAddress : function() {
		let b1 = (this._cnt_fv & 7) << 4;
		b1 = b1 | (this._cnt_v & 1) << 3;
		b1 = b1 | (this._cnt_h & 1) << 2;
		b1 = b1 | (this._cnt_vt >> 3) & 3;
		let b2 = (this._cnt_vt & 7) << 5;
		b2 = b2 | this._cnt_ht & 31;
		this._vram_address = ((b1 << 8) | b2) & 0x7fff;
	},
	IncTileCounter : function(count) {
		for (let i = count; i !== 0; i += -1) {
			++ this._cnt_ht;
			if (this._cnt_ht === 32) {
				this._cnt_ht = 0;
				++ this._cnt_vt;
				if (this._cnt_vt >= 30) {
					++ this._cnt_h;
					if (this._cnt_h === 2) {
						this._cnt_h = 0;
						++ this._cnt_v;
						if (this._cnt_v === 2) {
							this._cnt_v = 0;
							++ this._cnt_fv;
							this._cnt_fv = this._cnt_fv & 0x7;
						}
					}
				}
			}
		}
	},
	MirroredLoad : function(address) {
		return this._vram_mem.get(this._vram_mirror_table.get(address));
	},
	MirroredWrite : function(address, value) {
		if (address >= 0x3f00 && address < 0x3f20) {
			if (address === 0x3f00 || address === 0x3f10) {
				this.WriteMem(0x3f00, value);
				this.WriteMem(0x3f10, value);
			} else {
				if (address === 0x3f04 || address === 0x3f14) {
					this.WriteMem(0x3f04, value);
					this.WriteMem(0x3f14, value);
				} else {
					if (address === 0x3f08 || address === 0x3f18) {
						this.WriteMem(0x3f08, value);
						this.WriteMem(0x3f18, value);
					} else {
						if (address === 0x3f0c || address === 0x3f1c) {
							this.WriteMem(0x3f0c, value);
							this.WriteMem(0x3f1c, value);
						} else {
							this.WriteMem(address, value);
						}
					}
				}
			}
		} else {
			if (address < 0x8000) {
				this.WriteMem(this._vram_mirror_table.get(address), value);
			} else {
				ALittle.Log("Invalid VRAM address: " + address);
			}
		}
	},
	TriggerRendering : function() {
		if (this._scanline >= 21 && this._scanline <= 260) {
			this.RenderFramePartially(this._last_rendered_scanline + 1, this._scanline - 21 - this._last_rendered_scanline);
			this._last_rendered_scanline = this._scanline - 21;
		}
	},
	RenderFramePartially : function(startScan, scanCount) {
		if (this._f_sp_visibility === 1) {
			this.RenderSpritesPartially(startScan, scanCount, true);
		}
		if (this._f_bg_visibility === 1) {
			let si = startScan << 8;
			let ei = (startScan + scanCount) << 8;
			if (ei > 0xf000) {
				ei = 0xf000;
			}
			let buffer = this._buffer;
			let bgbuffer = this._bgbuffer;
			let pixrendered = this._pixrendered;
			for (let destIndex = si; destIndex < ei; destIndex += 1) {
				if (pixrendered.get(destIndex) > 0xff) {
					buffer.set(destIndex, bgbuffer.get(destIndex));
				}
			}
		}
		if (this._f_sp_visibility === 1) {
			this.RenderSpritesPartially(startScan, scanCount, false);
		}
		this._valid_tile_data = false;
	},
	RenderBgScanline : function(bgbuffer, scan) {
		let baseTile = NESEmulator.ConditionExpr(this._reg_s === 0, 0, 256);
		let destIndex = (scan << 8) - this._reg_fh;
		this._cur_nt = this._ntable_1.get(this._cnt_v + this._cnt_v + this._cnt_h);
		this._cnt_ht = this._reg_ht;
		this._cnt_h = this._reg_h;
		this._cur_nt = this._ntable_1.get(this._cnt_v + this._cnt_v + this._cnt_h);
		if (scan < 240 && scan - this._cnt_fv >= 0) {
			let tscanoffset = this._cnt_fv << 3;
			let scantile = this._scantile;
			let attrib = this._attrib;
			let ptTile = this._pt_tile;
			let nameTable = this._name_table;
			let imgPalette = this._img_palette;
			let pixrendered = this._pixrendered;
			let targetBuffer = this._buffer;
			if (bgbuffer !== undefined) {
				targetBuffer = this._bgbuffer;
			}
			let t = undefined;
			let tpix = undefined;
			let att = 0;
			let col = 0;
			for (let tile = 0; tile < 32; tile += 1) {
				if (scan >= 0) {
					if (this._valid_tile_data) {
						t = scantile.get(tile);
						if (t === undefined) {
							continue;
						}
						tpix = t._pix;
						att = attrib.get(tile);
					} else {
						t = ptTile.get(baseTile + nameTable.get(this._cur_nt).GetTileIndex(this._cnt_ht, this._cnt_vt));
						if (t === undefined) {
							continue;
						}
						tpix = t._pix;
						att = nameTable.get(this._cur_nt).GetAttrib(this._cnt_ht, this._cnt_vt);
						scantile.set(tile, t);
						attrib.set(tile, att);
					}
					let sx = 0;
					let x = (tile << 3) - this._reg_fh;
					if (x > -8) {
						if (x < 0) {
							destIndex = destIndex - (x);
							sx = -x;
						}
						if (t._opaque.get(this._cnt_fv)) {
							while (sx < 8) {
								targetBuffer.set(destIndex, imgPalette.get(tpix.get(tscanoffset + sx) + att));
								pixrendered.set(destIndex, pixrendered.get(destIndex) | 256);
								++ destIndex;
								++ sx;
							}
						} else {
							while (sx < 8) {
								col = tpix.get(tscanoffset + sx);
								if (col !== 0) {
									targetBuffer.set(destIndex, imgPalette.get(col + att));
									pixrendered.set(destIndex, pixrendered.get(destIndex) | 256);
								}
								++ destIndex;
								++ sx;
							}
						}
					}
				}
				++ this._cnt_ht;
				if (this._cnt_ht === 32) {
					this._cnt_ht = 0;
					++ this._cnt_h;
					this._cnt_h = this._cnt_h % (2);
					this._cur_nt = this._ntable_1.get((this._cnt_v << 1) + this._cnt_h);
				}
			}
			this._valid_tile_data = true;
		}
		++ this._cnt_fv;
		if (this._cnt_fv === 8) {
			this._cnt_fv = 0;
			++ this._cnt_vt;
			if (this._cnt_vt === 30) {
				this._cnt_vt = 0;
				++ this._cnt_v;
				this._cnt_v = this._cnt_v % (2);
				this._cur_nt = this._ntable_1.get((this._cnt_v << 1) + this._cnt_h);
			} else {
				if (this._cnt_vt === 32) {
					this._cnt_vt = 0;
				}
			}
			this._valid_tile_data = false;
		}
	},
	RenderSpritesPartially : function(startscan, scancount, bgPri) {
		if (this._f_sp_visibility === 1) {
			for (let i = 0; i < 64; i += 1) {
				if (this._bg_priority.get(i) === bgPri && this._spr_x.get(i) >= 0 && this._spr_x.get(i) < 256 && this._spr_y.get(i) + 8 >= startscan && this._spr_y.get(i) < startscan + scancount) {
					if (this._f_sprite_size === 0) {
						let srcy1 = 0;
						let srcy2 = 8;
						if (this._spr_y.get(i) < startscan) {
							srcy1 = startscan - this._spr_y.get(i) - 1;
						}
						if (this._spr_y.get(i) + 8 > startscan + scancount) {
							srcy2 = startscan + scancount - this._spr_y.get(i) + 1;
						}
						if (this._f_sp_pattern_table === 0) {
							this._pt_tile.get(this._spr_tile.get(i)).Render(this._buffer, 0, srcy1, 8, srcy2, this._spr_x.get(i), this._spr_y.get(i) + 1, this._spr_col.get(i), this._spr_palette, this._hori_flip.get(i), this._vert_flip.get(i), i, this._pixrendered);
						} else {
							this._pt_tile.get(this._spr_tile.get(i) + 256).Render(this._buffer, 0, srcy1, 8, srcy2, this._spr_x.get(i), this._spr_y.get(i) + 1, this._spr_col.get(i), this._spr_palette, this._hori_flip.get(i), this._vert_flip.get(i), i, this._pixrendered);
						}
					} else {
						let top = this._spr_tile.get(i);
						if ((top & 1) !== 0) {
							top = this._spr_tile.get(i) - 1 + 256;
						}
						let srcy1 = 0;
						let srcy2 = 8;
						if (this._spr_y.get(i) < startscan) {
							srcy1 = startscan - this._spr_y.get(i) - 1;
						}
						if (this._spr_y.get(i) + 8 > startscan + scancount) {
							srcy2 = startscan + scancount - this._spr_y.get(i);
						}
						this._pt_tile.get(top + NESEmulator.ConditionExpr(this._vert_flip.get(i), 1, 0)).Render(this._buffer, 0, srcy1, 8, srcy2, this._spr_x.get(i), this._spr_y.get(i) + 1, this._spr_col.get(i), this._spr_palette, this._hori_flip.get(i), this._vert_flip.get(i), i, this._pixrendered);
						srcy1 = 0;
						srcy2 = 8;
						if (this._spr_y.get(i) + 8 < startscan) {
							srcy1 = startscan - (this._spr_y.get(i) + 8 + 1);
						}
						if (this._spr_y.get(i) + 16 > startscan + scancount) {
							srcy2 = startscan + scancount - (this._spr_y.get(i) + 8);
						}
						this._pt_tile.get(top + NESEmulator.ConditionExpr(this._vert_flip.get(i), 0, 1)).Render(this._buffer, 0, srcy1, 8, srcy2, this._spr_x.get(i), this._spr_y.get(i) + 1 + 8, this._spr_col.get(i), this._spr_palette, this._hori_flip.get(i), this._vert_flip.get(i), i, this._pixrendered);
					}
				}
			}
		}
	},
	CheckSprite0 : function(scan) {
		this._spr_0_hit_x = -1;
		this._spr_0_hit_y = -1;
		let toffset = 0;
		let tIndexAdd = NESEmulator.ConditionExpr(this._f_sp_pattern_table === 0, 0, 256);
		let bufferIndex = 0;
		let x = this._spr_x.get(0);
		let y = this._spr_y.get(0) + 1;
		let t = undefined;
		if (this._f_sprite_size === 0) {
			if (y <= scan && y + 8 > scan && x >= -7 && x < 256) {
				t = this._pt_tile.get(this._spr_tile.get(0) + tIndexAdd);
				if (this._vert_flip.get(0)) {
					toffset = 7 - (scan - y);
				} else {
					toffset = scan - y;
				}
				toffset = toffset * (8);
				bufferIndex = scan * 256 + x;
				if (this._hori_flip.get(0)) {
					for (let i = 7; i >= 0; i += -1) {
						if (x >= 0 && x < 256) {
							if (bufferIndex >= 0 && bufferIndex < 61440 && this._pixrendered.get(bufferIndex) !== 0) {
								if (t._pix.get(toffset + i) !== 0) {
									this._spr_0_hit_x = bufferIndex % 256;
									this._spr_0_hit_y = scan;
									return true;
								}
							}
						}
						++ x;
						++ bufferIndex;
					}
				} else {
					for (let i = 0; i < 8; i += 1) {
						if (x >= 0 && x < 256) {
							if (bufferIndex >= 0 && bufferIndex < 61440 && this._pixrendered.get(bufferIndex) !== 0) {
								if (t._pix.get(toffset + i) !== 0) {
									this._spr_0_hit_x = bufferIndex % 256;
									this._spr_0_hit_y = scan;
									return true;
								}
							}
						}
						++ x;
						++ bufferIndex;
					}
				}
			}
		} else {
			if (y <= scan && y + 16 > scan && x >= -7 && x < 256) {
				if (this._vert_flip.get(0)) {
					toffset = 15 - (scan - y);
				} else {
					toffset = scan - y;
				}
				if (toffset < 8) {
					t = this._pt_tile.get(this._spr_tile.get(0) + NESEmulator.ConditionExpr(this._vert_flip.get(0), 1, 0) + NESEmulator.ConditionExpr((this._spr_tile.get(0) & 1) !== 0, 255, 0));
				} else {
					t = this._pt_tile.get(this._spr_tile.get(0) + NESEmulator.ConditionExpr(this._vert_flip.get(0), 0, 1) + NESEmulator.ConditionExpr((this._spr_tile.get(0) & 1) !== 0, 255, 0));
					if (this._vert_flip.get(0)) {
						toffset = 15 - toffset;
					} else {
						toffset = toffset - (8);
					}
				}
				toffset = toffset * (8);
				bufferIndex = scan * 256 + x;
				if (this._hori_flip.get(0)) {
					for (let i = 7; i >= 0; i += -1) {
						if (x >= 0 && x < 256) {
							if (bufferIndex >= 0 && bufferIndex < 61440 && this._pixrendered.get(bufferIndex) !== 0) {
								if (t._pix.get(toffset + i) !== 0) {
									this._spr_0_hit_x = bufferIndex % 256;
									this._spr_0_hit_y = scan;
									return true;
								}
							}
						}
						++ x;
						++ bufferIndex;
					}
				} else {
					for (let i = 0; i < 8; i += 1) {
						if (x >= 0 && x < 256) {
							if (bufferIndex >= 0 && bufferIndex < 61440 && this._pixrendered.get(bufferIndex) !== 0) {
								if (t._pix.get(toffset + i) !== 0) {
									this._spr_0_hit_x = bufferIndex % 256;
									this._spr_0_hit_y = scan;
									return true;
								}
							}
						}
						++ x;
						++ bufferIndex;
					}
				}
			}
		}
		return false;
	},
	WriteMem : function(address, value) {
		this._vram_mem.set(address, value);
		if (address < 0x2000) {
			this._vram_mem.set(address, value);
			this.PatternWrite(address, value);
		} else {
			if (address >= 0x2000 && address < 0x23c0) {
				this.NameTableWrite(this._ntable_1.get(0), address - 0x2000, value);
			} else {
				if (address >= 0x23c0 && address < 0x2400) {
					this.AttribTableWrite(this._ntable_1.get(0), address - 0x23c0, value);
				} else {
					if (address >= 0x2400 && address < 0x27c0) {
						this.NameTableWrite(this._ntable_1.get(1), address - 0x2400, value);
					} else {
						if (address >= 0x27c0 && address < 0x2800) {
							this.AttribTableWrite(this._ntable_1.get(1), address - 0x27c0, value);
						} else {
							if (address >= 0x2800 && address < 0x2bc0) {
								this.NameTableWrite(this._ntable_1.get(2), address - 0x2800, value);
							} else {
								if (address >= 0x2bc0 && address < 0x2c00) {
									this.AttribTableWrite(this._ntable_1.get(2), address - 0x2bc0, value);
								} else {
									if (address >= 0x2c00 && address < 0x2fc0) {
										this.NameTableWrite(this._ntable_1.get(3), address - 0x2c00, value);
									} else {
										if (address >= 0x2fc0 && address < 0x3000) {
											this.AttribTableWrite(this._ntable_1.get(3), address - 0x2fc0, value);
										} else {
											if (address >= 0x3f00 && address < 0x3f20) {
												this.UpdatePalettes();
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	},
	UpdatePalettes : function() {
		for (let i = 0; i < 16; i += 1) {
			if (this._f_disp_type === 0) {
				this._img_palette.set(i, this._pal_table.GetEntry(this._vram_mem.get(0x3f00 + i) & 63));
			} else {
				this._img_palette.set(i, this._pal_table.GetEntry(this._vram_mem.get(0x3f00 + i) & 32));
			}
		}
		for (let i = 0; i < 16; i += 1) {
			if (this._f_disp_type === 0) {
				this._spr_palette.set(i, this._pal_table.GetEntry(this._vram_mem.get(0x3f10 + i) & 63));
			} else {
				this._spr_palette.set(i, this._pal_table.GetEntry(this._vram_mem.get(0x3f10 + i) & 32));
			}
		}
	},
	PatternWrite : function(address, value) {
		let tileIndex = ALittle.Math_Floor(address / 16);
		let leftOver = address % 16;
		if (leftOver < 8) {
			this._pt_tile.get(tileIndex).SetScanline(leftOver, value, this._vram_mem.get(address + 8));
		} else {
			this._pt_tile.get(tileIndex).SetScanline(leftOver - 8, this._vram_mem.get(address - 8), value);
		}
	},
	NameTableWrite : function(index, address, value) {
		this._name_table.get(index)._tile.set(address, value);
		this.CheckSprite0(this._scanline - 20);
	},
	AttribTableWrite : function(index, address, value) {
		this._name_table.get(index).WriteAttrib(address, value);
	},
	SpriteRamWriteUpdate : function(address, value) {
		let tIndex = ALittle.Math_Floor(address / 4);
		if (tIndex === 0) {
			this.CheckSprite0(this._scanline - 20);
		}
		if (address % 4 === 0) {
			this._spr_y.set(tIndex, value);
		} else {
			if (address % 4 === 1) {
				this._spr_tile.set(tIndex, value);
			} else {
				if (address % 4 === 2) {
					this._vert_flip.set(tIndex, (value & 0x80) !== 0);
					this._hori_flip.set(tIndex, (value & 0x40) !== 0);
					this._bg_priority.set(tIndex, (value & 0x20) !== 0);
					this._spr_col.set(tIndex, (value & 3) << 2);
				} else {
					if (address % 4 === 3) {
						this._spr_x.set(tIndex, value);
					}
				}
			}
		}
	},
	DoNMI : function() {
		this.SetStatusFlag(NESEmulator.NesPPUStatus.STATUS_VBLANK, true);
		this._nes._cpu.RequestIrq(NESEmulator.NesCPUIRQ.IRQ_NMI);
	},
	IsPixelWhite : function(x, y) {
		this.TriggerRendering();
		return this._buffer.get((y << 8) + x) === 0xffffff;
	},
}, "NESEmulator.NesPPU");

}