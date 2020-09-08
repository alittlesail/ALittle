-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
BattleCity.BattleScene = Lua.Class(ALittle.DisplayLayout, "BattleCity.BattleScene")

function BattleCity.BattleScene:Ctor()
	___rawset(self, "_enemy_count", 0)
	___rawset(self, "_generate_enemy_cool", 0)
	___rawset(self, "_enemy_width", 0)
	___rawset(self, "_enemy_height", 0)
	___rawset(self, "_iron_flash", false)
	___rawset(self, "_iron_flash_frame", 0)
	___rawset(self, "_iron_flash_brush", 0)
	___rawset(self, "_iron_flash_count", 0)
	___rawset(self, "_river_flash_frame", 0)
	___rawset(self, "_river_flash_brush", 0)
	___rawset(self, "_is_gameover", false)
end

function BattleCity.BattleScene:TCtor()
	self._player_1 = BattleCity.g_Control:CreateControl("battle_player1")
	self._player_2 = BattleCity.g_Control:CreateControl("battle_player2")
	self._cell_size = self._tile_container.width / (13 * 4)
	local enemy = BattleCity.g_Control:CreateControl("battle_enemy")
	self._enemy_width = enemy.width
	self._enemy_height = enemy.height
end

function BattleCity.BattleScene.__getter:cell_size()
	return self._cell_size
end

function BattleCity.BattleScene.__getter:is_gameover()
	return self._is_gameover
end

function BattleCity.BattleScene:Show(stage)
	self._player1_kill = {}
	self._player2_kill = {}
	if self._anti_loop ~= nil then
		self._anti_loop:Stop()
		self._anti_loop = nil
	end
	self._battle_map = BattleCity.g_Control:LoadMessageFromFile(___all_struct[-922796193], "Other/Map/stage_" .. stage .. ".map")
	if self._battle_map == nil then
		ALittle.Error("map load filed! Other/Map/stage_" .. stage .. ".map")
		return
	end
	self._tile_container:RemoveAllChild()
	self._grass_container:RemoveAllChild()
	self._sprite_map = {}
	self._river_map = {}
	for row, sub_map in ___pairs(self._battle_map.tile_map) do
		for col, type in ___pairs(sub_map) do
			self:SetTileShow(row, col, type)
		end
	end
	for row, sub_map in ___pairs(self._sprite_map) do
		for col, sprite in ___pairs(sub_map) do
			if sprite.col_index >= (BattleCity.BrushType.BT_RIVER - 1) * 4 + 1 and sprite.col_index <= (BattleCity.BrushType.BT_RIVER) * 4 then
				local r_sub_map = self._river_map[row]
				if r_sub_map == nil then
					r_sub_map = {}
					self._river_map[row] = r_sub_map
				end
				r_sub_map[col] = sprite
			end
		end
	end
	self._river_flash_brush = BattleCity.BrushType.BT_RIVER
	if self._castle_explosion ~= nil then
		self._castle_explosion:Stop()
		self._castle_explosion.visible = false
	end
	self.visible = true
	self._is_gameover = false
	self._gameover_image.visible = false
	self._iron_flash = false
	self._iron_flash_brush = BattleCity.BrushType.BT_WALL
	self._stage_num.text = stage
	self._player1_life.text = g_GCenter.player1_data.life - 1
	self._player2_life.text = g_GCenter.player2_data.life - 1
	self._enemy_tiletable:RemoveAllChild()
	local i = 1
	while true do
		if not(i <= 20) then break end
		local icon = BattleCity.g_Control:CreateControl("enemy_icon")
		self._enemy_tiletable:AddChild(icon)
		i = i+(1)
	end
	self._enemy_map = {}
	self._enemy_count = 0
	self._generate_enemy_cool = 1000
	self._bullet_container:RemoveAllChild()
	self._bullet_map = {}
	self._entity_container:RemoveAllChild()
	for index, child in ___ipairs(self._item_container.childs) do
		child:Stop()
	end
	self._item_container:RemoveAllChild()
	self._player_1:RemoveFromParent()
	self._player_2:RemoveFromParent()
	self._player1_contianer.visible = g_GCenter.player_count >= 1
	self._player2_contianer.visible = g_GCenter.player_count >= 2
	self._quad_up.y = 0
	self._quad_up.visible = true
	self._quad_down.y = 0
	self._quad_down.visible = true
	self._anti_loop = ALittle.LoopList()
	local group = ALittle.LoopGroup()
	group:AddUpdater(ALittle.LoopLinear(self._quad_up, "y", -self._quad_up.height, 500, 0))
	group:AddUpdater(ALittle.LoopLinear(self._quad_down, "y", A_UISystem.view_height, 500, 0))
	self._anti_loop:AddUpdater(group)
	self._anti_loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(self.Start, self), 0))
	self._anti_loop:Start()
	A_UISystem.keydown_callback = Lua.Bind(self.HandleKeyDown, self)
	if self._frame_loop ~= nil then
		self._frame_loop:Stop()
	end
	self._frame_loop = ALittle.LoopFrame(Lua.Bind(self.HandleFrame, self))
	self._frame_loop:Start()
