-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(244548997, "ALittle.FullData", {
name = "ALittle.FullData", ns_name = "ALittle", rl_name = "FullData", hash_code = 244548997,
name_list = {"id"},
type_list = {"int"},
option_map = {primary="id"}
})

ALittle.FullDataSet = Lua.Class(nil, "ALittle.FullDataSet")

function ALittle.FullDataSet:Ctor(submit_interval_ms)
	___rawset(self, "_submit_interval_ms", submit_interval_ms)
	___rawset(self, "_data_map", {})
	___rawset(self, "_loading_map", {})
	___rawset(self, "_dirty_map", {})
end

function ALittle.FullDataSet:Init()
	local ___COROUTINE = coroutine.running()
	local rflt = self.__class.__element[1]
	self._primary = rflt.option_map["primary"]
	if self._primary == nil then
		return rflt.name .. "没有定义主键"
	end
	local error = A_MysqlSystem:CreateIfNotExit(self.__class.__element[1])
	if error ~= nil then
		return error
	end
	local select_list
	error, select_list = A_MysqlSystem:SelectListFromByMap(self.__class.__element[1], nil)
	if error ~= nil then
		return error
	end
	if select_list ~= nil then
		for index, data in ___ipairs(select_list) do
			self._data_map[data.id] = data
		end
	end
	if self._submit_timer ~= nil then
		A_LoopSystem:RemoveTimer(self._submit_timer)
	end
	self._submit_timer = A_LoopSystem:AddTimer(self._submit_interval_ms, Lua.Bind(self.Submit, self, true))
	return nil
end

function ALittle.FullDataSet:Release()
	if self._submit_timer ~= nil then
		A_LoopSystem:RemoveTimer(self._submit_timer)
		self._submit_timer = nil
	end
	self:Submit(false)
	self._data_map = {}
	self._loading_map = {}
	self._dirty_map = {}
	self._release = true
	local rflt = self.__class.__element[1]
	ALittle.Log(rflt.name .. "操作完毕")
end

function ALittle.FullDataSet:Submit(loop)
	self._submit_timer = nil
	local data_map = self._data_map
	local dirty_map = self._dirty_map
	for id, _ in ___pairs(dirty_map) do
		local data = data_map[id]
		if data ~= nil then
			local error = A_MysqlSystem:UpdateOne(self.__class.__element[1], data, self._primary, data.id, data.id)
			if error ~= nil then
				ALittle.Error(error)
			end
		end
	end
	self._dirty_map = {}
	if loop then
		self._submit_timer = A_LoopSystem:AddTimer(self._submit_interval_ms, Lua.Bind(self.Submit, self, true))
	end
end
ALittle.FullDataSet.Submit = Lua.CoWrap(ALittle.FullDataSet.Submit)

function ALittle.FullDataSet:GetDataAndDirty(id)
	local ___COROUTINE = coroutine.running()
	local data = self:GetData(id)
	if data ~= nil then
		self._dirty_map[id] = true
	end
	return data
end

function ALittle.FullDataSet:GetData(id)
	local ___COROUTINE = coroutine.running()
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
		ALittle.Error(error)
	end
	if self._release then
		return nil
	end
	self._loading_map[id] = nil
	if new_data == nil then
		return nil
	end
	self._data_map[id] = new_data
	return data
end

function ALittle.FullDataSet:CreateData(data)
	local ___COROUTINE = coroutine.running()
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
	local error = A_MysqlSystem:InsertInto(self.__class.__element[1], data, nil, data.id)
	if error ~= nil then
		ALittle.Error(error)
	end
	return nil
end

function ALittle.FullDataSet:DeleteData(id)
	local ___COROUTINE = coroutine.running()
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
	self._data_map[id] = nil
	local error = A_MysqlSystem:DeleteFromByKey(self.__class.__element[1], self._primary, id, id)
	if error ~= nil then
		ALittle.Error(error)
	end
	return nil
end

end