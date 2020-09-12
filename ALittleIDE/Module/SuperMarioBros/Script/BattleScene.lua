-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.SuperMarioBros == nil then _G.SuperMarioBros = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


local TILE_COL_COUNT = 13
local TILE_ROW_COUNT = 11
local TILE_WIDTH = 32
local TILE_HEIGHT = 32
local TILE_TEXTURE_NAME = "tile_map.png"
assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
SuperMarioBros.BattleScene = Lua.Class(ALittle.DisplayLayout, "SuperMarioBros.BattleScene")

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
	self._tile_linear:RemoveAllChild()
	self._entity_container:RemoveAllChild()
	self._entity_map = {}
	for row, submap in ___pairs(self._battle_map.background) do
		for col, index in ___pairs(submap) do
			local show_row = ALittle.Math_Floor(index / TILE_COL_COUNT) + 1
			local show_col = index % TILE_COL_COUNT + 1
			self:SetTileShow(row, col, show_row, show_col)
		end
	end
	self._scroll_screen.container.width = self._tile_linear.width + self._scroll_screen.view_width
	self._scroll_screen:RefreshClipDisLine()
	self.visible = true
end
SuperMarioBros.BattleScene.Show = Lua.CoWrap(SuperMarioBros.BattleScene.Show)

function SuperMarioBros.BattleScene:SetTileShow(row, col, show_row, show_col)
	if self._tile_linear.child_count < col + 1 then
		local i = self._tile_linear.child_count
		while true do
			if not(i < col + 1) then break end
			local linear = ALittle.Linear(SuperMarioBros.g_Control)
			linear.type = 2
			linear.width = TILE_WIDTH
			self._tile_linear:AddChild(linear)
			i = i+(1)
		end
		self._scroll_screen.container.width = self._tile_linear.width + self._scroll_screen.view_width
		self._scroll_screen:RejustScrollBar()
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
			sprite.texture_name = TILE_TEXTURE_NAME
			sprite.row_count = TILE_ROW_COUNT
			sprite.col_count = TILE_COL_COUNT
			sprite.width = TILE_WIDTH
			sprite.height = TILE_HEIGHT
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

function SuperMarioBros.BattleScene:Hide()
	self.visible = false
end

end