{
if (typeof BattleCity === "undefined") window.BattleCity = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
BattleCity.BattleSelectScene = JavaScript.Class(ALittle.DisplayLayout, {
	Show : function(stage) {
		this.visible = true;
		this._stage_num.text = stage;
		if (this._anti_loop !== undefined) {
			this._anti_loop.Stop();
			this._anti_loop = undefined;
		}
		this._quad_up.y = -this._quad_up.height;
		this._quad_down.y = A_UISystem.view_height;
		this._stage_container.visible = true;
		this._anti_loop = ALittle.NewObject(ALittle.LoopList);
		let group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._quad_up, "y", 0, 1000, 0));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._quad_down, "y", 0, 1000, 0));
		this._anti_loop.AddUpdater(group);
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, g_GCenter.battle_scene.Show.bind(g_GCenter.battle_scene, stage), 0));
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopAttribute, this, "visible", false, 0));
		this._anti_loop.Start();
	},
}, "BattleCity.BattleSelectScene");

}