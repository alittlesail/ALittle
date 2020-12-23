-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1755750412, "ALittle.ALittleJsonRPCInfo", {
name = "ALittle.ALittleJsonRPCInfo", ns_name = "ALittle", rl_name = "ALittleJsonRPCInfo", hash_code = 1755750412,
name_list = {"method","param"},
type_list = {"string","any"},
option_map = {}
})
ALittle.RegStruct(1720966934, "ALittle.NewIntentEvent", {
name = "ALittle.NewIntentEvent", ns_name = "ALittle", rl_name = "NewIntentEvent", hash_code = 1720966934,
name_list = {"target","url"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(1452333751, "ALittle.AppLowMemory", {
name = "ALittle.AppLowMemory", ns_name = "ALittle", rl_name = "AppLowMemory", hash_code = 1452333751,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(-1440165311, "ALittle.AppWillEnterBackground", {
name = "ALittle.AppWillEnterBackground", ns_name = "ALittle", rl_name = "AppWillEnterBackground", hash_code = -1440165311,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(-840570937, "ALittle.NotifyJsonRPCEvent", {
name = "ALittle.NotifyJsonRPCEvent", ns_name = "ALittle", rl_name = "NotifyJsonRPCEvent", hash_code = -840570937,
name_list = {"target","method","param"},
type_list = {"ALittle.EventDispatcher","string","any"},
option_map = {}
})
ALittle.RegStruct(812594882, "ALittle.AppWillEnterForeground", {
name = "ALittle.AppWillEnterForeground", ns_name = "ALittle", rl_name = "AppWillEnterForeground", hash_code = 812594882,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(760325696, "ALittle.AppDidEnterForeground", {
name = "ALittle.AppDidEnterForeground", ns_name = "ALittle", rl_name = "AppDidEnterForeground", hash_code = 760325696,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(708183011, "ALittle.NetChangeEvent", {
name = "ALittle.NetChangeEvent", ns_name = "ALittle", rl_name = "NetChangeEvent", hash_code = 708183011,
name_list = {"target","net_type"},
type_list = {"ALittle.EventDispatcher","int"},
option_map = {}
})
ALittle.RegStruct(521107426, "ALittle.AppDidEnterBackground", {
name = "ALittle.AppDidEnterBackground", ns_name = "ALittle", rl_name = "AppDidEnterBackground", hash_code = 521107426,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

assert(ALittle.EventDispatcher, " extends class:ALittle.EventDispatcher is nil")
ALittle.OtherSystem = Lua.Class(ALittle.EventDispatcher, "ALittle.OtherSystem")

function ALittle.OtherSystem:Ctor()
	___rawset(self, "_network_started", false)
	___rawset(self, "_system_select_directory", nil)
	___rawset(self, "_system_select_file", nil)
	___rawset(self, "_system_save_file", nil)
	___rawset(self, "_third_share_callback", nil)
	___rawset(self, "_third_login_callback", nil)
	___rawset(self, "_third_login_ing", false)
end

function ALittle.OtherSystem:HandleWillEnterBackground()
	self:DispatchEvent(___all_struct[-1440165311], {})
end

function ALittle.OtherSystem:HandleDidEnterBackground()
	self:DispatchEvent(___all_struct[521107426], {})
end

function ALittle.OtherSystem:HandleWillEnterForeground()
	self:DispatchEvent(___all_struct[812594882], {})
end

function ALittle.OtherSystem:HandleDidEnterForeground()
	self:DispatchEvent(___all_struct[760325696], {})
end

function ALittle.OtherSystem:HandleLowMemory()
	self:DispatchEvent(___all_struct[1452333751], {})
end

function ALittle.OtherSystem:HandleNewIntent(url)
	local event = {}
	event.url = url
	self:DispatchEvent(___all_struct[1720966934], event)
end

function ALittle.OtherSystem:HandleALittleJsonRPC(json)
	local error, content = Lua.TCall(ALittle.String_JsonDecode, json)
	if error ~= nil then
		ALittle.Log("OtherSystem:HandleALittleJsonRPC:", error, json)
		return
	end
	if content.method == nil then
		return
	end
	if content.param == nil then
		return
	end
	local event = {}
	event.target = self
	event.method = content.method
	event.param = content.param
	self:DispatchEvent(___all_struct[-840570937], event)
end

function ALittle.OtherSystem:SystemSelectDirectory(target, init_dir)
	self._system_select_directory = target
	__CPPAPI_System:SystemSelectDirectory(init_dir)
end

function ALittle.OtherSystem:HandleSystemSelectDirectory(path)
	if self._system_select_directory == nil then
		return
	end
	local tmp = self._system_select_directory
	self._system_select_directory = nil
	local event = {}
	event.target = tmp
	event.path = path
	tmp:DispatchEvent(___all_struct[1800966813], event)
end

function ALittle.OtherSystem:SystemSelectFile(target, init_dir)
	self._system_select_file = target
	__CPPAPI_System:SystemSelectFile(init_dir)
end

function ALittle.OtherSystem:HandleSystemSelectFile(path)
	if self._system_select_file == nil then
		return
	end
	local tmp = self._system_select_file
	self._system_select_file = nil
	local event = {}
	event.target = tmp
	event.path = path
	tmp:DispatchEvent(___all_struct[124598654], event)
end

function ALittle.OtherSystem:SystemSaveFile(target, file_name, path)
	self._system_save_file = target
	__CPPAPI_System:SystemSaveFile(file_name, path)
end

function ALittle.OtherSystem:HandleSystemSaveFile(path)
	if self._system_save_file == nil then
		return
	end
	local tmp = self._system_save_file
	self._system_save_file = nil
	local event = {}
	event.target = tmp
	event.path = path
	tmp:DispatchEvent(___all_struct[-1676610185], event)
end

_G.A_OtherSystem = ALittle.OtherSystem()
end