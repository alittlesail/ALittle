-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1358089220, "ALittle.MysqlExecuteInfo", {
name = "ALittle.MysqlExecuteInfo", ns_name = "ALittle", rl_name = "MysqlExecuteInfo", hash_code = 1358089220,
name_list = {"thread","query"},
type_list = {"ALittle.Thread","ALittle.MysqlStatementQuery"},
option_map = {}
})
ALittle.RegStruct(-930447138, "ALittle.Thread", {
name = "ALittle.Thread", ns_name = "ALittle", rl_name = "Thread", hash_code = -930447138,
name_list = {},
type_list = {},
option_map = {}
})

ALittle.MysqlStatementQuery = Lua.Class(nil, "ALittle.MysqlStatementQuery")

function ALittle.MysqlStatementQuery:Ctor()
	___rawset(self, "_query", __CPPAPIMysqlStatementQuery())
end

function ALittle.MysqlStatementQuery.__setter:sql(value)
	if value == nil then
		value = ""
	end
	self._query:SetSQL(value)
end

function ALittle.MysqlStatementQuery.__getter:sql()
	return self._query:GetSQL()
end

function ALittle.MysqlStatementQuery.__getter:count()
	return self._query:GetCount()
end

function ALittle.MysqlStatementQuery.__getter:affect_count()
	return self._query:GetAffectCount()
end

function ALittle.MysqlStatementQuery:Execute(thread_id)
	local ___COROUTINE = coroutine.running()
	return A_MysqlSystem:ExecuteStatement(self, thread_id)
end

function ALittle.MysqlStatementQuery.__getter:String()
	return self._query:ReadString()
end

function ALittle.MysqlStatementQuery.__setter:String(value)
	if value == nil then
		self._query:PushString("")
	else
		self._query:PushString(value)
	end
end

function ALittle.MysqlStatementQuery.__getter:Int()
	return self._query:ReadInt()
end

function ALittle.MysqlStatementQuery.__setter:Int(value)
	if value == nil then
		self._query:PushInt(0)
	else
		self._query:PushInt(value)
	end
end

function ALittle.MysqlStatementQuery.__getter:Long()
	return self._query:ReadI64()
end

function ALittle.MysqlStatementQuery.__setter:Long(value)
	if value == nil then
		self._query:PushI64(0)
	else
		self._query:PushI64(value)
	end
end

function ALittle.MysqlStatementQuery.__getter:Double()
	return self._query:ReadDouble()
end

function ALittle.MysqlStatementQuery.__setter:Double(value)
	if value == nil then
		self._query:PushDouble(0)
	else
		self._query:PushDouble(value)
	end
end

function ALittle.MysqlStatementQuery.__getter:value()
	local type_int = self._query:ReadType()
	if type_int == -1 then
		return nil
	end
	if type_int == 0 then
		return self._query:ReadBool()
	end
	if type_int == 1 then
		return self._query:ReadShort()
	end
	if type_int == 2 then
		return self._query:ReadInt()
	end
	if type_int == 3 then
		return self._query:ReadI64()
	end
	if type_int == 4 then
		return self._query:ReadFloat()
	end
	if type_int == 5 then
		return self._query:ReadDouble()
	end
	if type_int == 6 then
		return self._query:ReadString()
	end
	return nil
end

function ALittle.MysqlStatementQuery.__setter:value(v)
	local type_str = type(v)
	if type_str == "number" then
		if math.floor(v) < v then
			self._query:PushDouble(v)
		else
			self._query:PushInt(v)
		end
	elseif type_str == "string" then
		self._query:PushString(v)
	elseif type_str == "boolean" then
		if v == false then
			self._query:PushInt(0)
		else
			self._query:PushInt(1)
		end
	elseif type_str == "table" then
		self._query:PushString(ajson.encode(v))
	else
		self._query:PushString(tostring(v))
	end
end

