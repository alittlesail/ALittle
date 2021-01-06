-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1815508639, "ALittle.TextureCutInfo", {
name = "ALittle.TextureCutInfo", ns_name = "ALittle", rl_name = "TextureCutInfo", hash_code = -1815508639,
name_list = {"texture_name","max_width","max_height","cache"},
type_list = {"string","int","int","bool"},
option_map = {}
})
ALittle.RegStruct(1812223610, "ALittle.LoadAtlasInfo", {
name = "ALittle.LoadAtlasInfo", ns_name = "ALittle", rl_name = "LoadAtlasInfo", hash_code = 1812223610,
name_list = {"big_path","atlas","big_width","big_height"},
type_list = {"string","List<string>","int","int"},
option_map = {}
})
ALittle.RegStruct(1754262532, "ALittle.LoadingTextureInfo", {
name = "ALittle.LoadingTextureInfo", ns_name = "ALittle", rl_name = "LoadingTextureInfo", hash_code = 1754262532,
name_list = {"cache","object_map"},
type_list = {"bool","Map<ALittle.DisplayObject,ALittle.LoadingTextureObjectInfo>"},
option_map = {}
})
ALittle.RegStruct(1390702448, "ALittle.AltasCollectInfo", {
name = "ALittle.AltasCollectInfo", ns_name = "ALittle", rl_name = "AltasCollectInfo", hash_code = 1390702448,
name_list = {"count","list"},
type_list = {"int","List<List<any>>"},
option_map = {}
})
ALittle.RegStruct(1305876767, "ALittle.PrepareInfo", {
name = "ALittle.PrepareInfo", ns_name = "ALittle", rl_name = "PrepareInfo", hash_code = 1305876767,
name_list = {"total","succeed","failed","map","callback"},
type_list = {"int","int","int","Map<string,bool>","Functor<(int,int,int)>"},
option_map = {}
})
ALittle.RegStruct(1266404893, "ALittle.LoadTextureInfo", {
name = "ALittle.LoadTextureInfo", ns_name = "ALittle", rl_name = "LoadTextureInfo", hash_code = 1266404893,
name_list = {"loader","cut_loader","texture_mgr"},
type_list = {"ALittle.ITextureLoader","ALittle.ITextureCutLoader","ALittle.TextureManager"},
option_map = {}
})
ALittle.RegStruct(1002517605, "ALittle.LoadingTextureObjectInfo", {
name = "ALittle.LoadingTextureObjectInfo", ns_name = "ALittle", rl_name = "LoadingTextureObjectInfo", hash_code = 1002517605,
name_list = {"callback"},
type_list = {"Functor<(ALittle.DisplayObject,bool)>"},
option_map = {}
})
ALittle.RegStruct(-451991995, "ALittle.AltasTextureInfo", {
name = "ALittle.AltasTextureInfo", ns_name = "ALittle", rl_name = "AltasTextureInfo", hash_code = -451991995,
name_list = {"width","height","path"},
type_list = {"int","int","string"},
option_map = {}
})
ALittle.RegStruct(-60039899, "ALittle.AltasInfo", {
name = "ALittle.AltasInfo", ns_name = "ALittle", rl_name = "AltasInfo", hash_code = -60039899,
name_list = {"big_path","atlas","big_width","big_height","t","b","l","r"},
type_list = {"string","List<string>","int","int","double","double","double","double"},
option_map = {}
})

ALittle.LoadTextureManager = Lua.Class(nil, "ALittle.LoadTextureManager")

function ALittle.LoadTextureManager:Ctor()
	___rawset(self, "_id_map_info", {})
	___rawset(self, "_path_map_texture_cut", ALittle.CreateValueWeakMap())
	___rawset(self, "_path_map_objects_cut", {})
	___rawset(self, "_redraw_map_redraw", ALittle.CreateKeyWeakMap())
	___rawset(self, "_texmgr_map_texmgr", ALittle.CreateKeyWeakMap())
end

