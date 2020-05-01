-- ALittle Generate Lua
local ___pairs = pairs
local ___ipairs = ipairs


function RequireCore(base_path)
local ___COROUTINE = coroutine.running()
	ALittle.Require(base_path, "Core/Reflect/ReflectRegister")
	ALittle.Require(base_path, "Core/Reflect/ReflectDefine")
	ALittle.Require(base_path, "Core/Lua/LuaBind")
	ALittle.Require(base_path, "Core/Lua/LuaClass")
	ALittle.Require(base_path, "Core/Lua/LuaException")
	if _G["bit"] == nil then
		_G["bit"] = _G["bit32"]
	end
	ALittle.Require(base_path, "Core/Utility/Log")
	ALittle.Require(base_path, "Core/Utility/List")
	ALittle.Require(base_path, "Core/Utility/Map")
	ALittle.Require(base_path, "Core/Utility/Math")
	ALittle.Require(base_path, "Core/Utility/String")
	ALittle.Require(base_path, "Core/Utility/Time")
	ALittle.Require(base_path, "Core/Utility/Coroutine")
	ALittle.Require(base_path, "Core/Net/HttpFileReceiver")
	ALittle.Require(base_path, "Core/Net/HttpFileSender")
	ALittle.Require(base_path, "Core/Net/HttpReceiver")
	ALittle.Require(base_path, "Core/Net/HttpSender")
	ALittle.Require(base_path, "Core/Net/MsgCommon")
end

