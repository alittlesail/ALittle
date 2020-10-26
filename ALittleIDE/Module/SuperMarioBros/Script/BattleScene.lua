-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.SuperMarioBros == nil then _G.SuperMarioBros = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-873421098, "SuperMarioBros.EntityUserData", {
name = "SuperMarioBros.EntityUserData", ns_name = "SuperMarioBros", rl_name = "EntityUserData", hash_code = -873421098,
name_list = {"type","loop"},
type_list = {"int","ALittle.LoopList"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
SuperMarioBros.BattleScene = Lua.Class(ALittle.DisplayLayout, "SuperMarioBros.BattleScene")

function SuperMarioBros.BattleScene:Ctor()
	___rawset(self, "_coin_value", 0)
	___rawset(self, "_end_time", 0)
end

function SuperMarioBros.BattleScene:TCtor()
	self._scroll_screen.container:Init(self._tile_linear)
end

function SuperMarioBros.BattleScene:Show(world, subworld)
	self._battle_map = SuperMarioBros.g_Control:LoadMessageFromFile(___all_struct[-876795489], "Other/Map/world_" .. world .. "_" .. subworld .. ".map")
	if self._battle_map == nil then
		ALittle.Error("map load filed! Other/Map/world_" .. world .. "_" .. subworld .. ".map")
		return
	end
	self._coin_value = 0
	self._score.text = g_GCenter.player_data.score
	self._coin.text = self._coin_value
	self._stage.text = g_GCenter.player_data.world .. "-" .. g_GCenter.player_data.subworld
	self._time.text = 60 * 5
	local start_time = ALittle.System_GetCurMSTime()
	self._end_time = start_time + 60 * 5 * 1000
	self._time.text = ALittle.Math_Floor((self._end_time - start_time) / 1000)
	self._tile_linear:RemoveAllChild()
	self._entity_container:RemoveAllChild()
	self._effect_container:RemoveAllChild()
	self._entity_map = {}
	self._life_mushroom_map = {}
	self._enemy_mushroom_map = {}
	self._flag_map = {}
	for row, submap in ___pairs(self._battle_map.background) do
		for col, index in ___pairs(submap) do
			local show_row = ALittle.Math_Floor(index / SuperMarioBros.TILE_COL_COUNT) + 1
			local show_col = index % SuperMarioBros.TILE_COL_COUNT + 1
			self:SetTileShow(row, col, show_row, show_col)
		end
	end
	for row, submap in ___pairs(self._battle_map.object) do
		for col, type in ___pairs(submap) do
			if type == SuperMarioBros.EntityType.ET_BORN_1 then
				self._player:Init(row + 1, col, g_GCenter.player_data.level)
			elseif type == SuperMarioBros.EntityType.ET_ENEMY_1 then
				local enemy = SuperMarioBros.g_Control:CreateControl("enemy_mushroom")
				enemy:Init(row, col)
				self._enemy_mushroom_map[enemy] = true
				self._entity_container:AddChild(enemy)
			else
				self:CreateEntity(type, row, col)
			end
		end
	end
	self._scroll_screen.container.width = self._tile_linear.width
	self._scroll_screen.container_x = 0
	self._scroll_screen:RefreshClipDisLine()
	self.visible = true
	A_UISystem.keydown_callback = Lua.Bind(self.HandleKeyDown, self)
	if self._frame_loop ~= nil then
		self._frame_loop:Stop()
	end
	self._frame_loop = ALittle.LoopFrame(Lua.Bind(self.HandleFrame, self))
	self._frame_loop:Start()
end
SuperMarioBros.BattleScene.Show = Lua.CoWrap(SuperMarioBros.BattleScene.Show)

function SuperMarioBros.BattleScene:CreateEntity(type, row, col)
	local ui = ""
	if type == SuperMarioBros.EntityType.ET_WALL_1 then
		ui = "wall_1"
	elseif type == SuperMarioBros.EntityType.ET_HIDE_WALL_1 then
		ui = "hide_wall_1"
	elseif type == SuperMarioBros.EntityType.ET_RANDOM_WALL_1 then
		ui = "random_wall_1"
	elseif type == SuperMarioBros.EntityType.ET_FLAG_1 then
		ui = "flag_1"
	elseif type == SuperMarioBros.EntityType.ET_FLAG_2 then
		ui = "flag_2"
	elseif type == SuperMarioBros.EntityType.ET_FLAG_3 then
		ui = "flag_3"
	elseif type == SuperMarioBros.EntityType.ET_FLAG_4 then
		ui = "flag_4"
	elseif type == SuperMarioBros.EntityType.ET_FLAG_5 then
		ui = "flag_5"
	else
		return
	end
	local entity_sub_map = self._entity_map[row]
	if entity_sub_map == nil then
		entity_sub_map = {}
		self._entity_map[row] = entity_sub_map
	end
	local object = SuperMarioBros.g_Control:CreateControl(ui)
	entity_sub_map[col] = object
	object.x = col * SuperMarioBros.TILE_WIDTH
	object.y = row * SuperMarioBros.TILE_HEIGHT
	local data = {}
	data.type = type
	object._user_data = data
	if type == SuperMarioBros.EntityType.ET_HIDE_WALL_1 then
		object.visible = false
	end
	self._entity_container:AddChild(object)
	if type == SuperMarioBros.EntityType.ET_FLAG_1 or type == SuperMarioBros.EntityType.ET_FLAG_2 or type == SuperMarioBros.EntityType.ET_FLAG_3 or type == SuperMarioBros.EntityType.ET_FLAG_4 or type == SuperMarioBros.EntityType.ET_FLAG_5 then
		self._flag_map[object] = true
	end
end

function SuperMarioBros.BattleScene:SetTileShow(row, col, show_row, show_col)
	if self._tile_linear.child_count < col + 1 then
		local i = self._tile_linear.child_count
		while true do
			if not(i < col + 1) then break end
			local linear = ALittle.Linear(SuperMarioBros.g_Control)
			linear.type = 2
			linear.width = SuperMarioBros.TILE_WIDTH
			self._tile_linear:AddChild(linear)
			i = i+(1)
		end
		self._scroll_screen.container.width = self._tile_linear.width
		self._scroll_screen:AdjustScrollBar()
	end
	local linear = self._tile_linear:GetChildByIndex(col + 1)
	if linear == nil then
		return
	end
	if linear.child_count < row + 1 then
		local i = linear.child_count
		while true do
			if not(i < row + 1) then break end
			local sprite = ALittle.Sprite(SuperMarioBros.g_Control)
			sprite.texture_name = SuperMarioBros.TILE_TEXTURE_NAME
			sprite.row_count = SuperMarioBros.TILE_ROW_COUNT
			sprite.col_count = SuperMarioBros.TILE_COL_COUNT
			sprite.width = SuperMarioBros.TILE_WIDTH
			sprite.height = SuperMarioBros.TILE_HEIGHT
			sprite.visible = false
			linear:AddChild(sprite)
			i = i+(1)
		end
	end
	local sprite = linear:GetChildByIndex(row + 1)
	sprite.row_index = show_row
	sprite.col_index = show_col
	sprite.visible = true
end

function SuperMarioBros.BattleScene:TestCollision(a, b)
	if a.x + a.width < b.x then
		return false
	end
	if a.x > b.x + b.width then
		return false
	end
	if a.y + a.height < b.y then
		return false
	end
	if a.y > b.y + b.height then
		return false
	end
	return true
end

function SuperMarioBros.BattleScene:HandleFrame(frame_time)
	if self._player.win and self._player.visible and g_GCenter.battle_scene:CheckOutDoor(self._player) then
		self._player.visible = false
		self._player:Idle()
		g_GCenter.login_scene:UpdateTopScore()
		local loop = ALittle.LoopList()
		loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(g_GCenter.battle_scene.NextStage, g_GCenter.battle_scene), 1000))
		loop:Start()
	end
	local cur_time = ALittle.System_GetCurMSTime()
	local delta_time = ALittle.Math_Floor((self._end_time - cur_time) / 1000)
	if delta_time <= 0 then
		delta_time = 0
	end
	self._time.text = ALittle.Math_Floor(delta_time)
	if delta_time <= 0 then
		self._player:Death()
		return
	end
	self._player:UpdateFrame(frame_time)
	local scroll_x = -(self._player.x - self._scroll_screen.view_width / 2)
	if scroll_x > 0 then
		scroll_x = 0
	elseif scroll_x <= -(self._scroll_screen.container.width - self._scroll_screen.view_width) then
		scroll_x = -(self._scroll_screen.container.width - self._scroll_screen.view_width)
	end
	if self._scroll_screen.container_x > scroll_x then
		self._scroll_screen.container_x = scroll_x
	end
	if self._player.y >= A_UISystem.view_height then
		self._player:Death()
	end
	if self._player.state ~= SuperMarioBros.PlayerState.PS_DEATH and self._player.state ~= SuperMarioBros.PlayerState.PS_FLAG and not self._player.win then
		for flag, _ in ___pairs(self._flag_map) do
			if self:TestCollision(self._player, flag) then
				if self._player.right then
					if self._player.x >= flag.x - SuperMarioBros.TILE_WIDTH / 2 then
						self._player.x = flag.x - SuperMarioBros.TILE_WIDTH / 2
						self._player:Flag()
						break
					end
				else
					if self._player.x <= flag.x + flag.width - SuperMarioBros.TILE_WIDTH / 2 then
						self._player.x = flag.x + flag.width - SuperMarioBros.TILE_WIDTH / 2
						self._player:Flag()
						break
					end
				end
			end
		end
	end
	if self._player.state ~= SuperMarioBros.PlayerState.PS_DEATH then
		local remove_map
		for enemy, _ in ___pairs(self._enemy_mushroom_map) do
			if enemy.x < -self._scroll_screen.container_x + self._scroll_screen.view_width then
				enemy:TryWalk()
			end
			enemy:UpdateFrame(frame_time)
			if enemy.y >= A_UISystem.view_height then
				if remove_map == nil then
					remove_map = {}
				end
				remove_map[enemy] = true
				self._entity_container:RemoveChild(enemy)
			end
		end
		for enemy, _ in ___pairs(self._enemy_mushroom_map) do
			if self._player.state == SuperMarioBros.PlayerState.PS_DEATH then
				break
			end
			if enemy.state ~= SuperMarioBros.EnemyMushroomState.EMS_DEATH and self:TestCollision(self._player, enemy) then
				if self._player.y + self._player.height - enemy.y < SuperMarioBros.TILE_HEIGHT then
					if remove_map == nil then
						remove_map = {}
					end
					remove_map[enemy] = true
					enemy:Death()
					local remove_loop = ALittle.LoopList()
					remove_loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(self.EntityRemoveChild, self, enemy), 200))
					remove_loop:Start()
					self._player:SmallJump()
					do
						g_GCenter.player_data.score = g_GCenter.player_data.score + (100)
						self._score.text = g_GCenter.player_data.score
						local coin_text = SuperMarioBros.g_Control:CreateControl("effect_coin_text")
						coin_text.text = "100"
						coin_text.x = enemy.x + enemy.width / 2 - coin_text.width / 2
						coin_text.y = enemy.y - coin_text.height
						self._effect_container:AddChild(coin_text)
						local loop = ALittle.LoopList()
						loop:AddUpdater(ALittle.LoopLinear(coin_text, "y", coin_text.y - SuperMarioBros.TILE_HEIGHT * 2, 200, 0))
						loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(self.EffectRemoveChild, self, coin_text), 200))
						loop:Start()
					end
				else
					self._player:Death()
				end
			end
		end
		if remove_map ~= nil then
			for mushroom, _ in ___pairs(remove_map) do
				self._enemy_mushroom_map[mushroom] = nil
			end
		end
	end
	if self._player.state ~= SuperMarioBros.PlayerState.PS_DEATH then
		local remove_map
		for mushroom, _ in ___pairs(self._life_mushroom_map) do
			mushroom:UpdateFrame(frame_time)
			if mushroom.y >= A_UISystem.view_height then
				if remove_map == nil then
					remove_map = {}
				end
				remove_map[mushroom] = true
			elseif self:TestCollision(self._player, mushroom) then
				if remove_map == nil then
					remove_map = {}
				end
				remove_map[mushroom] = true
				g_GCenter.player_data.life = g_GCenter.player_data.life + (1)
				do
					local coin_text = SuperMarioBros.g_Control:CreateControl("effect_coin_text")
					coin_text.text = "1 UP"
					coin_text.x = self._player.x + self._player.width / 2 - coin_text.width / 2
					coin_text.y = self._player.y - coin_text.height
					self._effect_container:AddChild(coin_text)
					local loop = ALittle.LoopList()
					loop:AddUpdater(ALittle.LoopLinear(coin_text, "y", coin_text.y - SuperMarioBros.TILE_HEIGHT * 2, 200, 0))
					loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(self.EffectRemoveChild, self, coin_text), 200))
					loop:Start()
				end
			end
		end
		if remove_map ~= nil then
			for mushroom, _ in ___pairs(remove_map) do
				self._life_mushroom_map[mushroom] = nil
				self._entity_container:RemoveChild(mushroom)
			end
		end
	end
