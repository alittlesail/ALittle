{
if (typeof SuperMarioBros === "undefined") window.SuperMarioBros = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-873421098, "SuperMarioBros.EntityUserData", {
name : "SuperMarioBros.EntityUserData", ns_name : "SuperMarioBros", rl_name : "EntityUserData", hash_code : -873421098,
name_list : ["type","loop"],
type_list : ["int","ALittle.LoopList"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
SuperMarioBros.BattleScene = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._coin_value = 0;
		this._end_time = 0;
	},
	TCtor : function() {
		this._scroll_screen.container.Init(this._tile_linear);
	},
	Show : async function(world, subworld) {
		this._battle_map = await SuperMarioBros.g_Control.LoadMessageFromFile(___all_struct.get(-876795489), "Other/Map/world_" + world + "_" + subworld + ".map");
		if (this._battle_map === undefined) {
			ALittle.Error("map load filed! Other/Map/world_" + world + "_" + subworld + ".map");
			return;
		}
		this._coin_value = 0;
		this._score.text = g_GCenter.player_data.score;
		this._coin.text = this._coin_value;
		this._stage.text = g_GCenter.player_data.world + "-" + g_GCenter.player_data.subworld;
		this._time.text = 60 * 5;
		let start_time = ALittle.System_GetCurMSTime();
		this._end_time = start_time + 60 * 5 * 1000;
		this._time.text = ALittle.Math_Floor((this._end_time - start_time) / 1000);
		this._tile_linear.RemoveAllChild();
		this._entity_container.RemoveAllChild();
		this._effect_container.RemoveAllChild();
		this._entity_map = new Map();
		this._life_mushroom_map = new Map();
		this._enemy_mushroom_map = new Map();
		this._flag_map = new Map();
		for (let [row, submap] of this._battle_map.background) {
			if (submap === undefined) continue;
			for (let [col, index] of submap) {
				if (index === undefined) continue;
				let show_row = ALittle.Math_Floor(index / SuperMarioBros.TILE_COL_COUNT) + 1;
				let show_col = index % SuperMarioBros.TILE_COL_COUNT + 1;
				this.SetTileShow(row, col, show_row, show_col);
			}
		}
		for (let [row, submap] of this._battle_map.object) {
			if (submap === undefined) continue;
			for (let [col, type] of submap) {
				if (type === undefined) continue;
				if (type === SuperMarioBros.EntityType.ET_BORN_1) {
					this._player.Init(row + 1, col, g_GCenter.player_data.level);
				} else if (type === SuperMarioBros.EntityType.ET_ENEMY_1) {
					let enemy = SuperMarioBros.g_Control.CreateControl("enemy_mushroom");
					enemy.Init(row, col);
					this._enemy_mushroom_map.set(enemy, true);
					this._entity_container.AddChild(enemy);
				} else {
					this.CreateEntity(type, row, col);
				}
			}
		}
		this._scroll_screen.container.width = this._tile_linear.width;
		this._scroll_screen.container_x = 0;
		this._scroll_screen.RefreshClipDisLine();
		this.visible = true;
		A_UISystem.keydown_callback = this.HandleKeyDown.bind(this);
		if (this._frame_loop !== undefined) {
			this._frame_loop.Stop();
		}
		this._frame_loop = ALittle.NewObject(ALittle.LoopFrame, this.HandleFrame.bind(this));
		this._frame_loop.Start();
	},
	CreateEntity : function(type, row, col) {
		let ui = "";
		if (type === SuperMarioBros.EntityType.ET_WALL_1) {
			ui = "wall_1";
		} else if (type === SuperMarioBros.EntityType.ET_HIDE_WALL_1) {
			ui = "hide_wall_1";
		} else if (type === SuperMarioBros.EntityType.ET_RANDOM_WALL_1) {
			ui = "random_wall_1";
		} else if (type === SuperMarioBros.EntityType.ET_FLAG_1) {
			ui = "flag_1";
		} else if (type === SuperMarioBros.EntityType.ET_FLAG_2) {
			ui = "flag_2";
		} else if (type === SuperMarioBros.EntityType.ET_FLAG_3) {
			ui = "flag_3";
		} else if (type === SuperMarioBros.EntityType.ET_FLAG_4) {
			ui = "flag_4";
		} else if (type === SuperMarioBros.EntityType.ET_FLAG_5) {
			ui = "flag_5";
		} else {
			return;
		}
		let entity_sub_map = this._entity_map.get(row);
		if (entity_sub_map === undefined) {
			entity_sub_map = new Map();
			this._entity_map.set(row, entity_sub_map);
		}
		let object = SuperMarioBros.g_Control.CreateControl(ui);
		entity_sub_map.set(col, object);
		object.x = col * SuperMarioBros.TILE_WIDTH;
		object.y = row * SuperMarioBros.TILE_HEIGHT;
		let data = {};
		data.type = type;
		object._user_data = data;
		if (type === SuperMarioBros.EntityType.ET_HIDE_WALL_1) {
			object.visible = false;
		}
		this._entity_container.AddChild(object);
		if (type === SuperMarioBros.EntityType.ET_FLAG_1 || type === SuperMarioBros.EntityType.ET_FLAG_2 || type === SuperMarioBros.EntityType.ET_FLAG_3 || type === SuperMarioBros.EntityType.ET_FLAG_4 || type === SuperMarioBros.EntityType.ET_FLAG_5) {
			this._flag_map.set(object, true);
		}
	},
	SetTileShow : function(row, col, show_row, show_col) {
		if (this._tile_linear.child_count < col + 1) {
			for (let i = this._tile_linear.child_count; i < col + 1; i += 1) {
				let linear = ALittle.NewObject(ALittle.Linear, SuperMarioBros.g_Control);
				linear.type = 2;
				linear.width = SuperMarioBros.TILE_WIDTH;
				this._tile_linear.AddChild(linear);
			}
			this._scroll_screen.container.width = this._tile_linear.width;
			this._scroll_screen.AdjustScrollBar();
		}
		let linear = this._tile_linear.GetChildByIndex(col + 1);
		if (linear === undefined) {
			return;
		}
		if (linear.child_count < row + 1) {
			for (let i = linear.child_count; i < row + 1; i += 1) {
				let sprite = ALittle.NewObject(ALittle.Sprite, SuperMarioBros.g_Control);
				sprite.texture_name = SuperMarioBros.TILE_TEXTURE_NAME;
				sprite.row_count = SuperMarioBros.TILE_ROW_COUNT;
				sprite.col_count = SuperMarioBros.TILE_COL_COUNT;
				sprite.width = SuperMarioBros.TILE_WIDTH;
				sprite.height = SuperMarioBros.TILE_HEIGHT;
				sprite.visible = false;
				linear.AddChild(sprite);
			}
		}
		let sprite = linear.GetChildByIndex(row + 1);
		sprite.row_index = show_row;
		sprite.col_index = show_col;
		sprite.visible = true;
	},
	TestCollision : function(a, b) {
		if (a.x + a.width < b.x) {
			return false;
		}
		if (a.x > b.x + b.width) {
			return false;
		}
		if (a.y + a.height < b.y) {
			return false;
		}
		if (a.y > b.y + b.height) {
			return false;
		}
		return true;
	},
	HandleFrame : function(frame_time) {
		if (this._player.win && this._player.visible && g_GCenter.battle_scene.CheckOutDoor(this._player)) {
			this._player.visible = false;
			this._player.Idle();
			g_GCenter.login_scene.UpdateTopScore();
			let loop = ALittle.NewObject(ALittle.LoopList);
			loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, g_GCenter.battle_scene.NextStage.bind(g_GCenter.battle_scene), 1000));
			loop.Start();
		}
		let cur_time = ALittle.System_GetCurMSTime();
		let delta_time = ALittle.Math_Floor((this._end_time - cur_time) / 1000);
		if (delta_time <= 0) {
			delta_time = 0;
		}
		this._time.text = ALittle.Math_Floor(delta_time);
		if (delta_time <= 0) {
			this._player.Death();
			return;
		}
		this._player.UpdateFrame(frame_time);
		let scroll_x = -(this._player.x - this._scroll_screen.view_width / 2);
		if (scroll_x > 0) {
			scroll_x = 0;
		} else if (scroll_x <= -(this._scroll_screen.container.width - this._scroll_screen.view_width)) {
			scroll_x = -(this._scroll_screen.container.width - this._scroll_screen.view_width);
		}
		if (this._scroll_screen.container_x > scroll_x) {
			this._scroll_screen.container_x = scroll_x;
		}
		if (this._player.y >= A_UISystem.view_height) {
			this._player.Death();
		}
		if (this._player.state !== SuperMarioBros.PlayerState.PS_DEATH && this._player.state !== SuperMarioBros.PlayerState.PS_FLAG && !this._player.win) {
			for (let [flag, _] of this._flag_map) {
				if (_ === undefined) continue;
				if (this.TestCollision(this._player, flag)) {
					if (this._player.right) {
						if (this._player.x >= flag.x - SuperMarioBros.TILE_WIDTH / 2) {
							this._player.x = flag.x - SuperMarioBros.TILE_WIDTH / 2;
							this._player.Flag();
							break;
						}
					} else {
						if (this._player.x <= flag.x + flag.width - SuperMarioBros.TILE_WIDTH / 2) {
							this._player.x = flag.x + flag.width - SuperMarioBros.TILE_WIDTH / 2;
							this._player.Flag();
							break;
						}
					}
				}
			}
		}
		if (this._player.state !== SuperMarioBros.PlayerState.PS_DEATH) {
			let remove_map = undefined;
			for (let [enemy, _] of this._enemy_mushroom_map) {
				if (_ === undefined) continue;
				if (enemy.x < -this._scroll_screen.container_x + this._scroll_screen.view_width) {
					enemy.TryWalk();
				}
				enemy.UpdateFrame(frame_time);
				if (enemy.y >= A_UISystem.view_height) {
					if (remove_map === undefined) {
						remove_map = new Map();
					}
					remove_map.set(enemy, true);
					this._entity_container.RemoveChild(enemy);
				}
			}
			for (let [enemy, _] of this._enemy_mushroom_map) {
				if (_ === undefined) continue;
				if (this._player.state === SuperMarioBros.PlayerState.PS_DEATH) {
					break;
				}
				if (enemy.state !== SuperMarioBros.EnemyMushroomState.EMS_DEATH && this.TestCollision(this._player, enemy)) {
					if (this._player.y + this._player.height - enemy.y < SuperMarioBros.TILE_HEIGHT) {
						if (remove_map === undefined) {
							remove_map = new Map();
						}
						remove_map.set(enemy, true);
						enemy.Death();
						let remove_loop = ALittle.NewObject(ALittle.LoopList);
						remove_loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, this.EntityRemoveChild.bind(this, enemy), 200));
						remove_loop.Start();
						this._player.SmallJump();
						{
							g_GCenter.player_data.score = g_GCenter.player_data.score + (100);
							this._score.text = g_GCenter.player_data.score;
							let coin_text = SuperMarioBros.g_Control.CreateControl("effect_coin_text");
							coin_text.text = "100";
							coin_text.x = enemy.x + enemy.width / 2 - coin_text.width / 2;
							coin_text.y = enemy.y - coin_text.height;
							this._effect_container.AddChild(coin_text);
							let loop = ALittle.NewObject(ALittle.LoopList);
							loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, coin_text, "y", coin_text.y - SuperMarioBros.TILE_HEIGHT * 2, 200, 0));
							loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, this.EffectRemoveChild.bind(this, coin_text), 200));
							loop.Start();
						}
					} else {
						this._player.Death();
					}
				}
			}
			if (remove_map !== undefined) {
				for (let [mushroom, _] of remove_map) {
					if (_ === undefined) continue;
					this._enemy_mushroom_map.delete(mushroom);
				}
			}
		}
		if (this._player.state !== SuperMarioBros.PlayerState.PS_DEATH) {
			let remove_map = undefined;
			for (let [mushroom, _] of this._life_mushroom_map) {
				if (_ === undefined) continue;
				mushroom.UpdateFrame(frame_time);
				if (mushroom.y >= A_UISystem.view_height) {
					if (remove_map === undefined) {
						remove_map = new Map();
					}
					remove_map.set(mushroom, true);
				} else if (this.TestCollision(this._player, mushroom)) {
					if (remove_map === undefined) {
						remove_map = new Map();
					}
					remove_map.set(mushroom, true);
					g_GCenter.player_data.life = g_GCenter.player_data.life + (1);
					{
						let coin_text = SuperMarioBros.g_Control.CreateControl("effect_coin_text");
						coin_text.text = "1 UP";
						coin_text.x = this._player.x + this._player.width / 2 - coin_text.width / 2;
						coin_text.y = this._player.y - coin_text.height;
						this._effect_container.AddChild(coin_text);
						let loop = ALittle.NewObject(ALittle.LoopList);
						loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, coin_text, "y", coin_text.y - SuperMarioBros.TILE_HEIGHT * 2, 200, 0));
						loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, this.EffectRemoveChild.bind(this, coin_text), 200));
						loop.Start();
					}
				}
			}
			if (remove_map !== undefined) {
				for (let [mushroom, _] of remove_map) {
					if (_ === undefined) continue;
					this._life_mushroom_map.delete(mushroom);
					this._entity_container.RemoveChild(mushroom);
				}
			}
		}
	},
	Restart : function() {
		if (g_GCenter.player_data.life <= 0) {
			this.Hide();
			g_GCenter.login_scene.Show();
			return;
		}
		g_GCenter.player_data.life = g_GCenter.player_data.life - (1);
		g_GCenter.player_data.level = 1;
		this.Hide();
		g_GCenter.stage_scene.Show(g_GCenter.player_data.world, g_GCenter.player_data.subworld);
	},
	NextStage : function() {
		this.Hide();
		g_GCenter.stage_scene.Show(g_GCenter.player_data.world, g_GCenter.player_data.subworld);
	},
	CheckUp : function(entity) {
		let row = ALittle.Math_Floor((entity.y - 1) / SuperMarioBros.TILE_HEIGHT);
		let min_col = ALittle.Math_Floor(entity.x / SuperMarioBros.TILE_WIDTH);
		let max_col = ALittle.Math_Floor((entity.x + entity.width - 1) / SuperMarioBros.TILE_WIDTH);
		let check = false;
		for (let col = min_col; col <= max_col; col += 1) {
			let sub_map = this._entity_map.get(row);
			if (sub_map !== undefined) {
				let object = sub_map.get(col);
				if (object !== undefined) {
					let data = object._user_data;
					if (data.type === SuperMarioBros.EntityType.ET_WALL_1) {
						if (g_GCenter.player_data.level === 1) {
							if (data.loop !== undefined) {
								data.loop.SetCompleted();
							}
							data.loop = ALittle.NewObject(ALittle.LoopList);
							data.loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, object, "y", object.y - SuperMarioBros.TILE_HEIGHT / 2, 100, 0));
							data.loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, object, "y", object.y, 100, 0));
							data.loop.Start();
						} else {
							sub_map.delete(col);
							this._entity_container.RemoveChild(object);
							let link_map = {};
							let anti_object = SuperMarioBros.g_Control.CreateControl("wall_split_anti", link_map);
							anti_object.x = object.x;
							anti_object.y = object.y;
							this._effect_container.AddChild(anti_object);
							let anti = anti_object.CreateLoopAnimation("split");
							anti.Init(link_map);
							anti.Play();
							let loop = ALittle.NewObject(ALittle.LoopList);
							loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, this.EffectRemoveChild.bind(this, anti_object), 1000));
							loop.Start();
						}
						check = true;
					} else if (data.type === SuperMarioBros.EntityType.ET_RANDOM_WALL_1) {
						sub_map.delete(col);
						this._entity_container.RemoveChild(object);
						let sprite = ALittle.NewObject(ALittle.Sprite, SuperMarioBros.g_Control);
						sprite.texture_name = SuperMarioBros.TILE_TEXTURE_NAME;
						sprite.width = SuperMarioBros.TILE_WIDTH;
						sprite.height = SuperMarioBros.TILE_HEIGHT;
						sprite.row_count = SuperMarioBros.TILE_ROW_COUNT;
						sprite.col_count = SuperMarioBros.TILE_COL_COUNT;
						sprite.col_index = 7;
						sprite.row_index = 1;
						let sprite_data = {};
						sprite_data.type = SuperMarioBros.EntityType.ET_IRON;
						sprite._user_data = sprite_data;
						sub_map.set(col, sprite);
						this._entity_container.AddChild(sprite);
						sprite.x = object.x;
						sprite.y = object.y;
						object = sprite;
						if (sprite_data.loop !== undefined) {
							sprite_data.loop.SetCompleted();
						}
						sprite_data.loop = ALittle.NewObject(ALittle.LoopList);
						sprite_data.loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, object, "y", object.y - SuperMarioBros.TILE_HEIGHT / 2, 100, 0));
						sprite_data.loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, object, "y", object.y, 100, 0));
						sprite_data.loop.Start();
						{
							let coin = SuperMarioBros.g_Control.CreateControl("effect_coin");
							coin.x = object.x + object.width / 2 - coin.width / 2;
							coin.y = object.y - coin.height;
							coin.Play();
							this._effect_container.AddChild(coin);
							let loop = ALittle.NewObject(ALittle.LoopList);
							loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, coin, "y", coin.y - SuperMarioBros.TILE_HEIGHT * 3, 200, 0));
							loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, this.EffectRemoveChild.bind(this, coin), 200));
							loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, coin.Stop.bind(coin), 0));
							loop.Start();
						}
						{
							this._coin_value = this._coin_value + (1);
							this._coin.text = this._coin_value;
							g_GCenter.player_data.score = g_GCenter.player_data.score + (200);
							this._score.text = g_GCenter.player_data.score;
							let coin_text = SuperMarioBros.g_Control.CreateControl("effect_coin_text");
							coin_text.text = 200;
							coin_text.x = object.x + object.width / 2 - coin_text.width / 2;
							coin_text.y = object.y - coin_text.height;
							this._effect_container.AddChild(coin_text);
							let loop = ALittle.NewObject(ALittle.LoopList);
							loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, coin_text, "y", coin_text.y - SuperMarioBros.TILE_HEIGHT * 2, 200, 0));
							loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, this.EffectRemoveChild.bind(this, coin_text), 200));
							loop.Start();
						}
						check = true;
					} else if (data.type === SuperMarioBros.EntityType.ET_HIDE_WALL_1) {
						object.visible = true;
						if (data.loop !== undefined) {
							data.loop.SetCompleted();
						}
						data.loop = ALittle.NewObject(ALittle.LoopList);
						data.loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, object, "y", object.y - SuperMarioBros.TILE_HEIGHT / 2, 100, 0));
						data.loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, object, "y", object.y, 100, 0));
						data.loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, this.BornLifeMushroom.bind(this, row, col, object), 0));
						data.loop.Start();
						check = true;
					}
				}
			}
		}
		if (check) {
			return [true, row * SuperMarioBros.TILE_HEIGHT + SuperMarioBros.TILE_HEIGHT];
		}
		return [false, undefined];
	},
	BornLifeMushroom : function(row, col, object) {
		let index = this._entity_container.GetChildIndex(object);
		let mushroom = SuperMarioBros.g_Control.CreateControl("life_mushroom");
		this._life_mushroom_map.set(mushroom, true);
		this._entity_container.AddChild(mushroom, index);
		mushroom.Born(row, col);
	},
	EffectRemoveChild : function(object) {
		this._effect_container.RemoveChild(object);
	},
	EntityRemoveChild : function(object) {
		this._entity_container.RemoveChild(object);
	},
	CheckDown : function(entity) {
		let row = ALittle.Math_Floor((entity.y + entity.height) / SuperMarioBros.TILE_HEIGHT);
		let min_col = ALittle.Math_Floor(entity.x / SuperMarioBros.TILE_WIDTH);
		let max_col = ALittle.Math_Floor((entity.x + entity.width - 1) / SuperMarioBros.TILE_WIDTH);
		for (let col = min_col; col <= max_col; col += 1) {
			let sub_map = this._battle_map.background.get(row);
			if (sub_map !== undefined) {
				let index = sub_map.get(col);
				if (index !== undefined) {
					let show_row = ALittle.Math_Floor(index / SuperMarioBros.TILE_COL_COUNT) + 1;
					let show_col = index % SuperMarioBros.TILE_COL_COUNT + 1;
					let check = show_row === 1 && show_col === 1 || show_row >= 3 && show_row <= 4 && show_col >= 1 && show_col <= 2 || show_row === 3 && show_col === 3;
					if (check) {
						return [true, row * SuperMarioBros.TILE_HEIGHT];
					}
				}
			}
			let sub_entity_map = this._entity_map.get(row);
			if (sub_entity_map !== undefined) {
				let object = sub_entity_map.get(col);
				if (object !== undefined) {
					let type = object._user_data.type;
					let check = type === SuperMarioBros.EntityType.ET_RANDOM_WALL_1 || type === SuperMarioBros.EntityType.ET_WALL_1 || (type === SuperMarioBros.EntityType.ET_HIDE_WALL_1 && object.visible) || type === SuperMarioBros.EntityType.ET_IRON;
					if (check) {
						return [true, row * SuperMarioBros.TILE_HEIGHT];
					}
				}
			}
		}
		return [false, undefined];
	},
	CheckOutDoor : function(entity) {
		let col = ALittle.Math_Floor((entity.x + entity.width) / SuperMarioBros.TILE_WIDTH) - 1;
		let min_row = ALittle.Math_Floor(entity.y / SuperMarioBros.TILE_HEIGHT);
		let max_row = ALittle.Math_Floor((entity.y + entity.height - 1) / SuperMarioBros.TILE_HEIGHT);
		for (let row = min_row; row <= max_row; row += 1) {
			let sub_map = this._battle_map.background.get(row);
			if (sub_map !== undefined) {
				let index = sub_map.get(col);
				if (index !== undefined) {
					let show_row = ALittle.Math_Floor(index / SuperMarioBros.TILE_COL_COUNT) + 1;
					let show_col = index % SuperMarioBros.TILE_COL_COUNT + 1;
					let check = show_row === 7 && show_col === 2;
					if (check) {
						return true;
					}
				}
			}
		}
		return false;
	},
	CheckRight : function(entity) {
		let col = ALittle.Math_Floor((entity.x + entity.width) / SuperMarioBros.TILE_WIDTH);
		let min_row = ALittle.Math_Floor(entity.y / SuperMarioBros.TILE_HEIGHT);
		let max_row = ALittle.Math_Floor((entity.y + entity.height - 1) / SuperMarioBros.TILE_HEIGHT);
		for (let row = min_row; row <= max_row; row += 1) {
			let sub_map = this._battle_map.background.get(row);
			if (sub_map !== undefined) {
				let index = sub_map.get(col);
				if (index !== undefined) {
					let show_row = ALittle.Math_Floor(index / SuperMarioBros.TILE_COL_COUNT) + 1;
					let show_col = index % SuperMarioBros.TILE_COL_COUNT + 1;
					let check = show_row === 1 && show_col === 1 || show_row >= 3 && show_row <= 4 && show_col >= 1 && show_col <= 2 || show_row === 3 && show_col === 3;
					if (check) {
						return [true, col * SuperMarioBros.TILE_WIDTH];
					}
				}
			}
			let sub_entity_map = this._entity_map.get(row);
			if (sub_entity_map !== undefined) {
				let object = sub_entity_map.get(col);
				if (object !== undefined) {
					let type = object._user_data.type;
					let check = type === SuperMarioBros.EntityType.ET_RANDOM_WALL_1 || type === SuperMarioBros.EntityType.ET_WALL_1 || (type === SuperMarioBros.EntityType.ET_HIDE_WALL_1 && object.visible) || type === SuperMarioBros.EntityType.ET_IRON;
					if (check) {
						return [true, col * SuperMarioBros.TILE_WIDTH];
					}
				}
			}
		}
		return [false, undefined];
	},
	CheckLeft : function(entity) {
		let col = ALittle.Math_Floor((entity.x - 1) / SuperMarioBros.TILE_WIDTH);
		let min_row = ALittle.Math_Floor(entity.y / SuperMarioBros.TILE_HEIGHT);
		let max_row = ALittle.Math_Floor((entity.y + entity.height - 1) / SuperMarioBros.TILE_HEIGHT);
		for (let row = min_row; row <= max_row; row += 1) {
			let sub_map = this._battle_map.background.get(row);
			if (sub_map !== undefined) {
				let index = sub_map.get(col);
				if (index !== undefined) {
					let show_row = ALittle.Math_Floor(index / SuperMarioBros.TILE_COL_COUNT) + 1;
					let show_col = index % SuperMarioBros.TILE_COL_COUNT + 1;
					let check = show_row === 1 && show_col === 1 || show_row >= 3 && show_row <= 4 && show_col >= 1 && show_col <= 2 || show_row === 3 && show_col === 3;
					if (check) {
						return [true, col * SuperMarioBros.TILE_WIDTH + SuperMarioBros.TILE_WIDTH];
					}
				}
			}
			let sub_entity_map = this._entity_map.get(row);
			if (sub_entity_map !== undefined) {
				let object = sub_entity_map.get(col);
				if (object !== undefined) {
					let type = object._user_data.type;
					let check = type === SuperMarioBros.EntityType.ET_RANDOM_WALL_1 || type === SuperMarioBros.EntityType.ET_WALL_1 || (type === SuperMarioBros.EntityType.ET_HIDE_WALL_1 && object.visible) || type === SuperMarioBros.EntityType.ET_IRON;
					if (check) {
						return [true, col * SuperMarioBros.TILE_WIDTH + SuperMarioBros.TILE_WIDTH];
					}
				}
			}
		}
		return [false, undefined];
	},
	HandleKeyDown : function(mod, sym, scancode) {
		if (sym === 106) {
			this._player.Fire();
		}
	},
	Hide : function() {
		if (this._frame_loop !== undefined) {
			this._frame_loop.Stop();
		}
		this._frame_loop = undefined;
		this.visible = false;
	},
}, "SuperMarioBros.BattleScene");

}