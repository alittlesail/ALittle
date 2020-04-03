{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.File_BaseFilePath = function() {
	return "";
}

ALittle.File_ExternalFilePath = function() {
	return "";
}

ALittle.File_CopyFile = function(src_path, dst_path) {
	ALittle.Error("not support File_CopyFile");
	return false;
}

ALittle.File_CopyFileFromAsset = function(src_path, dst_path) {
	ALittle.Error("not support File_CopyFileFromAsset");
	return false;
}

ALittle.File_SaveFile = function(target_path, content, size) {
	ALittle.Error("not support File_SaveFile");
	return false;
}

ALittle.File_CopyDeepDir = function(src_path, dest_path, ext, log) {
}

ALittle.File_ReadTextFromFile = function(file_path, crypt_mode) {
	ALittle.Error("not support File_ReadTextFromFile");
	return undefined;
}

ALittle.File_WriteTextToFile = function(content, file_path) {
	return ALittle.File_SaveFile(file_path, content, -1);
}

ALittle.File_ReadJsonFromFile = function(file_path, crypt_mode) {
	ALittle.Error("not support File_ReadJsonFromFile");
	return [undefined, "not support File_ReadJsonFromFile"];
}

ALittle.File_ReadJsonFromAsset = function(file_path, crypt_mode) {
	ALittle.Error("not support File_ReadJsonFromAsset");
	return [undefined, "not support File_ReadJsonFromAsset"];
}

ALittle.File_WriteJsonToFile = function(content, file_path) {
	return ALittle.File_SaveFile(file_path, lua.json.encode(content), -1);
}

ALittle.DeleteLog = function(day_count_before) {
	ALittle.Error("not support DeleteLog");
}

}