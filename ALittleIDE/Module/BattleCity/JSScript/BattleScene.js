{
if (typeof BattleCity === "undefined") window.BattleCity = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
BattleCity.BattleScene = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._enemy_count = 0;
		this._generate_enemy_cool = 0;
		this._enemy_width = 0;
		this._enemy_height = 0;
		this._iron_flash = false;
		this._iron_flash_frame = 0;
		this._iron_flash_brush = 0;
		this._iron_flash_count = 0;
		this._river_flash_frame = 0;
		this._river_flash_brush = 0;
		this._is_gameover = false;
	},
	TCtor : function() {
		this._player_1 = BattleCity.g_Control.CreateControl("battle_player1");
		this._player_2 = BattleCity.g_Control.CreateControl("battle_player2");
		this._cell_size = this._tile_container.width / (13 * 4);
		let enemy = BattleCity.g_Control.CreateControl("battle_enemy");
		this._enemy_width = enemy.width;
		this._enemy_height = enemy.height;
	},
	get cell_size() {
		return this._cell_size;
	},
	get is_gameover() {
		return this._is_gameover;
	},
	Show : async function(stage) {
		this._player1_kill = new Map();
		this._player2_kill = new Map();
		if (this._anti_loop !== undefined) {
			this._anti_loop.Stop();
			this._anti_loop = undefined;
		}
		this._battle_map = await BattleCity.g_Control.LoadMessageFromFile(___all_struct.get(-922796193), "Other/Map/stage_" + stage + ".map");
		if (this._battle_map === undefined) {
			ALittle.Error("map load filed! Other/Map/stage_" + stage + ".map");
			return;
		}
		this._tile_container.RemoveAllChild();
		this._grass_container.RemoveAllChild();
		this._sprite_map = new Map();
		this._river_map = new Map();
		for (let [row, sub_map] of this._battle_map.tile_map) {
			if (sub_map === undefined) continue;
			for (let [col, type] of sub_map) {
				if (type === undefined) continue;
				this.SetTileShow(row, col, type);
			}
		}
		for (let [row, sub_map] of this._sprite_map) {
			if (sub_map === undefined) continue;
			for (let [col, sprite] of sub_map) {
				if (sprite === undefined) continue;
				if (sprite.col_index >= (BattleCity.BrushType.BT_RIVER - 1) * 4 + 1 && sprite.col_index <= (BattleCity.BrushType.BT_RIVER) * 4) {
					let r_sub_map = this._river_map.get(row);
					if (r_sub_map === undefined) {
						r_sub_map = new Map();
						this._river_map.set(row, r_sub_map);
					}
					r_sub_map.set(col, sprite);
				}
			}
		}
		this._river_flash_brush = BattleCity.BrushType.BT_RIVER;
		if (this._castle_explosion !== undefined) {
			this._castle_explosion.Stop();
			this._castle_explosion.visible = false;
		}
		this.visible = true;
		this._is_gameover = false;
		this._gameover_image.visible = false;
		this._iron_flash = false;
		this._iron_flash_brush = BattleCity.BrushType.BT_WALL;
		this._stage_num.text = stage;
		this._player1_life.text = g_GCenter.player1_data.life - 1;
		this._player2_life.text = g_GCenter.player2_data.life - 1;
		this._enemy_tiletable.RemoveAllChild();
		for (let i = 1; i <= 20; i += 1) {
			let icon = BattleCity.g_Control.CreateControl("enemy_icon");
			this._enemy_tiletable.AddChild(icon);
		}
		this._enemy_map = new Map();
		this._enemy_count = 0;
		this._generate_enemy_cool = 1000;
		this._bullet_container.RemoveAllChild();
		this._bullet_map = new Map();
		this._entity_container.RemoveAllChild();
		let ___OBJECT_1 = this._item_container.childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			child.Stop();
		}
		this._item_container.RemoveAllChild();
		this._player_1.RemoveFromParent();
		this._player_2.RemoveFromParent();
		this._player1_contianer.visible = g_GCenter.player_count >= 1;
		this._player2_contianer.visible = g_GCenter.player_count >= 2;
		this._quad_up.y = 0;
		this._quad_up.visible = true;
		this._quad_down.y = 0;
		this._quad_down.visible = true;
		this._anti_loop = ALittle.NewObject(ALittle.LoopList);
		let group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._quad_up, "y", -this._quad_up.height, 500, 0));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._quad_down, "y", A_UISystem.view_height, 500, 0));
		this._anti_loop.AddUpdater(group);
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, this.Start.bind(this), 0));
		this._anti_loop.Start();
		A_UISystem.keydown_callback = this.HandleKeyDown.bind(this);
		if (this._frame_loop !== undefined) {
			this._frame_loop.Stop();
		}
		this._frame_loop = ALittle.NewObject(ALittle.LoopFrame, this.HandleFrame.bind(this));
		this._frame_loop.Start();
	},
	Hide : function() {
		if (this._frame_loop !== undefined) {
			this._frame_loop.Stop();
			this._frame_loop = undefined;
		}
		if (this._anti_loop !== undefined) {
			this._anti_loop.Stop();
			this._anti_loop = undefined;
		}
		let ___OBJECT_2 = this._item_container.childs;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let child = ___OBJECT_2[index - 1];
			if (child === undefined) break;
			child.Stop();
		}
		this._item_container.RemoveAllChild();
		if (this._castle_explosion !== undefined) {
			this._castle_explosion.Stop();
			this._castle_explosion.visible = false;
		}
		if (this._gameover_loop !== undefined) {
			this._gameover_loop.Stop();
			this._gameover_loop = undefined;
		}
		this.visible = false;
	},
	SetTileShow : function(row, col, type) {
		let sub_map = this._sprite_map.get(row);
		if (sub_map === undefined) {
			sub_map = new Map();
			this._sprite_map.set(row, sub_map);
		}
		if (sub_map.get(col) !== undefined) {
			sub_map.get(col).RemoveFromParent();
		}
		let sprite = ALittle.NewObject(ALittle.Sprite, BattleCity.g_Control);
		sprite.texture_name = "tile.png";
		sprite.width = 32 / 4;
		sprite.height = 32 / 4;
		sprite.x = col * sprite.width;
		sprite.y = row * sprite.height;
		sprite.row_count = 4;
		sprite.col_count = 7 * 4;
		sprite.row_index = row % 4 + 1;
		sprite.col_index = col % 4 + 1 + (type - 1) * 4;
		if (type === BattleCity.BrushType.BT_GRASS) {
			this._grass_container.AddChild(sprite);
		} else {
			this._tile_container.AddChild(sprite);
		}
		sub_map.set(col, sprite);
	},
	TryRemoveWall : function(row, col) {
		let sub_map = this._sprite_map.get(row);
		if (sub_map === undefined) {
			return false;
		}
		let sprite = sub_map.get(col);
		if (sprite === undefined) {
			return false;
		}
		if (sprite.col_index >= (BattleCity.BrushType.BT_WALL - 1) * 4 + 1 && sprite.col_index <= (BattleCity.BrushType.BT_WALL) * 4) {
			this._tile_container.RemoveChild(sprite);
			sub_map.delete(col);
			return true;
		}
		return false;
	},
	RemoveTileShow : function(row, col) {
		let sub_map = this._sprite_map.get(row);
		if (sub_map === undefined) {
			return;
		}
		if (sub_map.get(col) !== undefined) {
			this._tile_container.RemoveChild(sub_map.get(col));
			sub_map.delete(col);
		}
	},
	CanWalkByMap : function(row, col) {
		let sub_map = this._sprite_map.get(row);
		if (sub_map === undefined) {
			return true;
		}
		let sprite = sub_map.get(col);
		if (sprite === undefined) {
			return true;
		}
		return sprite.col_index >= (BattleCity.BrushType.BT_GRASS - 1) * 4 + 1 && sprite.col_index <= (BattleCity.BrushType.BT_GRASS) * 4;
	},
	Collision : function(left, top, right, bottom, target) {
		let not_check = right < target.x || bottom < target.y || target.x + target.width < left || target.y + target.height < top;
		return !not_check;
	},
	Collision2 : function(target_1, target_2) {
		return this.Collision(target_1.x, target_1.y, target_1.x + target_1.width, target_1.y + target_1.height, target_2);
	},
	CanWalkByEntity : function(entity, left, top, right, bottom) {
		if (this._player_1.parent !== undefined && entity !== this._player_1 && !this._player_1.explosion && this.Collision(left, top, right, bottom, this._player_1)) {
			return false;
		}
		if (this._player_2.parent !== undefined && entity !== this._player_2 && !this._player_2.explosion && this.Collision(left, top, right, bottom, this._player_2)) {
			return false;
		}
		for (let [role, _] of this._enemy_map) {
			if (_ === undefined) continue;
			if (entity !== role && !role.explosion && this.Collision(left, top, right, bottom, role)) {
				return false;
			}
		}
		return true;
	},
	BulletCollisionByEntity : function(bullet, left, top, right, bottom) {
		if (bullet.role.is_enemy && this._player_1.parent !== undefined && bullet.role !== this._player_1 && this._player_1.alive && this.Collision(left, top, right, bottom, this._player_1)) {
			return [true, this._player_1.BeAttack()];
		}
		if (bullet.role.is_enemy && this._player_2.parent !== undefined && bullet.role !== this._player_2 && this._player_1.alive && this.Collision(left, top, right, bottom, this._player_2)) {
			return [true, this._player_2.BeAttack()];
		}
		if (!bullet.role.is_enemy) {
			for (let [role, _] of this._enemy_map) {
				if (_ === undefined) continue;
				if (role !== bullet.role && role.alive && this.Collision(left, top, right, bottom, role)) {
					let death = role.BeAttack();
					if (death) {
						if (bullet.role === this._player_1) {
							let count = this._player1_kill.get(role.level);
							if (count === undefined) {
								count = 0;
							}
							count = count + (1);
							this._player1_kill.set(role.level, count);
						} else if (bullet.role === this._player_2) {
							let count = this._player2_kill.get(role.level);
							if (count === undefined) {
								count = 0;
							}
							count = count + (2);
							this._player2_kill.set(role.level, count);
						}
					}
					return [true, death];
				}
			}
		}
		return [false, false];
	},
	ShowGameOver : function() {
		if (this._is_gameover) {
			return;
		}
		this._is_gameover = true;
		this._gameover_image.visible = true;
		this._gameover_loop = ALittle.NewObject(ALittle.LoopList);
		this._gameover_loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._gameover_image, "y", A_UISystem.view_height / 2, 2000, 0));
		this._gameover_loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, g_GCenter.Restart.bind(g_GCenter), 1000));
		this._gameover_loop.Start();
	},
	StageCompleted : function() {
		g_GCenter.player1_data.level = this._player_1.level;
		g_GCenter.player2_data.level = this._player_2.level;
		g_GCenter.battle_settlement.Show(this._player1_kill, this._player2_kill);
		this.Hide();
	},
	BulletCollisionByMap : function(row, col, min_or_max, dir) {
		let sub_map = this._sprite_map.get(row);
		if (sub_map === undefined) {
			return false;
		}
		let sprite = sub_map.get(col);
		if (sprite === undefined) {
			return false;
		}
		if (sprite.col_index >= (BattleCity.BrushType.BT_IRON - 1) * 4 + 1 && sprite.col_index <= (BattleCity.BrushType.BT_IRON) * 4) {
			return true;
		}
		if (sprite.col_index >= (BattleCity.BrushType.BT_GRASS - 1) * 4 + 1 && sprite.col_index <= (BattleCity.BrushType.BT_GRASS) * 4) {
			return false;
		}
		if (sprite.col_index >= (BattleCity.BrushType.BT_RIVER - 1) * 4 + 1 && sprite.col_index <= (BattleCity.BrushType.BT_RIVER) * 4) {
			return false;
		}
		if (sprite.col_index >= (BattleCity.BrushType.BT_RIVER2 - 1) * 4 + 1 && sprite.col_index <= (BattleCity.BrushType.BT_RIVER2) * 4) {
			return false;
		}
		if (sprite.col_index >= (BattleCity.BrushType.BT_CASTLE2 - 1) * 4 + 1 && sprite.col_index <= (BattleCity.BrushType.BT_CASTLE2) * 4) {
			return false;
		}
		if (sprite.col_index >= (BattleCity.BrushType.BT_CASTLE - 1) * 4 + 1 && sprite.col_index <= (BattleCity.BrushType.BT_CASTLE) * 4) {
			for (let r = 12 * 4; r < 13 * 4; r += 1) {
				for (let c = 6 * 4; c < 7 * 4; c += 1) {
					this.SetTileShow(r, c, BattleCity.BrushType.BT_CASTLE2);
				}
			}
			if (this._castle_explosion === undefined) {
				this._castle_explosion = BattleCity.g_Control.CreateControl("effect_explosion_big");
				this._castle_explosion.x = this.map_size / 2 - this._castle_explosion.width / 2;
				this._castle_explosion.y = this.map_size - this._cell_size * 2 - this._castle_explosion.height / 2;
				this._effect_container.AddChild(this._castle_explosion);
			}
			this._castle_explosion.visible = true;
			this._castle_explosion.Play();
			this.ShowGameOver();
			return true;
		}
		if (sprite.col_index >= (BattleCity.BrushType.BT_WALL - 1) * 4 + 1 && sprite.col_index <= (BattleCity.BrushType.BT_WALL) * 4) {
			if (dir === BattleCity.DirType.DT_UP || dir === BattleCity.DirType.DT_DOWN) {
				this.TryRemoveWall(row, col);
				if (min_or_max) {
					this.TryRemoveWall(row, col - 1);
				} else {
					this.TryRemoveWall(row, col + 1);
				}
			} else {
				this.TryRemoveWall(row, col);
				if (min_or_max) {
					this.TryRemoveWall(row - 1, col);
				} else {
					this.TryRemoveWall(row + 1, col);
				}
			}
			return true;
		}
		return false;
	},
	IsEnemyStopping : function() {
		return this._item_stop_delay_loop !== undefined && !this._item_stop_delay_loop.IsCompleted();
	},
	FireBullet : function(role, speed) {
		let bullet = BattleCity.g_Control.CreateControl("battle_bullet");
		if (role.dir === BattleCity.DirType.DT_UP) {
			bullet.x = role.x + role.width / 2 - bullet.width / 2;
			bullet.y = role.y;
		} else if (role.dir === BattleCity.DirType.DT_RIGHT) {
			bullet.x = role.x + role.width - bullet.width;
			bullet.y = role.y + role.height / 2 - bullet.height / 2;
		} else if (role.dir === BattleCity.DirType.DT_DOWN) {
			bullet.x = role.x + role.width / 2 - bullet.width / 2;
			bullet.y = role.y + role.height - bullet.height;
		} else {
			bullet.x = role.x;
			bullet.y = role.y + role.height / 2 - bullet.height / 2;
		}
		bullet.Init(role.dir, role, speed);
		this._bullet_container.AddChild(bullet);
		this._bullet_map.set(bullet, true);
	},
	GenerateItem : function() {
		let ___OBJECT_3 = this._item_container.childs;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let child = ___OBJECT_3[index - 1];
			if (child === undefined) break;
			child.Stop();
		}
		this._item_container.RemoveAllChild();
		let row = ALittle.Math_RandomInt(0, 12 * 4);
		let col = ALittle.Math_RandomInt(0, 12 * 4);
		let item_type = ALittle.Math_RandomInt(BattleCity.ItemType.IT_LIFE, BattleCity.ItemType.IT_SHIELD);
		let item = BattleCity.g_Control.CreateControl("battle_item");
		item.sprite.col_index = item_type;
		item.x = row * this._cell_size;
		item.y = col * this._cell_size;
		this._item_container.AddChild(item);
		item.Play();
	},
	GenerateEnemy : function() {
		let born_pos = [];
		born_pos[1 - 1] = 0;
		born_pos[2 - 1] = 6;
		born_pos[3 - 1] = 12;
		ALittle.List_Shuffle(born_pos);
		let ___OBJECT_4 = born_pos;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let pos = ___OBJECT_4[index - 1];
			if (pos === undefined) break;
			let failed = false;
			for (let row = 0; row < 4; row += 1) {
				for (let col = pos * 4; col < (pos + 1) * 4; col += 1) {
					if (!this.CanWalkByMap(row, col)) {
						failed = true;
						break;
					}
				}
				if (failed) {
					break;
				}
			}
			if (!failed) {
				let left = pos * 4 * this._cell_size;
				let right = left + this._enemy_width;
				if (!this.CanWalkByEntity(undefined, left, 0, right, this._enemy_height)) {
					failed = true;
				}
			}
			if (!failed) {
				this._enemy_tiletable.RemoveChild(this._enemy_tiletable.childs[this._enemy_tiletable.child_count - 1]);
				let enemy = BattleCity.g_Control.CreateControl("battle_enemy");
				this._enemy_map.set(enemy, true);
				enemy.StartBorn(0, pos * 4, ALittle.Math_RandomInt(1, 3), BattleCity.DirType.DT_DOWN, ALittle.Math_RandomInt(1, 100) > 80);
				this._entity_container.AddChild(enemy);
				this._enemy_count = this._enemy_count + (1);
				this._generate_enemy_cool = 1000;
				break;
			}
		}
	},
	get map_size() {
		return this._tile_container.width;
	},
	Start : function() {
		if (g_GCenter.player_count >= 1) {
			this._entity_container.AddChild(this._player_1);
			this._player_1.StartBorn(12 * 4, 4 * 4, g_GCenter.player1_data.level, BattleCity.DirType.DT_UP, 0.08);
		}
		if (g_GCenter.player_count >= 2) {
			this._entity_container.AddChild(this._player_2);
			this._player_2.StartBorn(12 * 4, 8 * 4, g_GCenter.player2_data.level, BattleCity.DirType.DT_UP, 0.08);
		}
	},
	HandleFrame : function(frame_time) {
		if (this._enemy_count < 4 && this._enemy_tiletable.child_count > 0) {
			this._generate_enemy_cool = this._generate_enemy_cool - (frame_time);
			if (this._generate_enemy_cool <= 0) {
				this.GenerateEnemy();
			}
		}
		if (!this._is_gameover) {
			if (A_UISystem.sym_map.get(97)) {
				if (this._player_1.parent !== undefined && this._player_1.alive) {
					this._player_1.Walk(BattleCity.DirType.DT_LEFT, frame_time);
				}
			} else if (A_UISystem.sym_map.get(119)) {
				if (this._player_1.parent !== undefined && this._player_1.alive) {
					this._player_1.Walk(BattleCity.DirType.DT_UP, frame_time);
				}
			} else if (A_UISystem.sym_map.get(115)) {
				if (this._player_1.parent !== undefined && this._player_1.alive) {
					this._player_1.Walk(BattleCity.DirType.DT_DOWN, frame_time);
				}
			} else if (A_UISystem.sym_map.get(100)) {
				if (this._player_1.parent !== undefined && this._player_1.alive) {
					this._player_1.Walk(BattleCity.DirType.DT_RIGHT, frame_time);
				}
			}
			if (A_UISystem.sym_map.get(1073741904)) {
				if (this._player_2.parent !== undefined && this._player_2.alive) {
					this._player_2.Walk(BattleCity.DirType.DT_LEFT, frame_time);
				}
			} else if (A_UISystem.sym_map.get(1073741906)) {
				if (this._player_2.parent !== undefined && this._player_2.alive) {
					this._player_2.Walk(BattleCity.DirType.DT_UP, frame_time);
				}
			} else if (A_UISystem.sym_map.get(1073741905)) {
				if (this._player_2.parent !== undefined && this._player_2.alive) {
					this._player_2.Walk(BattleCity.DirType.DT_DOWN, frame_time);
				}
			} else if (A_UISystem.sym_map.get(1073741903)) {
				if (this._player_2.parent !== undefined && this._player_2.alive) {
					this._player_2.Walk(BattleCity.DirType.DT_RIGHT, frame_time);
				}
			}
		}
		if (this._player_1.parent !== undefined) {
			this._player_1.UpdateFrame(frame_time);
		}
		if (this._player_2.parent !== undefined) {
			this._player_2.UpdateFrame(frame_time);
		}
		for (let [enemy, _] of this._enemy_map) {
			if (_ === undefined) continue;
			enemy.UpdateFrame(frame_time);
		}
		for (let [bullet, _] of this._bullet_map) {
			if (_ === undefined) continue;
			bullet.UpdateFrame(frame_time);
		}
		for (let [bullet_1, _1] of this._bullet_map) {
			if (_1 === undefined) continue;
			for (let [bullet_2, _2] of this._bullet_map) {
				if (_2 === undefined) continue;
				if (bullet_1 !== bullet_2 && bullet_1.alive && bullet_2.alive && bullet_1.role.is_enemy !== bullet_2.role.is_enemy && this.Collision2(bullet_1, bullet_2)) {
					bullet_1.BulletEnd();
					bullet_2.BulletEnd();
				}
			}
		}
		let remove_map = undefined;
		let ___OBJECT_5 = this._item_container.childs;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let child = ___OBJECT_5[index - 1];
			if (child === undefined) break;
			let player = undefined;
			let player_data = undefined;
			let player_life = undefined;
			if (this._player_1.parent !== undefined && this._player_1.alive && this.Collision2(this._player_1, child)) {
				player = this._player_1;
				player_data = g_GCenter.player1_data;
				player_life = this._player1_life;
			} else if (this._player_2.parent !== undefined && this._player_2.alive && this.Collision2(this._player_2, child)) {
				player = this._player_2;
				player_data = g_GCenter.player2_data;
				player_life = this._player2_life;
			}
			if (player !== undefined) {
				if (child.sprite.col_index === BattleCity.ItemType.IT_LIFE) {
					player_data.life = player_data.life + (1);
					player_life.text = player_data.life - 1;
				} else if (child.sprite.col_index === BattleCity.ItemType.IT_STAR) {
					player.LevelUp();
					player_data.level = player.level;
				} else if (child.sprite.col_index === BattleCity.ItemType.IT_BOMB) {
					for (let [enemy, _] of this._enemy_map) {
						if (_ === undefined) continue;
						if (enemy.alive) {
							enemy.StartExplosion();
						}
					}
				} else if (child.sprite.col_index === BattleCity.ItemType.IT_IRON) {
					this._iron_flash = false;
					this._iron_flash_count = 0;
					this._iron_flash_frame = 0;
					let brush_type = BattleCity.BrushType.BT_IRON;
					for (let row = 11 * 4 + 2; row <= 11 * 4 + 3; row += 1) {
						for (let col = 5 * 4 + 2; col <= 5 * 4 + 9; col += 1) {
							this.SetTileShow(row, col, brush_type);
						}
					}
					for (let row = 12 * 4 + 0; row <= 12 * 4 + 3; row += 1) {
						for (let col = 5 * 4 + 2; col <= 5 * 4 + 3; col += 1) {
							this.SetTileShow(row, col, brush_type);
						}
					}
					for (let row = 12 * 4 + 0; row <= 12 * 4 + 3; row += 1) {
						for (let col = 5 * 4 + 8; col <= 5 * 4 + 9; col += 1) {
							this.SetTileShow(row, col, brush_type);
						}
					}
					if (this._iron_flash_delay_loop !== undefined) {
						this._iron_flash_delay_loop.Stop();
					}
					this._iron_flash_delay_loop = ALittle.NewObject(ALittle.LoopTimer, this.StartIronFlash.bind(this), 10000);
					this._iron_flash_delay_loop.Start();
				} else if (child.sprite.col_index === BattleCity.ItemType.IT_SHIELD) {
					player.StartShield();
				} else if (child.sprite.col_index === BattleCity.ItemType.IT_STOP) {
					if (this._item_stop_delay_loop !== undefined) {
						this._item_stop_delay_loop.Stop();
					}
					this._item_stop_delay_loop = ALittle.NewObject(ALittle.LoopTimer, this.ItemStopEnd.bind(this), 10000);
					this._item_stop_delay_loop.Start();
				}
				if (remove_map === undefined) {
					remove_map = new Map();
				}
				remove_map.set(child, true);
			}
		}
		if (remove_map !== undefined) {
			for (let [child, _] of remove_map) {
				if (_ === undefined) continue;
				this._item_container.RemoveChild(child);
			}
		}
		if (this._iron_flash) {
			let brush_type = BattleCity.BrushType.BT_WALL;
			this._iron_flash_frame = this._iron_flash_frame + (0.005 * frame_time);
			if (this._iron_flash_frame >= 2) {
				this._iron_flash_frame = 0;
			}
			if (this._iron_flash_frame > 1) {
				this._iron_flash_count = this._iron_flash_count + (1);
				brush_type = BattleCity.BrushType.BT_IRON;
			} else {
				if (this._iron_flash_count >= 100) {
					this._iron_flash = false;
				}
			}
			if (this._iron_flash_brush !== brush_type) {
				this._iron_flash_brush = brush_type;
				for (let row = 11 * 4 + 2; row <= 11 * 4 + 3; row += 1) {
					for (let col = 5 * 4 + 2; col <= 5 * 4 + 9; col += 1) {
						this.SetTileShow(row, col, brush_type);
					}
				}
				for (let row = 12 * 4 + 0; row <= 12 * 4 + 3; row += 1) {
					for (let col = 5 * 4 + 2; col <= 5 * 4 + 3; col += 1) {
						this.SetTileShow(row, col, brush_type);
					}
				}
				for (let row = 12 * 4 + 0; row <= 12 * 4 + 3; row += 1) {
					for (let col = 5 * 4 + 8; col <= 5 * 4 + 9; col += 1) {
						this.SetTileShow(row, col, brush_type);
					}
				}
			}
		}
		let brush_type = BattleCity.BrushType.BT_RIVER;
		this._river_flash_frame = this._river_flash_frame + (0.0008 * frame_time);
		if (this._river_flash_frame >= 2) {
			this._river_flash_frame = 0;
		}
		if (this._river_flash_frame > 1) {
			brush_type = BattleCity.BrushType.BT_RIVER2;
		}
		if (this._river_flash_brush !== brush_type) {
			this._river_flash_brush = brush_type;
			for (let [row, sub_map] of this._river_map) {
				if (sub_map === undefined) continue;
				for (let [col, sprite] of sub_map) {
					if (sprite === undefined) continue;
					this.SetTileShow(row, col, this._river_flash_brush);
				}
			}
		}
		if (this._enemy_count <= 0 && this._enemy_tiletable.child_count === 0) {
			this.StageCompleted();
		}
	},
	ItemStopEnd : function() {
		this._item_stop_delay_loop = undefined;
	},
	StartIronFlash : function() {
		this._iron_flash = true;
		this._iron_flash_count = 0;
		this._iron_flash_frame = 0;
	},
	HandleKeyDown : function(mod, sym, scancode) {
		if (sym === 106) {
			if (this._player_1.parent !== undefined && !this._player_1.alive) {
				return;
			}
			this._player_1.Fire();
		}
		if (sym === 1073741913) {
			if (this._player_2.parent !== undefined && !this._player_2.alive) {
				return;
			}
			this._player_2.Fire();
		}
	},
	RoleDeath : function(role) {
		this._entity_container.RemoveChild(role);
		if (role === this._player_1) {
			g_GCenter.player1_data.life = g_GCenter.player1_data.life - (1);
			if (g_GCenter.player_count >= 1 && g_GCenter.player1_data.life >= 1) {
				g_GCenter.player1_data.level = 1;
				this._player1_life.text = g_GCenter.player1_data.life - 1;
				this._entity_container.AddChild(this._player_1);
				this._player_1.StartBorn(12 * 4, 4 * 4, g_GCenter.player1_data.level, BattleCity.DirType.DT_UP, 0.08);
			}
		} else if (role === this._player_2) {
			g_GCenter.player2_data.life = g_GCenter.player2_data.life - (1);
			if (g_GCenter.player_count >= 2 && g_GCenter.player2_data.life >= 1) {
				g_GCenter.player2_data.level = 1;
				this._player2_life.text = g_GCenter.player2_data.life - 1;
				this._entity_container.AddChild(this._player_2);
				this._player_2.StartBorn(12 * 4, 8 * 4, g_GCenter.player2_data.level, BattleCity.DirType.DT_UP, 0.08);
			}
		} else {
			this._enemy_map.delete(role);
			this._enemy_count = this._enemy_count - (1);
		}
		if (g_GCenter.player_count >= 2 && g_GCenter.player1_data.life <= 0 && g_GCenter.player2_data.life <= 0 || g_GCenter.player_count >= 1 && g_GCenter.player1_data.life <= 0) {
			this.ShowGameOver();
		}
	},
	BulletDeath : function(bullet) {
		let exist = this._bullet_map.get(bullet);
		if (exist === undefined) {
			return;
		}
		this._bullet_map.delete(bullet);
		bullet.role.AddBullet();
		this._bullet_container.RemoveChild(bullet);
	},
}, "BattleCity.BattleScene");

}