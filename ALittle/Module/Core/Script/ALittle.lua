-- ALittle Generate Lua
local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___pairs = pairs
local ___ipairs = ipairs


require(___thispath.."Core/Reflect/ReflectRegister")
require(___thispath.."Core/Reflect/ReflectDefine")
require(___thispath.."Core/Lua/LuaBind")
require(___thispath.."Core/Lua/LuaClass")
require(___thispath.."Core/Lua/LuaException")
local BitAdapter
BitAdapter = function()
	if _G["bit"] == nil then
		_G["bit"] = _G["bit32"]
	end
end

BitAdapter()
require(___thispath.."Core/Utility/Log")
require(___thispath.."Core/Utility/List")
require(___thispath.."Core/Utility/Map")
require(___thispath.."Core/Utility/Math")
require(___thispath.."Core/Utility/String")
require(___thispath.."Core/Utility/Time")
require(___thispath.."Core/Utility/Coroutine")
require(___thispath.."Core/Net/HttpFileReceiver")
require(___thispath.."Core/Net/HttpFileSender")
require(___thispath.."Core/Net/HttpReceiver")
require(___thispath.."Core/Net/HttpSender")
require(___thispath.."Core/Net/MsgCommon")
