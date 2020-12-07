{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
NESEmulator.GController = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._margin_rate = 0;
	},
	TCtor : function() {
	},
	UpdateDir : function(target, rel_x, rel_y) {
		let width = target.width;
		let height = target.height;
		let w_margin = width / 2 - width / 2 * this._margin_rate;
		let h_margin = height / 2 - height / 2 * this._margin_rate;
		let h_key_delta = 0;
		let h_key = undefined;
		{
			if (rel_x < w_margin) {
				h_key = NESEmulator.NesControlType.BUTTON_LEFT;
				h_key_delta = w_margin - rel_x;
			} else if (rel_x > width - w_margin) {
				h_key = NESEmulator.NesControlType.BUTTON_RIGHT;
				h_key_delta = rel_x - (width - w_margin);
			}
		}
		let v_key_delta = 0;
		let v_key = undefined;
		{
			if (rel_y < h_margin) {
				v_key = NESEmulator.NesControlType.BUTTON_UP;
				v_key_delta = h_margin - rel_y;
			} else if (rel_y > height - h_margin) {
				v_key = NESEmulator.NesControlType.BUTTON_DOWN;
				v_key_delta = rel_y - (height - h_margin);
			}
		}
		let new_key = undefined;
		if (h_key === undefined && v_key !== undefined) {
			new_key = v_key;
		} else if (h_key !== undefined && v_key === undefined) {
			new_key = h_key;
		} else if (h_key !== undefined && v_key !== undefined) {
			if (h_key_delta > v_key_delta) {
				new_key = h_key;
			} else {
				new_key = v_key;
			}
		}
		if (this._key_type === new_key) {
			return;
		}
		if (this._key_type !== undefined) {
			g_GNes.ButtonUp(1, this._key_type);
		}
		this._key_type = new_key;
		if (this._key_type !== undefined) {
			g_GNes.ButtonDown(1, this._key_type);
		}
	},
	StopDir : function() {
		if (this._key_type !== undefined) {
			g_GNes.ButtonUp(1, this._key_type);
		}
		this._key_type = undefined;
	},
	HandleLButtonDown : function(event) {
		this.UpdateDir(event.target, event.rel_x, event.rel_y);
	},
	HandleLButtonUp : function(event) {
		this.StopDir();
	},
	HandleDragBegin : function(event) {
	},
	HandleDrag : function(event) {
		this.UpdateDir(event.target, event.rel_x, event.rel_y);
	},
	HandleDragEnd : function(event) {
		this.StopDir();
	},
	HandleSelectDown : function(event) {
		g_GNes.ButtonDown(1, NESEmulator.NesControlType.BUTTON_SELECT);
	},
	HandleSelectUp : function(event) {
		g_GNes.ButtonUp(1, NESEmulator.NesControlType.BUTTON_SELECT);
	},
	HandleStartDown : function(event) {
		g_GNes.ButtonDown(1, NESEmulator.NesControlType.BUTTON_START);
	},
	HandleStartUp : function(event) {
		g_GNes.ButtonUp(1, NESEmulator.NesControlType.BUTTON_START);
	},
	HandleBDown : function(event) {
		g_GNes.ButtonDown(1, NESEmulator.NesControlType.BUTTON_B);
	},
	HandleBUp : function(event) {
		g_GNes.ButtonUp(1, NESEmulator.NesControlType.BUTTON_B);
	},
	HandleADown : function(event) {
		g_GNes.ButtonDown(1, NESEmulator.NesControlType.BUTTON_A);
	},
	HandleAUp : function(event) {
		g_GNes.ButtonUp(1, NESEmulator.NesControlType.BUTTON_A);
	},
}, "NESEmulator.GController");

}