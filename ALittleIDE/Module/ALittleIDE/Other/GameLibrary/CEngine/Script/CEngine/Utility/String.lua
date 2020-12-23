-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___pairs = pairs
local ___ipairs = ipairs


function ALittle.String_CryptPassword(account_name, pwd)
	local device_id_md5 = ALittle.String_Md5(ALittle.System_GetDeviceID())
	local account_name_md5 = ALittle.String_Md5(account_name)
	local device_id_md5_ex = ALittle.String_Md5("ALittle" .. ALittle.System_GetDeviceID() .. "ALittle")
	local account_name_md5_ex = ALittle.String_Md5("ALittle" .. account_name .. "ALittle")
	local device_id_md5_base64 = ALittle.String_Base64Encode(device_id_md5)
	local account_name_md5_base64 = ALittle.String_Base64Encode(account_name_md5)
	return ALittle.String_Base64Encode(device_id_md5_base64 .. ALittle.String_Base64Encode(device_id_md5_ex .. pwd .. account_name_md5_ex) .. account_name_md5_base64)
end

function ALittle.String_DecryptPassword(account_name, pwd)
	pwd = ALittle.String_Base64Decode(pwd)
	local device_id_md5 = ALittle.String_Md5(ALittle.System_GetDeviceID())
	local account_name_md5 = ALittle.String_Md5(account_name)
	local device_id_md5_ex = ALittle.String_Md5("ALittle" .. ALittle.System_GetDeviceID() .. "ALittle")
	local account_name_md5_ex = ALittle.String_Md5("ALittle" .. account_name .. "ALittle")
	local device_id_md5_base64 = ALittle.String_Base64Encode(device_id_md5)
	local account_name_md5_base64 = ALittle.String_Base64Encode(account_name_md5)
	local start_index = ALittle.String_Find(pwd, device_id_md5_base64)
	if start_index == nil then
		return nil
	end
	pwd = ALittle.String_Sub(pwd, start_index + ALittle.String_Len(device_id_md5_base64))
	start_index = ALittle.String_Find(pwd, account_name_md5_base64)
	if start_index == nil then
		return nil
	end
	pwd = ALittle.String_Sub(pwd, 1, start_index - 1)
	pwd = ALittle.String_Base64Decode(pwd)
	start_index = ALittle.String_Find(pwd, device_id_md5_ex)
	if start_index == nil then
		return nil
	end
	pwd = ALittle.String_Sub(pwd, start_index + ALittle.String_Len(device_id_md5_ex))
	start_index = ALittle.String_Find(pwd, account_name_md5_ex)
	if start_index == nil then
		return nil
	end
	pwd = ALittle.String_Sub(pwd, 1, start_index - 1)
	return pwd
end

end