{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.SpringCheckButton === undefined) throw new Error(" extends class:ALittle.SpringCheckButton is undefined");
ALittle.SpringRadioButton = JavaScript.Class(ALittle.SpringCheckButton, {
	Ctor : function(ctrl_sys) {
		this._cancel_select = false;
	},
	set group(group) {
		if (this._group === group) {
			return;
		}
		if (this._group !== undefined) {
			this._group.delete(this);
		}
		this._group = group;
		if (this._group !== undefined) {
			this._group.set(this, true);
		}
	},
	get group() {
		return this._group;
	},
	SetGroup : function(list) {
		let group = ALittle.CreateKeyWeakMap();
		let ___OBJECT_1 = list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let button = ___OBJECT_1[index - 1];
			if (button === undefined) break;
			if (button._group !== undefined) {
				button._group.delete(button);
			}
			button._group = group;
			group.set(button, true);
		}
	},
	set cancel_select(value) {
		this._cancel_select = value;
	},
	get cancel_select() {
		return this._cancel_select;
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			if (this._selected === false) {
				this._selected = true;
				if (this._group !== undefined) {
					for (let [k, _] of this._group) {
						if (_ === undefined) continue;
						if (k !== this && k._selected === true) {
							k._selected = false;
							k.ShowUp();
							k.DispatchEvent(___all_struct.get(958494922), {});
						}
					}
				}
				this.DispatchEvent(___all_struct.get(958494922), {});
			} else if (this._cancel_select) {
				this._selected = false;
				this.DispatchEvent(___all_struct.get(958494922), {});
			}
			let e = {};
			e.is_drag = event.is_drag;
			e.count = event.count;
			this.DispatchEvent(___all_struct.get(-449066808), e);
			if (ALittle.System_IsPhone() === false) {
				this.ShowOver();
			} else {
				this.ShowUp();
			}
		} else {
			this.ShowUp();
		}
	},
	set selected(value) {
		if (this._selected === value) {
			return;
		}
		this._selected = value;
		if (this._abs_disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp();
		}
		if (this._selected === false) {
			return;
		}
		if (this._group !== undefined) {
			for (let [k, _] of this._group) {
				if (_ === undefined) continue;
				if (k !== this && k._selected === true) {
					k._selected = false;
					k.ShowUp();
				}
			}
		}
	},
}, "ALittle.SpringRadioButton");

}