function ALittle.LoadTextureManager:CreateTexture(texture_mgr, atlas)
	local loader
	loader = __CPPAPITextureLoader()
	loader:SetPath(atlas.big_path, ALittle.String_Join(atlas.atlas, ";"), atlas.big_width, atlas.big_height, texture_mgr.crypt_mode)
	local info = {}
	self._id_map_info[loader:GetID()] = info
	info.texture_mgr = texture_mgr
	info.loader = loader
	loader:Start()
end

function ALittle.LoadTextureManager:HandleTextureLoadSucceed(loader, texture)
	local loader_id = loader:GetID()
	local info = self._id_map_info[loader_id]
	if info == nil then
		return
	end
	self._id_map_info[loader_id] = nil
	info.texture_mgr:HandleTextureLoadSucceed(loader, texture)
end

function ALittle.LoadTextureManager:HandleTextureLoadFailed(loader)
	local loader_id = loader:GetID()
	local info = self._id_map_info[loader_id]
	if info == nil then
		return
	end
	self._id_map_info[loader_id] = nil
	info.texture_mgr:HandleTextureLoadFailed(loader)
end

function ALittle.LoadTextureManager:GetTextureCut(path, max_width, max_height)
	local texture_id = path .. "_" .. max_width .. "_" .. max_height
	return self._path_map_texture_cut[texture_id]
end

function ALittle.LoadTextureManager:ClearTextureCut(path, max_width, max_height)
	local texture_id = path .. "_" .. max_width .. "_" .. max_height
	self._path_map_texture_cut[texture_id] = nil
end

function ALittle.LoadTextureManager:IsLoadingTextureCut(path, max_width, max_height)
	local texture_id = path .. "_" .. max_width .. "_" .. max_height
	return self._path_map_objects_cut[texture_id] ~= nil
end

function ALittle.LoadTextureManager:SetTextureCut(object, path, max_width, max_height, cache, callback)
	object:SetTextureCoord(0, 1, 0, 1)
	if max_width == nil then
		max_width = 0
	end
	max_width = ALittle.Math_Floor(max_width)
	if max_height == nil then
		max_height = 0
	end
	max_height = ALittle.Math_Floor(max_height)
	if cache == nil then
		cache = false
	end
	local texture_id = path .. "_" .. max_width .. "_" .. max_height
	local texture = self._path_map_texture_cut[texture_id]
	if texture ~= nil then
		object.texture = texture
		if callback ~= nil then
			callback(object, true)
		end
		return
	end
	local loading_info = self._path_map_objects_cut[texture_id]
	if loading_info ~= nil then
		local object_info = {}
		object_info.callback = callback
		loading_info.object_map[object] = object_info
		return
	end
	loading_info = {}
	loading_info.cache = cache
	self._path_map_objects_cut[texture_id] = loading_info
	loading_info.object_map = ALittle.CreateKeyWeakMap()
	local object_info = {}
	object_info.callback = callback
	loading_info.object_map[object] = object_info
	local loader
	loader = __CPPAPITextureCutLoader()
	loader:SetPath(path, max_width, max_height)
	local info = {}
	self._id_map_info[loader:GetID()] = info
	info.cut_loader = loader
	loader:Start()
end

function ALittle.LoadTextureManager:HandleTextureCutLoadSucceed(loader, texture)
	local loader_id = loader:GetID()
	local info = self._id_map_info[loader_id]
	if info == nil then
		return
	end
	self._id_map_info[loader_id] = nil
	local texture_wrap = __CPPAPITextureWrap()
	texture_wrap:SetTexture(texture)
	texture = texture_wrap
	local path = loader:GetPath()
	local max_width = loader:GetMaxWidth()
	local max_height = loader:GetMaxHeight()
	local texture_id = path .. "_" .. max_width .. "_" .. max_height
	local loading_info = self._path_map_objects_cut[texture_id]
	if loading_info == nil then
		return
	end
	if loading_info.cache then
		self._path_map_texture_cut[texture_id] = texture
	end
	for object, value in ___pairs(loading_info.object_map) do
		if object.texture_name == path then
			object.texture = texture
			if value.callback ~= nil then
				value.callback(object, true)
			end
		end
	end
	self._path_map_objects_cut[texture_id] = nil
