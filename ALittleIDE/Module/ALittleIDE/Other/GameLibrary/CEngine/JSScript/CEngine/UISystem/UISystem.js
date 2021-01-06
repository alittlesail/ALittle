{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1031172931, "ALittle.FingerInfo", {
name : "ALittle.FingerInfo", ns_name : "ALittle", rl_name : "FingerInfo", hash_code : 1031172931,
name_list : ["key","mouse_x","mouse_y","last_mouse_x","last_mouse_y","dl","mfc","mfc_rel_x","mfc_rel_y","is_sfc"],
type_list : ["string","double","double","double","double","bool","ALittle.DisplayObject","double","double","bool"],
option_map : {}
})

let __abs = ALittle.Math_Abs;
ALittle.UISystem = JavaScript.Class(undefined, {
	Ctor : function() {
		this._view_width = 0;
		this._view_height = 0;
		this._mouse_x = 0;
		this._mouse_y = 0;
		this._last_mouse_x = 0;
		this._last_mouse_y = 0;
		this._lbutton_down = false;
		this._lbutton_count = 0;
		this._lbutton_finger_id = undefined;
		this._lbutton_touch_id = undefined;
		this._mfc = undefined;
		this._mfc_rel_x = 0;
		this._mfc_rel_y = 0;
		this._mfd = undefined;
		this._sfc = undefined;
		this._wfc = undefined;
		this._pfc = undefined;
		this._button_type = undefined;
		this._sl = false;
		this._dl = false;
		this._dl_delta_x = 0;
		this._dl_delta_y = 0;
		this._max_dl_delta = 10;
		this._max_lp_delta = 2;
		if (ALittle.System_GetPlatform() === "Windows") {
			this._max_dl_delta = 1;
			this._max_lp_delta = 0;
		}
		this._ime_editing = false;
		this._ime_editing_callback = undefined;
		this._sym_map = new Map();
		this._keydown_callback = undefined;
		this._keyup_callback = undefined;
		this._view_resize_callback = undefined;
		this._long_press = undefined;
		this._finger_info = {};
	},
	set view_resize_callback(value) {
		this._view_resize_callback = value;
	},
	get view_resize_callback() {
		return this._view_resize_callback;
	},
	set keydown_callback(value) {
		this._keydown_callback = value;
	},
	get keydown_callback() {
		return this._keydown_callback;
	},
	set keyup_callback(value) {
		this._keyup_callback = value;
	},
	get keyup_callback() {
		return this._keyup_callback;
	},
	set quit_callback(value) {
		this._quit_callback = value;
	},
	get quit_callback() {
		return this._quit_callback;
	},
	get sym_map() {
		return this._sym_map;
	},
	set ime_callback(value) {
		this._ime_editing_callback = value;
	},
	get ime_callback() {
		return this._ime_editing_callback;
	},
	get mouse_x() {
		return this._mouse_x;
	},
	get mouse_y() {
		return this._mouse_y;
	},
	set focus(control) {
		if (this._sfc === control) {
			return;
		}
		this._wfc = undefined;
		if (this._sfc !== undefined) {
			if (this._dl === true) {
				this._dl = false;
				this._dl_delta_x = 0;
				this._dl_delta_y = 0;
				if (this._button_type === "ALittle.UILButtonDownEvent") {
					let event = {};
					event.target = this._sfc;
					event.rel_x = this._mfc_rel_x;
					event.rel_y = this._mfc_rel_y;
					if (this._mfc !== this._sfc) {
						[event.rel_x, event.rel_y] = this._sfc.GlobalToLocalMatrix2D(this._mouse_x, this._mouse_y);
					}
					event.delta_x = this._mouse_x - this._last_mouse_x;
					event.delta_y = this._mouse_y - this._last_mouse_y;
					event.abs_x = this._mouse_x;
					event.abs_y = this._mouse_y;
					this._sfc.DispatchEvent(___all_struct.get(150587926), event);
				}
			}
			let sfc = this._sfc;
			if (this._ime_editing_callback !== undefined) {
				this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
			}
			this._sfc = undefined;
			this._sl = false;
			sfc.DispatchEvent(___all_struct.get(292776509), {});
		}
		this._sfc = control;
		if (this._sfc !== undefined) {
			this._sfc.DispatchEvent(___all_struct.get(-644464135), {});
		}
	},
	get focus() {
		return this._sfc;
	},
	set pick(control) {
		if (this._pfc !== undefined) {
			A_LayerManager.RemoveFromTip(this._pfc);
		}
		this._pfc = control;
		if (this._pfc !== undefined) {
			A_LayerManager.AddToTip(this._pfc);
		}
	},
	get pick() {
		return this._pfc;
	},
	get view_width() {
		return this._view_width;
	},
	get view_height() {
		return this._view_height;
	},
	HandleMouseMoved : function(x, y) {
		let delta_x = x - this._mouse_x;
		let delta_y = y - this._mouse_y;
		this._last_mouse_x = this._mouse_x;
		this._last_mouse_y = this._mouse_y;
		this._mouse_x = x;
		this._mouse_y = y;
		if (this._long_press !== undefined && __abs(delta_x) <= this._max_lp_delta && __abs(delta_y) <= this._max_lp_delta) {
			return false;
		}
		if (this._long_press !== undefined) {
			this._long_press.Stop();
			this._long_press = undefined;
		}
		if (this._pfc !== undefined) {
			this._pfc.x = this._pfc.x + (delta_x);
			this._pfc.y = this._pfc.y + (delta_y);
		}
		if (this._sl && this._button_type === "ALittle.UILButtonDownEvent") {
			if (this._dl === true) {
				let event = {};
				event.target = this._sfc;
				[event.rel_x, event.rel_y] = this._sfc.GlobalToLocalMatrix2D(x, y);
				if (this._dl_delta_x > 0) {
					delta_x = this._dl_delta_x + delta_x;
					this._dl_delta_x = 0;
				}
				if (this._dl_delta_y > 0) {
					delta_y = this._dl_delta_y + delta_y;
					this._dl_delta_y = 0;
				}
				event.abs_x = x;
				event.abs_y = y;
				event.delta_x = delta_x;
				event.delta_y = delta_y;
				this._sfc.DispatchEvent(___all_struct.get(1337289812), event);
				return true;
			}
			if (this._dl === false) {
				this._dl_delta_x = this._dl_delta_x + (delta_x);
				this._dl_delta_y = this._dl_delta_y + (delta_y);
				if (__abs(this._dl_delta_x) >= this._max_dl_delta || __abs(this._dl_delta_y) >= this._max_dl_delta) {
					this._dl = true;
					let event = {};
					event.target = this._sfc;
					let mouse_x = x - delta_x;
					let mouse_y = y - delta_y;
					[event.rel_x, event.rel_y] = this._sfc.GlobalToLocalMatrix2D(mouse_x, mouse_y);
					event.abs_x = mouse_x;
					event.abs_y = mouse_y;
					event.delta_x = 0;
					event.delta_y = 0;
					this._sfc.DispatchEvent(___all_struct.get(1301789264), event);
				}
			}
			return true;
		}
		this.UpdateMoveFocus(x, y);
		return this._mfc !== undefined;
	},
	HandleLButtonDown : function(x, y, count) {
		this._lbutton_down = true;
		this._lbutton_count = count;
		this._lbutton_finger_id = undefined;
		this._lbutton_touch_id = undefined;
		return this.HandleButtonDown(___all_struct.get(1883782801), x, y, count);
	},
	HandleLButtonUp : function(x, y) {
		this._lbutton_down = false;
		return this.HandleButtonUp(___all_struct.get(40651933), x, y, this._lbutton_count);
	},
	HandleMButtonDown : function(x, y, count) {
		return this.HandleButtonDown(___all_struct.get(349963892), x, y, count);
	},
	HandleMButtonUp : function(x, y) {
		return this.HandleButtonUp(___all_struct.get(683647260), x, y, 1);
	},
	HandleButtonDown : function(T, x, y, count) {
		let rflt = T;
		this._wfc = undefined;
		A_LayerManager.HandleLRButtonDown(x, y);
		this.UpdateMoveFocus(x, y);
		if (this._mfc !== undefined) {
			this._sl = true;
			this._button_type = rflt.name;
			if (this._pfc !== undefined && rflt.name === "ALittle.UILButtonDownEvent") {
				let event = {};
				event.target = this._mfc;
				event.drop_target = this._pfc;
				this._mfc.DispatchEvent(___all_struct.get(1354499457), event);
				A_LayerManager.RemoveFromTip(this._pfc);
				this._pfc = undefined;
			}
			if (this._mfd !== undefined) {
				let layer = this._mfd.show_parent;
				layer.SetChildIndex(this._mfd, layer.child_count);
			}
			let event = {};
			event.target = this._mfc;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = this._mfc_rel_x;
			event.rel_y = this._mfc_rel_y;
			event.count = count;
			event.is_drag = false;
			this._mfc.DispatchEvent(T, event);
			if (rflt.name === "ALittle.UILButtonDownEvent") {
				if (this._long_press !== undefined) {
					this._long_press.Stop();
				}
				let long_event = {};
				long_event.target = this._mfc;
				long_event.abs_x = x;
				long_event.abs_y = y;
				long_event.rel_x = this._mfc_rel_x;
				long_event.rel_y = this._mfc_rel_y;
				long_event.is_drag = false;
				this._long_press = ALittle.NewObject(ALittle.LoopFunction, ALittle.UISystem.DispatchLongButtonEvent.bind(undefined, this._mfc, long_event), 1, 500, 1);
				this._long_press.Start();
			}
			if (this._sfc === undefined) {
				this._sfc = this._mfc;
				this._sfc.DispatchEvent(___all_struct.get(-644464135), {});
			} else if (this._mfc !== this._sfc) {
				this._sfc.DispatchEvent(___all_struct.get(292776509), {});
				if (this._ime_editing_callback !== undefined) {
					this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
				}
				this._sfc = this._mfc;
				this._sfc.DispatchEvent(___all_struct.get(-644464135), {});
			}
			return true;
		} else {
			if (this._sfc !== undefined) {
				this._sfc.DispatchEvent(___all_struct.get(292776509), {});
				if (this._ime_editing_callback !== undefined) {
					this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
				}
				this._sfc = undefined;
				this._sl = false;
			}
		}
		return false;
	},
	DispatchLongButtonEvent : function(mfc, event) {
		mfc.DispatchEvent(___all_struct.get(-439548260), event);
	},
	HandleButtonUp : function(T, x, y, count) {
		if (this._sl === false) {
			return false;
		}
		if (this._long_press !== undefined) {
			this._long_press.Stop();
			this._long_press = undefined;
		}
		this._sl = false;
		let [rel_x, rel_y] = this._sfc.GlobalToLocalMatrix2D(x, y);
		let save_dl = this._dl;
		if (this._dl === true) {
			this._dl = false;
			this._dl_delta_x = 0;
			this._dl_delta_y = 0;
			let event = {};
			event.target = this._sfc;
			event.abs_x = x;
			event.abs_y = y;
			event.delta_x = this._mouse_x - this._last_mouse_x;
			event.delta_y = this._mouse_y - this._last_mouse_y;
			event.rel_x = rel_x;
			event.rel_y = rel_y;
			this._sfc.DispatchEvent(___all_struct.get(150587926), event);
		}
		if (this._sfc !== undefined) {
			let event = {};
			event.target = this._sfc;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = rel_x;
			event.rel_y = rel_y;
			event.is_drag = save_dl;
			event.count = count;
			this._sfc.DispatchEvent(T, event);
		}
		this.UpdateMoveFocus(x, y);
		return this._mfc !== undefined;
	},
	HandleRButtonDown : function(x, y, count) {
		A_LayerManager.HandleLRButtonDown(x, y);
		if (this._sl) {
			return false;
		}
		this.UpdateMoveFocus(x, y);
		if (this._mfc !== undefined) {
			let event = {};
			event.target = this._mfc;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = this._mfc_rel_x;
			event.rel_y = this._mfc_rel_y;
			event.count = count;
			event.is_drag = false;
			this._mfc.DispatchEvent(___all_struct.get(-641444818), event);
			return true;
		}
		return false;
	},
	HandleRButtonUp : function(x, y) {
		return false;
	},
	HandleTextInput : function(text) {
		this._ime_editing = false;
		if (this._ime_editing_callback !== undefined) {
			this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
		}
		if (this._sfc !== undefined) {
			let event = {};
			event.target = this._sfc;
			event.text = text;
			this._sfc.DispatchEvent(___all_struct.get(-1234078962), event);
			return true;
		}
		return false;
	},
	HandleTextEditing : function(text, start) {
		if (text === "") {
			if (this._ime_editing === false) {
				return;
			}
			this._ime_editing = false;
			if (this._ime_editing_callback !== undefined) {
				this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
			}
		} else {
			this._ime_editing = true;
			if (this._sfc === undefined || this._sfc.is_input === false || this._sfc.editable === false || this._sfc.font_size === undefined) {
				return;
			}
			if (this._ime_editing_callback !== undefined) {
				let list = ALittle.String_Split(ALittle.System_GetIMESelectList(), " ");
				let new_list = [];
				let count = 0;
				let ___OBJECT_1 = list;
				for (let index = 1; index <= ___OBJECT_1.length; ++index) {
					let value = ___OBJECT_1[index - 1];
					if (value === undefined) break;
					if (value !== "") {
						++ count;
						new_list[count - 1] = value;
					}
				}
				this._ime_editing_callback(true, text, start, new_list, this._sfc);
				ALittle.System_SetIMEPos(ALittle.System_GetScreenWidth(), ALittle.System_GetScreenHeight());
			} else {
				let [abs_x, abs_y] = this._sfc.LocalToGlobal();
				abs_x = abs_x + (this._sfc.cursor_x);
				abs_y = abs_y + ((this._sfc.cursor_y + this._sfc.font_size) * this._sfc.scale_y);
				ALittle.System_SetIMEPos(ALittle.Math_Floor(abs_x), ALittle.Math_Floor(abs_y));
			}
		}
	},
	HandleKeyDown : function(mod, sym, scancode) {
		this._sym_map.set(sym, true);
		if (ALittle.System_GetIMESelectList() === "" && this._ime_editing) {
			this._ime_editing = false;
			if (this._ime_editing_callback !== undefined) {
				this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
			}
			return;
		}
		let event = {};
		event.target = this._sfc;
		event.mod = mod;
		event.sym = sym;
		event.scancode = scancode;
		if (this._sfc !== undefined && this._ime_editing === false) {
			this._sfc.DispatchEvent(___all_struct.get(-1604617962), event);
		}
		if (!event.handled && this._ime_editing === false && this._keydown_callback !== undefined) {
			this._keydown_callback(mod, sym, scancode);
		}
	},
	HandleKeyUp : function(mod, sym, scancode) {
		this._sym_map.delete(sym);
		let event = {};
		event.target = this._sfc;
		event.mod = mod;
		event.sym = sym;
		event.scancode = scancode;
		if (this._sfc !== undefined && this._ime_editing === false) {
			this._sfc.DispatchEvent(___all_struct.get(1213009422), event);
		}
		if (this._ime_editing === false && this._keyup_callback !== undefined) {
			this._keyup_callback(mod, sym, scancode);
		}
	},
	HandleMouseWheel : function(x, y) {
		if (this._mfc === undefined) {
			return false;
		}
		if (this._wfc === undefined) {
			let control = this._mfc;
			while (control !== undefined) {
				if (control.can_scroll === true) {
					this._wfc = control;
					break;
				}
				control = control.show_parent;
			}
		}
		if (this._wfc !== undefined) {
			let event = {};
			event.target = this._wfc;
			event.delta_x = x;
			event.delta_y = y;
			this._wfc.DispatchEvent(___all_struct.get(-1737121315), event);
		}
		return true;
	},
	UpdateMoveFocus : function(x, y) {
		let mfc = undefined;
		let mfd = undefined;
		[mfc, mfd, this._mfc_rel_x, this._mfc_rel_y] = A_LayerManager.PickUp(x, y);
		this._mfd = mfd;
		if (this._mfc === mfc) {
			if (mfc !== undefined) {
				let event = {};
				event.target = mfc;
				event.abs_x = x;
				event.abs_y = y;
				event.rel_x = this._mfc_rel_x;
				event.rel_y = this._mfc_rel_y;
				mfc.DispatchEvent(___all_struct.get(-1001723540), event);
			}
			return;
		}
		if (this._mfc !== undefined) {
			this._mfc.DispatchEvent(___all_struct.get(-1202439334), {});
		}
		if (mfc !== undefined) {
			mfc.DispatchEvent(___all_struct.get(544684311), {});
		}
		this._mfc = mfc;
		this._wfc = undefined;
	},
	HandleViewResized : function(width, height) {
		if (this._view_width === width && this._view_height === height) {
			return;
		}
		this._view_width = width;
		this._view_height = height;
		A_LayerManager.HandleViewResized(width, height);
		if (this._view_resize_callback !== undefined) {
			this._view_resize_callback(width, height);
		}
	},
	HandleDropFile : function(path) {
		let x = ALittle.System_GetCursorX();
		let y = ALittle.System_GetCursorY();
		this.HandleMouseMoved(x, y);
		if (this._mfc === undefined) {
			return;
		}
		let event = {};
		event.target = this._mfc;
		event.path = path;
		this._mfc.DispatchEvent(___all_struct.get(-338112738), event);
	},
	HandleWindowEnter : function() {
	},
	HandleWindowLeave : function() {
		if (this._lbutton_down) {
			this.HandleLButtonUp(this._mouse_x, this._mouse_y);
		}
	},
	HandleQuit : function() {
		if (this._quit_callback !== undefined && !this._quit_callback()) {
			return;
		}
		ALittle.System_Exit();
	},
	HandleFingerDown : function(x, y, finger_id, touch_id) {
		if (this._lbutton_down === false) {
			this._lbutton_down = true;
			this._lbutton_count = 1;
			this._lbutton_finger_id = finger_id;
			this._lbutton_touch_id = touch_id;
			this._mouse_x = x;
			this._mouse_y = y;
			return this.HandleButtonDown(___all_struct.get(1883782801), x, y, 1);
		}
		let key = finger_id + "_" + touch_id;
		let info = {};
		info.key = key;
		info.mouse_x = x;
		info.mouse_y = y;
		info.last_mouse_x = 0;
		info.last_mouse_y = 0;
		info.dl = false;
		info.mfc = undefined;
		info.mfc_rel_x = 0;
		info.mfc_rel_y = 0;
		info.is_sfc = false;
		let mfd = undefined;
		[info.mfc, mfd, info.mfc_rel_x, info.mfc_rel_y] = A_LayerManager.PickUp(x, y);
		if (info.mfc === undefined) {
			return false;
		}
		info.is_sfc = (this._sl && (info.mfc === this._mfc || info.mfc === this._sfc));
		let event = {};
		event.target = info.mfc;
		event.abs_x = x;
		event.abs_y = y;
		event.rel_x = info.mfc_rel_x;
		event.rel_y = info.mfc_rel_y;
		event.finger_key = info.key;
		event.is_sfc = info.is_sfc;
		event.is_drag = false;
		info.mfc.DispatchEvent(___all_struct.get(-1233353463), event);
		this._finger_info[key] = info;
		return true;
	},
	HandleFingerUp : function(x, y, finger_id, touch_id) {
		if (this._lbutton_down && this._lbutton_finger_id === finger_id && this._lbutton_touch_id === touch_id) {
			this._lbutton_down = false;
			return this.HandleButtonUp(___all_struct.get(40651933), x, y, this._lbutton_count);
		}
		let key = finger_id + "_" + touch_id;
		let info = this._finger_info[key];
		if (info === undefined) {
			return false;
		}
		delete this._finger_info[key];
		info.last_mouse_x = info.mouse_x;
		info.last_mouse_y = info.mouse_y;
		info.mouse_x = x;
		info.mouse_y = y;
		let save_dl = info.dl;
		if (info.dl === true) {
			info.dl = false;
			let event = {};
			event.target = info.mfc;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = info.mfc_rel_x;
			event.rel_y = info.mfc_rel_y;
			event.delta_x = info.mouse_x - info.last_mouse_x;
			event.delta_y = info.mouse_y - info.last_mouse_y;
			event.finger_key = key;
			event.is_sfc = info.is_sfc;
			info.mfc.DispatchEvent(___all_struct.get(-2050069067), event);
		}
		let event = {};
		event.target = info.mfc;
		event.abs_x = x;
		event.abs_y = y;
		event.rel_x = info.mfc_rel_x;
		event.rel_y = info.mfc_rel_y;
		event.finger_key = info.key;
		event.is_sfc = info.is_sfc;
		event.is_drag = save_dl;
		info.mfc.DispatchEvent(___all_struct.get(734860930), event);
		return true;
	},
	HandleFingerMoved : function(x, y, finger_id, touch_id) {
		if (this._lbutton_down && this._lbutton_finger_id === finger_id && this._lbutton_touch_id === touch_id) {
			return this.HandleMouseMoved(x, y);
		}
		let key = finger_id + "_" + touch_id;
		let info = this._finger_info[key];
		if (info === undefined) {
			return false;
		}
		let delta_x = x - info.mouse_x;
		let delta_y = y - info.mouse_y;
		info.last_mouse_x = info.mouse_x;
		info.last_mouse_y = info.mouse_y;
		info.mouse_x = x;
		info.mouse_y = y;
		if (info.mfc !== undefined) {
			[info.mfc_rel_x, info.mfc_rel_y] = info.mfc.GlobalToLocalMatrix2D(x, y);
		}
		if (info.dl === true) {
			let event = {};
			event.target = info.mfc;
			event.delta_x = delta_x;
			event.delta_y = delta_y;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = info.mfc_rel_x;
			event.rel_y = info.mfc_rel_y;
			event.finger_key = info.key;
			event.is_sfc = info.is_sfc;
			info.mfc.DispatchEvent(___all_struct.get(-51419723), event);
			return true;
		}
		if (info.dl === false) {
			info.dl = true;
			let event = {};
			event.target = info.mfc;
			event.delta_x = delta_x;
			event.delta_y = delta_y;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = info.mfc_rel_x;
			event.rel_y = info.mfc_rel_y;
			event.finger_key = info.key;
			event.is_sfc = info.is_sfc;
			info.mfc.DispatchEvent(___all_struct.get(1598008698), event);
			return true;
		}
		return false;
	},
}, "ALittle.UISystem");

window.A_UISystem = ALittle.NewObject(ALittle.UISystem);
}