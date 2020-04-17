
local ___pairs = pairs
local ___ipairs = ipairs


local LuaRequire
LuaRequire = function(path)
	require(path)
end

function Require(url)
local ___COROUTINE = coroutine.running()
	require(url)
	return nil
end

function __ALITTLEAPI_Core_Init(base_path)
local ___COROUTINE = coroutine.running()
	Require(base_path .. "Core/Reflect/ReflectRegister")
	Require(base_path .. "Core/Reflect/ReflectDefine")
	do
		Require(base_path .. "Core/Lua/LuaBind")
		Require(base_path .. "Core/Lua/LuaClass")
		Require(base_path .. "Core/Lua/LuaException")
		if _G["bit"] == nil then
			_G["bit"] = _G["bit32"]
		end
	end
	Require(base_path .. "Core/Utility/Log")
	Require(base_path .. "Core/Utility/List")
	Require(base_path .. "Core/Utility/Math")
	Require(base_path .. "Core/Utility/String")
	Require(base_path .. "Core/Utility/Time")
	Require(base_path .. "Core/Utility/Coroutine")
	Require(base_path .. "Core/Net/HttpFileReceiver")
	Require(base_path .. "Core/Net/HttpFileSender")
	Require(base_path .. "Core/Net/HttpReceiver")
	Require(base_path .. "Core/Net/HttpSender")
	Require(base_path .. "Core/Net/MsgCommon")
end

