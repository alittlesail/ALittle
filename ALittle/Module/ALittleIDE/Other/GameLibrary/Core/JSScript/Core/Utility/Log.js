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
	console.trace(...___args);
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