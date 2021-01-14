{


window.A_StdBasePath = undefined;
window.RequireStd = function(base_path) {
	return new Promise(async function(___COROUTINE, ___) {
		A_StdBasePath = base_path;
		await Require(base_path, "Cmd/ReflectCmd");
		await Require(base_path, "Config/ReflectCsv");
		await Require(base_path, "Net/ReflectMessage");
		await Require(base_path, "Loop/LoopObject");
		await Require(base_path, "Loop/ILoopSystem");
		await Require(base_path, "Loop/LoopFrame");
		await Require(base_path, "Loop/LoopFunction");
		await Require(base_path, "Loop/LoopGroup");
		await Require(base_path, "Loop/LoopList");
		await Require(base_path, "Loop/LoopTimer");
		await Require(base_path, "Config/CsvConfig");
		await Require(base_path, "Config/JsonConfig");
		await Require(base_path, "WeakRef/WeakRef");
		await Require(base_path, "Loop/IHeapTimer");
		await Require(base_path, "Schedule/ISchedule");
		await Require(base_path, "Utility/EventDispatcher");
		await Require(base_path, "Utility/SafeIDCreator");
		await Require(base_path, "String/String");
		await Require(base_path, "File/File");
		await Require(base_path, "Worker/Worker");
		await Require(base_path, "Net/HttpFileReceiverTemplate");
		await Require(base_path, "Net/HttpFileSenderTemplate");
		await Require(base_path, "Net/HttpReceiverTemplate");
		await Require(base_path, "Net/HttpSenderTemplate");
		await Require(base_path, "Net/MsgCommonTemplate");
		await Require(base_path, "Net/MsgReceiverTemplate");
		await Require(base_path, "Net/MsgSenderTemplate");
		await Require(base_path, "Net/MsgSessionTemplate");
		await Require(base_path, "Loop/JavaScript/JHeapTimer");
		await Require(base_path, "File/JavaScript/JFileSystem");
		await Require(base_path, "Net/JavaScript/JHttpFileInterface");
		await Require(base_path, "Net/JavaScript/JHttpFileWxInterface");
		await Require(base_path, "Net/JavaScript/JHttpInterface");
		await Require(base_path, "Net/JavaScript/JHttpWxInterface");
		await Require(base_path, "Net/JavaScript/JMessageFactory");
		await Require(base_path, "Net/JavaScript/JMsgInterface");
		await Require(base_path, "Schedule/JavaScript/JSchedule");
		await Require(base_path, "Config/JavaScript/JCsvFile");
		await Require(base_path, "../JSNative/md5.min");
		await Require(base_path, "../JSNative/native");
		await Require(base_path, "Loop/LoopSystem");
		await Require(base_path, "Schedule/Schedule");
		___COROUTINE();
	});
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(2073949729, "ALittle.CmdCallbackInfo", {
name : "ALittle.CmdCallbackInfo", ns_name : "ALittle", rl_name : "CmdCallbackInfo", hash_code : 2073949729,
name_list : ["callback","var_list","name_list","desc"],
type_list : ["Functor<(...)>","List<string>","List<string>","string"],
option_map : {}
})

let __all_callback = {};
ALittle.RegCmdCallback = function(method, callback, var_list, name_list, desc) {
	if (__all_callback[method] !== undefined) {
		ALittle.Error("RegCmdCallback消息回调函数注册失败，名字为" + method + "已存在");
		return;
	}
	let info = {};
	info.callback = callback;
	info.var_list = var_list;
	info.name_list = name_list;
	if (desc === undefined) {
		info.desc = "";
	} else {
		info.desc = desc;
	}
	__all_callback[method] = info;
}

ALittle.ExecuteCommand = function(cmd) {
	if (cmd === "") {
		ALittle.Warn("命令行是空");
		return;
	}
	let method = "";
	let param = "";
	let index = ALittle.String_Find(cmd, " ");
	if (index === undefined) {
		method = cmd;
		param = "";
	} else {
		method = ALittle.String_Sub(cmd, 1, index - 1);
		param = ALittle.String_Sub(cmd, index + 1);
	}
	if (ALittle.String_Upper(method) === "HELP") {
		let method_list = [];
		let ___OBJECT_1 = __all_callback;
		for (let method_name in ___OBJECT_1) {
			let info = ___OBJECT_1[method_name];
			if (info === undefined) continue;
			ALittle.List_Push(method_list, method_name);
		}
		ALittle.List_Sort(method_list);
		let out_list = [];
		ALittle.List_Push(out_list, "");
		ALittle.List_Push(out_list, "help 打印当前模块支持的指令列表");
		let ___OBJECT_2 = method_list;
		for (let _ = 1; _ <= ___OBJECT_2.length; ++_) {
			let method_name = ___OBJECT_2[_ - 1];
			if (method_name === undefined) break;
			let info = __all_callback[method_name];
			let detail = method_name + " ";
			let param_list = [];
			let ___OBJECT_3 = info.var_list;
			for (let i = 1; i <= ___OBJECT_3.length; ++i) {
				let v = ___OBJECT_3[i - 1];
				if (v === undefined) break;
				ALittle.List_Push(param_list, info.name_list[i - 1] + ":" + v);
			}
			detail = method_name + " " + ALittle.String_Join(param_list, ", ") + " " + info.desc;
			ALittle.List_Push(out_list, detail);
		}
		ALittle.Log(ALittle.String_Join(out_list, "\n"));
		return;
	}
	let info = __all_callback[method];
	if (info === undefined) {
		ALittle.Warn("未知指令:" + cmd);
		return;
	}
	let param_list = [];
	index = 1;
	let in_quote = false;
	let len = ALittle.String_Len(param);
	let i = 1;
	while (i <= len) {
		let byte = ALittle.String_Byte(param, i);
		if (byte === 32) {
			if (in_quote) {
				++ i;
			} else {
				if (index === i) {
					++ i;
					index = i;
				} else {
					ALittle.List_Push(param_list, ALittle.String_Sub(param, index, i - 1));
					++ i;
					index = i;
				}
			}
		} else if (byte === 34) {
			if (in_quote) {
				in_quote = false;
				if (index === i) {
					ALittle.List_Push(param_list, "");
					++ i;
					index = i;
				} else {
					ALittle.List_Push(param_list, ALittle.String_Sub(param, index, i - 1));
					++ i;
					index = i;
				}
			} else {
				in_quote = true;
				if (index !== i) {
					ALittle.List_Push(param_list, ALittle.String_Sub(param, index, i - 1));
					++ i;
					index = i;
				}
			}
		} else {
			++ i;
		}
	}
	if (index !== i) {
		ALittle.List_Push(param_list, ALittle.String_Sub(param, index, i - 1));
		++ i;
		index = i;
	}
	len = ALittle.List_Len(param_list);
	let need_len = ALittle.List_Len(info.var_list);
	if (len !== need_len) {
		ALittle.Warn("输入的参数数量" + len + "和指令要求" + need_len + "的不一致");
		return;
	}
	let value_list = [];
	let ___OBJECT_4 = param_list;
	for (let ii = 1; ii <= ___OBJECT_4.length; ++ii) {
		let _ = ___OBJECT_4[ii - 1];
		if (_ === undefined) break;
		let var_type = info.var_list[ii - 1];
		if (var_type === "int" || var_type === "long" || var_type === "double") {
			value_list[ii - 1] = ALittle.Math_ToDouble(param_list[ii - 1]);
			if (value_list[ii - 1] === undefined) {
				ALittle.Warn("输入的第" + ii + "个参数" + param_list[ii - 1] + "转为" + var_type + "失败");
				return;
			}
		} else if (var_type === "string") {
			value_list[ii - 1] = param_list[ii - 1];
		} else if (var_type === "bool") {
			if (param_list[ii - 1] === "true") {
				value_list[ii - 1] = true;
			} else if (param_list[ii - 1] === "false") {
				value_list[ii - 1] = false;
			} else {
				ALittle.Warn("输入的第" + ii + "个参数" + param_list[ii - 1] + "转为" + var_type + "失败");
				return;
			}
		} else {
			ALittle.Warn("输入的第" + ii + "个参数" + param_list[ii - 1] + "转为" + var_type + "失败，支持基本变量类型");
			return;
		}
	}
	info.callback.apply(undefined, value_list);
}

}
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
let list_len = ALittle.List_Len;
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
let __split_list_last = __split_list[list_len(__split_list) - 1];
let __split_list_max = list_len(__split_list);
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
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(1847150134, "ALittle.StructInfo", {
name : "ALittle.StructInfo", ns_name : "ALittle", rl_name : "StructInfo", hash_code : 1847150134,
name_list : ["name","ns_name","rl_name","hash_code","name_list","type_list","option_map"],
type_list : ["string","string","string","int","List<string>","List<string>","Map<string,string>"],
option_map : {}
})
ALittle.RegStruct(1821069430, "ALittle.ProtocolAnyStruct", {
name : "ALittle.ProtocolAnyStruct", ns_name : "ALittle", rl_name : "ProtocolAnyStruct", hash_code : 1821069430,
name_list : ["hash_code","value"],
type_list : ["int","any"],
option_map : {}
})
ALittle.RegStruct(-1602043290, "ALittle.ProtocolInvokeInfo", {
name : "ALittle.ProtocolInvokeInfo", ns_name : "ALittle", rl_name : "ProtocolInvokeInfo", hash_code : -1602043290,
name_list : ["wfunc","rfunc","rflt","var_name","key_info","value_info","sub_info","handle"],
type_list : ["Functor<(ALittle.IMessageWriteFactory,ALittle.ProtocolInvokeInfo,any,any):int>","Functor<(ALittle.IMessageReadFactory,ALittle.ProtocolInvokeInfo,any,int):any,int>","ALittle.StructInfo","string","ALittle.ProtocolInvokeInfo","ALittle.ProtocolInvokeInfo","ALittle.ProtocolInvokeInfo","List<ALittle.ProtocolInvokeInfo>"],
option_map : {}
})

let __all_name_invoke = {};
let __all_id_invoke = new Map();
let PS_WriteBool = function(factory, var_info, parent, var_value) {
	if (var_value === undefined) {
		return factory.WriteBool(false);
	}
	return factory.WriteBool(var_value);
}

let PS_WriteInt = function(factory, var_info, parent, var_value) {
	if (var_value === undefined) {
		return factory.WriteInt(0);
	}
	return factory.WriteInt(var_value);
}

let PS_WriteString = function(factory, var_info, parent, var_value) {
	if (var_value === undefined) {
		return factory.WriteString("");
	}
	return factory.WriteString(var_value);
}

let PS_WriteDouble = function(factory, var_info, parent, var_value) {
	if (var_value === undefined) {
		return factory.WriteDouble(0);
	}
	return factory.WriteDouble(var_value);
}

let PS_WriteLong = function(factory, var_info, parent, var_value) {
	if (var_value === undefined) {
		return factory.WriteLong(0);
	}
	return factory.WriteLong(var_value);
}

let PS_WriteArray = function(factory, var_info, parent, var_value) {
	if (var_value === undefined) {
		return factory.WriteInt(0);
	}
	let offset = factory.GetOffset();
	let l = factory.WriteInt(0);
	let sub_info = var_info.sub_info;
	let sub_func = sub_info.wfunc;
	let count = 0;
	let ___OBJECT_1 = var_value;
	for (let index = 1; index <= ___OBJECT_1.length; ++index) {
		let value = ___OBJECT_1[index - 1];
		if (value === undefined) break;
		l = l + sub_func(factory, sub_info, var_value, value);
		count = count + 1;
	}
	factory.SetInt(offset, count);
	return l;
}

let PS_WriteMap = function(factory, var_info, parent, var_value) {
	if (var_value === undefined) {
		return factory.WriteInt(0);
	}
	let offset = factory.GetOffset();
	let l = factory.WriteInt(0);
	let key_info = var_info.key_info;
	let key_func = key_info.wfunc;
	let value_info = var_info.value_info;
	let value_func = value_info.wfunc;
	let count = 0;
	if (key_func === PS_WriteString) {
		let ___OBJECT_2 = var_value;
		for (let key in ___OBJECT_2) {
			let value = ___OBJECT_2[key];
			if (value === undefined) continue;
			l = l + key_func(factory, key_info, var_value, key);
			l = l + value_func(factory, value_info, var_value, value);
			count = count + 1;
		}
	} else {
		for (let [key, value] of var_value) {
			if (value === undefined) continue;
			l = l + key_func(factory, key_info, var_value, key);
			l = l + value_func(factory, value_info, var_value, value);
			count = count + 1;
		}
	}
	factory.SetInt(offset, count);
	return l;
}

ALittle.PS_WriteMessage = function(factory, var_info, parent, var_value) {
	if (var_value === undefined) {
		let offset = factory.GetOffset();
		let pre_size = factory.WriteInt(0);
		let size = 0;
		let ___OBJECT_3 = var_info.handle;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let info = ___OBJECT_3[index - 1];
			if (info === undefined) break;
			size = size + info.wfunc(factory, info, var_value, undefined);
		}
		factory.SetInt(offset, size);
		return pre_size + size;
	}
	let offset = factory.GetOffset();
	let pre_size = factory.WriteInt(0);
	let size = 0;
	let ___OBJECT_4 = var_info.handle;
	for (let index = 1; index <= ___OBJECT_4.length; ++index) {
		let info = ___OBJECT_4[index - 1];
		if (info === undefined) break;
		size = size + info.wfunc(factory, info, var_value, var_value[info.var_name]);
	}
	factory.SetInt(offset, size);
	return pre_size + size;
}

ALittle.PS_WriteAny = function(factory, var_info, parent, var_value) {
	let invoke_info = ALittle.CreateProtocolInvokeInfo(parent.hash_code);
	return ALittle.PS_WriteMessage(factory, invoke_info, parent, var_value);
}

ALittle.PS_WriteMessageForSend = function(factory, var_info, parent, var_value) {
	if (var_value === undefined) {
		let offset = factory.GetOffset();
		let size = 0;
		let ___OBJECT_5 = var_info.handle;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let info = ___OBJECT_5[index - 1];
			if (info === undefined) break;
			size = size + info.wfunc(factory, info, var_value, undefined);
		}
		return size;
	}
	let offset = factory.GetOffset();
	let size = 0;
	let ___OBJECT_6 = var_info.handle;
	for (let index = 1; index <= ___OBJECT_6.length; ++index) {
		let info = ___OBJECT_6[index - 1];
		if (info === undefined) break;
		size = size + info.wfunc(factory, info, var_value, var_value[info.var_name]);
	}
	return size;
}

let PS_ReadBool = function(factory, var_info, parent, l) {
	if (l === 0) {
		return [false, 0];
	}
	if (l < 1) {
		return [false, -1];
	}
	return [factory.ReadBool(), 1];
}

let PS_ReadInt = function(factory, var_info, parent, l) {
	if (l === 0) {
		return [0, 0];
	}
	if (l < 4) {
		return [0, -1];
	}
	return [factory.ReadInt(), 4];
}

let PS_ReadString = function(factory, var_info, parent, l) {
	if (l === 0) {
		return ["", 0];
	}
	return [factory.ReadString(), factory.GetReadSize()];
}

let PS_ReadDouble = function(factory, var_info, parent, l) {
	if (l === 0) {
		return [0, 0];
	}
	if (l < 8) {
		return [0, -1];
	}
	return [factory.ReadDouble(), 8];
}

let PS_ReadLong = function(factory, var_info, parent, l) {
	if (l === 0) {
		return [0, 0];
	}
	if (l < 8) {
		return [0, -1];
	}
	return [factory.ReadLong(), 8];
}

let PS_ReadArray = function(factory, var_info, parent, l) {
	if (l === 0) {
		return [[], 0];
	}
	let save_len = l;
	if (l < 4) {
		return [undefined, -1];
	}
	let count = factory.ReadInt();
	l = l - 4;
	if (count < 0) {
		return [undefined, -1];
	}
	let sub_info = var_info.sub_info;
	let sub_func = sub_info.rfunc;
	let sub_len = 0;
	let value_list = [];
	for (let index = 1; index <= count; index += 1) {
		[value_list[index - 1], sub_len] = sub_func(factory, sub_info, value_list, l);
		if (sub_len < 0) {
			return [undefined, sub_len];
		}
		l = l - (sub_len);
	}
	return [value_list, save_len - l];
}

