{
if (typeof SuperMarioBros === "undefined") window.SuperMarioBros = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
SuperMarioBros.StageScene = JavaScript.Class(ALittle.DisplayLayout, {
	Show : function(world, subworld) {
		this.visible = true;
		this._score.text = g_GCenter.player_data.score;
		this._coin.text = 0;
		this._stage.text = g_GCenter.player_data.world + "-" + g_GCenter.player_data.subworld;
		this._time.text = 0;
		this._stage_text.text = this._stage.text;
		this._life_text.text = g_GCenter.player_data.life;
		if (this._loop !== undefined) {
			this._loop.Stop();
		}
		this._loop = ALittle.NewObject(ALittle.LoopTimer, this.ShowTimeOut.bind(this, world, subworld), 1000);
		this._loop.Start();
	},
	ShowTimeOut : function(world, subworld) {
		g_GCenter.battle_scene.Show(world, subworld);
		this.Hide();
	},
	Hide : function() {
		this.visible = false;
	},
}, "SuperMarioBros.StageScene");

}