end
BattleCity.BattleScene.Show = Lua.CoWrap(BattleCity.BattleScene.Show)

function BattleCity.BattleScene:Hide()
	if self._frame_loop ~= nil then
		self._frame_loop:Stop()
		self._frame_loop = nil
	end
	if self._anti_loop ~= nil then
		self._anti_loop:Stop()
		self._anti_loop = nil
	end
	for index, child in ___ipairs(self._item_container.childs) do
		child:Stop()
	end
	self._item_container:RemoveAllChild()
	if self._castle_explosion ~= nil then
		self._castle_explosion:Stop()
		self._castle_explosion.visible = false
	end
	if self._gameover_loop ~= nil then
		self._gameover_loop:Stop()
		self._gameover_loop = nil
	end
	self.visible = false
end

function BattleCity.BattleScene:SetTileShow(row, col, type)
	local sub_map = self._sprite_map[row]
	if sub_map == nil then
		sub_map = {}
		self._sprite_map[row] = sub_map
	end
	if sub_map[col] ~= nil then
		sub_map[col]:RemoveFromParent()
	end
	local sprite = ALittle.Sprite(BattleCity.g_Control)
	sprite.texture_name = "tile.png"
	sprite.width = 32 / 4
	sprite.height = 32 / 4
	sprite.x = col * sprite.width
	sprite.y = row * sprite.height
	sprite.row_count = 4
	sprite.col_count = 7 * 4
	sprite.row_index = row % 4 + 1
	sprite.col_index = col % 4 + 1 + (type - 1) * 4
	if type == BattleCity.BrushType.BT_GRASS then
		self._grass_container:AddChild(sprite)
	else
		self._tile_container:AddChild(sprite)
	end
	sub_map[col] = sprite
end

function BattleCity.BattleScene:TryRemoveWall(row, col)
	local sub_map = self._sprite_map[row]
	if sub_map == nil then
		return false
	end
	local sprite = sub_map[col]
	if sprite == nil then
		return false
	end
	if sprite.col_index >= (BattleCity.BrushType.BT_WALL - 1) * 4 + 1 and sprite.col_index <= (BattleCity.BrushType.BT_WALL) * 4 then
		self._tile_container:RemoveChild(sprite)
		sub_map[col] = nil
		return true
	end
	return false
end

function BattleCity.BattleScene:RemoveTileShow(row, col)
	local sub_map = self._sprite_map[row]
	if sub_map == nil then
		return
	end
	if sub_map[col] ~= nil then
		self._tile_container:RemoveChild(sub_map[col])
		sub_map[col] = nil
	end
end

function BattleCity.BattleScene:CanWalkByMap(row, col)
	local sub_map = self._sprite_map[row]
	if sub_map == nil then
		return true
	end
	local sprite = sub_map[col]
	if sprite == nil then
		return true
	end
	return sprite.col_index >= (BattleCity.BrushType.BT_GRASS - 1) * 4 + 1 and sprite.col_index <= (BattleCity.BrushType.BT_GRASS) * 4
end

function BattleCity.BattleScene:Collision(left, top, right, bottom, target)
	local not_check = right < target.x or bottom < target.y or target.x + target.width < left or target.y + target.height < top
	return not not_check
end

