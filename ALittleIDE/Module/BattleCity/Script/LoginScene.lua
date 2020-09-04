-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
BattleCity.LoginScene = Lua.Class(ALittle.DisplayLayout, "BattleCity.LoginScene")

function BattleCity.LoginScene:Ctor()
	___rawset(self, "_select_option", 1)
end

function BattleCity.LoginScene:TCtor()
	self._high_score.text = BattleCity.g_GConfig:GetInt("high_score", 2000)
	self._last_score_1.text = BattleCity.g_GConfig:GetInt("last_score_1", 0)
	self._last_score_2.text = BattleCity.g_GConfig:GetInt("last_score_2", 0)
	self._cursor:Stop()
	self.disabled = true
end

function BattleCity.LoginScene:Show()
	self.visible = true
	if self._anti_loop ~= nil then
		self._anti_loop:Stop()
		self._anti_loop = nil
	end
	self.y = A_UISystem.view_height
	self._cursor.visible = false
	self._anti_loop = ALittle.LoopList()
	self._anti_loop:AddUpdater(ALittle.LoopLinear(self, "y", 0, 10000, 0))
	self._anti_loop:AddUpdater(ALittle.LoopAttribute(self._cursor, "visible", true, 0))
	self._anti_loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(self._cursor.Play, self._cursor), 0))
	self._anti_loop:Start()
	A_UISystem.keydown_callback = Lua.Bind(self.HandleKeyDown, self)
end

function BattleCity.LoginScene:Hide()
	if self._anti_loop ~= nil then
		self._anti_loop:Stop()
		self._anti_loop = nil
	end
	self._cursor:Stop()
	self.visible = false
	A_UISystem.keydown_callback = nil
end

function BattleCity.LoginScene:HandleKeyDown(mod, sym, scancode)
	if self._cursor.visible == false then
		if sym == 103 or sym == 104 then
			self._anti_loop:SetCompleted()
		end
		return
	end
	if sym == 103 then
		self._select_option = self._select_option + (1)
		if self._select_option > 3 then
			self._select_option = 1
		end
		if self._select_option == 1 then
			self._cursor.y = self._1_player_text.y + self._1_player_text.height / 2 - self._cursor.height / 2
		elseif self._select_option == 2 then
			self._cursor.y = self._2_player_text.y + self._2_player_text.height / 2 - self._cursor.height / 2
		elseif self._select_option == 3 then
			self._cursor.y = self._edit_text.y + self._edit_text.height / 2 - self._cursor.height / 2
		end
		return
	end
	if sym == 104 then
		self:Hide()
		if self._select_option == 3 then
			g_GCenter.edit_scene:Show()
		else
			g_GCenter:StartPlay(self._select_option)
		end
	end
end

end