-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1741432339, "ALittle.LoopListInfo", {
name = "ALittle.LoopListInfo", ns_name = "ALittle", rl_name = "LoopListInfo", hash_code = -1741432339,
name_list = {"link","attribute","init","childs"},
type_list = {"string","string","any","List<ALittle.LoopChildInfo>"},
option_map = {}
})
ALittle.RegStruct(1653869333, "ALittle.LoopGroupInfo", {
name = "ALittle.LoopGroupInfo", ns_name = "ALittle", rl_name = "LoopGroupInfo", hash_code = 1653869333,
name_list = {"childs"},
type_list = {"List<ALittle.LoopListInfo>"},
option_map = {}
})
ALittle.RegStruct(-925381158, "ALittle.LoopChildInfo", {
name = "ALittle.LoopChildInfo", ns_name = "ALittle", rl_name = "LoopChildInfo", hash_code = -925381158,
name_list = {"clazz","target","total_time","delay_time"},
type_list = {"string","any","int","int"},
option_map = {}
})

ALittle.LoopAnimation = Lua.Class(nil, "ALittle.LoopAnimation")

function ALittle.LoopAnimation:Ctor(from, info)
	___rawset(self, "_from", from)
	___rawset(self, "_info", info)
end

function ALittle.LoopAnimation:Init(map)
	self:Stop()
	self._group = ALittle.LoopGroup()
	self._group.complete_callback = Lua.Bind(self.Completed, self)
	self._save_value_map = {}
	self._init_value_map = {}
	for _, list in ___ipairs(self._info.childs) do
		local target
		if map ~= nil then
			target = map[list.link]
		end
		if target == nil and self._from ~= nil then
			target = self._from[list.link]
		end
		if target == nil then
			self._group = nil
			self._save_value_map = nil
			self._init_value_map = nil
			return "can't find link:" .. list.link .. " from map or object"
		end
		local value_map = self._save_value_map[target]
		if value_map == nil then
			value_map = {}
			self._save_value_map[target] = value_map
		end
		value_map[list.attribute] = target[list.attribute]
		if list.init ~= nil then
			target[list.attribute] = list.init
			value_map = self._init_value_map[target]
			if value_map == nil then
				value_map = {}
				self._init_value_map[target] = value_map
			end
			value_map[list.attribute] = list.init
		end
		local loop_list = ALittle.LoopList()
		for index, info in ___ipairs(list.childs) do
			if info.clazz == "LoopLinear" then
				loop_list:AddUpdater(ALittle.LoopLinear(target, list.attribute, info.target, info.total_time, info.delay_time))
			elseif info.clazz == "LoopAttribute" then
				loop_list:AddUpdater(ALittle.LoopAttribute(target, list.attribute, info.target, info.delay_time))
			elseif info.clazz == "LoopRit" then
				loop_list:AddUpdater(ALittle.LoopRit(target, list.attribute, info.target, info.total_time, info.delay_time))
			end
		end
		self._group:AddUpdater(loop_list)
	end
	return nil
end

function ALittle.LoopAnimation:Completed()
	if self._loop == 0 then
		self:ReleaseCo(nil)
		return
	end
	if self._loop > 0 then
		self._loop = self._loop - 1
		if self._loop <= 0 then
			self:ReleaseCo(nil)
			return
		end
	end
	self:SetTime(0)
	self._group:Start()
end

function ALittle.LoopAnimation:Play(loop)
	self:ReleaseCo("Play被调用")
	if self._group == nil then
		return
	end
	if loop == nil then
		self._loop = 1
	elseif loop == 0 then
		self._loop = -1
	else
		self._loop = loop
	end
	self._group:Start()
end

function ALittle.LoopAnimation:AsyncPlay(loop)
	local ___COROUTINE = coroutine.running()
	self:ReleaseCo("AsyncPlay被调用")
	if self._group == nil then
		return "this._group == null"
	end
	if ___COROUTINE == nil then
		return "当前不是协程"
	end
	self._co = ___COROUTINE
	if loop == nil then
		self._loop = 1
	elseif loop == 0 then
		self._loop = -1
	else
		self._loop = loop
	end
	self._group:Start()
	return coroutine.yield()
end

function ALittle.LoopAnimation:ReleaseCo(reason)
	if self._co == nil then
		return
	end
	local result, error = ALittle.Coroutine.Resume(self._co, reason)
	if result ~= true then
		ALittle.Error(error)
	end
	self._co = nil
end

function ALittle.LoopAnimation:Pause()
	if self._group == nil then
		return
	end
	self._group:Stop()
end

function ALittle.LoopAnimation:SetTime(time)
	self:ReleaseCo("SetTime被调用")
	if self._group == nil then
		return
	end
	if self._save_value_map ~= nil then
		for object, value_map in ___pairs(self._save_value_map) do
			for attr, param in ___pairs(value_map) do
				object[attr] = param
			end
		end
	end
	if self._init_value_map ~= nil then
		for object, value_map in ___pairs(self._init_value_map) do
			for attr, param in ___pairs(value_map) do
				object[attr] = param
			end
		end
	end
	self._group:SetTime(time)
end

function ALittle.LoopAnimation:Stop()
	self:ReleaseCo("Stop被调用")
	if self._group ~= nil then
		self._group:Stop()
		self._group = nil
	end
	if self._save_value_map ~= nil then
		for object, value_map in ___pairs(self._save_value_map) do
			for attr, param in ___pairs(value_map) do
				object[attr] = param
			end
		end
		self._save_value_map = nil
	end
	self._init_value_map = nil
end

end