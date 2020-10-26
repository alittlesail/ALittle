-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.SuperMarioBros == nil then _G.SuperMarioBros = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
SuperMarioBros.LoginScene = Lua.Class(ALittle.DisplayLayout, "SuperMarioBros.LoginScene")

function SuperMarioBros.LoginScene:Ctor()
	___rawset(self, "_option", 1)
end

function SuperMarioBros.LoginScene:Show()
	self.visible = true
	A_UISystem.keydown_callback = Lua.Bind(self.HandleKeyDown, self)
	g_GCenter.player_data.life = 3
	self._top_score.text = SuperMarioBros.g_GConfig:GetInt("top_score", 0)
	self._score.text = g_GCenter.player_data.score
	self._coin.text = 0
end

function SuperMarioBros.LoginScene:HandleKeyDown(mod, sym, scancode)
	if sym == 103 then
		self._option = self._option + (1)
		if self._option > 2 then
			self._option = 1
		end
		if self._option == 1 then
			self._select_cursor.y = self._startgame_text.y + self._startgame_text.height / 2 - self._select_cursor.height / 2
		elseif self._option == 2 then
			self._select_cursor.y = self._editworld_text.y + self._editworld_text.height / 2 - self._select_cursor.height / 2
		end
	end
	if sym == 104 then
		if self._option == 2 then
			A_UISystem.keydown_callback = nil
			self:Hide()
			g_GCenter.edit_scene:Show()
		elseif self._option == 1 then
			A_UISystem.keydown_callback = nil
			self:Hide()
			g_GCenter.stage_scene:Show(1, 1)
		end
	end
end

function SuperMarioBros.LoginScene:UpdateTopScore()
	local top_score = SuperMarioBros.g_GConfig:GetInt("top_score", 0)
	if top_score < g_GCenter.player_data.score then
		top_score = g_GCenter.player_data.score
		SuperMarioBros.g_GConfig:SetConfig("top_score", top_score)
		self._score.text = g_GCenter.player_data.score
	end
end

function SuperMarioBros.LoginScene:Hide()
	self.visible = false
end

end