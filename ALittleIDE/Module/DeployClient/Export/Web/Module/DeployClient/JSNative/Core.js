{


let JSRequire = function(base_path, url, thread) {
	if (typeof(importScripts) !== "undefined") {
		importScripts("../../../" + base_path + url);
		thread(undefined);
		return;
	}
	if (typeof(require) !== "undefined") {
		require("../../../" + base_path + url);
		thread(undefined);
		return;
	}
	let script = document.createElement("script");
	script.type = "text/javascript";
	script.async = "async";
	let error = thread.bind("load failed:" + url);
	script.onabort = error;
	script.onerror = error;
	script.ontimeout = error;
	script.onload = thread.bind(undefined);
	script.src = base_path + url + ".js";
	document.body.appendChild(script);
}

window.Require = function(base_path, url) {
	return new Promise(function(___COROUTINE, ___) {
		JSRequire(base_path, url, ___COROUTINE);
		return;
	});
}

window.RunScript = function(script, path) {
	eval(script);
}

window.RequireFromPaths = function(base_path, rel_path, file_list) {
	return new Promise(async function(___COROUTINE, ___) {
		let ___OBJECT_1 = file_list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let path = ___OBJECT_1[index - 1];
			if (path === undefined) break;
			path = path.substring(0, path.length - 8);
			await Require(base_path, rel_path + path);
		}
		___COROUTINE();
	});
}

window.A_CoreBasePath = undefined;
window.RequireCore = function(base_path) {
	return new Promise(async function(___COROUTINE, ___) {
		A_CoreBasePath = base_path;
		await Require(base_path, "Core/Base");
		await Require(base_path, "Core/Reflect");
		await Require(base_path, "Core/JavaScript");
		await Require(base_path, "Core/Log");
		await Require(base_path, "Core/List");
		await Require(base_path, "Core/Map");
		await Require(base_path, "Core/Math");
		await Require(base_path, "Core/String");
		await Require(base_path, "Core/Time");
		await Require(base_path, "Core/Coroutine");
		await Require(base_path, "Core/Net");
		await Require(base_path, "Core/Worker");
		___COROUTINE();
	});
}

}
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
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(1847150134, "ALittle.StructInfo", {
name : "ALittle.StructInfo", ns_name : "ALittle", rl_name : "StructInfo", hash_code : 1847150134,
name_list : ["name","ns_name","rl_name","hash_code","name_list","type_list","option_map"],
type_list : ["string","string","string","int","List<string>","List<string>","Map<string,string>"],
option_map : {}
})
ALittle.RegStruct(318154964, "ALittle.ClassInfo", {
name : "ALittle.ClassInfo", ns_name : "ALittle", rl_name : "ClassInfo", hash_code : 318154964,
name_list : ["__name","__super","__element","__child","__getter","__setter"],
type_list : ["string","ALittle.ClassInfo","List<ALittle.ClassInfo>","Map<string,ALittle.ClassInfo>","Map<string,Functor<(any):any>>","Map<string,Functor<(any,any)>>"],
option_map : {}
})

ALittle.NewObject = function(clazz, ...___args) {
	return JavaScript.NewObject(clazz, ...___args);
}

