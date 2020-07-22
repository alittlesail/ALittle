{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.List_MaxN = function(list) {
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

ALittle.List_PushList = function(list, other_list) {
	let ___OBJECT_1 = other_list;
	for (let index = 1; index <= ___OBJECT_1.length; ++index) {
		let other = ___OBJECT_1[index - 1];
		if (other === undefined) break;
		ALittle.List_Push(list, other);
	}
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