end

function ALittle.LoadTextureManager:HandleTextureCutLoadFailed(loader)
	local loader_id = loader:GetID()
	local info = self._id_map_info[loader_id]
	if info == nil then
		return
	end
	self._id_map_info[loader_id] = nil
	local path = loader:GetPath()
	local max_width = loader:GetMaxWidth()
	local max_height = loader:GetMaxHeight()
	local texture_id = path .. "_" .. max_width .. "_" .. max_height
	local loading_info = self._path_map_objects_cut[texture_id]
	if loading_info == nil then
		return
	end
	for object, value in ___pairs(loading_info.object_map) do
		if value.callback ~= nil then
			value.callback(object, false)
		end
	end
	self._path_map_objects_cut[texture_id] = nil
end

function ALittle.LoadTextureManager:RegisterRedrawControl(control)
	self._redraw_map_redraw[control] = true
end

function ALittle.LoadTextureManager:RegisterTexmgrControl(control)
	self._texmgr_map_texmgr[control] = nil
end

function ALittle.LoadTextureManager:HandleRenderDeviceReset()
	self._path_map_texture_cut = ALittle.CreateValueWeakMap()
	for texmgr, _ in ___pairs(self._texmgr_map_texmgr) do
		texmgr:ClearCache()
	end
	for control, _ in ___pairs(self._redraw_map_redraw) do
		control:Redraw()
	end
end

_G.A_LoadTextureManager = ALittle.LoadTextureManager()
ALittle.AltasBinary = Lua.Class(nil, "ALittle.AltasBinary")

function ALittle.AltasBinary:Ctor(x, y, width, height)
	___rawset(self, "_width", width)
	___rawset(self, "_height", height)
	___rawset(self, "_x", x)
	___rawset(self, "_y", y)
	___rawset(self, "_texture_x", nil)
	___rawset(self, "_texture_y", nil)
	___rawset(self, "_texture_w", nil)
	___rawset(self, "_texture_h", nil)
	___rawset(self, "_texture_path", nil)
	___rawset(self, "_left", nil)
	___rawset(self, "_right", nil)
end

function ALittle.AltasBinary:Fill(texture_info, padding)
	if self._left ~= nil then
		if self._left:Fill(texture_info, padding) then
			return true
		end
	end
	if self._right ~= nil then
		if self._right:Fill(texture_info, padding) then
			return true
		end
	end
	if self._texture_path == nil then
		local real_width = texture_info.width + padding * 2
		local real_height = texture_info.height + padding * 2
		if real_width > self._width then
			return false
		end
		if real_height > self._height then
			return false
		end
		self._texture_w = texture_info.width
		self._texture_h = texture_info.height
		self._texture_x = self._x + padding
		self._texture_y = self._y + padding
		self._texture_path = texture_info.path
		self._left = ALittle.AltasBinary(self._x + real_width, self._y, self._width - real_width, real_height)
		self._right = ALittle.AltasBinary(self._x, self._y + real_height, self._width, self._height - real_height)
		return true
	end
	return false
end

function ALittle.AltasBinary:GetInfo(list_info)
	if list_info == nil then
		list_info = {}
		list_info.count = 0
		list_info.list = {}
	end
	if self._texture_path ~= nil then
		local info = {}
		info[1] = self._texture_path
		info[2] = self._texture_x
		info[3] = self._texture_y
		info[4] = self._texture_w
		info[5] = self._texture_h
		list_info.count = list_info.count + 1
		list_info.list[list_info.count] = info
	end
	if self._left ~= nil then
		self._left:GetInfo(list_info)
	end
	if self._right ~= nil then
		self._right:GetInfo(list_info)
	end
	return list_info.list
end

function ALittle.AltasBinary.TextureListComp(a, b)
	if a.height > b.height then
		return true
	elseif a.height == b.height then
		if a.width > b.width then
			return true
		elseif a.width == b.width then
			if a.path > b.path then
				return true
			end
		end
	end
	return false
