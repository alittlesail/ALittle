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

ALittle.List_Insert = function(list, index, object) {
	list.splice(index - 1, 0, object);
}

ALittle.List_Remove = function(list, index) {
	list.splice(index - 1, 1);
}

ALittle.List_Sort = function(list, cmp) {
	list.sort(cmp);
}

}