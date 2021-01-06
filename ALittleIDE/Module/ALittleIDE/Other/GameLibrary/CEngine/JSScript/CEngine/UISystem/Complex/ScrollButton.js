{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-2129379001, "ALittle.ScrollButtonDragBeginEvent", {
name : "ALittle.ScrollButtonDragBeginEvent", ns_name : "ALittle", rl_name : "ScrollButtonDragBeginEvent", hash_code : -2129379001,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(2101017097, "ALittle.ScrollButtonDragEndEvent", {
name : "ALittle.ScrollButtonDragEndEvent", ns_name : "ALittle", rl_name : "ScrollButtonDragEndEvent", hash_code : 2101017097,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(-646882501, "ALittle.ScrollButtonDragEvent", {
name : "ALittle.ScrollButtonDragEvent", ns_name : "ALittle", rl_name : "ScrollButtonDragEvent", hash_code : -646882501,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})

let __abs = ALittle.Math_Abs;
if (ALittle.TextButton === undefined) throw new Error(" extends class:ALittle.TextButton is undefined");
ALittle.ScrollButton = JavaScript.Class(ALittle.TextButton, {
	Ctor : function(ctrl_sys) {
		this.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		this.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this.AddEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
		this._button_down = false;
		this._drag_begin_x = 0;
		this._drag_begin_y = 0;
		this._btn_drag = false;
		this._can_drag_trans = true;
		this._can_set_drag_trans = true;
	},
	set can_drag_trans(value) {
		if (this._can_set_drag_trans === false) {
			return;
		}
		this._can_drag_trans = value;
	},
	get can_drag_trans() {
		return this._can_drag_trans;
	},
	HandleDragBegin : function(event) {
		this._drag_begin_x = event.abs_x;
		this._drag_begin_y = event.abs_y;
	},
	HandleDrag : function(event) {
		if (this._btn_drag === false) {
			if (__abs(event.abs_x - this._drag_begin_x) > 2 || __abs(event.abs_y - this._drag_begin_y) > 2) {
				this._button_down = false;
				this.ShowUp(undefined);
				let e = {};
				e.target = this;
				e.delta_x = event.delta_x;
				e.delta_y = event.delta_y;
				e.abs_x = event.abs_x;
				e.abs_y = event.abs_y;
				this.DispatchEvent(___all_struct.get(-2129379001), e);
				this._can_set_drag_trans = false;
				if (this._can_drag_trans && this._trans_target.get("drag") !== undefined) {
					let ue = {};
					ue.target = this._trans_target.get("drag");
					ue.delta_x = event.delta_x;
					ue.delta_y = event.delta_y;
					ue.abs_x = event.abs_x;
					ue.abs_y = event.abs_y;
					this._trans_target.get("drag").DispatchEvent(___all_struct.get(-2129379001), e);
				}
				this._btn_drag = true;
			}
		} else if (this._btn_drag === true) {
			let e = {};
			e.target = this;
			e.delta_x = event.delta_x;
			e.delta_y = event.delta_y;
			e.abs_x = event.abs_x;
			e.abs_y = event.abs_y;
			this.DispatchEvent(___all_struct.get(-646882501), e);
			if (this._can_drag_trans && this._trans_target.get("drag") !== undefined) {
				let ue = {};
				ue.target = this._trans_target.get("drag");
				ue.delta_x = event.delta_x;
				ue.delta_y = event.delta_y;
				ue.abs_x = event.abs_x;
				ue.abs_y = event.abs_y;
				this.DispatchEvent(___all_struct.get(-646882501), e);
			}
		}
	},
	HandleDragEnd : function(event) {
		if (this._btn_drag) {
			if (this._can_drag_trans && this._trans_target.get("drag") !== undefined) {
				let e = {};
				e.target = this._trans_target.get("drag");
				e.delta_x = event.delta_x;
				e.delta_y = event.delta_y;
				e.abs_x = event.abs_x;
				e.abs_y = event.abs_y;
				this._trans_target.get("drag").DispatchEvent(___all_struct.get(150587926), e);
			}
			this._can_set_drag_trans = true;
			let e = {};
			e.target = this;
			e.delta_x = event.delta_x;
			e.delta_y = event.delta_y;
			e.abs_x = event.abs_x;
			e.abs_y = event.abs_y;
			this.DispatchEvent(___all_struct.get(2101017097), e);
		}
	},
	HandleLButtonDown : function(event) {
		this._drag_begin_x = 0;
		this._drag_begin_y = 0;
		this._btn_drag = false;
		this._button_down = true;
		this._button_down_loop = ALittle.NewObject(ALittle.LoopFunction, this.HandleLButtonDownFunc.bind(this, undefined), 1, 0, 100);
		A_LoopSystem.AddUpdater(this._button_down_loop);
	},
	HandleLButtonUp : function(event) {
		if (this._btn_drag) {
			return;
		}
		if (this._button_down === false) {
			this.HandleLButtonUpFunc(event);
		} else {
			this.ShowDown();
			this._button_up_loop = ALittle.NewObject(ALittle.LoopFunction, this.HandleLButtonUpFunc.bind(this, event), 1, 0, 60);
			this._button_up_loop.Start();
		}
	},
	DispatchEvent : function(T, event) {
		let rflt = T;
		let event_target = this;
		if (this._trans_target.get("event") !== undefined) {
			event_target = this._trans_target.get("event");
		}
		if (event_target._abs_disabled) {
			return;
		}
		if (event_target._abs_disabled) {
			return;
		}
		let callback_table = event_target._listeners[rflt.name];
		if (callback_table === undefined) {
			return;
		}
		for (let [object, callback_value] of callback_table) {
			if (callback_value === undefined) continue;
			for (let [func, _] of callback_value) {
				if (_ === undefined) continue;
				func(object, event);
			}
		}
	},
	HandleLButtonDownFunc : function(event) {
		if (this._button_down === true) {
			this.ShowDown();
			this._button_down = false;
		}
		A_LoopSystem.RemoveUpdater(this._button_down_loop);
	},
	HandleLButtonUpFunc : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			e.count = event.count;
			this.DispatchEvent(___all_struct.get(-449066808), e);
			if (ALittle.System_IsPhone() === false) {
				this.ShowOver();
			} else {
				this.ShowUp(undefined);
			}
		} else {
			this.ShowUp(undefined);
		}
		A_LoopSystem.RemoveUpdater(this._button_up_loop);
	},
}, "ALittle.ScrollButton");

}