let PS_ReadMap = function(factory, var_info, parent, l) {
	if (l === 0) {
		if (var_info.key_info.rfunc === PS_ReadString) {
			return [{}, 0];
		} else {
			return [new Map(), 0];
		}
	}
	let save_len = l;
	if (l < 4) {
		return [undefined, -1];
	}
	let count = factory.ReadInt();
	l = l - 4;
	if (count < 0) {
		return [undefined, -1];
	}
	let key_info = var_info.key_info;
	let key_func = key_info.rfunc;
	let value_info = var_info.value_info;
	let value_func = value_info.rfunc;
	if (key_func === PS_ReadString) {
		let value_map = {};
		for (let index = 1; index <= count; index += 1) {
			let [key, key_len] = key_func(factory, key_info, value_map, l);
			if (key_len < 0) {
				return [undefined, key_len];
			}
			l = l - key_len;
			let [value, value_len] = value_func(factory, value_info, value_map, l);
			if (value_len < 0) {
				return [undefined, value_len];
			}
			l = l - value_len;
			value_map[key] = value;
		}
		return [value_map, save_len - l];
	} else {
		let value_map = new Map();
		for (let index = 1; index <= count; index += 1) {
			let [key, key_len] = key_func(factory, key_info, value_map, l);
			if (key_len < 0) {
				return [undefined, key_len];
			}
			l = l - key_len;
			let [value, value_len] = value_func(factory, value_info, value_map, l);
			if (value_len < 0) {
				return [undefined, value_len];
			}
			l = l - value_len;
			value_map.set(key, value);
		}
		return [value_map, save_len - l];
	}
}

ALittle.PS_ReadMessage = function(factory, var_info, parent, l) {
	if (l === 0) {
		let value_map = {};
		let sub_len = 0;
		let ___OBJECT_7 = var_info.handle;
		for (let index = 1; index <= ___OBJECT_7.length; ++index) {
			let info = ___OBJECT_7[index - 1];
			if (info === undefined) break;
			[value_map[info.var_name], sub_len] = info.rfunc(factory, info, value_map, 0);
		}
		return [value_map, 0];
	}
	if (l < 4) {
		return [undefined, -1];
	}
	let object_len = factory.ReadInt();
	l = l - 4;
	let save_len = 4;
	if (object_len > l) {
		return [undefined, -1];
	}
	save_len = save_len + object_len;
	let sub_len = 0;
	let value_map = {};
	let ___OBJECT_8 = var_info.handle;
	for (let index = 1; index <= ___OBJECT_8.length; ++index) {
		let info = ___OBJECT_8[index - 1];
		if (info === undefined) break;
		[value_map[info.var_name], sub_len] = info.rfunc(factory, info, value_map, object_len);
		if (sub_len < 0) {
			return [undefined, sub_len];
		}
		object_len = object_len - sub_len;
	}
	return [value_map, save_len];
}

ALittle.PS_ReadAny = function(factory, var_info, parent, l) {
	let invoke_info = ALittle.CreateProtocolInvokeInfo(parent.hash_code);
	return [ALittle.PS_ReadMessage(factory, invoke_info, parent, l)];
}

ALittle.PS_ReadMessageForReceive = function(factory, var_info, parent, l) {
	if (l === 0) {
		let value_map = {};
		let sub_len = 0;
		let ___OBJECT_9 = var_info.handle;
		for (let index = 1; index <= ___OBJECT_9.length; ++index) {
			let info = ___OBJECT_9[index - 1];
			if (info === undefined) break;
			[value_map[info.var_name], sub_len] = info.rfunc(factory, info, value_map, 0);
		}
		return [value_map, 0];
	}
	let sub_len = 0;
	let value_map = {};
	let ___OBJECT_10 = var_info.handle;
	for (let index = 1; index <= ___OBJECT_10.length; ++index) {
		let info = ___OBJECT_10[index - 1];
		if (info === undefined) break;
		[value_map[info.var_name], sub_len] = info.rfunc(factory, info, value_map, l);
		if (sub_len < 0) {
			return [undefined, sub_len];
		}
		l = l - sub_len;
	}
	return [value_map, l];
}

let __ps_write_data_map = {};
__ps_write_data_map["bool"] = PS_WriteBool;
__ps_write_data_map["int"] = PS_WriteInt;
__ps_write_data_map["long"] = PS_WriteLong;
__ps_write_data_map["string"] = PS_WriteString;
__ps_write_data_map["double"] = PS_WriteDouble;
__ps_write_data_map["any"] = ALittle.PS_WriteAny;
let __ps_read_data_map = {};
__ps_read_data_map["bool"] = PS_ReadBool;
__ps_read_data_map["int"] = PS_ReadInt;
__ps_read_data_map["long"] = PS_ReadLong;
__ps_read_data_map["string"] = PS_ReadString;
__ps_read_data_map["double"] = PS_ReadDouble;
__ps_read_data_map["any"] = ALittle.PS_ReadAny;
let find = ALittle.String_Find;
let sub = ALittle.String_Sub;
let len = ALittle.String_Len;
let byte = ALittle.String_Byte;
ALittle.CreateSubInfo = function(sub_type) {
	let wfunc = __ps_write_data_map[sub_type];
	if (wfunc !== undefined) {
		let sub_info = {};
		sub_info.wfunc = wfunc;
		sub_info.rfunc = __ps_read_data_map[sub_type];
		return sub_info;
	}
	if (find(sub_type, "List<") === 1) {
		return ALittle.CreateArrayInfo(sub_type);
	}
	if (find(sub_type, "Map<") === 1) {
		return ALittle.CreateMapInfo(sub_type);
	}
	return ALittle.CreateMessageInfo(sub_type);
}

ALittle.CreateArrayInfo = function(var_type) {
	let invoke_info = {};
	invoke_info.wfunc = PS_WriteArray;
	invoke_info.rfunc = PS_ReadArray;
	invoke_info.sub_info = ALittle.CreateSubInfo(sub(var_type, 6, -2));
	return invoke_info;
}

ALittle.CreateMapInfo = function(var_type) {
	let invoke_info = {};
	let sub_type = sub(var_type, 5, -2);
	let comma_index = 0;
	let sub_type_len = len(sub_type);
	let ltgt = 0;
	for (let i = 1; i <= sub_type_len; i += 1) {
		let code = byte(sub_type, i);
		if (code === 60) {
			ltgt = ltgt + 1;
		} else if (code === 62) {
			ltgt = ltgt - 1;
		} else if (code === 44) {
			if (ltgt === 0) {
				comma_index = i;
				break;
			}
		}
	}
	JavaScript.Assert(comma_index !== 0, "can'f find comma in var_type:" + var_type);
	invoke_info.wfunc = PS_WriteMap;
	invoke_info.rfunc = PS_ReadMap;
	invoke_info.key_info = ALittle.CreateSubInfo(sub(sub_type, 1, comma_index - 1));
	invoke_info.value_info = ALittle.CreateSubInfo(sub(sub_type, comma_index + 1));
	return invoke_info;
}

ALittle.CreateMessageInfo = function(var_type) {
	let invoke = __all_name_invoke[var_type];
	if (invoke !== undefined) {
		return invoke;
	}
	let rflt = ALittle.FindStructByName(var_type);
	JavaScript.Assert(rflt !== undefined, "FindReflect调用失败! 未知类型:" + var_type);
	invoke = ALittle.CreateMessageInfoImpl(rflt);
	__all_id_invoke.set(rflt.hash_code, invoke);
	__all_name_invoke[rflt.name] = invoke;
	return invoke;
}

ALittle.CreateMessageInfoImpl = function(rflt) {
	let invoke_info = {};
	invoke_info.wfunc = ALittle.PS_WriteMessage;
	invoke_info.rfunc = ALittle.PS_ReadMessage;
	invoke_info.rflt = rflt;
	let handle = [];
	invoke_info.handle = handle;
	let handle_count = 0;
	let ___OBJECT_11 = rflt.name_list;
	for (let index = 1; index <= ___OBJECT_11.length; ++index) {
		let var_name = ___OBJECT_11[index - 1];
		if (var_name === undefined) break;
		let var_info = ALittle.CreateSubInfo(rflt.type_list[index - 1]);
		var_info.var_name = var_name;
		handle_count = handle_count + 1;
		handle[handle_count - 1] = var_info;
	}
	return invoke_info;
}

ALittle.CreateProtocolInvokeInfo = function(msg_id) {
	let invoke = __all_id_invoke.get(msg_id);
	if (invoke !== undefined) {
		return invoke;
	}
	let rflt = ALittle.FindStructById(msg_id);
	JavaScript.Assert(rflt !== undefined, "FindReflect调用失败! 未知ID:" + msg_id);
	invoke = ALittle.CreateMessageInfoImpl(rflt);
	__all_id_invoke.set(rflt.hash_code, invoke);
	__all_name_invoke[rflt.name] = invoke;
	return invoke;
}

let CollectStructInfo = function(invoke, map) {
	if (invoke === undefined) {
		return;
	}
	if (invoke.rflt !== undefined) {
		if (map.get(invoke.rflt.hash_code) !== undefined) {
			return;
		}
		map.set(invoke.rflt.hash_code, invoke.rflt);
	}
	if (invoke.key_info !== undefined) {
		CollectStructInfo(invoke.key_info, map);
	}
	if (invoke.value_info !== undefined) {
		CollectStructInfo(invoke.value_info, map);
	}
	if (invoke.sub_info !== undefined) {
		CollectStructInfo(invoke.sub_info, map);
	}
	if (invoke.handle !== undefined) {
		let ___OBJECT_12 = invoke.handle;
		for (let index = 1; index <= ___OBJECT_12.length; ++index) {
			let info = ___OBJECT_12[index - 1];
			if (info === undefined) break;
			CollectStructInfo(info, map);
		}
	}
}

ALittle.CollectStructReflect = function(info, map) {
	if (info === undefined) {
		return "参数info是null";
	}
	let [error, invoke] = (function() { try { let ___VALUE = ALittle.CreateMessageInfoImpl.call(undefined, info); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } })();
	if (error !== undefined) {
		return error;
	}
	CollectStructInfo(invoke, map);
	return undefined;
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.LoopObject = JavaScript.Class(undefined, {
	IsCompleted : function() {
		return true;
	},
	Completed : function() {
	},
	Update : function(frame_time) {
	},
	Reset : function() {
	},
	SetTime : function(time) {
		return [time, true];
	},
	SetCompleted : function() {
	},
	Dispose : function(deep) {
		this.Stop();
	},
	Start : function() {
		A_JLoopSystem.AddUpdater(this);
	},
	Stop : function() {
		A_JLoopSystem.RemoveUpdater(this);
	},
}, "ALittle.LoopObject");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.ILoopSystem = JavaScript.Class(undefined, {
	Update : function(frame_time) {
	},
	Sleep : function(ms_time) {
		return new Promise((function(___COROUTINE, ___) {
			___COROUTINE();
		}).bind(this));
	},
	AddTimer : function(delay_ms, callback, loop, interval_ms) {
		return 0;
	},
	RemoveTimer : function(id) {
		return false;
	},
	AddUpdater : function(object) {
	},
	RemoveUpdater : function(object) {
	},
	HasUpdater : function(object) {
		return false;
	},
}, "ALittle.ILoopSystem");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.LoopObject === undefined) throw new Error(" extends class:ALittle.LoopObject is undefined");
ALittle.LoopFrame = JavaScript.Class(ALittle.LoopObject, {
	Ctor : function(func) {
		this._func = func;
		this._force_completed = false;
		if (this._func === undefined) {
			this._force_completed = true;
			ALittle.Log("LoopFrame create failed:function is nil or not a function");
			return;
		}
	},
	Reset : function() {
	},
	Completed : function() {
	},
	IsCompleted : function() {
		return this._force_completed;
	},
	SetCompleted : function() {
		this._force_completed = true;
	},
	SetTime : function(time) {
		return [time, true];
	},
	Update : function(frame_time) {
		this._func(frame_time);
	},
}, "ALittle.LoopFrame");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.LoopObject === undefined) throw new Error(" extends class:ALittle.LoopObject is undefined");
ALittle.LoopFunction = JavaScript.Class(ALittle.LoopObject, {
	Ctor : function(func, count, interval_time, delay_time) {
		this._func = func;
		this._total_count = count;
		this._force_completed = false;
		if (delay_time === undefined || delay_time < 0) {
			delay_time = 0;
		}
		if (interval_time < 0) {
			interval_time = 0;
		}
		this._total_interval_time = interval_time;
		this._total_delay_time = delay_time;
		this._accumulate_count = 0;
		this._accumulate_time = 0;
		this._accumulate_delay_time = 0;
		if (this._func === undefined) {
			this._accumulate_count = 0;
			this._total_count = 0;
			ALittle.Log("LoopFunction create failed:function is nil or not a function");
			return;
		}
		this._complete_callback = undefined;
	},
	get complete_callback() {
		return this._complete_callback;
	},
	set complete_callback(value) {
		this._complete_callback = value;
	},
	Reset : function() {
		this._accumulate_count = 0;
		this._accumulate_time = 0;
		this._accumulate_delay_time = 0;
	},
	Completed : function() {
		if (this._complete_callback !== undefined) {
			this._complete_callback();
		}
	},
	IsCompleted : function() {
		if (this._force_completed) {
			return true;
		}
		if (this._total_count < 0) {
			return false;
		}
		return this._total_count <= this._accumulate_count;
	},
	SetCompleted : function() {
		if (this._total_count < 0) {
			this._force_completed = true;
			return;
		}
		this._accumulate_count = this._total_count;
	},
	SetTime : function(time) {
		this._accumulate_count = 0;
		this._accumulate_delay_time = 0;
		this._accumulate_time = 0;
		if (time <= 0) {
			return [0, false];
		}
		if (this._total_count < 0) {
			return [0, false];
		}
		if (time <= this._total_delay_time) {
			this._accumulate_delay_time = time;
			return [0, false];
		}
		this._accumulate_delay_time = this._total_delay_time;
		time = time - (this._total_delay_time);
		let total_time = this._total_interval_time * this._total_count;
		if (time < total_time) {
			let float_count = total_time / this._total_interval_time;
			let count = ALittle.Math_Floor(float_count);
			this._accumulate_count = count;
			this._accumulate_time = ALittle.Math_Floor((float_count - count) * this._total_interval_time);
			return [0, false];
		}
		this._accumulate_count = this._total_count;
		return [time - total_time, true];
	},
	Update : function(frame_time) {
		if (this._accumulate_delay_time < this._total_delay_time) {
			this._accumulate_delay_time = this._accumulate_delay_time + (frame_time);
			if (this._accumulate_delay_time < this._total_delay_time) {
				return;
			}
			frame_time = this._accumulate_delay_time - this._total_delay_time;
			this._accumulate_delay_time = this._total_delay_time;
		}
		this._accumulate_time = this._accumulate_time + (frame_time);
		if (this._accumulate_time > this._total_interval_time) {
			this._accumulate_time = 0;
			++ this._accumulate_count;
			this._func();
		}
	},
}, "ALittle.LoopFunction");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.LoopObject === undefined) throw new Error(" extends class:ALittle.LoopObject is undefined");
ALittle.LoopGroup = JavaScript.Class(ALittle.LoopObject, {
	Ctor : function() {
		this._total_count = 0;
		this._complete_count = 0;
		this._loop_updaters = new Map();
		this._complete_updaters = new Map();
		this._complete_callback = undefined;
	},
	get complete_callback() {
		return this._complete_callback;
	},
	set complete_callback(value) {
		this._complete_callback = value;
	},
	get total_count() {
		return this._total_count;
	},
	AddUpdater : function(value) {
		if (value === undefined) {
			return;
		}
		if (this._complete_updaters.get(value) || this._loop_updaters.get(value)) {
			return;
		}
		this._loop_updaters.set(value, true);
		++ this._total_count;
	},
	RemoveUpdater : function(value) {
		if (this._loop_updaters.get(value)) {
			this._loop_updaters.delete(value);
			-- this._total_count;
			return;
		}
		if (this._complete_updaters.get(value)) {
			this._complete_updaters.delete(value);
			-- this._total_count;
			-- this._complete_count;
		}
	},
	Reset : function() {
		this._complete_count = 0;
		for (let [updater, v] of this._loop_updaters) {
			if (v === undefined) continue;
			updater.Reset();
		}
		for (let [updater, v] of this._complete_updaters) {
			if (v === undefined) continue;
			this._loop_updaters.set(updater, true);
			updater.Reset();
		}
	},
	SetTime : function(time) {
		if (this._total_count === 0) {
			return [time, true];
		}
		let total_updater = new Map();
		for (let [updater, v] of this._loop_updaters) {
			if (v === undefined) continue;
			total_updater.set(updater, true);
		}
		for (let [updater, v] of this._complete_updaters) {
			if (v === undefined) continue;
			total_updater.set(updater, true);
		}
		this._loop_updaters = new Map();
		this._complete_updaters = new Map();
		this._complete_count = 0;
		let min_time = undefined;
		for (let [updater, v] of total_updater) {
			if (v === undefined) continue;
			let [remain_time, completed] = updater.SetTime(time);
			if (completed) {
				this._complete_updaters.set(updater, true);
				++ this._complete_count;
			} else {
				this._loop_updaters.set(updater, true);
			}
			if (min_time === undefined || min_time > remain_time) {
				min_time = remain_time;
			}
		}
		return [min_time, this._complete_count === this._total_count];
	},
	IsCompleted : function() {
		return this._complete_count >= this._total_count;
	},
	Completed : function() {
		if (this._complete_callback !== undefined) {
			this._complete_callback();
		}
	},
	SetCompleted : function() {
		this._complete_count = this._total_count;
		for (let [updater, v] of this._loop_updaters) {
			if (v === undefined) continue;
			updater.SetCompleted();
			this._complete_updaters.set(updater, true);
		}
		this._loop_updaters = new Map();
	},
	Update : function(frame_time) {
		if (this._complete_count >= this._total_count) {
			return;
		}
		let remove_map = new Map();
		for (let [updater, v] of this._loop_updaters) {
			if (v === undefined) continue;
			if (updater.IsCompleted()) {
				remove_map.set(updater, true);
			} else {
				updater.Update(frame_time);
			}
		}
		for (let [updater, v] of remove_map) {
			if (v === undefined) continue;
			this._loop_updaters.delete(updater);
			this._complete_updaters.set(updater, true);
			++ this._complete_count;
			updater.Completed();
		}
	},
}, "ALittle.LoopGroup");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.LoopObject === undefined) throw new Error(" extends class:ALittle.LoopObject is undefined");
ALittle.LoopList = JavaScript.Class(ALittle.LoopObject, {
	Ctor : function() {
		this._count = 0;
		this._cur_index = 1;
		this._update_list = [];
		this._complete_callback = undefined;
	},
	get complete_callback() {
		return this._complete_callback;
	},
	set complete_callback(value) {
		this._complete_callback = value;
	},
	get total_count() {
		return this._count;
	},
	AddUpdater : function(value) {
		if (value === undefined) {
			return;
		}
		++ this._count;
		this._update_list[this._count - 1] = value;
	},
	RemoveUpdater : function(value) {
		if (value === undefined || this._count === 0) {
			return;
		}
		let ___OBJECT_1 = this._update_list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let updater = ___OBJECT_1[index - 1];
			if (updater === undefined) break;
			if (value === updater) {
				if (this._cur_index > index) {
					-- this._cur_index;
				}
				ALittle.List_Remove(this._update_list, index);
				-- this._count;
				break;
			}
		}
	},
	Reset : function() {
		this._cur_index = 1;
		let ___OBJECT_2 = this._update_list;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let updater = ___OBJECT_2[index - 1];
			if (updater === undefined) break;
			updater.Reset();
		}
	},
	SetTime : function(time) {
		let ___OBJECT_3 = this._update_list;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let updater = ___OBJECT_3[index - 1];
			if (updater === undefined) break;
			updater.SetTime(0);
		}
		this._cur_index = 1;
		if (time <= 0) {
			return [0, false];
		}
		let ___OBJECT_4 = this._update_list;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let updater = ___OBJECT_4[index - 1];
			if (updater === undefined) break;
			let completed = undefined;
			[time, completed] = updater.SetTime(time);
			if (!completed) {
				this._cur_index = index;
				return [0, false];
			}
		}
		this._cur_index = this._count + 1;
		return [time, true];
	},
	IsCompleted : function() {
		return this._cur_index > this._count;
	},
	Completed : function() {
		if (this._complete_callback !== undefined) {
			this._complete_callback();
		}
	},
	SetCompleted : function() {
		for (let index = this._cur_index; index <= this._count; index += 1) {
			this._update_list[index - 1].SetCompleted();
		}
		this._cur_index = this._count + 1;
	},
	Update : function(frame_time) {
		if (this._cur_index > this._count) {
			return;
		}
		let updater = this._update_list[this._cur_index - 1];
		updater.Update(frame_time);
		if (updater.IsCompleted()) {
			++ this._cur_index;
			updater.Completed();
		}
	},
}, "ALittle.LoopList");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.LoopObject === undefined) throw new Error(" extends class:ALittle.LoopObject is undefined");
ALittle.LoopTimer = JavaScript.Class(ALittle.LoopObject, {
	Ctor : function(func, delay_time) {
		this._func = func;
		if (delay_time === undefined || delay_time < 0) {
			delay_time = 0;
		}
		this._total_delay_time = delay_time;
		this._accumulate_count = 0;
		this._accumulate_delay_time = 0;
		if (this._func === undefined) {
			this._accumulate_count = 1;
			this._accumulate_delay_time = this._total_delay_time;
			ALittle.Log("LoopTimer create failed:function is nil or not a function");
			return;
		}
		this._complete_callback = undefined;
	},
	get complete_callback() {
		return this._complete_callback;
	},
	set complete_callback(value) {
		this._complete_callback = value;
	},
	Reset : function() {
		this._accumulate_count = 0;
		this._accumulate_delay_time = 0;
	},
	Completed : function() {
		if (this._complete_callback !== undefined) {
			this._complete_callback();
		}
	},
	IsCompleted : function() {
		return this._accumulate_count >= 1;
	},
	SetCompleted : function() {
		if (this._accumulate_count >= 1) {
			return;
		}
		this._accumulate_count = 1;
		this._accumulate_delay_time = this._total_delay_time;
		this._func();
	},
	SetTime : function(time) {
		this._accumulate_count = 0;
		this._accumulate_delay_time = 0;
		if (time <= 0) {
			return [0, false];
		}
		if (time <= this._total_delay_time) {
			this._accumulate_delay_time = time;
			return [0, false];
		}
		this._accumulate_delay_time = this._total_delay_time;
		this._accumulate_count = 1;
		this._func();
		return [time - this._total_delay_time, true];
	},
	Update : function(frame_time) {
		if (this._accumulate_delay_time < this._total_delay_time) {
			this._accumulate_delay_time = this._accumulate_delay_time + (frame_time);
			if (this._accumulate_delay_time < this._total_delay_time) {
				return;
			}
			this._accumulate_delay_time = this._total_delay_time;
		}
		if (this._accumulate_count >= 1) {
			return;
		}
		this._accumulate_count = 1;
		this._func();
	},
}, "ALittle.LoopTimer");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(115253948, "ALittle.KeyValueInfo", {
name : "ALittle.KeyValueInfo", ns_name : "ALittle", rl_name : "KeyValueInfo", hash_code : 115253948,
name_list : ["key","value"],
type_list : ["string","string"],
option_map : {}
})