end

function SuperMarioBros.BattleScene:Restart()
	if g_GCenter.player_data.life <= 0 then
		self:Hide()
		g_GCenter.login_scene:Show()
		return
	end
	g_GCenter.player_data.life = g_GCenter.player_data.life - (1)
	g_GCenter.player_data.level = 1
	self:Hide()
	g_GCenter.stage_scene:Show(g_GCenter.player_data.world, g_GCenter.player_data.subworld)
end

function SuperMarioBros.BattleScene:NextStage()
	self:Hide()
	g_GCenter.stage_scene:Show(g_GCenter.player_data.world, g_GCenter.player_data.subworld)
end

function SuperMarioBros.BattleScene:CheckUp(entity)
	local row = ALittle.Math_Floor((entity.y - 1) / SuperMarioBros.TILE_HEIGHT)
	local min_col = ALittle.Math_Floor(entity.x / SuperMarioBros.TILE_WIDTH)
	local max_col = ALittle.Math_Floor((entity.x + entity.width - 1) / SuperMarioBros.TILE_WIDTH)
	local check = false
	local col = min_col
	while true do
		if not(col <= max_col) then break end
		local sub_map = self._entity_map[row]
		if sub_map ~= nil then
			local object = sub_map[col]
			if object ~= nil then
				local data = object._user_data
				if data.type == SuperMarioBros.EntityType.ET_WALL_1 then
					if g_GCenter.player_data.level == 1 then
						if data.loop ~= nil then
							data.loop:SetCompleted()
						end
						data.loop = ALittle.LoopList()
						data.loop:AddUpdater(ALittle.LoopLinear(object, "y", object.y - SuperMarioBros.TILE_HEIGHT / 2, 100, 0))
						data.loop:AddUpdater(ALittle.LoopLinear(object, "y", object.y, 100, 0))
						data.loop:Start()
					else
						sub_map[col] = nil
						self._entity_container:RemoveChild(object)
						local link_map = {}
						local anti_object = SuperMarioBros.g_Control:CreateControl("wall_split_anti", link_map)
						anti_object.x = object.x
						anti_object.y = object.y
						self._effect_container:AddChild(anti_object)
						local anti = anti_object:CreateLoopAnimation("split")
						anti:Init(link_map)
						anti:Play()
						local loop = ALittle.LoopList()
						loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(self.EffectRemoveChild, self, anti_object), 1000))
						loop:Start()
					end
					check = true
				elseif data.type == SuperMarioBros.EntityType.ET_IRON then
					check = true
				elseif data.type == SuperMarioBros.EntityType.ET_RANDOM_WALL_1 then
					sub_map[col] = nil
					self._entity_container:RemoveChild(object)
					local sprite = ALittle.Sprite(SuperMarioBros.g_Control)
					sprite.texture_name = SuperMarioBros.TILE_TEXTURE_NAME
					sprite.width = SuperMarioBros.TILE_WIDTH
					sprite.height = SuperMarioBros.TILE_HEIGHT
					sprite.row_count = SuperMarioBros.TILE_ROW_COUNT
					sprite.col_count = SuperMarioBros.TILE_COL_COUNT
					sprite.col_index = 7
					sprite.row_index = 1
					local sprite_data = {}
					sprite_data.type = SuperMarioBros.EntityType.ET_IRON
					sprite._user_data = sprite_data
					sub_map[col] = sprite
					self._entity_container:AddChild(sprite)
					sprite.x = object.x
					sprite.y = object.y
					object = sprite
					if sprite_data.loop ~= nil then
						sprite_data.loop:SetCompleted()
					end
					sprite_data.loop = ALittle.LoopList()
					sprite_data.loop:AddUpdater(ALittle.LoopLinear(object, "y", object.y - SuperMarioBros.TILE_HEIGHT / 2, 100, 0))
					sprite_data.loop:AddUpdater(ALittle.LoopLinear(object, "y", object.y, 100, 0))
					sprite_data.loop:Start()
					do
						local coin = SuperMarioBros.g_Control:CreateControl("effect_coin")
						coin.x = object.x + object.width / 2 - coin.width / 2
						coin.y = object.y - coin.height
						coin:Play()
						self._effect_container:AddChild(coin)
						local loop = ALittle.LoopList()
						loop:AddUpdater(ALittle.LoopLinear(coin, "y", coin.y - SuperMarioBros.TILE_HEIGHT * 3, 200, 0))
						loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(self.EffectRemoveChild, self, coin), 200))
						loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(coin.Stop, coin), 0))
						loop:Start()
					end
					do
						self._coin_value = self._coin_value + (1)
						self._coin.text = self._coin_value
						g_GCenter.player_data.score = g_GCenter.player_data.score + (200)
						self._score.text = g_GCenter.player_data.score
						local coin_text = SuperMarioBros.g_Control:CreateControl("effect_coin_text")
						coin_text.text = 200
						coin_text.x = object.x + object.width / 2 - coin_text.width / 2
						coin_text.y = object.y - coin_text.height
						self._effect_container:AddChild(coin_text)
						local loop = ALittle.LoopList()
						loop:AddUpdater(ALittle.LoopLinear(coin_text, "y", coin_text.y - SuperMarioBros.TILE_HEIGHT * 2, 200, 0))
						loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(self.EffectRemoveChild, self, coin_text), 200))
						loop:Start()
					end
					check = true
				elseif data.type == SuperMarioBros.EntityType.ET_HIDE_WALL_1 then
					object.visible = true
					if data.loop ~= nil then
						data.loop:SetCompleted()
					end
					data.loop = ALittle.LoopList()
					data.loop:AddUpdater(ALittle.LoopLinear(object, "y", object.y - SuperMarioBros.TILE_HEIGHT / 2, 100, 0))
					data.loop:AddUpdater(ALittle.LoopLinear(object, "y", object.y, 100, 0))
					data.loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(self.BornLifeMushroom, self, row, col, object), 0))
					data.loop:Start()
					check = true
				end
			end
		end
		col = col+(1)
	end
	if check then
		return true, row * SuperMarioBros.TILE_HEIGHT + SuperMarioBros.TILE_HEIGHT
	end
	return false, nil