ALittle.Cast = function(T, O, object) {
	if (object === undefined) {
		return undefined;
	}
	let o_info = (object).__class;
	let t_info = T;
	while (o_info !== undefined && o_info !== t_info) {
		o_info = o_info.__super;
	}
	if (o_info === undefined) {
		return undefined;
	}
	return object;
}

}
{
if (typeof JavaScript === "undefined") window.JavaScript = {};


JavaScript.CloneProperty = function(clazz, copy_ctor) {
	let new_clazz = {};
	new_clazz.__super = clazz.__super;
	new_clazz.__name = clazz.__name;
	let setter_map = {};
	let getter_map = {};
	new_clazz.__setter = setter_map;
	new_clazz.__getter = getter_map;
	let ___OBJECT_1 = clazz;
	for (let name in ___OBJECT_1) {
		// 因为for使用了Native修饰，不做undefined处理
		// let _ = ___OBJECT_1[name];
		// if (_ === undefined) continue;
		if (!copy_ctor && name === "Ctor") {
			continue;
		}
		if (name !== "__super" && name !== "__getter" && name !== "__setter") {
			let info = Object.getOwnPropertyDescriptor(clazz, name);
			if (info["set"] !== undefined || info["get"] !== undefined) {
				Object.defineProperty(new_clazz, name, info);
			}
			if (info["set"] !== undefined) {
				setter_map[name] = info["set"];
			}
			if (info["get"] !== undefined) {
				getter_map[name] = info["get"];
			}
			if (info["set"] === undefined && info["get"] === undefined) {
				new_clazz[name] = clazz[name];
			}
		}
	}
	return new_clazz;
}

JavaScript.Class = function(drived, clazz_prop, clazz_name) {
	let clazz = undefined;
	if (drived !== undefined) {
		clazz = JavaScript.CloneProperty(drived, false);
		clazz.__super = drived;
	} else {
		clazz = {};
		clazz.__setter = {};
		clazz.__getter = {};
	}
	clazz.__name = clazz_name;
	let setter_map = clazz.__setter;
	let getter_map = clazz.__getter;
	let ___OBJECT_2 = clazz_prop;
	for (let name in ___OBJECT_2) {
		// 因为for使用了Native修饰，不做undefined处理
		// let _ = ___OBJECT_2[name];
		// if (_ === undefined) continue;
		let info = Object.getOwnPropertyDescriptor(clazz_prop, name);
		if (info["get"] === undefined && info["set"] === undefined) {
			clazz[name] = clazz_prop[name];
		} else {
			if (info["get"] !== undefined && info["set"] === undefined) {
				getter_map[name] = info["get"];
				if (setter_map[name] !== undefined) {
					info["set"] = setter_map[name];
				}
				Object.defineProperty(clazz, name, info);
			} else {
				if (info["get"] === undefined && info["set"] !== undefined) {
					setter_map[name] = info["set"];
					if (getter_map[name] !== undefined) {
						info["get"] = getter_map[name];
					}
					Object.defineProperty(clazz, name, info);
				} else {
					getter_map[name] = info["get"];
					setter_map[name] = info["set"];
					Object.defineProperty(clazz, name, info);
				}
			}
		}
	}
	return clazz;
}

JavaScript.Template = function(clazz, name, ...___args) {
	let child = clazz.__child;
	if (child === undefined) {
		child = {};
		clazz.__child = child;
	}
	let template = child[name];
	if (template !== undefined) {
		return template;
	}
	template = JavaScript.CloneProperty(clazz, true);
	child[name] = template;
	template.__name = name;
	template.__element = [...___args];
	return template;
}

JavaScript.ClassCtor = function(object, clazz, ...___args) {
	let drived = clazz.__super;
	if (drived !== undefined) {
		JavaScript.ClassCtor(object, drived, ...___args);
	}
	let fctor = clazz["Ctor"];
	if (fctor !== undefined) {
		fctor.call(object, ...___args);
	}
}

JavaScript.NewObject = function(clazz, ...___args) {
	let object = Object.create(clazz);
	object["__class"] = clazz;
	JavaScript.ClassCtor(object, clazz, ...___args);
	return object;
}

JavaScript.Assert = function(value, msg) {
	if (value !== undefined && value !== false) {
		return;
	}
	if (msg === undefined) {
		msg = "Assert failed";
	}
	throw new Error(msg);
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.LogLevel = {
	INFO : 0,
	WARN : 1,
	ERROR : 2,
}

let __LOG_FUNC = undefined;
ALittle.SetLogFunc = function(func) {
	__LOG_FUNC = func;
}

ALittle.Log = function(...___args) {
	if (__LOG_FUNC !== undefined) {
		let slist = [...___args];
		let ___OBJECT_1 = slist;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let value = ___OBJECT_1[index - 1];
			if (value === undefined) break;
			slist[index - 1] = ALittle.String_ToString(value);
		}
		let s = ALittle.String_Join(slist, "\t");
		__LOG_FUNC(s, 0);
		return;
	}
	console.log(...___args);
}

ALittle.Warn = function(...___args) {
	if (__LOG_FUNC !== undefined) {
		let slist = [...___args];
		let ___OBJECT_2 = slist;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let value = ___OBJECT_2[index - 1];
			if (value === undefined) break;
			slist[index - 1] = ALittle.String_ToString(value);
		}
		let s = ALittle.String_Join(slist, "\t");
		__LOG_FUNC(s, 1);
		return;
	}
	console.warn(...___args);
}

