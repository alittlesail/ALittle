-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.LocalFile = Lua.Class(nil, "ALittle.LocalFile")

function ALittle.LocalFile:Clear()
	if self._lua_file ~= nil then
		self._lua_file:Clear()
		self._lua_file = nil
	end
end

function ALittle.LocalFile:Load(path)
	self:Clear()
	do
		local file = carp.CarpLocalFile()
		file:SetPath(path)
		if not file:Load(false) then
			return false
		end
		self._lua_file = file
	end
	return true
end

function ALittle.LocalFile:GetSize()
	if self._lua_file == nil then
		return 0
	else
		return self._lua_file:GetSize()
	end
end

function ALittle.LocalFile:ReadChar(offset)
	return self._lua_file:ReadChar(offset)
end

function ALittle.LocalFile:ReadUChar(offset)
	return self._lua_file:ReadUChar(offset)
end

function ALittle.LocalFile:ReadShort(offset)
	return self._lua_file:ReadShort(offset)
end

function ALittle.LocalFile:ReadUShort(offset)
	return self._lua_file:ReadUShort(offset)
end

function ALittle.LocalFile:ReadInt(offset)
	return self._lua_file:ReadInt(offset)
end

function ALittle.LocalFile:ReadUInt(offset)
	return self._lua_file:ReadUInt(offset)
end

function ALittle.LocalFile:ReadFloat(offset)
	return self._lua_file:ReadFloat(offset)
end

function ALittle.LocalFile:ReadDouble(offset)
	return self._lua_file:ReadDouble(offset)
end

function ALittle.File_BaseFilePath()
	return carp.BaseFilePath()
end

function ALittle.File_ExternalFilePath()
	return carp.ExternalFilePath()
end

function ALittle.File_CopyFileFromAsset(src_path, dst_path)
	return carp.CopyFile(src_path, dst_path, true)
end

function ALittle.File_SaveFile(target_path, content, size)
	return carp.SaveFile(target_path, content, size)
end

function ALittle.File_Md5(path)
	return carp.FileMd5(path)
end

function ALittle.File_ReadTextFromFile(file_path, crypt_mode)
	do
		local file = carp.CarpLocalFile()
		file:SetPath(file_path)
		if file:Load(false) == false then
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
		local file = carp.CarpLocalFile()
		file:SetPath(file_path)
		if file:Load(false) == false then
			return nil, file_path .. " load failed"
		end
		if crypt_mode then
			file:Decrypt(nil)
		end
		local content = file:GetContent()
		file:Clear()
		local error, new_content = Lua.TCall(cjson.decode, content)
		if error == nil then
			return new_content, content
		end
		return nil, new_content
	end
end

function ALittle.File_ReadJsonFromAsset(file_path, crypt_mode)
	do
		local file = carp.CarpLocalFile()
		file:SetPath(file_path)
		if file:Load(true) == false then
			return nil, file_path .. " load failed!"
		end
		if crypt_mode then
			file:Decrypt(nil)
		end
		local content = file:GetContent()
		file:Clear()
		local error, new_content = Lua.TCall(cjson.decode, content)
		if error == nil then
			return new_content, content
		end
		return nil, new_content
	end
end

function ALittle.File_WriteJsonToFile(content, file_path)
	return ALittle.File_SaveFile(file_path, cjson.encode(content), -1)
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
		local file_list = carp.GetFileNameListInFolder(log_path)
		local delete_list = {}
		local delete_count = 0
		for index, file in ___ipairs(file_list) do
			if file <= time_string then
				delete_count = delete_count + 1
				delete_list[delete_count] = file
			end
		end
		for k, v in ___ipairs(delete_list) do
			ALittle.File_DeleteFile(ALittle.File_ExternalFilePath() .. "Log/" .. v)
		end
	end
end

end