function ALittle.MysqlStatementQuery:SelectPageBegin(field, condition, table_name, key, asc)
	local asc_str = " DESC"
	if not asc then
		asc_str = " ASC"
	end
	local sql = nil
	local cross = ALittle.String_Find(table_name, ",")
	if cross ~= nil then
		local field_list = ALittle.String_Split(table_name, ",")
		local as_name_list = {}
		local field_name_list = {}
		for k, v in ___ipairs(field_list) do
			local as_name = "tt" .. k
			ALittle.List_Push(as_name_list, as_name)
			ALittle.List_Push(field_name_list, v .. " as " .. as_name)
		end
		field = ALittle.String_Join(field_name_list, ",")
		local as_field = ALittle.String_Join(as_name_list, ",")
		if condition == nil then
			condition = ""
		end
		if key ~= nil then
			key = "ORDER BY " .. key .. asc_str
		else
			key = ""
		end
		sql = "SELECT " .. as_field .. " FROM ( SELECT @rownum:=@rownum+1 AS RowNumber, " .. field .. " FROM " .. table_name .. ", (SELECT @rownum:=0) __rownumb " .. condition .. " " .. key .. " ) AS temp WHERE temp.RowNumber BETWEEN ? AND ?"
	else
		if condition == nil then
			condition = ""
		end
		if key ~= nil then
			key = "ORDER BY " .. key .. asc_str
		else
			key = ""
		end
		sql = "SELECT " .. field .. " FROM (  SELECT @rownum:=@rownum+1 AS RowNumber, " .. field .. " FROM " .. table_name .. ", (SELECT @rownum:=0) __rownumb " .. condition .. " " .. key .. " ) AS temp WHERE temp.RowNumber BETWEEN ? AND ?"
	end
	self._query:SetSQL(sql)
end

function ALittle.MysqlStatementQuery:SelectPageEnd(page_size, page_index)
	local start_index = (page_index - 1) * page_size + 1
	if start_index < 1 then
		start_index = 1
	end
	local end_index = page_index * page_size
	self.Int = start_index
	self.Int = end_index
end

function ALittle.MysqlStatementQuery:HasNext()
	return self._query:HasNext()
end

local __TypeMap = {}
__TypeMap["bool"] = 1
__TypeMap["int"] = 2
__TypeMap["long"] = 3
__TypeMap["double"] = 4
__TypeMap["string"] = 5
ALittle.MysqlSystem = Lua.Class(nil, "ALittle.MysqlSystem")

function ALittle.MysqlSystem:Ctor()
	___rawset(self, "_id_creator", ALittle.SafeIDCreator())
	___rawset(self, "_info_map", {})
	___rawset(self, "_execute_empty_map", {})
end

function ALittle.MysqlSystem:HandleMysqlQueryTask(id, reason)
	local info = self._info_map[id]
	if info == nil then
		return
	end
	self._id_creator:ReleaseID(id)
	self._info_map[id] = nil
	local result, error = coroutine.resume(info.thread, reason)
	if result ~= true then
		ALittle.Error(error)
	end
end

function ALittle.MysqlSystem:HandleMysqlEmptyTask(id, reason)
	local thread = self._execute_empty_map[id]
	if thread == nil then
		return
	end
	self._id_creator:ReleaseID(id)
	self._execute_empty_map[id] = nil
	local result, error = coroutine.resume(thread, reason)
	if result ~= true then
		ALittle.Error(error)
	end
end

function ALittle.MysqlSystem:ExecuteStatement(query, thread_id)
	local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程"
	end
	if thread_id == nil then
		thread_id = 0
	end
	local id = self._id_creator:CreateID()
	if not __CPPAPI_ServerSchedule:AddMysqlStatement(thread_id, id, query._query) then
		self._id_creator:ReleaseID(id)
		return "任务添加失败"
	end
	local info = {}
	info.thread = ___COROUTINE
	info.query = query
	self._info_map[id] = info
	return coroutine.yield()
end

function ALittle.MysqlSystem:ExecuteNormal(sql, thread_id)
	local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程"
	end
	if thread_id == nil then
		thread_id = 0
	end
	local id = self._id_creator:CreateID()
	if not __CPPAPI_ServerSchedule:AddMysqlNormal(thread_id, id, sql) then
		self._id_creator:ReleaseID(id)
		return "任务添加失败"
	end
	local info = {}
	info.thread = ___COROUTINE
	self._info_map[id] = info
	return coroutine.yield()
end

function ALittle.MysqlSystem:ExecuteEmpty(thread_id)
	local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程"
	end
	if thread_id == nil then
		thread_id = 0
	end
	local id = self._id_creator:CreateID()
	if not __CPPAPI_ServerSchedule:AddMysqlEmpty(thread_id, id) then
		self._id_creator:ReleaseID(id)
		return "任务添加失败"
	end
	self._execute_empty_map[id] = ___COROUTINE
	return coroutine.yield()
end

function ALittle.MysqlSystem:SelectCountByReflect(info, key, value, thread_id)
	local ___COROUTINE = coroutine.running()
	if value == nil then
		return "value == null", 0
	end
	local sql = "SELECT COUNT(*) FROM `"
	sql = sql .. info.rl_name
	sql = sql .. "` WHERE `"
	sql = sql .. key
	sql = sql .. "`=?"
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	query.value = value
	local error = self:ExecuteStatement(query, thread_id)
	if error ~= nil then
		return error, 0
	end
	return nil, query.Long