ALittle.ICsvFile = JavaScript.Class(undefined, {
	Close : function() {
	},
	ReadCell : function(row, col) {
		return "";
	},
	GetRowCount : function() {
		return 0;
	},
	GetColCount : function() {
		return 0;
	},
}, "ALittle.ICsvFile");

ALittle.ICsvFileLoader = JavaScript.Class(undefined, {
	Start : function() {
	},
	SetPath : function(file_path, only_from_asset) {
	},
	GetPath : function() {
		return undefined;
	},
	GetID : function() {
		return undefined;
	},
}, "ALittle.ICsvFileLoader");

ALittle.CsvConfig = JavaScript.Class(undefined, {
	Load : function(file_path) {
		let js_file = ALittle.NewObject(JavaScript.JCsvFile);
		JavaScript.Assert(js_file.Load(file_path), file_path + " load failed!");
		this.Init(js_file);
		ALittle.Log(file_path + " load succeed!");
	},
	Init : function(file) {
	},
}, "ALittle.CsvConfig");

if (ALittle.CsvConfig === undefined) throw new Error(" extends class:ALittle.CsvConfig is undefined");
ALittle.KeyValueConfig = JavaScript.Class(ALittle.CsvConfig, {
	Ctor : function() {
		this._data = {};
		this._csv_info = ALittle.CreateCsvInfo(this.__class.__element[0]);
	},
	Init : function(file) {
		if (file === undefined) {
			return;
		}
		let reflt = this.__class.__element[0];
		let handle_map = {};
		let ___OBJECT_1 = this._csv_info.handle;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let handle = ___OBJECT_1[index - 1];
			if (handle === undefined) break;
			handle_map[handle.var_name] = handle;
		}
		let row_count = file.GetRowCount();
		for (let row = 1; row <= row_count; row += 1) {
			let key = file.ReadCell(row, 1);
			let value = file.ReadCell(row, 2);
			if (key !== undefined && value !== undefined) {
				let handle = handle_map[key];
				if (handle !== undefined) {
					let hvalue = handle.func(value, handle);
					if (hvalue !== undefined) {
						this._data[key] = hvalue;
					} else {
						ALittle.Error("key:" + key + " load failed!");
					}
				}
			}
		}
		file.Close();
	},
	GetFieldNameList : function() {
		let rflt = ___all_struct.get(115253948);
		return rflt.name_list;
	},
	GetData : function() {
		return this._data;
	},
}, "ALittle.KeyValueConfig");

if (ALittle.CsvConfig === undefined) throw new Error(" extends class:ALittle.CsvConfig is undefined");
ALittle.CsvTableConfig = JavaScript.Class(ALittle.CsvConfig, {
	Ctor : function() {
		let error = undefined;
		[error, this._csv_info] = (function() { try { let ___VALUE = ALittle.CreateCsvInfo.call(undefined, this.__class.__element[0]); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
		if (error !== undefined) {
			ALittle.Error(error);
		}
		this._col_map = new Map();
	},
	Init : function(file) {
		if (this._csv_file !== undefined) {
			this._csv_file.Close();
		}
		this._csv_file = file;
		if (this._csv_file === undefined) {
			return;
		}
		let rflt = this.__class.__element[0];
		let name_map = {};
		let ___OBJECT_2 = rflt.name_list;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let name = ___OBJECT_2[index - 1];
			if (name === undefined) break;
			name_map[name] = index;
		}
		for (let i = 1; i <= this._csv_file.GetColCount(); i += 1) {
			let name = this._csv_file.ReadCell(1, i);
			let index = name_map[name];
			if (index !== undefined) {
				this._col_map.set(index, i);
			}
		}
		this.onInit();
	},
	onInit : function() {
	},
	LoadCell : function(row) {
		let value = {};
		let ___OBJECT_3 = this._csv_info.handle;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let handle = ___OBJECT_3[index - 1];
			if (handle === undefined) break;
			let real = this._col_map.get(index);
			if (real === undefined) {
				value[handle.var_name] = handle.func("", handle);
			} else {
				let read = this._csv_file.ReadCell(row, real);
				if (read === undefined) {
					value[handle.var_name] = handle.func("", handle);
				} else {
					value[handle.var_name] = handle.func(read, handle);
				}
			}
		}
		return value;
	},
}, "ALittle.CsvTableConfig");

if (ALittle.CsvTableConfig === undefined) throw new Error(" extends class:ALittle.CsvTableConfig is undefined");
ALittle.SingleKeyTableConfig = JavaScript.Class(ALittle.CsvTableConfig, {
	Ctor : function() {
		this._key_map = new Map();
		this._cache_map = new Map();
	},
	onInit : function() {
		let rflt = this.__class.__element[0];
		let key_type = rflt.type_list[1 - 1];
		let key_index = this._col_map.get(1);
		let is_int = key_type === "int" || key_type === "long";
		let is_double = key_type === "double";
		let row_count = this._csv_file.GetRowCount();
		for (let row = 2; row <= row_count; row += 1) {
			let value = this._csv_file.ReadCell(row, key_index);
			if (value !== undefined) {
				if (is_int) {
					this._key_map.set(ALittle.Math_ToInt(value), row);
				} else if (is_double) {
					this._key_map.set(ALittle.Math_ToDouble(value), row);
				} else {
					this._key_map.set(value, row);
				}
			}
		}
	},
	GetData : function(key) {
		if (this._csv_file === undefined) {
			return undefined;
		}
		let value = this._cache_map.get(key);
		if (value !== undefined) {
			return value;
		}
		let row = this._key_map.get(key);
		if (row === undefined) {
			return undefined;
		}
		value = this.LoadCell(row);
		if (value === undefined) {
			return undefined;
		}
		this._cache_map.set(key, value);
		return value;
	},
}, "ALittle.SingleKeyTableConfig");

if (ALittle.CsvTableConfig === undefined) throw new Error(" extends class:ALittle.CsvTableConfig is undefined");
ALittle.DoubleKeyTableConfig = JavaScript.Class(ALittle.CsvTableConfig, {
	Ctor : function() {
		this._key_map = new Map();
		this._cache_map = new Map();
	},
	onInit : function() {
		let rflt = this.__class.__element[0];
		let first_key_type = rflt.type_list[1 - 1];
		let first_key_index = this._col_map.get(1);
		let first_is_int = first_key_type === "int" || first_key_type === "long";
		let first_is_double = first_key_type === "double";
		let second_key_type = rflt.type_list[2 - 1];
		let second_key_index = this._col_map.get(2);
		let second_is_int = second_key_type === "int" || second_key_type === "long";
		let second_is_double = second_key_type === "double";
		let row_count = this._csv_file.GetRowCount();
		for (let row = 2; row <= row_count; row += 1) {
			let tmp = undefined;
			let value = this._csv_file.ReadCell(row, first_key_index);
			if (value !== undefined) {
				if (first_is_int) {
					tmp = this._key_map.get(ALittle.Math_ToInt(value));
					if (tmp === undefined) {
						tmp = new Map();
						this._key_map.set(ALittle.Math_ToInt(value), tmp);
					}
				} else if (first_is_double) {
					tmp = this._key_map.get(ALittle.Math_ToDouble(value));
					if (tmp === undefined) {
						tmp = new Map();
						this._key_map.set(ALittle.Math_ToDouble(value), tmp);
					}
				} else {
					tmp = this._key_map.get(value);
					if (tmp === undefined) {
						tmp = new Map();
						this._key_map.set(value, tmp);
					}
				}
			}
			if (tmp === undefined) {
				continue;
			}
			value = this._csv_file.ReadCell(row, second_key_index);
			if (value !== undefined) {
				if (second_is_int) {
					tmp.set(ALittle.Math_ToInt(value), row);
				} else if (second_is_double) {
					tmp.set(ALittle.Math_ToDouble(value), row);
				} else {
					tmp.set(value, row);
				}
			}
		}
	},
	GetData : function(first_key, second_key) {
		if (this._csv_file === undefined) {
			return undefined;
		}
		let value_map = this._cache_map.get(first_key);
		if (value_map !== undefined) {
			let value = value_map.get(second_key);
			if (value !== undefined) {
				return value;
			}
		}
		let key_tmp = this._key_map.get(first_key);
		if (key_tmp === undefined) {
			return undefined;
		}
		let row = key_tmp.get(second_key);
		if (row === undefined) {
			return undefined;
		}
		let value = this.LoadCell(row);
		if (value === undefined) {
			return undefined;
		}
		let tmp = this._cache_map.get(first_key);
		if (tmp === undefined) {
			tmp = new Map();
			this._cache_map.set(first_key, tmp);
		}
		tmp.set(second_key, value);
		return value;
	},
}, "ALittle.DoubleKeyTableConfig");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IJsonConfig = JavaScript.Class(undefined, {
	GetConfig : function(key, defaultv) {
		return defaultv;
	},
	GetBool : function(key, defaultv) {
		return defaultv;
	},
	GetInt : function(key, defaultv) {
		return defaultv;
	},
	GetDouble : function(key, defaultv) {
		return defaultv;
	},
	GetString : function(key, defaultv) {
		return defaultv;
	},
	SetConfig : function(key, value, not_save) {
	},
	CoverConfig : function(msg, save) {
	},
	SaveConfig : function() {
	},
}, "ALittle.IJsonConfig");

if (ALittle.IJsonConfig === undefined) throw new Error(" extends class:ALittle.IJsonConfig is undefined");
ALittle.JsonConfig = JavaScript.Class(ALittle.IJsonConfig, {
	Ctor : function(file_path, print_error) {
		this._file_path = file_path;
		this._config_map = {};
		let file = ALittle.NewObject(this.__class.__element[0]);
		let content = file.Load(this._file_path);
		if (content === undefined) {
			if (print_error) {
				ALittle.Error("config load failed." + file_path);
			}
			return;
		}
		let [error, json_content] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
		if (error !== undefined) {
			ALittle.Log("Json Decode failed." + file_path + ", " + error);
			return;
		}
		this._config_map = json_content;
	},
	GetConfig : function(key, defaultv) {
		let value = this._config_map[key];
		if (value === undefined) {
			return defaultv;
		}
		return value;
	},
	GetBool : function(key, defaultv) {
		let value = this.GetConfig(key, defaultv);
		return value !== undefined && value !== false;
	},
	GetInt : function(key, defaultv) {
		let value = this.GetConfig(key, defaultv);
		if (value === undefined) {
			value = 0;
		}
		return value;
	},
	GetDouble : function(key, defaultv) {
		let value = this.GetConfig(key, defaultv);
		if (value === undefined) {
			value = 0;
		}
		return value;
	},
	GetString : function(key, defaultv) {
		let value = this.GetConfig(key, defaultv);
		if (value === undefined) {
			value = "";
		}
		return value;
	},
	SetConfig : function(key, value, not_save) {
		this._config_map[key] = value;
		if (!not_save) {
			this.SaveConfig();
		}
	},
	CoverConfig : function(msg, save) {
		let ___OBJECT_1 = msg;
		for (let k in ___OBJECT_1) {
			let v = ___OBJECT_1[k];
			if (v === undefined) continue;
			this._config_map[k] = v;
		}
		if (!save) {
			this.SaveConfig();
		}
	},
	SaveConfig : function() {
		let file = ALittle.NewObject(this.__class.__element[1]);
		if (!file.Save(this._file_path, ALittle.String_JsonEncode(this._config_map))) {
			ALittle.Log("Save Congig Failed.", this._file_path);
		}
	},
}, "ALittle.JsonConfig");

ALittle.CreateJsonConfig = function(file_path, print_error) {
	return ALittle.NewObject(JavaScript.Template(ALittle.JsonConfig, "ALittle.JsonConfig<ALittle.JFileLoader, ALittle.JFileSaver>", ALittle.JFileLoader, ALittle.JFileSaver), file_path, print_error);
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.CreateKeyWeakMap = function() {
	return new jkeyweakmap();
}

ALittle.CreateValueWeakMap = function() {
	return new jvalueweakmap();
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IHeapTimer = JavaScript.Class(undefined, {
	Add : function(delay_ms, loop, interval_ms) {
		return 0;
	},
	Remove : function(id) {
		return false;
	},
	Update : function(ms) {
	},
	Poll : function() {
		return 0;
	},
}, "ALittle.IHeapTimer");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.ISchedule = JavaScript.Class(undefined, {
	Run : function() {
	},
	RunInFrame : function() {
	},
}, "ALittle.ISchedule");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})

ALittle.EventDispatcher = JavaScript.Class(undefined, {
	Ctor : function() {
		this._listeners = new Map();
		this._abs_disabled = false;
	},
	AddEventListener : function(T, object, callback) {
		if (object === undefined) {
			return false;
		}
		if (callback === undefined) {
			return false;
		}
		let rflt = T;
		let callback_table = this._listeners.get(rflt.hash_code);
		if (callback_table === undefined) {
			callback_table = ALittle.CreateKeyWeakMap();
			this._listeners.set(rflt.hash_code, callback_table);
		}
		let callback_value = callback_table.get(object);
		if (callback_value === undefined) {
			callback_value = new Map();
			callback_table.set(object, callback_value);
		}
		callback_value.set(callback, true);
		return true;
	},
	RemoveEventListener : function(T, object, callback) {
		let rflt = T;
		let callback_table = this._listeners.get(rflt.hash_code);
		if (callback_table === undefined) {
			return;
		}
		if (callback === undefined) {
			callback_table.delete(object);
		} else {
			let callback_value = callback_table.get(object);
			if (callback_value === undefined) {
				return;
			}
			callback_value.delete(callback);
		}
	},
	ClearEventListener : function() {
		this._listeners = new Map();
	},
	DispatchEvent : function(T, event) {
		let rflt = T;
		if (event.target === undefined) {
			event.target = this;
		}
		let callback_table = this._listeners.get(rflt.hash_code);
		if (callback_table === undefined) {
			return;
		}
		for (let [object, callback_value] of callback_table) {
			if (callback_value === undefined) continue;
			for (let [func, _] of callback_value) {
				if (_ === undefined) continue;
				func.call(object, event);
			}
		}
	},
}, "ALittle.EventDispatcher");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.SafeIDCreator = JavaScript.Class(undefined, {
	Ctor : function() {
		this._max_id = 0;
		this._map = new Map();
	},
	CreateID : function() {
		let id = undefined;
		for (let [k, v] of this._map) {
			if (v === undefined) continue;
			id = k;
			break;
		}
		if (id !== undefined) {
			this._map.delete(id);
			return id;
		}
		this._max_id = this._max_id + 1;
		return this._max_id;
	},
	ReleaseID : function(id) {
		this._map.set(id, true);
	},
	PrintStatus : function() {
		let count = 0;
		for (let [k, v] of this._map) {
			if (v === undefined) continue;
			++ count;
		}
		ALittle.Log("SafeIDCreator:PrintStatus count:" + count + " max_id:" + this._max_id);
	},
}, "ALittle.SafeIDCreator");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.String_JsonEncode = function(object) {
	return JSON.stringify(object);
}

ALittle.String_JsonDecode = function(text) {
	return JSON.parse(text);
}

ALittle.String_Md5 = function(text) {
	return md5(text);
}

ALittle.String_Base64Encode = function(text) {
	return btoa(text);
}

ALittle.String_Base64Decode = function(text) {
	return atob(text);
}

ALittle.String_GetWordCount = function(text) {
	return text.length;
}

ALittle.String_GetByteCount = function(text, word_count) {
	if (text.length < word_count) {
		return text.length;
	} else {
		return word_count;
	}
}

ALittle.StringGenerateID = JavaScript.Class(undefined, {
	Ctor : function() {
		this._string_last_index = 0;
		this._string_last_time = 0;
	},
	GenID : function(pre) {
		let cur_time = ALittle.Time_GetCurTime();
		if (cur_time !== this._string_last_time) {
			this._string_last_time = cur_time;
			this._string_last_index = 0;
		} else {
			++ this._string_last_index;
		}
		let result = "";
		if (pre !== undefined) {
			result = pre + "-";
		}
		result = result + this._string_last_time + "-" + this._string_last_index + "-" + ALittle.Math_RandomInt(0, 10000) + "-" + ALittle.Math_RandomInt(0, 10000);
		return result;
	},
}, "ALittle.StringGenerateID");

let A_StringGenerateID = ALittle.NewObject(ALittle.StringGenerateID);
ALittle.String_GenerateID = function(pre) {
	return A_StringGenerateID.GenID(pre);
}

ALittle.String_HttpAnalysisValueMap = function(param, content) {
	let value_map = {};
	let param_split_list = ALittle.String_Split(param, "&");
	let ___OBJECT_1 = param_split_list;
	for (let index = 1; index <= ___OBJECT_1.length; ++index) {
		let param_content = ___OBJECT_1[index - 1];
		if (param_content === undefined) break;
		let value_split_list = ALittle.String_Split(param_content, "=");
		if (ALittle.List_Len(value_split_list) === 2) {
			if (ALittle.String_Sub(value_split_list[2 - 1], 1, 1) === "\"" && ALittle.String_Sub(value_split_list[2 - 1], -1, -1) === "\"") {
				value_map[value_split_list[1 - 1]] = ALittle.String_Sub(value_split_list[2 - 1], 2, -2);
			} else {
				let number = ALittle.Math_ToDouble(value_split_list[2 - 1]);
				if (number === undefined) {
					value_map[value_split_list[1 - 1]] = value_split_list[2 - 1];
				} else {
					value_map[value_split_list[1 - 1]] = number;
				}
			}
		}
	}
	if (ALittle.String_Len(content) > 0) {
		let [error, value] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } })();
		if (error === undefined) {
			let ___OBJECT_2 = value;
			for (let k in ___OBJECT_2) {
				let v = ___OBJECT_2[k];
				if (v === undefined) continue;
				value_map[k] = v;
			}
		}
	}
	return value_map;
}

