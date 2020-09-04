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

ALittle.List_Shuffle = function(list) {
	let len = ALittle.List_MaxN(list);
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