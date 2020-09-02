-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
BattleCity.BattleScene = Lua.Class(ALittle.DisplayLayout, "BattleCity.BattleScene")

function BattleCity.BattleScene:TCtor()
	self._player_1 = BattleCity.g_Control:CreateControl("battle_player1")
	self._player_2 = BattleCity.g_Control:CreateControl("battle_player2")
	self._cell_size = self._tile_container.width / (13 * 4)
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
	self._enemy_map = {}
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
	self._player_1:RemoveFromParent()
	self._player_2:RemoveFromParent()
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
	if self._player_1.parent ~= nil and self._player_1.alive and entity ~= self._player_1 and self:Collision(left, top, right, bottom, self._player_1) then
		return false
	end
	if self._player_2.parent ~= nil and self._player_2.alive and entity ~= self._player_2 and self:Collision(left, top, right, bottom, self._player_2) then
		return false
	end
	for role, _ in ___pairs(self._enemy_map) do
		if role ~= entity and entity.alive and self:Collision(left, top, right, bottom, role) then
			return false
		end
	end
	return true
end

function BattleCity.BattleScene:GenerateEnemy()
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
	if A_UISystem.sym_map[97] then
		if self._player_1.parent ~= nil and not self._player_1.alive then
			return
		end
		self._player_1:Walk(BattleCity.DirType.DT_LEFT, frame_time)
	elseif A_UISystem.sym_map[119] then
		if self._player_1.parent ~= nil and not self._player_1.alive then
			return
		end
		self._player_1:Walk(BattleCity.DirType.DT_UP, frame_time)
	elseif A_UISystem.sym_map[115] then
		if self._player_1.parent ~= nil and not self._player_1.alive then
			return
		end
		self._player_1:Walk(BattleCity.DirType.DT_DOWN, frame_time)
	elseif A_UISystem.sym_map[100] then
		if self._player_1.parent ~= nil and not self._player_1.alive then
			return
		end
		self._player_1:Walk(BattleCity.DirType.DT_RIGHT, frame_time)
	end
	if A_UISystem.sym_map[1073741904] then
		if self._player_2.parent ~= nil and not self._player_2.alive then
			return
		end
		self._player_2:Walk(BattleCity.DirType.DT_LEFT, frame_time)
	elseif A_UISystem.sym_map[1073741906] then
		if self._player_2.parent ~= nil and not self._player_2.alive then
			return
		end
		self._player_2:Walk(BattleCity.DirType.DT_UP, frame_time)
	elseif A_UISystem.sym_map[1073741905] then
		if self._player_2.parent ~= nil and not self._player_2.alive then
			return
		end
		self._player_2:Walk(BattleCity.DirType.DT_DOWN, frame_time)
	elseif A_UISystem.sym_map[1073741903] then
		if self._player_2.parent ~= nil and not self._player_2.alive then
			return
		end
		self._player_2:Walk(BattleCity.DirType.DT_RIGHT, frame_time)
	end
end

function BattleCity.BattleScene:HandleKeyDown(mod, sym, scancode)
end

function BattleCity.BattleScene:RoleDeath(player)
end

end