ALittle.String_IsPhoneNumber = function(number) {
	let l = ALittle.String_Len(number);
	for (let i = 1; i <= l; i += 1) {
		let value = ALittle.String_Byte(number, i);
		if (value < 48) {
			return false;
		}
		if (value > 57) {
			return false;
		}
	}
	return true;
}

ALittle.String_IsWordChar = function(char) {
	let len = ALittle.String_Len(char);
	if (len !== 1) {
		return false;
	}
	let value = ALittle.String_Byte(char, 1);
	if (value >= 48 && value <= 57) {
		return true;
	}
	if (value === 95) {
		return true;
	}
	if (value >= 97 && value <= 122) {
		return true;
	}
	if (value >= 64 && value <= 90) {
		return true;
	}
	return false;
}

ALittle.String_SplitUTF8 = function(content) {
	let len = ALittle.String_Len(content);
	let index = 1;
	let char_list = [];
	let char_count = 0;
	while (index <= len) {
		{
			let code = content.charCodeAt(index - 1);
			char_count = char_count + (1);
			char_list[char_count - 1] = content.substring(index - 1, index);
			index = index + (1);
		}
	}
	return char_list;
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(839664979, "ALittle.PathAttribute", {
name : "ALittle.PathAttribute", ns_name : "ALittle", rl_name : "PathAttribute", hash_code : 839664979,
name_list : ["directory","size"],
type_list : ["bool","int"],
option_map : {}
})

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
	return JavaScript.File_GetPathAttribute(path);
}

ALittle.File_GetFileAttrByDir = function(path, file_map) {
	return JavaScript.File_GetFileAttrByDir(path, file_map);
}

ALittle.File_GetFileListByDir = function(path, out_list) {
	return JavaScript.File_GetFileListByDir(path, out_list);
}

ALittle.File_GetNameListByDir = function(path, file_map) {
	return JavaScript.File_GetNameListByDir(path, file_map);
}

ALittle.File_DeleteDir = function(path) {
	JavaScript.File_DeleteDir(path);
}

ALittle.File_DeleteDeepDir = function(path, log_path) {
	JavaScript.File_DeleteDeepDir(path, log_path);
}

ALittle.File_CopyFile = function(src_path, dst_path) {
	return JavaScript.File_CopyFile(src_path, dst_path);
}

ALittle.File_CopyDeepDir = function(src_path, dest_path, ext, log) {
	JavaScript.File_CopyDeepDir(src_path, dest_path, ext, log);
}

ALittle.File_MakeDir = function(path) {
	JavaScript.File_MakeDir(path);
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
	let l = ALittle.List_Len(list);
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
	let l = ALittle.List_Len(list);
	if (l <= 0) {
		return file_path;
	}
	return list[l - 1];
}

