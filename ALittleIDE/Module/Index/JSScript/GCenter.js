{
if (typeof Index === "undefined") window.Index = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1632726113, "Index.ItemInfo", {
name : "Index.ItemInfo", ns_name : "Index", rl_name : "ItemInfo", hash_code : -1632726113,
name_list : ["_image","_title"],
type_list : ["ALittle.Image","ALittle.Text"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1403787970, "Index.ItemData", {
name : "Index.ItemData", ns_name : "Index", rl_name : "ItemData", hash_code : 1403787970,
name_list : ["title","texture_name","path"],
type_list : ["string","string","string"],
option_map : {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name : "ALittle.UIClickEvent", ns_name : "ALittle", rl_name : "UIClickEvent", hash_code : -449066808,
name_list : ["target","is_drag"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})

Index.g_GConfig = undefined;
Index.GCenter = JavaScript.Class(undefined, {
	Ctor : function() {
	},
	Setup : function() {
		Index.g_GConfig = ALittle.CreateConfigSystem(Index.g_ModuleBasePath + "/User.cfg");
		ALittle.Math_RandomSeed(ALittle.Time_GetCurTime());
		ALittle.System_SetThreadCount(1);
		this._main_layer = ALittle.NewObject(ALittle.DisplayLayout, Index.g_Control);
		this._main_layer.width_type = 4;
		this._main_layer.height_type = 4;
		Index.g_LayerGroup.AddChild(this._main_layer, undefined);
		this._dialog_layer = ALittle.NewObject(ALittle.DisplayLayout, Index.g_Control);
		this._dialog_layer.width_type = 4;
		this._dialog_layer.height_type = 4;
		Index.g_LayerGroup.AddChild(this._dialog_layer, undefined);
		let main_scene = Index.g_Control.CreateControl("main_scene", this, this._main_layer);
		this._item_tiletable = ALittle.Cast(ALittle.TileTable, ALittle.DisplayGroup, this._item_container.container);
		let data_list = [];
		{
			let data = {};
			data.title = "BattleCity";
			data.texture_name = "BattleCity.png";
			data.path = "BattleCity.html";
			ALittle.List_Push(data_list, data);
			data = {};
			data.title = "SuperMarioBros";
			data.texture_name = "SuperMarioBros.png";
			data.path = "SuperMarioBros.html";
			ALittle.List_Push(data_list, data);
			data = {};
			data.title = "ALittleIDE";
			data.texture_name = "ALittleIDE.png";
			data.path = "ALittleIDE.html";
			ALittle.List_Push(data_list, data);
			data = {};
			data.title = "2048";
			data.texture_name = "G2048.png";
			data.path = "G2048.html";
			ALittle.List_Push(data_list, data);
			data = {};
			data.title = "FlappyBird";
			data.texture_name = "FlappyBird.png";
			data.path = "FlappyBird.html";
			ALittle.List_Push(data_list, data);
			data = {};
			data.title = "NES Emulator";
			data.texture_name = "NESEmulator.png";
			data.path = "NESEmulator.html";
			ALittle.List_Push(data_list, data);
		}
		this._item_width = 0;
		let ___OBJECT_1 = data_list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let data = ___OBJECT_1[index - 1];
			if (data === undefined) break;
			let info = {};
			let item = Index.g_Control.CreateControl("sample_item", info);
			this._item_tiletable.AddChild(item);
			info._image.texture_name = data.texture_name;
			info._title.text = data.title;
			info._image._user_data = data;
			info._image.AddEventListener(___all_struct.get(-449066808), this, this.HandleImageClick);
			this._item_width = item.width;
		}
		if (this._item_width > 0 && this._item_tiletable !== undefined) {
			this._item_tiletable.col_count = ALittle.Math_Floor(this._item_container.width / this._item_width);
		}
		this._item_container.AdjustScrollBar();
		A_UISystem.view_resize_callback = this.HandleViewResized.bind(this);
	},
	HandleViewResized : function(width, height) {
		if (this._item_width > 0 && this._item_tiletable !== undefined) {
			this._item_tiletable.col_count = ALittle.Math_Floor(this._item_container.width / this._item_width);
		}
		this._item_container.AdjustScrollBar();
	},
	HandleImageClick : function(event) {
		let data = event.target._user_data;
		let fixed_host = "139.159.176.119";
		let base_url = "http://" + fixed_host + "/";
		let host = location.host;
		if (host !== fixed_host) {
			base_url = "https://alittlesail.github.io/";
		}
		window.open(base_url + data.path);
	},
	HandleGithubClick : function(event) {
		let url = "https://github.com/alittlesail/ALittle.git";
		window.open(url);
	},
	Shutdown : function() {
	},
}, "Index.GCenter");

window.g_GCenter = ALittle.NewObject(Index.GCenter);
}