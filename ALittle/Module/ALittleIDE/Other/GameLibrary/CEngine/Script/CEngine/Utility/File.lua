
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function File_BaseFilePath()
	return __CPPAPI_ScriptSystemEx:BaseFilePath()
end

function File_ExternalFilePath()
	return __CPPAPI_ScriptSystemEx:ExternalFilePath()
end

function File_CopyFile(src_path, dst_path)
	return __CPPAPI_CopyFile(src_path, dst_path, false)
end

function File_CopyFileFromAsset(src_path, dst_path)
	return __CPPAPI_CopyFile(src_path, dst_path, true)
end

function File_SaveFile(target_path, content, size)
	return __CPPAPI_SaveFile(target_path, content, size)
end

function File_MD5(path)
	return __CPPAPI_ScriptSystemEx:FileMD5(path)
end

function File_CopyDeepDir(src_path, dest_path, ext, log)
	do
		local upper_ext = nil
		if ext ~= nil then
			upper_ext = string.upper(ext)
		end
		for file in lfs.dir(src_path) do
			if file ~= "." and file ~= ".." then
				local src_file_path = src_path .. "/" .. file
				local dest_file_path = dest_path .. "/" .. file
				local attr = lfs.attributes(src_file_path)
				if attr.mode == "directory" then
					lfs.mkdir(dest_file_path)
					File_CopyDeepDir(src_file_path, dest_file_path, upper_ext, log)
				else
					if upper_ext == nil or File_GetFileExtByPathAndUpper(src_file_path) == upper_ext then
						File_CopyFile(src_file_path, dest_file_path)
						if log then
							Log("copy file:", src_file_path, dest_file_path)
						end
					end
				end
			end
		end
	end
end

function File_ReadTextFromFile(file_path, crypt_mode)
	do
		local file = __CPPAPILocalFile()
		file:SetPath(file_path)
		if file:Load() == false then
			return nil
		end
		if crypt_mode then
			file:Decrypt(nil)
		end
		local content = file:GetContent()
		file:Clear()
		return content
	end
end

function File_WriteTextToFile(content, file_path)
	return File_SaveFile(file_path, content, -1)
end

function File_ReadJsonFromFile(file_path, crypt_mode)
	do
		local file = __CPPAPILocalFile()
		file:SetPath(file_path)
		if file:Load() == false then
			return nil, file_path .. " load failed"
		end
		if crypt_mode then
			file:Decrypt(nil)
		end
		local content = file:GetContent()
		file:Clear()
		local error, new_content = Lua.TCall(json.decode, content)
		if error == nil then
			return new_content, content
		end
		return nil, new_content
	end
end

function File_ReadJsonFromAsset(file_path, crypt_mode)
	do
		local file = __CPPAPILocalFile()
		file:SetPath(file_path)
		if file:LoadBySDL() == false then
			return nil, file_path .. " load failed!"
		end
		if crypt_mode then
			file:Decrypt(nil)
		end
		local content = file:GetContent()
		file:Clear()
		local error, new_content = Lua.TCall(json.decode, content)
		if error == nil then
			return new_content, content
		end
		return nil, new_content
	end
end

function File_WriteJsonToFile(content, file_path)
	return File_SaveFile(file_path, json.encode(content), -1)
end

function DeleteLog(day_count_before)
	do
		if day_count_before <= 0 then
			return
		end
		local log_path = File_ExternalFilePath() .. "Log"
		if File_GetFileAttr(log_path) == nil then
			return
		end
		local time_table = os.date("*t")
		time_table.day = time_table.day - day_count_before
		local time_string = os.date("%Y-%m-%d", os.time(time_table)) .. ".log"
		local delete_list = {}
		local delete_count = 0
		for file in lfs.dir(log_path) do
			if file ~= "." and file ~= ".." then
				if file <= time_string then
					delete_count = delete_count + 1
					delete_list[delete_count] = file
				end
			end
		end
		for k, v in ___ipairs(delete_list) do
			File_DeleteFile(File_ExternalFilePath() .. "Log/" .. v)
		end
	end
end

