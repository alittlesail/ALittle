-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1040774381, "ALittle.CsvPreloadInfo", {
name = "ALittle.CsvPreloadInfo", ns_name = "ALittle", rl_name = "CsvPreloadInfo", hash_code = -1040774381,
name_list = {"total","succeed","failed","loader_map","callback"},
type_list = {"int","int","int","Map<int,ALittle.CsvPreloadInfoDetail>","Functor<(int,int,int)>"},
option_map = {}
})
ALittle.RegStruct(332955965, "ALittle.CsvPreloadInfoDetail", {
name = "ALittle.CsvPreloadInfoDetail", ns_name = "ALittle", rl_name = "CsvPreloadInfoDetail", hash_code = 332955965,
name_list = {"loader","config"},
type_list = {"ALittle.ICsvFileLoader","ALittle.CsvConfig"},
option_map = {}
})

ALittle.CsvConfigManager = Lua.Class(nil, "ALittle.CsvConfigManager")

function ALittle.CsvConfigManager:Ctor()
	___rawset(self, "_preload_map", {})
end

function ALittle.CsvConfigManager:PrepareCsv(csv_map, callback)
	local preload_info = {}
	preload_info.total = 0
	preload_info.succeed = 0
	preload_info.failed = 0
	preload_info.loader_map = {}
	preload_info.callback = callback
	for file_path, config in ___pairs(csv_map) do
		local loader
		loader = __CPPAPICsvFileLoader()
		loader:SetPath(file_path, false)
		local detail = {}
		detail.loader = loader
		detail.config = config
		preload_info.loader_map[loader:GetID()] = detail
		loader:Start()
		preload_info.total = preload_info.total + 1
	end
	if preload_info.total > preload_info.succeed + preload_info.failed then
		self._preload_map[preload_info] = true
	end
	if callback ~= nil then
		callback(preload_info.total, preload_info.succeed, preload_info.failed)
	end
end

function ALittle.CsvConfigManager:HandleCsvFileLoadSucceed(loader, file)
	local id = loader:GetID()
	for info, value in ___pairs(self._preload_map) do
		local detail = info.loader_map[id]
		if detail ~= nil then
			info.succeed = info.succeed + 1
			if detail.config ~= nil then
				local wrap = __CPPAPICsvFileWrap()
				wrap:SetCsvFile(file)
				detail.config:Init(wrap)
			end
			if info.callback ~= nil then
				info.callback(info.total, info.succeed, info.failed)
			end
			if info.total == info.succeed + info.failed then
				self._preload_map[info] = nil
			end
			return
		end
	end
end

function ALittle.CsvConfigManager:HandleCsvFileLoadFailed(loader)
	ALittle.Error("csv load failed! path:" .. loader:GetPath())
	local id = loader:GetID()
	for info, value in ___pairs(self._preload_map) do
		local detail = info.loader_map[id]
		if detail ~= nil then
			info.failed = info.failed + 1
			if detail.config ~= nil then
				detail.config:Init(nil)
			end
			if info.callback ~= nil then
				info.callback(info.total, info.succeed, info.failed)
			end
			if info.total == info.succeed + info.failed then
				self._preload_map[info] = nil
			end
			return
		end
	end
end

_G.A_CsvConfigManager = ALittle.CsvConfigManager()
end