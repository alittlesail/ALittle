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

ALittle.String_Split = function(target, sep) {
	if (target === undefined || target === "") {
		return [];
	}
	if (sep === undefined || sep === "") {
		sep = ",";
	}
	let fields = [];
	let fields_count = 0;
	let start_pos = 1;
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