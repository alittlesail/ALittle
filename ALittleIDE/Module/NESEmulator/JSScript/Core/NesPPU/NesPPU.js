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
		this._spr_y = new Map();
		this._spr_tile = new Map();
		this._spr_col = new Map();
		this._vert_flip = new Map();
		this._hori_flip = new Map();
		this._bg_priority = new Map();
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
}