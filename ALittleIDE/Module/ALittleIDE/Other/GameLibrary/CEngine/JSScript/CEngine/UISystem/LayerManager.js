{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


ALittle.LayerManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._normal_groups = [];
		this._normal_group_count = 0;
		this._modal_layer = ALittle.NewObject(ALittle.DisplayLayout, undefined);
		A_JDisplaySystem.AddSpecialChild(this._modal_layer.native_show);
		this._right_layer = ALittle.NewObject(ALittle.DisplayLayout, undefined);
		this._right_show = undefined;
		A_JDisplaySystem.AddSpecialChild(this._right_layer.native_show);
		this._tip_layer = ALittle.NewObject(ALittle.DisplayLayout, undefined);
		this._tip_layer.disabled = true;
		A_JDisplaySystem.AddSpecialChild(this._tip_layer.native_show);
	},
	Shutdown : function() {
		A_JDisplaySystem.RemoveAllChild();
	},
	get group_count() {
		return this._normal_group_count;
	},
	AddChild : function(child, index) {
		if (child === undefined) {
			return;
		}
		if (index === undefined || index > this._normal_group_count || this._normal_group_count < 1) {
			++ this._normal_group_count;
			this._normal_groups[this._normal_group_count - 1] = child;
			A_JDisplaySystem.AddChild(child.native_show);
		} else {
			if (index < 1) {
				index = 1;
			}
			let back_child = this._normal_groups[index - 1];
			A_JDisplaySystem.AddChildBefore(back_child.native_show, child.native_show);
			ALittle.List_Insert(this._normal_groups, index, child);
			++ this._normal_group_count;
		}
		child.width = A_UISystem.view_width;
		child.height = A_UISystem.view_height;
	},
	RemoveChild : function(child) {
		if (child === undefined) {
			return;
		}
		let has_layer = false;
		let ___OBJECT_1 = this._normal_groups;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let value = ___OBJECT_1[index - 1];
			if (value === undefined) break;
			if (value === child) {
				ALittle.List_Remove(this._normal_groups, index);
				has_layer = true;
				break;
			}
		}
		if (has_layer === false) {
			return;
		}
		A_JDisplaySystem.RemoveChild(child.native_show);
		-- this._normal_group_count;
	},
	HandleViewResized : function(width, height) {
		let ___OBJECT_2 = this._normal_groups;
		for (let group_index = 1; group_index <= ___OBJECT_2.length; ++group_index) {
			let group = ___OBJECT_2[group_index - 1];
			if (group === undefined) break;
			group.width = width;
			group.height = height;
		}
		this._modal_layer.width = width;
		this._modal_layer.height = height;
		this._right_layer.width = width;
		this._right_layer.height = height;
		this._tip_layer.width = width;
		this._tip_layer.height = height;
		this.HideCurrentFromRight();
	},
	AddToModal : function(dialog, index) {
		if (dialog === undefined) {
			return;
		}
		dialog.x_type = 3;
		dialog.x_value = 0;
		dialog.y_type = 3;
		dialog.y_value = 0;
		dialog.modal = true;
		dialog.visible = false;
		this._modal_layer.AddChild(dialog, index);
	},
	RemoveFromModal : function(dialog) {
		if (dialog === undefined) {
			return;
		}
		dialog.modal = false;
		dialog.visible = true;
		this._modal_layer.RemoveChild(dialog);
	},
	ShowFromRight : function(dialog, focus) {
		if (focus === undefined) {
			focus = true;
		}
		if (this._right_show === dialog) {
			return;
		}
		if (this._right_show !== undefined) {
			this._right_show.DispatchEvent(___all_struct.get(348388800), {});
			this._right_layer.RemoveChild(this._right_show);
			this._right_show = undefined;
		}
		this._right_show = dialog;
		if (this._right_show !== undefined) {
			this._right_layer.AddChild(this._right_show);
			if (focus) {
				this._right_show.focus = true;
			}
			dialog.DispatchEvent(___all_struct.get(1862557463), {});
			dialog.visible = true;
		}
	},
	HideFromRight : function(dialog) {
		if (this._right_show !== dialog) {
			return;
		}
		if (this._right_show === undefined) {
			return;
		}
		this._right_show.DispatchEvent(___all_struct.get(348388800), {});
		this._right_layer.RemoveChild(this._right_show);
		this._right_show.focus = false;
		this._right_show = undefined;
	},
	HideCurrentFromRight : function() {
		if (this._right_show === undefined) {
			return false;
		}
		this.HideFromRight(this._right_show);
		return true;
	},
	IsCurrentRight : function(dialog) {
		return this._right_show === dialog;
	},
	AddToTip : function(dialog) {
		this._tip_layer.AddChild(dialog);
	},
	RemoveFromTip : function(dialog) {
		this._tip_layer.RemoveChild(dialog);
	},
	PickUp : function(x, y) {
		let mfc_rel_x = undefined;
		let mfc_rel_y = undefined;
		let mfc = undefined;
		let mfd = undefined;
		[mfc, mfc_rel_x, mfc_rel_y] = this._right_layer.PickUp(x, y);
		if (mfc !== undefined) {
			return [mfc, undefined, mfc_rel_x, mfc_rel_y];
		}
		[mfc, mfc_rel_x, mfc_rel_y] = this._modal_layer.PickUp(x, y);
		if (mfc !== undefined) {
			return [mfc, undefined, mfc_rel_x, mfc_rel_y];
		}
		let normal_groups = this._normal_groups;
		for (let group_index = this._normal_group_count; group_index > 0; group_index += -1) {
			let normal_layers = normal_groups[group_index - 1];
			let layer_list = normal_layers.childs;
			for (let layer_index = normal_layers.child_count; layer_index > 0; layer_index += -1) {
				let layer = layer_list[layer_index - 1];
				[mfc, mfd, mfc_rel_x, mfc_rel_y] = this.LayerPickup(layer, x, y);
				if (mfc !== undefined) {
					return [mfc, mfd, mfc_rel_x, mfc_rel_y];
				}
			}
		}
		return [undefined, undefined, undefined, undefined];
	},
	LayerPickup : function(layer, x, y) {
		let mfc_rel_x = undefined;
		let mfc_rel_y = undefined;
		let mfc = undefined;
		let mfd = undefined;
		if (layer.visible && layer.disabled === false && layer.childs !== undefined) {
			let rel_x = x - layer.x;
			let rel_y = y - layer.y;
			let child_list = layer.childs;
			for (let index = layer.child_count; index > 0; index += -1) {
				let dialog = child_list[index - 1];
				[mfc, mfc_rel_x, mfc_rel_y] = dialog.PickUp(rel_x, rel_y);
				if (mfc !== undefined) {
					mfd = dialog;
					break;
				}
			}
		}
		return [mfc, mfd, mfc_rel_x, mfc_rel_y];
	},
	HandleLRButtonDown : function(x, y) {
		if (this._right_show === undefined) {
			return;
		}
		let [left, top] = this._right_show.LocalToGlobal();
		let right = this._right_show.width * this._right_show.scale_x + left;
		let bottom = this._right_show.height * this._right_show.scale_y + top;
		if (x >= left && x < right && y >= top && y < bottom) {
			return;
		}
		let link_control = this._right_show.__right_data;
		if (link_control !== undefined) {
			let [abs_x, abs_y] = link_control.LocalToGlobal();
			if (x >= abs_x && x < abs_x + link_control.width * link_control.scale_x && y >= abs_y && y < abs_y + link_control.height * link_control.scale_y) {
				return;
			}
		}
		this._right_show.DispatchEvent(___all_struct.get(348388800), {});
		this._right_show.visible = false;
		this._right_show = undefined;
	},
}, "ALittle.LayerManager");

window.A_LayerManager = ALittle.NewObject(ALittle.LayerManager);
}