end

function ALittle.MysqlSystem:SelectCount(T, key, value, thread_id)
	local ___COROUTINE = coroutine.running()
	return self:SelectCountByReflect(T, key, value, thread_id)
end

function ALittle.MysqlSystem:SelectOneFromByKeyByReflect(info, key, value, thread_id)
	local ___COROUTINE = coroutine.running()
	if value == nil then
		return "value == null", nil
	end
	local sql = "SELECT "
	local field_list = {}
	for i, name in ___ipairs(info.name_list) do
		ALittle.List_Push(field_list, "`" .. name .. "`")
	end
	sql = sql .. ALittle.String_Join(field_list, ",")
	sql = sql .. " FROM `"
	sql = sql .. info.rl_name
	sql = sql .. "` WHERE `"
	sql = sql .. key
	sql = sql .. "`=?"
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	query.value = value
	local error = self:ExecuteStatement(query, thread_id)
	if error ~= nil then
		return error, nil
	end
	if query.count == 0 then
		return nil, nil
	end
	local map = {}
	for i, name in ___ipairs(info.name_list) do
		local type = __TypeMap[info.type_list[i]]
		if type == 1 then
			map[name] = query.Int ~= 0
		elseif type == 2 then
			map[name] = query.Int
		elseif type == 3 then
			map[name] = query.Long
		elseif type == 4 then
			map[name] = query.Double
		elseif type == 5 then
			map[name] = query.String
		else
			local str = query.String
			if str == "" then
				map[name] = {}
			else
				local content = nil
				error, content = Lua.TCall(ajson.decode, str)
				if error ~= nil then
					return error, nil
				else
					map[name] = content
				end
			end
		end
	end
	return nil, map
end

function ALittle.MysqlSystem:SelectOneFromByKey(T, key, value, thread_id)
	local ___COROUTINE = coroutine.running()
	return self:SelectOneFromByKeyByReflect(T, key, value, thread_id)
end

function ALittle.MysqlSystem:SelectListFromByMapByReflect(info, value_map, thread_id)
	local ___COROUTINE = coroutine.running()
	local sql = "SELECT "
	local field_list = {}
	for i, name in ___ipairs(info.name_list) do
		ALittle.List_Push(field_list, "`" .. name .. "`")
	end
	sql = sql .. ALittle.String_Join(field_list, ",")
	sql = sql .. " FROM `"
	sql = sql .. info.rl_name
	sql = sql .. "`"
	local value_list = {}
	if value_map ~= nil then
		local condition = ""
		local where_list = {}
		local index = 1
		for key, value in ___pairs(value_map) do
			where_list[index] = "`" .. key .. "`=?"
			value_list[index] = value
		end
		condition = ALittle.String_Join(where_list, " AND ")
		if condition ~= "" then
			condition = " WHERE " .. condition
		end
		sql = sql .. condition
	end
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	for index, value in ___ipairs(value_list) do
		query.value = value
	end
	local error = self:ExecuteStatement(query, thread_id)
	if error ~= nil then
		return error, nil
	end
	local query_count = query.count
	if query_count == 0 then
		return nil, {}
	end
	local list = {}
	local row = 1
	while true do
		if not(row <= query_count) then break end
		local map = {}
		for i, name in ___ipairs(info.name_list) do
			local type = __TypeMap[info.type_list[i]]
			if type == 1 then
				map[name] = query.Int ~= 0
			elseif type == 2 then
				map[name] = query.Int
			elseif type == 3 then
				map[name] = query.Long
			elseif type == 4 then
				map[name] = query.Double
			elseif type == 5 then
				map[name] = query.String
			else
				local value = query.String
				if value == "" then
					map[name] = {}
				else
					local content = nil
					error, content = Lua.TCall(ajson.decode, value)
					if error ~= nil then
						return error, nil
					else
						map[name] = content
					end
				end
			end
		end
		list[row] = map
		row = row+(1)
	end
	return nil, list
end

function ALittle.MysqlSystem:SelectListFromByMap(T, value_map, thread_id)
	local ___COROUTINE = coroutine.running()
	return self:SelectListFromByMapByReflect(T, value_map, thread_id)
end

