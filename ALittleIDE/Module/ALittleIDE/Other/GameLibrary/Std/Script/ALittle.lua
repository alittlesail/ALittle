-- ALittle Generate Lua And Do Not Edit This Line!
do
local ___pairs = pairs
local ___ipairs = ipairs


function _G.RequireStd(base_path)
	local ___COROUTINE = coroutine.running()
	Require(base_path, "Cmd/ReflectCmd")
	Require(base_path, "Config/ReflectCsv")
	Require(base_path, "Net/ReflectMessage")
	Require(base_path, "Loop/LoopObject")
	Require(base_path, "Loop/ILoopSystem")
	Require(base_path, "Loop/LoopFrame")
	Require(base_path, "Loop/LoopFunction")
	Require(base_path, "Loop/LoopGroup")
	Require(base_path, "Loop/LoopList")
	Require(base_path, "Loop/LoopTimer")
	Require(base_path, "Config/CsvConfig")
	Require(base_path, "Config/JsonConfig")
	Require(base_path, "Bit/Bit")
	Require(base_path, "WeakRef/WeakRef")
	Require(base_path, "Loop/IHeapTimer")
	Require(base_path, "Schedule/ISchedule")
	Require(base_path, "Utility/EventDispatcher")
	Require(base_path, "Utility/SafeIDCreator")
	Require(base_path, "String/String")
	Require(base_path, "File/File")
	Require(base_path, "Net/HttpFileReceiverTemplate")
	Require(base_path, "Net/HttpFileSenderTemplate")
	Require(base_path, "Net/HttpReceiverTemplate")
	Require(base_path, "Net/HttpSenderTemplate")
	Require(base_path, "Net/MsgCommonTemplate")
	Require(base_path, "Net/MsgReceiverTemplate")
	Require(base_path, "Net/MsgSenderTemplate")
	Require(base_path, "Net/MsgSessionTemplate")
	Require(base_path, "Loop/Lua/LuaHeapTimer")
	Require(base_path, "Config/Lua/LuaCsvFile")
	do
		Require(base_path, "Net/Lua/LuaHttpFileInterface")
		Require(base_path, "Net/Lua/LuaHttpInterface")
		Require(base_path, "Net/Lua/LuaMsgInterface")
		Require(base_path, "Net/Lua/LuaMessageFactory")
		Require(base_path, "Schedule/Lua/LuaSchedule")
	end
	Require(base_path, "Loop/LoopSystem")
	Require(base_path, "Schedule/Schedule")
end

end