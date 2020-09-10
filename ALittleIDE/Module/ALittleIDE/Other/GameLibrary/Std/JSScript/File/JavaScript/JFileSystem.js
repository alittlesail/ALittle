{
if (typeof JavaScript === "undefined") window.JavaScript = {};

ALittle.RegStruct(-1393456776, "JavaScript.FileInfo", {
name : "JavaScript.FileInfo", ns_name : "JavaScript", rl_name : "FileInfo", hash_code : -1393456776,
name_list : ["parent","name","content","buffer","is_directory","file"],
type_list : ["JavaScript.FileInfo","string","string","native javascript.ArrayBuffer","bool","Map<string,JavaScript.FileInfo>"],
option_map : {}
})

let root = {};
root.is_directory = true;
root.name = "";
let cur_dir = "";
let Path_FilterEmpty = function(list) {
	let new_list = [];
	let ___OBJECT_1 = list;
	for (let index = 1; index <= ___OBJECT_1.length; ++index) {
		let value = ___OBJECT_1[index - 1];
		if (value === undefined) break;
		if (value === "") {
			continue;
		}
		ALittle.List_Push(new_list, value);
	}
	return new_list;
}

JavaScript.File_GetCurrentPath = function() {
	return cur_dir;
}

JavaScript.File_SetCurrentPath = function(path) {
	let list = Path_FilterEmpty(ALittle.String_SplitSepList(path, ["/", "\\"]));
	let cur = root;
	let dir = "";
	let ___OBJECT_2 = list;
	for (let index = 1; index <= ___OBJECT_2.length; ++index) {
		let name = ___OBJECT_2[index - 1];
		if (name === undefined) break;
		if (cur.file === undefined) {
			return false;
		}
		let file = cur.file[name];
		if (file === undefined) {
			return false;
		}
		if (!file.is_directory) {
			return false;
		}
		cur = file;
		dir = dir + "/" + file.name;
	}
	cur_dir = dir;
	if (ALittle.String_Len(cur_dir) > 0) {
		cur_dir = cur_dir + "/";
	}
	return true;
}

JavaScript.File_RenameFile = function(path, new_path) {
	let list = Path_FilterEmpty(ALittle.String_SplitSepList(path, ["/", "\\"]));
	let list_len = ALittle.List_MaxN(list);
	let cur = root;
	for (let i = 1; i <= list_len - 1; i += 1) {
		if (cur.file === undefined) {
			return false;
		}
		let file = cur.file[list[i - 1]];
		if (file === undefined) {
			return false;
		}
		if (!file.is_directory) {
			return false;
		}
		cur = file;
	}
	if (cur.file === undefined) {
		return false;
	}
	let cur_file = cur.file[list[list_len - 1]];
	if (cur_file === undefined || cur_file.is_directory) {
		return false;
	}
	let new_list = Path_FilterEmpty(ALittle.String_SplitSepList(new_path, ["/", "\\"]));
	let new_list_len = ALittle.List_MaxN(new_list);
	let new_cur = root;
	for (let i = 1; i <= new_list_len - 1; i += 1) {
		if (new_cur.file === undefined) {
			return false;
		}
		let file = new_cur.file[new_list[i - 1]];
		if (file === undefined) {
			return false;
		}
		if (!file.is_directory) {
			return false;
		}
		new_cur = file;
	}
	new_cur.file[new_list[new_list_len - 1]] = cur_file;
	delete cur.file[list[list_len - 1]];
	cur_file.parent = new_cur;
	return true;
}

JavaScript.File_DeleteFile = function(path) {
	let list = Path_FilterEmpty(ALittle.String_SplitSepList(path, ["/", "\\"]));
	let list_len = ALittle.List_MaxN(list);
	let cur = root;
	for (let i = 1; i <= list_len - 1; i += 1) {
		if (cur.file === undefined) {
			return false;
		}
		let file = cur.file[list[i - 1]];
		if (file === undefined) {
			return false;
		}
		if (!file.is_directory) {
			return false;
		}
		cur = file;
	}
	if (cur.file === undefined) {
		return false;
	}
	let cur_file = cur.file[list[list_len - 1]];
	if (cur_file === undefined || cur_file.is_directory) {
		return false;
	}
	delete cur.file[list[list_len - 1]];
	cur_file.parent = undefined;
	return true;
}

JavaScript.File_GetFileAttr = function(path) {
	let list = Path_FilterEmpty(ALittle.String_SplitSepList(path, ["/", "\\"]));
	let list_len = ALittle.List_MaxN(list);
	let cur = root;
	for (let i = 1; i <= list_len - 1; i += 1) {
		if (cur.file === undefined) {
			return undefined;
		}
		let file = cur.file[list[i - 1]];
		if (file === undefined) {
			return undefined;
		}
		if (!file.is_directory) {
			return undefined;
		}
		cur = file;
	}
	if (cur.file === undefined) {
		return undefined;
	}
	let cur_file = cur.file[list[list_len - 1]];
	if (cur_file === undefined) {
		return undefined;
	}
	let attr = {};
	attr.mode = "file";
	attr.size = 0;
	if (cur_file.is_directory) {
		attr.mode = "directory";
	} else {
		if (cur_file.buffer !== undefined) {
			attr.size = cur_file.buffer.byteLength;
		} else {
			attr.size = ALittle.String_Len(cur_file.content);
		}
	}
	return attr;
}

JavaScript.File_GetFileAttrByDir = function(path, file_map) {
	if (file_map === undefined) {
		file_map = {};
	}
	let list = Path_FilterEmpty(ALittle.String_SplitSepList(path, ["/", "\\"]));
	let cur = root;
	let ___OBJECT_3 = list;
	for (let index = 1; index <= ___OBJECT_3.length; ++index) {
		let name = ___OBJECT_3[index - 1];
		if (name === undefined) break;
		if (cur.file === undefined) {
			return file_map;
		}
		let file = cur.file[name];
		if (file === undefined) {
			return file_map;
		}
		if (!file.is_directory) {
			return file_map;
		}
		cur = file;
	}
	if (cur.file === undefined) {
		return file_map;
	}
	let ___OBJECT_4 = cur.file;
	for (let name in ___OBJECT_4) {
		let value = ___OBJECT_4[name];
		if (value === undefined) continue;
		let file_path = path + "/" + name;
		if (value.is_directory) {
			JavaScript.File_GetFileAttrByDir(file_path, file_map);
		} else {
			let attr = {};
			attr.mode = "file";
			attr.size = ALittle.String_Len(value.content);
			file_map[file_path] = attr;
		}
	}
	return file_map;
}

JavaScript.File_GetFileListByDir = function(path, file_list) {
	if (file_list === undefined) {
		file_list = [];
	}
	let list = Path_FilterEmpty(ALittle.String_SplitSepList(path, ["/", "\\"]));
	let cur = root;
	let ___OBJECT_5 = list;
	for (let index = 1; index <= ___OBJECT_5.length; ++index) {
		let name = ___OBJECT_5[index - 1];
		if (name === undefined) break;
		if (cur.file === undefined) {
			return file_list;
		}
		let file = cur.file[name];
		if (file === undefined) {
			return file_list;
		}
		if (!file.is_directory) {
			return file_list;
		}
		cur = file;
	}
	if (cur.file === undefined) {
		return file_list;
	}
	let ___OBJECT_6 = cur.file;
	for (let name in ___OBJECT_6) {
		let value = ___OBJECT_6[name];
		if (value === undefined) continue;
		let file_path = path + "/" + name;
		if (value.is_directory) {
			JavaScript.File_GetFileListByDir(file_path, file_list);
		} else {
			let attr = {};
			attr.mode = "file";
			attr.size = ALittle.String_Len(value.content);
			ALittle.List_Push(file_list, file_path);
		}
	}
	return file_list;
}

JavaScript.File_GetFileNameListByDir = function(path, file_map) {
	if (file_map === undefined) {
		file_map = {};
	}
	let list = Path_FilterEmpty(ALittle.String_SplitSepList(path, ["/", "\\"]));
	let cur = root;
	let ___OBJECT_7 = list;
	for (let index = 1; index <= ___OBJECT_7.length; ++index) {
		let name = ___OBJECT_7[index - 1];
		if (name === undefined) break;
		if (cur.file === undefined) {
			return file_map;
		}
		let file = cur.file[name];
		if (file === undefined) {
			return file_map;
		}
		if (!file.is_directory) {
			return file_map;
		}
		cur = file;
	}
	if (cur.file === undefined) {
		return file_map;
	}
	let ___OBJECT_8 = cur.file;
	for (let name in ___OBJECT_8) {
		let value = ___OBJECT_8[name];
		if (value === undefined) continue;
		let file_path = path + "/" + name;
		if (value.is_directory) {
			let attr = {};
			attr.mode = "directory";
			attr.size = 0;
			file_map[name] = attr;
		} else {
			let attr = {};
			attr.mode = "file";
			attr.size = ALittle.String_Len(value.content);
			file_map[name] = attr;
		}
	}
	return file_map;
}

JavaScript.File_DeleteDir = function(path) {
	let list = Path_FilterEmpty(ALittle.String_SplitSepList(path, ["/", "\\"]));
	let cur = root;
	let ___OBJECT_9 = list;
	for (let index = 1; index <= ___OBJECT_9.length; ++index) {
		let name = ___OBJECT_9[index - 1];
		if (name === undefined) break;
		if (cur.file === undefined) {
			return false;
		}
		let file = cur.file[name];
		if (file === undefined) {
			return false;
		}
		if (!file.is_directory) {
			return false;
		}
		cur = file;
	}
	let can = true;
	if (cur.file !== undefined) {
		let ___OBJECT_10 = cur.file;
		for (let index in ___OBJECT_10) {
			let value = ___OBJECT_10[index];
			if (value === undefined) continue;
			can = false;
			break;
		}
	}
	if (!can) {
		return false;
	}
	delete cur.parent.file[cur.name];
	cur.parent = undefined;
	return true;
}

JavaScript.File_DeleteDeepDir = function(path, log_path) {
	if (log_path) {
		let file_map = JavaScript.File_GetFileAttrByDir(path);
		let ___OBJECT_11 = file_map;
		for (let file_path in ___OBJECT_11) {
			let attr = ___OBJECT_11[file_path];
			if (attr === undefined) continue;
			ALittle.Log("delete file:", file_path);
		}
	}
	let list = Path_FilterEmpty(ALittle.String_SplitSepList(path, ["/", "\\"]));
	let cur = root;
	let ___OBJECT_12 = list;
	for (let index = 1; index <= ___OBJECT_12.length; ++index) {
		let name = ___OBJECT_12[index - 1];
		if (name === undefined) break;
		let file = cur.file[name];
		if (file === undefined) {
			return;
		}
		if (!file.is_directory) {
			return;
		}
		cur = file;
	}
	delete cur.parent.file[cur.name];
	cur.parent = undefined;
}

JavaScript.File_MakeDir = function(path) {
	let list = Path_FilterEmpty(ALittle.String_SplitSepList(path, ["/", "\\"]));
	let list_len = ALittle.List_MaxN(list);
	let cur = root;
	for (let i = 1; i <= list_len - 1; i += 1) {
		if (cur.file === undefined) {
			return false;
		}
		let file = cur.file[list[i - 1]];
		if (file === undefined) {
			return false;
		}
		if (!file.is_directory) {
			return false;
		}
		cur = file;
	}
	if (cur.file === undefined) {
		cur.file = {};
	}
	let cur_file = cur.file[list[list_len - 1]];
	if (cur_file !== undefined) {
		return false;
	}
	let file = {};
	file.is_directory = true;
	file.name = list[list_len - 1];
	file.parent = cur;
	cur.file[list[list_len - 1]] = file;
	return true;
}

JavaScript.File_LoadFile = function(path) {
	let list = Path_FilterEmpty(ALittle.String_SplitSepList(path, ["/", "\\"]));
	let list_len = ALittle.List_MaxN(list);
	let cur = root;
	for (let i = 1; i <= list_len - 1; i += 1) {
		if (cur.file === undefined) {
			return [undefined, undefined];
		}
		let file = cur.file[list[i - 1]];
		if (file === undefined) {
			return [undefined, undefined];
		}
		if (!file.is_directory) {
			return [undefined, undefined];
		}
		cur = file;
	}
	if (cur.file === undefined) {
		return [undefined, undefined];
	}
	let cur_file = cur.file[list[list_len - 1]];
	if (cur_file === undefined || cur_file.is_directory) {
		return [undefined, undefined];
	}
	return [cur_file.content, cur_file.buffer];
}

JavaScript.File_CopyFile = function(src_path, dst_path) {
	let [content, buffer] = JavaScript.File_LoadFile(src_path);
	if (content === undefined && buffer === undefined) {
		return false;
	}
	return JavaScript.File_SaveFile(dst_path, content, buffer);
}

JavaScript.File_SaveFile = function(path, content, buffer) {
	let list = Path_FilterEmpty(ALittle.String_SplitSepList(path, ["/", "\\"]));
	let list_len = ALittle.List_MaxN(list);
	let cur = root;
	for (let i = 1; i <= list_len - 1; i += 1) {
		if (cur.file === undefined) {
			return false;
		}
		let file = cur.file[list[i - 1]];
		if (file === undefined) {
			return false;
		}
		if (!file.is_directory) {
			return false;
		}
		cur = file;
	}
	if (cur.file === undefined) {
		cur.file = {};
	}
	let file = {};
	file.content = content;
	file.buffer = buffer;
	file.is_directory = false;
	file.name = list[list_len - 1];
	file.parent = cur;
	cur.file[list[list_len - 1]] = file;
	return true;
}

JavaScript.File_CopyDeepDir = function(src_path, dest_path, ext, log) {
	let upper_ext = undefined;
	if (ext !== undefined) {
		upper_ext = ext.toUpperCase();
	}
	let list = Path_FilterEmpty(ALittle.String_SplitSepList(src_path, ["/", "\\"]));
	let cur = root;
	let ___OBJECT_13 = list;
	for (let index = 1; index <= ___OBJECT_13.length; ++index) {
		let name = ___OBJECT_13[index - 1];
		if (name === undefined) break;
		if (cur.file === undefined) {
			return;
		}
		let file = cur.file[name];
		if (file === undefined) {
			return;
		}
		if (!file.is_directory) {
			return;
		}
		cur = file;
	}
	if (cur.file === undefined) {
		return;
	}
	let ___OBJECT_14 = cur.file;
	for (let file in ___OBJECT_14) {
		let info = ___OBJECT_14[file];
		if (info === undefined) continue;
		let src_file_path = src_path + "/" + file;
		let dest_file_path = dest_path + "/" + file;
		if (info.is_directory) {
			JavaScript.File_MakeDir(dest_file_path);
			JavaScript.File_CopyDeepDir(src_file_path, dest_file_path, upper_ext, log);
		} else {
			if (upper_ext === undefined || ALittle.File_GetFileExtByPathAndUpper(src_file_path) === upper_ext) {
				JavaScript.File_CopyFile(src_file_path, dest_file_path);
				if (log) {
					ALittle.Log("copy file:", src_file_path, dest_file_path);
				}
			}
		}
	}
}

}