function ALittle.MysqlSystem:InsertIntoByReflect(info, map, table_name, thread_id)
	local ___COROUTINE = coroutine.running()
	local sql = "INSERT INTO `"
	if table_name == nil then
		sql = sql .. info.rl_name
	else
		sql = sql .. table_name
	end
	sql = sql .. "` ("
	local field_list = {}
	for i, name in ___ipairs(info.name_list) do
		ALittle.List_Push(field_list, "`" .. name .. "`")
	end
	sql = sql .. ALittle.String_Join(field_list, ",")
	sql = sql .. ") VALUES ("
	local value_list = {}
	for i, name in ___ipairs(info.name_list) do
		ALittle.List_Push(value_list, "?")
	end
	sql = sql .. ALittle.String_Join(value_list, ",")
	sql = sql .. ")"
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	for i, name in ___ipairs(info.name_list) do
		local type = __TypeMap[info.type_list[i]]
		local value = map[name]
		if type == 1 then
			if value ~= true then
				query.Int = 0
			else
				query.Int = 1
			end
		elseif type == 2 then
			if value ~= nil then
				query.Int = tonumber(value)
			else
				query.Int = 0
			end
		elseif type == 3 then
			if value ~= nil then
				query.Long = tonumber(value)
			else
				query.Long = 0
			end
		elseif type == 4 then
			if value ~= nil then
				query.Double = tonumber(value)
			else
				query.Double = 0
			end
		elseif type == 5 then
			if value ~= nil then
				query.String = tostring(value)
			else
				query.String = ""
			end
		else
			if value ~= nil then
				query.String = ajson.encode(value)
			else
				query.String = ""
			end
		end
	end
	return self:ExecuteStatement(query, thread_id)
end

function ALittle.MysqlSystem:InsertInto(T, value, table_name, thread_id)
	local ___COROUTINE = coroutine.running()
	return self:InsertIntoByReflect(T, value, table_name, thread_id)
end

function ALittle.MysqlSystem:UpdateOneByReflect(info, map, key, key_value, thread_id)
	local ___COROUTINE = coroutine.running()
	if key_value == nil then
		return "key_value == null"
	end
	local sql = "UPDATE `"
	sql = sql .. info.rl_name
	sql = sql .. "` SET "
	local set_list = {}
	for i, name in ___ipairs(info.name_list) do
		if key ~= name then
			ALittle.List_Push(set_list, "`" .. name .. "`=?")
		end
	end
	sql = sql .. ALittle.String_Join(set_list, ",")
	sql = sql .. " WHERE `"
	sql = sql .. key
	sql = sql .. "`=?"
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	for i, name in ___ipairs(info.name_list) do
		if key ~= name then
			local type = __TypeMap[info.type_list[i]]
			local value = map[name]
			if type == 1 then
				if value ~= true then
					query.Int = 0
				else
					query.Int = 1
				end
			elseif type == 2 then
				if value ~= nil then
					query.Int = tonumber(value)
				else
					query.Int = 0
				end
			elseif type == 3 then
				if value ~= nil then
					query.Long = tonumber(value)
				else
					query.Long = 0
				end
			elseif type == 4 then
				if value ~= nil then
					query.Double = tonumber(value)
				else
					query.Double = 0
				end
			elseif type == 5 then
				if value ~= nil then
					query.String = tostring(value)
				else
					query.String = ""
				end
			else
				if value ~= nil then
					query.String = ajson.encode(value)
				else
					query.String = ""
				end
			end
		end
	end
	query.value = key_value
	return self:ExecuteStatement(query, thread_id)
end

function ALittle.MysqlSystem:UpdateOne(T, value, key, key_value, thread_id)
	local ___COROUTINE = coroutine.running()
	return self:UpdateOneByReflect(T, value, key, key_value, thread_id)
end

function ALittle.MysqlSystem:UpdateSetByReflect(info, field, field_value, key, key_value, thread_id)
	local ___COROUTINE = coroutine.running()
	if field_value == nil then
		return "field_value == null"
	end
	if key_value == nil then
		return "key_value == null"
	end
	local sql = "UPDATE `"
	sql = sql .. info.rl_name
	sql = sql .. "` SET `"
	sql = sql .. field
	sql = sql .. "`=?"
	sql = sql .. " WHERE `"
	sql = sql .. key
	sql = sql .. "`=?"
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	query.value = field_value
	query.value = key_value
	return self:ExecuteStatement(query, thread_id)
end

function ALittle.MysqlSystem:UpdateSet(T, field, field_value, key, key_value, thread_id)
	local ___COROUTINE = coroutine.running()
	return self:UpdateSetByReflect(T, field, field_value, key, key_value, thread_id)
end

