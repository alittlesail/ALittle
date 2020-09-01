{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IFileLoader = JavaScript.Class(undefined, {
	Load : function(file_path) {
		return undefined;
	},
}, "ALittle.IFileLoader");

if (ALittle.IFileLoader === undefined) throw new Error(" extends class:ALittle.IFileLoader is undefined");
ALittle.JFileLoader = JavaScript.Class(ALittle.IFileLoader, {
	Load : function(file_path) {
		let [content, buffer] = JavaScript.File_LoadFile(file_path);
		return content;
	},
}, "ALittle.JFileLoader");

ALittle.IFileSaver = JavaScript.Class(undefined, {
	Save : function(file_path, content) {
		return false;
	},
}, "ALittle.IFileSaver");

if (ALittle.IFileSaver === undefined) throw new Error(" extends class:ALittle.IFileSaver is undefined");
ALittle.JFileSaver = JavaScript.Class(ALittle.IFileSaver, {
	Save : function(file_path, content) {
		return JavaScript.File_SaveFile(file_path, content, undefined);
	},
}, "ALittle.JFileSaver");

ALittle.File_GetCurrentPath = function() {
	return JavaScript.File_GetCurrentPath();
}

ALittle.File_SetCurrentPath = function(path) {
	return JavaScript.File_SetCurrentPath(path);
}

ALittle.File_RenameFile = function(path, new_path) {
	return JavaScript.File_RenameFile(path, new_path);
}

ALittle.File_DeleteFile = function(path) {
	return JavaScript.File_DeleteFile(path);
}

ALittle.File_GetFileAttr = function(path) {
	return JavaScript.File_GetFileAttr(path);
}

ALittle.File_GetFileAttrByDir = function(path, file_map) {
	return JavaScript.File_GetFileAttrByDir(path, file_map);
}

ALittle.File_GetFileListByDir = function(path, file_list) {
	return JavaScript.File_GetFileListByDir(path, file_list);
}

ALittle.File_GetFileNameListByDir = function(path, file_map) {
	return JavaScript.File_GetFileNameListByDir(path, file_map);
}

ALittle.File_DeleteDir = function(path) {
	return JavaScript.File_DeleteDir(path);
}

ALittle.File_DeleteDeepDir = function(path, log_path) {
	JavaScript.File_DeleteDeepDir(path, log_path);
}

ALittle.File_MakeDir = function(path) {
	return JavaScript.File_MakeDir(path);
}

ALittle.File_MakeDeepDir = function(path) {
	let path_list = ALittle.String_SplitSepList(path, ["/", "\\"]);
	let cur_path = "";
	let ___OBJECT_1 = path_list;
	for (let index = 1; index <= ___OBJECT_1.length; ++index) {
		let sub_path = ___OBJECT_1[index - 1];
		if (sub_path === undefined) break;
		cur_path = cur_path + sub_path;
		ALittle.File_MakeDir(cur_path);
		cur_path = cur_path + "/";
	}
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
	let l = ALittle.List_MaxN(list);
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
	let l = ALittle.List_MaxN(list);
	if (l <= 0) {
		return file_path;
	}
	return list[l - 1];
}

ALittle.File_ChangeFileExtByPath = function(file_path, ext) {
	let list = ALittle.String_Split(file_path, ".");
	let l = ALittle.List_MaxN(list);
	if (l <= 0) {
		return file_path + "." + ext;
	}
	list[l - 1] = ext;
	return ALittle.String_Join(list, ".");
}

ALittle.File_GetFileExtByPathAndUpper = function(file_path) {
	return ALittle.String_Upper(ALittle.File_GetFileExtByPath(file_path));
}

ALittle.File_GetJustFileNameByPath = function(file_path) {
	let new_file_path = ALittle.File_GetFileNameByPath(file_path);
	let list = ALittle.String_Split(new_file_path, ".");
	let l = ALittle.List_MaxN(list);
	if (l <= 1) {
		return new_file_path;
	}
	return list[l - 1 - 1];
}

ALittle.File_ReadJsonFromStdFile = function(file_path) {
	{
		let [content] = JavaScript.File_LoadFile(file_path);
		if (content === undefined) {
			return [undefined, file_path + " load failed"];
		}
		let [error, new_content] = (function() { try { let ___VALUE = JSON.parse.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } })();
		if (error === undefined) {
			return [new_content, content];
		}
		return [undefined, new_content];
	}
}

ALittle.File_WriteJsonFromStdFile = function(content, file_path) {
	{
		return JavaScript.File_SaveFile(file_path, JSON.stringify(content), undefined);
	}
}

ALittle.File_ReadTextFromStdFile = function(file_path) {
	{
		let [content, buffer] = JavaScript.File_LoadFile(file_path);
		return content;
	}
}

ALittle.File_WriteTextFromStdFile = function(content, file_path) {
	{
		return JavaScript.File_SaveFile(file_path, content, undefined);
	}
}

}