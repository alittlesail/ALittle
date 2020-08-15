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
	len = ALittle.List_MaxN(param_list);
	let need_len = ALittle.List_MaxN(info.var_list);
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