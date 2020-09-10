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