ALittle.Error = function(...___args) {
	if (__LOG_FUNC !== undefined) {
		let slist = [...___args];
		let ___OBJECT_3 = slist;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let value = ___OBJECT_3[index - 1];
			if (value === undefined) break;
			slist[index - 1] = ALittle.String_ToString(value);
		}
		let s = ALittle.String_Join(slist, "\t");
		__LOG_FUNC(s, 2);
		return;
	}
	console.error(...___args);
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.List_Len = function(list) {
	return list.length;
}

ALittle.List_Push = function(list, object) {
	for (let i = 1; i <= list.length; i += 1) {
		if (list[i - 1] === undefined) {
			list[i - 1] = object;
			return;
		}
	}
	list.push(object);
}

ALittle.List_Shuffle = function(list) {
	let len = ALittle.List_Len(list);
	for (let i = 1; i <= len; i += 1) {
		let index = ALittle.Math_RandomInt(i, len);
		let temp = list[index - 1];
		list[index - 1] = list[i - 1];
		list[i - 1] = temp;
	}
}

ALittle.List_PushList = function(list, other_list) {
	let ___OBJECT_1 = other_list;
	for (let index = 1; index <= ___OBJECT_1.length; ++index) {
		let other = ___OBJECT_1[index - 1];
		if (other === undefined) break;
		ALittle.List_Push(list, other);
	}
}

ALittle.List_Find = function(list, object) {
	let ___OBJECT_2 = list;
	for (let index = 1; index <= ___OBJECT_2.length; ++index) {
		let o = ___OBJECT_2[index - 1];
		if (o === undefined) break;
		if (o === object) {
			return index;
		}
	}
	return undefined;
}

ALittle.List_Copy = function(list) {
	let new_list = [];
	let ___OBJECT_3 = list;
	for (let index = 1; index <= ___OBJECT_3.length; ++index) {
		let o = ___OBJECT_3[index - 1];
		if (o === undefined) break;
		new_list[index - 1] = o;
	}
	return new_list;
}

ALittle.List_Insert = function(list, index, object) {
	list.splice(index - 1, 0, object);
}

ALittle.List_IndexOf = function(list, object) {
	let index = list.indexOf(object);
	if (index < 0) {
		return undefined;
	} else {
		return index + 1;
	}
}

ALittle.List_Remove = function(list, index) {
	list.splice(index - 1, 1);
}

ALittle.List_Splice = function(list, index, count) {
	list.splice(index - 1, count);
}

