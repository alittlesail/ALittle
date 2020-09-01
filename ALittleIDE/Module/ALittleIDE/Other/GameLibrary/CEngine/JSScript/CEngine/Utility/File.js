{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.File_BaseFilePath = function() {
	return "";
}

ALittle.File_ExternalFilePath = function() {
	return "";
}

ALittle.File_CopyFile = function(src_path, dst_path) {
	return JavaScript.File_CopyFile(src_path, dst_path);
}

ALittle.File_CopyFileFromAsset = function(src_path, dst_path) {
	return JavaScript.File_CopyFile(src_path, dst_path);
}

ALittle.File_SaveFile = function(target_path, content, size) {
	return JavaScript.File_SaveFile(target_path, content, undefined);
}

ALittle.File_MD5 = function(path) {
	let [content] = JavaScript.File_LoadFile(path);
	if (content === undefined) {
		return "";
	}
	return md5(content);
}

ALittle.File_CopyDeepDir = function(src_path, dest_path, ext, log) {
	JavaScript.File_CopyDeepDir(src_path, dest_path, ext, log);
}

ALittle.File_ReadTextFromFile = function(file_path, crypt_mode) {
	{
		let [content, buffer] = JavaScript.File_LoadFile(file_path);
		return content;
	}
}

ALittle.File_WriteTextToFile = function(content, file_path) {
	return ALittle.File_SaveFile(file_path, content, -1);
}

ALittle.File_ReadJsonFromFile = function(file_path, crypt_mode) {
	return [ALittle.File_ReadJsonFromStdFile(file_path)];
}

ALittle.File_ReadJsonFromAsset = function(file_path, crypt_mode) {
	return [ALittle.File_ReadJsonFromStdFile(file_path)];
}

ALittle.File_WriteJsonToFile = function(content, file_path) {
	return ALittle.File_SaveFile(file_path, lua.json.encode(content), -1);
}

ALittle.DeleteLog = function(day_count_before) {
}

}