-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.IFileLoader, " extends class:ALittle.IFileLoader is nil")
ALittle.LuaClientFileLoader = Lua.Class(ALittle.IFileLoader, "ALittle.LuaClientFileLoader")

function ALittle.LuaClientFileLoader:Load(file_path)
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
ALittle.LuaClientFileSaver = Lua.Class(ALittle.IFileSaver, "ALittle.LuaClientFileSaver")

function ALittle.LuaClientFileSaver:Save(file_path, content)
	return ALittle.File_SaveFile(file_path, content, -1)
end

function ALittle.CreateConfigSystem(file_path, print_error)
	return Lua.Template(ALittle.JsonConfig, "ALittle.JsonConfig<ALittle.LuaClientFileLoader, ALittle.LuaClientFileSaver>", ALittle.LuaClientFileLoader, ALittle.LuaClientFileSaver)(file_path, print_error)
end

end