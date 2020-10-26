{
if (typeof SuperMarioBros === "undefined") window.SuperMarioBros = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
SuperMarioBros.LoginScene = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._option = 1;
	},
	Show : function() {
		this.visible = true;
		A_UISystem.keydown_callback = this.HandleKeyDown.bind(this);
		g_GCenter.player_data.life = 3;
		this._top_score.text = SuperMarioBros.g_GConfig.GetInt("top_score", 0);
		this._score.text = g_GCenter.player_data.score;
		this._coin.text = 0;
	},
	HandleKeyDown : function(mod, sym, scancode) {
		if (sym === 103) {
			this._option = this._option + (1);
			if (this._option > 2) {
				this._option = 1;
			}
			if (this._option === 1) {
				this._select_cursor.y = this._startgame_text.y + this._startgame_text.height / 2 - this._select_cursor.height / 2;
			} else if (this._option === 2) {
				this._select_cursor.y = this._editworld_text.y + this._editworld_text.height / 2 - this._select_cursor.height / 2;
			}
		}
		if (sym === 104) {
			if (this._option === 2) {
				A_UISystem.keydown_callback = undefined;
				this.Hide();
				g_GCenter.edit_scene.Show();
			} else if (this._option === 1) {
				A_UISystem.keydown_callback = undefined;
				this.Hide();
				g_GCenter.stage_scene.Show(1, 1);
			}
		}
	},
	UpdateTopScore : function() {
		let top_score = SuperMarioBros.g_GConfig.GetInt("top_score", 0);
		if (top_score < g_GCenter.player_data.score) {
			top_score = g_GCenter.player_data.score;
			SuperMarioBros.g_GConfig.SetConfig("top_score", top_score);
			this._score.text = g_GCenter.player_data.score;
		}
	},
	Hide : function() {
		this.visible = false;
	},
}, "SuperMarioBros.LoginScene");

}