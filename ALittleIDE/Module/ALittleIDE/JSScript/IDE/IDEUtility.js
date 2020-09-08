{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.IDEUtility_CheckName = function(name) {
	let len = ALittle.String_Len(name);
	if (len === 0) {
		return "命名只能支持字母数字下划线，不能以数字开头";
	}
	for (let i = 1; i <= len; i += 1) {
		let byte = ALittle.String_Byte(name, i);
		let check_all = byte >= 65 && byte <= 90 || byte >= 97 && byte <= 122 || byte >= 48 && byte <= 57 || byte === 95;
		if (i === 1) {
			let check_first = byte >= 65 && byte <= 90 || byte >= 97 && byte <= 122 || byte === 95;
			if (check_first === false) {
				return "命名只能支持字母数字下划线，不能以数字开头";
			}
		} else {
			if (check_all === false) {
				return "命名只能支持字母数字下划线，不能以数字开头";
			}
		}
	}
	return undefined;
}

ALittleIDE.IDEUtility_CheckResourceName = function(name) {
	let len = ALittle.String_Len(name);
	if (len === 0) {
		return "命名只能支持字母数字下划线";
	}
	for (let i = 1; i <= len; i += 1) {
		let byte = ALittle.String_Byte(name, i);
		let check_all = byte >= 65 && byte <= 90 || byte >= 97 && byte <= 122 || byte >= 48 && byte <= 57 || byte === 95;
		if (check_all === false) {
			return "命名只能支持字母数字下划线";
		}
	}
	return undefined;
}

}