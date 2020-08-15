-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function ALittle.File_BaseFilePath()
	return __CPPAPI_ScriptSystemEx:BaseFilePath()
end

function ALittle.File_ExternalFilePath()
	return __CPPAPI_ScriptSystemEx:ExternalFilePath()
end

function ALittle.File_CopyFile(src_path, dst_path)
	return __CPPAPI_CopyFile(src_path, dst_path, false)
end

function ALittle.File_CopyFileFromAsset(src_path, dst_path)
	return __CPPAPI_CopyFile(src_path, dst_path, true)
end

function ALittle.File_SaveFile(target_path, content, size)
	return __CPPAPI_SaveFile(target_path, content, size)
end

function ALittle.File_MD5(path)
	return __CPPAPI_ScriptSystemEx:FileMD5(path)
end

function ALittle.File_CopyDeepDir(src_path, dest_path, ext, log)
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
					ALittle.File_CopyDeepDir(src_file_path, dest_file_path, upper_ext, log)
				else
					if upper_ext == nil or ALittle.File_GetFileExtByPathAndUpper(src_file_path) == upper_ext then
						ALittle.File_CopyFile(src_file_path, dest_file_path)
						if log then
							ALittle.Log("copy file:", src_file_path, dest_file_path)
						end
					end
				end
			end
		end
	end
end

function ALittle.File_ReadTextFromFile(file_path, crypt_mode)
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

function ALittle.File_WriteTextToFile(content, file_path)
	return ALittle.File_SaveFile(file_path, content, -1)
end

function ALittle.File_ReadJsonFromFile(file_path, crypt_mode)
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

function ALittle.File_ReadJsonFromAsset(file_path, crypt_mode)
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

function ALittle.File_WriteJsonToFile(content, file_path)
	return ALittle.File_SaveFile(file_path, json.encode(content), -1)
end

function ALittle.DeleteLog(day_count_before)
	do
		if day_count_before <= 0 then
			return
		end
		local log_path = ALittle.File_ExternalFilePath() .. "Log"
		if ALittle.File_GetFileAttr(log_path) == nil then
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
			ALittle.File_DeleteFile(ALittle.File_ExternalFilePath() .. "Log/" .. v)
		end
	end
end

end