ALittle.File_ChangeFileExtByPath = function(file_path, ext) {
	let list = ALittle.String_Split(file_path, ".");
	let l = ALittle.List_Len(list);
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
	let l = ALittle.List_Len(list);
	if (l <= 1) {
		return new_file_path;
	}
	if (l === 2) {
		return list[1 - 1];
	}
	ALittle.List_Remove(list, l);
	return ALittle.String_Join(list, ".");
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
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(-1631648859, "ALittle.WorkerRPCInfo", {
name : "ALittle.WorkerRPCInfo", ns_name : "ALittle", rl_name : "WorkerRPCInfo", hash_code : -1631648859,
name_list : ["thread","rpc_id"],
type_list : ["ALittle.Thread","int"],
option_map : {}
})
ALittle.RegStruct(-930447138, "ALittle.Thread", {
name : "ALittle.Thread", ns_name : "ALittle", rl_name : "Thread", hash_code : -930447138,
name_list : [],
type_list : [],
option_map : {}
})

if (ALittle.IWorker === undefined) throw new Error(" extends class:ALittle.IWorker is undefined");
ALittle.IWorkerCommon = JavaScript.Class(ALittle.IWorker, {
	Ctor : function() {
		this._id_map_rpc = new Map();
		this._id_creator = ALittle.NewObject(ALittle.SafeIDCreator);
	},
	ClearRPC : function(reason) {
		let tmp = new Map();
		for (let [rpc_id, info] of this._id_map_rpc) {
			if (info === undefined) continue;
			this._id_creator.ReleaseID(rpc_id);
			tmp.set(rpc_id, info);
		}
		this._id_map_rpc = new Map();
		for (let [rpc_id, info] of tmp) {
			if (info === undefined) continue;
			let [result, error] = ALittle.Coroutine.Resume(info.thread, reason, undefined);
			if (result !== true) {
				ALittle.Error(error);
			}
		}
	},
	HandleMessage : function(worker_msg) {
		let id = worker_msg.id;
		let rpc_id = worker_msg.rpc_id;
		if (id === 0) {
			return;
		}
		if (rpc_id === 0) {
			let callback = ALittle.FindWorkerCallback(id);
			if (callback === undefined) {
				let name = "unknow";
				let rflt = ALittle.FindStructById(id);
				if (rflt !== undefined) {
					name = rflt.name;
				}
				ALittle.Log("WorkerCommon can't find callback by id:" + id + ", name:" + name);
				return;
			}
			let msg = worker_msg.msg;
			if (msg === undefined) {
				let name = "unknow";
				let rflt = ALittle.FindStructById(id);
				if (rflt !== undefined) {
					name = rflt.name;
				}
				ALittle.Log("WorkerCommon MessageRead failed by id:" + id + ", name:" + name);
				return;
			}
			callback(this, msg);
			return;
		}
		if (rpc_id > 0) {
			this.HandleRPCRequest(id, rpc_id, worker_msg.msg);
			return;
		}
		rpc_id = -rpc_id;
		this._id_creator.ReleaseID(rpc_id);
		let info = this._id_map_rpc.get(rpc_id);
		if (info === undefined) {
			ALittle.Log("WorkerCommon can't find rpc info by id:" + id);
			return;
		}
		this._id_map_rpc.delete(rpc_id);
		if (id === 1) {
			let [result, reason] = ALittle.Coroutine.Resume(info.thread, worker_msg.reason, undefined);
			if (result !== true) {
				ALittle.Error(reason);
			}
			return;
		}
		let [result, reason] = ALittle.Coroutine.Resume(info.thread, undefined, worker_msg.msg);
		if (result !== true) {
			ALittle.Error(reason);
		}
	},
	SendRpcError : function(rpc_id, reason) {
		let msg = {};
		msg.id = 1;
		msg.reason = reason;
		msg.rpc_id = -rpc_id;
		this.Send(msg);
	},
	SendRPC : function(thread, msg_id, msg_body) {
		let rpc_id = this._id_creator.CreateID();
		let worker_msg = {};
		worker_msg.id = msg_id;
		worker_msg.msg = msg_body;
		worker_msg.rpc_id = rpc_id;
		this.Send(worker_msg);
		let info = {};
		info.thread = thread;
		info.rpc_id = rpc_id;
		this._id_map_rpc.set(rpc_id, info);
	},
	HandleRPCRequest : async function(id, rpc_id, msg) {
		let [callback, return_id] = ALittle.FindWorkerRpcCallback(id);
		if (callback === undefined) {
			this.SendRpcError(rpc_id, "没有注册消息RPC回调函数");
			ALittle.Log("WorkerCommon.HandleMessage can't find callback by id:" + id);
			return;
		}
		let [error, return_body] = await (async function() { try { let ___VALUE = await callback.call(this, msg); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
		if (error !== undefined) {
			this.SendRpcError(rpc_id, error);
			ALittle.Log("WorkerCommon.HandleMessage callback invoke failed! by id:" + id + ", reason:" + error);
			return;
		}
		if (return_body === undefined) {
			this.SendRpcError(rpc_id, "WorkerCommon.HandleMessage callback have not return! by id:" + id);
			ALittle.Log("WorkerCommon.HandleMessage callback have not return! by id:" + id);
			return;
		}
		let worker_msg = {};
		worker_msg.id = return_id;
		worker_msg.msg = return_body;
		worker_msg.rpc_id = -rpc_id;
		this.Send(worker_msg);
	},
}, "ALittle.IWorkerCommon");

if (ALittle.IWorkerCommon === undefined) throw new Error(" extends class:ALittle.IWorkerCommon is undefined");
ALittle.Worker = JavaScript.Class(ALittle.IWorkerCommon, {
	Ctor : function(path) {
		this._stop = false;
		if (window.wx !== undefined) {
			this._wx_worker = window.wx.createWorker(path + ".js");
			this._wx_worker.onMessage(this.HandleWxMessage.bind(this));
		} else {
			this._web_worker = new Worker(path + ".js");
			this._web_worker.onmessage = this.HandleWebMessage.bind(this);
		}
	},
	IsStopped : function() {
		return this._stop;
	},
	Stop : function(reason) {
		if (this._stop) {
			return;
		}
		this._stop = true;
		if (reason === undefined) {
			reason = "主动关闭Worker";
		}
		this.ClearRPC(reason);
		if (this._wx_worker !== undefined) {
			this._wx_worker.terminate();
			this._wx_worker = undefined;
		} else {
			this._web_worker.terminate();
			this._web_worker = undefined;
		}
	},
	Send : function(msg) {
		if (this._wx_worker !== undefined) {
			this._wx_worker.postMessage(msg);
		} else {
			this._web_worker.postMessage(msg);
		}
	},
	HandleWxMessage : function(event) {
		this.HandleMessage(event.data);
	},
	HandleWebMessage : function(event) {
		this.HandleMessage(event.data);
	},
	HandleLuaMessage : function(frame_time) {
		while (true) {
			let content = this._lua_worker.Pull();
			if (content === undefined) {
				return;
			}
			let [result, object] = lua.pcall(lua.ajson.decode, content);
			if (result) {
				this.HandleMessage(object);
			}
		}
	},
}, "ALittle.Worker");

if (ALittle.IWorkerCommon === undefined) throw new Error(" extends class:ALittle.IWorkerCommon is undefined");
ALittle.WorkerInst = JavaScript.Class(ALittle.IWorkerCommon, {
	Send : function(msg) {
		if (window.wx !== undefined) {
			worker.postMessage(msg);
			return;
		}
		postMessage(msg);
	},
}, "ALittle.WorkerInst");

let A_WorkerInst = undefined;
let __WebWorkerMessage = function(event) {
	A_WorkerInst.HandleMessage(event.data);
}

let __WxWorkerMessage = function(event) {
	A_WorkerInst.HandleMessage(event.data);
}

ALittle.__ALITTLEAPI_WorkerMessage = function(json) {
	let [result, object] = lua.pcall(lua.ajson.decode, json);
	if (!result) {
		ALittle.Error("__ALITTLEAPI_WorkerMessage ajson decode failed");
		return;
	}
	A_WorkerInst.HandleMessage(object);
}

ALittle.__ALITTLEAPI_WorkerUpdate = function(frame_time) {
	A_LoopSystem.Update(frame_time);
	A_WeakLoopSystem.Update(frame_time);
}

let __WorkerInit = function() {
	if (window.wx !== undefined && worker !== undefined) {
		worker.onMessage(__WxWorkerMessage);
	}
	if (postMessage !== undefined) {
		onmessage = __WebWorkerMessage;
	}
	return true;
}

let __worker_init = __WorkerInit();
}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IHttpFileReceiverNative = JavaScript.Class(undefined, {
	Close : function(http_id) {
	},
	SendString : function(http_id, content) {
	},
	StartReceiveFile : function(http_id, file_path, start_size) {
	},
}, "ALittle.IHttpFileReceiverNative");

if (ALittle.IHttpFileReceiver === undefined) throw new Error(" extends class:ALittle.IHttpFileReceiver is undefined");
ALittle.HttpFileReceiverTemplate = JavaScript.Class(ALittle.IHttpFileReceiver, {
	Ctor : function(http_id, thread) {
		this._http_id = http_id;
		this._thread = thread;
		this._received = false;
		this._interface = ALittle.NewObject(this.__class.__element[0]);
	},
	StartReceiveFile : function(file_path, start_size) {
		return new Promise((function(___COROUTINE, ___) {
			if (this._received) {
				___COROUTINE("StartReceiveFile已经被调用过"); return;
			}
			this._received = true;
			this._interface.StartReceiveFile(this._http_id, file_path, start_size);
			return;
		}).bind(this));
	},
	HandleReceiveResult : function(reason) {
		let [result, error] = ALittle.Coroutine.Resume(this._thread, reason);
		if (!result) {
			ALittle.Error(error);
		}
	},
	get received() {
		return this._received;
	},
	SendString : function(content) {
		this._interface.SendString(this._http_id, content);
	},
	Clsoe : function() {
		this._interface.Close(this._http_id);
	},
}, "ALittle.HttpFileReceiverTemplate");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IHttpFileSenderNative = JavaScript.Class(undefined, {
	GetID : function() {
		return 0;
	},
	SetURL : function(url, file_path, download, start_size, array_buffer) {
	},
	Start : function() {
	},
	Stop : function() {
	},
	GetPath : function() {
		return "";
	},
}, "ALittle.IHttpFileSenderNative");

let __HttpFileSenderMap = new Map();
if (ALittle.IHttpFileSender === undefined) throw new Error(" extends class:ALittle.IHttpFileSender is undefined");
ALittle.HttpFileSenderTemplate = JavaScript.Class(ALittle.IHttpFileSender, {
	Ctor : function(ip, port, file_path, start_size, callback) {
		this._interface = ALittle.NewObject(this.__class.__element[0]);
		this._ip = ip;
		this._port = port;
		if (this._port === undefined) {
			if (location.protocol === "https:") {
				this._port = 443;
			} else {
				this._port = 80;
			}
		}
		this._file_path = file_path;
		this._start_size = start_size;
		this._callback = callback;
		this._cur_size = 0;
		this._total_size = 0;
	},
	SendDownloadRPC : function(thread, method, content, array_buffer) {
		this._thread = thread;
		__HttpFileSenderMap.set(this._interface.GetID(), this);
		if (this._start_size === undefined) {
			this._start_size = 0;
		}
		let url = this._ip + ":" + this._port + "/" + method;
		if (ALittle.String_Find(this._ip, "http://") !== 1 && ALittle.String_Find(this._ip, "https://") !== 1) {
			if (location.hostname === this._ip) {
				url = location.protocol + "//" + url;
			} else {
				if (this._port === 443) {
					url = "https://" + url;
				} else {
					url = "http://" + url;
				}
			}
		}
		this._interface.SetURL(this.HttpUrlAppendParamMap(url, content), this._file_path, true, this._start_size, array_buffer);
		this._interface.Start();
	},
	SendUploadRPC : function(thread, method, content, array_buffer) {
		this._thread = thread;
		__HttpFileSenderMap.set(this._interface.GetID(), this);
		if (this._start_size === undefined) {
			this._start_size = 0;
		}
		let url = "http://" + this._ip + ":" + this._port + "/" + method;
		this._interface.SetURL(this.HttpUrlAppendParamMap(url, content), this._file_path, false, this._start_size, array_buffer);
		this._interface.Start();
	},
	Stop : function() {
		this._interface.Stop();
	},
	GetFilePath : function() {
		return this._file_path;
	},
	GetTotalSize : function() {
		return this._total_size;
	},
	GetCurSize : function() {
		return this._cur_size;
	},
	HandleSucceed : function() {
		__HttpFileSenderMap.delete(this._interface.GetID());
		let [result, reason] = ALittle.Coroutine.Resume(this._thread, undefined);
		if (result !== true) {
			ALittle.Error(reason);
		}
	},
	HandleFailed : function(reason) {
		__HttpFileSenderMap.delete(this._interface.GetID());
		let [result, error] = ALittle.Coroutine.Resume(this._thread, reason);
		if (result !== true) {
			ALittle.Error(error);
		}
	},
	HandleProcess : function(cur_size, total_size) {
		this._cur_size = cur_size;
		this._total_size = total_size;
		if (this._callback !== undefined) {
			this._callback(this);
		}
	},
	HttpUrlAppendParamMap : function(url, param) {
		if (param === undefined) {
			return url;
		}
		let list = [];
		let count = 0;
		let ___OBJECT_1 = param;
		for (let key in ___OBJECT_1) {
			let value = ___OBJECT_1[key];
			if (value === undefined) continue;
			++ count;
			list[count - 1] = key + "=" + ALittle.String_ToString(value);
		}
		if (ALittle.String_Find(url, "?") === undefined) {
			url = url + "?";
		} else {
			url = url + "&";
		}
		return url + ALittle.String_Join(list, "&");
	},
}, "ALittle.HttpFileSenderTemplate");

ALittle.__ALITTLEAPI_HttpFileSucceed = function(id) {
	let client = __HttpFileSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleSucceed();
}

ALittle.__ALITTLEAPI_HttpFileFailed = function(id, reason) {
	let client = __HttpFileSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleFailed(reason);
}

ALittle.__ALITTLEAPI_HttpFileProcess = function(id, cur_size, total_size) {
	let client = __HttpFileSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleProcess(cur_size, total_size);
}

ALittle.DownloadFile = function(ip, port, method, file_path, array_buffer) {
	return new Promise(async function(___COROUTINE, ___) {
		let sender = undefined;
		sender = ALittle.NewObject(JavaScript.Template(ALittle.HttpFileSenderTemplate, "ALittle.HttpFileSenderTemplate<JavaScript.JHttpFileInterface>", JavaScript.JHttpFileInterface), ip, port, file_path, 0);
		___COROUTINE(await ALittle.IHttpFileSender.InvokeDownload(method, sender, undefined, array_buffer)); return;
	});
}

ALittle.UploadFile = function(ip, port, method, file_path, array_buffer) {
	return new Promise(async function(___COROUTINE, ___) {
		let sender = undefined;
		sender = ALittle.NewObject(JavaScript.Template(ALittle.HttpFileSenderTemplate, "ALittle.HttpFileSenderTemplate<JavaScript.JHttpFileInterface>", JavaScript.JHttpFileInterface), ip, port, file_path, 0);
		let error = await ALittle.IHttpFileSender.InvokeUpload(method, sender, undefined, array_buffer);
		___COROUTINE(error); return;
	});
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IHttpReceiverNative = JavaScript.Class(undefined, {
	Close : function(http_id) {
	},
	SendString : function(http_id, content) {
	},
	SendFile : function(http_id, file_path, start_size) {
	},
}, "ALittle.IHttpReceiverNative");

if (ALittle.IHttpReceiver === undefined) throw new Error(" extends class:ALittle.IHttpReceiver is undefined");
ALittle.HttpReceiverTemplate = JavaScript.Class(ALittle.IHttpReceiver, {
	Ctor : function(method, http_id) {
		this._http_id = http_id;
		this._interface = ALittle.NewObject(this.__class.__element[0]);
	},
	Close : function() {
		this._interface.Close(this._http_id);
	},
	SendString : function(content) {
		this._interface.SendString(this._http_id, content);
	},
	SendFile : function(file_path, start_size) {
		this._interface.SendFile(this._http_id, file_path, start_size);
	},
}, "ALittle.HttpReceiverTemplate");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IHttpSenderNative = JavaScript.Class(undefined, {
	GetID : function() {
		return 0;
	},
	SetURL : function(url, content) {
	},
	Start : function() {
	},
	Stop : function() {
	},
	GetResponse : function() {
		return undefined;
	},
}, "ALittle.IHttpSenderNative");

let __HttpSenderMap = new Map();
if (ALittle.IHttpSender === undefined) throw new Error(" extends class:ALittle.IHttpSender is undefined");
ALittle.HttpSenderTemplate = JavaScript.Class(ALittle.IHttpSender, {
	Ctor : function(ip, port) {
		this._interface = ALittle.NewObject(this.__class.__element[0]);
		this._ip = ip;
		this._port = port;
		if (this._port === undefined) {
			if (location.protocol === "https:") {
				this._port = 443;
			} else {
				this._port = 80;
			}
		}
	},
	SendRPC : function(thread, method, content) {
		this._thread = thread;
		__HttpSenderMap.set(this._interface.GetID(), this);
		let url = this._ip + ":" + this._port + "/" + method;
		if (ALittle.String_Find(this._ip, "http://") !== 1 && ALittle.String_Find(this._ip, "https://") !== 1) {
			if (location.hostname === this._ip) {
				url = location.protocol + "//" + url;
			} else {
				if (this._port === 443) {
					url = "https://" + url;
				} else {
					url = "http://" + url;
				}
			}
		}
		if (content === undefined) {
			this._interface.SetURL(url, undefined);
		} else {
			this._interface.SetURL(url, ALittle.String_JsonEncode(content));
		}
		this._interface.Start();
	},
	Stop : function() {
		this._interface.Stop();
	},
	HandleSucceed : function() {
		__HttpSenderMap.delete(this._interface.GetID());
		let [error, param] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, this._interface.GetResponse()); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
		if (error !== undefined) {
			let [result, reason] = ALittle.Coroutine.Resume(this._thread, error, undefined);
			if (result !== true) {
				ALittle.Error(reason);
			}
			return;
		}
		if (param["error"] !== undefined) {
			let [result, reason] = ALittle.Coroutine.Resume(this._thread, param["error"], undefined);
			if (result !== true) {
				ALittle.Error(reason);
			}
			return;
		}
		let [result, reason] = ALittle.Coroutine.Resume(this._thread, undefined, param);
		if (result !== true) {
			ALittle.Error(reason);
		}
	},
	HandleFailed : function(reason) {
		__HttpSenderMap.delete(this._interface.GetID());
		let [result, error] = ALittle.Coroutine.Resume(this._thread, reason, undefined);
		if (result !== true) {
			ALittle.Error(error);
		}
	},
}, "ALittle.HttpSenderTemplate");

ALittle.__ALITTLEAPI_HttpClientSucceed = function(id) {
	let client = __HttpSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleSucceed();
}

ALittle.__ALITTLEAPI_HttpClientFailed = function(id, reason) {
	let client = __HttpSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleFailed(reason);
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(-930447138, "ALittle.Thread", {
name : "ALittle.Thread", ns_name : "ALittle", rl_name : "Thread", hash_code : -930447138,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(361433949, "ALittle.MsgRPCInfo", {
name : "ALittle.MsgRPCInfo", ns_name : "ALittle", rl_name : "MsgRPCInfo", hash_code : 361433949,
name_list : ["rpc_id","thread"],
type_list : ["int","ALittle.Thread"],
option_map : {}
})

ALittle.IMsgCommonNative = JavaScript.Class(undefined, {
	SetID : function(id) {
	},
	GetID : function() {
		return 0;
	},
	Connect : function(ip, port) {
	},
	IsConnected : function() {
		return false;
	},
	SendFactory : function(factory) {
	},
	Close : function() {
	},
}, "ALittle.IMsgCommonNative");

if (ALittle.IMsgCommon === undefined) throw new Error(" extends class:ALittle.IMsgCommon is undefined");
ALittle.IMsgCommonTemplate = JavaScript.Class(ALittle.IMsgCommon, {
	Ctor : function() {
		this._last_recv_time = 0;
		this._id_creator = ALittle.NewObject(ALittle.SafeIDCreator);
		this._id_map_rpc = new Map();
	},
	GetID : function() {
		return this._interface.GetID();
	},
	Connect : function(ip, port) {
		return new Promise((function(___COROUTINE, ___) {
			___COROUTINE("not impl"); return;
		}).bind(this));
	},
	IsConnected : function() {
		return this._interface.IsConnected();
	},
	MessageRead : function(factory, msg_id) {
		let invoke = ALittle.CreateProtocolInvokeInfo(msg_id);
		let [object, size] = ALittle.PS_ReadMessageForReceive(factory, invoke, undefined, factory.GetDataSize());
		return object;
	},
	MessageWrite : function(msg_id, msg_body) {
		let invoke = ALittle.CreateProtocolInvokeInfo(msg_id);
		this._write_factory.ResetOffset();
		ALittle.PS_WriteMessageForSend(this._write_factory, invoke, undefined, msg_body);
		this._write_factory.SetID(msg_id);
	},
	HandleMessage : function(id, rpc_id, factory) {
		if (id === 0) {
			this._last_recv_time = ALittle.Time_GetCurTime();
			return;
		}
		if (rpc_id === 0) {
			let callback = ALittle.FindMsgCallback(id);
			if (callback === undefined) {
				let name = "unknow";
				let rflt = ALittle.FindStructById(id);
				if (rflt !== undefined) {
					name = rflt.name;
				}
				ALittle.Log("MsgSystem.HandleMessage can't find callback by id:" + id + ", name:" + name);
				return;
			}
			let msg = this.MessageRead(factory, id);
			if (msg === undefined) {
				let name = "unknow";
				let rflt = ALittle.FindStructById(id);
				if (rflt !== undefined) {
					name = rflt.name;
				}
				ALittle.Log("MsgSystem.HandleMessage MessageRead failed by id:" + id + ", name:" + name);
				return;
			}
			callback(this, msg);
			return;
		}
		if (rpc_id > 0) {
			this.HandleRPCRequest(id, rpc_id, factory);
			return;
		}
		rpc_id = -rpc_id;
		this._id_creator.ReleaseID(rpc_id);
		let info = this._id_map_rpc.get(rpc_id);
		if (info === undefined) {
			ALittle.Log("MsgSystem.HandleMessage can't find rpc info by id:" + id);
			return;
		}
		this._id_map_rpc.delete(rpc_id);
		if (id === 1) {
			let [result, reason] = ALittle.Coroutine.Resume(info.thread, factory.ReadString(), undefined);
			if (result !== true) {
				ALittle.Error(reason);
			}
			return;
		}
		let msg = this.MessageRead(factory, id);
		if (msg === undefined) {
			let [result, reason] = ALittle.Coroutine.Resume(info.thread, "MsgSystem.HandleMessage MessageRead failed by id:" + id, undefined);
			if (result !== true) {
				ALittle.Error(reason);
			}
			ALittle.Log("MsgSystem.HandleMessage MessageRead failed by id:" + id);
			return;
		}
		let [result, reason] = ALittle.Coroutine.Resume(info.thread, undefined, msg);
		if (result !== true) {
			ALittle.Error(reason);
		}
	},
	SendMsg : function(T, msg) {
		let info = T;
		this.Send(info.hash_code, msg, 0);
	},
	Send : function(msg_id, msg_body, rpc_id) {
		if (!this.IsConnected()) {
			return;
		}
		this._write_factory.SetRpcID(rpc_id);
		this.MessageWrite(msg_id, msg_body);
		this._interface.SendFactory(this._write_factory);
	},
	SendRpcError : function(rpc_id, reason) {
		if (!this.IsConnected()) {
			return;
		}
		this._write_factory.ResetOffset();
		this._write_factory.SetID(1);
		this._write_factory.SetRpcID(-rpc_id);
		this._write_factory.WriteString(reason);
		this._interface.SendFactory(this._write_factory);
	},
	SendRPC : function(thread, msg_id, msg_body) {
		let rpc_id = this._id_creator.CreateID();
		this._write_factory.SetRpcID(rpc_id);
		this.MessageWrite(msg_id, msg_body);
		this._interface.SendFactory(this._write_factory);
		let info = {};
		info.thread = thread;
		info.rpc_id = rpc_id;
		this._id_map_rpc.set(rpc_id, info);
	},
	HandleRPCRequest : async function(id, rpc_id, factory) {
		let [callback, return_id] = ALittle.FindMsgRpcCallback(id);
		if (callback === undefined) {
			this.SendRpcError(rpc_id, "没有注册消息RPC回调函数");
			ALittle.Log("MsgSystem.HandleMessage can't find callback by id:" + id);
			return;
		}
		let msg = this.MessageRead(factory, id);
		if (msg === undefined) {
			this.SendRpcError(rpc_id, "MsgSystem.HandleMessage MessageRead failed by id:" + id);
			ALittle.Log("MsgSystem.HandleMessage MessageRead failed by id:" + id);
			return;
		}
		let [error, return_body] = await (async function() { try { let ___VALUE = await callback.call(this, msg); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
		if (error !== undefined) {
			this.SendRpcError(rpc_id, error);
			ALittle.Log("MsgSystem.HandleMessage callback invoke failed! by id:" + id + ", reason:" + error);
			return;
		}
		if (return_body === undefined) {
			this.SendRpcError(rpc_id, "MsgSystem.HandleMessage callback have not return! by id:" + id);
			ALittle.Log("MsgSystem.HandleMessage callback have not return! by id:" + id);
			return;
		}
		this.Send(return_id, return_body, -rpc_id);
	},
	ClearRPC : function(reason) {
		let tmp = new Map();
		for (let [rpc_id, info] of this._id_map_rpc) {
			if (info === undefined) continue;
			this._id_creator.ReleaseID(rpc_id);
			tmp.set(rpc_id, info);
		}
		this._id_map_rpc = new Map();
		for (let [rpc_id, info] of tmp) {
			if (info === undefined) continue;
			let [result, error] = ALittle.Coroutine.Resume(info.thread, reason, undefined);
			if (result !== true) {
				ALittle.Error(error);
			}
		}
	},
	Close : function(reason) {
		if (reason === undefined) {
			reason = "主动关闭连接";
		}
		this.ClearRPC(reason);
		this._interface.Close();
	},
}, "ALittle.IMsgCommonTemplate");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.IMsgCommonTemplate === undefined) throw new Error(" extends class:ALittle.IMsgCommonTemplate is undefined");
ALittle.MsgReceiverTemplate = JavaScript.Class(ALittle.IMsgCommonTemplate, {
	Ctor : function(client_id, remote_ip, remote_port) {
		this._interface = ALittle.NewObject(this.__class.__element[0]);
		this._interface.SetID(client_id);
		this._write_factory = ALittle.NewObject(this.__class.__element[1]);
		this._is_connected = true;
		this._client_id = client_id;
		this._remote_ip = remote_ip;
		this._remote_port = remote_port;
		this._client_account_id = 0;
		this._client_logining = false;
		this._web_account_id = "";
		this._web_is_logining = false;
	},
	get remote_ip() {
		return this._remote_ip;
	},
	get remote_port() {
		return this._remote_port;
	},
	IsConnected : function() {
		return this._is_connected;
	},
	HandleConnected : function() {
		this._is_connected = true;
	},
	HandleDisconnected : function() {
		this._is_connected = false;
		this.ClearRPC("连接断开了");
	},
	Close : function(reason) {
		if (!this._is_connected) {
			return;
		}
		this._is_connected = false;
		if (reason === undefined) {
			reason = "主动关闭连接";
		}
		this.ClearRPC(reason);
		this._interface.Close();
	},
}, "ALittle.MsgReceiverTemplate");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


let __MsgSenderMap = new Map();
if (ALittle.IMsgCommonTemplate === undefined) throw new Error(" extends class:ALittle.IMsgCommonTemplate is undefined");
ALittle.MsgSenderTemplate = JavaScript.Class(ALittle.IMsgCommonTemplate, {
	Ctor : function(heartbeat, check_heartbeat, loop_system, callback) {
		this._interface = ALittle.NewObject(this.__class.__element[0]);
		this._write_factory = ALittle.NewObject(this.__class.__element[1]);
		this._loop_system = loop_system;
		this._heartbeat = heartbeat;
		this._heartbeat_loop = undefined;
		this._check_heartbeat = undefined;
		if (this._heartbeat !== undefined) {
			this._check_heartbeat = check_heartbeat;
		}
		this._last_recv_time = 0;
		this._callback = callback;
	},
	Connect : function(ip, port) {
		return new Promise((function(___COROUTINE, ___) {
			if (ip === undefined) {
				ip = "";
			}
			if (port === undefined) {
				port = 0;
			}
			if (___COROUTINE === undefined) {
				___COROUTINE("当前不是协程"); return;
			}
			this._co = ___COROUTINE;
			__MsgSenderMap.set(this._interface.GetID(), this);
			this._ip = ip;
			this._port = port;
			this._interface.Connect(ip, port);
			return;
		}).bind(this));
	},
	HandleConnectSucceed : function() {
		this._last_recv_time = 0;
		this.SendHeartbeat();
		this.StartHeartbeat();
		let [result, reason] = ALittle.Coroutine.Resume(this._co, undefined);
		if (result !== true) {
			ALittle.Error(reason);
		}
	},
	HandleDisconnected : function() {
		this.StopHeartbeat();
		__MsgSenderMap.delete(this._interface.GetID());
		this.ClearRPC("连接断开了");
		if (this._callback !== undefined) {
			this._callback();
		}
	},
	HandleConnectFailed : function(error) {
		__MsgSenderMap.delete(this._interface.GetID());
		if (error === undefined) {
			error = this._ip + ":" + this._port + "连接失败";
		}
		let [result, reason] = ALittle.Coroutine.Resume(this._co, error);
		if (result !== true) {
			ALittle.Error(reason);
		}
	},
	Close : function(reason) {
		this.StopHeartbeat();
		this._interface.Close();
		if (reason === undefined) {
			reason = "主动关闭连接";
		}
		this.ClearRPC(reason);
		__MsgSenderMap.delete(this._interface.GetID());
	},
	SendHeartbeat : function(max_ms) {
		if (this._interface.IsConnected() === false) {
			return;
		}
		this._write_factory.ResetOffset();
		this._write_factory.SetID(0);
		this._write_factory.SetRpcID(0);
		this._interface.SendFactory(this._write_factory);
		if (this._check_heartbeat) {
			let send_time = ALittle.Time_GetCurTime();
			let default_delta = this._heartbeat / 2;
			let delta_time = max_ms;
			if (delta_time === undefined) {
				delta_time = default_delta;
			}
			if (delta_time > default_delta) {
				delta_time = default_delta;
			}
			this._loop_system.AddTimer(ALittle.Math_Floor(delta_time) * 1000, this.CheckHeartbeat.bind(this, send_time, ALittle.Math_Floor(delta_time)));
		}
	},
	CheckHeartbeat : function(send_time, delta_time) {
		let invoke_time = ALittle.Time_GetCurTime();
		let interval_time = invoke_time - send_time;
		if (interval_time > delta_time + 2) {
			return;
		}
		if (this._last_recv_time > 0 && send_time - this._last_recv_time > delta_time) {
			if (this._interface.IsConnected() === false) {
				return;
			}
			this.Close("心跳检测失败，主动断开连接");
			if (this._callback !== undefined) {
				this._callback();
			}
		}
	},
	StartHeartbeat : function() {
		if (this._heartbeat === undefined) {
			return;
		}
		if (this._heartbeat <= 0) {
			return;
		}
		if (this._heartbeat_loop !== undefined) {
			return;
		}
		this._heartbeat_loop = this._loop_system.AddTimer(1, this.SendHeartbeat.bind(this, undefined), -1, this._heartbeat * 1000);
	},
	StopHeartbeat : function() {
		if (this._heartbeat_loop === undefined) {
			return;
		}
		this._last_recv_time = 0;
		this._loop_system.RemoveTimer(this._heartbeat_loop);
		this._heartbeat_loop = undefined;
	},
}, "ALittle.MsgSenderTemplate");

ALittle.__ALITTLEAPI_ConnectSucceed = function(id) {
	let client = __MsgSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleConnectSucceed();
}

ALittle.__ALITTLEAPI_Disconnected = function(id) {
	let client = __MsgSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleDisconnected();
}

ALittle.__ALITTLEAPI_ConnectFailed = function(id) {
	let client = __MsgSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleConnectFailed(undefined);
}

ALittle.__ALITTLEAPI_Message = function(id, msg_id, rpc_id, factory) {
	let client = __MsgSenderMap.get(id);
	if (client === undefined) {
		return;
	}
	client.HandleMessage(msg_id, rpc_id, factory);
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.IMsgCommonTemplate === undefined) throw new Error(" extends class:ALittle.IMsgCommonTemplate is undefined");
ALittle.MsgSessionTemplate = JavaScript.Class(ALittle.IMsgCommonTemplate, {
	Ctor : function(connect_key, route_type, route_num) {
		this._interface = ALittle.NewObject(this.__class.__element[0]);
		this._interface.SetID(connect_key);
		this._write_factory = ALittle.NewObject(this.__class.__element[1]);
		this._is_connected = true;
		this._connect_key = connect_key;
		this._route_type = route_type;
		this._route_num = route_num;
	},
	get route_type() {
		return this._route_type;
	},
	get route_num() {
		return this._route_num;
	},
	IsConnected : function() {
		return this._is_connected;
	},
	HandleConnected : function() {
		this._is_connected = true;
	},
	HandleDisconnected : function() {
		this._is_connected = false;
		this.ClearRPC("连接断开了");
	},
	Close : function(reason) {
		if (!this._is_connected) {
			return;
		}
		this._is_connected = false;
		if (reason === undefined) {
			reason = "主动关闭连接";
		}
		this.ClearRPC(reason);
		this._interface.Close();
	},
}, "ALittle.MsgSessionTemplate");

}
{
if (typeof JavaScript === "undefined") window.JavaScript = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1961635951, "JavaScript.MiniHeapNodeInfo", {
name : "JavaScript.MiniHeapNodeInfo", ns_name : "JavaScript", rl_name : "MiniHeapNodeInfo", hash_code : 1961635951,
name_list : ["heap_index","end_time"],
type_list : ["int","int"],
option_map : {}
})
ALittle.RegStruct(979480799, "JavaScript.TimerInfo", {
name : "JavaScript.TimerInfo", ns_name : "JavaScript", rl_name : "TimerInfo", hash_code : 979480799,
name_list : ["heap_index","end_time","id","loop","interval_ms"],
type_list : ["int","int","int","int","int"],
option_map : {}
})

let Math_Floor = Math.floor;
JavaScript.MiniHeap = JavaScript.Class(undefined, {
	Ctor : function() {
		this._nodes = [];
		this._size = 0;
		this._capacity = 0;
	},
	get size() {
		return this._size;
	},
	get empty() {
		return this._size === 0;
	},
	GetTop : function() {
		if (this._size === 0) {
			return undefined;
		}
		return this._nodes[0 /*因为使用了Native修饰，下标从0开始，不做减1处理*/];
	},
	Push : function(node) {
		if (this._capacity < this._size + 1) {
			this._capacity = this._capacity + (1);
			this._nodes[this._capacity /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = undefined;
		}
		this.ShiftUp(this._size, node);
		++ this._size;
		return true;
	},
	Pop : function() {
		if (this._size === 0) {
			return undefined;
		}
		let node = this._nodes[0 /*因为使用了Native修饰，下标从0开始，不做减1处理*/];
		this.ShiftDown(0, this._nodes[this._size - 1 /*因为使用了Native修饰，下标从0开始，不做减1处理*/]);
		this._size = this._size - (1);
		node.heap_index = -1;
		return node;
	},
	Adjust : function(node) {
		if (node.heap_index === -1) {
			return this.Push(node);
		}
		if (node.heap_index > 0 && this._nodes[Math_Floor((node.heap_index - 1) / 2) /*因为使用了Native修饰，下标从0开始，不做减1处理*/].end_time > node.end_time) {
			this.ShiftUpUnconditional(node.heap_index, node);
		} else {
			this.ShiftDown(node.heap_index, node);
		}
		return true;
	},
	Erase : function(node) {
		if (node.heap_index < 0) {
			return false;
		}
		let last = this._nodes[this._size - 1 /*因为使用了Native修饰，下标从0开始，不做减1处理*/];
		this._size = this._size - (1);
		if (node.heap_index > 0 && this._nodes[Math_Floor((node.heap_index - 1) / 2) /*因为使用了Native修饰，下标从0开始，不做减1处理*/].end_time > last.end_time) {
			this.ShiftUpUnconditional(node.heap_index, last);
		} else {
			this.ShiftDown(node.heap_index, last);
		}
		node.heap_index = -1;
		return true;
	},
	ShiftUp : function(index, node) {
		let parent = Math_Floor((index - 1) / 2);
		while (index > 0 && this._nodes[parent /*因为使用了Native修饰，下标从0开始，不做减1处理*/].end_time > node.end_time) {
			this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = this._nodes[parent /*因为使用了Native修饰，下标从0开始，不做减1处理*/];
			this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/].heap_index = index;
			index = parent;
			parent = Math_Floor((index - 1) / 2);
		}
		this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = node;
		node.heap_index = index;
	},
	ShiftUpUnconditional : function(index, node) {
		let parent = Math_Floor((index - 1) / 2);
		do {
			this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = this._nodes[parent /*因为使用了Native修饰，下标从0开始，不做减1处理*/];
			this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/].heap_index = index;
			index = parent;
			parent = Math_Floor((index - 1) / 2);
		} while (index > 0 && this._nodes[parent /*因为使用了Native修饰，下标从0开始，不做减1处理*/].end_time > node.end_time);
		this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = node;
		node.heap_index = index;
	},
	ShiftDown : function(index, node) {
		let min_child = 2 * (index + 1);
		while (min_child <= this._size) {
			if (min_child === this._size || this._nodes[min_child /*因为使用了Native修饰，下标从0开始，不做减1处理*/].end_time > this._nodes[min_child - 1 /*因为使用了Native修饰，下标从0开始，不做减1处理*/].end_time) {
				min_child = min_child - (1);
			}
			if (!(node.end_time > this._nodes[min_child /*因为使用了Native修饰，下标从0开始，不做减1处理*/].end_time)) {
				break;
			}
			this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = this._nodes[min_child /*因为使用了Native修饰，下标从0开始，不做减1处理*/];
			this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/].heap_index = index;
			index = min_child;
			min_child = 2 * (index + 1);
		}
		this._nodes[index /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = node;
		node.heap_index = index;
	},
}, "JavaScript.MiniHeap");

if (ALittle.IHeapTimer === undefined) throw new Error(" extends class:ALittle.IHeapTimer is undefined");
JavaScript.JHeapTimer = JavaScript.Class(ALittle.IHeapTimer, {
	Ctor : function() {
		this._max_id = 0;
		this._cur_time = 0;
		this._heap = ALittle.NewObject(JavaScript.Template(JavaScript.MiniHeap, "JavaScript.MiniHeap<JavaScript.TimerInfo>", ___all_struct.get(979480799)));
		this._map = new Map();
		this._pool = [];
		this._pool_count = 0;
	},
	Create : function() {
		if (this._pool_count === 0) {
			return {};
		}
		let info = this._pool[this._pool_count - 1];
		this._pool[this._pool_count - 1] = undefined;
		this._pool_count = this._pool_count - (1);
		return info;
	},
	Release : function(info) {
		if (this._pool_count >= 1000) {
			return;
		}
		this._pool_count = this._pool_count + (1);
		this._pool[this._pool_count - 1] = info;
	},
	Add : function(delay_ms, loop, interval_ms) {
		let info = this.Create();
		info.heap_index = -1;
		if (delay_ms < 0) {
			delay_ms = 0;
		}
		info.end_time = this._cur_time + delay_ms;
		if (loop <= 0) {
			info.loop = -1;
		} else {
			info.loop = loop;
		}
		info.interval_ms = interval_ms;
		if (info.interval_ms <= 0) {
			info.interval_ms = 1;
		}
		let find_count = 1000000;
		while (find_count > 0) {
			this._max_id = this._max_id + (1);
			if (this._max_id === 0x7FFFFFFF) {
				this._max_id = 1;
			}
			if (this._map.get(this._max_id) === undefined) {
				info.id = this._max_id;
				break;
			}
			-- find_count;
		}
		if (!this._heap.Push(info)) {
			this.Release(info);
			return 0;
		}
		this._map.set(info.id, info);
		return info.id;
	},
	Remove : function(id) {
		let info = this._map.get(id);
		if (info === undefined) {
			return false;
		}
		this._heap.Erase(info);
		this.Release(info);
		this._map.delete(id);
		return true;
	},
	Update : function(frame_ms) {
		this._cur_time = this._cur_time + (frame_ms);
	},
	Poll : function() {
		let info = this._heap.GetTop();
		if (info === undefined) {
			return 0;
		}
		if (info.end_time > this._cur_time) {
			return 0;
		}
		this._heap.Pop();
		if (info.loop < 0) {
			info.end_time = info.end_time + info.interval_ms;
			this._heap.Push(info);
			return info.id;
		}
		if (info.loop > 1) {
			-- info.loop;
			info.end_time = info.end_time + info.interval_ms;
			this._heap.Push(info);
			return info.id;
		}
		this._map.delete(info.id);
		this.Release(info);
		return -info.id;
	},
}, "JavaScript.JHeapTimer");

}
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
	let list_len = ALittle.List_Len(list);
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
	let new_list_len = ALittle.List_Len(new_list);
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
	let list_len = ALittle.List_Len(list);
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

JavaScript.File_GetPathAttribute = function(path) {
	let list = Path_FilterEmpty(ALittle.String_SplitSepList(path, ["/", "\\"]));
	let list_len = ALittle.List_Len(list);
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
	attr.directory = cur_file.is_directory;
	attr.size = 0;
	if (!cur_file.is_directory) {
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
			attr.directory = false;
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
			ALittle.List_Push(file_list, file_path);
		}
	}
	return file_list;
}

JavaScript.File_GetNameListByDir = function(path, file_map) {
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
			attr.directory = true;
			attr.size = 0;
			file_map[name] = attr;
		} else {
			let attr = {};
			attr.directory = false;
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
	let list_len = ALittle.List_Len(list);
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
	let list_len = ALittle.List_Len(list);
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
	let list_len = ALittle.List_Len(list);
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
{
if (typeof JavaScript === "undefined") window.JavaScript = {};


let __JHTTPFILE_MAXID = 0;
if (ALittle.IHttpFileSenderNative === undefined) throw new Error(" extends class:ALittle.IHttpFileSenderNative is undefined");
JavaScript.JHttpFileInterface = JavaScript.Class(ALittle.IHttpFileSenderNative, {
	Ctor : function() {
		++ __JHTTPFILE_MAXID;
		this._id = __JHTTPFILE_MAXID;
	},
	GetID : function() {
		return this._id;
	},
	SetURL : function(url, file_path, download, start_size, array_buffer) {
		this._url = url;
		this._file_path = file_path;
		this._download = download;
		this._array_buffer = array_buffer;
	},
	Start : function() {
		let content = undefined;
		let buffer = undefined;
		if (!this._download) {
			[content, buffer] = JavaScript.File_LoadFile(this._file_path);
			if (content === undefined && buffer === undefined) {
				ALittle.__ALITTLEAPI_HttpFileFailed(this._id, "file is not exist:" + this._file_path);
				return;
			}
		}
		this._request = new XMLHttpRequest();
		if (this._download) {
			this._request.open("GET", this._url, true);
		} else {
			this._request.open("POST", this._url, true);
		}
		if (this._array_buffer) {
			this._request.responseType = "arraybuffer";
		}
		let error_func = this.HandleError.bind(this);
		this._request.onerror = error_func;
		this._request.ontimeout = error_func;
		this._request.onload = this.HandleCompleted.bind(this);
		this._request.onprogress = this.HandleOnProgress.bind(this);
		if (this._download) {
			this._request.send(undefined);
		} else if (content !== undefined) {
			this._request.send(content);
		} else {
			this._request.send(new Uint8Array(buffer));
		}
	},
	Stop : function() {
		if (this._request !== undefined) {
			this._request.abort();
		}
	},
	GetPath : function() {
		return this._file_path;
	},
	GetContent : function() {
		return this._request.responseText;
	},
	GetResponse : function() {
		return this._request.response;
	},
	HandleError : function() {
		ALittle.__ALITTLEAPI_HttpFileFailed(this._id, this._request.statusText);
	},
	HandleCompleted : function() {
		let content = undefined;
		let buffer = undefined;
		if (this._array_buffer) {
			buffer = this._request.response;
		} else {
			content = this._request.responseText;
		}
		if (this._download && !JavaScript.File_SaveFile(this._file_path, content, buffer)) {
			ALittle.__ALITTLEAPI_HttpFileFailed(this._id, "file save failed:" + this._file_path);
			return;
		}
		ALittle.__ALITTLEAPI_HttpFileSucceed(this._id);
	},
	HandleOnProgress : function(event) {
		ALittle.__ALITTLEAPI_HttpFileProcess(this._id, event.loaded, event.total);
	},
}, "JavaScript.JHttpFileInterface");

}
{
if (typeof JavaScript === "undefined") window.JavaScript = {};


let __JHTTPWXFILE_MAXID = 0;
if (ALittle.IHttpFileSenderNative === undefined) throw new Error(" extends class:ALittle.IHttpFileSenderNative is undefined");
JavaScript.JHttpFileWxInterface = JavaScript.Class(ALittle.IHttpFileSenderNative, {
	Ctor : function() {
		++ __JHTTPWXFILE_MAXID;
		this._id = __JHTTPWXFILE_MAXID;
	},
	GetID : function() {
		return this._id;
	},
	SetURL : function(url, file_path, download, start_size, array_buffer) {
		this._url = url;
		this._file_path = file_path;
		this._download = download;
		this._array_buffer = array_buffer;
	},
	Start : function() {
		let content = undefined;
		let buffer = undefined;
		if (!this._download) {
			[content, buffer] = JavaScript.File_LoadFile(this._file_path);
			if (content === undefined && buffer === undefined) {
				ALittle.__ALITTLEAPI_HttpFileFailed(this._id, "file is not exist:" + this._file_path);
				return;
			}
		}
		let info = {};
		info.url = this._url;
		if (this._download) {
			info.method = "GET";
		} else {
			info.method = "POST";
		}
		if (content !== undefined) {
			info.dataType = "text";
			info.data = content;
		} else if (buffer !== undefined) {
			info.dataType = "arraybuffer";
			info.data = buffer;
		}
		if (this._array_buffer === true) {
			info.responseType = "arraybuffer";
		}
		info.success = this.HandleCompleted.bind(this);
		info.fail = this.HandleError.bind(this);
		this._request = window.wx.request(info);
	},
	Stop : function() {
		if (this._request !== undefined) {
			this._request.abort();
		}
	},
	GetPath : function() {
		return this._file_path;
	},
	GetContent : function() {
		return this._response.data;
	},
	HandleError : function() {
		ALittle.__ALITTLEAPI_HttpFileFailed(this._id, "wx.request failed");
	},
	HandleCompleted : function(info) {
		let content = undefined;
		let buffer = undefined;
		if (this._array_buffer) {
			buffer = info.data;
		} else {
			content = info.data;
		}
		if (this._download && !JavaScript.File_SaveFile(this._file_path, content, buffer)) {
			ALittle.__ALITTLEAPI_HttpFileFailed(this._id, "file save failed:" + this._file_path);
			return;
		}
		this._response = info;
		ALittle.__ALITTLEAPI_HttpFileSucceed(this._id);
	},
	HandleOnProgress : function(event) {
		ALittle.__ALITTLEAPI_HttpFileProcess(this._id, event.loaded, event.total);
	},
}, "JavaScript.JHttpFileWxInterface");

}
{
if (typeof JavaScript === "undefined") window.JavaScript = {};


let __JHTTP_MAXID = 0;
if (ALittle.IHttpSenderNative === undefined) throw new Error(" extends class:ALittle.IHttpSenderNative is undefined");
JavaScript.JHttpInterface = JavaScript.Class(ALittle.IHttpSenderNative, {
	Ctor : function() {
		++ __JHTTP_MAXID;
		this._id = __JHTTP_MAXID;
	},
	GetID : function() {
		return this._id;
	},
	SetURL : function(url, content) {
		this._url = url;
		this._content = content;
	},
	Start : function() {
		this._request = new XMLHttpRequest();
		if (this._content === undefined) {
			this._request.open("GET", this._url, true);
		} else {
			this._request.open("POST", this._url, true);
		}
		let error_func = this.HandleError.bind(this);
		this._request.onerror = error_func;
		this._request.ontimeout = error_func;
		this._request.onload = this.HandleCompleted.bind(this);
		this._request.send(this._content);
	},
	Stop : function() {
		if (this._request !== undefined) {
			this._request.abort();
		}
	},
	GetResponse : function() {
		return this._request.responseText;
	},
	HandleError : function() {
		ALittle.__ALITTLEAPI_HttpClientFailed(this._id, this._request.statusText);
	},
	HandleCompleted : function() {
		ALittle.__ALITTLEAPI_HttpClientSucceed(this._id);
	},
}, "JavaScript.JHttpInterface");

}
{
if (typeof JavaScript === "undefined") window.JavaScript = {};


let __JHTTPWX_MAXID = 0;
if (ALittle.IHttpSenderNative === undefined) throw new Error(" extends class:ALittle.IHttpSenderNative is undefined");
JavaScript.JHttpWxInterface = JavaScript.Class(ALittle.IHttpSenderNative, {
	Ctor : function() {
		++ __JHTTPWX_MAXID;
		this._id = __JHTTPWX_MAXID;
	},
	GetID : function() {
		return this._id;
	},
	SetURL : function(url, content) {
		this._url = url;
		this._content = content;
	},
	Start : function() {
		let info = {};
		info.url = this._url;
		if (this._content === undefined) {
			info.method = "GET";
		} else {
			info.method = "POST";
		}
		if (this._content !== undefined) {
			info.data = this._content;
		}
		info.success = this.HandleCompleted.bind(this);
		info.fail = this.HandleError.bind(this);
		this._request = window.wx.request(info);
	},
	Stop : function() {
		if (this._request !== undefined) {
			this._request.abort();
		}
	},
	GetResponse : function() {
		return this._response.data;
	},
	HandleError : function() {
		ALittle.__ALITTLEAPI_HttpClientFailed(this._id, "wx.request failed");
	},
	HandleCompleted : function(info) {
		this._response = info;
		ALittle.__ALITTLEAPI_HttpClientSucceed(this._id);
	},
}, "JavaScript.JHttpWxInterface");

}
{
if (typeof JavaScript === "undefined") window.JavaScript = {};


if (ALittle.IMessageWriteFactory === undefined) throw new Error(" extends class:ALittle.IMessageWriteFactory is undefined");
JavaScript.JMessageWriteFactory = JavaScript.Class(ALittle.IMessageWriteFactory, {
	Ctor : function(init_size) {
		this._size = 0;
		this._id = 0;
		this._rpc_id = 0;
		if (init_size === undefined || init_size <= 0) {
			init_size = 1024;
		}
		let data = new ArrayBuffer(init_size);
		this._memory = new DataView(data);
	},
	ResizeMemory : function(add_size) {
		if (this._memory.byteLength >= this._size + add_size) {
			return;
		}
		let new_data = new ArrayBuffer(this._memory.byteLength * 2);
		let new_memory = new DataView(new_data);
		for (let i = 0; i < this._memory.byteLength; i += 1) {
			new_memory.setUint8(i, this._memory.getUint8(i));
		}
		this._memory = new_memory;
	},
	SetID : function(id) {
		this._id = id;
	},
	SetRpcID : function(id) {
		this._rpc_id = id;
	},
	ResetOffset : function() {
		this._size = 0;
	},
	GetOffset : function() {
		return this._size;
	},
	SetInt : function(offset, value) {
		this._memory.setInt32(offset, value, true);
	},
	WriteBool : function(value) {
		this.ResizeMemory(1);
		if (value) {
			this._memory.setUint8(this._size, 1);
		} else {
			this._memory.setUint8(this._size, 0);
		}
		this._size = this._size + (1);
		return 1;
	},
	WriteInt : function(value) {
		this.ResizeMemory(4);
		this._memory.setInt32(this._size, value, true);
		this._size = this._size + (4);
		return 4;
	},
	WriteLong : function(value) {
		throw new Error("not suppert long");
	},
	WriteString : function(value) {
		this.ResizeMemory(value.length * 4 + 5);
		let old_size = this._size;
		this._size = this._size + (4);
		let new_data = StringToUTF8Array(value);
		let new_memory = new DataView(new_data.buffer);
		for (let i = 0; i < new_memory.byteLength; i += 1) {
			this._memory.setUint8(this._size, new_memory.getUint8(i));
			++ this._size;
		}
		let str_len = this._size - 4 - old_size;
		this._memory.setUint32(old_size, str_len + 1, true);
		this._memory.setUint8(this._size, 0);
		this._size = this._size + (1);
		return str_len + 4 + 1;
	},
	WriteDouble : function(value) {
		this.ResizeMemory(8);
		this._memory.setFloat64(this._size, value, true);
		this._size = this._size + (8);
		return 8;
	},
	GetArrayBuffer : function(head) {
		if (head) {
			let new_data = new ArrayBuffer(this._size + 12);
			let new_view = new DataView(new_data);
			new_view.setInt32(0, this._size, true);
			new_view.setInt32(4, this._id, true);
			new_view.setInt32(8, this._rpc_id, true);
			for (let i = 0; i < this._size; i += 1) {
				new_view.setUint8(12 + i, this._memory.getUint8(i));
			}
			return new_data;
		} else {
			let new_data = new ArrayBuffer(this._size);
			let new_view = new DataView(new_data);
			for (let i = 0; i < this._size; i += 1) {
				new_view.setUint8(i, this._memory.getUint8(i));
			}
			return new_data;
		}
	},
	WriteToStdFile : function(file_path) {
		let buffer = this.GetArrayBuffer(false);
		return JavaScript.File_SaveFile(file_path, undefined, buffer);
	},
}, "JavaScript.JMessageWriteFactory");

if (ALittle.IMessageReadFactory === undefined) throw new Error(" extends class:ALittle.IMessageReadFactory is undefined");
JavaScript.JMessageReadFactory = JavaScript.Class(ALittle.IMessageReadFactory, {
	Ctor : function(data, offset, head) {
		this._memory = data;
		this._offset = offset;
		this._total_size = data.byteLength;
		this._read_size = 0;
		if (head) {
			this._data_size = this.ReadInt();
			this._id = this.ReadInt();
			this._rpc_id = this.ReadInt();
		} else {
			this._data_size = data.byteLength;
			this._id = 0;
			this._rpc_id = 0;
		}
		this._last_read_size = 0;
	},
	GetID : function() {
		return this._id;
	},
	GetRpcID : function() {
		return this._rpc_id;
	},
	GetDataSize : function() {
		return this._data_size;
	},
	ReadBool : function() {
		if (this._read_size >= this._total_size || this._read_size < 0) {
			this._last_read_size = -1;
			ALittle.Error("id: " + this._id + " already read completed:" + this._total_size + ", " + this._read_size);
			return false;
		}
		let value = this._memory.getUint8(this._read_size);
		this._read_size = this._read_size + (1);
		this._last_read_size = 1;
		return value !== 0;
	},
	ReadInt : function() {
		if (this._read_size >= this._total_size || this._read_size < 0) {
			this._last_read_size = -1;
			ALittle.Error("id: " + this._id + " already read completed:" + this._total_size + ", " + this._read_size);
			return 0;
		}
		let value = this._memory.getInt32(this._read_size, true);
		this._read_size = this._read_size + (4);
		this._last_read_size = 4;
		return value;
	},
	ReadLong : function() {
		ALittle.Error("id: " + this._id + " not support long");
		return 0;
	},
	ReadString : function() {
		if (this._read_size >= this._total_size || this._read_size < 0) {
			this._last_read_size = -1;
			ALittle.Log("id:" + this._id + " already read completed:" + this._total_size + ", " + this._read_size);
			return "";
		}
		let len = this._memory.getInt32(this._read_size, true);
		if (len <= 0) {
			this._last_read_size = -1;
			ALittle.Error("id:" + this._id + " string len: " + len + " is error:" + this._total_size + ", " + this._read_size);
			return "";
		}
		this._read_size = this._read_size + (4);
		let value = "";
		if (len > 1) {
			value = UTF8ArrayToString(new Uint8Array(this._memory.buffer, this._offset + this._read_size, len - 1));
		}
		this._read_size = this._read_size + (len);
		this._last_read_size = len + 4;
		return value;
	},
	ReadDouble : function() {
		if (this._read_size >= this._total_size || this._read_size < 0) {
			this._last_read_size = -1;
			ALittle.Error("id: " + this._id + " already read completed:" + this._total_size + ", " + this._read_size);
			return 0;
		}
		let value = this._memory.getFloat64(this._read_size, true);
		this._read_size = this._read_size + (8);
		this._last_read_size = 8;
		return value;
	},
	GetReadSize : function() {
		return this._last_read_size;
	},
}, "JavaScript.JMessageReadFactory");

}
{
if (typeof JavaScript === "undefined") window.JavaScript = {};


JavaScript.JNetBuffer = JavaScript.Class(undefined, {
	Ctor : function(init_size) {
		this._msize = 0;
		this._dstart = 0;
		this._dsize = 0;
		let data = new ArrayBuffer(init_size);
		this._memory = new DataView(data);
	},
	Add : function(array_buffer) {
		let data_view = new DataView(array_buffer);
		this.Resize(data_view.byteLength);
		for (let i = 0; i < data_view.byteLength; i += 1) {
			this._memory.setUint8(this._dstart + this._dsize, data_view.getUint8(i));
			++ this._dsize;
		}
	},
	Read : function() {
		if (this._dsize < 12) {
			return [undefined, 0];
		}
		if (this._dsize >= 4) {
			this._msize = this._memory.getUint32(this._dstart, true);
		}
		if (this._dsize - 12 >= this._msize) {
			let offset = this._dstart;
			let data = new DataView(this._memory.buffer, this._dstart, this._msize + 12);
			this._dstart = this._dstart + (this._msize + 12);
			this._dsize = this._dsize - (this._msize + 12);
			return [data, offset];
		}
		return [undefined, 0];
	},
	Optimizes : function() {
		if (this._dstart < 100) {
			return;
		}
		let start = this._dstart;
		let endv = this._dstart + this._dsize;
		for (let i = start; i < endv; i += 1) {
			this._memory.setUint8(i - this._dsize, this._memory.getUint8(i));
		}
		this._dstart = 0;
	},
	Resize : function(add_size) {
		let need_size = this._dstart + this._dsize + add_size;
		if (need_size <= this._memory.byteLength) {
			return;
		}
		let new_data = undefined;
		if (this._memory.byteLength * 2 < need_size) {
			new_data = new ArrayBuffer(need_size);
		} else {
			new_data = new ArrayBuffer(this._memory.byteLength * 2);
		}
		let new_memory = new DataView(new_data);
		for (let i = 0; i < this._memory.byteLength; i += 1) {
			new_memory.setUint8(i, this._memory.getUint8(i));
		}
		this._memory = new_memory;
	},
}, "JavaScript.JNetBuffer");

JavaScript.JConnectStatus = {
	NET_IDLE : 0,
	NET_CONNECTING : 1,
	NET_CONNECTED : 2,
}

let __JMSG_MAXID = 0;
if (ALittle.IMsgCommonNative === undefined) throw new Error(" extends class:ALittle.IMsgCommonNative is undefined");
JavaScript.JMsgInterface = JavaScript.Class(ALittle.IMsgCommonNative, {
	Ctor : function() {
		++ __JMSG_MAXID;
		this._id = __JMSG_MAXID;
		this._net_status = 0;
		this._ip = "";
		this._port = 0;
		this._net_buffer = ALittle.NewObject(JavaScript.JNetBuffer, 2048);
	},
	GetID : function() {
		return this._id;
	},
	Connect : function(ip, port) {
		if (this._net_status === 2) {
			this.Close();
		}
		if (this._net_status === 1) {
			ALittle.Warn("net system already connecting:" + this._ip + ":" + this._port);
			return;
		}
		let url = "ws://" + ip + ":" + port;
		this._net_status = 1;
		this._net_system = new WebSocket(url);
		this._net_system.binaryType = "arraybuffer";
		this._net_system.onmessage = this.HandleMessage.bind(this);
		this._net_system.onopen = this.HandleOpen.bind(this);
		this._net_system.onclose = this.HandleClose.bind(this);
		this._net_system.onerror = this.HandleError.bind(this);
	},
	IsConnected : function() {
		return this._net_status === 2;
	},
	SendFactory : function(factory) {
		this._net_system.send(factory.GetArrayBuffer(true));
	},
	Close : function() {
		if (this._net_status === 0) {
			return;
		}
		this._net_system.close();
		this._net_system = undefined;
		this._net_status = 0;
	},
	HandleOpen : function(event) {
		if (this._net_status !== 1) {
			return;
		}
		this._net_status = 2;
		ALittle.__ALITTLEAPI_ConnectSucceed(this._id);
	},
	HandleClose : function(event) {
		if (this._net_status !== 2) {
			return;
		}
		this._net_status = 0;
		this._net_system = undefined;
		ALittle.__ALITTLEAPI_Disconnected(this._id);
	},
	HandleError : function(event) {
		if (this._net_status !== 1) {
			return;
		}
		this._net_status = 0;
		this._net_system = undefined;
		ALittle.__ALITTLEAPI_ConnectFailed(this._id);
	},
	HandleMessage : function(event) {
		if (event.data === undefined) {
			return;
		}
		this._net_buffer.Add(event.data);
		while (true) {
			let [data, offset] = this._net_buffer.Read();
			if (data === undefined) {
				break;
			}
			let factory = ALittle.NewObject(JavaScript.JMessageReadFactory, data, offset, true);
			ALittle.__ALITTLEAPI_Message(this._id, factory.GetID(), factory.GetRpcID(), factory);
		}
		this._net_buffer.Optimizes();
	},
}, "JavaScript.JMsgInterface");

}
{
if (typeof JavaScript === "undefined") window.JavaScript = {};


if (ALittle.ISchedule === undefined) throw new Error(" extends class:ALittle.ISchedule is undefined");
JavaScript.JSchedule = JavaScript.Class(ALittle.ISchedule, {
	Ctor : function() {
		let global = window;
		this._requestAnimationFrame = global["requestAnimationFrame"];
		if (this._requestAnimationFrame === undefined) {
			this._requestAnimationFrame = global["mozRequestAnimationFrame"];
		}
		if (this._requestAnimationFrame === undefined) {
			this._requestAnimationFrame = global["webkitRequestAnimationFrame"];
		}
		if (this._requestAnimationFrame === undefined) {
			this._requestAnimationFrame = global["msRequestAnimationFrame"];
		}
		this._callback = this.MainLoop.bind(this);
		this._run = false;
	},
	Run : function() {
		this.RunInFrame();
	},
	RunInFrame : function() {
		if (this._run) {
			return;
		}
		this._run = true;
		if (this._requestAnimationFrame !== undefined) {
			this._requestAnimationFrame.call(window, this._callback);
		} else {
			ALittle.Error("current browser is not support requestAnimationFrame");
		}
	},
	MainLoop : function(cur_time) {
		if (this._last_time === undefined) {
			this._last_time = cur_time;
			return;
		}
		A_JLoopSystem.Update(cur_time - this._last_time);
		this._last_time = cur_time;
		this._requestAnimationFrame.call(window, this._callback);
	},
}, "JavaScript.JSchedule");

window.A_JSchedule = ALittle.NewObject(JavaScript.JSchedule);
}
{
if (typeof JavaScript === "undefined") window.JavaScript = {};


if (ALittle.ICsvFile === undefined) throw new Error(" extends class:ALittle.ICsvFile is undefined");
JavaScript.JCsvFile = JavaScript.Class(ALittle.ICsvFile, {
	Ctor : function() {
		this._row_count = 0;
		this._col_count = 0;
		this._file_path = "";
	},
	addRow : function(row) {
		if (this._col_count === 0) {
			++ this._row_count;
			this._data[this._row_count - 1] = row;
			this._col_count = row.length;
			return true;
		}
		if (row.length !== this._col_count) {
			ALittle.Error("row(" + ((this._row_count + 1)) + ") col: " + row.length + " != " + this._col_count);
			return false;
		}
		++ this._row_count;
		this._data[this._row_count - 1] = row;
		return true;
	},
	Load : function(path) {
		let [content] = JavaScript.File_LoadFile(path);
		if (content === undefined) {
			ALittle.Error("file load failed:" + path);
			return false;
		}
		this._file_path = path;
		this._data = [];
		let data_index = 1;
		let char_index = 0;
		if (char_index >= content.length) {
			ALittle.Error("file is empty:" + this._file_path);
			return false;
		}
		let cur_char = content.charCodeAt(char_index);
		++ char_index;
		if (char_index >= content.length) {
			this._data[1 - 1] = [];
			this._data[1 - 1][1 - 1] = String.fromCharCode(cur_char);
			return true;
		}
		let next_char = content.charCodeAt(char_index);
		let in_quote = false;
		let row = [];
		let row_index = 0;
		let cell = "";
		while (true) {
			if (cur_char === 44) {
				if (in_quote) {
					cell = cell + ",";
					if (next_char === undefined) {
						ALittle.Error("row(" + this._row_count + ") have no close quote");
						return false;
					}
				} else {
					++ row_index;
					row[row_index - 1] = cell;
					cell = "";
					if (next_char === undefined) {
						++ row_index;
						row[row_index - 1] = "";
						if (!this.addRow(row)) {
							return false;
						}
						row_index = 0;
						row = [];
					}
				}
			} else if (cur_char === 10) {
				if (in_quote) {
					cell = cell + "\n";
					if (next_char === undefined) {
						ALittle.Error("row(" + this._row_count + ") have no close quote");
						return false;
					}
				} else {
					++ row_index;
					row[row_index - 1] = cell;
					cell = "";
					if (!this.addRow(row)) {
						return false;
					}
					row_index = 0;
					row = [];
				}
			} else if (cur_char === 34) {
				if (in_quote) {
					if (next_char === 34) {
						cell = cell + "\"";
						next_char = undefined;
						if (char_index + 1 < content.length) {
							++ char_index;
							next_char = content.charCodeAt(char_index);
						}
						if (next_char === undefined) {
							ALittle.Error("row(" + this._row_count + ") have no close quote");
							return false;
						}
					} else {
						in_quote = false;
						if (next_char === undefined) {
							++ row_index;
							row[row_index - 1] = cell;
							cell = "";
							if (!this.addRow(row)) {
								return false;
							}
							row_index = 0;
							row = [];
						}
					}
				} else {
					if (cell.length === 0) {
						in_quote = true;
					} else {
						cell = cell + "\"";
					}
					if (next_char === undefined) {
						ALittle.Error("row(" + this._row_count + ") have no close quote");
						return false;
					}
				}
			} else {
				if (in_quote) {
					cell = cell + String.fromCharCode(cur_char);
					if (next_char === undefined) {
						ALittle.Error("row(" + this._row_count + ") have no close quote");
						return false;
					}
				} else {
					if (!(cur_char === 13 && next_char === 10)) {
						cell = cell + String.fromCharCode(cur_char);
					}
					if (next_char === undefined) {
						++ row_index;
						row[row_index - 1] = cell;
						cell = "";
						if (!this.addRow(row)) {
							return false;
						}
						row_index = 0;
						row = [];
					}
				}
			}
			if (next_char === undefined) {
				break;
			}
			cur_char = next_char;
			next_char = undefined;
			if (char_index + 1 < content.length) {
				++ char_index;
				next_char = content.charCodeAt(char_index);
			}
		}
		return true;
	},
	Close : function() {
		this._data = undefined;
		this._row_count = 0;
		this._col_count = 0;
	},
	GetPath : function() {
		return this._file_path;
	},
	ReadCell : function(row, col) {
		return this._data[row - 1][col - 1];
	},
	GetRowCount : function() {
		return this._row_count;
	},
	GetColCount : function() {
		return this._col_count;
	},
}, "JavaScript.JCsvFile");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.ILoopSystem === undefined) throw new Error(" extends class:ALittle.ILoopSystem is undefined");
ALittle.LoopSystem = JavaScript.Class(ALittle.ILoopSystem, {
	Ctor : function(weak) {
		if (weak) {
			this._loop_updaters = ALittle.CreateKeyWeakMap();
		} else {
			this._loop_updaters = new Map();
		}
		this._in_update = false;
		this._loop_cache = new Map();
		this._cache_empty = true;
		this._timer = ALittle.NewObject(this.__class.__element[0]);
		this._handler_map = new Map();
	},
	Sleep : function(ms_time) {
		return new Promise((function(___COROUTINE, ___) {
			this.AddTimer(ms_time, this.HandleSleep.bind(this, ___COROUTINE));
			return;
			___COROUTINE();
		}).bind(this));
	},
	HandleSleep : function(thread) {
		ALittle.Coroutine.Resume(thread);
	},
	AddUpdater : function(updater) {
		if (updater === undefined) {
			return;
		}
		if (this._in_update) {
			this._cache_empty = false;
			this._loop_cache.set(updater, true);
		} else {
			this._loop_updaters.set(updater, true);
		}
	},
	RemoveUpdater : function(updater) {
		if (updater === undefined) {
			return;
		}
		if (this._in_update) {
			this._cache_empty = false;
			this._loop_cache.set(updater, false);
		} else {
			this._loop_updaters.delete(updater);
		}
	},
	HasUpdater : function(updater) {
		return this._loop_updaters.get(updater) !== undefined || this._loop_cache.get(updater) === true;
	},
	AddTimer : function(delay_ms, callback, loop, interval_ms) {
		if (callback === undefined) {
			return 0;
		}
		if (loop === undefined) {
			loop = 1;
		}
		if (interval_ms === undefined) {
			interval_ms = 1;
		}
		let id = this._timer.Add(delay_ms, loop, interval_ms);
		this._handler_map.set(id, callback);
		return id;
	},
	RemoveTimer : function(id) {
		if (id === undefined) {
			return false;
		}
		this._handler_map.delete(id);
		return this._timer.Remove(id);
	},
	Update : function(frame_time) {
		this._in_update = true;
		let remove_map = undefined;
		for (let [updater, v] of this._loop_updaters) {
			if (v === undefined) continue;
			if (updater.IsCompleted()) {
				if (remove_map === undefined) {
					remove_map = new Map();
				}
				remove_map.set(updater, true);
			} else {
				updater.Update(frame_time);
			}
		}
		if (remove_map !== undefined) {
			for (let [updater, v] of remove_map) {
				if (v === undefined) continue;
				this._loop_updaters.delete(updater);
				updater.Completed();
			}
		}
		if (!this._cache_empty) {
			for (let [updater, v] of this._loop_cache) {
				if (v === undefined) continue;
				if (v) {
					this._loop_updaters.set(updater, true);
				} else {
					this._loop_updaters.delete(updater);
				}
			}
			this._loop_cache = new Map();
			this._cache_empty = true;
		}
		this._in_update = false;
		this._timer.Update(frame_time);
		while (true) {
			let id = this._timer.Poll();
			if (id === 0) {
				break;
			}
			if (id < 0) {
				let handle = this._handler_map.get(-id);
				if (handle !== undefined) {
					this._handler_map.delete(-id);
					handle();
				}
			} else {
				let handle = this._handler_map.get(id);
				if (handle !== undefined) {
					handle();
				}
			}
		}
	},
}, "ALittle.LoopSystem");

window.A_JLoopSystem = ALittle.NewObject(JavaScript.Template(ALittle.LoopSystem, "ALittle.LoopSystem<JavaScript.JHeapTimer>", JavaScript.JHeapTimer));
window.A_JWeakLoopSystem = ALittle.NewObject(JavaScript.Template(ALittle.LoopSystem, "ALittle.LoopSystem<JavaScript.JHeapTimer>", JavaScript.JHeapTimer), true);
let GetLoopSystem = function() {
	return A_JLoopSystem;
}

let GetWeakLoopSystem = function() {
	return A_JWeakLoopSystem;
}

window.A_LoopSystem = GetLoopSystem();
window.A_WeakLoopSystem = GetWeakLoopSystem();
}
{
if (typeof ALittle === "undefined") window.ALittle = {};


let GetSchedule = function() {
	return A_JSchedule;
}

window.A_Schedule = GetSchedule();
}