function BattleCity.BattleScene:Collision2(target_1, target_2)
	return self:Collision(target_1.x, target_1.y, target_1.x + target_1.width, target_1.y + target_1.height, target_2)
end

function BattleCity.BattleScene:CanWalkByEntity(entity, left, top, right, bottom)
	if self._player_1.parent ~= nil and entity ~= self._player_1 and not self._player_1.explosion and self:Collision(left, top, right, bottom, self._player_1) then
		return false
	end
	if self._player_2.parent ~= nil and entity ~= self._player_2 and not self._player_2.explosion and self:Collision(left, top, right, bottom, self._player_2) then
		return false
	end
	for role, _ in ___pairs(self._enemy_map) do
		if entity ~= role and not role.explosion and self:Collision(left, top, right, bottom, role) then
			return false
		end
	end
	return true
end

function BattleCity.BattleScene:BulletCollisionByEntity(bullet, left, top, right, bottom)
	if bullet.role.is_enemy and self._player_1.parent ~= nil and bullet.role ~= self._player_1 and self._player_1.alive and self:Collision(left, top, right, bottom, self._player_1) then
		return true, self._player_1:BeAttack()
	end
	if bullet.role.is_enemy and self._player_2.parent ~= nil and bullet.role ~= self._player_2 and self._player_1.alive and self:Collision(left, top, right, bottom, self._player_2) then
		return true, self._player_2:BeAttack()
	end
	if not bullet.role.is_enemy then
		for role, _ in ___pairs(self._enemy_map) do
			if role ~= bullet.role and role.alive and self:Collision(left, top, right, bottom, role) then
				local death = role:BeAttack()
				if death then
					if bullet.role == self._player_1 then
						local count = self._player1_kill[role.level]
						if count == nil then
							count = 0
						end
						count = count + (1)
						self._player1_kill[role.level] = count
					elseif bullet.role == self._player_2 then
						local count = self._player2_kill[role.level]
						if count == nil then
							count = 0
						end
						count = count + (2)
						self._player2_kill[role.level] = count
					end
				end
				return true, death
			end
		end
	end
	return false, false
end

function BattleCity.BattleScene:ShowGameOver()
	if self._is_gameover then
		return
	end
	self._is_gameover = true
	self._gameover_image.visible = true
	self._gameover_loop = ALittle.LoopList()
	self._gameover_loop:AddUpdater(ALittle.LoopLinear(self._gameover_image, "y", A_UISystem.view_height / 2, 2000, 0))
	self._gameover_loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(g_GCenter.Restart, g_GCenter), 1000))
	self._gameover_loop:Start()
end

function BattleCity.BattleScene:StageCompleted()
	g_GCenter.player1_data.level = self._player_1.level
	g_GCenter.player2_data.level = self._player_2.level
	g_GCenter.battle_settlement:Show(self._player1_kill, self._player2_kill)
	self:Hide()
end

