{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.String_CryptPassword = function(account_name, pwd) {
	let device_id_md5 = ALittle.String_Md5(ALittle.System_GetDeviceID());
	let account_name_md5 = ALittle.String_Md5(account_name);
	let device_id_md5_ex = ALittle.String_Md5("ALittle" + ALittle.System_GetDeviceID() + "ALittle");
	let account_name_md5_ex = ALittle.String_Md5("ALittle" + account_name + "ALittle");
	let device_id_md5_base64 = ALittle.String_Base64Encode(device_id_md5);
	let account_name_md5_base64 = ALittle.String_Base64Encode(account_name_md5);
	return ALittle.String_Base64Encode(device_id_md5_base64 + (ALittle.String_Base64Encode(device_id_md5_ex + pwd + account_name_md5_ex)) + account_name_md5_base64);
}

ALittle.String_DecryptPassword = function(account_name, pwd) {
	pwd = ALittle.String_Base64Decode(pwd);
	let device_id_md5 = ALittle.String_Md5(ALittle.System_GetDeviceID());
	let account_name_md5 = ALittle.String_Md5(account_name);
	let device_id_md5_ex = ALittle.String_Md5("ALittle" + ALittle.System_GetDeviceID() + "ALittle");
	let account_name_md5_ex = ALittle.String_Md5("ALittle" + account_name + "ALittle");
	let device_id_md5_base64 = ALittle.String_Base64Encode(device_id_md5);
	let account_name_md5_base64 = ALittle.String_Base64Encode(account_name_md5);
	let start_index = ALittle.String_Find(pwd, device_id_md5_base64);
	if (start_index === undefined) {
		return undefined;
	}
	pwd = ALittle.String_Sub(pwd, start_index + ALittle.String_Len(device_id_md5_base64));
	start_index = ALittle.String_Find(pwd, account_name_md5_base64);
	if (start_index === undefined) {
		return undefined;
	}
	pwd = ALittle.String_Sub(pwd, 1, start_index - 1);
	pwd = ALittle.String_Base64Decode(pwd);
	start_index = ALittle.String_Find(pwd, device_id_md5_ex);
	if (start_index === undefined) {
		return undefined;
	}
	pwd = ALittle.String_Sub(pwd, start_index + ALittle.String_Len(device_id_md5_ex));
	start_index = ALittle.String_Find(pwd, account_name_md5_ex);
	if (start_index === undefined) {
		return undefined;
	}
	pwd = ALittle.String_Sub(pwd, 1, start_index - 1);
	return pwd;
}

}