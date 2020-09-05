{
if (typeof BattleCity === "undefined") window.BattleCity = {};


if (BattleCity.BattleRole === undefined) throw new Error(" extends class:BattleCity.BattleRole is undefined");
BattleCity.BattleEnemy = JavaScript.Class(BattleCity.BattleRole, {
	Ctor : function() {
		this._flash = false;
		this._walk_frame = 0;
		this._flash_frame = 0;
		this._changed_frame = 0;
		this._fire_frame = 0;
	},
	StartBorn : function(row, col, level, dir, flash) {
		this._level = level;
		this._dir = dir;
		this._flash = flash;
		if (this._level === 1) {
			this._speed = 0.08;
		} else if (this._level === 2) {
			this._speed = 0.1;
		} else {
			this._speed = 0.06;
		}
		this._fire_count = 0;
		this.x = col * g_GCenter.battle_scene.cell_size;
		this.y = row * g_GCenter.battle_scene.cell_size;
		this._sprite.visible = false;
		this._effect_explosion.visible = false;
		this._effect_explosion.Stop();
		this._effect_born.visible = true;
		this._effect_born.Play();
		let loop = ALittle.NewObject(ALittle.LoopTimer, this.HandleBornEnd.bind(this), 1000);
		loop.Start();
	},
	HandleBornEnd : function() {
		this._sprite.visible = true;
		this._effect_born.visible = false;
		this.UpdateFrame(0);
		this.UpdateWalk(0);
	},
	BeAttack : function() {
		if (this._flash) {
			this._flash = false;
			g_GCenter.battle_scene.GenerateItem();
			return false;
		}
		this.StartExplosion();
		return true;
	},
	get is_enemy() {
		return true;
	},
	UpdateFrame : function(frame_time) {
		if (this.alive && !g_GCenter.battle_scene.IsEnemyStopping()) {
			this._changed_frame = this._changed_frame + (frame_time * 0.001);
			if (this._changed_frame >= 2) {
				this._changed_frame = 0;
			}
			if (this._changed_frame > 1 && ALittle.Math_RandomInt(1, 100) > 95) {
				this.Walk(ALittle.Math_RandomInt(BattleCity.DirType.DT_UP, BattleCity.DirType.DT_RIGHT), frame_time);
			} else {
				if (!this.Walk(this._dir, frame_time)) {
					this._changed_frame = 1;
				}
			}
			this._fire_frame = this._fire_frame + (frame_time * 0.001);
			if (this._fire_frame >= 2) {
				this._fire_frame = 0;
			}
			if (this._fire_frame > 1 && ALittle.Math_RandomInt(1, 100) > 90) {
				this.Fire();
			}
		}
		this.UpdateSpriteCol(frame_time);
	},
	UpdateWalk : function(frame_time) {
		if (this._dir === BattleCity.DirType.DT_UP) {
			this._sprite.row_index = 1;
		} else if (this._dir === BattleCity.DirType.DT_RIGHT) {
			this._sprite.row_index = 2;
		} else if (this._dir === BattleCity.DirType.DT_DOWN) {
			this._sprite.row_index = 3;
		} else if (this._dir === BattleCity.DirType.DT_LEFT) {
			this._sprite.row_index = 4;
		}
		this._walk_frame = this._walk_frame + (0.01 * frame_time);
		if (this._walk_frame > 2) {
			this._walk_frame = 0;
		}
		this.UpdateSpriteCol(frame_time);
	},
	UpdateSpriteCol : function(frame_time) {
		this._flash_frame = this._flash_frame + (0.005 * frame_time);
		if (this._flash_frame > 2) {
			this._flash_frame = 0;
		}
		if (this._flash && this._flash_frame <= 1) {
			if (this._walk_frame <= 1) {
				this._sprite.col_index = (this._level - 1) * 4 + 2 + 1;
			} else {
				this._sprite.col_index = (this._level - 1) * 4 + 2 + 2;
			}
		} else {
			if (this._walk_frame <= 1) {
				this._sprite.col_index = (this._level - 1) * 4 + 1;
			} else {
				this._sprite.col_index = (this._level - 1) * 4 + 2;
			}
		}
	},
}, "BattleCity.BattleEnemy");

}