ALittle.List_Sort = function(list, cmp) {
	list.sort(cmp);
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IsEmpty = function(object) {
	if (object.__proto__.constructor === Map) {
		return object.size === 0;
	}
	if (object.__proto__.constructor === Object) {
		let has = true;
		let ___OBJECT_1 = object;
		for (let key in ___OBJECT_1) {
			let value = ___OBJECT_1[key];
			if (value === undefined) continue;
			has = false;
			break;
		}
		return has;
	}
	return false;
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.Math_Min = function(x, y) {
	if (x < y) {
		return x;
	}
	return y;
}

ALittle.Math_Max = function(x, y) {
	if (x < y) {
		return y;
	}
	return x;
}

ALittle.Math_Sin = function(v) {
	return Math.sin(v);
}

ALittle.Math_Tan = function(v) {
	return Math.tan(v);
}

ALittle.Math_Cos = function(v) {
	return Math.cos(v);
}

ALittle.Math_Abs = function(v) {
	return Math.abs(v);
}

ALittle.Math_Floor = function(v) {
	return Math.floor(v);
}

ALittle.Math_Ceil = function(v) {
	return Math.ceil(v);
}

ALittle.Math_Sqrt = function(v) {
	return Math.sqrt(v);
}

ALittle.Math_ToInt = function(s) {
	let value = parseInt(s);
	if (isNaN(value)) {
		return undefined;
	} else {
		return value;
	}
}

ALittle.Math_ToIntOrZero = function(s) {
	let value = ALittle.Math_ToInt(s);
	if (value === undefined) {
		return 0;
	}
	return value;
}

ALittle.Math_ToDouble = function(s) {
	let value = parseFloat(s);
	if (isNaN(value)) {
		return undefined;
	} else {
		return value;
	}
}

ALittle.Math_ToDoubleOrZero = function(s) {
	let value = ALittle.Math_ToDouble(s);
	if (value === undefined) {
		return 0;
	}
	return value;
}

ALittle.Math_RandomSeed = function(seed) {
}

ALittle.Math_RandomInt = function(min, max) {
	return Math.floor(Math.random() * (max - min + 1)) + min;
}

ALittle.Math_RandomDouble = function(min, max) {
	return Math.random() * (max - min) + min;
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.String_Upper = function(s) {
	return s.toUpperCase();
}

ALittle.String_Lower = function(s) {
	return s.toLowerCase();
}

ALittle.String_ToString = function(s) {
	if (s === undefined) {
		return "nil";
	} else {
		return s.toString();
	}
}

ALittle.String_Byte = function(s, index) {
	return s.charCodeAt(index - 1);
}

ALittle.String_Type = function(v) {
	let value = typeof(v);
	if (value === "object") {
		return "table";
	} else {
		return value;
	}
}

ALittle.String_Len = function(s) {
	return s.length;
}

ALittle.String_Find = function(s, t, init) {
	if (init === undefined) {
		let index = s.indexOf(t);
		if (index >= 0) {
			return index + 1;
		} else {
			return undefined;
		}
	} else {
		let index = s.indexOf(t, init - 1);
		if (index >= 0) {
			return index + 1;
		} else {
			return undefined;
		}
	}
}

ALittle.String_Sub = function(s, starti, endi) {
	if (endi === undefined) {
		return s.slice(starti - 1);
	} else if (endi >= 0) {
		return s.slice(starti - 1, endi);
	} else {
		return s.slice(starti - 1, s.length + endi + 1);
	}
}

ALittle.String_Trim = function(text) {
	return text.trim();
}

ALittle.String_Split = function(target, sep, start_pos) {
	if (target === undefined || target === "") {
		return [];
	}
	if (sep === undefined || sep === "") {
		sep = ",";
	}
	let fields = [];
	let fields_count = 0;
	if (start_pos === undefined) {
		start_pos = 1;
	}
	while (true) {
		let start_index = ALittle.String_Find(target, sep, start_pos);
		if (start_index === undefined) {
			++ fields_count;
			fields[fields_count - 1] = ALittle.String_Sub(target, start_pos);
			break;
		}
		++ fields_count;
		fields[fields_count - 1] = ALittle.String_Sub(target, start_pos, start_index - 1);
		start_pos = start_index + ALittle.String_Len(sep);
	}
	return fields;
}

ALittle.String_SplitSepList = function(target, sep_list) {
	if (target === undefined || target === "") {
		return [];
	}
	if (sep_list === undefined) {
		sep_list = [];
	}
	let fields = [];
	let fields_count = 0;
	let start_pos = 1;
	while (true) {
		let start_index = undefined;
		let end_index = undefined;
		let ___OBJECT_1 = sep_list;
		for (let _ = 1; _ <= ___OBJECT_1.length; ++_) {
			let sep = ___OBJECT_1[_ - 1];
			if (sep === undefined) break;
			let start_index_tmp = ALittle.String_Find(target, sep, start_pos);
			if (start_index_tmp !== undefined) {
				if (start_index === undefined || start_index_tmp < start_index) {
					start_index = start_index_tmp;
					end_index = start_index + ALittle.String_Len(sep) - 1;
				}
			}
		}
		if (start_index === undefined) {
			let value = ALittle.String_Sub(target, start_pos);
			if (ALittle.String_Len(value) > 0) {
				++ fields_count;
				fields[fields_count - 1] = ALittle.String_Sub(target, start_pos);
			}
			break;
		}
		let value = ALittle.String_Sub(target, start_pos, start_index - 1);
		if (ALittle.String_Len(value) > 0) {
			++ fields_count;
			fields[fields_count - 1] = ALittle.String_Sub(target, start_pos, start_index - 1);
		}
		start_pos = end_index + 1;
	}
	return fields;
}

ALittle.String_Join = function(list, sep) {
	return list.join(sep);
}

ALittle.String_Replace = function(s, os, ns) {
	return s.replace(os, ns);
}

ALittle.String_CopyTable = function(info) {
	{
		if (typeof(info) === "object") {
			if (info.__proto__.constructor === Array) {
				let new_info = [];
				let ___OBJECT_2 = info;
				for (let key = 1; key <= ___OBJECT_2.length; ++key) {
					let value = ___OBJECT_2[key - 1];
					if (value === undefined) break;
					if (typeof(info) !== "object") {
						new_info[key - 1] = value;
					} else {
						new_info[key - 1] = ALittle.String_CopyTable(value);
					}
				}
				return new_info;
			}
			if (info.__proto__.constructor === Map) {
				let new_info = new Map();
				for (let [key, value] of info) {
					if (value === undefined) continue;
					if (typeof(info) !== "object") {
						new_info.set(key, value);
					} else {
						new_info.set(key, ALittle.String_CopyTable(value));
					}
				}
				return new_info;
			}
			if (info.__proto__.constructor === Object) {
				let new_info = {};
				let ___OBJECT_3 = info;
				for (let key in ___OBJECT_3) {
					let value = ___OBJECT_3[key];
					if (value === undefined) continue;
					if (typeof(info) !== "object") {
						new_info[key] = value;
					} else {
						new_info[key] = ALittle.String_CopyTable(value);
					}
				}
				return new_info;
			}
		}
		return info;
	}
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.Time_GetCurTime = function() {
	return ALittle.Math_Floor(Date.now() / 1000);
}

ALittle.Time_GetCurDate = function(time) {
	{
		let date = new Date();
		if (time !== undefined) {
			date.setTime(time * 1000);
		}
		let result = date.getFullYear() + "-";
		let month = (date.getMonth() + 1);
		if (month < 10) {
			result = result + "-0" + month;
		} else {
			result = result + "-" + month;
		}
		let day = date.getDate();
		if (day < 10) {
			result = result + "-0" + day;
		} else {
			result = result + "-" + day;
		}
		let hours = date.getHours();
		if (hours < 10) {
			result = result + "-0" + hours;
		} else {
			result = result + "-" + hours;
		}
		let minutes = date.getMinutes();
		if (minutes < 10) {
			result = result + "-0" + minutes;
		} else {
			result = result + "-" + minutes;
		}
		let seconds = date.getSeconds();
		if (seconds < 10) {
			result = result + "-0" + seconds;
		} else {
			result = result + "-" + seconds;
		}
		return result;
	}
}

ALittle.Time_GetCurYMD = function(time) {
	{
		let date = new Date();
		if (time !== undefined) {
			date.setTime(time * 1000);
		}
		let result = date.getFullYear() + "-";
		let month = (date.getMonth() + 1);
		if (month < 10) {
			result = result + "-0" + month;
		} else {
			result = result + "-" + month;
		}
		let day = date.getDate();
		if (day < 10) {
			result = result + "-0" + day;
		} else {
			result = result + "-" + day;
		}
		return result;
	}
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

ALittle.Coroutine = JavaScript.Class(undefined, {
	Resume : function(thread, ...___args) {
		let value = [...___args];
		if (value.length === 0) {
			thread();
		} else if (value.length === 1) {
			thread(value[1 - 1]);
		} else {
			thread(value);
		}
		return [true];
	},
}, "ALittle.Coroutine");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IHttpFileReceiver = JavaScript.Class(undefined, {
	StartReceiveFile : function(file_path, start_size) {
		return new Promise((function(___COROUTINE, ___) {
			___COROUTINE("not impl"); return;
		}).bind(this));
	},
}, "ALittle.IHttpFileReceiver");

let __all_file_callback = {};
ALittle.RegHttpFileCallback = function(method, callback) {
	if (__all_file_callback[method] !== undefined) {
		ALittle.Error("RegHttpFileCallback消息回调函数注册失败，名字为" + method + "已存在");
		return;
	}
	__all_file_callback[method] = callback;
}

ALittle.FindHttpFileReceiverCallback = function(method) {
	return __all_file_callback[method];
}

ALittle.IHttpFileSender = JavaScript.Class(undefined, {
	HandleSucceed : function() {
	},
	HandleProcess : function(cur_size, total_size) {
	},
	HandleFailed : function(reason) {
	},
	Stop : function() {
	},
	GetFilePath : function() {
		return undefined;
	},
	GetTotalSize : function() {
		return 0;
	},
	GetCurSize : function() {
		return 0;
	},
	SendDownloadRPC : function(thread, method, content, array_buffer) {
		throw new Error("not impl");
	},
	SendUploadRPC : function(thread, method, content, array_buffer) {
		throw new Error("not impl");
	},
	InvokeDownload : function(method, client, content, array_buffer) {
		return new Promise(function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE("当前不是协程"); return;
			}
			client.SendDownloadRPC(___COROUTINE, method, content, array_buffer);
			return;
		});
	},
	InvokeUpload : function(method, client, content, array_buffer) {
		return new Promise(function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE("当前不是协程"); return;
			}
			client.SendUploadRPC(___COROUTINE, method, content, array_buffer);
			return;
		});
	},
}, "ALittle.IHttpFileSender");

ALittle.IHttpReceiver = JavaScript.Class(undefined, {
	Ctor : function(method) {
		this._method = method;
	},
	get method() {
		return this._method;
	},
}, "ALittle.IHttpReceiver");

let __all_receiver_callback = {};
ALittle.RegHttpCallback = function(method, callback) {
	if (__all_receiver_callback[method] !== undefined) {
		ALittle.Error("RegHttpCallback消息回调函数注册失败，名字为" + method + "已存在");
		return;
	}
	__all_receiver_callback[method] = callback;
}

ALittle.FindHttpCallback = function(method) {
	return __all_receiver_callback[method];
}

let __all_download_callback = {};
let __download_callback_factory = undefined;
ALittle.RegHttpDownloadCallback = function(method, callback) {
	if (__all_download_callback[method] !== undefined) {
		ALittle.Error("RegHttpDownloadCallback消息回调函数注册失败，名字为" + method + "已存在");
		return;
	}
	__all_download_callback[method] = callback;
}

ALittle.RegHttpDownloadCallbackFactory = function(value) {
	__download_callback_factory = value;
}

ALittle.FindHttpDownloadCallback = function(method) {
	let callback = __all_download_callback[method];
	if (callback === undefined && __download_callback_factory !== undefined) {
		callback = __download_callback_factory(method);
	}
	return callback;
}

ALittle.IHttpSender = JavaScript.Class(undefined, {
	HandleSucceed : function() {
	},
	HandleFailed : function(reason) {
	},
	Stop : function() {
	},
	SendRPC : function(thread, method, content) {
		throw new Error("not impl");
	},
	Invoke : function(method, client, content) {
		return new Promise(function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE(["当前不是协程", undefined]); return;
			}
			client.SendRPC(___COROUTINE, method, content);
			return;
		});
	},
}, "ALittle.IHttpSender");

