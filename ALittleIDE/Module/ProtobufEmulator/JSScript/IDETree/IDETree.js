{
if (typeof Emulator === "undefined") window.Emulator = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name : "ALittle.UIResizeEvent", ns_name : "ALittle", rl_name : "UIResizeEvent", hash_code : -431205740,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

if (Emulator.IDETreeLogic === undefined) throw new Error(" extends class:Emulator.IDETreeLogic is undefined");
Emulator.IDETree = JavaScript.Class(Emulator.IDETreeLogic, {
	Ctor : function(ctrl_sys, root) {
		this._body = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
		this._body.type = 2;
		this._body.x = 8;
		ALittle.DisplayGroup.AddChild.call(this, this._body);
		this._body.AddEventListener(___all_struct.get(-431205740), this, this.HandleChildResize);
	},
	Init : function() {
		this._body.y = this._head.height;
		this._body.width = this._head.width;
		this._item_checkbutton.selected = true;
		this._pickup_rect = false;
		this._pickup_child = true;
		this.fold = false;
		this._upper_description = ALittle.String_Upper(this._item_title.text);
	},
	HandleLButtonDown : function(event) {
		if (event.count === 1) {
			return;
		}
		this.fold = !this.fold;
	},
	IsTree : function() {
		return true;
	},
	SearchBegin : function() {
		this.fold = false;
		this.light = false;
		let ___OBJECT_1 = this._body.childs;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let child = ___OBJECT_1[k - 1];
			if (child === undefined) break;
			child.SearchBegin();
		}
	},
	SearchDescription : function(name, list) {
		if (list === undefined) {
			list = [];
		}
		if (ALittle.String_Find(this._upper_description, name) !== undefined) {
			ALittle.List_Push(list, this);
		}
		let ___OBJECT_2 = this._body.childs;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let child = ___OBJECT_2[k - 1];
			if (child === undefined) break;
			child.SearchDescription(name, list);
		}
		return list;
	},
	HandleChildResize : function(event) {
		this.DispatchEvent(___all_struct.get(-431205740), {});
	},
	HandleHeadChanged : function(event) {
		this._body.visible = event.target.selected;
		this.DispatchEvent(___all_struct.get(-431205740), {});
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
	HasChild : function(child) {
		return this._body.HasChild(child);
	},
	AddChild : function(child, index) {
		if (this._body.width < child.width) {
			this._body.width = child.width;
		}
		if (this._body.AddChild(child, index) === false) {
			return false;
		}
		child._logic_parent = this;
		this.DispatchEvent(___all_struct.get(-431205740), {});
		return true;
	},
	RemoveChild : function(child) {
		if (this._body.RemoveChild(child) === false) {
			return false;
		}
		this.DispatchEvent(___all_struct.get(-431205740), {});
		return true;
	},
	RemoveAllChild : function() {
		this._body.RemoveAllChild();
		this.DispatchEvent(___all_struct.get(-431205740), {});
	},
	get width() {
		let head_width = 0.0;
		if (this._head !== undefined) {
			head_width = this._head.width;
		}
		let body_width = 0.0;
		if (this._body.visible) {
			let start_x = this._body.x;
			body_width = start_x + this._body.width;
			let childs = this._body.childs;
			let ___OBJECT_3 = childs;
			for (let k = 1; k <= ___OBJECT_3.length; ++k) {
				let v = ___OBJECT_3[k - 1];
				if (v === undefined) break;
				let child_width = start_x + v.x + v.width;
				if (body_width < child_width) {
					body_width = child_width;
				}
			}
		}
		if (head_width > body_width) {
			return head_width;
		}
		return body_width;
	},
	get height() {
		let head_height = 0.0;
		if (this._head !== undefined) {
			head_height = this._head.height;
		}
		if (this._body.visible) {
			return head_height + this._body.height;
		}
		return head_height;
	},
	get fold() {
		return this._body.visible;
	},
	set fold(value) {
		if (value === this._body.visible) {
			return;
		}
		this._body.visible = value;
		this._item_checkbutton.selected = value;
		this.DispatchEvent(___all_struct.get(-431205740), {});
	},
	get max_right() {
		return this.width;
	},
	get max_bottom() {
		return this.height;
	},
}, "Emulator.IDETree");

}