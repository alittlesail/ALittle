{
if (typeof BattleCity === "undefined") window.BattleCity = {};


BattleCity.g_GConfig = undefined;
BattleCity.GCenter = JavaScript.Class(undefined, {
	Ctor : function() {
		this._player_count = 1;
		this._stage = 1;
	},
	Setup : function() {
		BattleCity.g_GConfig = ALittle.CreateConfigSystem(BattleCity.g_ModuleBasePath + "/User.cfg");
		ALittle.Math_RandomSeed(ALittle.Time_GetCurTime());
		ALittle.System_SetThreadCount(1);
		this._main_layer = ALittle.NewObject(ALittle.DisplayLayout, BattleCity.g_Control);
		this._main_layer.width_type = 4;
		this._main_layer.height_type = 4;
		BattleCity.g_LayerGroup.AddChild(this._main_layer, undefined);
		this._dialog_layer = ALittle.NewObject(ALittle.DisplayLayout, BattleCity.g_Control);
		this._dialog_layer.width_type = 4;
		this._dialog_layer.height_type = 4;
		BattleCity.g_LayerGroup.AddChild(this._dialog_layer, undefined);
		this._login_scene = BattleCity.g_Control.CreateControl("login_scene");
		this._login_scene.visible = false;
		this._main_layer.AddChild(this._login_scene);
		this._battle_select_scene = BattleCity.g_Control.CreateControl("battle_select");
		this._battle_select_scene.visible = false;
		this._main_layer.AddChild(this._battle_select_scene);
		this._battle_scene = BattleCity.g_Control.CreateControl("battle_scene");
		this._battle_scene.visible = false;
		this._main_layer.AddChild(this._battle_scene);
		this._battle_settlement = BattleCity.g_Control.CreateControl("battle_settlement");
		this._battle_settlement.visible = false;
		this._main_layer.AddChild(this._battle_settlement);
		this._edit_scene = BattleCity.g_Control.CreateControl("edit_scene");
		this._edit_scene.visible = false;
		this._main_layer.AddChild(this._edit_scene);
		this.Restart();
	},
	Shutdown : function() {
	},
	get player_count() {
		return this._player_count;
	},
	get player1_data() {
		return this._player1;
	},
	get player2_data() {
		return this._player2;
	},
	get battle_scene() {
		return this._battle_scene;
	},
	get battle_settlement() {
		return this._battle_settlement;
	},
	get edit_scene() {
		return this._edit_scene;
	},
	get stage() {
		return this._stage;
	},
	Restart : function() {
		this._battle_scene.Hide();
		this._player1 = {};
		this._player1.level = 1;
		this._player1.life = 3;
		this._player1.score = 0;
		this._player2 = {};
		this._player2.level = 1;
		this._player2.life = 3;
		this._player2.score = 0;
		this._login_scene.Show();
	},
	StartPlay : function(player_count) {
		this._player_count = player_count;
		this._stage = 1;
		this._battle_select_scene.Show(this._stage);
	},
	NextStage : function() {
		this._stage = this._stage + (1);
		if (this._stage > 10) {
			this._stage = 1;
		}
		this._battle_select_scene.Show(this._stage);
	},
}, "BattleCity.GCenter");

window.g_GCenter = ALittle.NewObject(BattleCity.GCenter);
}