-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


local open = io.open
local rename = os.rename
local remove = os.remove
local attributes = lfs.attributes
local dir = lfs.dir
local currentdir = lfs.currentdir
local chdir = lfs.chdir
local rmdir = lfs.rmdir
local mkdir = lfs.mkdir
IFileLoader = Lua.Class(nil, "ALittle.IFileLoader")

function IFileLoader:Load(file_path)
	return nil
end

assert(ALittle.IFileLoader, " extends class:ALittle.IFileLoader is nil")
LuaFileLoader = Lua.Class(ALittle.IFileLoader, "ALittle.LuaFileLoader")

function LuaFileLoader:Load(file_path)
	local file = open(file_path, "r")
	if file == nil then
		return nil
	end
	local content = file:read("*a")
	file:close()
	return content
end

IFileSaver = Lua.Class(nil, "ALittle.IFileSaver")

function IFileSaver:Save(file_path, content)
	return false
end

assert(ALittle.IFileSaver, " extends class:ALittle.IFileSaver is nil")
LuaFileSaver = Lua.Class(ALittle.IFileSaver, "ALittle.LuaFileSaver")

function LuaFileSaver:Save(file_path, content)
	local file = open(file_path, "w")
	if file == nil then
		return false
	end
	file:write(content)
	file:close()
	return true
end

function File_GetCurrentPath()
	return currentdir()
end

function File_SetCurrentPath(path)
	return chdir(path)
end

function File_RenameFile(path, new_path)
	return rename(path, new_path)
end

function File_DeleteFile(path)
	return remove(path)
end

function File_GetFileAttr(path)
	return attributes(path)
end

function File_GetFileAttrByDir(path, file_map)
	do
		if file_map == nil then
			file_map = {}
		end
		for file in dir(path) do
			if file ~= "." and file ~= ".." then
				local file_path = path .. "/" .. file
				local attr = attributes(file_path)
				if attr.mode == "directory" then
					File_GetFileAttrByDir(file_path, file_map)
				else
					file_map[file_path] = attr
				end
			end
		end
		return file_map
	end
end

function File_GetFileNameListByDir(path, file_map)
	do
		if file_map == nil then
			file_map = {}
		end
		for file in dir(path) do
			if file ~= "." and file ~= ".." then
				local file_path = path .. "/" .. file
				file_map[file] = attributes(file_path)
			end
		end
		return file_map
	end
end

function File_DeleteDir(path)
	return rmdir(path)
end

function File_DeleteDeepDir(path, log_path)
	do
		if path == nil or path == "" then
			return
		end
		if File_GetFileAttr(path) == nil then
			return
		end
		for file in dir(path) do
			if file ~= "." and file ~= ".." then
				local file_path = path .. "/" .. file
				local attr = attributes(file_path)
				if attr.mode == "directory" then
					File_DeleteDeepDir(file_path, log_path)
				else
					File_DeleteFile(file_path)
					if log_path then
						Log("delete file:", file_path)
					end
				end
			end
		end
		File_DeleteDir(path)
	end
end

function File_MakeDir(path)
	return mkdir(path)
end

function File_MakeDeepDir(path)
	local path_list = String_SplitSepList(path, {"/", "\\"})
	local cur_path = ""
	for index, sub_path in ___ipairs(path_list) do
		cur_path = cur_path .. sub_path
		File_MakeDir(cur_path)
		cur_path = cur_path .. "/"
	end
end

function File_PathEndWithSplit(file_path)
	local len = String_Len(file_path)
	if len == 0 then
		return file_path
	end
	local byte = String_Byte(file_path, len)
	if byte == 47 or byte == 92 then
		return file_path
	end
	if String_Find(file_path, "\\") ~= nil then
		return file_path .. "\\"
	end
	return file_path .. "/"
end

function File_GetFileNameByPath(file_path)
	local list = String_SplitSepList(file_path, {"/", "\\"})
	local l = List_MaxN(list)
	if l <= 0 then
		return file_path
	end
	return list[l]
end

function File_GetFilePathByPath(file_path)
	local new_file_path = File_GetFileNameByPath(file_path)
	return String_Sub(file_path, 1, -String_Len(new_file_path) - 2)
end

function File_GetFileExtByPath(file_path)
	local list = String_Split(file_path, ".")
	local l = List_MaxN(list)
	if l <= 0 then
		return file_path
	end
	return list[l]
end

function File_GetFileExtByPathAndUpper(file_path)
	return String_Upper(File_GetFileExtByPath(file_path))
end

function File_GetJustFileNameByPath(file_path)
	local new_file_path = File_GetFileNameByPath(file_path)
	local list = String_Split(new_file_path, ".")
	local l = List_MaxN(list)
	if l <= 1 then
		return new_file_path
	end
	return list[l - 1]
end

function File_ReadJsonFromStdFile(file_path)
	do
		local file = io.open(file_path, "rb")
		if file == nil then
			return nil, file_path .. " load failed"
		end
		local content = file:read("*a")
		file:close()
		local error, new_content = Lua.TCall(json.decode, content)
		if error == nil then
			return new_content, content
		end
		return nil, new_content
	end
end

function File_WriteJsonFromStdFile(content, file_path)
	do
		local file = io.open(file_path, "wb")
		if file == nil then
			return false
		end
		file:write(json.encode(content))
		file:close()
		return true
	end
end

function File_ReadTextFromStdFile(file_path)
	do
		local file = io.open(file_path, "rb")
		if file == nil then
			return nil, file_path .. " load failed"
		end
		local content = file:read("*a")
		file:close()
		return nil, content
	end
end

function File_WriteTextFromStdFile(content, file_path)
	do
		local file = io.open(file_path, "wb")
		if file == nil then
			return false
		end
		file:write(content)
		file:close()
		return true
	end
end