function BattleCity.BattleScene:BulletCollisionByMap(row, col, min_or_max, dir)
	local sub_map = self._sprite_map[row]
	if sub_map == nil then
		return false
	end
	local sprite = sub_map[col]
	if sprite == nil then
		return false
	end
	if sprite.col_index >= (BattleCity.BrushType.BT_IRON - 1) * 4 + 1 and sprite.col_index <= (BattleCity.BrushType.BT_IRON) * 4 then
		return true
	end
	if sprite.col_index >= (BattleCity.BrushType.BT_GRASS - 1) * 4 + 1 and sprite.col_index <= (BattleCity.BrushType.BT_GRASS) * 4 then
		return false
	end
	if sprite.col_index >= (BattleCity.BrushType.BT_RIVER - 1) * 4 + 1 and sprite.col_index <= (BattleCity.BrushType.BT_RIVER) * 4 then
		return false
	end
	if sprite.col_index >= (BattleCity.BrushType.BT_RIVER2 - 1) * 4 + 1 and sprite.col_index <= (BattleCity.BrushType.BT_RIVER2) * 4 then
		return false
	end
	if sprite.col_index >= (BattleCity.BrushType.BT_CASTLE2 - 1) * 4 + 1 and sprite.col_index <= (BattleCity.BrushType.BT_CASTLE2) * 4 then
		return false
	end
	if sprite.col_index >= (BattleCity.BrushType.BT_CASTLE - 1) * 4 + 1 and sprite.col_index <= (BattleCity.BrushType.BT_CASTLE) * 4 then
		local r = 12 * 4
		while true do
			if not(r < 13 * 4) then break end
			local c = 6 * 4
			while true do
				if not(c < 7 * 4) then break end
				self:SetTileShow(r, c, BattleCity.BrushType.BT_CASTLE2)
				c = c+(1)
			end
			r = r+(1)
		end
		if self._castle_explosion == nil then
			self._castle_explosion = BattleCity.g_Control:CreateControl("effect_explosion_big")
			self._castle_explosion.x = self.map_size / 2 - self._castle_explosion.width / 2
			self._castle_explosion.y = self.map_size - self._cell_size * 2 - self._castle_explosion.height / 2
			self._effect_container:AddChild(self._castle_explosion)
		end
		self._castle_explosion.visible = true
		self._castle_explosion:Play()
		self:ShowGameOver()
		return true
	end
	if sprite.col_index >= (BattleCity.BrushType.BT_WALL - 1) * 4 + 1 and sprite.col_index <= (BattleCity.BrushType.BT_WALL) * 4 then
		if dir == BattleCity.DirType.DT_UP or dir == BattleCity.DirType.DT_DOWN then
			self:TryRemoveWall(row, col)
			if min_or_max then
				self:TryRemoveWall(row, col - 1)
			else
				self:TryRemoveWall(row, col + 1)
			end
		else
			self:TryRemoveWall(row, col)
			if min_or_max then
				self:TryRemoveWall(row - 1, col)
			else
				self:TryRemoveWall(row + 1, col)
			end
		end
		return true
	end
	return false
end

function BattleCity.BattleScene:IsEnemyStopping()
	return self._item_stop_delay_loop ~= nil and not self._item_stop_delay_loop:IsCompleted()
end

function BattleCity.BattleScene:FireBullet(role, speed)
	local bullet = BattleCity.g_Control:CreateControl("battle_bullet")
	if role.dir == BattleCity.DirType.DT_UP then
		bullet.x = role.x + role.width / 2 - bullet.width / 2
		bullet.y = role.y
	elseif role.dir == BattleCity.DirType.DT_RIGHT then
		bullet.x = role.x + role.width - bullet.width
		bullet.y = role.y + role.height / 2 - bullet.height / 2
	elseif role.dir == BattleCity.DirType.DT_DOWN then
		bullet.x = role.x + role.width / 2 - bullet.width / 2
		bullet.y = role.y + role.height - bullet.height
	else
		bullet.x = role.x
		bullet.y = role.y + role.height / 2 - bullet.height / 2
	end
	bullet:Init(role.dir, role, speed)
	self._bullet_container:AddChild(bullet)
	self._bullet_map[bullet] = true
end

function BattleCity.BattleScene:GenerateItem()
	for index, child in ___ipairs(self._item_container.childs) do
		child:Stop()
	end
	self._item_container:RemoveAllChild()
	local row = ALittle.Math_RandomInt(0, 12 * 4)
	local col = ALittle.Math_RandomInt(0, 12 * 4)
	local item_type = ALittle.Math_RandomInt(BattleCity.ItemType.IT_LIFE, BattleCity.ItemType.IT_SHIELD)
	local item = BattleCity.g_Control:CreateControl("battle_item")
	item.sprite.col_index = item_type
	item.x = row * self._cell_size
	item.y = col * self._cell_size
	self._item_container:AddChild(item)
	item:Play()
end

