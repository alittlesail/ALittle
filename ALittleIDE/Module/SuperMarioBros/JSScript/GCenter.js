{
if (typeof SuperMarioBros === "undefined") window.SuperMarioBros = {};


SuperMarioBros.g_GConfig = undefined;
SuperMarioBros.GCenter = JavaScript.Class(undefined, {
	Ctor : function() {
	},
	Setup : function() {
		SuperMarioBros.g_GConfig = ALittle.CreateConfigSystem(SuperMarioBros.g_ModuleBasePath + "/User.cfg");
		ALittle.Math_RandomSeed(ALittle.Time_GetCurTime());
		ALittle.System_SetThreadCount(1);
		this._main_layer = ALittle.NewObject(ALittle.DisplayLayout, SuperMarioBros.g_Control);
		this._main_layer.width_type = 4;
		this._main_layer.height_type = 4;
		SuperMarioBros.g_LayerGroup.AddChild(this._main_layer, undefined);
		this._dialog_layer = ALittle.NewObject(ALittle.DisplayLayout, SuperMarioBros.g_Control);
		this._dialog_layer.width_type = 4;
		this._dialog_layer.height_type = 4;
		SuperMarioBros.g_LayerGroup.AddChild(this._dialog_layer, undefined);
		this._login_scene = SuperMarioBros.g_Control.CreateControl("login_scene");
		this._main_layer.AddChild(this._login_scene);
		this._login_scene.visible = false;
		this._stage_scene = SuperMarioBros.g_Control.CreateControl("stage_scene");
		this._main_layer.AddChild(this._stage_scene);
		this._stage_scene.visible = false;
		this._battle_scene = SuperMarioBros.g_Control.CreateControl("battle_scene");
		this._main_layer.AddChild(this._battle_scene);
		this._battle_scene.visible = false;
		this._edit_scene = SuperMarioBros.g_Control.CreateControl("edit_scene");
		this._main_layer.AddChild(this._edit_scene);
		this._edit_scene.visible = false;
		this.ReStart();
	},
	ReStart : function() {
		this._player_data = {};
		this._player_data.score = 0;
		this._player_data.world = 1;
		this._player_data.subworld = 1;
		this._player_data.life = 3;
		this._player_data.level = 1;
		this._login_scene.Show();
	},
	get login_scene() {
		return this._login_scene;
	},
	get stage_scene() {
		return this._stage_scene;
	},
	get battle_scene() {
		return this._battle_scene;
	},
	get edit_scene() {
		return this._edit_scene;
	},
	get player_data() {
		return this._player_data;
	},
	Shutdown : function() {
		this._edit_scene.Save();
	},
}, "SuperMarioBros.GCenter");

window.g_GCenter = ALittle.NewObject(SuperMarioBros.GCenter);
}