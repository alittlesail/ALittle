-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


ALittleIDE.IDETileSettingDialog = Lua.Class(nil, "ALittleIDE.IDETileSettingDialog")

function ALittleIDE.IDETileSettingDialog:CreateDialog()
	self._dialog = ALittleIDE.g_Control:CreateControl("ide_tile_setting_dialog", self)
	A_LayerManager:AddToModal(self._dialog)
	self._dialog.visible = false
	self._dialog.close_callback = Lua.Bind(self.HandleClose, self)
end

function ALittleIDE.IDETileSettingDialog:ShowDialog(tile_map)
	local ___COROUTINE = coroutine.running()
	if self._dialog == nil then
		self:CreateDialog()
	end
	self._dialog.visible = true
	if tile_map.tile_type == 1 then
		self._tile_type.text = "正方形"
	elseif tile_map.tile_type == 3 then
		self._tile_type.text = "水平正六边形"
	elseif tile_map.tile_type == 2 then
		self._tile_type.text = "垂直正六边形"
	else
		self._tile_type.text = ""
	end
	self._side_len.text = tile_map.side_len
	self._tile_width.text = tile_map.tile_width
	self._tile_height.text = tile_map.tile_height
	self._tile_x.text = tile_map.tile_x
	self._tile_y.text = tile_map.tile_y
	self._tile_map = tile_map
	self._thread = ___COROUTINE
	return coroutine.yield()
end

function ALittleIDE.IDETileSettingDialog:HandleClose()
	self:HandleTileSettingCancel(nil)
	return true
end

function ALittleIDE.IDETileSettingDialog:HandleTileSettingCancel(event)
	self._dialog.visible = false
	self._tile_map = nil
	local thread = self._thread
	self._thread = nil
	if thread ~= nil then
		ALittle.Coroutine.Resume(thread, false)
	end
end

function ALittleIDE.IDETileSettingDialog:HandleTileSettingConfirm(event)
	self._dialog.visible = false
	local tile_map = self._tile_map
	self._tile_map = nil
	local thread = self._thread
	self._thread = nil
	if self._tile_type.text == "正方形" then
		tile_map.tile_type = 1
	elseif self._tile_type.text == "水平正六边形" then
		tile_map.tile_type = 3
	elseif self._tile_type.text == "垂直正六边形" then
		tile_map.tile_type = 2
	end
	tile_map.side_len = ALittle.Math_ToIntOrZero(self._side_len.text)
	tile_map.tile_width = ALittle.Math_ToIntOrZero(self._tile_width.text)
	tile_map.tile_height = ALittle.Math_ToIntOrZero(self._tile_height.text)
	tile_map.tile_x = ALittle.Math_ToIntOrZero(self._tile_x.text)
	tile_map.tile_y = ALittle.Math_ToIntOrZero(self._tile_y.text)
	if thread ~= nil then
		ALittle.Coroutine.Resume(thread, true)
	end
end

ALittleIDE.g_IDETileSettingDialog = ALittleIDE.IDETileSettingDialog()
end