-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
BattleCity.BattleSettlement = Lua.Class(ALittle.DisplayLayout, "BattleCity.BattleSettlement")

function BattleCity.BattleSettlement:Show(player1_kill, player2_kill)
	self.visible = true
	if self._show_loop ~= nil then
		self._show_loop:Stop()
		self._show_loop = nil
	end
	self._player_1_container.visible = g_GCenter.player_count >= 1
	self._player_2_container.visible = g_GCenter.player_count >= 2
	local player_1_total = 0
	local player_2_total = 0
	local player_1_count = player1_kill[1]
	if player_1_count == nil then
		player_1_count = 0
	end
	local player_2_count = player2_kill[1]
	if player_2_count == nil then
		player_2_count = 0
	end
	player_1_total = player_1_total + (player_1_count)
	player_2_total = player_2_total + (player_2_count)
	self._show_loop = ALittle.LoopList()
	self._1_enemy_1_count.text = 0
	self._1_enemy_1_score.text = 0
	self._1_enemy_2_count.text = 0
	self._1_enemy_2_score.text = 0
	self._1_enemy_3_count.text = 0
	self._1_enemy_3_score.text = 0
	self._1_enemy_total.text = ""
	self._2_enemy_1_count.text = 0
	self._2_enemy_1_score.text = 0
	self._2_enemy_2_count.text = 0
	self._2_enemy_2_score.text = 0
	self._2_enemy_3_count.text = 0
	self._2_enemy_3_score.text = 0
	self._2_enemy_total.text = ""
	self._high_score.text = BattleCity.g_GConfig:GetInt("high_score", 2000)
	self._stage_num.text = g_GCenter.stage
	local player1_data = g_GCenter.player1_data
	local player2_data = g_GCenter.player2_data
	self._player_1_score.text = player1_data.score
	self._player_2_score.text = player2_data.score
	local group = ALittle.LoopGroup()
	group:AddUpdater(ALittle.LoopFunction(Lua.Bind(self.HandlePlayerEnemyScore, self, self._1_enemy_1_count, self._1_enemy_1_score, self._player_1_score, 1, player1_data), player_1_count, 500, 500))
	group:AddUpdater(ALittle.LoopFunction(Lua.Bind(self.HandlePlayerEnemyScore, self, self._2_enemy_1_count, self._2_enemy_1_score, self._player_2_score, 1, player2_data), player_2_count, 500, 500))
	self._show_loop:AddUpdater(group)
	player_1_count = player1_kill[2]
	if player_1_count == nil then
		player_1_count = 0
	end
	player_2_count = player2_kill[2]
	if player_2_count == nil then
		player_2_count = 0
	end
	player_1_total = player_1_total + (player_1_count)
	player_2_total = player_2_total + (player_2_count)
	group = ALittle.LoopGroup()
	group:AddUpdater(ALittle.LoopFunction(Lua.Bind(self.HandlePlayerEnemyScore, self, self._1_enemy_2_count, self._1_enemy_2_score, self._player_1_score, 2, player1_data), player_1_count, 500, 500))
	group:AddUpdater(ALittle.LoopFunction(Lua.Bind(self.HandlePlayerEnemyScore, self, self._2_enemy_2_count, self._2_enemy_2_score, self._player_2_score, 2, player2_data), player_2_count, 500, 500))
	self._show_loop:AddUpdater(group)
	player_1_count = player1_kill[3]
	if player_1_count == nil then
		player_1_count = 0
	end
	player_2_count = player2_kill[3]
	if player_2_count == nil then
		player_2_count = 0
	end
	player_1_total = player_1_total + (player_1_count)
	player_2_total = player_2_total + (player_2_count)
	group = ALittle.LoopGroup()
	group:AddUpdater(ALittle.LoopFunction(Lua.Bind(self.HandlePlayerEnemyScore, self, self._1_enemy_3_count, self._1_enemy_3_score, self._player_1_score, 3, player1_data), player_1_count, 500, 500))
	group:AddUpdater(ALittle.LoopFunction(Lua.Bind(self.HandlePlayerEnemyScore, self, self._2_enemy_3_count, self._2_enemy_3_score, self._player_2_score, 3, player2_data), player_2_count, 500, 500))
	self._show_loop:AddUpdater(group)
	group = ALittle.LoopGroup()
	group:AddUpdater(ALittle.LoopTimer(Lua.Bind(self.HandlePlayerTotalScore, self, self._1_enemy_total, player_1_total), 1000))
	group:AddUpdater(ALittle.LoopTimer(Lua.Bind(self.HandlePlayerTotalScore, self, self._2_enemy_total, player_2_total), 1000))
	self._show_loop:AddUpdater(group)
	self._show_loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(self.Hide, self), 1000))
	self._show_loop:Start()
end

function BattleCity.BattleSettlement:HandlePlayerEnemyScore(count_text, score_text, player_score, level, player_data)
	local count = ALittle.Math_ToInt(count_text.text)
	count = count + (1)
	count_text.text = count
	local score = ALittle.Math_ToInt(score_text.text)
	score = score + (level * 100)
	score_text.text = score
	player_data.score = player_data.score + (score)
	player_score.text = player_data.score
	local high_score = BattleCity.g_GConfig:GetInt("high_score", 2000)
	if player_data.score >= high_score then
		high_score = player_data.score
		BattleCity.g_GConfig:SetConfig("high_score", high_score, true)
		self._high_score.text = high_score
	end
end

function BattleCity.BattleSettlement:HandlePlayerTotalScore(total, value)
	total.text = value
end

function BattleCity.BattleSettlement:Hide()
	if g_GCenter.player_count >= 1 then
		BattleCity.g_GConfig:SetConfig("last_score_1", g_GCenter.player1_data.score, true)
	end
	if g_GCenter.player_count >= 2 then
		BattleCity.g_GConfig:SetConfig("last_score_2", g_GCenter.player2_data.score, true)
	end
	BattleCity.g_GConfig:SaveConfig()
	self.visible = false
	g_GCenter:NextStage()
end

end