ALittle.IMessageWriteFactory = JavaScript.Class(undefined, {
	WriteToStdFile : function(file_path) {
		return false;
	},
	SetID : function(id) {
	},
	SetRpcID : function(id) {
	},
	ResetOffset : function() {
	},
	GetOffset : function() {
		return 0;
	},
	SetInt : function(offset, value) {
	},
	WriteBool : function(value) {
		return 0;
	},
	WriteInt : function(value) {
		return 0;
	},
	WriteLong : function(value) {
		return 0;
	},
	WriteString : function(value) {
		return 0;
	},
	WriteDouble : function(value) {
		return 0;
	},
}, "ALittle.IMessageWriteFactory");

ALittle.IMessageReadFactory = JavaScript.Class(undefined, {
	GetDataSize : function() {
		return 0;
	},
	ReadBool : function() {
		return false;
	},
	ReadInt : function() {
		return 0;
	},
	ReadLong : function() {
		return 0;
	},
	ReadString : function() {
		return "";
	},
	ReadDouble : function() {
		return 0;
	},
	GetReadSize : function() {
		return 0;
	},
}, "ALittle.IMessageReadFactory");

ALittle.IMsgCommon = JavaScript.Class(undefined, {
	IsConnected : function() {
		return false;
	},
	Close : function(reason) {
	},
	HandleConnectSucceed : function() {
	},
	HandleDisconnected : function() {
	},
	HandleConnectFailed : function(reason) {
	},
	HandleMessage : function(id, rpc_id, factory) {
	},
	SendMsg : function(T, msg) {
		let rflt = T;
		this.Send(rflt.hash_code, msg, 0);
	},
	Send : function(msg_id, msg_body, rpc_id) {
		throw new Error("not impl");
	},
	SendRPC : function(thread, msg_id, msg_body) {
	},
	Invoke : function(msg_id, client, msg_body) {
		client.Send(msg_id, msg_body, 0);
	},
	InvokeRPC : function(msg_id, client, msg_body) {
		return new Promise(function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE(["当前不是协程", undefined]); return;
			}
			if (!client.IsConnected()) {
				___COROUTINE(["连接还没成功", undefined]); return;
			}
			client.SendRPC(___COROUTINE, msg_id, msg_body);
			return;
		});
	},
}, "ALittle.IMsgCommon");

let __all_msg_callback = new Map();
ALittle.RegMsgCallback = function(msg_id, callback) {
	if (__all_msg_callback.get(msg_id) !== undefined) {
		ALittle.Error("RegMsgCallback消息回调函数注册失败，名字为" + msg_id + "已存在");
		return;
	}
	__all_msg_callback.set(msg_id, callback);
}

ALittle.FindMsgCallback = function(msg_id) {
	return __all_msg_callback.get(msg_id);
}

let __all_rpc_callback = new Map();
let __all_rpc_return_id = new Map();
ALittle.RegMsgRpcCallback = function(msg_id, callback, return_id) {
	if (__all_rpc_callback.get(msg_id) !== undefined) {
		ALittle.Error("RegMsgRpcCallback消息回调函数注册失败，名字为" + msg_id + "已存在");
		return;
	}
	__all_rpc_callback.set(msg_id, callback);
	__all_rpc_return_id.set(msg_id, return_id);
}

ALittle.FindMsgRpcCallback = function(msg_id) {
	return [__all_rpc_callback.get(msg_id), __all_rpc_return_id.get(msg_id)];
}

}