function BattleCity.BattleScene:GenerateEnemy()
	local born_pos = {}
	born_pos[1] = 0
	born_pos[2] = 6
	born_pos[3] = 12
	ALittle.List_Shuffle(born_pos)
	for index, pos in ___ipairs(born_pos) do
		local failed = false
		local row = 0
		while true do
			if not(row < 4) then break end
			local col = pos * 4
			while true do
				if not(col < (pos + 1) * 4) then break end
				if not self:CanWalkByMap(row, col) then
					failed = true
					break
				end
				col = col+(1)
			end
			if failed then
				break
			end
			row = row+(1)
		end
		if not failed then
			local left = pos * 4 * self._cell_size
			local right = left + self._enemy_width
			if not self:CanWalkByEntity(nil, left, 0, right, self._enemy_height) then
				failed = true
			end
		end
		if not failed then
			self._enemy_tiletable:RemoveChild(self._enemy_tiletable.childs[self._enemy_tiletable.child_count])
			local enemy = BattleCity.g_Control:CreateControl("battle_enemy")
			self._enemy_map[enemy] = true
			enemy:StartBorn(0, pos * 4, ALittle.Math_RandomInt(1, 3), BattleCity.DirType.DT_DOWN, ALittle.Math_RandomInt(1, 100) > 80)
			self._entity_container:AddChild(enemy)
			self._enemy_count = self._enemy_count + (1)
			self._generate_enemy_cool = 1000
			break
		end
	end
end

function BattleCity.BattleScene.__getter:map_size()
	return self._tile_container.width
end

function BattleCity.BattleScene:Start()
	if g_GCenter.player_count >= 1 then
		self._entity_container:AddChild(self._player_1)
		self._player_1:StartBorn(12 * 4, 4 * 4, g_GCenter.player1_data.level, BattleCity.DirType.DT_UP, 0.08)
	end
	if g_GCenter.player_count >= 2 then
		self._entity_container:AddChild(self._player_2)
		self._player_2:StartBorn(12 * 4, 8 * 4, g_GCenter.player2_data.level, BattleCity.DirType.DT_UP, 0.08)
	end
end

