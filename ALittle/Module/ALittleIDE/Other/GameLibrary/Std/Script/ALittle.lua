
local ___pairs = pairs
local ___ipairs = ipairs


function __ALITTLEAPI_Std_Init(base_path)
local ___COROUTINE = coroutine.running()
	Require(base_path .. "Std/Reflect/ReflectCmd")
	Require(base_path .. "Std/Reflect/ReflectCsv")
	Require(base_path .. "Std/Reflect/ReflectMessage")
	Require(base_path .. "Std/Loop/LoopObject")
	Require(base_path .. "Std/Loop/ILoopSystem")
	Require(base_path .. "Std/Loop/LoopFunction")
	Require(base_path .. "Std/Loop/LoopGroup")
	Require(base_path .. "Std/Loop/LoopList")
	Require(base_path .. "Std/Loop/LoopTimer")
	Require(base_path .. "Std/Utility/IHeapTimer")
	Require(base_path .. "Std/Utility/ISchedule")
	Require(base_path .. "Std/Utility/CsvConfig")
	Require(base_path .. "Std/Utility/EventDispatcher")
	Require(base_path .. "Std/Utility/SafeIDCreator")
	Require(base_path .. "Std/Utility/String")
	Require(base_path .. "Std/Utility/File")
	Require(base_path .. "Std/Utility/JsonConfig")
	Require(base_path .. "Std/Net/HttpFileReceiverTemplate")
	Require(base_path .. "Std/Net/HttpFileSenderTemplate")
	Require(base_path .. "Std/Net/HttpReceiverTemplate")
	Require(base_path .. "Std/Net/HttpSenderTemplate")
	Require(base_path .. "Std/Net/MsgCommonTemplate")
	Require(base_path .. "Std/Net/MsgReceiverTemplate")
	Require(base_path .. "Std/Net/MsgSenderTemplate")
	Require(base_path .. "Std/Net/MsgSessionTemplate")
	do
		Require(base_path .. "Adapter/Lua/LuaHeapTimer")
		Require(base_path .. "Adapter/Lua/LuaCsvFile")
		if net ~= nil then
			Require(base_path .. "Adapter/Lua/LuaHttpFileInterface")
			Require(base_path .. "Adapter/Lua/LuaHttpInterface")
			Require(base_path .. "Adapter/Lua/LuaMsgInterface")
			Require(base_path .. "Adapter/Lua/LuaMessageFactory")
			Require(base_path .. "Adapter/Lua/LuaSchedule")
		end
	end
	Require(base_path .. "Std/Loop/LoopSystem")
	Require(base_path .. "Std/Utility/Schedule")
end

