{
if (typeof JavaScript === "undefined") JavaScript = {};

ALittle.RegStruct(-1393456776, "JavaScript.FileInfo", {
name : "JavaScript.FileInfo", ns_name : "JavaScript", rl_name : "FileInfo", hash_code : -1393456776,
name_list : ["parent","name","content","is_directory","file"],
type_list : ["JavaScript.FileInfo","string","string","bool","Map<string,JavaScript.FileInfo>"],
option_map : {}
})

let root = {};
root.is_directory = true;
root.name = "";
let cur_dir = "";
JavaScript.File_GetCurrentPath = function() {
	return cur_dir;
}

JavaScript.File_SetCurrentPath = function(path) {
	let ends = ALittle.String_Byte(path, ALittle.String_Len(path));
	if (ends === 47 || ends === 92) {
		path = ALittle.String_Sub(path, 1, ALittle.String_Len(path) - 1);
	}
	let list = ALittle.String_SplitSepList(path, ["/", "\\"]);
	let cur = root;
	let dir = "";
	let ___OBJECT_1 = list;
	for (let index = 1; index <= ___OBJECT_1.length; ++index) {
		let name = ___OBJECT_1[index - 1];
		if (name === undefined) break;
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
	let list = ALittle.String_SplitSepList(path, ["/", "\\"]);
	let list_len = ALittle.List_MaxN(list);
	let cur = root;
	for (let i = 1; i <= list_len - 1; i += 1) {
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
	let new_list = ALittle.String_SplitSepList(path, ["/", "\\"]);
	let new_list_len = ALittle.List_MaxN(new_list);
	let new_cur = root;
	for (let i = 1; i <= new_list_len - 1; i += 1) {
		let file = new_cur.file[list[i - 1]];
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
	let list = ALittle.String_SplitSepList(path, ["/", "\\"]);
	let list_len = ALittle.List_MaxN(list);
	let cur = root;
	for (let i = 1; i <= list_len - 1; i += 1) {
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
	let ends = ALittle.String_Byte(path, ALittle.String_Len(path));
	if (ends === 47 || ends === 92) {
		path = ALittle.String_Sub(path, 1, ALittle.String_Len(path) - 1);
	}
	let list = ALittle.String_SplitSepList(path, ["/", "\\"]);
	let list_len = ALittle.List_MaxN(list);
	let cur = root;
	for (let i = 1; i <= list_len - 1; i += 1) {
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
		attr.size = ALittle.String_Len(cur_file.content);
	}
	return attr;
}

JavaScript.File_GetFileAttrByDir = function(path, file_map) {
	let ends = ALittle.String_Byte(path, ALittle.String_Len(path));
	if (ends === 47 || ends === 92) {
		path = ALittle.String_Sub(path, 1, ALittle.String_Len(path) - 1);
	}
	if (file_map === undefined) {
		file_map = {};
	}
	let list = ALittle.String_SplitSepList(path, ["/", "\\"]);
	let cur = root;
	let dir = "";
	let ___OBJECT_2 = list;
	for (let index = 1; index <= ___OBJECT_2.length; ++index) {
		let name = ___OBJECT_2[index - 1];
		if (name === undefined) break;
		let file = cur.file[name];
		if (file === undefined) {
			return file_map;
		}
		if (!file.is_directory) {
			return file_map;
		}
		cur = file;
		dir = dir + "/" + file.name;
	}
	cur_dir = dir;
	if (ALittle.String_Len(cur_dir) > 0) {
		cur_dir = cur_dir + "/";
	}
	if (cur.file === undefined) {
		return file_map;
	}
	let ___OBJECT_3 = cur.file;
	for (let name in ___OBJECT_3) {
		let value = ___OBJECT_3[name];
		if (value === undefined) continue;
		let file_path = cur_dir + name;
		if (value.is_directory) {
			JavaScript.File_GetFileAttrByDir(file_path, file_map);
		} else {
			let attr = {};
			attr.mode = "file";
			attr.size = 0;
			if (value.is_directory) {
				attr.mode = "directory";
			} else {
				attr.size = ALittle.String_Len(value.content);
			}
			file_map[file_path] = attr;
		}
	}
	return file_map;
}

JavaScript.File_DeleteDir = function(path) {
	let ends = ALittle.String_Byte(path, ALittle.String_Len(path));
	if (ends === 47 || ends === 92) {
		path = ALittle.String_Sub(path, 1, ALittle.String_Len(path) - 1);
	}
	let list = ALittle.String_SplitSepList(path, ["/", "\\"]);
	let cur = root;
	let ___OBJECT_4 = list;
	for (let index = 1; index <= ___OBJECT_4.length; ++index) {
		let name = ___OBJECT_4[index - 1];
		if (name === undefined) break;
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
		let ___OBJECT_5 = cur.file;
		for (let index in ___OBJECT_5) {
			let value = ___OBJECT_5[index];
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
	let ends = ALittle.String_Byte(path, ALittle.String_Len(path));
	if (ends === 47 || ends === 92) {
		path = ALittle.String_Sub(path, 1, ALittle.String_Len(path) - 1);
	}
	if (log_path) {
		let file_map = JavaScript.File_GetFileAttrByDir(path);
		let ___OBJECT_6 = file_map;
		for (let file_path in ___OBJECT_6) {
			let attr = ___OBJECT_6[file_path];
			if (attr === undefined) continue;
			ALittle.Log("delete file:", file_path);
		}
	}
	let list = ALittle.String_SplitSepList(path, ["/", "\\"]);
	let cur = root;
	let ___OBJECT_7 = list;
	for (let index = 1; index <= ___OBJECT_7.length; ++index) {
		let name = ___OBJECT_7[index - 1];
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
	let ends = ALittle.String_Byte(path, ALittle.String_Len(path));
	if (ends === 47 || ends === 92) {
		path = ALittle.String_Sub(path, 1, ALittle.String_Len(path) - 1);
	}
	let list = ALittle.String_SplitSepList(path, ["/", "\\"]);
	let list_len = ALittle.List_MaxN(list);
	let cur = root;
	for (let i = 1; i <= list_len - 1; i += 1) {
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
	file.parent = cur_file;
	return true;
}

JavaScript.File_LoadFile = function(path) {
	let list = ALittle.String_SplitSepList(path, ["/", "\\"]);
	let list_len = ALittle.List_MaxN(list);
	let cur = root;
	for (let i = 1; i <= list_len - 1; i += 1) {
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
	if (cur_file === undefined || cur_file.is_directory) {
		return undefined;
	}
	return cur_file.content;
}

JavaScript.File_SaveFile = function(path, content) {
	let list = ALittle.String_SplitSepList(path, ["/", "\\"]);
	let list_len = ALittle.List_MaxN(list);
	let cur = root;
	for (let i = 1; i <= list_len - 1; i += 1) {
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
	let file = {};
	file.content = content;
	file.is_directory = false;
	file.name = list[list_len - 1];
	file.parent = cur;
	cur.file[list[list_len - 1]] = file;
	return true;
}

}