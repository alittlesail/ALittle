{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.String_JsonEncode = function(object) {
	return JSON.stringify(object);
}

ALittle.String_JsonDecode = function(text) {
	return JSON.parse(text);
}

ALittle.String_MD5 = function(text) {
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
		if (ALittle.List_MaxN(value_split_list) === 2) {
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