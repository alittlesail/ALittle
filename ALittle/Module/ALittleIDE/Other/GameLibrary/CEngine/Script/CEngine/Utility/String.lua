-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function String_CryptPassword(account_name, pwd)
	local device_id_md5 = String_MD5(System_GetDeviceID())
	local account_name_md5 = String_MD5(account_name)
	local device_id_md5_ex = String_MD5("ALittle" .. System_GetDeviceID() .. "ALittle")
	local account_name_md5_ex = String_MD5("ALittle" .. account_name .. "ALittle")
	local device_id_md5_base64 = String_Base64Encode(device_id_md5)
	local account_name_md5_base64 = String_Base64Encode(account_name_md5)
	return String_Base64Encode(device_id_md5_base64 .. String_Base64Encode(device_id_md5_ex .. pwd .. account_name_md5_ex) .. account_name_md5_base64)
end

function String_DecryptPassword(account_name, pwd)
	pwd = String_Base64Decode(pwd)
	local device_id_md5 = String_MD5(System_GetDeviceID())
	local account_name_md5 = String_MD5(account_name)
	local device_id_md5_ex = String_MD5("ALittle" .. System_GetDeviceID() .. "ALittle")
	local account_name_md5_ex = String_MD5("ALittle" .. account_name .. "ALittle")
	local device_id_md5_base64 = String_Base64Encode(device_id_md5)
	local account_name_md5_base64 = String_Base64Encode(account_name_md5)
	local start_index = String_Find(pwd, device_id_md5_base64)
	if start_index == nil then
		return nil
	end
	pwd = String_Sub(pwd, start_index + string.len(device_id_md5_base64))
	start_index = String_Find(pwd, account_name_md5_base64)
	if start_index == nil then
		return nil
	end
	pwd = String_Sub(pwd, 1, start_index - 1)
	pwd = String_Base64Decode(pwd)
	start_index = String_Find(pwd, device_id_md5_ex)
	if start_index == nil then
		return nil
	end
	pwd = String_Sub(pwd, start_index + string.len(device_id_md5_ex))
	start_index = String_Find(pwd, account_name_md5_ex)
	if start_index == nil then
		return nil
	end
	pwd = String_Sub(pwd, 1, start_index - 1)
	return pwd
end

