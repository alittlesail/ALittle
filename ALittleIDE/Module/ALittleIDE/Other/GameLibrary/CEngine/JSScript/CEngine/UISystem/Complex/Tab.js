{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-18570489, "ALittle.UITabCloseEvent", {
name : "ALittle.UITabCloseEvent", ns_name : "ALittle", rl_name : "UITabCloseEvent", hash_code : -18570489,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

if (ALittle.Grid3 === undefined) throw new Error(" extends class:ALittle.Grid3 is undefined");
ALittle.Tab = JavaScript.Class(ALittle.Grid3, {
	Ctor : function(ctrl_sys) {
		this._button_inner_gap = 8;
		this._child_id_map = ALittle.CreateKeyWeakMap();
		this._group = ALittle.CreateKeyWeakMap();
		this.type = 2;
		this._view = ALittle.NewObject(ALittle.DisplayView, this._ctrl_sys);
		this._view.height_type = 4;
		this._view.width_type = 4;
		this._linear = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
		this._linear.type = 1;
		this._linear.height_type = 4;
		this._linear.y_type = 4;
		this._view.AddChild(this._linear);
		this._view_start = 0;
		this._view_margin = 0;
		let show_up = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
		show_up.AddChild(this._view);
		this.show_up = show_up;
		this.show_center = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
		this._pickup_rect = true;
		this._pickup_child = true;
		this._tab_index = 0;
		this._child_width_margin = 0;
	},
	RefreshView : function() {
		if (this._radiobutton_style === undefined || this._text_style === undefined || this._closebutton_style === undefined || this._selected_text_style === undefined || this._selected_closebutton_style === undefined) {
			return;
		}
		let child_list = this._linear.childs;
		let ___OBJECT_1 = child_list;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			let childs = v.childs;
			childs[1 - 1].RemoveEventListener(___all_struct.get(958494922), this, this.HandleRadioButtonChanged);
			childs[1 - 1].RemoveEventListener(___all_struct.get(1337289812), this, this.HandleRadioButtonDrag);
			childs[1 - 1].RemoveEventListener(___all_struct.get(1301789264), this, this.HandleRadioButtonDragBegin);
			childs[1 - 1].RemoveEventListener(___all_struct.get(150587926), this, this.HandleRadioButtonDragEnd);
			childs[1 - 1].RemoveEventListener(___all_struct.get(-1330840), this, this.HandleRadioButtonMClick);
			childs[1 - 1].RemoveEventListener(___all_struct.get(-641444818), this, this.HandleRadioButtonRButtonDown);
			childs[1 - 1].RemoveEventListener(___all_struct.get(-1604617962), this, this.HandleRadioButtonKeyDown);
			childs[3 - 1].RemoveEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
			childs[5 - 1].RemoveEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
			childs[1 - 1].group = undefined;
		}
		this._linear.RemoveAllChild();
		let show_center = this.show_center;
		child_list = show_center.childs;
		let ___OBJECT_2 = child_list;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let v = ___OBJECT_2[k - 1];
			if (v === undefined) break;
			let radiobutton = this._ctrl_sys.CreateControl(this._radiobutton_style);
			let text = this._ctrl_sys.CreateControl(this._text_style);
			let closebutton = this._ctrl_sys.CreateControl(this._closebutton_style);
			let selected_text = this._ctrl_sys.CreateControl(this._selected_text_style);
			let selected_closebutton = this._ctrl_sys.CreateControl(this._selected_closebutton_style);
			if (radiobutton !== undefined && text !== undefined && closebutton !== undefined && selected_text !== undefined && selected_closebutton !== undefined) {
				let simplelayout = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
				radiobutton.selected = (this._tab_index === k);
				radiobutton.AddEventListener(___all_struct.get(958494922), this, this.HandleRadioButtonChanged);
				radiobutton.AddEventListener(___all_struct.get(1337289812), this, this.HandleRadioButtonDrag);
				radiobutton.AddEventListener(___all_struct.get(1301789264), this, this.HandleRadioButtonDragBegin);
				radiobutton.AddEventListener(___all_struct.get(150587926), this, this.HandleRadioButtonDragEnd);
				radiobutton.AddEventListener(___all_struct.get(-1330840), this, this.HandleRadioButtonMClick);
				radiobutton.AddEventListener(___all_struct.get(-641444818), this, this.HandleRadioButtonRButtonDown);
				radiobutton.AddEventListener(___all_struct.get(-1604617962), this, this.HandleRadioButtonKeyDown);
				radiobutton.group = this._group;
				radiobutton.width_type = 4;
				radiobutton.height_type = 4;
				v.visible = radiobutton.selected;
				text.text = this._child_id_map.get(v);
				text.disabled = true;
				text.y_type = 3;
				text.y_value = 2;
				text.x = this._button_inner_gap;
				text.visible = !radiobutton.selected;
				selected_text.text = this._child_id_map.get(v);
				selected_text.disabled = true;
				selected_text.y_type = 3;
				selected_text.y_value = 2;
				selected_text.x = this._button_inner_gap;
				selected_text.visible = radiobutton.selected;
				closebutton.AddEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
				closebutton.y_type = 3;
				closebutton.y_value = 2;
				closebutton.x = text.x + text.width + this._button_inner_gap;
				closebutton.visible = !radiobutton.selected;
				selected_closebutton.AddEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
				selected_closebutton.y_type = 3;
				selected_closebutton.y_value = 2;
				selected_closebutton.x = selected_text.x + selected_text.width + this._button_inner_gap;
				selected_closebutton.visible = radiobutton.selected;
				simplelayout.width = this._button_inner_gap * 3 + text.width + closebutton.width;
				this._linear.AddChild(simplelayout);
				simplelayout.AddChild(radiobutton);
				simplelayout.AddChild(text);
				simplelayout.AddChild(closebutton);
				simplelayout.AddChild(selected_text);
				simplelayout.AddChild(selected_closebutton);
			}
		}
	},
	set radiobutton_style(value) {
		if (this._radiobutton_style === value) {
			return;
		}
		this._radiobutton_style = value;
		this.RefreshView();
	},
	get radiobutton_style() {
		return this._radiobutton_style;
	},
	set closebutton_style(value) {
		if (this._closebutton_style === value) {
			return;
		}
		this._closebutton_style = value;
		this.RefreshView();
	},
	get closebutton_style() {
		return this._closebutton_style;
	},
	set selected_closebutton_style(value) {
		if (this._selected_closebutton_style === value) {
			return;
		}
		this._selected_closebutton_style = value;
		this.RefreshView();
	},
	get selected_closebutton_style() {
		return this._selected_closebutton_style;
	},
	set text_style(value) {
		if (this._text_style === value) {
			return;
		}
		this._text_style = value;
		this.RefreshView();
	},
	get text_style() {
		return this._text_style;
	},
	set selected_text_style(value) {
		if (this._selected_text_style === value) {
			return;
		}
		this._selected_text_style = value;
		this.RefreshView();
	},
	get selected_text_style() {
		return this._selected_text_style;
	},
	set show_head_background(value) {
		if (this._head_background !== undefined) {
			this._view.RemoveChild(this._head_background);
		}
		this._head_background = value;
		if (this._head_background !== undefined) {
			this._head_background.width_type = 4;
			this._head_background.width_value = 0;
			this._head_background.height_type = 4;
			this._head_background.height_value = 0;
			this._view.AddChild(this._head_background, 1);
		}
	},
	get show_head_background() {
		return this._head_background;
	},
	set button_gap(value) {
		this._linear.gap = value;
	},
	get button_gap() {
		return this._linear.gap;
	},
	set button_start(value) {
		this._view.x = value;
	},
	get button_start() {
		return this._view.x;
	},
	set button_margin(value) {
		this._linear.height_value = value;
	},
	get button_margin() {
		return this._linear.height_value;
	},
	set child_width_margin(value) {
		this._child_width_margin = value;
		let show_center = this.show_center;
		let childs = show_center.childs;
		let ___OBJECT_3 = childs;
		for (let k = 1; k <= ___OBJECT_3.length; ++k) {
			let v = ___OBJECT_3[k - 1];
			if (v === undefined) break;
			v.width_value = this._child_width_margin;
		}
	},
	get child_width_margin() {
		return this._child_width_margin;
	},
	set head_size(value) {
		this.up_size = value;
	},
	get head_size() {
		return this.up_size;
	},
	set close_callback(value) {
		this._close_callback = value;
	},
	get close_callback() {
		return this._close_callback;
	},
	set close_post_callback(value) {
		this._close_post_callback = value;
	},
	get close_post_callback() {
		return this._close_post_callback;
	},
	set drag_callback(value) {
		this._drag_callback = value;
	},
	get drag_callback() {
		return this._drag_callback;
	},
	set drag_post_callback(value) {
		this._drag_post_callback = value;
	},
	get drag_post_callback() {
		return this._drag_post_callback;
	},
	get view_margin() {
		return this._view.width_value;
	},
	set view_margin(value) {
		this._view.width_value = value;
	},
	get view() {
		return this._view;
	},
	get view_linear() {
		return this._linear;
	},
	GetChildIndex : function(child) {
		return this.show_center.GetChildIndex(child);
	},
	SetChildIndex : function(child, index) {
		let show_center = this.show_center;
		let cur_index = show_center.GetChildIndex(child);
		if (index > show_center.child_count) {
			index = show_center.child_count;
		}
		if (cur_index === index) {
			return true;
		}
		let linear = this._linear;
		let linear_childs = linear.childs;
		let tab_child = this.tab;
		let button_child = linear_childs[cur_index - 1];
		if (button_child !== undefined) {
			linear.SetChildIndex(button_child, index);
		}
		let show_center_childs = show_center.childs;
		let body_child = show_center_childs[cur_index - 1];
		show_center.SetChildIndex(body_child, index);
		this._tab_index = show_center.GetChildIndex(tab_child);
		return true;
	},
	GetChildByIndex : function(index) {
		return this.show_center.GetChildByIndex(index);
	},
	GetChildIndex : function(child) {
		return this.show_center.GetChildIndex(child);
	},
	get childs() {
		let show_center = this.show_center;
		return show_center.childs;
	},
	get child_count() {
		let show_center = this.show_center;
		return show_center.child_count;
	},
	AddChild : function(child, index) {
		if (child === undefined || child === this) {
			return false;
		}
		if (child._show_parent === this.show_center || child._logic_parent === this) {
			return true;
		}
		if (child._logic_parent !== undefined) {
			child._logic_parent.RemoveChild(child);
		} else if (child._show_parent !== undefined) {
			child._show_parent.RemoveChild(child);
		}
		let show_center = this.show_center;
		show_center.AddChild(child, index);
		child._logic_parent = this;
		child.x = 0;
		child.y = 0;
		child.width_type = 4;
		child.width_value = this._child_width_margin;
		child.height_type = 4;
		child.height_value = 0;
		child.x_type = 4;
		this._child_id_map.set(child, child.description);
		if (this._child_id_map.get(child) === undefined) {
			this._child_id_map.set(child, "");
		}
		if (this._radiobutton_style === undefined || this._text_style === undefined || this._closebutton_style === undefined || this._selected_text_style === undefined || this._selected_closebutton_style === undefined) {
			return true;
		}
		let radiobutton = this._ctrl_sys.CreateControl(this._radiobutton_style);
		let text = this._ctrl_sys.CreateControl(this._text_style);
		let closebutton = this._ctrl_sys.CreateControl(this._closebutton_style);
		let selected_text = this._ctrl_sys.CreateControl(this._selected_text_style);
		let selected_closebutton = this._ctrl_sys.CreateControl(this._selected_closebutton_style);
		if (radiobutton !== undefined && text !== undefined && closebutton !== undefined && selected_text !== undefined && selected_closebutton !== undefined) {
			let simplelayout = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
			radiobutton.AddEventListener(___all_struct.get(958494922), this, this.HandleRadioButtonChanged);
			radiobutton.AddEventListener(___all_struct.get(1337289812), this, this.HandleRadioButtonDrag);
			radiobutton.AddEventListener(___all_struct.get(1301789264), this, this.HandleRadioButtonDragBegin);
			radiobutton.AddEventListener(___all_struct.get(150587926), this, this.HandleRadioButtonDragEnd);
			radiobutton.AddEventListener(___all_struct.get(-1330840), this, this.HandleRadioButtonMClick);
			radiobutton.AddEventListener(___all_struct.get(-641444818), this, this.HandleRadioButtonRButtonDown);
			radiobutton.AddEventListener(___all_struct.get(-1604617962), this, this.HandleRadioButtonKeyDown);
			radiobutton.group = this._group;
			radiobutton.width_type = 4;
			radiobutton.width_value = 0;
			radiobutton.height_type = 4;
			radiobutton.height_value = 0;
			child.visible = radiobutton.selected;
			text.text = this._child_id_map.get(child);
			text.disabled = true;
			text.y_type = 3;
			text.y_value = 2;
			text.x = this._button_inner_gap;
			text.visible = !radiobutton.selected;
			selected_text.text = this._child_id_map.get(child);
			selected_text.disabled = true;
			selected_text.y_type = 3;
			selected_text.y_value = 2;
			selected_text.x = this._button_inner_gap;
			selected_text.visible = radiobutton.selected;
			closebutton.AddEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
			closebutton.y_type = 3;
			closebutton.y_value = 2;
			closebutton.x = text.x + text.width + this._button_inner_gap;
			closebutton.visible = !radiobutton.selected;
			selected_closebutton.AddEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
			selected_closebutton.y_type = 3;
			selected_closebutton.y_value = 2;
			selected_closebutton.x = selected_text.x + selected_text.width + this._button_inner_gap;
			selected_closebutton.visible = radiobutton.selected;
			simplelayout.width = this._button_inner_gap * 3 + text.width + closebutton.width;
			this._linear.AddChild(simplelayout, index);
			simplelayout.AddChild(radiobutton);
			simplelayout.AddChild(text);
			simplelayout.AddChild(closebutton);
			simplelayout.AddChild(selected_text);
			simplelayout.AddChild(selected_closebutton);
		}
		if (this._tab_index <= 0) {
			this.tab_index = 1;
		} else if (index !== undefined && this._tab_index >= index) {
			this._tab_index = this._tab_index + 1;
		}
		return true;
	},
	RemoveChild : function(child) {
		if (child === undefined) {
			return false;
		}
		if (child._show_parent !== this.show_center && child._logic_parent !== this) {
			return false;
		}
		let show_center = this.show_center;
		let index = show_center.GetChildIndex(child);
		if (index === 0) {
			return false;
		}
		show_center.RemoveChild(child);
		child.visible = true;
		this._child_id_map.delete(child);
		let simplelayout = this._linear.GetChildByIndex(index);
		if (simplelayout !== undefined) {
			let layout_childs = simplelayout.childs;
			layout_childs[1 - 1].RemoveEventListener(___all_struct.get(958494922), this, this.HandleRadioButtonChanged);
			layout_childs[1 - 1].RemoveEventListener(___all_struct.get(1337289812), this, this.HandleRadioButtonDrag);
			layout_childs[1 - 1].RemoveEventListener(___all_struct.get(1301789264), this, this.HandleRadioButtonDragBegin);
			layout_childs[1 - 1].RemoveEventListener(___all_struct.get(150587926), this, this.HandleRadioButtonDragEnd);
			layout_childs[1 - 1].RemoveEventListener(___all_struct.get(-1330840), this, this.HandleRadioButtonMClick);
			layout_childs[1 - 1].RemoveEventListener(___all_struct.get(-641444818), this, this.HandleRadioButtonRButtonDown);
			layout_childs[1 - 1].RemoveEventListener(___all_struct.get(-1604617962), this, this.HandleRadioButtonKeyDown);
			layout_childs[3 - 1].RemoveEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
			layout_childs[5 - 1].RemoveEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
			layout_childs[1 - 1].group = undefined;
			this._linear.RemoveChild(simplelayout);
		}
		let new_index = 0;
		if (this._tab_index === index) {
			new_index = index;
		} else if (this._tab_index > index) {
			new_index = this._tab_index - 1;
		} else {
			new_index = this._tab_index;
		}
		if (new_index > show_center.child_count) {
			new_index = show_center.child_count;
		} else if (new_index < 0) {
			new_index = 0;
		}
		this.tab_index = new_index;
		return true;
	},
	SpliceChild : function(index, count) {
		let remain_count = this._child_count - index + 1;
		if (count === undefined) {
			count = remain_count;
		}
		if (count <= 0) {
			return 0;
		}
		if (count > remain_count) {
			count = remain_count;
		}
		let show_center = this.show_center;
		let endv = index + count;
		for (let i = index; i < endv; i += 1) {
			let child = show_center.GetChildByIndex(i);
			if (child === undefined) {
				break;
			}
			child.visible = true;
			this._child_id_map.delete(child);
			let simplelayout = this._linear.GetChildByIndex(index);
			if (simplelayout !== undefined) {
				let layout_childs = simplelayout.childs;
				layout_childs[1 - 1].RemoveEventListener(___all_struct.get(958494922), this, this.HandleRadioButtonChanged);
				layout_childs[1 - 1].RemoveEventListener(___all_struct.get(1337289812), this, this.HandleRadioButtonDrag);
				layout_childs[1 - 1].RemoveEventListener(___all_struct.get(1301789264), this, this.HandleRadioButtonDragBegin);
				layout_childs[1 - 1].RemoveEventListener(___all_struct.get(150587926), this, this.HandleRadioButtonDragEnd);
				layout_childs[1 - 1].RemoveEventListener(___all_struct.get(-1330840), this, this.HandleRadioButtonMClick);
				layout_childs[1 - 1].RemoveEventListener(___all_struct.get(-641444818), this, this.HandleRadioButtonRButtonDown);
				layout_childs[1 - 1].RemoveEventListener(___all_struct.get(-1604617962), this, this.HandleRadioButtonKeyDown);
				layout_childs[3 - 1].RemoveEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
				layout_childs[5 - 1].RemoveEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
				layout_childs[1 - 1].group = undefined;
			}
		}
		this._linear.SpliceChild(index, count);
		let result = show_center.SpliceChild(index, count);
		let new_index = 0;
		if (this._tab_index >= index && this._tab_index < endv) {
			new_index = index;
		} else if (this._tab_index >= endv) {
			new_index = this._tab_index - result;
		} else {
			new_index = this._tab_index;
		}
		if (new_index > show_center.child_count) {
			new_index = show_center.child_count;
		} else if (new_index < 0) {
			new_index = 0;
		}
		this.tab_index = new_index;
		return result;
	},
	HasChild : function(child) {
		let show_center = this.show_center;
		return show_center.HasChild(child);
	},
	RemoveAllChild : function() {
		this._linear.RemoveAllChild();
		let show_center = this.show_center;
		let childs = show_center.childs;
		let ___OBJECT_4 = childs;
		for (let k = 1; k <= ___OBJECT_4.length; ++k) {
			let v = ___OBJECT_4[k - 1];
			if (v === undefined) break;
			v.visible = true;
		}
		show_center.RemoveAllChild();
		this._child_id_map = new Map();
		this._tab_index = 0;
	},
	HandleRadioButtonChanged : function(event) {
		let button = event.target;
		if (button.selected) {
			let show_center = this.show_center;
			let childs = show_center.childs;
			let ___OBJECT_5 = childs;
			for (let k = 1; k <= ___OBJECT_5.length; ++k) {
				let v = ___OBJECT_5[k - 1];
				if (v === undefined) break;
				v.visible = false;
			}
			let simplelayout = button.parent;
			let index = this._linear.GetChildIndex(simplelayout);
			let show_center_childs = show_center.childs;
			show_center_childs[index - 1].visible = true;
			let layout_childs = simplelayout.childs;
			layout_childs[3 - 1].visible = false;
			layout_childs[2 - 1].visible = false;
			if (layout_childs[5 - 1].disabled === false) {
				layout_childs[5 - 1].visible = true;
			}
			layout_childs[4 - 1].visible = true;
			this._tab_index = index;
			this.DispatchEvent(___all_struct.get(444989011), {});
		} else {
			let simplelayout = button.parent;
			let layout_childs = simplelayout.childs;
			if (layout_childs[3 - 1].disabled === false) {
				layout_childs[3 - 1].visible = true;
			}
			layout_childs[2 - 1].visible = true;
			layout_childs[5 - 1].visible = false;
			layout_childs[4 - 1].visible = false;
		}
	},
	HandleCloseButtonClick : function(event) {
		let simplelayout = event.target._show_parent;
		let index = this._linear.GetChildIndex(simplelayout);
		let show_center = this.show_center;
		let show_center_childs = show_center.childs;
		let child = show_center_childs[index - 1];
		if (this._close_callback !== undefined && this._close_callback(child) === false) {
			return;
		}
		this.RemoveChild(child);
		this.DispatchEvent(___all_struct.get(-18570489), {});
		if (this._close_post_callback !== undefined) {
			this._close_post_callback(child);
		}
	},
	HandleRadioButtonDragBegin : function(event) {
		let simplelayout = event.target._show_parent;
		let control_x = undefined;
		let control_y = undefined;
		[control_x, control_y] = simplelayout.LocalToGlobal();
		this._tab_image = ALittle.NewObject(ALittle.EffectImage, this._ctrl_sys);
		this._tab_image.Action(simplelayout);
		A_LayerManager.AddToTip(this._tab_image);
		this._tab_image.x = control_x;
		this._tab_image.y = control_y;
		this._tab_image.alpha = 0.9;
	},
	HandleRadioButtonDrag : function(event) {
		if (this._tab_image === undefined) {
			return;
		}
		this._tab_image.x = this._tab_image.x + event.delta_x;
		this._tab_image.y = this._tab_image.y + event.delta_y;
	},
	HandleRadioButtonDragEnd : function(event) {
		let target_index = this._linear.child_count;
		if (this._scale_x > 0) {
			let linear_x = undefined;
			let linear_y = undefined;
			[linear_x, linear_y] = this._linear.LocalToGlobal();
			let delta_x = (event.abs_x - linear_x) / this._scale_x;
			let child_list = this._linear.childs;
			let ___OBJECT_6 = child_list;
			for (let k = 1; k <= ___OBJECT_6.length; ++k) {
				let v = ___OBJECT_6[k - 1];
				if (v === undefined) break;
				if (delta_x < v.x + v.width / 2) {
					target_index = k;
					break;
				}
			}
		}
		let simplelayout = event.target._show_parent;
		let index = this._linear.GetChildIndex(simplelayout);
		let show_center = this.show_center;
		let show_center_childs = show_center.childs;
		let child = show_center_childs[index - 1];
		if (this._drag_callback !== undefined && this._drag_callback(child, target_index) === false) {
			return;
		}
		this._linear.SetChildIndex(simplelayout, target_index);
		show_center.SetChildIndex(child, target_index);
		if (this._drag_post_callback !== undefined) {
			this._drag_post_callback(child);
		}
		if (this._tab_image !== undefined) {
			A_LayerManager.RemoveFromTip(this._tab_image);
			this._tab_image.Clear();
			this._tab_image = undefined;
		}
	},
	HandleRadioButtonMClick : function(event) {
		let simplelayout = event.target._show_parent;
		let layout_childs = simplelayout.childs;
		if (layout_childs[3 - 1].disabled && layout_childs[5 - 1].disabled) {
			return;
		}
		let index = this._linear.GetChildIndex(simplelayout);
		let show_center = this.show_center;
		let show_center_childs = show_center.childs;
		let child = show_center_childs[index - 1];
		if (this._close_callback !== undefined && this._close_callback(child) === false) {
			return;
		}
		this.RemoveChild(child);
		this.DispatchEvent(___all_struct.get(-18570489), {});
		if (this._close_post_callback !== undefined) {
			this._close_post_callback(child);
		}
	},
	HandleRadioButtonRButtonDown : function(event) {
		let simplelayout = event.target._show_parent;
		let index = this._linear.GetChildIndex(simplelayout);
		let show_center = this.show_center;
		let show_center_childs = show_center.childs;
		let child = show_center_childs[index - 1];
		let e = {};
		e.target = child;
		this.DispatchEvent(___all_struct.get(-641444818), e);
	},
	HandleRadioButtonKeyDown : function(event) {
		let simplelayout = event.target._show_parent;
		let index = this._linear.GetChildIndex(simplelayout);
		let show_center = this.show_center;
		let show_center_childs = show_center.childs;
		let child = show_center_childs[index - 1];
		let e = {};
		e.target = child;
		e.mod = event.mod;
		e.sym = event.sym;
		e.scancode = event.scancode;
		this.DispatchEvent(___all_struct.get(-1604617962), e);
		event.handled = e.handled;
	},
	SetChildText : function(child, text) {
		if (this._radiobutton_style === undefined) {
			return;
		}
		let show_center = this.show_center;
		let index = show_center.GetChildIndex(child);
		if (index === 0) {
			return;
		}
		let simplelayout = this._linear.GetChildByIndex(index);
		if (simplelayout !== undefined) {
			let childs = simplelayout.childs;
			let text_control = childs[2 - 1];
			let closebutton = childs[3 - 1];
			let selected_text_control = childs[4 - 1];
			let selected_closebutton = childs[5 - 1];
			text_control.text = text;
			selected_text_control.text = text;
			closebutton.x = text_control.x + text_control.width + this._button_inner_gap;
			selected_closebutton.x = selected_text_control.x + selected_text_control.width + this._button_inner_gap;
			simplelayout.width = this._button_inner_gap * 3 + text_control.width + closebutton.width;
			this._child_id_map.set(child, text);
			this._linear.Layout(1);
		}
	},
	GetChildText : function(child) {
		return this._child_id_map.get(child);
	},
	HasChildText : function(text) {
		for (let [k, v] of this._child_id_map) {
			if (v === undefined) continue;
			if (v === text) {
				return true;
			}
		}
		return false;
	},
	GetChildByText : function(text) {
		for (let [k, v] of this._child_id_map) {
			if (v === undefined) continue;
			if (v === text) {
				return k;
			}
		}
		return undefined;
	},
	set tab(child) {
		let show_center = this.show_center;
		let index = show_center.GetChildIndex(child);
		if (index === 0) {
			return;
		}
		this.tab_index = index;
	},
	get tab() {
		let show_center = this.show_center;
		let show_center_childs = show_center.childs;
		return show_center_childs[this._tab_index - 1];
	},
	set tab_index(index) {
		let show_center = this.show_center;
		let show_center_childs = show_center.childs;
		if (this._tab_index !== 0) {
			let cur_child = show_center_childs[this._tab_index - 1];
			if (cur_child !== undefined) {
				cur_child.visible = false;
			}
			let simplelayout = this._linear.GetChildByIndex(this._tab_index);
			if (simplelayout !== undefined) {
				let childs = simplelayout.childs;
				childs[1 - 1].selected = false;
				childs[2 - 1].visible = true;
				if (childs[3 - 1].disabled === false) {
					childs[3 - 1].visible = true;
				}
				childs[4 - 1].visible = false;
				childs[5 - 1].visible = false;
			}
			this._tab_index = 0;
		}
		this._tab_index = index;
		if (this._tab_index !== 0) {
			let child = show_center_childs[this._tab_index - 1];
			if (child === undefined) {
				return;
			}
			child.visible = true;
			let simplelayout = this._linear.GetChildByIndex(this._tab_index);
			if (simplelayout !== undefined) {
				let childs = simplelayout.childs;
				childs[1 - 1].selected = true;
				childs[2 - 1].visible = false;
				childs[3 - 1].visible = false;
				childs[4 - 1].visible = true;
				if (childs[5 - 1].disabled === false) {
					childs[5 - 1].visible = true;
				}
			}
		}
		if (this._tab_index < 1 || this._tab_index > show_center.child_count) {
			this._tab_index = 0;
		}
	},
	get tab_index() {
		return this._tab_index;
	},
	DisableCloseButton : function(child) {
		let show_center = this.show_center;
		let index = show_center.GetChildIndex(child);
		if (index === 0) {
			return;
		}
		let linear_childs = this._linear.childs;
		let simplelayout = linear_childs[index - 1];
		if (simplelayout === undefined) {
			return;
		}
		let layout_childs = simplelayout.childs;
		layout_childs[3 - 1].visible = false;
		layout_childs[3 - 1].disabled = true;
		layout_childs[2 - 1].x_type = 3;
		layout_childs[2 - 1].x_value = 0;
		layout_childs[5 - 1].visible = false;
		layout_childs[5 - 1].disabled = true;
		layout_childs[4 - 1].x_type = 3;
		layout_childs[4 - 1].x_value = 0;
	},
	DisableAllCloseButton : function() {
		let show_center = this.show_center;
		let count = show_center.child_count;
		let linear_childs = this._linear.childs;
		for (let index = 1; index <= count; index += 1) {
			let simplelayout = linear_childs[index - 1];
			if (simplelayout === undefined) {
				return;
			}
			let layout_childs = simplelayout.childs;
			layout_childs[3 - 1].visible = false;
			layout_childs[3 - 1].disabled = true;
			layout_childs[2 - 1].x_type = 3;
			layout_childs[2 - 1].x_value = 0;
			layout_childs[5 - 1].visible = false;
			layout_childs[5 - 1].disabled = true;
			layout_childs[4 - 1].x_type = 3;
			layout_childs[4 - 1].x_value = 0;
		}
	},
	EnableCloseButton : function(child) {
		let show_center = this.show_center;
		let index = show_center.GetChildIndex(child);
		if (index === 0) {
			return;
		}
		let linear_childs = this._linear.childs;
		let simplelayout = linear_childs[index - 1];
		if (simplelayout === undefined) {
			return;
		}
		let layout_childs = simplelayout.childs;
		layout_childs[3 - 1].visible = !layout_childs[1 - 1].selected;
		layout_childs[3 - 1].disabled = false;
		layout_childs[2 - 1].x_type = 1;
		layout_childs[2 - 1].x = this._button_inner_gap;
		layout_childs[5 - 1].visible = layout_childs[1 - 1].selected;
		layout_childs[5 - 1].disabled = false;
		layout_childs[4 - 1].x_type = 1;
		layout_childs[4 - 1].x = this._button_inner_gap;
	},
	GetChildHead : function(child) {
		let show_center = this.show_center;
		let index = show_center.GetChildIndex(child);
		if (index === 0) {
			return undefined;
		}
		let linear_childs = this._linear.childs;
		return linear_childs[index - 1];
	},
}, "ALittle.Tab");

}