end

function SuperMarioBros.BattleScene:BornLifeMushroom(row, col, object)
	local index = self._entity_container:GetChildIndex(object)
	local mushroom = SuperMarioBros.g_Control:CreateControl("life_mushroom")
	self._life_mushroom_map[mushroom] = true
	self._entity_container:AddChild(mushroom, index)
	mushroom:Born(row, col)
end

function SuperMarioBros.BattleScene:EffectRemoveChild(object)
	self._effect_container:RemoveChild(object)
end

function SuperMarioBros.BattleScene:EntityRemoveChild(object)
	self._entity_container:RemoveChild(object)
end

function SuperMarioBros.BattleScene:CheckDown(entity)
	local row = ALittle.Math_Floor((entity.y + entity.height) / SuperMarioBros.TILE_HEIGHT)
	local min_col = ALittle.Math_Floor(entity.x / SuperMarioBros.TILE_WIDTH)
	local max_col = ALittle.Math_Floor((entity.x + entity.width - 1) / SuperMarioBros.TILE_WIDTH)
	local col = min_col
	while true do
		if not(col <= max_col) then break end
		local sub_map = self._battle_map.background[row]
		if sub_map ~= nil then
			local index = sub_map[col]
			if index ~= nil then
				local show_row = ALittle.Math_Floor(index / SuperMarioBros.TILE_COL_COUNT) + 1
				local show_col = index % SuperMarioBros.TILE_COL_COUNT + 1
				local check = show_row == 1 and show_col == 1 or show_row >= 3 and show_row <= 4 and show_col >= 1 and show_col <= 2 or show_row == 3 and show_col == 3
				if check then
					return true, row * SuperMarioBros.TILE_HEIGHT
				end
			end
		end
		local sub_entity_map = self._entity_map[row]
		if sub_entity_map ~= nil then
			local object = sub_entity_map[col]
			if object ~= nil then
				local type = object._user_data.type
				local check = type == SuperMarioBros.EntityType.ET_RANDOM_WALL_1 or type == SuperMarioBros.EntityType.ET_WALL_1 or (type == SuperMarioBros.EntityType.ET_HIDE_WALL_1 and object.visible) or type == SuperMarioBros.EntityType.ET_IRON
				if check then
					return true, row * SuperMarioBros.TILE_HEIGHT
				end
			end
		end
		col = col+(1)
	end
	return false, nil
