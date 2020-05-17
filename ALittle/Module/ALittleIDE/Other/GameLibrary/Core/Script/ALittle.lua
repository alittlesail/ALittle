-- ALittle Generate Lua And Do Not Edit This Line!
local ___pairs = pairs
local ___ipairs = ipairs


function Require(base_path, url)
	local ___COROUTINE = coroutine.running()
	if _G["core_require"] ~= nil then
		_G["core_require"](base_path .. url)
	else
		require(base_path .. url)
	end
	return nil
end

function RequireCore(base_path)
	local ___COROUTINE = coroutine.running()
	Require(base_path, "Core/Reflect/ReflectRegister")
	Require(base_path, "Core/Reflect/ReflectDefine")
	Require(base_path, "Core/Lua/LuaBind")
	Require(base_path, "Core/Lua/LuaClass")
	Require(base_path, "Core/Lua/LuaException")
	if _G["bit"] == nil then
		_G["bit"] = _G["bit32"]
	end
	Require(base_path, "Core/Utility/Log")
	Require(base_path, "Core/Utility/List")
	Require(base_path, "Core/Utility/Map")
	Require(base_path, "Core/Utility/Math")
	Require(base_path, "Core/Utility/String")
	Require(base_path, "Core/Utility/Time")
	Require(base_path, "Core/Utility/Coroutine")
	Require(base_path, "Core/Net/HttpFileReceiver")
	Require(base_path, "Core/Net/HttpFileSender")
	Require(base_path, "Core/Net/HttpReceiver")
	Require(base_path, "Core/Net/HttpSender")
	Require(base_path, "Core/Net/MsgCommon")
end

