{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesTile = JavaScript.Class(undefined, {
	Ctor : function() {
		this._pix = new Map();
		this._opaque = new Map();
		this._init = false;
	},
	SetBuffer : function(scanline) {
		for (let y = 0; y < 8; y += 1) {
			this.SetScanline(y, scanline.get(y), scanline.get(y + 8));
		}
	},
	SetScanline : function(sline, b1, b2) {
		this._init = true;
		let t_index = sline << 3;
		for (let x = 0; x < 8; x += 1) {
			this._pix.set(t_index + x, ((b1 >> (7 - x)) & 1) + (((b2 >> (7 - x)) & 1) << 1));
			if (this._pix.get(t_index + x) === 0) {
				this._opaque.set(sline, false);
			}
		}
	},
	Render : function(buffer, src_x1, src_y1, src_x2, src_y2, dx, dy, pal_add, palette, flip_horizontal, flip_vertical, pri, pri_table) {
		if (dx < -7 || dx >= 256 || dy < -7 || dy >= 240) {
			return;
		}
		let w = src_x2 - src_x1;
		let h = src_y2 - src_y1;
		if (dx < 0) {
			src_x1 = src_x1 - (dx);
		}
		if (dx + src_x2 >= 256) {
			src_x2 = 256 - dx;
		}
		if (dy < 0) {
			src_y1 = src_y1 - (dy);
		}
		if (dy + src_y2 >= 240) {
			src_y2 = 240 - dy;
		}
		if (!flip_horizontal && !flip_vertical) {
			let fb_index = (dy << 8) + dx;
			let t_index = 0;
			for (let y = 0; y < 8; y += 1) {
				for (let x = 0; x < 8; x += 1) {
					if (x >= src_x1 && x < src_x2 && y >= src_y1 && y < src_y2) {
						let pal_index = this._pix.get(t_index);
						let tpri = pri_table.get(fb_index);
						if (pal_index !== 0 && pri <= (tpri & 0xff)) {
							buffer.set(fb_index, palette.get(pal_index + pal_add));
							tpri = (tpri & 0xf00) | pri;
							pri_table.set(fb_index, tpri);
						}
					}
					++ fb_index;
					++ t_index;
				}
				fb_index = fb_index - (8);
				fb_index = fb_index + (256);
			}
		} else if (flip_horizontal && !flip_vertical) {
			let fb_index = (dy << 8) + dx;
			let t_index = 7;
			for (let y = 0; y < 8; y += 1) {
				for (let x = 0; x < 8; x += 1) {
					if (x >= src_x1 && x < src_x2 && y >= src_y1 && y < src_y2) {
						let pal_index = this._pix.get(t_index);
						let tpri = pri_table.get(fb_index);
						if (pal_index !== 0 && pri <= (tpri & 0xff)) {
							buffer.set(fb_index, palette.get(pal_index + pal_add));
							tpri = (tpri & 0xf00) | pri;
							pri_table.set(fb_index, tpri);
						}
					}
					++ fb_index;
					-- t_index;
				}
				fb_index = fb_index - (8);
				fb_index = fb_index + (256);
				t_index = t_index + (16);
			}
		} else if (!flip_horizontal && flip_vertical) {
			let fb_index = (dy << 8) + dx;
			let t_index = 56;
			for (let y = 0; y < 8; y += 1) {
				for (let x = 0; x < 8; x += 1) {
					if (x >= src_x1 && x < src_x2 && y >= src_y1 && y < src_y2) {
						let pal_index = this._pix.get(t_index);
						let tpri = pri_table.get(fb_index);
						if (pal_index !== 0 && pri <= (tpri & 0xff)) {
							buffer.set(fb_index, palette.get(pal_index + pal_add));
							tpri = (tpri & 0xf00) | pri;
							pri_table.set(fb_index, tpri);
						}
					}
					++ fb_index;
					++ t_index;
				}
				fb_index = fb_index - (8);
				fb_index = fb_index + (256);
				t_index = t_index - (16);
			}
		} else {
			let fb_index = (dy << 8) + dx;
			let t_index = 63;
			for (let y = 0; y < 8; y += 1) {
				for (let x = 0; x < 8; x += 1) {
					if (x >= src_x1 && x < src_x2 && y >= src_y1 && y < src_y2) {
						let pal_index = this._pix.get(t_index);
						let tpri = pri_table.get(fb_index);
						if (pal_index !== 0 && pri <= (tpri & 0xff)) {
							buffer.set(fb_index, palette.get(pal_index + pal_add));
							tpri = (tpri & 0xf00) | pri;
							pri_table.set(fb_index, tpri);
						}
					}
					++ fb_index;
					-- t_index;
				}
				fb_index = fb_index - (8);
				fb_index = fb_index + (256);
			}
		}
	},
	IsTransparent : function(x, y) {
		return this._pix.get((y << 3) + x) === 0;
	},
}, "NESEmulator.NesTile");

}