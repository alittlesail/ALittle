
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

RegStruct(-1164907202, "ALittle.CacheData", {
name = "ALittle.CacheData", ns_name = "ALittle", rl_name = "CacheData", hash_code = -1164907202,
name_list = {"id"},
type_list = {"int"},
option_map = {primary="id"}
})

CacheDataSet = Class(nil, "ALittle.CacheDataSet")

function CacheDataSet:Ctor(submit_interval_ms, cache_interval_ms)
	___rawset(self, "_submit_interval_ms", submit_interval_ms)
	___rawset(self, "_cache_interval_ms", cache_interval_ms)
	___rawset(self, "_data_map", {})
	___rawset(self, "_loading_map", {})
	___rawset(self, "_timer_map", {})
	___rawset(self, "_dirty_map", {})
end

function CacheDataSet:Init()
	local rflt = self.__class.__element[1]
	self._primary = rflt.option_map["primary"]
	if self._primary == nil then
		return rflt.name .. "没有定义主键"
	end
	local error = A_MysqlSystem:CreateIfNotExit(self.__class.__element[1])
	if error ~= nil then
		return error
	end
	if self._submit_timer ~= nil then
		A_LoopSystem:RemoveTimer(self._submit_timer)
	end
	self._submit_timer = A_LoopSystem:AddTimer(self._submit_interval_ms, Bind(self.Submit, self, true))
	return nil
end

function CacheDataSet:Release()
	if self._submit_timer ~= nil then
		A_LoopSystem:RemoveTimer(self._submit_timer)
		self._submit_timer = nil
	end
	self:Submit(false)
	self._data_map = {}
	self._loading_map = {}
	for id, timer in ___pairs(self._timer_map) do
		A_LoopSystem:RemoveTimer(timer)
	end
	self._timer_map = {}
	self._dirty_map = {}
	self._release = true
	local rflt = self.__class.__element[1]
	Log(rflt.name .. "操作完毕")
end

function CacheDataSet:Submit(loop)
	self._submit_timer = nil
	local data_map = self._data_map
	local dirty_map = self._dirty_map
	for id, _ in ___pairs(dirty_map) do
		local data = data_map[id]
		if data ~= nil then
			local error = A_MysqlSystem:UpdateOne(self.__class.__element[1], data, self._primary, data.id, data.id)
			if error ~= nil then
				Error(error)
			end
		end
	end
	self._dirty_map = {}
	if loop then
		self._submit_timer = A_LoopSystem:AddTimer(self._submit_interval_ms, Bind(self.Submit, self, true))
	end
end
CacheDataSet.Submit = CoWrap(CacheDataSet.Submit)

function CacheDataSet:GetDataAndDirty(id)
	local data = self:GetData(id)
	if data ~= nil then
		self._dirty_map[id] = true
	end
	return data
end

function CacheDataSet:GetData(id)
	if self._release then
		return nil
	end
	local data = self._data_map[id]
	if data ~= nil then
		return data
	end
	if self._loading_map[id] then
		A_MysqlSystem:ExecuteEmpty(id)
		if self._release then
			return nil
		end
		return self._data_map[id]
	end
	self._loading_map[id] = true
	local error, new_data = A_MysqlSystem:SelectOneFromByKey(self.__class.__element[1], self._primary, id, id)
	if error ~= nil then
		Error(error)
	end
	if self._release then
		return nil
	end
	self._loading_map[id] = nil
	if new_data == nil then
		return nil
	end
	self._data_map[id] = new_data
	if self._timer_map[id] ~= nil then
		A_LoopSystem:RemoveTimer(self._timer_map[id])
	end
	self._timer_map[id] = A_LoopSystem:AddTimer(self._cache_interval_ms, Bind(self.RemoveCache, self, id))
	return new_data
end

function CacheDataSet:RemoveCache(id)
	if self._release then
		return
	end
	self._timer_map[id] = nil
	local data = self._data_map[id]
	if data == nil then
		return
	end
	self._data_map[id] = nil
	if self._dirty_map[id] then
		self._dirty_map[data.id] = nil
		self:SubmitData(data)
	end
end

function CacheDataSet:SubmitData(data)
	local error = A_MysqlSystem:UpdateOne(self.__class.__element[1], data, self._primary, data.id, data.id)
	if error ~= nil then
		Error(error)
	end
end
CacheDataSet.SubmitData = CoWrap(CacheDataSet.SubmitData)

function CacheDataSet:CreateData(data)
	if self._release then
		return "数据集已经被释放"
	end
	if self._loading_map[data.id] then
		A_MysqlSystem:ExecuteEmpty(data.id)
		if self._release then
			return "数据集已经被释放"
		end
	end
	if self._data_map[data.id] ~= nil then
		return "数据已存在"
	end
	self._data_map[data.id] = data
	if self._timer_map[data.id] ~= nil then
		A_LoopSystem:RemoveTimer(self._timer_map[data.id])
	end
	self._timer_map[data.id] = A_LoopSystem:AddTimer(self._cache_interval_ms, Bind(self.RemoveCache, self, data.id))
	local error = A_MysqlSystem:InsertInto(self.__class.__element[1], data, nil, data.id)
	if error ~= nil then
		Error(error)
	end
	return nil
end

function CacheDataSet:DeleteData(id)
	if self._release then
		return "数据集已经被释放"
	end
	if self._loading_map[id] then
		A_MysqlSystem:ExecuteEmpty(id)
		if self._release then
			return "数据集已经被释放"
		end
	end
	self._dirty_map[id] = nil
	local timer = self._timer_map[id]
	if timer ~= nil then
		A_LoopSystem:RemoveTimer(timer)
		self._timer_map[id] = nil
	end
	self._data_map[id] = nil
	local error = A_MysqlSystem:DeleteFromByKey(self.__class.__element[1], self._primary, id, id)
	if error ~= nil then
		Error(error)
	end
	return nil
end
