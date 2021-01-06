{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name : "ALittle.UIChangedEvent", ns_name : "ALittle", rl_name : "UIChangedEvent", hash_code : 958494922,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name : "ALittle.UIClickEvent", ns_name : "ALittle", rl_name : "UIClickEvent", hash_code : -449066808,
name_list : ["target","is_drag","count"],
type_list : ["ALittle.DisplayObject","bool","int"],
option_map : {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name : "ALittle.UIResizeEvent", ns_name : "ALittle", rl_name : "UIResizeEvent", hash_code : -431205740,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEAntiFrameLinearItem = JavaScript.Class(ALittle.DisplayLayout, {
	Init : function(panel, frame) {
		this._panel = panel;
		this._frame_text.text = frame;
	},
}, "ALittleIDE.IDEAntiFrameLinearItem");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEAntiFrameLinkItem = JavaScript.Class(ALittle.DisplayLayout, {
	Init : function(panel, info) {
		this._panel = panel;
		if (info !== undefined) {
			if (info.link !== undefined) {
				this._link_input.text = info.link;
			}
			if (info.attribute !== undefined) {
				this._attribute_dropdown.text = info.attribute;
			}
			if (info.init !== undefined) {
				if (info.init === true) {
					this._init_input.text = "true";
				} else if (info.init === false) {
					this._init_input.text = "false";
				} else {
					this._init_input.text = info.init;
				}
			}
		}
	},
	HandleDeleteClick : function(event) {
		this._panel.RemoveAttr(this._panel.anti_link_linear.GetChildIndex(this));
	},
	HandleLinkChanged : function(event) {
		let info = this._panel.GetCurLoopInfo();
		if (info === undefined) {
			return;
		}
		let child_index = this._panel.anti_link_linear.GetChildIndex(this);
		if (child_index <= 0) {
			return;
		}
		let child = info.childs[child_index - 1];
		child.link = this._link_input.text;
		this._panel.tab_child.save = false;
	},
	HandleAttributeChanged : function(event) {
		let info = this._panel.GetCurLoopInfo();
		if (info === undefined) {
			return;
		}
		let child_index = this._panel.anti_link_linear.GetChildIndex(this);
		if (child_index <= 0) {
			return;
		}
		let child = info.childs[child_index - 1];
		child.attribute = this._attribute_dropdown.text;
		if (this._init_input.text === "") {
			child.init = undefined;
		} else {
			if (this._attribute_dropdown.text === "visible" || this._attribute_dropdown.text === "disabled") {
				child.init = this._init_input.text === "true";
			} else {
				child.init = ALittle.Math_ToDouble(this._init_input.text);
			}
		}
		this._panel.tab_child.save = false;
	},
	HandleInitChanged : function(event) {
		let info = this._panel.GetCurLoopInfo();
		if (info === undefined) {
			return;
		}
		let child_index = this._panel.anti_link_linear.GetChildIndex(this);
		if (child_index <= 0) {
			return;
		}
		let child = info.childs[child_index - 1];
		if (this._init_input.text === "") {
			child.init = undefined;
		} else {
			if (this._attribute_dropdown.text === "visible" || this._attribute_dropdown.text === "disabled") {
				child.init = this._init_input.text === "true";
			} else {
				child.init = ALittle.Math_ToDouble(this._init_input.text);
			}
		}
		this._panel.tab_child.save = false;
	},
}, "ALittleIDE.IDEAntiFrameLinkItem");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEAntiFrameLoopItem = JavaScript.Class(ALittle.DisplayLayout, {
	Init : function(item, info) {
		this._item = item;
		this._button.drag_trans_target = this._item.panel.anti_screen;
		this._bg_quad.drag_trans_target = this._item.panel.anti_screen;
		this._info = info;
		this._button.group = this._item.panel.loop_group;
		this.UpdateText();
		this.UpdateShow();
	},
	get info() {
		return this._info;
	},
	get button() {
		return this._button;
	},
	get item() {
		return this._item;
	},
	UpdateText : function() {
		let value = "null";
		if (this._info.target === true) {
			value = "true";
		} else if (this._info.target === false) {
			value = "false";
		} else {
			value = ALittle.String_ToString(this._info.target);
		}
		if (this._info.clazz === "LoopLinear") {
			this._button.text = "L(" + value + ")";
		} else if (this._info.clazz === "LoopAttribute") {
			this._button.text = "A(" + value + ")";
		} else if (this._info.clazz === "LoopRit") {
			this._button.text = "R(" + value + ")";
		}
	},
	UpdateShow : function() {
		let width = this._item.CalcWidthByTime(this._info.total_time + this._info.delay_time);
		this._button.width = this._item.CalcWidthByTime(this._info.total_time);
		if (this._button.width < this._item.panel._MIN_WIDTH) {
			this._button.width = this._item.panel._MIN_WIDTH;
		}
		if (width < this._button.width) {
			this._button.x_value = (width - this._button.width) / 2;
		} else {
			this._button.x_value = 0;
		}
		this.width = width;
	},
	get info() {
		return this._info;
	},
	HandleButtonChanged : function(event) {
		this._item.panel.ShowAntiLoop(this);
	},
	HandleKeyDown : function(event) {
		if (event.sym === 1073741904) {
			let child_index = this._item.container.GetChildIndex(this);
			if (child_index > 1) {
				-- child_index;
				let item = this._item.container.GetChildByIndex(child_index);
				item._button.selected = true;
				this._item.panel.ShowAntiLoop(item);
				item._button.focus = true;
			}
			event.handled = true;
		} else if (event.sym === 1073741903) {
			let child_index = this._item.container.GetChildIndex(this);
			if (child_index < this._item.container.child_count) {
				++ child_index;
				let item = this._item.container.GetChildByIndex(child_index);
				item._button.selected = true;
				this._item.panel.ShowAntiLoop(item);
				item._button.focus = true;
			}
			event.handled = true;
		}
	},
	HandleRButtonDown : function(event) {
		ALittleIDE.g_IDECenter.center.control_anti.ShowAntiLoopMenu(this);
	},
	ValueToString : function(value) {
		if (value === undefined) {
			return "";
		}
		if (value === true) {
			return "true";
		}
		if (value === false) {
			return "false";
		}
		return ALittle.String_ToString(value);
	},
	StringToValue : function(attribute, value) {
		if (value === "") {
			return undefined;
		}
		if (attribute === "visible" || attribute === "disabled") {
			if (value === "true") {
				return true;
			} else {
				return false;
			}
		} else {
			return ALittle.Math_ToDouble(value);
		}
	},
	SetTargetValue : function(text) {
		let old_value = this._info.target;
		this._info.target = ALittleIDE.IDEAntiFrameLoopItem.StringToValue(this._item.info.attribute, text);
		this.UpdateText();
		if (old_value !== this._info.target) {
			let old_value_string = ALittleIDE.IDEAntiFrameLoopItem.ValueToString(old_value);
			let new_value_string = ALittleIDE.IDEAntiFrameLoopItem.ValueToString(this._info.target);
			let revoke = ALittle.NewObject(ALittleIDE.IDEAntiLoopTargetValueChangeRevoke, this, old_value_string, new_value_string);
			this._item.panel.tab_child.revoke_list.PushRevoke(revoke);
			this._item.panel.tab_child.save = false;
		}
	},
	SetTotalTime : function(time) {
		if (this._info.total_time === time) {
			return;
		}
		let old_time = this._info.total_time;
		this._info.total_time = time;
		if (this._info.total_time === undefined) {
			this._info.total_time = 0;
		}
		this.UpdateShow();
		this.DispatchEvent(___all_struct.get(-431205740), {});
		let revoke = ALittle.NewObject(ALittleIDE.IDEAntiLoopTotalTimeChangeRevoke, this, old_time, this._info.total_time);
		this._item.panel.tab_child.revoke_list.PushRevoke(revoke);
		this._item.panel.tab_child.save = false;
	},
	SetDelayTime : function(time) {
		if (this._info.delay_time === time) {
			return;
		}
		let old_time = this._info.delay_time;
		this._info.delay_time = time;
		if (this._info.delay_time === undefined) {
			if (this._info.clazz === "LoopAttribute") {
				this._info.delay_time = 1;
			} else {
				this._info.delay_time = 0;
			}
		}
		this.UpdateShow();
		this.DispatchEvent(___all_struct.get(-431205740), {});
		let revoke = ALittle.NewObject(ALittleIDE.IDEAntiLoopDelayTimeChangeRevoke, this, old_time, this._info.delay_time);
		this._item.panel.tab_child.revoke_list.PushRevoke(revoke);
		this._item.panel.tab_child.save = false;
	},
}, "ALittleIDE.IDEAntiFrameLoopItem");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEAntiFrameAntiItem = JavaScript.Class(ALittle.DisplayLayout, {
	Init : function(panel, info) {
		this._panel = panel;
		this._bg_quad.drag_trans_target = this._panel.anti_screen;
		this._info = info;
		if (this._info.childs === undefined) {
			this._info.childs = [];
		}
		let ___OBJECT_1 = this._info.childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			let loop_item = ALittleIDE.g_Control.CreateControl("ide_anti_screen_loop_item");
			loop_item.Init(this, child);
			this._container.AddChild(loop_item);
		}
	},
	get panel() {
		return this._panel;
	},
	get info() {
		return this._info;
	},
	get container() {
		return this._container;
	},
	CalcTimeByWidth : function(width) {
		return ALittle.Math_Floor(width / this._panel._FRAME_WIDTH * this._panel._FRAME_TIME);
	},
	CalcWidthByTime : function(time) {
		return time / this._panel._FRAME_TIME * this._panel._FRAME_WIDTH;
	},
	HandleBgRButtonDown : function(event) {
		let child_index = this._panel.anti_anti_linear.GetChildIndex(this);
		if (child_index <= 0) {
			return;
		}
		ALittleIDE.g_IDECenter.center.control_anti.ShowAntiAntiMenu(this, child_index, event.rel_x);
	},
	Insert : function(rel_x, clazz) {
		let child = {};
		child.clazz = clazz;
		if (this._info.attribute === "visible" || this._info.attribute === "disabled") {
			child.target = true;
		} else {
			child.target = 0;
		}
		if (clazz === "LoopLinear" || clazz === "LoopRit") {
			child.delay_time = 0;
			child.total_time = this.CalcTimeByWidth(rel_x - (this._container.x + this._container.width));
		} else if (clazz === "LoopAttribute") {
			child.delay_time = this.CalcTimeByWidth(rel_x - (this._container.x + this._container.width));
			if (child.delay_time <= 0) {
				child.delay_time = 1;
			}
			child.total_time = 0;
		} else {
			return;
		}
		ALittle.List_Push(this._info.childs, child);
		let loop_item = ALittleIDE.g_Control.CreateControl("ide_anti_screen_loop_item");
		loop_item.Init(this, child);
		this._container.AddChild(loop_item);
		let revoke = ALittle.NewObject(ALittleIDE.IDEAntiInsertLoopRevoke, this, child, loop_item, ALittle.List_Len(this._info.childs));
		this._panel.tab_child.revoke_list.PushRevoke(revoke);
		loop_item.button.selected = true;
		this._panel.ShowAntiLoop(loop_item);
		this._panel.tab_child.save = false;
	},
	ClearLoop : function() {
		if (this._container.child_count === 0) {
			return;
		}
		this._panel.HideAntiLoop();
		let loop_item_list = [];
		let ___OBJECT_2 = this._container.childs;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let child = ___OBJECT_2[index - 1];
			if (child === undefined) break;
			loop_item_list[index - 1] = child;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDEAntiClearLoopRevoke, this, this._info.childs, loop_item_list);
		this._panel.tab_child.revoke_list.PushRevoke(revoke);
		this._info.childs = [];
		this._container.RemoveAllChild();
		this._panel.tab_child.save = false;
	},
	InsertBefore : function(loop_item, clazz) {
		let child = {};
		child.clazz = clazz;
		if (this._info.attribute === "visible" || this._info.attribute === "disabled") {
			child.target = true;
		} else {
			child.target = 0;
		}
		if (clazz === "LoopLinear" || clazz === "LoopRit") {
			child.delay_time = 0;
			child.total_time = this._panel._INIT_TIME;
		} else if (clazz === "LoopAttribute") {
			child.delay_time = this._panel._INIT_TIME;
			child.total_time = 0;
		} else {
			return;
		}
		let child_index = this._container.GetChildIndex(loop_item);
		ALittle.List_Insert(this._info.childs, child_index, child);
		loop_item = ALittleIDE.g_Control.CreateControl("ide_anti_screen_loop_item");
		loop_item.Init(this, child);
		this._container.AddChild(loop_item, child_index);
		let revoke = ALittle.NewObject(ALittleIDE.IDEAntiInsertLoopRevoke, this, child, loop_item, child_index);
		this._panel.tab_child.revoke_list.PushRevoke(revoke);
		loop_item.button.selected = true;
		this._panel.ShowAntiLoop(loop_item);
		this._panel.tab_child.save = false;
	},
	DeleteLoop : function(loop_item) {
		this._panel.HideAntiLoop(loop_item);
		let child_index = this._container.GetChildIndex(loop_item);
		if (child_index <= 0) {
			return;
		}
		let child = this._info.childs[child_index - 1];
		ALittle.List_Remove(this._info.childs, child_index);
		this._container.RemoveChild(loop_item);
		let revoke = ALittle.NewObject(ALittleIDE.IDEAntiDeleteLoopRevoke, this, child, loop_item, child_index);
		this._panel.tab_child.revoke_list.PushRevoke(revoke);
		this._panel.tab_child.save = false;
	},
}, "ALittleIDE.IDEAntiFrameAntiItem");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEAntiPanel = JavaScript.Class(ALittle.DisplayLayout, {
	TCtor : function() {
		this._handle_container.visible = false;
		this._loop_linear.visible = false;
		this._loop_attribute.visible = false;
		this._loop_rit.visible = false;
		this._cur_loop_item = undefined;
		this._FRAME_WIDTH = 40;
		this._FRAME_TIME = 50;
		this._INIT_TIME = 10;
		this._MIN_WIDTH = 10;
	},
	get anti_link_linear() {
		return this._anti_link_linear;
	},
	get anti_anti_linear() {
		return this._anti_anti_linear;
	},
	get anti_screen() {
		return this._anti_screen;
	},
	get loop_group() {
		return this._loop_group;
	},
	get anti_scroll_list() {
		return this._anti_scroll_list;
	},
	get cur_show() {
		return this._cur_show;
	},
	get cur_loop_item() {
		return this._cur_loop_item;
	},
	get linear_target_value() {
		return this._linear_target_value;
	},
	get attribute_target_value() {
		return this._attribute_target_value;
	},
	get rit_target_value() {
		return this._rit_target_value;
	},
	get linear_total_time() {
		return this._linear_total_time;
	},
	get rit_total_time() {
		return this._rit_total_time;
	},
	get linear_delay_time() {
		return this._linear_delay_time;
	},
	get attribute_delay_time() {
		return this._attribute_delay_time;
	},
	get rit_delay_time() {
		return this._rit_delay_time;
	},
	Init : function(tab_child) {
		this._tab_child = tab_child;
		this._list_group = ALittle.CreateKeyWeakMap();
		this._loop_group = ALittle.CreateKeyWeakMap();
		let user_info = this._tab_child.tree_object.user_info;
		if (user_info.base.loop_map !== undefined) {
			let ___OBJECT_3 = user_info.base.loop_map;
			for (let name in ___OBJECT_3) {
				let info = ___OBJECT_3[name];
				if (info === undefined) continue;
				let item = ALittleIDE.g_Control.CreateControl("tree_item_radiobutton");
				item.text = name;
				item.group = this._list_group;
				item.AddEventListener(___all_struct.get(-1479093282), this, this.HandleAntiListItemRButtonDown);
				item.AddEventListener(___all_struct.get(958494922), this, this.HandleAntiListItemChanged);
				this._anti_scroll_list.AddChild(item);
			}
		}
		let static_object_hv = ALittleIDE.g_Control.CreateControl("ide_anti_screen_hv");
		let static_object_h = ALittleIDE.g_Control.CreateControl("ide_anti_screen_h", this);
		this._anti_frame_linear.x = static_object_hv.width;
		for (let frame = 0; frame <= 10000; frame += 50) {
			let text = ALittleIDE.g_Control.CreateControl("ide_anti_screen_frame_item");
			text.width = this._FRAME_WIDTH;
			text.Init(this, frame);
			this._anti_frame_linear.AddChild(text);
		}
		static_object_h.width = this._anti_frame_linear.x + this._anti_frame_linear.width;
		let static_object_v = ALittleIDE.g_Control.CreateControl("ide_anti_screen_v", this);
		static_object_v.width = static_object_hv.width;
		static_object_v.height = static_object_hv.height;
		this._anti_link_linear.y = static_object_hv.height;
		this._anti_screen.static_object_h = static_object_h;
		this._anti_screen.static_object_hv = static_object_hv;
		this._anti_screen.static_object_v = static_object_v;
		this._anti_anti_linear.x = static_object_hv.width;
		this._anti_anti_linear.y = static_object_hv.height;
		this._anti_anti_linear.width = static_object_h.width - static_object_hv.width;
		this._anti_screen.AdjustScrollBar();
		if (this._anti_scroll_list.child_count > 0) {
			this._anti_scroll_list.childs[1 - 1].selected = true;
			this.ShowAnti(this._anti_scroll_list.childs[1 - 1].text);
		}
	},
	get tab_child() {
		return this._tab_child;
	},
	GetCurLoopInfo : function() {
		if (this._cur_show === undefined) {
			return undefined;
		}
		let user_info = this._tab_child.tree_object.user_info;
		if (user_info.base.loop_map === undefined) {
			return undefined;
		}
		return user_info.base.loop_map[this._cur_show];
	},
	CreateAnti : function(name) {
		let user_info = this._tab_child.tree_object.user_info;
		if (user_info.base.loop_map === undefined) {
			user_info.base.loop_map = {};
		}
		if (user_info.base.loop_map[name] !== undefined) {
			g_AUITool.ShowNotice("错误", "动画名称已存在");
			return;
		}
		let root = {};
		root.childs = [];
		user_info.base.loop_map[name] = root;
		let item = ALittleIDE.g_Control.CreateControl("tree_item_radiobutton");
		item.text = name;
		item.group = this._list_group;
		item.AddEventListener(___all_struct.get(-1479093282), this, this.HandleAntiListItemRButtonDown);
		item.AddEventListener(___all_struct.get(-449066808), this, this.HandleAntiListItemClick);
		this._anti_scroll_list.AddChild(item);
		item.selected = true;
		this.ShowAnti(name);
		let revoke = ALittle.NewObject(ALittleIDE.IDECreateAntiRevoke, this, name, root, item);
		this._tab_child.revoke_list.PushRevoke(revoke);
		this._tab_child.save = false;
	},
	DeleteAnti : function(name) {
		let user_info = this._tab_child.tree_object.user_info;
		if (user_info.base.loop_map === undefined) {
			return;
		}
		let root = user_info.base.loop_map[name];
		if (root === undefined) {
			return;
		}
		delete user_info.base.loop_map[name];
		let ___OBJECT_4 = this._anti_scroll_list.childs;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let item = ___OBJECT_4[index - 1];
			if (item === undefined) break;
			if (item.text === name) {
				item.group = undefined;
				this._anti_scroll_list.RemoveChild(item);
				let revoke = ALittle.NewObject(ALittleIDE.IDEDeleteAntiRevoke, this, name, root, item, index);
				this._tab_child.revoke_list.PushRevoke(revoke);
				break;
			}
		}
		if (this._anti_scroll_list.child_count === 0) {
			user_info.base.loop_map = undefined;
		}
		this._tab_child.save = false;
		if (this._cur_show === name) {
			if (this._anti_scroll_list.child_count === 0) {
				this.HideAnti();
			} else {
				this._anti_scroll_list.childs[1 - 1].selected = true;
				this.ShowAnti(this._anti_scroll_list.childs[1 - 1].text);
			}
		}
	},
	CopyAndNewAnti : function(old_name, new_name) {
		let user_info = this._tab_child.tree_object.user_info;
		if (user_info.base.loop_map === undefined) {
			return;
		}
		let root = user_info.base.loop_map[old_name];
		if (root === undefined) {
			return;
		}
		if (user_info.base.loop_map[new_name] !== undefined) {
			g_AUITool.ShowNotice("错误", "新建的动画名称已存在");
			return;
		}
		let new_root = ALittle.String_CopyTable(root);
		user_info.base.loop_map[new_name] = new_root;
		let item = ALittleIDE.g_Control.CreateControl("ide_common_item_radiobutton");
		item.text = new_name;
		item.group = this._list_group;
		item.AddEventListener(___all_struct.get(-1479093282), this, this.HandleAntiListItemRButtonDown);
		item.AddEventListener(___all_struct.get(-449066808), this, this.HandleAntiListItemClick);
		this._anti_scroll_list.AddChild(item);
		item.selected = true;
		this.ShowAnti(new_name);
		let revoke = ALittle.NewObject(ALittleIDE.IDECreateAntiRevoke, this, new_name, new_root, item);
		this._tab_child.revoke_list.PushRevoke(revoke);
		this._tab_child.save = false;
	},
	ShowAnti : function(name) {
		if (this._cur_show === name) {
			return;
		}
		this.HideAnti();
		let user_info = this._tab_child.tree_object.user_info;
		if (user_info.base.loop_map === undefined) {
			return;
		}
		let info = user_info.base.loop_map[name];
		if (info === undefined) {
			return;
		}
		this._cur_show = name;
		let static_object_v = this._anti_screen.static_object_v;
		this._anti_link_linear.RemoveAllChild();
		this._anti_anti_linear.RemoveAllChild();
		let ___OBJECT_5 = info.childs;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let child = ___OBJECT_5[index - 1];
			if (child === undefined) break;
			let anti_item = ALittleIDE.g_Control.CreateControl("ide_anti_screen_anti_item");
			anti_item.Init(this, child);
			this._anti_anti_linear.AddChild(anti_item);
			let link_item = ALittleIDE.g_Control.CreateControl("ide_anti_screen_link_item");
			link_item.Init(this, child);
			this._anti_link_linear.AddChild(link_item);
		}
		static_object_v.height = this._anti_link_linear.y + this._anti_link_linear.height;
		this._anti_screen.AdjustScrollBar();
		this._handle_container.visible = true;
	},
	HideAnti : function() {
		if (this._cur_show === undefined) {
			return;
		}
		this._cur_show = undefined;
		this._anti_anti_linear.RemoveAllChild();
		this._anti_link_linear.RemoveAllChild();
		this._anti_screen.static_object_v.height = this._anti_link_linear.y;
		this._anti_screen.AdjustScrollBar();
		this._handle_container.visible = false;
		this._loop_linear.visible = false;
		this._loop_attribute.visible = false;
		this._loop_rit.visible = false;
		this._cur_loop_item = undefined;
		if (this._cur_anti !== undefined) {
			this._cur_anti.Stop();
			this._cur_anti = undefined;
		}
		if (this._anti_dialog !== undefined) {
			this._anti_dialog.visible = false;
		}
	},
	HandleAntiListItemRButtonDown : function(event) {
		ALittleIDE.g_IDECenter.center.control_anti.ShowAntiListMenu(this, event.target.text);
	},
	HandleAntiListItemClick : function(event) {
		this.ShowAnti(event.target.text);
	},
	HandleAntiListItemChanged : function(event) {
		this.ShowAnti(event.target.text);
	},
	HandleNewClick : function(event) {
		ALittleIDE.g_IDECenter.center.control_anti.ShowNewAntiDialog(this);
	},
	HandleCopyAttrLineClick : function(event) {
		if (this._cur_loop_item === undefined) {
			return;
		}
		let info = this.GetCurLoopInfo();
		if (info === undefined) {
			return;
		}
		let child = ALittle.String_CopyTable(this._cur_loop_item.item.info);
		ALittle.List_Push(info.childs, child);
		let anti_item = ALittleIDE.g_Control.CreateControl("ide_anti_screen_anti_item");
		anti_item.Init(this, child);
		this._anti_anti_linear.AddChild(anti_item);
		let link_item = ALittleIDE.g_Control.CreateControl("ide_anti_screen_link_item");
		link_item.Init(this, child);
		this._anti_link_linear.AddChild(link_item);
		let static_object_v = this._anti_screen.static_object_v;
		static_object_v.height = this._anti_link_linear.y + this._anti_link_linear.height;
		this._anti_screen.AdjustScrollBar();
		let revoke = ALittle.NewObject(ALittleIDE.IDEAntiAddAttrRevoke, this, this._cur_show, child, anti_item, link_item);
		this._tab_child.revoke_list.PushRevoke(revoke);
		this._tab_child.save = false;
	},
	HandleAddAttrClick : function(event) {
		let user_info = this._tab_child.tree_object.user_info;
		if (user_info.base.loop_map === undefined) {
			return;
		}
		let info = user_info.base.loop_map[this._cur_show];
		if (info === undefined) {
			return;
		}
		let child = {};
		child.childs = [];
		child.attribute = "x";
		ALittle.List_Push(info.childs, child);
		let anti_item = ALittleIDE.g_Control.CreateControl("ide_anti_screen_anti_item");
		anti_item.Init(this, child);
		this._anti_anti_linear.AddChild(anti_item);
		let link_item = ALittleIDE.g_Control.CreateControl("ide_anti_screen_link_item");
		link_item.Init(this, child);
		this._anti_link_linear.AddChild(link_item);
		let static_object_v = this._anti_screen.static_object_v;
		static_object_v.height = this._anti_link_linear.y + this._anti_link_linear.height;
		this._anti_screen.AdjustScrollBar();
		let revoke = ALittle.NewObject(ALittleIDE.IDEAntiAddAttrRevoke, this, this._cur_show, child, anti_item, link_item);
		this._tab_child.revoke_list.PushRevoke(revoke);
		this._tab_child.save = false;
	},
	RemoveAttr : function(child_index) {
		let user_info = this._tab_child.tree_object.user_info;
		if (user_info.base.loop_map === undefined) {
			return;
		}
		let info = user_info.base.loop_map[this._cur_show];
		if (info === undefined) {
			return;
		}
		let child = info.childs[child_index - 1];
		ALittle.List_Remove(info.childs, child_index);
		let anti_item = this._anti_anti_linear.GetChildByIndex(child_index);
		this._anti_anti_linear.RemoveChild(anti_item);
		let link_item = this._anti_link_linear.GetChildByIndex(child_index);
		this._anti_link_linear.RemoveChild(link_item);
		this._anti_screen.static_object_v.height = this._anti_link_linear.y + this._anti_link_linear.height;
		this._anti_screen.AdjustScrollBar();
		let revoke = ALittle.NewObject(ALittleIDE.IDEAntiRemoveAttrRevoke, this, this._cur_show, child, anti_item, link_item, child_index);
		this._tab_child.revoke_list.PushRevoke(revoke);
		this._tab_child.save = false;
	},
	ShowAntiLoop : function(loop_item) {
		let info = loop_item.info;
		if (info.clazz === "LoopLinear") {
			this._loop_linear.visible = true;
			this._loop_attribute.visible = false;
			this._loop_rit.visible = false;
			this._cur_loop_item = loop_item;
			if (info.target === undefined) {
				this._linear_target_value.text = "";
			} else if (info.target === false) {
				this._linear_target_value.text = "false";
			} else if (info.target === true) {
				this._linear_target_value.text = "true";
			} else {
				this._linear_target_value.text = info.target;
			}
			this._linear_total_time.text = info.total_time;
			this._linear_delay_time.text = info.delay_time;
		} else if (info.clazz === "LoopLinear" || info.clazz === "LoopRit") {
			this._loop_rit.visible = true;
			this._loop_linear.visible = false;
			this._loop_attribute.visible = false;
			this._cur_loop_item = loop_item;
			if (info.target === undefined) {
				this._rit_target_value.text = "";
			} else if (info.target === false) {
				this._rit_target_value.text = "false";
			} else if (info.target === true) {
				this._rit_target_value.text = "true";
			} else {
				this._rit_target_value.text = info.target;
			}
			this._rit_total_time.text = info.total_time;
			this._rit_delay_time.text = info.delay_time;
		} else if (info.clazz === "LoopAttribute") {
			this._loop_linear.visible = false;
			this._loop_attribute.visible = true;
			this._loop_rit.visible = false;
			this._cur_loop_item = loop_item;
			if (info.target === undefined) {
				this._attribute_target_value.text = "";
			} else if (info.target === false) {
				this._attribute_target_value.text = "false";
			} else if (info.target === true) {
				this._attribute_target_value.text = "true";
			} else {
				this._attribute_target_value.text = info.target;
			}
			this._attribute_delay_time.text = info.delay_time;
		}
	},
	HideAntiLoop : function(loop_item) {
		if (loop_item !== undefined && this._cur_loop_item !== loop_item) {
			return;
		}
		this._loop_linear.visible = false;
		this._loop_attribute.visible = false;
		this._loop_rit.visible = false;
		this._cur_loop_item = undefined;
	},
	HandleDeleteLoopClick : function(event) {
		if (this._cur_loop_item !== undefined) {
			this._cur_loop_item.item.DeleteLoop(this._cur_loop_item);
			this._cur_loop_item = undefined;
		}
		this.HideAntiLoop();
	},
	HandleTargetValueChanged : function(event) {
		if (this._cur_loop_item === undefined) {
			return;
		}
		this._cur_loop_item.SetTargetValue(event.target.text);
	},
	HandleTotalTimeChanged : function(event) {
		if (this._cur_loop_item === undefined) {
			return;
		}
		let time = ALittle.Math_ToInt(event.target.text);
		if (time === undefined || time < 0) {
			time = 0;
			event.target.text = time;
		}
		this._cur_loop_item.SetTotalTime(time);
	},
	HandleDelayTimeChanged : function(event) {
		if (this._cur_loop_item === undefined) {
			return;
		}
		let time = ALittle.Math_ToInt(event.target.text);
		if (time === undefined || time < 0) {
			time = 0;
			event.target.text = time;
		}
		this._cur_loop_item.SetDelayTime(time);
	},
	PlayImpl : function(loop) {
		let cur_loop_info = this.GetCurLoopInfo();
		if (cur_loop_info === undefined) {
			return;
		}
		let save = this._tab_child.save;
		this._tab_child.save = true;
		if (this._anti_dialog === undefined) {
			this._anti_dialog = ALittleIDE.g_Control.CreateControl("ide_anti_play_dialog", this);
			this._anti_dialog.title = "动画播放窗口";
			this._anti_dialog.visible = false;
			ALittleIDE.g_DialogLayer.AddChild(this._anti_dialog);
		}
		if (save === false || this._cur_anti === undefined || this._anti_dialog.visible === false || this._anti_dialog._user_data !== this._tab_child.name) {
			let map = {};
			let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(this._tab_child.module);
			let object = ui_manager.control.CreateControl(this._tab_child.name, map);
			let anti = ALittle.NewObject(ALittle.LoopAnimation, object, cur_loop_info);
			let error = anti.Init(map);
			if (error !== undefined) {
				g_AUITool.ShowNotice("错误", error);
				return;
			}
			this._anti_play_container.RemoveAllChild();
			this._anti_play_container.AddChild(object);
			this._anti_dialog._user_data = this._tab_child.name;
			if (object.width_type !== 1 || object.height_type !== 1) {
				this._anti_dialog.width = ALittleIDE.g_IDEProject.project.config.GetConfig("default_show_width", 800);
				this._anti_dialog.height = ALittleIDE.g_IDEProject.project.config.GetConfig("default_show_height", 800);
			} else {
				this._anti_dialog.width = object.width + 10;
				this._anti_dialog.height = object.height + this._anti_dialog.head_size + 10;
			}
			if (this._anti_dialog.width < 300) {
				this._anti_dialog.width = 300;
			}
			if (this._anti_dialog.height < 300) {
				this._anti_dialog.height = 300;
			}
			if (this._anti_dialog.visible === false) {
				this._anti_dialog.x = (A_UISystem.view_width - this._anti_dialog.width) / 2;
				this._anti_dialog.y = (A_UISystem.view_height - this._anti_dialog.height) / 2;
			}
			this._anti_dialog.visible = true;
			this._cur_anti = anti;
		}
		this._cur_anti.SetTime(0);
		this._cur_anti.Play(loop);
	},
	HandlePlayClick : function(event) {
		this.PlayImpl();
	},
	HandleLoopPlayClick : function(event) {
		this.PlayImpl(-1);
	},
	HandlePauseClick : function(event) {
		if (this._cur_anti !== undefined) {
			this._cur_anti.Pause();
		}
	},
}, "ALittleIDE.IDEAntiPanel");

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEUIControlAnti = JavaScript.Class(ALittle.DisplayLayout, {
	Setup : function(tab, control) {
		this._main_tab = tab;
		this._main_control = control;
		this._main_tab.SetChildText(this._main_control, "动画编辑器");
	},
	ShowNewAntiDialog : function(panel) {
		if (this._new_anti_dialog === undefined) {
			this._new_anti_dialog = ALittleIDE.g_Control.CreateControl("ide_new_anti_dialog", this);
			A_LayerManager.AddToModal(this._new_anti_dialog);
		}
		this._new_anti_dialog.visible = true;
		this._new_anti_name_input.text = "";
		this._new_anti_dialog._user_data = panel;
	},
	HandleNewAntiCancel : function(event) {
		this._new_anti_dialog.visible = false;
		this._new_anti_dialog._user_data = undefined;
	},
	HandleNewAntiConfirm : function(event) {
		this._new_anti_dialog.visible = false;
		let panel = this._new_anti_dialog._user_data;
		this._new_anti_dialog._user_data = undefined;
		panel.CreateAnti(this._new_anti_name_input.text);
	},
	ShowAntiListMenu : function(panel, name) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("复制并新建", this.HandleAntiListRightMenuCopyAnNew.bind(this, panel, name));
		menu.AddItem("删除", panel.DeleteAnti.bind(panel, name));
		menu.Show();
	},
	HandleAntiListRightMenuCopyAnNew : async function(panel, name) {
		let x = undefined;
		let y = undefined;
		let ___OBJECT_6 = panel.anti_scroll_list.childs;
		for (let index = 1; index <= ___OBJECT_6.length; ++index) {
			let child = ___OBJECT_6[index - 1];
			if (child === undefined) break;
			if (child.text === name) {
				[x, y] = child.LocalToGlobal();
				break;
			}
		}
		let old_name = name;
		let new_name = await g_AUITool.ShowRename(old_name, x, y, 200);
		if (new_name === undefined || old_name === new_name) {
			return;
		}
		panel.CopyAndNewAnti(old_name, new_name);
	},
	ShowAntiAntiMenu : function(item, child_index, rel_x) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("插入Linear", item.Insert.bind(item, rel_x, "LoopLinear"));
		menu.AddItem("插入Rit", item.Insert.bind(item, rel_x, "LoopRit"));
		menu.AddItem("插入Attribute", item.Insert.bind(item, rel_x, "LoopAttribute"));
		menu.AddItem("清空", item.ClearLoop.bind(item));
		menu.Show();
	},
	ShowAntiLoopMenu : function(loop_item) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("插入Linear", loop_item.item.InsertBefore.bind(loop_item.item, loop_item, "LoopLinear"));
		menu.AddItem("插入Rit", loop_item.item.InsertBefore.bind(loop_item.item, loop_item, "LoopRit"));
		menu.AddItem("插入Attribute", loop_item.item.InsertBefore.bind(loop_item.item, loop_item, "LoopAttribute"));
		menu.AddItem("清空", loop_item.item.DeleteLoop.bind(loop_item.item, loop_item));
		menu.Show();
	},
}, "ALittleIDE.IDEUIControlAnti");

}