{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1971745271, "ALittle.DialogDragBeginEvent", {
name : "ALittle.DialogDragBeginEvent", ns_name : "ALittle", rl_name : "DialogDragBeginEvent", hash_code : 1971745271,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1517533145, "ALittle.DialogDragEvent", {
name : "ALittle.DialogDragEvent", ns_name : "ALittle", rl_name : "DialogDragEvent", hash_code : 1517533145,
name_list : ["target","delta_x","delta_y"],
type_list : ["ALittle.DisplayObject","double","double"],
option_map : {}
})
ALittle.RegStruct(-1482649531, "ALittle.DialogDragEndEvent", {
name : "ALittle.DialogDragEndEvent", ns_name : "ALittle", rl_name : "DialogDragEndEvent", hash_code : -1482649531,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.Dialog = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._pickup_rect = true;
		this._pickup_child = true;
		this._title_text = "";
		this._head = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
		this._head_container = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
		this._head_container.width_type = 4;
		this._head_container.height_type = 4;
		this._head.AddChild(this._head_container);
		this._head_left_margin = 0;
		this._head_right_margin = 0;
		this._head_top_margin = 0;
		this._head_bottom_margin = 0;
		this._body = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
		this._grid3 = ALittle.NewObject(ALittle.Grid3, this._ctrl_sys);
		this._grid3.width_type = 4;
		this._grid3.width_value = 0;
		this._grid3.height_type = 4;
		this._grid3.height_value = 0;
		this._grid3.type = 2;
		this._grid3.show_up = this._head;
		this._grid3.show_center = this._body;
		ALittle.DisplayLayout.AddChild.call(this, this._grid3);
	},
	GetChildOffset : function() {
		return [0, this._grid3.up_size];
	},
	set head_size(value) {
		this._grid3.up_size = value;
		if (this._background !== undefined) {
			this._background.height_value = this._grid3.up_size;
		}
		if (this._close_button !== undefined) {
			this._close_button.x_value = (value - this._close_button.height) / 2;
		}
	},
	get head_size() {
		return this._grid3.up_size;
	},
	get head_left_margin() {
		return this._head_left_margin;
	},
	set head_left_margin(value) {
		this._head_left_margin = value;
		this._head_container.x = value;
		this._head_container.width_value = this._head_left_margin + this._head_right_margin;
	},
	get head_right_margin() {
		return this._head_right_margin;
	},
	set head_right_margin(value) {
		this._head_right_margin = value;
		this._head_container.width_value = this._head_left_margin + this._head_right_margin;
	},
	get head_top_margin() {
		return this._head_top_margin;
	},
	set head_top_margin(value) {
		this._head_top_margin = value;
		this._head_container.y = value;
		this._head_container.height_value = this._head_top_margin + this._head_bottom_margin;
	},
	get head_bottom_margin() {
		return this._head_bottom_margin;
	},
	set head_bottom_margin(value) {
		this._head_bottom_margin = value;
		this._head_container.height_value = this._head_top_margin + this._head_bottom_margin;
	},
	set show_background(value) {
		if (this._background !== undefined) {
			ALittle.DisplayLayout.RemoveChild.call(this, this._background);
		}
		this._background = value;
		if (this._background !== undefined) {
			this._background.width_type = 4;
			this._background.width_value = 0;
			this._background.height_type = 4;
			this._background.height_value = this._grid3.up_size;
			this._background.y_type = 4;
			ALittle.DisplayLayout.AddChild.call(this, this._background, 1);
		}
	},
	get show_background() {
		return this._background;
	},
	set show_head_drag(value) {
		if (this._head_drag !== undefined) {
			this._head.RemoveChild(this._head_drag);
			this._head_drag.RemoveEventListener(___all_struct.get(1301789264), this, this.HandleHeadDragBegin);
			this._head_drag.RemoveEventListener(___all_struct.get(1337289812), this, this.HandleHeadDrag);
			this._head_drag.RemoveEventListener(___all_struct.get(150587926), this, this.HandleHeadDragEnd);
		}
		this._head_drag = value;
		if (this._head_drag !== undefined) {
			this._head_drag.width_type = 4;
			this._head_drag.width_value = 0;
			this._head_drag.height_type = 4;
			this._head_drag.height_value = 0;
			this._head.AddChild(this._head_drag, 1);
			this._head_drag.AddEventListener(___all_struct.get(1301789264), this, this.HandleHeadDragBegin);
			this._head_drag.AddEventListener(___all_struct.get(1337289812), this, this.HandleHeadDrag);
			this._head_drag.AddEventListener(___all_struct.get(150587926), this, this.HandleHeadDragEnd);
		}
	},
	get show_head_drag() {
		return this._head_drag;
	},
	set show_title(value) {
		if (this._title !== undefined) {
			this._title_text = this._title.text;
			this._head_container.RemoveChild(this._title);
		}
		this._title = value;
		if (this._title !== undefined) {
			this._title.text = this._title_text;
			this._title.disabled = true;
			this._title.y_type = 3;
			this._title.y_value = 0;
			this._title.x = 0;
			this._head_container.AddChild(this._title);
		}
	},
	get show_title() {
		return this._title;
	},
	set title(value) {
		this._title_text = value;
		if (this._title !== undefined) {
			this._title.text = value;
		}
	},
	get title() {
		if (this._title !== undefined) {
			return this._title.text;
		}
		return this._title_text;
	},
	set show_close_button(value) {
		if (this._close_button !== undefined) {
			this._head_container.RemoveChild(this._close_button);
			this._close_button.RemoveEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClicked);
		}
		this._close_button = value;
		if (this._close_button !== undefined) {
			this._close_button.y_value = 0;
			this._close_button.y_type = 3;
			this._head_container.AddChild(this._close_button);
			this._close_button.x_type = 4;
			this._close_button.x_value = (this._grid3.up_size - this._close_button.height) / 2;
			this._close_button.AddEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClicked);
		}
	},
	get show_close_button() {
		return this._close_button;
	},
	set close_callback(value) {
		this._close_callback = value;
	},
	get close_callback() {
		return this._close_callback;
	},
	HandleCloseButtonClicked : function(event) {
		if (this._close_callback !== undefined && !this._close_callback()) {
			return;
		}
		this.visible = false;
	},
	HandleHeadDragBegin : function(event) {
		this.DispatchEvent(___all_struct.get(1971745271), {});
	},
	HandleHeadDrag : function(event) {
		this.x = this.x + (event.delta_x);
		this.y = this.y + (event.delta_y);
		let new_event = {};
		new_event.target = this;
		new_event.delta_x = event.delta_x;
		new_event.delta_y = event.delta_y;
		this.DispatchEvent(___all_struct.get(1517533145), new_event);
	},
	HandleHeadDragEnd : function(event) {
		this.DispatchEvent(___all_struct.get(-1482649531), {});
	},
	GetChildIndex : function(child) {
		return this._body.GetChildIndex(child);
	},
	SetChildIndex : function(child, index) {
		return this._body.SetChildIndex(child, index);
	},
	GetChildByIndex : function(index) {
		return this._body.GetChildByIndex(index);
	},
	GetChildIndex : function(child) {
		return this._body.GetChildIndex(child);
	},
	get childs() {
		return this._body.childs;
	},
	get child_count() {
		return this._body.child_count;
	},
	AddChild : function(child, index) {
		if (child === undefined || child === this) {
			return false;
		}
		if (child._show_parent === this._body || child._logic_parent === this) {
			return true;
		}
		if (child._logic_parent !== undefined) {
			child._logic_parent.RemoveChild(child);
		} else if (child._show_parent !== undefined) {
			child._show_parent.RemoveChild(child);
		}
		let result = this._body.AddChild(child, index);
		child._logic_parent = this;
		return result;
	},
	RemoveChild : function(child) {
		if (child === undefined) {
			return false;
		}
		if (child._show_parent !== this._body && child._logic_parent !== this) {
			return false;
		}
		let index = this._body.GetChildIndex(child);
		if (index === 0) {
			return false;
		}
		return this._body.RemoveChild(child);
	},
	SpliceChild : function(index, count) {
		return this._body.SpliceChild(index, count);
	},
	HasChild : function(child) {
		return this._body.HasChild(child);
	},
	RemoveAllChild : function() {
		this._body.RemoveAllChild();
	},
}, "ALittle.Dialog");

}