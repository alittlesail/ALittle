-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = GetAllStruct()

RegStruct(-840570937, "ALittle.NotifyJsonRPCEvent", {
name = "ALittle.NotifyJsonRPCEvent", ns_name = "ALittle", rl_name = "NotifyJsonRPCEvent", hash_code = -840570937,
name_list = {"target","method","param"},
type_list = {"ALittle.EventDispatcher","string","any"},
option_map = {}
})
RegStruct(521107426, "ALittle.AppDidEnterBackground", {
name = "ALittle.AppDidEnterBackground", ns_name = "ALittle", rl_name = "AppDidEnterBackground", hash_code = 521107426,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
RegStruct(708183011, "ALittle.NetChangeEvent", {
name = "ALittle.NetChangeEvent", ns_name = "ALittle", rl_name = "NetChangeEvent", hash_code = 708183011,
name_list = {"target","net_type"},
type_list = {"ALittle.EventDispatcher","int"},
option_map = {}
})
RegStruct(760325696, "ALittle.AppDidEnterForeground", {
name = "ALittle.AppDidEnterForeground", ns_name = "ALittle", rl_name = "AppDidEnterForeground", hash_code = 760325696,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
RegStruct(812594882, "ALittle.AppWillEnterForeground", {
name = "ALittle.AppWillEnterForeground", ns_name = "ALittle", rl_name = "AppWillEnterForeground", hash_code = 812594882,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
RegStruct(1452333751, "ALittle.AppLowMemory", {
name = "ALittle.AppLowMemory", ns_name = "ALittle", rl_name = "AppLowMemory", hash_code = 1452333751,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
RegStruct(1720966934, "ALittle.NewIntentEvent", {
name = "ALittle.NewIntentEvent", ns_name = "ALittle", rl_name = "NewIntentEvent", hash_code = 1720966934,
name_list = {"target","url"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
RegStruct(1755750412, "ALittle.ALittleJsonRPCInfo", {
name = "ALittle.ALittleJsonRPCInfo", ns_name = "ALittle", rl_name = "ALittleJsonRPCInfo", hash_code = 1755750412,
name_list = {"method","param"},
type_list = {"string","any"},
option_map = {}
})
RegStruct(-1440165311, "ALittle.AppWillEnterBackground", {
name = "ALittle.AppWillEnterBackground", ns_name = "ALittle", rl_name = "AppWillEnterBackground", hash_code = -1440165311,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

NetworkType = {
	NONE = "OtherSystem_NotifyNetwork_none",
	WIFI = "OtherSystem_NotifyNetwork_wifi",
	LINE = "OtherSystem_NotifyNetwork_line",
}

assert(ALittle.EventDispatcher, " extends class:ALittle.EventDispatcher is nil")
OtherSystem = Lua.Class(ALittle.EventDispatcher, "ALittle.OtherSystem")

function OtherSystem:Ctor()
	___rawset(self, "_network_started", false)
	___rawset(self, "_system_select_directory", nil)
	___rawset(self, "_system_select_file", nil)
	___rawset(self, "_system_save_file", nil)
	___rawset(self, "_third_share_callback", nil)
	___rawset(self, "_third_login_callback", nil)
	___rawset(self, "_third_login_ing", false)
end

function OtherSystem:HandleWillEnterBackground()
	self:DispatchEvent(___all_struct[-1440165311], {})
end

function OtherSystem:HandleDidEnterBackground()
	self:DispatchEvent(___all_struct[521107426], {})
end

function OtherSystem:HandleWillEnterForeground()
	self:DispatchEvent(___all_struct[812594882], {})
end

function OtherSystem:HandleDidEnterForeground()
	self:DispatchEvent(___all_struct[760325696], {})
end

function OtherSystem:HandleLowMemory()
	self:DispatchEvent(___all_struct[1452333751], {})
end

function OtherSystem:HandleNewIntent(url)
	local event = {}
	event.url = url
	self:DispatchEvent(___all_struct[1720966934], event)
end

function OtherSystem:AddEventListener(T, object, callback)
	do
		local rflt = T
		local net_rflt = ___all_struct[708183011]
		if rflt.hash_code == net_rflt.hash_code then
			if self._network_started == false then
				__CPPAPI_StartNetworkListener()
				self._network_started = true
			end
		end
	end
	return EventDispatcher.AddEventListener(self, T, object, callback)
end

function OtherSystem:HandleNetworkChanged(net_type)
	local event = {}
	event.net_type = net_type
	self:DispatchEvent(___all_struct[708183011], event)
end

function OtherSystem:GetNetworkType()
	return __CPPAPI_GetNetworkType()
end

function OtherSystem:HandleALittleJsonRPC(json)
	local error, content = Lua.TCall(String_JsonDecode, json)
	if error ~= nil then
		Log("OtherSystem:HandleALittleJsonRPC:", error, json)
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

function OtherSystem:SystemSelectDirectory(target, init_dir)
	self._system_select_directory = target
	__CPPAPI_SystemSelectDirectory(init_dir)
end

function OtherSystem:HandleSystemSelectDirectory(path)
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

function OtherSystem:SystemSelectFile(target, init_dir)
	self._system_select_file = target
	__CPPAPI_SystemSelectFile(init_dir)
end

function OtherSystem:HandleSystemSelectFile(path)
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

function OtherSystem:SystemSaveFile(target, file_name, path)
	self._system_save_file = target
	__CPPAPI_SystemSaveFile(file_name, path)
end

function OtherSystem:HandleSystemSaveFile(path)
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

_G.A_OtherSystem = OtherSystem()
