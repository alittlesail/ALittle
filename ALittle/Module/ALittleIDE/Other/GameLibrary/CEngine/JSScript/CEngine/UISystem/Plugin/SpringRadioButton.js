{
if (typeof ALittle === "undefined") ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.SpringCheckButton === undefined) throw new Error(" extends class:ALittle.SpringCheckButton is undefined");
ALittle.SpringRadioButton = JavaScript.Class(ALittle.SpringCheckButton, {
	Ctor : function(ctrl_sys) {
		this._cancel_select = false;
	},
	set group_name(value) {
		A_TextRadioButtonManager.SetGroupName(this, this._group_name, value);
		this._group_name = value;
	},
	get group_name() {
		return this._group_name;
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
				let group = A_TextRadioButtonManager.GetGroupByName(this._group_name);
				if (group !== undefined) {
					for (let [k, _] of group) {
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
			this.DispatchEvent(___all_struct.get(-449066808), e);
			if (ALittle.System_IsPhone === false) {
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
		let group = A_TextRadioButtonManager.GetGroupByName(this._group_name);
		if (group !== undefined) {
			for (let [k, _] of group) {
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