-- ALittle Generate Lua
local ___pairs = pairs
local ___ipairs = ipairs


function RequireStd(base_path)
local ___COROUTINE = coroutine.running()
	ALittle.Require(base_path, "Std/Reflect/ReflectCmd")
	ALittle.Require(base_path, "Std/Reflect/ReflectCsv")
	ALittle.Require(base_path, "Std/Reflect/ReflectMessage")
	ALittle.Require(base_path, "Std/Loop/LoopObject")
	ALittle.Require(base_path, "Std/Loop/ILoopSystem")
	ALittle.Require(base_path, "Std/Loop/LoopFrame")
	ALittle.Require(base_path, "Std/Loop/LoopFunction")
	ALittle.Require(base_path, "Std/Loop/LoopGroup")
	ALittle.Require(base_path, "Std/Loop/LoopList")
	ALittle.Require(base_path, "Std/Loop/LoopTimer")
	ALittle.Require(base_path, "Std/Utility/Bit")
	ALittle.Require(base_path, "Std/Utility/WeakRef")
	ALittle.Require(base_path, "Std/Utility/IHeapTimer")
	ALittle.Require(base_path, "Std/Utility/ISchedule")
	ALittle.Require(base_path, "Std/Utility/CsvConfig")
	ALittle.Require(base_path, "Std/Utility/EventDispatcher")
	ALittle.Require(base_path, "Std/Utility/SafeIDCreator")
	ALittle.Require(base_path, "Std/Utility/String")
	ALittle.Require(base_path, "Std/Utility/File")
	ALittle.Require(base_path, "Std/Utility/JsonConfig")
	ALittle.Require(base_path, "Std/Net/HttpFileReceiverTemplate")
	ALittle.Require(base_path, "Std/Net/HttpFileSenderTemplate")
	ALittle.Require(base_path, "Std/Net/HttpReceiverTemplate")
	ALittle.Require(base_path, "Std/Net/HttpSenderTemplate")
	ALittle.Require(base_path, "Std/Net/MsgCommonTemplate")
	ALittle.Require(base_path, "Std/Net/MsgReceiverTemplate")
	ALittle.Require(base_path, "Std/Net/MsgSenderTemplate")
	ALittle.Require(base_path, "Std/Net/MsgSessionTemplate")
	ALittle.Require(base_path, "Adapter/Lua/LuaHeapTimer")
	ALittle.Require(base_path, "Adapter/Lua/LuaCsvFile")
	if net ~= nil then
		ALittle.Require(base_path, "Adapter/Lua/LuaHttpFileInterface")
		ALittle.Require(base_path, "Adapter/Lua/LuaHttpInterface")
		ALittle.Require(base_path, "Adapter/Lua/LuaMsgInterface")
		ALittle.Require(base_path, "Adapter/Lua/LuaMessageFactory")
		ALittle.Require(base_path, "Adapter/Lua/LuaSchedule")
	end
	ALittle.Require(base_path, "Std/Loop/LoopSystem")
	ALittle.Require(base_path, "Std/Utility/Schedule")
end

