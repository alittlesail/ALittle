-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
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
ALittle.IFileLoader = Lua.Class(nil, "ALittle.IFileLoader")

function ALittle.IFileLoader:Load(file_path)
	return nil
end

assert(ALittle.IFileLoader, " extends class:ALittle.IFileLoader is nil")
ALittle.LuaFileLoader = Lua.Class(ALittle.IFileLoader, "ALittle.LuaFileLoader")

function ALittle.LuaFileLoader:Load(file_path)
	local file = open(file_path, "r")
	if file == nil then
		return nil
	end
	local content = file:read("*a")
	file:close()
	return content
end

ALittle.IFileSaver = Lua.Class(nil, "ALittle.IFileSaver")

function ALittle.IFileSaver:Save(file_path, content)
	return false
end

assert(ALittle.IFileSaver, " extends class:ALittle.IFileSaver is nil")
ALittle.LuaFileSaver = Lua.Class(ALittle.IFileSaver, "ALittle.LuaFileSaver")

function ALittle.LuaFileSaver:Save(file_path, content)
	local file = open(file_path, "w")
	if file == nil then
		return false
	end
	file:write(content)
	file:close()
	return true
end

function ALittle.File_GetCurrentPath()
	return currentdir()
end

function ALittle.File_SetCurrentPath(path)
	return chdir(path)
end

function ALittle.File_RenameFile(path, new_path)
	return rename(path, new_path)
end

function ALittle.File_DeleteFile(path)
	return remove(path)
end

function ALittle.File_GetFileAttr(path)
	return attributes(path)
end

function ALittle.File_GetFileAttrByDir(path, file_map)
	do
		if file_map == nil then
			file_map = {}
		end
		for file in dir(path) do
			if file ~= "." and file ~= ".." then
				local file_path = path .. "/" .. file
				local attr = attributes(file_path)
				if attr.mode == "directory" then
					ALittle.File_GetFileAttrByDir(file_path, file_map)
				else
					file_map[file_path] = attr
				end
			end
		end
		return file_map
	end
end

function ALittle.File_GetFileListByDir(path, file_list)
	do
		if file_list == nil then
			file_list = {}
		end
		for file in dir(path) do
			if file ~= "." and file ~= ".." then
				local file_path = path .. "/" .. file
				local attr = attributes(file_path)
				if attr.mode == "directory" then
					ALittle.File_GetFileListByDir(file_path, file_list)
				else
					ALittle.List_Push(file_list, file_path)
				end
			end
		end
		return file_list
	end
end

function ALittle.File_GetFileNameListByDir(path, file_map)
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

function ALittle.File_DeleteDir(path)
	return rmdir(path)
end

function ALittle.File_DeleteDeepDir(path, log_path)
	do
		if path == nil or path == "" then
			return
		end
		if ALittle.File_GetFileAttr(path) == nil then
			return
		end
		for file in dir(path) do
			if file ~= "." and file ~= ".." then
				local file_path = path .. "/" .. file
				local attr = attributes(file_path)
				if attr.mode == "directory" then
					ALittle.File_DeleteDeepDir(file_path, log_path)
				else
					ALittle.File_DeleteFile(file_path)
					if log_path then
						ALittle.Log("delete file:", file_path)
					end
				end
			end
		end
		ALittle.File_DeleteDir(path)
	end
end

function ALittle.File_MakeDir(path)
	return mkdir(path)
end

function ALittle.File_MakeDeepDir(path)
	local path_list = ALittle.String_SplitSepList(path, {"/", "\\"})
	local cur_path = ""
	for index, sub_path in ___ipairs(path_list) do
		cur_path = cur_path .. sub_path
		ALittle.File_MakeDir(cur_path)
		cur_path = cur_path .. "/"
	end
end

function ALittle.File_PathEndWithSplit(file_path)
	local len = ALittle.String_Len(file_path)
	if len == 0 then
		return file_path
	end
	local byte = ALittle.String_Byte(file_path, len)
	if byte == 47 or byte == 92 then
		return file_path
	end
	if ALittle.String_Find(file_path, "\\") ~= nil then
		return file_path .. "\\"
	end
	return file_path .. "/"
end

function ALittle.File_GetFileNameByPath(file_path)
	local list = ALittle.String_SplitSepList(file_path, {"/", "\\"})
	local l = ALittle.List_MaxN(list)
	if l <= 0 then
		return file_path
	end
	return list[l]
end

function ALittle.File_GetFilePathByPath(file_path)
	local new_file_path = ALittle.File_GetFileNameByPath(file_path)
	return ALittle.String_Sub(file_path, 1, -ALittle.String_Len(new_file_path) - 2)
end

function ALittle.File_GetFileExtByPath(file_path)
	local list = ALittle.String_Split(file_path, ".")
	local l = ALittle.List_MaxN(list)
	if l <= 0 then
		return file_path
	end
	return list[l]
end

function ALittle.File_ChangeFileExtByPath(file_path, ext)
	local list = ALittle.String_Split(file_path, ".")
	local l = ALittle.List_MaxN(list)
	if l <= 0 then
		return file_path .. "." .. ext
	end
	list[l] = ext
	return ALittle.String_Join(list, ".")
end

function ALittle.File_GetFileExtByPathAndUpper(file_path)
	return ALittle.String_Upper(ALittle.File_GetFileExtByPath(file_path))
end

function ALittle.File_GetJustFileNameByPath(file_path)
	local new_file_path = ALittle.File_GetFileNameByPath(file_path)
	local list = ALittle.String_Split(new_file_path, ".")
	local l = ALittle.List_MaxN(list)
	if l <= 1 then
		return new_file_path
	end
	return list[l - 1]
end

function ALittle.File_ReadJsonFromStdFile(file_path)
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

function ALittle.File_WriteJsonFromStdFile(content, file_path)
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

function ALittle.File_ReadTextFromStdFile(file_path)
	do
		local file = io.open(file_path, "rb")
		if file == nil then
			return nil
		end
		local content = file:read("*a")
		file:close()
		return content
	end
end

function ALittle.File_WriteTextFromStdFile(content, file_path)
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

end