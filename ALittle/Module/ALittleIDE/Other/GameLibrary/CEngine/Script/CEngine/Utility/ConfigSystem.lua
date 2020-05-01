-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.IFileLoader, " extends class:ALittle.IFileLoader is nil")
LuaClientFileLoader = Lua.Class(ALittle.IFileLoader, "ALittle.LuaClientFileLoader")

function LuaClientFileLoader:Load(file_path)
	local file = __CPPAPILocalFile()
	file:SetPath(file_path)
	if not file:Load() then
		return nil
	end
	local content = file:GetContent()
	file:Clear()
	return content
end

assert(ALittle.IFileSaver, " extends class:ALittle.IFileSaver is nil")
LuaClientFileSaver = Lua.Class(ALittle.IFileSaver, "ALittle.LuaClientFileSaver")

function LuaClientFileSaver:Save(file_path, content)
	return File_SaveFile(file_path, content, -1)
end

function CreateConfigSystem(file_path, print_error)
	return Lua.Template(JsonConfig, "ALittle.JsonConfig<ALittle.LuaClientFileLoader, ALittle.LuaClientFileSaver>", LuaClientFileLoader, LuaClientFileSaver)(file_path, print_error)
end

