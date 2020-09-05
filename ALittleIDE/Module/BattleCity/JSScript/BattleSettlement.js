{
if (typeof BattleCity === "undefined") window.BattleCity = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
BattleCity.BattleSettlement = JavaScript.Class(ALittle.DisplayLayout, {
	Show : function(player1_kill, player2_kill) {
		this.visible = true;
		if (this._show_loop !== undefined) {
			this._show_loop.Stop();
			this._show_loop = undefined;
		}
		this._player_1_container.visible = g_GCenter.player_count >= 1;
		this._player_2_container.visible = g_GCenter.player_count >= 2;
		let player_1_total = 0;
		let player_2_total = 0;
		let player_1_count = player1_kill.get(1);
		if (player_1_count === undefined) {
			player_1_count = 0;
		}
		let player_2_count = player2_kill.get(1);
		if (player_2_count === undefined) {
			player_2_count = 0;
		}
		player_1_total = player_1_total + (player_1_count);
		player_2_total = player_2_total + (player_2_count);
		this._show_loop = ALittle.NewObject(ALittle.LoopList);
		this._1_enemy_1_count.text = 0;
		this._1_enemy_1_score.text = 0;
		this._1_enemy_2_count.text = 0;
		this._1_enemy_2_score.text = 0;
		this._1_enemy_3_count.text = 0;
		this._1_enemy_3_score.text = 0;
		this._1_enemy_total.text = "";
		this._2_enemy_1_count.text = 0;
		this._2_enemy_1_score.text = 0;
		this._2_enemy_2_count.text = 0;
		this._2_enemy_2_score.text = 0;
		this._2_enemy_3_count.text = 0;
		this._2_enemy_3_score.text = 0;
		this._2_enemy_total.text = "";
		this._high_score.text = BattleCity.g_GConfig.GetInt("high_score", 2000);
		this._stage_num.text = g_GCenter.stage;
		let player1_data = g_GCenter.player1_data;
		let player2_data = g_GCenter.player2_data;
		this._player_1_score.text = player1_data.score;
		this._player_2_score.text = player2_data.score;
		let group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopFunction, this.HandlePlayerEnemyScore.bind(this, this._1_enemy_1_count, this._1_enemy_1_score, this._player_1_score, 1, player1_data), player_1_count, 500, 500));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopFunction, this.HandlePlayerEnemyScore.bind(this, this._2_enemy_1_count, this._2_enemy_1_score, this._player_2_score, 1, player2_data), player_2_count, 500, 500));
		this._show_loop.AddUpdater(group);
		player_1_count = player1_kill.get(2);
		if (player_1_count === undefined) {
			player_1_count = 0;
		}
		player_2_count = player2_kill.get(2);
		if (player_2_count === undefined) {
			player_2_count = 0;
		}
		player_1_total = player_1_total + (player_1_count);
		player_2_total = player_2_total + (player_2_count);
		group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopFunction, this.HandlePlayerEnemyScore.bind(this, this._1_enemy_2_count, this._1_enemy_2_score, this._player_1_score, 2, player1_data), player_1_count, 500, 500));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopFunction, this.HandlePlayerEnemyScore.bind(this, this._2_enemy_2_count, this._2_enemy_2_score, this._player_2_score, 2, player2_data), player_2_count, 500, 500));
		this._show_loop.AddUpdater(group);
		player_1_count = player1_kill.get(3);
		if (player_1_count === undefined) {
			player_1_count = 0;
		}
		player_2_count = player2_kill.get(3);
		if (player_2_count === undefined) {
			player_2_count = 0;
		}
		player_1_total = player_1_total + (player_1_count);
		player_2_total = player_2_total + (player_2_count);
		group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopFunction, this.HandlePlayerEnemyScore.bind(this, this._1_enemy_3_count, this._1_enemy_3_score, this._player_1_score, 3, player1_data), player_1_count, 500, 500));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopFunction, this.HandlePlayerEnemyScore.bind(this, this._2_enemy_3_count, this._2_enemy_3_score, this._player_2_score, 3, player2_data), player_2_count, 500, 500));
		this._show_loop.AddUpdater(group);
		group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, this.HandlePlayerTotalScore.bind(this, this._1_enemy_total, player_1_total), 1000));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, this.HandlePlayerTotalScore.bind(this, this._2_enemy_total, player_2_total), 1000));
		this._show_loop.AddUpdater(group);
		this._show_loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, this.Hide.bind(this), 1000));
		this._show_loop.Start();
	},
	HandlePlayerEnemyScore : function(count_text, score_text, player_score, level, player_data) {
		let count = ALittle.Math_ToInt(count_text.text);
		count = count + (1);
		count_text.text = count;
		let score = ALittle.Math_ToInt(score_text.text);
		score = score + (level * 100);
		score_text.text = score;
		player_data.score = player_data.score + (score);
		player_score.text = player_data.score;
		let high_score = BattleCity.g_GConfig.GetInt("high_score", 2000);
		if (player_data.score >= high_score) {
			high_score = player_data.score;
			BattleCity.g_GConfig.SetConfig("high_score", high_score, true);
			this._high_score.text = high_score;
		}
	},
	HandlePlayerTotalScore : function(total, value) {
		total.text = value;
	},
	Hide : function() {
		if (g_GCenter.player_count >= 1) {
			BattleCity.g_GConfig.SetConfig("last_score_1", g_GCenter.player1_data.score, true);
		}
		if (g_GCenter.player_count >= 2) {
			BattleCity.g_GConfig.SetConfig("last_score_2", g_GCenter.player2_data.score, true);
		}
		BattleCity.g_GConfig.SaveConfig();
		this.visible = false;
		g_GCenter.NextStage();
	},
}, "BattleCity.BattleSettlement");

}