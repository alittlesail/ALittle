{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.IFileLoader = JavaScript.Class(undefined, {
	Load : function(file_path) {
		return undefined;
	},
}, "ALittle.IFileLoader");

ALittle.IFileSaver = JavaScript.Class(undefined, {
	Save : function(file_path, content) {
		return false;
	},
}, "ALittle.IFileSaver");

ALittle.File_GetCurrentPath = function() {
	return "";
}

ALittle.File_SetCurrentPath = function(path) {
	ALittle.Error("not support File_SetCurrentPath");
	return false;
}

ALittle.File_RenameFile = function(path, new_path) {
	ALittle.Error("not support File_RenameFile");
	return false;
}

ALittle.File_DeleteFile = function(path) {
	ALittle.Error("not support File_DeleteFile");
	return false;
}

ALittle.File_GetFileAttr = function(path) {
	ALittle.Error("not support File_GetFileAttr");
	return undefined;
}

ALittle.File_IteratorDir = function(path) {
	ALittle.Error("not support File_IteratorDir");
	return [undefined, undefined, undefined];
}

ALittle.File_GetFileAttrByDir = function(path, file_map) {
	ALittle.Error("not support File_GetFileAttrByDir");
	return {};
}

ALittle.File_DeleteDir = function(path) {
	ALittle.Error("not support File_DeleteDir");
	return false;
}

ALittle.File_DeleteDeepDir = function(path, log_path) {
	ALittle.Error("not support File_DeleteDeepDir");
}

ALittle.File_MakeDir = function(path) {
	ALittle.Error("not support File_MakeDir");
	return false;
}

ALittle.File_MakeDeepDir = function(path) {
	ALittle.Error("not support File_MakeDeepDir");
}

ALittle.File_PathEndWithSplit = function(file_path) {
	let len = ALittle.String_Len(file_path);
	if (len === 0) {
		return file_path;
	}
	let byte = ALittle.String_Byte(file_path, len);
	if (byte === 47 || byte === 92) {
		return file_path;
	}
	if (ALittle.String_Find(file_path, "\\") !== undefined) {
		return file_path + "\\";
	}
	return file_path + "/";
}

ALittle.File_GetFileNameByPath = function(file_path) {
	let list = ALittle.String_SplitSepList(file_path, ["/", "\\"]);
	let l = ALittle.MaxN(list);
	if (l <= 0) {
		return file_path;
	}
	return list[l - 1];
}

ALittle.File_GetFilePathByPath = function(file_path) {
	let new_file_path = ALittle.File_GetFileNameByPath(file_path);
	return ALittle.String_Sub(file_path, 1, -ALittle.String_Len(new_file_path) - 2);
}

ALittle.File_GetFileExtByPath = function(file_path) {
	let list = ALittle.String_Split(file_path, ".");
	let l = ALittle.MaxN(list);
	if (l <= 0) {
		return file_path;
	}
	return list[l - 1];
}

ALittle.File_GetFileExtByPathAndUpper = function(file_path) {
	return ALittle.String_Upper(ALittle.File_GetFileExtByPath(file_path));
}

ALittle.File_GetJustFileNameByPath = function(file_path) {
	let new_file_path = ALittle.File_GetFileNameByPath(file_path);
	let list = ALittle.String_Split(new_file_path, ".");
	let l = ALittle.MaxN(list);
	if (l <= 1) {
		return new_file_path;
	}
	return list[l - 1 - 1];
}

}