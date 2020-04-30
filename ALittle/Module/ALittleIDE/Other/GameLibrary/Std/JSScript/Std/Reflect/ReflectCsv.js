{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(-1155101349, "ALittle.CsvInvokeInfo", {
name : "ALittle.CsvInvokeInfo", ns_name : "ALittle", rl_name : "CsvInvokeInfo", hash_code : -1155101349,
name_list : ["func","var_name","split","sub_info","handle"],
type_list : ["Functor<(string,ALittle.CsvInvokeInfo):any>","string","string","ALittle.CsvInvokeInfo","List<ALittle.CsvInvokeInfo>"],
option_map : {}
})

let floor = ALittle.Math_Floor;
let tonumber = ALittle.Math_ToDouble;
let maxn = ALittle.List_MaxN;
let upper = ALittle.String_Upper;
let Csv_ReadBool = function(content, value) {
	return upper(content) === "TRUE";
}

let Csv_ReadInt = function(content, value) {
	if (content === "") {
		return 0;
	}
	return floor(tonumber(content));
}

let Csv_ReadLong = function(content, value) {
	if (content === "") {
		return 0;
	}
	return floor(tonumber(content));
}

let Csv_ReadString = function(content, value) {
	return content;
}

let Csv_ReadDouble = function(content, value) {
	if (content === "") {
		return 0;
	}
	return tonumber(content);
}

let Csv_ReadArray = function(content, value) {
	let list = ALittle.String_Split(content, value.split);
	let result = [];
	let ___OBJECT_1 = list;
	for (let index = 1; index <= ___OBJECT_1.length; ++index) {
		let sub = ___OBJECT_1[index - 1];
		if (sub === undefined) break;
		let v = value.sub_info.func(sub, value.sub_info);
		if (v === undefined) {
			return undefined;
		}
		result[index - 1] = v;
	}
	return result;
}

ALittle.Csv_ReadMessage = function(content, value) {
	let list = ALittle.String_Split(content, value.split);
	let t = {};
	let ___OBJECT_2 = value.handle;
	for (let index = 1; index <= ___OBJECT_2.length; ++index) {
		let handle = ___OBJECT_2[index - 1];
		if (handle === undefined) break;
		t[handle.var_name] = handle.func(list[index - 1], handle);
	}
	return t;
}

let __csv_read_data_map = {};
__csv_read_data_map["bool"] = Csv_ReadBool;
__csv_read_data_map["int"] = Csv_ReadInt;
__csv_read_data_map["long"] = Csv_ReadLong;
__csv_read_data_map["string"] = Csv_ReadString;
__csv_read_data_map["double"] = Csv_ReadDouble;
let __split_list = ["*", "#", ";"];
let __split_list_last = __split_list[maxn(__split_list) - 1];
let __split_list_max = maxn(__split_list);
let find = ALittle.String_Find;
let sub = ALittle.String_Sub;
ALittle.CalcCsvSubInfoSplit = function(sub_type, split_index) {
	if (find(sub_type, "List<") === 1) {
		return ALittle.CalcCsvSubInfoSplit(sub(sub_type, 6, -2), split_index + 1);
	}
	if (find(sub_type, "Map<") === 1) {
		throw new Error("不支持Map解析");
	}
	let func = __csv_read_data_map[sub_type];
	if (func !== undefined) {
		return split_index;
	}
	return ALittle.CalcCsvInfoSplitImpl(sub_type, split_index + 1);
}

ALittle.CalcCsvInfoSplitImpl = function(var_type, split_index) {
	let rflt = ALittle.FindStructByName(var_type);
	JavaScript.Assert(rflt !== undefined, "FindReflectByName调用失败! 未知类型:" + var_type);
	let max_count = split_index;
	let ___OBJECT_3 = rflt.name_list;
	for (let index = 1; index <= ___OBJECT_3.length; ++index) {
		let var_name = ___OBJECT_3[index - 1];
		if (var_name === undefined) break;
		let count = ALittle.CalcCsvSubInfoSplit(rflt.type_list[index - 1], split_index);
		if (max_count < count) {
			max_count = count;
		}
	}
	return max_count;
}

ALittle.CalcCsvInfoSplit = function(rflt) {
	let max_count = 0;
	let ___OBJECT_4 = rflt.name_list;
	for (let index = 1; index <= ___OBJECT_4.length; ++index) {
		let var_name = ___OBJECT_4[index - 1];
		if (var_name === undefined) break;
		let count = ALittle.CalcCsvSubInfoSplit(rflt.type_list[index - 1], 0);
		if (max_count < count) {
			max_count = count;
		}
	}
	return max_count;
}

ALittle.CreateCsvSubInfo = function(sub_type, split_index) {
	let func = __csv_read_data_map[sub_type];
	if (func !== undefined) {
		let sub_info = {};
		sub_info.func = func;
		return sub_info;
	}
	if (find(sub_type, "List<") === 1) {
		return ALittle.CreateCsvArrayInfo(sub_type, split_index);
	}
	if (find(sub_type, "Map<") === 1) {
		throw new Error("不支持Map解析");
	}
	return ALittle.CreateCsvInfoImpl(sub_type, split_index);
}

ALittle.CreateCsvArrayInfo = function(var_type, split_index) {
	JavaScript.Assert(split_index > 0, "分隔符数量不足");
	let invoke_info = {};
	invoke_info.func = Csv_ReadArray;
	invoke_info.split = __split_list[split_index - 1];
	invoke_info.sub_info = ALittle.CreateCsvSubInfo(sub(var_type, 6, -2), split_index - 1);
	return invoke_info;
}

ALittle.CreateCsvInfoImpl = function(var_type, split_index) {
	JavaScript.Assert(split_index > 0, "分隔符数量不足");
	let rflt = ALittle.FindStructByName(var_type);
	JavaScript.Assert(rflt, "FindReflectByName调用失败! 未知类型:" + var_type);
	let invoke_info = {};
	invoke_info.split = __split_list[split_index - 1];
	invoke_info.func = ALittle.Csv_ReadMessage;
	let handle = [];
	invoke_info.handle = handle;
	let handle_count = 0;
	let ___OBJECT_5 = rflt.name_list;
	for (let index = 1; index <= ___OBJECT_5.length; ++index) {
		let var_name = ___OBJECT_5[index - 1];
		if (var_name === undefined) break;
		let var_info = ALittle.CreateCsvSubInfo(rflt.type_list[index - 1], split_index - 1);
		var_info.var_name = var_name;
		handle_count = handle_count + 1;
		handle[handle_count - 1] = var_info;
	}
	return invoke_info;
}

ALittle.CreateCsvInfo = function(rflt) {
	let split_index = ALittle.CalcCsvInfoSplit(rflt);
	let invoke_info = {};
	invoke_info.split = __split_list[split_index - 1];
	invoke_info.func = ALittle.Csv_ReadMessage;
	let handle = [];
	invoke_info.handle = handle;
	let handle_count = 0;
	let ___OBJECT_6 = rflt.name_list;
	for (let index = 1; index <= ___OBJECT_6.length; ++index) {
		let var_name = ___OBJECT_6[index - 1];
		if (var_name === undefined) break;
		let var_info = ALittle.CreateCsvSubInfo(rflt.type_list[index - 1], split_index);
		var_info.var_name = var_name;
		handle_count = handle_count + 1;
		handle[handle_count - 1] = var_info;
	}
	return invoke_info;
}

}