{
if (typeof BattleCity === "undefined") window.BattleCity = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
BattleCity.LoginScene = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._select_option = 1;
	},
	TCtor : function() {
		this._high_score.text = BattleCity.g_GConfig.GetInt("high_score", 2000);
		this._last_score_1.text = BattleCity.g_GConfig.GetInt("last_score_1", 0);
		this._last_score_2.text = BattleCity.g_GConfig.GetInt("last_score_2", 0);
		this._cursor.Stop();
		this.disabled = true;
	},
	Show : function() {
		this.visible = true;
		if (this._anti_loop !== undefined) {
			this._anti_loop.Stop();
			this._anti_loop = undefined;
		}
		this.y = A_UISystem.view_height;
		this._cursor.visible = false;
		this._anti_loop = ALittle.NewObject(ALittle.LoopList);
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "y", 0, 10000, 0));
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopAttribute, this._cursor, "visible", true, 0));
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, this._cursor.Play.bind(this._cursor), 0));
		this._anti_loop.Start();
		A_UISystem.keydown_callback = this.HandleKeyDown.bind(this);
	},
	Hide : function() {
		if (this._anti_loop !== undefined) {
			this._anti_loop.Stop();
			this._anti_loop = undefined;
		}
		this._cursor.Stop();
		this.visible = false;
		A_UISystem.keydown_callback = undefined;
	},
	HandleKeyDown : function(mod, sym, scancode) {
		if (this._cursor.visible === false) {
			if (sym === 103 || sym === 104) {
				this._anti_loop.SetCompleted();
			}
			return;
		}
		if (sym === 103) {
			this._select_option = this._select_option + (1);
			if (this._select_option > 3) {
				this._select_option = 1;
			}
			if (this._select_option === 1) {
				this._cursor.y = this._1_player_text.y + this._1_player_text.height / 2 - this._cursor.height / 2;
			} else if (this._select_option === 2) {
				this._cursor.y = this._2_player_text.y + this._2_player_text.height / 2 - this._cursor.height / 2;
			} else if (this._select_option === 3) {
				this._cursor.y = this._edit_text.y + this._edit_text.height / 2 - this._cursor.height / 2;
			}
			return;
		}
		if (sym === 104) {
			this.Hide();
			if (this._select_option === 3) {
				g_GCenter.edit_scene.Show();
			} else {
				g_GCenter.StartPlay(this._select_option);
			}
		}
	},
}, "BattleCity.LoginScene");

}