function ALittle.MysqlSystem:DeleteFromByMapByReflect(info, value_map, thread_id)
	local ___COROUTINE = coroutine.running()
	local sql = "DELETE FROM `"
	sql = sql .. info.rl_name
	sql = sql .. "`"
	local condition = ""
	local value_list = {}
	if value_map ~= nil then
		local where_list = {}
		local index = 1
		for key, value in ___pairs(value_map) do
			where_list[index] = "`" .. key .. "`=?"
			value_list[index] = value
		end
		condition = ALittle.String_Join(where_list, " AND ")
		if condition ~= "" then
			condition = " WHERE " .. condition
		end
	end
	sql = sql .. condition
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	for index, value in ___ipairs(value_list) do
		query.value = value
	end
	return self:ExecuteStatement(query, thread_id)
end

function ALittle.MysqlSystem:DeleteFromByMap(T, value_map, thread_id)
	local ___COROUTINE = coroutine.running()
	return self:DeleteFromByMapByReflect(T, value_map, thread_id)
end

function ALittle.MysqlSystem:DeleteFromByKeyByReflect(info, key, value, thread_id)
	local ___COROUTINE = coroutine.running()
	local sql = "DELETE FROM `"
	sql = sql .. info.rl_name
	sql = sql .. "` WHERE `"
	sql = sql .. key
	sql = sql .. "`=?"
	local query = ALittle.MysqlStatementQuery()
	query.sql = sql
	query.value = value
	return self:ExecuteStatement(query, thread_id)
end

function ALittle.MysqlSystem:DeleteFromByKey(T, key, value, thread_id)
	local ___COROUTINE = coroutine.running()
	return self:DeleteFromByKeyByReflect(T, key, value, thread_id)
end

function ALittle.MysqlSystem:CreateIfNotExitByReflect(info, table_name, thread_id)
	local ___COROUTINE = coroutine.running()
	local name_map = {}
	for index, name in ___ipairs(info.name_list) do
		name_map[name] = true
	end
	local primary = info.option_map["primary"]
	if primary ~= nil and name_map[primary] == nil then
		primary = ALittle.String_Trim(primary)
		if name_map[primary] == nil then
			return "指定的主键" .. primary .. "不是字段"
		end
	end
	local unique_map = {}
	local unique = info.option_map["unique"]
	if unique ~= nil then
		local list = ALittle.String_Split(unique, ",")
		for index, value in ___ipairs(list) do
			value = ALittle.String_Trim(value)
			unique_map[value] = true
			if name_map[value] == nil then
				return "指定的唯一索引" .. value .. "不是字段"
			end
		end
	end
	local index_map = {}
	local index = info.option_map["index"]
	if index ~= nil then
		local list = ALittle.String_Split(index, ",")
		for i, value in ___ipairs(list) do
			value = ALittle.String_Trim(value)
			index_map[value] = true
			if name_map[value] == nil then
				return "指定的索引" .. value .. "不是字段"
			end
		end
	end
	local sql = "CREATE TABLE IF NOT EXISTS `"
	if table_name == nil then
		sql = sql .. info.rl_name
	else
		sql = sql .. table_name
	end
	sql = sql .. "` ("
	local sql_list = {}
	for i, name in ___ipairs(info.name_list) do
		local type = __TypeMap[info.type_list[i]]
		if type == 1 then
			ALittle.List_Push(sql_list, "`" .. name .. "` tinyint(4) NOT NULL DEFAULT 0")
		elseif type == 2 then
			ALittle.List_Push(sql_list, "`" .. name .. "` int(11) NOT NULL DEFAULT 0")
		elseif type == 3 then
			ALittle.List_Push(sql_list, "`" .. name .. "` bigint(20) NOT NULL DEFAULT 0")
		elseif type == 4 then
			ALittle.List_Push(sql_list, "`" .. name .. "` double NOT NULL DEFAULT 0")
		elseif type == 5 then
			ALittle.List_Push(sql_list, "`" .. name .. "` varchar(250) NOT NULL DEFAULT ''")
		else
			ALittle.List_Push(sql_list, "`" .. name .. "` text")
		end
	end
	sql = sql .. ALittle.String_Join(sql_list, ",")
	if primary ~= nil then
		sql = sql .. ", PRIMARY KEY (`" .. primary .. "`)"
	end
	for name, _ in ___pairs(unique_map) do
		sql = sql .. ", UNIQUE KEY `" .. name .. "` (`" .. name .. "`)"
	end
	for name, _ in ___pairs(index_map) do
		sql = sql .. ", KEY `" .. name .. "` (`" .. name .. "`)"
	end
	sql = sql .. ") DEFAULT CHARSET=utf8mb4"
	return self:ExecuteNormal(sql, thread_id)
end

function ALittle.MysqlSystem:CreateIfNotExit(T, table_name, thread_id)
	local ___COROUTINE = coroutine.running()
	return self:CreateIfNotExitByReflect(T, table_name, thread_id)
end

_G.A_MysqlSystem = ALittle.MysqlSystem()
end