function BattleCity.BattleScene:HandleFrame(frame_time)
	if self._enemy_count < 4 and self._enemy_tiletable.child_count > 0 then
		self._generate_enemy_cool = self._generate_enemy_cool - (frame_time)
		if self._generate_enemy_cool <= 0 then
			self:GenerateEnemy()
		end
	end
	if not self._is_gameover then
		if A_UISystem.sym_map[97] then
			if self._player_1.parent ~= nil and self._player_1.alive then
				self._player_1:Walk(BattleCity.DirType.DT_LEFT, frame_time)
			end
		elseif A_UISystem.sym_map[119] then
			if self._player_1.parent ~= nil and self._player_1.alive then
				self._player_1:Walk(BattleCity.DirType.DT_UP, frame_time)
			end
		elseif A_UISystem.sym_map[115] then
			if self._player_1.parent ~= nil and self._player_1.alive then
				self._player_1:Walk(BattleCity.DirType.DT_DOWN, frame_time)
			end
		elseif A_UISystem.sym_map[100] then
			if self._player_1.parent ~= nil and self._player_1.alive then
				self._player_1:Walk(BattleCity.DirType.DT_RIGHT, frame_time)
			end
		end
		if A_UISystem.sym_map[1073741904] then
			if self._player_2.parent ~= nil and self._player_2.alive then
				self._player_2:Walk(BattleCity.DirType.DT_LEFT, frame_time)
			end
		elseif A_UISystem.sym_map[1073741906] then
			if self._player_2.parent ~= nil and self._player_2.alive then
				self._player_2:Walk(BattleCity.DirType.DT_UP, frame_time)
			end
		elseif A_UISystem.sym_map[1073741905] then
			if self._player_2.parent ~= nil and self._player_2.alive then
				self._player_2:Walk(BattleCity.DirType.DT_DOWN, frame_time)
			end
		elseif A_UISystem.sym_map[1073741903] then
			if self._player_2.parent ~= nil and self._player_2.alive then
				self._player_2:Walk(BattleCity.DirType.DT_RIGHT, frame_time)
			end
		end
	end
	if self._player_1.parent ~= nil then
		self._player_1:UpdateFrame(frame_time)
	end
	if self._player_2.parent ~= nil then
		self._player_2:UpdateFrame(frame_time)
	end
	for enemy, _ in ___pairs(self._enemy_map) do
		enemy:UpdateFrame(frame_time)
	end
	for bullet, _ in ___pairs(self._bullet_map) do
		bullet:UpdateFrame(frame_time)
	end
	for bullet_1, _1 in ___pairs(self._bullet_map) do
		for bullet_2, _2 in ___pairs(self._bullet_map) do
			if bullet_1 ~= bullet_2 and bullet_1.alive and bullet_2.alive and bullet_1.role.is_enemy ~= bullet_2.role.is_enemy and self:Collision2(bullet_1, bullet_2) then
				bullet_1:BulletEnd()
				bullet_2:BulletEnd()
			end
		end
	end
	local remove_map
	for index, child in ___ipairs(self._item_container.childs) do
		local player = nil
		local player_data = nil
		local player_life = nil
		if self._player_1.parent ~= nil and self._player_1.alive and self:Collision2(self._player_1, child) then
			player = self._player_1
			player_data = g_GCenter.player1_data
			player_life = self._player1_life
		elseif self._player_2.parent ~= nil and self._player_2.alive and self:Collision2(self._player_2, child) then
			player = self._player_2
			player_data = g_GCenter.player2_data
			player_life = self._player2_life
		end
		if player ~= nil then
			if child.sprite.col_index == BattleCity.ItemType.IT_LIFE then
				player_data.life = player_data.life + (1)
				player_life.text = player_data.life - 1
			elseif child.sprite.col_index == BattleCity.ItemType.IT_STAR then
				player:LevelUp()
				player_data.level = player.level
			elseif child.sprite.col_index == BattleCity.ItemType.IT_BOMB then
				for enemy, _ in ___pairs(self._enemy_map) do
					if enemy.alive then
						enemy:StartExplosion()
					end
				end
			elseif child.sprite.col_index == BattleCity.ItemType.IT_IRON then
				self._iron_flash = false
				self._iron_flash_count = 0
				self._iron_flash_frame = 0
				local brush_type = BattleCity.BrushType.BT_IRON
				local row = 11 * 4 + 2
				while true do
					if not(row <= 11 * 4 + 3) then break end
					local col = 5 * 4 + 2
					while true do
						if not(col <= 5 * 4 + 9) then break end
						self:SetTileShow(row, col, brush_type)
						col = col+(1)
					end
					row = row+(1)
				end
				local row = 12 * 4 + 0
				while true do
					if not(row <= 12 * 4 + 3) then break end
					local col = 5 * 4 + 2
					while true do
						if not(col <= 5 * 4 + 3) then break end
						self:SetTileShow(row, col, brush_type)
						col = col+(1)
					end
					row = row+(1)
				end
				local row = 12 * 4 + 0
				while true do
					if not(row <= 12 * 4 + 3) then break end
					local col = 5 * 4 + 8
					while true do
						if not(col <= 5 * 4 + 9) then break end
						self:SetTileShow(row, col, brush_type)
						col = col+(1)
					end
					row = row+(1)
				end
				if self._iron_flash_delay_loop ~= nil then
					self._iron_flash_delay_loop:Stop()
				end
				self._iron_flash_delay_loop = ALittle.LoopTimer(Lua.Bind(self.StartIronFlash, self), 10000)
				self._iron_flash_delay_loop:Start()
			elseif child.sprite.col_index == BattleCity.ItemType.IT_SHIELD then
				player:StartShield()
			elseif child.sprite.col_index == BattleCity.ItemType.IT_STOP then
				if self._item_stop_delay_loop ~= nil then
					self._item_stop_delay_loop:Stop()
				end
				self._item_stop_delay_loop = ALittle.LoopTimer(Lua.Bind(self.ItemStopEnd, self), 10000)
				self._item_stop_delay_loop:Start()
			end
			if remove_map == nil then
				remove_map = {}
			end
			remove_map[child] = true
		end
	end
	if remove_map ~= nil then
		for child, _ in ___pairs(remove_map) do
			self._item_container:RemoveChild(child)
		end
	end
	if self._iron_flash then
		local brush_type = BattleCity.BrushType.BT_WALL
		self._iron_flash_frame = self._iron_flash_frame + (0.005 * frame_time)
		if self._iron_flash_frame >= 2 then
			self._iron_flash_frame = 0
		end
		if self._iron_flash_frame > 1 then
			self._iron_flash_count = self._iron_flash_count + (1)
			brush_type = BattleCity.BrushType.BT_IRON
		else
			if self._iron_flash_count >= 100 then
				self._iron_flash = false
			end
		end
		if self._iron_flash_brush ~= brush_type then
			self._iron_flash_brush = brush_type
			local row = 11 * 4 + 2
			while true do
				if not(row <= 11 * 4 + 3) then break end
				local col = 5 * 4 + 2
				while true do
					if not(col <= 5 * 4 + 9) then break end
					self:SetTileShow(row, col, brush_type)
					col = col+(1)
				end
				row = row+(1)
			end
			local row = 12 * 4 + 0
			while true do
				if not(row <= 12 * 4 + 3) then break end
				local col = 5 * 4 + 2
				while true do
					if not(col <= 5 * 4 + 3) then break end
					self:SetTileShow(row, col, brush_type)
					col = col+(1)
				end
				row = row+(1)
			end
			local row = 12 * 4 + 0
			while true do
				if not(row <= 12 * 4 + 3) then break end
				local col = 5 * 4 + 8
				while true do
					if not(col <= 5 * 4 + 9) then break end
					self:SetTileShow(row, col, brush_type)
					col = col+(1)
				end
				row = row+(1)
			end
		end
	end
	local brush_type = BattleCity.BrushType.BT_RIVER
	self._river_flash_frame = self._river_flash_frame + (0.0008 * frame_time)
	if self._river_flash_frame >= 2 then
		self._river_flash_frame = 0
	end
	if self._river_flash_frame > 1 then
		brush_type = BattleCity.BrushType.BT_RIVER2
	end
	if self._river_flash_brush ~= brush_type then
		self._river_flash_brush = brush_type
		for row, sub_map in ___pairs(self._river_map) do
			for col, sprite in ___pairs(sub_map) do
				self:SetTileShow(row, col, self._river_flash_brush)
			end
		end
	end
	if self._enemy_count <= 0 and self._enemy_tiletable.child_count == 0 then
		self:StageCompleted()
	end
