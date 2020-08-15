{
if (typeof ALittle === "undefined") window.ALittle = {};


let __all_name_struct = {};
let __all_id_struct = new Map();
ALittle.RegStruct = function(hash, name, info) {
	if (__all_name_struct[name] !== undefined) {
		return;
	}
	let old_info = __all_id_struct.get(hash);
	if (old_info !== undefined) {
		throw new Error("RegReflect 名字为" + name + "和名字为" + old_info.name + "哈希值冲突, 请为" + name + "修改名字来避开冲突！");
	}
	__all_name_struct[name] = info;
	__all_id_struct.set(hash, info);
}

ALittle.FindStructByName = function(name) {
	return __all_name_struct[name];
}

ALittle.FindStructById = function(id) {
	return __all_id_struct.get(id);
}

ALittle.GetAllStruct = function() {
	return __all_id_struct;
}

}