end

function ALittle.AltasBinary.GenerateAltas(texture_list, max_width, max_height, padding)
	ALittle.List_Sort(texture_list, ALittle.AltasBinary.TextureListComp)
	local big_list = {}
	local big_list_count = 0
	big_list_count = big_list_count + 1
	big_list[big_list_count] = max_width
	big_list_count = big_list_count + 1
	big_list[big_list_count] = max_height
	while true do
		local altas = ALittle.AltasBinary(0, 0, max_width, max_height)
		local left_list = {}
		local left_list_count = 0
		for index, texture_info in ___ipairs(texture_list) do
			local real_width = texture_info.width + padding * 2
			local real_height = texture_info.height + padding * 2
			if real_width <= max_width and real_height <= max_height then
				if altas:Fill(texture_info, padding) ~= true then
					left_list_count = left_list_count + 1
					left_list[left_list_count] = texture_info
				end
			end
		end
		local list = altas:GetInfo()
		if list[2] ~= nil then
			big_list_count = big_list_count + 1
			big_list[big_list_count] = list
		end
		texture_list = left_list
		if texture_list[1] == nil then
			break
		end
	end
	return big_list
end

ALittle.TextureManager = Lua.Class(nil, "ALittle.TextureManager")

function ALittle.TextureManager:Ctor(module_name, crypt_mode)
	___rawset(self, "_cache_texture", true)
	___rawset(self, "_base_path", "Module/" .. module_name .. "/Texture/")
	___rawset(self, "_crypt_mode", crypt_mode or false)
	___rawset(self, "_path_map_texture", ALittle.CreateValueWeakMap())
	___rawset(self, "_prepare_map", {})
	___rawset(self, "_path_map_objects", {})
	self:LoadAtlas()
end

function ALittle.TextureManager:LoadAtlas()
	self._name_map_atlas = {}
	if not self._crypt_mode then
		return
	end
	local big_list = ALittle.File_ReadJsonFromFile(self._base_path .. "Atlas.ali", self._crypt_mode)
	if big_list == nil then
		return
	end
	local big_list_count = ALittle.List_Len(big_list)
	if big_list_count < 2 then
		return
	end
	local texture_width = big_list[1]
	local texture_height = big_list[2]
	local index = 3
	while true do
		if not(index <= big_list_count) then break end
		local list = big_list[index]
		local big_path = index .. ".atlas"
		local info = {}
		local info_count = 0
		for _, value in ___ipairs(list) do
			local path = value[1]
			local x = value[2]
			local y = value[3]
			local w = value[4]
			local h = value[5]
			local atlas = {}
			atlas.big_path = big_path
			atlas.t = y / texture_height
			atlas.b = (y + h) / texture_height
			atlas.l = x / texture_width
			atlas.r = (x + w) / texture_width
			atlas.big_width = texture_width
			atlas.big_height = texture_height
			atlas.atlas = info
			self._name_map_atlas[path] = atlas
			info_count = info_count + 1
			info[info_count] = self._base_path .. path .. "," .. y .. "," .. (y + h) .. "," .. x .. "," .. (x + w) .. "," .. w .. "," .. h
		end
		index = index+(1)
	end
end

function ALittle.TextureManager:GetAtlas(name)
	local atlas = self._name_map_atlas[name]
	if atlas ~= nil then
		return atlas
	end
	atlas = {}
	self._name_map_atlas[name] = atlas
	atlas.big_path = name
	atlas.t = 0
	atlas.b = 1
	atlas.l = 0
	atlas.r = 1
	atlas.big_width = 0
	atlas.big_height = 0
	atlas.atlas = {}
	atlas.atlas[1] = self._base_path .. name .. ",0,0,0,0,0,0"
	return atlas
end

function ALittle.TextureManager.__setter:cache_texture(cache)
	self._cache_texture = cache
end

function ALittle.TextureManager.__getter:cache_texture()
	return self._cache_texture
end

