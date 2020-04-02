{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.MaxN = function(list) {
	return list.length;
}

ALittle.Push = function(list, object) {
	for (let i = 1; i <= list.length; i += 1) {
		if (list[i - 1] === undefined) {
			list[i - 1] = object;
			return;
		}
	}
	list.push(object);
}

ALittle.Insert = function(list, index, object) {
	list.splice(index - 1, 0, object);
}

ALittle.Remove = function(list, index) {
	list.splice(index - 1, 1);
}

ALittle.Sort = function(list, cmp) {
	list.sort(cmp);
}

}