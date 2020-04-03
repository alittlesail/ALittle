{
if (typeof ALittle === "undefined") ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


ALittle.TextRadioButtonManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._name_map_group = {};
		this._group_id = 0;
	},
	CreateGroupName : function() {
		++ this._group_id;
		return "__TextRadioButtonManager_" + this._group_id;
	},
	SetGroupName : function(object, old_name, new_name) {
		if (old_name !== undefined) {
			let group = this._name_map_group[old_name];
			if (group !== undefined) {
				group.delete(object);
			}
		}
		if (new_name !== undefined) {
			let group = this._name_map_group[new_name];
			if (group === undefined) {
				group = new Map();
				this._name_map_group[new_name] = group;
			}
			group.set(object, object);
		}
	},
	GetGroupByName : function(name) {
		return this._name_map_group[name];
	},
}, "ALittle.TextRadioButtonManager");

window.A_TextRadioButtonManager = ALittle.NewObject(ALittle.TextRadioButtonManager);
if (ALittle.TextCheckButton === undefined) throw new Error(" extends class:ALittle.TextCheckButton is undefined");
ALittle.TextRadioButton = JavaScript.Class(ALittle.TextCheckButton, {
	Ctor : function(ctrl_sys) {
		this._group_name = undefined;
	},
	set group_name(name) {
		A_TextRadioButtonManager.SetGroupName(this, this._group_name, name);
		this._group_name = name;
	},
	get group_name() {
		return this._group_name;
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			if (this._selected === false) {
				this._selected = true;
				let group = A_TextRadioButtonManager.GetGroupByName(this._group_name);
				if (group !== undefined) {
					for (let [k, v] of group) {
						if (v === undefined) continue;
						if (k !== this && v._selected === true) {
							v._selected = false;
							v.ShowUp();
							v.DispatchEvent(___all_struct.get(958494922), {});
						}
					}
				}
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
			for (let [k, v] of group) {
				if (v === undefined) continue;
				if (k !== this && v._selected === true) {
					v._selected = false;
					v.ShowUp();
				}
			}
		}
	},
}, "ALittle.TextRadioButton");

}