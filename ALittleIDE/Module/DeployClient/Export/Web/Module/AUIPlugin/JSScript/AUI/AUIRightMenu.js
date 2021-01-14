{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-970735483, "AUIPlugin.AUIRightMenuInfo", {
name : "AUIPlugin.AUIRightMenuInfo", ns_name : "AUIPlugin", rl_name : "AUIRightMenuInfo", hash_code : -970735483,
name_list : ["name","disabled","auto_hide","callback"],
type_list : ["string","bool","bool","Functor<()>"],
option_map : {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name : "ALittle.UIClickEvent", ns_name : "ALittle", rl_name : "UIClickEvent", hash_code : -449066808,
name_list : ["target","is_drag","count"],
type_list : ["ALittle.DisplayObject","bool","int"],
option_map : {}
})
ALittle.RegStruct(348388800, "ALittle.UIHideEvent", {
name : "ALittle.UIHideEvent", ns_name : "ALittle", rl_name : "UIHideEvent", hash_code : 348388800,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

AUIPlugin.AUIRightMenu = JavaScript.Class(undefined, {
	Ctor : function() {
		this._info_list = [];
	},
	AddItem : function(name, callback, disabled, auto_hide) {
		if (name === undefined) {
			name = "";
		}
		if (disabled === undefined) {
			disabled = false;
		}
		if (auto_hide === undefined) {
			auto_hide = true;
		}
		let info = {};
		info.name = name;
		info.callback = callback;
		info.disabled = disabled;
		info.auto_hide = auto_hide;
		ALittle.List_Push(this._info_list, info);
	},
	Show : function(target, hide_callback) {
		if (this._menu === undefined) {
			this._menu = AUIPlugin.g_Control.CreateControl("aui_menu", this);
			let max_width = 0.0;
			let ___OBJECT_1 = this._info_list;
			for (let index = 1; index <= ___OBJECT_1.length; ++index) {
				let info = ___OBJECT_1[index - 1];
				if (info === undefined) break;
				let item = AUIPlugin.g_Control.CreateControl("aui_menu_item_button");
				item.text = info.name;
				if (item.show_text !== undefined && item.show_text.width > max_width) {
					max_width = item.show_text.width;
				}
				item.disabled = info.disabled;
				item._user_data = info;
				item.AddEventListener(___all_struct.get(-449066808), this, this.HandleItemClick);
				this._linear.AddChild(item);
			}
			this._menu.width = max_width + 50;
			this._menu.height = this._linear.height + 10;
			this._menu.AddEventListener(___all_struct.get(348388800), this, this.HandleHideEvent);
		}
		if (target !== undefined) {
			let [x, y] = target.LocalToGlobal();
			this._menu.x = x - 5;
			this._menu.y = y + target.height;
		} else {
			this._menu.x = A_UISystem.mouse_x;
			this._menu.y = A_UISystem.mouse_y;
		}
		if (this._menu.x + this._menu.width > A_UISystem.view_width) {
			this._menu.x = A_UISystem.view_width - this._menu.width;
		}
		if (this._menu.y + this._menu.height > A_UISystem.view_height) {
			this._menu.y = A_UISystem.view_height - this._menu.height;
		}
		this._hide_callback = hide_callback;
		A_LayerManager.ShowFromRight(this._menu);
	},
	Hide : function() {
		if (this._menu !== undefined) {
			A_LayerManager.HideFromRight(this._menu);
		}
	},
	HandleHideEvent : function(event) {
		if (this._hide_callback !== undefined) {
			let callback = this._hide_callback;
			this._hide_callback = undefined;
			callback();
		}
	},
	HandleItemClick : function(event) {
		let info = event.target._user_data;
		if (info.auto_hide) {
			this.Hide();
		}
		if (info.callback !== undefined) {
			info.callback();
		}
	},
}, "AUIPlugin.AUIRightMenu");

}