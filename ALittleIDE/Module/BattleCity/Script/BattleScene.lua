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

function BattleCity.BattleScene:Show(stage)
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
	self._sprite_map = {}
	for row, sub_map in ___pairs(self._battle_map.tile_map) do
		for col, type in ___pairs(sub_map) do
			self:SetTileShow(row, col, type)
		end
	end
	self.visible = true
	self._stage_num.text = stage
	self._player1_life.text = g_GCenter.player1_data.life
	self._player2_life.text = g_GCenter.player2_data.life
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
	self:GenerateEnemy()
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
end

function BattleCity.BattleScene:SetTileShow(row, col, type)
	local sub_map = self._sprite_map[row]
	if sub_map == nil then
		sub_map = {}
		self._sprite_map[row] = sub_map
	end
	if sub_map[col] ~= nil then
		self._tile_container:RemoveChild(sub_map[col])
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
	self._tile_container:AddChild(sprite)
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

function BattleCity.BattleScene:CanWalkByEntity(entity, left, top, right, bottom)
	if self._player_1.parent ~= nil and entity ~= self._player_1 and self:Collision(left, top, right, bottom, self._player_1) then
		return false
	end
	if self._player_2.parent ~= nil and entity ~= self._player_2 and self:Collision(left, top, right, bottom, self._player_2) then
		return false
	end
	for role, _ in ___pairs(self._enemy_map) do
		if role ~= entity and self:Collision(left, top, right, bottom, role) then
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
				return true, role:BeAttack()
			end
		end
	end
	return false, false
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

function BattleCity.BattleScene:FireBullet(role)
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
	bullet:Init(role.dir, role)
	self._bullet_container:AddChild(bullet)
	self._bullet_map[bullet] = true
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
		self._player_1:StartBorn(12 * 4, 4 * 4 + 2, g_GCenter.player1_data.level, BattleCity.DirType.DT_UP, 0.08)
	end
	if g_GCenter.player_count >= 2 then
		self._entity_container:AddChild(self._player_2)
		self._player_2:StartBorn(12 * 4, 8 * 4 - 2, g_GCenter.player2_data.level, BattleCity.DirType.DT_UP, 0.08)
	end
end

function BattleCity.BattleScene:HandleFrame(frame_time)
	if self._enemy_count < 4 then
		self._generate_enemy_cool = self._generate_enemy_cool - (frame_time)
		if self._generate_enemy_cool <= 0 then
			self:GenerateEnemy()
		end
	end
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
		if g_GCenter.player_count >= 1 and g_GCenter.player1_data.life > 0 then
			g_GCenter.player1_data.life = g_GCenter.player1_data.life - (1)
			g_GCenter.player1_data.level = 1
			self._player1_life.text = g_GCenter.player1_data.life
			self._entity_container:AddChild(self._player_1)
			self._player_1:StartBorn(12 * 4, 4 * 4 + 2, g_GCenter.player1_data.level, BattleCity.DirType.DT_UP, 0.08)
		end
	elseif role == self._player_2 then
		if g_GCenter.player_count >= 2 and g_GCenter.player2_data.life > 0 then
			g_GCenter.player2_data.life = g_GCenter.player2_data.life - (1)
			g_GCenter.player2_data.level = 1
			self._player2_life.text = g_GCenter.player2_data.life
			self._entity_container:AddChild(self._player_2)
			self._player_2:StartBorn(12 * 4, 4 * 4 + 2, g_GCenter.player2_data.level, BattleCity.DirType.DT_UP, 0.08)
		end
	else
		self._enemy_map[role] = nil
		self._enemy_count = self._enemy_count - (1)
	end
end

function BattleCity.BattleScene:BulletDeath(bullet)
	self._bullet_container:RemoveChild(bullet)
	self._bullet_map[bullet] = nil
end

end