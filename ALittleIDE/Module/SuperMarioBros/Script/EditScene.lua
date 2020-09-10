-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.SuperMarioBros == nil then _G.SuperMarioBros = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
SuperMarioBros.EditScene = Lua.Class(ALittle.DisplayLayout, "SuperMarioBros.EditScene")

function SuperMarioBros.EditScene:Show()
	self.visible = true
	self:Load(1, 1)
	ALittle.File_MakeDeepDir(SuperMarioBros.g_ModuleBasePath .. "Other/Map")
	ALittle.System_SetViewSize(ALittle.Math_Floor(self.width), ALittle.Math_Floor(self.height))
end

function SuperMarioBros.EditScene:Hide()
	self.visible = false
end

function SuperMarioBros.EditScene:Load(world, subworld)
	self:Save()
	self._world_input.text = world
	self._subworld_input.text = subworld
	self._path = "Other/Map/world_" .. world .. "_" .. subworld .. ".map"
	self._cur_data = SuperMarioBros.g_Control:LoadMessageFromFile(___all_struct[-876795489], self._path)
	if self._cur_data == nil then
		self._cur_data = {}
		self._cur_data.row_count = 0
		self._cur_data.col_count = 0
		self._cur_data.background = {}
		self._cur_data.mask = {}
		self._cur_data.object = {}
	end
end
SuperMarioBros.EditScene.Load = Lua.CoWrap(SuperMarioBros.EditScene.Load)

function SuperMarioBros.EditScene:Save()
	if self._cur_data == nil then
		return
	end
	local rflct = ___all_struct[-876795489]
	local factory
	factory = __CPPAPIMessageWriteFactory()
	if factory == nil then
		ALittle.Error("factory create failed")
		return
	end
	local invoke_info = ALittle.CreateMessageInfo(rflct.name)
	if invoke_info == nil then
		ALittle.Error("create message info failed:" .. rflct.name)
		return
	end
	ALittle.PS_WriteMessage(factory, invoke_info, nil, self._cur_data)
	factory:WriteToStdFile(ALittle.File_BaseFilePath() .. SuperMarioBros.g_ModuleBasePath .. self._path)
end

function SuperMarioBros.EditScene:HandleTileSelected(event)
	local col = ALittle.Math_Floor(event.rel_x / self._select_tile.width) + 1
	local row = ALittle.Math_Floor(event.rel_y / self._select_tile.height) + 1
	self._select_tile.col_index = col
	self._select_tile.row_index = row
end

function SuperMarioBros.EditScene:HandleWorldChanged(event)
	local world = ALittle.Math_ToInt(self._world_input.text)
	if world == nil or world < 0 then
		return
	end
	local subworld = ALittle.Math_ToInt(self._subworld_input.text)
	if subworld == nil or world < 0 then
		return
	end
	self:Load(world, subworld)
end

function SuperMarioBros.EditScene:HandleSaveClick(event)
	self:Save()
end

function SuperMarioBros.EditScene:HandleBackClick(event)
	self:Save()
	self:Hide()
	ALittle.System_SetViewSize(ALittle.Math_Floor(g_GCenter.login_scene.width), ALittle.Math_Floor(g_GCenter.login_scene.height))
	g_GCenter.login_scene:Show()
end

end