end

function BattleCity.BattleScene:ItemStopEnd()
	self._item_stop_delay_loop = nil
end

function BattleCity.BattleScene:StartIronFlash()
	self._iron_flash = true
	self._iron_flash_count = 0
	self._iron_flash_frame = 0
end

function BattleCity.BattleScene:HandleKeyDown(mod, sym, scancode)
	if sym == 106 then
		if self._player_1.parent ~= nil and not self._player_1.alive then
			return
		end
		self._player_1:Fire()
	end
	if sym == 1073741913 then
		if self._player_2.parent ~= nil and not self._player_2.alive then
			return
		end
		self._player_2:Fire()
	end
end

function BattleCity.BattleScene:RoleDeath(role)
	self._entity_container:RemoveChild(role)
	if role == self._player_1 then
		g_GCenter.player1_data.life = g_GCenter.player1_data.life - (1)
		if g_GCenter.player_count >= 1 and g_GCenter.player1_data.life >= 1 then
			g_GCenter.player1_data.level = 1
			self._player1_life.text = g_GCenter.player1_data.life - 1
			self._entity_container:AddChild(self._player_1)
			self._player_1:StartBorn(12 * 4, 4 * 4, g_GCenter.player1_data.level, BattleCity.DirType.DT_UP, 0.08)
		end
	elseif role == self._player_2 then
		g_GCenter.player2_data.life = g_GCenter.player2_data.life - (1)
		if g_GCenter.player_count >= 2 and g_GCenter.player2_data.life >= 1 then
			g_GCenter.player2_data.level = 1
			self._player2_life.text = g_GCenter.player2_data.life - 1
			self._entity_container:AddChild(self._player_2)
			self._player_2:StartBorn(12 * 4, 8 * 4, g_GCenter.player2_data.level, BattleCity.DirType.DT_UP, 0.08)
		end
	else
		self._enemy_map[role] = nil
		self._enemy_count = self._enemy_count - (1)
	end
	if g_GCenter.player_count >= 2 and g_GCenter.player1_data.life <= 0 and g_GCenter.player2_data.life <= 0 or g_GCenter.player_count >= 1 and g_GCenter.player1_data.life <= 0 then
		self:ShowGameOver()
	end
end

function BattleCity.BattleScene:BulletDeath(bullet)
	local exist = self._bullet_map[bullet]
	if exist == nil then
		return
	end
	self._bullet_map[bullet] = nil
	bullet.role:AddBullet()
	self._bullet_container:RemoveChild(bullet)
end

end