end

function SuperMarioBros.BattleScene:CheckOutDoor(entity)
	local col = ALittle.Math_Floor((entity.x + entity.width) / SuperMarioBros.TILE_WIDTH) - 1
	local min_row = ALittle.Math_Floor(entity.y / SuperMarioBros.TILE_HEIGHT)
	local max_row = ALittle.Math_Floor((entity.y + entity.height - 1) / SuperMarioBros.TILE_HEIGHT)
	local row = min_row
	while true do
		if not(row <= max_row) then break end
		local sub_map = self._battle_map.background[row]
		if sub_map ~= nil then
			local index = sub_map[col]
			if index ~= nil then
				local show_row = ALittle.Math_Floor(index / SuperMarioBros.TILE_COL_COUNT) + 1
				local show_col = index % SuperMarioBros.TILE_COL_COUNT + 1
				local check = show_row == 7 and show_col == 2
				if check then
					return true
				end
			end
		end
		row = row+(1)
	end
	return false
end

function SuperMarioBros.BattleScene:CheckRight(entity)
	local col = ALittle.Math_Floor((entity.x + entity.width) / SuperMarioBros.TILE_WIDTH)
	local min_row = ALittle.Math_Floor(entity.y / SuperMarioBros.TILE_HEIGHT)
	local max_row = ALittle.Math_Floor((entity.y + entity.height - 1) / SuperMarioBros.TILE_HEIGHT)
	local row = min_row
	while true do
		if not(row <= max_row) then break end
		local sub_map = self._battle_map.background[row]
		if sub_map ~= nil then
			local index = sub_map[col]
			if index ~= nil then
				local show_row = ALittle.Math_Floor(index / SuperMarioBros.TILE_COL_COUNT) + 1
				local show_col = index % SuperMarioBros.TILE_COL_COUNT + 1
				local check = show_row == 1 and show_col == 1 or show_row >= 3 and show_row <= 4 and show_col >= 1 and show_col <= 2 or show_row == 3 and show_col == 3
				if check then
					return true, col * SuperMarioBros.TILE_WIDTH
				end
			end
		end
		local sub_entity_map = self._entity_map[row]
		if sub_entity_map ~= nil then
			local object = sub_entity_map[col]
			if object ~= nil then
				local type = object._user_data.type
				local check = type == SuperMarioBros.EntityType.ET_RANDOM_WALL_1 or type == SuperMarioBros.EntityType.ET_WALL_1 or (type == SuperMarioBros.EntityType.ET_HIDE_WALL_1 and object.visible) or type == SuperMarioBros.EntityType.ET_IRON
				if check then
					return true, col * SuperMarioBros.TILE_WIDTH
				end
			end
		end
		row = row+(1)
	end
	return false, nil