function ALittle.TextureManager.__getter:crypt_mode()
	return self._crypt_mode
end

function ALittle.TextureManager:ClearCache()
	self._path_map_texture = ALittle.CreateValueWeakMap()
	self._prepare_map = {}
end

function ALittle.TextureManager:PrepareTexture(name_map, callback)
	local new_name_map = {}
	for name, value in ___pairs(name_map) do
		local atlas = self:GetAtlas(name)
		if new_name_map[atlas.big_path] == nil then
			local texture = self._path_map_texture[atlas.big_path]
			if texture == nil then
				local loading_map = self._path_map_objects[atlas.big_path]
				if loading_map == nil then
					loading_map = ALittle.CreateKeyWeakMap()
					self._path_map_objects[atlas.big_path] = loading_map
				end
				A_LoadTextureManager:CreateTexture(self, atlas)
				new_name_map[atlas.big_path] = false
			else
				new_name_map[atlas.big_path] = true
			end
		end
	end
	local prepare_info = {}
	prepare_info.total = 0
	prepare_info.succeed = 0
	prepare_info.failed = 0
	prepare_info.map = new_name_map
	prepare_info.callback = callback
	for name, value in ___pairs(new_name_map) do
		prepare_info.total = prepare_info.total + 1
		if value then
			prepare_info.succeed = prepare_info.succeed + 1
		end
	end
	if prepare_info.total > prepare_info.succeed + prepare_info.failed then
		self._prepare_map[prepare_info] = true
	end
	if callback ~= nil then
		callback(prepare_info.total, prepare_info.succeed, prepare_info.failed)
	end
end

function ALittle.TextureManager:SetTexture(object, name)
	local atlas = self:GetAtlas(name)
	object:SetTextureCoord(atlas.t, atlas.b, atlas.l, atlas.r)
	local texture = self._path_map_texture[atlas.big_path]
	if texture ~= nil then
		object.texture = texture
		return
	end
	local loading_map = self._path_map_objects[atlas.big_path]
	if loading_map ~= nil then
		loading_map[object] = name
		return
	end
	loading_map = ALittle.CreateKeyWeakMap()
	self._path_map_objects[atlas.big_path] = loading_map
	loading_map[object] = name
	A_LoadTextureManager:CreateTexture(self, atlas)
end

function ALittle.TextureManager:HandleTextureLoadSucceed(loader, texture)
	local texture_wrap = __CPPAPITextureWrap()
	texture_wrap:SetTexture(texture)
	texture = texture_wrap
	local path = loader:GetPath()
	local loading_map = self._path_map_objects[path]
	if loading_map ~= nil then
		if self._cache_texture then
			self._path_map_texture[path] = texture
		end
		for k, v in ___pairs(loading_map) do
			if k.texture_name == v then
				k.texture = texture
			end
		end
		self._path_map_objects[path] = nil
	end
	local copy_map = {}
	for k, v in ___pairs(self._prepare_map) do
		copy_map[k] = v
	end
	local erase_map = {}
	for info, v in ___pairs(copy_map) do
		if info.map[path] == false then
			info.succeed = info.succeed + 1
			info.map[path] = true
			if info.callback ~= nil then
				info.callback(info.total, info.succeed, info.failed)
			end
			if info.total <= info.succeed + info.failed then
				erase_map[info] = true
			end
		end
	end
	for info, v in ___pairs(erase_map) do
		self._prepare_map[info] = nil
	end
end

function ALittle.TextureManager:HandleTextureLoadFailed(loader)
	local path = loader:GetPath()
	self._path_map_objects[path] = nil
	local erase_map = {}
	for info, v in ___pairs(self._prepare_map) do
		if info.map[path] == false then
			info.failed = info.failed + 1
			info.map[path] = true
			if info.callback ~= nil then
				info.callback(info.total, info.succeed, info.failed)
			end
			if info.total <= info.succeed + info.failed then
				erase_map[info] = true
			end
		end
	end
	for info, v in ___pairs(erase_map) do
		self._prepare_map[info] = nil
	end
end

end