end

function SuperMarioBros.BattleScene:CheckLeft(entity)
	local col = ALittle.Math_Floor((entity.x - 1) / SuperMarioBros.TILE_WIDTH)
	local min_row = ALittle.Math_Floor(entity.y / SuperMarioBros.TILE_HEIGHT)
	local max_row = ALittle.Math_Floor((entity.y + entity.height - 1) / SuperMarioBros.TILE_HEIGHT)
	local row = min_row
	while true do
		if not(row <= max_row) then break end
		local sub_map = self._battle_map.background[row]
		if sub_map ~= nil then
			local index = sub_map[col]
			if index ~= nil then
				local show_row = ALittle.Math_Floor(index / SuperMarioBros.TILE_COL_COUNT) + 1
				local show_col = index % SuperMarioBros.TILE_COL_COUNT + 1
				local check = show_row == 1 and show_col == 1 or show_row >= 3 and show_row <= 4 and show_col >= 1 and show_col <= 2 or show_row == 3 and show_col == 3
				if check then
					return true, col * SuperMarioBros.TILE_WIDTH + SuperMarioBros.TILE_WIDTH
				end
			end
		end
		local sub_entity_map = self._entity_map[row]
		if sub_entity_map ~= nil then
			local object = sub_entity_map[col]
			if object ~= nil then
				local type = object._user_data.type
				local check = type == SuperMarioBros.EntityType.ET_RANDOM_WALL_1 or type == SuperMarioBros.EntityType.ET_WALL_1 or (type == SuperMarioBros.EntityType.ET_HIDE_WALL_1 and object.visible) or type == SuperMarioBros.EntityType.ET_IRON
				if check then
					return true, col * SuperMarioBros.TILE_WIDTH + SuperMarioBros.TILE_WIDTH
				end
			end
		end
		row = row+(1)
	end
	return false, nil
end

function SuperMarioBros.BattleScene:HandleKeyDown(mod, sym, scancode)
	if sym == 106 then
		self._player:Fire()
	end
end

function SuperMarioBros.BattleScene:Hide()
	if self._frame_loop ~= nil then
		self._frame_loop:Stop()
	end
	self._frame_loop = nil
	self.visible = false
end

end